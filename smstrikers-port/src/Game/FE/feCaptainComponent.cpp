#include "Game/FE/feCaptainComponent.h"
#include "Game/FE/feAsyncImage.h"
#include "Game/FE/feFinder.h"
#include "Game/FE/fePresentation.h"
#include "Game/FE/tlSlide.h"
#include "NL/nlConfig.h"
#include "Game/FE/feImage.h"
#include "Game/FE/feTextureResource.h"
#include "Game/FE/tlComponent.h"
#include <string.h>
#include "NL/gl/glTexture.h"
#include "dolphin/os.h"

extern bool g_e3_Build;

static const char* const SLIDE_IN = "in";

// ===========================================================================
// MOD (mixed teams): the in-menu team picker.
//
// With `mixed_picker` on, the captain screen asks four times instead of once:
// first your captain, then each of your three teammates, all on the captain
// grid. Y flips the view to the classic sidekick grid and back, and confirm
// takes whichever face is highlighted, so all twelve characters are reachable.
// B un-picks the last choice. Once a side has four, it locks in, and the
// picks land in the same team1_slot2..team2_slot4 settings the pitch reads.
// ===========================================================================

static bool gPickerOn = false;
static int gPickCount[2];          // -1 = captain not chosen yet, 0..3 = teammates picked
static char gPickNames[2][3][20];
static bool gPickedASidekick[2];

// Picked faces are tinted in the picked character's colour, the way the game
// blacks out a taken captain (the face's own colour multiplied down): Mario
// goes red, Luigi green, Wario yellow. A sidekick takes the team's colour.
// Tints fade in when placed and fade out when B rewinds, and every face is
// restored when the screen is left.

// Fade length in seconds, from picker_fade_ms (default 350).
static float PickerFadeTime()
{
    int ms = GetConfigInt(Config::Global(), "picker_fade_ms", 350);
    if (ms < 1) { ms = 1; }
    return ms / 1000.0f;
}

struct PickerTint
{
    TLInstance* mIcon;   // the face on the grid
    nlColour mOriginal;  // its colour before the tint
    nlColour mTarget;    // the character's colour
    float mT;            // 0 = original, 1 = fully tinted
    bool mDying;         // fading back to the original, then dropped
};
static PickerTint gPickerTints[2][4]; // [side][pick 0=captain,1..3=teammates]

// Indexed by eTeamID: DAISY, DK, LUIGI, MARIO, PEACH, WALUIGI, WARIO, YOSHI, MYSTERY.
static const char* const kPickerCaptCell[9] = {
    "choose_capt_daisy", "choose_capt_dk", "choose_capt_luigi", "choose_capt_mario",
    "choose_capt_peach", "choose_capt_waluigi", "choose_capt_wario", "choose_capt_yoshi",
    "choose_capt_super",
};

// The captains' colours, same order.
static const unsigned char kPickerTeamRGB[9][3] = {
    { 255, 150,  40 }, // Daisy, orange
    { 150,  90,  40 }, // Donkey Kong, brown
    {  60, 210,  60 }, // Luigi, green
    { 255,  50,  50 }, // Mario, red
    { 255, 130, 210 }, // Peach, pink
    { 170,  70, 230 }, // Waluigi, purple
    { 250, 225,  40 }, // Wario, yellow
    {  90, 200,  70 }, // Yoshi, green
    { 140, 170, 215 }, // the robot: steel blue
};

static const char* PickerSidekickCell(eSidekickID sk)
{
    switch (sk)
    {
    case SK_TOAD:       return "choose_sidek_toad";
    case SK_KOOPA:      return "choose_sidek_koopa";
    case SK_HAMMERBROS: return "choose_sidek_hammer";
    case SK_BIRDO:      return "choose_sidek_birdo";
    default:            return NULL;
    }
}

static void PickerApplyTint(PickerTint* t)
{
    nlColour c;
    for (int i = 0; i < 3; ++i)
    {
        float v = t->mOriginal.c[i] + (t->mTarget.c[i] - t->mOriginal.c[i]) * t->mT;
        c.c[i] = (unsigned char)(v < 0.0f ? 0 : (v > 255.0f ? 255 : v));
    }
    c.c[3] = t->mOriginal.c[3];
    t->mIcon->SetAssetColour(c);
}

// Called every frame: run the fades, and let faded-out tints go.
static void PickerTickTints(float dt)
{
    for (int side = 0; side < 2; ++side)
    {
        for (int k = 0; k < 4; ++k)
        {
            PickerTint* t = &gPickerTints[side][k];
            if (t->mIcon == NULL)
            {
                continue;
            }
            if (t->mDying)
            {
                t->mT -= dt / PickerFadeTime();
                if (t->mT <= 0.0f)
                {
                    t->mIcon->SetAssetColour(t->mOriginal);
                    t->mIcon = NULL;
                    continue;
                }
            }
            else if (t->mT < 1.0f)
            {
                t->mT += dt / PickerFadeTime();
                if (t->mT > 1.0f) { t->mT = 1.0f; }
            }
            PickerApplyTint(t);
        }
    }
}

// Leaving the screen: every face back to its own colour at once.
static void PickerRestoreAllTints()
{
    for (int side = 0; side < 2; ++side)
    {
        for (int k = 0; k < 4; ++k)
        {
            PickerTint* t = &gPickerTints[side][k];
            if (t->mIcon != NULL)
            {
                t->mIcon->SetAssetColour(t->mOriginal);
                t->mIcon = NULL;
            }
        }
    }
}

// Tint a face for pick pickIdx (0 = captain) in charName's colour.
static void PickerTintFace(IChooseCaptain* p, int side, int pickIdx, bool onCaptainGrid, const char* cellName, const char* charName)
{
    PickerTint* t = &gPickerTints[side][pickIdx];
    if (t->mIcon != NULL)
    {
        t->mIcon->SetAssetColour(t->mOriginal);
        t->mIcon = NULL;
    }
    if (cellName == NULL)
    {
        return;
    }

    // The character's colour: a captain's own, or the team's for a sidekick.
    eTeamID team = ConvertToTeamID(charName);
    if (team == TEAM_INVALID)
    {
        team = (eTeamID)p->mHomeAwayTeam[side]; // a sidekick takes the team's colour
    }
    if (team < 0 || team > 8)
    {
        return;
    }

    TLComponentInstance* grid = onCaptainGrid
        ? p->mCaptainGridComponents[side]->mParentComponent
        : p->mSidekickGridComponents[side]->mParentComponent;
    TLInstance* cell = FEFinder<TLInstance, 2>::Find<TLSlide>(
        grid->GetActiveSlide(), InlineHasher(nlStringLowerHash(cellName)));
    if (cell == NULL)
    {
        OSReport("[mixed teams] picker: cell %s not found\n", cellName);
        return;
    }

    t->mIcon = cell;
    t->mOriginal = cell->m_component->GetColour();
    t->mTarget.c[0] = kPickerTeamRGB[team][0];
    t->mTarget.c[1] = kPickerTeamRGB[team][1];
    t->mTarget.c[2] = kPickerTeamRGB[team][2];
    t->mTarget.c[3] = t->mOriginal.c[3];
    t->mT = 0.0f;
    t->mDying = false;
    OSReport("[mixed teams] picker: %s tinted in %s colours (pick %d)\n", cellName, GetTeamName(team), pickIdx + 1);
}

