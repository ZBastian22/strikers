#include "Game/Render/Indicators.h"

#include "Game/AI/AiUtil.h"
#include "Game/CharacterTemplate.h"
#include "Game/CharacterTweaks.h"
#include "Game/Game.h"
#include "Game/GameTweaks.h"
#include "Game/RenderSnapshot.h"
#include "Game/Drawable/DrawableCharacter.h"
#include "Game/Player.h"
#include "Game/ReplayManager.h"
#include "Game/Team.h"
#include "NL/gl/glDraw2.h"
#include "NL/gl/glState.h"
#include "NL/gl/glTexture.h"
#include "NL/gl/glView.h"
#include "NL/globalpad.h"
#include "NL/nlColour.h"
#include "NL/nlMath.h"
#include "types.h"

static float s_fOverheadSize = 35.0f;
static float s_fAdditiveBlendingIntensity = 0.55f;
static float s_fAdditiveTextureScale = 1.25f;
static float s_fPulseRate = 2.0f;
static unsigned char s_bPulseGlowTexture = 1;
static float s_fGlowIntensityScale;
static unsigned char s_bGlowIsRising;

typedef struct
{
    char pad0[0x19C];
    float mSwitchScale;
    char pad1[0x28];
    void* mPossessionObject;
} cPlayerIndicatorState;

typedef struct
{
    void* vtbl;
    void* mGameTweaks;
} cGameOverlay;

typedef struct
{
    char pad0[0x2B4];
    float mVerticalOffset;
    float mProjectionYOffset;
} GameTweaksOverlay;

typedef struct
{
    nlVector3 mPosition;
    char pad0[0x4C];
} ReplayIndicatorCharacter;

typedef struct
{
    char pad0[0x68];
    ReplayIndicatorCharacter mCharacters[10];
} ReplayIndicatorSnapshot;

unsigned long uIndicatorTexID[4] = {
    nlStringLowerHash("fe/controller_1_indicator"),
    nlStringLowerHash("fe/controller_2_indicator"),
    nlStringLowerHash("fe/controller_3_indicator"),
    nlStringLowerHash("fe/controller_4_indicator")
};

unsigned long uGlowTexID[4] = {
    nlStringLowerHash("fe/controller_1_indicator_E"),
    nlStringLowerHash("fe/controller_2_indicator_E"),
    nlStringLowerHash("fe/controller_3_indicator_E"),
    nlStringLowerHash("fe/controller_4_indicator_E")
};

float fMaxAlpha = 0.9f;
float fOpacityFadePerSecond = 1.2f;

class IndicatorInfo
{
public:
    float m_fOpacity;

    inline void IncrementOnscreenTimer(float fTimeDelta)
    {
        m_fOpacity -= fTimeDelta * fOpacityFadePerSecond;
        if (m_fOpacity < 0.0f)
        {
            m_fOpacity = 0.0f;
        }
    }

    inline void IncrementOffscreenTimer(float fTimeDelta)
    {
        m_fOpacity += fTimeDelta * fOpacityFadePerSecond;
        if (m_fOpacity > fMaxAlpha)
        {
            m_fOpacity = fMaxAlpha;
        }
    }
};

IndicatorInfo indicatorInfo[10];

static inline void SetIndicatorPolyColour(glPoly2& poly, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    nlColour c = { 0, 0, 0, 0 };
    nlColourSet(c, r, g, b, a);
    poly.SetColour(c);
}

static inline void DrawIndicator(int xCentre, int yCentre, float fPixelWidth, float fPixelHeight, float fOpacity, unsigned long uTexID,
    float rotationAngle, unsigned char additiveBlending);
static inline void DrawOffscreenIndicator(const nlVector3& v3NormalizedScreenPos, IndicatorInfo* pInfo, cPlayer* pCharacter);
static inline unsigned long GetCharacterTexID(cPlayer* pCharacter);

static inline float max_float(float a, float b)
{
    return (b >= a) ? b : a;
}

/**
 * Offset/Address/Size: 0x868 | 0x8015FACC | size: 0x440
 */
