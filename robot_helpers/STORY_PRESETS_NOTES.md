# Story presets: how they were traced

`story_presets.lua` describes what a Polished Crystal 3.2.3 save holds at 13
points along the main story (female player, Chikorita). This file explains
how that was worked out, where it differs from the task description, and
what is guessed. The step-by-step trace for each checkpoint is at the end.

## Source and method

- Source: `Rangi42/polishedcrystal`, tag `v3.2.3` (commit `3fa4319`). Every
  name and line number comes from that version.
- The story was split into stretches between checkpoints, and each stretch
  was traced by reading every script a player runs on the way: talking to
  story characters, map callbacks, scene scripts, coord (step-on) events,
  trainer and gym leader scripts. Calls were followed into `scall`,
  `farscall`, `jumpstd`/`callstd`, `special`s, phone scripts
  (`specialphonecall`), `givebadge`, `halloffame` and engine code that sets
  flags directly (e.g. `RespawnOneOffs` in `engine/events/specials.asm`).
- `appear`/`disappear` change an object's event flag
  (`engine/overworld/scripting.asm`). Those flags are cited at the
  `object_event` line that names the flag, because the `disappear` line
  itself doesn't name it; the exact `disappear` lines are in the trace notes.
- Which trainers the main path can't avoid is not written anywhere in the
  scripts. It was worked out with a path search over each map's collision
  data, blocking objects and trainer sight lines. Trainers that spin in
  place were treated as avoidable. This is the least certain part; see
  "Forced trainers" in each checkpoint's notes.
- Later, `story_steps.lua` traced the same route step by step, checking
  every trainer's line of sight on the way. Comparing the two found a few
  forced battles and two Day-Care flags the checkpoints had missed; they
  were added (see "Changed when combining" in C04, C09, C11 and C12), so
  each chapter of steps now gives exactly its checkpoint's changes.
- Every name and `sources` entry was then checked automatically with
  `check_presets.py` (every name exists in the 3.2.3 constants; every cited
  line exists and mentions the name, its badge, or the bit that stores the
  engine flag). The result is 0 errors, 0 warnings. The file also loads in
  Lua 5.4.

## Order: C10 comes before C09

Polished keeps Crystal's order here. Beating Pryce starts the Radio Tower
takeover (`maps/MahoganyGym.asm:40-49`), and a Dragon Tamer stands in front
of Blackthorn Gym until the tower is cleared (`maps/BlackthornCity.asm:29-30`,
`maps/RadioTower5F.asm:108-109`). So the list runs
C08_GLACIER → **C10_TOWER → C09_RISING** → C11_CHAMPION. The ids are kept.

## Where Polished differs from the task description

- **Pokédex (C01):** Professor Oak gives it at Mr. Pokémon's house
  (`maps/MrPokemonsHouse.asm:107-108`), not Elm.
- **Poké Balls (C02):** Elm's aide gives none. The 5 Poké Balls come from
  Lyra's catching lesson on Route 29 (`maps/Route29.asm:91`), at the start of C02.
- **Before Falkner (C02):** Sprout Tower is required. The gym is empty until
  you meet Falkner in Dark Cave, and he only lets you through in the dark
  once you have TM70 Flash from Elder Li at the top of Sprout Tower.
- **Before Whitney (C04):** the Radio Tower quiz (Radio Card) is required. A
  lass blocks the gym door until Whitney leaves the Radio Tower after it.
- **HMs:** Cut from the Ilex Forest apprentice (C04), Surf from the Dance
  Theatre after the Kimono Girls (C06), Strength from the Cianwood Pokémon
  Center (C06, needed for Chuck's gym boulders), Whirlpool from **Lyra** on
  Route 42 (C08), Waterfall from an item ball in Ice Path (C09).
  **Fly** is only given in Yellow Forest (`maps/YellowForest.asm:148`) at the
  end of an optional side quest, so it is not in any checkpoint; the
  main-path player walks and surfs.
- **Rocket hideout (C08):** Lance gives TM Thief at the end, and the rival
  only shoves you (no battle).
- **Clair (C09):** her gym script gives no badge. The Rising Badge is given
  in the Dragon Shrine after the Elder's quiz, and TM Dragon Pulse right
  outside it.
- **After the credits (C11):** the game continues in New Bark Town
  (`SPAWN_NEW_BARK`), just south of the player's house.
- **Kanto (C12):** Elm gives the S.S. Ticket after the credits, and the
  lazy-sailor quest on the S.S. Aqua is required to reach the captain.
  Blue is always last: his gym stays closed until you talk to him on
  Cinnabar with 15 badges. Both Snorlax need the Poké Flute radio channel,
  so the EXPN card and a restored Power Plant come first. The other gym
  order is a choice (see its notes).
- **Red (C13):** the way to Mt. Silver opens only after an Elite Four
  rematch with 16 badges and then beating Professor Oak in his lab.
  Red has one fixed team (Pikachu 90 … Charizard 88).
- **Goldenrod:** its Pokémon Center map is `GOLDENROD_POKECOM_CENTER_1F`;
  there is no `GOLDENROD_POKECENTER_1F` in 3.2.3.

## Conventions

- Each entry lists the **net change** over its stretch. A flag set and then
  cleared inside one stretch is left out; the notes mention such cases.
- C01 starts from an all-clear save, so it includes everything
  `InitializeEvents` sets (171 event flags, 2 engine flags, 3 scenes). Five
  of those are cleared again on the way and are listed in `events_clear`
  instead. If the robot starts from a save the game made itself, those are
  already in place and re-applying them is harmless.
- Scenes are numbers: 3.2.3 has no `SCENE_*` constants.
- `money_hint` is the total: 3000 at the start, plus winnings from
  main-path battles and gifts, minus tolls. Shopping is ignored, so it's on
  the high side. Winnings use the battle code's rule: 4 × the class's base
  reward × the level of the trainer's last Pokémon.
- `party_hint` is invented but plausible: the Chikorita line plus Pokémon
  that can be caught early (Pidgey on Route 29, Mareep and Wooper on
  Route 32), the Togepi from the egg, and the red Gyarados (level 35) from
  the Lake of Rage. Levels are set a little above each checkpoint's key
  opponent. In C03 the Togepi is still an **egg** (it needs about 2560
  steps), listed as `{ "TOGEPI", 1 }`. The Gyarados is the red form in the
  real game.

## Choices made on the main path

- Chikorita; the rival takes Cyndaquil; Lyra takes Totodile.
- Mom's "save money?" call: **no** (so `ENGINE_MOM_SAVING_MONEY` stays clear).
- Sudowoodo is knocked out, not caught, so the Hall of Fame puts it back
  (C11 clears `EVENT_ROUTE_36_SUDOWOODO`).
- The red Gyarados is caught, so it's in the party. No other legendary is caught.
- Optional things are left out: Master Ball from Elm, Dratini from the
  Dragon Shrine, the Cianwood Suicune scene, Bug Contest, item balls,
  hidden items, day-of-week NPCs, phone rematches.
- The Kurt's Apricorn Box gift in C03 is included (it's part of Kurt's
  house events).

## What a save needs that isn't a flag

These aren't in the Lua file because they aren't flags, items or scenes,
but a save builder may want them:

- **Respawn point:** entering a Pokémon Center sets it to the town outside
  (`engine/overworld/warp_connection.asm:262-283`), so a checkpoint standing
  in a Pokémon Center already has the right respawn town. C01's is set to
  Cherrygrove by `blackoutmod` (`maps/MrPokemonsHouse.asm:46`). C11's is
  New Bark (`maps/HallOfFame.asm:90`).
- **Pending phone call** (`wSpecialPhoneCallID`): none at the end of C01–C10
  (the aide call and Pryce's "weird broadcast" call ring on the first step
  outside the gym). At **C11** Elm's S.S. Ticket call is pending
  (`maps/HallOfFame.asm:86`), and it rings on the first step in New Bark.
- Player and rival names, the Pokédex seen/caught lists, the Pokémon
  themselves (moves, items: the starter holds an Oran Berry), the
  variable sprites from `InitialVariableSpritesAndMapScenes`, and the time
  of day and day of week (several NPCs depend on them).

## Biggest uncertainties

1. **Forced trainers** (see Method). A few route choices change which
   trainers are fought: Route 35 direct vs. the National Park (C05), Radio
   Tower 2F grunt M6 vs. M5 and the Underground entrance (C10), the Rocket
   hideout trap room (C08), the Ice Path boulders (C09).
2. **Walking instead of flying.** Some traces say "fly to …" for travel
   over maps that were already visited. On foot the flags are the same;
   the extra trainers met on foot (Route 45, Route 1) were found when the
   story steps were traced and are included.
3. **Money** is a rough upper estimate (see Conventions).
4. **Kanto (C12)** has the most freedom in order; see its notes.
5. Flags that reset daily or weekly (`ENGINE_RED_IN_MOUNT_SILVER`,
   `ENGINE_INDIGO_PLATEAU_LYRA_FIGHT`) are listed as set, as they are just
   after the event; the game clears them later.

## The checkpoints at a glance

In list order. Flag columns are set / cleared. "Received" counts key items, TMs/HMs and items. The last column is the lead Pokémon of `party_hint`.

| id | at | key opponent (top level) | events | engine | scenes | received | money | lead |
|---|---|---|---|---|---|---|---|---|
| C01_STARTER | ELMS_LAB (4,10) | RIVAL0 (5) | +187 / −5 | +8 / −0 | 9 | 1 | 3600 | CHIKORITA 7 |
| C02_ZEPHYR | VIOLET_POKECENTER_1F (5,6) | FALKNER (13) | +19 / −2 | +3 / −0 | 4 | 3 | 5900 | CHIKORITA 14 |
| C03_HIVE | AZALEA_POKECENTER_1F (5,6) | BUGSY (17) | +23 / −5 | +3 / −0 | 3 | 2 | 10400 | BAYLEEF 18 |
| C04_PLAIN | GOLDENROD_POKECOM_CENTER_1F (6,14) | WHITNEY (21) | +16 / −2 | +3 / −0 | 3 | 2 | 15000 | BAYLEEF 23 |
| C05_FOG | ECRUTEAK_POKECENTER_1F (5,6) | MORTY (26) | +22 / −2 | +2 / −0 | 5 | 2 | 22900 | BAYLEEF 28 |
| C06_STORM | CIANWOOD_POKECENTER_1F (5,6) | CHUCK (31) | +18 / −0 | +3 / −0 | 1 | 3 | 41400 | MEGANIUM 33 |
| C07_MINERAL | OLIVINE_POKECENTER_1F (5,6) | JASMINE (37) | +7 / −2 | +1 / −0 | 1 | 1 | 45100 | MEGANIUM 37 |
| C08_GLACIER | MAHOGANY_POKECENTER_1F (5,6) | PRYCE (42) | +43 / −3 | +4 / −1 | 4 | 4 | 60600 | MEGANIUM 42 |
| C10_TOWER | GOLDENROD_POKECOM_CENTER_1F (6,14) | ARCHER (44) | +34 / −6 | +0 / −2 | 3 | 3 | 107900 | MEGANIUM 45 |
| C09_RISING | BLACKTHORN_POKECENTER_1F (5,6) | CLAIR (47) | +18 / −6 | +2 / −0 | 2 | 2 | 120400 | MEGANIUM 48 |
| C11_CHAMPION | NEW_BARK_TOWN (15,6) | LANCE (60) | +22 / −7 | +2 / −0 | 11 | 0 | 161200 | MEGANIUM 60 |
| C12_KANTO | VIRIDIAN_POKECENTER_1F (5,6) | BLUE (70) | +97 / −8 | +21 / −0 | 3 | 10 | 191700 | MEGANIUM 72 |
| C13_POSTGAME | SILVER_CAVE_POKECENTER_1F (5,6) | RED (90) | +9 / −1 | +3 / −0 | 0 | 2 | 253100 | MEGANIUM 90 |

## Trace notes per checkpoint

Written while tracing each stretch; the `unsure` lists in `story_presets.lua` repeat the open questions.

### C01_STARTER: Got Chikorita, Mystery Egg errand, rival in Cherrygrove, back to Elm

**Changed when combining the checkpoints** (these override the trace notes below):

- `money_earned_estimate` set to 600
- money: the helper's estimate of 3600 included START_MONEY 3000; the builder adds the 3000 itself, so C01 counts only the 600 won (Lyra 300 + rival 300).


