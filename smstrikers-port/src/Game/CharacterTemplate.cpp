#include "Game/CharacterTemplate.h"
#include "NL/nlConfig.h"
#include "NL/gc/gcSwizzler.h"
#include "NL/gl/glMemory.h"
#include "Game/CharacterEffects.h"
#include "dolphin/os.h"
#include "Game/SHierarchy.h"
#include "Game/SAnim/AnimRetargeter.h"
#include "Game/Player.h"
#include "Game/AI/Fielder.h"
#include "Game/CharacterTweaks.h"
#include "Game/FE/feHelpFuncs.h"
#include "Game/Goalie.h"
#include "Game/AI/ScriptAction.h"
#include "Game/Audio/AudioLoader.h"
#include "Game/Sys/GCStream.h"
#include "Game/Audio/AudioStream.h"
#include "Game/AnimInventory.h"
#include "Game/Physics/CharacterPhysicsElement.h"
#include "Game/Triggers/AnimTrigger.h"
#include "Game/Triggers/SebringAnimScript.h"
#include "NL/nlFile.h"
#include "NL/nlFileGC.h"
#include "NL/nlPrint.h"
#include "NL/nlString.h"
#include "NL/nlMemory.h"
#include "NL/gl/gl.h"
#include "NL/gl/glRenderList.h"
#include "NL/gl/glTexture.h"
#include "NL/glx/glxTexture.h"

extern SoundPropAccessor* gpBIRDOSoundPropAccessor;
extern SoundPropAccessor* gpDAISYSoundPropAccessor;
extern SoundPropAccessor* gpDKSoundPropAccessor;
extern SoundPropAccessor* gpHAMBROSSoundPropAccessor;
extern SoundPropAccessor* gpKOOPASoundPropAccessor;
extern SoundPropAccessor* gpLUIGISoundPropAccessor;
extern SoundPropAccessor* gpMARIOSoundPropAccessor;
extern SoundPropAccessor* gpPEACHSoundPropAccessor;
extern SoundPropAccessor* gpTOADSoundPropAccessor;
extern SoundPropAccessor* gpWALUIGISoundPropAccessor;
extern SoundPropAccessor* gpWARIOSoundPropAccessor;
extern SoundPropAccessor* gpYOSHISoundPropAccessor;
extern SoundPropAccessor* gpSUPERSoundPropAccessor;
extern SoundPropAccessor* gpCRITTERSoundPropAccessor;

SebringAnimTagScriptInterpreter* g_pAnimScriptInterp;
class cCharacter;
// PORT: cCharacter*, matching the three files that declare it extern.
cCharacter* g_pCurrentlyUpdatingCharacter;

extern AnimProperties GLOBALAnimProperties[];
extern AnimProperties GOALIEAnimProperties[];
void AnimTriggerCallback_MARIO(unsigned int);

cCharacter* g_pCharacters[10];
static tCharacterTemplateInfo g_aCharacterTemplateInfo[13] = {
    { "birdo", FIELDER, "characters/birdo/birdo.glg", "characters/birdo/birdo_blend.glg", "characters/birdo/birdo.glt", "art/animation/birdo.trg", AnimTriggerCallback_MARIO, "art/animation/birdo.shier", "birdo", GLOBALAnimProperties, 119, "art/animation/birdo.sanim", "mario", gpBIRDOSoundPropAccessor, "art/animation/birdo.cph", "birdo.ini", "art/characters/birdo/animretarget/birdo.bin" },
    { "daisy", FIELDER, "characters/daisy/daisy.glg", "characters/daisy/daisy_blend.glg", "characters/daisy/daisy.glt", "art/animation/daisy.trg", AnimTriggerCallback_MARIO, "art/animation/daisy.shier", "daisy", GLOBALAnimProperties, 119, "art/animation/daisy.sanim", "daisy", gpDAISYSoundPropAccessor, "art/animation/daisy.cph", "daisy.ini", "art/characters/daisy/animretarget/daisy.bin" },
    { "donkeykong", FIELDER, "characters/donkeykong/donkeykong.glg", "characters/donkeykong/donkeykong_blend.glg", "characters/donkeykong/donkeykong.glt", "art/animation/donkeykong.trg", AnimTriggerCallback_MARIO, "art/animation/donkeykong.shier", "donkeykong", GLOBALAnimProperties, 119, "art/animation/donkeykong.sanim", "donkeykong", gpDKSoundPropAccessor, "art/animation/DonkeyKong.cph", "dk.ini", "art/characters/donkeykong/animretarget/donkeykong.bin" },
    { "hammerbro", FIELDER, "characters/hammerbro/hammerbro.glg", "characters/hammerbro/hammerbro_blend.glg", "characters/hammerbro/hammerbro.glt", "art/animation/hammerbro.trg", AnimTriggerCallback_MARIO, "art/animation/hammerbro.shier", "hammerbro", GLOBALAnimProperties, 119, "art/animation/hammerbro.sanim", "hammerbro", gpHAMBROSSoundPropAccessor, "art/animation/hammerbro.cph", "hammerbros.ini", "art/characters/hammerbro/animretarget/hammerbro.bin" },
    { "koopa", FIELDER, "characters/koopa/koopa.glg", "characters/koopa/koopa_blend.glg", "characters/koopa/koopa.glt", "art/animation/koopa.trg", AnimTriggerCallback_MARIO, "art/animation/koopa.shier", "koopa", GLOBALAnimProperties, 119, "art/animation/koopa.sanim", "mario", gpKOOPASoundPropAccessor, "art/animation/koopa.cph", "koopa.ini", "art/characters/koopa/animretarget/koopa.bin" },
    { "luigi", FIELDER, "characters/luigi/luigi.glg", "characters/luigi/luigi_blend.glg", "characters/luigi/luigi.glt", "art/animation/luigi.trg", NULL, "art/animation/luigi.shier", "luigi", GLOBALAnimProperties, 119, "art/animation/luigi.sanim", "luigi", gpLUIGISoundPropAccessor, "art/animation/mario.cph", "luigi.ini", "art/characters/luigi/animretarget/luigi.bin" },
    { "mario", FIELDER, "characters/mario/mario.glg", "characters/mario/mario_blend.glg", "characters/mario/mario.glt", "art/animation/mario.trg", AnimTriggerCallback_MARIO, "art/animation/mario.shier", "mario", GLOBALAnimProperties, 119, "art/animation/mario.sanim", "mario", gpMARIOSoundPropAccessor, "art/animation/mario.cph", "mario.ini", "art/characters/mario/animretarget/mario.bin" },
    { "peach", FIELDER, "characters/peach/peach.glg", "characters/peach/peach_blend.glg", "characters/peach/peach.glt", "art/animation/peach.trg", AnimTriggerCallback_MARIO, "art/animation/peach.shier", "peach", GLOBALAnimProperties, 119, "art/animation/peach.sanim", "peach", gpPEACHSoundPropAccessor, "art/animation/peach.cph", "peach.ini", "art/characters/peach/animretarget/peach.bin" },
    { "toad", FIELDER, "characters/toad/toad.glg", "characters/toad/toad_blend.glg", "characters/toad/toad.glt", "art/animation/toad.trg", AnimTriggerCallback_MARIO, "art/animation/toad.shier", "toad", GLOBALAnimProperties, 119, "art/animation/toad.sanim", "toad", gpTOADSoundPropAccessor, "art/animation/toad.cph", "toad.ini", "art/characters/toad/animretarget/toad.bin" },
    { "waluigi", FIELDER, "characters/waluigi/waluigi.glg", "characters/waluigi/waluigi_blend.glg", "characters/waluigi/waluigi.glt", "art/animation/waluigi.trg", NULL, "art/animation/waluigi.shier", "waluigi", GLOBALAnimProperties, 119, "art/animation/waluigi.sanim", "waluigi", gpWALUIGISoundPropAccessor, "art/animation/waluigi.cph", "waluigi.ini", "art/characters/waluigi/animretarget/waluigi.bin" },
    { "wario", FIELDER, "characters/wario/wario.glg", "characters/wario/wario_blend.glg", "characters/wario/wario.glt", "art/animation/wario.trg", NULL, "art/animation/wario.shier", "wario", GLOBALAnimProperties, 119, "art/animation/wario.sanim", "wario", gpWARIOSoundPropAccessor, "art/animation/wario.cph", "wario.ini", "art/characters/wario/animretarget/wario.bin" },
    { "yoshi", FIELDER, "characters/yoshi/yoshi.glg", "characters/yoshi/yoshi_blend.glg", "characters/yoshi/yoshi.glt", "art/animation/yoshi.trg", AnimTriggerCallback_MARIO, "art/animation/yoshi.shier", "yoshi", GLOBALAnimProperties, 119, "art/animation/yoshi.sanim", "yoshi", gpYOSHISoundPropAccessor, "art/animation/yoshi.cph", "yoshi.ini", "art/characters/yoshi/animretarget/yoshi.bin" },
    { "superteam", FIELDER, "characters/superteam/superteam.glg", "characters/superteam/superteam_blend.glg", "characters/superteam/superteam.glt", "art/animation/superteam.trg", NULL, "art/animation/superteam.shier", "superteam", GLOBALAnimProperties, 119, "art/animation/superteam.sanim", "superteam", gpSUPERSoundPropAccessor, "art/animation/superteam.cph", "superteam.ini", "art/characters/superteam/animretarget/superteam.bin" },
};
static tCharacterTemplate* g_aCharacterTemplates[13];
static tCharacterTemplateInfo g_GoalieTemplateInfo = {
    "mariogoalie", GOALIE, "characters/mariogoalie/mariogoalie.glg", "characters/mariogoalie/mariogoalie_blend.glg", "characters/mariogoalie/mariogoalie.glt", "art/animation/mariogoalie.trg", NULL, "art/animation/mariogoalie.shier", "mariogoalie", GOALIEAnimProperties, 149, "art/animation/mariogoalie.sanim", "mario", gpCRITTERSoundPropAccessor, "art/animation/mariogoalie.cph", "goalie.ini", NULL
};
static tCharacterTemplate* g_GoalieTemplate;

