# Story checkpoints in the dev version: notes per checkpoint

Notes written while redoing `story_presets.lua` for the dev version (master 411e5913), giving `story_presets_dev.lua`. Paths and line numbers are in the dev source unless they say v3.2.3. Money shifts carried between checkpoints were applied when combining: +720 from C06 on (C03 and C05 payout changes) and -9720 from C10 on (six fewer forced battles in the Goldenrod Underground); C11-C13 also include Veteran Matt (+2960) and C12 Schoolboy Sherman (on foot back from Cinnabar).

## C01_STARTER: dev changes (dev 411e5913 vs v3.2.3)

### Story / flag changes
- **InitialEvents renames** (data/events/initialize_events.asm). Four new-game flags were renamed. They are set the same way, so they are replaced one for one in `events_set`:
  - EVENT_RIVAL_UNDERGROUND_PATH -> EVENT_RIVAL_GOLDENROD_UNDERGROUND (:25)
  - EVENT_WAREHOUSE_LAYOUT_1 -> EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_1 (:82)
  - EVENT_WAREHOUSE_BLOCKED_OFF -> EVENT_GOLDENROD_WAREHOUSE_BLOCKED_OFF (:83)
  - EVENT_SHAMOUTI_ISLAND_PIKABLU_GUY -> EVENT_SHAMOUTI_ISLAND_WILHOMENA (:145)
  - Commits 91cb920c/cf08098b (Goldenrod Underground renames) and c12270fa (Wilhomena).
  - C10 must use the new names when it clears/sets the warehouse flags.
- **InitialEvents additions**, both added to `events_set`:
  - EVENT_BETA_IN_NAVEL_ROCK (:178), from 9b77ef6c, the fourth player choice.
  - EVENT_BURNED_TOWER_FIREBREATHER_DICK_ASHES (:179), from cb3c15c7. C05 clears it again when Firebreather Dick's ashes appear in Burned Tower 1F.
- **Player choice**: dev adds PLAYER_BETA = 3 (constants/ram_constants.asm:209-212).
  - Female is still PLAYER_FEMALE = 1 and is still the default (engine/menus/intro_menu.asm:174-175).
  - No C01 script branches on the new value.
- **Scene constants** (6b0ccd59): dev names every scene (scene_script/scene_const in each map header, numbered from 0).
  - All C01 maps keep the same order, so the recorded numbers are unchanged:
    - ELMS_LAB 2 = SCENE_ELMSLAB_NOOP
    - NEW_BARK_TOWN 2 = SCENE_NEWBARKTOWN_NOOP
    - PLAYERS_HOUSE_1F 1 = SCENE_PLAYERSHOUSE1F_NOOP
    - CHERRYGROVE_CITY 2 = SCENE_CHERRYGROVECITY_NOOP
    - MR_POKEMONS_HOUSE 1 = SCENE_MRPOKEMONSHOUSE_NOOP
    - ROUTE_29 1 = SCENE_ROUTE29_CATCH_TUTORIAL