// Start a tint fading back to the face's own colour.
static void PickerUntintFace(int side, int pickIdx)
{
    gPickerTints[side][pickIdx].mDying = true;
}

// Coming back from the side-select screen rebuilds this screen, so the
// picker's memory is empty while the sides are already locked in. The picks
// are still in the settings; read them back so B can rewind properly.
static bool PickerRestoreSide(IChooseCaptain* p, int side)
{
    if (gPickCount[side] >= 0)
    {
        return true;
    }
    if (p->mComponentState[side].mCurrentPhase != PHASE_READY || p->mHomeAwayTeam[side] == 8)
    {
        OSReport("[mixed teams] picker: side %d not restorable (phase %d, team %d)\n",
                 side, (int)p->mComponentState[side].mCurrentPhase, p->mHomeAwayTeam[side]);
        return false;
    }
    Config& cfg = Config::Global();
    char szKey[16];
    for (int k = 0; k < 3; ++k)
    {
        nlSNPrintf(szKey, 16, "team%d_slot%d", side + 1, k + 2);
        BasicString<char, Detail::TempStringAllocator> v
            = cfg.Get<BasicString<char, Detail::TempStringAllocator> >(szKey, BasicString<char, Detail::TempStringAllocator>(""));
        if (v.c_str() == NULL || v.c_str()[0] == 0)
        {
            OSReport("[mixed teams] picker: side %d not restorable, %s is empty\n", side, szKey);
            return false;
        }
        nlSNPrintf(gPickNames[side][k], 20, "%s", v.c_str());
    }
    gPickCount[side] = 3;
    gPickedASidekick[side] = false;
    for (int k = 0; k < 3; ++k)
    {
        if (ConvertToSidekickID(gPickNames[side][k]) != SK_INVALID)
        {
            gPickedASidekick[side] = true;
            break;
        }
    }
    OSReport("[mixed teams] picker: side %d picks restored (%s, %s, %s)\n", side,
             gPickNames[side][0], gPickNames[side][1], gPickNames[side][2]);
    return true;
}

// Put the tints back on a side's faces (after the grid has been shown again).
static void PickerRetintSide(IChooseCaptain* p, int side)
{
    for (int k = 0; k < 4; ++k)
    {
        PickerUntintFace(side, k);
    }
    if (gPickCount[side] < 0)
    {
        return;
    }
    const char* captain = GetTeamName((eTeamID)p->mHomeAwayTeam[side]);
    PickerTintFace(p, side, 0, true, kPickerCaptCell[p->mHomeAwayTeam[side]], captain);
    for (int k = 0; k < gPickCount[side]; ++k)
    {
        eTeamID t = ConvertToTeamID(gPickNames[side][k]);
        if (t != TEAM_INVALID)
        {
            PickerTintFace(p, side, k + 1, true, kPickerCaptCell[(int)t], gPickNames[side][k]);
        }
        else
        {
            PickerTintFace(p, side, k + 1, false, PickerSidekickCell(ConvertToSidekickID(gPickNames[side][k])), gPickNames[side][k]);
        }
    }
}

// B while locked in: back to the captain grid with the last teammate removed,
// the same way the game returns from a ready mystery captain.
static void MixedPickerReadyToCaptainGrid(IChooseCaptain* p, int side)
{
    IChooseCaptain::ComponentState& st = p->mComponentState[side];
    st.mCurrentPhase = PHASE_CHOOSING_CAPTAIN;

    ICaptainGridComponent* grid = p->mCaptainGridComponents[side];
    grid->mParentComponent->SetActiveSlide("SELECT");
    grid->mParentComponent->Update(0.0f);
    grid->RebuildInstanceTable();
    grid->mMapMenu->UpdateAllItems();
    grid->RebindHighliteComponent("HIGHLIGHT");
    grid->mHighliteComponent->m_bVisible = true;
    grid->mParentComponent->m_bVisible = true;
    grid->MoveHighlightToTarget((eTeamID)p->mHomeAwayTeam[side]);
    p->mCaptainComponents[side]->m_bVisible = false;
    p->mSidekickComponents[side]->m_bVisible = false;
    p->mSidekickMiniHeadComponents[side]->m_bVisible = false;

    ICaptainGridComponent* other = p->mCaptainGridComponents[side ^ 1];
    other->RebuildInstanceTable();
    other->SetAllItemsActive();
    grid->RebuildInstanceTable();
    grid->SetAllItemsActive();
    if (p->mComponentState[side ^ 1].mCurrentPhase > PHASE_CHOOSING_CAPTAIN)
    {
        grid->mMapMenu->SetItemActive(other->mMapMenu->GetSelectedItem(), false);
    }
    // Our own captain stays greyed on their grid, as when he was picked.
    other->mMapMenu->SetItemActive(grid->mMapMenu->GetSelectedItem(), false);

    IChooseCaptain::NameComponent* nc = &p->mNameComponents[side];
    nc->mComponent->SetActiveSlide("Slide1");
    nc->mComponent->Update(0.0f);
    nc->SetCaptainName(GetLOCCharacterName((eTeamID)p->mHomeAwayTeam[side], false, false));
    nc->SetCaptainLogo(GetTeamName((eTeamID)p->mHomeAwayTeam[side]));

    FEAudio::PlayAnimAudioEvent("sfx_back_no_screen_change", false);
}

// True when this side already has that character (captain included).
static bool PickerAlreadyPicked(IChooseCaptain* p, int side, const char* nm)
{
    if (gPickCount[side] >= 0 && nlStrCmp<char>(nm, GetTeamName((eTeamID)p->mHomeAwayTeam[side])) == 0)
    {
        return true;
    }
    for (int k = 0; k < gPickCount[side]; ++k)
    {
        if (nlStrCmp<char>(nm, gPickNames[side][k]) == 0)
        {
            return true;
        }
    }
    return false;
}

static bool MixedPickerOn()
{
    return gPickerOn;
}

// Fresh state every time the screen is entered. Old slot picks are cleared so
// a previous match (or a lineup.lua) never leaks into a side the picker owns.
static void MixedPickerReset()
{
    Config& cfg = Config::Global();
    gPickerOn = GetConfigBool(cfg, "mixed_teams", false) && GetConfigBool(cfg, "mixed_picker", false);
    gPickCount[0] = gPickCount[1] = -1;
    gPickedASidekick[0] = gPickedASidekick[1] = false;
    for (int i = 0; i < 2; ++i)
    {
        for (int k = 0; k < 4; ++k)
        {
            gPickerTints[i][k].mIcon = NULL; // fresh scene, fresh faces
        }
    }
}

// A fresh lineup for one side starts when its captain is picked.
static void PickerClearSlots(int side)
{
    Config& cfg = Config::Global();
    char szKey[16];
    for (int k = 2; k <= 4; ++k)
    {
        nlSNPrintf(szKey, 16, "team%d_slot%d", side + 1, k);
        cfg.Set(szKey, "");
    }
}

