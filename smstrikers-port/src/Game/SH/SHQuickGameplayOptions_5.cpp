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
#include "Game/FE/tlImageInstance.h"
#include "Game/FE/feHelpFuncs.h"
#include "Game/FE/feSlideMenu.h"
#include "Game/FE/feMenu.h"
#include "NL/nlString.h"
#include <string.h>
#include "dolphin/os.h"

extern FEInput* g_pFEInput;

// ---------------------------------------------------------------------------
// MOD (mixed teams): a third choice on the SUPER STRIKE row: ON / OFF / ALL.
//   ON  = only each team's real captain may throw one (the balanced default)
//   OFF = nobody may (the game's own setting)
//   ALL = every captain on the pitch may
//
// The row's choices are slides in its artwork (Slide1 = ON, Slide2 = OFF),
// so the ON slide is deep-copied in memory and appended as Slide3 before the
// menu is built; the menu then discovers three choices on its own. The
// artwork re-applies each text's original wording every frame, so the copy is
// relabelled "ALL" after each menu update. Only with mixed teams on.
// ---------------------------------------------------------------------------

static TLSlide* gAllSlide = NULL;

static TLInstance* MixedCloneRing(TLInstance* head);

static TLInstance* MixedCloneInstance(const TLInstance* src)
{
    unsigned long size;
    switch (src->m_type)
    {
    case TLAT_COMPONENT: size = sizeof(TLComponentInstance); break;
    case TLAT_TEXT:      size = sizeof(TLTextInstance); break;
    case TLAT_IMAGE:     size = sizeof(TLImageInstance); break;
    default:             size = sizeof(TLInstance); break;
    }
    TLInstance* dst = (TLInstance*)nlMalloc(size, 8, false);
    memcpy(dst, src, size);
    dst->m_next = dst;
    dst->m_prev = dst;
    dst->pChildren = MixedCloneRing(src->pChildren);
    if (src->m_type == TLAT_TEXT)
    {
        ((TLTextInstance*)dst)->m_pFontString = NULL; // rebuild the glyph cache
    }
    return dst;
}

static TLInstance* MixedCloneRing(TLInstance* head)
{
    if (head == NULL)
    {
        return NULL;
    }
    TLInstance* first = NULL;
    TLInstance* last = NULL;
    TLInstance* curr = head;
    for (int guard = 0; guard < 256; ++guard)
    {
        TLInstance* copy = MixedCloneInstance(curr);
        if (first == NULL)
        {
            first = copy;
        }
        else
        {
            last->m_next = copy;
            copy->m_prev = last;
        }
        last = copy;
        curr = curr->m_next;
        if (curr == head || curr == NULL)
        {
            break;
        }
    }
    last->m_next = first;
    first->m_prev = last;
    return first;
}

static void MixedSetTextsBelow(TLInstance* inst, const unsigned short* label, int depth)
{
    if (inst == NULL || depth > 8)
    {
        return;
    }
    if (inst->m_type == TLAT_TEXT)
    {
        ((TLTextInstance*)inst)->SetString(label);
    }
    if (inst->pChildren != NULL)
    {
        TLInstance* head = inst->pChildren;
        TLInstance* c = head;
        for (int guard = 0; guard < 256; ++guard)
        {
            MixedSetTextsBelow(c, label, depth + 1);
            c = c->m_next;
            if (c == head || c == NULL) break;
        }
    }
}

static void MixedRelabelAllSlide()
{
    static const unsigned short kAll[] = {'A','L','L',0};
    if (gAllSlide == NULL || gAllSlide->m_instances == NULL)
    {
        return;
    }
    TLInstance* head = gAllSlide->m_instances;
    TLInstance* c = head;
    for (int guard = 0; guard < 256; ++guard)
    {
        MixedSetTextsBelow(c, kAll, 0);
        c = c->m_next;
        if (c == head || c == NULL) break;
    }
}

