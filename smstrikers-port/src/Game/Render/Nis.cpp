#include "Game/Render/Nis.h"
#include "NL/nlWare.h"
#include "dolphin/os.h"
#include "port/endian.h"
extern "C" unsigned long port_cam_swap(void*, unsigned long);
#include "NL/vmath.h"
#include "Game/ReplayManager.h"
#include "Game/CharacterTemplate.h"
#include "Game/Player.h"
#include "NL/nlConfig.h"
#include "Game/NisPlayer.h"
#include "Game/Sys/audio.h"
#include "Game/Sys/GCStream.h"
#include "Game/Audio/AudioStream.h"
#include "Game/CharacterAudio.h"
#include "Game/CharacterTriggers.h"
#include "Game/WorldManager.h"
#include "Game/Effects/EmissionManager.h"
#include "Game/Effects/EffectsGroup.h"
#include "Game/EventDataTypes.h"
#include "Game/Sys/eventman.h"
#include "Game/Game.h"
#include "NL/nlFunction.h"
#include "NL/nlList.h"
#include "NL/nlString.h"
#include "NL/nlFormat.h"

#include "types.h"

#include "NL/nlBind.h"

class nlTaskManager
{
public:
    static void SetTimeDilation(float);
};

class EmissionController;

// ---------------------------------------------------------------------------
// MOD (mixed teams): intros. A captain standing in a sidekick slot would walk
// in and face off with the sidekick's animation (Donkey Kong upright on two
// legs). With intro_own_anims on, his body plays his own captain routine from
// his own file of the same type, while his position and facing still come
// from the sidekick slot's animation: he is exactly where the sidekick would
// be, doing his own thing.
//   intro_own_anims_who      "all" or one name
//   intro_faceoff_generic    captains who keep the generic routine in the
//                            face-off (a standing scene): "mario,yoshi"
// ---------------------------------------------------------------------------
extern char* NisLoadOwnFile(const char* charName, const char* likeName, const char* nisType, int* outSize, char* outName);
extern const char* NisLastType(int target);

static char* gNisCharBuffer[10];                 // the captain's own file, while in use
static cPN_SAnimController* gNisSlotCtrl[10];    // the slot's animation: position and facing
static Nis* gNisCharOwner[10];
static nlVector3 gNisHipFix[10];                 // cancels any placement baked into the captain's body
static bool gNisHipFixDone[10];

static bool NisNameInList(const char* list, const char* name)
{
    if (list == NULL || name == NULL) return false;
    size_t n = strlen(name);
    const char* p = list;
    while (*p)
    {
        while (*p == ' ' || *p == ',') ++p;
        const char* q = p;
        while (*q && *q != ',' && *q != ' ') ++q;
        if ((size_t)(q - p) == n && strncmp(p, name, n) == 0) return true;
        p = q;
    }
    return false;
}