// The captain grid sliding out, exactly as a vanilla accept does it.
static void MixedPickerCaptainGridOut(IChooseCaptain* p, int side)
{
    ICaptainGridComponent* cg = p->mCaptainGridComponents[side];
    cg->mParentComponent->SetActiveSlide("OUT");
    cg->mParentComponent->Update(0.0f);
    cg->RebuildInstanceTable();
    cg->mMapMenu->UpdateAllItems();
    cg->RebindHighliteComponent("HIGHLIGHT");
    cg->mHighliteComponent->m_bVisible = false;
    FEAudio::PlayAnimAudioEvent((side == 0) ? "sfx_character_group_left_exit" : "sfx_character_group_right_exit", false);
}

// The sidekick grid sliding in, exactly as the vanilla captain accept does it.
static void MixedPickerSidekickGridIn(IChooseCaptain* p, int side)
{
    ISidekickGridComponent* sg = p->mSidekickGridComponents[side];
    sg->mParentComponent->SetActiveSlide("IN");
    sg->mParentComponent->Update(0.0f);
    sg->RebuildInstanceTable();
    sg->mMapMenu->UpdateAllItems();
    sg->RebindHighliteComponent("HIGHLIGHT");
    sg->mHighliteComponent->m_bVisible = false;
    sg->mHighliteVisibilityAtAnimEnd = true;
    sg->SetVisibleInstanceTable(true);
    sg->mParentComponent->m_bVisible = true;
    FEAudio::PlayAnimAudioEvent((side == 0) ? "sfx_character_group_left_enter" : "sfx_character_group_right_enter", false);
}

// The sidekick grid sliding out, as the vanilla sidekick accept does it.
static void MixedPickerSidekickGridOut(IChooseCaptain* p, int side)
{
    ISidekickGridComponent* sg = p->mSidekickGridComponents[side];
    sg->mParentComponent->SetActiveSlide("OUT");
    sg->mParentComponent->Update(0.0f);
    sg->RebuildInstanceTable();
    sg->mMapMenu->UpdateAllItems();
    sg->RebindHighliteComponent("HIGHLIGHT");
    sg->mHighliteComponent->m_bVisible = false;
    FEAudio::PlayAnimAudioEvent((side == 0) ? "sfx_character_group_left_exit" : "sfx_character_group_right_exit", false);
}

// A side has all four picks: write them where the pitch reads them, bring in
// the big captain portrait, and stand ready.
static void MixedPickerFinish(IChooseCaptain* p, int side)
{
    if (p->mComponentState[side].mCurrentPhase == PHASE_CHOOSING_SIDEKICK)
    {
        MixedPickerSidekickGridOut(p, side);
    }
    else
    {
        MixedPickerCaptainGridOut(p, side);
    }

    Config& cfg = Config::Global();
    char szKey[16];
    for (int k = 0; k < 3; ++k)
    {
        nlSNPrintf(szKey, 16, "team%d_slot%d", side + 1, k + 2);
        cfg.Set(szKey, (const char*)gPickNames[side][k]);
        OSReport("[mixed teams] picker: %s = %s\n", szKey, gPickNames[side][k]);
    }

    int teamID = p->mHomeAwayTeam[side];
    char fn0[0x80], fn1[0x80], fn2[0x80];
    CaptainSidekickFilename::Build(CaptainSidekickFilename::TYPE_CAPTAIN, fn0, 0x80, teamID, side);
    CaptainSidekickFilename::Build(CaptainSidekickFilename::TYPE_CAPTAIN_OUTLINE, fn1, 0x80, teamID, side);
    CaptainSidekickFilename::Build(CaptainSidekickFilename::TYPE_CAPTAIN_FLASH, fn2, 0x80, teamID, side);
    p->mAsyncImage[side][0]->QueueLoad(fn0, false);
    p->mAsyncImage[side][1]->QueueLoad(fn1, false);
    p->mAsyncImage[side][2]->QueueLoad(fn2, false);
    p->mDidSwapCaptains[side] = false;

    // The little sidekick head next to the portrait: the first sidekick picked,
    // or hidden when the team is captains only.
    p->StartSidekickMiniHead(side, gPickedASidekick[side] ? (eSidekickID)p->mHomeAwaySidekicks[side] : SK_MYSTERY);

    p->mComponentState[side].mCurrentPhase = PHASE_READY;
    FEAudio::PlayAnimAudioEvent("sfx_accept_no_screen_change", false);
}

// Confirm, with the picker on. Returns true when handled; false hands the
// press back to the vanilla flow (mystery captains, ready sides).
static bool MixedPickerConfirm(IChooseCaptain* p, int side)
{
    if (!MixedPickerOn() || side < 0)
    {
        return false;
    }

    IChooseCaptain::ComponentState::Phase ph = p->mComponentState[side].mCurrentPhase;
    if (ph != PHASE_CHOOSING_CAPTAIN && ph != PHASE_CHOOSING_SIDEKICK)
    {
        return false;
    }

    int& count = gPickCount[side];

    // First confirm: the captain himself.
    if (count < 0)
    {
        if (ph != PHASE_CHOOSING_CAPTAIN)
        {
            return false;
        }
        ICaptainGridComponent* cg = p->mCaptainGridComponents[side];
        eTeamID sel = cg->GetSelectedItem();
        if (sel == TEAM_MYSTERY)
        {
            return false; // vanilla knows what to do with the question mark
        }
        if (!cg->mMapMenu->IsSelectedItemActive())
        {
            FEAudio::PlayAnimAudioEvent("sfx_deny", false);
            return true;
        }

        p->mHomeAwayTeam[side] = sel;
        p->mHomeAwaySidekicks[side] = SK_TOAD; // placeholder until a sidekick is picked
        p->mCaptainGridComponents[side ^ 1]->mMapMenu->SetItemActive(cg->mMapMenu->GetSelectedItem(), false);

        count = 0;
        PickerClearSlots(side);
        PickerTintFace(p, side, 0, true, kPickerCaptCell[(int)sel], GetTeamName(sel));
        FEAudio::PlayAnimAudioEvent("sfx_accept_no_screen_change", false);
        p->mLastCaptainSelectSoundStrPlayed[side] = (char*)FECharacterSound::PlayCaptainName(sel);
        OSReport("[mixed teams] picker: side %d captain = %s\n", side, GetTeamName(sel));
        return true;
    }

    // Teammates two to four, from whichever grid is showing. Each character
    // once per team: a face already numbered is refused.
    const char* nm = NULL;
    const char* cell = NULL;
    bool onCaptainGrid = (ph == PHASE_CHOOSING_CAPTAIN);
    eSidekickID pickedSk = SK_INVALID;
    if (onCaptainGrid)
    {
        eTeamID sel = p->mCaptainGridComponents[side]->GetSelectedItem();
        if (sel == TEAM_INVALID)
        {
            FEAudio::PlayAnimAudioEvent("sfx_deny", false);
            return true;
        }
        nm = GetTeamName(sel); // the robot's "?" cell is a teammate like any other
        cell = kPickerCaptCell[(int)sel];
    }
    else
    {
        eSidekickID sk = p->mSidekickGridComponents[side]->GetSelectedItem();
        nm = GetSidekickName(sk);
        cell = PickerSidekickCell(sk);
        pickedSk = sk;
    }

    if (PickerAlreadyPicked(p, side, nm))
    {
        FEAudio::PlayAnimAudioEvent("sfx_deny", false);
        return true;
    }

    if (onCaptainGrid)
    {
        FECharacterSound::PlayCaptainName(p->mCaptainGridComponents[side]->GetSelectedItem());
    }
    else
    {
        FECharacterSound::PlaySidekickName(pickedSk);
        if (!gPickedASidekick[side])
        {
            gPickedASidekick[side] = true;
            p->mHomeAwaySidekicks[side] = pickedSk;
        }
    }

    PickerTintFace(p, side, count + 1, onCaptainGrid, cell, nm);
    nlSNPrintf(gPickNames[side][count], 20, "%s", nm);
    count++;
    FEAudio::PlayAnimAudioEvent("sfx_accept_no_screen_change", false);

    if (count == 3)
    {
        MixedPickerFinish(p, side);
    }
    return true;
}

