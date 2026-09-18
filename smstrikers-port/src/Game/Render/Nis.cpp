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
// MOD (mixed teams): intros. A captain standing in a sidekick slot would
// otherwise use the sidekick's animation (Donkey Kong upright on two legs).
//
// Walk-in ("enter_stadium", "establish_stadium"): he plays his own walk from
// his own file, along his own path, but placed a set distance behind the
// leader so the team walks in single file (intro_walk_gap metres apart).
//
// Face-off ("attitude"): by default borrowed captains are not drawn at all
// (intro_faceoff_hide). With intro_faceoff_own on, each performs his own
// face-off routine at the sidekick's final mark, timed to finish with the
// scene; he stays hidden until his routine starts.
// ---------------------------------------------------------------------------
extern char* NisLoadOwnFile(const char* charName, const char* likeName, const char* nisType, int* outSize, char* outName);
extern const char* NisLastType(int target);

enum { NIS_MOD_NONE = 0, NIS_MOD_WALK = 1, NIS_MOD_FACEOFF = 2, NIS_MOD_SLOT = 3 };

static char* gNisCharBuffer[10];                 // the captain's own file, while in use
static cPN_SAnimController* gNisSlotCtrl[10];    // the slot's animation, kept for measuring
static Nis* gNisCharOwner[10];
static int gNisMode[10];
static int gNisSlotNumber[10];                   // 1..3 within the team
static nlVector3 gNisShift[10];                  // added to the root, after mirroring
static bool gNisShiftDone[10];
static float gNisDelay[10];                      // seconds before the own routine starts
static float gNisWalkGap[10];                    // walk-in: metres behind the leader
static float gNisWalkSide[10];                   // walk-in: metres to the side (+left/-right)
static float gNisLastDirX[10];                   // walk-in: last known heading
static float gNisLastDirY[10];
static bool gNisWalkDelayOnly[10];               // walk-in: space by start time only
static int gNisWalkLogged[10];                   // diagnostics: how many samples logged
static float gNisWalkLoggedT[10];                // diagnostics: controller time of the last sample
static Nis* gNisHideOwner[10];                   // borrowed captains hidden in the face-off
static char gNisOwnName[10][64];                 // the own file's name, for its voice script
int gNisTriggerVoiceOnly = 0;                    // while set, AddTrigger keeps only character voice

// The cutscene's idea of a character class, from the character's name.
static NisCharacterClass NisClassOf(eCharacterClass cc)
{
    const char* n = GetCharacterName(cc);
    if (n == NULL) return NIS_CHAR_CLASS_INVALID;
    if (nlStrCmp<char>(n, "birdo") == 0) return NIS_CHAR_CLASS_BIRDO;
    if (nlStrCmp<char>(n, "daisy") == 0) return NIS_CHAR_CLASS_DAISY;
    if (nlStrCmp<char>(n, "donkeykong") == 0) return NIS_CHAR_CLASS_DONKEYKONG;
    if (strncmp(n, "hammer", 6) == 0) return NIS_CHAR_CLASS_HAMMERBROS;
    if (nlStrCmp<char>(n, "koopa") == 0) return NIS_CHAR_CLASS_KOOPA;
    if (nlStrCmp<char>(n, "luigi") == 0) return NIS_CHAR_CLASS_LUIGI;
    if (nlStrCmp<char>(n, "mario") == 0) return NIS_CHAR_CLASS_MARIO;
    if (nlStrCmp<char>(n, "peach") == 0) return NIS_CHAR_CLASS_PEACH;
    if (nlStrCmp<char>(n, "toad") == 0) return NIS_CHAR_CLASS_TOAD;
    if (nlStrCmp<char>(n, "waluigi") == 0) return NIS_CHAR_CLASS_WALUIGI;
    if (nlStrCmp<char>(n, "wario") == 0) return NIS_CHAR_CLASS_WARIO;
    if (nlStrCmp<char>(n, "yoshi") == 0) return NIS_CHAR_CLASS_YOSHI;
    return NIS_CHAR_CLASS_INVALID;
}

// For the voice scripts: the own file names of this cutscene's borrowed captains.
int NisOwnFilesFor(const Nis* pNis, const char** outNames, int maxNames)
{
    int n = 0;
    for (int i = 0; i < 10 && n < maxNames; i++)
    {
        if (gNisCharOwner[i] == pNis && gNisOwnName[i][0] != 0)
        {
            outNames[n++] = gNisOwnName[i];
        }
    }
    return n;
}