- **Nothing else on the path changed story-wise**:
  - ElmsLab.asm (+115 -109): scene renames, `DoNothingScript` scenes, local labels, `scalltable` for Elm's jumps, the new line ElmAfterTheftText7 (ElmsLab.asm:395), and the aide's Potion as `verbosegiveitem_unsafe` (:673). No flag, item or scene was added or removed.
  - New Bark (coord events of Lyra's *final* trigger moved from x=17 to x=19, NewBarkTown.asm:21-24; that trigger is not armed in C01) and Mr. Pokemon's house (scene names only): no flag change.
  - Cherrygrove's guide-gent walk (movement only) and Route 29/30 (Route 30 is 2 tiles wider, has a second cut tree EVENT_ROUTE_30_CUT_TREE_2 off the path, and gets a palette-swap callback): no flag change.
  - Elm's phone call (engine/phone/scripts/elm.asm, unchanged) and Route 31: no flag change.
- **Checked unchanged**:
  - RIVAL0 2 (data/trainers/parties.asm:1522-1524, RATTATA 4 / CYNDAQUIL 5) and LYRA1_3 (:2034-2035, TOTODILE 5), so money and party_hint are unchanged.
  - `at` ELMS_LAB (4,10) is still floor, one tile above the entrance warps (4,11)/(5,11).

### Source-line-only changes
- Wrong draft sources were fixed:
  - ELMS_LAB scene -> ElmsLab.asm:390. The draft pointed at the `setmapscene ROUTE_29` line.
  - CHIKORITA -> ElmsLab.asm:299 (`givepoke`). The draft pointed at `cry CHIKORITA`.
  - Init scene lines are now exact: GOLDENROD_CITY :196, BATTLE_TOWER_OUTSIDE :197, BELLCHIME_TRAIL :198.
- Every other src was checked with a diff-based line map (v3.2.3 -> dev); it is the dev line that makes the change.
- Unsure lines I touched now quote dev lines, and the rest are flagged as v3.2.3 line numbers.

## C02_ZEPHYR: dev changes (dev 411e5913 vs v3.2.3)

### Story / flag changes
None found. The C02 lists are unchanged.

Checked:
- **Route 29**: tutorial coords (53,8)/(53,9) at SCENE_ROUTE29_CATCH_TUTORIAL = 1 (maps/Route29.asm:13-14), still unavoidable.
  - The 5 Poke Balls are now `verbosegiveitems_unsafe POKE_BALL, 5` (:94), same effect.
  - setscene SCENE_ROUTE29_NOOP (:100), EVENT_LEARNED_TO_CATCH_POKEMON (:101).
- **Route 30** is 2 tiles wider and has train tracks (836bf009, fb2f4c27).
  - The old cut tree became EVENT_ROUTE_30_CUT_TREE_1 at (10,6), and there is a new EVENT_ROUTE_30_CUT_TREE_2 at (3,29) (maps/Route30.asm:31-32).
  - Both are off the main path. Joey's battle objects are still hidden by EVENT_ROUTE_30_BATTLE.
  - Mikey (7,23) is still the only forced trainer (generictrainer :192), re-checked on the dev .ablk.
- **Route 31**: Mom's worried call (Route31CheckMomCall :33-40, engine/phone/scripts/mom.asm unchanged) and Finch's intro (trainer 0,0, :43, still forced) are unchanged.
- **Sprout Tower**:
  - 1F/3F have only palette and scene renames: SCENE_SPROUTTOWER3F_NOOP = 1 (maps/SproutTower3F.asm:63).
  - Chow, Jin and Neal are still forced, and the 3F rival coord (9,9) is still unavoidable (dev .ablk re-check).
  - Elder Li's TM_FLASH / EVENT_GOT_TM70_FLASH / EVENT_BEAT_ELDER_LI are unchanged (:79-81).
- **Dark Cave Violet Entrance**: the layout changed (.ablk) but the walk from (3,15) to the Falkner coord (6,2) still needs no HM.
  - Script unchanged: clearevent EVENT_VIOLET_GYM_FALKNER (:56), setmapscene VIOLET_GYM = SCENE_VIOLETGYM_NOOP 1 (:57), setscene SCENE_DARKCAVEVIOLETENTRANCE_NOOP 1 (:58).
- **Violet Gym** was redesigned (3b274400, 2 rows taller) and the gym guy / Falkner / trainers moved.
  - Falkner's script is unchanged: EVENT_BEAT_FALKNER :54, ZEPHYRBADGE :56, Rod/Abe :60-61, SPECIALCALL_ASSISTANT :63, TM_ROOST :66, EVENT_GOT_TM31_ROOST :67.
  - Rod and Abe are forced in the new layout, as they were in 3.2.3. Falkner sets both flags, and they stay out of the money estimate as before.
- **Elm's aide call** (engine/phone/scripts/elm.asm:280-281, unchanged).
- **Other checks**:
  - FALKNER 1 (data/trainers/parties.asm:105-114) keeps NATU 10 / HOOTHOOT 11 / PIDGEOTTO 13; only abilities and genders were added. No party_hint shift.
  - `at` VIOLET_POKECENTER_1F (5,6) is still floor above warps (5,7)/(6,7).

### Source-line-only changes
- DARK_CAVE_VIOLET_ENTRANCE scene src -> maps/DarkCaveVioletEntrance.asm:58 (`setscene`). The draft pointed at the VIOLET_GYM `setmapscene` line :57.
- Every other src matches the diff-based v3.2.3 -> dev line map.
- A dev re-check line and "Line numbers in the older notes refer to v3.2.3." were added to `unsure`.

## C03_HIVE: dev changes (dev 411e5913 vs v3.2.3)

### Story / flag changes
- **Azalea Gym puzzle** (maps/AzaleaGym.asm, +581 lines).
  - Commits: 42176df6 "Implement Azalea Gym puzzle from HGSS", plus 2f6171d9/c132c848 (half-step movement) and d55ad8a0 (dirt tiles).
  - The gym is now 2x taller: entrance warps (6,23)/(7,23) (:6-7).
  - Four Spinarak carts carry the player along scripted paths (SpinarakCart1Script-4Script). A red switch (bg_event :15) and blue switches (:16-18) toggle webs with `changeblock` (AzaleaGymRedSwitch / AzaleaGymBlueSwitch).
  - **The puzzle keeps its state only in EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1/2**, which reset on every map load. No persistent flag, coord event or forced script was added.
  - Bugsy's script is unchanged in effect: `setevent EVENT_BEAT_BUGSY` :59, `givebadge HIVEBADGE` :61, AZALEA_TOWN -> SCENE_AZALEATOWN_RIVAL_BATTLE 1 :62, the four gym-trainer flags :63-66, TM_U_TURN :88, EVENT_GOT_TM69_U_TURN :89.
  - All gym trainers moved (Benny 5,12 R; Al 11,13 D; Josh 11,4 D; twins 1,4 / 2,4 D). Their flags are still set by Bugsy.
  - Not checked: which of them the carts make unavoidable. My grid model can't follow scripted cart rides, so they stay out of the money estimate, as in 3.2.3.
- **Bugsy's party order** (data/trainers/parties.asm:156-168): SCYTHER L17 moved to the front, so BUTTERFREE 14 / BEEDRILL 14 / YANMA 14 follow.
  - The top level is still 17, so there is no party_hint shift.
  - His payout uses the last mon (now Yanma L14): 25x14x4 = 1400 instead of 1700.
  - money_hint 10400 -> 10100.
- **Checked unchanged**:
  - Violet PC aide / Togepi egg (maps/VioletPokeCenter1F.asm:56-61, `setmapscene ROUTE_32, SCENE_ROUTE32_LYRA_GROTTOES`; `disappear` :76).
  - Route 32:
    - The Lyra grotto intro now also handles an already-hatched egg (text only, 326dfb06, Route32.asm:285-292).
    - Scene names: 0 COOLTRAINER_M_BLOCKS, 1 LYRA_GROTTOES, 2 OFFER_SLOWPOKETAIL, 3 NOOP (setscene :442).
    - Albert is still forced (:711), and all coords are still unavoidable (dev .ablk re-check).
  - Union Cave 1F (Daniel forced, :53) and Route 33 (Imogen became a `trainer` with an after-script, same flag, still avoidable, Route33.asm:130).
  - Kurt's house (EVENT_AZALEA_TOWN_SLOWPOKETAIL_ROCKET :67, APRICORN_BOX :92-93) and Slowpoke Well B1F (3 grunts + Proton forced; Proton2Script flags :70-79; ILEX_FOREST -> SCENE_ILEXFOREST_NOOP 2 :71).
  - Azalea Town: fly point :57. The Rockets still block the well and gym doors, and the rival coords (5,10)/(5,11) (:22-23) are still off the gym->PC path.
  - Togepi is still HATCH_FASTER (data/pokemon/base_stats/togepi.asm:8), so EVENT_TOGEPI_HATCHED is still not set.
  - `at` AZALEA_POKECENTER_1F (5,6) is still floor above warps (5,7)/(6,7).

### Source-line-only changes
- EVENT_BEAT_BUGSY -> maps/AzaleaGym.asm:59. The draft pointed at `checkevent` :52.
- ENGINE_HIVEBADGE -> AzaleaGym.asm:61 (`givebadge`). The draft pointed at the statue's `checkflag` :41.
- Every other src matches the diff-based v3.2.3 -> dev line map.
- The money/rival unsure lines now quote dev lines, and a v3.2.3 line-number notice was added.

## C04_PLAIN: dev changes (dev 411e5913 vs v3.2.3)

### Story / flag changes
- **Dev did not change the story here.**
- **Added (coordinator's correction, applies to 3.2.3 too): EVENT_DAYCARE_MON_1 and EVENT_DAYCARE_MON_2 in `events_set`.**
  - Route34EggCheckCallback (MAPCALLBACK_OBJECTS, maps/Route34.asm:7) runs on the first entry to Route 34.
  - The Day-Care holds no Pokemon (ENGINE_DAY_CARE_MAN_HAS_MON / ENGINE_DAY_CARE_LADY_HAS_MON clear), so it hides both Day-Care Pokemon objects: `setevent EVENT_DAYCARE_MON_1` (:71) and `setevent EVENT_DAYCARE_MON_2` (:81).
  - v3.2.3 had the same code at Route34.asm:69/:79. Neither flag is in InitialEvents.
  - Dev still does this; the callback is unchanged apart from line shifts (:49-82).
- **money_hint** 15000 -> 14700. This only carries C03's -300 (Bugsy's last mon is L14 in dev). No C04 payout changed:
  - RIVAL1_5 still ends with QUILAVA 18 (data/trainers/parties.asm:1557-1570).
  - LYRA1_6 still ends with CROCONAW 18 (:2064-2071).
  - WHITNEY 1 is unchanged (:210-223; Miltank got the nickname "Milky").
  - No party_hint shift (top level 21).
- **Checked unchanged**:
  - Azalea rival: coords (5,10)/(5,11) still forced; `setmapscene ROUTE_34, SCENE_ROUTE34_LYRA_DAYCARE` (AzaleaTown.asm:122); setscene SCENE_AZALEATOWN_NOOP 0 (:123).
  - Ilex Forest scene names: 0 FARFETCHD_QUEST, 1 CUT_SCENE, 2 NOOP.
    - The apprentice coord (9,31) and the cut tree (10,27) are still unavoidable.
    - Herding and HM_CUT: EVENT_HERDED_FARFETCHD :308, HM_CUT :376, EVENT_GOT_HM01_CUT :377, kiln/forest flags :381-386.
    - Only text/`thistext` changes otherwise.
  - Route 34:
    - Lyra's intro text no longer branches on gender (Route34.asm:108).
    - The flags, the LYRA1_6 battle and setscene SCENE_ROUTE34_NOOP (:156) are unchanged.
    - The trainers are still avoidable.
  - Day-Care: gender text via `.GetPlayerPronouns` (DayCare.asm:78-105, handles PLAYER_BETA). PHONE_LYRA :62, Lyra `disappear` :74, setscene SCENE_DAYCARE_NOOP 1 :75.
  - Goldenrod City:
    - New palette-swap callback, renamed Goldenrod Underground warps, extra double-door warps.
    - The gym door (28,7) is still reachable only from (28,8), where the Radio Card lass stands (GoldenrodCity.asm:59), so the quiz is still required.
    - Fly point :79.
  - Radio Tower 1F quiz: ENGINE_RADIO_CARD :173, Whitney `disappear` :184.
  - Goldenrod Gym:
    - Lass Cathy became a `trainer` with an after-script (GoldenrodGym.asm:22), same flag.
    - Whitney's script: :40-46, `givebadge PLAINBADGE` :69, TM_ATTRACT :73-74.
    - WhitneyCriesScript at (8,5) is still the only exit.
  - `at` GOLDENROD_POKECOM_CENTER_1F (6,14) is still floor above warps (6,15)/(7,15).

### Source-line-only changes
- Wrong draft sources were fixed:
  - EVENT_GOT_HM01_CUT -> IlexForest.asm:377. The draft pointed at `checkevent` :370.
  - EVENT_GOT_TM45_ATTRACT -> GoldenrodGym.asm:74. The draft pointed at `checkevent` :62.
  - ENGINE_PLAINBADGE -> GoldenrodGym.asm:69 (`givebadge`). The draft pointed at `checkflag` :64.
  - AZALEA_TOWN scene -> AzaleaTown.asm:123 (`setscene`). The draft pointed at the ROUTE_34 `setmapscene` :122.
- Every other src matches the diff-based v3.2.3 -> dev line map.
- The unsure lines I touched quote dev lines, and a v3.2.3 notice was added.

## C05_FOG: dev changes (dev 411e5913 vs v3.2.3)

### Story / flag changes
- **Burned Tower 1F: new forced Firebreather Dick battle** (commit cb3c15c7 "Restore burnt-out Firebreather from G/S"; 6712cf7d music fix).
  - **Scene order** is now 0 MEET_EUSINE, 1 FIREBREATHER_DICK, 2 RIVAL_BATTLE, 3 NOOP (maps/BurnedTower1F.asm:3-6).
  - **Eusine's intro** now sets scene 1 (:63). That arms the coord event at (6,1) (:18).
  - **BurnedTowerFirebreatherDickBattleScript** (:66):
    - `loadtrainer FIREBREATHER, DICK` (:67). The party is CHARMELEON 17 (data/trainers/parties.asm:4473-4474). After loading, engine/battle/core.asm:8965-8977 swaps the class to FIREBREATHER_ASHES.
    - `appear` of the ashes object (:77/:80) clears **EVENT_BURNED_TOWER_FIREBREATHER_DICK_ASHES**. It was set by InitialEvents (initialize_events.asm:179, recorded in C01).
    - On a win:
      - `disappear` Dick (:89) sets **EVENT_BURNED_TOWER_FIREBREATHER_DICK_NORMAL** (object :29; not in InitialEvents).
      - `setevent` **EVENT_BEAT_FIREBREATHER_DICK** (:90).
      - `setscene` 2 (:91).
    - A loss re-hides the ashes (:96) and keeps scene 1.
  - **Only scene 2 arms the rival coord (9,9)** (:19). The rival script now ends with `setscene SCENE_BURNEDTOWER1F_NOOP` = **3** (:144), not 2. BURNED_TOWER_1F scene is now 3, src :144.
  - **Forced**: the pathfinder on the dev map shows that (6,1) is the only way from the entrance (7,15) to the rival tile (9,9). The callback blocks were applied: hole block $32 at (8,8) and no ladder ($09 at (4,14)), with Dick standing on (6,3).
  - **After the battle** the ashes stand on (6,2), and (6,1)->(7,1)->(9,9) is still open.
  - **Added to the JSON**:
    - events_set: EVENT_BEAT_FIREBREATHER_DICK (:90), EVENT_BURNED_TOWER_FIREBREATHER_DICK_NORMAL (:29).
    - events_clear: EVENT_BURNED_TOWER_FIREBREATHER_DICK_ASHES (:28).
    - Money +1020: FIREBREATHER and FIREBREATHER_ASHES both have base 15 (data/trainers/attributes.asm:329-331, :893-895), so 15x17x4.
- **Hex Maniac Tamara** moved from (1,1) facing right to (3,6) facing left (BurnedTower1F.asm:33).
  - She is still forced: her sight covers (2,6)/(1,6), and the way to (6,1) runs up column x=1.
  - Same flag (generictrainer :165) and party.
- **money_hint** 22900 -> 23600: +1020 for Dick, and -300 carried from C03 (Bugsy).
- **Party**: MORTY 1 is unchanged (data/trainers/parties.asm:261-286, top level 26), so there is no party_hint shift.
- **Cross-chapter notes**:
  - EVENT_BEAT_FIREBREATHER_DICK is a new flag (constants/event_flags.asm:2443). 3.2.3's Rock Tunnel "Dick" is now Firebreather Cyd with EVENT_BEAT_FIREBREATHER_CYD (maps/RockTunnelB1F.asm:27).
  - The C12 draft still lists EVENT_BEAT_FIREBREATHER_DICK for Rock Tunnel. It should become EVENT_BEAT_FIREBREATHER_CYD, or the checker warns that C05 already set it.
- **Checked unchanged**:
  - Flower Shop: SQUIRTBOTTLE :49, EVENT_GOT_SQUIRTBOTTLE :50. The Mulch purchase was reworked; it is optional.
  - Route 35: Arnie forced (:130), cut tree (21,6) needed (:33); the National Park detour still avoids both.
  - Route 36: map trimmed by 18 columns (Sudowoodo now at (21,9), :33). Sudowoodo is still the only way north: EVENT_FOUGHT_SUDOWOODO :99, `disappear` :101.
  - Route 37: Callie and Cassandra forced. Cassandra became a `trainer` with an after-script (:129), same flag.
  - Ecruteak City: new pagoda objects and moved warps. The Burned Tower door, gym and Pokemon Center are still reachable. Fly point :58.
  - Burned Tower B1F: scene names only. ReleaseTheBeasts flags :94-109 are the same; ECRUTEAK_GYM -> SCENE_ECRUTEAKGYM_NOOP 1, CIANWOOD_CITY -> SCENE_CIANWOODCITY_SUICUNE_AND_EUSINE 1.
  - Ecruteak Gym: redesigned (taller, more pits, lamps). Morty's script flags are the same:
    - EVENT_BEAT_MORTY :93, FOGBADGE :95, ECRUTEAK_HOUSE -> NOOP 1 :96, bells :97-98.
    - Gym trainers :102-105, TM_SHADOW_BALL :108, EVENT_GOT_TM30_SHADOW_BALL :109.
  - `at` ECRUTEAK_POKECENTER_1F (5,6) is still floor above warps (5,7)/(6,7).

### Source-line-only changes
- Wrong draft sources were fixed:
  - EVENT_BEAT_MORTY -> EcruteakGym.asm:93. The draft pointed at `checkevent` :84.
  - EVENT_GOT_TM30_SHADOW_BALL -> :109. The draft pointed at `checkevent` :100.
  - BURNED_TOWER_1F scene -> BurnedTower1F.asm:144. The draft pointed at Dick's `setscene` :91.
- Every other src matches the diff-based v3.2.3 -> dev line map.
- The unsure lines I touched quote dev lines, and a v3.2.3 notice was added.

## C06_STORM: what changed in dev

All paths are in the dev checkout (master 411e5913).
The route is the same as in 3.2.3 (Dance Theatre -> Route 38/39 -> Olivine -> Lighthouse 6F ->
Route 40/41 -> Cianwood Pokemon Center -> Cianwood Gym).

### Story changes

1. **Cianwood Gym was rebuilt** (maps/CianwoodGym.asm, TILESET_GYM, new .ablk; commit 353436de "Use the Cianwood Gym layout from HGSS").
   - Chuck trains under a waterfall. The object you see first is CHUCK2 (:22, flag
     EVENT_BOULDERS_IN_CIANWOOD_GYM, new in constants/event_flags.asm:2440); talking to him only
     shows text (:356). The real Chuck (:21) is hidden by EVENT_TEMPORARY_UNTIL_MAP_RELOAD_4,
     which the TILES callback sets while the flag is clear (:43-47).
   - Two Strength boulders, (9,4) and (16,4) (:24-25), must be pushed into the stone warps (12,4)/(13,4)
     (:11-12; stonetable :64-65). The second drop runs .BlockWaterfall (:83-127):
     `appear CIANWOODGYM_CHUCK1`, `disappear CIANWOODGYM_CHUCK2` (:85), which **sets
     EVENT_BOULDERS_IN_CIANWOOD_GYM**. Added to events_set, cited at the object line :22 (the
     project's rule for appear/disappear flags). It is not in data/events/initialize_events.asm.
   - HM Strength is still needed and still comes from the Gym Guy (maps/CianwoodPokeCenter1F.asm:58-59).
   - Chuck's script is unchanged apart from line numbers: EVENT_BEAT_CHUCK :149, STORMBADGE :151,
     SPECIALCALL_YELLOWFOREST :152, the four Blackbelt setevents :156-159, TM_DYNAMICPUNCH :162,
     EVENT_GOT_TM01_DYNAMICPUNCH :163.
   - Forced trainers re-checked on the new collision (my render of the dev .ablk): Yoshi (5,10, right,
     range 2) sees (7,10), the only way into the left room from (7,11); Nob (9,6, left, 2) sees (7,6),
     the only way up to row 5 on the left; Lao (21,10, left, 2) sees (19,10), the only way to row 9 on
     the right; Lung (20,6, left, 2) sees (18,6), the only way to row 5 on the right. One boulder is in
     each half, so all four are fought (and Chuck sets all four anyway). No object stands in any of
     these sight lines (dev lets objects block sight, home/trainers.asm).
2. **Olivine City scene value is now 2, not 1** (maps/OlivineCity.asm).
   - New scene names: 0 SCENE_OLIVINECITY_RIVAL_ENCOUNTER, 1 SCENE_OLIVINECITY_STEP_DOWN,
     2 SCENE_OLIVINECITY_NOOP (:3-5). The lighthouse rival (coord (33,22), :25) now ends with
     `setscene SCENE_OLIVINECITY_NOOP` (:133).
   - The Lighthouse door became a coord_event (33,21) in scene NOOP (:26) that sets STEP_DOWN (:95)
     and warps to OLIVINE_LIGHTHOUSE_1F (10,17) (:96). Coming back out (warp 8 at (33,21), :19), the
     STEP_DOWN scene script steps the player down and sets NOOP again (:70-82).
   - So OLIVINE_CITY ends at 2; src changed to :82. (33,21) is reachable only from (33,22), so the
     rival is still forced (side stairs at (29,23)/(31,22) lead to the lighthouse yard).

### Source-line-only changes (no flag/route effect)
Text and macro renames (jumpthistext, `verbosegiveitem X, iffalse...`, PAL_MON_*), moved signs/objects:
DanceTheatre (Kimono Girls :30-78, Surf :113-114), Route38 (Beauty Valencia moved to (26,9); the north
and south routes still avoid everyone), Route38EcruteakGate, Route39 (objects +2 rows; Derek now
(10,38), still forced, :46), EcruteakCity, OlivineLighthouse1F-6F (text only; Jasmine :33),
Route40/Route41 (open water, swimmers avoidable), CianwoodCity (scene names, flypoint :55).
Draft src fixes: EVENT_BEAT_CHUCK :132 -> :149 and EVENT_GOT_TM01_DYNAMICPUNCH :154 -> :163 (the
draft pointed at checkevent lines). Chuck's party (data/trainers/parties.asm:329) and all C06
trainer levels are unchanged, so party_hint and money_hint stay.

## C07_MINERAL: what changed in dev

Dev checkout (master 411e5913). Route unchanged:
Cianwood Pharmacy -> Route 41/40 (Surf) -> Olivine -> Lighthouse 6F (SecretPotion) -> Olivine Gym.

### Story changes
None. Every flag, item and scene of this stretch is set by the same script as in 3.2.3.

- Olivine Lighthouse entry/exit is new (see C06 dev notes): walking onto the coord_event (33,21)
  sets OLIVINE_CITY to 1 (SCENE_OLIVINECITY_STEP_DOWN, maps/OlivineCity.asm:95) and warps in;
  coming back out, the scene script sets it back to 2 (SCENE_OLIVINECITY_NOOP, :82). C06 already
  leaves it at 2, so C07 has no net change and nothing is listed.
- Olivine Gym now uses TILESET_GYM (data/maps/maps.asm) and one block changed, but the collision is
  identical to 3.2.3 (compared tile by tile), so Preston (3,10) and Connie (6,7) are still forced
  (trainer 0 "spoke to" flags, maps/OlivineGym.asm:103 and :69).
- ROUTE_42 scene 1 is now written `setmapscene ROUTE_42, SCENE_ROUTE42_LYRA` (maps/OlivineGym.asm:38;
  SCENE_ROUTE42_LYRA = 1, maps/Route42.asm:4).

### Source-line-only changes
Jasmine at the Lighthouse moved down 5 lines (EVENT_JASMINE_RETURNED_TO_GYM :70, clear
EVENT_OLIVINE_GYM_JASMINE :71, takekeyitem SECRETPOTION :48, disappear :76/:81/:86); Pharmacy
(:29-30) and Olivine Gym (:34-45) unchanged; Lighthouse floors only text. Jasmine's party
(data/trainers/parties.asm:388) has the same levels, so party_hint and money_hint stay.

## C08_GLACIER: what changed in dev

Dev checkout (master 411e5913). Route unchanged:
Route 42 (Lyra, Whirlpool) -> Mahogany -> Route 43 gate -> Lake of Rage -> Mahogany Mart ->
Rocket base B1F/B2F/B3F -> Mahogany Gym.

### Story changes
None. All scripts on the path only got scene names, text macros or reordering:

- Scene names, same values as 3.2.3: ROUTE_42 0/1/2 = SCENE_ROUTE42_NOOP/LYRA/SUICUNE
  (maps/Route42.asm:3-5; Lyra ends with `setscene SCENE_ROUTE42_NOOP` :143); ROUTE_43_GATE 0/1 =
  ROCKET_SHAKEDOWN/NOOP (maps/Route43Gate.asm:5-6; reset by maps/Route43.asm:44, no net change);
  MAHOGANY_MART_1F 0/1 = NOOP/LANCE_UNCOVERS_STAIRS (maps/MahoganyMart1F.asm:3-4; Lake of Rage sets 1
  at maps/LakeOfRage.asm:137, the Mart scene sets 0 at :78; the scene scripts were only reordered);
  TEAM_ROCKET_BASE_B2F 3 = SCENE_TEAMROCKETBASEB2F_NOOP (maps/TeamRocketBaseB2F.asm:6, set :325);
  TEAM_ROCKET_BASE_B3F 3 = SCENE_TEAMROCKETBASEB3F_NOOP (maps/TeamRocketBaseB3F.asm:6, set :123);
  MAHOGANY_TOWN 1 = SCENE_MAHOGANYTOWN_NOOP (maps/MahoganyTown.asm:4, set maps/MahoganyGym.asm:49).
- Rocket base B2F TILES callback now also shows the turbines stopped once all three Electrode flags
  are set (maps/TeamRocketBaseB2F.asm:83-99). Display only.
- Rocket base maps use TILESET_HIDEOUT. Collision compared tile by tile with 3.2.3: B1F opens
  (13-14,13); B2F opens (12-17,9) inside the transmitter room; B3F opens (8,7),(13,7) inside Petrel's
  office and (2,13),(2,15) next to the Protein ball; the rest are counter->wall swaps. None joins
  two separate areas, so the forced camera 1 grunts, Grunt M19, the B3F Lance/rival coords and the
  route stay as traced. Mahogany Town opens one dead-end tile (3,13); Lake of Rage, Route 43,
  Mt. Mortar outside and Mahogany Gym collision are unchanged.
- Dev lets objects block trainer sight (home/trainers.asm); no object stands in Grunt M19's line.

### Source-line-only changes
All src lines moved to dev lines; two draft picks were wrong and are fixed:
EVENT_OPENED_DOOR_TO_ROCKET_HIDEOUT_TRANSMITTER :336 (the BGEVENT_IFNOTSET `dw` line) ->
maps/TeamRocketBaseB2F.asm:346 (setevent), and the ROUTE_42 scene :140 (`setscene ..._SUICUNE`) ->
maps/Route42.asm:143 (`setscene SCENE_ROUTE42_NOOP`, the branch taken because
EVENT_SAW_SUICUNE_ON_ROUTE_42 is still set). Disappear lines in unsure updated (B1F :73, B2F
:153-155/:250/:268/:286/:320, B3F :77/:122). Pryce (data/trainers/parties.asm:446), Lyra, Petrel 2
and Ariana 2 have the same levels, so party_hint and money_hint stay.

## C10_TOWER: what changed in dev

Dev checkout (master 411e5913). Radio Tower 1F-5F, Goldenrod
City, Dept Store B1F/elevator and the Pokecom Center only got renames; the Goldenrod Underground part
was rebuilt and re-traced from scratch.

### Story changes

1. **Maps split and renamed** (commits 91cb920c, cf08098b, daa17687):
   WarehouseEntrance -> GOLDENROD_UNDERGROUND (maps/GoldenrodUnderground.asm; same tunnel, the basement
   room moved from x24-31 to x14-21); the stair buildings -> GOLDENROD_UNDERGROUND_ENTRANCES
   (maps/GoldenrodUndergroundEntrances.asm, no trainers or scripts on the path); the switch room ->
   GOLDENROD_UNDERGROUND_SWITCH_ROOM (maps/GoldenrodUndergroundSwitchRoom.asm, scene var
   data/maps/scenes.asm:107); UndergroundWarehouse -> GOLDENROD_UNDERGROUND_WAREHOUSE (same collision,
   same grunts and director). UNDERGROUND_PATH_SWITCH_ROOM_ENTRANCES is gone.
2. **Path in dev**: Goldenrod (13,5) (maps/GoldenrodCity.asm:23) -> Entrances (4,9) -> (4,5) ->
   GOLDENROD_UNDERGROUND (1,2). Donald (0,6, right, 3) still covers the only way down (row 6 x1-3) and
   Teru (4,9, up, 2) still covers (4,7): both forced, :164/:144. Basement door (16,6): BasementDoorScript
   sets EVENT_USED_BASEMENT_KEY (:410; the draft had the checkevent at :399) -> warp to (17,23) ->
   (18,19) -> switch room (28,2).
3. **Switch room is the HGSS puzzle** (commit d3f88b64 "Port the Underground Warehouse switch puzzle
   from HGSS", e69aa35e switches used from below). Red/Green/Blue switches at (11,4)/(10,4)/(9,4) and an
   Emergency switch at (25,8) toggle 11 shutters whose state is EVENT_DOOR_1..11_OPEN (door table :62-73,
   toggles :281-323). EVENT_SWITCH_1..14 and EVENT_EMERGENCY_SWITCH no longer exist.
   - Rival: coords (23,1)-(23,3) in scene 0 (:15-17) span the only column west, so forced; RIVAL1_11 for
     Chikorita (:174), `setscene SCENE_GOLDENRODUNDERGROUNDSWITCHROOM_NOOP` = 1 (:121). Rival object flag
     EVENT_RIVAL_GOLDENROD_UNDERGROUND (init :25, appear, setevent :150, disappear): no net change.
     EVENT_RIVAL_BURNED_TOWER already set in C05, so :145-146 are skipped.
   - **Forced trainers now: Grunt M11 only** (18,1, down, range 2; west past x=18 needs row 2 or 3).
     BFS over (position, door state) from the reset state, forbidding each trainer's sight tiles in turn
     (walls don't block sight in dev, objects do; none in these lines): Grunts M13, M25, F3 and Burglars
     Duncan, Orson are avoidable. Removed their 5 EVENT_BEAT_ flags (3.2.3 forced all six).
     Example: row 3 west, door 1 (16,4), door 6 (13,5-6), press Blue, Green, Red, door 5 (16,8),
     door 8 (19,9-10), row 11 under Grunt F3, warp (27,8).
4. **Door flags are a new net change.** GoldenrodUndergroundResetSwitches (maps/GoldenrodUnderground.asm:50-61)
   SETS doors 1-6, 9, 10 and clears 7, 8, 11. It runs on NEWMAP of GOLDENROD_UNDERGROUND (:5) and of
   the Warehouse (maps/GoldenrodUndergroundWarehouse.asm:5). The flags are clear on a new game (not in
   data/events/initialize_events.asm, and no earlier checkpoint enters the Underground), and the
   Warehouse entry is the last reset before the player leaves by the Dept Store. So
   EVENT_DOOR_1..6_OPEN, EVENT_DOOR_9_OPEN, EVENT_DOOR_10_OPEN were added to events_set (:51-56, :59, :60).
   In 3.2.3 the reset cleared EVENT_SWITCH_*, so nothing was listed.
5. **Warehouse / Dept Store flags renamed** (same logic): director gives CARD_KEY and sets
   EVENT_RECEIVED_CARD_KEY (maps/GoldenrodUndergroundWarehouse.asm:61-62), sets
   EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_1 (:63, already set at init). Dept Store B1F NEWMAP clears
   EVENT_GOLDENROD_WAREHOUSE_BLOCKED_OFF (maps/GoldenrodDeptStoreB1F.asm:52). The elevator ride rotates
   the layout: clear LAYOUT_1 (maps/GoldenrodDeptStoreElevator.asm:38), set LAYOUT_2 (:39). B1F now has
   one elevator warp (9,4); reachable from (17,2) with the Card Key + layout 1 (checked on dev collision).
6. Money: 5 fewer battles, -9720 (M13 1480, M25 1400, F3 1400, Duncan 2720, Orson 2720):
   money_hint 107900 -> 98180. C09 and later were NOT shifted; carry -9720 when merging.

### Source-line-only changes
Radio Tower 1F-5F (renames/text; all forced grunts, Marc, Rich, Proton, Ariana, Archer unchanged; no
object in any forced sight line), RadioTower5F scene names (RADIO_TOWER_5F 2 = SCENE_RADIOTOWER5F_NOOP
:127, ECRUTEAK_HOUSE 0 = SCENE_ECRUTEAKHOUSE_SAGE_BLOCKS :128), GoldenrodCity scene names (0 STEP_DOWN /
1 NOOP, :117/:130, net zero), Card Key src fixed to the setevent :143 (draft had checkevent :133).
Rival RIVAL1_11 (data/trainers/parties.asm:1687) and ARCHER1 (:7403) levels unchanged; party_hint kept.

## C09_RISING: what changed in dev

Dev checkout (master 411e5913). Route unchanged:
Mahogany -> Route 44 -> Ice Path (Waterfall ball, B1F boulders) -> Blackthorn -> Gym (Clair) ->
Dragon's Den -> Dragon Shrine quiz -> Clair's TM at the (19,30) coord -> Pokemon Center.

### Story changes
None on the main path. The quiz / badge / TM part was re-read line by line:

- Dragon Shrine (maps/DragonShrine.asm): same five questions and right answers (:51-133). Passing:
  `givebadge RISINGBADGE, JOHTO_REGION` :164, SPECIALCALL_MASTERBALL :166, `setscene
  SCENE_DRAGONSHRINE_NOOP` :167 (= 1, :3-4), `setmapscene DRAGONS_DEN_B1F,
  SCENE_DRAGONSDENB1F_CLAIR_GIVES_TM` :168. A wrong answer still only sets
  EVENT_ANSWERED_DRAGON_MASTER_QUIZ_WRONG (:122). Dratini givepoke moved to :213/:216 (optional).
- New back door (commit c1f3ca99 "Add area in back of Dragon Shrine"): warps (4,1)/(5,1) <-> Dragon's Den
  B1F (19,26)/(20,26) behind the building (maps/DragonsDenB1F.asm:12-13). The take-test scene skips the
  cutscene when entered by the back door (DragonShrineTakeTestScene :30-43 reads wPrevWarp), but the back
  strip (rows 1-2, Kimono Girl Mina moved here from B1F, :21, commit 6d566dd7) is walled off from the
  Elder's room. The main path uses the front door (B1F (19,29)), so the test runs, and after it the front
  door is the only way out, so the Clair coord (19,30) is still forced.
- Dragon's Den B1F: Clair's TM unchanged: `verbosegivetmhm TM_DRAGON_PULSE` :76, EVENT_GOT_TM59 :77,
  `setscene SCENE_DRAGONSDENB1F_NOOP` :88, `setmapscene NEW_BARK_TOWN, SCENE_NEWBARKTOWN_LYRA_FINAL` :89
  (= 1, maps/NewBarkTown.asm:4), `clearevent EVENT_LYRA_IN_HER_ROOM` :90. The -91 lines are Kimono Girl
  Mina's script moving to the shrine. Collision: only the back-door tiles (18-21,26) and one whirlpool
  moved ((10,20) -> (11,21)).
- Dragon's Den 1F is now its own 20x8-tile map (maps/DragonsDen1F.asm:6-10, own .ablk, commit 89f4fb57); no objects.

### Source-line-only changes
Ice Path: MAPCALLBACK_STONETABLE -> MAPCALLBACK_CMDQUEUE and SPRITE_ICE_BOULDER_FOSSILS; collision
unchanged; boulder stonetable lines unchanged (maps/IcePathB1F.asm:49-65). Blackthorn Gym 2F same
callback rename (:5), collision of both floors unchanged, Clair's script unchanged
(maps/BlackthornGym1F.asm:63-75). Blackthorn City: 15 collision tiles changed, all off the path
((17,13) by the gym, south-west shore). Route 44 / Pokemon Center text only. Dev lets objects block
trainer sight (home/trainers.asm); that can only make trainers easier to avoid, and none is listed.
Clair's party (data/trainers/parties.asm:511) is unchanged. money_hint is NOT changed here; it should
carry C10's -9720 when merging.

## C11_CHAMPION: dev changes (v3.2.3 -> dev 411e5913)

Path unchanged: (walk) Blackthorn -> New Bark (Lyra farewell) -> Route 27 -> Tohjo Falls -> Route 26 ->
Pokemon League Gate -> Route 23 (8 badge checks) -> Victory Road -> Indigo Plateau -> E4 + Lance ->
Hall of Fame -> credits -> Continue in New Bark (15,6). Key opponent Lance, top level 60 (dev
data/trainers/parties.asm:833), unchanged, so party_hint is kept.

### Story changes in dev

1. **Route 23 was split into ROUTE_23_SOUTH and ROUTE_23_NORTH** (commit 395315a3; ROUTE_23 and
   maps/Route23.asm are gone). The 8 officers are still there:
   - maps/Route23South.asm: Zephyr (16,55), Hive (11,47), Plain (row 31), Fog (row 22, surfing),
     Storm (row 7); coord events :17-31, `setscene` :61, :79, :97, :115, :133 (0 -> 5).
   - maps/Route23North.asm: Mineral (row 70), Glacier (14,55), Rising (8/9,47); `setscene` :89, :107,
     :125 (5 -> 8). The heal officer (:36/:47) is optional.
   - Both maps use one scene byte, wRoute23SceneID (data/maps/scenes.asm:69-70), so the net change is
     recorded once: ROUTE_23_NORTH = 8 (SCENE_ROUTE23NORTH_NOOP, maps/Route23North.asm:125).
   - Collision flood fill of the dev maps: each of the 8 check lines blocks the way on its own, and
     the north half can only be crossed through Victory Road (Route23North warps (6,31) VR 1F entry,
     (16,31) VR 2F exit).
2. **New fly point ENGINE_FLYPOINT_POKEMON_LEAGUE** (commit 9e2aad02): NEWMAP callback
   maps/PokemonLeagueGate.asm:7 -> `setflag` :31 (spawn ROUTE_26 8,6, data/maps/spawn_points.asm:27;
   engine bit data/events/engine_flags.asm:98). Added to engine_set. The gate doors moved (Route 22 now
   east (21,6)/(21,7), Route 28 west (0,6)/(0,7), Route 26 (10,17)/(11,17)); the reminder coord events
   (10,10)/(11,10) (:21-22, scene set at :44) are still the only way north (flood fill).
3. **New Bark**: Lyra's farewell coord events moved from x=17 to x=19 (maps/NewBarkTown.asm:21-24);
   the water still only touches land there. Battle `loadtrainer LYRA1, LYRA1_12` :140, `setscene` :150.
4. **Route 27** was trimmed 4 tiles on the west; the first-step events are now (14,10)/(15,10)
   (maps/Route27.asm:15-16), still the only landing from New Bark's water; `setscene` :56.
5. **Not a dev change, found while re-checking**: Victory Road 1F Veteran Matt (12,6, facing down,
   range 3) is unavoidable (only way from the entrance to the 2F ladder is the walled bridge x=12-13
   and then across column 12 inside his sight; VR 1F is identical in v3.2.3). Added
   EVENT_BEAT_VETERANM_MATT (maps/VictoryRoad1F.asm:21). **money_hint +2960** (4 x 20 x Sandslash 37,
   dev data/trainers/parties.asm:7172, attributes.asm:623-625); C12 and C13 carry the same +2960.
6. Checked, no story change: Hall of Fame script (maps/HallOfFame.asm:46-92, same flags), 
   engine/events/halloffame.asm (only predef -> farcall), RespawnOneOffs (engine/events/specials.asm:328;
   EVENT_BEAT_KATY -> EVENT_BEAT_LARRY at :330, an optional Shamouti trainer; main-path clears at
   :356, :428, :435, :437), E4 rooms (only scene constants), Lance's room (block ids only),
   Continue/spawn (engine/menus/intro_menu.asm:369-391, spawn NEW_BARK 15,6 unchanged), Indigo
   Pokecenter (scene constant only), Victory Road 2F rival (maps/VictoryRoad2F.asm:66, :78).
7. On foot Blackthorn -> New Bark (not traced in v3.2.3): the direct Route 45 way forces Hiker Erik
   (maps/Route45.asm, (12,20)), but Dark Cave (Blackthorn entrance -> Violet entrance -> Route 46)
   avoids every trainer, so nothing is added (in unsure).

### Source-line-only changes
Scenes are now SCENE_* constants with the same values (NEW_BARK_TOWN 2, ROUTE_27 1, POKEMON_LEAGUE_GATE 1,
VICTORY_ROAD_2F 1, E4 rooms/LANCES_ROOM/HALL_OF_FAME 1); all other srcs only moved lines (WillsRoom.asm:33-76,
KogasRoom/BrunosRoom/KarensRoom.asm:34-77, LancesRoom.asm:23/43/44/97, HallOfFame.asm:46-89,
IndigoPlateau.asm:19, halloffame.asm:16). dev_problems (ROUTE_23) resolved as item 1.

## C12_KANTO: dev changes (v3.2.3 -> dev 411e5913)

Same route and order (Surge, Sabrina, Misty, Janine, Erika, Brock, Blaine, Blue), same story gates
(S.S. Ticket, lazy sailor, Power Plant chain, EXPN card, two big Snorlax, Blue last). Key opponent
Blue, top level 70 (dev data/trainers/parties.asm:1355), unchanged; all 8 leaders' top levels
unchanged, so party_hint is kept.

### Story changes in dev

1. **Rock Tunnel B1F: Firebreather Dick is now Firebreather Cyd** (commit cb3c15c7 "Restore burnt-out
   Firebreather from G/S"; Dick moved to Burned Tower, C05). Same spot (27,14), facing and range, still
   forced: EVENT_BEAT_FIREBREATHER_DICK replaced by **EVENT_BEAT_FIREBREATHER_CYD**
   (maps/RockTunnelB1F.asm:27). Cyd has the old Dick party (parties.asm:4521), so no money change.
2. **Route 13 East + West merged into ROUTE_13** (commit 22cbdb13; maps/Route13West.asm deleted,
   Route13East.asm -> Route13.asm). Joshua (38,8) `generictrainer` maps/Route13.asm:240 and Kenny (14,10)
   :260 are both still unavoidable between Route 12 South and Route 14 (dev path search; the new south
   dual connection to Lucky Island, data/maps/dual_connections.asm, gives no way round). Kenny's src
   moved to Route13.asm:260.
3. **Route 24 bridge / Cerulean**: CERULEAN_CITY now shares ROUTE_24's scene byte wRoute24SceneID
   (data/maps/scenes.asm:71-72, commit 1f9e29db), with new Cerulean coord events (20/21,2) and (4/5,2)
   at scene 0 (maps/CeruleanCity.asm:22-25, write at :74). Route 24 triggers: maps/Route24.asm:13-32,
   write at :97. Re-traced: northbound Cerulean (20,2) sets 1, bridge north end (20,12) sets 0; walking
   back from the Cape over the bridge, (20,13) sets 1 (Route24.asm:97) and nothing resets it, so
   **ROUTE_24 = 1 is kept** (same byte as CERULEAN_CITY). Surfing back under the bridge would leave 0.
4. **Power Plant** (maps/PowerPlant.asm:140-190): same flags (EVENT_MET_MANAGER_AT_POWER_PLANT :149,
   MACHINE_PART taken :159, EVENT_RESTORED_POWER_TO_KANTO :163 ...); new turbine tile changes; the Zap
   Cannon tutor is now free (optional). No list change.
5. Checked, no story change: Fast Ship (scene constants, Sailor Garrett now a `trainer`, optional),
   Vermilion (new layout, gym still behind cut tree (13,19) maps/VermilionCity.asm:53 or Surf),
   Route 6/5/Saffron/Cerulean layouts, Route 10 North (cut trees now :32-33, new optional wild Electrode
   EVENT_ROUTE_10_NORTH_ELECTRODE :34 off the path, Lawrence scene gains a 4th-gender branch; female
   unchanged), Fuchsia (zoo signs and Fuchsia Aquarium added, gym door now (6,27) maps/FuchsiaCity.asm:10,
   fly point :61), Celadon (cut tree (32,34) still needed, :60), Pewter/Viridian layouts, Seafoam 1F
   shrunk (warps :8-12, rocks flag :22), Viridian Gym / Blue (text only), kantopostgymevents
   (engine/events/std_scripts.asm:1760, unchanged).
6. Forced trainers, cut trees and blockers were re-run with a collision path search on every changed
   map of the route: Dean (Route9.asm:28), Grunt 31 (story, Route24.asm:109), Seamus (RockTunnel1F.asm:28),
   Cyd, Joshua, Kenny, Leona (Route20.asm:94) forced; Route 9, Vermilion, Celadon, Route 2 cut trees 1
   and 2 used; both big Snorlax (2x2) block. Same as v3.2.3.
7. Sources fixed to the changing line (the draft pointed at `checkevent` lines):
   EVENT_FAST_SHIP_INFORMED_ABOUT_LAZY_SAILOR FastShipB1F.asm:70, EVENT_MET_MANAGER_AT_POWER_PLANT
   PowerPlant.asm:149, EVENT_RESTORED_POWER_TO_KANTO PowerPlant.asm:163, EVENT_GOT_TM61_WILL_O_WISP
   SeafoamGym.asm:107.
8. Walking without Fly (unsure only, not listed): Route 11 -> Vermilion is blocked by the Vermilion
   Snorlax (37-38,14-15) until woken; Route 8 forces Gentleman Milton (43,14) and two cut trees.

Money: no payout change inside C12. money_hint +2960 only because C11 now includes Victory Road
Veteran Matt (running total).

### Source-line-only changes
Scenes now SCENE_* constants with the same values (VERMILION_CITY 1 VermilionCity.asm:114, FAST_SHIP_B1F 1
FastShipCabins_NNW_NNE_NE.asm:118); every other src only moved lines (ElmsLab.asm:485/525/526, VermilionGym,
SaffronGym, CeruleanGym, FuchsiaGym, CeladonGym, PewterGym, SeafoamGym, ViridianGym, CinnabarIsland ...).
dev_problems (Dick, Route13West) resolved as items 1 and 2.

## C13_POSTGAME: dev changes (v3.2.3 -> dev 411e5913)

Same route: Indigo Plateau (forced final Lyra fight) -> E4 rematch (party 2, LANCE2) -> Hall of Fame
(gold trophy, EVENT_BEAT_ELITE_FOUR_AGAIN) -> New Bark -> Pallet, Oak (battle, opens Mt. Silver) ->
Route 22 -> Pokemon League Gate west corridor -> Route 28 -> Silver Cave -> Red. Key opponent Red, top
level 90 (dev data/trainers/parties.asm:1426), unchanged, so party_hint is kept.

### Story changes in dev

None in the scripts. Details that moved:
1. **Silver Cave Room 3 redesigned** (commit 54917bff): Red now stands at (8,6) (maps/SilverCaveRoom3.asm:15),
   the entrance warp is (7,29), and decorative arch objects were added. The script is the same:
   MYSTICTICKET :53, EVENT_GOT_MYSTICTICKET_FROM_RED :54, `disappear` :57, ENGINE_RED_IN_MOUNT_SILVER :60,
   EVENT_BEAT_RED :65. Path from Silver Cave Outside through Rooms 1-3 to (8,7) re-checked (no Cut/Surf).
   The literal post-battle spot is now SILVER_CAVE_ROOM_3 (8,7) (unsure updated); `at` stays the
   Pokecenter (5,6).
2. **Red's team** changed: Lapras 86, Pikachu 90, Espeon 84, Machamp 85, Snorlax 87, Charizard 88 (was
   ... Omastar 87, Gyarados 87 ...). Top level 90 and last mon 88 unchanged, so money is unchanged.
3. **Pokemon League Gate** (maps/PokemonLeagueGate.asm): new doors (Route 22 at (21,6)/(21,7), Route 28 at
   (0,6)/(0,7)) and a fly point (set in C11). The Black Belt (7,5) (:27, EVENT_OPENED_MT_SILVER) still
   blocks the only way to Route 28 (path search with/without the flag), so Oak's battle is still required.
4. Checked, no story change: Oak's Lab (text only; EVENT_TALKED_TO_OAK_IN_KANTO :50, CATCH_CHARM :98,
   rematch check :86, EVENT_BEAT_PROF_OAK :155, EVENT_OPENED_MT_SILVER :156), Indigo Pokecenter (scene
   constant only; Lyra final fight :65/:180, ENGINE_INDIGO_PLATEAU_LYRA_FIGHT :193, clear :194), Hall of
   Fame (gold trophy :57, EVENT_BEAT_ELITE_FOUR_AGAIN :76), Route 28 (door moved), Silver Cave Outside fly
   point (:24).
5. Sources fixed to the changing line (the draft pointed at `checkevent` lines):
   EVENT_LISTENED_TO_OAK_INTRO OaksLab.asm:139 (was :135), EVENT_GOT_MYSTICTICKET_FROM_RED
   SilverCaveRoom3.asm:54 (was :51).

Money: no payout change inside C13. money_hint +2960 only because C11 now includes Victory Road
Veteran Matt (running total).

### Source-line-only changes
All other srcs only moved lines (HallOfFame.asm:57/76, OaksLab.asm:50/98/155/156, IndigoPlateauPokecenter1F.asm:193/194,
SilverCaveOutside.asm:24, SilverCaveRoom3.asm:15/53/60/65). The draft had no dev_problems.