#### Route traced (female, Chikorita, first time through)
1. **New game** (engine/menus/intro_menu.asm): NewGame -> ResetWRAM_NotPlus (money = START_MONEY 3000, Mom's money 0) -> ResetWRAM (wPlayerGender defaults to PLAYER_FEMALE at :170-171, empty lists, rival/backup name "???", trendy phrase "Prism", Mom item trigger 2300, InitDecorations: wDecoBed = DECO_FEATHERY_BED, wDecoPoster = DECO_TOWN_MAP) -> SetInitialOptions (options menu only, no flags) -> ProfElmSpeech (InitGender, NamePlayer) -> InitializeWorld -> InitializeEvents. No starting PC or bag items. Spawn: SPAWN_HOME = PLAYERS_HOUSE_2F (3,3).
2. **InitializeEvents** (engine/events/initialize_events.asm): sets every `dw EVENT_*` in InitialEvents (lines 2-178), ENGINE_ROCKET_SIGNAL_ON_CH20 and ENGINE_ROCKETS_IN_MAHOGANY (182-183), and scene bytes GOLDENROD_CITY=1, BATTLE_TOWER_OUTSIDE=1, BELLCHIME_TRAIL=1 (194-196). EVENT_AZALEA_TOWN_KURT appears twice (106 and 107); it is listed once, citing 106.
   - Variable sprites (188-193, not recorded in the JSON): SPRITE_FUCHSIA_GYM_1..4 -> SPRITE_JANINE, SPRITE_COPYCAT -> SPRITE_LASS, SPRITE_JANINE_IMPERSONATOR -> SPRITE_CUTE_GIRL.
3. **PlayersHouse2F**: the NEWMAP callback sets EVENT_TEMPORARY_UNTIL_MAP_RELOAD_8 (:27), and ResetOWMapState clears it on the next warp, so it is left out. The radio (EVENT_LISTENED_TO_INITIAL_RADIO) and journal (ENGINE_READ_PROF_ELM_JOURNAL) are optional and left out.
4. **PlayersHouse1F**: the Mom coord trigger is forced (checked with the collision grid: every way out of the stairs area crosses (9,1)/(9,2)/(10,4)/(11,4)). givespecialitem POKEGEAR (:69) only shows the item; the real state is ENGINE_POKEGEAR (:70) + ENGINE_PHONE_CARD (:71). Also PHONE_MOM (:72), setscene 1 (:73), EVENT_PLAYERS_HOUSE_MOM_1 set (:74), EVENT_PLAYERS_HOUSE_MOM_2 cleared (:75). The day-of-week and DST prompts change wDST and the clock, not flags. Running Shoes have no flag in Polished.
5. **NewBarkTown**: ENGINE_FLYPOINT_NEW_BARK (:43). The clearevent EVENT_FIRST_TIME_BANKING_WITH_MOM at :44 is a no-op here. Lyra intro at (6,4): appear (:77) and then disappear (:92) of Lyra, so EVENT_LYRA_NEW_BARK_TOWN ends set, as InitializeEvents left it. setscene $2 (:93).
6. **ElmsLab** (collision grid checked: y=6 and y=7 are walkable only at x=4,5):
   - Scene 0 autowalk; setscene $1 (:122).
   - Chikorita ball: disappear POKE_BALL3 (:288) sets EVENT_CHIKORITA_POKEBALL_IN_ELMS_LAB (object :51). setevent EVENT_GOT_CHIKORITA_FROM_ELM (:289). givepoke CHIKORITA L5 holding ORAN_BERRY (:293). Lyra takes Totodile: disappear POKE_BALL2 (:299) sets EVENT_TOTODILE_POKEBALL_IN_ELMS_LAB (object :50).
   - ElmDirectionsScript: PHONE_ELM (:318), EVENT_GOT_A_POKEMON_FROM_ELM (:329), EVENT_RIVAL_CHERRYGROVE_CITY (:330, already set by init), setscene $6 (:331).
   - Lyra ends at (5,5), so leaving must cross (4,6): LyraBattleScript, LYRA1_3 = TOTODILE L5 (parties.asm:1414). disappear Lyra (:623) sets EVENT_LYRA_IN_ELMS_LAB (object :53). setscene $5 (:625).
   - Aide trigger at (4,8)/(5,8): verbosegiveitem POTION (:647), setscene $2 (:648).
7. **Route29**: no scene or coord event at scene 0. The OBJECTS callback hides Tuscany (sets EVENT_ROUTE_29_TUSCANY_OF_TUESDAY) on every entry. It is a day-of-week NPC, so it is left out.
8. **CherrygroveCity**: ENGINE_FLYPOINT_CHERRYGROVE (:38). The guide gent trigger at (33,7) is forced: the east entrance is 2 tiles wide (y=6,7) and the gent stands on (32,6). givespecialitem MAP_CARD (:70) + ENGINE_MAP_CARD (:71). disappear gramps (:82) sets EVENT_GUIDE_GENT_IN_HIS_HOUSE (object :26). clearevent EVENT_GUIDE_GENT_VISIBLE_IN_CHERRYGROVE (:83). setscene $2 (:84).
9. **Route30**: no callbacks or coord events. Joey's scripted battle (EVENT_ROUTE_30_BATTLE still clear) blocks the 1-wide west lane at x=5, y=24-26, so the player takes the east grass lane. Mikey (range 1, faces the Pidgey) and Don (1,7) are off that lane, so they are optional.
10. **MrPokemonsHouse** (scene 0, sdefer): verbosegivekeyitem MYSTERY_EGG (:44), EVENT_GOT_MYSTERY_EGG_FROM_MR_POKEMON (:45), blackoutmod CHERRYGROVE_CITY (:46).
    - Oak: disappear Pokedex object (:102) sets EVENT_GOT_POKEDEX_FROM_OAK (object :24). givespecialitem POKEDEX (:107) + ENGINE_POKEDEX (:108). disappear Oak (:115) sets EVENT_MR_POKEMONS_HOUSE_OAK (object :23). HealParty.
    - Then: EVENT_RIVAL_NEW_BARK_TOWN (:129), EVENT_PLAYERS_HOUSE_1F_NEIGHBOR (:130), clear EVENT_PLAYERS_NEIGHBORS_HOUSE_NEIGHBOR (:131), setscene $1 (:132), CHERRYGROVE_CITY scene 1 (:133), ELMS_LAB scene 3 (:134), specialphonecall SPECIALCALL_ROBBED (:135), clear EVENT_COP_IN_ELMS_LAB (:136), and the Chikorita branch sets EVENT_CYNDAQUIL_POKEBALL_IN_ELMS_LAB (:149).
11. **Elm's call**: SpecialCallOnlyWhenOutside, checked by CountStep, so it fires on the first step on Route 30. ElmPhoneScript2 .disaster sets EVENT_ELM_CALLED_ABOUT_STOLEN_POKEMON (engine/phone/scripts/elm.asm:274).
12. **Cherrygrove rival** (scene 1, (33,6)/(33,7), forced when going east): appear (:95) clears EVENT_RIVAL_CHERRYGROVE_CITY. Chikorita branch `loadtrainer RIVAL0, 2` (:127): RATTATA 4, CYNDAQUIL 5 @ ORAN_BERRY (parties.asm:1080-1082, the only variant; no FAITHFUL split). Then setevent (:131), disappear (:146), HealParty, setscene $2 (:148).
13. **ElmsLab return** (scene 3, cop trigger at y=5, forced):
    - Lyra: disappear (:669), appear (:671), disappear (:692). SpecialNameRival (:680). Cop: disappear (:686) sets EVENT_COP_IN_ELMS_LAB again. setscene $2 (:693).
    - ElmAfterTheftScript: takekeyitem MYSTERY_EGG (:366), EVENT_GAVE_MYSTERY_EGG_TO_ELM (:375), clear EVENT_LYRA_ROUTE_29 (:376), ROUTE_29 scene 1 (:377), clear EVENT_ROUTE_30_YOUNGSTER_JOEY (:378), EVENT_ROUTE_30_BATTLE (:379), setscene $2 (:380).
    - Elm tells the player to talk to Mom and suggests the Violet Gym. The player walks out and the checkpoint ends.

#### Decisions
- **InitialEvents flags cleared on the path go in `events_clear` and not in `events_set`**: EVENT_PLAYERS_HOUSE_MOM_2, EVENT_GUIDE_GENT_VISIBLE_IN_CHERRYGROVE, EVENT_PLAYERS_NEIGHBORS_HOUSE_NEIGHBOR, EVENT_LYRA_ROUTE_29, EVENT_ROUTE_30_YOUNGSTER_JOEY.
- **InitialEvents flags that are cleared and later set again** end set, so they cite their initialize_events.asm line:
  - EVENT_COP_IN_ELMS_LAB: MrPokemonsHouse:136 clears it, ElmsLab:686 sets it again.
  - EVENT_RIVAL_CHERRYGROVE_CITY: Cherrygrove:95 clears it, :131 and :146 set it again.
  - EVENT_LYRA_NEW_BARK_TOWN: NewBarkTown:77 clears it, :92 sets it again.
- **Object flags changed by appear/disappear** cite the object_event line that names the flag; the disappear line numbers are in the route above. Script_disappear sets the object's flag and Script_appear clears it (engine/overworld/scripting.asm:1059-1095).
- **MYSTERY_EGG** is received (MrPokemonsHouse:44) and taken back (ElmsLab:366) inside C01, so it is in neither list.
- **POKEGEAR, MAP_CARD and POKEDEX** are special items (givespecialitem, display only). They are recorded as ENGINE_POKEGEAR, ENGINE_MAP_CARD and ENGINE_POKEDEX, not as key_items: their constants are special-item indexes, not key item ids.
- **Pokedex source**: Prof. Oak gives it at Mr. Pokemon's house, not Elm. Elm only reacts to it (ElmAfterTheftText5).
- **Poke Balls**: none are given in C01. The aide gives none in 3.2.3; Lyra's Route 29 tutorial (C02) gives 5 POKE_BALL.
- **Mom's savings talk** is not forced; it comes after the checkpoint (BOUNDARY in `unsure`).
- **`at` = ELMS_LAB (4,10)**, one tile north of the entrance warp (4,11).
  - Floor tile. At lab scene 2 there is no coord event on it and no object stands there (the aide at (2,9) only spins; Lyra and the cop are hidden).
  - The healing machine is nearby, and the player has just finished the post-egg talk here.
  - Alternative: NEW_BARK_TOWN (6,4), just outside the door; the scene-0 Lyra trigger there is inactive at scene 2.
- **Money**: payout = base reward x last mon level x 4 (engine/battle/core.asm payout loop with c=4; read_trainer_attributes.asm ComputeTrainerReward).
  - Rival0 and Lyra1 both have base 15 (data/trainers/attributes.asm:161-182) and a last mon at L5: 300 + 300.
  - Plus START_MONEY 3000 gives 3600. Mom isn't saving yet, so all of it goes to the wallet.

#### Other non-flag state the robot may need
- wLastSpawnMap = CHERRYGROVE_CITY (blackoutmod).
- Rival name from the naming screen (default "Silver").
- Party: CHIKORITA L5 holding ORAN_BERRY.
- Bag: medicine POTION x1.
- Phone: Mom and Elm.

#### Files read
- data/events/initialize_events.asm, engine/events/initialize_events.asm, engine/menus/intro_menu.asm, engine/menus/init_options.asm, engine/overworld/decorations.asm, engine/overworld/time.asm
- maps/PlayersHouse2F.asm, PlayersHouse1F.asm, NewBarkTown.asm, ElmsLab.asm, Route29.asm, CherrygroveCity.asm, Route30.asm, MrPokemonsHouse.asm, Route31.asm (Mom call only)
- engine/phone/scripts/elm.asm, engine/phone/scripts/mom.asm, engine/phone/phone.asm, data/phone/special_calls.asm
- engine/overworld/scripting.asm (appear/disappear, givespecialitem, blackoutmod), engine/overworld/warp_connection.asm, engine/overworld/events.asm (CountStep)
- engine/events/specials.asm (SpecialNameRival), data/trainers/parties.asm, data/trainers/attributes.asm, engine/battle/core.asm, engine/battle/read_trainer_attributes.asm
- data/maps/scenes.asm, data/maps/spawn_points.asm, constants/*
- Collision checks used maps/*.ablk with data/tilesets/*_collision.asm for ElmsLab, PlayersHouse1F, CherrygroveCity and Route30.

### C02_ZEPHYR: Beat Falkner in Violet City

**Changed when combining the checkpoints** (these override the trace notes below):

- added to `events_clear`: `EVENT_ELMS_AIDE_IN_VIOLET_POKEMON_CENTER` (engine/phone/scripts/elm.asm:280)
- added to `events_set`: `EVENT_ELMS_AIDE_IN_LAB` (engine/phone/scripts/elm.asm:281)
- removed from `engine_set`: `ENGINE_MOM_SAVING_MONEY`
- Elm's aide call: Falkner's script queues specialphonecall SPECIALCALL_ASSISTANT (maps/VioletGym.asm:62) and it rings on the first step outside the gym, before the player reaches the Pokemon Center where this checkpoint stands. So its two flag changes (engine/phone/scripts/elm.asm:280-281) are in C02: the aide is waiting in the Violet Pokemon Center and no call is pending (wSpecialPhoneCallID = SPECIALCALL_NONE).
- Mom: assumed the player does not go home, so Mom's worried call fires on Route 31 (maps/Route31.asm:39); visiting her instead sets the same EVENT_TALKED_TO_MOM_AFTER_MYSTERY_EGG_QUEST. The player answers NO to saving money (engine/phone/scripts/mom.asm:114 clears ENGINE_MOM_SAVING_MONEY, which is already clear), so ENGINE_MOM_SAVING_MONEY stays clear and money_hint is the plain total. Answer YES would set it (mom.asm:108) and send part of each win to Mom.


Start: right after Elm's ElmAfterTheftScript (C01). At that point ROUTE_29 scene = 1, EVENT_LYRA_ROUTE_29 clear, ELMS_LAB scene = 2.
End: Violet Pokemon Center (5,6), one tile north of the entrance mat (warps 5,7 / 6,7). The tile is FLOOR and has no object on it.

#### Route traced
1. New Bark: the NEWMAP callback only re-sets things that are already set/clear. No net change.
2. Route 29: coord event (53,8)/(53,9), scene 1, runs `Route29Tutorial*`. Only x=54..55 rows 8-9 lead west, so it can't be avoided.
   Answer yes. `verbosegiveitem POKE_BALL, 5` (:91), `disappear ROUTE29_LYRA` (:96 -> EVENT_LYRA_ROUTE_29 set), `setscene $0` (:97), EVENT_LEARNED_TO_CATCH_POKEMON (:98).
3. Cherrygrove: its rival fight and guide belong to C01; scene is already 2. Nothing new.
4. Route 30: EVENT_ROUTE_30_BATTLE is set (C01), so Joey's "important battle" objects are hidden. The west passage is now the
   only way north: the cut tree (8,6) cuts off the east half. Youngster Mikey (5,23, facing down, range 1) sees (5,24),
   which you must cross, so he is forced (generictrainer :184). Joey and Don can be avoided.
5. Route 31: MAPCALLBACK_NEWMAP `Route31CheckMomCall` -> `specialphonecall SPECIALCALL_WORRIED` -> MomPhoneLectureScript
   (engine/phone/scripts/mom.asm:135-142): EVENT_TALKED_TO_MOM_AFTER_MYSTERY_EGG_QUEST, ENGINE_MOM_ACTIVE, yes/no
   (yes -> ENGINE_MOM_SAVING_MONEY :108). Cooltrainer Finch (28,7, facing down, range 2) is `trainer 0, 0, EVENT_INTRODUCED_ROUTE_LEADERS`.
   Every westward tile at x=28 (rows 8-9) is in his sight. The seen-trainer script (engine/events/trainer_scripts.asm:9-31)
   runs with class 0: no battle, `trainerflagaction SET_FLAG` sets EVENT_INTRODUCED_ROUTE_LEADERS. Bug Catcher Wade can be avoided.
6. Violet City: `setflag ENGINE_FLYPOINT_VIOLET`. Earl / Type Chart is optional and left out.
7. Violet Gym, first visit: `VioletGymTrigger0` (scene 0) makes the Gym Guy say "Falkner is in Dark Cave" and warps you out. No flags.
8. Sprout Tower (REQUIRED, see below): 1F inner -> 2F(4,4) -> 2F(15,3) -> 1F outer ring -> 1F(0,6) -> 2F(0,6) -> 2F(8,14) -> 3F.
   Forced by line of sight: Sage Chow (1F, 1,5 facing up, range 4, covers (1,1) on the only link to (0,6)), Sage Jin (3F, row 13 gap x7-9)
   and Sage Neal (3F, row 11 x6-8). The 3F rival coord event (9,9) can't be avoided: `disappear` rival (EVENT_RIVAL_SPROUT_TOWER), `setscene $1`.
   Elder Li: loadtrainer ELDER, LI; TM_FLASH (:77), EVENT_GOT_TM70_FLASH (:78), EVENT_BEAT_ELDER_LI (:79).
9. Route 31 -> Dark Cave Violet Entrance (Route31 warp 34,5). Walkable from warp (3,15) to the coord event (6,2) with no HMs:
   up via (5,13)->(5,10)->(3,10) ledge tile->(2,9)...->(3,2). In darkness `checkdarkness` is TRUE, and it continues only because
   EVENT_GOT_TM70_FLASH is set (.ProgressAnyway). Result: Ursaring, Pidgeotto and Falkner all `disappear`, clearevent EVENT_VIOLET_GYM_FALKNER (:54),
   setmapscene VIOLET_GYM $1 (:55), setscene $1 (:56). EVENT_DARK_CAVE_FALKNER also hides Violet Gym's blocking Gym Guy (VioletGym.asm:18).
10. Violet Gym: Falkner (FALKNER, 1). EVENT_BEAT_FALKNER, givebadge ZEPHYRBADGE, Rod/Abe set, setmapscene ELMS_LAB $2 (unchanged),
    specialphonecall SPECIALCALL_ASSISTANT (queued only, see below), TM_ROOST, EVENT_GOT_TM31_ROOST.

#### Answer to the Sprout Tower question
Sprout Tower is required and is included. The gym is locked until the Dark Cave Falkner scene (VIOLET_GYM scene 1 and the Gym Guy hidden
by EVENT_DARK_CAVE_FALKNER). That scene refuses you in darkness unless EVENT_GOT_TM70_FLASH is set (DarkCaveVioletEntrance.asm:59-64).
TM70 is only given by Elder Li. Field Flash also needs TM_FLASH (engine/events/overworld.asm:397), so there is no other way.

#### Elm's aide call (open question when tracing)
The trigger is Falkner's script: `specialphonecall SPECIALCALL_ASSISTANT` (VioletGym.asm:62). In data/phone/special_calls.asm that entry is
SpecialCallOnlyWhenOutside -> ElmPhoneScript2 .assistant (engine/phone/scripts/elm.asm:277-282): clearevent
EVENT_ELMS_AIDE_IN_VIOLET_POKEMON_CENTER, setevent EVENT_ELMS_AIDE_IN_LAB. It rings on the first step in Violet City after leaving the gym.
The aide then waits in the Violet PC, and you have to TALK to him; there is no scene or coord event (VioletPokeCenter1F.asm:44-78).
As instructed, I put the call and the egg in C03. Caveat (BOUNDARY): the call really happens before this checkpoint's PC. A save built
from C02 flags has no aide in the PC and no pending call, which blocks forward play at Route 32. See unsure[0] for the fixes.

#### Files read
maps/ElmsLab, NewBarkTown, Route29, CherrygroveCity, Route30, Route31, VioletCity, VioletGym, SproutTower1F/2F/3F,
DarkCaveVioletEntrance, VioletPokeCenter1F, PlayersHouse1F; engine/phone/scripts/mom.asm, elm.asm; data/phone/special_calls.asm;
engine/overworld/scripting.asm (appear/disappear, checkdarkness, giveegg); engine/events/trainer_scripts.asm; home/trainers.asm;
home/map.asm + engine/overworld/player_movement.asm (side walls, ledges); data/events/initialize_events.asm;
data/trainers/parties.asm + attributes.asm; engine/battle/core.asm + read_trainer_attributes.asm (payout).

#### Method for "forced" trainers
I wrote a small script (scratchpad/work/nav.py) that builds the collision grid from maps/*.ablk + data/tilesets/*_collision.asm. It handles
ledges the Polished way: you stand on the ledge tile and jump 2 tiles. It also handles side walls, NPC tiles as obstacles, and warps.
Then it searches for the smallest set of fixed-facing trainers whose straight sight line (range from the object_event, walls ignored
as in FacingPlayerDistance) has to be crossed. Spinning or wandering trainers count as avoidable.

#### Choices
- Tutorial: yes (the Poke Balls are the same either way).
- Mom: no home visit, so the phone call on Route 31; saving money: YES (typical). NO would give engine_clear/no ENGINE_MOM_SAVING_MONEY.
- `disappear`-set flags are cited at their object_event line (it names the flag). The real setter is the `disappear` line; see JSON unsure.
- ELMS_LAB scene (2 -> 2) is left out because it doesn't change.

#### Money
Payout = base x last-mon level, added 4 times (core.asm loop, c=4). Mikey 16, Chow 24, Jin 56, Neal 48, Li 100, Falkner 325
-> 569 x 4 = 2276. With Mom saving on, 1/4 of each payout goes to Mom (MOM_SAVING_SOME_MONEY_F -> b=1).

#### Key opponent
FALKNER party 1 (data/trainers/parties.asm:84, the only normal party): NATU 10, HOOTHOOT 11, PIDGEOTTO 13.

### C03_HIVE: Clear Slowpoke Well and beat Bugsy in Azalea Town

**Changed when combining the checkpoints** (these override the trace notes below):

- added to `events_set`: `EVENT_ELMS_AIDE_IN_VIOLET_POKEMON_CENTER` (maps/VioletPokeCenter1F.asm:17)
- added to `events_clear`: `EVENT_ELMS_AIDE_IN_LAB` (maps/VioletPokeCenter1F.asm:59)
- Elm's aide: the phone call is booked in C02 (it rings before C02's Pokemon Center). Here the aide hands over the Togepi egg: EVENT_ELMS_AIDE_IN_LAB cleared (maps/VioletPokeCenter1F.asm:59) and the aide leaves (`disappear` at line 76 sets EVENT_ELMS_AIDE_IN_VIOLET_POKEMON_CENTER, cited at its object_event line 17).


Start: right after Falkner's TM (VioletGym.asm:66). Falkner's script has already queued SPECIALCALL_ASSISTANT; as first planned, the
call's effects are booked here.
End: Azalea Pokemon Center (5,6), one tile north of the entrance mat (warps 5,7 / 6,7). Shared JohtoPokeCenter1F layout; the tile is FLOOR and has no object on it.

#### Route traced
1. Violet City: Elm's call rings (SpecialCallOnlyWhenOutside, data/phone/special_calls.asm:13) -> engine/phone/scripts/elm.asm:277-282:
   clearevent EVENT_ELMS_AIDE_IN_VIOLET_POKEMON_CENTER (:280), setevent EVENT_ELMS_AIDE_IN_LAB (:281).
2. Violet PC: talk to the aide (no scene or coord event; VioletPokeCenter1F.asm:44), answer yes: `giveegg TOGEPI` (:56, level
   EGG_LEVEL=1, scripting.asm:2107), EVENT_GOT_TOGEPI_EGG_FROM_ELMS_AIDE (:58), clearevent EVENT_ELMS_AIDE_IN_LAB (:59), clearevent
   EVENT_TOGEPI_HATCHED (:60, already clear), setmapscene ROUTE_32 $1 (:61), `disappear` aide (:76 -> EVENT_ELMS_AIDE_IN_VIOLET_POKEMON_CENTER set).
   Net for both aide flags = start value, so neither is listed.
   The egg is REQUIRED: Route 32 coord (18,8) at scene 0 (Route32CooltrainerMStopsYou, :206) pushes you back without it.
3. Route 32 (enter from Violet's south edge): NEWMAP `setflag ENGINE_FLYPOINT_UNION_CAVE` (:64). The OBJECTS callback toggles Frieda
   by weekday; left out as day-of-week content. Forced Youngster Albert (16,18, facing right, range 3; row 18 x17-19 is the only way
   through), generictrainer :670. Lyra hidden-grotto intro: coord events x10-13 row 24, scene 1, cover the whole row, can't be avoided.
   Lyra `disappear` (:363 -> EVENT_LYRA_ROUTE_32), setscene $2 (:364). Slowpoke Tail coord event (7,71), scene 2, can't be avoided:
   setscene $3 (:420). The yes/no only changes text. Route 32's south edge can't reach Route 33 on foot (TOP_WALL row 86),
   so Union Cave is required.
4. Union Cave 1F, warp 4 (17,15) -> warp 3 (17,43): forced Hiker Daniel (3,18, facing right, range 2, covers (5,18), the only link),
   generictrainer :53. Firebreathers Ray and Bill can be avoided.
5. Route 33: MAPCALLBACK_TILES only (rain). Imogen can be avoided; Anthony is a spinner. -> Azalea Town: `setflag ENGINE_FLYPOINT_AZALEA` (:54).
   The Rocket at (31,9) (EVENT_AZALEA_TOWN_SLOWPOKETAIL_ROCKET) blocks the well door, and the Rocket at (10,16) (EVENT_SLOWPOKE_WELL_ROCKETS)
   blocks the gym door (checked with the pathfinder).
6. Kurt's House: Kurt1 (:56) before the well: setevent EVENT_AZALEA_TOWN_SLOWPOKETAIL_ROCKET (:67). Kurt `disappear`s
   (EVENT_KURTS_HOUSE_KURT_1 set; cleared again at SlowpokeWellB1F.asm:80, so net zero).
7. Slowpoke Well Entrance (Kurt stands there, text only) -> B1F: my path model says all three grunts are forced: M29 (sight covers
   (15,10), the only link), F1 (row 4 x11-14), M2 (row 6 x6-7). Then Proton (trainer PROTON, PROTON2, :52) -> Proton2Script
   (:54-85): disappear Proton and the grunts (EVENT_SLOWPOKE_WELL_ROCKETS), Kurt disappear/appear, EVENT_CLEARED_SLOWPOKE_WELL,
   ILEX_FOREST scene 2, clear EVENT_ILEX_FOREST_APPRENTICE/FARFETCHD (set by InitializeEvents), set EVENT_CHARCOAL_KILN_FARFETCH_D/
   APPRENTICE, set EVENT_SLOWPOKE_WELL_SLOWPOKES and EVENT_SLOWPOKE_WELL_KURT, clear EVENT_AZALEA_TOWN_SLOWPOKES and EVENT_KURTS_HOUSE_SLOWPOKE
   (both init-set), clear EVENT_KURTS_HOUSE_KURT_1, HealParty, warp KURTS_HOUSE 3,3.
8. Kurt's House: the OBJECTS callback swaps Kurt 1 and 2 and the twins with no net change. Talk to Kurt: `verbosegivekeyitem APRICORN_BOX` (:92),
   EVENT_KURT_GAVE_YOU_APRICORN_BOX (:93). This is optional but typical, and included because the tracing brief listed "Kurt's house events".
9. Azalea Gym: Bugsy (BUGSY, 1). EVENT_BEAT_BUGSY (:45), givebadge HIVEBADGE (:47), setmapscene AZALEA_TOWN $1 (:48),
   twins and the 3 bug catchers set (:49-52), TM_U_TURN (:74), EVENT_GOT_TM69_U_TURN (:75). No phone call is queued.
10. Walk to Azalea PC. The pathfinder confirms the gym->PC route never touches the rival coord events (5,10)/(5,11).

#### Rival in Azalea (open question when tracing)
AZALEA_TOWN scene 1 is set by Bugsy. AzaleaTownRivalBattleTrigger1/2 are coord events at (5,10)/(5,11), scene 1, right beside the
Ilex Forest gate (warps 2,10 / 2,11). So the rival fight only happens when you head west toward Ilex Forest after the badge, which makes it C04,
together with EVENT_RIVAL_AZALEA_TOWN (already set by InitializeEvents) and setmapscene ROUTE_34 $1.

#### Elm aide / egg placement (open question when tracing)
How it triggers: Falkner's script queues SPECIALCALL_ASSISTANT. The call rings outside, and then you talk to the aide in the Violet PC.
Both happen after the Zephyr badge, so per the instruction they are here. Their net flag effect is zero. Only
EVENT_GOT_TOGEPI_EGG_FROM_ELMS_AIDE, the Togepi egg and ROUTE_32's scene survive. BOUNDARY caveat: see the JSON unsure[0] and the C02 notes.
The C02 save lacks both the aide and the pending call.

#### Files read
maps/VioletGym, VioletPokeCenter1F, Route32, Route32PokeCenter1F, UnionCave1F, Route33, AzaleaTown, KurtsHouse, SlowpokeWellEntrance,
SlowpokeWellB1F, AzaleaGym, AzaleaPokeCenter1F; engine/phone/scripts/elm.asm; data/phone/special_calls.asm;
data/events/initialize_events.asm; engine/pokemon/breeding.asm and move_mon.asm (Togepi hatch flag, egg cycles);
data/trainers/parties.asm and attributes.asm; engine/battle/core.asm (payout).

#### Choices and uncertainties
- Forced trainers come from my collision + line-of-sight pathfinder (scratchpad/work/nav.py; method in the C02 notes). Spinners
  (Gordon, Larry, Russell, Anthony) count as avoidable.
- EVENT_TOGEPI_HATCHED is not set: Togepi is HATCH_FASTER, so (1+1)*5 = 10 cycles, about 2560 steps. The direct route is far shorter.
- Flags set by `disappear` are cited at their object_event line: EVENT_LYRA_ROUTE_32 at Route32.asm:41, EVENT_SLOWPOKE_WELL_ROCKETS at
  SlowpokeWellB1F.asm:15.
- Money: 4 x base x last level. Albert 40, Daniel 96, M29 100, M2 100, F1 120, Proton 252, Bugsy 425 -> 1133 x 4 = 4532.
  1/4 goes to Mom if she is saving (C02 choice).

#### Key opponent
BUGSY party 1 (data/trainers/parties.asm:116, the only normal party): BUTTERFREE 14, BEEDRILL 14, YANMA 14, SCYTHER 17.

### C04_PLAIN: Beat Whitney in Goldenrod City

**Changed when combining the checkpoints** (these override the trace notes below):

- added to `events_set`: `EVENT_DAYCARE_MON_1` (maps/Route34.asm:69)
- added to `events_set`: `EVENT_DAYCARE_MON_2` (maps/Route34.asm:79)
- EVENT_DAYCARE_MON_1/2: Route 34's callback hides both Day-Care Pokemon when the Day-Care is empty (maps/Route34.asm:69, :79), so they are set on the first visit. Found when tracing story_steps.lua.


Start: right after Bugsy gives TM_U_TURN (AzaleaGym.asm:74-75). End: GOLDENROD_POKECOM_CENTER_1F (6,14),
one step north of the entrance warps (6,15)/(7,15). There is no GOLDENROD_POKECENTER_1F constant.

#### Route traced
1. **Azalea Town.** Bugsy set AZALEA_TOWN scene 1 (AzaleaGym.asm:48, C03). The coord events (5,10)/(5,11) are the only way to the
   west gate (checked on the collision map), so the rival fight is forced. For a Chikorita player this is `loadtrainer RIVAL1, RIVAL1_5`.
   `setevent EVENT_RIVAL_AZALEA_TOWN` then `disappear` leave that flag as InitialEvents set it (no net change).
   The script runs `setmapscene ROUTE_34, $1` and `setscene $0` (AZALEA_TOWN -> 0).
2. **Ilex Forest Azalea Gate.** Only NPC text (the Exp. Share aide is optional).
3. **Ilex Forest.** ILEX_FOREST is at scene 2 (SlowpokeWellB1F.asm:71). The apprentice coord (9,31) is the only way east to the x=10 column.
   IlexForestCharcoalApprenticeScript -> `setscene $0`. Herding the Farfetch'd (WRAM wFarfetchdPosition 1..10): position 9 -> 10 shows the
   Charcoal master, sets EVENT_CHARCOAL_KILN_BOSS and EVENT_HERDED_FARFETCHD. The master gives HM_CUT and EVENT_GOT_HM01_CUT,
   sets FARFETCHD/APPRENTICE/CHARCOAL_MASTER and clears the three CHARCOAL_KILN_* flags.
   Net result: KILN_BOSS unchanged (clear), CHARCOAL_MASTER unchanged (set, InitialEvents).
   Cutting the tree at (10,27) is required: row 27 x=10 is the only link north. `disappear -2` in engine/events/overworld.asm:363
   sets EVENT_ILEX_FOREST_CUT_TREE, and nothing resets cut-tree flags. ENGINE_AUTOCUT_ACTIVE is wOWState, which is cleared on warp.
   The shrine, the Headbutt tutor (Wing Case) and item balls are skipped.
4. **Route 34 Ilex Forest Gate.** The callback only re-applies the initial teacher flags. The coord (4,7) needs EVENT_FOREST_IS_RESTLESS, so it does nothing. False Swipe TM is optional.
5. **Route 34.** The Lyra coord events (8-10,17) at scene 1 are forced (x=11 is a dead end, water on the west).
   Battle: LYRA1, LYRA1_6 (PIDGEY 16, GROWLITHE 17, MAREEP 15, CROCONAW 18; parties.asm:1444). Then `disappear` of the day-care man and
   `setscene $0`, and the player is warped into the Day-Care.
   Route34EggCheckCallback (scene 1 on first entry) first shows the man outside. After returning (scene 0, no egg) it runs
   `clearevent EVENT_DAYCARE_MAN_IN_DAYCARE` / `setevent EVENT_DAYCARE_MAN_ON_ROUTE_34` (:53-54), so the final state is ON_ROUTE_34 set and IN_DAYCARE clear.
   All Route 34 trainers can be avoided (grid search with fixed trainer sight lines).
6. **Day-Care.** Scene 0 runs DayCare_MeetGrandma: `addcellnum PHONE_LYRA` (:65), `disappear DAYCARE_LYRA` (sets EVENT_LYRA_DAYCARE, :77), `setscene $1` (:78).
   The Odd Egg (day-care man inside) is optional and skipped.
7. **Goldenrod City.** Fly point (:74). The move tutor callback needs EVENT_BEAT_WHITNEY and COIN_CASE, so the tutor stays hidden (no change).
   **The Radio Card quiz is required.** The lass at GoldenrodCity.asm:54 stands on (28,8), the only access tile to the gym door (28,7),
   while EVENT_GOLDENROD_GYM_WHITNEY is clear ("Whitney bolted out to get a Radio Card").
   Radio Tower 1F (coord (9,15), scene 1 pan-up, then scene 0; on return the step-down script sets scene 1 again): the quiz answers are Y,Y,N,N,N.
   `givespecialitem RADIO_CARD` is cosmetic. `setflag ENGINE_RADIO_CARD` (:161). Whitney walks off and `disappear RADIOTOWER1F_WHITNEY` (:172)
   sets EVENT_GOLDENROD_GYM_WHITNEY, which also hides the gym-door lass.
8. **Goldenrod Gym.** WHITNEY 1: setevent BEAT_WHITNEY + MADE_WHITNEY_CRY, scene 1, four gym trainer flags (:38-44).
   Whitney's area has one exit, (8,5), which is the WhitneyCriesScript coord: scene 0, clear MADE_WHITNEY_CRY.
   Talking again runs `givebadge PLAINBADGE` (:59), TM_ATTRACT (:63) and EVENT_GOT_TM45_ATTRACT (:64).
   Net: GOLDENROD_GYM scene 0 -> 1 -> 0, not listed.
9. Walk to the PokeCom Center (no scenes; nurse healing and Wonder Trade are optional).

#### Opponents (normal build)
- Azalea rival RIVAL1_5 (parties.asm:1111): GASTLY 14, ZUBAT 16, GEODUDE 15, QUILAVA 18.
- Whitney 1 (parties.asm:155): CLEFAIRY 19, TEDDIURSA 20, MUNCHLAX 19, MILTANK 21.
- Money: payout = 4 x base x level of last mon (ComputeTrainerReward, then the 4-pass loop in core.asm).
  Rival 1440 + Lyra 1080 + Whitney 2100 = 4620.

#### Choices / uncertainties
- Net-unchanged flags and scenes are left out (listed in the JSON `unsure`).
- Flags set through `disappear` cite the object_event line that contains the flag name.
- ILEX_FOREST scene and the CHARCOAL_KILN reversals assume C03 recorded the SlowpokeWellB1F.asm:71-75 changes.
- Bike Shop, Bill's house, Dept Store, Game Corner, Camper Todd's phone number and the False Swipe TM are optional and skipped.

#### Files read
maps/AzaleaGym, AzaleaTown, IlexForestAzaleaGate, IlexForest, Route34IlexForestGate, Route34, DayCare, GoldenrodCity,
RadioTower1F, GoldenrodGym, GoldenrodPokecomCenter1F, PlayersHouse2F (debug hints only); data/events/initialize_events.asm;
engine/events/overworld.asm (cut), engine/overworld/scripting.asm (givebadge/givespecialitem), warp_connection.asm (wOWState reset),
home/trainers.asm (sight), engine/battle/core.asm and read_trainer_attributes.asm (money), data/trainers/parties.asm and attributes.asm.
Walkability was checked with a small script that renders maps/*.ablk against data/tilesets/*_collision.asm.

### C05_FOG: Beat Morty in Ecruteak City


Start: right after Whitney's TM_ATTRACT (GoldenrodGym.asm:63-64). End: ECRUTEAK_POKECENTER_1F (5,6), one step north of
the entrance warps (5,7)/(6,7).

#### Route traced
1. **Goldenrod Flower Shop.** The teacher checks EVENT_FOUGHT_SUDOWOODO (clear), then EVENT_FLORIA_AT_SUDOWOODO. That flag is set by
   InitialEvents and never cleared in 3.2.3, so the script takes the .MetFloria branch. With PLAINBADGE and no SquirtBottle yet,
   it runs `verbosegivekeyitem SQUIRTBOTTLE` (:49) and `setevent EVENT_GOT_SQUIRTBOTTLE` (:50). Floria stays hidden (EVENT_FLORIA_AT_FLOWER_SHOP set).
2. **Route 35 Goldenrod Gate** has no scenes, coords or callbacks. The NE Goldenrod strip that also connects to Route 35 is a walled pocket
   (x=17-23, rows 33-35), so the gate is the only way onto Route 35.
3. **Route 35.** The south part reaches rows 8-9 only through the gap (7,10)/(8,10) between spinners Walt and Irwin, which are left out.
   From rows 8-9, the top column is reached only by crossing x=20 at rows 8-10, which Bug Catcher Arnie (20,7, facing down, sight 3) sees.
   So he is forced: `trainer ... EVENT_BEAT_BUG_CATCHER_ARNIE` (:130). His after-script uses `endifjustbattled`, so no phone prompt.
   The Cut tree at (21,6) is the only tile north (x=20 is a headbutt tree), so EVENT_ROUTE_35_CUT_TREE is set by cutting it.
   Alternative: going through the National Park (Route35NationalParkGate -> NationalPark -> Route36NationalParkGate) avoids both,
   and I found no fixed-facing forced trainers there. The direct route was chosen; see the JSON `unsure`.
4. **Route 36.** The south strip (rows 14-15) -> (39,10) -> Sudowoodo at (39,9). That tile is the only link to the Route 37 area
   (the NP-gate pocket x=22-26 is walled off by headbutt trees at x=27). Psychic Mark and Schoolboy Alan can be avoided by walking row 15.
   SudowoodoScript: SquirtBottle "yes", wild SUDOWOODO 20 (BATTLETYPE_TRAP), `setevent EVENT_FOUGHT_SUDOWOODO` (:97),
   `disappear` (sets EVENT_ROUTE_36_SUDOWOODO). Assumed KO'd, so no ENGINE_PLAYER_CAUGHT_SUDOWOODO. No Lyra or Floria event on Route 36.
   The Arthur day-of-week callback is ignored.
5. **Route 37.** The ledges at row 6 leave only (6,6)/(7,6) going north. Beauty Callie (4,6, facing right, sight 3) and Beauty Cassandra (9,6, facing left, sight 3)
   both see those two tiles. PlayerEvents re-checks trainers every frame, so both battles are forced (Route37.asm:96, :103).
   The east side (Psychic Greg, apricorn trees) is a dead-end pocket. The Sunny day-of-week callback is ignored.
6. **Ecruteak City.** `setflag ENGINE_FLYPOINT_ECRUTEAK` (:56). No coord events. Bill (Eevee) in the PokeCenter and the Dance Theater / Surf are optional.
   Ecruteak Gym at scene 0 is blocked: EcruteakGymClosed has the Gramps walk you out (no flags). It needs ECRUTEAK_GYM scene 1 and
   EVENT_ECRUTEAK_GYM_GRAMPS, both set in Burned Tower B1F.
7. **Burned Tower 1F.** The scene 0 Eusine intro sets `setscene $1` (:55).
   Hex Maniac Tamara (1,1, facing right, sight 2) is forced: from the entrance the middle area is reached only via row 1 through (3,1).
   Firebreather Ned can be avoided. This was checked after applying the callback block changes ($32 at (8,8) before the hole, $9 at (4,14): no ladder before release).
   The rival coord (9,9) runs `loadtrainer RIVAL1, RIVAL1_8` (Chikorita branch), then `setscene $2` (:102),
   `setevent EVENT_RIVAL_BURNED_TOWER` (:103) and `setevent EVENT_HOLE_IN_BURNED_TOWER` (:117). The player falls to B1F.
8. **Burned Tower B1F.** The coord (10,6) runs ReleaseTheBeasts. It is forced because the ladder block only appears afterwards.
   - The walking beasts appear and then disappear, so BEASTS_1 is unchanged. The still beasts' `disappear` sets EVENT_BURNED_TOWER_B1F_BEASTS_2.
   - It runs `setevent EVENT_RELEASED_THE_BEASTS` and `special InitRoamMons` (WRAM only).
   - It sets ECRUTEAK_GYM and CIANWOOD_CITY to scene 1.
   - It clears EVENT_SAW_SUICUNE_AT_CIANWOOD_CITY and EVENT_ECRUTEAK_CITY_GRAMPS (both set by InitialEvents).
   - It sets EVENT_ECRUTEAK_GYM_GRAMPS, EVENT_BURNED_TOWER_MORTY and EVENT_BURNED_TOWER_1F_EUSINE, appears Eusine, and runs `setscene $1` (:107).
   Eusine stands on (10,12), the only tile toward the ladder at (7,15), so talking to him is forced. He disappears, which leaves
   EVENT_EUSINE_IN_BURNED_TOWER set, as in InitialEvents. Climb the ladder and leave. The TM Flame Charge ball and the Strength boulder are optional.
9. **Ecruteak Gym** (scene 1, no script). MORTY 1 -> EVENT_BEAT_MORTY (:76), `givebadge FOGBADGE` (:78),
   ECRUTEAK_HOUSE scene 1 (:79), RANG_CLEAR_BELL_1 (:80, already set by InitialEvents, not listed), RANG_CLEAR_BELL_2 (:81),
   four gym trainer flags (:85-88), TM_SHADOW_BALL (:91), EVENT_GOT_TM30_SHADOW_BALL (:92).
10. Walk to the Ecruteak PokeCenter (no scenes or callbacks).

#### Opponents (default, non-FAITHFUL build)
- Burned Tower rival RIVAL1_8 (parties.asm:1151): HAUNTER 20, MAGNEMITE 18, DROWZEE 19, ZUBAT 20, QUILAVA 22.
- Morty 1 (parties.asm:192): HAUNTER 24, NOCTOWL 24, MISDREAVUS 25, GENGAR 26. The FAITHFUL build has HAUNTER 24 instead of NOCTOWL.
- Forced side trainers: Arnie (VENONAT 16), Callie and Cassandra (CLEFABLE 16, WIGGLYTUFF 16), Tamara (GASTLY 16, MISDREAVUS 18).
- Money (4 x base x last level): 256 + 1280 + 1280 + 1760 + 720 + 2600 = 7896.

#### Choices / uncertainties
- The route choice on Route 35 (direct vs National Park) decides Arnie and the Route 35 Cut tree.
- Sudowoodo is KO'd, not caught.
- Flags set by `disappear` cite the object line that names the flag.
- Spinner trainers are never counted as forced.

#### Files read
maps/GoldenrodFlowerShop, Route35GoldenrodGate, Route35, Route35NationalParkGate, NationalPark (headers/objects),
Route36NationalParkGate, Route36, Route37, EcruteakCity, EcruteakGym, BurnedTower1F, BurnedTowerB1F, EcruteakPokeCenter1F;
engine/events/specials.asm (RespawnOneOffs), engine/overworld/wildmons.asm (InitRoamMons), home/trainers.asm,
engine/overworld/events.asm (PlayerEvents), data/trainers/parties.asm and attributes.asm, data/events/initialize_events.asm.

### C06_STORM: Get Surf, meet Jasmine at the Lighthouse, beat Chuck in Cianwood City

**Changed when combining the checkpoints** (these override the trace notes below):

- removed from `events_set`: `EVENT_EUSINE_IN_BURNED_TOWER`


Start: right after Morty gives TM30 (maps/EcruteakGym.asm). End: right after Chuck gives TM01, standing in CIANWOOD_POKECENTER_1F at (5,6), one step north of the (5,7) mat.

#### Route traced
1. **Dance Theatre (Ecruteak):** 5 Kimono Girls (all `trainer`/`generictrainer`, range 0, so the player talks to them). `DanceTheaterSurfGuy` checks all 5 flags, then gives HM_SURF and sets EVENT_GOT_HM03_SURF (:113-114). HM Surf is given only here in 3.2.3.
2. **Route 38 gate, Route 38:** no callbacks. The only trainers near the path spin with range 1-2 (Lass Dana, Bird Keeper, Beauties), and there are two ways west (via the grass north of Dana, or south through the x8-9 grass column). Nothing is forced.
3. **Route 39:** no callbacks. Pokefan M Derek (10,36), facing up, range 4, sees (10,32)-(10,35). The only way south is (8,36)/(9,36), and every path from the x12-15 corridor to it crosses column 10 in rows 32-35, so he is **forced**. His after-script runs right away, but with no Pikachu it only shows text.
4. **Olivine City:** NEWMAP gives ENGINE_FLYPOINT_OLIVINE. `coord_event 33,23` (scene 0) is the only tile leading to the Lighthouse door, so the rival cutscene is forced and ends with `setscene $1` (:101). The Gym-door coord (10,8) does the same thing (:81) if the player visits the Gym first.
5. **Olivine Lighthouse:** I drew each floor from .ablk + data/tilesets/lighthouse_collision.asm (the 16,x warps are HOLEs, so they only go down). The only way up is: 1F ladder (3,11) -> 2F ladder (5,3) -> 3F ladder (13,3) -> 4F hole (8,3) -> 3F ladder (9,5) -> 4F ladder (9,7) -> 5F ladder (9,15) -> 6F.
   - 2F Gentleman Alfred (17,8, left, range 3): row 8 of the only corridor is x14-16, all in his sight. **Forced.**
   - 3F Gentleman Preston (13,5, right, range 4): from row 6 to row 4 the player must cross row 5 at x14-17, all in his sight. **Forced.**
   - 4F Lass Connie (11,2, down, range 1): (11,3) is the only link between x>=12 and the (8-9,3) holes. **Forced.**
   - Avoidable: 2F Huey (use row 2), 3F Theo (use column 2), 3F Terrell (drop through (8,3), not (9,3)), 4F Kent. 5F Ernest spins in the middle of the ladder room, so a player is likely but not certain to fight him. Left out.
   - 6F Jasmine: first talk sets EVENT_JASMINE_EXPLAINED_AMPHYS_SICKNESS (:33). No SecretPotion yet.
6. **Route 40, Route 41 (Surf):** open water, swimmers avoidable, no scripts. Route 40's OBJECTS callback toggles Monica by weekday, which is not a story change.
7. **Cianwood City:** NEWMAP gives ENGINE_FLYPOINT_CIANWOOD and `setevent EVENT_EUSINE_IN_BURNED_TOWER`. EVENT_BEAT_EUSINE is not set, so Eusine stays visible. The Suicune/Eusine coord (11,16) (scene 1, set in C05 by BurnedTowerB1F) is in the north part of town, which the Gym, Pokemon Center, Pharmacy and Cliff Edge Gate routes never touch. It is NOT triggered, so CIANWOOD_CITY scene stays 1, Suicune stays visible, and there is no Eusine battle.
8. **Cianwood Pokemon Center:** the Gym Guy gives HM_STRENGTH the first time he is talked to (:58-59). It is **needed**: in CianwoodGym, row 5 is open only at x4 (plus Lung's tile) and row 6 x3-5 is reached only through the boulder row (3-5,7), so Strength must push a boulder up. Strength checks the Plain Badge (engine/events/overworld.asm:1208).
9. **Cianwood Gym:** Yoshi and Lao (range 3, facing each other, row 12, only way through is x4/5), Nob (range 2, covers (4,9),(5,9)) and Lung (range 1, covers (4,5)) are all forced. The Chuck script also runs `setevent` on all four (:59-62), and those are the lines cited. Chuck: EVENT_BEAT_CHUCK :52, `givebadge STORMBADGE` :54, `specialphonecall SPECIALCALL_YELLOWFOREST` :55 (a Lyra call, no flag), TM_DYNAMICPUNCH :65, EVENT_GOT_TM01_DYNAMICPUNCH :66. Chuck's `disappear CIANWOODGYM_BOULDER1` has no flag, because strengthboulder_event uses -1.

#### Choices / boundary
- Surf is placed in C06 as the tracing brief asked. It could have happened in C05 (BOUNDARY in `unsure`).
- EVENT_EUSINE_IN_BURNED_TOWER is included even though C05 may already have set it. Setting it again changes nothing.
- The trainers listed are the ones that are forced by layout (sight lines checked on the drawn collision maps). The tracing brief called the lighthouse trainers optional, but three of them physically block the only way up.
- Money: 4 x base x last-mon level (the core.asm payout loop adds the reward 4 times). Bases are from data/trainers/attributes.asm: Kimono 20, Pokefan M 15, Gentleman 16, Lass 15, Blackbelt T 6, Chuck 25.

#### HM FLY: not included. The tracing brief asked for it, but it is not "right there"
Chuck's wife (CianwoodCity.asm:106-109) only talks. `verbosegivetmhm HM_FLY` exists only at maps/YellowForest.asm:148 (the Walker). Getting there is an optional Team Rocket side quest. Lyra's post-Chuck call only hints at it ("Team Rocket was up to something there"). It goes through the Cliff Edge Gate (the Rocket at CianwoodCity (4,26) is hidden by EVENT_BEAT_CHUCK) -> Route 47 (bridges and several grunts) -> Cliff Cave -> Route 48 -> Yellow Forest. If the lead wants Fly, this is what I found, **not fully traced** (Route 47 / Cliff Cave blocking not checked):
- Likely forced: EVENT_BEAT_ROCKET_GRUNTM_12 (CliffEdgeGate.asm:46; he stands at (17,16) facing the entrance, range 3).
- ENGINE_FLYPOINT_YELLOW_FOREST (Route48.asm:31 and YellowForest.asm:54).
- Jessie & James coord battle: EVENT_ROUTE_48_JESSIE / EVENT_ROUTE_48_JAMES (Route48.asm:51-52), ROUTE_48 scene 1 (:59).
- Archer (on the tile in front of the Yellow Forest Gate door): EVENT_BEAT_ARCHER_2 (Route48.asm:80), EVENT_CLEARED_YELLOW_FOREST set (:89), EVENT_YELLOW_FOREST_ROCKET_TAKEOVER cleared (:90).
- Walker: EVENT_BEAT_WALKER (YellowForest.asm:144), HM_FLY (:148), EVENT_GOT_HM02_FLY (:149), EVENT_YELLOW_FOREST_WALKER set by `disappear` (:165, flag bound at :32).
- Plus whichever Route 47 / Cliff Cave grunts block the way (GruntF6, GruntM23, GruntM26, GruntM22). These are not analysed.
I can trace it fully as a separate segment if wanted.

#### Files read
maps/: EcruteakGym, EcruteakCity, DanceTheatre, Route38EcruteakGate, Route38, Route39, Route39Barn, Route39Farmhouse, OlivineCity, OlivineGym, OlivineLighthouse1F-6F, OlivinePokeCenter1F, OlivinePort, Route40, Route41, CianwoodCity, CianwoodPokeCenter1F, CianwoodGym, CianwoodPharmacy, BurnedTowerB1F, Route36, Route42, CliffEdgeGate, Route47, Route48, CliffCave, YellowForestGate, YellowForest.
Also: engine/overworld/scripting.asm (appear/disappear, givebadge, specialphonecall), engine/events/trainer_scripts.asm, engine/phone/scripts/lyra.asm, engine/battle/core.asm + read_trainer_attributes.asm (payout), data/trainers/{attributes,parties}.asm, data/events/initialize_events.asm, data/maps/{maps,attributes,blocks}.asm, constants/*, data/tilesets/*_collision.asm (map drawing).

### C07_MINERAL: Bring the SecretPotion to Amphy and beat Jasmine in Olivine City


Start: right after Chuck gives TM01 (C06 end, Cianwood Pokemon Center). There is no Fly (see C06 notes). End: right after Jasmine gives TM23, standing in OLIVINE_POKECENTER_1F at (5,6), one step north of the (5,7) mat.

#### Route traced
1. **Cianwood Pharmacy:** `CianwoodPharmacist` gives the item when EVENT_GOT_SECRETPOTION_FROM_PHARMACY is clear AND EVENT_JASMINE_EXPLAINED_AMPHYS_SICKNESS is set (from C06, Lighthouse 6F :33). `verbosegivekeyitem SECRETPOTION` :29, `setevent EVENT_GOT_SECRETPOTION_FROM_PHARMACY` :30. The SecretPotion cannot be got before meeting Jasmine, so the whole medicine quest is in C07, as the tracing brief asked.
2. **Route 41 -> Route 40 (Surf) -> Olivine City:** no scripts. The OLIVINE_CITY scene is already 1, so the rival does not appear.
3. **Olivine Lighthouse 1F->6F:** same route as C06 (ladders (3,11), (5,3), (13,3), hole 4F (8,3), ladders (9,5), (9,7), (9,15)). Alfred, Preston and Connie are already beaten. Ernest on 5F is optional.
4. **Lighthouse 6F, Jasmine** (`OlivineLighthouseJasmine`): `checkkeyitem SECRETPOTION` is true, so `yesorno` -> YES. Then `takekeyitem SECRETPOTION` :43, `setevent EVENT_JASMINE_RETURNED_TO_GYM` :65, `clearevent EVENT_OLIVINE_GYM_JASMINE` :66, and `disappear OLIVINELIGHTHOUSE6F_JASMINE` (:71, player facing up; :76 or :81 for other facings). That disappear sets her hide flag EVENT_OLIVINE_LIGHTHOUSE_JASMINE. The same flag hides Preston (3F) and Connie (4F) in the Lighthouse. It is not in initialize_events.asm, so it goes from clear to set.
5. **Olivine Gym:** the Gym is now filled (Jasmine, Preston and Connie are hidden by EVENT_OLIVINE_GYM_JASMINE, now clear). I drew the layout (TILESET_CHAMPIONS_ROOM collision):
   - Preston (3,10), facing right, range 2, covers (4,10) and (5,10). Row 9 is open only at x4-5, so he is forced.
   - Connie (6,7), facing left, range 2, covers (4,7) and (5,7). Rows 5-6 are open only at x4-5, so she is forced.
   - Both are `trainer 0, 0, EVENT_SPOKE_TO_...`: SeenByTrainerScript -> CheckTrainerClass is 0 -> no battle -> `trainerflagaction SET_FLAG`.
6. **Jasmine** (`OlivineGymJasmineScript`): `setevent EVENT_BEAT_JASMINE` :34, `givebadge MINERALBADGE, JOHTO_REGION` :36 (ENGINE_MINERALBADGE, same order in constants/ram_constants.asm and engine_flags.asm), `clearevent EVENT_GOLDENROD_CITY_ROCKET_TAKEOVER` :37 (this flag is set at init, data/events/initialize_events.asm:5, so this really clears it), `setmapscene ROUTE_42, $1` :38 (arms the Route 42 Lyra battle / HM Whirlpool coord events for C08), `verbosegivetmhm TM_IRON_TAIL` :44, `setevent EVENT_GOT_TM23_IRON_TAIL` :45.
7. Walk out to the Olivine Pokemon Center. The OlivineCity TILES callback only changes blocks at night once Jasmine has returned. No flags.

#### Items
- SECRETPOTION: received and taken back inside C07, so it is in neither list.
- TM_IRON_TAIL: kept.

#### Choices / uncertainties
- For EVENT_OLIVINE_LIGHTHOUSE_JASMINE the src points at the object_event line (:16), which names the flag. The line that actually changes it is the `disappear` at :71. The lead may prefer :71.
- The Olivine Gym Guy, the Olivine Pokemon Center Beauty Charlotte and the Pokemon Journal are optional and left out.
- Money: only Jasmine, 4 x 25 x 37 = 3700.
- Party: def_trainer 1 "Jasmine" (data/trainers/parties.asm:305): Skarmory 34, Magneton 33, Forretress 34, Scizor 33, Steelix 37 (Leftovers).

#### Files read
maps/CianwoodPharmacy.asm, OlivineLighthouse1F-6F.asm, OlivineGym.asm, OlivineCity.asm, OlivinePokeCenter1F.asm, Route40.asm, Route41.asm, Route42.asm, GoldenrodCity.asm (what the Rocket-takeover flag hides); engine/events/trainer_scripts.asm; engine/overworld/scripting.asm; data/events/initialize_events.asm; data/trainers/{attributes,parties}.asm; constants/{event_flags,engine_flags,ram_constants,item_constants,tmhm_constants,map_constants}.asm.

### C08_GLACIER: Lake of Rage, Mahogany Rocket hideout, beat Pryce in Mahogany Town


Segment: from right after Jasmine's TM (Olivine Gym) to Mahogany PokeCenter after Pryce's TM.
Source: polishedcrystal v3.2.3.

#### Route traced
1. Olivine -> Route 39 -> Ecruteak -> Route42EcruteakGate: no scripts. The Route 42 officers are hidden by EVENT_BEAT_JASMINE.
2. Route 42 (maps/Route42.asm): ROUTE_42 is at scene 1 (Jasmine, OlivineGym.asm:38). Coord events at x=12, y=6..9 and at (10,6).
   A BFS over the collision map shows every way east (Surf, or the Mt. Mortar west door) steps on one of them.
   Lyra battle (LYRA1_9, Chikorita branch), then `verbosegivetmhm HM_WHIRLPOOL` (:128) and EVENT_GOT_HM05_WHIRLPOOL (:129).
   In Polished, Whirlpool comes from Lyra, not Lance.
   Scene: EVENT_SAW_SUICUNE_ON_ROUTE_42 is still set from InitialEvents, so `setscene $0` runs (:140). This is a BOUNDARY item: see unsure.
   EVENT_LYRA_ROUTE_42 is set, then appear/setevent/disappear, then set again, so there is no net change.
   The Suicune coord (24,14) sits behind a Cut tree, so it is optional.
3. Mahogany Town: NEWMAP fly point (:33). The Rage Candy Bar coord events are on the east edge (19,8/9), so they are not on the path.
   The gym door (6,13) is blocked by a fisher until EVENT_MAHOGANY_TOWN_POKEFAN_M_BLOCKS_GYM is set.
4. Route 43 -> Route43Gate: the scene-0 toll takes 1000 and sets the gate scene to 1.
   Route43.asm's NEWMAP callback sets ROUTE_43_GATE back to 0 on the next Route 43 entry, so the scene has no net change.
   The bypass path west of the gate forces the Sr&Jr twins (BFS), so the gate route is taken.
5. Lake of Rage: fly point (:53). The red Gyarados is a wild battle, and on WIN `disappear` sets EVENT_LAKE_OF_RAGE_RED_GYARADOS (:243).
   givekeyitem RED_SCALE (:247). `appear` Lance, answer YES (:128-137): EVENT_DECIDED_TO_HELP_LANCE is set,
   EVENT_MAHOGANY_MART_LANCE_AND_DRAGONITE is cleared, and MAHOGANY_MART_1F goes to scene 1.
   Lance's `disappear` re-sets EVENT_LAKE_OF_RAGE_LANCE (no net change).
6. MahoganyMart1F scene 1: Lance uncovers the stairs and sets EVENT_UNCOVERED_STAIRCASE_IN_MAHOGANY_MART (:83).
   Lance and Dragonite disappear (their flag is set again) and `setscene $0` runs. Mart scene and Lance flag: no net change.
7. TeamRocketBaseB1F: the OBJECTS callback `disappear`s the security grunt, which sets EVENT_TEAM_ROCKET_BASE_SECURITY_GRUNTS.
   Camera 1 (24,2/24,3) is unavoidable: GRUNTM 20 and GRUNTM 21.
   The route goes (9,4) -> row 9 -> (19,8) -> camera 3 -> (26,8) -> bottom corridor -> cameras 4 and 5 -> ladder (3,14). It skips the trap room and Grunt M16.
   The Persian-statue switch (19,11) turns the cameras off; it is optional.
8. B2F: coord (5,14)/(4,13) is forced, so Lance heals: EVENT_LANCE_HEALED_YOU_IN_TEAM_ROCKET_BASE, scene 1.
   Grunt M19 (21,14, facing left, range 4) covers every tile from row 14 to 15 (BFS), so he is forced. Go to B3F via (27,14).
9. B3F: scene-0 Lance password talk (disappear sets EVENT_TEAM_ROCKET_BASE_B3F_LANCE_PASSWORDS, scene 1).
   Grunt F5 and Grunt M28: battle each, talk again for the password flag.
   B3F (27,2) -> B2F row 1 -> B2F (3,2) -> B3F left part. Rival coord (8,10) is forced: he shoves you, no battle, scene 2.
   EVENT_RIVAL_TEAM_ROCKET_BASE has no net change. Office door (both passwords). Petrel PETREL2, scene 3.
   Petrel's object flag is set. Murkrow gives EVENT_LEARNED_HAIL_GIOVANNI.
10. B2F: the door (EVENT_OPENED_DOOR_TO_ROCKET_HIDEOUT_TRANSMITTER) leads to coord (14/15,11), scene 1: the Ariana ARIANA2 battle.
    The B2F_ARIANA, B2F_PETREL and B2F_DRAGONITE flags end set as they started. EVENT_BEAT_ARIANA_2 is set.
    The `disappear` of ROCKET1-3 sets EVENT_TEAM_ROCKET_BASE_POPULATION (hides every grunt and the Mahogany Mart fake clerks). Scene 2.
    Three Electrode wild battles; each `disappear` sets ELECTRODE_n. RocketBaseElectrodeScript (:292-321) does the following:
    TM_THIEF, EVENT_CLEARED_ROCKET_HIDEOUT, clearflag ENGINE_ROCKET_SIGNAL_ON_CH20 (set by InitialEngineFlags), gate rockets gone,
    gym fisher gone, scene 3, Lake of Rage civilians back, all cameras off. EVENT_TEAM_ROCKET_BASE_B2F_LANCE ends set (Lance's final disappear).
11. MahoganyGym: Pryce (trainer 1), GLACIERBADGE, then the takeover block (:41-49): ENGINE_ROCKETS_IN_RADIO_TOWER, CIVILIANS, BLACKBELT,
    clear RADIO_TOWER_ROCKET_TAKEOVER and USED_THE_CARD_KEY (both set by InitialEvents), SPECIALCALL_WEIRDBROADCAST, merchant hidden,
    and Mahogany scene 1. The 5 gym trainer flags and TM_AVALANCHE follow.
    The weird-broadcast call is ElmPhoneScript2 `.rocket` (engine/phone/scripts/elm.asm), which only resets the call ID: no flags.
12. Mahogany PokeCenter: entrance warps (5,7)/(6,7), so "at" is (5,6), a floor tile (JohtoPokeCenter1F blocks).

#### Method notes
- appear/disappear change the object's event flag (engine/overworld/scripting.asm:1059-1095).
  For those flags the src is the object_event line that names the flag; the actual disappear lines are listed in unsure.
- Forced trainers were decided with a BFS over the .ablk collision maps plus trainer sight lines (no line-of-sight blocking, as in the engine).
  Spinning trainers count as random and are left out.
- Money: 4 x base reward x last-mon level (engine/battle/core.asm; the reward is added 4 times). 17476 - 2 x 1000 toll = 15476
  (walking back south through the gate re-armed by Route43.asm:44; flying back saves one toll).

#### Files read
maps/OlivineGym, Route42, Route42EcruteakGate, EcruteakCity, Route39, CianwoodCity, MahoganyTown, Route43MahoganyGate, Route43, Route43Gate,
LakeOfRage, MahoganyMart1F, TeamRocketBaseB1F/B2F/B3F, MahoganyGym, MahoganyPokeCenter1F, MountMortar1FOutside;
data/events/initialize_events.asm, data/trainers/parties.asm + attributes.asm, data/maps/scenes.asm, data/phone/special_calls.asm,
engine/phone/scripts/elm.asm, engine/battle/core.asm, engine/battle/read_trainer_attributes.asm, engine/overworld/scripting.asm.

#### Uncertainties (also in JSON unsure)
- ROUTE_42 scene 0 vs 2 depends on whether C06 triggered the optional Cianwood Suicune event.
- EVENT_GOLDENROD_CITY_ROCKET_SCOUT: the clearevent at MahoganyGym:44 changes nothing (it was never set), so it is omitted.
- B1F route: the trap room / Grunt M16 route instead would add EVENT_BEAT_ROCKET_GRUNTM_16 and path-dependent EVENT_EXPLODING_TRAP_n.
- Random or avoidable: B2F Grunt M18 (spins, by the (3,2) ladder), Grunt M17, Scientists Jed/Ross/Mitch. Red Gyarados caught or KO'd: same flags.

### C10_TOWER: Clear the Team Rocket takeover of the Goldenrod Radio Tower


Segment: from right after Pryce's TM (Mahogany) to Goldenrod's PokeCom Center after the Radio Tower is cleared.
Source: polishedcrystal v3.2.3. The executives are Petrel (fake director, 5F), Proton (4F), Ariana (5F) and Archer (last, 5F).

#### Route traced
1. Walk Mahogany -> Route 42 -> Ecruteak -> Routes 37/36/35 -> Goldenrod (no active coord scripts; or fly). GoldenrodCity: the scene-1 coord (9,15) pan-up script sets scene 0 and warps into RADIO_TOWER_1F.
   Leaving the tower, the scene-0 trigger sets it back to 1. Net: unchanged (1, from InitialVariableSpritesAndMapScenes).
2. RadioTower1F: Grunt M3 (14,1, facing down, range 3) covers rows 2-4, the only rows east to the stairs, so he is forced.
3. 2F: stairs (0,0). The Black Belt at (0,1) is hidden (EVENT_RADIO_TOWER_BLACKBELT_BLOCKS_STAIRS set by Pryce).
   Forced: Grunt F2 and Grunt M4. One of M5/M6 is also forced; I chose M6 on the direct row-2 route.
4. 3F first pass: Scientist Marc (x=9, facing up, range 5) and Grunt M7 (whose sight covers (7,1) under the 4F stairs) are forced.
   Grunt M8 is avoidable along row 7.
5. 4F first pass: Scientist Rich covers row 2, x=0-3, the only way to the 5F stairs at (0,0). Grunt M10 spins, so he is random.
6. 5F: coord (0,3), scene 0 (FakeDirectorScript). `disappear` director, `appear` Petrel, setscene 1, PETREL1 battle,
   BASEMENT_KEY (:60), EVENT_BEAT_PETREL_1 (:62).
7. Goldenrod north Underground entrance (13,5) -> switch-room entrance building (20,27) -> stairs (21,23) -> WAREHOUSE_ENTRANCE (1,2).
   Pokemaniac Donald (0,6, facing right) covers the only way down from rows 1-5. Super Nerd Teru (4,9, facing up) covers (4,7), which every entrance passes.
   Basement door (16,6) sets EVENT_USED_BASEMENT_KEY (:388) and warps to (27,23). Then (28,19) -> switch room (23,3).
   The NEWMAP switch reset changes nothing (the flags are already clear). The day-of-week OBJECTS callback is ignored.
8. UndergroundPathSwitchRoomEntrances: rival coord (19,4)/(19,5) is forced (BFS). RIVAL1_11 for Chikorita, setscene 1 (:150).
   EVENT_RIVAL_UNDERGROUND_PATH: set -> appear -> setevent -> disappear, so no net change.
   EVENT_RIVAL_BURNED_TOWER was already set in C05, so the setmapscene BURNED_TOWER_1F branch is skipped.
   Door 16 (the only way to the warehouse door) opens only at position 6 (switches 1+2+3) or with the Emergency switch, which sits inside the target area.
   A BFS over switch states and door blocks gives 6 forced trainers: Grunts M13, M11, M25, F3 and Burglars Duncan, Orson.
   An example order is S1, S2, S1 off, S3, S1.
9. UndergroundWarehouse: NEWMAP clears every EVENT_SWITCH_* and the Emergency switch, so they end clear (no net change).
   Grunts M15 (covers the right column at row 3), M24 (covers x=9, rows 5-7) and M14 (covers x=8, rows 12-14) are all forced (BFS).
   The director gives CARD_KEY (:81) and sets EVENT_RECEIVED_CARD_KEY. It also sets LAYOUT_1 (already set) and clears LAYOUT_2/3 (already clear).
10. Warehouse door (17,2) -> GoldenrodDeptStoreB1F. With the Card Key, changeblock 16,4 opens the path; layout 1 opens 10,8.
    NEWMAP clears EVENT_WAREHOUSE_BLOCKED_OFF (set by InitialEvents).
    Elevator B1F -> 1F: moving floors returns TRUE (Script_elevator), so the layout rotates (.BoxLayout1): LAYOUT_1 cleared, LAYOUT_2 set.
11. Back to the Radio Tower. 3F: the Card Key slot (read from 14,3) sets EVENT_USED_THE_CARD_KEY_IN_THE_RADIO_TOWER (Pryce had cleared it).
    The shutter opens x=14-15 on rows 3-5 only. Grunt M9 (16,6, facing up, range 3) covers x=16 on rows 3-5, so he is forced. Stairs (17,0) -> 4F.
12. 4F: Proton (14,1, facing left, range 2) sees (12,1) below the 5F stairs, so he is forced. 5F: Ariana (17,2) sees (16,2), the only way down, so she is forced.
    Coord (16,5), scene 1: Archer ARCHER1.
    Then :98-127 run: tower cleared, CLEAR_BELL, RADIO_TOWER_5F scene 2, ECRUTEAK_HOUSE scene 0 (Morty had set 1), EVENT_TEAM_ROCKET_DISBANDED.
    Blackthorn: BLOCKS_GYM is set and DOES_NOT_BLOCK_GYM cleared, which swaps which Dragon Tamer object is shown.
    Director appear/disappear: EVENT_RADIO_TOWER_DIRECTOR ends clear (as at start). EVENT_RADIO_TOWER_PETREL ends set (as at start).
13. Walk out through the tower (every Rocket is now hidden by EVENT_RADIO_TOWER_ROCKET_TAKEOVER) into GOLDENROD_POKECOM_CENTER_1F.
    Entrance warps (6,15)/(7,15), so "at" is (6,14).

#### Key opponent / rival
- Archer ARCHER1 (parties.asm:6672): HOUNDOUR 41, RATICATE 43, GENGAR 41, WEEZING 42, HOUNDOOM 44.
- Underground rival RIVAL1_11 (parties.asm:1205; loaded at UndergroundPathSwitchRoomEntrances.asm:207 for Chikorita):
  GOLBAT 40, MAGNETON 39, HAUNTER 39, SNEASEL 41, TYPHLOSION 43.
- The other executives: Petrel PETREL1 (lv 39-41), Proton PROTON1 (39-41), Ariana ARIANA1 (40-42).

#### Money (4 x base x last level)
Grunts, base 10: M3 1320, F2 1400, M4 1360, M6 1360, M7 1360, M13 1480, M11 1440, M25 1400, F3 1400, M24 1440, M14 1400, M15 1400, M9 1440.
Scientists, base 25: Marc 3500, Rich 3500. Petrel1 2808, Proton1 2952, Ariana1 3024, Archer1 3168 (base 18). Rival 3440 (base 20).
Burglars Duncan and Orson 2720 each (base 20). Donald 676 and Teru 572 (base 13). Total 47280.

#### Files read
maps/GoldenrodCity, RadioTower1F-5F, WarehouseEntrance, UndergroundPathSwitchRoomEntrances, UndergroundWarehouse,
GoldenrodDeptStoreB1F, GoldenrodDeptStoreElevator, GoldenrodDeptStore1F, GoldenrodPokecomCenter1F, EcruteakHouse, EcruteakGym,
BlackthornCity (flag objects), BurnedTower1F; data/events/initialize_events.asm; data/trainers/parties.asm + attributes.asm;
engine/overworld/scripting.asm (appear/disappear/elevator/startbattle); engine/events/elevator.asm.

#### Uncertainties (also in JSON unsure)
- The map constant GOLDENROD_POKECENTER_1F does not exist, so GOLDENROD_POKECOM_CENTER_1F is used.
- Route choices: 2F M6 vs M5. Underground entrance north (Donald) vs south (Eric) vs east (Clara). Teru may already be set by C04.
- Exit after the Card Key: I assumed Dept Store + elevator. The Emergency-switch exit back through the switch room would leave different
  warehouse and switch flags (details in unsure).
- 3F Grunt M8, 4F Grunt M10 (spinning) and Grunt F4 are optional or random, so they are left out.

### C09_RISING: Beat Clair and pass the Dragon's Den test in Blackthorn City

**Changed when combining the checkpoints** (these override the trace notes below):

- added to `events_set`: `EVENT_BEAT_SKIER_MARIA` (maps/IcePath1F.asm:24)
- added to `events_set`: `EVENT_BEAT_SKIER_BECKY` (maps/IcePathB1F.asm:85)
- added to `events_set`: `EVENT_BEAT_DRAGON_TAMER_DARIN` (maps/DragonsDenB1F.asm:248)
- `money_earned_estimate` set to 12524
- Fly: HM_FLY is only given in Yellow Forest (maps/YellowForest.asm:148) at the end of an optional side quest, so the main-path player walks or surfs. Where the traced path says 'fly to', walking over already-visited maps gives the same flags.
- Forced battles found when tracing story_steps.lua with trainer sight lines: Skier Maria (Ice Path 1F), Skier Becky (Ice Path B1F) and Dragon Tamer Darin (Dragon's Den B1F) can't be avoided on the main path. Added with their prize money (+7824).


Start: right after C10 (RadioTower5F.asm director gives CLEAR_BELL; that script already set
EVENT_BLACKTHORN_CITY_DRAGON_TAMER_BLOCKS_GYM and cleared ..._DOES_NOT_BLOCK_GYM, lines 108-109).
End: Blackthorn Pokemon Center after Clair's TM. `at` = BLACKTHORN_POKECENTER_1F (5,6), one step
north of the entrance warp (5,7).

#### Route traced
1. Fly to Mahogany. The east exit is open: MahoganyGym.asm:48-49 (C08) hid the Rage Candy Bar
   merchant and set MAHOGANY_TOWN scene 1, so the coord events at (19,8)/(19,9) (scene 0) don't fire.
2. Route 44: no callbacks or scene scripts. Ice Path has no callbacks except B1F's stonetable.
   - 1F: `tmhmball_event 31, 7, HM_WATERFALL, EVENT_GOT_HM06_WATERFALL` (IcePath1F.asm:19).
     Picking it up runs FindTMHMInBallScript (engine/events/itemball.asm:66), which gives the HM;
     `disappear LAST_TALKED` then sets the object flag. This is the ONLY HM_WATERFALL in the game
     (grep), and C11 needs it for Tohjo Falls (TryWaterfallOW also checks ENGINE_RISINGBADGE,
     engine/events/overworld.asm:904-909). It is not physically blocking (my 1F reachability sim),
     but it is next to the route (30,7).
   - B1F: four Strength boulders. The stonetable (IcePathB1F.asm:40-68) runs `disappear BOULDERn`
     (sets EVENT_BOULDER_IN_ICE_PATH_n) and `clearevent EVENT_BOULDER_IN_ICE_PATH_nA` (shows the
     boulder on B2F Mahogany side). I rendered the .ablk + ice_path collision and simulated ice
     sliding. B2F's ladder island (9,11) can only be reached from the B1F ladder arrival (17,1)
     when all 4 boulders sit on B2F as stoppers (the ICE_STONE ball on the island at (8,9) also
     blocks). Using the B1F holes, boulder 2 alone would do. Listed all 4 (intended solution).
   - B3F (Lorelei is optional; the smash rock at (6,6) does not block), B2F Blackthorn side,
     B1F lower, 1F (37,13) -> exit (36,27): all reachable without anything else.
3. Blackthorn City: NEWMAP callback `setflag ENGINE_FLYPOINT_BLACKTHORN` (line 45). The Santos
   OBJECTS callback is day-of-week only, so I ignored it. Dragon Tamer (18,12) is hidden since C10.
4. Blackthorn Gym. The 2F stonetable disappears boulder 1/2/3 (sets EVENT_BOULDER_IN_BLACKTHORN_GYM_n),
   and the 1F TILES callback changeblocks (8,2), (2,4), (8,6). Simulation: Clair's platform needs
   boulders 1 and 3; boulder 2 is optional (and 2F can drop 1+3 without 2). Clair: `loadtrainer
   CLAIR, 1` (BlackthornGym1F.asm:63). After the win: EVENT_BEAT_CLAIR, the 5 gym trainers,
   `clearevent EVENT_MAHOGANY_MART_OWNERS` (already clear since C10, so no net change), gramps swap.
   No badge and no TM in the gym.
5. Dragon's Den 1F -> B1F. The B1F NEWMAP callback hides the rival (EVENT_BEAT_RIVAL_IN_MT_MOON
   is clear), which re-sets the init-set EVENT_RIVAL_DRAGONS_DEN: no change. No rival fight in C09.
6. Dragon Shrine scene 0 -> `sdefer DragonShrineTestScript` (DragonShrine.asm:26). Answer
   correctly (wrong answers just repeat the question and set ..._QUIZ_WRONG). Passed:
   `givebadge RISINGBADGE, JOHTO_REGION` (148) = ENGINE_RISINGBADGE (Script_givebadge adds the
   badge index to ENGINE_BADGES), `specialphonecall SPECIALCALL_MASTERBALL` (150, WRAM only),
   `setscene $1` (151, DRAGON_SHRINE), `setmapscene DRAGONS_DEN_B1F, $1` (152). The Clair object's
   appear/disappear leaves EVENT_DRAGON_SHRINE_CLAIR set, the same as its init: no change.
   EVENT_TEMPORARY_UNTIL_MAP_RELOAD_* are reset on map load (constants/event_flags.asm:5).
7. Leaving the shrine you land on the door (19,29); the only exit is (19,30) = coord_event scene 1
   (DragonsDenB1F.asm:12). Clair: `verbosegivetmhm TM_DRAGON_PULSE` (72),
   `setevent EVENT_GOT_TM59_DRAGON_PULSE` (73), `setscene $0` (84, back to 0),
   `setmapscene NEW_BARK_TOWN, $1` (85, arms Lyra's farewell battle in C11),
   `clearevent EVENT_LYRA_IN_HER_ROOM` (86; init-set, initialize_events.asm:18).
   EVENT_DRAGONS_DEN_CLAIR ends set, the same as its init: no change.
8. Back to the Pokemon Center (no scripts there; the Clair journal flag is optional).

#### Optional things left out
Dratini from the Elder (needs a map reload; EVENT_GOT_DRATINI, givepoke DRATINI 15 at
DragonShrine.asm:187/190), Master Ball from Elm, Dragon's Den / Ice Path / Route 44 trainers and
items, Lorelei (Ice Path B3F), Kimono Girl Mina.

#### Money
Payout = base reward x level of the last mon x 4 (read_trainer_attributes.asm ComputeTrainerReward
plus the 4-pass add loop in engine/battle/core.asm). Clair base 25 (attributes.asm:67), Kingdra 47
-> 25*47*4 = 4700.

#### Key opponent
CLAIR 1 (parties.asm:391, non-FAITHFUL): Gyarados 43, Yanmega 45, Ampharos 44, Dragonair 44,
Kingdra 47. FAITHFUL: Dragonair 44 instead of Ampharos.

#### Files read
maps/RadioTower5F, MahoganyTown, MahoganyGym, Route44, IcePath1F/B1F/B2FMahoganySide/B3F/
B2FBlackthornSide, BlackthornCity, BlackthornGym1F/2F, DragonsDen1F/B1F, DragonShrine,
BlackthornPokeCenter1F, ElmsLab, LyrasHouse2F, NewBarkTown; engine/events/itemball.asm,
engine/overworld/scripting.asm (givebadge, disappear), player_movement.asm (ice),
engine/phone/scripts/elm.asm, data/events/initialize_events.asm, data/trainers/*.
Map geometry: the .ablk files rendered through data/tilesets/*_collision.asm (my own scripts).

### C11_CHAMPION: Beat the Elite Four and Champion Lance, back in New Bark after the credits

**Changed when combining the checkpoints** (these override the trace notes below):

- added to `events_clear`: `EVENT_ROUTE_36_SUDOWOODO` (engine/events/specials.asm:368)
- added to `events_set`: `EVENT_BEAT_HIKER_ERIK` (maps/Route45.asm:245)
- added to `events_set`: `EVENT_BEAT_COOLTRAINERF_BETH` (maps/Route26.asm:145)
- added to `events_set`: `EVENT_BETH_ASKED_FOR_PHONE_NUMBER` (maps/Route26.asm:158)
- added to `events_set`: `EVENT_BEAT_VETERANM_MATT` (maps/VictoryRoad1F.asm:21)
- `money_earned_estimate` set to 40824
- EVENT_ROUTE_36_SUDOWOODO: the Hall of Fame runs RespawnOneOffs (engine/events/specials.asm:340), which puts Sudowoodo back on Route 36 unless ENGINE_PLAYER_CAUGHT_SUDOWOODO is set. C05 assumes Sudowoodo was knocked out, not caught, so it is cleared here. If the save should have caught it instead, drop this clear and set ENGINE_PLAYER_CAUGHT_SUDOWOODO in C05.
- Fly: HM_FLY is only given in Yellow Forest (maps/YellowForest.asm:148) at the end of an optional side quest, so the main-path player walks or surfs. Where the traced path says 'fly to', walking over already-visited maps gives the same flags.
- Forced battles found when tracing story_steps.lua with trainer sight lines: Hiker Erik (Route 45, on the walk Blackthorn -> Route 45 -> Route 46; either Erik or Cooltrainer Ryan is forced), Cooltrainer Beth (Route 26; answer NO to her phone number, which sets EVENT_BETH_ASKED_FOR_PHONE_NUMBER) and Veteran Matt (Victory Road 1F). Added with their prize money (+6484).


Start: right after C09 (Clair's TM_DRAGON_PULSE in Dragon's Den, Blackthorn Pokemon Center).
C09 left NEW_BARK_TOWN at scene 1 (DragonsDenB1F.asm:85) and HM_WATERFALL in the bag.
End: after the credits, on Continue. `at` = NEW_BARK_TOWN (15,6).

#### Route traced
1. Fly to New Bark (NEWMAP: ENGINE_FLYPOINT_NEW_BARK already set; clears
   EVENT_FIRST_TIME_BANKING_WITH_MOM, assumed already clear). Elm's Master Ball (ElmsLab.asm:143-146,
   409-411) is optional: you have to walk into the lab and talk to Elm.
2. New Bark east shore: the water (18-19, 6-9) touches land only at (17, 6-9), which are scene-1
   coord events (NewBarkTown.asm:18-21). Lyra's farewell: `setevent EVENT_LYRA_NEW_BARK_TOWN` (122;
   the flag is init-set, so no change), `loadtrainer LYRA1, LYRA1_12` (137, Chikorita), then `setscene $2` (147).
3. Route 27: coord events (18,10)/(19,10) scene 0, the only landing from the western water
   (flood-fill check, whirlpools counted as passable) -> `setscene $1` (Route27.asm:54).
   Tohjo Falls: 13,15 -> Surf, climb the falls (Waterfall + Rising Badge) -> 25,15 -> Route 27 east.
4. Route 26 (trainers optional) -> POKEMON_LEAGUE_GATE: coord events (10/11,10) in the 2-wide
   neck (rows 8-11) -> `setscene $1` (PokemonLeagueGate.asm:37).
5. Route 23: 8 badge officers with sequential scene checks 0..7. Flood fill with each check's row
   blocked: every one is unavoidable. Final `setscene $8` (Route23.asm:233). The heal officer is optional.
6. Victory Road 1F/3F: generic trainers only. VR 2F coord (25,9) scene 0 = the exit to north
   Route 23. Rival: `loadtrainer RIVAL1, RIVAL1_14` (VictoryRoad2F.asm:64), `setscene $1` (76).
   EVENT_RIVAL_VICTORY_ROAD is init-set, then appear/setevent/disappear, so no change.
7. Indigo Plateau: `setflag ENGINE_FLYPOINT_INDIGO_PLATEAU` (IndigoPlateau.asm:19).
   Pokecenter NEWMAP `PrepareEliteFourCallback`: E4 scenes 0 and room flags / EVENT_BEAT_ELITE_4_* /
   EVENT_BEAT_CHAMPION_LANCE cleared, EVENT_LANCES_ROOM_OAK_AND_MARY set (all already in that
   state). Coord events (14/15,4): no fight, because EVENT_BEAT_RIVAL_IN_MT_MOON and
   EVENT_BEAT_ELITE_FOUR_AGAIN are clear.
8. Each E4 room: scene script (entrance closes, `setscene $1`, ENTRANCE_CLOSED), leader
   `loadtrainer X, 1` (VAR_BADGES = 8, not 16), EXIT_OPEN + EVENT_BEAT_ELITE_4_X.
9. Lance's room: entrance scene (42-43), coord (6/7,5) -> `loadtrainer CHAMPION, LANCE` (79),
   `setevent EVENT_BEAT_CHAMPION_LANCE` (96), `appear LANCESROOM_MARY/OAK` (108, clears
   EVENT_LANCES_ROOM_OAK_AND_MARY), then `warpfacing UP, HALL_OF_FAME, 4, 13`.
10. HallOfFame.asm scene script: EVENT_DECO_SILVER_TROPHY (45), `setscene $1` (69),
    EVENT_BEAT_ELITE_FOUR (77), EVENT_RIVAL_SPROUT_TOWER (78, already set), Olivine port sprite swap
    (79-80), `special RespawnOneOffs` (81), `setmapscene SPROUT_TOWER_3F, $1` (82, already 1),
    HealParty, `specialphonecall SPECIALCALL_SSTICKET` + EVENT_BATTLE_TOWER_OPEN set /
    EVENT_BATTLE_TOWER_CLOSED cleared (86-88, EVENT_GOT_SS_TICKET_FROM_ELM clear),
    `blackoutmod NEW_BARK_TOWN` (90), `halloffame` (91).
11. RespawnOneOffs (engine/events/specials.asm:340-470): on the main path, with no legendary
    caught, it clears the init-set EVENT_WHIRL_ISLAND_LUGIA_CHAMBER_LUGIA (440),
    EVENT_TIN_TOWER_ROOF_HO_OH (447) and EVENT_EUSINES_HOUSE_EUSINE (449). The other resets touch
    flags that are clear on the main path. EVENT_ROUTE_36_SUDOWOODO (368) is conditional (see unsure).
12. `halloffame` = Script_halloffame -> HallOfFame (engine/events/halloffame.asm):
    wSpawnAfterChampion = SPAWN_LANCE; set STATUSFLAGS_HALL_OF_FAME_F (= ENGINE_CREDITS_SKIP);
    HallOfFame_InitSaveIfNeeded; wHallOfFameCount++; SaveGameData (the save happens here); add HOF
    entry; animation; `farjp Credits`. Back in Script_halloffame, ReturnFromCredits ends the
    script, the overworld loop exits, and FinishContinueFunction -> SoftReset (intro_menu.asm:452-455).
13. Continue (intro_menu.asm:365-384): wSpawnAfterChampion == SPAWN_LANCE -> wDefaultSpawnpoint =
    SPAWN_NEW_BARK, MAPSETUP_WARP, wSpawnAfterChampion reset to 0. The spawn table
    (data/maps/spawn_points.asm, read as map, X, Y by EnterMapSpawnPoint) gives NEW_BARK_TOWN
    x=15, y=6: the tile south of the player's house door (15,5). New Bark's NEWMAP callback runs.
    NEW_BARK_TOWN is scene 2, so no coord event fires. Nothing else runs on arrival. Elm's queued
    SS Ticket call will ring (WRAM only). PLAYERS_HOUSE_1F/2F are not involved.

#### Party levels (normal, non-FAITHFUL; only Charizard's moves differ in FAITHFUL)
- Lyra LYRA1_12 (parties.asm:1524): Pidgeot 44, Girafarig 43, Sunflora 45, Arcanine 45, Ampharos 46, Feraligatr 47
- Rival, Victory Road, RIVAL1_14 (parties.asm:1256): Weavile 45, Golbat 47, Magneton 46, Gengar 46, Alakazam 46, Typhlosion 49
- Will 1 (447): 48/49/50/50/49/51 (Xatu last). Koga 1 (488): 50/50/52/51/51/53 (Crobat).
  Bruno 1 (529): 51/53/51/51/53/55 (Machamp). Karen 1 (570): 53/53/54/55/55/57 (Houndoom).
- Lance (611): Gyarados 57, Dragonite 58, Kingdra 58, Aerodactyl 57, Charizard 57, Dragonite 60

#### Money
4 x base x last level: Lyra 2820 + rival 3920 + Will 5100 + Koga 5300 + Bruno 5500 + Karen 5700
+ Lance 6000 = 34340.

#### Files read
maps/NewBarkTown, ElmsLab, PlayersHouse1F, LyrasHouse2F, Route27, TohjoFalls, Route26,
PokemonLeagueGate, Route23, VictoryRoad1F/2F/3F, IndigoPlateau, IndigoPlateauPokecenter1F,
WillsRoom, KogasRoom, BrunosRoom, KarensRoom, LancesRoom, HallOfFame, SproutTower3F, Route36,
TinTower1F; engine/events/halloffame.asm, specials.asm (RespawnOneOffs), movie/credits.asm,
menus/intro_menu.asm, overworld/spawn_points.asm, overworld/scripting.asm (halloffame, credits,
blackoutmod), events/overworld.asm (Waterfall); data/maps/spawn_points.asm, scenes.asm,
data/events/initialize_events.asm, engine_flags.asm, data/trainers/parties.asm + attributes.asm.
Chokepoints were checked by rendering .ablk files through the tileset collision and flood filling.

### C12_KANTO: Collect all 8 Kanto badges (Blue beaten in Viridian)

**Changed when combining the checkpoints** (these override the trace notes below):

- added to `scenes`: `ROUTE_24 = 1` (maps/Route24.asm:92)
- added to `events_set`: `EVENT_BEAT_SCHOOLBOY_SHERMAN` (maps/Route1.asm:32)
- `money_earned_estimate` set to 30440
- Fly: HM_FLY is only given in Yellow Forest (maps/YellowForest.asm:148) at the end of an optional side quest, so the main-path player has no Fly. The trace's 'fly to X' steps are walks or surfs on foot. The story flags are the same, but walking may cross trainers that weren't traced (for example on Routes 5, 6 and 11).
- ROUTE_24 scene 1: on foot, the way back from Cerulean Cape crosses the Route 24 bridge southward. The underfoot trigger at its north end sets scene 1 (maps/Route24.asm:86-92, also wWalkingOnBridge = 1), and nothing sets it back at the south end. With Fly it would stay 0. The scene only controls the bridge graphics and which bridge triggers are active.
- EVENT_BEAT_SCHOOLBOY_SHERMAN: on foot (no Fly) the way back from Cinnabar to Viridian goes north on Route 1, where Schoolboy Sherman can't be avoided (one-way ledges). Found when tracing story_steps.lua.
- money: +2440 for Schoolboy Sherman (Route 1, forced on foot).


Start: New Bark after the credits, female player, Chikorita. End: VIRIDIAN_POKECENTER_1F (5,6), one step north of the entrance, right after Blue's badge and TM.

#### Kanto gates found in the source
- Ticket: HallOfFame.asm:86 queues SPECIALCALL_SSTICKET. ProfElmScript -> ElmGiveTicketScript (ElmsLab.asm:461-506) gives S_S_TICKET and sets EVENT_GOT_SS_TICKET_FROM_ELM and EVENT_LYRA_IN_HER_ROOM.
- S.S. Aqua, first trip (OlivinePort.asm:63-82). The grandpa bump (FastShip1F scene 2) is forced. The B1F on-duty sailor blocks both columns (coord events 26/27,5, scene 0). He only stops once the Polished lazy-sailor quest is done: talk to him (FastShipB1F:65-66), then beat Sailor Stanly in the NNW cabins, which sets FAST_SHIP_B1F scene 1 (NNW:118). The Captain's cabin is reached through B1F's left stairs. The granddaughter script (Captain's cabin :41-105) gives MACHO_BRACE and sets HAS_ARRIVED and FOUND_GIRL. Then talk to the gangway sailor (FastShip1F:79-92). VermilionPort leave-ship script: lines 33-43.
- Vermilion: the LawrenceIntroScript scene sets the flypoint. The gym door sits behind cut tree (13,23). Surge needs both trash-can switches (VermilionGym.asm:137-178).
- Route 8 from Saffron is blocked by protesters until Lavender is visited (LavenderTown.asm:41-46). Route 7 (Celadon) and Diglett's Cave (Vermilion) each have a sleeping big Snorlax. Both need the Poke Flute channel (specials.asm SpecialSnorlaxAwake), so the EXPN card is needed (LavRadioTower1F.asm:38-45), and that needs EVENT_RESTORED_POWER_TO_KANTO.
- The Radio Card is already owned: it is required in C04, because the Goldenrod gym lass (EVENT_GOLDENROD_GYM_WHITNEY) blocks the gym until the quiz is done.
- Power Plant chain: meet the manager (PowerPlant:75-91). The Cerulean Gym grunt then runs out (CeruleanGym:37-61). Next is the Route 24 grunt (Route24:95-116), then Misty's date at Cerulean Cape (clears EVENT_TRAINERS_IN_CERULEAN_GYM). Last are the hidden Machine Part in the gym (:149-162) and the return to the manager (:93-103).
- The Power Plant is on Route 10 North, south of a fence line. It is reached by surfing down the river (TOP_WALL fences at row 42).
- Pewter/Viridian need one Snorlax. Either use Diglett's Cave (Vermilion Snorlax), or go Celadon -> Route 16 NE (cut tree) -> Route 16 West (Lass Gina forced) -> Route 2 South. Route 4 is one-way (ledges), and Route 22 is gated by the League-gate black belt (EVENT_FOUGHT_SNORLAX). I took Diglett's Cave (the classic path). Seafoam can only be reached from Cinnabar via Route 20 (70,9). Route 19 rocks stay until Seafoam 1F is entered (SeafoamIslands1F:22).
- Viridian Gym: a gramps blocks the door (EVENT_BLUE_IN_CINNABAR). Blue at Cinnabar needs 15 badges (CinnabarIsland.asm:42-53), then clears EVENT_VIRIDIAN_GYM_BLUE. So Blue is always the 16th badge.
- Kanto badges: `givebadge X, KANTO_REGION` becomes ENGINE_X (scripting.asm Script_givebadge: $1n xor $18 -> ENGINE_BADGES+8+n).
- kantopostgymevents (std_scripts.asm:1769) fires a phone call at 9 badges (Lyra), 10 (Bill, GS Ball) and 12 (Lyra's egg -> EVENT_LYRA_GAVE_AWAY_EGG, lyra.asm:258). Blue's script does not call it.

#### Route taken (order chosen: Surge, Sabrina, Misty, Janine, Erika, Brock, Blaine, Blue)
1. Elm's Lab: S.S. Ticket. Fly to Olivine, then the Port and the S.S. Aqua (grandpa, lazy sailor, girl) to Vermilion Port.
2. Vermilion: Lawrence, flypoint, cut tree, gym puzzle, Surge (9).
3. Route 6 -> Saffron (flypoint) -> Sabrina (10).
4. Route 5 -> Cerulean (flypoint) -> Route 9 (cut tree; Camper Dean forced) -> Route 10 N (flypoint) -> surf -> Power Plant manager.
5. Fly to Cerulean -> gym grunt -> Route 24 bridge grunt -> Route 25 south beach strip -> Cape (flypoint, date trigger 3) -> fly to Cerulean -> Machine Part + Misty (11).
6. Route 9/10 N -> Power Plant return -> Lawrence and Zapdos scene -> Rock Tunnel 1F/B1F/1F (Seamus and Dick forced) -> Route 10 S -> Lavender (flypoint) -> EXPN card.
7. Route 12 N/gate/12 S -> 13 E (Joshua forced) -> 13 W (Kenny forced) -> 14 -> 15 -> Fuchsia (flypoint) -> Janine (12) -> Lyra's egg call.
8. Fly to Saffron -> Route 7 Snorlax -> Celadon (flypoint) -> cut tree (32,34) -> Erika (13).
9. Fly to Vermilion -> Snorlax -> Diglett's Cave -> Route 2 N (cut tree 1) -> Pewter (flypoint) -> Brock (14).
10. Route 2 N (cut tree 2) -> Route 2 Gate -> Route 2 S -> Viridian (flypoint) -> Route 1 -> Pallet (flypoint) -> surf Route 21 -> Cinnabar (flypoint) -> Route 20 (Swimmer Leona forced) -> Seafoam 1F -> Blaine (15).
11. Cinnabar: Blue teleports. Fly to Viridian -> gym -> Blue (16) -> Viridian Pokecenter.

#### How forced trainers were decided
I wrote throwaway scripts that read the .ablk block files and each tileset's collision file (my models of ledges, side walls, warps and map connections). They find the path that stays out of trainers' sight lines, with Surf allowed. Sight passes through walls, as in home/trainers.asm. Only fixed-facing trainers that no path can avoid are listed. Every multi-trainer result was re-checked one trainer at a time. Spinning trainers go to `unsure`. Gym trainers are set by each leader's own script.

#### Kanto leaders (party 1, normal mode, data/trainers/parties.asm)
- Lt.Surge :754 - Electabuzz 58, Electrode 56, Magnezone 57, Electrode 56, Jolteon 58, Raichu 60 (ace)
- Sabrina :891 - Espeon 61, Girafarig 59, Mr. Mime 60, Hypno 59, Wobbuffet 58, Alakazam 62 (ace)
- Misty :713 - Golduck 61, Quagsire 60, Lapras 62, Kingler 60, Lanturn 62, Starmie 64 (ace)
- Janine :850 - Crobat 64, Ariados 61, Qwilfish 62, Nidoqueen 64, Weezing 63, Venomoth 66 (ace)
- Erika :795 - Sunflora 61, Tangela 62, Politoed 61 (non-FAITHFUL; Parasect in FAITHFUL), Victreebel 64, Vileplume 65, Bellossom 65
- Brock :672 - Golem 64, Rhydon 63, Omastar 65, Onix 68, Kabutops 65, Aerodactyl 65
- Blaine :932 - Magcargo 65, Magmar 68, Arcanine 66, Ninetales 66, Flareon 65, Rapidash 69 (ace)
- Blue :973 (key_opponent) - Exeggutor 68, Umbreon 69, Machamp 66, Kabutops 67, Arcanine 68, Blastoise 70

#### Items
- Received and kept: S_S_TICKET, MACHO_BRACE, and 8 TMs (Wild Charge, Psychic, Water Pulse, Poison Jab, Giga Drain, Rock Slide, Will-O-Wisp, Stone Edge).
- MACHINE_PART was received and handed back inside the segment. EXPN card is recorded as ENGINE_EXPN_CARD only.

#### Files read (main)
- maps: ElmsLab, LyrasHouse1F, HallOfFame, OlivinePort, OlivineCity, the FastShip maps, VermilionPort, VermilionCity, VermilionGym, Route6, Route5, SaffronCity, SaffronGym, CeruleanCity, CeruleanGym, Route9, Route10North/South, PowerPlant, Route24, Route25, CeruleanCape, RockTunnel1F/B1F/2F, LavenderTown, LavRadioTower1F, Route8, Route12N/S, 13E/W, 14, 15, FuchsiaCity, FuchsiaGym, Route7, CeladonCity, CeladonGym, DiglettsCave, Route2North/South, PewterCity, PewterGym, ViridianCity, ViridianGym, Route1, PalletTown, Route21, Route20, Route19, SeafoamIslands1F, SeafoamGym, CinnabarIsland, Route4, MountMoon1F, PokemonLeagueGate, RadioTower1F, GoldenrodCity.
- engine: overworld/scripting.asm (appear, disappear, givebadge, reloadmapafterbattle), events/std_scripts.asm, phone/scripts/{elm,lyra,bill}.asm, phone/phone.asm, events/specials.asm, home/trainers.asm, home/map.asm (side walls, coord events), overworld/player_movement.asm (ledges), battle/read_trainer_attributes.asm.

### C13_POSTGAME: Beat the Elite Four again and Prof. Oak, then beat Red on Mt. Silver

**Changed when combining the checkpoints** (these override the trace notes below):

- removed from `engine_set`: `ENGINE_FLYPOINT_PALLET`
- Fly: HM_FLY is only given in Yellow Forest (maps/YellowForest.asm:148) at the end of an optional side quest, so the main-path player walks or surfs. Where the traced path says 'fly to', walking over already-visited maps gives the same flags.
- ENGINE_FLYPOINT_PALLET is not listed here because C12 already visits Pallet Town (on the way to Cinnabar) and sets it there. C12 does not talk to Oak, so EVENT_TALKED_TO_OAK_IN_KANTO and CATCH_CHARM stay in C13.


#### What Polished needs to reach Red (differs from vanilla Crystal)
- Red (maps/SilverCaveRoom3.asm) appears through MAPCALLBACK_OBJECTS: `disappear`, then `appear` only if
  EVENT_BEAT_RED and ENGINE_RED_IN_MOUNT_SILVER (daily flag) are both clear. No other condition
  (no weather, no Leaf, no dex requirement for the first fight).
- The only way to Route 28 is the Pokemon League Gate west corridor. A Black Belt at (7,5) blocks it and
  is hidden by EVENT_OPENED_MT_SILVER (PokemonLeagueGate.asm:24; checked on the collision map).
- EVENT_OPENED_MT_SILVER is set only by Oak (OaksLab.asm:151), and only after you beat him. His
  battle branch needs EVENT_BEAT_ELITE_FOUR_AGAIN (OaksLab.asm:86). With 16 badges and no rematch he
  only complains (OakNoEliteFourRematchText).
- EVENT_BEAT_ELITE_FOUR_AGAIN is set in HallOfFame.asm:75 when VAR_BADGES >= 16. So the main path
  is: E4 rematch, then Oak's battle, then Mt. Silver. (PlayersHouse2F.asm:175 is DEBUG only.)

#### Route traced
1. Start: Viridian City right after Blue (EARTHBADGE, TM_STONE_EDGE). Blue's script also set
   EVENT_FINAL_BATTLE_WITH_LYRA (ViridianGym.asm:45).
2. Fly to Indigo Plateau (IndigoPlateau.asm callback: fly point already set in C11).
3. IndigoPlateauPokecenter1F: PrepareEliteFourCallback resets the E4 scenes and flags. The map uses
   wAlways0SceneID, so coord_events (14,4)/(15,4) always fire. Collision render: the only corridor
   to Will's warp (12,3) is columns 14-15, so the event is unavoidable. EVENT_FINAL_BATTLE_WITH_LYRA
   jumps straight to .LyraFight, ignoring the weekday. Chikorita branch: LYRA2 3. The script then
   sets EVENT_INDIGO_PLATEAU_POKECENTER_LYRA (initially set, so no net change), sets
   ENGINE_INDIGO_PLATEAU_LYRA_FIGHT (weekly) and clears EVENT_FINAL_BATTLE_WITH_LYRA.
4. With VAR_BADGES == 16, WillsRoom/KogasRoom/BrunosRoom/KarensRoom use party 2 and LancesRoom uses
   LANCE2. Each room sets ENTRANCE_CLOSED/EXIT_OPEN/BEAT flags and scene 1, the same state as after
   C11, so none are listed. In Lance's room Oak gives the default speech (Mt. Silver not open yet).
5. HallOfFame.asm: 16 badges -> .CheckGoldTrophy -> setevent EVENT_DECO_GOLD_TROPHY (:56). Then
   setscene 1, EVENT_BEAT_ELITE_FOUR_AGAIN (:75), EVENT_BEAT_ELITE_FOUR etc. (already set),
   RespawnOneOffs (optional one-offs only), the SS ticket call is skipped (already have the ticket),
   blackoutmod NEW_BARK_TOWN, `halloffame`. HallOfFame:: then SPAWN_LANCE and Credits. After the
   soft reset the player continues at New Bark (intro_menu.asm .SpawnAfterE4). New Bark callback:
   fly point plus EVENT_FIRST_TIME_BANKING_WITH_MOM cleared, both unchanged.
6. Pallet Town (PalletTownFlyPoint -> ENGINE_FLYPOINT_PALLET) -> OaksLab, Oak:
   - not opened and not talked -> welcome text, EVENT_TALKED_TO_OAK_IN_KANTO (:50)
   - no Ivy starter -> .CheckBadges -> EVENT_BEAT_ELITE_FOUR_AGAIN -> .BattleOak
   - EVENT_LISTENED_TO_OAK_INTRO (:134), yes/no -> YES, loadtrainer PROF_OAK 1
   - EVENT_BEAT_PROF_OAK (:150), EVENT_OPENED_MT_SILVER (:151) -> .CheckPokedex:
     CATCH_CHARM (:98) if not owned. ProfOaksPCBoot only rates the dex. Oval/Shiny Charm need a
     full dex, so they are skipped.
7. Viridian -> Route 22 (no coord events; Kukui optional) -> Pokemon League Gate east door (19,7),
   west along row 5 (coord events at (10,10)/(11,10) are in the south corridor, not crossed) ->
   Route 28 (no scripts) -> Silver Cave Outside (setflag ENGINE_FLYPOINT_SILVER_CAVE :24).
   Collision BFS from the Route 28 gate door reaches the Pokecenter door (23,13) and the cave
   (18,5) with both cut trees standing.
8. SilverCavePokeCenter1F (heal; the journal/gramps are optional) -> Room1 (15,1) -> Room2 (11,5)
   -> Room3. The rooms hold only itemballs and hidden items (all optional).
9. Red: loadtrainer RED 1, then verbosegivekeyitem MYSTICTICKET (:45),
   EVENT_GOT_MYSTICTICKET_FROM_RED (:46), fade, `disappear` (EVENT_RED_IN_MT_SILVER),
   setflag ENGINE_RED_IN_MOUNT_SILVER (:52), HealParty, setevent EVENT_BEAT_RED (:57),
   playmapmusic, end. No credits, no warp, no special call beyond fades and heal.

#### Red's party (data/trainers/parties.asm:1013, `def_trainer 1, "Red"`, the only Red party)
PIKACHU 90, ESPEON 84, SNORLAX 85, OMASTAR 87, GYARADOS 87, CHARIZARD 88 (the FAITHFUL ifdef
changes only Charizard's ability and moves). There is no level scaling: AdjustLevelForBadges only
changes encoded levels above MAX_LEVEL, and these are literal.
Other battles in this segment: LYRA2 3 (parties.asm:1562, last mon 72), WILL 2 (:468), KOGA 2
(:509), BRUNO 2 (:550), KAREN 2 (:591), LANCE2 (:642, last mon 80), PROF_OAK 1 (:6770, levels
78/76/80/80/80/82).

#### at
Polished leaves the player at SILVER_CAVE_ROOM_3 (10,7), below Red's old spot (10,6). I used the
Pokecenter convention: SILVER_CAVE_POKECENTER_1F (5,6). That map uses the shared
JohtoPokeCenter1F layout, with the entrance mat at (5,7)/(6,7), and (5,6) is floor. Walking back
changes no flags.

#### Choices and uncertainties
- BOUNDARY: Oak welcome, Catch Charm and the Pallet fly point may already be done in C12 if that
  path visited Pallet or Oak.
- BOUNDARY: the forced Lyra fight belongs here unless C12 went back to Indigo Plateau after Blue.
- E4 room scenes and flags, the HoF's repeated flags and RespawnOneOffs have no net change versus
  C11, so they are not listed (see `unsure`).
- EVENT_RED_IN_MT_SILVER's src is the object_event line (15), because line 51
  (`disappear SILVERCAVEROOM3_RED`) does not contain the name.
- Daily and weekly flags (ENGINE_RED_IN_MOUNT_SILVER, ENGINE_INDIGO_PLATEAU_LYRA_FIGHT) reset
  over time; EVENT_BEAT_RED keeps Red hidden until Leaf is beaten (NavelRockRoof.asm:108).
- Money is about 61,400 (100 x last-mon level for 8 battles).
- The Hall of Fame count (wHallOfFameCount) goes up by 1 (a second HoF entry). It is not a flag.

Files read: maps/{OaksLab,SilverCaveRoom3,SilverCaveRoom1,SilverCaveRoom2,SilverCaveOutside,
SilverCavePokeCenter1F,Route28,Route22,PokemonLeagueGate,PalletTown,IndigoPlateau,
IndigoPlateauPokecenter1F,WillsRoom,KogasRoom,BrunosRoom,KarensRoom,LancesRoom,HallOfFame,
ViridianGym,NewBarkTown,Route1,ViridianCity,Route23}.asm, engine/events/halloffame.asm,
engine/movie/credits.asm, engine/menus/intro_menu.asm, engine/overworld/scripting.asm
(halloffame/credits), engine/events/specials.asm (RespawnOneOffs),
engine/events/prof_oaks_pc.asm, engine/battle/{read_trainer_party,read_trainer_attributes,core}.asm,
data/trainers/{parties,attributes}.asm, data/events/initialize_events.asm, data/maps/scenes.asm,
constants/{event_flags,engine_flags,item_constants}.asm.
