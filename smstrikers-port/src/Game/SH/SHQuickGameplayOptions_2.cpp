#include "Game/SH/SHQuickGameplayOptions.h"

#include "Game/BaseGameSceneManager.h"
#include "Game/FE/FEAudio.h"
#include "Game/FE/feInput.h"
#include "Game/FE/feOptionsSubMenus.h"
#include "Game/FE/fePackage.h"
#include "Game/GameInfo.h"
#include "Game/GameSceneManager.h"
#include "NL/nlMemory.h"
#include "NL/nlConfig.h"
#include "Game/FE/feFinder.h"
#include "Game/FE/tlTextInstance.h"
#include "Game/FE/tlSlide.h"
#include "Game/FE/tlComponent.h"
#include "Game/FE/tlComponentInstance.h"
#include "dolphin/os.h"

extern FEInput* g_pFEInput;

// ---------------------------------------------------------------------------
// MOD (mixed teams): the Super Strikes rule, as a row in this options menu.
//
// The menu's six rows are baked into the artwork, so instead of a seventh row
// the rule lives on the SUPER STRIKES row itself: with mixed teams on, X
// flips who may throw one, and the row's label spells out the current rule
// in the game's own font. The row's ON/OFF list keeps its vanilla meaning.
// ---------------------------------------------------------------------------

// Walk every slide of a component and every child below it, and rewrite each
// text object found. Names are not needed: objects carry a type tag.
static int MixedRelabelTexts(TLInstance* inst, const unsigned short* label, int depth);

static int MixedRelabelSlide(TLSlide* slide, const unsigned short* label, int depth)
{
    int n = 0;
    TLInstance* head = slide->m_instances;
    if (head == NULL)
    {
        return 0;
    }
    TLInstance* curr = head->m_next;
    for (int guard = 0; guard < 256; ++guard)
    {
        n += MixedRelabelTexts(curr, label, depth);
        if (curr == head)
        {
            break;
        }
        curr = curr->m_next;
    }
    return n;
}

static int MixedRelabelTexts(TLInstance* inst, const unsigned short* label, int depth)
{
    if (inst == NULL || depth > 8)
    {
        return 0;
    }
    int n = 0;
    switch (inst->GetType())
    {
    case TLAT_TEXT:
        ((TLTextInstance*)inst)->SetString(label);
        n = 1;
        break;
    case TLAT_COMPONENT:
    {
        TLComponent* comp = (TLComponent*)inst->m_component;
        if (comp != NULL && comp->pChildren != NULL)
        {
            if (depth <= 1)
            {
                OSReport("[mixed teams]   options row part: component '%s'\n", comp->m_szName);
            }
            TLSlide* head = comp->pChildren;
            TLSlide* curr = head->m_next;
            for (int guard = 0; guard < 64; ++guard)
            {
                n += MixedRelabelSlide(curr, label, depth + 1);
                if (curr == head)
                {
                    break;
                }
                curr = curr->m_next;
            }
        }
        break;
    }
    default:
        break;
    }
    // Layers and groups hold their children directly.
    if (inst->pChildren != NULL)
    {
        TLInstance* head = inst->pChildren;
        TLInstance* curr = head->m_next;
        for (int guard = 0; guard < 256; ++guard)
        {
            n += MixedRelabelTexts(curr, label, depth + 1);
            if (curr == head)
            {
                break;
            }
            curr = curr->m_next;
        }
    }
    return n;
}

static void MixedRelabelSuperRow(FEPresentation* pres)
{
    Config& cfg = Config::Global();
    if (!GetConfigBool(cfg, "mixed_teams", false))
    {
        OSReport("[mixed teams] options menu: mixed teams is off, label left vanilla\n");
        return; // vanilla menu stays word-for-word vanilla
    }

    static const unsigned short kAll[] = {
        'S','U','P','E','R',':',' ','E','V','E','R','Y','O','N','E',' ','(','X',')',0};
    static const unsigned short kCaptain[] = {
        'S','U','P','E','R',':',' ','C','A','P','T','A','I','N','S',' ','(','X',')',0};
    bool all = GetConfigBool(cfg, "super_all", false);
    const unsigned short* label = all ? kAll : kCaptain;

    TLComponentInstance* row = FEFinder<TLComponentInstance, 4>::Find<TLSlide>(
        pres->GetActiveSlide(),
        InlineHasher(nlStringLowerHash("Layer")),
        InlineHasher(nlStringLowerHash("MENU ITEM4")));
    if (row == NULL)
    {
        OSReport("[mixed teams] options menu: row MENU ITEM4 not found\n");
        return;
    }

    int n = MixedRelabelTexts(row, label, 0);
    OSReport("[mixed teams] options menu: super strikes = %s, %d text object(s) relabelled\n",
             all ? "everyone" : "captains only", n);
}

/**
 * Offset/Address/Size: 0x278 | 0x8010D0BC | size: 0x74
 */
