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
// MOD (mixed teams): a seventh row in this options menu, "SUPER STRIKERS",
// with CAPTAINS ONLY / EVERYONE, sitting under BOWSER ATTACK.
//
// The artwork only has six rows, so the sixth row (and its value list) is
// deep-copied at runtime, moved down by one row's spacing, and registered
// with the menu like any other. The menu's animation re-applies every text's
// original wording each frame, so our labels are re-asserted after each
// update. Only with mixed teams on; otherwise the menu is untouched.
// ---------------------------------------------------------------------------

static TLInstance* gSuperRow = NULL;              // the cloned row (label + highlight)
static TLComponentInstance* gSuperValue = NULL;   // the cloned value list (two slides)

static TLInstance* MixedCloneRing(TLInstance* head);

static TLSlide* MixedCloneSlides(TLSlide* head, TLSlide* active, TLSlide** outActive)
{
    *outActive = NULL;
    if (head == NULL)
    {
        return NULL;
    }
    TLSlide* first = NULL;
    TLSlide* last = NULL;
    TLSlide* curr = head;
    for (int guard = 0; guard < 64; ++guard)
    {
        TLSlide* copy = (TLSlide*)nlMalloc(sizeof(TLSlide), 8, false);
        memcpy(copy, curr, sizeof(TLSlide));
        copy->m_instances = MixedCloneRing(curr->m_instances);
        if (curr == active)
        {
            *outActive = copy;
        }
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

    if (src->m_type == TLAT_COMPONENT && src->m_component != NULL)
    {
        // A component keeps its own "which slide is showing" state, so it
        // gets a private copy along with all of its slides.
        TLComponent* sc = src->m_component;
        TLComponent* dc = (TLComponent*)nlMalloc(sizeof(TLComponent), 8, false);
        memcpy(dc, sc, sizeof(TLComponent));
        TLSlide* active = NULL;
        dc->pChildren = MixedCloneSlides(sc->pChildren, sc->m_pActiveSlide, &active);
        dc->m_pActiveSlide = active;
        dst->m_component = dc;
    }
    else if (src->m_type == TLAT_TEXT)
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

// Set every text under an instance to one string (label rows).
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
    if (inst->m_type == TLAT_COMPONENT && inst->m_component != NULL && inst->m_component->pChildren != NULL)
    {
        TLSlide* head = inst->m_component->pChildren;
        TLSlide* slide = head;
        for (int guard = 0; guard < 64; ++guard)
        {
            if (slide->m_instances != NULL)
            {
                TLInstance* ihead = slide->m_instances;
                TLInstance* ic = ihead;
                for (int g2 = 0; g2 < 256; ++g2)
                {
                    MixedSetTextsBelow(ic, label, depth + 1);
                    ic = ic->m_next;
                    if (ic == ihead || ic == NULL) break;
                }
            }
            slide = slide->m_next;
            if (slide == head || slide == NULL) break;
        }
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

// The value list: slide 1 says CAPTAINS ONLY, slide 2 says EVERYONE.
static void MixedSetValueTexts(TLComponentInstance* value)
{
    static const unsigned short kCaptains[] = {'C','A','P','T','A','I','N','S',' ','O','N','L','Y',0};
    static const unsigned short kEveryone[] = {'E','V','E','R','Y','O','N','E',0};
    if (value == NULL || value->m_component == NULL || value->m_component->pChildren == NULL)
    {
        return;
    }
    TLSlide* head = value->m_component->pChildren;
    TLSlide* slide = head;
    int index = 0;
    for (int guard = 0; guard < 64; ++guard)
    {
        const unsigned short* label = (index == 0) ? kCaptains : kEveryone;
        if (slide->m_instances != NULL)
        {
            TLInstance* ihead = slide->m_instances;
            TLInstance* ic = ihead;
            for (int g2 = 0; g2 < 256; ++g2)
            {
                MixedSetTextsBelow(ic, label, 0);
                ic = ic->m_next;
                if (ic == ihead || ic == NULL) break;
            }
        }
        ++index;
        slide = slide->m_next;
        if (slide == head || slide == NULL) break;
    }
}

static void MixedAssertSuperRowTexts()
{
    static const unsigned short kRow[] = {'S','U','P','E','R',' ','S','T','R','I','K','E','R','S',0};
    if (gSuperRow != NULL)
    {
        MixedSetTextsBelow(gSuperRow, kRow, 0);
    }
    MixedSetValueTexts(gSuperValue);
}

static TLInstance* MixedFindInLayer(TLInstance* layer, const char* name)
{
    return FindItemByHashID(layer->pChildren, nlStringLowerHash(name));
}

// Clone row 6 below itself, register it as row 7, and hook up its value list.
static void MixedBuildSuperRow(FEPresentation* pres, OptionsGameplayMenuV2* menu)
{
    gSuperRow = NULL;
    gSuperValue = NULL;

    Config& cfg = Config::Global();
    if (!GetConfigBool(cfg, "mixed_teams", false))
    {
        return;
    }

    TLInstance* layer = FindItemByHashID(pres->GetActiveSlide()->m_instances, nlStringLowerHash("Layer"));
    if (layer == NULL || layer->pChildren == NULL)
    {
        OSReport("[mixed teams] options menu: no Layer, row not added\n");
        return;
    }

    TLInstance* row5 = MixedFindInLayer(layer, "MENU ITEM5");
    TLInstance* row6 = MixedFindInLayer(layer, "MENU ITEM6");
    TLInstance* val5 = MixedFindInLayer(layer, "RUMBLE");
    TLInstance* val6 = MixedFindInLayer(layer, "BOWSER");
    if (row5 == NULL || row6 == NULL || val5 == NULL || val6 == NULL)
    {
        OSReport("[mixed teams] options menu: rows not found (%p %p %p %p), row not added\n", row5, row6, val5, val6);
        return;
    }

    // Copies, one row-spacing lower than the row they came from.
    feVector3& p5 = row5->GetPosition();
    feVector3& p6 = row6->GetPosition();
    feVector3& v5 = val5->GetPosition();
    feVector3& v6 = val6->GetPosition();

    TLInstance* row7 = MixedCloneInstance(row6);
    nlSNPrintf(row7->m_szName, 32, "MENU ITEM7");
    row7->m_hash = nlStringLowerHash("MENU ITEM7");
    row7->SetAssetPosition(p6.f.x + (p6.f.x - p5.f.x), p6.f.y + (p6.f.y - p5.f.y), p6.f.z + (p6.f.z - p5.f.z));

    TLInstance* val7 = MixedCloneInstance(val6);
    nlSNPrintf(val7->m_szName, 32, "SUPERRULE");
    val7->m_hash = nlStringLowerHash("SUPERRULE");
    val7->SetAssetPosition(v6.f.x + (v6.f.x - v5.f.x), v6.f.y + (v6.f.y - v5.f.y), v6.f.z + (v6.f.z - v5.f.z));

    // Into the layer's draw list, right after their originals.
    row7->m_next = row6->m_next; row7->m_prev = row6; row6->m_next->m_prev = row7; row6->m_next = row7;
    val7->m_next = val6->m_next; val7->m_prev = val6; val6->m_next->m_prev = val7; val6->m_next = val7;

    gSuperRow = row7;
    gSuperValue = (TLComponentInstance*)val7;

    // Register with the menu exactly as the constructor does for rows 1-6.
    MenuItem<TLComponentInstance>* item = menu->mMenuItems.AddItem((TLComponentInstance*)row7);
    item->SetCallback(ON_HIGHLIGHT, SingleHighlite::OpenItem);
    item->SetCallback(ON_UNHIGHLIGHT, SingleHighlite::CloseItem);
    menu->CloseItem((TLComponentInstance*)row7);
    menu->BuildSubMenuList(6, gSuperValue, true, GetConfigBool(cfg, "super_all", false) ? 1 : 0);

    MixedAssertSuperRowTexts();
    OSReport("[mixed teams] options menu: SUPER STRIKERS row added at (%.1f, %.1f)\n",
             p6.f.x + (p6.f.x - p5.f.x), p6.f.y + (p6.f.y - p5.f.y));
}

// After the menu updates: keep our wording, and mirror the choice into the rule.
static void MixedUpdateSuperRow(OptionsGameplayMenuV2* menu)
{
    if (gSuperRow == NULL || menu == NULL || menu->mSlideMenuLists[6] == NULL)
    {
        return;
    }
    MixedAssertSuperRowTexts();
    bool all = (menu->mSlideMenuLists[6]->GetActiveItemIndex() == 1);
    Config& cfg = Config::Global();
    if (GetConfigBool(cfg, "super_all", false) != all)
    {
        cfg.Set("super_all", all);
        OSReport("[mixed teams] super strikes: %s\n", all ? "everyone" : "captains only");
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
    gSuperRow = NULL;   // MOD (mixed teams): the copies die with the scene's artwork
    gSuperValue = NULL;
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

    // MOD (mixed teams): the seventh row.
    MixedBuildSuperRow(pPresentation, pMem);
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

    // MOD (mixed teams): keep the seventh row's wording and apply its choice.
    MixedUpdateSuperRow(m_pOptionsMenu);
}