// B, with the picker on: un-pick the last choice. Returns true when handled.
static bool MixedPickerBack(IChooseCaptain* p, int side)
{
    OSReport("[mixed teams] picker: B side=%d on=%d single=%d phases=%d/%d counts=%d/%d\n",
             side, MixedPickerOn() ? 1 : 0, p->mIsSinglePlayerInput ? 1 : 0,
             (int)p->mComponentState[0].mCurrentPhase, (int)p->mComponentState[1].mCurrentPhase,
             gPickCount[0], gPickCount[1]);
    if (!MixedPickerOn() || side < 0)
    {
        return false;
    }

    IChooseCaptain::ComponentState::Phase ph = p->mComponentState[side].mCurrentPhase;
    int& count = gPickCount[side];

    if (ph == PHASE_READY && (count == 3 || PickerRestoreSide(p, side)))
    {
        MixedPickerReadyToCaptainGrid(p, side);
        count = 2;
        PickerRetintSide(p, side);
        return true;
    }

    if (ph != PHASE_CHOOSING_CAPTAIN && ph != PHASE_CHOOSING_SIDEKICK)
    {
        return false;
    }

    if (count > 0)
    {
        count--;
        PickerUntintFace(side, count + 1);
        if (gPickedASidekick[side])
        {
            // Recount: does any remaining pick still name a sidekick?
            gPickedASidekick[side] = false;
            for (int k = 0; k < count; ++k)
            {
                eSidekickID sk = ConvertToSidekickID(gPickNames[side][k]);
                if (sk != SK_INVALID)
                {
                    gPickedASidekick[side] = true;
                    p->mHomeAwaySidekicks[side] = sk;
                    break;
                }
            }
            if (!gPickedASidekick[side])
            {
                p->mHomeAwaySidekicks[side] = SK_TOAD;
            }
        }
        FEAudio::PlayAnimAudioEvent("sfx_back_no_screen_change", false);
        return true;
    }

    if (count == 0)
    {
        // Un-choose the captain himself.
        count = -1;
        PickerUntintFace(side, 0);
        p->mCaptainGridComponents[side ^ 1]->mMapMenu->SetItemActive(
            p->mCaptainGridComponents[side]->mMapMenu->GetSelectedItem(), true);
        if (ph == PHASE_CHOOSING_SIDEKICK)
        {
            p->mComponentState[side].GotoPreviousPhase(); // back to the captain grid
        }
        else
        {
            FEAudio::PlayAnimAudioEvent("sfx_back_no_screen_change", false);
        }
        return true;
    }

    // Nothing picked on this side. In single player, with the other side locked
    // in, the game would rewind that side to its sidekick screen; rewind it to
    // the captain grid instead, with its last teammate removed.
    if (p->mIsSinglePlayerInput && side == 1
        && p->mComponentState[0].mCurrentPhase == PHASE_READY
        && (gPickCount[0] == 3 || PickerRestoreSide(p, 0)))
    {
        p->mComponentState[1].GotoPreviousPhase(); // side 2 back to idle
        MixedPickerReadyToCaptainGrid(p, 0);
        gPickCount[0] = 2;
        PickerRetintSide(p, 0);
        return true;
    }

    return false; // captain not chosen: vanilla back (leave the screen)
}

// Y, with the picker on: flip between the captain grid and the sidekick grid.
static void MixedPickerToggle(IChooseCaptain* p, int side)
{
    if (!MixedPickerOn() || side < 0 || gPickCount[side] < 0)
    {
        return;
    }

    IChooseCaptain::ComponentState::Phase ph = p->mComponentState[side].mCurrentPhase;
    if (ph == PHASE_CHOOSING_CAPTAIN)
    {
        MixedPickerCaptainGridOut(p, side);
        MixedPickerSidekickGridIn(p, side);
        p->mComponentState[side].mCurrentPhase = PHASE_CHOOSING_SIDEKICK;

        IChooseCaptain::NameComponent* nc = &p->mNameComponents[side];
        nc->mComponent->SetActiveSlide("Slide2");
        nc->mComponent->Update(0.0f);
        nc->SetCaptainName(GetLOCCharacterName((eTeamID)p->mHomeAwayTeam[side], false, false));
        nc->SetCaptainLogo(GetTeamName((eTeamID)p->mHomeAwayTeam[side]));
        nc->SetSidekickName(GetLOCSidekickName(p->mSidekickGridComponents[side]->GetSelectedItem()));
    }
    else if (ph == PHASE_CHOOSING_SIDEKICK)
    {
        p->mComponentState[side].GotoPreviousPhase(); // vanilla restores the captain grid
    }
}

/**
 * Offset/Address/Size: 0x1DF4 | 0x800BF790 | size: 0x14
 */
IChooseCaptain::IChooseCaptain()
{
    mIsSinglePlayerInput = true;
    mNumTotalPushedPlayers = 0;
}

/**
 * Offset/Address/Size: 0x1CE0 | 0x800BF67C | size: 0x114
 */
IChooseCaptain::~IChooseCaptain()
{
    PickerRestoreAllTints(); // MOD (mixed teams): every face back to normal when this screen goes

    // PORT: was a walk over `this` with hardcoded 0xC and 4 byte strides, three pointers and one pointer.
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            delete mAsyncImage[i][j];
            mAsyncImage[i][j] = NULL;
        }
    }

    delete mCaptainGridComponents[0];
    delete mCaptainGridComponents[1];
    delete mSidekickGridComponents[0];
    delete mSidekickGridComponents[1];
}

/**
 * Offset/Address/Size: 0x1B4C | 0x800BF4E8 | size: 0x194
 */