// PORT: a texture hash; as s32, one with bit 31 set sign-extends when compared against the unsigned long handle.
static u32 skiptexture = 0xFFFFFFFF;

static tGoalieTemplateInfo g_GoalieTextureInfo[9] = {
    { "daisygoalie", "characters/daisygoalie/daisygoalie.glt", 0 },
    { "donkeykonggoalie", "characters/donkeykonggoalie/donkeykonggoalie.glt", 0 },
    { "luigigoalie", "characters/luigigoalie/luigigoalie.glt", 0 },
    { "mariogoalie", "characters/mariogoalie/mariogoalie.glt", 0 },
    { "peachgoalie", "characters/peachgoalie/peachgoalie.glt", 0 },
    { "waluigigoalie", "characters/waluigigoalie/waluigigoalie.glt", 0 },
    { "wariogoalie", "characters/wariogoalie/wariogoalie.glt", 0 },
    { "yoshigoalie", "characters/yoshigoalie/yoshigoalie.glt", 0 },
    { "superteamgoalie", "characters/superteamgoalie/superteamgoalie.glt", 0 },
};

static u32 GetHashFromTextureFile(const char* szTextureFileName)
{
    char name[200];
    char* pDest = name;
    const char* pSrc = NULL;
    int count = 0;

    for (count = 0; count < 100; count++)
    {
        if (szTextureFileName[count] == '\\' || szTextureFileName[count] == '/')
        {
            pSrc = &szTextureFileName[count + 1];
            break;
        }
    }

    for (int k = 0; k < 100; k++)
    {
        if (*pSrc != '\0' && *pSrc != '.')
        {
            __memcpy(pDest, pSrc, sizeof(*pDest));
            pSrc++;
            pDest++;
        }
        else
        {
            *pDest = '\0';
            return nlStringLowerHash(name);
        }
    }
    return 0;
}

static cAnimInventory* FindDuplicateAnimInventory(int nCurIndex, unsigned long uHashID);
static char* GetCharacterTriggerFileName(eCharacterClass cc);

/**
 * Offset/Address/Size: 0x2128 | 0x80014410 | size: 0x34
 */
char* GetCharacterName(eCharacterClass cc)
{
    if (cc < 13)
    {
        return (char*)g_aCharacterTemplateInfo[cc].szCharName;
    }
    return (char*)g_GoalieTextureInfo[cc - 13].szCharName;
}

static char* GetCharacterModelFileName(eCharacterClass cc)
{
    if (cc < NUM_FIELDER_CLASSES)
    {
        return (char*)g_aCharacterTemplateInfo[cc].szModelFilename;
    }
    return (char*)g_GoalieTemplateInfo.szModelFilename;
}

static char* GetCharacterModelTextureFileName(eCharacterClass cc)
{
    if (cc < NUM_FIELDER_CLASSES)
    {
        return (char*)g_aCharacterTemplateInfo[cc].szTextureFilename;
    }
    return (char*)g_GoalieTextureInfo[cc - NUM_FIELDER_CLASSES].szTextureFilename;
}

static AnimProperties* GetCharacterModelAnimProperties(eCharacterClass cc)
{
    if (cc < NUM_FIELDER_CLASSES)
    {
        return (AnimProperties*)g_aCharacterTemplateInfo[cc].pAnimProperties;
    }
    return (AnimProperties*)g_GoalieTemplateInfo.pAnimProperties;
}

static int GetCharacterModelNumAnumProperties(eCharacterClass cc)
{
    if (cc < NUM_FIELDER_CLASSES)
    {
        return g_aCharacterTemplateInfo[cc].nNumAnimProperties;
    }
    return g_GoalieTemplateInfo.nNumAnimProperties;
}

static char* GetCharacterModelHierarchyFileName(eCharacterClass cc)
{
    if (cc < NUM_FIELDER_CLASSES)
    {
        return (char*)g_aCharacterTemplateInfo[cc].szHierarchyFilename;
    }
    return (char*)g_GoalieTemplateInfo.szHierarchyFilename;
}

static char* GetCharacterModelHierarchyName(eCharacterClass cc)
{
    if (cc < NUM_FIELDER_CLASSES)
    {
        return (char*)g_aCharacterTemplateInfo[cc].szHierarchy;
    }
    return (char*)g_GoalieTemplateInfo.szHierarchy;
}

static char* GetCharacterModelAnimFileName(eCharacterClass cc)
{
    if (cc < NUM_FIELDER_CLASSES)
    {
        return (char*)g_aCharacterTemplateInfo[cc].szAnimFilename;
    }
    return (char*)g_GoalieTemplateInfo.szAnimFilename;
}

static unsigned char IsSidekick(eCharacterClass cc)
{
    if (cc == BIRDO || cc == HAMMERBROS || cc == KOOPA || cc == TOAD)
    {
        return true;
    }
    return false;
}

/**
 * Offset/Address/Size: 0x20EC | 0x800143D4 | size: 0x3C
 */
bool IsCaptain(eCharacterClass cc)
{
    if (((cc - 1) <= 1U) || ((cc - 5) <= 2U) || ((cc - 9) <= 2U) || (cc == 0xC))
    {
        return true;
    }
    return false;
}

/**
 * Offset/Address/Size: 0x1CFC | 0x80013FE4 | size: 0x3F0
 */