static cSAnim* NisOwnIntroAnim(Nis* owner, int charIndex, NisTarget target, const char* likeName, cSAnim* slotAnim)
{
    Config& cfg = Config::Global();
    if (!GetConfigBool(cfg, "mixed_teams", false) || !GetConfigBool(cfg, "intro_own_anims", true))
    {
        return NULL;
    }
    if (target != NIS_TARGET_HOME_SIDEKICK && target != NIS_TARGET_AWAY_SIDEKICK)
    {
        return NULL;
    }
    if (g_pCharacters[charIndex] == NULL)
    {
        return NULL;
    }
    eCharacterClass cc = ((cPlayer*)g_pCharacters[charIndex])->m_eCharacterClass;
    if (!::IsCaptain(cc))
    {
        return NULL;
    }
    const char* charName = GetCharacterName(cc);
    BasicString<char, Detail::TempStringAllocator> who
        = cfg.Get<BasicString<char, Detail::TempStringAllocator> >("intro_own_anims_who", BasicString<char, Detail::TempStringAllocator>("all"));
    if (who.c_str() != NULL && who.c_str()[0] != 0 && nlStrCmp<char>(who.c_str(), "all") != 0
        && nlStrCmp<char>(who.c_str(), charName) != 0)
    {
        return NULL;
    }

    // A standing scene (the face-off) is one where the slot barely moves.
    nlVector3 a = { 0.0f, 0.0f, 0.0f };
    nlVector3 b = { 0.0f, 0.0f, 0.0f };
    slotAnim->GetRootTrans(0.0f, &a);
    slotAnim->GetRootTrans(slotAnim->GetDuration(), &b);
    float travel = sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    bool standing = travel < 1.0f;
    if (standing)
    {
        BasicString<char, Detail::TempStringAllocator> keep
            = cfg.Get<BasicString<char, Detail::TempStringAllocator> >("intro_faceoff_generic", BasicString<char, Detail::TempStringAllocator>("mario,yoshi"));
        if (NisNameInList(keep.c_str(), charName))
        {
            OSReport("[mixed teams] intro: %s keeps the generic face-off routine\n", charName);
            return NULL;
        }
    }

    int size = 0;
    char szName[64];
    char* buffer = NisLoadOwnFile(charName, likeName, NisLastType((int)target), &size, szName);
    if (buffer == NULL)
    {
        return NULL;
    }

    // The captain's own routine is the first animation in his file.
    cSAnim* own = NULL;
    nlChunk* chunk = (nlChunk*)buffer;
    nlChunk* endc = (nlChunk*)(buffer + size);
    while (chunk < endc)
    {
        const u32 uChunkID = port_be32(&chunk->m_ID) & 0x80FFFFFF;
        const u32 uChunkSize = port_be32(&chunk->m_Size);
        if (uChunkID == 0x80017000)
        {
            own = cSAnim::Initialize(chunk);
            break;
        }
        chunk = (nlChunk*)((char*)chunk + uChunkSize + 8);
    }
    if (own == NULL)
    {
        nlFree(buffer);
        return NULL;
    }

    // Position and facing keep coming from the slot's own animation.
    if (gNisCharBuffer[charIndex] != NULL)
    {
        nlFree(gNisCharBuffer[charIndex]);
    }
    gNisCharBuffer[charIndex] = buffer;
    gNisSlotCtrl[charIndex] = ::new (AllocateSAnimController()) cPN_SAnimController(slotAnim, NULL, PM_HOLD, NULL, 0, false);
    gNisCharOwner[charIndex] = owner;
    gNisHipFixDone[charIndex] = false;
    gNisHipFix[charIndex].x = gNisHipFix[charIndex].y = gNisHipFix[charIndex].z = 0.0f;
    OSReport("[mixed teams] intro: character %d (%s) plays '%s' at the %s slot's position (%s scene, slot travels %.1f)\n",
             charIndex, charName, szName, likeName, standing ? "standing" : "walking", travel);
    return own;
}

/**
 * Offset/Address/Size: 0x1658 | 0x8012CA68 | size: 0x53C
 */