static void UpdateAndRenderOffScreenIndicators(float dt)
{
    nlVector3 worldPos = { 0 };
    float half;
    int i;

    half = 0.5f;

    for (i = 0; i < 10; i++)
    {
        nlVector3 projectedPos;
        ReplayManager* replay;

        replay = ReplayManager::Instance();
        if (replay->mRender != 0)
        {
            replay = ReplayManager::Instance();
            worldPos = replay->mRender->mCharacters[i].mPosition;
        }

        {
            float h = ((cPlayer*)g_pCharacters[i])->m_pTweaks->fPhysCapsuleHeight;
            worldPos.z += h * half;
        }

        glViewProjectPoint((eGLView)7, worldPos, projectedPos);
        ((cPlayer*)g_pCharacters[i])->m_v3ScreenPosition = projectedPos;

        if (((cPlayer*)g_pCharacters[i])->GetGlobalPad() != 0)
        {
            u8 onScreenFlags[2];
            float fOne;

            const nlVector3& screenPos = ((cPlayer*)g_pCharacters[i])->m_v3ScreenPosition;
            onScreenFlags[1] = 0;
            fOne = 1.0f;
            onScreenFlags[0] = onScreenFlags[1];

            if ((float)__fabs(screenPos.x) <= fOne)
            {
                if ((float)__fabs(screenPos.y) <= fOne)
                {
                    onScreenFlags[0] = 1;
                }
            }

            if (onScreenFlags[0] != 0)
            {
                if ((float)__fabs(screenPos.z) <= fOne)
                {
                    onScreenFlags[1] = 1;
                }
            }

            if (onScreenFlags[1] != 0 || !g_pGame->IsGameplayOrOvertime())
            {
                indicatorInfo[i].IncrementOnscreenTimer(dt);
            }
            else
            {
                indicatorInfo[i].IncrementOffscreenTimer(dt);
                DrawOffscreenIndicator(projectedPos, &indicatorInfo[i], (cPlayer*)g_pCharacters[i]);
            }
        }
    }
}

static inline void DrawOffscreenIndicator(const nlVector3& v3NormalizedScreenPos, IndicatorInfo* pInfo, cPlayer* pCharacter)
{
    float screenPosX;
    float screenPosY;
    float scale;

    // PORT: half the frame rather than 320/240, and the clamps as that less the same 32-unit margin the literals encoded (288 = 320 - 32).
    const float halfW = 0.5f * glGetOrthographicWidth();
    const float halfH = 0.5f * glGetOrthographicHeight();

    screenPosY = v3NormalizedScreenPos.y * halfH;
    screenPosX = v3NormalizedScreenPos.x * halfW;

    if (screenPosX < -(halfW - 32.0f))
        screenPosX = -(halfW - 32.0f);
    else if (screenPosX > halfW - 32.0f)
        screenPosX = halfW - 32.0f;

    if (screenPosY < -(halfH - 32.0f))
        screenPosY = -(halfH - 32.0f);
    else if (screenPosY > halfH - 32.0f)
        screenPosY = halfH - 32.0f;

    screenPosX += halfW;
    screenPosY += halfH;

    scale = (float)fabs(1.0f - max_float((float)fabs(v3NormalizedScreenPos.y), (float)fabs(v3NormalizedScreenPos.x)));
    scale = InterpolateRangeClamped(1.0f, 0.5f, 0.0f, 2.0f, scale);
    DrawIndicator((int)screenPosX, (int)screenPosY, 64.0f * scale, 64.0f * scale, pInfo->m_fOpacity, GetCharacterTexID(pCharacter), 0.0f, 1);
}

static inline void DrawIndicator(int xCentre, int yCentre, float fPixelWidth, float fPixelHeight, float fOpacity, unsigned long uTexID,
    float rotationAngle, unsigned char additiveBlending)
{
    if ((u8)glTextureLoad(uTexID))
    {
        glPoly2 poly;

        glSetDefaultState(0);
        glSetRasterState(GLS_AlphaBlend, additiveBlending);
        glSetRasterState(GLS_AlphaTest, 1);
        glSetRasterState(GLS_AlphaTestRef, 0);
        glSetCurrentRasterState(glHandleizeRasterState());
        glSetCurrentTexture(uTexID, (eGLTextureType)0);
        glTextureGetWidth();
        glTextureGetHeight();

        poly.SetupRotatedRectangle((float)xCentre, (float)yCentre, fPixelWidth, fPixelHeight, rotationAngle, 10000000000.0f);

        if (additiveBlending == 2)
        {
            unsigned char intensity = (unsigned char)(255.0f * fOpacity);
            SetIndicatorPolyColour(poly, intensity, intensity, intensity, 0xFF);
        }
        else
        {
            SetIndicatorPolyColour(poly, 0xFF, 0xFF, 0xFF, (unsigned char)(255.0f * fOpacity));
        }

        poly.depth = -0.5f;
        poly.Attach((eGLView)27, 0, 0, (unsigned long)-1);
    }
}

static inline unsigned long GetCharacterTexID(cPlayer* pCharacter)
{
    return uIndicatorTexID[pCharacter->GetGlobalPad()->m_padIndex];
}

static inline unsigned long GetCharacterGlowTexID(cPlayer* pCharacter)
{
    return uGlowTexID[pCharacter->GetGlobalPad()->m_padIndex];
}