void IChooseCaptain::Initialize(const char* captainfilename, const char* sidekickfilename)
{
    int i;

    for (i = 0; i < 2; i++)
    {
        mAsyncImage[i][0] = new (0x20, true) AsyncImage(captainfilename, NULL);
        mAsyncImage[i][1] = new (0x20, true) AsyncImage(captainfilename, NULL);
        mAsyncImage[i][2] = new (0x20, true) AsyncImage(captainfilename, NULL);
    }

    mAllPushedPlayers[0] = FE_ALL_PADS;
    mAllPushedPlayerSides[0] = -1;
    mAllPushedPlayers[1] = FE_ALL_PADS;
    mAllPushedPlayerSides[1] = -1;
    mAllPushedPlayers[2] = FE_ALL_PADS;
    mAllPushedPlayerSides[2] = -1;
    mAllPushedPlayers[3] = FE_ALL_PADS;
    mAllPushedPlayerSides[3] = -1;
    mNumTotalPushedPlayers = 0;

    mHomeAwayTeam[0] = nlSingleton<GameInfoManager>::Instance()->GetTeam(0);
    mHomeAwayTeam[1] = nlSingleton<GameInfoManager>::Instance()->GetTeam(1);
    mHomeAwaySidekicks[0] = nlSingleton<GameInfoManager>::Instance()->GetSidekick(0);
    mHomeAwaySidekicks[1] = nlSingleton<GameInfoManager>::Instance()->GetSidekick(1);

    mDidSwapCaptains[1] = false;
    mDidSwapCaptains[0] = false;
    mDidSwapSidekicks[1] = false;
    mDidSwapSidekicks[0] = false;

    mComponentState[0].mCurrentPhase = PHASE_IDLE;
    mComponentState[0].mParent = this;
    mComponentState[0].mHomeAway = 0;
    mComponentState[1].mCurrentPhase = PHASE_IDLE;
    mComponentState[1].mParent = this;
    mComponentState[1].mHomeAway = 1;

    mCaptainSoundDelay[0] = 0.0f;
    mCaptainSoundDelay[1] = 0.0f;

    mLastCaptainSelectSoundStrPlayed[0] = NULL;
    mLastCaptainSelectSoundStrPlayed[1] = NULL;
}

/**
 * Offset/Address/Size: 0x1AB0 | 0x800BF44C | size: 0x9C
 */
void IChooseCaptain::UpdateSound(float dt)
{
    for (s32 i = 0; i < 2; i++)
    {
        if (mCaptainSoundDelay[i] > 0.0f)
        {
            mCaptainSoundDelay[i] -= dt;
            if (mCaptainSoundDelay[i] <= 0.0f)
            {
                mCaptainSoundDelay[i] = 0.0f;
                FECharacterSound::PlayCaptainSlideIn((eTeamID)mHomeAwayTeam[i]);
            }
        }
    }
}

/**
 * Offset/Address/Size: 0x141C | 0x800BEDB8 | size: 0x694
 */
UpdateResult IChooseCaptain::Update(float dt)
{
    PickerTickTints(dt); // MOD (mixed teams): tint fades

    CheckForDisconnectedHumanPlayers();
    FindAliveHumanPlayers();

    UpdateSinglePlayerState();

    unsigned char goback;
    unsigned char isdoneanimating;

    for (int i = 0; i < 4; i++)
    {
        eFEINPUT_PAD inputpad = (eFEINPUT_PAD)i;
        int side = GetSide(i);

        if (side == -1)
        {
            continue;
        }

        if (g_pFEInput->JustPressed(inputpad, 0x200, false, NULL))
        {
            goback = 0;

            // MOD (mixed teams): with the picker on, B un-picks instead.
            if (MixedPickerBack(this, side))
            {
                continue;
            }

            switch (mComponentState[side].mCurrentPhase)
            {
            case PHASE_READY:
                mComponentState[side].GotoPreviousPhase();
                break;

            case PHASE_CHOOSING_SIDEKICK:
                mComponentState[side].GotoPreviousPhase();
                break;

            case PHASE_CHOOSING_CAPTAIN:
                if (mIsSinglePlayerInput)
                {
                    if (side == 1 && mIsSinglePlayerInput)
                    {
                        mComponentState[1].GotoPreviousPhase();
                        mComponentState[0].GotoPreviousPhase();
                    }
                    else
                    {
                        goback = true;
                    }
                }
                else
                {
                    goback = true;
                }
                break;
            }

            if (goback)
            {
                FEAudio::PlayAnimAudioEvent("sfx_back_no_screen_change", false);
                return UPDATE_GO_BACK;
            }
        }
        else if (g_pFEInput->JustPressed(inputpad, 0x100, false, &inputpad))
        {
            isdoneanimating = 1;

            switch (mComponentState[side].mCurrentPhase)
            {
            case PHASE_CHOOSING_CAPTAIN:
            {
                TLSlide* slide = mCaptainGridComponents[side]->mParentComponent->GetActiveSlide();
                unsigned char done;

                if (slide == NULL)
                {
                    done = 1;
                }
                else if (slide->m_time >= slide->m_start + slide->m_duration)
                {
                    done = 1;
                }
                else
                {
                    done = 0;
                }
                isdoneanimating = done;
                break;
            }

            case PHASE_CHOOSING_SIDEKICK:
            {
                TLSlide* slide = mSidekickGridComponents[side]->mParentComponent->GetActiveSlide();
                unsigned char done;

                if (slide == NULL)
                {
                    done = 1;
                }
                else if (slide->m_time >= slide->m_start + slide->m_duration)
                {
                    done = 1;
                }
                else
                {
                    done = 0;
                }
                isdoneanimating = done;
                break;
            }
            }

            if (isdoneanimating)
            {
                int side2 = GetSide(inputpad);

                // MOD (mixed teams): with the picker on, confirm records one of
                // four picks; the vanilla step only runs when it declines.
                if (!MixedPickerConfirm(this, side2))
                {
                    mComponentState[side2].GotoNextPhase();
                }

                if (mIsSinglePlayerInput && mComponentState[0].mCurrentPhase == PHASE_READY && mComponentState[1].mCurrentPhase == PHASE_IDLE)
                {
                    mComponentState[1].SetCurrentPhase(PHASE_CHOOSING_CAPTAIN);
                }
            }
        }
        else if (g_pFEInput->JustPressed(inputpad, 0x400, false, &inputpad))
        {
            // MOD (mixed teams): X flips between the two character grids.
            MixedPickerToggle(this, GetSide(inputpad));
        }
        else
        {
            switch (mComponentState[side].mCurrentPhase)
            {
            case PHASE_CHOOSING_CAPTAIN:
                mCaptainGridComponents[side]->Update(inputpad);
                if (mCaptainGridComponents[side]->mHasChangedSinceLastUpdate)
                {
                    mNameComponents[side].mComponent->SetActiveSlide("Slide1");
                    mNameComponents[side].mComponent->Update(0.0f);
                    mNameComponents[side].SetCaptainName(GetLOCCharacterName(mCaptainGridComponents[side]->GetSelectedItem(), false, true));
                    mNameComponents[side].SetCaptainLogo(GetTeamName(mCaptainGridComponents[side]->GetSelectedItem()));
                }
                break;

            case PHASE_CHOOSING_SIDEKICK:
                mSidekickGridComponents[side]->Update(inputpad);
                if (mSidekickGridComponents[side]->mHasChangedSinceLastUpdate)
                {
                    mNameComponents[side].mComponent->SetActiveSlide("Slide2");
                    mNameComponents[side].mComponent->Update(0.0f);
                    mNameComponents[side].SetCaptainName(GetLOCCharacterName((eTeamID)mHomeAwayTeam[side], false, false));
                    mNameComponents[side].SetSidekickName(GetLOCSidekickName(mSidekickGridComponents[side]->GetSelectedItem()));
                    mNameComponents[side].SetCaptainLogo(GetTeamName((eTeamID)mHomeAwayTeam[side]));
                }
                break;
            }
        }
    }

    if (mComponentState[0].mCurrentPhase == PHASE_READY && mComponentState[1].mCurrentPhase == PHASE_READY)
    {
        int playerIndex;
        GameInfoManager* const gim = nlSingleton<GameInfoManager>::s_pInstance;

        gim->SetTeam(0, (eTeamID)mHomeAwayTeam[0]);
        gim->SetTeam(1, (eTeamID)mHomeAwayTeam[1]);
        gim->SetSidekick(0, (eSidekickID)mHomeAwaySidekicks[0]);
        gim->SetSidekick(1, (eSidekickID)mHomeAwaySidekicks[1]);

        for (playerIndex = 0; playerIndex < mNumTotalPushedPlayers; playerIndex++)
        {
            gim->SetPlayingSide((unsigned short)mAllPushedPlayers[playerIndex], (short)mAllPushedPlayerSides[playerIndex]);
        }

        return UPDATE_GO_FORWARD;
    }

    UpdateAsyncImages();

    return UPDATE_OK;
}

