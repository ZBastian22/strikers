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

static void MixedRelabelSuperRow(FEPresentation* pres)
{
    Config& cfg = Config::Global();
    if (!GetConfigBool(cfg, "mixed_teams", false))
    {
        return; // vanilla menu stays word-for-word vanilla
    }

    static const unsigned short kAll[] = {
        'S','U','P','E','R',':',' ','E','V','E','R','Y','O','N','E',' ','(','X',')',0};
    static const unsigned short kCaptain[] = {
        'S','U','P','E','R',':',' ','C','A','P','T','A','I','N','S',' ','(','X',')',0};
    const unsigned short* label = GetConfigBool(cfg, "super_all", false) ? kAll : kCaptain;

    TLComponentInstance* row = FEFinder<TLComponentInstance, 4>::Find<TLSlide>(
        pres->GetActiveSlide(),
        InlineHasher(nlStringLowerHash("Layer")),
        InlineHasher(nlStringLowerHash("MENU ITEM4")));
    if (row == NULL)
    {
        return;
    }
    TLComponentInstance* high = FEFinder<TLComponentInstance, 4>::Find<TLSlide>(
        row->GetActiveSlide(),
        InlineHasher(nlStringLowerHash("high")));
    if (high == NULL)
    {
        return;
    }

    // The label text exists once per state slide ("in" open, "out" closed),
    // so both copies are rewritten, and the slide that was showing stays.
    TLSlide* pOriginal = high->GetActiveSlide();
    static const char* const kStates[2] = { "in", "out" };
    for (int i = 0; i < 2; ++i)
    {
        high->SetActiveSlide(kStates[i]);
        if (high->GetActiveSlide() == NULL)
        {
            continue;
        }
        TLTextInstance* text = FEFinder<TLTextInstance, 3>::Find<TLSlide>(
            high->GetActiveSlide(),
            InlineHasher(nlStringLowerHash("Layer")),
            InlineHasher(nlStringLowerHash("CENTER")));
        if (text != NULL)
        {
            text->SetString(label);
        }
    }
    for (int i = 0; i < 2; ++i)
    {
        high->SetActiveSlide(kStates[i]);
        if (high->GetActiveSlide() == pOriginal)
        {
            break;
        }
    }
    row->Update(0.0f);
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