// Before the menu is built: give the SUPER STRIKE list its third slide.
static void MixedAddAllChoice(FEPresentation* pres)
{
    gAllSlide = NULL;
    if (!GetConfigBool(Config::Global(), "mixed_teams", false))
    {
        return;
    }

    pres->SetActiveSlide("Slide3"); // the gameplay page, as the menu itself does
    pres->Update(0.0f);
    TLInstance* layer = FindItemByHashID(pres->GetActiveSlide()->m_instances, nlStringLowerHash("Layer"));
    if (layer == NULL || layer->pChildren == NULL)
    {
        OSReport("[mixed teams] options menu: no Layer, ALL choice not added\n");
        return;
    }
    TLInstance* s2s = FindItemByHashID(layer->pChildren, nlStringLowerHash("S2S"));
    if (s2s == NULL || s2s->m_component == NULL || s2s->m_component->pChildren == NULL)
    {
        OSReport("[mixed teams] options menu: S2S list not found, ALL choice not added\n");
        return;
    }

    TLComponent* comp = s2s->m_component;
    TLSlide* on = FindItemByHashID(comp->pChildren, nlStringLowerHash("Slide1"));
    if (on == NULL)
    {
        OSReport("[mixed teams] options menu: S2S Slide1 not found, ALL choice not added\n");
        return;
    }
    if (FindItemByHashID(comp->pChildren, nlStringLowerHash("Slide3")) != NULL)
    {
        return; // already there (same artwork reused)
    }

    TLSlide* all = (TLSlide*)nlMalloc(sizeof(TLSlide), 8, false);
    memcpy(all, on, sizeof(TLSlide));
    all->m_instances = MixedCloneRing(on->m_instances);
    nlSNPrintf(all->m_szName, 32, "Slide3");
    all->m_hash = nlStringLowerHash("Slide3");

    // Append to the ring, after the last existing slide.
    TLSlide* head = comp->pChildren;
    TLSlide* last = head->m_prev != NULL ? head->m_prev : head;
    all->m_next = head;
    all->m_prev = last;
    last->m_next = all;
    head->m_prev = all;

    gAllSlide = all;
    MixedRelabelAllSlide();
    OSReport("[mixed teams] options menu: SUPER STRIKE now offers ON / OFF / ALL\n");
}

// After the menu is built: land on ALL when that is the current rule.
static void MixedSelectAllIfSet(OptionsGameplayMenuV2* menu)
{
    if (gAllSlide == NULL || menu == NULL || menu->mSlideMenuLists[3] == NULL)
    {
        return;
    }
    GameInfoManager* gi = GameInfoManager::GetInstance();
    if (gi->mCurGameGameplayOptions.Shoot2Score && GetConfigBool(Config::Global(), "super_all", false))
    {
        menu->mSlideMenuLists[3]->SetItem(2);
    }
}

// Each frame after the menu updates: keep "ALL" spelled out, apply the rule.
static void MixedUpdateAllChoice(OptionsGameplayMenuV2* menu)
{
    if (gAllSlide == NULL || menu == NULL || menu->mSlideMenuLists[3] == NULL)
    {
        return;
    }
    MixedRelabelAllSlide();
    bool all = (menu->mSlideMenuLists[3]->GetActiveItemIndex() == 2);
    Config& cfg = Config::Global();
    if (GetConfigBool(cfg, "super_all", false) != all)
    {
        cfg.Set("super_all", all);
        OSReport("[mixed teams] super strikes: %s\n", all ? "everyone" : "captains only");
    }
}

// The vanilla save reads "index 0 means on"; index 2 (ALL) must also mean on.
static void MixedFixSaveForAll(OptionsGameplayMenuV2* menu)
{
    if (gAllSlide == NULL || menu == NULL || menu->mSlideMenuLists[3] == NULL)
    {
        return;
    }
    if (menu->mSlideMenuLists[3]->GetActiveItemIndex() == 2)
    {
        GameInfoManager::GetInstance()->mCurGameGameplayOptions.Shoot2Score = true;
    }
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
    gAllSlide = NULL;   // MOD (mixed teams): the copy dies with the scene's artwork
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

    // MOD (mixed teams): SUPER STRIKE gets its ALL choice before the menu reads the list.
    MixedAddAllChoice(pPresentation);

    OptionsGameplayMenuV2* pMem = (OptionsGameplayMenuV2*)nlMalloc(sizeof(OptionsGameplayMenuV2), 8, false);
    pMem = new (pMem) OptionsGameplayMenuV2(pPresentation, ButtonComponent::BS_B_ONLY, GameInfoManager::GetInstance()->mCurGameGameplayOptions, maxSkillLevel);
    m_pOptionsMenu = pMem;

    MixedSelectAllIfSet(pMem);
}

/**
 * Offset/Address/Size: 0x0 | 0x8010CE44 | size: 0x100
 */
void QuickGameplayOptionsScene::Update(float dt)
{
    BaseSceneHandler::Update(dt);

    if (!g_pFEInput->JustPressed(FE_ALL_PADS, 0x100, false, NULL))
    {
        if (g_pFEInput->JustPressed(FE_ALL_PADS, 0x200, false, NULL))
        {
            m_pOptionsMenu->Save();
            MixedFixSaveForAll(m_pOptionsMenu); // MOD (mixed teams): ALL still means on

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

    // MOD (mixed teams): keep "ALL" spelled out and apply the choice.
    MixedUpdateAllChoice(m_pOptionsMenu);
}