Nis::Nis(NisHeader& header, char* data, int size)
{
    cSAnim* anim;
    int i;

    mHeader = &header;
    mTarget = header.target;
    mWinnerType = header.winnerType;
    mData = data;
    mSize = size;
    mMirrored = NisPlayer::Instance()->IsMirrored(header.target, header.name, header.winnerType);
    mCamera = NULL;
    mNumCameras = 0;
    mNumTriggers = 0;
    mMainCharacterIndex = -1;
    mAudioCharacterIndex = -1;
    mNisAudioDataList = NULL;
    for (int i = 0; i < 10; i++)
    {
        mCharacterControllers[i] = NULL;
        mBallId[i] = -1;
    }
    nlChunk* chunk = (nlChunk*)data;
    nlChunk* end = (nlChunk*)(data + size);
    int numAnimations = 0;
    while (chunk != end)
    {
        // PORT: the file is big-endian and each animation converts its own subtree, so read the header rather than trusting it.
        const u32 uChunkID = port_be32(&chunk->m_ID) & 0x80FFFFFF;
        const u32 uChunkSize = port_be32(&chunk->m_Size);

        if (uChunkID == 0x80017000)
        {
            anim = cSAnim::Initialize(chunk);
            i = NisPlayer::Instance()->TargetToIndex(mTarget, numAnimations, mWinnerType);
            // MOD (mixed teams): the scorer is the star of every winner cutscene in
            // his goal's sequence, captain or not; only the first animation of a
            // file is re-aimed, the rest keep their own targets.
            {
                extern int NisGetScorerIndex();
                int goalScorer = NisPlayer::Instance()->mGoalScorerCharIndex;
                if (goalScorer < 0 && numAnimations == 0)
                {
                    goalScorer = NisGetScorerIndex();
                }
                if (goalScorer >= 0
                    && (mTarget == NIS_TARGET_WINNER_SIDEKICK || mTarget == NIS_TARGET_WINNER_CAPTAIN))
                {
                    mMainCharacterIndex = goalScorer;
                    i = goalScorer;
                }
            }
            NisPlayer* player = NisPlayer::Instance();
            player->mGoalScorerCharIndex = -1;
            if (mCharacterControllers[i] != NULL)
            {
                i = NisPlayer::Instance()->TargetToIndex(NIS_TARGET_HOME_CAPTAIN, numAnimations, mWinnerType);
            }
            if (mCharacterControllers[i] != NULL)
            {
                i = NisPlayer::Instance()->TargetToIndex(NIS_TARGET_AWAY_CAPTAIN, numAnimations, mWinnerType);
            }
            if (mCharacterControllers[i] != NULL)
            {
                for (i = 0; i < 10; i++)
                {
                    if (mCharacterControllers[i] == NULL)
                        break;
                }
            }
            if (i < 10)
            {
                {
                    const char* who = (g_pCharacters[i] != NULL)
                        ? GetCharacterName(((cPlayer*)g_pCharacters[i])->m_eCharacterClass) : "?";
                    OSReport("[mixed teams] nis: '%s' animation %d -> character %d (%s)\n",
                             mHeader->name, numAnimations, i, who);
                }
                // MOD (mixed teams): a borrowed captain in a sidekick slot gets his own routine.
                if (gNisCharOwner[i] != this)
                {
                    gNisCharOwner[i] = NULL;
                    gNisSlotCtrl[i] = NULL;
                }
                cSAnim* own = NisOwnIntroAnim(this, i, mTarget, mHeader->name, anim);
                if (own != NULL)
                {
                    anim = own;
                }
                mBallId[i] = numAnimations;
                cPN_SAnimController* controller = ::new (AllocateSAnimController()) cPN_SAnimController(anim, NULL, PM_HOLD, NULL, 0, false);
                mCharacterControllers[i] = controller;
                if (mAudioCharacterIndex < 0)
                {
                    mAudioCharacterIndex = i;
                }
            }
            numAnimations++;
        }
        if (uChunkID == 0x80015501)
        {
            // PORT: nothing else owns these; a chunk the converter refuses would be walked out of bounds.
            if (port_cam_swap(chunk, uChunkSize + 8) == 0)
            {
                OSReport("Error: NIS camera %lu is not well-formed; skipped\n", (unsigned long)mNumCameras);
            }
            else
            {
                BasicString<char, Detail::TempStringAllocator> name = Format(BasicString<char, Detail::TempStringAllocator>("{0}_{1}"), mHeader->name, mNumCameras);
                nlChunk* cameraBegin = (nlChunk*)((char*)chunk + 8);
                nlChunk* cameraEnd = (nlChunk*)((char*)chunk + uChunkSize + 8);
                cAnimCamera::LoadCameraAnimation(cameraBegin, cameraEnd, name.c_str(), false);
                mNumCameras++;
            }
        }
        chunk = (nlChunk*)((char*)chunk + uChunkSize + 8);
    }
}

/**
 * Offset/Address/Size: 0x1650 | 0x8012CA60 | size: 0x8
 */
char* Nis::Name() const
{
    return mHeader->name;
}

/**
 * Offset/Address/Size: 0x13C0 | 0x8012C7D0 | size: 0x290
 */
Nis::~Nis()
{
    // MOD (mixed teams): drop any borrowed-captain intro files this cutscene owned.
    for (int i = 0; i < 10; i++)
    {
        if (gNisCharOwner[i] == this)
        {
            if (gNisCharBuffer[i] != NULL)
            {
                nlFree(gNisCharBuffer[i]);
                gNisCharBuffer[i] = NULL;
            }
            if (gNisSlotCtrl[i] != NULL)
            {
                delete gNisSlotCtrl[i]; // back to the controller pool
                gNisSlotCtrl[i] = NULL;
            }
            gNisCharOwner[i] = NULL;
        }
    }
    for (int i = 0; i < mNumCameras; i++)
    {
        BasicString<char, Detail::TempStringAllocator> name = Format(BasicString<char, Detail::TempStringAllocator>(((void)0, "{0}_{1}")), mHeader->name, i);
        cAnimCamera::FreeCameraAnimation(name.c_str());
    }

    if (mCamera)
    {
        mCamera->UnselectCameraAnimation();
    }

    StopAllOutstandingNisAudio();
    NisPlayer::Instance()->ResetEffects();
    nlTaskManager::SetTimeDilation(1.0f);
}