void CharacterLoadingGuts(tCharacterTemplate* pCharacterTemplate, const tCharacterTemplateInfo& charTemplateInfo, eCharacterClass cc, bool bForViewer)
{
    glModel* pRigidCharacterModel = glLoadModel(charTemplateInfo.szModelFilename, NULL);
    glModel* pBlendCharacterModel = glLoadModel(charTemplateInfo.szBlendedModelFilename, NULL);

    pCharacterTemplate->nCharacterModelID[0] = pRigidCharacterModel->id;
    pCharacterTemplate->nCharacterModelID[1] = pBlendCharacterModel->id;

    pCharacterTemplate->pHierarchyInventory = new (nlMalloc(sizeof(cInventory<cSHierarchy>), 8, false)) cInventory<cSHierarchy>();
    pCharacterTemplate->pHierarchyInventory->AddFile((char*)charTemplateInfo.szHierarchyFilename);

    if (!bForViewer)
    {
        CharacterPhysicsData* pPhys = new (nlMalloc(sizeof(CharacterPhysicsData), 8, false)) CharacterPhysicsData();
        pCharacterTemplate->pPhysicsData = pPhys;
        LoadCharacterPhysicsElements(charTemplateInfo.szPhysicsFilename, (CharacterPhysicsData*)pCharacterTemplate->pPhysicsData);
    }
    else
    {
        pCharacterTemplate->pPhysicsData = NULL;
    }

    pCharacterTemplate->uAnimInventoryHashID = nlStringLowerHash(charTemplateInfo.szAnimFilename);

    cAnimInventory* found = FindDuplicateAnimInventory(cc, pCharacterTemplate->uAnimInventoryHashID);

    if (found != NULL)
    {
        pCharacterTemplate->pAnimInventory = found;
        pCharacterTemplate->bAnimInventoryCopy = true;
    }
    else
    {
        cAnimInventory* pAnim = new (nlMalloc(sizeof(cAnimInventory), 8, false))
            cAnimInventory(charTemplateInfo.pAnimProperties, charTemplateInfo.nNumAnimProperties);
        pCharacterTemplate->pAnimInventory = pAnim;
        pCharacterTemplate->pAnimInventory->AddAnimBundle(charTemplateInfo.szAnimFilename);
        pCharacterTemplate->bAnimInventoryCopy = false;

        cInventory<cSAnim>* pAnimCont = pCharacterTemplate->pAnimInventory->m_pSAnimInventory;
        g_pAnimScriptInterp->SetupAnimationTriggers(GetCharacterTriggerFileName(cc), pAnimCont);
    }

    if (charTemplateInfo.szAnimRetargetFilename != NULL)
    {
        pCharacterTemplate->pAnimRetargetListInventory = new (nlMalloc(sizeof(cInventory<AnimRetargetList>), 8, false)) cInventory<AnimRetargetList>();
        pCharacterTemplate->pAnimRetargetListInventory->AddFile((char*)charTemplateInfo.szAnimRetargetFilename);
    }
    else
    {
        pCharacterTemplate->pAnimRetargetListInventory = NULL;
    }
}

static cAnimInventory* FindDuplicateAnimInventory(int nCurIndex, unsigned long uHashID)
{
    for (int index = 0; index < NUM_FIELDER_CLASSES; index++)
    {
        if (index == nCurIndex)
            continue;
        if (g_aCharacterTemplates[index] == NULL)
            continue;
        if (uHashID != g_aCharacterTemplates[index]->uAnimInventoryHashID)
            continue;
        return g_aCharacterTemplates[index]->pAnimInventory;
    }
    return NULL;
}

static char* GetCharacterTriggerFileName(eCharacterClass cc)
{
    if (cc < NUM_FIELDER_CLASSES)
    {
        return (char*)g_aCharacterTemplateInfo[cc].szTriggerFilename;
    }
    return (char*)g_GoalieTemplateInfo.szTriggerFilename;
}

/**
 * Offset/Address/Size: 0x1ABC | 0x80013DA4 | size: 0x240
 */
cPlayer* CreateCharacter(int nPlayerID, int nTeamID, eCharacterClass cc, bool bForViewer)
{
    if (cc >= NUM_FIELDER_CLASSES)
    {
        return CreateGoalie(cc, bForViewer);
    }

    if (g_aCharacterTemplates[cc] == NULL)
    {
        glLoadTextureBundle(g_aCharacterTemplateInfo[cc].szTextureFilename);
        g_aCharacterTemplates[cc] = (tCharacterTemplate*)nlMalloc(sizeof(tCharacterTemplate), 8, false);
        CharacterLoadingGuts(g_aCharacterTemplates[cc], g_aCharacterTemplateInfo[cc], cc, bForViewer);
    }

    cInventory<cSHierarchy>* pHierInv = g_aCharacterTemplates[cc]->pHierarchyInventory;
    u32 hash = nlStringHash(g_aCharacterTemplateInfo[cc].szHierarchy);

    AnimRetargetList* pAnimRetargetList;
    FielderTweaks* pTweaks;
    cSHierarchy* pHierarchy = pHierInv->Find((unsigned int)hash);

    pAnimRetargetList = NULL;
    if (g_aCharacterTemplates[cc]->pAnimRetargetListInventory != NULL)
    {
        pAnimRetargetList = g_aCharacterTemplates[cc]->pAnimRetargetListInventory->Find(0);
    }

    pTweaks = new (nlMalloc(sizeof(FielderTweaks), 8, false)) FielderTweaks(g_aCharacterTemplateInfo[cc].szTweaksFilename);

    cPlayer* pChar;
    if (!bForViewer)
    {
        cFielder* pFielder = new (nlMalloc(sizeof(cFielder), 8, false)) cFielder(
            nPlayerID, nTeamID, cc, (const int*)g_aCharacterTemplates[cc], pHierarchy, g_aCharacterTemplates[cc]->pAnimInventory, g_aCharacterTemplates[cc]->pPhysicsData, pTweaks, pAnimRetargetList);
        pChar = pFielder;
    }
    else
    {
        cPlayer* pPlayer = new (nlMalloc(sizeof(cPlayer), 8, false)) cPlayer(
            nPlayerID, cc, (const int*)g_aCharacterTemplates[cc], pHierarchy, g_aCharacterTemplates[cc]->pAnimInventory, g_aCharacterTemplates[cc]->pPhysicsData, (PlayerTweaks*)pTweaks, pAnimRetargetList, (eClassTypes)1);
        pChar = pPlayer;
    }

    pChar->m_szEffectsName = g_aCharacterTemplateInfo[cc].szEffectsName;
    if (!AudioLoader::gbDisableAudio)
    {
        pChar->SetSFX(g_aCharacterTemplateInfo[cc].pSFXPropAccessor);
    }

    return pChar;
}

/**
 * Offset/Address/Size: 0x1AA0 | 0x80013D88 | size: 0x1C
 */
// PORT: glxTextureLoadCallback_t returns unsigned long, and it was declared s32 and installed through a cast.
static unsigned long SidekickTexture_cb(unsigned long textureId)
{
    unsigned long result = (unsigned long)-1;
    if (textureId != skiptexture)
    {
        result = textureId;
    }
    return result;
}

/**
 * Offset/Address/Size: 0x14A4 | 0x8001378C | size: 0x5FC
 */
cPlayer* CreateSidekick(int nPlayerID, int nTeamID, eCharacterClass cc, eCharacterClass captaincc, bool bForViewer)
{
    char szTexPath[64];
    char szArtPath[64];
    char szBundlePath[64];
    char szPlayerPath[64];

    glxTextureLoadCallback_t oldCallback = glx_SetLoadCallback(SidekickTexture_cb);

    if (cc == HAMMERBROS)
    {
        nlSNPrintf(szTexPath, 64, "hammerbro/hammer_mario");
    }
    else
    {
        nlSNPrintf(szTexPath, 64, "%s/%s_mario", GetCharacterName(cc), GetCharacterName(cc));
    }

    skiptexture = glGetTexture(szTexPath);

    cPlayer* pChar = CreateCharacter(nPlayerID, nTeamID, cc, bForViewer);

    glx_SetLoadCallback(oldCallback);

    bool swaptextureloaded = false;

    if (cc == HAMMERBROS)
    {
        nlSNPrintf(szBundlePath, 64, "characters/%s/hammer_%s.glt", GetCharacterName(cc), GetCharacterName(captaincc));
        nlSNPrintf(szArtPath, 64, "art/characters/%s/hammer_%s.glt", GetCharacterName(cc), GetCharacterName(captaincc));
    }
    else
    {
        nlSNPrintf(szBundlePath, 64, "characters/%s/%s_%s.glt", GetCharacterName(cc), GetCharacterName(cc), GetCharacterName(captaincc));
        nlSNPrintf(szArtPath, 64, "art/characters/%s/%s_%s.glt", GetCharacterName(cc), GetCharacterName(cc), GetCharacterName(captaincc));
    }

    if (cc == HAMMERBROS)
    {
        nlSNPrintf(szPlayerPath, 64, "hammer_%s/hammer_%s", GetCharacterName(captaincc), GetCharacterName(captaincc));
    }
    else
    {
        nlSNPrintf(szPlayerPath, 64, "%s_%s/%s_%s", GetCharacterName(cc), GetCharacterName(captaincc), GetCharacterName(cc), GetCharacterName(captaincc));
    }

    if (glTextureLoad(glGetTexture(szPlayerPath)))
    {
        swaptextureloaded = true;
    }
    else
    {
        nlFile* texturefile = nlOpen(szArtPath);
        if (texturefile != NULL)
        {
            nlClose(texturefile);
            swaptextureloaded = glLoadTextureBundle(szBundlePath);
        }
    }

    if (swaptextureloaded)
    {
        if (cc == HAMMERBROS)
        {
            nlSNPrintf(szBundlePath, 64, "%s/hammer_mario", GetCharacterName(cc));
        }
        else
        {
            nlSNPrintf(szBundlePath, 64, "%s/%s_mario", GetCharacterName(cc), GetCharacterName(cc));
        }
        pChar->m_uNormalTextureID = glGetTexture(szBundlePath);
        pChar->m_uSwapTextureID = glGetTexture(szPlayerPath);
    }
    else
    {
        pChar->m_uNormalTextureID = (u32)-1;
        pChar->m_uSwapTextureID = (u32)-1;
    }

    return pChar;
}