/**
 * Offset/Address/Size: 0x12F0 | 0x800BEC8C | size: 0x12C
 */
void IChooseCaptain::UpdateAsyncImages()
{
    int j;
    int i;
    bool canswapcaptains;

    for (j = 0; j < 3; j++)
    {
        mAsyncImage[0][j]->Update(false);
        mAsyncImage[1][j]->Update(false);
    }

    for (i = 0; i < 2; i++)
    {
        if (mComponentState[i].mCurrentPhase != PHASE_READY)
        {
            mCaptainSoundDelay[i] = 0.0f;
        }
        else
        {
            canswapcaptains = false;
            if (!mDidSwapCaptains[i])
            {
                if (mAsyncImage[i][0]->CanSwapTextures() && mAsyncImage[i][1]->CanSwapTextures() && mAsyncImage[i][2]->CanSwapTextures())
                {
                    canswapcaptains = true;
                }
            }

            if (canswapcaptains)
            {
                mCaptainComponents[i]->SetActiveSlide("Slide1");
                mCaptainComponents[i]->m_bVisible = true;
                mAsyncImage[i][0]->Update(true);
                mAsyncImage[i][1]->Update(true);
                mAsyncImage[i][2]->Update(true);
                mDidSwapCaptains[i] = true;
                mCaptainSoundDelay[i] = mCaptainSlideDurations[0];
            }
        }
    }
}

/**
 * Offset/Address/Size: 0xAB0 | 0x800BE44C | size: 0x840
 */
void IChooseCaptain::SceneCreated(FEPresentation* presentation)
{
    TLComponentInstance* compinstance;
    char filenameC2[0x80];
    char filenameC1[0x80];
    char filenameC0[0x80];
    char filenameS2[0x80];
    char filenameS1[0x80];
    char filenameS0[0x80];

    compinstance = FEFinder<TLComponentInstance, 4>::Find<TLSlide>(
        presentation->m_currentSlide,
        InlineHasher(nlStringLowerHash("Layer")),
        InlineHasher(nlStringLowerHash("LEFT_CAPT")));
    SetupCaptainComponent(compinstance, 0);
    compinstance->m_bVisible = false;

    compinstance = FEFinder<TLComponentInstance, 4>::Find<TLSlide>(
        presentation->m_currentSlide,
        InlineHasher(nlStringLowerHash("Layer")),
        InlineHasher(nlStringLowerHash("RIGHT_CAPT")));
    SetupCaptainComponent(compinstance, 1);
    compinstance->m_bVisible = false;

    {
        int team0 = mHomeAwayTeam[0];
        CaptainSidekickFilename::Build(CaptainSidekickFilename::TYPE_CAPTAIN, filenameC0, 0x80, team0, 0);
        CaptainSidekickFilename::Build(CaptainSidekickFilename::TYPE_CAPTAIN_OUTLINE, filenameC1, 0x80, team0, 0);
        CaptainSidekickFilename::Build(CaptainSidekickFilename::TYPE_CAPTAIN_FLASH, filenameC2, 0x80, team0, 0);
    }
    mAsyncImage[0][0]->QueueLoad(filenameC0, true);
    mAsyncImage[0][1]->QueueLoad(filenameC1, true);
    mAsyncImage[0][2]->QueueLoad(filenameC2, true);
    mDidSwapCaptains[0] = false;

    {
        int team1 = mHomeAwayTeam[1];
        CaptainSidekickFilename::Build(CaptainSidekickFilename::TYPE_CAPTAIN, filenameS0, 0x80, team1, 1);
        CaptainSidekickFilename::Build(CaptainSidekickFilename::TYPE_CAPTAIN_OUTLINE, filenameS1, 0x80, team1, 1);
        CaptainSidekickFilename::Build(CaptainSidekickFilename::TYPE_CAPTAIN_FLASH, filenameS2, 0x80, team1, 1);
    }
    mAsyncImage[1][0]->QueueLoad(filenameS0, true);
    mAsyncImage[1][1]->QueueLoad(filenameS1, true);
    mAsyncImage[1][2]->QueueLoad(filenameS2, true);
    mDidSwapCaptains[1] = false;

    compinstance = FEFinder<TLComponentInstance, 4>::Find<TLSlide>(
        presentation->m_currentSlide,
        InlineHasher(nlStringLowerHash("Layer")),
        InlineHasher(nlStringLowerHash("LEFT_SK")));
    mSidekickComponents[0] = compinstance;
    {
        TLSlide* slide = compinstance->GetActiveSlide();
        mSidekickSlideDurations[0] = (slide->m_start + slide->m_duration) / 2.0f;
    }
    compinstance->m_bVisible = false;
    mSidekickComponents[0]->m_bVisible = false;

    compinstance = FEFinder<TLComponentInstance, 4>::Find<TLSlide>(
        presentation->m_currentSlide,
        InlineHasher(nlStringLowerHash("Layer")),
        InlineHasher(nlStringLowerHash("RIGHT_SK")));
    mSidekickComponents[1] = compinstance;
    {
        TLSlide* slide = compinstance->GetActiveSlide();
        mSidekickSlideDurations[1] = (slide->m_start + slide->m_duration) / 2.0f;
    }
    compinstance->m_bVisible = false;
    mSidekickComponents[1]->m_bVisible = false;

    mCaptainGridComponents[0] = new (8, false) ICaptainGridComponent(
        FEFinder<TLComponentInstance, 4>::Find<TLSlide>(
            presentation->m_currentSlide,
            InlineHasher(nlStringLowerHash("Layer")),
            InlineHasher(nlStringLowerHash("CAPTAIN_CHOOSER_LEFT"))),
        false);

    mCaptainGridComponents[1] = new (8, false) ICaptainGridComponent(
        FEFinder<TLComponentInstance, 4>::Find<TLSlide>(
            presentation->m_currentSlide,
            InlineHasher(nlStringLowerHash("Layer")),
            InlineHasher(nlStringLowerHash("CAPTAIN_CHOOSER_RIGHT"))),
        true);

    mCaptainGridComponents[0]->BuildMapMenu();
    mCaptainGridComponents[1]->BuildMapMenu();

    mSidekickGridComponents[0] = new (8, false) ISidekickGridComponent(
        FEFinder<TLComponentInstance, 4>::Find<TLSlide>(
            presentation->m_currentSlide,
            InlineHasher(nlStringLowerHash("Layer")),
            InlineHasher(nlStringLowerHash("CHOOSE_SIDEKICKS_LEFT"))),
        false);

    mSidekickGridComponents[1] = new (8, false) ISidekickGridComponent(
        FEFinder<TLComponentInstance, 4>::Find<TLSlide>(
            presentation->m_currentSlide,
            InlineHasher(nlStringLowerHash("Layer")),
            InlineHasher(nlStringLowerHash("CHOOSE_SIDEKICKS_RIGHT"))),
        true);

    mSidekickGridComponents[0]->mParentComponent->m_bVisible = false;
    mSidekickGridComponents[1]->mParentComponent->m_bVisible = false;
    mSidekickGridComponents[0]->BuildMapMenu();
    mSidekickGridComponents[1]->BuildMapMenu();

    mSidekickMiniHeadComponents[0] = FEFinder<TLComponentInstance, 4>::Find<TLSlide>(
        presentation->m_currentSlide,
        InlineHasher(nlStringLowerHash("Layer")),
        InlineHasher(nlStringLowerHash("sidekick icon left")));

    mSidekickMiniHeadComponents[1] = FEFinder<TLComponentInstance, 4>::Find<TLSlide>(
        presentation->m_currentSlide,
        InlineHasher(nlStringLowerHash("Layer")),
        InlineHasher(nlStringLowerHash("sidekick icon right")));

    mNameComponents[0].mComponent = FEFinder<TLComponentInstance, 4>::Find<TLSlide>(
        presentation->m_currentSlide,
        InlineHasher(nlStringLowerHash("Layer")),
        InlineHasher(nlStringLowerHash("CAPTAIN_NAME_LEFT")));

    mNameComponents[0].mCaptainObjName = "CAPTAIN_NAME";
    mNameComponents[0].mSidekickObjName = "SIDEKICK_NAME";

    mNameComponents[1].mComponent = FEFinder<TLComponentInstance, 4>::Find<TLSlide>(
        presentation->m_currentSlide,
        InlineHasher(nlStringLowerHash("Layer")),
        InlineHasher(nlStringLowerHash("CAPTAIN_NAME_RIGHT")));

    mNameComponents[1].mCaptainObjName = "CAPTAIN_NAME";
    mNameComponents[1].mSidekickObjName = "SIDEKICK_NAME";

    // MOD (mixed teams): fresh picker state every time this screen appears.
    MixedPickerReset();

    mComponentState[0].SetCurrentPhase(PHASE_CHOOSING_CAPTAIN);
    mComponentState[1].SetCurrentPhase(PHASE_IDLE);
}