/**
 * Offset/Address/Size: 0x1350 | 0x8012C760 | size: 0x70
 */
void Nis::Update(float dt)
{
    for (int i = 0; i < 10; ++i)
    {
        cPN_SAnimController* pController = mCharacterControllers[i];
        if (pController != nullptr)
        {
            pController->Update(dt);
            if (gNisCharOwner[i] == this && gNisSlotCtrl[i] != NULL)
            {
                gNisSlotCtrl[i]->Update(dt); // MOD (mixed teams): the slot's placement keeps time too
            }
        }
    }
}

/**
 * Offset/Address/Size: 0x1270 | 0x8012C680 | size: 0xE0
 */
void Nis::UpdateTriggers(float oldTime, float newTime, float duration)
{
    if (duration != 0.0f)
    {
        for (int i = 0; i < mNumTriggers; ++i)
        {
            float triggerFrame = (mTriggers[i].frameNumber / 30.0f) / duration;
            if ((oldTime <= triggerFrame) && (newTime > triggerFrame))
            {
                mTriggers[i].Fire(*this);
            }
        }
    }
}

/**
 * Offset/Address/Size: 0xF80 | 0x8012C390 | size: 0x2F0
 */
void Nis::SelectCamera(cAnimCamera& camera, int cameraIndex)
{
    if (mNumCameras == 0)
    {
        return;
    }

    int index = cameraIndex % mNumCameras;
    BasicString<char, Detail::TempStringAllocator> cameraName = Format(BasicString<char, Detail::TempStringAllocator>(((void)0, "{0}_{1}")), mHeader->name, index);

    camera.SelectCameraAnimation(cameraName.c_str());

    if (mMirrored)
    {
        camera.m_Mirror = (nlVector3) { -1.0f, 1.0f, 1.0f };
    }
    else
    {
        camera.m_Mirror = (nlVector3) { 1.0f, 1.0f, 1.0f };
    }

    camera.m_fAnimationTime = 0.0f;
    camera.BuildAnimViewMatrix(camera.m_matView);

    if (strstr(mHeader->name, "cup") != NULL)
    {
        camera.m_bCyclic = true;
    }
    else
    {
        camera.m_bCyclic = false;
    }

    mCamera = &camera;
}

/**
 * Offset/Address/Size: 0xF18 | 0x8012C328 | size: 0x68
 */
bool Nis::SelectRandomCamera(cAnimCamera& camera)
{
    if (mNumCameras == 0)
    {
        return false;
    }

    int randomIndex = nlRandom(mNumCameras, &nlDefaultSeed);
    SelectCamera(camera, randomIndex);
    return true;
}

/**
 * Offset/Address/Size: 0xD18 | 0x8012C128 | size: 0x200
 */
void Nis::Render()
{
    DrawableCharacter* pDC;
    RenderSnapshot& snapshot = ReplayManager::Instance()->GetMutableRenderSnapshot();
    nlVector3 offset = { 0.0f, 0.0f, 0.0f };
    int numBalls = 0;

    for (int i = 0; i < 10; i++)
    {
        pDC = &snapshot.GetCharacter(i);
        if (mCharacterControllers[i] == NULL)
            continue;
        pDC->mVisible = true;

        nlVector3 rootTrans = { 0.0f, 0.0f, 0.0f };
        u16 angle = 0;
        // MOD (mixed teams): a borrowed captain is placed by the slot's animation.
        cPN_SAnimController* pPlace = (gNisCharOwner[i] == this && gNisSlotCtrl[i] != NULL)
            ? gNisSlotCtrl[i] : mCharacterControllers[i];
        float fTime = pPlace->get_fTime();
        pPlace->m_pSAnim->GetRootTrans(fTime, &rootTrans);
        fTime = pPlace->get_fTime();
        pPlace->m_pSAnim->GetRootRot(fTime, &angle);
        if (mMirrored)
        {
            mCharacterControllers[i]->m_bMirror = true;
            rootTrans.x *= -1.0f;
            angle = angle + (0x4000 - angle) * 2;
        }

        nlVec3Add(rootTrans, rootTrans, mHeader->stadiumOffset);
        nlVec3Add(rootTrans, rootTrans, offset);

        // MOD (mixed teams): a borrowed captain's routine may carry its own
        // placement in the body. On his first frame, measure where the slot's
        // pose puts the hips versus where his own pose puts them, and shift by
        // the difference from then on, so his hips sit where the sidekick's would.
        if (gNisCharOwner[i] == this && gNisSlotCtrl[i] != NULL)
        {
            if (!gNisHipFixDone[i])
            {
                pDC->EvaluateFrom(*gNisSlotCtrl[i], rootTrans, angle);
                nlVector3 slotHip = pDC->mBip01Position;
                pDC->EvaluateFrom(*mCharacterControllers[i], rootTrans, angle);
                nlVector3 ownHip = pDC->mBip01Position;
                gNisHipFix[i].x = slotHip.x - ownHip.x;
                gNisHipFix[i].y = slotHip.y - ownHip.y;
                gNisHipFix[i].z = 0.0f;
                gNisHipFixDone[i] = true;
                OSReport("[mixed teams] intro: character %d hips: slot (%.1f, %.1f) own (%.1f, %.1f) -> shift (%.1f, %.1f)\n",
                         i, slotHip.x, slotHip.y, ownHip.x, ownHip.y, gNisHipFix[i].x, gNisHipFix[i].y);
            }
            nlVec3Add(rootTrans, rootTrans, gNisHipFix[i]);
        }
        pDC->EvaluateFrom(*mCharacterControllers[i], rootTrans, angle);
        pDC->BuildNodeMatrices();
        if (mBallId[i] >= 0 && numBalls < mHeader->numBalls
            && numBalls < NisPlayer::Instance()->mMaxNumBallsVisible)
        {
            if (mBallId[i] == 0)
            {
                snapshot.mBall.mVisible = true;
                snapshot.mBall.EvaluateFrom(*pDC);
            }
            numBalls++;
        }
    }
}