/**
 * Offset/Address/Size: 0xA8 | 0x8015F30C | size: 0x7C0
 */
static void UpdateAndRenderPlayerIndicators(float)
{
    static int whoHadBall;
    static signed char init;
    nlVector3 v3Position;
    nlVector3 v3ScreenPosition;
    float fX;
    float fY;
    float fOpacity;
    unsigned long indicatorTexID;
    unsigned long glowTexID;
    int whoHasBall;
    int i;
    float fDistInPixels;
    float switchScale;
    float sizeScale;

    whoHasBall = -1;
    if (!init)
    {
        whoHadBall = -1;
        init = 1;
    }

    for (i = 0; i < 10; i++)
    {
        ReplayManager* pReplay;
        GameTweaks* pTweaks;   // PORT: the real class

        if (((cPlayer*)g_pCharacters[i])->GetGlobalPad() == 0)
        {
            continue;
        }

        fOpacity = 1.0f - indicatorInfo[i].m_fOpacity;
        if (fOpacity <= 0.011764706f)
        {
            continue;
        }

        indicatorTexID = GetCharacterTexID((cPlayer*)g_pCharacters[i]);
        glowTexID = GetCharacterGlowTexID((cPlayer*)g_pCharacters[i]);

        pReplay = ReplayManager::Instance();
        // PORT: was two stand-ins over RenderSnapshot at console offsets. 0x68 is mCharacters (0x4C) plus DrawableCharacter::mHeadPosition (0x1C).
        v3Position = pReplay->mRender->GetCharacter(i).mHeadPosition;

        // PORT: was two shadow structs at console offsets.
        pTweaks = g_pGame->GetGameTweaks();
        switchScale = pTweaks->fIndicatorDistInPixels;
        v3Position.z += pTweaks->fIndicatorDistAboveHead;

        glViewProjectPoint((eGLView)7, v3Position, v3ScreenPosition);

        // PORT: half the frame; the 2D space is 480 * aspect wide now.
        fX = 0.5f * glGetOrthographicWidth() * (v3ScreenPosition.x + 1.0f);
        fY = 0.5f * glGetOrthographicHeight() * (v3ScreenPosition.y + 1.0f);
        fY -= switchScale;

        // PORT: cPlayerIndicatorState was a stand-in reading cPlayer at console 0x19C and 0x1C8.
        cPlayer* pIndicatorPlayer = (cPlayer*)g_pCharacters[i];

        if (pIndicatorPlayer->m_UserControlledTime < 0.5f)
        {
            switchScale = (0.5f - pIndicatorPlayer->m_UserControlledTime) / 0.5f;
            sizeScale = Interpolate(1.0f, 2.0f, switchScale);

            DrawIndicator((int)fX, (int)fY, s_fAdditiveTextureScale * (s_fOverheadSize * sizeScale), s_fAdditiveTextureScale * (s_fOverheadSize * sizeScale), s_fAdditiveBlendingIntensity * switchScale, glowTexID, 0.0f, 2);

            fDistInPixels = s_fOverheadSize * sizeScale;
            DrawIndicator((int)fX, (int)fY, fDistInPixels, fDistInPixels, fOpacity, indicatorTexID, 0.0f, 1);
        }
        else if (pIndicatorPlayer->m_pBall)
        {
            whoHasBall = i;

            if (whoHadBall == -1)
            {
                s_fGlowIntensityScale = 0.0f;
            }

            DrawIndicator((int)fX, (int)fY, s_fOverheadSize * s_fAdditiveTextureScale, s_fOverheadSize * s_fAdditiveTextureScale, s_fAdditiveBlendingIntensity * (s_bPulseGlowTexture ? s_fGlowIntensityScale : 1.0f), glowTexID, 0.0f, 2);
            fDistInPixels = s_fOverheadSize;
            DrawIndicator((int)fX, (int)fY, fDistInPixels, fDistInPixels, fOpacity, indicatorTexID, 0.0f, 1);
        }
        else
        {
            fDistInPixels = s_fOverheadSize;
            DrawIndicator((int)fX, (int)fY, fDistInPixels, fDistInPixels, fOpacity, indicatorTexID, 0.0f, 1);
        }
    }

    whoHadBall = whoHasBall;
}

/**
 * Offset/Address/Size: 0x0 | 0x8015F264 | size: 0xA8
 */
// MOD (mixed teams): team numbers. Replaces the controller number over the
// controlled player with a number over every fielder, in his captain's colour.
// 1 = has the ball (or is being controlled when nobody on the team does),
// 2-4 = the rest, in slot order.
extern bool MixedNumbersOn();
extern unsigned long MixedNumberTexture(int side, int digit);
extern "C" int PortModsIndicator(int side, int digit, int hasBall, int isControlled, int isCaptain,
    int* pDigit, float* pSize, float* pDy, int* pShow);