/**
 * Offset/Address/Size: 0x890 | 0x800BE22C | size: 0x220
 */
void IChooseCaptain::SetupCaptainComponent(TLComponentInstance* compinstance, int homeaway)
{
    mCaptainComponents[homeaway] = compinstance;

    TLSlide* slide = compinstance->GetActiveSlide();
    mCaptainSlideDurations[homeaway] = (slide->m_start + slide->m_duration) / 2.0f;

    mAsyncImage[homeaway][0]->mImageInstance = FEFinder<TLImageInstance, 2>::Find<TLSlide>(
        compinstance->GetActiveSlide(),
        InlineHasher(nlStringLowerHash((homeaway == 0) ? "CAPT_L" : "CAPT_R")));

    mAsyncImage[homeaway][1]->mImageInstance = FEFinder<TLImageInstance, 2>::Find<TLSlide>(
        compinstance->GetActiveSlide(),
        InlineHasher(nlStringLowerHash((homeaway == 0) ? "CAPT_L_OUT" : "CAPT_R_OUT")));

    mAsyncImage[homeaway][2]->mImageInstance = FEFinder<TLImageInstance, 2>::Find<TLSlide>(
        compinstance->GetActiveSlide(),
        InlineHasher(nlStringLowerHash((homeaway == 0) ? "CAPT_L_WHITE" : "CAPT_R_WHITE")));
}

/**
 * Offset/Address/Size: 0x70C | 0x800BE0A8 | size: 0x184
 */
void IChooseCaptain::StartSidekickMiniHead(int homeaway, eSidekickID sidekick)
{
    static const char* SidekickImageNames[] = {
        "choose_sidek_toad",
        "choose_sidek_koopa",
        "choose_sidek_hammer",
        "choose_sidek_birdo",
    };

    static const char* SidekickDestImageNames[] = {
        "sidekick left",
        "sidekick right",
    };

    FETextureResource* sourceres;
    TLComponentInstance* component;
    TLSlide* activeslide;
    TLImageInstance* sourceimage;
    TLImageInstance* destimage;

    if (sidekick == SK_MYSTERY)
    {
        mSidekickMiniHeadComponents[homeaway]->m_bVisible = false;
        return;
    }

    component = mSidekickMiniHeadComponents[homeaway];
    activeslide = component->GetActiveSlide();
    component->SetActiveSlide(activeslide);
    component->Update(0.0f);
    component->m_bVisible = true;

    TLComponentInstance* sourcecomp = mSidekickGridComponents[homeaway]->GetParentComponent();
    sourceimage = FEFinder<TLImageInstance, 2>::Find<TLSlide>(
        sourcecomp->GetActiveSlide(),
        InlineHasher(nlStringLowerHash(SidekickImageNames[sidekick])));
    sourceres = sourceimage->m_pTextureResource;

    destimage = FEFinder<TLImageInstance, 2>::Find<TLSlide>(
        component->GetActiveSlide(),
        InlineHasher(nlStringLowerHash(SidekickDestImageNames[homeaway])));

    destimage->m_component->pChildren = (TLSlide*)sourceres;
}

/**
 * Offset/Address/Size: 0x670 | 0x800BE00C | size: 0x9C
 */
void IChooseCaptain::CheckForDisconnectedHumanPlayers()
{
    for (int i = 0; i < 4; i++)
    {
        if (IsPlayerPushed(i))
        {
            if (!g_pFEInput->IsConnected((eFEINPUT_PAD)i))
            {
                PopPlayer((eFEINPUT_PAD)i);
            }
        }
    }
}

/**
 * Offset/Address/Size: 0x4E0 | 0x800BDE7C | size: 0x190
 */