/**
 * Offset/Address/Size: 0xE70 | 0x80013158 | size: 0x634
 */
cPlayer* CreateGoalie(eCharacterClass gcc, bool bForViewer)
{
    s32 goalieIdx = gcc - NUM_FIELDER_CLASSES;
    if (!g_GoalieTextureInfo[goalieIdx].bLoaded)
    {
        glLoadTextureBundle(g_GoalieTextureInfo[goalieIdx].szTextureFilename);
        g_GoalieTextureInfo[goalieIdx].bLoaded = 1;
    }

    if (g_GoalieTemplate == NULL)
    {
        g_GoalieTemplate = (tCharacterTemplate*)nlMalloc(sizeof(tCharacterTemplate), 8, false);
        CharacterLoadingGuts(g_GoalieTemplate, g_GoalieTemplateInfo, gcc, bForViewer);
    }

    cSHierarchy* pHierarchy = g_GoalieTemplate->pHierarchyInventory->Find((char*)g_GoalieTemplateInfo.szHierarchy);

    AnimRetargetList* pAnimRetargetList = NULL;
    if (g_GoalieTemplate->pAnimRetargetListInventory != NULL)
    {
        pAnimRetargetList = g_GoalieTemplate->pAnimRetargetListInventory->Find(0);
    }

    GoalieTweaks* pTweaks = new (nlMalloc(sizeof(GoalieTweaks), 8, false)) GoalieTweaks(g_GoalieTemplateInfo.szTweaksFilename);

    cPlayer* pChar;
    if (!bForViewer)
    {
        Goalie* pGoalie = new (nlMalloc(sizeof(Goalie), 8, false)) Goalie(
            gcc, (const int*)g_GoalieTemplate, pHierarchy, g_GoalieTemplate->pAnimInventory, g_GoalieTemplate->pPhysicsData, pTweaks, pAnimRetargetList);
        pChar = pGoalie;
    }
    else
    {
        cPlayer* pPlayer = new (nlMalloc(sizeof(cPlayer), 8, false)) cPlayer(
            4, gcc, (const int*)g_GoalieTemplate, pHierarchy, g_GoalieTemplate->pAnimInventory, g_GoalieTemplate->pPhysicsData, (PlayerTweaks*)pTweaks, pAnimRetargetList, (eClassTypes)3);
        pChar = pPlayer;
    }

    pChar->m_szEffectsName = g_GoalieTemplateInfo.szEffectsName;
    pChar->m_uNormalTextureID = GetHashFromTextureFile(g_GoalieTemplateInfo.szTextureFilename);
    pChar->m_uSwapTextureID = GetHashFromTextureFile(g_GoalieTextureInfo[goalieIdx].szTextureFilename);

    if (!AudioLoader::gbDisableAudio)
    {
        pChar->SetSFX(g_GoalieTemplateInfo.pSFXPropAccessor);
    }

    return pChar;
}

static eCharacterClass GetGoalieFromCaptain(eCharacterClass captain)
{
    switch (captain)
    {
    case DAISY:
        return DAISY_GOALIE;
    case DONKEYKONG:
        return DONKEYKONG_GOALIE;
    case LUIGI:
        return LUIGI_GOALIE;
    case MARIO:
        return MARIO_GOALIE;
    case PEACH:
        return PEACH_GOALIE;
    case WALUIGI:
        return WALUIGI_GOALIE;
    case WARIO:
        return WARIO_GOALIE;
    case YOSHI:
        return YOSHI_GOALIE;
    case MYSTERY:
        return SUPERTEAM_GOALIE;
    default:
        return MARIO_GOALIE;
    }
}

static inline bool CaptainClassGreater(eCharacterClass first, eCharacterClass second)
{
    return first > second;
}

static inline bool SameCharacterClass(const eCharacterClass* first, const eCharacterClass* second, int index)
{
    return first[index] == second[index];
}

// ===========================================================================
// MOD (mixed teams): automatic kit recolouring.
//
// A sidekick has a kit painted for every captain, so Koopa can wear Mario red.
// A captain has only his own, because he never played for anyone else. Rather
// than paint 56 new images, this shifts the hue of the captain's own texture
// towards the team he is playing for: Luigi's green becomes Mario's red.
//
// Only strongly coloured pixels close to the character's own team hue move, so
// skin, eyes and white areas stay put. It works on the texture as the disc
// stores it, which means the recolour is pixel-for-pixel in place, with no
// re-compression and no loss.
// ===========================================================================

struct MixedTeamHue
{
    eCharacterClass cc;
    int hue; // degrees, 0-359
};

// The dominant kit hue of each captain: what to shift away from, and what to shift towards.
static const MixedTeamHue kMixedTeamHues[] = {
    { MARIO, 0 },      // red
    { LUIGI, 120 },    // green
    { PEACH, 320 },    // pink
    { DAISY, 30 },     // orange
    { YOSHI, 100 },    // green
    { DONKEYKONG, 15 },// red-brown
    { WARIO, 50 },     // yellow
    { WALUIGI, 275 },  // purple
};

static bool MixedTeamHueFor(eCharacterClass cc, int* outHue)
{
    for (unsigned int i = 0; i < sizeof(kMixedTeamHues) / sizeof(kMixedTeamHues[0]); ++i)
    {
        if (kMixedTeamHues[i].cc == cc)
        {
            *outHue = kMixedTeamHues[i].hue;
            return true;
        }
    }
    return false;
}

// How far from the source hue a pixel may sit and still count as "kit", and how
// colourful it must be. Raise the window to catch more, lower it to protect skin.
static int gMixedHueWindow = 45;
static int gMixedMinSat = 90;  // 0-255
static int gMixedMinVal = 40;  // 0-255

static void MixedRGBtoHSV(int r, int g, int b, int* h, int* s, int* v)
{
    int mx = r > g ? (r > b ? r : b) : (g > b ? g : b);
    int mn = r < g ? (r < b ? r : b) : (g < b ? g : b);
    int d = mx - mn;

    *v = mx;
    *s = (mx == 0) ? 0 : (d * 255) / mx;

    if (d == 0)
    {
        *h = 0;
        return;
    }

    int hue;
    if (mx == r)
    {
        hue = 60 * (g - b) / d;
    }
    else if (mx == g)
    {
        hue = 120 + 60 * (b - r) / d;
    }
    else
    {
        hue = 240 + 60 * (r - g) / d;
    }
    while (hue < 0)
    {
        hue += 360;
    }
    *h = hue % 360;
}

