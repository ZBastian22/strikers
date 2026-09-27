# Map event changes between v3.2.3 and dev

Per map file: events (warps, coord/bg/object events and the object helpers) added or removed, compared by kind, coordinates and arguments. A moved object shows as one removed and one added.

Renamed: CeladonDeptStore6F.asm -> CeladonDeptStoreRoof.asm, FarawayIsland.asm -> FarawayIslandSouth.asm, Route13East.asm -> Route13.asm, Route16Northwest.asm -> Route16North.asm, Route16South.asm -> Route17North.asm, Route17.asm -> Route17South.asm, Route5UndergroundEntrance.asm -> Route5UndergroundPathEntrance.asm, Route6UndergroundEntrance.asm -> Route6UndergroundPathEntrance.asm, UndergroundWarehouse.asm -> GoldenrodUndergroundWarehouse.asm, WarehouseEntrance.asm -> GoldenrodUnderground.asm

Removed: Route13West.asm, Route16Northeast.asm, Route23.asm, Underground.asm, UndergroundPathSwitchRoomEntrances.asm

Added: CherrygroveTrainTrackDual.asm, FarawayIslandNorth.asm, FuchsiaAquarium1F.asm, FuchsiaAquarium2F.asm, GoldenrodUndergroundEntrances.asm, GoldenrodUndergroundSwitchRoom.asm, Route14LuckyIslandDual.asm, Route16East.asm, Route23North.asm, Route23South.asm, UndergroundPath.asm

## AzaleaGym

- removed `warp_event 4, 15, AZALEA_TOWN, 5`
- removed `warp_event 5, 15, AZALEA_TOWN, 5`
- removed `bg_event 3, 13, BGEVENT_READ, AzaleaGymStatue`
- removed `bg_event 6, 13, BGEVENT_READ, AzaleaGymStatue`
- removed `object_event 5, 7, SPRITE_BUGSY, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, AzaleaGymBugsyScript, -1`
- removed `object_event 7, 13, SPRITE_GYM_GUY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, AzaleaGymGuyScript, -1`
- removed `object_event 5, 3, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerBug_catcherBenny, -1`
- removed `object_event 8, 8, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBug_catcherAl, -1`
- removed `object_event 0, 2, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBug_catcherJosh, -1`
- removed `object_event 4, 10, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerTwinsAmyandmimi1, -1`
- removed `object_event 5, 10, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerTwinsAmyandmimi2, -1`
+ added `warp_event 6, 23, AZALEA_TOWN, 5`
+ added `warp_event 7, 23, AZALEA_TOWN, 5`
+ added `bg_event 5, 21, BGEVENT_READ, AzaleaGymStatue`
+ added `bg_event 8, 21, BGEVENT_READ, AzaleaGymStatue`
+ added `bg_event 1, 10, BGEVENT_READ, AzaleaGymRedSwitch`
+ added `bg_event 3, 4, BGEVENT_READ, AzaleaGymBlueSwitch`
+ added `bg_event 8, 5, BGEVENT_READ, AzaleaGymBlueSwitch`
+ added `bg_event 8, 10, BGEVENT_READ, AzaleaGymBlueSwitch`
+ added `object_event 2, 18, SPRITE_SPINARAK_CART, SPRITEMOVEDATA_SPINARAK_CART, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, SpinarakCart1Script, -1`
+ added `object_event 6, 18, SPRITE_SPINARAK_CART, SPRITEMOVEDATA_SPINARAK_CART, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, SpinarakCart2Script, -1`
+ added `object_event 11, 18, SPRITE_SPINARAK_CART, SPRITEMOVEDATA_SPINARAK_CART, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, SpinarakCart3Script, -1`
+ added `object_event 6, 9, SPRITE_SPINARAK_CART, SPRITEMOVEDATA_SPINARAK_CART, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, SpinarakCart4Script, -1`
+ added `object_event 7, 3, SPRITE_BUGSY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, AzaleaGymBugsyScript, -1`
+ added `object_event 9, 21, SPRITE_GYM_GUY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, AzaleaGymGuyScript, -1`
+ added `object_event 5, 12, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBug_catcherBenny, -1`
+ added `object_event 11, 13, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerBug_catcherAl, -1`
+ added `object_event 11, 4, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerBug_catcherJosh, -1`
+ added `object_event 1, 4, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerTwinsAmyandmimi1, -1`
+ added `object_event 2, 4, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerTwinsAmyandmimi2, -1`

## AzaleaTown

- removed `coord_event 5, 10, 1, AzaleaTownRivalBattleTrigger1`
- removed `coord_event 5, 11, 1, AzaleaTownRivalBattleTrigger2`
- removed `coord_event 9, 6, 2, AzaleaTown_CelebiTrigger`
- removed `bg_event 14, 15, BGEVENT_JUMPTEXT, AzaleaGymSignText`
- removed `object_event 8, 17, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, SLOWPOKE, -1, PAL_NPC_PINK, OBJECTTYPE_SCRIPT, PLAIN_FORM, AzaleaTownSlowpokeScript, EVENT_AZALEA_TOWN_SLOWPOKES`
- removed `object_event 18, 9, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, SLOWPOKE, -1, PAL_NPC_PINK, OBJECTTYPE_SCRIPT, PLAIN_FORM, AzaleaTownSlowpokeScript, EVENT_AZALEA_TOWN_SLOWPOKES`
- removed `object_event 30, 9, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, SLOWPOKE, -1, PAL_NPC_PINK, OBJECTTYPE_SCRIPT, PLAIN_FORM, AzaleaTownSlowpokeScript, EVENT_AZALEA_TOWN_SLOWPOKES`
- removed `object_event 15, 15, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, SLOWPOKE, -1, PAL_NPC_PINK, OBJECTTYPE_SCRIPT, PLAIN_FORM, AzaleaTownSlowpokeScript, EVENT_AZALEA_TOWN_SLOWPOKES`
- removed `pokemon_event 14, 12, WOOPER, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BLUE, AzaleaTownWoosterText, EVENT_SLOWPOKE_WELL_SLOWPOKES`
- removed `pokemon_event 14, 12, QUAGSIRE, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BLUE, AzaleaTownWoosterText, EVENT_AZALEA_TOWN_SLOWPOKES`
- removed `fruittree_event 8, 2, FRUITTREE_AZALEA_TOWN, WHT_APRICORN, PAL_NPC_WHITE`
+ added `coord_event 5, 10, SCENE_AZALEATOWN_RIVAL_BATTLE, AzaleaTownRivalBattleTrigger1`
+ added `coord_event 5, 11, SCENE_AZALEATOWN_RIVAL_BATTLE, AzaleaTownRivalBattleTrigger2`
+ added `coord_event 9, 6, SCENE_AZALEATOWN_CELEBI_EVENT, AzaleaTown_CelebiTrigger`
+ added `bg_event 11, 15, BGEVENT_JUMPTEXT, AzaleaGymSignText`
+ added `object_event 8, 17, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, SLOWPOKE, -1, PAL_MON_PINK, OBJECTTYPE_SCRIPT, PLAIN_FORM, AzaleaTownSlowpokeScript, EVENT_AZALEA_TOWN_SLOWPOKES`
+ added `object_event 18, 9, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, SLOWPOKE, -1, PAL_MON_PINK, OBJECTTYPE_SCRIPT, PLAIN_FORM, AzaleaTownSlowpokeScript, EVENT_AZALEA_TOWN_SLOWPOKES`
+ added `object_event 30, 9, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, SLOWPOKE, -1, PAL_MON_PINK, OBJECTTYPE_SCRIPT, PLAIN_FORM, AzaleaTownSlowpokeScript, EVENT_AZALEA_TOWN_SLOWPOKES`
+ added `object_event 14, 15, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, SLOWPOKE, -1, PAL_MON_PINK, OBJECTTYPE_SCRIPT, PLAIN_FORM, AzaleaTownSlowpokeScript, EVENT_AZALEA_TOWN_SLOWPOKES`
+ added `pokemon_event 14, 12, WOOPER, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BLUE, AzaleaTownWoosterText, EVENT_SLOWPOKE_WELL_SLOWPOKES`
+ added `pokemon_event 14, 12, QUAGSIRE, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BLUE, AzaleaTownWoosterText, EVENT_AZALEA_TOWN_SLOWPOKES`
+ added `fruittree_event 8, 2, FRUITTREE_AZALEA_TOWN, WHT_APRICORN, PAL_NPC_ENV_WHITE`

## BattleFactory1F

- removed `warp_event 13, 11, VERMILION_CITY, 16`
+ added `warp_event 13, 11, VERMILION_CITY, 15`

## BattleTower2F

- removed `pokemon_event 18, 8, PIKACHU, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_RED, BattleTower2FPikachuText, EVENT_QUIET_CAVE_MARLEY`
+ added `pokemon_event 18, 8, PIKACHU, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_RED, BattleTower2FPikachuText, EVENT_QUIET_CAVE_MARLEY`

## BattleTowerOutside

- removed `coord_event 8, 9, 1, BattleTowerOutsidePanUpTrigger1`
- removed `coord_event 9, 9, 1, BattleTowerOutsidePanUpTrigger2`
- removed `object_event 8, 9, SPRITE_RATTATA_BACK, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptext, BattleTowerOutsideDoorsClosedText, EVENT_BATTLE_TOWER_OPEN`
- removed `object_event 9, 9, SPRITE_RATTATA_BACK, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptext, BattleTowerOutsideDoorsClosedText, EVENT_BATTLE_TOWER_OPEN`
+ added `coord_event 8, 9, SCENE_BATTLETOWEROUTSIDE_NOOP, BattleTowerOutsidePanUpTrigger1`
+ added `coord_event 9, 9, SCENE_BATTLETOWEROUTSIDE_NOOP, BattleTowerOutsidePanUpTrigger2`
+ added `object_event 8, 9, SPRITE_BLANK_FRUIT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptext, BattleTowerOutsideDoorsClosedText, EVENT_BATTLE_TOWER_OPEN`
+ added `object_event 9, 9, SPRITE_BLANK_FRUIT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptext, BattleTowerOutsideDoorsClosedText, EVENT_BATTLE_TOWER_OPEN`

## BeautifulBeach

- removed `object_event 12, 13, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_SPINCOUNTERCLOCKWISE, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerSwimmerfRachel, -1`
+ added `object_event 12, 13, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_SPINCOUNTERCLOCKWISE, 0, 0, -1, PAL_NPC_DARK_GREEN, OBJECTTYPE_TRAINER, 2, TrainerSwimmerfRachel, -1`

## BellchimeTrail

- removed `coord_event 21, 9, 1, BellchimeTrailPanUpTrigger`
- removed `bg_event 8, 3, BGEVENT_JUMPTEXT, BellchimeTrailWaterText`
- removed `bg_event 9, 3, BGEVENT_JUMPTEXT, BellchimeTrailWaterText`
- removed `bg_event 8, 6, BGEVENT_JUMPTEXT, BellchimeTrailWaterText`
- removed `bg_event 9, 6, BGEVENT_JUMPTEXT, BellchimeTrailWaterText`
+ added `coord_event 21, 9, SCENE_BELLCHIMETRAIL_NOOP, BellchimeTrailPanUpTrigger`

## BlackthornCity

- removed `bg_event 17, 13, BGEVENT_JUMPTEXT, BlackthornGymSignText`
+ added `bg_event 19, 11, BGEVENT_JUMPTEXT, BlackthornGymSignText`

## BlackthornDragonSpeechHouse

- removed `pokemon_event 5, 5, DRATINI, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BLUE, BlackthornDragonSpeechHouseDratiniText, -1`
+ added `pokemon_event 5, 5, DRATINI, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BLUE, BlackthornDragonSpeechHouseDratiniText, -1`

## BurnedTower1F

- removed `coord_event 9, 9, 1, BurnedTowerRivalBattleScript`
- removed `object_event 1, 1, SPRITE_HEX_MANIAC, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerHexManiacTamara, -1`
+ added `coord_event 6, 1, SCENE_BURNEDTOWER1F_FIREBREATHER_DICK, BurnedTowerFirebreatherDickBattleScript`
+ added `coord_event 9, 9, SCENE_BURNEDTOWER1F_RIVAL_BATTLE, BurnedTowerRivalBattleScript`
+ added `object_event 6, 2, SPRITE_FIREBREATHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_GRAY, OBJECTTYPE_COMMAND, jumptextfaceplayer, FirebreatherDickAfterText, EVENT_BURNED_TOWER_FIREBREATHER_DICK_ASHES`
+ added `object_event 6, 3, SPRITE_FIREBREATHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, FirebreatherDickAfterText, EVENT_BURNED_TOWER_FIREBREATHER_DICK_NORMAL`
+ added `object_event 3, 6, SPRITE_HEX_MANIAC, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerHexManiacTamara, -1`

## BurnedTowerB1F

- removed `coord_event 10, 6, 0, ReleaseTheBeasts`
- removed `pokemon_event 7, 3, RAIKOU, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BROWN, ClearText, EVENT_BURNED_TOWER_B1F_BEASTS_1`
- removed `pokemon_event 12, 3, ENTEI, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_RED, ClearText, EVENT_BURNED_TOWER_B1F_BEASTS_1`
- removed `pokemon_event 10, 4, SUICUNE, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BLUE, ClearText, EVENT_BURNED_TOWER_B1F_BEASTS_1`
- removed `pokemon_event 7, 3, RAIKOU, SPRITEMOVEDATA_STILL, -1, PAL_NPC_WHITE, ClearText, EVENT_BURNED_TOWER_B1F_BEASTS_2`
- removed `pokemon_event 12, 3, ENTEI, SPRITEMOVEDATA_STILL, -1, PAL_NPC_WHITE, ClearText, EVENT_BURNED_TOWER_B1F_BEASTS_2`
- removed `pokemon_event 10, 4, SUICUNE, SPRITEMOVEDATA_STILL, -1, PAL_NPC_WHITE, ClearText, EVENT_BURNED_TOWER_B1F_BEASTS_2`
+ added `coord_event 10, 6, SCENE_BURNEDTOWERB1F_RELEASE_THE_BEASTS, ReleaseTheBeasts`
+ added `pokemon_event 7, 3, RAIKOU, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BROWN, ClearText, EVENT_BURNED_TOWER_B1F_BEASTS_1`
+ added `pokemon_event 12, 3, ENTEI, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_RED, ClearText, EVENT_BURNED_TOWER_B1F_BEASTS_1`
+ added `pokemon_event 10, 4, SUICUNE, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_AZURE, ClearText, EVENT_BURNED_TOWER_B1F_BEASTS_1`
+ added `pokemon_event 7, 3, RAIKOU, SPRITEMOVEDATA_STILL, -1, PAL_MON_WHITE, ClearText, EVENT_BURNED_TOWER_B1F_BEASTS_2`
+ added `pokemon_event 12, 3, ENTEI, SPRITEMOVEDATA_STILL, -1, PAL_MON_WHITE, ClearText, EVENT_BURNED_TOWER_B1F_BEASTS_2`
+ added `pokemon_event 10, 4, SUICUNE, SPRITEMOVEDATA_STILL, -1, PAL_MON_WHITE, ClearText, EVENT_BURNED_TOWER_B1F_BEASTS_2`

## CeladonCity

- removed `warp_event 14, 29, CELADON_GYM, 1`
- removed `warp_event 4, 29, CELADON_UNIVERSITY_1F, 1`
- removed `bg_event 9, 18, BGEVENT_JUMPTEXT, CeladonCitySignText`
- removed `bg_event 15, 31, BGEVENT_JUMPTEXT, CeladonGymSignText`
- removed `object_event 5, 16, SPRITE_RICH_BOY, SPRITEMOVEDATA_WALK_UP_DOWN, 2, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, CeladonCityScript, -1`
- removed `pokemon_event 31, 11, POLIWRATH, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BLUE, CeladonCityPoliwrathText, -1`
- removed `object_event 12, 31, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, CeladonCityGramps2Text, -1`
- removed `cuttree_event -5, 24, EVENT_ROUTE_16_CUT_TREE`
+ added `warp_event 12, 29, CELADON_GYM, 1`
+ added `warp_event 5, 29, CELADON_UNIVERSITY_1F, 1`
+ added `warp_event 9, 9, CELADON_DEPT_STORE_1F, 2`
+ added `warp_event 23, 19, CELADON_GAME_CORNER, 2`
+ added `warp_event 6, 29, CELADON_UNIVERSITY_1F, 2`
+ added `bg_event 11, 18, BGEVENT_JUMPTEXT, CeladonCitySignText`
+ added `bg_event 13, 29, BGEVENT_JUMPTEXT, CeladonGymSignText`
+ added `object_event 4, 15, SPRITE_RICH_BOY, SPRITEMOVEDATA_WALK_UP_DOWN, 2, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, CeladonCityScript, -1`
+ added `pokemon_event 31, 11, POLIWRATH, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BLUE, CeladonCityPoliwrathText, -1`
+ added `object_event 10, 32, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_UP, 0, 0, (1 << DAY) | (1 << NITE), PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, CeladonCityGramps2Text, -1`
+ added `object_event 9, 31, SPRITE_PICNICKER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, (1 << MORN) | (1 << EVE), PAL_NPC_GREEN, OBJECTTYPE_COMMAND, jumptextfaceplayer, CeladonCityPicnickerText, -1`

## CeladonDeptStore1F

- removed `warp_event 8, 7, CELADON_CITY, 1`
+ added `warp_event 8, 7, CELADON_CITY, 17`

## CeladonDeptStore5F

- removed `warp_event 15, 0, CELADON_DEPT_STORE_6F, 1`
+ added `warp_event 15, 0, CELADON_DEPT_STORE_ROOF, 1`

## CeladonDeptStore6F -> CeladonDeptStoreRoof

- removed `warp_event 15, 0, CELADON_DEPT_STORE_5F, 2`
- removed `warp_event 2, 0, CELADON_DEPT_STORE_ELEVATOR, 1`
- removed `bg_event 14, 0, BGEVENT_JUMPTEXT, CeladonDeptStore6FDirectoryText`
- removed `object_event 9, 2, SPRITE_POKEMANIAC, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, CeladonDeptStore6FSuperNerdText, -1`
- removed `object_event 12, 5, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_WANDER, 1, 2, -1, PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, CeladonDeptStore6FYoungsterText, -1`
- removed `object_event 5, 1, SPRITE_GAMEBOY_KID, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, CeladonDeptStore3FGameboyKid1Script, -1`
- removed `object_event 6, 1, SPRITE_GAMER_GIRL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, CeladonDeptStore3FGameboyKid2Script, -1`
+ added `warp_event 17, 2, CELADON_DEPT_STORE_5F, 2`
+ added `bg_event 16, 2, BGEVENT_JUMPTEXT, CeladonDeptStoreRoofDirectoryText`
+ added `object_event 13, 2, SPRITE_POKEMANIAC, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, CeladonDeptStoreRoofSuperNerdText, -1`
+ added `object_event 16, 5, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_WANDER, 1, 2, -1, PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, CeladonDeptStoreRoofYoungsterText, -1`
+ added `object_event 5, 3, SPRITE_GAMEBOY_KID, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, CeladonDeptStoreRoofGameboyKid1Script, -1`
+ added `object_event 8, 2, SPRITE_GAMER_GIRL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, CeladonDeptStoreRoofGameboyKid2Script, -1`

## CeladonGameCorner

- removed `warp_event 15, 13, CELADON_CITY, 6`
- removed `object_event 9, 1, SPRITE_RICH_BOY, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 1, CeladonGameCornerRichBoyTobin, EVENT_CELADON_GAME_CORNER_RICH_BOY_TOBIN`
+ added `warp_event 15, 13, CELADON_CITY, 18`
+ added `object_event 9, 1, SPRITE_RICH_BOY, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_DARK_RED, OBJECTTYPE_TRAINER, 1, CeladonGameCornerRichBoyTobin, EVENT_CELADON_GAME_CORNER_RICH_BOY_TOBIN`

## CeladonHomeDecorStore1F

- removed `object_event 7, 5, SPRITE_MON_ICON, SPRITEMOVEDATA_STILL, 0, BULBASAUR, -1, PAL_NPC_TEAL, OBJECTTYPE_SCRIPT, NO_FORM, CeladonHomeDecorStore1FBulbasaurDollScript, -1`
- removed `object_event 8, 5, SPRITE_MON_ICON, SPRITEMOVEDATA_STILL, 0, CHARMANDER, -1, PAL_NPC_ORANGE, OBJECTTYPE_SCRIPT, NO_FORM, CeladonHomeDecorStore1FCharmanderDollScript, -1`
- removed `object_event 9, 5, SPRITE_MON_ICON, SPRITEMOVEDATA_STILL, 0, SQUIRTLE, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, NO_FORM, CeladonHomeDecorStore1FSquirtleDollScript, -1`
+ added `object_event 7, 5, SPRITE_MON_ICON, SPRITEMOVEDATA_STILL, 0, BULBASAUR, -1, PAL_MON_TEAL, OBJECTTYPE_SCRIPT, NO_FORM, CeladonHomeDecorStore1FBulbasaurDollScript, -1`
+ added `object_event 8, 5, SPRITE_MON_ICON, SPRITEMOVEDATA_STILL, 0, CHARMANDER, -1, PAL_MON_ORANGE, OBJECTTYPE_SCRIPT, NO_FORM, CeladonHomeDecorStore1FCharmanderDollScript, -1`
+ added `object_event 9, 5, SPRITE_MON_ICON, SPRITEMOVEDATA_STILL, 0, SQUIRTLE, -1, PAL_MON_BLUE, OBJECTTYPE_SCRIPT, NO_FORM, CeladonHomeDecorStore1FSquirtleDollScript, -1`

## CeladonHotelPool

+ added `object_event 2, 6, SPRITE_DRAGONITE, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_COPY_BG_YELLOW, OBJECTTYPE_COMMAND, jumptext, CeladonHotelPoolSwimRingText, -1`
+ added `object_event 12, 4, SPRITE_DRAGONITE, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_COPY_BG_RED, OBJECTTYPE_COMMAND, jumptext, CeladonHotelPoolSwimRingText, -1`

## CeladonMansion1F

- removed `pokemon_event 2, 6, MEOWTH, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BROWN, CeladonMansion1FMeowthText, -1`
- removed `pokemon_event 3, 4, CLEFAIRY, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_PINK, CeladonMansion1FClefairyText, -1`
- removed `pokemon_event 4, 4, NIDORAN_F, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_TEAL, CeladonMansion1FNidoranFText, -1`
+ added `pokemon_event 2, 6, MEOWTH, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BROWN, CeladonMansion1FMeowthText, -1`
+ added `pokemon_event 3, 4, CLEFAIRY, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_PINK, CeladonMansion1FClefairyText, -1`
+ added `pokemon_event 4, 4, NIDORAN_F, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_TEAL, CeladonMansion1FNidoranFText, -1`

## CeladonMansionRoof

- removed `warp_event 1, 1, CELADON_MANSION_3F, 1`
- removed `warp_event 6, 1, CELADON_MANSION_3F, 4`
- removed `warp_event 2, 5, CELADON_MANSION_ROOF_HOUSE, 1`
- removed `bg_event 6, 1, BGEVENT_LEFT, MapCeladonMansionRoofSignpost0Script`
- removed `object_event 7, 5, SPRITE_FAT_GUY, SPRITEMOVEDATA_WALK_UP_DOWN, 1, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_COMMAND, jumptextfaceplayer, CeladonMansionRoofFisherText, -1`
+ added `warp_event 5, 1, CELADON_MANSION_3F, 1`
+ added `warp_event 10, 1, CELADON_MANSION_3F, 4`
+ added `warp_event 6, 5, CELADON_MANSION_ROOF_HOUSE, 1`
+ added `bg_event 10, 1, BGEVENT_LEFT, MapCeladonMansionRoofSignpost0Script`
+ added `object_event 11, 5, SPRITE_FAT_GUY, SPRITEMOVEDATA_WALK_UP_DOWN, 1, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_COMMAND, jumptextfaceplayer, CeladonMansionRoofFisherText, -1`

## CeladonUniversity1F

- removed `warp_event 15, 19, CELADON_CITY, 13`
+ added `warp_event 15, 19, CELADON_CITY, 19`

## CeruleanCape

- removed `coord_event 4, 6, 1, CeruleanCapeDateInterruptedTrigger1`
- removed `coord_event 4, 7, 1, CeruleanCapeDateInterruptedTrigger2`
- removed `coord_event 9, 12, 1, CeruleanCapeDateInterruptedTrigger3`
- removed `object_event 41, 16, SPRITE_SWIMMER_GUY, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerSwimmermMalcolm, -1`
- removed `object_event 32, 11, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerFisherLeroy, -1`
- removed `itemball_event 31, 12, SHELL_BELL, 1, EVENT_CERULEAN_CAPE_SHELL_BELL`
+ added `coord_event 4, 6, SCENE_CERULEANCAPE_MISTYS_DATE, CeruleanCapeDateInterruptedTrigger1`
+ added `coord_event 4, 7, SCENE_CERULEANCAPE_MISTYS_DATE, CeruleanCapeDateInterruptedTrigger2`
+ added `coord_event 9, 12, SCENE_CERULEANCAPE_MISTYS_DATE, CeruleanCapeDateInterruptedTrigger3`
+ added `object_event 41, 16, SPRITE_SWIMMER_GUY, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, PAL_NPC_DARK_RED, OBJECTTYPE_TRAINER, 4, TrainerSwimmermMalcolm, -1`
+ added `object_event 32, 12, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerFisherLeroy, -1`
+ added `object_event 29, 11, SPRITE_FLOATING_BALL, SPRITEMOVEDATA_POKEMON, 0, 0, -1, 0, OBJECTTYPE_ITEMBALL, PLAYEREVENT_ITEMBALL, SHELL_BELL, 1, EVENT_CERULEAN_CAPE_SHELL_BELL`

## CeruleanCave1F

- removed `coord_event 20, 4, 1, CeruleanCave1FBridgeOverheadTrigger`
- removed `coord_event 20, 5, 1, CeruleanCave1FBridgeOverheadTrigger`
- removed `coord_event 23, 4, 1, CeruleanCave1FBridgeOverheadTrigger`
- removed `coord_event 23, 5, 1, CeruleanCave1FBridgeOverheadTrigger`
- removed `coord_event 21, 7, 0, CeruleanCave1FBridgeUnderfootTrigger`
- removed `coord_event 22, 7, 0, CeruleanCave1FBridgeUnderfootTrigger`
+ added `coord_event 20, 4, SCENE_CERULEANCAVE1F_BRIDGE_OVERHEAD, CeruleanCave1FBridgeOverheadTrigger`
+ added `coord_event 20, 5, SCENE_CERULEANCAVE1F_BRIDGE_OVERHEAD, CeruleanCave1FBridgeOverheadTrigger`
+ added `coord_event 23, 4, SCENE_CERULEANCAVE1F_BRIDGE_OVERHEAD, CeruleanCave1FBridgeOverheadTrigger`
+ added `coord_event 23, 5, SCENE_CERULEANCAVE1F_BRIDGE_OVERHEAD, CeruleanCave1FBridgeOverheadTrigger`
+ added `coord_event 21, 7, SCENE_CERULEANCAVE1F_BRIDGE_UNDERFOOT, CeruleanCave1FBridgeUnderfootTrigger`
+ added `coord_event 22, 7, SCENE_CERULEANCAVE1F_BRIDGE_UNDERFOOT, CeruleanCave1FBridgeUnderfootTrigger`

## CeruleanCaveB1F

- removed `object_event 7, 13, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, MEWTWO, -1, PAL_NPC_PURPLE, OBJECTTYPE_SCRIPT, PLAIN_FORM, CeruleanCaveMewtwo, EVENT_CERULEAN_CAVE_MEWTWO`
+ added `object_event 7, 13, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, MEWTWO, -1, PAL_MON_PURPLE, OBJECTTYPE_SCRIPT, PLAIN_FORM, CeruleanCaveMewtwo, EVENT_CERULEAN_CAVE_MEWTWO`

## CeruleanCity

- removed `warp_event 7, 11, CERULEAN_GYM_BADGE_SPEECH_HOUSE, 1`
- removed `warp_event 28, 13, CERULEAN_POLICE_STATION, 1`
- removed `warp_event 13, 15, CERULEAN_TRADE_SPEECH_HOUSE, 1`
- removed `warp_event 19, 17, CERULEAN_POKECENTER_1F, 1`
- removed `warp_event 30, 19, CERULEAN_GYM, 1`
- removed `warp_event 25, 25, CERULEAN_MART, 2`
- removed `warp_event 2, 9, CERULEAN_CAVE_1F, 1`
- removed `warp_event 14, 25, CERULEAN_BIKE_SHOP, 1`
- removed `warp_event 15, 11, CERULEAN_BERRY_POWDER_HOUSE, 1`
- removed `warp_event 19, 25, CERULEAN_COUPLE_HOUSE, 1`
- removed `warp_event 29, 7, CERULEAN_WATER_SHOW_SPEECH_HOUSE, 1`
- removed `coord_event 20, 3, 0, Route24BridgeUnderfootTrigger`
- removed `coord_event 21, 3, 0, Route24BridgeUnderfootTrigger`
- removed `coord_event 20, 4, 1, Route24BridgeOverheadTrigger`
- removed `coord_event 21, 4, 1, Route24BridgeOverheadTrigger`
- removed `bg_event 17, 20, BGEVENT_JUMPTEXT, CeruleanCitySignText`
- removed `bg_event 23, 19, BGEVENT_JUMPTEXT, CeruleanGymSignText`
- removed `bg_event 11, 25, BGEVENT_JUMPTEXT, CeruleanBikeShopSignText`
- removed `bg_event 25, 13, BGEVENT_JUMPTEXT, CeruleanPoliceSignText`
- removed `bg_event 23, 5, BGEVENT_JUMPTEXT, CeruleanCapeSignText`
- removed `bg_event 11, 19, BGEVENT_JUMPTEXT, CeruleanBubblerText`
- removed `bg_event 21, 27, BGEVENT_JUMPTEXT, CeruleanTrainerTipsText`
- removed `bg_event 4, 13, BGEVENT_ITEM + BERSERK_GENE, EVENT_FOUND_BERSERK_GENE_IN_CERULEAN_CITY`
- removed `object_event 21, 20, SPRITE_BATTLE_GIRL, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, CeruleanCityCooltrainerFScript, -1`
- removed `object_event 6, 8, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, CeruleanCityYoungsterScript, -1`
- removed `object_event 30, 22, SPRITE_COOL_DUDE, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, CeruleanCityCooltrainerMScript, -1`
- removed `object_event 23, 11, SPRITE_POKEMANIAC, SPRITEMOVEDATA_WANDER, 1, 1, -1, PAL_NPC_BLUE, OBJECTTYPE_COMMAND, jumptextfaceplayer, CeruleanCitySuperNerdText, -1`
- removed `pokemon_event 20, 20, SLOWBRO, SPRITEMOVEDATA_STILL, -1, PAL_NPC_PINK, CeruleanCitySlowbroText, -1`
- removed `object_event 13, 18, SPRITE_FAT_GUY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, CeruleanCityFisherScript, -1`
- removed `object_event 2, 10, SPRITE_ACE_TRAINER_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, CeruleanCaveGuardText, EVENT_BEAT_BLUE`
- removed `object_event 44, 16, SPRITE_BALL_CUT_FRUIT, SPRITEMOVEDATA_CUTTABLE_TREE, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_ROUTE_9_CUT_TREE`
+ added `warp_event 8, 9, CERULEAN_GYM_BADGE_SPEECH_HOUSE, 1`
+ added `warp_event 24, 9, CERULEAN_POLICE_STATION, 1`
+ added `warp_event 13, 13, CERULEAN_TRADE_SPEECH_HOUSE, 1`
+ added `warp_event 19, 15, CERULEAN_POKECENTER_1F, 1`
+ added `warp_event 26, 17, CERULEAN_GYM, 1`
+ added `warp_event 25, 23, CERULEAN_MART, 2`
+ added `warp_event 2, 7, CERULEAN_CAVE_1F, 1`
+ added `warp_event 13, 23, CERULEAN_BIKE_SHOP, 1`
+ added `warp_event 14, 9, CERULEAN_BERRY_POWDER_HOUSE, 1`
+ added `warp_event 19, 23, CERULEAN_COUPLE_HOUSE, 1`
+ added `warp_event 31, 9, CERULEAN_WATER_SHOW_SPEECH_HOUSE, 1`
+ added `coord_event 4, 2, SCENE_ROUTE24_BRIDGE_UNDERFOOT, CeruleanCityPrepareRoute24BridgeOverhead`
+ added `coord_event 5, 2, SCENE_ROUTE24_BRIDGE_UNDERFOOT, CeruleanCityPrepareRoute24BridgeOverhead`
+ added `coord_event 20, 2, SCENE_ROUTE24_BRIDGE_UNDERFOOT, CeruleanCityPrepareRoute24BridgeUnderfoot`
+ added `coord_event 21, 2, SCENE_ROUTE24_BRIDGE_UNDERFOOT, CeruleanCityPrepareRoute24BridgeUnderfoot`
+ added `bg_event 17, 18, BGEVENT_JUMPTEXT, CeruleanCitySignText`
+ added `bg_event 27, 17, BGEVENT_JUMPTEXT, CeruleanGymSignText`
+ added `bg_event 11, 23, BGEVENT_JUMPTEXT, CeruleanBikeShopSignText`
+ added `bg_event 29, 9, BGEVENT_JUMPTEXT, CeruleanPoliceSignText`
+ added `bg_event 19, 3, BGEVENT_JUMPTEXT, CeruleanCapeSignText`
+ added `bg_event 12, 17, BGEVENT_JUMPTEXT, CeruleanBubblerText`
+ added `bg_event 21, 25, BGEVENT_JUMPTEXT, CeruleanTrainerTipsText`
+ added `bg_event 4, 7, BGEVENT_ITEM + BERSERK_GENE, EVENT_FOUND_BERSERK_GENE_IN_CERULEAN_CITY`
+ added `bg_event 31, 15, BGEVENT_ITEM + RARE_CANDY, EVENT_CERULEAN_CITY_HIDDEN_RARE_CANDY`
+ added `object_event 21, 18, SPRITE_BATTLE_GIRL, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, CeruleanCityCooltrainerFScript, -1`
+ added `object_event 7, 6, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, CeruleanCityYoungsterScript, -1`
+ added `object_event 30, 20, SPRITE_COOL_DUDE, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, CeruleanCityCooltrainerMScript, -1`
+ added `object_event 28, 12, SPRITE_POKEMANIAC, SPRITEMOVEDATA_WANDER, 1, 1, -1, PAL_NPC_BLUE, OBJECTTYPE_COMMAND, jumptextfaceplayer, CeruleanCitySuperNerdText, -1`
+ added `pokemon_event 20, 18, SLOWBRO, SPRITEMOVEDATA_STILL, -1, PAL_MON_PINK, CeruleanCitySlowbroText, -1`
+ added `object_event 10, 17, SPRITE_FAT_GUY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, CeruleanCityFisherScript, -1`
+ added `object_event 2, 8, SPRITE_ACE_TRAINER_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, CeruleanCaveGuardText, EVENT_BEAT_BLUE`
+ added `cuttree_event 44, 14, EVENT_ROUTE_9_CUT_TREE`

## CeruleanPoliceStation

- removed `pokemon_event 3, 5, DIGLETT, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BROWN, CeruleanDiglettText, -1`
+ added `pokemon_event 3, 5, DIGLETT, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BROWN, CeruleanDiglettText, -1`

## CeruleanTradeSpeechHouse

- removed `pokemon_event 6, 2, POLIWRATH, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BLUE, CeruleanTradeSpeechHouseRhydonText, -1`
- removed `pokemon_event 5, 6, IVYSAUR, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_TEAL, CeruleanTradeSpeechHouseZubatText, -1`
+ added `pokemon_event 6, 2, POLIWRATH, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BLUE, CeruleanTradeSpeechHouseRhydonText, -1`
+ added `pokemon_event 5, 6, IVYSAUR, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_TEAL, CeruleanTradeSpeechHouseZubatText, -1`

## CharcoalKiln

+ added `bg_event 9, 1, BGEVENT_JUMPTEXT, CharcoalKilnBucketText`

## CherrygroveBay

- removed `object_event 22, 39, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerSwimmerfTara, -1`
- removed `cuttree_event -1, 8, EVENT_CHERRYGROVE_BAY_CUT_TREE`
- removed `fruittree_event 15, 11, FRUITTREE_CHERRYGROVE_BAY_5, GREPA_BERRY, PAL_NPC_YELLOW`
+ added `object_event 22, 39, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, PAL_NPC_DARK_GREEN, OBJECTTYPE_TRAINER, 4, TrainerSwimmerfTara, -1`
+ added `cuttree_event -1, 8, EVENT_CHERRYGROVE_BAY_CUT_TREE_1`
+ added `cuttree_event 24, 5, EVENT_CHERRYGROVE_BAY_CUT_TREE_2`
+ added `fruittree_event 15, 11, FRUITTREE_CHERRYGROVE_BAY_5, GREPA_BERRY, PAL_NPC_ENV_YELLOW`

## CherrygroveCity

- removed `coord_event 33, 7, 0, CherrygroveGuideGentTrigger`
- removed `coord_event 33, 6, 1, CherrygroveRivalTriggerNorth`
- removed `coord_event 33, 7, 1, CherrygroveRivalTriggerSouth`
- removed `pokemon_event 26, 13, PIDGEY, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BROWN, CherrygrovePidgeyText, -1`
+ added `coord_event 33, 7, SCENE_CHERRYGROVECITY_GUIDE_GENT, CherrygroveGuideGentTrigger`
+ added `coord_event 33, 6, SCENE_CHERRYGROVECITY_MEET_RIVAL, CherrygroveRivalTriggerNorth`
+ added `coord_event 33, 7, SCENE_CHERRYGROVECITY_MEET_RIVAL, CherrygroveRivalTriggerSouth`
+ added `pokemon_event 26, 13, PIDGEY, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BROWN, CherrygrovePidgeyText, -1`

## CherrygroveTrainTrackDual

+ added `bg_event 3, 4, BGEVENT_ITEM + PREMIER_BALL, EVENT_CHERRYGROVE_TRAIN_TRACK_DUAL_HIDDEN_PREMIER_BALL`
+ added `cuttree_event -6, 5, EVENT_CHERRYGROVE_BAY_CUT_TREE_2`
+ added `cuttree_event 11, 5, EVENT_ROUTE_30_CUT_TREE_2`

## CianwoodCity

- removed `coord_event 11, 16, 1, CianwoodCitySuicuneAndEusine`
- removed `bg_event 6, 44, BGEVENT_JUMPTEXT, CianwoodGymSignText`
- removed `bg_event 19, 47, BGEVENT_JUMPTEXT, CianwoodPharmacySignText`
- removed `bg_event 8, 32, BGEVENT_JUMPTEXT, CianwoodPhotoStudioSignText`
- removed `bg_event 8, 22, BGEVENT_JUMPTEXT, CianwoodMoveManiacSignText`
- removed `bg_event 16, 31, BGEVENT_JUMPTEXT, CianwoodAdvancedTipsSignText`
- removed `pokemon_event 10, 14, SUICUNE, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BLUE, ClearText, EVENT_SAW_SUICUNE_AT_CIANWOOD_CITY`
- removed `smashrock_event 4, 29, `
+ added `coord_event 11, 16, SCENE_CIANWOODCITY_SUICUNE_AND_EUSINE, CianwoodCitySuicuneAndEusine`
+ added `bg_event 9, 43, BGEVENT_JUMPTEXT, CianwoodGymSignText`
+ added `bg_event 18, 47, BGEVENT_JUMPTEXT, CianwoodPharmacySignText`
+ added `bg_event 12, 31, BGEVENT_JUMPTEXT, CianwoodPhotoStudioSignText`
+ added `bg_event 7, 21, BGEVENT_JUMPTEXT, CianwoodMoveManiacSignText`
+ added `bg_event 11, 37, BGEVENT_JUMPTEXT, CianwoodAdvancedTipsSignText`
+ added `pokemon_event 10, 14, SUICUNE, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_AZURE, ClearText, EVENT_SAW_SUICUNE_AT_CIANWOOD_CITY`
+ added `smashrock_event 5, 29, `

## CianwoodGym

- removed `warp_event 4, 17, CIANWOOD_CITY, 2`
- removed `warp_event 5, 17, CIANWOOD_CITY, 2`
- removed `bg_event 3, 15, BGEVENT_READ, CianwoodGymStatue`
- removed `bg_event 6, 15, BGEVENT_READ, CianwoodGymStatue`
- removed `object_event 4, 1, SPRITE_CHUCK, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, CianwoodGymChuckScript, -1`
- removed `strengthboulder_event 5, 1, `
- removed `object_event 2, 12, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBlackbeltYoshi, -1`
- removed `object_event 7, 12, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBlackbeltLao, -1`
- removed `object_event 3, 9, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerBlackbeltNob, -1`
- removed `object_event 5, 5, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerBlackbeltLung, -1`
- removed `object_event 7, 15, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, CianwoodGymBlackBeltText, -1`
- removed `strengthboulder_event 3, 7, `
- removed `strengthboulder_event 4, 7, `
- removed `strengthboulder_event 5, 7, `
+ added `warp_event 12, 17, CIANWOOD_CITY, 2`
+ added `warp_event 13, 17, CIANWOOD_CITY, 2`
+ added `warp_event 12, 4, CIANWOOD_GYM, 1`
+ added `warp_event 13, 4, CIANWOOD_GYM, 2`
+ added `bg_event 11, 15, BGEVENT_READ, CianwoodGymStatue`
+ added `bg_event 14, 15, BGEVENT_READ, CianwoodGymStatue`
+ added `object_event 12, 11, SPRITE_CHUCK, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, CianwoodGymChuckScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_4`
+ added `object_event 12, 11, SPRITE_BIG_HO_OH, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_COMMAND, jumptext, CianwoodGymChuckTrainingText, EVENT_BOULDERS_IN_CIANWOOD_GYM`
+ added `object_event 13, 11, SPRITE_BOULDER_ROCK, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptext, CianwoodGymChucksBoulderText, -1`
+ added `strengthboulder_event 9, 4, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
+ added `strengthboulder_event 16, 4, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_3`
+ added `object_event 12, 4, SPRITE_BOULDER_ROCK, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptext, CianwoodGymBoulderText, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_4`
+ added `object_event 13, 4, SPRITE_BOULDER_ROCK, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptext, CianwoodGymBoulderText, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_5`
+ added `object_event 5, 10, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerBlackbeltYoshi, -1`
+ added `object_event 21, 10, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerBlackbeltLao, -1`
+ added `object_event 9, 6, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerBlackbeltNob, -1`
+ added `object_event 20, 6, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerBlackbeltLung, -1`
+ added `object_event 15, 15, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, CianwoodGymBlackBeltText, -1`

## CinnabarLab

- removed `coord_event 2, 6, 1, CinnabarLabCelebiEventScript`
- removed `pokemon_event 15, 7, MEWTWO, SPRITEMOVEDATA_STILL, -1, PAL_NPC_PURPLE, ClearText, EVENT_CINNABAR_LAB_MEWTWO`
+ added `coord_event 2, 6, SCENE_CINNABARLAB_CELEBI_EVENT, CinnabarLabCelebiEventScript`
+ added `pokemon_event 15, 7, MEWTWO, SPRITEMOVEDATA_STILL, -1, PAL_MON_PURPLE, ClearText, EVENT_CINNABAR_LAB_MEWTWO`
+ added `object_event 15, 8, SPRITE_BETA, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_CINNABAR_LAB_BETA`

## CinnabarVolcanoB1F

- removed `warp_event 23, 13, CINNABAR_VOLCANO_1F, 8`
- removed `warp_event 20, 8, CINNABAR_VOLCANO_1F, 10`
+ added `warp_event 24, 13, CINNABAR_VOLCANO_1F, 8`
+ added `warp_event 20, 9, CINNABAR_VOLCANO_1F, 10`

## CinnabarVolcanoB2F

- removed `object_event 18, 22, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, MOLTRES, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, PLAIN_FORM, CinnabarVolcanoMoltres, EVENT_CINNABAR_VOLCANO_MOLTRES`
- removed `itemball_event 18, 3, FLAME_ORB, 1, EVENT_CINNABAR_VOLCANO_B2F_FLAME_ORB`
+ added `object_event 18, 22, SPRITE_AQUARIUM_MON, SPRITEMOVEDATA_POKEMON, 0, MOLTRES, -1, PAL_NPC_MOLTRES, OBJECTTYPE_SCRIPT, PLAIN_FORM, CinnabarVolcanoMoltres, EVENT_CINNABAR_VOLCANO_MOLTRES`
+ added `itemball_event 19, 4, FLAME_ORB, 1, EVENT_CINNABAR_VOLCANO_B2F_FLAME_ORB`

## CopycatsHouse1F

- removed `pokemon_event 4, 5, BLISSEY, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_PINK, CopycatsHouse1FBlisseyText, -1`
+ added `pokemon_event 4, 5, BLISSEY, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_PINK, CopycatsHouse1FBlisseyText, -1`

## CopycatsHouse2F

- removed `object_event 4, 3, SPRITE_COPYCAT, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_SCRIPT, 0, Copycat1Script, EVENT_COPYCAT_1`
- removed `object_event 4, 3, SPRITE_COPYCAT, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_SCRIPT, 0, Copycat2Script, EVENT_COPYCAT_2`
- removed `object_event 4, 3, SPRITE_COPYCAT, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_SCRIPT, 0, Copycat3Script, EVENT_COPYCAT_3`
- removed `object_event 6, 4, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, DODRIO, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, NO_FORM, CopycatsDodrioScript, -1`
- removed `object_event 6, 1, SPRITE_MON_ICON, SPRITEMOVEDATA_STILL, 0, CLEFAIRY, -1, PAL_NPC_PINK, OBJECTTYPE_SCRIPT, NO_FORM, CopycatsHouse2FDollScript, EVENT_COPYCATS_HOUSE_2F_DOLL`
- removed `object_event 2, 1, SPRITE_MON_ICON, SPRITEMOVEDATA_STILL, 0, GENGAR, -1, PAL_NPC_PURPLE, OBJECTTYPE_SCRIPT, NO_FORM, CopycatsHouse2FDollScript, -1`
- removed `object_event 7, 1, SPRITE_MON_ICON, SPRITEMOVEDATA_STILL, 0, MURKROW, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, NO_FORM, CopycatsHouse2FDollScript, -1`
- removed `pokemon_event 0, 4, DITTO, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_PURPLE, CopycatsHouse2FDittoText, -1`
+ added `object_event 4, 3, SPRITE_COPYCAT, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_TEAL, OBJECTTYPE_SCRIPT, 0, CopycatScript, -1`
+ added `object_event 6, 4, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, DODRIO, -1, PAL_MON_BROWN, OBJECTTYPE_SCRIPT, NO_FORM, CopycatsDodrioScript, -1`
+ added `object_event 6, 1, SPRITE_MON_ICON, SPRITEMOVEDATA_STILL, 0, CLEFAIRY, -1, PAL_MON_PINK, OBJECTTYPE_SCRIPT, NO_FORM, CopycatsHouse2FDollScript, EVENT_COPYCATS_HOUSE_2F_DOLL`
+ added `object_event 2, 1, SPRITE_MON_ICON, SPRITEMOVEDATA_STILL, 0, GENGAR, -1, PAL_MON_PURPLE, OBJECTTYPE_SCRIPT, NO_FORM, CopycatsHouse2FDollScript, -1`
+ added `object_event 7, 1, SPRITE_MON_ICON, SPRITEMOVEDATA_STILL, 0, MURKROW, -1, PAL_MON_BLUE, OBJECTTYPE_SCRIPT, NO_FORM, CopycatsHouse2FDollScript, -1`
+ added `pokemon_event 0, 4, DITTO, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_PURPLE, CopycatsHouse2FDittoText, -1`

## DanceTheatre

- removed `object_event 6, 2, SPRITE_KIMONO_GIRL, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, PAL_NPC_GRAY, OBJECTTYPE_TRAINER, 0, GenericTrainerKimono_girlZuki, -1`
- removed `object_event 11, 2, SPRITE_KIMONO_GIRL, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 0, GenericTrainerKimono_girlMiki, -1`
- removed `pokemon_event 6, 10, RHYDON, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BROWN, RhydonText, -1`
+ added `object_event 6, 2, SPRITE_KIMONO_GIRL, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, PAL_NPC_BLACK, OBJECTTYPE_TRAINER, 0, GenericTrainerKimono_girlZuki, -1`
+ added `object_event 11, 2, SPRITE_KIMONO_GIRL, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, PAL_NPC_YELLOW, OBJECTTYPE_TRAINER, 0, GenericTrainerKimono_girlMiki, -1`
+ added `pokemon_event 6, 10, RHYDON, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BROWN, RhydonText, -1`

## DarkCaveVioletEntrance

- removed `coord_event 6, 2, 0, DarkCaveVioletEntranceFalknerTrigger`
- removed `pokemon_event 10, 2, URSARING, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BROWN, ClearText, EVENT_DARK_CAVE_URSARING`
+ added `coord_event 6, 2, SCENE_DARKCAVEVIOLETENTRANCE_FALKNER, DarkCaveVioletEntranceFalknerTrigger`
+ added `pokemon_event 10, 2, URSARING, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BROWN, ClearText, EVENT_DARK_CAVE_URSARING`

## DimCave1F

- removed `object_event 27, 21, SPRITE_ROCKER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerGuitaristmBiff, -1`
+ added `object_event 27, 21, SPRITE_ROCKER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, PAL_NPC_DARK_RED, OBJECTTYPE_TRAINER, 2, TrainerGuitaristmBiff, -1`

## DimCave2F

- removed `warp_event 26, 32, DIM_CAVE_1F, 4`
- removed `object_event 14, 21, SPRITE_BOULDER_ROCK_FOSSIL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptext, DimCaveFallenBoulderText, EVENT_BOULDER_FELL_IN_DIM_CAVE_2F`
- removed `tmhmball_event 31, 33, TM_FACADE, EVENT_DIM_CAVE_2F_TM_FACADE`
+ added `warp_event 2, 28, DIM_CAVE_1F, 4`
+ added `object_event 14, 21, SPRITE_BOULDER_ROCK, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptext, DimCaveFallenBoulderText, EVENT_BOULDER_FELL_IN_DIM_CAVE_2F`
+ added `tmhmball_event 7, 29, TM_FACADE, EVENT_DIM_CAVE_2F_TM_FACADE`

## DimCave3F

- removed `object_event 15, 8, SPRITE_BOULDER_ROCK_FOSSIL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptext, DimCaveFallenBoulderText, EVENT_BOULDER_FELL_IN_DIM_CAVE_3F`
+ added `object_event 15, 8, SPRITE_BOULDER_ROCK, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptext, DimCaveFallenBoulderText, EVENT_BOULDER_FELL_IN_DIM_CAVE_3F`

## DimCave4F

- removed `object_event 27, 25, SPRITE_BOULDER_ROCK_FOSSIL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptext, DimCaveFallenBoulderText, EVENT_BOULDER_FELL_IN_DIM_CAVE_4F`
+ added `object_event 27, 25, SPRITE_BOULDER_ROCK, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptext, DimCaveFallenBoulderText, EVENT_BOULDER_FELL_IN_DIM_CAVE_4F`

## DragonShrine

- removed `warp_event 4, 9, DRAGONS_DEN_B1F, 2`
- removed `warp_event 5, 9, DRAGONS_DEN_B1F, 2`
- removed `object_event 5, 1, SPRITE_ELDER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, DragonShrineElder1Script, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1`
- removed `object_event 4, 8, SPRITE_CLAIR, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_DRAGON_SHRINE_CLAIR`
- removed `object_event 2, 4, SPRITE_ELDER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_COMMAND, jumptextfaceplayer, DragonShrineElder2Text, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1`
- removed `object_event 7, 4, SPRITE_ELDER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_COMMAND, jumptextfaceplayer, DragonShrineElder3Text, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1`
+ added `warp_event 4, 13, DRAGONS_DEN_B1F, 2`
+ added `warp_event 5, 13, DRAGONS_DEN_B1F, 2`
+ added `warp_event 4, 1, DRAGONS_DEN_B1F, 3`
+ added `warp_event 5, 1, DRAGONS_DEN_B1F, 4`
+ added `object_event 4, 5, SPRITE_ELDER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, DragonShrineElder1Script, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1`
+ added `object_event 5, 12, SPRITE_CLAIR, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_DRAGON_SHRINE_CLAIR`
+ added `object_event 3, 2, SPRITE_KIMONO_GIRL, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, PAL_NPC_PINK, OBJECTTYPE_SCRIPT, 0, KimonoGirlMinaScript, -1`
+ added `object_event 2, 8, SPRITE_ELDER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_COMMAND, jumptextfaceplayer, DragonShrineElder2Text, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1`
+ added `object_event 7, 8, SPRITE_ELDER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_COMMAND, jumptextfaceplayer, DragonShrineElder3Text, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1`

## DragonsDen1F

- removed `warp_event 15, 55, BLACKTHORN_CITY, 8`
- removed `warp_event 15, 53, DRAGONS_DEN_1F, 4`
- removed `warp_event 5, 55, DRAGONS_DEN_B1F, 1`
- removed `warp_event 5, 53, DRAGONS_DEN_1F, 2`
+ added `warp_event 15, 5, BLACKTHORN_CITY, 8`
+ added `warp_event 15, 3, DRAGONS_DEN_1F, 4`
+ added `warp_event 5, 5, DRAGONS_DEN_B1F, 1`
+ added `warp_event 5, 3, DRAGONS_DEN_1F, 2`

## DragonsDenB1F

- removed `coord_event 19, 30, 1, DragonsDenB1FClairTrigger`
- removed `object_event 34, 19, SPRITE_KIMONO_GIRL, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, PAL_NPC_PINK, OBJECTTYPE_SCRIPT, 0, KimonoGirlMinaScript, -1`
+ added `warp_event 19, 26, DRAGON_SHRINE, 3`
+ added `warp_event 20, 26, DRAGON_SHRINE, 4`
+ added `coord_event 19, 30, SCENE_DRAGONSDENB1F_CLAIR_GIVES_TM, DragonsDenB1FClairTrigger`
+ added `object_event 19, 26, SPRITE_PAGODA, SPRITEMOVEDATA_PAGODA_LEFT, 0, 0, -1, 0, OBJECTTYPE_COMMAND, end, NULL, -1`
+ added `object_event 20, 26, SPRITE_PAGODA, SPRITEMOVEDATA_PAGODA_RIGHT, 0, 0, -1, 0, OBJECTTYPE_COMMAND, end, NULL, -1`

## EcruteakCity

- removed `warp_event 35, 26, ROUTE_42_ECRUTEAK_GATE, 1`
- removed `warp_event 35, 27, ROUTE_42_ECRUTEAK_GATE, 2`
- removed `warp_event 5, 17, VALERIES_HOUSE, 1`
- removed `warp_event 0, 18, ROUTE_38_ECRUTEAK_GATE, 3`
- removed `warp_event 0, 19, ROUTE_38_ECRUTEAK_GATE, 4`
- removed `warp_event 13, 17, ECRUTEAK_DESTINY_KNOT_HOUSE, 1`
- removed `bg_event 8, 28, BGEVENT_JUMPTEXT, EcruteakGymSign`
- removed `bg_event 21, 26, BGEVENT_JUMPTEXT, EcruteakCityAdvancedTips`
- removed `bg_event 1, 17, BGEVENT_ITEM + ULTRA_BALL, EVENT_ECRUTEAK_CITY_HIDDEN_ULTRA_BALL`
- removed `object_event 19, 26, SPRITE_CUTE_GIRL, SPRITEMOVEDATA_WALK_UP_DOWN, 1, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_COMMAND, jumptextfaceplayer, EcruteakCityLass1Text, -1`
- removed `pokemon_event 12, 11, SMEARGLE, SPRITEMOVEDATA_POKEMON, (1 << MORN) | (1 << DAY), PAL_NPC_BROWN, EcruteakCitySmeargleText, -1`
+ added `warp_event 35, 22, ROUTE_42_ECRUTEAK_GATE, 1`
+ added `warp_event 35, 23, ROUTE_42_ECRUTEAK_GATE, 2`
+ added `warp_event 5, 16, VALERIES_HOUSE, 1`
+ added `warp_event 0, 22, ROUTE_38_ECRUTEAK_GATE, 3`
+ added `warp_event 0, 23, ROUTE_38_ECRUTEAK_GATE, 4`
+ added `warp_event 13, 16, ECRUTEAK_DESTINY_KNOT_HOUSE, 1`
+ added `bg_event 7, 27, BGEVENT_JUMPTEXT, EcruteakGymSign`
+ added `bg_event 9, 15, BGEVENT_JUMPTEXT, EcruteakCityAdvancedTips`
+ added `bg_event 1, 21, BGEVENT_ITEM + ULTRA_BALL, EVENT_ECRUTEAK_CITY_HIDDEN_ULTRA_BALL`
+ added `object_event 20, 26, SPRITE_CUTE_GIRL, SPRITEMOVEDATA_WALK_UP_DOWN, 1, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_COMMAND, jumptextfaceplayer, EcruteakCityLass1Text, -1`
+ added `pokemon_event 12, 11, SMEARGLE, SPRITEMOVEDATA_POKEMON, (1 << MORN) | (1 << DAY), PAL_MON_BROWN, EcruteakCitySmeargleText, -1`
+ added `object_event 23, 18, SPRITE_PAGODA, SPRITEMOVEDATA_PAGODA_LEFT, 0, 0, -1, 0, OBJECTTYPE_COMMAND, end, NULL, -1`
+ added `object_event 24, 18, SPRITE_PAGODA, SPRITEMOVEDATA_PAGODA_RIGHT, 0, 0, -1, 0, OBJECTTYPE_COMMAND, end, NULL, -1`

## EcruteakGym

- removed `warp_event 4, 17, ECRUTEAK_CITY, 10`
- removed `warp_event 5, 17, ECRUTEAK_CITY, 10`
- removed `warp_event 4, 14, ECRUTEAK_GYM, 4`
- removed `warp_event 6, 8, ECRUTEAK_GYM, 3`
- removed `warp_event 2, 9, ECRUTEAK_GYM, 3`
- removed `warp_event 3, 12, ECRUTEAK_GYM, 3`
- removed `warp_event 7, 11, ECRUTEAK_GYM, 3`
- removed `warp_event 7, 13, ECRUTEAK_GYM, 3`
- removed `bg_event 3, 15, BGEVENT_READ, EcruteakGymStatue`
- removed `bg_event 6, 15, BGEVENT_READ, EcruteakGymStatue`
- removed `object_event 4, 14, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_ECRUTEAK_GYM_GRAMPS`
- removed `object_event 2, 7, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerSageJeffrey, -1`
- removed `object_event 3, 13, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerSagePing, -1`
- removed `object_event 7, 9, SPRITE_GRANNY, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerMediumGrace, -1`
- removed `object_event 7, 15, SPRITE_GYM_GUY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, EcruteakGymGuyScript, -1`
+ added `warp_event 4, 21, ECRUTEAK_CITY, 10`
+ added `warp_event 5, 21, ECRUTEAK_CITY, 10`
+ added `warp_event 4, 18, ECRUTEAK_GYM, 4`
+ added `warp_event 6, 4, ECRUTEAK_GYM, 3`
+ added `warp_event 5, 7, ECRUTEAK_GYM, 3`
+ added `warp_event 3, 8, ECRUTEAK_GYM, 3`
+ added `warp_event 7, 9, ECRUTEAK_GYM, 3`
+ added `warp_event 6, 10, ECRUTEAK_GYM, 3`
+ added `warp_event 4, 11, ECRUTEAK_GYM, 3`
+ added `warp_event 6, 12, ECRUTEAK_GYM, 3`
+ added `warp_event 2, 14, ECRUTEAK_GYM, 3`
+ added `warp_event 3, 14, ECRUTEAK_GYM, 3`
+ added `warp_event 4, 14, ECRUTEAK_GYM, 3`
+ added `warp_event 5, 14, ECRUTEAK_GYM, 3`
+ added `warp_event 7, 14, ECRUTEAK_GYM, 3`
+ added `warp_event 5, 15, ECRUTEAK_GYM, 3`
+ added `warp_event 7, 15, ECRUTEAK_GYM, 3`
+ added `warp_event 2, 16, ECRUTEAK_GYM, 3`
+ added `warp_event 3, 16, ECRUTEAK_GYM, 3`
+ added `warp_event 4, 16, ECRUTEAK_GYM, 3`
+ added `warp_event 5, 16, ECRUTEAK_GYM, 3`
+ added `warp_event 7, 16, ECRUTEAK_GYM, 3`
+ added `warp_event 2, 17, ECRUTEAK_GYM, 3`
+ added `warp_event 7, 17, ECRUTEAK_GYM, 3`
+ added `bg_event 3, 19, BGEVENT_READ, EcruteakGymStatue`
+ added `bg_event 6, 19, BGEVENT_READ, EcruteakGymStatue`
+ added `object_event 4, 18, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_ECRUTEAK_GYM_GRAMPS`
+ added `object_event 2, 9, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerSageJeffrey, -1`
+ added `object_event 3, 17, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerSagePing, -1`
+ added `object_event 7, 13, SPRITE_GRANNY, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerMediumGrace, -1`
+ added `object_event 7, 19, SPRITE_GYM_GUY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, EcruteakGymGuyScript, -1`

## EcruteakHouse

- removed `coord_event 4, 7, 0, EcruteakHouse_XYTrigger1`
- removed `coord_event 5, 7, 0, EcruteakHouse_XYTrigger2`
+ added `coord_event 4, 7, SCENE_ECRUTEAKHOUSE_SAGE_BLOCKS, EcruteakHouse_XYTrigger1`
+ added `coord_event 5, 7, SCENE_ECRUTEAKHOUSE_SAGE_BLOCKS, EcruteakHouse_XYTrigger2`

## EcruteakShrineInside

- removed `warp_event 5, 11, ECRUTEAK_SHRINE_OUTSIDE, 1`
- removed `warp_event 6, 11, ECRUTEAK_SHRINE_OUTSIDE, 1`
- removed `bg_event 5, 6, BGEVENT_JUMPTEXT, EcruteakShrineInsideAltarText`
- removed `bg_event 6, 6, BGEVENT_JUMPTEXT, EcruteakShrineInsideAltarText`
- removed `object_event 7, 6, SPRITE_SABRINA, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, EcruteakShrineInsideReiScript, -1`
- removed `object_event 3, 8, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, EcruteakShrineInsideGrampsText, -1`
- removed `object_event 10, 5, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, EcruteakShrineInsideSageText, -1`
- removed `pokemon_event 10, 3, FURRET, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BROWN, ClearText, -1`
+ added `warp_event 5, 9, ECRUTEAK_SHRINE_OUTSIDE, 1`
+ added `warp_event 6, 9, ECRUTEAK_SHRINE_OUTSIDE, 1`
+ added `bg_event 5, 1, BGEVENT_JUMPTEXT, EcruteakShrineInsideAltarText`
+ added `bg_event 6, 1, BGEVENT_JUMPTEXT, EcruteakShrineInsideAltarText`
+ added `bg_event 4, 0, BGEVENT_JUMPTEXT, EcruteakShrineInsideSignText`
+ added `bg_event 7, 0, BGEVENT_JUMPTEXT, EcruteakShrineInsideSignText`
+ added `object_event 4, 2, SPRITE_SABRINA, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, EcruteakShrineInsideReiScript, -1`
+ added `object_event 3, 6, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, EcruteakShrineInsideGrampsText, -1`
+ added `object_event 10, 6, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, EcruteakShrineInsideSageText, -1`
+ added `pokemon_event 9, 6, FURRET, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BROWN, EcruteakShrineInsideFurretText, -1`

## EcruteakShrineOutside

- removed `pokemon_event 9, 8, HOOTHOOT, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BROWN, EcruteakShrineOutsideHoothootText, -1`
+ added `pokemon_event 9, 8, HOOTHOOT, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BROWN, EcruteakShrineOutsideHoothootText, -1`

## ElmsLab

- removed `coord_event 4, 6, 1, LabTryToLeaveScript`
- removed `coord_event 5, 6, 1, LabTryToLeaveScript`
- removed `coord_event 4, 5, 3, MeetCopScript`
- removed `coord_event 5, 5, 3, MeetCopScript2`
- removed `coord_event 4, 8, 5, AideScript_WalkPotions1`
- removed `coord_event 5, 8, 5, AideScript_WalkPotions2`
- removed `coord_event 4, 6, 6, LyraBattleScript`
- removed `object_event 6, 3, SPRITE_BALL_CUT_FRUIT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_POKE_BALL, OBJECTTYPE_SCRIPT, 0, CyndaquilPokeBallScript, EVENT_CYNDAQUIL_POKEBALL_IN_ELMS_LAB`
- removed `object_event 7, 3, SPRITE_BALL_CUT_FRUIT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_DECO_ITEM, OBJECTTYPE_SCRIPT, 0, TotodilePokeBallScript, EVENT_TOTODILE_POKEBALL_IN_ELMS_LAB`
- removed `object_event 8, 3, SPRITE_BALL_CUT_FRUIT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_KEY_ITEM, OBJECTTYPE_SCRIPT, 0, ChikoritaPokeBallScript, EVENT_CHIKORITA_POKEBALL_IN_ELMS_LAB`
+ added `coord_event 4, 6, SCENE_ELMSLAB_CANT_LEAVE, LabTryToLeaveScript`
+ added `coord_event 5, 6, SCENE_ELMSLAB_CANT_LEAVE, LabTryToLeaveScript`
+ added `coord_event 4, 5, SCENE_ELMSLAB_MEET_OFFICER, MeetCopScript`
+ added `coord_event 5, 5, SCENE_ELMSLAB_MEET_OFFICER, MeetCopScript2`
+ added `coord_event 4, 8, SCENE_ELMSLAB_AIDE_GIVES_POTION, AideScript_WalkPotions1`
+ added `coord_event 5, 8, SCENE_ELMSLAB_AIDE_GIVES_POTION, AideScript_WalkPotions2`
+ added `coord_event 4, 6, SCENE_ELMSLAB_LYRA_BATTLE, LyraBattleScript`
+ added `object_event 6, 3, SPRITE_BALL_CUT_TREE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_ENV_RED, OBJECTTYPE_SCRIPT, 0, CyndaquilPokeBallScript, EVENT_CYNDAQUIL_POKEBALL_IN_ELMS_LAB`
+ added `object_event 7, 3, SPRITE_BALL_CUT_TREE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_ENV_BLUE, OBJECTTYPE_SCRIPT, 0, TotodilePokeBallScript, EVENT_TOTODILE_POKEBALL_IN_ELMS_LAB`
+ added `object_event 8, 3, SPRITE_BALL_CUT_TREE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_ENV_GREEN, OBJECTTYPE_SCRIPT, 0, ChikoritaPokeBallScript, EVENT_CHIKORITA_POKEBALL_IN_ELMS_LAB`

## FarawayIsland -> FarawayIslandSouth

- removed `warp_event 22, 8, FARAWAY_JUNGLE, 1`
- removed `warp_event 23, 8, FARAWAY_JUNGLE, 2`
- removed `bg_event 4, 34, BGEVENT_JUMPTEXT, FarawayIslandSignText`
- removed `object_event 12, 42, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, FarawayIslandSailorScript, EVENT_OLIVINE_PORT_SAILOR_AT_GANGWAY`
- removed `object_event 3, 37, SPRITE_LAWRENCE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, FarawayIslandLawrenceScript, EVENT_LAWRENCE_FARAWAY_ISLAND`
+ added `bg_event 4, 4, BGEVENT_JUMPTEXT, FarawayIslandSouthSignText`
+ added `object_event 12, 12, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, FarawayIslandSouthSailorScript, EVENT_OLIVINE_PORT_SAILOR_AT_GANGWAY`
+ added `object_event 3, 7, SPRITE_LAWRENCE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, FarawayIslandSouthLawrenceScript, EVENT_LAWRENCE_FARAWAY_ISLAND`
+ added `object_event 22, 4, SPRITE_PEARL, SPRITEMOVEDATA_CUTTABLE_TREE, 0, 0, -1, PAL_NPC_FARAWAY_ROCK, OBJECTTYPE_COMMAND, end, NULL, -1`
+ added `object_event 8, 8, SPRITE_PEARL, SPRITEMOVEDATA_CUTTABLE_TREE, 0, 0, -1, PAL_NPC_FARAWAY_ROCK, OBJECTTYPE_COMMAND, end, NULL, -1`
+ added `object_event 7, 9, SPRITE_PEARL, SPRITEMOVEDATA_CUTTABLE_TREE, 0, 0, -1, PAL_NPC_FARAWAY_ROCK, OBJECTTYPE_COMMAND, end, NULL, -1`
+ added `object_event 3, 11, SPRITE_PEARL, SPRITEMOVEDATA_CUTTABLE_TREE, 0, 0, -1, PAL_NPC_FARAWAY_ROCK, OBJECTTYPE_COMMAND, end, NULL, -1`
+ added `object_event 6, 14, SPRITE_PEARL, SPRITEMOVEDATA_CUTTABLE_TREE, 0, 0, -1, PAL_NPC_FARAWAY_ROCK, OBJECTTYPE_COMMAND, end, NULL, -1`

## FarawayIslandNorth

+ added `warp_event 22, 8, FARAWAY_JUNGLE, 1`
+ added `warp_event 23, 8, FARAWAY_JUNGLE, 2`
+ added `object_event 30, 26, SPRITE_PEARL, SPRITEMOVEDATA_CUTTABLE_TREE, 0, 0, -1, PAL_NPC_FARAWAY_ROCK, OBJECTTYPE_COMMAND, end, NULL, -1`
+ added `object_event 22, 34, SPRITE_PEARL, SPRITEMOVEDATA_CUTTABLE_TREE, 0, 0, -1, PAL_NPC_FARAWAY_ROCK, OBJECTTYPE_COMMAND, end, NULL, -1`

## FarawayJungle

- removed `warp_event 12, 18, FARAWAY_ISLAND, 1`
- removed `warp_event 13, 18, FARAWAY_ISLAND, 2`
+ added `warp_event 12, 18, FARAWAY_ISLAND_NORTH, 1`
+ added `warp_event 13, 18, FARAWAY_ISLAND_NORTH, 2`

## FastShip1F

- removed `coord_event 24, 6, 2, WorriedGrandpaTriggerLeft`
- removed `coord_event 25, 6, 2, WorriedGrandpaTriggerRight`
+ added `coord_event 24, 6, SCENE_FASTSHIP1F_MEET_GRANDPA, WorriedGrandpaTriggerLeft`
+ added `coord_event 25, 6, SCENE_FASTSHIP1F_MEET_GRANDPA, WorriedGrandpaTriggerRight`

## FastShipB1F

- removed `coord_event 26, 5, 0, FastShipB1FSailorBlocksLeft`
- removed `coord_event 27, 5, 0, FastShipB1FSailorBlocksRight`
- removed `object_event 13, 2, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerSailorGarrett, EVENT_FAST_SHIP_PASSENGERS_EASTBOUND`
+ added `coord_event 26, 5, SCENE_FASTSHIPB1F_SAILOR_BLOCKS, FastShipB1FSailorBlocksLeft`
+ added `coord_event 27, 5, SCENE_FASTSHIPB1F_SAILOR_BLOCKS, FastShipB1FSailorBlocksRight`
+ added `bg_event 23, 7, BGEVENT_IFNOTSET, FastShipB1FJugglerFritzSeasickTrashScript`
+ added `object_event 13, 2, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_DARK_BLUE, OBJECTTYPE_TRAINER, 4, TrainerSailorGarrett, EVENT_FAST_SHIP_PASSENGERS_EASTBOUND`

## FightingDojo

- removed `object_event 0, 1, SPRITE_BIG_DOLL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, RematchRed0Script, EVENT_REMATCH_GYM_LEADER_1`
- removed `object_event 0, 2, SPRITE_COPYCAT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, RematchGreen1Script, EVENT_REMATCH_GYM_LEADER_2`
- removed `object_event 0, 3, SPRITE_COPYCAT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, RematchBlue1Script, EVENT_REMATCH_GYM_LEADER_3`
- removed `object_event 0, 4, SPRITE_CONSOLE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, RematchBlue2Script, EVENT_REMATCH_GYM_LEADER_4`
- removed `object_event 0, 5, SPRITE_COPYCAT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, RematchBrown1Script, EVENT_REMATCH_GYM_LEADER_5`
- removed `object_event 0, 6, SPRITE_CONSOLE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, RematchBrown2Script, EVENT_REMATCH_GYM_LEADER_6`
- removed `object_event 4, 4, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, FightingDojoBlackBelt, -1`
+ added `object_event 0, 1, FIGHTINGDOJO_REMATCH_VARSPRITE_1, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, FightingDojoRematch1Script, EVENT_REMATCH_GYM_LEADER_1`
+ added `object_event 0, 2, FIGHTINGDOJO_REMATCH_VARSPRITE_2, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, FightingDojoRematch2Script, EVENT_REMATCH_GYM_LEADER_2`
+ added `object_event 0, 3, FIGHTINGDOJO_REMATCH_VARSPRITE_3, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, FightingDojoRematch3Script, EVENT_REMATCH_GYM_LEADER_3`
+ added `object_event 4, 3, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, FightingDojoBlackBelt, -1`

## FuchsiaAquarium1F

+ added `warp_event 6, 9, FUCHSIA_CITY, 12`
+ added `warp_event 7, 9, FUCHSIA_CITY, 13`
+ added `warp_event 10, 2, FUCHSIA_AQUARIUM_2F, 1`
+ added `bg_event 1, 5, BGEVENT_READ, FuchsiaAquarium1FGoldeenOrQwilfishSign`
+ added `bg_event 2, 5, BGEVENT_READ, FuchsiaAquarium1FMagikarpSign`
+ added `bg_event 13, 5, BGEVENT_READ, FuchsiaAquarium1FCorsolaSign`
+ added `bg_event 15, 5, BGEVENT_READ, FuchsiaAquarium1FTentacoolOrHorseaSign`
+ added `bg_event 16, 5, BGEVENT_READ, FuchsiaAquarium1FChinchouSign`
+ added `bg_event 8, 3, BGEVENT_JUMPTEXT, FuchsiaAquarium1FLaprasStatueSignText`
+ added `bg_event 5, 2, BGEVENT_JUMPTEXT, FuchsiaAquarium1FPoster1Text`
+ added `bg_event 6, 2, BGEVENT_JUMPTEXT, FuchsiaAquarium1FPoster2Text`
+ added `object_event 1, 4, SPRITE_AQUARIUM_MON, SPRITEMOVEDATA_AQUARIUM_TOP, 0, GOLDEEN, -1, PAL_NPC_AQUA_RED, OBJECTTYPE_DONOTHING, NO_FORM, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1`
+ added `object_event 1, 4, SPRITE_AQUARIUM_MON, SPRITEMOVEDATA_AQUARIUM_TOP, 0, QWILFISH, -1, PAL_NPC_AQUA_PURPLE, OBJECTTYPE_DONOTHING, HISUIAN_FORM, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
+ added `object_event 2, 4, SPRITE_AQUARIUM_MON, SPRITEMOVEDATA_ADMIN_MEOWTH, 0, MAGIKARP, -1, PAL_NPC_AQUA_RED, OBJECTTYPE_DONOTHING, NO_FORM, DoNothingScript, -1`
+ added `object_event 13, 4, SPRITE_AQUARIUM_MON, SPRITEMOVEDATA_AQUARIUM_BOTTOM, 0, CORSOLA, -1, PAL_NPC_AQUA_RED, OBJECTTYPE_DONOTHING, NO_FORM, DoNothingScript, -1`
+ added `object_event 15, 4, SPRITE_AQUARIUM_MON, SPRITEMOVEDATA_AQUARIUM_TOP, 0, TENTACOOL, -1, PAL_NPC_AQUA_BLUE, OBJECTTYPE_DONOTHING, NO_FORM, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1`
+ added `object_event 15, 4, SPRITE_AQUARIUM_MON, SPRITEMOVEDATA_AQUARIUM_TOP, 0, HORSEA, -1, PAL_NPC_AQUA_BLUE, OBJECTTYPE_DONOTHING, NO_FORM, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
+ added `object_event 16, 4, SPRITE_AQUARIUM_MON, SPRITEMOVEDATA_AQUARIUM_BOTTOM, 0, CHINCHOU, -1, PAL_NPC_AQUA_BLUE, OBJECTTYPE_DONOTHING, NO_FORM, DoNothingScript, -1`
+ added `object_event 3, 9, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_COMMAND, jumptextfaceplayer, FuchsiaAquarium1FReceptionistText, -1`
+ added `object_event 1, 9, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_COMMAND, jumptextfaceplayer, FuchsiaAquarium1FOfficerText, -1`
+ added `object_event 9, 6, SPRITE_CUTE_GIRL, SPRITEMOVEDATA_WANDER, 1, 1, -1, PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, FuchsiaAquarium1FCuteGirlText, -1`
+ added `object_event 4, 4, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_COMMAND, jumptextfaceplayer, FuchsiaAquarium1FSchoolboyText, -1`
+ added `object_event 13, 9, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, FuchsiaAquarium1FFisherText, -1`
+ added `object_event 14, 9, SPRITE_AROMA_LADY, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_ORANGE, OBJECTTYPE_COMMAND, jumptextfaceplayer, FuchsiaAquarium1FAromaLadyText, -1`

## FuchsiaAquarium2F

+ added `warp_event 10, 2, FUCHSIA_AQUARIUM_1F, 3`
+ added `bg_event 1, 5, BGEVENT_READ, FuchsiaAquarium1FRemoraidSign`
+ added `bg_event 2, 5, BGEVENT_READ, FuchsiaAquarium1FMantineSign`
+ added `bg_event 6, 5, BGEVENT_READ, FuchsiaAquarium1FSquirtleOrSeelSign`
+ added `bg_event 15, 5, BGEVENT_READ, FuchsiaAquarium1FShellderOrKrabbySign`
+ added `bg_event 16, 5, BGEVENT_READ, FuchsiaAquarium1FStaryuSign`
+ added `bg_event 12, 2, BGEVENT_JUMPTEXT, FuchsiaAquarium2FPosterText`
+ added `object_event 1, 4, SPRITE_AQUARIUM_MON, SPRITEMOVEDATA_ADMIN_MEOWTH, 0, REMORAID, -1, PAL_NPC_AQUA_BLUE, OBJECTTYPE_DONOTHING, NO_FORM, DoNothingScript, -1`
+ added `object_event 2, 4, SPRITE_AQUARIUM_MON, SPRITEMOVEDATA_AQUARIUM_TOP, 0, MANTINE, -1, PAL_NPC_AQUA_BLUE, OBJECTTYPE_DONOTHING, NO_FORM, DoNothingScript, -1`
+ added `object_event 6, 4, SPRITE_AQUARIUM_MON, SPRITEMOVEDATA_AQUARIUM_BOTTOM, 0, SQUIRTLE, -1, PAL_NPC_AQUA_BLUE, OBJECTTYPE_DONOTHING, NO_FORM, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1`
+ added `object_event 6, 4, SPRITE_AQUARIUM_MON, SPRITEMOVEDATA_ADMIN_MEOWTH, 0, SEEL, -1, PAL_NPC_AQUA_BLUE, OBJECTTYPE_DONOTHING, NO_FORM, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
+ added `object_event 15, 4, SPRITE_AQUARIUM_MON, SPRITEMOVEDATA_AQUARIUM_BOTTOM, 0, SHELLDER, -1, PAL_NPC_AQUA_PURPLE, OBJECTTYPE_DONOTHING, NO_FORM, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1`
+ added `object_event 15, 4, SPRITE_AQUARIUM_MON, SPRITEMOVEDATA_AQUARIUM_BOTTOM, 0, KRABBY, -1, PAL_NPC_AQUA_RED, OBJECTTYPE_DONOTHING, NO_FORM, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
+ added `object_event 16, 4, SPRITE_AQUARIUM_MON, SPRITEMOVEDATA_AQUARIUM_BOTTOM, 0, STARYU, -1, PAL_NPC_AQUA_BROWN, OBJECTTYPE_DONOTHING, NO_FORM, DoNothingScript, -1`
+ added `object_event 12, 8, SPRITE_POKEFAN_M, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, FuchsiaAquarium2FPokefanMScript, -1`
+ added `object_event 16, 7, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_COMMAND, jumptextfaceplayer, FuchsiaAquarium2FPokefanFText, -1`
+ added `object_event 2, 7, SPRITE_LASS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_DARK_RED, OBJECTTYPE_SCRIPT, 0, FuchsiaAquarium2FLassScript, -1`
+ added `object_event 3, 7, SPRITE_BATTLE_GIRL, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_AZURE, OBJECTTYPE_SCRIPT, 0, FuchsiaAquarium2FBattleGirlScript, -1`

## FuchsiaCity

- removed `warp_event 8, 27, FUCHSIA_GYM, 1`
- removed `bg_event 21, 15, BGEVENT_JUMPTEXT, FuchsiaCitySignText`
- removed `bg_event 5, 29, BGEVENT_JUMPTEXT, FuchsiaGymSignText`
- removed `bg_event 25, 15, BGEVENT_JUMPTEXT, SafariZoneOfficeSignText`
- removed `bg_event 7, 7, BGEVENT_JUMPTEXT, SafariZoneExhibitSignText`
- removed `bg_event 13, 7, BGEVENT_JUMPTEXT, SafariZoneExhibitSignText`
- removed `bg_event 27, 7, BGEVENT_JUMPTEXT, SafariZoneExhibitSignText`
- removed `bg_event 33, 7, BGEVENT_JUMPTEXT, SafariZoneExhibitSignText`
- removed `bg_event 31, 13, BGEVENT_JUMPTEXT, SafariZoneExhibitSignText`
- removed `object_event 23, 18, SPRITE_CAMPER, SPRITEMOVEDATA_WANDER, 1, 1, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, FuchsiaCityYoungsterText, -1`
- removed `object_event 28, 8, SPRITE_POKEFAN_F, SPRITEMOVEDATA_WANDER, 2, 2, -1, PAL_NPC_BLUE, OBJECTTYPE_COMMAND, jumptextfaceplayer, FuchsiaCityPokefanFText, -1`
- removed `object_event 22, 13, SPRITE_RATTATA_BACK, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptext, SafariZoneOfficeClosedSignText, -1`
- removed `object_event 31, 27, SPRITE_RATTATA_BACK, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptext, HouseForSaleSignText, -1`
+ added `warp_event 6, 27, FUCHSIA_GYM, 1`
+ added `warp_event 22, 13, FUCHSIA_AQUARIUM_1F, 1`
+ added `warp_event 23, 13, FUCHSIA_AQUARIUM_1F, 2`
+ added `bg_event 25, 19, BGEVENT_JUMPTEXT, FuchsiaCitySignText`
+ added `bg_event 7, 27, BGEVENT_JUMPTEXT, FuchsiaGymSignText`
+ added `bg_event 21, 16, BGEVENT_JUMPTEXT, FuchsiaZooSignText`
+ added `bg_event 7, 7, BGEVENT_READ, FuchsiaCityZooDratiniSign`
+ added `bg_event 13, 7, BGEVENT_READ, FuchsiaCityZooKangaskhanSign`
+ added `bg_event 27, 7, BGEVENT_READ, FuchsiaCityZooTaurosSign`
+ added `bg_event 33, 7, BGEVENT_READ, FuchsiaCityZooChanseySign`
+ added `bg_event 31, 13, BGEVENT_READ, FuchsiaCityZooSlowpokeSign`
+ added `bg_event 9, 15, BGEVENT_READ, FuchsiaCityZooLaprasSign`
+ added `bg_event 26, 13, BGEVENT_JUMPTEXT, FuchsiaAquariumSignText`
+ added `bg_event 31, 27, BGEVENT_JUMPTEXT, HouseForSaleSignText`
+ added `bg_event 26, 12, BGEVENT_ITEM + NUGGET, EVENT_FUCHSIA_CITY_HIDDEN_NUGGET`
+ added `object_event 19, 18, SPRITE_CAMPER, SPRITEMOVEDATA_WANDER, 1, 1, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, FuchsiaCityYoungsterText, -1`
+ added `object_event 30, 9, SPRITE_POKEFAN_F, SPRITEMOVEDATA_WANDER, 2, 2, -1, PAL_NPC_BLUE, OBJECTTYPE_COMMAND, jumptextfaceplayer, FuchsiaCityPokefanFText, -1`
+ added `pokemon_event 6, 5, DRATINI, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_AZURE, EmptyString, -1`
+ added `pokemon_event 12, 6, KANGASKHAN, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BROWN, EmptyString, -1`
+ added `pokemon_event 26, 6, TAUROS, TAUROS_PALDEAN_FIRE_FORM, SPRITEMOVEDATA_POKEMON, 1 << MORN, PAL_MON_RED, EmptyString, -1`
+ added `pokemon_event 25, 6, TAUROS, NO_FORM, SPRITEMOVEDATA_POKEMON, 1 << DAY, PAL_MON_BROWN, EmptyString, -1`
+ added `pokemon_event 25, 5, TAUROS, PALDEAN_FORM, SPRITEMOVEDATA_POKEMON, 1 << EVE, PAL_MON_BLACK, EmptyString, -1`
+ added `pokemon_event 26, 5, TAUROS, TAUROS_PALDEAN_WATER_FORM, SPRITEMOVEDATA_POKEMON, 1 << NITE, PAL_MON_BLUE, EmptyString, -1`
+ added `pokemon_event 31, 5, CHANSEY, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_PINK, EmptyString, -1`
+ added `pokemon_event 30, 12, SLOWPOKE, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_PINK, EmptyString, -1`
+ added `object_event 8, 17, SPRITE_LAPRAS, SPRITEMOVEDATA_SWIM_AROUND, 2, 1, -1, 0, OBJECTTYPE_DONOTHING, NO_FORM, DoNothingScript, -1`

## GiovannisCave

- removed `warp_event 15, 7, TOHJO_FALLS, 3`
- removed `bg_event 15, 2, BGEVENT_READ, GiovannisCaveRadioScript`
- removed `bg_event 12, 6, BGEVENT_ITEM + BERSERK_GENE, EVENT_GIOVANNIS_CAVE_HIDDEN_BERSERK_GENE`
- removed `object_event 15, 6, SPRITE_CELEBI, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_GIOVANNIS_CAVE_CELEBI`
- removed `object_event 14, 5, SPRITE_LYRA, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_GIOVANNIS_CAVE_LYRA`
- removed `object_event 15, 3, SPRITE_GIOVANNI, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_GIOVANNIS_CAVE_GIOVANNI`
- removed `smashrock_event 13, 6, `
- removed `smashrock_event 16, 2, `
+ added `warp_event 5, 7, TOHJO_FALLS, 3`
+ added `bg_event 5, 2, BGEVENT_READ, GiovannisCaveRadioScript`
+ added `bg_event 2, 6, BGEVENT_ITEM + BERSERK_GENE, EVENT_GIOVANNIS_CAVE_HIDDEN_BERSERK_GENE`
+ added `object_event 5, 6, SPRITE_CELEBI, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_GIOVANNIS_CAVE_CELEBI`
+ added `object_event 4, 5, SPRITE_LYRA, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_GIOVANNIS_CAVE_LYRA`
+ added `object_event 5, 3, SPRITE_GIOVANNI, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_GIOVANNIS_CAVE_GIOVANNI`
+ added `smashrock_event 3, 6, `
+ added `smashrock_event 6, 2, `

## GoldenrodBandHouse

- removed `object_event 6, 4, SPRITE_ROCKER, SPRITEMOVEDATA_WALK_UP_DOWN, 1, 0, -1, PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, GoldenrodBandHouseRocker2Text, -1`
- removed `object_event 2, 4, SPRITE_BATTLE_GIRL, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, GoldenrodBandHouseCooltrainerFText, -1`
+ added `object_event 6, 4, SPRITE_ROCKER, SPRITEMOVEDATA_WALK_UP_DOWN, 1, 0, -1, PAL_NPC_DARK_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, GoldenrodBandHouseRocker2Text, -1`
+ added `object_event 2, 4, SPRITE_BATTLE_GIRL, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_DARK_GREEN, OBJECTTYPE_COMMAND, jumptextfaceplayer, GoldenrodBandHouseCooltrainerFText, -1`

## GoldenrodCity

- removed `warp_event 13, 5, UNDERGROUND_PATH_SWITCH_ROOM_ENTRANCES, 8`
- removed `warp_event 13, 29, UNDERGROUND_PATH_SWITCH_ROOM_ENTRANCES, 5`
- removed `warp_event 30, 15, GOLDENROD_MUSEUM_1F, 2`
- removed `warp_event 39, 27, UNDERGROUND_PATH_SWITCH_ROOM_ENTRANCES, 11`
- removed `coord_event 9, 15, 1, GoldenrodCityPanUpScript`
- removed `bg_event 14, 14, BGEVENT_JUMPTEXT, GoldenrodCityStationSignText`
- removed `bg_event 30, 9, BGEVENT_JUMPTEXT, GoldenrodGymSignText`
- removed `bg_event 16, 7, BGEVENT_JUMPTEXT, GoldenrodCityNameRaterSignText`
- removed `bg_event 34, 6, BGEVENT_JUMPTEXT, GoldenrodCityFlowerShopSignText`
+ added `warp_event 13, 5, GOLDENROD_UNDERGROUND_ENTRANCES, 5`
+ added `warp_event 13, 29, GOLDENROD_UNDERGROUND_ENTRANCES, 2`
+ added `warp_event 30, 15, GOLDENROD_MUSEUM_1F, 1`
+ added `warp_event 39, 27, GOLDENROD_UNDERGROUND_ENTRANCES, 8`
+ added `warp_event 19, 21, GOLDENROD_GAME_CORNER, 2`
+ added `warp_event 29, 27, GOLDENROD_DEPT_STORE_1F, 2`
+ added `warp_event 31, 15, GOLDENROD_MUSEUM_1F, 2`
+ added `coord_event 9, 15, SCENE_GOLDENRODCITY_NOOP, GoldenrodCityPanUpScript`
+ added `bg_event 15, 14, BGEVENT_JUMPTEXT, GoldenrodCityStationSignText`
+ added `bg_event 29, 7, BGEVENT_JUMPTEXT, GoldenrodGymSignText`
+ added `bg_event 17, 7, BGEVENT_JUMPTEXT, GoldenrodCityNameRaterSignText`
+ added `bg_event 35, 6, BGEVENT_JUMPTEXT, GoldenrodCityFlowerShopSignText`

## GoldenrodDeptStore1F

- removed `warp_event 8, 7, GOLDENROD_CITY, 9`
+ added `warp_event 8, 7, GOLDENROD_CITY, 24`

## GoldenrodDeptStoreB1F

- removed `warp_event 17, 2, UNDERGROUND_WAREHOUSE, 3`
- removed `warp_event 10, 4, GOLDENROD_DEPT_STORE_ELEVATOR, 2`
- removed `pokemon_event 7, 7, MACHOKE, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_GRAY, GoldenrodDeptStoreB1FMachokeText, -1`
+ added `warp_event 17, 2, GOLDENROD_UNDERGROUND_WAREHOUSE, 3`
+ added `pokemon_event 7, 7, MACHOKE, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_GRAY, GoldenrodDeptStoreB1FMachokeText, -1`

## GoldenrodGameCorner

- removed `warp_event 3, 13, GOLDENROD_CITY, 10`
+ added `warp_event 3, 13, GOLDENROD_CITY, 23`

## GoldenrodGym

- removed `coord_event 8, 5, 1, WhitneyCriesScript`
- removed `object_event 9, 13, SPRITE_LASS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerLassCathy, -1`
+ added `coord_event 8, 5, SCENE_GOLDENRODGYM_WHITNEY_STOPS_CRYING, WhitneyCriesScript`
+ added `object_event 9, 13, SPRITE_LASS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_DARK_BLUE, OBJECTTYPE_TRAINER, 4, TrainerLassCathy, -1`

## GoldenrodHarbor

- removed `object_event 21, 15, SPRITE_MON_ICON, SPRITEMOVEDATA_STILL, 0, MAGIKARP, -1, PAL_NPC_ORANGE, OBJECTTYPE_SCRIPT, PLAIN_FORM, GoldenrodHarborMagikarpScript, -1`
- removed `object_event 6, 14, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 5, GenericTrainerSwimmerfKatie, -1`
+ added `object_event 21, 15, SPRITE_MON_ICON, SPRITEMOVEDATA_STILL, 0, MAGIKARP, -1, PAL_MON_ORANGE, OBJECTTYPE_SCRIPT, PLAIN_FORM, GoldenrodHarborMagikarpScript, -1`
+ added `object_event 6, 14, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_DARK_GREEN, OBJECTTYPE_TRAINER, 5, TrainerSwimmerfKatie, -1`

## GoldenrodHoneyHouse

- removed `pokemon_event 6, 3, BUTTERFREE, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BLUE, GoldenrodHoneyHouseButterfreeText, -1`
+ added `pokemon_event 6, 3, BUTTERFREE, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BLUE, GoldenrodHoneyHouseButterfreeText, -1`

## GoldenrodMagnetTrainStation

- removed `coord_event 11, 6, 0, Script_ArriveFromSaffron`
+ added `coord_event 11, 6, SCENE_GOLDENRODMAGNETTRAINSTATION_ARRIVE_FROM_SAFFRON, Script_ArriveFromSaffron`

## GoldenrodMuseum1F

- removed `warp_event 7, 7, GOLDENROD_CITY, 18`
- removed `object_event 12, 3, SPRITE_BIG_LAPRAS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_PEARL, OBJECTTYPE_COMMAND, jumptext, GoldenrodMuseum1FBigPearlText, -1`
+ added `warp_event 7, 7, GOLDENROD_CITY, 25`
+ added `object_event 12, 3, SPRITE_PEARL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_PEARL, OBJECTTYPE_COMMAND, jumptext, GoldenrodMuseum1FBigPearlText, -1`

## GoldenrodMuseum2F

- removed `object_event 4, 2, SPRITE_SIGHTSEER_M, SPRITEMOVEDATA_STANDING_UP, 0, 0, (1 << EVE) | (1 << NITE), 0, OBJECTTYPE_SCRIPT, 0, GoldenrodMuseum2FSightseerMScript, -1`
- removed `pokemon_event 5, 2, SMEARGLE, SPRITEMOVEDATA_POKEMON, (1 << EVE) | (1 << NITE), PAL_NPC_BROWN, GoldenrodMuseum2FSmeargleText, -1`
+ added `object_event 4, 2, SPRITE_SIGHTSEER_M, SPRITEMOVEDATA_STANDING_UP, 0, 0, (1 << EVE) | (1 << NITE), 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, GoldenrodMuseum2FSightseerMText, -1`
+ added `pokemon_event 5, 2, SMEARGLE, SPRITEMOVEDATA_POKEMON, (1 << EVE) | (1 << NITE), PAL_MON_BROWN, GoldenrodMuseum2FSmeargleText, -1`

## GoldenrodPokecomCenter1F

- removed `object_event 3, 9, SPRITE_ICE_BOULDER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_POKECOM_SIGN, OBJECTTYPE_SCRIPT, 0, InfoSignScript, -1`
- removed `object_event 23, 3, SPRITE_ICE_BOULDER, SPRITEMOVEDATA_POKECOM_NEWS, 0, 0, -1, PAL_NPC_POKECOM_SIGN, OBJECTTYPE_COMMAND, end, NULL, -1`
+ added `object_event 3, 9, SPRITE_BOULDER_ROCK, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_POKECOM_SIGN, OBJECTTYPE_SCRIPT, 0, InfoSignScript, -1`
+ added `object_event 23, 3, SPRITE_FLOATING_BALL, SPRITEMOVEDATA_POKECOM_NEWS, 0, 0, -1, PAL_NPC_POKECOM_SIGN, OBJECTTYPE_COMMAND, end, NULL, -1`

## GoldenrodPokecomCenterOffice

- removed `bg_event 3, 2, BGEVENT_JUMPTEXT, RangiComputerText`
- removed `bg_event 6, 2, BGEVENT_JUMPTEXT, LunaComputerText`
- removed `bg_event 9, 2, BGEVENT_JUMPTEXT, FredrikComputerText`
- removed `bg_event 9, 5, BGEVENT_JUMPTEXT, VulcanComputerText`
- removed `bg_event 6, 5, BGEVENT_JUMPTEXT, AizawaComputerText`
- removed `bg_event 4, 2, BGEVENT_READ, RangiKeyboardScript`
- removed `object_event 4, 4, SPRITE_SCIENTIST_F, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, PAL_NPC_RANGI, OBJECTTYPE_COMMAND, jumptextfaceplayer, AdminRangiText, -1`
+ added `bg_event 3, 2, BGEVENT_UP, RangiComputerScript`
+ added `bg_event 6, 2, BGEVENT_UP, LunaComputerScript`
+ added `bg_event 9, 2, BGEVENT_UP, FredrikComputerScript`
+ added `bg_event 12, 2, BGEVENT_UP, EmiComputerScript`
+ added `bg_event 6, 5, BGEVENT_UP, AizawaComputerScript`
+ added `bg_event 9, 5, BGEVENT_UP, VulcanComputerScript`
+ added `bg_event 12, 5, BGEVENT_UP, SourComputerScript`
+ added `object_event 4, 4, SPRITE_SCIENTIST_F, SPRITEMOVEDATA_WALK_UP_DOWN, 1, 0, -1, PAL_NPC_RANGI, OBJECTTYPE_COMMAND, jumptextfaceplayer, AdminRangiText, -1`
+ added `object_event 13, 3, SPRITE_DAISY, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_EMI, OBJECTTYPE_COMMAND, jumptextfaceplayer, AdminEmiText, -1`
+ added `object_event 13, 6, SPRITE_FAT_GUY, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_COMMAND, jumptextfaceplayer, AdminSourText, -1`
+ added `object_event 4, 1, SPRITE_MON_ICON, SPRITEMOVEDATA_ADMIN_MEOWTH, 0, MEOWTH, -1, PAL_MON_BROWN, OBJECTTYPE_SCRIPT, NO_FORM, AdminEldredScript, -1`

## GoldenrodUndergroundEntrances

+ added `warp_event 4, 19, GOLDENROD_UNDERGROUND, 2`
+ added `warp_event 4, 23, GOLDENROD_CITY, 14`
+ added `warp_event 5, 23, GOLDENROD_CITY, 14`
+ added `warp_event 4, 5, GOLDENROD_UNDERGROUND, 1`
+ added `warp_event 4, 9, GOLDENROD_CITY, 13`
+ added `warp_event 5, 9, GOLDENROD_CITY, 13`
+ added `warp_event 4, 33, GOLDENROD_UNDERGROUND, 7`
+ added `warp_event 4, 37, GOLDENROD_CITY, 22`
+ added `warp_event 5, 37, GOLDENROD_CITY, 22`
+ added `object_event 3, 21, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, GoldenrodUndergroundEntrances_TeacherText, -1`
+ added `object_event 8, 20, SPRITE_SUPER_NERD, SPRITEMOVEDATA_WALK_UP_DOWN, 2, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, GoldenrodUndergroundEntrances_SuperNerd1Text, -1`
+ added `object_event 3, 7, SPRITE_BUG_MANIAC, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, GoldenrodUndergroundEntrances_SuperNerd2Text, -1`
+ added `object_event 1, 35, SPRITE_VETERAN_M, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 1, -1, PAL_NPC_GRAY, OBJECTTYPE_SCRIPT, 0, GoldenrodUndergroundEntrancesVeteranMScript, -1`
+ added `object_event 8, 34, SPRITE_BEAUTY, SPRITEMOVEDATA_WALK_UP_DOWN, 1, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, GoldenrodUndergroundEntrances_BeautyText, -1`

## GoldenrodUndergroundSwitchRoom

+ added `warp_event 28, 2, GOLDENROD_UNDERGROUND, 6`
+ added `warp_event 27, 8, GOLDENROD_UNDERGROUND_WAREHOUSE, 1`
+ added `warp_event 28, 8, GOLDENROD_UNDERGROUND_WAREHOUSE, 2`
+ added `coord_event 23, 1, SCENE_GOLDENRODUNDERGROUNDSWITCHROOM_RIVAL_BATTLE, UndergroundRivalTrigger1`
+ added `coord_event 23, 2, SCENE_GOLDENRODUNDERGROUNDSWITCHROOM_RIVAL_BATTLE, UndergroundRivalTrigger2`
+ added `coord_event 23, 3, SCENE_GOLDENRODUNDERGROUNDSWITCHROOM_RIVAL_BATTLE, UndergroundRivalTrigger3`
+ added `bg_event 11, 4, BGEVENT_UP, RedSwitchScript`
+ added `bg_event 10, 4, BGEVENT_UP, GreenSwitchScript`
+ added `bg_event 9, 4, BGEVENT_UP, BlueSwitchScript`
+ added `bg_event 25, 8, BGEVENT_UP, EmergencySwitchScript`
+ added `bg_event 16, 6, BGEVENT_ITEM + MAX_POTION, EVENT_GOLDENROD_UNDERGROUND_SWITCH_ROOM_HIDDEN_MAX_POTION`
+ added `bg_event 3, 2, BGEVENT_ITEM + REVIVE, EVENT_GOLDENROD_UNDERGROUND_SWITCH_ROOM_HIDDEN_REVIVE`
+ added `object_event 28, 2, SPRITE_RIVAL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_RIVAL_GOLDENROD_UNDERGROUND`
+ added `object_event 9, 10, SPRITE_BURGLAR, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerBurglarDuncan, EVENT_RADIO_TOWER_ROCKET_TAKEOVER`
+ added `object_event 3, 6, SPRITE_BURGLAR, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerBurglarOrson, EVENT_RADIO_TOWER_ROCKET_TAKEOVER`
+ added `object_event 20, 5, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerGruntM13, EVENT_RADIO_TOWER_ROCKET_TAKEOVER`
+ added `object_event 18, 1, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerGruntM11, EVENT_RADIO_TOWER_ROCKET_TAKEOVER`
+ added `object_event 5, 1, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerGruntM25, EVENT_RADIO_TOWER_ROCKET_TAKEOVER`
+ added `object_event 24, 9, SPRITE_ROCKET_GIRL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerGruntF3, EVENT_RADIO_TOWER_ROCKET_TAKEOVER`
+ added `itemball_event 4, 10, SMOKE_BALL, 1, EVENT_GOLDENROD_UNDERGROUND_SWITCH_ROOM_SMOKE_BALL`
+ added `itemball_event 10, 2, FULL_HEAL, 1, EVENT_GOLDENROD_UNDERGROUND_SWITCH_ROOM_FULL_HEAL`

## HiddenCaveGrotto

- removed `warp_event 35, 85, HIDDEN_CAVE_GROTTO, -1`
- removed `bg_event 34, 74, BGEVENT_GROTTOITEM, HiddenGrottoHiddenItemScript`
- removed `object_event 34, 74, SPRITE_GROTTO_MON, SPRITEMOVEDATA_POKEMON, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, HiddenGrottoPokemonScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1`
- removed `object_event 34, 74, SPRITE_BALL_CUT_FRUIT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_POKE_BALL, OBJECTTYPE_SCRIPT, 0, HiddenGrottoItemScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
+ added `warp_event 3, 9, HIDDEN_CAVE_GROTTO, -1`
+ added `bg_event 3, 3, BGEVENT_GROTTOITEM, HiddenGrottoHiddenItemScript`
+ added `object_event 3, 3, SPRITE_GROTTO_MON, SPRITEMOVEDATA_POKEMON, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, HiddenGrottoPokemonScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1`
+ added `object_event 3, 3, SPRITE_BALL_CUT_TREE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_ENV_RED, OBJECTTYPE_SCRIPT, 0, HiddenGrottoItemScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`

## HiddenTreeGrotto

- removed `warp_event 4, 15, HIDDEN_TREE_GROTTO, -1`
- removed `warp_event 5, 15, HIDDEN_TREE_GROTTO, -1`
- removed `bg_event 4, 4, BGEVENT_GROTTOITEM, HiddenGrottoHiddenItemScript`
- removed `object_event 4, 4, SPRITE_GROTTO_MON, SPRITEMOVEDATA_POKEMON, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, HiddenGrottoPokemonScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1`
- removed `object_event 4, 4, SPRITE_BALL_CUT_FRUIT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_POKE_BALL, OBJECTTYPE_SCRIPT, 0, HiddenGrottoItemScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
+ added `warp_event 3, 9, HIDDEN_TREE_GROTTO, -1`
+ added `bg_event 3, 3, BGEVENT_GROTTOITEM, HiddenGrottoHiddenItemScript`
+ added `object_event 3, 3, SPRITE_GROTTO_MON, SPRITEMOVEDATA_POKEMON, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, HiddenGrottoPokemonScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1`
+ added `object_event 3, 3, SPRITE_BALL_CUT_TREE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_ENV_RED, OBJECTTYPE_SCRIPT, 0, HiddenGrottoItemScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`

## IceIsland

- removed `itemball_event 19, 6, ICY_ROCK, 1, EVENT_ICE_ISLAND_ICY_ROCK`
+ added `itemball_event 17, 6, ICY_ROCK, 1, EVENT_ICE_ISLAND_ICY_ROCK`

## IcePathB1F

- removed `object_event 11, 7, SPRITE_ICE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, PAL_NPC_COPY_BG_BROWN, OBJECTTYPE_COMMAND, jumpstd, strengthboulder, EVENT_BOULDER_IN_ICE_PATH_1`
- removed `object_event 7, 8, SPRITE_ICE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, PAL_NPC_COPY_BG_BROWN, OBJECTTYPE_COMMAND, jumpstd, strengthboulder, EVENT_BOULDER_IN_ICE_PATH_2`
- removed `object_event 8, 9, SPRITE_ICE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, PAL_NPC_COPY_BG_BROWN, OBJECTTYPE_COMMAND, jumpstd, strengthboulder, EVENT_BOULDER_IN_ICE_PATH_3`
- removed `object_event 17, 7, SPRITE_ICE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, PAL_NPC_COPY_BG_BROWN, OBJECTTYPE_COMMAND, jumpstd, strengthboulder, EVENT_BOULDER_IN_ICE_PATH_4`
+ added `object_event 11, 7, SPRITE_ICE_BOULDER_FOSSILS, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, PAL_NPC_COPY_BG_BROWN, OBJECTTYPE_COMMAND, jumpstd, strengthboulder, EVENT_BOULDER_IN_ICE_PATH_1`
+ added `object_event 7, 8, SPRITE_ICE_BOULDER_FOSSILS, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, PAL_NPC_COPY_BG_BROWN, OBJECTTYPE_COMMAND, jumpstd, strengthboulder, EVENT_BOULDER_IN_ICE_PATH_2`
+ added `object_event 8, 9, SPRITE_ICE_BOULDER_FOSSILS, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, PAL_NPC_COPY_BG_BROWN, OBJECTTYPE_COMMAND, jumpstd, strengthboulder, EVENT_BOULDER_IN_ICE_PATH_3`
+ added `object_event 17, 7, SPRITE_ICE_BOULDER_FOSSILS, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, PAL_NPC_COPY_BG_BROWN, OBJECTTYPE_COMMAND, jumpstd, strengthboulder, EVENT_BOULDER_IN_ICE_PATH_4`

## IcePathB2FMahoganySide

- removed `object_event 11, 3, SPRITE_ICE_BOULDER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_COPY_BG_BROWN, OBJECTTYPE_COMMAND, jumptext, IcePathB2FMahoganySideBoulderText, EVENT_BOULDER_IN_ICE_PATH_1A`
- removed `object_event 4, 7, SPRITE_ICE_BOULDER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_COPY_BG_BROWN, OBJECTTYPE_COMMAND, jumptext, IcePathB2FMahoganySideBoulderText, EVENT_BOULDER_IN_ICE_PATH_2A`
- removed `object_event 3, 12, SPRITE_ICE_BOULDER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_COPY_BG_BROWN, OBJECTTYPE_COMMAND, jumptext, IcePathB2FMahoganySideBoulderText, EVENT_BOULDER_IN_ICE_PATH_3A`
- removed `object_event 12, 13, SPRITE_ICE_BOULDER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_COPY_BG_BROWN, OBJECTTYPE_COMMAND, jumptext, IcePathB2FMahoganySideBoulderText, EVENT_BOULDER_IN_ICE_PATH_4A`
+ added `object_event 11, 3, SPRITE_ICE_BOULDER_FOSSILS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_COPY_BG_BROWN, OBJECTTYPE_COMMAND, jumptext, IcePathB2FMahoganySideBoulderText, EVENT_BOULDER_IN_ICE_PATH_1A`
+ added `object_event 4, 7, SPRITE_ICE_BOULDER_FOSSILS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_COPY_BG_BROWN, OBJECTTYPE_COMMAND, jumptext, IcePathB2FMahoganySideBoulderText, EVENT_BOULDER_IN_ICE_PATH_2A`
+ added `object_event 3, 12, SPRITE_ICE_BOULDER_FOSSILS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_COPY_BG_BROWN, OBJECTTYPE_COMMAND, jumptext, IcePathB2FMahoganySideBoulderText, EVENT_BOULDER_IN_ICE_PATH_3A`
+ added `object_event 12, 13, SPRITE_ICE_BOULDER_FOSSILS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_COPY_BG_BROWN, OBJECTTYPE_COMMAND, jumptext, IcePathB2FMahoganySideBoulderText, EVENT_BOULDER_IN_ICE_PATH_4A`

## IlexForest

- removed `coord_event 9, 31, 2, IlexForestApprenticeTrigger`
+ added `coord_event 9, 31, SCENE_ILEXFOREST_NOOP, IlexForestApprenticeTrigger`

## IndigoPlateauPokecenter1F

- removed `coord_event 14, 4, 0, PlateauRivalBattleTrigger1`
- removed `coord_event 15, 4, 0, PlateauRivalBattleTrigger2`
- removed `pokemon_event 5, 9, ABRA, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BROWN, IndigoPlateauAbraText, EVENT_TELEPORT_GUY`
+ added `coord_event 14, 4, SCENE_INDIGOPLATEAUPOKECENTER1F_RIVAL_BATTLE, PlateauRivalBattleTrigger1`
+ added `coord_event 15, 4, SCENE_INDIGOPLATEAUPOKECENTER1F_RIVAL_BATTLE, PlateauRivalBattleTrigger2`
+ added `pokemon_event 5, 9, ABRA, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BROWN, IndigoPlateauAbraText, EVENT_TELEPORT_GUY`

## IvysLab

- removed `object_event 5, 3, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, NIDORINO, -1, PAL_NPC_PURPLE, OBJECTTYPE_SCRIPT, NO_FORM, IvysLabNidorinoScript, -1`
+ added `object_event 5, 3, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, NIDORINO, -1, PAL_MON_PURPLE, OBJECTTYPE_SCRIPT, NO_FORM, IvysLabNidorinoScript, -1`

## KurtsHouse

- removed `pokemon_event 6, 3, SLOWPOKE, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_PINK, KurtsHouseSlowpokeText, EVENT_KURTS_HOUSE_SLOWPOKE`
+ added `pokemon_event 6, 3, SLOWPOKE, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_PINK, KurtsHouseSlowpokeText, EVENT_KURTS_HOUSE_SLOWPOKE`

## LancesRoom

- removed `coord_event 6, 5, 1, ApproachLanceFromLeftTrigger`
- removed `coord_event 7, 5, 1, ApproachLanceFromRightTrigger`
+ added `coord_event 6, 5, SCENE_LANCESROOM_APPROACH_LANCE, ApproachLanceFromLeftTrigger`
+ added `coord_event 7, 5, SCENE_LANCESROOM_APPROACH_LANCE, ApproachLanceFromRightTrigger`

## LuckyIsland

- removed `object_event 27, 18, SPRITE_BALL_CUT_FRUIT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_POKE_BALL, OBJECTTYPE_SCRIPT, 0, LuckyIslandLuckyEgg, EVENT_LUCKY_ISLAND_LUCKY_EGG`
- removed `object_event 29, 6, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerFisherHall, EVENT_LUCKY_ISLAND_CIVILIANS`
- removed `object_event 21, 16, SPRITE_BAKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerBakerMargaret, EVENT_LUCKY_ISLAND_CIVILIANS`
- removed `object_event 32, 23, SPRITE_BAKER, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBakerOlga, EVENT_LUCKY_ISLAND_CIVILIANS`
- removed `object_event 20, 21, SPRITE_ARTIST, SPRITEMOVEDATA_SPINCOUNTERCLOCKWISE, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerArtistReina, EVENT_LUCKY_ISLAND_CIVILIANS`
- removed `object_event 36, 16, SPRITE_ARTIST, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerArtistAlina, EVENT_LUCKY_ISLAND_CIVILIANS`
- removed `object_event 23, 11, SPRITE_SIGHTSEER_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerSightseersLiandsu1, EVENT_LUCKY_ISLAND_CIVILIANS`
- removed `object_event 23, 12, SPRITE_LADY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerSightseersLiandsu2, EVENT_LUCKY_ISLAND_CIVILIANS`
- removed `fruittree_event 25, 16, FRUITTREE_LUCKY_ISLAND, JABOCA_BERRY, PAL_NPC_YELLOW, MORN, EVENT_LUCKY_ISLAND_CIVILIANS`
- removed `fruittree_event 25, 16, FRUITTREE_LUCKY_ISLAND, ROWAP_BERRY, PAL_NPC_TEAL, DAY, EVENT_LUCKY_ISLAND_CIVILIANS`
- removed `fruittree_event 25, 16, FRUITTREE_LUCKY_ISLAND, KEE_BERRY, PAL_NPC_PINK, EVE, EVENT_LUCKY_ISLAND_CIVILIANS`
- removed `fruittree_event 25, 16, FRUITTREE_LUCKY_ISLAND, MARANGABERRY, PAL_NPC_BROWN, NITE, EVENT_LUCKY_ISLAND_CIVILIANS`
+ added `object_event 33, 18, SPRITE_BALL_CUT_TREE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_ENV_RED, OBJECTTYPE_SCRIPT, 0, LuckyIslandLuckyEgg, EVENT_LUCKY_ISLAND_LUCKY_EGG`
+ added `object_event 35, 6, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerFisherHall, EVENT_LUCKY_ISLAND_CIVILIANS`
+ added `object_event 27, 16, SPRITE_BAKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerBakerMargaret, EVENT_LUCKY_ISLAND_CIVILIANS`
+ added `object_event 38, 23, SPRITE_BAKER, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBakerOlga, EVENT_LUCKY_ISLAND_CIVILIANS`
+ added `object_event 26, 21, SPRITE_ARTIST, SPRITEMOVEDATA_SPINCOUNTERCLOCKWISE, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerArtistReina, EVENT_LUCKY_ISLAND_CIVILIANS`
+ added `object_event 42, 16, SPRITE_ARTIST, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerArtistAlina, EVENT_LUCKY_ISLAND_CIVILIANS`
+ added `object_event 29, 11, SPRITE_SIGHTSEER_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerSightseersLiandsu1, EVENT_LUCKY_ISLAND_CIVILIANS`
+ added `object_event 29, 12, SPRITE_LADY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerSightseersLiandsu2, EVENT_LUCKY_ISLAND_CIVILIANS`
+ added `fruittree_event 31, 16, FRUITTREE_LUCKY_ISLAND, JABOCA_BERRY, PAL_NPC_ENV_YELLOW, MORN, EVENT_LUCKY_ISLAND_CIVILIANS`
+ added `fruittree_event 31, 16, FRUITTREE_LUCKY_ISLAND, ROWAP_BERRY, PAL_NPC_TEAL, DAY, EVENT_LUCKY_ISLAND_CIVILIANS`
+ added `fruittree_event 31, 16, FRUITTREE_LUCKY_ISLAND, KEE_BERRY, PAL_NPC_PINK, EVE, EVENT_LUCKY_ISLAND_CIVILIANS`
+ added `fruittree_event 31, 16, FRUITTREE_LUCKY_ISLAND, MARANGABERRY, PAL_NPC_BROWN, NITE, EVENT_LUCKY_ISLAND_CIVILIANS`
+ added `object_event -3, 15, SPRITE_BIRD_KEEPER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, -1`

## LyrasHouse2F

- removed `bg_event 5, 1, BGEVENT_READ, LyrasHouseRadio`
- removed `pokemon_event 3, 3, PIDGEOT, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BROWN, LyrasHousePidgeotText, EVENT_LYRA_IN_HER_ROOM`
+ added `bg_event 5, 1, BGEVENT_READ, InitialRadio`
+ added `pokemon_event 3, 3, PIDGEOT, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BROWN, LyrasHousePidgeotText, EVENT_LYRA_IN_HER_ROOM`

## MagnetTunnelEast

- removed `warp_event 8, 7, MAGNET_TUNNEL_INSIDE, 2`
- removed `cuttree_event 19, 11, EVENT_MAGNET_TUNNEL_EAST_CUT_TREE`
- removed `smashrock_event 12, 8, `
- removed `smashrock_event 13, 4, `
- removed `smashrock_event 12, 5, `
+ added `warp_event 8, 5, MAGNET_TUNNEL_INSIDE, 2`
+ added `cuttree_event 19, 9, EVENT_MAGNET_TUNNEL_EAST_CUT_TREE`
+ added `smashrock_event 12, 6, `
+ added `smashrock_event 14, 4, `
+ added `smashrock_event 12, 3, `

## MahoganyTown

- removed `coord_event 19, 8, 0, MahoganyTownTryARageCandyBarScript`
- removed `coord_event 19, 9, 0, MahoganyTownTryARageCandyBarScript`
- removed `bg_event 3, 13, BGEVENT_JUMPTEXT, MahoganyGymSignText`
+ added `coord_event 19, 8, SCENE_MAHOGANYTOWN_TRY_RAGECANDYBAR, MahoganyTownTryARageCandyBarScript`
+ added `coord_event 19, 9, SCENE_MAHOGANYTOWN_TRY_RAGECANDYBAR, MahoganyTownTryARageCandyBarScript`
+ added `bg_event 7, 13, BGEVENT_JUMPTEXT, MahoganyGymSignText`

## MountMoonB2F

- removed `object_event 10, 6, SPRITE_BOULDER_ROCK_FOSSIL, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_ITEMBALL, PLAYEREVENT_ITEMBALL, HELIX_FOSSIL, 1, EVENT_MOUNT_MOON_B2F_HELIX_FOSSIL`
- removed `object_event 11, 6, SPRITE_BOULDER_ROCK_FOSSIL, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_ITEMBALL, PLAYEREVENT_ITEMBALL, DOME_FOSSIL, 1, EVENT_MOUNT_MOON_B2F_DOME_FOSSIL`
+ added `object_event 10, 6, SPRITE_ICE_BOULDER_FOSSILS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_ITEMBALL, PLAYEREVENT_ITEMBALL, HELIX_FOSSIL, 1, EVENT_MOUNT_MOON_B2F_HELIX_FOSSIL`
+ added `object_event 11, 6, SPRITE_ICE_BOULDER_FOSSILS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_ITEMBALL, PLAYEREVENT_ITEMBALL, DOME_FOSSIL, 1, EVENT_MOUNT_MOON_B2F_DOME_FOSSIL`

## MountMoonSquare

- removed `coord_event 7, 11, 0, ClefairyDance`
+ added `coord_event 7, 11, SCENE_MOUNTMOONSQUARE_CLEFAIRY_DANCE, ClefairyDance`

## MrFujisHouse

- removed `pokemon_event 8, 4, PSYDUCK, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BROWN, MrFujisPsyduckText, -1`
- removed `pokemon_event 5, 5, NIDORINO, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_PURPLE, MrFujisNidorinoText, -1`
- removed `pokemon_event 1, 3, PIDGEY, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BROWN, MrFujisPidgeyText, -1`
+ added `pokemon_event 8, 4, PSYDUCK, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BROWN, MrFujisPsyduckText, -1`
+ added `pokemon_event 5, 5, NIDORINO, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_PURPLE, MrFujisNidorinoText, -1`
+ added `pokemon_event 1, 3, PIDGEY, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BROWN, MrFujisPidgeyText, -1`

## MurkySwamp

- removed `object_event 6, 2, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, URSALUNA, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, URSALUNA_BLOODMOON_FORM, MurkySwampBloodmoonUrsaluna, EVENT_MURKY_SWAMP_BLOODMOON_URSALUNA`
+ added `object_event 6, 2, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, URSALUNA, -1, PAL_MON_RED, OBJECTTYPE_SCRIPT, URSALUNA_BLOODMOON_FORM, MurkySwampBloodmoonUrsaluna, EVENT_MURKY_SWAMP_BLOODMOON_URSALUNA`

## MystriStage

- removed `coord_event 6, 11, 1, MystriStageTrigger1Script`
- removed `coord_event 7, 11, 1, MystriStageTrigger2Script`
- removed `object_event 6, 8, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, EGG, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, NO_FORM, MystriStageEggScript, EVENT_MYSTRI_STAGE_EGG`
+ added `coord_event 6, 11, SCENE_MYSTRISTAGE_ARCEUS_EVENT, MystriStageTrigger1Script`
+ added `coord_event 7, 11, SCENE_MYSTRISTAGE_ARCEUS_EVENT, MystriStageTrigger2Script`
+ added `object_event 6, 8, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, EGG, -1, PAL_MON_BLUE, OBJECTTYPE_SCRIPT, NO_FORM, MystriStageEggScript, EVENT_MYSTRI_STAGE_EGG`

## NationalPark

- removed `pokemon_event 28, 40, PERSIAN, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BROWN, NationalParkPersianText, -1`
+ added `pokemon_event 28, 40, PERSIAN, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BROWN, NationalParkPersianText, -1`

## NavelRockInside

- removed `warp_event 7, 81, NAVEL_ROCK_OUTSIDE, 3`
- removed `warp_event 8, 64, NAVEL_ROCK_INSIDE, 3`
- removed `warp_event 3, 3, NAVEL_ROCK_INSIDE, 2`
- removed `warp_event 9, 5, NAVEL_ROCK_INSIDE, 5`
- removed `warp_event 23, 85, NAVEL_ROCK_INSIDE, 4`
- removed `warp_event 23, 3, NAVEL_ROCK_INSIDE, 7`
- removed `warp_event 5, 45, NAVEL_ROCK_INSIDE, 6`
- removed `warp_event 2, 42, NAVEL_ROCK_INSIDE, 9`
- removed `warp_event 2, 32, NAVEL_ROCK_INSIDE, 8`
- removed `warp_event 5, 35, NAVEL_ROCK_INSIDE, 11`
- removed `warp_event 5, 25, NAVEL_ROCK_INSIDE, 10`
- removed `warp_event 2, 22, NAVEL_ROCK_INSIDE, 13`
- removed `warp_event 2, 12, NAVEL_ROCK_INSIDE, 12`
- removed `warp_event 5, 15, NAVEL_ROCK_ROOF, 1`
- removed `itemball_event 12, 12, SACRED_ASH, 1, EVENT_NAVEL_ROCK_SACRED_ASH`
- removed `itemball_event 37, 12, MASTER_BALL, 1, EVENT_NAVEL_ROCK_MASTER_BALL`
+ added `warp_event 49, 9, NAVEL_ROCK_OUTSIDE, 3`
+ added `warp_event 28, 44, NAVEL_ROCK_INSIDE, 3`
+ added `warp_event 43, 47, NAVEL_ROCK_INSIDE, 2`
+ added `warp_event 49, 49, NAVEL_ROCK_INSIDE, 5`
+ added `warp_event 35, 33, NAVEL_ROCK_INSIDE, 4`
+ added `warp_event 13, 3, NAVEL_ROCK_INSIDE, 7`
+ added `warp_event 51, 39, NAVEL_ROCK_INSIDE, 6`
+ added `warp_event 48, 36, NAVEL_ROCK_INSIDE, 9`
+ added `warp_event 48, 26, NAVEL_ROCK_INSIDE, 8`
+ added `warp_event 51, 29, NAVEL_ROCK_INSIDE, 11`
+ added `warp_event 51, 19, NAVEL_ROCK_INSIDE, 10`
+ added `warp_event 48, 16, NAVEL_ROCK_INSIDE, 13`
+ added `warp_event 26, 2, NAVEL_ROCK_INSIDE, 12`
+ added `warp_event 29, 5, NAVEL_ROCK_ROOF, 1`
+ added `itemball_event 2, 12, SACRED_ASH, 1, EVENT_NAVEL_ROCK_SACRED_ASH`
+ added `itemball_event 27, 12, MASTER_BALL, 1, EVENT_NAVEL_ROCK_MASTER_BALL`

## NavelRockRoof

+ added `object_event 8, 8, SPRITE_BETA, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_BETA_IN_NAVEL_ROCK`

## NewBarkTown

- removed `coord_event 1, 8, 0, NewBarkTown_TeacherStopsYouTrigger1`
- removed `coord_event 1, 9, 0, NewBarkTown_TeacherStopsYouTrigger2`
- removed `coord_event 6, 4, 0, NewBarkTown_LyraIntroTrigger`
- removed `coord_event 17, 6, 1, NewBarkTown_LyraFinalTrigger1`
- removed `coord_event 17, 7, 1, NewBarkTown_LyraFinalTrigger2`
- removed `coord_event 17, 8, 1, NewBarkTown_LyraFinalTrigger3`
- removed `coord_event 17, 9, 1, NewBarkTown_LyraFinalTrigger4`
+ added `coord_event 1, 8, SCENE_NEWBARKTOWN_TEACHER_STOPS_YOU, NewBarkTown_TeacherStopsYouTrigger1`
+ added `coord_event 1, 9, SCENE_NEWBARKTOWN_TEACHER_STOPS_YOU, NewBarkTown_TeacherStopsYouTrigger2`
+ added `coord_event 6, 4, SCENE_NEWBARKTOWN_TEACHER_STOPS_YOU, NewBarkTown_LyraIntroTrigger`
+ added `coord_event 19, 6, SCENE_NEWBARKTOWN_LYRA_FINAL, NewBarkTown_LyraFinalTrigger1`
+ added `coord_event 19, 7, SCENE_NEWBARKTOWN_LYRA_FINAL, NewBarkTown_LyraFinalTrigger2`
+ added `coord_event 19, 8, SCENE_NEWBARKTOWN_LYRA_FINAL, NewBarkTown_LyraFinalTrigger3`
+ added `coord_event 19, 9, SCENE_NEWBARKTOWN_LYRA_FINAL, NewBarkTown_LyraFinalTrigger4`

## NoisyForest

- removed `object_event 19, 36, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_TOLD_ABOUT_PIKABLU`
- removed `object_event 24, 31, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, MARILL, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, NO_FORM, NoisyForestPikabluScript, EVENT_NOISY_FOREST_PIKABLU`
- removed `object_event 20, 19, SPRITE_KATY, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, KatyScript, -1`
- removed `tmhmball_event 17, 22, TM_DRAIN_PUNCH, EVENT_NOISY_FOREST_TM_DRAIN_PUNCH`
+ added `object_event 19, 36, SPRITE_AROMA_LADY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_TOLD_ABOUT_PIKABLU`
+ added `object_event 24, 31, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, MARILL, -1, PAL_MON_BLUE, OBJECTTYPE_SCRIPT, NO_FORM, NoisyForestPikabluScript, EVENT_NOISY_FOREST_PIKABLU`
+ added `tmhmball_event 20, 20, TM_DRAIN_PUNCH, EVENT_NOISY_FOREST_TM_DRAIN_PUNCH`

## OaksLab

- removed `object_event 7, 3, SPRITE_MON_ICON, SPRITEMOVEDATA_STILL, 0, EEVEE, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, NO_FORM, EeveeDollScript, EVENT_DECO_EEVEE_DOLL`
+ added `object_event 7, 3, SPRITE_MON_ICON, SPRITEMOVEDATA_STILL, 0, EEVEE, -1, PAL_MON_BROWN, OBJECTTYPE_SCRIPT, NO_FORM, EeveeDollScript, EVENT_DECO_EEVEE_DOLL`

## OlivineCity

- removed `warp_event 13, 11, OLIVINE_GOOD_ROD_HOUSE, 1`
- removed `warp_event 19, 13, OLIVINE_MART, 2`
- removed `warp_event 33, 19, OLIVINE_LIGHTHOUSE_1F, 1`
- removed `warp_event 18, 31, OLIVINE_PORT, 1`
- removed `warp_event 19, 31, OLIVINE_PORT, 2`
- removed `coord_event 10, 8, 0, OlivineCityRivalGymScript`
- removed `coord_event 33, 23, 0, OlivineCityRivalLighthouseScript`
- removed `bg_event 20, 27, BGEVENT_JUMPTEXT, OlivineCityPortSignText`
- removed `bg_event 7, 7, BGEVENT_JUMPTEXT, OlivineGymSignText`
- removed `bg_event 34, 20, BGEVENT_JUMPTEXT, OlivineLighthouseSignText`
- removed `bg_event 36, 14, BGEVENT_ITEM + RARE_CANDY, EVENT_OLIVINE_CITY_HIDDEN_RARE_CANDY`
- removed `object_event 21, 25, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, (1 << MORN) | (1 << NITE), PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, OlivineCityPokefanMScript, -1`
- removed `object_event 26, 22, SPRITE_SAILOR, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 2, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, OlivineCitySailor1Text, -1`
- removed `object_event 31, 17, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, (1 << MORN) | (1 << DAY), 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, OlivineCityFisherText, -1`
- removed `object_event 31, 17, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, (1 << EVE) | (1 << NITE), 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, OlivineCitySailor3Text, -1`
- removed `object_event 22, 25, SPRITE_MATRON, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, (1 << DAY), PAL_NPC_BROWN, OBJECTTYPE_COMMAND, jumptextfaceplayer, OlivineCityPokefanFText, -1`
- removed `object_event 23, 16, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, OlivineCitySailor4Text, -1`
- removed `object_event 23, 17, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, OlivineCitySailor5Text, -1`
+ added `warp_event 15, 11, OLIVINE_GOOD_ROD_HOUSE, 1`
+ added `warp_event 21, 17, OLIVINE_MART, 2`
+ added `warp_event 33, 21, OLIVINE_LIGHTHOUSE_1F, 1`
+ added `warp_event 18, 28, OLIVINE_PORT, 1`
+ added `warp_event 19, 28, OLIVINE_PORT, 2`
+ added `coord_event 10, 8, SCENE_OLIVINECITY_RIVAL_ENCOUNTER, OlivineCityRivalGymScript`
+ added `coord_event 33, 22, SCENE_OLIVINECITY_RIVAL_ENCOUNTER, OlivineCityRivalLighthouseScript`
+ added `coord_event 33, 21, SCENE_OLIVINECITY_NOOP, OlivineCityPanUpScript`
+ added `bg_event 20, 25, BGEVENT_JUMPTEXT, OlivineCityPortSignText`
+ added `bg_event 11, 7, BGEVENT_JUMPTEXT, OlivineGymSignText`
+ added `bg_event 35, 23, BGEVENT_JUMPTEXT, OlivineLighthouseSignText`
+ added `bg_event 35, 18, BGEVENT_ITEM + RARE_CANDY, EVENT_OLIVINE_CITY_HIDDEN_RARE_CANDY`
+ added `object_event 21, 23, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, (1 << MORN) | (1 << NITE), PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, OlivineCityPokefanMScript, -1`
+ added `object_event 26, 20, SPRITE_SAILOR, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 2, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, OlivineCitySailor1Text, -1`
+ added `object_event 31, 19, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, (1 << MORN) | (1 << DAY), 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, OlivineCityFisherText, -1`
+ added `object_event 31, 19, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, (1 << EVE) | (1 << NITE), 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, OlivineCitySailor3Text, -1`
+ added `object_event 22, 23, SPRITE_MATRON, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, (1 << DAY), PAL_NPC_BROWN, OBJECTTYPE_COMMAND, jumptextfaceplayer, OlivineCityPokefanFText, -1`
+ added `object_event 25, 16, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_DARK_BLUE, OBJECTTYPE_COMMAND, jumptextfaceplayer, OlivineCitySailor4Text, -1`
+ added `object_event 25, 17, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, OlivineCitySailor5Text, -1`

## OlivineLighthouse4F

- removed `object_event 7, 14, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 3, TrainerSailorKent, -1`
+ added `object_event 7, 14, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_DARK_BLUE, OBJECTTYPE_TRAINER, 3, TrainerSailorKent, -1`

## OlivineLighthouse6F

- removed `object_event 9, 8, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, AMPHAROS, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, NO_FORM, OlivineLighthouseAmphy, -1`
+ added `object_event 9, 8, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, AMPHAROS, -1, PAL_MON_BROWN, OBJECTTYPE_SCRIPT, NO_FORM, OlivineLighthouseAmphy, -1`

## OlivinePort

- removed `coord_event 7, 7, 0, OlivinePortWalkUpToShipScript`
- removed `keyitemball_event 16, 14, GO_GOGGLES, EVENT_OLIVINE_PORT_GO_GOGGLES`
+ added `coord_event 7, 7, SCENE_OLIVINEPORT_ASK_ENTER_SHIP, OlivinePortWalkUpToShipScript`
+ added `object_event 16, 13, SPRITE_FLOATING_BALL, SPRITEMOVEDATA_POKEMON, 0, 0, -1, PAL_NPC_ENV_GREEN, OBJECTTYPE_ITEMBALL, PLAYEREVENT_KEYITEMBALL, GO_GOGGLES, EVENT_OLIVINE_PORT_GO_GOGGLES`

## PewterCity

- removed `warp_event 29, 13, PEWTER_NIDORAN_SPEECH_HOUSE, 1`
- removed `warp_event 16, 17, PEWTER_GYM, 1`
- removed `warp_event 23, 17, PEWTER_MART, 2`
- removed `warp_event 13, 25, PEWTER_POKECENTER_1F, 1`
- removed `warp_event 7, 29, PEWTER_SNOOZE_SPEECH_HOUSE, 1`
- removed `warp_event 14, 7, PEWTER_MUSEUM_OF_SCIENCE_1F, 1`
- removed `warp_event 19, 5, PEWTER_MUSEUM_OF_SCIENCE_1F, 3`
- removed `bg_event 25, 23, BGEVENT_JUMPTEXT, PewterCitySignText`
- removed `bg_event 11, 17, BGEVENT_JUMPTEXT, PewterGymSignText`
- removed `bg_event 15, 9, BGEVENT_JUMPTEXT, PewterMuseumOfScienceSignText`
- removed `bg_event 33, 19, BGEVENT_JUMPTEXT, PewterCityMtMoonGiftShopSignText`
- removed `bg_event 19, 29, BGEVENT_JUMPTEXT, PewterCityTrainerTipsText`
- removed `object_event 22, 11, SPRITE_BATTLE_GIRL, SPRITEMOVEDATA_STANDING_DOWN, 2, 2, -1, PAL_NPC_GREEN, OBJECTTYPE_COMMAND, jumptextfaceplayer, PewterCityCooltrainerFText, -1`
- removed `object_event 19, 10, SPRITE_COOL_DUDE, SPRITEMOVEDATA_SPINRANDOM_SLOW, 2, 2, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, PewterCityCooltrainermText, -1`
- removed `object_event 14, 29, SPRITE_CHILD, SPRITEMOVEDATA_WANDER, 2, 2, -1, PAL_NPC_BLUE, OBJECTTYPE_COMMAND, jumptextfaceplayer, PewterCityBugCatcherText, -1`
- removed `object_event 29, 17, SPRITE_GRAMPS, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 2, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, PewterCityGrampsScript, -1`
- removed `object_event 7, 17, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_WANDER, 2, 2, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, PewterCityYoungsterScript, -1`
- removed `object_event 25, 26, SPRITE_POKEFAN_M, SPRITEMOVEDATA_WANDER, 2, 2, -1, PAL_NPC_PURPLE, OBJECTTYPE_SCRIPT, 0, PewterCityPokefanMScript, -1`
- removed `fruittree_event 32, 3, FRUITTREE_PEWTER_CITY_1, PETAYA_BERRY, PAL_NPC_PINK`
- removed `fruittree_event 30, 3, FRUITTREE_PEWTER_CITY_2, APICOT_BERRY, PAL_NPC_BLUE`
+ added `warp_event 29, 15, PEWTER_NIDORAN_SPEECH_HOUSE, 1`
+ added `warp_event 12, 19, PEWTER_GYM, 1`
+ added `warp_event 23, 21, PEWTER_MART, 2`
+ added `warp_event 13, 27, PEWTER_POKECENTER_1F, 1`
+ added `warp_event 7, 31, PEWTER_SNOOZE_SPEECH_HOUSE, 1`
+ added `warp_event 14, 9, PEWTER_MUSEUM_OF_SCIENCE_1F, 1`
+ added `warp_event 19, 7, PEWTER_MUSEUM_OF_SCIENCE_1F, 3`
+ added `warp_event 15, 9, PEWTER_MUSEUM_OF_SCIENCE_1F, 2`
+ added `bg_event 25, 25, BGEVENT_JUMPTEXT, PewterCitySignText`
+ added `bg_event 13, 19, BGEVENT_JUMPTEXT, PewterGymSignText`
+ added `bg_event 13, 10, BGEVENT_JUMPTEXT, PewterMuseumOfScienceSignText`
+ added `bg_event 33, 21, BGEVENT_JUMPTEXT, PewterCityMtMoonGiftShopSignText`
+ added `bg_event 19, 31, BGEVENT_JUMPTEXT, PewterCityTrainerTipsText`
+ added `object_event 22, 13, SPRITE_BATTLE_GIRL, SPRITEMOVEDATA_STANDING_DOWN, 2, 2, -1, PAL_NPC_GREEN, OBJECTTYPE_COMMAND, jumptextfaceplayer, PewterCityCooltrainerFText, -1`
+ added `object_event 19, 12, SPRITE_COOL_DUDE, SPRITEMOVEDATA_SPINRANDOM_SLOW, 2, 2, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, PewterCityCooltrainermText, -1`
+ added `object_event 14, 31, SPRITE_CHILD, SPRITEMOVEDATA_WANDER, 2, 2, -1, PAL_NPC_BLUE, OBJECTTYPE_COMMAND, jumptextfaceplayer, PewterCityBugCatcherText, -1`
+ added `object_event 29, 19, SPRITE_GRAMPS, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 2, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, PewterCityGrampsScript, -1`
+ added `object_event 6, 15, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_WANDER, 2, 2, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, PewterCityYoungsterScript, -1`
+ added `object_event 25, 28, SPRITE_POKEFAN_M, SPRITEMOVEDATA_WANDER, 2, 2, -1, PAL_NPC_PURPLE, OBJECTTYPE_SCRIPT, 0, PewterCityPokefanMScript, -1`
+ added `fruittree_event 26, 5, FRUITTREE_PEWTER_CITY_1, PETAYA_BERRY, PAL_NPC_PINK`
+ added `fruittree_event 24, 5, FRUITTREE_PEWTER_CITY_2, APICOT_BERRY, PAL_NPC_BLUE`

## PewterMuseumOfScience1F

- removed `warp_event 11, 7, PEWTER_CITY, 6`
+ added `warp_event 11, 7, PEWTER_CITY, 8`

## PewterNidoranSpeechHouse

- removed `pokemon_event 4, 5, NIDORAN_M, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_PURPLE, PewterNidoranText, -1`
+ added `pokemon_event 4, 5, NIDORAN_M, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_PURPLE, PewterNidoranText, -1`

## PewterPokeCenter1F

- removed `pokemon_event 2, 3, JIGGLYPUFF, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_PINK, PewterJigglypuffText, -1`
+ added `pokemon_event 2, 3, JIGGLYPUFF, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_PINK, PewterJigglypuffText, -1`

## PlayersHouse1F

- removed `coord_event 10, 4, 0, MomTrigger1`
- removed `coord_event 11, 4, 0, MomTrigger2`
- removed `coord_event 9, 1, 0, MomTrigger3`
- removed `coord_event 9, 2, 0, MomTrigger4`
+ added `coord_event 10, 4, SCENE_PLAYERSHOUSE1F_MEET_MOM, MomTrigger1`
+ added `coord_event 11, 4, SCENE_PLAYERSHOUSE1F_MEET_MOM, MomTrigger2`
+ added `coord_event 9, 1, SCENE_PLAYERSHOUSE1F_MEET_MOM, MomTrigger3`
+ added `coord_event 9, 2, SCENE_PLAYERSHOUSE1F_MEET_MOM, MomTrigger4`

## PlayersNeighborsHouse

- removed `bg_event 5, 1, BGEVENT_READ, PlayersNeighborsHouseRadio`
+ added `bg_event 5, 1, BGEVENT_READ, InitialRadio`

## PokemonFanClub

- removed `warp_event 2, 7, VERMILION_CITY, 3`
- removed `warp_event 3, 7, VERMILION_CITY, 3`
- removed `object_event 3, 3, SPRITE_MON_ICON, SPRITEMOVEDATA_STILL, 0, CLEFAIRY, -1, PAL_NPC_PINK, OBJECTTYPE_SCRIPT, NO_FORM, ClefairyDollScript, EVENT_VERMILION_FAN_CLUB_DOLL`
- removed `object_event 5, 1, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, PokemonFanClubChairmanScript, -1`
- removed `object_event 3, 4, SPRITE_FAT_GUY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, PokemonFanClubClefairyGuyScript, -1`
- removed `pokemon_event 7, 3, ODDISH, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_GREEN, FanClubOddishText, -1`
+ added `warp_event 4, 7, VERMILION_CITY, 3`
+ added `warp_event 5, 7, VERMILION_CITY, 3`
+ added `object_event 2, 3, SPRITE_MON_ICON, SPRITEMOVEDATA_STILL, 0, CLEFAIRY, -1, PAL_MON_PINK, OBJECTTYPE_SCRIPT, NO_FORM, ClefairyDollScript, EVENT_VERMILION_FAN_CLUB_DOLL`
+ added `object_event 4, 1, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, PokemonFanClubChairmanScript, -1`
+ added `object_event 2, 4, SPRITE_FAT_GUY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, PokemonFanClubClefairyGuyScript, -1`
+ added `pokemon_event 7, 3, ODDISH, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_GREEN, FanClubOddishText, -1`

## PokemonLeagueGate

- removed `warp_event 19, 7, ROUTE_22, 1`
- removed `warp_event 20, 7, ROUTE_22, 1`
- removed `warp_event 11, 17, ROUTE_26, 1`
- removed `warp_event 10, 0, ROUTE_23, 1`
- removed `warp_event 11, 0, ROUTE_23, 2`
- removed `warp_event 1, 7, ROUTE_28, 2`
- removed `warp_event 2, 7, ROUTE_28, 2`
- removed `coord_event 10, 10, 0, PokemonLeagueGateXYTriggerScript1`
- removed `coord_event 11, 10, 0, PokemonLeagueGateXYTriggerScript2`
+ added `warp_event 21, 6, ROUTE_22, 1`
+ added `warp_event 21, 7, ROUTE_22, 2`
+ added `warp_event 11, 17, ROUTE_26, 2`
+ added `warp_event 10, 0, ROUTE_23_SOUTH, 1`
+ added `warp_event 11, 0, ROUTE_23_SOUTH, 2`
+ added `warp_event 0, 6, ROUTE_28, 2`
+ added `warp_event 0, 7, ROUTE_28, 3`
+ added `coord_event 10, 10, SCENE_POKEMONLEAGUEGATE_BADGE_CHECK, PokemonLeagueGateXYTriggerScript1`
+ added `coord_event 11, 10, SCENE_POKEMONLEAGUEGATE_BADGE_CHECK, PokemonLeagueGateXYTriggerScript2`

## PowerPlant

- removed `coord_event 5, 12, 1, PowerPlantGuardPhoneScript`
+ added `coord_event 5, 12, SCENE_POWERPLANT_GUARD_GETS_PHONE_CALL, PowerPlantGuardPhoneScript`

## QuietCaveB3F

- removed `warp_event 8, 31, QUIET_CAVE_B2F, 5`
- removed `warp_event 33, 7, QUIET_CAVE_B2F, 6`
- removed `warp_event 15, 9, QUIET_CAVE_B3F, 4`
- removed `bg_event 16, 20, BGEVENT_ITEM + PP_UP, EVENT_QUIET_CAVE_B3F_HIDDEN_PP_UP`
- removed `bg_event 12, 22, BGEVENT_ITEM + MAX_REVIVE, EVENT_QUIET_CAVE_B3F_HIDDEN_MAX_REVIVE`
- removed `tmhmball_event 7, 22, TM_FOCUS_BLAST, EVENT_QUIET_CAVE_B3F_TM_FOCUS_BLAST`
+ added `warp_event 8, 33, QUIET_CAVE_B2F, 5`
+ added `warp_event 33, 9, QUIET_CAVE_B2F, 6`
+ added `warp_event 15, 11, QUIET_CAVE_B3F, 4`
+ added `bg_event 16, 22, BGEVENT_ITEM + PP_UP, EVENT_QUIET_CAVE_B3F_HIDDEN_PP_UP`
+ added `bg_event 12, 24, BGEVENT_ITEM + MAX_REVIVE, EVENT_QUIET_CAVE_B3F_HIDDEN_MAX_REVIVE`
+ added `tmhmball_event 7, 24, TM_FOCUS_BLAST, EVENT_QUIET_CAVE_B3F_TM_FOCUS_BLAST`

## RadioTower2F

- removed `pokemon_event 12, 1, JIGGLYPUFF, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_PINK, RadioTowerJigglypuffText, -1`
+ added `pokemon_event 12, 1, JIGGLYPUFF, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_PINK, RadioTowerJigglypuffText, -1`

## RadioTower4F

- removed `pokemon_event 12, 7, MEOWTH, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BROWN, RadioTowerMeowthText, -1`
+ added `pokemon_event 12, 7, MEOWTH, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BROWN, RadioTowerMeowthText, -1`

## RadioTower5F

- removed `coord_event 0, 3, 0, FakeDirectorScript`
- removed `coord_event 16, 5, 1, RadioTower5FRocketBossTrigger`
+ added `coord_event 0, 3, SCENE_RADIOTOWER5F_FAKE_DIRECTOR, FakeDirectorScript`
+ added `coord_event 16, 5, SCENE_RADIOTOWER5F_ROCKET_BOSS, RadioTower5FRocketBossTrigger`

## RockTunnel2F

- removed `object_event 8, 12, SPRITE_BALL_CUT_FRUIT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_POKE_BALL, OBJECTTYPE_SCRIPT, 0, RockTunnel2FElectrode, EVENT_ROCK_TUNNEL_2F_ELECTRODE`
+ added `object_event 8, 12, SPRITE_BALL_CUT_TREE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_ENV_RED, OBJECTTYPE_SCRIPT, 0, RockTunnel2FElectrode, EVENT_ROCK_TUNNEL_2F_ELECTRODE`

## RockTunnelB1F

- removed `object_event 27, 14, SPRITE_FIREBREATHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerFirebreatherDick, -1`
+ added `object_event 27, 14, SPRITE_FIREBREATHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerFirebreatherCyd, -1`

## RocketHideoutB1F

- removed `object_event 10, 17, SPRITE_BATTLE_GIRL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, RocketHideoutB1FBattleGirlSasha, -1`
+ added `object_event 12, 19, SPRITE_BATTLE_GIRL, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, RocketHideoutB1FBattleGirlSasha, -1`

## RocketHideoutB4F

- removed `coord_event 16, 11, 0, RocketHideoutB4FMeetLeadersLeftScript`
- removed `coord_event 17, 11, 0, RocketHideoutB4FMeetLeadersRightScript`
+ added `coord_event 16, 11, SCENE_ROCKETHIDEOUTB4F_MEET_LEADERS, RocketHideoutB4FMeetLeadersLeftScript`
+ added `coord_event 17, 11, SCENE_ROCKETHIDEOUTB4F_MEET_LEADERS, RocketHideoutB4FMeetLeadersRightScript`

## RockyBeach

- removed `object_event 23, 10, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, RockyBeachYoungsterScript, EVENT_NOISY_FOREST_PIKABLU`
+ added `object_event 23, 10, SPRITE_AROMA_LADY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_GENERICTRAINER, 1, RockyBeachWilhomenaScript, EVENT_NOISY_FOREST_PIKABLU`

## Route10North

- removed `object_event 13, 44, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, ZAPDOS, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, PLAIN_FORM, Route10Zapdos, EVENT_ROUTE_10_ZAPDOS`
- removed `object_event 14, 52, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, ZAPDOS, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, PLAIN_FORM, ObjectEvent, EVENT_LAWRENCES_ZAPDOS_ROUTE_10`
- removed `cuttree_event 7, 21, EVENT_ROUTE_10_CUT_TREE_1`
- removed `cuttree_event 9, 21, EVENT_ROUTE_10_CUT_TREE_2`
- removed `cuttree_event 11, 21, EVENT_ROUTE_10_CUT_TREE_3`
- removed `cuttree_event 13, 21, EVENT_ROUTE_10_CUT_TREE_4`
+ added `object_event 13, 44, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, ZAPDOS, -1, PAL_MON_YELLOW_BROWN, OBJECTTYPE_SCRIPT, PLAIN_FORM, Route10Zapdos, EVENT_ROUTE_10_ZAPDOS`
+ added `object_event 14, 52, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, ZAPDOS, -1, PAL_MON_YELLOW_BROWN, OBJECTTYPE_SCRIPT, PLAIN_FORM, ObjectEvent, EVENT_LAWRENCES_ZAPDOS_ROUTE_10`
+ added `object_event 12, 52, SPRITE_BETA, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_BETA_IN_NAVEL_ROCK`
+ added `cuttree_event 11, 21, EVENT_ROUTE_10_CUT_TREE_1`
+ added `cuttree_event 14, 21, EVENT_ROUTE_10_CUT_TREE_2`
+ added `object_event 5, 10, SPRITE_FLOATING_BALL, SPRITEMOVEDATA_POKEMON, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route10NorthElectrode, EVENT_ROUTE_10_NORTH_ELECTRODE`

## Route13East -> Route13

- removed `bg_event 11, 13, BGEVENT_JUMPTEXT, Route13TrainerTips1Text`
- removed `bg_event 29, 5, BGEVENT_JUMPTEXT, Route13TrainerTips2Text`
- removed `bg_event 27, 11, BGEVENT_JUMPTEXT, Route13SignText`
- removed `bg_event 12, 13, BGEVENT_ITEM + CALCIUM, EVENT_ROUTE_13_HIDDEN_CALCIUM`
- removed `object_event 36, 11, SPRITE_BIRD_KEEPER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 5, GenericTrainerBird_keeperPerry, -1`
- removed `object_event 40, 1, SPRITE_BIRD_KEEPER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBird_keeperBret, -1`
- removed `object_event 10, 5, SPRITE_CAMPER, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerCamperTanner, -1`
- removed `object_event 41, 9, SPRITE_PICNICKER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerPicnickerPiper, -1`
- removed `object_event 28, 6, SPRITE_COOL_DUDE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerCoupleTimandsue1, -1`
- removed `object_event 29, 6, SPRITE_CUTE_GIRL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerCoupleTimandsue2, -1`
- removed `object_event 14, 8, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerPokefanmJoshua, -1`
- removed `object_event 1, 6, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerPokefanmAlex, -1`
- removed `object_event 5, 13, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_SCRIPT, 0, Route13EastGrampsScript, -1`
- removed `cuttree_event 30, 4, EVENT_ROUTE_13_CUT_TREE`
+ added `bg_event 35, 13, BGEVENT_JUMPTEXT, Route13TrainerTips1Text`
+ added `bg_event 53, 5, BGEVENT_JUMPTEXT, Route13TrainerTips2Text`
+ added `bg_event 51, 11, BGEVENT_JUMPTEXT, Route13SignText`
+ added `bg_event 17, 13, BGEVENT_JUMPTEXT, Route13DirectionsSignText`
+ added `bg_event 36, 13, BGEVENT_ITEM + CALCIUM, EVENT_ROUTE_13_HIDDEN_CALCIUM`
+ added `bg_event 5, 15, BGEVENT_ITEM + OVAL_STONE, EVENT_ROUTE_13_HIDDEN_OVAL_STONE`
+ added `object_event 5, 5, SPRITE_CAMPER, SPRITEMOVEDATA_SPINCOUNTERCLOCKWISE, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerCamperClark, -1`
+ added `object_event 16, 6, SPRITE_PICNICKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerPicnickerGinger, -1`
+ added `object_event 60, 11, SPRITE_BIRD_KEEPER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 5, GenericTrainerBird_keeperPerry, -1`
+ added `object_event 64, 1, SPRITE_BIRD_KEEPER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBird_keeperBret, -1`
+ added `object_event 34, 5, SPRITE_CAMPER, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerCamperTanner, -1`
+ added `object_event 65, 9, SPRITE_PICNICKER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerPicnickerPiper, -1`
+ added `object_event 52, 6, SPRITE_COOL_DUDE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerCoupleTimandsue1, -1`
+ added `object_event 53, 6, SPRITE_CUTE_GIRL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerCoupleTimandsue2, -1`
+ added `object_event 38, 8, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerPokefanmJoshua, -1`
+ added `object_event 14, 10, SPRITE_HIKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerHikerKenny, -1`
+ added `object_event 25, 6, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerPokefanmAlex, -1`
+ added `object_event 21, 13, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_SCRIPT, 0, Route13GrampsScript, -1`
+ added `cuttree_event 54, 4, EVENT_ROUTE_13_CUT_TREE`

## Route13West

- removed `bg_event 17, 13, BGEVENT_JUMPTEXT, Route13DirectionsSignText`
- removed `object_event 5, 5, SPRITE_CAMPER, SPRITEMOVEDATA_SPINCOUNTERCLOCKWISE, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerCamperClark, -1`
- removed `object_event 16, 6, SPRITE_PICNICKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerPicnickerGinger, -1`
- removed `object_event 14, 10, SPRITE_HIKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerHikerKenny, -1`
- removed `object_event 25, 6, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, -1`

## Route14

- removed `object_event 11, 21, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerPokefanmCarter, -1`
- removed `object_event 15, 14, SPRITE_BIRD_KEEPER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerBird_keeperJosh, -1`
- removed `object_event 4, 17, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerSchoolboyConnor, -1`
- removed `object_event 4, 15, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerSchoolboyTorin, -1`
- removed `object_event 4, 13, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerSchoolboyTravis, -1`
- removed `object_event 9, 15, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerTeacherClarice, -1`
- removed `cuttree_event 5, 10, EVENT_ROUTE_14_CUT_TREE_1`
- removed `cuttree_event 11, 16, EVENT_ROUTE_14_CUT_TREE_2`
- removed `cuttree_event 3, 26, EVENT_ROUTE_14_CUT_TREE_3`
- removed `fruittree_event 5, 20, FRUITTREE_ROUTE_14, CUSTAP_BERRY, PAL_NPC_RED`
+ added `bg_event 15, 12, BGEVENT_JUMPTEXT, Route14SignText`
+ added `object_event 11, 22, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerPokefanmCarter, -1`
+ added `object_event 15, 15, SPRITE_BIRD_KEEPER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerBird_keeperJosh, -1`
+ added `object_event 4, 19, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerSchoolboyConnor, -1`
+ added `object_event 4, 17, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerSchoolboyTorin, -1`
+ added `object_event 4, 15, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerSchoolboyTravis, -1`
+ added `object_event 9, 17, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerTeacherClarice, -1`
+ added `cuttree_event 4, 9, EVENT_ROUTE_14_CUT_TREE_1`
+ added `cuttree_event 10, 18, EVENT_ROUTE_14_CUT_TREE_2`
+ added `cuttree_event 3, 25, EVENT_ROUTE_14_CUT_TREE_3`
+ added `fruittree_event 5, 12, FRUITTREE_ROUTE_14, CUSTAP_BERRY, PAL_NPC_RED`

## Route15

- removed `object_event 20, 10, SPRITE_TEACHER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerTeacherHillary, -1`
- removed `object_event 43, 6, SPRITE_BALL_CUT_FRUIT, SPRITEMOVEDATA_CUTTABLE_TREE, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_ROUTE_14_CUT_TREE_3`
+ added `object_event 20, 10, SPRITE_TEACHER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, PAL_NPC_DARK_GREEN, OBJECTTYPE_TRAINER, 3, TrainerTeacherHillary, -1`
+ added `cuttree_event 43, 5, EVENT_ROUTE_14_CUT_TREE_3`

## Route1617Gate

- removed `warp_event 0, 5, ROUTE_16_SOUTH, 1`
- removed `warp_event 0, 6, ROUTE_16_SOUTH, 2`
- removed `warp_event 9, 5, ROUTE_16_NORTHEAST, 1`
- removed `warp_event 9, 6, ROUTE_16_NORTHEAST, 2`
- removed `coord_event 5, 3, 0, Route16GateBicycleCheck`
- removed `coord_event 5, 4, 0, Route16GateBicycleCheck`
- removed `coord_event 5, 5, 0, Route1617GateStepUpOneTrigger`
- removed `coord_event 5, 6, 0, Route1617GateStepUpTwoTrigger`
- removed `coord_event 5, 7, 0, Route1617GateStepUpThreeTrigger`
+ added `warp_event 0, 5, ROUTE_17_NORTH, 1`
+ added `warp_event 0, 6, ROUTE_17_NORTH, 2`
+ added `warp_event 9, 5, ROUTE_16_EAST, 1`
+ added `warp_event 9, 6, ROUTE_16_EAST, 2`
+ added `coord_event 5, 3, SCENE_ROUTE1617GATE_BICYCLE_CHECK, Route16GateBicycleCheck`
+ added `coord_event 5, 4, SCENE_ROUTE1617GATE_BICYCLE_CHECK, Route16GateBicycleCheck`
+ added `coord_event 5, 5, SCENE_ROUTE1617GATE_BICYCLE_CHECK, Route1617GateStepUpOneTrigger`
+ added `coord_event 5, 6, SCENE_ROUTE1617GATE_BICYCLE_CHECK, Route1617GateStepUpTwoTrigger`
+ added `coord_event 5, 7, SCENE_ROUTE1617GATE_BICYCLE_CHECK, Route1617GateStepUpThreeTrigger`

## Route16East

+ added `warp_event 6, 10, ROUTE_16_17_GATE, 3`
+ added `warp_event 6, 11, ROUTE_16_17_GATE, 4`
+ added `warp_event 4, 2, ROUTE_16_GATE, 3`
+ added `warp_event 4, 3, ROUTE_16_GATE, 4`
+ added `bg_event 7, 1, BGEVENT_JUMPTEXT, Route16SignpostText`

## Route16FuchsiaSpeechHouse

- removed `warp_event 2, 7, ROUTE_16_NORTHWEST, 1`
- removed `warp_event 3, 7, ROUTE_16_NORTHWEST, 1`
+ added `warp_event 2, 7, ROUTE_16_NORTH, 1`
+ added `warp_event 3, 7, ROUTE_16_NORTH, 1`

## Route16Gate

- removed `warp_event 0, 4, ROUTE_16_NORTHWEST, 2`
- removed `warp_event 0, 5, ROUTE_16_NORTHWEST, 3`
- removed `warp_event 9, 4, ROUTE_16_NORTHEAST, 3`
- removed `warp_event 9, 5, ROUTE_16_NORTHEAST, 4`
+ added `warp_event 0, 4, ROUTE_16_NORTH, 2`
+ added `warp_event 0, 5, ROUTE_16_NORTH, 3`
+ added `warp_event 9, 4, ROUTE_16_EAST, 3`
+ added `warp_event 9, 5, ROUTE_16_EAST, 4`

## Route16Northeast

- removed `warp_event 22, 10, ROUTE_16_17_GATE, 3`
- removed `warp_event 22, 11, ROUTE_16_17_GATE, 4`
- removed `warp_event 20, 4, ROUTE_16_GATE, 3`
- removed `warp_event 20, 5, ROUTE_16_GATE, 4`
- removed `cuttree_event 23, 4, EVENT_ROUTE_16_CUT_TREE`

## Route16Northwest -> Route16North

- removed `bg_event 5, 2, BGEVENT_JUMPTEXT, Route16SignpostText`
- removed `cuttree_event -5, 2, EVENT_ROUTE_16_WEST_CUT_TREE`
+ added `cuttree_event 5, 3, EVENT_ROUTE_16_NORTH_CUT_TREE`
+ added `cuttree_event -5, 4, EVENT_ROUTE_16_WEST_CUT_TREE`

## Route16South -> Route17North

- removed `warp_event 15, 10, ROUTE_16_17_GATE, 1`
- removed `warp_event 15, 11, ROUTE_16_17_GATE, 2`
- removed `bg_event 11, 9, BGEVENT_JUMPTEXT, CyclingRoadSignText`
- removed `object_event 12, 11, SPRITE_OFFICER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, OfficerfJamieScript, -1`
+ added `warp_event 9, 6, ROUTE_16_17_GATE, 1`
+ added `warp_event 9, 7, ROUTE_16_17_GATE, 2`
+ added `bg_event 7, 3, BGEVENT_JUMPTEXT, CyclingRoadSignText`
+ added `object_event 3, 6, SPRITE_OFFICER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, OfficerfJamieScript, -1`

## Route16West

+ added `cuttree_event 67, 3, EVENT_ROUTE_16_NORTH_CUT_TREE`

## Route17 -> Route17South

- removed `bg_event 11, 71, BGEVENT_ITEM + MAX_ETHER, EVENT_ROUTE_17_HIDDEN_MAX_ETHER`
- removed `bg_event 10, 123, BGEVENT_ITEM + MAX_ELIXIR, EVENT_ROUTE_17_HIDDEN_MAX_ELIXIR`
- removed `bg_event 9, 64, BGEVENT_JUMPTEXT, Route17Notice1Text`
- removed `bg_event 9, 71, BGEVENT_JUMPTEXT, Route17TrainerTips1Text`
- removed `bg_event 9, 94, BGEVENT_JUMPTEXT, Route17TrainerTips2Text`
- removed `bg_event 9, 101, BGEVENT_JUMPTEXT, Route17Notice2Text`
- removed `object_event 12, 9, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerBikerDale, -1`
- removed `object_event 4, 17, SPRITE_BIKER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerBikerReilly, -1`
- removed `object_event 18, 24, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBikerJacob, -1`
- removed `object_event 2, 37, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBikerDan, -1`
- removed `object_event 3, 56, SPRITE_BIKER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBikerGlenn, -1`
- removed `object_event 11, 65, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerBikerJoel, -1`
- removed `object_event 13, 72, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerBikerAiden, -1`
- removed `object_event 3, 86, SPRITE_BIKER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerBikerTeddy, -1`
- removed `object_event 6, 128, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, -1`
- removed `object_event 1, 29, SPRITE_ROUGHNECK, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerRoughneckBrian, -1`
- removed `object_event 6, 42, SPRITE_ROUGHNECK, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerRoughneckTheron, -1`
- removed `object_event 4, 91, SPRITE_ROUGHNECK, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerRoughneckMarkey, -1`
+ added `bg_event 11, 69, BGEVENT_ITEM + MAX_ETHER, EVENT_ROUTE_17_SOUTH_HIDDEN_MAX_ETHER`
+ added `bg_event 10, 121, BGEVENT_ITEM + MAX_ELIXIR, EVENT_ROUTE_17_SOUTH_HIDDEN_MAX_ELIXIR`
+ added `bg_event 9, 62, BGEVENT_JUMPTEXT, Route17SouthNotice1Text`
+ added `bg_event 9, 69, BGEVENT_JUMPTEXT, Route17SouthTrainerTips1Text`
+ added `bg_event 9, 92, BGEVENT_JUMPTEXT, Route17SouthTrainerTips2Text`
+ added `bg_event 9, 99, BGEVENT_JUMPTEXT, Route17SouthNotice2Text`
+ added `object_event 12, 7, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerBikerDale, -1`
+ added `object_event 4, 15, SPRITE_BIKER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerBikerReilly, -1`
+ added `object_event 18, 22, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBikerJacob, -1`
+ added `object_event 2, 35, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBikerDan, -1`
+ added `object_event 3, 54, SPRITE_BIKER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBikerGlenn, -1`
+ added `object_event 11, 63, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerBikerJoel, -1`
+ added `object_event 13, 70, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerBikerAiden, -1`
+ added `object_event 3, 84, SPRITE_BIKER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerBikerTeddy, -1`
+ added `object_event 6, 126, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, -1`
+ added `object_event 1, 27, SPRITE_ROUGHNECK, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerRoughneckBrian, -1`
+ added `object_event 6, 40, SPRITE_ROUGHNECK, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerRoughneckTheron, -1`
+ added `object_event 4, 89, SPRITE_ROUGHNECK, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerRoughneckMarkey, -1`

## Route18Gate

- removed `coord_event 5, 3, 0, Route17Route18GateBicycleCheck`
- removed `coord_event 5, 4, 0, Route17Route18GateBicycleCheck`
- removed `coord_event 5, 5, 0, Route18GateStepUpOneTrigger`
- removed `coord_event 5, 6, 0, Route18GateStepUpTwoTrigger`
- removed `coord_event 5, 7, 0, Route18GateStepUpThreeTrigger`
+ added `coord_event 5, 3, SCENE_ROUTE18GATE_BICYCLE_CHECK, Route17Route18GateBicycleCheck`
+ added `coord_event 5, 4, SCENE_ROUTE18GATE_BICYCLE_CHECK, Route17Route18GateBicycleCheck`
+ added `coord_event 5, 5, SCENE_ROUTE18GATE_BICYCLE_CHECK, Route18GateStepUpOneTrigger`
+ added `coord_event 5, 6, SCENE_ROUTE18GATE_BICYCLE_CHECK, Route18GateStepUpTwoTrigger`
+ added `coord_event 5, 7, SCENE_ROUTE18GATE_BICYCLE_CHECK, Route18GateStepUpThreeTrigger`

## Route18West

- removed `coord_event 12, 0, 0, Route18WestBikeCheckScript`
+ added `coord_event 12, 0, SCENE_ROUTE18WEST_BICYCLE_CHECK, Route18WestBikeCheckScript`

## Route19

- removed `object_event 8, 34, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerSwimmerfDawn, -1`
- removed `object_event 9, 34, SPRITE_SWIMMER_GUY, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerSwimmermTucker, -1`
- removed `object_event 13, 43, SPRITE_SWIMMER_GUY, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerSwimmermHarold, -1`
- removed `object_event 13, 51, SPRITE_COSPLAYER, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerCosplayerBrooke, -1`
- removed `tmhmball_event 14, 52, TM_SCALD, EVENT_ROUTE_19_TM_SCALD`
+ added `object_event 8, 33, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerSwimmerfDawn, -1`
+ added `object_event 9, 33, SPRITE_SWIMMER_GUY, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerSwimmermTucker, -1`
+ added `object_event 13, 42, SPRITE_SWIMMER_GUY, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerSwimmermHarold, -1`
+ added `object_event 12, 50, SPRITE_COSPLAYER, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerCosplayerBrooke, -1`
+ added `tmhmball_event 13, 51, TM_SCALD, EVENT_ROUTE_19_TM_SCALD`

## Route20

- removed `bg_event 23, 10, BGEVENT_ITEM + STARDUST, EVENT_ROUTE_20_HIDDEN_STARDUST`
- removed `object_event 26, 14, SPRITE_PICNICKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 5, GenericTrainerPicnickerAdrian, -1`
- removed `object_event 14, 14, SPRITE_CAMPER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerCamperPedro, -1`
+ added `bg_event 21, 11, BGEVENT_ITEM + STARDUST, EVENT_ROUTE_20_HIDDEN_STARDUST`
+ added `object_event 25, 14, SPRITE_PICNICKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 5, GenericTrainerPicnickerAdrian, -1`
+ added `object_event 13, 14, SPRITE_CAMPER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerCamperPedro, -1`

## Route21

- removed `bg_event 12, 37, BGEVENT_ITEM + STARDUST, EVENT_ROUTE_21_HIDDEN_STARDUST_1`
- removed `object_event 5, 45, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerSwimmerfKendra, -1`
- removed `object_event 15, 25, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerFisherArnold, -1`
- removed `object_event 7, 36, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerFisherLiam, -1`
- removed `object_event 5, 56, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerFisherGideon, -1`
+ added `bg_event 14, 37, BGEVENT_ITEM + STARDUST, EVENT_ROUTE_21_HIDDEN_STARDUST_1`
+ added `object_event 5, 46, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerSwimmerfKendra, -1`
+ added `object_event 16, 25, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerFisherArnold, -1`
+ added `object_event 8, 36, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerFisherLiam, -1`
+ added `object_event 4, 55, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerFisherGideon, -1`

## Route22

- removed `warp_event 3, 5, POKEMON_LEAGUE_GATE, 1`
- removed `bg_event 6, 6, BGEVENT_JUMPTEXT, VictoryRoadEntranceSignText`
- removed `bg_event 5, 9, BGEVENT_JUMPTEXT, Route22AdvancedTipsSignText`
- removed `object_event 14, 11, SPRITE_KUKUI, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, KukuiScript, -1`
- removed `object_event 20, 2, SPRITE_ACE_TRAINER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route22CooltrainerfText, -1`
+ added `warp_event 4, 4, POKEMON_LEAGUE_GATE, 1`
+ added `warp_event 4, 5, POKEMON_LEAGUE_GATE, 2`
+ added `bg_event 7, 7, BGEVENT_JUMPTEXT, VictoryRoadEntranceSignText`
+ added `bg_event 23, 11, BGEVENT_JUMPTEXT, Route22AdvancedTipsSignText`
+ added `object_event 20, 11, SPRITE_KUKUI, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, KukuiScript, -1`
+ added `object_event 28, 2, SPRITE_ACE_TRAINER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route22CooltrainerfText, -1`

## Route23

- removed `warp_event 9, 135, POKEMON_LEAGUE_GATE, 5`
- removed `warp_event 10, 135, POKEMON_LEAGUE_GATE, 6`
- removed `warp_event 6, 31, VICTORY_ROAD_1F, 1`
- removed `warp_event 16, 31, VICTORY_ROAD_2F, 1`
- removed `coord_event 16, 131, 0, Route23ZephyrBadgeTriggerScript`
- removed `coord_event 11, 123, 1, Route23HiveBadgeTriggerScript`
- removed `coord_event 12, 107, 2, Route23PlainBadgeTriggerScript`
- removed `coord_event 14, 107, 2, Route23PlainBadgeTriggerScript`
- removed `coord_event 15, 107, 2, Route23PlainBadgeTriggerScript`
- removed `coord_event 16, 107, 2, Route23PlainBadgeTriggerScript`
- removed `coord_event 17, 107, 2, Route23PlainBadgeTriggerScript`
- removed `coord_event 10, 98, 3, Route23FogBadgeTriggerScript`
- removed `coord_event 11, 98, 3, Route23FogBadgeTriggerScript`
- removed `coord_event 13, 98, 3, Route23FogBadgeTriggerScript`
- removed `coord_event 14, 98, 3, Route23FogBadgeTriggerScript`
- removed `coord_event 15, 98, 3, Route23FogBadgeTriggerScript`
- removed `coord_event 6, 83, 4, Route23StormBadgeTriggerScript`
- removed `coord_event 8, 83, 4, Route23StormBadgeTriggerScript`
- removed `coord_event 9, 83, 4, Route23StormBadgeTriggerScript`
- removed `coord_event 10, 70, 5, Route23MineralBadgeTriggerScript`
- removed `coord_event 11, 70, 5, Route23MineralBadgeTriggerScript`
- removed `coord_event 12, 70, 5, Route23MineralBadgeTriggerScript`
- removed `coord_event 14, 70, 5, Route23MineralBadgeTriggerScript`
- removed `coord_event 15, 70, 5, Route23MineralBadgeTriggerScript`
- removed `coord_event 14, 55, 6, Route23GlacierBadgeTriggerScript`
- removed `coord_event 8, 47, 7, Route23RisingBadgeTriggerScript`
- removed `coord_event 9, 47, 7, Route23RisingBadgeTriggerScript`
- removed `bg_event 5, 32, BGEVENT_JUMPTEXT, VictoryRoadSignText`
- removed `object_event 17, 131, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route23ZephyrBadgeOfficerScript, -1`
- removed `object_event 10, 123, SPRITE_OFFICER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route23HiveBadgeOfficerScript, -1`
- removed `object_event 13, 107, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route23PlainBadgeOfficerScript, -1`
- removed `object_event 12, 98, SPRITE_SWIMMING_OFFICER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route23FogBadgeOfficerScript, -1`
- removed `object_event 7, 83, SPRITE_SWIMMING_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route23StormBadgeOfficerScript, -1`
- removed `object_event 13, 70, SPRITE_OFFICER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route23MineralBadgeOfficerScript, -1`
- removed `object_event 15, 55, SPRITE_OFFICER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route23GlacierBadgeOfficerScript, -1`
- removed `object_event 10, 47, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route23RisingBadgeOfficerScript, -1`
- removed `object_event 8, 32, SPRITE_OFFICER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route23HealOfficerScript, -1`

## Route23North

+ added `warp_event 6, 31, VICTORY_ROAD_1F, 1`
+ added `warp_event 16, 31, VICTORY_ROAD_2F, 1`
+ added `coord_event 10, 70, SCENE_ROUTE23NORTH_BADGE_CHECK_5, Route23NorthMineralBadgeTriggerScript`
+ added `coord_event 11, 70, SCENE_ROUTE23NORTH_BADGE_CHECK_5, Route23NorthMineralBadgeTriggerScript`
+ added `coord_event 12, 70, SCENE_ROUTE23NORTH_BADGE_CHECK_5, Route23NorthMineralBadgeTriggerScript`
+ added `coord_event 14, 70, SCENE_ROUTE23NORTH_BADGE_CHECK_5, Route23NorthMineralBadgeTriggerScript`
+ added `coord_event 15, 70, SCENE_ROUTE23NORTH_BADGE_CHECK_5, Route23NorthMineralBadgeTriggerScript`
+ added `coord_event 14, 55, SCENE_ROUTE23NORTH_BADGE_CHECK_6, Route23NorthGlacierBadgeTriggerScript`
+ added `coord_event 8, 47, SCENE_ROUTE23NORTH_BADGE_CHECK_7, Route23NorthRisingBadgeTriggerScript`
+ added `coord_event 9, 47, SCENE_ROUTE23NORTH_BADGE_CHECK_7, Route23NorthRisingBadgeTriggerScript`
+ added `bg_event 5, 32, BGEVENT_JUMPTEXT, VictoryRoadSignText`
+ added `object_event 13, 70, SPRITE_OFFICER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route23NorthMineralBadgeOfficerScript, -1`
+ added `object_event 15, 55, SPRITE_OFFICER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route23NorthGlacierBadgeOfficerScript, -1`
+ added `object_event 10, 47, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route23NorthRisingBadgeOfficerScript, -1`
+ added `object_event 8, 32, SPRITE_OFFICER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route23NorthHealOfficerScript, -1`

## Route23South

+ added `warp_event 9, 59, POKEMON_LEAGUE_GATE, 5`
+ added `warp_event 10, 59, POKEMON_LEAGUE_GATE, 6`
+ added `coord_event 16, 55, SCENE_ROUTE23SOUTH_BADGE_CHECK_0, Route23SouthZephyrBadgeTriggerScript`
+ added `coord_event 11, 47, SCENE_ROUTE23SOUTH_BADGE_CHECK_1, Route23SouthHiveBadgeTriggerScript`
+ added `coord_event 12, 31, SCENE_ROUTE23SOUTH_BADGE_CHECK_2, Route23SouthPlainBadgeTriggerScript`
+ added `coord_event 14, 31, SCENE_ROUTE23SOUTH_BADGE_CHECK_2, Route23SouthPlainBadgeTriggerScript`
+ added `coord_event 15, 31, SCENE_ROUTE23SOUTH_BADGE_CHECK_2, Route23SouthPlainBadgeTriggerScript`
+ added `coord_event 16, 31, SCENE_ROUTE23SOUTH_BADGE_CHECK_2, Route23SouthPlainBadgeTriggerScript`
+ added `coord_event 17, 31, SCENE_ROUTE23SOUTH_BADGE_CHECK_2, Route23SouthPlainBadgeTriggerScript`
+ added `coord_event 10, 22, SCENE_ROUTE23SOUTH_BADGE_CHECK_3, Route23SouthFogBadgeTriggerScript`
+ added `coord_event 11, 22, SCENE_ROUTE23SOUTH_BADGE_CHECK_3, Route23SouthFogBadgeTriggerScript`
+ added `coord_event 13, 22, SCENE_ROUTE23SOUTH_BADGE_CHECK_3, Route23SouthFogBadgeTriggerScript`
+ added `coord_event 14, 22, SCENE_ROUTE23SOUTH_BADGE_CHECK_3, Route23SouthFogBadgeTriggerScript`
+ added `coord_event 15, 22, SCENE_ROUTE23SOUTH_BADGE_CHECK_3, Route23SouthFogBadgeTriggerScript`
+ added `coord_event 6, 7, SCENE_ROUTE23SOUTH_BADGE_CHECK_4, Route23SouthStormBadgeTriggerScript`
+ added `coord_event 8, 7, SCENE_ROUTE23SOUTH_BADGE_CHECK_4, Route23SouthStormBadgeTriggerScript`
+ added `coord_event 9, 7, SCENE_ROUTE23SOUTH_BADGE_CHECK_4, Route23SouthStormBadgeTriggerScript`
+ added `object_event 17, 55, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route23SouthZephyrBadgeOfficerScript, -1`
+ added `object_event 10, 47, SPRITE_OFFICER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route23SouthHiveBadgeOfficerScript, -1`
+ added `object_event 13, 31, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route23SouthPlainBadgeOfficerScript, -1`
+ added `object_event 12, 22, SPRITE_SWIMMING_OFFICER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route23SouthFogBadgeOfficerScript, -1`
+ added `object_event 7, 7, SPRITE_SWIMMING_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route23SouthStormBadgeOfficerScript, -1`

## Route24

- removed `coord_event 19, 15, 1, Route24BridgeOverheadTrigger`
- removed `coord_event 20, 14, 1, Route24BridgeOverheadTrigger`
- removed `coord_event 21, 14, 1, Route24BridgeOverheadTrigger`
- removed `coord_event 22, 15, 1, Route24BridgeOverheadTrigger`
- removed `coord_event 20, 15, 0, Route24BridgeUnderfootTrigger`
- removed `coord_event 21, 15, 0, Route24BridgeUnderfootTrigger`
- removed `coord_event 20, 39, 0, Route24BridgeUnderfootTrigger`
- removed `coord_event 21, 39, 0, Route24BridgeUnderfootTrigger`
- removed `coord_event 25, 13, 1, Route24BridgeOverheadTrigger`
- removed `coord_event 25, 15, 1, Route24BridgeOverheadTrigger`
- removed `coord_event 25, 16, 1, Route24BridgeOverheadTrigger`
- removed `coord_event 25, 17, 1, Route24BridgeOverheadTrigger`
- removed `coord_event 25, 18, 1, Route24BridgeOverheadTrigger`
- removed `coord_event 25, 19, 1, Route24BridgeOverheadTrigger`
- removed `coord_event 25, 20, 1, Route24BridgeOverheadTrigger`
- removed `coord_event 25, 21, 1, Route24BridgeOverheadTrigger`
- removed `coord_event 25, 22, 1, Route24BridgeOverheadTrigger`
- removed `coord_event 25, 23, 1, Route24BridgeOverheadTrigger`
- removed `bg_event 15, 19, BGEVENT_ITEM + MAX_POTION, EVENT_ROUTE_24_HIDDEN_MAX_POTION`
- removed `bg_event 23, 11, BGEVENT_JUMPTEXT, Route24AdvancedTipsSignText`
- removed `object_event 21, 25, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 1, TrainerGruntM31, EVENT_ROUTE_24_ROCKET`
- removed `fruittree_event 16, 5, FRUITTREE_ROUTE_24, LANSAT_BERRY, PAL_NPC_PINK`
+ added `coord_event 19, 13, SCENE_ROUTE24_BRIDGE_OVERHEAD, Route24BridgeOverheadTrigger`
+ added `coord_event 20, 12, SCENE_ROUTE24_BRIDGE_OVERHEAD, Route24BridgeOverheadTrigger`
+ added `coord_event 21, 12, SCENE_ROUTE24_BRIDGE_OVERHEAD, Route24BridgeOverheadTrigger`
+ added `coord_event 22, 13, SCENE_ROUTE24_BRIDGE_OVERHEAD, Route24BridgeOverheadTrigger`
+ added `coord_event 20, 13, SCENE_ROUTE24_BRIDGE_UNDERFOOT, Route24BridgeUnderfootTrigger`
+ added `coord_event 21, 13, SCENE_ROUTE24_BRIDGE_UNDERFOOT, Route24BridgeUnderfootTrigger`
+ added `coord_event 16, 37, SCENE_ROUTE24_BRIDGE_OVERHEAD, Route24BridgeOverheadTrigger`
+ added `coord_event 17, 37, SCENE_ROUTE24_BRIDGE_OVERHEAD, Route24BridgeOverheadTrigger`
+ added `coord_event 20, 37, SCENE_ROUTE24_BRIDGE_UNDERFOOT, Route24BridgeUnderfootTrigger`
+ added `coord_event 21, 37, SCENE_ROUTE24_BRIDGE_UNDERFOOT, Route24BridgeUnderfootTrigger`
+ added `coord_event 25, 11, SCENE_ROUTE24_BRIDGE_OVERHEAD, Route24BridgeOverheadTrigger`
+ added `coord_event 25, 13, SCENE_ROUTE24_BRIDGE_OVERHEAD, Route24BridgeOverheadTrigger`
+ added `coord_event 25, 14, SCENE_ROUTE24_BRIDGE_OVERHEAD, Route24BridgeOverheadTrigger`
+ added `coord_event 25, 15, SCENE_ROUTE24_BRIDGE_OVERHEAD, Route24BridgeOverheadTrigger`
+ added `coord_event 25, 16, SCENE_ROUTE24_BRIDGE_OVERHEAD, Route24BridgeOverheadTrigger`
+ added `coord_event 25, 17, SCENE_ROUTE24_BRIDGE_OVERHEAD, Route24BridgeOverheadTrigger`
+ added `coord_event 25, 18, SCENE_ROUTE24_BRIDGE_OVERHEAD, Route24BridgeOverheadTrigger`
+ added `coord_event 25, 19, SCENE_ROUTE24_BRIDGE_OVERHEAD, Route24BridgeOverheadTrigger`
+ added `coord_event 25, 20, SCENE_ROUTE24_BRIDGE_OVERHEAD, Route24BridgeOverheadTrigger`
+ added `coord_event 25, 21, SCENE_ROUTE24_BRIDGE_OVERHEAD, Route24BridgeOverheadTrigger`
+ added `bg_event 15, 17, BGEVENT_ITEM + MAX_POTION, EVENT_ROUTE_24_HIDDEN_MAX_POTION`
+ added `bg_event 23, 9, BGEVENT_JUMPTEXT, Route24AdvancedTipsSignText`
+ added `object_event 21, 23, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 1, TrainerGruntM31, EVENT_ROUTE_24_ROCKET`
+ added `fruittree_event 16, 3, FRUITTREE_ROUTE_24, LANSAT_BERRY, PAL_NPC_PINK`

## Route25

- removed `object_event 30, 8, SPRITE_ACE_TRAINER_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, TrainerCooltrainermKevin, EVENT_ROUTE_25_COOLTRAINER_M_BEFORE`
- removed `object_event 32, 8, SPRITE_ACE_TRAINER_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, CooltrainermKevinAfterBattleText, EVENT_ROUTE_25_COOLTRAINER_M_AFTER`
- removed `object_event 7, 11, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerSchoolboyDudley, -1`
- removed `object_event 11, 8, SPRITE_LASS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerLassEllen, -1`
- removed `object_event 14, 10, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerSchoolboyJoe, -1`
- removed `object_event 12, 6, SPRITE_LASS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerLassLaura, -1`
- removed `object_event 18, 9, SPRITE_CAMPER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerCamperLloyd, -1`
- removed `object_event 22, 11, SPRITE_LASS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerLassShannon, -1`
- removed `object_event 25, 7, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerSupernerdPat, -1`
- removed `itemball_event 25, 4, PROTEIN, 1, EVENT_ROUTE_25_PROTEIN`
- removed `cuttree_event 28, 6, EVENT_ROUTE_25_CUT_TREE`
- removed `object_event 20, 4, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route25MewYoungsterText, -1`
- removed `object_event 21, 4, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, SLOWPOKE, -1, PAL_NPC_PINK, OBJECTTYPE_SCRIPT, PLAIN_FORM, Route25SlowpokeScript, -1`
+ added `object_event 30, 6, SPRITE_ACE_TRAINER_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, TrainerCooltrainermKevin, EVENT_ROUTE_25_COOLTRAINER_M_BEFORE`
+ added `object_event 32, 6, SPRITE_ACE_TRAINER_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, CooltrainermKevinAfterBattleText, EVENT_ROUTE_25_COOLTRAINER_M_AFTER`
+ added `object_event 7, 9, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerSchoolboyDudley, -1`
+ added `object_event 11, 6, SPRITE_LASS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerLassEllen, -1`
+ added `object_event 14, 8, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerSchoolboyJoe, -1`
+ added `object_event 12, 4, SPRITE_LASS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerLassLaura, -1`
+ added `object_event 18, 7, SPRITE_CAMPER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerCamperLloyd, -1`
+ added `object_event 22, 9, SPRITE_LASS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerLassShannon, -1`
+ added `object_event 25, 5, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerSupernerdPat, -1`
+ added `itemball_event 25, 2, PROTEIN, 1, EVENT_ROUTE_25_PROTEIN`
+ added `cuttree_event 28, 4, EVENT_ROUTE_25_CUT_TREE`
+ added `object_event 20, 2, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route25MewYoungsterText, -1`
+ added `object_event 21, 2, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, SLOWPOKE, -1, PAL_MON_PINK, OBJECTTYPE_SCRIPT, PLAIN_FORM, Route25SlowpokeScript, -1`

## Route26

- removed `warp_event 7, 5, POKEMON_LEAGUE_GATE, 3`
- removed `bg_event 8, 6, BGEVENT_JUMPTEXT, Route26SignText`
+ added `warp_event 8, 5, POKEMON_LEAGUE_GATE, 3`
+ added `warp_event 9, 5, POKEMON_LEAGUE_GATE, 4`
+ added `bg_event 10, 6, BGEVENT_JUMPTEXT, Route26SignText`

## Route26DayofWeekSiblingsHouse

- removed `warp_event 2, 7, ROUTE_26, 3`
- removed `warp_event 3, 7, ROUTE_26, 3`
+ added `warp_event 2, 7, ROUTE_26, 4`
+ added `warp_event 3, 7, ROUTE_26, 4`

## Route26HealSpeechHouse

- removed `warp_event 2, 7, ROUTE_26, 2`
- removed `warp_event 3, 7, ROUTE_26, 2`
+ added `warp_event 2, 7, ROUTE_26, 3`
+ added `warp_event 3, 7, ROUTE_26, 3`

## Route27

- removed `warp_event 33, 7, ROUTE_27_REST_HOUSE, 1`
- removed `warp_event 26, 5, TOHJO_FALLS, 1`
- removed `warp_event 36, 5, TOHJO_FALLS, 2`
- removed `coord_event 18, 10, 0, FirstStepIntoKantoLeftScene`
- removed `coord_event 19, 10, 0, FirstStepIntoKantoRightScene`
- removed `bg_event 25, 7, BGEVENT_JUMPTEXT, TohjoFallsSignText`
- removed `object_event 48, 12, SPRITE_VETERAN_F, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route27VeteranfScript, -1`
- removed `object_event 21, 10, SPRITE_FAT_GUY, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route27FisherText, -1`
- removed `object_event 48, 7, SPRITE_ACE_TRAINER_M, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerCooltrainermBlake, -1`
- removed `object_event 58, 6, SPRITE_ACE_TRAINER_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerAceDuoJakeandbri1, -1`
- removed `object_event 59, 6, SPRITE_ACE_TRAINER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerAceDuoJakeandbri2, -1`
- removed `object_event 72, 10, SPRITE_ACE_TRAINER_F, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 4, TrainerCooltrainerfReena, -1`
- removed `object_event 37, 6, SPRITE_ACE_TRAINER_F, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerCooltrainerfMegan, -1`
- removed `object_event 65, 7, SPRITE_PSYCHIC, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerPsychicGilbert, -1`
- removed `object_event 58, 13, SPRITE_BIRD_KEEPER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 3, TrainerBird_keeperJose1, -1`
- removed `itemball_event 53, 12, RARE_CANDY, 1, EVENT_ROUTE_27_RARE_CANDY`
- removed `itemball_event 71, 4, DESTINY_KNOT, 1, EVENT_ROUTE_27_DESTINY_KNOT`
- removed `fruittree_event 60, 12, FRUITTREE_ROUTE_27, LUM_BERRY, PAL_NPC_GREEN`
+ added `warp_event 29, 7, ROUTE_27_REST_HOUSE, 1`
+ added `warp_event 22, 5, TOHJO_FALLS, 1`
+ added `warp_event 32, 5, TOHJO_FALLS, 2`
+ added `coord_event 14, 10, SCENE_ROUTE27_FIRST_STEP_INTO_KANTO, FirstStepIntoKantoLeftScene`
+ added `coord_event 15, 10, SCENE_ROUTE27_FIRST_STEP_INTO_KANTO, FirstStepIntoKantoRightScene`
+ added `bg_event 21, 7, BGEVENT_JUMPTEXT, TohjoFallsSignText`
+ added `object_event 44, 12, SPRITE_VETERAN_F, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route27VeteranfScript, -1`
+ added `object_event 17, 10, SPRITE_FAT_GUY, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route27FisherText, -1`
+ added `object_event 44, 7, SPRITE_ACE_TRAINER_M, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerCooltrainermBlake, -1`
+ added `object_event 54, 6, SPRITE_ACE_TRAINER_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerAceDuoJakeandbri1, -1`
+ added `object_event 55, 6, SPRITE_ACE_TRAINER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerAceDuoJakeandbri2, -1`
+ added `object_event 68, 10, SPRITE_ACE_TRAINER_F, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 4, TrainerCooltrainerfReena, -1`
+ added `object_event 33, 6, SPRITE_ACE_TRAINER_F, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerCooltrainerfMegan, -1`
+ added `object_event 61, 7, SPRITE_PSYCHIC, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerPsychicGilbert, -1`
+ added `object_event 54, 13, SPRITE_BIRD_KEEPER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 3, TrainerBird_keeperJose1, -1`
+ added `itemball_event 49, 12, RARE_CANDY, 1, EVENT_ROUTE_27_RARE_CANDY`
+ added `itemball_event 67, 4, DESTINY_KNOT, 1, EVENT_ROUTE_27_DESTINY_KNOT`
+ added `fruittree_event 56, 12, FRUITTREE_ROUTE_27, LUM_BERRY, PAL_NPC_GREEN`

## Route28

- removed `warp_event 33, 5, POKEMON_LEAGUE_GATE, 7`
- removed `bg_event 31, 5, BGEVENT_JUMPTEXT, Route28SignText`
+ added `warp_event 33, 6, POKEMON_LEAGUE_GATE, 7`
+ added `warp_event 33, 7, POKEMON_LEAGUE_GATE, 8`
+ added `bg_event 29, 7, BGEVENT_JUMPTEXT, Route28SignText`

## Route28FamousSpeechHouse

- removed `pokemon_event 6, 5, SKARMORY, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_GRAY, CelebritysSkarmoryText, -1`
+ added `pokemon_event 6, 5, SKARMORY, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_GRAY, CelebritysSkarmoryText, -1`

## Route29

- removed `coord_event 53, 8, 1, Route29Tutorial1`
- removed `coord_event 53, 9, 1, Route29Tutorial2`
+ added `coord_event 53, 8, SCENE_ROUTE29_CATCH_TUTORIAL, Route29Tutorial1`
+ added `coord_event 53, 9, SCENE_ROUTE29_CATCH_TUTORIAL, Route29Tutorial2`

## Route30

- removed `warp_event 7, 39, ROUTE_30_BERRY_SPEECH_HOUSE, 1`
- removed `warp_event 17, 5, MR_POKEMONS_HOUSE, 1`
- removed `bg_event 9, 43, BGEVENT_JUMPTEXT, Route30SignText`
- removed `bg_event 13, 29, BGEVENT_JUMPTEXT, MrPokemonsHouseDirectionsSignText`
- removed `bg_event 15, 5, BGEVENT_JUMPTEXT, MrPokemonsHouseSignText`
- removed `bg_event 3, 21, BGEVENT_JUMPTEXT, Route30TrainerTipsText`
- removed `bg_event 11, 8, BGEVENT_JUMPTEXT, Route30AdvancedTipsText`
- removed `bg_event 14, 9, BGEVENT_ITEM + POTION, EVENT_ROUTE_30_HIDDEN_POTION`
- removed `bg_event 5, 39, BGEVENT_JUMPTEXT, BerryMastersHouseSignText`
- removed `object_event 5, 26, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, YoungsterJoey_ImportantBattleScript, EVENT_ROUTE_30_BATTLE`
- removed `pokemon_event 5, 24, PIDGEY, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BROWN, ClearText, EVENT_ROUTE_30_BATTLE`
- removed `object_event 5, 25, SPRITE_RATTATA_BACK, SPRITEMOVEDATA_POKEMON, 0, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_ROUTE_30_BATTLE`
- removed `object_event 2, 28, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 3, TrainerYoungsterJoey, EVENT_ROUTE_30_YOUNGSTER_JOEY`
- removed `object_event 5, 23, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerYoungsterMikey, -1`
- removed `object_event 1, 7, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBug_catcherDon, -1`
- removed `object_event 7, 30, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, Route30YoungsterScript, -1`
- removed `object_event 2, 13, SPRITE_LASS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route30CooltrainerFText, -1`
- removed `cuttree_event 8, 6, EVENT_ROUTE_30_CUT_TREE`
- removed `fruittree_event 10, 39, FRUITTREE_ROUTE_30_1, ORAN_BERRY, PAL_NPC_BLUE`
- removed `fruittree_event 11, 5, FRUITTREE_ROUTE_30_2, PECHA_BERRY, PAL_NPC_PINK`
- removed `itemball_event 8, 35, ANTIDOTE, 1, EVENT_ROUTE_30_ANTIDOTE`
+ added `warp_event 9, 39, ROUTE_30_BERRY_SPEECH_HOUSE, 1`
+ added `warp_event 19, 5, MR_POKEMONS_HOUSE, 1`
+ added `bg_event 11, 43, BGEVENT_JUMPTEXT, Route30SignText`
+ added `bg_event 15, 27, BGEVENT_JUMPTEXT, MrPokemonsHouseDirectionsSignText`
+ added `bg_event 17, 5, BGEVENT_JUMPTEXT, MrPokemonsHouseSignText`
+ added `bg_event 5, 21, BGEVENT_JUMPTEXT, Route30TrainerTipsText`
+ added `bg_event 13, 8, BGEVENT_JUMPTEXT, Route30AdvancedTipsText`
+ added `bg_event 16, 9, BGEVENT_ITEM + POTION, EVENT_ROUTE_30_HIDDEN_POTION`
+ added `bg_event 7, 39, BGEVENT_JUMPTEXT, BerryMastersHouseSignText`
+ added `object_event 7, 26, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, YoungsterJoey_ImportantBattleScript, EVENT_ROUTE_30_BATTLE`
+ added `pokemon_event 7, 24, PIDGEY, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BROWN, ClearText, EVENT_ROUTE_30_BATTLE`
+ added `object_event 7, 25, SPRITE_RATTATA_BACK, SPRITEMOVEDATA_RATTATA_BACK, 0, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_ROUTE_30_BATTLE`
+ added `object_event 4, 28, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 3, TrainerYoungsterJoey, EVENT_ROUTE_30_YOUNGSTER_JOEY`
+ added `object_event 7, 23, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerYoungsterMikey, -1`
+ added `object_event 3, 7, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBug_catcherDon, -1`
+ added `object_event 10, 31, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 2, -1, PAL_NPC_ORANGE, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route30YoungsterText, -1`
+ added `object_event 4, 13, SPRITE_LASS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route30CooltrainerFText, -1`
+ added `cuttree_event 10, 6, EVENT_ROUTE_30_CUT_TREE_1`
+ added `cuttree_event 3, 29, EVENT_ROUTE_30_CUT_TREE_2`
+ added `fruittree_event 12, 39, FRUITTREE_ROUTE_30_1, ORAN_BERRY, PAL_NPC_BLUE`
+ added `fruittree_event 13, 5, FRUITTREE_ROUTE_30_2, PECHA_BERRY, PAL_NPC_PINK`
+ added `itemball_event 10, 35, ANTIDOTE, 1, EVENT_ROUTE_30_ANTIDOTE`

## Route32

- removed `coord_event 18, 8, 0, Route32CooltrainerMStopsYou`
- removed `coord_event 10, 24, 1, Route32LyraIntroducesHiddenGrottoes1`
- removed `coord_event 11, 24, 1, Route32LyraIntroducesHiddenGrottoes2`
- removed `coord_event 12, 24, 1, Route32LyraIntroducesHiddenGrottoes3`
- removed `coord_event 13, 24, 1, Route32LyraIntroducesHiddenGrottoes4`
- removed `coord_event 7, 71, 2, Route32WannaBuyASlowpokeTailScript`
- removed `cuttree_event 19, 32, EVENT_CHERRYGROVE_BAY_CUT_TREE`
+ added `coord_event 18, 8, SCENE_ROUTE32_COOLTRAINER_M_BLOCKS, Route32CooltrainerMStopsYou`
+ added `coord_event 10, 24, SCENE_ROUTE32_LYRA_GROTTOES, Route32LyraIntroducesHiddenGrottoes1`
+ added `coord_event 11, 24, SCENE_ROUTE32_LYRA_GROTTOES, Route32LyraIntroducesHiddenGrottoes2`
+ added `coord_event 12, 24, SCENE_ROUTE32_LYRA_GROTTOES, Route32LyraIntroducesHiddenGrottoes3`
+ added `coord_event 13, 24, SCENE_ROUTE32_LYRA_GROTTOES, Route32LyraIntroducesHiddenGrottoes4`
+ added `coord_event 7, 71, SCENE_ROUTE32_OFFER_SLOWPOKETAIL, Route32WannaBuyASlowpokeTailScript`
+ added `cuttree_event 19, 32, EVENT_CHERRYGROVE_BAY_CUT_TREE_1`

## Route32Coast

- removed `object_event 18, 65, SPRITE_SWIMMER_GUY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerSwimmermLucas, -1`
- removed `object_event 18, 21, SPRITE_BIRD_KEEPER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 5, GenericTrainerBird_keeperPowell, -1`
- removed `itemball_event 22, 61, SOFT_SAND, 1, EVENT_ROUTE_32_COAST_SOFT_SAND`
+ added `object_event 18, 65, SPRITE_SWIMMER_GUY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_DARK_RED, OBJECTTYPE_TRAINER, 4, TrainerSwimmermLucas, -1`
+ added `object_event 17, 21, SPRITE_BIRD_KEEPER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_DARK_BLUE, OBJECTTYPE_TRAINER, 4, TrainerBird_keeperPowell, -1`
+ added `object_event 21, 61, SPRITE_FLOATING_BALL, SPRITEMOVEDATA_POKEMON, 0, 0, -1, 0, OBJECTTYPE_ITEMBALL, PLAYEREVENT_ITEMBALL, SOFT_SAND, 1, EVENT_ROUTE_32_COAST_SOFT_SAND`

## Route32RuinsOfAlphGate

- removed `warp_event 0, 4, RUINS_OF_ALPH_OUTSIDE, 10`
- removed `warp_event 0, 5, RUINS_OF_ALPH_OUTSIDE, 11`
+ added `warp_event 0, 4, RUINS_OF_ALPH_OUTSIDE, 11`
+ added `warp_event 0, 5, RUINS_OF_ALPH_OUTSIDE, 12`

## Route33

- removed `object_event 12, 17, SPRITE_SCHOOLGIRL, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerSchoolgirlImogen, -1`
+ added `object_event 12, 17, SPRITE_SCHOOLGIRL, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_DARK_RED, OBJECTTYPE_TRAINER, 3, TrainerSchoolgirlImogen, -1`

## Route34

- removed `coord_event 8, 17, 1, Route34LyraTrigger1`
- removed `coord_event 9, 17, 1, Route34LyraTrigger2`
- removed `coord_event 10, 17, 1, Route34LyraTrigger3`
+ added `coord_event 8, 17, SCENE_ROUTE34_LYRA_DAYCARE, Route34LyraTrigger1`
+ added `coord_event 9, 17, SCENE_ROUTE34_LYRA_DAYCARE, Route34LyraTrigger2`
+ added `coord_event 10, 17, SCENE_ROUTE34_LYRA_DAYCARE, Route34LyraTrigger3`

## Route34Coast

- removed `object_event 10, 21, SPRITE_SWIMMER_GUY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerSwimmermNadar, -1`
- removed `itemball_event 4, 34, PEARL_STRING, 1, EVENT_ROUTE_34_COAST_PEARL_STRING`
+ added `object_event 10, 21, SPRITE_SWIMMER_GUY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_DARK_RED, OBJECTTYPE_TRAINER, 4, TrainerSwimmermNadar, -1`
+ added `object_event 3, 37, SPRITE_FLOATING_BALL, SPRITEMOVEDATA_POKEMON, 0, 0, -1, 0, OBJECTTYPE_ITEMBALL, PLAYEREVENT_ITEMBALL, PEARL_STRING, 1, EVENT_ROUTE_34_COAST_PEARL_STRING`

## Route34IlexForestGate

- removed `coord_event 4, 7, 0, Route34IlexForestGateCelebiEvent`
- removed `pokemon_event 9, 4, HERACROSS, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BLUE, Route34IlexForestGateHeracrossText, EVENT_ROUTE_34_ILEX_FOREST_GATE_TEACHER_BEHIND_COUNTER`
+ added `coord_event 4, 7, SCENE_ROUTE34ILEXFORESTGATE_TEACHER_BLOCKS, Route34IlexForestGateCelebiEvent`
+ added `pokemon_event 9, 4, HERACROSS, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BLUE, Route34IlexForestGateHeracrossText, EVENT_ROUTE_34_ILEX_FOREST_GATE_TEACHER_BEHIND_COUNTER`

## Route35CoastNorth

- removed `bg_event 6, 21, BGEVENT_JUMPTEXT, Route35CoastNorthPokeathlonDomeSignText`
- removed `bg_event 6, 12, BGEVENT_JUMPTEXT, Route35CoastNorthAdvancedTipsSignText`
- removed `bg_event 3, 11, BGEVENT_ITEM + BIG_PEARL, EVENT_ROUTE_35_COAST_NORTH_HIDDEN_BIG_PEARL`
- removed `bg_event 5, 23, BGEVENT_ITEM + SOFT_SAND, EVENT_ROUTE_35_COAST_NORTH_HIDDEN_SOFT_SAND`
- removed `smashrock_event 8, 17, `
- removed `smashrock_event 11, 20, `
+ added `bg_event 9, 19, BGEVENT_JUMPTEXT, Route35CoastNorthAdvancedTipsSignText`
+ added `bg_event 4, 13, BGEVENT_ITEM + BIG_PEARL, EVENT_ROUTE_35_COAST_NORTH_HIDDEN_BIG_PEARL`
+ added `bg_event 4, 22, BGEVENT_ITEM + SOFT_SAND, EVENT_ROUTE_35_COAST_NORTH_HIDDEN_SOFT_SAND`

## Route35CoastSouth

- removed `itemball_event 37, 5, BIG_PEARL, 1, EVENT_ROUTE_35_COAST_SOUTH_BIG_PEARL`
- removed `keyitemball_event 6, 16, GO_GOGGLES, EVENT_OLIVINE_PORT_GO_GOGGLES`
+ added `object_event 33, 6, SPRITE_FLOATING_BALL, SPRITEMOVEDATA_POKEMON, 0, 0, -1, 0, OBJECTTYPE_ITEMBALL, PLAYEREVENT_ITEMBALL, BIG_PEARL, 1, EVENT_ROUTE_35_COAST_SOUTH_BIG_PEARL`
+ added `object_event 6, 15, SPRITE_FLOATING_BALL, SPRITEMOVEDATA_POKEMON, 0, 0, -1, PAL_NPC_ENV_GREEN, OBJECTTYPE_ITEMBALL, PLAYEREVENT_KEYITEMBALL, GO_GOGGLES, EVENT_OLIVINE_PORT_GO_GOGGLES`
+ added `itemball_event 13, 31, STAR_PIECE, 1, EVENT_GOLDENROD_HARBOR_STAR_PIECE`
+ added `object_event 17, 31, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, -1`

## Route36

- removed `warp_event 22, 8, ROUTE_36_NATIONAL_PARK_GATE, 3`
- removed `warp_event 22, 9, ROUTE_36_NATIONAL_PARK_GATE, 4`
- removed `warp_event 51, 13, ROUTE_36_RUINS_OF_ALPH_GATE, 1`
- removed `warp_event 52, 13, ROUTE_36_RUINS_OF_ALPH_GATE, 2`
- removed `warp_event 61, 8, ROUTE_36_VIOLET_GATE, 1`
- removed `warp_event 61, 9, ROUTE_36_VIOLET_GATE, 2`
- removed `warp_event 30, 12, HIDDEN_TREE_GROTTO, 1`
- removed `coord_event 24, 7, 1, Route36SuicuneScript`
- removed `coord_event 26, 7, 1, Route36SuicuneScript`
- removed `bg_event 33, 1, BGEVENT_JUMPTEXT, Route36TrainerTips2Text`
- removed `bg_event 49, 11, BGEVENT_JUMPTEXT, RuinsOfAlphNorthSignText`
- removed `bg_event 59, 7, BGEVENT_JUMPTEXT, Route36SignText`
- removed `bg_event 25, 7, BGEVENT_JUMPTEXT, Route36TrainerTips1Text`
- removed `bg_event 53, 4, BGEVENT_JUMPTEXT, Route36AdvancedTips1Text`
- removed `bg_event 34, 7, BGEVENT_JUMPTEXT, Route36AdvancedTips2Text`
- removed `bg_event 30, 11, BGEVENT_JUMPSTD, treegrotto, HIDDENGROTTO_ROUTE_36`
- removed `bg_event 31, 11, BGEVENT_JUMPSTD, treegrotto, HIDDENGROTTO_ROUTE_36`
- removed `object_event 39, 9, SPRITE_WEIRD_TREE, SPRITEMOVEDATA_SUDOWOODO, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, SudowoodoScript, EVENT_ROUTE_36_SUDOWOODO`
- removed `object_event 53, 6, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_WANDER, 1, 1, -1, 0, OBJECTTYPE_SCRIPT, 0, ArthurScript, EVENT_ROUTE_36_ARTHUR_OF_THURSDAY`
- removed `object_event 37, 12, SPRITE_CUTE_GIRL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, Route36FloriaScript, EVENT_FLORIA_AT_SUDOWOODO`
- removed `pokemon_event 25, 6, SUICUNE, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BLUE, ClearText, EVENT_SAW_SUICUNE_ON_ROUTE_36`
- removed `object_event 30, 6, SPRITE_ACE_TRAINER_F, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route36CooltrainerfChiaraScript, -1`
- removed `object_event 24, 13, SPRITE_PSYCHIC, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerPsychicMark, -1`
- removed `object_event 35, 14, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 5, TrainerSchoolboyAlan1, -1`
- removed `object_event 57, 9, SPRITE_CUTE_GIRL, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 2, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, Route36LassScript, -1`
- removed `object_event 48, 9, SPRITE_FAT_GUY, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_SCRIPT, 0, Route36RockSmashGuyScript, -1`
- removed `fruittree_event 25, 4, FRUITTREE_ROUTE_36, RAWST_BERRY, PAL_NPC_TEAL`
- removed `object_event 50, 5, SPRITE_SCHOOLGIRL, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerSchoolgirlMolly, -1`
+ added `warp_event 4, 8, ROUTE_36_NATIONAL_PARK_GATE, 3`
+ added `warp_event 4, 9, ROUTE_36_NATIONAL_PARK_GATE, 4`
+ added `warp_event 33, 13, ROUTE_36_RUINS_OF_ALPH_GATE, 1`
+ added `warp_event 34, 13, ROUTE_36_RUINS_OF_ALPH_GATE, 2`
+ added `warp_event 41, 8, ROUTE_36_VIOLET_GATE, 1`
+ added `warp_event 41, 9, ROUTE_36_VIOLET_GATE, 2`
+ added `warp_event 12, 12, HIDDEN_TREE_GROTTO, 1`
+ added `coord_event 6, 7, SCENE_ROUTE36_SUICUNE, Route36SuicuneScript`
+ added `coord_event 8, 7, SCENE_ROUTE36_SUICUNE, Route36SuicuneScript`
+ added `bg_event 15, 1, BGEVENT_JUMPTEXT, Route36TrainerTips2Text`
+ added `bg_event 31, 11, BGEVENT_JUMPTEXT, RuinsOfAlphNorthSignText`
+ added `bg_event 39, 7, BGEVENT_JUMPTEXT, Route36SignText`
+ added `bg_event 7, 7, BGEVENT_JUMPTEXT, Route36TrainerTips1Text`
+ added `bg_event 33, 4, BGEVENT_JUMPTEXT, Route36AdvancedTips1Text`
+ added `bg_event 16, 7, BGEVENT_JUMPTEXT, Route36AdvancedTips2Text`
+ added `bg_event 12, 11, BGEVENT_JUMPSTD, treegrotto, HIDDENGROTTO_ROUTE_36`
+ added `bg_event 13, 11, BGEVENT_JUMPSTD, treegrotto, HIDDENGROTTO_ROUTE_36`
+ added `object_event 21, 9, SPRITE_WEIRD_TREE, SPRITEMOVEDATA_SUDOWOODO, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, SudowoodoScript, EVENT_ROUTE_36_SUDOWOODO`
+ added `object_event 33, 6, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_WANDER, 1, 1, -1, 0, OBJECTTYPE_SCRIPT, 0, ArthurScript, EVENT_ROUTE_36_ARTHUR_OF_THURSDAY`
+ added `object_event 19, 12, SPRITE_CUTE_GIRL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, Route36FloriaScript, EVENT_FLORIA_AT_SUDOWOODO`
+ added `pokemon_event 7, 6, SUICUNE, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_AZURE, ClearText, EVENT_SAW_SUICUNE_ON_ROUTE_36`
+ added `object_event 12, 6, SPRITE_ACE_TRAINER_F, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Route36CooltrainerfChiaraScript, -1`
+ added `object_event 6, 13, SPRITE_PSYCHIC, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerPsychicMark, -1`
+ added `object_event 17, 14, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 5, TrainerSchoolboyAlan1, -1`
+ added `object_event 37, 9, SPRITE_CUTE_GIRL, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 2, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, Route36LassScript, -1`
+ added `object_event 28, 9, SPRITE_FAT_GUY, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_SCRIPT, 0, Route36RockSmashGuyScript, -1`
+ added `fruittree_event 7, 4, FRUITTREE_ROUTE_36, RAWST_BERRY, PAL_NPC_TEAL`
+ added `object_event 30, 5, SPRITE_SCHOOLGIRL, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerSchoolgirlMolly, -1`

## Route36RuinsOfAlphGate

- removed `warp_event 4, 7, RUINS_OF_ALPH_OUTSIDE, 9`
- removed `warp_event 5, 7, RUINS_OF_ALPH_OUTSIDE, 9`
+ added `warp_event 4, 7, RUINS_OF_ALPH_OUTSIDE, 10`
+ added `warp_event 5, 7, RUINS_OF_ALPH_OUTSIDE, 10`

## Route37

- removed `object_event 9, 6, SPRITE_BEAUTY, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBeautyCassandra, -1`
+ added `object_event 9, 6, SPRITE_BEAUTY, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_DARK_BLUE, OBJECTTYPE_TRAINER, 3, TrainerBeautyCassandra, -1`

## Route38

- removed `warp_event 35, 8, ROUTE_38_ECRUTEAK_GATE, 1`
- removed `warp_event 35, 9, ROUTE_38_ECRUTEAK_GATE, 2`
- removed `bg_event 33, 7, BGEVENT_JUMPTEXT, Route38SignText`
- removed `object_event 19, 9, SPRITE_BEAUTY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerBeautyValencia, -1`
- removed `object_event 24, 5, SPRITE_SAILOR, SPRITEMOVEDATA_SPINCOUNTERCLOCKWISE, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerSailorHarry, -1`
- removed `object_event 5, 8, SPRITE_BEAUTY, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerBeautyOlivia, -1`
+ added `warp_event 35, 10, ROUTE_38_ECRUTEAK_GATE, 1`
+ added `warp_event 35, 11, ROUTE_38_ECRUTEAK_GATE, 2`
+ added `bg_event 33, 8, BGEVENT_JUMPTEXT, Route38SignText`
+ added `object_event 26, 9, SPRITE_BEAUTY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerBeautyValencia, -1`
+ added `object_event 24, 5, SPRITE_SAILOR, SPRITEMOVEDATA_SPINCOUNTERCLOCKWISE, 0, 0, -1, PAL_NPC_DARK_BLUE, OBJECTTYPE_TRAINER, 2, TrainerSailorHarry, -1`
+ added `object_event 5, 7, SPRITE_BEAUTY, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerBeautyOlivia, -1`

## Route39

- removed `warp_event 1, 17, ROUTE_39_BARN, 1`
- removed `warp_event 5, 17, ROUTE_39_FARMHOUSE, 1`
- removed `bg_event 5, 45, BGEVENT_JUMPTEXT, Route39TrainerTipsText`
- removed `bg_event 9, 19, BGEVENT_JUMPTEXT, MoomooFarmSignText`
- removed `bg_event 15, 21, BGEVENT_JUMPTEXT, Route39SignText`
- removed `bg_event 10, 45, BGEVENT_JUMPTEXT, Route39AdvancedTips2Text`
- removed `bg_event 5, 27, BGEVENT_ITEM + NUGGET, EVENT_ROUTE_39_HIDDEN_NUGGET`
- removed `object_event 7, 28, SPRITE_COWGIRL, SPRITEMOVEDATA_WANDER, 1, 2, -1, 0, OBJECTTYPE_SCRIPT, 0, Route39CowgirlAnnieScript, -1`
- removed `object_event 13, 43, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 5, GenericTrainerSailorEugene, -1`
- removed `object_event 10, 36, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 4, TrainerPokefanmDerek1, -1`
- removed `object_event 11, 33, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerPokefanfRuth, -1`
- removed `pokemon_event 3, 26, MILTANK, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_PINK, Route39MiltankText, -1`
- removed `pokemon_event 6, 25, MILTANK, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_PINK, Route39MiltankText, -1`
- removed `pokemon_event 4, 29, MILTANK, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_PINK, Route39MiltankText, -1`
- removed `pokemon_event 8, 27, MILTANK, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_PINK, Route39MiltankText, -1`
- removed `object_event 13, 21, SPRITE_PSYCHIC, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerPsychicNorman, -1`
- removed `fruittree_event 9, 17, FRUITTREE_ROUTE_39, CHESTO_BERRY, PAL_NPC_PURPLE`
- removed `object_event 4, 36, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, TrainerPokefanfJaime, -1`
- removed `object_event 4, 44, SPRITE_BEAUTY, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 1, -1, PAL_NPC_GREEN, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route39BeautyText, -1`
- removed `object_event 15, 11, SPRITE_HIKER, SPRITEMOVEDATA_WALK_UP_DOWN, 2, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route39HikerText, -1`
- removed `object_event 25, 22, SPRITE_BEAUTY, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerBeautyOlivia, -1`
- removed `tmhmball_event 1, 21, TM_BULLDOZE, EVENT_ROUTE_39_TM_BULLDOZE`
+ added `warp_event 2, 19, ROUTE_39_BARN, 1`
+ added `warp_event 7, 19, ROUTE_39_FARMHOUSE, 1`
+ added `warp_event 3, 19, ROUTE_39_BARN, 2`
+ added `bg_event 5, 47, BGEVENT_JUMPTEXT, Route39TrainerTipsText`
+ added `bg_event 8, 21, BGEVENT_JUMPTEXT, MoomooFarmSignText`
+ added `bg_event 15, 25, BGEVENT_JUMPTEXT, Route39SignText`
+ added `bg_event 14, 31, BGEVENT_JUMPTEXT, Route39AdvancedTips2Text`
+ added `bg_event 5, 29, BGEVENT_ITEM + NUGGET, EVENT_ROUTE_39_HIDDEN_NUGGET`
+ added `object_event 7, 30, SPRITE_COWGIRL, SPRITEMOVEDATA_WANDER, 1, 2, -1, 0, OBJECTTYPE_SCRIPT, 0, Route39CowgirlAnnieScript, -1`
+ added `object_event 13, 45, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 5, GenericTrainerSailorEugene, -1`
+ added `object_event 10, 38, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 4, TrainerPokefanmDerek1, -1`
+ added `object_event 11, 35, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerPokefanfRuth, -1`
+ added `pokemon_event 3, 28, MILTANK, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_PINK, Route39MiltankText, -1`
+ added `pokemon_event 6, 27, MILTANK, SPRITEMOVEDATA_POKEMON, (1 << MORN) | (1 << DAY), PAL_MON_PINK, Route39MiltankText, -1`
+ added `pokemon_event 4, 31, MILTANK, SPRITEMOVEDATA_POKEMON, (1 << MORN) | (1 << DAY), PAL_MON_AZURE, Route39MiltankText, -1`
+ added `pokemon_event 8, 29, MILTANK, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_PINK, Route39MiltankText, -1`
+ added `object_event 13, 23, SPRITE_PSYCHIC, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerPsychicNorman, -1`
+ added `fruittree_event 9, 26, FRUITTREE_ROUTE_39, CHESTO_BERRY, PAL_NPC_PURPLE`
+ added `object_event 4, 38, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_DARK_PURPLE, OBJECTTYPE_SCRIPT, 0, TrainerPokefanfJaime, -1`
+ added `object_event 4, 46, SPRITE_BEAUTY, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 1, -1, PAL_NPC_GREEN, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route39BeautyText, -1`
+ added `object_event 15, 12, SPRITE_HIKER, SPRITEMOVEDATA_WALK_UP_DOWN, 2, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route39HikerText, -1`
+ added `object_event 25, 25, SPRITE_BEAUTY, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerBeautyOlivia, -1`
+ added `tmhmball_event 1, 23, TM_BULLDOZE, EVENT_ROUTE_39_TM_BULLDOZE`

## Route39Barn

- removed `warp_event 3, 7, ROUTE_39, 1`
- removed `warp_event 4, 7, ROUTE_39, 1`
- removed `object_event 3, 3, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, MILTANK, -1, PAL_NPC_PINK, OBJECTTYPE_SCRIPT, NO_FORM, MooMoo, -1`
- removed `object_event 2, 3, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, Route39BarnTwin1Script, -1`
- removed `object_event 4, 3, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, Route39BarnTwin2Script, -1`
+ added `warp_event 6, 7, ROUTE_39, 1`
+ added `warp_event 7, 7, ROUTE_39, 4`
+ added `bg_event 10, 1, BGEVENT_ITEM + MOOMOO_MILK, EVENT_MOOMOO_FARM_HIDDEN_MOOMOO_MILK`
+ added `bg_event 0, 1, BGEVENT_JUMPTEXT, Route39BarnBucketText`
+ added `bg_event 5, 1, BGEVENT_JUMPTEXT, Route39BarnBucketText`
+ added `bg_event 10, 1, BGEVENT_JUMPTEXT, Route39BarnBucketText`
+ added `object_event 6, 3, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, MILTANK, -1, PAL_MON_PINK, OBJECTTYPE_SCRIPT, NO_FORM, MooMoo, -1`
+ added `object_event 5, 3, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, Route39BarnTwin1Script, -1`
+ added `object_event 7, 3, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, Route39BarnTwin2Script, -1`
+ added `pokemon_event 2, 2, MILTANK, SPRITEMOVEDATA_POKEMON, (1 << EVE) | (1 << NITE), PAL_MON_PINK, MoomooHappyMooText, -1`
+ added `pokemon_event 11, 2, MILTANK, SPRITEMOVEDATA_POKEMON, (1 << EVE) | (1 << NITE), PAL_MON_AZURE, MoomooHappyMooText, -1`

## Route39RuggedRoadGate

- removed `coord_event 2, 4, 0, Route39RuggedRoadGateGoGogglesCheck`
- removed `coord_event 3, 4, 0, Route39RuggedRoadGateGoGogglesCheck`
- removed `coord_event 4, 4, 0, Route39RuggedRoadGateGoGogglesCheck`
- removed `coord_event 5, 4, 0, Route39RuggedRoadGateStepLeftOneTrigger`
- removed `coord_event 6, 4, 0, Route39RuggedRoadGateStepLeftTwoTrigger`
- removed `coord_event 7, 4, 0, Route39RuggedRoadGateStepLeftThreeTrigger`
+ added `coord_event 2, 4, SCENE_ROUTE39RUGGEDROADGATE_BICYCLE_CHECK, Route39RuggedRoadGateGoGogglesCheck`
+ added `coord_event 3, 4, SCENE_ROUTE39RUGGEDROADGATE_BICYCLE_CHECK, Route39RuggedRoadGateGoGogglesCheck`
+ added `coord_event 4, 4, SCENE_ROUTE39RUGGEDROADGATE_BICYCLE_CHECK, Route39RuggedRoadGateGoGogglesCheck`
+ added `coord_event 5, 4, SCENE_ROUTE39RUGGEDROADGATE_BICYCLE_CHECK, Route39RuggedRoadGateStepLeftOneTrigger`
+ added `coord_event 6, 4, SCENE_ROUTE39RUGGEDROADGATE_BICYCLE_CHECK, Route39RuggedRoadGateStepLeftTwoTrigger`
+ added `coord_event 7, 4, SCENE_ROUTE39RUGGEDROADGATE_BICYCLE_CHECK, Route39RuggedRoadGateStepLeftThreeTrigger`

## Route40

- removed `object_event 8, 10, SPRITE_BEAUTY, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, MonicaScript, EVENT_ROUTE_40_MONICA_OF_MONDAY`
- removed `smashrock_event 7, 11, `
+ added `object_event 7, 11, SPRITE_BEAUTY, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, MonicaScript, EVENT_ROUTE_40_MONICA_OF_MONDAY`
+ added `smashrock_event 8, 10, `

## Route42

- removed `coord_event 12, 6, 1, Route42LyraScript1`
- removed `coord_event 12, 7, 1, Route42LyraScript2`
- removed `coord_event 12, 8, 1, Route42LyraScript3`
- removed `coord_event 12, 9, 1, Route42LyraScript4`
- removed `coord_event 10, 6, 1, Route42LyraScript5`
- removed `coord_event 24, 14, 2, Route42SuicuneScript`
- removed `pokemon_event 26, 16, SUICUNE, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BLUE, ClearText, EVENT_SAW_SUICUNE_ON_ROUTE_42`
- removed `fruittree_event 29, 16, FRUITTREE_ROUTE_42_3, YLW_APRICORN, PAL_NPC_YELLOW`
+ added `coord_event 12, 6, SCENE_ROUTE42_LYRA, Route42LyraScript1`
+ added `coord_event 12, 7, SCENE_ROUTE42_LYRA, Route42LyraScript2`
+ added `coord_event 12, 8, SCENE_ROUTE42_LYRA, Route42LyraScript3`
+ added `coord_event 12, 9, SCENE_ROUTE42_LYRA, Route42LyraScript4`
+ added `coord_event 10, 6, SCENE_ROUTE42_LYRA, Route42LyraScript5`
+ added `coord_event 24, 14, SCENE_ROUTE42_SUICUNE, Route42SuicuneScript`
+ added `pokemon_event 26, 16, SUICUNE, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_AZURE, ClearText, EVENT_SAW_SUICUNE_ON_ROUTE_42`
+ added `fruittree_event 29, 16, FRUITTREE_ROUTE_42_3, YLW_APRICORN, PAL_NPC_ENV_YELLOW`

## Route45

- removed `warp_event 4, 5, DARK_CAVE_BLACKTHORN_ENTRANCE, 1`
- removed `warp_event 16, 22, HIDDEN_CAVE_GROTTO, 1`
- removed `bg_event 17, 5, BGEVENT_JUMPTEXT, Route45SignText`
- removed `bg_event 17, 78, BGEVENT_ITEM + PP_UP, EVENT_ROUTE_45_HIDDEN_PP_UP`
- removed `bg_event 16, 21, BGEVENT_JUMPSTD, cavegrotto, HIDDENGROTTO_ROUTE_45`
- removed `object_event 19, 75, SPRITE_DRAGON_TAMER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 2, -1, 0, OBJECTTYPE_SCRIPT, 0, Route45Dragon_tamerScript, -1`
- removed `object_event 5, 59, SPRITE_BATTLE_GIRL, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerBattleGirlNozomi, -1`
- removed `object_event 12, 18, SPRITE_HIKER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerHikerErik, -1`
- removed `object_event 19, 65, SPRITE_HIKER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerHikerMichael, -1`
- removed `object_event 7, 28, SPRITE_HIKER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 2, TrainerHikerParry, -1`
- removed `object_event 13, 65, SPRITE_HIKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerHikerTimothy, -1`
- removed `object_event 16, 50, SPRITE_BLACK_BELT, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 2, TrainerBlackbeltKenji, -1`
- removed `object_event 21, 18, SPRITE_ACE_TRAINER_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerCooltrainermRyan, -1`
- removed `object_event 6, 33, SPRITE_ACE_TRAINER_F, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerCooltrainerfKelly, -1`
- removed `fruittree_event 20, 80, FRUITTREE_ROUTE_45, LEPPA_BERRY, PAL_NPC_RED`
- removed `itemball_event 8, 51, NUGGET, 1, EVENT_ROUTE_45_NUGGET`
- removed `itemball_event 5, 66, REVIVE, 1, EVENT_ROUTE_45_REVIVE`
- removed `itemball_event 7, 20, ELIXIR, 1, EVENT_ROUTE_45_ELIXIR`
- removed `itemball_event 15, 32, MAX_POTION, 1, EVENT_ROUTE_45_MAX_POTION`
- removed `object_event 4, 70, SPRITE_CAMPER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerCamperQuentin, -1`
+ added `warp_event 7, 3, DARK_CAVE_BLACKTHORN_ENTRANCE, 1`
+ added `warp_event 16, 26, HIDDEN_CAVE_GROTTO, 1`
+ added `bg_event 17, 3, BGEVENT_JUMPTEXT, Route45SignText`
+ added `bg_event 6, 4, BGEVENT_JUMPTEXT, Route45DarkCaveSignText`
+ added `bg_event 17, 82, BGEVENT_ITEM + PP_UP, EVENT_ROUTE_45_HIDDEN_PP_UP`
+ added `bg_event 16, 25, BGEVENT_JUMPSTD, cavegrotto, HIDDENGROTTO_ROUTE_45`
+ added `object_event 19, 79, SPRITE_DRAGON_TAMER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 2, -1, 0, OBJECTTYPE_SCRIPT, 0, Route45Dragon_tamerScript, -1`
+ added `object_event 5, 63, SPRITE_BATTLE_GIRL, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerBattleGirlNozomi, -1`
+ added `object_event 12, 20, SPRITE_HIKER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerHikerErik, -1`
+ added `object_event 19, 69, SPRITE_HIKER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerHikerMichael, -1`
+ added `object_event 7, 32, SPRITE_HIKER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 2, TrainerHikerParry, -1`
+ added `object_event 13, 69, SPRITE_HIKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerHikerTimothy, -1`
+ added `object_event 16, 54, SPRITE_BLACK_BELT, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 2, TrainerBlackbeltKenji, -1`
+ added `object_event 21, 22, SPRITE_ACE_TRAINER_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerCooltrainermRyan, -1`
+ added `object_event 6, 37, SPRITE_ACE_TRAINER_F, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerCooltrainerfKelly, -1`
+ added `fruittree_event 20, 84, FRUITTREE_ROUTE_45, LEPPA_BERRY, PAL_NPC_RED`
+ added `itemball_event 8, 55, NUGGET, 1, EVENT_ROUTE_45_NUGGET`
+ added `itemball_event 5, 70, REVIVE, 1, EVENT_ROUTE_45_REVIVE`
+ added `itemball_event 7, 24, ELIXIR, 1, EVENT_ROUTE_45_ELIXIR`
+ added `itemball_event 15, 36, MAX_POTION, 1, EVENT_ROUTE_45_MAX_POTION`
+ added `object_event 4, 74, SPRITE_CAMPER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerCamperQuentin, -1`

## Route47

- removed `coord_event 42, 24, 1, Route47Bridge1OverheadTrigger`
- removed `coord_event 42, 25, 1, Route47Bridge1OverheadTrigger`
- removed `coord_event 51, 24, 1, Route47Bridge1OverheadTrigger`
- removed `coord_event 51, 25, 1, Route47Bridge1OverheadTrigger`
- removed `coord_event 43, 24, 0, Route47Bridge1UnderfootTrigger`
- removed `coord_event 43, 25, 0, Route47Bridge1UnderfootTrigger`
- removed `coord_event 50, 24, 0, Route47Bridge1UnderfootTrigger`
- removed `coord_event 50, 25, 0, Route47Bridge1UnderfootTrigger`
- removed `coord_event 42, 18, 1, Route47Bridge2OverheadTrigger`
- removed `coord_event 42, 19, 1, Route47Bridge2OverheadTrigger`
- removed `coord_event 51, 18, 1, Route47Bridge2OverheadTrigger`
- removed `coord_event 51, 19, 1, Route47Bridge2OverheadTrigger`
- removed `coord_event 43, 18, 0, Route47Bridge2UnderfootTrigger`
- removed `coord_event 43, 19, 0, Route47Bridge2UnderfootTrigger`
- removed `coord_event 50, 18, 0, Route47Bridge2UnderfootTrigger`
- removed `coord_event 50, 19, 0, Route47Bridge2UnderfootTrigger`
- removed `coord_event 18, 24, 1, Route47Bridge3OverheadTrigger`
- removed `coord_event 18, 25, 1, Route47Bridge3OverheadTrigger`
- removed `coord_event 27, 24, 1, Route47Bridge3OverheadTrigger`
- removed `coord_event 27, 25, 1, Route47Bridge3OverheadTrigger`
- removed `coord_event 19, 24, 0, Route47Bridge3UnderfootTrigger`
- removed `coord_event 19, 25, 0, Route47Bridge3UnderfootTrigger`
- removed `coord_event 26, 24, 0, Route47Bridge3UnderfootTrigger`
- removed `coord_event 26, 25, 0, Route47Bridge3UnderfootTrigger`
- removed `coord_event 18, 16, 1, Route47Bridge4OverheadTrigger`
- removed `coord_event 18, 17, 1, Route47Bridge4OverheadTrigger`
- removed `coord_event 27, 16, 1, Route47Bridge4OverheadTrigger`
- removed `coord_event 27, 17, 1, Route47Bridge4OverheadTrigger`
- removed `coord_event 19, 16, 0, Route47Bridge4UnderfootTrigger`
- removed `coord_event 19, 17, 0, Route47Bridge4UnderfootTrigger`
- removed `coord_event 26, 16, 0, Route47Bridge4UnderfootTrigger`
- removed `coord_event 26, 17, 0, Route47Bridge4UnderfootTrigger`
- removed `object_event 40, 24, SPRITE_CAMPER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerCamperGrant, EVENT_YELLOW_FOREST_ROCKET_TAKEOVER`
+ added `coord_event 42, 24, SCENE_ROUTE47_BRIDGE_OVERHEAD, Route47Bridge1OverheadTrigger`
+ added `coord_event 42, 25, SCENE_ROUTE47_BRIDGE_OVERHEAD, Route47Bridge1OverheadTrigger`
+ added `coord_event 51, 24, SCENE_ROUTE47_BRIDGE_OVERHEAD, Route47Bridge1OverheadTrigger`
+ added `coord_event 51, 25, SCENE_ROUTE47_BRIDGE_OVERHEAD, Route47Bridge1OverheadTrigger`
+ added `coord_event 43, 24, SCENE_ROUTE47_BRIDGE_UNDERFOOT, Route47Bridge1UnderfootTrigger`
+ added `coord_event 43, 25, SCENE_ROUTE47_BRIDGE_UNDERFOOT, Route47Bridge1UnderfootTrigger`
+ added `coord_event 50, 24, SCENE_ROUTE47_BRIDGE_UNDERFOOT, Route47Bridge1UnderfootTrigger`
+ added `coord_event 50, 25, SCENE_ROUTE47_BRIDGE_UNDERFOOT, Route47Bridge1UnderfootTrigger`
+ added `coord_event 42, 18, SCENE_ROUTE47_BRIDGE_OVERHEAD, Route47Bridge2OverheadTrigger`
+ added `coord_event 42, 19, SCENE_ROUTE47_BRIDGE_OVERHEAD, Route47Bridge2OverheadTrigger`
+ added `coord_event 51, 18, SCENE_ROUTE47_BRIDGE_OVERHEAD, Route47Bridge2OverheadTrigger`
+ added `coord_event 51, 19, SCENE_ROUTE47_BRIDGE_OVERHEAD, Route47Bridge2OverheadTrigger`
+ added `coord_event 43, 18, SCENE_ROUTE47_BRIDGE_UNDERFOOT, Route47Bridge2UnderfootTrigger`
+ added `coord_event 43, 19, SCENE_ROUTE47_BRIDGE_UNDERFOOT, Route47Bridge2UnderfootTrigger`
+ added `coord_event 50, 18, SCENE_ROUTE47_BRIDGE_UNDERFOOT, Route47Bridge2UnderfootTrigger`
+ added `coord_event 50, 19, SCENE_ROUTE47_BRIDGE_UNDERFOOT, Route47Bridge2UnderfootTrigger`
+ added `coord_event 18, 24, SCENE_ROUTE47_BRIDGE_OVERHEAD, Route47Bridge3OverheadTrigger`
+ added `coord_event 18, 25, SCENE_ROUTE47_BRIDGE_OVERHEAD, Route47Bridge3OverheadTrigger`
+ added `coord_event 27, 24, SCENE_ROUTE47_BRIDGE_OVERHEAD, Route47Bridge3OverheadTrigger`
+ added `coord_event 27, 25, SCENE_ROUTE47_BRIDGE_OVERHEAD, Route47Bridge3OverheadTrigger`
+ added `coord_event 19, 24, SCENE_ROUTE47_BRIDGE_UNDERFOOT, Route47Bridge3UnderfootTrigger`
+ added `coord_event 19, 25, SCENE_ROUTE47_BRIDGE_UNDERFOOT, Route47Bridge3UnderfootTrigger`
+ added `coord_event 26, 24, SCENE_ROUTE47_BRIDGE_UNDERFOOT, Route47Bridge3UnderfootTrigger`
+ added `coord_event 26, 25, SCENE_ROUTE47_BRIDGE_UNDERFOOT, Route47Bridge3UnderfootTrigger`
+ added `coord_event 18, 16, SCENE_ROUTE47_BRIDGE_OVERHEAD, Route47Bridge4OverheadTrigger`
+ added `coord_event 18, 17, SCENE_ROUTE47_BRIDGE_OVERHEAD, Route47Bridge4OverheadTrigger`
+ added `coord_event 27, 16, SCENE_ROUTE47_BRIDGE_OVERHEAD, Route47Bridge4OverheadTrigger`
+ added `coord_event 27, 17, SCENE_ROUTE47_BRIDGE_OVERHEAD, Route47Bridge4OverheadTrigger`
+ added `coord_event 19, 16, SCENE_ROUTE47_BRIDGE_UNDERFOOT, Route47Bridge4UnderfootTrigger`
+ added `coord_event 19, 17, SCENE_ROUTE47_BRIDGE_UNDERFOOT, Route47Bridge4UnderfootTrigger`
+ added `coord_event 26, 16, SCENE_ROUTE47_BRIDGE_UNDERFOOT, Route47Bridge4UnderfootTrigger`
+ added `coord_event 26, 17, SCENE_ROUTE47_BRIDGE_UNDERFOOT, Route47Bridge4UnderfootTrigger`
+ added `object_event 40, 24, SPRITE_CAMPER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_DARK_GREEN, OBJECTTYPE_TRAINER, 2, TrainerCamperGrant, EVENT_YELLOW_FOREST_ROCKET_TAKEOVER`

## Route48

- removed `coord_event 20, 12, 0, Route48JessieJamesScript1`
- removed `coord_event 20, 13, 0, Route48JessieJamesScript2`
+ added `coord_event 20, 12, SCENE_ROUTE48_JESSIE_AND_JAMES, Route48JessieJamesScript1`
+ added `coord_event 20, 13, SCENE_ROUTE48_JESSIE_AND_JAMES, Route48JessieJamesScript2`

## Route5

- removed `warp_event 17, 27, ROUTE_5_UNDERGROUND_ENTRANCE, 1`
- removed `bg_event 17, 29, BGEVENT_JUMPTEXT, Route5UndergroundPathSignText`
+ added `warp_event 17, 27, ROUTE_5_UNDERGROUND_PATH_ENTRANCE, 1`
+ added `bg_event 18, 28, BGEVENT_JUMPTEXT, Route5UndergroundPathSignText`

## Route5UndergroundEntrance -> Route5UndergroundPathEntrance

- removed `warp_event 4, 4, UNDERGROUND, 1`
- removed `object_event 2, 3, SPRITE_TEACHER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 1, 1, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route5UndergroundPathEntranceTeacherText, -1`
+ added `warp_event 3, 4, UNDERGROUND_PATH, 1`
+ added `object_event 5, 3, SPRITE_TEACHER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 1, 1, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route5UndergroundPathEntranceTeacherText, -1`

## Route6

- removed `warp_event 21, 9, ROUTE_6_UNDERGROUND_ENTRANCE, 1`
- removed `warp_event 10, 1, ROUTE_6_SAFFRON_GATE, 3`
- removed `bg_event 23, 11, BGEVENT_JUMPTEXT, Route6UndergroundPathSignText`
- removed `bg_event 7, 9, BGEVENT_JUMPTEXT, Route6AdvancedTipsSignText`
- removed `object_event 21, 10, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route6PokefanMText, EVENT_ROUTE_5_6_POKEFAN_M_BLOCKS_UNDERGROUND_PATH`
- removed `object_event 13, 24, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 0, GenericTrainerPokefanmRex, -1`
- removed `object_event 14, 24, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 0, GenericTrainerPokefanmAllan, -1`
- removed `object_event 16, 17, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerTwinsDayanddani1, -1`
- removed `object_event 17, 17, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerTwinsDayanddani2, -1`
- removed `object_event 20, 27, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerYoungsterChaz, -1`
- removed `object_event 12, 13, SPRITE_BATTLE_GIRL, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerGuitaristfWanda, -1`
- removed `object_event 21, 19, SPRITE_OFFICER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 1, OfficerfJennyScript, -1`
- removed `fruittree_event 17, 5, FRUITTREE_ROUTE_6, STARF_BERRY, PAL_NPC_GREEN`
+ added `warp_event 21, 11, ROUTE_6_UNDERGROUND_PATH_ENTRANCE, 1`
+ added `warp_event 12, 1, ROUTE_6_SAFFRON_GATE, 3`
+ added `bg_event 23, 12, BGEVENT_JUMPTEXT, Route6UndergroundPathSignText`
+ added `bg_event 7, 11, BGEVENT_JUMPTEXT, Route6AdvancedTipsSignText`
+ added `object_event 21, 12, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route6PokefanMText, EVENT_ROUTE_5_6_POKEFAN_M_BLOCKS_UNDERGROUND_PATH`
+ added `object_event 10, 26, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 0, GenericTrainerPokefanmRex, -1`
+ added `object_event 11, 26, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 0, GenericTrainerPokefanmAllan, -1`
+ added `object_event 14, 19, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerTwinsDayanddani1, -1`
+ added `object_event 15, 19, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerTwinsDayanddani2, -1`
+ added `object_event 22, 24, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerYoungsterChaz, -1`
+ added `object_event 6, 15, SPRITE_BATTLE_GIRL, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerGuitaristfWanda, -1`
+ added `object_event 9, 7, SPRITE_OFFICER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 1, OfficerfJennyScript, -1`
+ added `fruittree_event 17, 3, FRUITTREE_ROUTE_6, STARF_BERRY, PAL_NPC_GREEN`

## Route6UndergroundEntrance -> Route6UndergroundPathEntrance

- removed `warp_event 4, 4, UNDERGROUND, 2`
+ added `warp_event 3, 4, UNDERGROUND_PATH, 2`

## Route7

- removed `bg_event 5, 13, BGEVENT_JUMPTEXT, Route7UndergroundPathSignText`
+ added `bg_event 4, 12, BGEVENT_JUMPTEXT, Route7UndergroundPathSignText`

## Route8

- removed `bg_event 11, 9, BGEVENT_JUMPTEXT, Route8UndergroundPathSignText`
- removed `object_event 10, 10, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_GENERICTRAINER, 5, GenericTrainerBikerDwayne, EVENT_ROUTE_8_KANTO_POKEMON_FEDERATION`
- removed `object_event 10, 11, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_GENERICTRAINER, 5, GenericTrainerBikerHarris, EVENT_ROUTE_8_KANTO_POKEMON_FEDERATION`
- removed `object_event 10, 12, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_GENERICTRAINER, 5, GenericTrainerBikerZeke, EVENT_ROUTE_8_KANTO_POKEMON_FEDERATION`
- removed `object_event 17, 9, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerSupernerdSam, -1`
- removed `object_event 32, 9, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerSupernerdTom, -1`
- removed `object_event 29, 4, SPRITE_LASS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerLassMeadow, -1`
- removed `cuttree_event 21, 14, EVENT_ROUTE_8_CUT_TREE_1`
- removed `cuttree_event 32, 12, EVENT_ROUTE_8_CUT_TREE_2`
- removed `object_event 6, 9, SPRITE_BIKER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route8BikerDwayneProtestText, EVENT_ROUTE_8_PROTESTORS`
- removed `object_event 7, 10, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route8BikerHarrisProtestText, EVENT_ROUTE_8_PROTESTORS`
- removed `object_event 6, 11, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route8BikerZekeProtestText, EVENT_ROUTE_8_PROTESTORS`
+ added `bg_event 8, 8, BGEVENT_JUMPTEXT, Route8UndergroundPathSignText`
+ added `object_event 12, 10, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 5, TrainerBikerDwayne, EVENT_ROUTE_8_KANTO_POKEMON_FEDERATION`
+ added `object_event 12, 11, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 5, TrainerBikerHarris, EVENT_ROUTE_8_KANTO_POKEMON_FEDERATION`
+ added `object_event 12, 12, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_DARK_BLUE, OBJECTTYPE_TRAINER, 5, TrainerBikerZeke, EVENT_ROUTE_8_KANTO_POKEMON_FEDERATION`
+ added `object_event 19, 9, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerSupernerdSam, -1`
+ added `object_event 34, 9, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerSupernerdTom, -1`
+ added `object_event 31, 4, SPRITE_LASS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerLassMeadow, -1`
+ added `cuttree_event 23, 14, EVENT_ROUTE_8_CUT_TREE_1`
+ added `cuttree_event 34, 12, EVENT_ROUTE_8_CUT_TREE_2`
+ added `object_event 8, 9, SPRITE_BIKER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route8BikerDwayneProtestText, EVENT_ROUTE_8_PROTESTORS`
+ added `object_event 9, 10, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route8BikerHarrisProtestText, EVENT_ROUTE_8_PROTESTORS`
+ added `object_event 8, 11, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_DARK_BLUE, OBJECTTYPE_COMMAND, jumptextfaceplayer, Route8BikerZekeProtestText, EVENT_ROUTE_8_PROTESTORS`

## RuggedRoadNorth

- removed `bg_event 23, 9, BGEVENT_ITEM + RARE_BONE, EVENT_RUGGED_ROAD_NORTH_HIDDEN_RARE_BONE`
+ added `bg_event 25, 8, BGEVENT_ITEM + RARE_BONE, EVENT_RUGGED_ROAD_NORTH_HIDDEN_RARE_BONE`
+ added `object_event 6, 11, SPRITE_BATTLE_GIRL, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerBattleGirlMei, -1`
+ added `object_event 23, 9, SPRITE_HIKER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, (1 << DAY) | (1 << NITE), 0, OBJECTTYPE_SCRIPT, 0, RuggedRoadNorthHikerScript, -1`
+ added `object_event 22, 10, SPRITE_HIKER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, (1 << MORN) | (1 << EVE), 0, OBJECTTYPE_SCRIPT, 0, RuggedRoadNorthHikerScript, -1`
+ added `object_event 25, 10, SPRITE_FIREBREATHER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 1, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, RuggedRoadNorthFirebreatherText, -1`
+ added `object_event 23, 10, SPRITE_CAMPFIRE, SPRITEMOVEDATA_POKEMON, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, RuggedRoadNorthCampfireText, -1`

## RuggedRoadSouth

- removed `coord_event 27, 3, 1, RuggedRoadSouthBridgeOverheadTrigger`
- removed `coord_event 27, 1, 0, RuggedRoadSouthBridgeUnderfootTrigger`
- removed `coord_event 25, 23, 1, RuggedRoadSouthBridgeOverheadTrigger`
+ added `coord_event 27, 3, SCENE_RUGGEDROADSOUTH_BRIDGE_OVERHEAD, RuggedRoadSouthBridgeOverheadTrigger`
+ added `coord_event 27, 1, SCENE_RUGGEDROADSOUTH_BRIDGE_UNDERFOOT, RuggedRoadSouthBridgeUnderfootTrigger`
+ added `coord_event 25, 23, SCENE_RUGGEDROADSOUTH_BRIDGE_OVERHEAD, RuggedRoadSouthBridgeOverheadTrigger`
+ added `object_event 7, 7, SPRITE_BIRD_KEEPER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_DARK_BLUE, OBJECTTYPE_TRAINER, 4, TrainerBird_keeperSalim, -1`
+ added `object_event 24, 8, SPRITE_HIKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerHikerMaynard, -1`
+ added `object_event 12, 18, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerFisherCarlos, -1`
+ added `object_event 22, 24, SPRITE_HIKER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 4, GenericTrainerHikerElijah, -1`
+ added `object_event 13, 12, SPRITE_BLACK_BELT, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 2, -1, 0, OBJECTTYPE_SCRIPT, 0, RuggedRoadSouthBlackBeltScript, -1`
+ added `object_event 11, 24, SPRITE_CAMPER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 2, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, RuggedRoadSouthCamperText, -1`

## RuinsOfAlphEntranceChamber

- removed `warp_event 4, 7, RUINS_OF_ALPH_OUTSIDE, 5`
+ added `warp_event 4, 7, RUINS_OF_ALPH_OUTSIDE, 6`

## RuinsOfAlphOutside

- removed `warp_event 4, 23, RUINS_OF_ALPH_HO_OH_CHAMBER, 1`
- removed `warp_event 16, 13, RUINS_OF_ALPH_KABUTO_CHAMBER, 1`
- removed `warp_event 4, 35, RUINS_OF_ALPH_OMANYTE_CHAMBER, 1`
- removed `warp_event 18, 39, RUINS_OF_ALPH_AERODACTYL_CHAMBER, 1`
- removed `warp_event 12, 19, RUINS_OF_ALPH_ENTRANCE_CHAMBER, 1`
- removed `warp_event 8, 25, UNION_CAVE_B1F_NORTH, 1`
- removed `warp_event 8, 33, UNION_CAVE_B1F_NORTH, 2`
- removed `warp_event 3, 5, ROUTE_36_RUINS_OF_ALPH_GATE, 3`
- removed `warp_event 15, 26, ROUTE_32_RUINS_OF_ALPH_GATE, 1`
- removed `warp_event 15, 27, ROUTE_32_RUINS_OF_ALPH_GATE, 2`
- removed `warp_event 10, 9, RUINS_OF_ALPH_SINJOH_CHAMBER, 1`
- removed `warp_event 11, 36, HIDDEN_CAVE_GROTTO, 1`
- removed `coord_event 13, 20, 1, RuinsOfAlphOutsideScientistScene1`
- removed `coord_event 12, 21, 1, RuinsOfAlphOutsideScientistScene1`
- removed `bg_event 18, 14, BGEVENT_JUMPTEXT, RuinsOfAlphOutsideMysteryChamberSignText`
- removed `bg_event 14, 22, BGEVENT_JUMPTEXT, RuinsOfAlphSignText`
- removed `bg_event 20, 18, BGEVENT_JUMPTEXT, RuinsOfAlphResearchCenterSignText`
- removed `bg_event 3, 9, BGEVENT_JUMPTEXT, RuinsOfAlphAdvancedTipsSignText`
- removed `bg_event 10, 9, BGEVENT_IFNOTSET, MapRuinsofAlphOutsideSealedCaveSign`
- removed `bg_event 4, 13, BGEVENT_ITEM + RARE_CANDY, EVENT_RUINS_OF_ALPH_OUTSIDE_HIDDEN_RARE_CANDY`
- removed `bg_event 11, 35, BGEVENT_JUMPSTD, cavegrotto, HIDDENGROTTO_RUINS_OF_ALPH`
- removed `object_event 13, 21, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, RuinsOfAlphOutsideScientistScript, EVENT_RUINS_OF_ALPH_OUTSIDE_SCIENTIST`
- removed `object_event 18, 18, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_RUINS_OF_ALPH_OUTSIDE_SCIENTIST_CLIMAX`
- removed `object_event 6, 26, SPRITE_PSYCHIC, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerPsychicNathan, -1`
- removed `object_event 5, 37, SPRITE_SUPER_NERD, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerSuperNerdStan, -1`
- removed `object_event 15, 23, SPRITE_FISHER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, RuinsOfAlphOutsideFisherScript, EVENT_RUINS_OF_ALPH_OUTSIDE_TOURIST_FISHER`
- removed `object_event 14, 14, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, RuinsOfAlphOutsideYoungster2Script, EVENT_RUINS_OF_ALPH_OUTSIDE_TOURIST_YOUNGSTERS`
- removed `object_event 16, 17, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_WANDER, 1, 1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, RuinsOfAlphOutsideYoungster1Script, EVENT_RUINS_OF_ALPH_OUTSIDE_TOURIST_YOUNGSTERS`
- removed `smashrock_event 7, 10, `
- removed `smashrock_event 8, 10, `
- removed `smashrock_event 4, 12, `
- removed `smashrock_event 5, 13, `
- removed `smashrock_event 7, 13, `
- removed `smashrock_event 8, 15, `
+ added `warp_event 7, 17, RUINS_OF_ALPH_HO_OH_CHAMBER, 1`
+ added `warp_event 15, 5, RUINS_OF_ALPH_KABUTO_CHAMBER, 1`
+ added `warp_event 7, 29, RUINS_OF_ALPH_OMANYTE_CHAMBER, 1`
+ added `warp_event 15, 31, RUINS_OF_ALPH_AERODACTYL_CHAMBER, 1`
+ added `warp_event 11, 18, RUINS_OF_ALPH_ENTRANCE_CHAMBER, 1`
+ added `warp_event 12, 18, RUINS_OF_ALPH_ENTRANCE_CHAMBER, 2`
+ added `warp_event 2, 17, UNION_CAVE_B1F_NORTH, 1`
+ added `warp_event 2, 29, UNION_CAVE_B1F_NORTH, 2`
+ added `warp_event 11, 1, ROUTE_36_RUINS_OF_ALPH_GATE, 3`
+ added `warp_event 23, 22, ROUTE_32_RUINS_OF_ALPH_GATE, 1`
+ added `warp_event 23, 23, ROUTE_32_RUINS_OF_ALPH_GATE, 2`
+ added `warp_event 7, 11, RUINS_OF_ALPH_SINJOH_CHAMBER, 1`
+ added `warp_event 23, 36, HIDDEN_CAVE_GROTTO, 1`
+ added `coord_event 11, 20, SCENE_RUINSOFALPHOUTSIDE_GET_UNOWN_DEX, RuinsOfAlphOutsideScientistScene`
+ added `bg_event 16, 12, BGEVENT_JUMPTEXT, RuinsOfAlphOutsideMysteryChamberSignText`
+ added `bg_event 10, 19, BGEVENT_JUMPTEXT, RuinsOfAlphOutsideMysteriousHallSignText`
+ added `bg_event 9, 5, BGEVENT_JUMPTEXT, RuinsOfAlphSignText`
+ added `bg_event 21, 21, BGEVENT_JUMPTEXT, RuinsOfAlphSignText`
+ added `bg_event 18, 18, BGEVENT_JUMPTEXT, RuinsOfAlphResearchCenterSignText`
+ added `bg_event 21, 11, BGEVENT_JUMPTEXT, RuinsOfAlphAdvancedTipsSignText`
+ added `bg_event 7, 11, BGEVENT_IFNOTSET, MapRuinsofAlphOutsideSealedCaveSign`
+ added `bg_event 4, 3, BGEVENT_ITEM + RARE_CANDY, EVENT_RUINS_OF_ALPH_OUTSIDE_HIDDEN_RARE_CANDY`
+ added `bg_event 5, 34, BGEVENT_ITEM + NUGGET, EVENT_RUINS_OF_ALPH_OUTSIDE_HIDDEN_NUGGET`
+ added `bg_event 15, 23, BGEVENT_ITEM + BIG_MUSHROOM, EVENT_RUINS_OF_ALPH_OUTSIDE_HIDDEN_BIG_MUSHROOM`
+ added `bg_event 23, 35, BGEVENT_JUMPSTD, cavegrotto, HIDDENGROTTO_RUINS_OF_ALPH`
+ added `object_event 12, 20, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, RuinsOfAlphOutsideScientistScript, EVENT_RUINS_OF_ALPH_OUTSIDE_SCIENTIST`
+ added `object_event 19, 19, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_RUINS_OF_ALPH_OUTSIDE_SCIENTIST_CLIMAX`
+ added `object_event 5, 18, SPRITE_PSYCHIC, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerPsychicNathan, -1`
+ added `object_event 5, 33, SPRITE_SUPER_NERD, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerSuperNerdStan, -1`
+ added `object_event 10, 23, SPRITE_FISHER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, RuinsOfAlphOutsideFisherScript, EVENT_RUINS_OF_ALPH_OUTSIDE_TOURIST_FISHER`
+ added `object_event 13, 10, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, RuinsOfAlphOutsideYoungster2Script, EVENT_RUINS_OF_ALPH_OUTSIDE_TOURIST_YOUNGSTERS`
+ added `object_event 15, 21, SPRITE_SCHOOLBOY, SPRITEMOVEDATA_WANDER, 1, 1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, RuinsOfAlphOutsideYoungster1Script, EVENT_RUINS_OF_ALPH_OUTSIDE_TOURIST_YOUNGSTERS`
+ added `itemball_event 2, 9, HYPER_POTION, 1, EVENT_RUINS_OF_ALPH_OUTSIDE_HYPER_POTION`
+ added `smashrock_event 0, 4, `
+ added `smashrock_event 0, 9, `
+ added `smashrock_event 1, 8, `
+ added `smashrock_event 5, 3, `
+ added `smashrock_event 6, 2, `
+ added `smashrock_event 8, 3, `

## RuinsOfAlphResearchCenter

- removed `warp_event 2, 7, RUINS_OF_ALPH_OUTSIDE, 6`
- removed `warp_event 3, 7, RUINS_OF_ALPH_OUTSIDE, 6`
- removed `bg_event 6, 5, BGEVENT_JUMPTEXT, RuinsOfAlphResearchCenterAcademicBooksText`
- removed `bg_event 3, 4, BGEVENT_READ, MapRuinsofAlphResearchCenterSignpost1Script`
- removed `bg_event 7, 1, BGEVENT_JUMPTEXT, RuinsOfAlphResearchCenterPrinterText_DoesntWork`
- removed `bg_event 5, 0, BGEVENT_JUMPTEXT, RuinsOfAlphResearchCenterProfSilktreePhotoText`
- removed `object_event 4, 5, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, RuinsOfAlphResearchCenterScientist1Script, -1`
- removed `object_event 5, 2, SPRITE_SCIENTIST, SPRITEMOVEDATA_WANDER, 1, 2, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, RuinsOfAlphResearchCenterScientist2Script, -1`
- removed `object_event 2, 5, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, RuinsOfAlphResearchCenterScientist3Script, EVENT_RUINS_OF_ALPH_RESEARCH_CENTER_SCIENTIST`
+ added `warp_event 4, 7, RUINS_OF_ALPH_OUTSIDE, 7`
+ added `warp_event 5, 7, RUINS_OF_ALPH_OUTSIDE, 7`
+ added `bg_event 8, 5, BGEVENT_JUMPTEXT, RuinsOfAlphResearchCenterAcademicBooksText`
+ added `bg_event 5, 4, BGEVENT_READ, MapRuinsofAlphResearchCenterSignpost1Script`
+ added `bg_event 9, 1, BGEVENT_JUMPTEXT, RuinsOfAlphResearchCenterPrinterText_DoesntWork`
+ added `bg_event 7, 0, BGEVENT_JUMPTEXT, RuinsOfAlphResearchCenterProfSilktreePhotoText`
+ added `bg_event 1, 3, BGEVENT_JUMPTEXT, RuinsOfAlphResearchCenterFossilComputerText`
+ added `object_event 6, 5, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, RuinsOfAlphResearchCenterScientist1Script, -1`
+ added `object_event 7, 2, SPRITE_SCIENTIST, SPRITEMOVEDATA_WANDER, 1, 2, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, RuinsOfAlphResearchCenterScientist2Script, -1`
+ added `object_event 4, 5, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, RuinsOfAlphResearchCenterScientist3Script, EVENT_RUINS_OF_ALPH_RESEARCH_CENTER_SCIENTIST`
+ added `object_event 0, 4, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, RuinsOfAlphResearchCenterScientist4Script, -1`

## RuinsOfAlphSinjohChamber

- removed `warp_event 5, 9, RUINS_OF_ALPH_OUTSIDE, 12`
- removed `warp_event 4, 9, RUINS_OF_ALPH_OUTSIDE, 12`
+ added `warp_event 5, 9, RUINS_OF_ALPH_OUTSIDE, 13`

## SafariZoneWardensHome

- removed `warp_event 2, 7, FUCHSIA_CITY, 5`
- removed `warp_event 3, 7, FUCHSIA_CITY, 5`
- removed `bg_event 7, 0, BGEVENT_JUMPTEXT, WardenPhotoText`
- removed `bg_event 9, 0, BGEVENT_JUMPTEXT, SafariZonePhotoText`
+ added `warp_event 4, 7, FUCHSIA_CITY, 5`
+ added `warp_event 5, 7, FUCHSIA_CITY, 5`
+ added `bg_event 5, 0, BGEVENT_JUMPTEXT, WardenPhotoText`
+ added `bg_event 7, 0, BGEVENT_JUMPTEXT, SafariZonePhotoText`
+ added `bg_event 8, 1, BGEVENT_JUMPTEXT, WardensHouseCuriosText`
+ added `bg_event 9, 1, BGEVENT_JUMPTEXT, WardensHouseCuriosText`

## SaffronCity

- removed `warp_event 34, 3, SAFFRON_GYM, 1`
- removed `warp_event 25, 11, SAFFRON_MART, 2`
- removed `warp_event 27, 29, MR_PSYCHICS_HOUSE, 1`
- removed `warp_event 8, 3, SAFFRON_TRAIN_STATION, 2`
- removed `warp_event 18, 21, SILPH_CO_1F, 1`
- removed `warp_event 32, 11, POKEMON_TRAINER_FAN_CLUB, 1`
- removed `warp_event 21, 29, SAFFRON_HITMONTOP_KID_HOUSE, 1`
- removed `bg_event 21, 5, BGEVENT_JUMPTEXT, SaffronCitySignText`
- removed `bg_event 33, 5, BGEVENT_JUMPTEXT, SaffronGymSignText`
- removed `bg_event 25, 5, BGEVENT_JUMPTEXT, FightingDojoSignText`
- removed `bg_event 25, 29, BGEVENT_JUMPTEXT, MrPsychicsHouseSignText`
- removed `bg_event 11, 5, BGEVENT_JUMPTEXT, SaffronCityMagnetTrainStationSignText`
- removed `bg_event 35, 11, BGEVENT_JUMPTEXT, PokemonTrainerFanClubSignText`
- removed `bg_event 35, 21, BGEVENT_JUMPTEXT, SaffronTrainerTips2Text`
- removed `object_event 20, 24, SPRITE_ACE_TRAINER_F, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 2, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, SaffronCityCooltrainerFText, -1`
- removed `object_event 35, 23, SPRITE_BIRD_KEEPER, SPRITEMOVEDATA_WANDER, 1, 1, -1, PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, SaffronCityYoungster2Text, -1`
- removed `object_event 22, 8, SPRITE_PSYCHIC, SPRITEMOVEDATA_SPINRANDOM_SLOW, 4, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, SaffronCitySuperNerdText, -1`
- removed `object_event 23, 22, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_DOWN, 4, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, SaffronCityScientistText, -1`
+ added `warp_event 32, 3, SAFFRON_GYM, 1`
+ added `warp_event 27, 11, SAFFRON_MART, 2`
+ added `warp_event 29, 29, MR_PSYCHICS_HOUSE, 1`
+ added `warp_event 6, 3, SAFFRON_TRAIN_STATION, 2`
+ added `warp_event 19, 21, SILPH_CO_1F, 1`
+ added `warp_event 34, 11, POKEMON_TRAINER_FAN_CLUB, 1`
+ added `warp_event 23, 29, SAFFRON_HITMONTOP_KID_HOUSE, 1`
+ added `warp_event 20, 21, SILPH_CO_1F, 2`
+ added `bg_event 20, 5, BGEVENT_JUMPTEXT, SaffronCitySignText`
+ added `bg_event 33, 3, BGEVENT_JUMPTEXT, SaffronGymSignText`
+ added `bg_event 27, 3, BGEVENT_JUMPTEXT, FightingDojoSignText`
+ added `bg_event 27, 29, BGEVENT_JUMPTEXT, MrPsychicsHouseSignText`
+ added `bg_event 8, 5, BGEVENT_JUMPTEXT, SaffronCityMagnetTrainStationSignText`
+ added `bg_event 31, 11, BGEVENT_JUMPTEXT, PokemonTrainerFanClubSignText`
+ added `bg_event 35, 25, BGEVENT_JUMPTEXT, SaffronTrainerTips2Text`
+ added `object_event 19, 25, SPRITE_ACE_TRAINER_F, SPRITEMOVEDATA_WANDER, 1, 2, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, SaffronCityCooltrainerFText, -1`
+ added `object_event 32, 23, SPRITE_BIRD_KEEPER, SPRITEMOVEDATA_WANDER, 1, 1, -1, PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, SaffronCityYoungster2Text, -1`
+ added `object_event 22, 8, SPRITE_PSYCHIC, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 4, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, SaffronCitySuperNerdText, -1`
+ added `object_event 22, 22, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_DOWN, 4, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, SaffronCityScientistText, -1`

## SaffronTrainStation

- removed `coord_event 11, 6, 0, Script_ArriveFromGoldenrod`
+ added `coord_event 11, 6, SCENE_SAFFRONTRAINSTATION_ARRIVE_FROM_GOLDENROD, Script_ArriveFromGoldenrod`

## ScaryCave1F

- removed `object_event 22, 20, SPRITE_COOL_DUDE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerCoupleJoeandjo1, -1`
- removed `object_event 23, 20, SPRITE_CUTE_GIRL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerCoupleJoeandjo2, -1`
+ added `object_event 22, 20, SPRITE_COOL_DUDE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_DARK_RED, OBJECTTYPE_TRAINER, 1, TrainerCoupleJoeandjo1, -1`
+ added `object_event 23, 20, SPRITE_CUTE_GIRL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_DARK_RED, OBJECTTYPE_TRAINER, 1, TrainerCoupleJoeandjo2, -1`

## ScaryCaveShipwreck

+ added `bg_event 2, 4, BGEVENT_JUMPTEXT, ScaryCaveShipwreckText`
+ added `bg_event 3, 4, BGEVENT_JUMPTEXT, ScaryCaveShipwreckText`
+ added `bg_event 4, 4, BGEVENT_JUMPTEXT, ScaryCaveShipwreckText`
+ added `bg_event 5, 4, BGEVENT_JUMPTEXT, ScaryCaveShipwreckText`
+ added `bg_event 6, 4, BGEVENT_JUMPTEXT, ScaryCaveShipwreckText`
+ added `bg_event 7, 4, BGEVENT_JUMPTEXT, ScaryCaveShipwreckText`
+ added `bg_event 8, 4, BGEVENT_JUMPTEXT, ScaryCaveShipwreckText`
+ added `bg_event 9, 4, BGEVENT_JUMPTEXT, ScaryCaveShipwreckText`

## SeafoamGym

- removed `object_event 12, 7, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerScientistLinden, -1`
+ added `object_event 12, 7, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_DARK_BLUE, OBJECTTYPE_TRAINER, 1, TrainerScientistLinden, -1`

## SeafoamIslands1F

- removed `warp_event 15, 33, ROUTE_20, 1`
- removed `warp_event 15, 31, SEAFOAM_GYM, 1`
- removed `warp_event 12, 28, SEAFOAM_ISLANDS_B1F, 1`
- removed `bg_event 17, 29, BGEVENT_ITEM + ESCAPE_ROPE, EVENT_SEAFOAM_ISLANDS_1F_HIDDEN_ESCAPE_ROPE`
+ added `warp_event 5, 17, ROUTE_20, 1`
+ added `warp_event 5, 15, SEAFOAM_GYM, 1`
+ added `warp_event 2, 12, SEAFOAM_ISLANDS_B1F, 1`
+ added `bg_event 7, 13, BGEVENT_ITEM + ESCAPE_ROPE, EVENT_SEAFOAM_ISLANDS_1F_HIDDEN_ESCAPE_ROPE`

## SeafoamIslandsB4F

- removed `object_event 22, 13, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, ARTICUNO, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, PLAIN_FORM, SeafoamIslandsArticuno, EVENT_SEAFOAM_ISLANDS_ARTICUNO`
+ added `object_event 22, 13, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, ARTICUNO, -1, PAL_MON_BLUE, OBJECTTYPE_SCRIPT, PLAIN_FORM, SeafoamIslandsArticuno, EVENT_SEAFOAM_ISLANDS_ARTICUNO`

## ShamoutiCoast

- removed `object_event 12, 5, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_SPINCOUNTERCLOCKWISE, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerSwimmerfMarina, -1`
- removed `object_event 71, 16, SPRITE_SWIMMER_GUY, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerSwimmermAshe, -1`
+ added `object_event 12, 5, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_SPINCOUNTERCLOCKWISE, 0, 0, -1, PAL_NPC_DARK_GREEN, OBJECTTYPE_TRAINER, 3, TrainerSwimmerfMarina, -1`
+ added `object_event 71, 16, SPRITE_SWIMMER_GUY, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, PAL_NPC_DARK_RED, OBJECTTYPE_TRAINER, 3, TrainerSwimmermAshe, -1`

## ShamoutiHotelRestaurant

- removed `coord_event 16, 6, 1, ShamoutiHotelRestaurantLeavingTrigger1`
- removed `coord_event 16, 7, 1, ShamoutiHotelRestaurantLeavingTrigger2`
+ added `coord_event 16, 6, SCENE_SHAMOUTIHOTELRESTAURANT_NOOP, ShamoutiHotelRestaurantLeavingTrigger1`
+ added `coord_event 16, 7, SCENE_SHAMOUTIHOTELRESTAURANT_NOOP, ShamoutiHotelRestaurantLeavingTrigger2`

## ShamoutiIsland

- removed `object_event 16, 7, SPRITE_RATTATA_BACK, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_SHAMOUTI_ISLAND_ALOLAN_EXEGGUTOR`
- removed `object_event 24, 14, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ShamoutiIslandYoungsterScript, EVENT_SHAMOUTI_ISLAND_PIKABLU_GUY`
- removed `pokemon_event 25, 14, MARILL, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BLUE, ShamoutiIslandPikabluText, EVENT_SHAMOUTI_ISLAND_PIKABLU_GUY`
+ added `object_event 16, 7, SPRITE_BLANK_FRUIT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_SHAMOUTI_ISLAND_ALOLAN_EXEGGUTOR`
+ added `object_event 24, 14, SPRITE_AROMA_LADY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, ShamoutiIslandWilhomenaScript, EVENT_SHAMOUTI_ISLAND_WILHOMENA`
+ added `pokemon_event 25, 14, MARILL, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BLUE, ShamoutiIslandPikabluText, EVENT_SHAMOUTI_ISLAND_WILHOMENA`

## ShamoutiTouristCenter

+ added `object_event 2, 4, SPRITE_LARRY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, LarryScript, -1`

## SilphCo1F

- removed `warp_event 2, 7, SAFFRON_CITY, 7`
- removed `warp_event 3, 7, SAFFRON_CITY, 7`
- removed `object_event 11, 4, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_COMMAND, jumptextfaceplayer, SilphCo1FGentlemanText, -1`
- removed `object_event 8, 2, SPRITE_BATTLE_GIRL, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, SilphCo1FCooltrainerfText, -1`
+ added `warp_event 2, 9, SAFFRON_CITY, 7`
+ added `warp_event 3, 9, SAFFRON_CITY, 21`
+ added `bg_event 8, 0, BGEVENT_JUMPTEXT, SilphCoElevatorText`
+ added `object_event 11, 3, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_COMMAND, jumptextfaceplayer, SilphCo1FGentlemanText, -1`
+ added `object_event 8, 4, SPRITE_BATTLE_GIRL, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 1, -1, PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, SilphCo1FCooltrainerfText, -1`

## SilphCo2F

- removed `bg_event 3, 2, BGEVENT_JUMPTEXT, SilphCo2FDeptSignText`
- removed `bg_event 9, 2, BGEVENT_JUMPTEXT, SilphCo2FDeptSignText`
- removed `bg_event 5, 0, BGEVENT_JUMPTEXT, SilphCo2FElevatorText`
- removed `bg_event 0, 3, BGEVENT_JUMPSTD, difficultbookshelf`
- removed `bg_event 6, 3, BGEVENT_JUMPSTD, difficultbookshelf`
- removed `bg_event 7, 3, BGEVENT_JUMPSTD, difficultbookshelf`
- removed `bg_event 12, 3, BGEVENT_JUMPSTD, difficultbookshelf`
- removed `bg_event 13, 3, BGEVENT_JUMPSTD, difficultbookshelf`
- removed `object_event 4, 5, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, SilphCo2FScientist1Script, -1`
- removed `object_event 14, 4, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, SilphCo2FScientist2Text, -1`
- removed `object_event 8, 5, SPRITE_SILPH_EMPLOYEE, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, SilphCo2FSilphEmployee1Text, -1`
- removed `object_event 2, 5, SPRITE_SILPH_EMPLOYEE, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, SilphCo2FSilphEmployee2Text, -1`
+ added `bg_event 8, 0, BGEVENT_JUMPTEXT, SilphCoElevatorText`
+ added `bg_event 2, 3, BGEVENT_JUMPTEXT, SilphCo2FDeptSignText`
+ added `bg_event 9, 3, BGEVENT_JUMPTEXT, SilphCo2FDeptSignText`
+ added `bg_event 1, 1, BGEVENT_JUMPTEXT, SilphCo2FPrinterText`
+ added `bg_event 14, 5, BGEVENT_JUMPSTD, difficultbookshelf`
+ added `bg_event 15, 5, BGEVENT_JUMPSTD, difficultbookshelf`
+ added `object_event 6, 5, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, SilphCo2FScientist1Text, -1`
+ added `object_event 12, 5, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, SilphCo2FScientist2Text, -1`
+ added `object_event 3, 6, SPRITE_SILPH_EMPLOYEE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, SilphCo2FEmployee1Script, -1`
+ added `object_event 12, 9, SPRITE_SILPH_EMPLOYEE, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, SilphCo2FSilphEmployee2Text, -1`

## SilphCo3F

- removed `bg_event 3, 2, BGEVENT_JUMPTEXT, SilphCo3FDeptSignText`
- removed `bg_event 9, 2, BGEVENT_JUMPTEXT, SilphCo3FDeptSignText`
- removed `bg_event 5, 0, BGEVENT_JUMPTEXT, SilphCo3FElevatorText`
- removed `bg_event 0, 3, BGEVENT_JUMPSTD, difficultbookshelf`
- removed `bg_event 6, 3, BGEVENT_JUMPSTD, difficultbookshelf`
- removed `bg_event 7, 3, BGEVENT_JUMPSTD, difficultbookshelf`
- removed `bg_event 12, 3, BGEVENT_JUMPSTD, difficultbookshelf`
- removed `bg_event 13, 3, BGEVENT_JUMPSTD, difficultbookshelf`
- removed `object_event 10, 5, SPRITE_SILPH_EMPLOYEE, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, SilphCo3FSilphEmployeeScript, -1`
- removed `object_event 8, 7, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, SilphCo3FScientist2Text, -1`
- removed `object_event 14, 4, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, pokemart, MARTTYPE_SILPH, MART_SILPH_CO, -1`
- removed `object_event 6, 6, SPRITE_GENTLEMAN, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, SilphCo3FGentlemanText, -1`
+ added `bg_event 8, 0, BGEVENT_JUMPTEXT, SilphCoElevatorText`
+ added `bg_event 4, 3, BGEVENT_JUMPTEXT, SilphCo3FDeptSignText`
+ added `bg_event 10, 3, BGEVENT_JUMPTEXT, SilphCo3FDeptSignText`
+ added `bg_event 0, 5, BGEVENT_JUMPTEXT, SilphCo3FPhotoText`
+ added `bg_event 1, 5, BGEVENT_JUMPSTD, difficultbookshelf`
+ added `bg_event 5, 0, BGEVENT_JUMPSTD, difficultbookshelf`
+ added `object_event 10, 7, SPRITE_SILPH_EMPLOYEE, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, SilphCo3FSilphEmployeeScript, -1`
+ added `object_event 9, 9, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, SilphCo3FScientist2Text, -1`
+ added `object_event 14, 5, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, pokemart, MARTTYPE_SILPH, MART_SILPH_CO, -1`
+ added `object_event 7, 6, SPRITE_GENTLEMAN, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, SilphCo3FGentlemanText, -1`

## SilverCaveItemRooms

- removed `warp_event 21, 33, SILVER_CAVE_ROOM_2, 3`
- removed `warp_event 5, 27, SILVER_CAVE_ROOM_2, 4`
- removed `itemball_event 14, 33, MAX_REVIVE, 1, EVENT_SILVER_CAVE_ITEM_ROOMS_MAX_REVIVE`
- removed `itemball_event 13, 23, FULL_RESTORE, 1, EVENT_SILVER_CAVE_ITEM_ROOMS_FULL_RESTORE`
+ added `warp_event 21, 11, SILVER_CAVE_ROOM_2, 3`
+ added `warp_event 5, 7, SILVER_CAVE_ROOM_2, 4`
+ added `itemball_event 14, 11, MAX_REVIVE, 1, EVENT_SILVER_CAVE_ITEM_ROOMS_MAX_REVIVE`
+ added `itemball_event 13, 3, FULL_RESTORE, 1, EVENT_SILVER_CAVE_ITEM_ROOMS_FULL_RESTORE`

## SilverCaveRoom3

- removed `warp_event 9, 29, SILVER_CAVE_ROOM_2, 2`
- removed `object_event 10, 6, SPRITE_RED, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Red, EVENT_RED_IN_MT_SILVER`
+ added `warp_event 7, 29, SILVER_CAVE_ROOM_2, 2`
+ added `object_event 8, 6, SPRITE_RED, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, Red, EVENT_RED_IN_MT_SILVER`
+ added `object_event 0, 9, SPRITE_RATTATA_BACK, SPRITEMOVEDATA_ARCH_TREE_LEFT, 0, 0, -1, PAL_NPC_COPY_BG_ROOF, OBJECTTYPE_COMMAND, end, NULL, -1`
+ added `object_event 1, 8, SPRITE_RATTATA_BACK, SPRITEMOVEDATA_ARCH_TREE_LEFT, 0, 0, -1, PAL_NPC_COPY_BG_ROOF, OBJECTTYPE_COMMAND, end, NULL, -1`
+ added `object_event 2, 7, SPRITE_RATTATA_BACK, SPRITEMOVEDATA_POKECOM_NEWS, 0, 0, -1, PAL_NPC_COPY_BG_ROOF, OBJECTTYPE_COMMAND, end, NULL, -1`
+ added `object_event 3, 6, SPRITE_BALL_CUT_TREE, SPRITEMOVEDATA_ARCH_TREE_LEFT, 0, 0, -1, PAL_NPC_COPY_BG_ROOF, OBJECTTYPE_COMMAND, end, NULL, -1`
+ added `object_event 15, 9, SPRITE_BLANK_FRUIT, SPRITEMOVEDATA_ARCH_TREE_RIGHT, 0, 0, -1, PAL_NPC_COPY_BG_ROOF, OBJECTTYPE_COMMAND, end, NULL, -1`
+ added `object_event 14, 8, SPRITE_BLANK_FRUIT, SPRITEMOVEDATA_ARCH_TREE_RIGHT, 0, 0, -1, PAL_NPC_COPY_BG_ROOF, OBJECTTYPE_COMMAND, end, NULL, -1`
+ added `object_event 13, 7, SPRITE_BLANK_FRUIT, SPRITEMOVEDATA_POKECOM_NEWS, 0, 0, -1, PAL_NPC_COPY_BG_ROOF, OBJECTTYPE_COMMAND, end, NULL, -1`
+ added `object_event 12, 6, SPRITE_BALL_CUT_TREE, SPRITEMOVEDATA_ARCH_TREE_RIGHT, 0, 0, -1, PAL_NPC_COPY_BG_ROOF, OBJECTTYPE_COMMAND, end, NULL, -1`

## SinjohRuins

- removed `warp_event 5, 7, MYSTRI_STAGE, 1`
- removed `warp_event 13, 21, SINJOH_RUINS_HOUSE, 1`
- removed `warp_event 8, 22, HIDDEN_CAVE_GROTTO, 1`
- removed `bg_event 7, 8, BGEVENT_JUMPTEXT, SinjohRuinsSignpostText`
- removed `bg_event 8, 21, BGEVENT_JUMPSTD, cavegrotto, HIDDENGROTTO_SINJOH_RUINS`
+ added `warp_event 4, 5, MYSTRI_STAGE, 1`
+ added `warp_event 13, 17, SINJOH_RUINS_HOUSE, 1`
+ added `warp_event 8, 18, HIDDEN_CAVE_GROTTO, 1`
+ added `bg_event 6, 6, BGEVENT_JUMPTEXT, SinjohRuinsSignpostText`
+ added `bg_event 8, 17, BGEVENT_JUMPSTD, cavegrotto, HIDDENGROTTO_SINJOH_RUINS`

## SinjohRuinsHouse

- removed `pokemon_event 2, 3, ABRA, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BROWN, SinjohRuinsHouseAbraText, -1`
+ added `pokemon_event 2, 3, ABRA, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BROWN, SinjohRuinsHouseAbraText, -1`

## SnowtopMountainInside

- removed `object_event 28, 14, SPRITE_KIMONO_GIRL, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, KimonoGirlAmiScript, -1`
+ added `object_event 28, 14, SPRITE_KIMONO_GIRL, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, PAL_NPC_AZURE, OBJECTTYPE_SCRIPT, 0, KimonoGirlAmiScript, -1`

## SnowtopMountainOutside

- removed `warp_event 9, 31, SNOWTOP_MOUNTAIN_INSIDE, 2`
- removed `warp_event 17, 33, SNOWTOP_POKECENTER_1F, 1`
- removed `coord_event 4, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 5, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 6, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 7, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 8, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 9, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 10, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 11, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 12, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 13, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 14, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 15, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 16, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 17, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 18, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 19, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 20, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 21, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 22, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 23, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 24, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 25, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `coord_event 26, 28, 1, SnowtopMountainOutsideStopPanningScript`
- removed `bg_event 10, 27, BGEVENT_UP, SnowtopMountainOutsideStartPanningScript`
- removed `bg_event 11, 27, BGEVENT_UP, SnowtopMountainOutsideStartPanningScript`
- removed `bg_event 12, 27, BGEVENT_UP, SnowtopMountainOutsideStartPanningScript`
- removed `bg_event 13, 27, BGEVENT_UP, SnowtopMountainOutsideStartPanningScript`
- removed `bg_event 14, 27, BGEVENT_UP, SnowtopMountainOutsideStartPanningScript`
- removed `bg_event 15, 27, BGEVENT_UP, SnowtopMountainOutsideStartPanningScript`
- removed `bg_event 16, 27, BGEVENT_UP, SnowtopMountainOutsideStartPanningScript`
- removed `bg_event 17, 27, BGEVENT_UP, SnowtopMountainOutsideStartPanningScript`
- removed `bg_event 18, 27, BGEVENT_UP, SnowtopMountainOutsideStartPanningScript`
- removed `bg_event 19, 27, BGEVENT_UP, SnowtopMountainOutsideStartPanningScript`
- removed `object_event 26, 11, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 0, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
- removed `object_event 16, 16, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 1, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
- removed `object_event 17, 11, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 3, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
- removed `object_event 14, 11, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 3, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
- removed `object_event 11, 13, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 3, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
- removed `object_event 14, 14, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 2, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
- removed `object_event 8, 16, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 2, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
- removed `object_event 6, 16, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 2, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
- removed `object_event 5, 7, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 4, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_OLIVINE_GYM_JASMINE`
- removed `object_event 5, 8, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 5, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
- removed `object_event 5, 10, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 6, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
+ added `warp_event 9, 25, SNOWTOP_MOUNTAIN_INSIDE, 2`
+ added `warp_event 17, 27, SNOWTOP_POKECENTER_1F, 1`
+ added `coord_event 4, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 5, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 6, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 7, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 8, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 9, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 10, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 11, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 12, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 13, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 14, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 15, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 16, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 17, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 18, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 19, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 20, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 21, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 22, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 23, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 24, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 25, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `coord_event 26, 22, SCENE_SNOWTOPMOUNTAINOUTSIDE_PANNING, SnowtopMountainOutsideStopPanningScript`
+ added `bg_event 10, 21, BGEVENT_UP, SnowtopMountainOutsideStartPanningScript`
+ added `bg_event 11, 21, BGEVENT_UP, SnowtopMountainOutsideStartPanningScript`
+ added `bg_event 12, 21, BGEVENT_UP, SnowtopMountainOutsideStartPanningScript`
+ added `bg_event 13, 21, BGEVENT_UP, SnowtopMountainOutsideStartPanningScript`
+ added `bg_event 14, 21, BGEVENT_UP, SnowtopMountainOutsideStartPanningScript`
+ added `bg_event 15, 21, BGEVENT_UP, SnowtopMountainOutsideStartPanningScript`
+ added `bg_event 16, 21, BGEVENT_UP, SnowtopMountainOutsideStartPanningScript`
+ added `bg_event 17, 21, BGEVENT_UP, SnowtopMountainOutsideStartPanningScript`
+ added `bg_event 18, 21, BGEVENT_UP, SnowtopMountainOutsideStartPanningScript`
+ added `bg_event 19, 21, BGEVENT_UP, SnowtopMountainOutsideStartPanningScript`
+ added `object_event 26, 9, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 0, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
+ added `object_event 16, 14, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 1, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
+ added `object_event 17, 9, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 3, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
+ added `object_event 14, 9, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 3, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
+ added `object_event 10, 9, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 3, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
+ added `object_event 13, 12, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 2, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
+ added `object_event 8, 14, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 2, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
+ added `object_event 6, 14, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 2, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
+ added `object_event 5, 4, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 4, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_OLIVINE_GYM_JASMINE`
+ added `object_event 5, 5, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 5, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`
+ added `object_event 5, 6, SPRITE_SAILBOAT, SPRITEMOVEDATA_TINY_WINDOWS, 0, 6, (1 << EVE) | (1 << NITE), PAL_NPC_TINY_WINDOW, OBJECTTYPE_SCRIPT, 0, DoNothingScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2`

## SnowtopPokeCenter1F

- removed `warp_event 0, 7, POKECENTER_2F, 1`

## SproutTower1F

- removed `object_event 7, 9, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, SproutTower1FTeacherText, -1`
+ added `object_event 7, 9, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, SproutTower1FTeacherText, -1`

## SproutTower3F

- removed `coord_event 9, 9, 0, SproutTower3FRivalScene`
+ added `coord_event 9, 9, SCENE_SPROUTTOWER3F_RIVAL_ENCOUNTER, SproutTower3FRivalScene`

## StormyBeach

- removed `object_event 26, 17, SPRITE_SWIMMER_GUY, SPRITEMOVEDATA_SWIM_AROUND, 1, 1, -1, PAL_NPC_BLUE, OBJECTTYPE_COMMAND, jumptextfaceplayer, StormyBeachSwimmermText, -1`
+ added `object_event 22, 16, SPRITE_SWIMMER_GUY, SPRITEMOVEDATA_SWIM_AROUND, 1, 1, -1, PAL_NPC_BLUE, OBJECTTYPE_COMMAND, jumptextfaceplayer, StormyBeachSwimmermText, -1`

## TeamRocketBaseB1F

- removed `coord_event 24, 2, 0, SecurityCamera1a`
- removed `coord_event 24, 3, 0, SecurityCamera1b`
- removed `coord_event 6, 2, 0, SecurityCamera2a`
- removed `coord_event 6, 3, 0, SecurityCamera2b`
- removed `coord_event 24, 6, 0, SecurityCamera3a`
- removed `coord_event 24, 7, 0, SecurityCamera3b`
- removed `coord_event 22, 16, 0, SecurityCamera4`
- removed `coord_event 8, 16, 0, SecurityCamera5`
- removed `coord_event 2, 7, 0, ExplodingTrap1`
- removed `coord_event 3, 7, 0, ExplodingTrap2`
- removed `coord_event 4, 7, 0, ExplodingTrap3`
- removed `coord_event 1, 8, 0, ExplodingTrap4`
- removed `coord_event 3, 8, 0, ExplodingTrap5`
- removed `coord_event 5, 8, 0, ExplodingTrap6`
- removed `coord_event 3, 9, 0, ExplodingTrap7`
- removed `coord_event 4, 9, 0, ExplodingTrap8`
- removed `coord_event 1, 10, 0, ExplodingTrap9`
- removed `coord_event 2, 10, 0, ExplodingTrap10`
- removed `coord_event 3, 10, 0, ExplodingTrap11`
- removed `coord_event 5, 10, 0, ExplodingTrap12`
- removed `coord_event 2, 11, 0, ExplodingTrap13`
- removed `coord_event 4, 11, 0, ExplodingTrap14`
- removed `coord_event 1, 12, 0, ExplodingTrap15`
- removed `coord_event 2, 12, 0, ExplodingTrap16`
- removed `coord_event 4, 12, 0, ExplodingTrap17`
- removed `coord_event 5, 12, 0, ExplodingTrap18`
- removed `coord_event 1, 13, 0, ExplodingTrap19`
- removed `coord_event 3, 13, 0, ExplodingTrap20`
- removed `coord_event 4, 13, 0, ExplodingTrap21`
- removed `coord_event 5, 13, 0, ExplodingTrap22`
+ added `coord_event 24, 2, SCENE_TEAMROCKETBASEB1F_TRAPS, SecurityCamera1a`
+ added `coord_event 24, 3, SCENE_TEAMROCKETBASEB1F_TRAPS, SecurityCamera1b`
+ added `coord_event 6, 2, SCENE_TEAMROCKETBASEB1F_TRAPS, SecurityCamera2a`
+ added `coord_event 6, 3, SCENE_TEAMROCKETBASEB1F_TRAPS, SecurityCamera2b`
+ added `coord_event 24, 6, SCENE_TEAMROCKETBASEB1F_TRAPS, SecurityCamera3a`
+ added `coord_event 24, 7, SCENE_TEAMROCKETBASEB1F_TRAPS, SecurityCamera3b`
+ added `coord_event 22, 16, SCENE_TEAMROCKETBASEB1F_TRAPS, SecurityCamera4`
+ added `coord_event 8, 16, SCENE_TEAMROCKETBASEB1F_TRAPS, SecurityCamera5`
+ added `coord_event 2, 7, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap1`
+ added `coord_event 3, 7, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap2`
+ added `coord_event 4, 7, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap3`
+ added `coord_event 1, 8, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap4`
+ added `coord_event 3, 8, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap5`
+ added `coord_event 5, 8, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap6`
+ added `coord_event 3, 9, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap7`
+ added `coord_event 4, 9, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap8`
+ added `coord_event 1, 10, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap9`
+ added `coord_event 2, 10, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap10`
+ added `coord_event 3, 10, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap11`
+ added `coord_event 5, 10, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap12`
+ added `coord_event 2, 11, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap13`
+ added `coord_event 4, 11, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap14`
+ added `coord_event 1, 12, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap15`
+ added `coord_event 2, 12, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap16`
+ added `coord_event 4, 12, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap17`
+ added `coord_event 5, 12, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap18`
+ added `coord_event 1, 13, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap19`
+ added `coord_event 3, 13, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap20`
+ added `coord_event 4, 13, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap21`
+ added `coord_event 5, 13, SCENE_TEAMROCKETBASEB1F_TRAPS, ExplodingTrap22`

## TeamRocketBaseB2F

- removed `coord_event 5, 14, 0, LanceHealsScript`
- removed `coord_event 4, 13, 0, LanceHealsScript`
- removed `coord_event 14, 11, 1, RocketBaseBossFLeft`
- removed `coord_event 15, 11, 1, RocketBaseBossFRight`
- removed `coord_event 14, 12, 2, RocketBaseCantLeaveScript`
- removed `coord_event 15, 12, 2, RocketBaseCantLeaveScript`
- removed `coord_event 12, 3, 2, RocketBaseLancesSideScript`
- removed `coord_event 12, 10, 2, RocketBaseLancesSideScript`
- removed `coord_event 12, 11, 2, RocketBaseLancesSideScript`
- removed `bg_event 17, 9, BGEVENT_READ, TeamRocketBaseB2FTransmitterScript`
- removed `bg_event 16, 9, BGEVENT_READ, TeamRocketBaseB2FTransmitterScript`
- removed `bg_event 15, 9, BGEVENT_READ, TeamRocketBaseB2FTransmitterScript`
- removed `bg_event 14, 9, BGEVENT_READ, TeamRocketBaseB2FTransmitterScript`
- removed `bg_event 13, 9, BGEVENT_READ, TeamRocketBaseB2FTransmitterScript`
- removed `bg_event 12, 9, BGEVENT_READ, TeamRocketBaseB2FTransmitterScript`
- removed `object_event 7, 5, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, ELECTRODE, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, NO_FORM, RocketElectrode1, EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_1`
- removed `object_event 7, 7, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, ELECTRODE, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, NO_FORM, RocketElectrode2, EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_2`
- removed `object_event 7, 9, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, ELECTRODE, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, NO_FORM, RocketElectrode3, EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_3`
- removed `pokemon_event 22, 5, ELECTRODE, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_RED, ClearText, EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_1`
- removed `pokemon_event 22, 7, ELECTRODE, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_RED, ClearText, EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_2`
- removed `pokemon_event 22, 9, ELECTRODE, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_RED, ClearText, EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_3`
+ added `coord_event 5, 14, SCENE_TEAMROCKETBASEB2F_LANCE_HEALS, LanceHealsScript`
+ added `coord_event 4, 13, SCENE_TEAMROCKETBASEB2F_LANCE_HEALS, LanceHealsScript`
+ added `coord_event 14, 11, SCENE_TEAMROCKETBASEB2F_ROCKET_BOSS, RocketBaseBossFLeft`
+ added `coord_event 15, 11, SCENE_TEAMROCKETBASEB2F_ROCKET_BOSS, RocketBaseBossFRight`
+ added `coord_event 14, 12, SCENE_TEAMROCKETBASEB2F_ELECTRODES, RocketBaseCantLeaveScript`
+ added `coord_event 15, 12, SCENE_TEAMROCKETBASEB2F_ELECTRODES, RocketBaseCantLeaveScript`
+ added `coord_event 12, 3, SCENE_TEAMROCKETBASEB2F_ELECTRODES, RocketBaseLancesSideScript`
+ added `coord_event 12, 10, SCENE_TEAMROCKETBASEB2F_ELECTRODES, RocketBaseLancesSideScript`
+ added `coord_event 12, 11, SCENE_TEAMROCKETBASEB2F_ELECTRODES, RocketBaseLancesSideScript`
+ added `bg_event 16, 8, BGEVENT_READ, TeamRocketBaseB2FTransmitterScript`
+ added `bg_event 15, 8, BGEVENT_READ, TeamRocketBaseB2FTransmitterScript`
+ added `bg_event 14, 8, BGEVENT_READ, TeamRocketBaseB2FTransmitterScript`
+ added `bg_event 13, 8, BGEVENT_READ, TeamRocketBaseB2FTransmitterScript`
+ added `object_event 7, 5, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, ELECTRODE, -1, PAL_MON_RED, OBJECTTYPE_SCRIPT, NO_FORM, RocketElectrode1, EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_1`
+ added `object_event 7, 7, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, ELECTRODE, -1, PAL_MON_RED, OBJECTTYPE_SCRIPT, NO_FORM, RocketElectrode2, EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_2`
+ added `object_event 7, 9, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, ELECTRODE, -1, PAL_MON_RED, OBJECTTYPE_SCRIPT, NO_FORM, RocketElectrode3, EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_3`
+ added `pokemon_event 22, 5, ELECTRODE, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_RED, ClearText, EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_1`
+ added `pokemon_event 22, 7, ELECTRODE, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_RED, ClearText, EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_2`
+ added `pokemon_event 22, 9, ELECTRODE, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_RED, ClearText, EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_3`

## TeamRocketBaseB3F

- removed `coord_event 10, 8, 2, RocketBaseBossLeft`
- removed `coord_event 11, 8, 2, RocketBaseBossRight`
- removed `coord_event 8, 10, 1, RocketBaseRival`
- removed `object_event 7, 2, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, MURKROW, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, NO_FORM, RocketBaseMurkrow, EVENT_TEAM_ROCKET_BASE_POPULATION`
+ added `coord_event 10, 8, SCENE_TEAMROCKETBASEB3F_ROCKET_BOSS, RocketBaseBossLeft`
+ added `coord_event 11, 8, SCENE_TEAMROCKETBASEB3F_ROCKET_BOSS, RocketBaseBossRight`
+ added `coord_event 8, 10, SCENE_TEAMROCKETBASEB3F_RIVAL_ENCOUNTER, RocketBaseRival`
+ added `object_event 7, 2, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, MURKROW, -1, PAL_MON_BLUE, OBJECTTYPE_SCRIPT, NO_FORM, RocketBaseMurkrow, EVENT_TEAM_ROCKET_BASE_POPULATION`

## TinTower10F

- removed `warp_event 7, 15, TIN_TOWER_ROOF, 1`
+ added `warp_event 6, 15, TIN_TOWER_ROOF, 1`

## TinTower1F

- removed `pokemon_event 7, 9, SUICUNE, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BLUE, ClearText, EVENT_TIN_TOWER_1F_SUICUNE`
- removed `pokemon_event 5, 9, RAIKOU, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BROWN, ClearText, EVENT_TIN_TOWER_1F_RAIKOU`
- removed `pokemon_event 10, 9, ENTEI, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_RED, ClearText, EVENT_TIN_TOWER_1F_ENTEI`
- removed `object_event 3, 9, SPRITE_ELDER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, TinTower1FSage1Text, EVENT_TIN_TOWER_1F_WISE_TRIO_1`
- removed `object_event 9, 11, SPRITE_ELDER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, TinTower1FSage2Text, EVENT_TIN_TOWER_1F_WISE_TRIO_1`
- removed `object_event 12, 6, SPRITE_ELDER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, TinTower1FSage3Text, EVENT_TIN_TOWER_1F_WISE_TRIO_1`
- removed `object_event 2, 2, SPRITE_ELDER, SPRITEMOVEDATA_WALK_UP_DOWN, 1, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, TinTower1FSage4Script, EVENT_TIN_TOWER_1F_WISE_TRIO_2`
- removed `object_event 7, 1, SPRITE_ELDER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, TinTower1FSage5Script, EVENT_TIN_TOWER_1F_WISE_TRIO_2`
- removed `object_event 12, 2, SPRITE_ELDER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 1, -1, 0, OBJECTTYPE_SCRIPT, 0, TinTower1FSage6Script, EVENT_TIN_TOWER_1F_WISE_TRIO_2`
+ added `pokemon_event 7, 9, SUICUNE, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_AZURE, ClearText, EVENT_TIN_TOWER_1F_SUICUNE`
+ added `pokemon_event 5, 9, RAIKOU, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BROWN, ClearText, EVENT_TIN_TOWER_1F_RAIKOU`
+ added `pokemon_event 10, 9, ENTEI, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_RED, ClearText, EVENT_TIN_TOWER_1F_ENTEI`
+ added `object_event 3, 9, SPRITE_ELDER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, TinTower1FSage1Text, EVENT_TIN_TOWER_1F_WISE_TRIO_1`
+ added `object_event 9, 11, SPRITE_ELDER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_COMMAND, jumptextfaceplayer, TinTower1FSage2Text, EVENT_TIN_TOWER_1F_WISE_TRIO_1`
+ added `object_event 12, 6, SPRITE_ELDER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_COMMAND, jumptextfaceplayer, TinTower1FSage3Text, EVENT_TIN_TOWER_1F_WISE_TRIO_1`
+ added `object_event 2, 2, SPRITE_ELDER, SPRITEMOVEDATA_WALK_UP_DOWN, 1, 0, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, TinTower1FSage4Script, EVENT_TIN_TOWER_1F_WISE_TRIO_2`
+ added `object_event 7, 1, SPRITE_ELDER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, TinTower1FSage5Script, EVENT_TIN_TOWER_1F_WISE_TRIO_2`
+ added `object_event 12, 2, SPRITE_ELDER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, TinTower1FSage6Script, EVENT_TIN_TOWER_1F_WISE_TRIO_2`

## TinTower5F

- removed `warp_event 9, 15, TIN_TOWER_6F, 2`
- removed `warp_event 0, 4, TIN_TOWER_4F, 1`
- removed `warp_event 0, 14, TIN_TOWER_4F, 3`
- removed `warp_event 15, 15, TIN_TOWER_4F, 4`
- removed `bg_event 14, 14, BGEVENT_ITEM + FULL_RESTORE, EVENT_TIN_TOWER_5F_HIDDEN_FULL_RESTORE`
- removed `bg_event 1, 15, BGEVENT_ITEM + CARBOS, EVENT_TIN_TOWER_5F_HIDDEN_CARBOS`
- removed `itemball_event 7, 9, RARE_CANDY, 1, EVENT_TIN_TOWER_5F_RARE_CANDY`
+ added `warp_event 9, 17, TIN_TOWER_6F, 2`
+ added `warp_event 0, 6, TIN_TOWER_4F, 1`
+ added `warp_event 0, 16, TIN_TOWER_4F, 3`
+ added `warp_event 15, 17, TIN_TOWER_4F, 4`
+ added `bg_event 14, 16, BGEVENT_ITEM + FULL_RESTORE, EVENT_TIN_TOWER_5F_HIDDEN_FULL_RESTORE`
+ added `bg_event 1, 17, BGEVENT_ITEM + CARBOS, EVENT_TIN_TOWER_5F_HIDDEN_CARBOS`
+ added `itemball_event 7, 11, RARE_CANDY, 1, EVENT_TIN_TOWER_5F_RARE_CANDY`

## TinTowerRoof

- removed `warp_event 7, 13, TIN_TOWER_10F, 2`
- removed `object_event 7, 3, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, HO_OH, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, NO_FORM, TinTowerHoOh, EVENT_TIN_TOWER_ROOF_HO_OH`
+ added `warp_event 6, 13, TIN_TOWER_10F, 2`
+ added `object_event 6, 2, SPRITE_BIG_HO_OH, SPRITEMOVEDATA_BIG_HO_OH, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, TinTowerHoOh, EVENT_TIN_TOWER_ROOF_HO_OH`

## TrainerHouse1F

- removed `object_event 0, 10, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_COMMAND, jumptextfaceplayer, TrainerHouse1FReceptionistText, -1`
+ added `object_event 1, 10, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_COMMAND, jumptextfaceplayer, TrainerHouse1FReceptionistText, -1`

## TrainerHouseB1F

- removed `coord_event 7, 3, 0, TrainerHouseReceptionistScript`
+ added `coord_event 7, 3, SCENE_TRAINERHOUSEB1F_ASK_BATTLE, TrainerHouseReceptionistScript`

## Underground

- removed `warp_event 3, 2, ROUTE_5_UNDERGROUND_ENTRANCE, 3`
- removed `warp_event 3, 32, ROUTE_6_UNDERGROUND_ENTRANCE, 3`
- removed `bg_event 3, 9, BGEVENT_ITEM + FULL_RESTORE, EVENT_UNDERGROUND_HIDDEN_FULL_RESTORE`
- removed `bg_event 1, 21, BGEVENT_ITEM + X_SP_ATK, EVENT_UNDERGROUND_HIDDEN_X_SP_ATK`
- removed `tmhmball_event 4, 15, TM_EXPLOSION, EVENT_UNDERGROUND_TM_EXPLOSION`

## UndergroundPath

+ added `warp_event 3, 2, ROUTE_5_UNDERGROUND_PATH_ENTRANCE, 3`
+ added `warp_event 3, 46, ROUTE_6_UNDERGROUND_PATH_ENTRANCE, 3`
+ added `bg_event 3, 14, BGEVENT_ITEM + FULL_RESTORE, EVENT_UNDERGROUND_PATH_HIDDEN_FULL_RESTORE`
+ added `bg_event 1, 33, BGEVENT_ITEM + X_SP_ATK, EVENT_UNDERGROUND_PATH_HIDDEN_X_SP_ATK`
+ added `tmhmball_event 4, 21, TM_EXPLOSION, EVENT_UNDERGROUND_PATH_TM_EXPLOSION`

## UndergroundPathSwitchRoomEntrances

- removed `warp_event 23, 3, WAREHOUSE_ENTRANCE, 6`
- removed `warp_event 22, 10, UNDERGROUND_WAREHOUSE, 1`
- removed `warp_event 23, 10, UNDERGROUND_WAREHOUSE, 2`
- removed `warp_event 5, 23, WAREHOUSE_ENTRANCE, 2`
- removed `warp_event 4, 27, GOLDENROD_CITY, 14`
- removed `warp_event 5, 27, GOLDENROD_CITY, 14`
- removed `warp_event 21, 23, WAREHOUSE_ENTRANCE, 1`
- removed `warp_event 20, 27, GOLDENROD_CITY, 13`
- removed `warp_event 21, 27, GOLDENROD_CITY, 13`
- removed `warp_event 5, 37, WAREHOUSE_ENTRANCE, 7`
- removed `warp_event 4, 41, GOLDENROD_CITY, 22`
- removed `warp_event 5, 41, GOLDENROD_CITY, 22`
- removed `coord_event 19, 4, 0, UndergroundRivalTrigger1`
- removed `coord_event 19, 5, 0, UndergroundRivalTrigger2`
- removed `bg_event 16, 1, BGEVENT_READ, Switch1Script`
- removed `bg_event 10, 1, BGEVENT_READ, Switch2Script`
- removed `bg_event 2, 1, BGEVENT_READ, Switch3Script`
- removed `bg_event 20, 11, BGEVENT_READ, EmergencySwitchScript`
- removed `bg_event 8, 9, BGEVENT_ITEM + MAX_POTION, EVENT_UNDERGROUND_PATH_SWITCH_ROOM_ENTRANCES_HIDDEN_MAX_POTION`
- removed `bg_event 1, 8, BGEVENT_ITEM + REVIVE, EVENT_UNDERGROUND_PATH_SWITCH_ROOM_ENTRANCES_HIDDEN_REVIVE`
- removed `object_event 23, 3, SPRITE_RIVAL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_RIVAL_UNDERGROUND_PATH`
- removed `object_event 9, 12, SPRITE_BURGLAR, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerBurglarDuncan, EVENT_RADIO_TOWER_ROCKET_TAKEOVER`
- removed `object_event 4, 8, SPRITE_BURGLAR, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 2, GenericTrainerBurglarOrson, EVENT_RADIO_TOWER_ROCKET_TAKEOVER`
- removed `object_event 17, 2, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerGruntM13, EVENT_RADIO_TOWER_ROCKET_TAKEOVER`
- removed `object_event 11, 2, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerGruntM11, EVENT_RADIO_TOWER_ROCKET_TAKEOVER`
- removed `object_event 3, 2, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerGruntM25, EVENT_RADIO_TOWER_ROCKET_TAKEOVER`
- removed `object_event 19, 12, SPRITE_ROCKET_GIRL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_GENERICTRAINER, 1, GenericTrainerGruntF3, EVENT_RADIO_TOWER_ROCKET_TAKEOVER`
- removed `object_event 3, 25, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, UndergroundPathSwitchRoomEntrances_TeacherText, -1`
- removed `object_event 8, 24, SPRITE_SUPER_NERD, SPRITEMOVEDATA_WALK_UP_DOWN, 2, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, UndergroundPathSwitchRoomEntrances_SuperNerd1Text, -1`
- removed `object_event 19, 25, SPRITE_BUG_MANIAC, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, UndergroundPathSwitchRoomEntrances_SuperNerd2Text, -1`
- removed `object_event 1, 39, SPRITE_VETERAN_M, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 1, -1, PAL_NPC_GRAY, OBJECTTYPE_SCRIPT, 0, UndergroundPathSwitchRoomEntrancesVeteranMScript, -1`
- removed `object_event 8, 38, SPRITE_BEAUTY, SPRITEMOVEDATA_WALK_UP_DOWN, 1, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, UndergroundPathSwitchRoomEntrances_BeautyText, -1`
- removed `itemball_event 1, 12, SMOKE_BALL, 1, EVENT_UNDERGROUND_PATH_SWITCH_ROOM_ENTRANCES_SMOKE_BALL`
- removed `itemball_event 14, 9, FULL_HEAL, 1, EVENT_UNDERGROUND_PATH_SWITCH_ROOM_ENTRANCES_FULL_HEAL`

## UndergroundWarehouse -> GoldenrodUndergroundWarehouse

- removed `warp_event 2, 12, UNDERGROUND_PATH_SWITCH_ROOM_ENTRANCES, 2`
- removed `warp_event 3, 12, UNDERGROUND_PATH_SWITCH_ROOM_ENTRANCES, 3`
- removed `itemball_event 18, 15, MAX_ETHER, 1, EVENT_UNDERGROUND_WAREHOUSE_MAX_ETHER`
- removed `tmhmball_event 13, 9, TM_X_SCISSOR, EVENT_UNDERGROUND_WAREHOUSE_TM_X_SCISSOR`
- removed `itemball_event 2, 1, ULTRA_BALL, 1, EVENT_UNDERGROUND_WAREHOUSE_ULTRA_BALL`
+ added `warp_event 2, 12, GOLDENROD_UNDERGROUND_SWITCH_ROOM, 2`
+ added `warp_event 3, 12, GOLDENROD_UNDERGROUND_SWITCH_ROOM, 3`
+ added `itemball_event 18, 15, MAX_ETHER, 1, EVENT_GOLDENROD_UNDERGROUND_WAREHOUSE_MAX_ETHER`
+ added `tmhmball_event 13, 9, TM_X_SCISSOR, EVENT_GOLDENROD_UNDERGROUND_WAREHOUSE_TM_X_SCISSOR`
+ added `itemball_event 2, 1, ULTRA_BALL, 1, EVENT_GOLDENROD_UNDERGROUND_WAREHOUSE_ULTRA_BALL`

## UnionCaveB1FNorth

- removed `warp_event 3, 3, RUINS_OF_ALPH_OUTSIDE, 7`
- removed `warp_event 3, 11, RUINS_OF_ALPH_OUTSIDE, 8`
+ added `warp_event 3, 3, RUINS_OF_ALPH_OUTSIDE, 8`
+ added `warp_event 3, 11, RUINS_OF_ALPH_OUTSIDE, 9`

## UragaChannelEast

- removed `bg_event 45, 5, BGEVENT_JUMPTEXT, UragaChannelSignText`
- removed `itemball_event 9, 2, DIVE_BALL, 1, EVENT_URAGA_CHANNEL_EAST_DIVE_BALL`
+ added `bg_event 45, 4, BGEVENT_JUMPTEXT, UragaChannelSignText`
+ added `object_event 10, 3, SPRITE_FLOATING_BALL, SPRITEMOVEDATA_POKEMON, 0, 0, -1, 0, OBJECTTYPE_ITEMBALL, PLAYEREVENT_ITEMBALL, DIVE_BALL, 1, EVENT_URAGA_CHANNEL_EAST_DIVE_BALL`

## ValeriesHouse

- removed `object_event 3, 3, SPRITE_BOOK_PAPER_POKEDEX, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptext, ValeriesHouseRedFairyBookText, EVENT_RED_FAIRY_BOOK`
- removed `object_event 3, 3, SPRITE_BOOK_PAPER_POKEDEX, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_COMMAND, jumptext, ValeriesHouseBlueFairyBookText, EVENT_BLUE_FAIRY_BOOK`
- removed `object_event 3, 3, SPRITE_BOOK_PAPER_POKEDEX, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_COMMAND, jumptext, ValeriesHouseGreenFairyBookText, EVENT_GREEN_FAIRY_BOOK`
- removed `object_event 3, 3, SPRITE_BOOK_PAPER_POKEDEX, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_COMMAND, jumptext, ValeriesHouseBrownFairyBookText, EVENT_BROWN_FAIRY_BOOK`
- removed `object_event 3, 3, SPRITE_BOOK_PAPER_POKEDEX, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_COMMAND, jumptext, ValeriesHouseVioletFairyBookText, EVENT_VIOLET_FAIRY_BOOK`
- removed `object_event 3, 3, SPRITE_BOOK_PAPER_POKEDEX, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_PINK, OBJECTTYPE_COMMAND, jumptext, ValeriesHousePinkFairyBookText, EVENT_PINK_FAIRY_BOOK`
- removed `object_event 3, 3, SPRITE_BOOK_PAPER_POKEDEX, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_YELLOW, OBJECTTYPE_COMMAND, jumptext, ValeriesHouseYellowFairyBookText, EVENT_YELLOW_FAIRY_BOOK`
+ added `object_event 3, 3, SPRITE_BOOK_PAPER_POKEDEX, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ValeriesHouseFairyBookScript, -1`

## VermilionCity

- removed `warp_event 5, 5, VERMILION_HOUSE_FISHING_SPEECH_HOUSE, 1`
- removed `warp_event 9, 5, VERMILION_POKECENTER_1F, 1`
- removed `warp_event 7, 17, POKEMON_FAN_CLUB, 1`
- removed `warp_event 13, 17, VERMILION_MAGNET_TRAIN_SPEECH_HOUSE, 1`
- removed `warp_event 21, 17, VERMILION_MART, 2`
- removed `warp_event 21, 21, VERMILION_HOUSE_DIGLETTS_CAVE_SPEECH_HOUSE, 1`
- removed `warp_event 10, 23, VERMILION_GYM, 1`
- removed `warp_event 18, 35, VERMILION_PORT, 1`
- removed `warp_event 19, 35, VERMILION_PORT, 3`
- removed `warp_event 36, 17, DIGLETTS_CAVE, 1`
- removed `warp_event 28, 35, SEAGALLOP_FERRY_VERMILION_GATE, 1`
- removed `warp_event 29, 35, SEAGALLOP_FERRY_VERMILION_GATE, 1`
- removed `warp_event 13, 5, VERMILION_POLLUTION_SPEECH_HOUSE, 1`
- removed `warp_event 19, 5, VERMILION_S_S_ANNE_SPEECH_HOUSE, 1`
- removed `warp_event 29, 9, BATTLE_FACTORY_1F, 1`
- removed `warp_event 30, 9, BATTLE_FACTORY_1F, 2`
- removed `bg_event 19, 9, BGEVENT_JUMPTEXT, VermilionCitySignText`
- removed `bg_event 5, 23, BGEVENT_JUMPTEXT, VermilionGymSignText`
- removed `bg_event 5, 17, BGEVENT_JUMPTEXT, PokemonFanClubSignText`
- removed `bg_event 33, 17, BGEVENT_JUMPTEXT, VermilionCityDiglettsCaveSignText`
- removed `bg_event 27, 19, BGEVENT_JUMPTEXT, VermilionCityPortSignText`
- removed `bg_event 23, 13, BGEVENT_JUMPTEXT, VermilionCityBattleFactorySignText`
- removed `bg_event 11, 27, BGEVENT_JUMPTEXT, VermilionCityAdvancedTipsSignText`
- removed `bg_event 12, 23, BGEVENT_ITEM + FULL_HEAL, EVENT_VERMILION_CITY_HIDDEN_FULL_HEAL`
- removed `object_event 35, 18, SPRITE_BIG_SNORLAX, SPRITEMOVEDATA_SNORLAX, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, VermilionSnorlax, EVENT_VERMILION_CITY_SNORLAX`
- removed `object_event 18, 31, SPRITE_LAWRENCE, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_LAWRENCE_VERMILION_CITY`
- removed `object_event 18, 13, SPRITE_BATTLE_GIRL, SPRITEMOVEDATA_WANDER, 1, 1, -1, PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, VermilionCityTeacherText, -1`
- removed `object_event 23, 10, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, VermilionMachokeOwnerScript, -1`
- removed `pokemon_event 24, 10, MACHOKE, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_GRAY, VermilionMachokeText, -1`
- removed `object_event 16, 20, SPRITE_ROCKER, SPRITEMOVEDATA_WANDER, 1, 1, -1, PAL_NPC_GREEN, OBJECTTYPE_COMMAND, jumptextfaceplayer, VermilionCitySuperNerdText, -1`
- removed `object_event 32, 12, SPRITE_POKEMANIAC, SPRITEMOVEDATA_WALK_UP_DOWN, 1, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, VermilionCitySuperNerd2Script, -1`
- removed `object_event 11, 9, SPRITE_SAILOR, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 3, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, VermilionCitySailorText, -1`
- removed `object_event 31, 16, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_SCRIPT, 0, VermilionGymBadgeGuy, -1`
- removed `object_event 29, 10, SPRITE_OFFICER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, VermilionCityOfficerFText, EVENT_RESTORED_POWER_TO_KANTO`
- removed `object_event 30, 10, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, VermilionCityOfficerText, EVENT_RESTORED_POWER_TO_KANTO`
- removed `cuttree_event 13, 23, EVENT_VERMILION_CITY_CUT_TREE`
+ added `warp_event 5, 3, VERMILION_HOUSE_FISHING_SPEECH_HOUSE, 1`
+ added `warp_event 9, 3, VERMILION_POKECENTER_1F, 1`
+ added `warp_event 7, 13, POKEMON_FAN_CLUB, 1`
+ added `warp_event 13, 13, VERMILION_MAGNET_TRAIN_SPEECH_HOUSE, 1`
+ added `warp_event 21, 13, VERMILION_MART, 2`
+ added `warp_event 21, 17, VERMILION_HOUSE_DIGLETTS_CAVE_SPEECH_HOUSE, 1`
+ added `warp_event 8, 19, VERMILION_GYM, 1`
+ added `warp_event 18, 31, VERMILION_PORT, 1`
+ added `warp_event 19, 31, VERMILION_PORT, 3`
+ added `warp_event 38, 13, DIGLETTS_CAVE, 1`
+ added `warp_event 28, 31, SEAGALLOP_FERRY_VERMILION_GATE, 1`
+ added `warp_event 29, 31, SEAGALLOP_FERRY_VERMILION_GATE, 1`
+ added `warp_event 13, 3, VERMILION_POLLUTION_SPEECH_HOUSE, 1`
+ added `warp_event 19, 3, VERMILION_S_S_ANNE_SPEECH_HOUSE, 1`
+ added `warp_event 28, 7, BATTLE_FACTORY_1F, 1`
+ added `bg_event 15, 7, BGEVENT_JUMPTEXT, VermilionCitySignText`
+ added `bg_event 9, 19, BGEVENT_JUMPTEXT, VermilionGymSignText`
+ added `bg_event 5, 13, BGEVENT_JUMPTEXT, PokemonFanClubSignText`
+ added `bg_event 35, 13, BGEVENT_JUMPTEXT, VermilionCityDiglettsCaveSignText`
+ added `bg_event 27, 15, BGEVENT_JUMPTEXT, VermilionCityPortSignText`
+ added `bg_event 27, 24, BGEVENT_JUMPTEXT, VermilionCityPierSignText`
+ added `bg_event 23, 7, BGEVENT_JUMPTEXT, VermilionCityBattleFactorySignText`
+ added `bg_event 10, 23, BGEVENT_JUMPTEXT, VermilionCityAdvancedTipsSignText`
+ added `bg_event 12, 19, BGEVENT_ITEM + FULL_HEAL, EVENT_VERMILION_CITY_HIDDEN_FULL_HEAL`
+ added `bg_event 32, 4, BGEVENT_ITEM + MAX_ETHER, EVENT_VERMILION_CITY_HIDDEN_MAX_ETHER`
+ added `object_event 37, 14, SPRITE_BIG_SNORLAX, SPRITEMOVEDATA_SNORLAX, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, VermilionSnorlax, EVENT_VERMILION_CITY_SNORLAX`
+ added `object_event 18, 27, SPRITE_LAWRENCE, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_LAWRENCE_VERMILION_CITY`
+ added `object_event 18, 10, SPRITE_BATTLE_GIRL, SPRITEMOVEDATA_WANDER, 1, 1, -1, PAL_NPC_RED, OBJECTTYPE_COMMAND, jumptextfaceplayer, VermilionCityTeacherText, -1`
+ added `object_event 20, 7, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, VermilionMachokeOwnerScript, -1`
+ added `pokemon_event 21, 7, MACHOKE, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_GRAY, VermilionMachokeText, -1`
+ added `object_event 16, 16, SPRITE_ROCKER, SPRITEMOVEDATA_WANDER, 1, 1, -1, PAL_NPC_GREEN, OBJECTTYPE_COMMAND, jumptextfaceplayer, VermilionCitySuperNerdText, -1`
+ added `object_event 31, 10, SPRITE_POKEMANIAC, SPRITEMOVEDATA_WALK_UP_DOWN, 1, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, VermilionCitySuperNerd2Script, -1`
+ added `object_event 11, 6, SPRITE_SAILOR, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 0, 3, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, VermilionCitySailorText, -1`
+ added `object_event 19, 13, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_PURPLE, OBJECTTYPE_SCRIPT, 0, VermilionGymBadgeGuy, -1`
+ added `object_event 28, 8, SPRITE_OFFICER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_COMMAND, jumptextfaceplayer, VermilionCityOfficerFText, EVENT_RESTORED_POWER_TO_KANTO`
+ added `cuttree_event 13, 19, EVENT_VERMILION_CITY_CUT_TREE`
+ added `object_event 30, 1, SPRITE_PEARL, SPRITEMOVEDATA_ARCH_TREE_LEFT, 0, 0, -1, PAL_NPC_COPY_BG_GREEN, OBJECTTYPE_COMMAND, end, NULL, -1`
+ added `object_event 26, 1, SPRITE_PEARL, SPRITEMOVEDATA_ARCH_TREE_RIGHT, 0, 0, -1, PAL_NPC_COPY_BG_GREEN, OBJECTTYPE_COMMAND, end, NULL, -1`
+ added `object_event 27, 32, SPRITE_BIG_LAPRAS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_COPY_BG_WATER, OBJECTTYPE_COMMAND, end, NULL, -1`
+ added `object_event 30, 32, SPRITE_BIG_LAPRAS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, PAL_NPC_COPY_BG_WATER, OBJECTTYPE_COMMAND, end, NULL, -1`

## VermilionPort

- removed `coord_event 7, 11, 0, VermilionPortWalkUpToShipScript`
+ added `coord_event 7, 11, SCENE_VERMILIONPORT_ASK_ENTER_SHIP, VermilionPortWalkUpToShipScript`

## VictoryRoad1F

- removed `warp_event 11, 21, ROUTE_23, 3`
+ added `warp_event 11, 21, ROUTE_23_NORTH, 1`

## VictoryRoad2F

- removed `warp_event 25, 9, ROUTE_23, 4`
- removed `coord_event 25, 9, 0, VictoryRoadRivalLeft`
+ added `warp_event 25, 9, ROUTE_23_NORTH, 2`
+ added `coord_event 25, 9, SCENE_VICTORYROAD2F_RIVAL_BATTLE, VictoryRoadRivalLeft`

## VioletCity

- removed `warp_event 2, 8, ROUTE_36_VIOLET_GATE, 3`
- removed `warp_event 2, 9, ROUTE_36_VIOLET_GATE, 4`
- removed `bg_event 15, 17, BGEVENT_JUMPTEXT, VioletGymSignText`
+ added `warp_event 0, 8, ROUTE_36_VIOLET_GATE, 3`
+ added `warp_event 0, 9, ROUTE_36_VIOLET_GATE, 4`
+ added `bg_event 19, 17, BGEVENT_JUMPTEXT, VioletGymSignText`

## VioletGym

- removed `warp_event 4, 15, VIOLET_CITY, 2`
- removed `warp_event 5, 15, VIOLET_CITY, 2`
- removed `bg_event 3, 13, BGEVENT_READ, VioletGymStatue`
- removed `bg_event 6, 13, BGEVENT_READ, VioletGymStatue`
- removed `object_event 4, 13, SPRITE_GYM_GUY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_DARK_CAVE_FALKNER`
- removed `object_event 5, 1, SPRITE_FALKNER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, VioletGymFalknerScript, EVENT_VIOLET_GYM_FALKNER`
- removed `object_event 7, 6, SPRITE_BIRD_KEEPER, SPRITEMOVEDATA_STANDING_LEFT, 0, 2, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBird_keeperRod, EVENT_VIOLET_GYM_FALKNER`
- removed `object_event 2, 10, SPRITE_BIRD_KEEPER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 2, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBird_keeperAbe, EVENT_VIOLET_GYM_FALKNER`
- removed `object_event 7, 13, SPRITE_GYM_GUY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, VioletGymGuyScript, EVENT_VIOLET_GYM_FALKNER`
+ added `warp_event 4, 17, VIOLET_CITY, 2`
+ added `warp_event 5, 17, VIOLET_CITY, 2`
+ added `bg_event 3, 15, BGEVENT_READ, VioletGymStatue`
+ added `bg_event 6, 15, BGEVENT_READ, VioletGymStatue`
+ added `object_event 4, 15, SPRITE_GYM_GUY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_DARK_CAVE_FALKNER`
+ added `object_event 5, 2, SPRITE_FALKNER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, VioletGymFalknerScript, EVENT_VIOLET_GYM_FALKNER`
+ added `object_event 7, 7, SPRITE_BIRD_KEEPER, SPRITEMOVEDATA_STANDING_LEFT, 0, 2, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBird_keeperRod, EVENT_VIOLET_GYM_FALKNER`
+ added `object_event 2, 11, SPRITE_BIRD_KEEPER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 2, -1, 0, OBJECTTYPE_GENERICTRAINER, 3, GenericTrainerBird_keeperAbe, EVENT_VIOLET_GYM_FALKNER`
+ added `object_event 7, 15, SPRITE_GYM_GUY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, VioletGymGuyScript, EVENT_VIOLET_GYM_FALKNER`

## VioletOutskirts

- removed `object_event 16, -2, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, SUICUNE, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, NO_FORM, ObjectEvent, EVENT_SAW_SUICUNE_ON_ROUTE_42`
- removed `fruittree_event 19, -2, FRUITTREE_ROUTE_42_3, YLW_APRICORN, PAL_NPC_YELLOW`
- removed `itemball_event 14, 24, PP_UP, 1, EVENT_VIOLET_CITY_PP_UP`
+ added `object_event 16, -2, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, SUICUNE, -1, PAL_MON_AZURE, OBJECTTYPE_SCRIPT, NO_FORM, ObjectEvent, EVENT_SAW_SUICUNE_ON_ROUTE_42`
+ added `fruittree_event 19, -2, FRUITTREE_ROUTE_42_3, YLW_APRICORN, PAL_NPC_ENV_YELLOW`
+ added `itemball_event 14, 28, PP_UP, 1, EVENT_VIOLET_CITY_PP_UP`

## ViridianCity

- removed `warp_event 32, 7, VIRIDIAN_GYM, 1`
- removed `warp_event 23, 15, TRAINER_HOUSE_1F, 1`
- removed `bg_event 27, 7, BGEVENT_JUMPTEXT, ViridianGymSignText`
- removed `bg_event 21, 15, BGEVENT_JUMPTEXT, TrainerHouseSignText`
- removed `object_event 32, 8, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, ViridianCityGrampsNearGym, EVENT_BLUE_IN_CINNABAR`
- removed `object_event 30, 8, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, ViridianCityGrampsNearGym, EVENT_VIRIDIAN_GYM_BLUE`
+ added `warp_event 30, 7, VIRIDIAN_GYM, 1`
+ added `warp_event 21, 15, TRAINER_HOUSE_1F, 1`
+ added `bg_event 31, 7, BGEVENT_JUMPTEXT, ViridianGymSignText`
+ added `bg_event 24, 16, BGEVENT_JUMPTEXT, TrainerHouseSignText`
+ added `object_event 30, 8, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, ViridianCityGrampsNearGym, EVENT_BLUE_IN_CINNABAR`
+ added `object_event 33, 8, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, ViridianCityGrampsNearGym, EVENT_VIRIDIAN_GYM_BLUE`

## ViridianNicknameSpeechHouse

- removed `pokemon_event 5, 2, HOOTHOOT, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_BROWN, HootyText, -1`
- removed `pokemon_event 6, 3, RATTATA, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_PURPLE, RatteyText, -1`
+ added `pokemon_event 5, 2, HOOTHOOT, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_BROWN, HootyText, -1`
+ added `pokemon_event 6, 3, RATTATA, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_PURPLE, RatteyText, -1`

## WarehouseEntrance -> GoldenrodUnderground

- removed `warp_event 1, 2, UNDERGROUND_PATH_SWITCH_ROOM_ENTRANCES, 7`
- removed `warp_event 1, 38, UNDERGROUND_PATH_SWITCH_ROOM_ENTRANCES, 4`
- removed `warp_event 16, 6, WAREHOUSE_ENTRANCE, 4`
- removed `warp_event 27, 23, WAREHOUSE_ENTRANCE, 3`
- removed `warp_event 28, 23, WAREHOUSE_ENTRANCE, 3`
- removed `warp_event 28, 19, UNDERGROUND_PATH_SWITCH_ROOM_ENTRANCES, 1`
- removed `warp_event 19, 36, UNDERGROUND_PATH_SWITCH_ROOM_ENTRANCES, 10`
- removed `bg_event 4, 17, BGEVENT_ITEM + PARALYZEHEAL, EVENT_WAREHOUSE_ENTRANCE_HIDDEN_PARALYZEHEAL`
- removed `bg_event 2, 22, BGEVENT_ITEM + SUPER_POTION, EVENT_WAREHOUSE_ENTRANCE_HIDDEN_SUPER_POTION`
- removed `bg_event 15, 8, BGEVENT_ITEM + ANTIDOTE, EVENT_WAREHOUSE_ENTRANCE_HIDDEN_ANTIDOTE`
- removed `bg_event 20, 31, BGEVENT_ITEM + X_SP_ATK, EVENT_WAREHOUSE_ENTRANCE_HIDDEN_X_SP_ATK`
- removed `object_event 5, 15, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, BargainMerchantScript, EVENT_WAREHOUSE_ENTRANCE_GRAMPS`
- removed `object_event 5, 18, SPRITE_POKEMANIAC, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, OlderHaircutBrotherScript, EVENT_WAREHOUSE_ENTRANCE_OLDER_HAIRCUT_BROTHER`
- removed `object_event 5, 19, SPRITE_POKEMANIAC, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, YoungerHaircutBrotherScript, EVENT_WAREHOUSE_ENTRANCE_YOUNGER_HAIRCUT_BROTHER`
- removed `object_event 5, 25, SPRITE_GRANNY, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, BitterMerchantScript, EVENT_WAREHOUSE_ENTRANCE_GRANNY`
- removed `keyitemball_event 5, 28, COIN_CASE, EVENT_WAREHOUSE_ENTRANCE_COIN_CASE`
+ added `warp_event 1, 2, GOLDENROD_UNDERGROUND_ENTRANCES, 4`
+ added `warp_event 1, 38, GOLDENROD_UNDERGROUND_ENTRANCES, 1`
+ added `warp_event 16, 6, GOLDENROD_UNDERGROUND, 4`
+ added `warp_event 17, 23, GOLDENROD_UNDERGROUND, 3`
+ added `warp_event 18, 23, GOLDENROD_UNDERGROUND, 3`
+ added `warp_event 18, 19, GOLDENROD_UNDERGROUND_SWITCH_ROOM, 1`
+ added `warp_event 19, 36, GOLDENROD_UNDERGROUND_ENTRANCES, 7`
+ added `bg_event 4, 17, BGEVENT_ITEM + PARALYZEHEAL, EVENT_GOLDENROD_UNDERGROUND_HIDDEN_PARALYZEHEAL`
+ added `bg_event 2, 22, BGEVENT_ITEM + SUPER_POTION, EVENT_GOLDENROD_UNDERGROUND_HIDDEN_SUPER_POTION`
+ added `bg_event 15, 8, BGEVENT_ITEM + ANTIDOTE, EVENT_GOLDENROD_UNDERGROUND_HIDDEN_ANTIDOTE`
+ added `bg_event 20, 31, BGEVENT_ITEM + X_SP_ATK, EVENT_GOLDENROD_UNDERGROUND_HIDDEN_X_SP_ATK`
+ added `object_event 5, 15, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, BargainMerchantScript, EVENT_GOLDENROD_UNDERGROUND_GRAMPS`
+ added `object_event 5, 18, SPRITE_POKEMANIAC, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, OlderHaircutBrotherScript, EVENT_GOLDENROD_UNDERGROUND_OLDER_HAIRCUT_BROTHER`
+ added `object_event 5, 19, SPRITE_POKEMANIAC, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, YoungerHaircutBrotherScript, EVENT_GOLDENROD_UNDERGROUND_YOUNGER_HAIRCUT_BROTHER`
+ added `object_event 5, 25, SPRITE_GRANNY, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_SCRIPT, 0, BitterMerchantScript, EVENT_GOLDENROD_UNDERGROUND_GRANNY`
+ added `keyitemball_event 5, 28, COIN_CASE, EVENT_GOLDENROD_UNDERGROUND_COIN_CASE`

## WarmBeach

- removed `object_event 17, 21, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, SLOWKING, -1, PAL_NPC_PINK, OBJECTTYPE_SCRIPT, PLAIN_FORM, WarmBeachSlowkingScript, -1`
+ added `object_event 17, 21, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, SLOWKING, -1, PAL_MON_PINK, OBJECTTYPE_SCRIPT, PLAIN_FORM, WarmBeachSlowkingScript, -1`

## WhirlIslandCave

- removed `warp_event 37, 43, WHIRL_ISLAND_B1F, 9`
- removed `warp_event 33, 51, WHIRL_ISLAND_NW, 4`
+ added `warp_event 7, 5, WHIRL_ISLAND_B1F, 9`
+ added `warp_event 3, 13, WHIRL_ISLAND_NW, 4`

## WhirlIslandLugiaChamber

- removed `object_event 9, 5, SPRITE_MON_ICON, SPRITEMOVEDATA_POKEMON, 0, LUGIA, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, NO_FORM, Lugia, EVENT_WHIRL_ISLAND_LUGIA_CHAMBER_LUGIA`
+ added `object_event 9, 5, SPRITE_BIG_LUGIA, SPRITEMOVEDATA_BIG_LUGIA, 0, 0, -1, PAL_NPC_ENV_WHITE, OBJECTTYPE_SCRIPT, 0, Lugia, EVENT_WHIRL_ISLAND_LUGIA_CHAMBER_LUGIA`

## WhirlIslandNW

- removed `warp_event 5, 33, ROUTE_41, 1`
- removed `warp_event 5, 29, WHIRL_ISLAND_B1F, 1`
- removed `warp_event 15, 31, WHIRL_ISLAND_SW, 4`
- removed `warp_event 19, 31, WHIRL_ISLAND_CAVE, 2`
+ added `warp_event 5, 7, ROUTE_41, 1`
+ added `warp_event 5, 3, WHIRL_ISLAND_B1F, 1`
+ added `warp_event 3, 15, WHIRL_ISLAND_SW, 4`
+ added `warp_event 7, 15, WHIRL_ISLAND_CAVE, 2`

## WiseTriosRoom

- removed `coord_event 7, 4, 0, WiseTriosRoom_CannotEnterTinTowerScript`
- removed `object_event 4, 2, SPRITE_ELDER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 2, TrainerElderGaku, EVENT_WISE_TRIOS_ROOM_WISE_TRIO_2`
- removed `object_event 4, 6, SPRITE_ELDER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 2, TrainerElderMasa, EVENT_WISE_TRIOS_ROOM_WISE_TRIO_2`
- removed `object_event 6, 4, SPRITE_ELDER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, 0, OBJECTTYPE_TRAINER, 2, TrainerElderKoji, EVENT_WISE_TRIOS_ROOM_WISE_TRIO_2`
+ added `coord_event 7, 4, SCENE_WISETRIOSROOM_SAGE_BLOCKS, WiseTriosRoom_CannotEnterTinTowerScript`
+ added `object_event 4, 2, SPRITE_ELDER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 2, TrainerElderGaku, EVENT_WISE_TRIOS_ROOM_WISE_TRIO_2`
+ added `object_event 4, 6, SPRITE_ELDER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 2, TrainerElderMasa, EVENT_WISE_TRIOS_ROOM_WISE_TRIO_2`
+ added `object_event 6, 4, SPRITE_ELDER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 2, TrainerElderKoji, EVENT_WISE_TRIOS_ROOM_WISE_TRIO_2`

## YellowForest

- removed `coord_event 32, 16, 1, YellowForestBridgeOverheadTrigger`
- removed `coord_event 32, 17, 1, YellowForestBridgeOverheadTrigger`
- removed `coord_event 39, 16, 1, YellowForestBridgeOverheadTrigger`
- removed `coord_event 39, 17, 1, YellowForestBridgeOverheadTrigger`
- removed `coord_event 33, 16, 0, YellowForestBridgeUnderfootTrigger`
- removed `coord_event 33, 17, 0, YellowForestBridgeUnderfootTrigger`
- removed `coord_event 38, 16, 0, YellowForestBridgeUnderfootTrigger`
- removed `coord_event 38, 17, 0, YellowForestBridgeUnderfootTrigger`
- removed `pokemon_event 8, 24, SKARMORY, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_GRAY, ClearText, EVENT_YELLOW_FOREST_SKARMORY`
- removed `object_event 49, 26, SPRITE_BALL_CUT_FRUIT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_DECO_ITEM, OBJECTTYPE_SCRIPT, 0, YellowForestSurfPikachuDoll, EVENT_DECO_SURFING_PIKACHU_DOLL`
+ added `coord_event 32, 16, SCENE_YELLOWFOREST_BRIDGE_OVERHEAD, YellowForestBridgeOverheadTrigger`
+ added `coord_event 32, 17, SCENE_YELLOWFOREST_BRIDGE_OVERHEAD, YellowForestBridgeOverheadTrigger`
+ added `coord_event 39, 16, SCENE_YELLOWFOREST_BRIDGE_OVERHEAD, YellowForestBridgeOverheadTrigger`
+ added `coord_event 39, 17, SCENE_YELLOWFOREST_BRIDGE_OVERHEAD, YellowForestBridgeOverheadTrigger`
+ added `coord_event 33, 16, SCENE_YELLOWFOREST_BRIDGE_UNDERFOOT, YellowForestBridgeUnderfootTrigger`
+ added `coord_event 33, 17, SCENE_YELLOWFOREST_BRIDGE_UNDERFOOT, YellowForestBridgeUnderfootTrigger`
+ added `coord_event 38, 16, SCENE_YELLOWFOREST_BRIDGE_UNDERFOOT, YellowForestBridgeUnderfootTrigger`
+ added `coord_event 38, 17, SCENE_YELLOWFOREST_BRIDGE_UNDERFOOT, YellowForestBridgeUnderfootTrigger`
+ added `pokemon_event 8, 24, SKARMORY, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_GRAY, ClearText, EVENT_YELLOW_FOREST_SKARMORY`
+ added `object_event 49, 26, SPRITE_BALL_CUT_TREE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, PAL_NPC_ENV_BLUE, OBJECTTYPE_SCRIPT, 0, YellowForestSurfPikachuDoll, EVENT_DECO_SURFING_PIKACHU_DOLL`

## YellowForestGate

- removed `pokemon_event 9, 4, CHANSEY, SPRITEMOVEDATA_POKEMON, -1, PAL_NPC_PINK, YellowForestGateChanseyText, -1`
+ added `pokemon_event 9, 4, CHANSEY, SPRITEMOVEDATA_POKEMON, -1, PAL_MON_PINK, YellowForestGateChanseyText, -1`