// True when any comma-separated token of list appears inside name.
static bool NisTypeMatches(const char* list, const char* name)
{
    if (list == NULL || name == NULL) return false;
    const char* p = list;
    while (*p)
    {
        while (*p == ' ' || *p == ',') ++p;
        const char* q = p;
        while (*q && *q != ',' && *q != ' ') ++q;
        if (q > p)
        {
            char tok[64];
            size_t n = (size_t)(q - p);
            if (n > 63) n = 63;
            memcpy(tok, p, n);
            tok[n] = 0;
            if (strstr(name, tok) != NULL) return true;
        }
        p = q;
    }
    return false;
}

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

static cSAnim* NisOwnIntroAnim(Nis* owner, int charIndex, NisTarget target, const char* likeName, cSAnim* slotAnim, int slotNumber)
{
    Config& cfg = Config::Global();
    if (!GetConfigBool(cfg, "mixed_teams", false) || !GetConfigBool(cfg, "intro_own_anims", true))
    {
        return NULL;
    }
    if (target != NIS_TARGET_HOME_SIDEKICK && target != NIS_TARGET_AWAY_SIDEKICK && target != NIS_TARGET_LOSER_SIDEKICK)
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

    // Which scene is this? Files are named by scene.
    BasicString<char, Detail::TempStringAllocator> walkTypes
        = cfg.Get<BasicString<char, Detail::TempStringAllocator> >("intro_walk_scenes", BasicString<char, Detail::TempStringAllocator>("enter_stadium,establish_stadium"));
    BasicString<char, Detail::TempStringAllocator> faceTypes
        = cfg.Get<BasicString<char, Detail::TempStringAllocator> >("intro_faceoff_scenes", BasicString<char, Detail::TempStringAllocator>("attitude"));
    BasicString<char, Detail::TempStringAllocator> markTypes
        = cfg.Get<BasicString<char, Detail::TempStringAllocator> >("intro_mark_scenes", BasicString<char, Detail::TempStringAllocator>("loser"));
    bool faceoff = NisTypeMatches(faceTypes.c_str(), likeName);
    bool walking = NisTypeMatches(walkTypes.c_str(), likeName);
    bool onMark = !faceoff && !walking && NisTypeMatches(markTypes.c_str(), likeName)
                  && GetConfigBool(cfg, "reaction_own_anims", true);
    if (!faceoff && !walking && !onMark)
    {
        return NULL; // not a scene we touch
    }

    if (faceoff)
    {
        if (GetConfigBool(cfg, "intro_faceoff_hide", true))
        {
            gNisHideOwner[charIndex] = owner;
            OSReport("[mixed teams] intro: %s hidden for the face-off\n", charName);
            return NULL;
        }
        if (!GetConfigBool(cfg, "intro_faceoff_own", false))
        {
            OSReport("[mixed teams] intro: %s keeps the generic face-off routine\n", charName);
            return NULL;
        }
        BasicString<char, Detail::TempStringAllocator> keep
            = cfg.Get<BasicString<char, Detail::TempStringAllocator> >("intro_faceoff_generic", BasicString<char, Detail::TempStringAllocator>(""));
        if (NisNameInList(keep.c_str(), charName))
        {
            OSReport("[mixed teams] intro: %s keeps the generic face-off routine (listed)\n", charName);
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

    if (gNisCharBuffer[charIndex] != NULL)
    {
        nlFree(gNisCharBuffer[charIndex]);
    }
    gNisCharBuffer[charIndex] = buffer;
    gNisSlotCtrl[charIndex] = ::new (AllocateSAnimController()) cPN_SAnimController(slotAnim, NULL, PM_HOLD, NULL, 0, false);
    gNisCharOwner[charIndex] = owner;
    nlSNPrintf(gNisOwnName[charIndex], 64, "%s", szName);
    bool standStill = onMark;
    gNisMode[charIndex] = faceoff ? NIS_MOD_FACEOFF : (standStill ? NIS_MOD_SLOT : NIS_MOD_WALK);
    gNisSlotNumber[charIndex] = slotNumber;
    gNisShift[charIndex].x = gNisShift[charIndex].y = gNisShift[charIndex].z = 0.0f;
    gNisShiftDone[charIndex] = false;
    gNisDelay[charIndex] = 0.0f;

    if (standStill)
    {
        // A reaction on the spot (conceding a goal): he stays on the sidekick's
        // mark, which is already spread out, and performs his own routine.
        gNisShiftDone[charIndex] = true;
        OSReport("[mixed teams] intro: character %d (%s) reacts on the slot's mark with '%s'\n",
                 charIndex, charName, szName);
    }
    else if (walking)
    {
        // Single file: his own path, moved back by gap * slot number, with a
        // small left/right stagger so the line reads as a group. "Back" is the
        // walk direction, or the way he faces at the end if he barely walks.
        nlVector3 a = { 0.0f, 0.0f, 0.0f };
        nlVector3 b = { 0.0f, 0.0f, 0.0f };
        own->GetRootTrans(0.0f, &a);
        own->GetRootTrans(own->GetDuration(), &b);
        float dx = b.x - a.x;
        float dy = b.y - a.y;
        float len = sqrtf(dx * dx + dy * dy);
        if (len >= 3.0f)
        {
            dx /= len; dy /= len;
        }
        else
        {
            u16 face = 0;
            own->GetRootRot(own->GetDuration(), &face);
            float rad = 0.0000958738f * (float)face;
            dx = cosf(rad); dy = sinf(rad);
        }
        float gap = GetConfigFloat(cfg, "intro_walk_gap", 2.5f);
        if (target == NIS_TARGET_AWAY_SIDEKICK)
        {
            gap = GetConfigFloat(cfg, "intro_walk_gap_away", gap);
        }
        float stagger = GetConfigFloat(cfg, "intro_walk_stagger", 0.8f);
        float delay = GetConfigFloat(cfg, "intro_walk_delay", 0.35f);
        // Per-scene overrides, keyed on the scene's own name as the log prints
        // it: intro_walk_gap_establish_stadium_home, intro_walk_stagger_..., intro_walk_delay_...
        {
            const char* sceneType = NisLastType((int)target);
            if (sceneType != NULL && sceneType[0] != 0)
            {
                char szKey[96];
                nlSNPrintf(szKey, 96, "intro_walk_gap_%s", sceneType);
                gap = GetConfigFloat(cfg, szKey, gap);
                nlSNPrintf(szKey, 96, "intro_walk_stagger_%s", sceneType);
                stagger = GetConfigFloat(cfg, szKey, stagger);
                nlSNPrintf(szKey, 96, "intro_walk_delay_%s", sceneType);
                delay = GetConfigFloat(cfg, szKey, delay);
            }
        }
        // intro_walk_spacing: "shift" (distance + delay) or "delay" (start times only).
        BasicString<char, Detail::TempStringAllocator> spacing
            = cfg.Get<BasicString<char, Detail::TempStringAllocator> >("intro_walk_spacing", BasicString<char, Detail::TempStringAllocator>("shift"));
        {
            const char* sceneType = NisLastType((int)target);
            if (sceneType != NULL && sceneType[0] != 0)
            {
                char szKey[96];
                nlSNPrintf(szKey, 96, "intro_walk_spacing_%s", sceneType);
                spacing = cfg.Get<BasicString<char, Detail::TempStringAllocator> >(szKey, spacing);
            }
        }
        gNisWalkDelayOnly[charIndex] = (spacing.c_str() != NULL && nlStrCmp<char>(spacing.c_str(), "delay") == 0);
        gNisWalkLogged[charIndex] = 0;
        gNisWalkLoggedT[charIndex] = -1.0f;
        float side = (slotNumber % 2 == 1) ? -1.0f : 1.0f; // 1 left, 2 right, 3 left
        gNisWalkGap[charIndex] = gNisWalkDelayOnly[charIndex] ? 0.0f : gap * (float)slotNumber;
        gNisWalkSide[charIndex] = gNisWalkDelayOnly[charIndex] ? 0.0f : stagger * side;
        gNisLastDirX[charIndex] = dx;
        gNisLastDirY[charIndex] = dy;
        gNisShift[charIndex].x = -dx * gNisWalkGap[charIndex] + (-dy) * gNisWalkSide[charIndex];
        gNisShift[charIndex].y = -dy * gNisWalkGap[charIndex] + (dx) * gNisWalkSide[charIndex];
        gNisShiftDone[charIndex] = true;
        // And each follower sets off a beat after the one ahead, which spreads
        // the line along the path whatever direction the shift ended up in.
        gNisDelay[charIndex] = delay * (float)slotNumber;
        OSReport("[mixed teams] intro: character %d (%s) walks in with '%s', %.1f m behind the leader, %.1f m to the %s, sets off after %.2fs (scene %s)\n",
                 charIndex, charName, szName, gap * (float)slotNumber, stagger, side < 0.0f ? "left" : "right",
                 gNisDelay[charIndex], NisLastType((int)target));
    }
    else
    {
        // Face-off: finish together with the scene; placement measured on the first frame.
        float slotDur = slotAnim->GetDuration();
        float ownDur = own->GetDuration();
        gNisDelay[charIndex] = (slotDur > ownDur) ? (slotDur - ownDur) : 0.0f;
        OSReport("[mixed teams] intro: character %d (%s) performs '%s' at the slot's mark, starting %.2fs in (slot %.2fs, own %.2fs)\n",
                 charIndex, charName, szName, gNisDelay[charIndex], slotDur, ownDur);
    }
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
                    gNisMode[i] = NIS_MOD_NONE;
                }
                if (gNisHideOwner[i] != this)
                {
                    gNisHideOwner[i] = NULL;
                }
                cSAnim* own = NisOwnIntroAnim(this, i, mTarget, mHeader->name, anim, numAnimations + 1);
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
        if (gNisHideOwner[i] == this)
        {
            gNisHideOwner[i] = NULL;
        }
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
            // MOD (mixed teams): a face-off routine waits so it ends with the scene.
            if (gNisCharOwner[i] == this && gNisDelay[i] > 0.0f)
            {
                gNisDelay[i] -= dt;
                if (gNisDelay[i] > 0.0f)
                {
                    continue;
                }
            }
            pController->Update(dt);
            if (gNisCharOwner[i] == this && gNisMode[i] == NIS_MOD_SLOT && gNisSlotCtrl[i] != NULL)
            {
                gNisSlotCtrl[i]->Update(dt); // MOD (mixed teams): the mark keeps time too
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
        if (gNisHideOwner[i] == this)
        {
            pDC->mVisible = false; // MOD (mixed teams): hidden for the face-off
            continue;
        }
        pDC->mVisible = true;

        nlVector3 rootTrans = { 0.0f, 0.0f, 0.0f };
        u16 angle = 0;
        // MOD (mixed teams): on the overhead scene a borrowed captain is placed by the slot.
        cPN_SAnimController* pPlace = (gNisCharOwner[i] == this && gNisMode[i] == NIS_MOD_SLOT && gNisSlotCtrl[i] != NULL)
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

        // MOD (mixed teams): borrowed captains with their own routine.
        if (gNisCharOwner[i] == this && gNisMode[i] != NIS_MOD_NONE)
        {
            if (gNisDelay[i] > 0.0f && gNisMode[i] == NIS_MOD_FACEOFF)
            {
                pDC->mVisible = false; // not on yet
                continue;
            }
            if (gNisMode[i] == NIS_MOD_FACEOFF && !gNisShiftDone[i] && gNisSlotCtrl[i] != NULL)
            {
                // Where the sidekick's routine ends versus where his own ends,
                // measured on the hips; the difference moves his whole routine.
                cPN_SAnimController* slot = gNisSlotCtrl[i];
                cPN_SAnimController* own = mCharacterControllers[i];
                float slotEnd = slot->m_pSAnim->GetDuration();
                float ownEnd = own->m_pSAnim->GetDuration();

                nlVector3 sr = { 0.0f, 0.0f, 0.0f };
                u16 sa = 0;
                slot->m_pSAnim->GetRootTrans(slotEnd, &sr);
                slot->m_pSAnim->GetRootRot(slotEnd, &sa);
                if (mMirrored) { sr.x *= -1.0f; sa = sa + (0x4000 - sa) * 2; }
                nlVec3Add(sr, sr, mHeader->stadiumOffset);
                slot->SetTime(slotEnd);
                pDC->EvaluateFrom(*slot, sr, sa);
                nlVector3 slotHip = pDC->mBip01Position;

                nlVector3 orr = { 0.0f, 0.0f, 0.0f };
                u16 oa = 0;
                own->m_pSAnim->GetRootTrans(ownEnd, &orr);
                own->m_pSAnim->GetRootRot(ownEnd, &oa);
                if (mMirrored) { orr.x *= -1.0f; oa = oa + (0x4000 - oa) * 2; }
                nlVec3Add(orr, orr, mHeader->stadiumOffset);
                float keep = own->get_fTime();
                own->SetTime(ownEnd);
                pDC->EvaluateFrom(*own, orr, oa);
                nlVector3 ownHip = pDC->mBip01Position;
                own->SetTime(keep);

                gNisShift[i].x = slotHip.x - ownHip.x;
                gNisShift[i].y = slotHip.y - ownHip.y;
                gNisShift[i].z = 0.0f;
                gNisShiftDone[i] = true;
                OSReport("[mixed teams] intro: character %d face-off placed by (%.1f, %.1f)\n", i, gNisShift[i].x, gNisShift[i].y);
            }
            if (gNisMode[i] == NIS_MOD_WALK)
            {
                // Follow the path as it bends: "behind" is the heading right now.
                cSAnim* pAnim = mCharacterControllers[i]->m_pSAnim;
                float tNow = mCharacterControllers[i]->get_fTime();
                float tPrev = tNow - 0.25f;
                if (tPrev < 0.0f) { tPrev = 0.0f; }
                nlVector3 pNow = { 0.0f, 0.0f, 0.0f };
                nlVector3 pPrev = { 0.0f, 0.0f, 0.0f };
                pAnim->GetRootTrans(tNow, &pNow);
                pAnim->GetRootTrans(tPrev, &pPrev);
                float vx = pNow.x - pPrev.x;
                float vy = pNow.y - pPrev.y;
                float vl = sqrtf(vx * vx + vy * vy);
                if (vl > 0.05f)
                {
                    vx /= vl; vy /= vl;
                    gNisLastDirX[i] += (vx - gNisLastDirX[i]) * 0.2f; // eased, no jitter
                    gNisLastDirY[i] += (vy - gNisLastDirY[i]) * 0.2f;
                    float dl = sqrtf(gNisLastDirX[i] * gNisLastDirX[i] + gNisLastDirY[i] * gNisLastDirY[i]);
                    if (dl > 0.001f) { gNisLastDirX[i] /= dl; gNisLastDirY[i] /= dl; }
                }
                float dx = gNisLastDirX[i];
                float dy = gNisLastDirY[i];
                gNisShift[i].x = -dx * gNisWalkGap[i] + (-dy) * gNisWalkSide[i];
                gNisShift[i].y = -dy * gNisWalkGap[i] + (dx) * gNisWalkSide[i];
                if (gNisWalkLogged[i] < 5 && tNow >= gNisWalkLoggedT[i] + 1.0f)
                {
                    ++gNisWalkLogged[i];
                    gNisWalkLoggedT[i] = tNow;
                    OSReport("[mixed teams] walk: '%s' char %d t=%.2f root (%.1f, %.1f, %.1f) moved (%.2f, %.2f) heading (%.2f, %.2f) shift (%.1f, %.1f)%s\n",
                             mHeader->name, i, tNow, rootTrans.x, rootTrans.y, rootTrans.z, vx, vy, dx, dy,
                             gNisShift[i].x, gNisShift[i].y, mMirrored ? " mirrored" : "");
                }
            }
            nlVector3 shift = gNisShift[i];
            if (gNisMode[i] == NIS_MOD_WALK && mMirrored) { shift.x = -shift.x; }
            nlVec3Add(rootTrans, rootTrans, shift);
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
    // MOD (mixed teams): a borrowed captain's own script only lends its voice.
    if (gNisTriggerVoiceOnly)
    {
        bool voice = (triggerType == NIS_TRIGGER_TYPE_PLAY_RANDOM_DIALOGUE)
            || (triggerType == NIS_TRIGGER_TYPE_PLAY_SOUND && trigParams != NULL && trigParams->param1 != (unsigned long)-1);
        if (!voice)
        {
            return;
        }
    }
    if (mNumTriggers >= MAX_NUM_TRIGGERS)
    {
        return;
    }
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

// MOD (mixed teams): a voice line belongs in a cutscene if someone in it has
// that class, or if no borrowed captain was swapped in (vanilla behaviour).
static bool NisVoiceBelongsHere(const Nis& nis, NisCharacterClass cls)
{
    bool swapped = false;
    for (int i = 0; i < 10; i++)
    {
        if (gNisCharOwner[i] == &nis) { swapped = true; break; }
    }
    if (!swapped || cls == NIS_CHAR_CLASS_INVALID)
    {
        return true;
    }
    for (int i = 0; i < 10; i++)
    {
        if (nis.mCharacterControllers[i] == NULL || g_pCharacters[i] == NULL) continue;
        if (NisClassOf(((cPlayer*)g_pCharacters[i])->m_eCharacterClass) == cls) return true;
    }
    return false;
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
            // MOD (mixed teams): no Toad lines from a slot that holds a captain.
            if (!NisVoiceBelongsHere(nis, (NisCharacterClass)params.param1))
            {
                return;
            }
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
        if (!NisVoiceBelongsHere(nis, (NisCharacterClass)params.param1)) // MOD (mixed teams)
        {
            return;
        }
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