static void MixedHSVtoRGB(int h, int s, int v, int* r, int* g, int* b)
{
    if (s == 0)
    {
        *r = *g = *b = v;
        return;
    }

    h = ((h % 360) + 360) % 360;
    int region = h / 60;
    int rem = (h - region * 60) * 255 / 60;

    int p = (v * (255 - s)) / 255;
    int q = (v * (255 - (s * rem) / 255)) / 255;
    int t = (v * (255 - (s * (255 - rem)) / 255)) / 255;

    switch (region)
    {
    case 0:  *r = v; *g = t; *b = p; break;
    case 1:  *r = q; *g = v; *b = p; break;
    case 2:  *r = p; *g = v; *b = t; break;
    case 3:  *r = p; *g = q; *b = v; break;
    case 4:  *r = t; *g = p; *b = v; break;
    default: *r = v; *g = p; *b = q; break;
    }
}

// One pixel. Returns true if it was changed.
static bool MixedShiftPixel(int* r, int* g, int* b, int srcHue, int dstHue)
{
    int h, s, v;
    MixedRGBtoHSV(*r, *g, *b, &h, &s, &v);

    if (s < gMixedMinSat || v < gMixedMinVal)
    {
        return false;
    }

    int dist = h - srcHue;
    while (dist > 180) { dist -= 360; }
    while (dist < -180) { dist += 360; }
    if (dist > gMixedHueWindow || dist < -gMixedHueWindow)
    {
        return false;
    }

    // Keep the pixel's own variation around the team hue, so shading survives.
    MixedHSVtoRGB(dstHue + dist, s, v, r, g, b);
    return true;
}

static inline u16 MixedReadBE16(const u8* p)
{
    return (u16)((p[0] << 8) | p[1]);
}

static inline void MixedWriteBE16(u8* p, u16 v)
{
    p[0] = (u8)(v >> 8);
    p[1] = (u8)(v & 0xFF);
}

// 5:6:5, as CMPR endpoints and RGB565 textures store it.
static bool MixedShift565(u8* p, int srcHue, int dstHue)
{
    u16 c = MixedReadBE16(p);
    int r = ((c >> 11) & 0x1F) * 255 / 31;
    int g = ((c >> 5) & 0x3F) * 255 / 63;
    int b = (c & 0x1F) * 255 / 31;

    if (!MixedShiftPixel(&r, &g, &b, srcHue, dstHue))
    {
        return false;
    }

    u16 out = (u16)(((r * 31 / 255) << 11) | ((g * 63 / 255) << 5) | (b * 31 / 255));
    MixedWriteBE16(p, out);
    return true;
}

// RGB5A3: top bit set means opaque 5:5:5, clear means 3:4:4:4 with alpha.
static void MixedShift5A3(u8* p, int srcHue, int dstHue)
{
    u16 c = MixedReadBE16(p);
    int r, g, b;

    if (c & 0x8000)
    {
        r = ((c >> 10) & 0x1F) * 255 / 31;
        g = ((c >> 5) & 0x1F) * 255 / 31;
        b = (c & 0x1F) * 255 / 31;
        if (MixedShiftPixel(&r, &g, &b, srcHue, dstHue))
        {
            MixedWriteBE16(p, (u16)(0x8000 | ((r * 31 / 255) << 10) | ((g * 31 / 255) << 5) | (b * 31 / 255)));
        }
    }
    else
    {
        int a = (c >> 12) & 0x7;
        r = ((c >> 8) & 0xF) * 255 / 15;
        g = ((c >> 4) & 0xF) * 255 / 15;
        b = (c & 0xF) * 255 / 15;
        if (MixedShiftPixel(&r, &g, &b, srcHue, dstHue))
        {
            MixedWriteBE16(p, (u16)((a << 12) | ((r * 15 / 255) << 8) | ((g * 15 / 255) << 4) | (b * 15 / 255)));
        }
    }
}

// Walk a whole texture. The GameCube stores pixels in tiles, but a colour does not
// care where it sits, so tiling can be ignored for everything except RGBA8, whose
// channels are split across a tile.
static void MixedShiftTexture(u8* data, u32 sizeBytes, eGXTextureFormat format, int srcHue, int dstHue)
{
    switch (format)
    {
    case GXTex_CMPR:
    {
        // Eight bytes per block: two 5:6:5 endpoints then packed indices. Only the
        // endpoints move. Their order decides whether the block has transparency, so
        // a block whose order would flip is left alone rather than risk holes.
        for (u32 off = 0; off + 8 <= sizeBytes; off += 8)
        {
            u8* blk = data + off;
            u16 c0 = MixedReadBE16(blk);
            u16 c1 = MixedReadBE16(blk + 2);
            bool wasGreater = (c0 > c1);

            u8 saved[4];
            saved[0] = blk[0]; saved[1] = blk[1]; saved[2] = blk[2]; saved[3] = blk[3];

            bool a = MixedShift565(blk, srcHue, dstHue);
            bool b = MixedShift565(blk + 2, srcHue, dstHue);

            if (a || b)
            {
                u16 n0 = MixedReadBE16(blk);
                u16 n1 = MixedReadBE16(blk + 2);
                if ((n0 > n1) != wasGreater)
                {
                    blk[0] = saved[0]; blk[1] = saved[1]; blk[2] = saved[2]; blk[3] = saved[3];
                }
            }
        }
        break;
    }
    case GXTex_RGB565:
        for (u32 off = 0; off + 2 <= sizeBytes; off += 2)
        {
            MixedShift565(data + off, srcHue, dstHue);
        }
        break;
    case GXTex_RGB5A3:
        for (u32 off = 0; off + 2 <= sizeBytes; off += 2)
        {
            MixedShift5A3(data + off, srcHue, dstHue);
        }
        break;
    case GXTex_RGBA8:
    {
        // 64-byte tile: sixteen alpha/red pairs, then sixteen green/blue pairs.
        for (u32 tile = 0; tile + 64 <= sizeBytes; tile += 64)
        {
            u8* t = data + tile;
            for (int i = 0; i < 16; ++i)
            {
                int r = t[i * 2 + 1];
                int g = t[32 + i * 2];
                int b = t[32 + i * 2 + 1];
                if (MixedShiftPixel(&r, &g, &b, srcHue, dstHue))
                {
                    t[i * 2 + 1] = (u8)r;
                    t[32 + i * 2] = (u8)g;
                    t[32 + i * 2 + 1] = (u8)b;
                }
            }
        }
        break;
    }
    default:
        // I4, I8, A8, IA8 carry no colour of their own.
        break;
    }
}

// Build a recoloured copy of a loaded texture and register it under a new name.
// Returns the new handle, or -1 if the source is not loaded.
static u32 MixedMakeRecolouredTexture(u32 srcHandle, const char* newName, int srcHue, int dstHue)
{
    PlatTexture* pSrc = glx_GetTex(srcHandle, false, false);
    if (pSrc == NULL || pSrc->m_SwizzledData == NULL)
    {
        return (u32)-1;
    }

    u32 newHandle = glGetTexture(newName);
    if (glx_GetTex(newHandle, false, false) != NULL)
    {
        return newHandle; // already built earlier this match
    }

    PlatTexture* pDst = glx_CreatePlatTexture();
    if (pDst == NULL)
    {
        return (u32)-1;
    }

    u32 dataSize = GCTextureSize(pSrc->m_Format, pSrc->m_Width, pSrc->m_Height, pSrc->m_Levels, (unsigned long)-1);

    pDst->m_Width = pSrc->m_Width;
    pDst->m_Height = pSrc->m_Height;
    pDst->m_Levels = pSrc->m_Levels;
    pDst->m_MaxLevel = pSrc->m_MaxLevel;
    pDst->m_Format = pSrc->m_Format;
    pDst->m_bMissingTexture = pSrc->m_bMissingTexture;
    memcpy(pDst->m_Bits, pSrc->m_Bits, sizeof(pDst->m_Bits));

    pDst->m_SwizzledData = glResourceAlloc(dataSize, GLM_TextureData);
    if (pDst->m_SwizzledData == NULL)
    {
        return (u32)-1;
    }
    memcpy(pDst->m_SwizzledData, pSrc->m_SwizzledData, dataSize);
    pDst->m_LinearData = NULL;

    if (pSrc->m_nPaletteEntries > 0 && pSrc->m_PaletteData != NULL)
    {
        // A paletted texture is recoloured by recolouring its palette: a few hundred
        // bytes instead of the whole image.
        pDst->m_PaletteData = (u16*)glResourceAlloc(pSrc->m_nPaletteEntries * 2, GLM_TextureData);
        if (pDst->m_PaletteData == NULL)
        {
            return (u32)-1;
        }
        memcpy(pDst->m_PaletteData, pSrc->m_PaletteData, pSrc->m_nPaletteEntries * 2);
        pDst->m_nPaletteEntries = pSrc->m_nPaletteEntries;

        u8* pal = (u8*)pDst->m_PaletteData;
        for (int i = 0; i < pSrc->m_nPaletteEntries; ++i)
        {
            MixedShift5A3(pal + i * 2, srcHue, dstHue);
        }
    }
    else
    {
        MixedShiftTexture((u8*)pDst->m_SwizzledData, dataSize, pDst->m_Format, srcHue, dstHue);
    }

    pDst->Prepare();

    if (!glx_AddTex(newHandle, pDst))
    {
        return (u32)-1;
    }

    OSReport("[mixed teams] recoloured %s (%ux%u, format %d, hue %d -> %d)\n",
             newName, (unsigned)pDst->m_Width, (unsigned)pDst->m_Height, (int)pDst->m_Format, srcHue, dstHue);
    return newHandle;
}