void IChooseCaptain::FindAliveHumanPlayers()
{
    for (int i = 0; i < 4; i++)
    {
        eFEINPUT_PAD pad = (eFEINPUT_PAD)i;

        if (g_pFEInput->IsAutoPressed(pad, 0xB, true, NULL) || g_pFEInput->IsAutoPressed(pad, 0xC, true, NULL)
            || g_pFEInput->IsAutoPressed(pad, 0xD, true, NULL) || g_pFEInput->IsAutoPressed(pad, 0xE, true, NULL)
            || g_pFEInput->JustPressed(pad, 0x100, false, NULL))
        {
            int numPushedPlayers = mNumTotalPushedPlayers;

            if (!IsPlayerPushed(i))
            {
                int side = numPushedPlayers & 1;
                if (mComponentState[side].mCurrentPhase == PHASE_IDLE)
                {
                    mComponentState[side].SetCurrentPhase(PHASE_CHOOSING_CAPTAIN);
                }

                mAllPushedPlayers[mNumTotalPushedPlayers] = (eFEINPUT_PAD)i;
                if (side != -1)
                {
                    mAllPushedPlayerSides[mNumTotalPushedPlayers] = side;
                }
                else
                {
                    mAllPushedPlayerSides[mNumTotalPushedPlayers] = mNumTotalPushedPlayers & 1;
                }

                mNumTotalPushedPlayers++;
            }
        }
    }
}

int IChooseCaptain::GetSide(int padid)
{
    if (mIsSinglePlayerInput)
    {
        if (mComponentState[0].mCurrentPhase < PHASE_READY)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        for (int i = 0; i < mNumTotalPushedPlayers; i++)
        {
            if (mAllPushedPlayers[i] == padid)
            {
                return mAllPushedPlayerSides[i];
            }
        }
        return -1;
    }
}

void IChooseCaptain::UpdateSinglePlayerState()
{
    int numSide1;
    int numSide0;
    mIsSinglePlayerInput = numSide0 = 0;

    if (mNumTotalPushedPlayers == 1)
    {
        mIsSinglePlayerInput = true;
    }
    else
    {
        int numSide1 = numSide0;
        for (int i = 0; i < mNumTotalPushedPlayers; i++)
        {
            if (mAllPushedPlayerSides[i] == 0)
            {
                numSide0++;
            }
            else if (mAllPushedPlayerSides[i] == 1)
            {
                numSide1++;
            }
        }
        if (numSide0 == 0 || numSide1 == 0)
        {
            mIsSinglePlayerInput = true;
        }
    }
}

/**
 * Offset/Address/Size: 0x388 | 0x800BDD24 | size: 0x158
 */
void IChooseCaptain::SetupForLastPhase(eFEINPUT_PAD pad)
{
    UpdateSinglePlayerState();

    if (mIsSinglePlayerInput)
    {
        mComponentState[1].GotoPreviousPhase();
        return;
    }

    if (pad == FE_ALL_PADS)
    {
        mComponentState[0].GotoPreviousPhase();
        mComponentState[1].GotoPreviousPhase();
        return;
    }

    int side = GetSide(pad);

    if (side == -1)
    {
        mComponentState[1].GotoPreviousPhase();
    }
    else
    {
        mComponentState[side].GotoPreviousPhase();
    }
}

/**
 * Offset/Address/Size: 0x338 | 0x800BDCD4 | size: 0x50
 */
void IChooseCaptain::PushPlayer(eFEINPUT_PAD pad, int side)
{
    mAllPushedPlayers[mNumTotalPushedPlayers] = pad;
    if (side != -1)
    {
        mAllPushedPlayerSides[mNumTotalPushedPlayers] = side;
    }
    else
    {
        mAllPushedPlayerSides[mNumTotalPushedPlayers] = mNumTotalPushedPlayers & 1;
    }
    mNumTotalPushedPlayers++;
}

/**
 * Offset/Address/Size: 0x1DC | 0x800BDB78 | size: 0x15C
 */
void IChooseCaptain::PopPlayer(eFEINPUT_PAD pad)
{
    int foundIndex = 0;
    int idx = 0;
    for (int i = 0; i < mNumTotalPushedPlayers; i++, idx++)
    {
        if (mAllPushedPlayers[i] == pad)
        {
            foundIndex = idx;
            break;
        }
    }

    for (int i = foundIndex; i < mNumTotalPushedPlayers - 1; i++)
    {
        mAllPushedPlayers[i] = mAllPushedPlayers[i + 1];
        mAllPushedPlayerSides[i] = mAllPushedPlayerSides[i + 1];
    }

    mNumTotalPushedPlayers--;
    UpdateSinglePlayerState();

    if (mNumTotalPushedPlayers != 0 && mIsSinglePlayerInput && mComponentState[1].mCurrentPhase != PHASE_READY)
    {
        if (mComponentState[0].mCurrentPhase != PHASE_READY)
        {
            mComponentState[1].SetCurrentPhase(PHASE_IDLE);
        }

        if (mNumTotalPushedPlayers == 1)
        {
            mAllPushedPlayerSides[0] = 0;
        }
    }
}

/**
 * Offset/Address/Size: 0x1A8 | 0x800BDB44 | size: 0x34
 */
void IChooseCaptain::ResetPushPlayerData()
{
    mAllPushedPlayers[0] = FE_ALL_PADS;
    mAllPushedPlayerSides[0] = -1;
    mAllPushedPlayers[1] = FE_ALL_PADS;
    mAllPushedPlayerSides[1] = -1;
    mAllPushedPlayers[2] = FE_ALL_PADS;
    mAllPushedPlayerSides[2] = -1;
    mAllPushedPlayers[3] = FE_ALL_PADS;
    mAllPushedPlayerSides[3] = -1;
    mNumTotalPushedPlayers = 0;
}

/**
 * Offset/Address/Size: 0xD8 | 0x800BDA74 | size: 0xD0
 */
void IChooseCaptain::PushPlayerWithGameInfoDB()
{
    int i;
    int side;

    for (i = 0; i < 4; i++)
    {
        side = nlSingleton<GameInfoManager>::Instance()->GetPlayingSide(i);
        if (g_pFEInput->IsConnected((eFEINPUT_PAD)i))
        {
            if (side != -1)
            {
                mAllPushedPlayers[mNumTotalPushedPlayers] = (eFEINPUT_PAD)i;
                if (side != -1)
                {
                    mAllPushedPlayerSides[mNumTotalPushedPlayers] = side;
                }
                else
                {
                    mAllPushedPlayerSides[mNumTotalPushedPlayers] = mNumTotalPushedPlayers & 1;
                }
                mNumTotalPushedPlayers++;
            }
        }
        else
        {
            nlSingleton<GameInfoManager>::Instance()->SetPlayingSide(i, -1);
        }
    }
}

/**
 * Offset/Address/Size: 0x8C | 0x800BDA28 | size: 0x4C
 */
void IChooseCaptain::MoveHighlightToCurrentCaptain(int which)
{
    if (which == 0 || which == 1)
    {
        mCaptainGridComponents[which]->MoveHighlightToTarget((eTeamID)mHomeAwayTeam[which]);
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x800BD99C | size: 0x8C
 */
void IChooseCaptain::SetupNameComponentToCurrentCaptain(int slot)
{
    if (slot == 0 || slot == 1)
    {
        mNameComponents[slot].SetCaptainName(GetLOCCharacterName((eTeamID)mHomeAwayTeam[slot], false, false));
        mNameComponents[slot].SetCaptainLogo(GetTeamName((eTeamID)mHomeAwayTeam[slot]));
    }
}