/**
 * Offset/Address/Size: 0xCF8 | 0x8012C108 | size: 0x20
 */
nlVector3 Nis::Offset() const
{
    return mHeader->stadiumOffset;
}

/**
 * Offset/Address/Size: 0xC10 | 0x8012C020 | size: 0xE8
 */
void Nis::AddTrigger(NisTriggerType triggerType, float frameNumber, const char* name, const char* target, Nis::TriggerParams* trigParams)
{
    mTriggers[mNumTriggers].type = triggerType;
    mTriggers[mNumTriggers].frameNumber = frameNumber;
    mTriggers[mNumTriggers].name = name;
    mTriggers[mNumTriggers].target = target;

    TriggerParams* pParams = &(mTriggers[mNumTriggers].params);
    pParams->float1 = -1.0f;
    pParams->param1 = -1;
    pParams->param2 = -1;
    pParams->param3 = -1;
    pParams->param4 = -1;

    if (trigParams != NULL)
    {
        mTriggers[mNumTriggers].params.float1 = trigParams->float1;
        mTriggers[mNumTriggers].params.param1 = trigParams->param1;
        mTriggers[mNumTriggers].params.param2 = trigParams->param2;
        mTriggers[mNumTriggers].params.param3 = trigParams->param3;
        mTriggers[mNumTriggers].params.param4 = trigParams->param4;
    }

    mNumTriggers++;
}

static inline bool EffectNeedsValidCoordSys(EffectsGroup* pGroup)
{
    EffectsSpec* pSpec = pGroup->m_specs;
    if (pSpec == NULL)
        return false;

    for (int i = pGroup->m_numSpecs; i > 0; i--, pSpec++)
    {
        if (pSpec->m_vLocalOffset.x != 0.0f || pSpec->m_vLocalOffset.y != 0.0f || pSpec->m_vLocalOffset.z != 0.0f)
            return true;
    }
    return false;
}

/**
 * Offset/Address/Size: 0x834 | 0x8012BC44 | size: 0x3DC
 */