// Put a captain standing in a sidekick slot into his team's colours.
static void MixedApplyCaptainKit(cPlayer* pChar, eCharacterClass slotcc, eCharacterClass captaincc)
{
    int srcHue, dstHue;
    if (!MixedTeamHueFor(slotcc, &srcHue) || !MixedTeamHueFor(captaincc, &dstHue))
    {
        return;
    }
    if (srcHue == dstHue)
    {
        return;
    }

    // The texture a captain's model draws with. The first name that is actually
    // loaded wins; the report says which, so an odd character can be chased down.
    char szTry[64];
    const char* name = GetCharacterName(slotcc);
    u32 srcHandle = (u32)-1;

    nlSNPrintf(szTry, 64, "%s/%s", name, name);
    if (glx_GetTex(glGetTexture(szTry), false, false) != NULL)
    {
        srcHandle = glGetTexture(szTry);
    }
    else
    {
        nlSNPrintf(szTry, 64, "%s/%s_%s", name, name, name);
        if (glx_GetTex(glGetTexture(szTry), false, false) != NULL)
        {
            srcHandle = glGetTexture(szTry);
        }
    }

    if (srcHandle == (u32)-1)
    {
        OSReport("[mixed teams] no base texture found for %s; keeping his own colours\n", name);
        return;
    }

    char szNew[64];
    nlSNPrintf(szNew, 64, "%s_auto_%s", name, GetCharacterName(captaincc));

    u32 newHandle = MixedMakeRecolouredTexture(srcHandle, szNew, srcHue, dstHue);
    if (newHandle == (u32)-1)
    {
        OSReport("[mixed teams] could not recolour %s; keeping his own colours\n", name);
        return;
    }

    pChar->m_uNormalTextureID = srcHandle;
    pChar->m_uSwapTextureID = newHandle;
}

// ---------------------------------------------------------------------------
// MOD (mixed teams): team-colour sheen.
//
// The second approach to captains without kits: leave their colours alone and
// draw a soft wash of the team colour over the whole model, using the same
// overlay layer the game already uses for ice, fire and the star glow. The
// texture is a small flat colour built in memory; nothing is read from disc.
// ---------------------------------------------------------------------------

struct MixedSheenRGB
{
    eCharacterClass cc;
    u8 r, g, b;
};

static const MixedSheenRGB kMixedSheenColours[] = {
    { MARIO, 230, 40, 40 },
    { LUIGI, 50, 200, 60 },
    { PEACH, 240, 130, 180 },
    { DAISY, 245, 160, 40 },
    { YOSHI, 110, 220, 70 },
    { DONKEYKONG, 200, 80, 40 },
    { WARIO, 235, 210, 50 },
    { WALUIGI, 140, 60, 200 },
};

// How strongly the wash reads, 0-255. It scales the colour itself, because the
// overlay is additive: darker colour, fainter sheen.
static int gMixedSheenStrength = 130;

// Which characters carry a sheen this match, and the overlay entry each uses.
static const cCharacter* gMixedSheenChar[10];
static EffectsTexturing gMixedSheenFx[10];

static int gMixedOutline = 0; // 0-100, the slider; 0 is off
static const cCharacter* gMixedOutlineChar[10];
static u32 gMixedOutlineTex[10];

static void MixedSheenReset()
{
    for (int i = 0; i < 10; ++i)
    {
        gMixedSheenChar[i] = NULL;
    }
    for (int i = 0; i < 10; ++i)
    {
        gMixedOutlineChar[i] = NULL;
    }
}

// The per-frame lookup, called from the drawing code when a character has no
// active effect overlay. Not static: DrawableCharacter.cpp reaches it.
EffectsTexturing* MixedTeamSheenFor(const cCharacter* pChar)
{
    for (int i = 0; i < 10; ++i)
    {
        if (gMixedSheenChar[i] == pChar)
        {
            return &gMixedSheenFx[i];
        }
    }
    return NULL;
}