QuickGameplayOptionsScene::QuickGameplayOptionsScene()
    : BaseSceneHandler()
{
    m_pOptionsMenu = NULL;
    g_pFEInput->PushExclusiveInputLock(this, SCENE_QUICK_GAMEPLAY_OPTIONS);
}

/**
 * Offset/Address/Size: 0x1DC | 0x8010D020 | size: 0x9C
 */
QuickGameplayOptionsScene::~QuickGameplayOptionsScene()
{
    if (m_pOptionsMenu != NULL)
    {
        delete m_pOptionsMenu;
    }
    g_pFEInput->PopExclusiveInputLock(this);
}

/**
 * Offset/Address/Size: 0x100 | 0x8010CF44 | size: 0xDC
 */
void QuickGameplayOptionsScene::SceneCreated()
{
    GameInfoManager* pGameInfo = GameInfoManager::GetInstance();

    if (!pGameInfo->mUseCurGameSettings)
    {
        // Restore gameplay options from user's saved settings
        pGameInfo->mCurGameGameplayOptions.SkillLevel = pGameInfo->mUserInfo.mGameplayOptions.SkillLevel;
        pGameInfo->mCurGameGameplayOptions.GameTime = pGameInfo->mUserInfo.mGameplayOptions.GameTime;
        pGameInfo->mCurGameGameplayOptions.PowerUps = pGameInfo->mUserInfo.mGameplayOptions.PowerUps;
        pGameInfo->mCurGameGameplayOptions.Shoot2Score = pGameInfo->mUserInfo.mGameplayOptions.Shoot2Score;
        pGameInfo->mCurGameGameplayOptions.BowserAttackEnabled = pGameInfo->mUserInfo.mGameplayOptions.BowserAttackEnabled;
        pGameInfo->mCurGameGameplayOptions.RumbleEnabled = pGameInfo->mUserInfo.mGameplayOptions.RumbleEnabled;
    }

    FEPresentation* pPresentation = m_pFEScene->m_pFEPackage->GetPresentation();

    int maxSkillLevel = GameInfoManager::GetInstance()->IsLegendSkillUnlocked() ? -1 : 4;

    OptionsGameplayMenuV2* pMem = (OptionsGameplayMenuV2*)nlMalloc(sizeof(OptionsGameplayMenuV2), 8, false);
    pMem = new (pMem) OptionsGameplayMenuV2(pPresentation, ButtonComponent::BS_B_ONLY, GameInfoManager::GetInstance()->mCurGameGameplayOptions, maxSkillLevel);
    m_pOptionsMenu = pMem;

    // MOD (mixed teams): show the current Super Strikes rule on its row.
    MixedRelabelSuperRow(pPresentation);
}

/**
 * Offset/Address/Size: 0x0 | 0x8010CE44 | size: 0x100
 */
void QuickGameplayOptionsScene::Update(float dt)
{
    BaseSceneHandler::Update(dt);

    // MOD (mixed teams): X flips who may throw a Super Strike.
    if (g_pFEInput->JustPressed(FE_ALL_PADS, 0x400, false, NULL)
        && GetConfigBool(Config::Global(), "mixed_teams", false))
    {
        Config& cfg = Config::Global();
        bool all = !GetConfigBool(cfg, "super_all", false);
        cfg.Set("super_all", all);
        OSReport("[mixed teams] super strikes: %s\n", all ? "everyone" : "captains only");
        MixedRelabelSuperRow(m_pFEScene->m_pFEPackage->GetPresentation());
        FEAudio::PlayAnimAudioEvent("sfx_accept_no_screen_change", false);
    }

    if (!g_pFEInput->JustPressed(FE_ALL_PADS, 0x100, false, NULL))
    {
        if (g_pFEInput->JustPressed(FE_ALL_PADS, 0x200, false, NULL))
        {
            m_pOptionsMenu->Save();

            GameInfoManager* pGameInfo = GameInfoManager::GetInstance();
            pGameInfo->mUserInfo.mGameplayOptions.SkillLevel = pGameInfo->mCurGameGameplayOptions.SkillLevel;
            pGameInfo->mUserInfo.mGameplayOptions.GameTime = pGameInfo->mCurGameGameplayOptions.GameTime;
            pGameInfo->mUserInfo.mGameplayOptions.PowerUps = pGameInfo->mCurGameGameplayOptions.PowerUps;
            pGameInfo->mUserInfo.mGameplayOptions.Shoot2Score = pGameInfo->mCurGameGameplayOptions.Shoot2Score;
            pGameInfo->mUserInfo.mGameplayOptions.BowserAttackEnabled = pGameInfo->mCurGameGameplayOptions.BowserAttackEnabled;
            pGameInfo->mUserInfo.mGameplayOptions.RumbleEnabled = pGameInfo->mCurGameGameplayOptions.RumbleEnabled;

            GameSceneManager::GetInstance()->Pop();
            FEAudio::PlayAnimAudioEvent("sfx_screen_back", false);
            return;
        }
    }

    m_pOptionsMenu->Update(dt);
}