void Nis::Trigger::FireEffect(const Nis& nis) const
{
    NisPlayer* player = NULL;
    if (params.param1 == 0)
    {
        player = NisPlayer::Instance();
    }

    if (strstr(target, "ball") != NULL)
    {
        EffectsGroup* group = fxGetGroup(name);
        if (group == NULL)
            return;
        EmissionController* ctrl = EmissionManager::Create(group, 0);
        if (ctrl == NULL)
            return;
        ctrl->m_uUserData = (uintptr_t)player;
        {
            Function1<void, EmissionController&> update(UpdateEmitterFromBall);
            ctrl->SetUpdateCallback(update);
        }
    }
    else if (strstr(target, "bip0") != NULL)
    {
        s32 idx = (s32)(s8)target[4] - '1';
        if (idx < 0)
            idx = 0;

        int charIdx;
        if (nis.mMainCharacterIndex >= 0)
        {
            charIdx = nis.mMainCharacterIndex;
        }
        else
        {
            charIdx = NisPlayer::Instance()->TargetToIndex(nis.mTarget, idx, nis.mWinnerType);
        }
        if (charIdx >= 10)
            return;

        EffectsGroup* group = fxGetGroup(name);
        if (group == NULL)
            return;
        EmissionController* ctrl = EmissionManager::Create(group, 0);
        if (ctrl == NULL)
            return;
        ctrl->SetAnimController(*nis.mCharacterControllers[charIdx]);
        ctrl->m_uUserData = (uintptr_t)player;
        if (!nis.mMirrored)
        {
            nlVector3 mirror = { -1.0f, 1.0f, 1.0f };
            ctrl->m_Mirror = mirror;
        }
        if (EffectNeedsValidCoordSys(group))
        {
            Function1<void, EmissionController&> callback(
                Bind<void>(UpdateEmitterFromCharacterIdxWithCoordSys, placeholder0, charIdx));
            ctrl->SetUpdateCallback(callback);
        }
        else
        {
            Function1<void, EmissionController&> callback(
                Bind<void>(UpdateEmitterFromCharacterIdxWithoutAnimController, placeholder0, charIdx));
            ctrl->SetUpdateCallback(callback);
        }
    }
    else
    {
        World* const world = WorldManager::s_World;
        HelperObject* helperObj = world->FindHelperObject(world->GetHashIdForGenericName(target));
        if (helperObj == NULL)
            return;
        nlVector3 velocity = { 0.0f, 0.0f, 1.0f };
        EmissionController* ctrl = EmissionManager::Create(fxGetGroup(name), 0);
        ctrl->m_uUserData = (uintptr_t)player;
        ctrl->SetVelocity(velocity);
        ctrl->SetPosition(helperObj->m_worldMatrix.GetTranslation());
        ctrl->m_fGround = 0.02f;
    }
}

/**
 * Offset/Address/Size: 0x2D0 | 0x8012B6E0 | size: 0x564
 */
void Nis::Trigger::Fire(Nis& nis) const
{
    switch (type)
    {
    case NIS_TRIGGER_TYPE_PLAY_SOUND:
    {
        uintptr_t index;   /* PORT: may hold an SFXEmitter* */
        bool isEmitter;
        bool stopAtNisEnd;
        float volume = params.float1;
        unsigned long soundType = (unsigned long)-1;
        isEmitter = false;
        stopAtNisEnd = true;

        volume = params.float1 != -1.0f ? params.float1 : 100.0f;

        if (params.param1 == (unsigned long)-1)
        {
            if (strlen(target) > 0)
            {
                World* const pWorld = WorldManager::s_World;
                HelperObject* helper = pWorld->FindHelperObject(pWorld->GetHashIdForGenericName(target));
                if (helper == NULL)
                    return;
                static const nlVector3 zeroDirection = { 0.0f, 0.0f, 0.0f };
                index = Audio::PlayWorldSFXbyStr(name, volume, -1.0f, true, false, (const nlVector3*)&helper->m_worldMatrix.e2[3][0], &zeroDirection, &soundType);
                isEmitter = true;
            }
            else
            {
                index = Audio::PlayWorldSFXbyStr(name, 100.0f, -1.0f, false, true, NULL, NULL, NULL);
            }
        }
        else
        {
            index = Audio::PlayCharSFXbyStr(name, (NisCharacterClass)params.param1, volume, -1.0f, true, false, &ReplayManager::Instance()->GetMutableRenderSnapshot().GetCharacter(nis.mAudioCharacterIndex).mBip01Position, &ReplayManager::Instance()->GetMutableRenderSnapshot().GetCharacter(nis.mAudioCharacterIndex).mVelocity, &soundType);
            isEmitter = true;
        }

        if (params.param2 != (unsigned long)-1)
            stopAtNisEnd = false;
        if (index == (uintptr_t)-1)
            break;

        nis.AddNisAudioData(NIS_AUDIO_TYPE_SFX, index, name, isEmitter, stopAtNisEnd, soundType);
        break;
    }

    case NIS_TRIGGER_TYPE_PLAY_RANDOM_DIALOGUE:
    {
        uintptr_t index;   /* PORT: may hold an SFXEmitter* */
        bool stopAtNisEnd;
        unsigned long soundType = (unsigned long)-1;
        index = Audio::cCharacterSFX::PlayNISRandomCharDialogue((CharDialogueType)params.param2, (NisCharacterClass)params.param1, 100.0f, -1.0f, true, &ReplayManager::Instance()->GetMutableRenderSnapshot().GetCharacter(nis.mAudioCharacterIndex).mBip01Position, &ReplayManager::Instance()->GetMutableRenderSnapshot().GetCharacter(nis.mAudioCharacterIndex).mVelocity, &soundType);
        stopAtNisEnd = true;
        if (params.param3 != (unsigned long)-1)
            stopAtNisEnd = false;
        if (index == (uintptr_t)-1)
            break;

        nis.AddNisAudioData(NIS_AUDIO_TYPE_SFX, index, name, true, stopAtNisEnd, soundType);
        break;
    }

    case NIS_TRIGGER_TYPE_STOP_SOUND:
        nis.StopNisAudio(NIS_AUDIO_TYPE_SFX, name);
        break;

    case NIS_TRIGGER_TYPE_PLAY_STREAM:
    case NIS_TRIGGER_TYPE_STOP_STREAM:
    case NIS_TRIGGER_TYPE_SET_ACTIVE_STREAM_LOOPING:
        break;

    case NIS_TRIGGER_TYPE_STOP_ALL_STREAMS:
        Audio::StopStreaming();
        break;

    case NIS_TRIGGER_TYPE_REGISTER_GOAL_AUDIO:
        g_pGame->m_nLastTeamToScore = NisPlayer::Instance()->mWinnerSide[1];
        break;

    case NIS_TRIGGER_TYPE_TIME_DILATION:
        nlTaskManager::SetTimeDilation(params.float1);
        break;

    case NIS_TRIGGER_TYPE_EFFECT:
        FireEffect(nis);
        break;

    case NIS_TRIGGER_TYPE_RAISE_EVENT:
    {
        Event* event = g_pEventManager->CreateValidEvent(0x56, 0x20);
        NISData* pData = new (&event->m_data) NISData();
        pData->Type = name;
        pData->Param = target;
        break;
    }
    }
}