// An 8x8 image of one flat colour. Layered over the character the way the star
// power-up glow is, it tints him without replacing his own skin.
static u32 MixedMakeGlowTexture(const char* name, u8 r, u8 g, u8 b)
{
    u32 handle = glGetTexture(name);
    if (glx_GetTex(handle, false, false) != NULL)
    {
        return handle;
    }

    PlatTexture* pTex = glx_CreatePlatTexture();
    if (pTex == NULL)
    {
        return (u32)-1;
    }

    pTex->Create(8, 8, GXTex_RGB5A3, 1, false, false);
    if (pTex->m_SwizzledData == NULL)
    {
        return (u32)-1;
    }

    u16 texel = (u16)(0x8000 | ((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3));
    u8* data = (u8*)pTex->m_SwizzledData;
    for (int i = 0; i < 64; ++i)
    {
        MixedWriteBE16(data + i * 2, texel);
    }

    pTex->Prepare();
    if (!glx_AddTex(handle, pTex))
    {
        return (u32)-1;
    }
    return handle;
}

static void MixedApplySheen(cCharacter* pChar, eCharacterClass captaincc)
{
    const MixedSheenRGB* pColour = NULL;
    for (unsigned int i = 0; i < sizeof(kMixedSheenColours) / sizeof(kMixedSheenColours[0]); ++i)
    {
        if (kMixedSheenColours[i].cc == captaincc)
        {
            pColour = &kMixedSheenColours[i];
            break;
        }
    }
    if (pColour == NULL || pChar == NULL)
    {
        return;
    }

    int slot = -1;
    for (int i = 0; i < 10; ++i)
    {
        if (gMixedSheenChar[i] == NULL)
        {
            slot = i;
            break;
        }
    }
    if (slot < 0)
    {
        return;
    }

    int strength = gMixedSheenStrength;
    if (strength < 0) { strength = 0; }
    if (strength > 255) { strength = 255; }

    char szName[64];
    nlSNPrintf(szName, 64, "auto_glow_%s", GetCharacterName(captaincc));

    u32 texHandle = MixedMakeGlowTexture(szName,
                                          (u8)(pColour->r * strength / 255),
                                          (u8)(pColour->g * strength / 255),
                                          (u8)(pColour->b * strength / 255));
    if (texHandle == (u32)-1)
    {
        OSReport("[mixed teams] could not build sheen texture for %s\n", GetCharacterName(captaincc));
        return;
    }

    gMixedSheenFx[slot].m_uTexture = texHandle;
    gMixedSheenFx[slot].m_eBlendMode = GLB_None;   // the star glow settings: layered on top,
    gMixedSheenFx[slot].m_bEnviro = false;         // not replacing the skin, so the model stays
    gMixedSheenFx[slot].m_bDetail = true;          // solid and fully himself
    gMixedSheenChar[slot] = pChar;

    OSReport("[mixed teams] sheen on %s in %s colours (strength %d)\n",
             GetCharacterName(pChar->m_eCharacterClass), GetCharacterName(captaincc), strength);
}

// ---------------------------------------------------------------------------
// MOD (mixed teams): true outline.
//
// The character is drawn a second time, inflated a few percent around his own
// centre, in flat team colour, back faces only. The real model covers all of it
// except a thin rim past his edges: a drawn outline that follows the pose.
// The slider (0-100) sets how far the shell sticks out; 0 turns it off.
// ---------------------------------------------------------------------------

// The per-frame lookup, called from the drawing code. Not static:
// DrawableCharacter.cpp reaches it.
int gMixedOutlineCull = 1; // 0 none, 1 front, 2 back: which faces of the shell to hide

bool MixedOutlineFor(const cCharacter* pChar, unsigned long* pTex, float* pScale)
{
    static int nPtrHits = 0;
    static int nClassHits = 0;
    static int nMisses = 0;

    if (gMixedOutline <= 0 || pChar == NULL)
    {
        return false;
    }
    for (int i = 0; i < 10; ++i)
    {
        if (gMixedOutlineChar[i] == pChar)
        {
            if (nPtrHits++ < 3)
            {
                OSReport("[mixed teams] draw: outline matched directly (%d)\n", nPtrHits);
            }
            *pTex = gMixedOutlineTex[i];
            *pScale = 1.0f + (float)gMixedOutline * 0.0006f; // 100 -> 6% bigger
            return true;
        }
    }
    // The renderer may draw from a copied snapshot of the character rather than
    // the live object, in which case the address differs. Fall back to matching
    // by who the character is.
    for (int i = 0; i < 10; ++i)
    {
        if (gMixedOutlineChar[i] != NULL
            && gMixedOutlineChar[i]->m_eCharacterClass == pChar->m_eCharacterClass)
        {
            if (nClassHits++ < 3)
            {
                OSReport("[mixed teams] draw: outline matched by identity, not address (%d)\n", nClassHits);
            }
            *pTex = gMixedOutlineTex[i];
            *pScale = 1.0f + (float)gMixedOutline * 0.0006f;
            return true;
        }
    }
    if (nMisses++ < 3)
    {
        OSReport("[mixed teams] draw: character %d has no outline entry (%d)\n", (int)pChar->m_eCharacterClass, nMisses);
    }
    return false;
}

static void MixedApplyOutline(cCharacter* pChar, eCharacterClass captaincc)
{
    const MixedSheenRGB* pColour = NULL;
    for (unsigned int i = 0; i < sizeof(kMixedSheenColours) / sizeof(kMixedSheenColours[0]); ++i)
    {
        if (kMixedSheenColours[i].cc == captaincc)
        {
            pColour = &kMixedSheenColours[i];
            break;
        }
    }
    if (pColour == NULL || pChar == NULL)
    {
        return;
    }

    int slot = -1;
    for (int i = 0; i < 10; ++i)
    {
        if (gMixedOutlineChar[i] == NULL)
        {
            slot = i;
            break;
        }
    }
    if (slot < 0)
    {
        return;
    }

    char szName[64];
    nlSNPrintf(szName, 64, "auto_outline_%s", GetCharacterName(captaincc));
    u32 tex = MixedMakeGlowTexture(szName, pColour->r, pColour->g, pColour->b);
    if (tex == (u32)-1)
    {
        OSReport("[mixed teams] could not build outline texture for %s\n", GetCharacterName(captaincc));
        return;
    }

    gMixedOutlineTex[slot] = tex;
    gMixedOutlineChar[slot] = pChar;
    OSReport("[mixed teams] outline on %s in %s colours (size %d)\n",
             GetCharacterName(pChar->m_eCharacterClass), GetCharacterName(captaincc), gMixedOutline);
}

// MOD (mixed teams): with `mixed_teams` on, each of a team's three sidekick slots may hold its own
// character. The keys are team1_slot2, team1_slot3, team1_slot4 and team2_slot2..team2_slot4, and a
// value is any character name the game already knows: a sidekick ("toad", "koopa", "hammerbro",
// "birdo") or a captain ("mario", "luigi", "peach", "daisy", "yoshi", "donkeykong", "wario",
// "waluigi"). A slot that is unset or misspelt falls back to the team's normal sidekick.
static eCharacterClass MixedTeamSlotClass(const char* key, eCharacterClass fallback)
{
    Config& cfg = Config::Global();
    if (!cfg.Exists(key))
    {
        return fallback;
    }

    BasicString<char, Detail::TempStringAllocator> name
        = cfg.Get<BasicString<char, Detail::TempStringAllocator> >(key, BasicString<char, Detail::TempStringAllocator>(""));

    eSidekickID sk = ConvertToSidekickID(name.c_str());
    if (sk != SK_INVALID)
    {
        return ConvertToCharacterClass(sk);
    }

    eTeamID team = ConvertToTeamID(name.c_str());
    if (team != TEAM_INVALID && team != TEAM_MYSTERY)
    {
        return ConvertToCharacterClass(team);
    }

    OSReport("[mixed teams] %s=%s is not a character name; using the team's sidekick\n", key, name.c_str());
    return fallback;
}

/**
 * Offset/Address/Size: 0x954 | 0x80012C3C | size: 0x51C
 */
void CreateCharacters()
{
    eCharacterClass captain[2];
    eCharacterClass sidekick[2];
    eCharacterClass goalie[2];
    captain[0] = ConvertToCharacterClass(nlSingleton<GameInfoManager>::Instance()->GetTeam(0));
    captain[1] = ConvertToCharacterClass(nlSingleton<GameInfoManager>::Instance()->GetTeam(1));
    sidekick[0] = ConvertToCharacterClass(nlSingleton<GameInfoManager>::Instance()->GetSidekick(0));
    sidekick[1] = ConvertToCharacterClass(nlSingleton<GameInfoManager>::Instance()->GetSidekick(1));

    goalie[0] = GetGoalieFromCaptain(captain[0]);
    goalie[1] = GetGoalieFromCaptain(captain[1]);

    Config& cfg = Config::Global();
    bool allcaptains = cfg.Get<bool>("allcaptains", false);
    if (allcaptains)
    {
        sidekick[0] = captain[0];
        sidekick[1] = captain[1];
    }

    // MOD (mixed teams): the toggle. Off, and the game builds teams exactly as it always did.
    bool mixedTeams = GetConfigBool(cfg, "mixed_teams", false);
    bool mixedRecolour = GetConfigBool(cfg, "mixed_recolour", true);
    bool mixedSheen = GetConfigBool(cfg, "mixed_sheen", false);
    MixedSheenReset(); // always: stale pointers from a previous match must never survive
    if (mixedTeams)
    {
        // The knobs are here so a bad-looking character can be tuned without a rebuild.
        gMixedHueWindow = GetConfigInt(cfg, "mixed_hue_window", 45);
        gMixedMinSat = GetConfigInt(cfg, "mixed_min_saturation", 90);
        gMixedMinVal = GetConfigInt(cfg, "mixed_min_brightness", 40);
        gMixedSheenStrength = GetConfigInt(cfg, "mixed_sheen_strength", 130);
        gMixedOutline = GetConfigInt(cfg, "mixed_outline", 0);
        if (gMixedOutline > 100) { gMixedOutline = 100; }
        BasicString<char, Detail::TempStringAllocator> cullName
            = cfg.Get<BasicString<char, Detail::TempStringAllocator> >("mixed_outline_cull", BasicString<char, Detail::TempStringAllocator>("front"));
        gMixedOutlineCull = 1;
        if (nlStrCmp<char>(cullName.c_str(), "none") == 0) { gMixedOutlineCull = 0; }
        if (nlStrCmp<char>(cullName.c_str(), "back") == 0) { gMixedOutlineCull = 2; }
        if (gMixedOutline > 0)
        {
            OSReport("[mixed teams] outline size %d, cull %s\n", gMixedOutline, cullName.c_str());
        }
        OSReport("[mixed teams] on: each sidekick slot may hold its own character (recolour %s, sheen %s)\n",
                 mixedRecolour ? "on" : "off", mixedSheen ? "on" : "off");
    }

    if (captain[0] == MYSTERY)
    {
        sidekick[0] = MYSTERY;
    }
    else if (captain[1] == MYSTERY)
    {
        sidekick[1] = MYSTERY;
    }

    nlVector3 pos[8] = {
        { 1.5f, 1.5f, 0.0f },
        { 1.5f, -1.5f, 0.0f },
        { 1.5f, 0.0f, 0.0f },
        { 1.5f, 2.5f, 0.0f },
        { -1.5f, 1.5f, 0.0f },
        { -1.5f, -1.5f, 0.0f },
        { -1.5f, 0.0f, 0.0f },
        { -1.5f, 2.5f, 0.0f },
    };

    nlVector3 goaliepos[2] = {
        { 18.0f, 0.0f, 0.0f },
        { -18.0f, 0.0f, 0.0f },
    };

    int plrindex;
    int charIdx;

    SebringAnimTagScriptInterpreter* pInterp = new (nlMalloc(sizeof(SebringAnimTagScriptInterpreter), 8, false)) SebringAnimTagScriptInterpreter();

    g_pAnimScriptInterp = pInterp;

    for (int teami = 0; teami < 2; teami++)
    {
        plrindex = CaptainClassGreater(captain[0], captain[1]) ? !teami : teami;

        int idx = plrindex * 4;
        g_pCharacters[idx] = CreateCharacter(0, plrindex, captain[plrindex], false);
        g_pCharacters[idx]->SetPosition(pos[idx]);
        ((Audio::cCharacterSFX*)g_pCharacters[idx]->m_pCharacterSFX)->mGroup = idx;

        g_pTeams[plrindex]->SetPlayer((cPlayer*)g_pCharacters[idx], 0);
        ((cPlayer*)g_pCharacters[idx])->m_pTeam = g_pTeams[plrindex];

        g_pCharacters[plrindex + 8] = CreateGoalie(goalie[plrindex], false);
        g_pCharacters[plrindex + 8]->SetPosition(goaliepos[plrindex]);

        g_pTeams[plrindex]->SetGoalie((Goalie*)g_pCharacters[plrindex + 8]);
        ((cPlayer*)g_pCharacters[plrindex + 8])->m_pTeam = g_pTeams[plrindex];
    }

    for (int teami = 0; teami < 2; teami++)
    {
        plrindex = (sidekick[0] > sidekick[1]) ? !teami : teami;

        charIdx = plrindex * 4 + 1;

        for (int index = 1; index < 4; index++)
        {
            // MOD (mixed teams): what goes in this slot. Normally the team's one sidekick.
            eCharacterClass slotcc = sidekick[plrindex];
            if (mixedTeams && captain[plrindex] != MYSTERY)
            {
                char szKey[32];
                nlSNPrintf(szKey, 32, "team%d_slot%d", plrindex + 1, index + 1);
                slotcc = MixedTeamSlotClass(szKey, sidekick[plrindex]);
            }

            if (slotcc == captain[plrindex])
            {
                g_pCharacters[charIdx] = CreateCharacter(index, plrindex, captain[plrindex], false);
            }
            else if (IsCaptain(slotcc))
            {
                // A captain playing as a sidekick: built the same way the captain is. No painted kit
                // exists for him, so with `mixed_recolour` on his own texture is hue-shifted into the
                // team's colours instead.
                g_pCharacters[charIdx] = CreateCharacter(index, plrindex, slotcc, false);
                if (mixedRecolour)
                {
                    MixedApplyCaptainKit((cPlayer*)g_pCharacters[charIdx], slotcc, captain[plrindex]);
                }
                if (mixedSheen)
                {
                    MixedApplySheen(g_pCharacters[charIdx], captain[plrindex]);
                }
                if (gMixedOutline > 0)
                {
                    MixedApplyOutline(g_pCharacters[charIdx], captain[plrindex]);
                }
            }
            else
            {
                g_pCharacters[charIdx] = (cCharacter*)CreateSidekick(index, plrindex, slotcc, captain[plrindex], false);
            }

            g_pCharacters[charIdx]->SetPosition(pos[charIdx]);
            ((Audio::cCharacterSFX*)g_pCharacters[charIdx]->m_pCharacterSFX)->mGroup = charIdx;

            g_pTeams[plrindex]->SetPlayer((cPlayer*)g_pCharacters[charIdx], index);
            ((cPlayer*)g_pCharacters[charIdx])->m_pTeam = g_pTeams[plrindex];

            charIdx++;
        }

        g_pTeams[plrindex]->UpdateControllers();
    }
}

/**
 * Offset/Address/Size: 0x294 | 0x8001257C | size: 0x6C0
 */
void DestroyCharacters()
{
    int i;

    delete g_pAnimScriptInterp;
    g_pAnimScriptInterp = NULL;

    for (i = 0; i < 10; i++)
    {
        delete g_pCharacters[i];
        g_pCharacters[i] = NULL;
    }

    for (i = 0; i < 13; i++)
    {
        if (g_aCharacterTemplates[i] != NULL)
        {
            delete g_aCharacterTemplates[i]->pHierarchyInventory;

            if (!g_aCharacterTemplates[i]->bAnimInventoryCopy)
            {
                delete g_aCharacterTemplates[i]->pAnimInventory;
            }

            delete g_aCharacterTemplates[i]->pPhysicsData;
            if (g_aCharacterTemplates[i]->pAnimRetargetListInventory != NULL)
            {
                delete g_aCharacterTemplates[i]->pAnimRetargetListInventory;
            }
            delete g_aCharacterTemplates[i];
            g_aCharacterTemplates[i] = NULL;
        }
    }

    if (g_GoalieTemplate != NULL)
    {
        delete g_GoalieTemplate->pHierarchyInventory;

        if (!g_GoalieTemplate->bAnimInventoryCopy)
        {
            delete g_GoalieTemplate->pAnimInventory;
        }

        delete g_GoalieTemplate->pPhysicsData;
        if (g_GoalieTemplate->pAnimRetargetListInventory != NULL)
        {
            delete g_GoalieTemplate->pAnimRetargetListInventory;
        }
        delete g_GoalieTemplate;
        g_GoalieTemplate = NULL;
    }

    g_GoalieTextureInfo[0].bLoaded = 0;
    g_GoalieTextureInfo[1].bLoaded = 0;
    g_GoalieTextureInfo[2].bLoaded = 0;
    g_GoalieTextureInfo[3].bLoaded = 0;
    g_GoalieTextureInfo[4].bLoaded = 0;
    g_GoalieTextureInfo[5].bLoaded = 0;
    g_GoalieTextureInfo[6].bLoaded = 0;
    g_GoalieTextureInfo[7].bLoaded = 0;
    g_GoalieTextureInfo[8].bLoaded = 0;

    SlotPoolBase::BaseFreeBlocks(&AnimTriggerCallbackInfo::m_AnimTriggerCallbackInfoSlotPool, sizeof(AnimTriggerCallbackInfo));
    SlotPoolBase::BaseFreeBlocks(&ScriptAction::m_ScriptActionSlotPool, sizeof(ScriptAction));
}

/**
 * Offset/Address/Size: 0x1C0 | 0x800124A8 | size: 0xD4
 */
s32 GetCharacterIndex(const cCharacter* character)
{
    cCharacter** ptr = g_pCharacters;
    for (s32 i = 0; i < 10; ++i, ptr++)
    {
        if (*ptr == character)
            return i;
    }
    return -1;
}

/**
 * Offset/Address/Size: 0x0 | 0x800122E8 | size: 0x1C0
 */
s32 GetGoalieIndex(int side)
{
    if (side == 0)
    {
        cCharacter** ptr = g_pCharacters;
        for (s32 i = 0; i < 10; ++i, ptr++)
        {
            if (*ptr == g_pCharacters[8])
                return i;
        }
        return -1;
    }

    cCharacter** ptr = g_pCharacters;
    for (s32 i = 0; i < 10; ++i, ptr++)
    {
        if (*ptr == g_pCharacters[9])
            return i;
    }
    return -1;
}