static void MixedRenderTeamNumbers()
{
    int digitOf[10];
    for (int i = 0; i < 10; ++i)
    {
        digitOf[i] = 0;
    }

    for (int side = 0; side < 2; ++side)
    {
        cTeam* pTeam = g_pTeams[side];
        if (pTeam == NULL)
        {
            continue;
        }

        // Who gets the 1: ball carrier, else a controlled player, else the captain.
        int oneIdx = -1;
        for (int pass = 0; pass < 3 && oneIdx < 0; ++pass)
        {
            for (int i = 0; i < 10; ++i)
            {
                cPlayer* pP = (cPlayer*)g_pCharacters[i];
                if (pP == NULL || pP->m_pTeam != pTeam || pP->m_eClassType == GOALIE)
                {
                    continue;
                }
                if ((pass == 0 && pP->m_pBall != NULL)
                    || (pass == 1 && pP->GetGlobalPad() != NULL)
                    || (pass == 2 && pP->IsCaptain()))
                {
                    oneIdx = i;
                    break;
                }
            }
        }

        int next = 2;
        for (int i = 0; i < 10; ++i)
        {
            cPlayer* pP = (cPlayer*)g_pCharacters[i];
            if (pP == NULL || pP->m_pTeam != pTeam || pP->m_eClassType == GOALIE)
            {
                continue;
            }
            digitOf[i] = (i == oneIdx) ? 1 : (next <= 4 ? next++ : 4);
        }

        for (int i = 0; i < 10; ++i)
        {
            if (digitOf[i] == 0)
            {
                continue;
            }
            cPlayer* pP = (cPlayer*)g_pCharacters[i];
            if (pP->m_pTeam != pTeam)
            {
                continue;
            }

            // MOD (mod layer): a script may change the digit, resize it, move it,
            // or hide it, per player, per frame.
            int drawDigit = digitOf[i];
            float fSizeMul = 1.0f;
            float fDy = 0.0f;
            int nShow = 1;
            PortModsIndicator(side, digitOf[i], pP->m_pBall != NULL ? 1 : 0,
                pP->GetGlobalPad() != NULL ? 1 : 0, pP->IsCaptain() ? 1 : 0,
                &drawDigit, &fSizeMul, &fDy, &nShow);
            if (!nShow || drawDigit < 1 || drawDigit > 4)
            {
                continue;
            }

            unsigned long tex = MixedNumberTexture(side, drawDigit);
            if (tex == (unsigned long)-1)
            {
                continue;
            }

            nlVector3 v3Position = ReplayManager::Instance()->mRender->GetCharacter(i).mHeadPosition;
            GameTweaks* pTweaks = g_pGame->GetGameTweaks();
            v3Position.z += pTweaks->fIndicatorDistAboveHead;

            nlVector3 v3Screen;
            glViewProjectPoint((eGLView)7, v3Position, v3Screen);
            if (v3Screen.z < -1.0f || v3Screen.z > 1.0f)
            {
                continue; // behind the camera
            }

            float fX = 0.5f * glGetOrthographicWidth() * (v3Screen.x + 1.0f);
            float fY = 0.5f * glGetOrthographicHeight() * (v3Screen.y + 1.0f);
            fY -= pTweaks->fIndicatorDistInPixels;

            fY += fDy;

            // The 1 is drawn a touch larger, so the ball carrier still stands out.
            float fSize = ((drawDigit == 1) ? s_fOverheadSize * 1.25f : s_fOverheadSize) * fSizeMul;
            DrawIndicator((int)fX, (int)fY, fSize, fSize, fMaxAlpha, tex, 0.0f, 1);
        }
    }
}

void UpdateAndRenderIndicators(float dt)
{
    UpdateAndRenderOffScreenIndicators(dt);
    if (MixedNumbersOn())
    {
        MixedRenderTeamNumbers();
    }
    else
    {
        UpdateAndRenderPlayerIndicators(dt);
    }

    if (s_bPulseGlowTexture)
    {
        if (s_bGlowIsRising)
        {
            s_fGlowIntensityScale += s_fPulseRate * dt;
            if (s_fGlowIntensityScale > 1.0f)
            {
                s_fGlowIntensityScale = 1.0f;
                s_bGlowIsRising = 0;
            }
        }
        else
        {
            s_fGlowIntensityScale -= s_fPulseRate * dt;
            if (s_fGlowIntensityScale < 0.0f)
            {
                s_fGlowIntensityScale = 0.0f;
                s_bGlowIsRising = 1;
            }
        }
    }
}