inline Nis::NisAudioData* Nis::NisAudioData::Allocate()
{
    return (NisAudioData*)nlMalloc(sizeof(NisAudioData), 8, false);
}

inline void Nis::AddNisAudioData(
    NisAudioType type,
    uintptr_t index,
    const char* str,
    bool isEmitter,
    bool stopAtNisEnd,
    unsigned long soundType)
{
    NisAudioData* pNisAudioData = NisAudioData::Allocate();
    pNisAudioData->audioType = NIS_AUDIO_TYPE_NONE;
    pNisAudioData->identifier.index = (uintptr_t)-1;
    memset(pNisAudioData->str, 0, NisAudioData::MAX_NIS_AUDIO_STR_CHARS);
    pNisAudioData->soundType = (unsigned long)-1;
    pNisAudioData->stopAtNisEnd = true;
    pNisAudioData->isEmitter = false;
    pNisAudioData->audioType = type;
    if (isEmitter)
        pNisAudioData->identifier.pEmitter = (SFXEmitter*)index;
    else
        pNisAudioData->identifier.index = index;
    nlStrNCpy(pNisAudioData->str, str, NisAudioData::MAX_NIS_AUDIO_STR_CHARS);
    pNisAudioData->soundType = soundType;
    pNisAudioData->isEmitter = isEmitter;
    pNisAudioData->stopAtNisEnd = stopAtNisEnd;
    pNisAudioData->next = NULL;
    nlListAddStart(&mNisAudioDataList, pNisAudioData, (NisAudioData**)NULL);
}

inline void Nis::StopNisAudio(NisAudioType type, const char* str)
{
    NisAudioData* pNisAudioData = mNisAudioDataList;
    while (pNisAudioData != NULL)
    {
        if (nlStrICmp(pNisAudioData->str, str) == 0)
            pNisAudioData = StopNisAudio(pNisAudioData, 0);
        else
            pNisAudioData = pNisAudioData->next;
    }
}

inline Nis::NisAudioData* Nis::StopNisAudio(NisAudioData* pNisAudioData, bool bNisEndedNormally)
{
    SFXEmitter* pSFXEmitter;
    bool bResult;
    if (pNisAudioData->isEmitter)
    {
        pSFXEmitter = pNisAudioData->identifier.pEmitter;
        if (pNisAudioData->soundType == pSFXEmitter->soundType)
        {
            if ((!bNisEndedNormally) || (bNisEndedNormally && pNisAudioData->stopAtNisEnd))
            {
                bResult = Audio::Remove3DSFXEmitter(pSFXEmitter);
                if (bResult)
                {
                    if (!Audio::IsEmitterActive(pSFXEmitter))
                    {
                        pSFXEmitter->bKeepTrack = true;
                        pSFXEmitter->soundType = (unsigned long)-1;
                        pSFXEmitter->fTimeStamp = -1.0f;
                        pSFXEmitter->bIsStopping = false;
                        pSFXEmitter->bInUse = false;
                        pSFXEmitter->bIsFilterOn = false;
                        pSFXEmitter->m_unk_0x5F = false;
                        pSFXEmitter->pPhysObj = NULL;
                        pSFXEmitter->pOwner = NULL;
                        pSFXEmitter->pos.pvPos = NULL;
                        pSFXEmitter->dir.pvDir = NULL;
                        pSFXEmitter->pos.vPos.x = 0.0f;
                        pSFXEmitter->pos.vPos.y = 0.0f;
                        pSFXEmitter->pos.vPos.z = 0.0f;
                        pSFXEmitter->dir.vDir.x = 0.0f;
                        pSFXEmitter->dir.vDir.y = 0.0f;
                        pSFXEmitter->dir.vDir.z = 0.0f;
                        pSFXEmitter->posUpdateMethod = NONE;
                        if (pSFXEmitter->pMIDIControllerInfo != NULL)
                        {
                            if (pSFXEmitter->pMIDIControllerInfo->paraArray != NULL)
                                delete[] pSFXEmitter->pMIDIControllerInfo->paraArray;
                            delete pSFXEmitter->pMIDIControllerInfo;
                        }
                        pSFXEmitter->pMIDIControllerInfo = NULL;
                        pNisAudioData->identifier.pEmitter = NULL;
                    }
                }
            }
        }
    }
    else if (Audio::IsSFXPlaying(pNisAudioData->identifier.index))
    {
        if ((!bNisEndedNormally) || (bNisEndedNormally && pNisAudioData->stopAtNisEnd))
        {
            Audio::StopSFX(pNisAudioData->identifier.index);
            pNisAudioData->identifier.index = (uintptr_t)-1;
        }
    }
    return RemoveNisAudioData(pNisAudioData);
}

inline Nis::NisAudioData* Nis::RemoveNisAudioData(NisAudioData* pNisAudioData)
{
    NisAudioData* pNextNisAudioData;
    nlListRemoveElement(&mNisAudioDataList, pNisAudioData, (NisAudioData**)NULL);
    pNextNisAudioData = pNisAudioData->next;
    pNisAudioData->audioType = NIS_AUDIO_TYPE_NONE;
    pNisAudioData->identifier.index = (uintptr_t)-1;
    memset(pNisAudioData->str, 0, NisAudioData::MAX_NIS_AUDIO_STR_CHARS);
    pNisAudioData->soundType = (unsigned long)-1;
    pNisAudioData->stopAtNisEnd = true;
    pNisAudioData->isEmitter = false;
    delete pNisAudioData;
    return pNextNisAudioData;
}

/**
 * Offset/Address/Size: 0x0 | 0x8012B410 | size: 0x2D0
 */
void Nis::StopAllOutstandingNisAudio()
{
    NisAudioData* pNisAudioData = mNisAudioDataList;
    while (pNisAudioData != NULL)
    {
        switch (pNisAudioData->audioType)
        {
        case NIS_AUDIO_TYPE_SFX:
        {
            bool bNisEndedNormally = false;
            cPN_SAnimController* pController;
            int i;
            for (i = 0; i < 10; i++)
            {
                pController = mCharacterControllers[i];
                if (pController != NULL)
                {
                    float remainingTime = 1.0f - pController->m_fTime;
                    if (remainingTime < 0.025f)
                    {
                        bNisEndedNormally = true;
                        break;
                    }
                }
            }

            pNisAudioData = StopNisAudio(pNisAudioData, bNisEndedNormally);
            break;
        }
        case NIS_AUDIO_TYPE_NONE:
        case NIS_AUDIO_TYPE_STREAM:
        default:
            pNisAudioData = pNisAudioData->next;
            break;
        }
    }

    nlDeleteList(&mNisAudioDataList);
    mNisAudioDataList = NULL;
}
