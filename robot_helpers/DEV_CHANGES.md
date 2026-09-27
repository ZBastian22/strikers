# What changed in the developers' version

Compared: **Polished Crystal v3.2.3** (tag `v3.2.3`, commit
`3fa43192379df5c3e7b09a08e4d5d79af4f02f42`) against the **development
version**: the default branch `master` of `Rangi42/polishedcrystal` at
commit **`411e5913abd6dc3e2366668e4327ee85331a21a9`** (2026-09-25, "Moody
will now invoke Eject Pack if applicable"), 864 commits later.

Overall: 3323 files changed (+55249 −38824 lines). By share of changed
files: maps 22%, `gfx/minis` 16%, `data/pokemon/base_stats` 10%,
`gfx/items` 8%, `gfx/icons` 7%, `gfx/tilesets` 5.5%, `data/tilesets` 4.4%,
engine 3.6%.

How this was made: by reading the diffs and commit messages between the
two versions (nothing was built or run), plus scripts that compare the
constants and every map's events in both checkouts. Paths are relative to
the repository root. "[HIGH]" marks changes likely to break a port that
ignores them, "[MED]" and "[LOW]" the rest; within each group HIGH comes
first. "Faithful" means the `FAITHFUL` build option; otherwise changes are
for the default build.

Full lists that are too long for this page:
[`dev_changes/names.md`](dev_changes/names.md) (every constant name added
or removed, per list) and
[`dev_changes/map_events.md`](dev_changes/map_events.md) (every warp,
person, sign and trigger added, removed or moved, per map).

## Most likely to break a port

In rough order of how badly a port breaks if it ignores them. Details and
more changes are in the sections below.

1. **Text compression replaced** — `home/text.asm`, `constants/huffman_text.*`, `data/text/compressed_text.asm` — ROM text is now contextual Huffman (3 trees picked by the previous character, raw-byte escape `$fc`); the n-gram dictionary is gone and Pokédex entries are compressed too. Old text decoders can't read it.
2. **`text_far` layout changed** — `macros/scripts/text.asm`, `home/text.asm` — the address is now big-endian, and its bit 15 means "end after this" (`text_farend`).
3. **`.lz` → `.lzp` everywhere** — `home/decompress.asm`, `tools/lzpcompress.c` — every compressed graphic, tilemap, tileset and block file uses 3 new LZ opcodes (`$fc`, `$fd`, `$fe`).
4. **Map ids renumbered** — `constants/map_constants.asm`, `data/maps/maps.asm` — 605 → 611 maps, 37 → 39 groups; 132 kept maps have a new group or number (e.g. NEW_BARK_TOWN 24:4 → 24:2, ELMS_LAB 24:5 → 24:3).
5. **Blocks and tilesets must both come from dev** — `maps/*.ablk`, `data/maps/blocks.asm`, `constants/tileset_constants.asm` — 53 maps changed size, 231 block files were redrawn, 85 maps use another tileset, tileset ids renumbered (11 added, 3 removed).
6. **Map header and map source format** — `constants/map_data_constants.asm`, `data/maps/attributes.asm`, `macros/scripts/maps.asm` — environment constants reordered (TOWN 1 → 0, ROUTE 2 → 1, …) so every map header byte changes; `map_attributes` lost its connection-mask argument; scenes are now named `SCENE_*` constants.
7. **Script bytecode shifts** — `macros/scripts/movement.asm`, `macros/scripts/events.asm`, `data/events/special_pointers.asm` — movement commands from `$48` up moved down by 3, `half_step_*` added at `$65-$68`; `MAPCALLBACK_*` renumbered; 4 new event commands `$dc-$df` (`nooryes`, `digmod`, `toggleevent`, `usepaletteswap`); a special inserted at index 77 moves the 82 after it by +1.
8. **Saves: same `SAVE_VERSION` (10), different meaning** — `ram/*.asm` — `wPlayerState` values, `wVisitedSpawns` bits and formerly unused save bytes (palette swap, overcast maps, object glow) changed. A v3.2.3 save loads without error and is silently wrong.
9. **Spawn / fly / engine flag ids shifted** — `constants/engine_flags.asm`, `constants/map_data_constants.asm`, `data/maps/spawn_points.asm` — a Pokémon League spawn and fly point were inserted after Indigo; 175 engine flags have a new number.
10. **Trainer data renumbered and re-encoded** — `constants/trainer_constants.asm`, `data/trainers/*` — classes renumbered (EUNA inserted, CAL/CARRIE swapped, KATY → LARRY, FIREBREATHER_ASHES appended); `TRAINERTYPE_*` party bits each moved down one bit, so party blobs differ with the same source.
11. **Pokémon form and ability numbering** — `constants/pokemon_constants.asm`, `constants/ability_constants.asm` — a new `ARBOK_ORANGE_FORM` moves every extended-form index from `$140` up by 1 (all ext-indexed tables gain a row); 5 new abilities (4 inserted mid-list) shift ability ids; ability behaviour lists became a flags table.
12. **Data record formats** — `data/wild/*`, `data/pokemon/cries.asm`, `data/events/npc_trades.asm`, Battle Tower and Wonder Trade data, `data/items/*` — wild grass records 68 → 66 bytes (one rate per map), cry rows 6 → 5 bytes (+38 cries), name fields 1 byte shorter, mon icon palettes 2 bytes, `HELD_*` +1, item use effects moved into data tables.
13. **Overworld weather and palettes reworked** — `engine/overworld/*`, `data/maps/overcast_maps.asm`, `data/maps/dual_obj_pals.asm`, `data/tileset_palettes.asm` — 4 random overcast maps a day (overcast, rain, thunderstorm; rain carries into battle), new special-palette format, palette-swap regions, glow tiles tinting objects, dual object palettes, new collision values (a cave-mouth tile that warps).
14. **Main story changes** — see "Main story path" below — Burned Tower adds a forced battle (scene values +1), the Goldenrod Underground was rebuilt (5 maps, door switches, renamed flags), Route 23 split in two (officers now push you back), Route 13 merged, new gym puzzles in Azalea, Ecruteak and Cianwood, the Dragon Shrine test starts only from the front door.
15. **Event flags: stable slots, some new meanings** — `constants/event_flags.asm`, `data/events/initialize_events.asm` — only `EVENT_BEAT_FIREBREATHER_DICK` moved (1070 → 2268; 1070 is now Firebreather Cyd); slots 610-620 changed meaning (switches → Underground doors); a new game sets 2 more flags and 4 were renamed.
16. **Other renumbered lists** — music from `$70` on (76 ids), sprites (`SPRITE_MON_ICON` `$ef` → `$ee`, 20 added, some renamed e.g. `SPRITE_BALL_CUT_FRUIT` → `SPRITE_BALL_CUT_TREE`), `PAL_NPC_*`, radio channels.
17. **Battle behaviour** — `engine/battle/*`, `data/moves/*`, `data/pokemon/base_stats/*` — 89 species with new stats (non-Faithful), several type and move changes (Growth is Grass type, Iron Head flinch 30 → 20, …), Binding Band, new abilities; boss teams overhauled (Red now has Lapras and Machamp).
18. **A fourth player** — `data/player/*`, `constants/*` — `PLAYER_BETA` ("Krys") in every per-player table, plus a running sprite.

Unchanged by number: moves, types, TMs/HMs, species names, items (Pink Bow was renamed Fairy Feather in the same slot), phone contacts, sound effects (one appended), script commands (four appended).

## Main story path

What changes for a player following the main story (female, Chikorita),
checkpoint by checkpoint. `story_presets_dev.lua` holds the dev version of
each checkpoint; its per-checkpoint notes give the dev file:line for each
change. Line numbers moved almost everywhere; only real story changes are
listed here.

- **New game (C01):** 4 flags set at new game were renamed
  (`EVENT_RIVAL_UNDERGROUND_PATH` → `EVENT_RIVAL_GOLDENROD_UNDERGROUND`,
  `EVENT_WAREHOUSE_LAYOUT_1` → `EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_1`,
  `EVENT_WAREHOUSE_BLOCKED_OFF` → `EVENT_GOLDENROD_WAREHOUSE_BLOCKED_OFF`,
  `EVENT_SHAMOUTI_ISLAND_PIKABLU_GUY` → `EVENT_SHAMOUTI_ISLAND_WILHOMENA`)
  and 2 were added (`EVENT_BETA_IN_NAVEL_ROCK`,
  `EVENT_BURNED_TOWER_FIREBREATHER_DICK_ASHES`) —
  `data/events/initialize_events.asm`. A fourth player choice exists
  (`PLAYER_BETA`); no story script branches on it. Elm's lab, New Bark and
  Mr. Pokémon changed only in text and layout.
- **Violet (C02):** no story change. Violet Gym was redesigned; Falkner's
  script is the same.
- **Azalea Gym (C03):** now the HGSS Spinarak-cart and web-switch puzzle —
  `maps/AzaleaGym.asm`. Its switches only use temporary flags, so nothing
  new is saved; Bugsy's script sets the same flags. Bugsy's party order
  changed (Scyther first), which changes his payout.
- **C04:** no story change (Day-Care, Route 34, Goldenrod, Ilex Forest,
  Radio Tower quiz all the same).
- **Burned Tower (C05):** a new forced battle. After Eusine's intro, the
  burnt-out Firebreather Dick (Charmeleon, level 17) blocks the way at
  (6,1), and the rival's trigger only becomes active after beating him —
  `maps/BurnedTower1F.asm`. New flags: `EVENT_BEAT_FIREBREATHER_DICK`
  (moved to slot 2268), `EVENT_BURNED_TOWER_FIREBREATHER_DICK_NORMAL`; the
  Burned Tower 1F scene ends at 3 instead of 2. Ecruteak Gym has a new pit
  layout; Morty's flags are the same.
- **Cianwood Gym (C06):** rebuilt in the HGSS waterfall style. Chuck only
  appears after both Strength boulders are pushed into the holes, which
  sets the new `EVENT_BOULDERS_IN_CIANWOOD_GYM` — `maps/CianwoodGym.asm`.
  Olivine City has named scenes and a new "step down" scene; it ends at
  scene 2 instead of 1 — `maps/OlivineCity.asm`.
- **C07, C08:** no story change. The Rocket hideout was redrawn with a new
  tileset; collision and the route are the same.
- **Radio Tower / Goldenrod Underground (C10):** the Underground was
  rebuilt into `GOLDENROD_UNDERGROUND`, `GOLDENROD_UNDERGROUND_ENTRANCES`,
  `GOLDENROD_UNDERGROUND_SWITCH_ROOM` and `GOLDENROD_UNDERGROUND_WAREHOUSE`
  (the old `UNDERGROUND_PATH_SWITCH_ROOM_ENTRANCES` is gone). The switch
  room is now the HGSS puzzle with 11 shutters (`EVENT_DOOR_1..11_OPEN`,
  reusing old switch slots 610-620); entering the Underground or the
  Warehouse opens doors 1-6, 9 and 10. Only the rival and Grunt M11 are
  forced now (six battles fewer). The Dept Store B1F / elevator flags use
  the new names.
- **Blackthorn (C09):** the Dragon Shrine has a new back door; the Elder's
  test only starts from the front door. Dragon's Den 1F is a separate map.
  The quiz, badge and TM are the same.
- **To the League (C11):** Route 23 is now two maps, `ROUTE_23_SOUTH`
  (Zephyr to Storm badge checks) and `ROUTE_23_NORTH` (Mineral to Rising),
  sharing one scene variable (the checkpoint records `ROUTE_23_NORTH` = 8).
  The officers now push you back if you lack a badge. The Pokémon League
  Gate has a new fly point (`ENGINE_FLYPOINT_POKEMON_LEAGUE`). The Lyra
  farewell trigger in New Bark and the Route 27 landing moved; both are
  still forced. Hall of Fame and `RespawnOneOffs` have no story change.
- **Kanto (C12):** the Rock Tunnel B1F trainer is now Firebreather Cyd
  (`EVENT_BEAT_FIREBREATHER_CYD`, same spot and party). Route 13 East and
  West were merged into one `ROUTE_13` (Joshua and Kenny are still
  forced). Cerulean City now shares Route 24's scene variable. Fuchsia
  gained a zoo and the Fuchsia Aquarium, Route 10 North an optional wild
  Electrode; the Power Plant, Vermilion, Cerulean, Fast Ship and Viridian
  Gym changed only in layout or text on the main path.
- **Red (C13):** no script change. Silver Cave Room 3 was redesigned and
  Red now stands at (8,6). His team changed (Lapras and Machamp replace
  Omastar and Gyarados), with the same top level (90).

## Renumbered and renamed names at a glance

"Kept names with a new number" counts names that exist in both versions
but have a different value (group and number for maps, class and id for
trainers). The names themselves are in `dev_changes/names.md`.

| list | file | names | added | removed | kept names with a new number |
|---|---|---|---|---|---|
| event flags | `constants/event_flags.asm` | 2259 → 2267 | 74 | 66 | 1 |
| engine flags | `constants/engine_flags.asm` | 242 → 243 | 2 | 1 | 175 |
| items and key items | `constants/item_constants.asm` | 316 → 316 | 1 | 1 | 0 |
| TMs/HMs/tutors | `constants/tmhm_constants.asm` | 112 → 112 | 0 | 0 | 0 |
| moves | `constants/move_constants.asm` | 287 → 287 | 0 | 0 | 0 |
| species / forms | `constants/pokemon_constants.asm` | 290 → 290 | 0 | 0 | 0 |
| maps | `constants/map_constants.asm` | 605 → 611 | 21 | 15 | 132 |
| trainer classes and ids | `constants/trainer_constants.asm` | 955 → 963 | 9 | 1 | 946 |
| sprites | `constants/sprite_constants.asm` | 220 → 236 | 20 | 4 | 1 |
| music | `constants/music_constants.asm` | 197 → 196 | 0 | 1 | 76 |
| sound effects | `constants/sfx_constants.asm` | 215 → 216 | 1 | 0 | 0 |
| specials | `data/events/special_pointers.asm` | 159 → 163 | 4 | 0 | 82 |
| phone contacts | `constants/phone_constants.asm` | 35 → 35 | 0 | 0 | 0 |
| abilities | `constants/ability_constants.asm` | 155 → 160 | 5 | 0 | 50 |
| script commands | `macros/scripts/events.asm` | 220 → 224 | 4 | 0 | 0 |
| tilesets | `constants/tileset_constants.asm` | 45 → 53 | 11 | 3 | 40 |

## Engine, text, formats and tools

Scope: engine/, home/, macros/ (incl. script macros), ram/, non-list constants/, tools/, Makefile, layout.link, and the formats of gfx/ and audio/ assets. Per-map event lists and flag/constant name lists are in `dev_changes/map_events.md` and `dev_changes/names.md`. Where this file lists enum shifts, it names only the ones the engine or a data format depends on.
Sources: `git log v3.2.3..HEAD` (484 commits touching these paths) plus the diffs that matter. Paths are relative to the repository root.

### Text system and charmap

- **[HIGH] Contextual Huffman replaces order-0 Huffman + n-grams** — `home/text.asm` (`ReadHuffmanChar`, `DecompressString*`), `constants/huffman_text.asm`, `constants/huffman_text.inc`, `data/text/compressed_text.asm`, `macros/scripts/text.asm`
  - The tree is picked by the previous decoded character:
    - `TextCompressionHuffmanTreeBoundary` after a space or `<LNBRK>`..`<PARA>`, and at the start of a string
    - `...Vowel` after A/E/I/O/U in either case
    - `...Other` otherwise
  - The decoder seeds `hCompressedTextBuffer` with `' '` and updates it after every character.
  - Node IDs:
    - `$00-$7e` are parent nodes.
    - `$7f-$eb` are the characters themselves.
    - `$ec-$fb` stand for characters `$4d-$5c`.
    - `$fc` is the escape: the next 8 bits (MSB first, straight from the bitstream) are a literal character.
  - Each tree is stored as pairs of child IDs (left, right) per parent node.
- **[HIGH] The n-gram dictionary was removed** — `constants/charmap.asm`, `data/text/ngrams.asm` (deleted)
  - The old 2-5 character n-grams at `$0a-$4c` ("ou", "the ", "You " …) no longer exist, and that byte range is unused.
  - Text commands still stop at `NUM_TEXT_COMMANDS=$0a`. `<FAR>` is `$08`, `<PLURAL>` is `$09`.
  - `$4d-$51` (`#`, `#mon`, `<PLAYER>`, `<RIVAL>`, `<TRENDY>`) are still "n-grams" that expand from ROM or WRAM.
- **[HIGH] New `<FAR>` encoding** — `macros/scripts/text.asm` (`text_far`, `text_farend`), `home/text.asm` `TextCommand_FAR`
  - Layout: `$08, hi(addr) | $80 if end, lo(addr), bank`.
  - With bit 15 set, the far text also ends the current text stream: it pops the `DoTextUntilTerminator` return, like `text_far` + `text_end`.
  - Most `text_far` + `text_end` pairs were converted to `text_farend` (#1580).
- **[HIGH] Charmap slot changes** — `constants/charmap.asm`
  - `$cb` `"ê"` was removed and is now `<BOLDH>`, a bold H used for HMs in the Bag.
  - `$61` `<STAR>` was renamed `<SHINY>` and now shows a separate light-gray star icon (`gfx/stats/shiny.png`).
  - Every Huffman `ctxtmap` code was dropped from the charmap. It is now a plain `charmap` plus the separate `huffmap` tables.
- **[HIGH] Pokédex entry text is now compressible `text`** — `data/pokemon/dex_entries.asm`, `macros/scripts/text.asm` (`page`)
  - The species kind stays as raw `db "Seed@"`.
  - Each page of the description is a separate `text` string that may start with `<CTXT>` (`$5d`). `page` now emits `"@"` and then starts a new `text`.
  - A port must decode entries with `PlaceString`'s `<CTXT>` path, not read them as raw bytes.
- **[MED] Non-blocking text pause flag** — `constants/ram_constants.asm` (`NO_TEXT_PAUSE_F`=5 in `wTextboxFlags`), `home/text.asm`
  - When the flag is set, `<CONT>`/`<PARA>` stop printing (`hStopPrintingString`) and `<PROMPT>` acts like `<DONE>`.
  - The scrolling option descriptions use it. States: `OPTDESCSTATE_PAGE/SCROLL/DONE`.
- **[MED] Pokédex Show radio program removed; radio text decompression shared** — `engine/pokegear/radio.asm`, `constants/radio_constants.asm`
  - `POKEDEX_SHOW*` channels were deleted, so every radio channel/line ID shifts. `POKEMON_MUSIC` is now `$01`.
  - Channel 16 is now only Oak's Pokémon Talk.
  - `PrepareToDecompressRadioText` is shared.
- **[LOW] Huffman tooling** — `utils/huffman.py`, `utils/verify_huffman.py`, Makefile `huffman` target
  - The `huffman` target is `.NOTPARALLEL` and prints characters per text in source order to regenerate `huffman_text.inc`.
  - `verify_huffman.py` round-trips the tree stored in the ROM.

### Compression, build tools, asset pipeline

- **[HIGH] LZP extended LZ opcodes** — `home/decompress.asm`, `tools/lzpcompress.c` (replaces `tools/lz/*` lzcomp, `tools/lz.py`)
  - A first byte of `$fc/$fd/$fe` (the long-command range, low 2 bits = subtype) is followed by a count byte (n-1, so 1-256) and ceil(n/2) payload bytes, high nibble first:
    - `$fc` packhi0: each output byte is `nibble<<4`.
    - `$fd` pack16: each output byte is `table[nibble]`, with table `00 ff 01 02 03 fe 80 07 c0 7f 04 0f 1f 3f 08 fc`.
    - `$fe` packlo0: each output byte is `nibble`.
  - `$ff` is still end-of-data.
  - Every `INCBIN "*.lz"` is now `*.lzp` (#1343; about 23 KB saved).
- **[HIGH] Tilesets, sprites, pics, icons, minis and item icons are all `.lzp`** — `gfx/*.asm`, `data/tilesets.asm`
  - Any extractor or asset converter must use the new decompressor.
  - Tileset metatiles, attributes and collision `.bin` are `.lzp` too.
- **[MED] New `tools/fine_print.c` renders text into 2bpp tiles**
  - Title-screen version string: `gfx/title/version.2bpp` from Makefile `COPYRIGHT = @YYYY RANGI42 vX.Y.Z` plus ` F` (faithful) / ` dbg`.
  - Splash copyright: `gfx/splash/copyright.txt` -> `copyright.2bpp`.
  - `logo_version.2bpp`, `version.png` and `splash/copyright.png` were removed.
- **[MED] Makefile gfx rule changes** — `Makefile`
  - `gfx/title/suicune_unowns.{2bpp,tilemap}` are built with rgbgfx `--unique-tiles --nb-tiles 127,127 --base-tiles 0,128` (two VRAM banks).
  - `gfx/stats/%.bin` = tilemap + attrmap (Judge Machine).
  - New trim flags for `gfx/evo/bubble`, `gfx/pokedex/oam`, `gfx/battle/hpexpbar` and the `gfx/trade/*` dedupe/flip rules.
  - New `*_back`/`*_card` rules for the `beta` player.
- **[LOW] `tools/gfx.py` and `tools/lz.py` removed; `tools/dedenc.c` added** — `tools/`
  - `dedenc.c` is an unused encoder for DED-format cries. `make_patch.c` is endian-independent and simpler.
  - The tools accept `-` for stdin/stdout, and `scan_includes` reads stdin.
- **[LOW] Toolchain bump** — `rgbdscheck.asm`, `.github`
  - CI builds with RGBDS v1.0.4 (v1.0.0 or newer is still required).
  - The `jmp` macro warns across the HRAM/ROM0 wrap, and `farcall`/`farjp`/`homecall` became `MACRO?`.
- **[LOW] `utils/lz_analyze_pack16.py`** — derives the pack16 table. `utils/optimize.py` gained more peephole patterns.

### Script engine: event commands, specials, macros

- **[HIGH] New event commands (appended, so existing opcodes keep their numbers)** — `macros/scripts/events.asm`, `engine/overworld/scripting.asm`
  - `$dc nooryes`: a Yes/No box with the cursor on "No"; sets `hScriptVar` TRUE if Yes.
  - `$dd digmod warp_id, map`: 3 bytes (warp, group, number), written to `wDigWarpNumber`/`wDigMapGroup`/`wDigMapNumber`.
  - `$de toggleevent flag`: `dw` flag. Flips the event flag and sets `hScriptVar` to its new value (TRUE = now set).
  - `$df usepaletteswap ptr`: `dw` pointer into the map-script bank, stored in `wPaletteSwapAddress`.
  - `NUM_EVENT_COMMANDS` is `$e0`.
- **[HIGH] The specials table was reordered** — `data/events/special_pointers.asm`
  - `GetSelectedPokemonHappiness` was inserted after `CheckFirstMonIsEgg`, so every later `special` byte is +1.
  - `ItemManiac_SelectQuantity`, `MultiplyMoneyByQuantity` and `TakeItemFromMemWithQuantity` were appended.
  - `special` emits a 1-byte index into the 3-byte `dba` table.
- **[HIGH] Map callback type numbering changed** — `constants/map_setup_constants.asm`
  - Now `MAPCALLBACK_NEWMAP=1, TILES=2, OBJECTS=3, CMDQUEUE=4`. It was TILES=1, OBJECTS=2, STONETABLE=3, 4 unused, NEWMAP=5.
  - `CMDQUEUE` (formerly STONETABLE) runs in `HandleContinueMap`, after the engine clears `wStoneTableAddress` and all 4 palette-swap bytes.
  - Maps now use it for both `usestonetable` and `usepaletteswap`.
- **[HIGH] Movement command renumbering** — `macros/scripts/movement.asm`, `engine/overworld/movement.asm`
  - `step_resume`($48), `step_loop`($4a) and `step_4b`($4b) were removed. `step_end` is still $47.
  - From there: `remove_object` $48, `teleport_from` $49, `teleport_to` $4a, `skyfall` $4b, `step_dig` $4c, … `paired_step_right` $64.
  - New `half_step_down/up/left/right` at `$65-$68`. `NUM_MOVEMENT_CMDS=$69`.
  - The movement table now stores parameters inline (`movement Func, STEP_x<<2|DIR`).
- **[MED] Item-giving macros now require a failure handler** — `macros/scripts/events.asm`
  - `giveitem X, iffalsefwd .Full`, `giveitems`, `verbosegiveitem(s)`, `verbosegiveitemvar`, plus `_unsafe` variants.
  - The bytecode is unchanged (quantity is always emitted).
  - `GiveItemScript` now keeps the success flag in `hScriptVar+1` across the item-icon special.
- **[MED] Scene constants** — `macros/scripts/maps.asm`
  - `scene_script ptr, SCENE_CONST` exports named scene IDs (`scene_const`). `SCENE_ALWAYS=-1` for coord events (the behavior already existed).
  - Binary unchanged.
- **[MED] `connection` macro** — `macros/scripts/maps.asm`, `data/maps/attributes.asm`
  - The connection bitmask byte of `map_attributes` is now computed automatically, and the macro enforces N/S/W/E order.
  - Binary unchanged.
  - `dual_connection` now has 3 entries: Route 13 -> Route 14/Lucky Island; Route 35 Coast South -> Olivine/Route 35 Coast North; Cherrygrove Bay -> Train Track Dual/Cherrygrove City.
- **[MED] `paletteswap` data macro** — `macros/scripts/maps.asm`
  - Layout: `db x1,x2, y1,y2, palID; dw outsidePals, insidePals` (NULL = no change). The list ends with `db -1`.
  - At most 8 entries per list, because `wPaletteSwapStates`/`wPaletteSwapInits` use one bit per entry.
  - The palette lists live in the "color" ROMX bank (`SwapColorPalette`).
- **[MED] Object events: `SPRITE_AQUARIUM_MON` uses the same species/form encoding as `SPRITE_MON_ICON`** — `macros/scripts/maps.asm`
  - Item balls now use `SPRITE_BALL_CUT_TREE` + `PAL_NPC_ENV_RED/GREEN/YELLOW`.
  - Fruit trees use `SPRITE_BLANK_FRUIT`. Boulders use `SPRITE_BOULDER_ROCK`.
- **[MED] Setup-script commands added** — `data/maps/setup_script_pointers.asm`, `data/maps/setup_scripts.asm`
  - `$39 SavePrevPalStates` and `$3a ClearSavedObjPals`.
  - `MapSetupScript_Connection` now also runs `BufferScreen`.
- **[LOW] `trainer` macro trainer-palette byte now takes `TRAINERPAL_*` from a separate list** (see IDs section). `Script_loadtrainer` resets it to `TRAINERPAL_NONE`.
- **[LOW] Script fixes**
  - `Script_random16` stored the wrong registers (bug fixed; not used by any script yet).
  - `Script_specialphonecall` no longer clears a second byte (`wSpecialPhoneCallID` is 1 byte).
  - The `pokepic` form handling was simplified.
- **[LOW] `std_scripts`** — `ElevatorButtonScript` no longer plays `SFX_READ_TEXT_2`. Scripts use named scene constants.
- **[LOW] Fossil revival is now a shared script** — `engine/events/fossils.asm` (`AskResurrectFossilScript`)
  - It is a multi-choice menu for Helix/Dome/Old Amber.
  - It is used at the Ruins of Alph once `EVENT_CAN_RESURRECT_FOSSILS_IN_RUINS_OF_ALPH` is set (after all Unown are caught). It uses `wResurrectFossilScript(Bank)`.

### IDs and enums that data depends on (renumbered)

- **[HIGH] Map environments reordered** — `constants/map_data_constants.asm`, `data/maps/environment_colors.asm`
  - Now `TOWN=0, ROUTE=1, ISOLATED=2, INDOOR=3, GATE=4, CAVE=5, DUNGEON=6`. It was TOWN=1, ROUTE=2, INDOOR=3, CAVE=4, ISOLATED=5, GATE=6, DUNGEON=7.
  - New range helpers: `LAST_OUTDOOR_ENV`, `FIRST_INDOOR_ENV`, `FIRST_DIGGABLE_ENV`.
  - The map header's environment byte must be re-mapped.
- **[HIGH] Tileset IDs renumbered** — `constants/tileset_constants.asm`, `data/tilesets.asm`
  - `01` JOHTO_TRADITIONAL, `02` MODERN, `03` COAST(new), `04` OUTLANDS (ex-JOHTO_OVERCAST), `05` ANCIENT, `06` SACRED, `07` BATTLE_TOWER_OUTSIDE, `08` SNOWTOP_MOUNTAIN (moved up).
  - `NO_ROOF_TILESETS=$09`: tilesets 1-8 load map-group roofs.
  - Then `09` KANTO, `0a` KANTO_NORTH, `0b` KANTO_URBAN, … up to `35` KANTO_GYM (53 total).
  - `ECRUTEAK_SHRINE` and `ALPH_WORD_ROOM` were removed. `VOLCANO`, `HIDDEN_GROTTO`, `PEAKS` and `HIDEOUT` were added.
- **[HIGH] NPC palette IDs renumbered** — `constants/sprite_data_constants.asm`, `gfx/overworld/npc_sprites*.pal`
  - `PAL_NPC_x = PAL_OW_x + 1`.
  - Time-of-day palettes, `$00-$1b`:
    - PURPLE and BROWN swapped (03/04). New TAN `$0d`, DARK_RED/BLUE/GREEN/PURPLE `$0e-$11`.
    - ENV_RED/BLUE/GREEN/YELLOW/WHITE `$12-$16`: color 1 is the environment white, used for item balls.
    - SAILBOAT `$17`, RAIN `$18`, SAND `$19`, LEAF_GREEN `$1a`, FARAWAY_ROCK `$1b`.
    - POKE_BALL, DECO_ITEM, KEY_ITEM and MARLON were removed.
  - Single-object palettes `$1c-$32`, adding AQUA_*, EMI, MOLTRES and CAMPFIRE.
  - Copy-BG palettes `$33-$3b`, adding `COPY_BG_WHITE`.
  - All 3 `.pal` sets (normal, darkness, overcast) follow this order.
- **[HIGH] Special sprite IDs moved** — `constants/sprite_constants.asm`
  - `SPRITE_MON_ICON` `$ef` -> `$ee`. New `SPRITE_AQUARIUM_MON=$ef`.
  - New overworld sprites `$cb-$d9`: CHRIS/KRIS/CRYS_RUN, BLANK_FRUIT, BIG_HO_OH, BIG_LUGIA, BETA(+BIKE/SURF/RUN), FLOATING_BALL, SPINARAK_CART, PEARL, PAGODA, CAMPFIRE.
  - Renamed in place: `$b4` BALL_CUT_TREE, `$b5` BOULDER_ROCK, `$c0` ICE_BOULDER_FOSSILS, `$c4` LARRY.
- **[HIGH] Music IDs shifted** — `constants/music_constants.asm`, `audio/music_pointers.asm`
  - `MUSIC_MARINE_TUBE_B2W2` moved to `$70`, so the old `$70..` IDs (DIGLETTS_CAVE_RBY …) are +1 up to where it used to be.
  - `MUSIC_UNDERTALE_MEGALOVANIA` (the last one) was removed.
  - Music-player origin/composer enums lost UNDERTALE/TOBY_FOX.
- **[HIGH] Trainer classes shifted** — `constants/trainer_constants.asm`
  - Order is now `CAL=1 (CHRIS), CARRIE=2 (KRIS), JACKY=3 (CRYS), EUNA=4 (BETA, new)`; then FALKNER… each +1 compared with v3.2.3.
  - `KATY` was replaced by `POKEMANIAC_LARRY` in place. `FIREBREATHER_ASHES` is new.
  - Class-indexed tables (names, pics, palettes, DVs, genders, music, sprites, attributes) all follow this order.
  - The link battle maps player gender to class as `PLAYER_* + 1`.
- **[HIGH] Trainer palettes are a separate enum** — `constants/trainer_constants.asm`, `data/trainers/palettes.asm`
  - `TRAINERPAL_NONE=0`, then SAYO..MINA (Kimono Girls), GAKU/MASA/KOJI, BIKER_DWAYNE/HARRIS/ZEKE and 14 `DARK_*` palettes (numbered 1..).
  - They index the new `CustomTrainerPalettes` table. Before, they continued after the class IDs, e.g. SAYO=`$9a`.
  - This is the `trainer` macro's 8th byte and `loadtrainerwithpal`'s 3rd byte.
- **[HIGH] Trainer party type bits shifted down one** — `constants/trainer_data_constants.asm`
  - `TRNTYPE_NORMAL` was removed. Now `TRAINERTYPE_ITEM=$01, EVS=$02, DVS=$04, PERSONALITY=$08, NICKNAME=$10, MOVES=$20`; before it was `$02..$40`.
  - The party-type byte in `data/trainers/parties.asm` is decoded differently.
- **[HIGH] Held-effect IDs +1** — `constants/item_data_constants.asm`, `data/items/attributes.asm`
  - `HELD_OTHER` was inserted at 1 (for items with no held effect but a non-inert party icon: Lucky Egg, Soothe Bell, Light Ball, Leek, mail, …), so every `HELD_*` from `HELD_BERRY` on is +1.
  - `HELDTYPE_ITEM/INERT_ITEM/MAIL/BERRY` pick the party-menu icon.
- **[HIGH] Ability IDs shifted** — `constants/ability_constants.asm`
  - `BAD_DREAMS` was inserted after RECKLESS, `IRON_BARBS` after SAND_FORCE, `FLUFFY` after CORROSION, `WIND_RIDER` after QUICK_DRAW; `MEGA_SOL` was appended. `NUM_ABILITIES` is 160.
  - Base stats, trainer data and ability names/descriptions are indexed by ability ID.
- **[HIGH] Engine flags, spawns and fly points shifted** — `constants/engine_flags.asm`, `constants/map_data_constants.asm`, `data/events/engine_flags.asm`, `data/maps/spawn_points.asm`, `data/maps/flypoints.asm`
  - `ENGINE_FLYPOINT_POKEMON_LEAGUE`, `SPAWN_POKEMON_LEAGUE` (Route 26, 8,6) and `FLY_POKEMON_LEAGUE` were inserted after INDIGO, so every later engine flag, spawn and fly ID is +1.
  - Engine flags are 2-byte indexes in scripts, so every script that names a shifted flag changes.
- **[HIGH] `wPlayerState` values** — `constants/ram_constants.asm`
  - Now `NORMAL=0, RUN=1 (new), BIKE=2, SKATE=3, SURF=4, SURF_PIKA=5`. Before it was 0/1/2/4/8 (bit-like).
  - `PlayerStateSprites` is now a flat `NUM_PLAYER_GENDERS × NUM_PLAYER_STATES` table.
- **[MED] `PLAYER_BETA=3`** — `constants/ram_constants.asm`
  - Adds a 4th player choice with default name "Krys", purple, Trainer House opponent Euna (`OPP_EUNA` inserted before `OPP_EN`).
  - Tables indexed by gender grew to 4: `data/player/*.asm` (graphics, card pics, backpics, pack gfx/pals, Pokégear pals, fishing gfx, state sprites, default names).
- **[MED] Collision constants** — `constants/collision_constants.asm`, `data/collision/collision_permissions.asm`
  - New glow tiles:
    - `COLL_CAMPFIRE_GLOW $03`, `AQUARIUM_GLOW $04`, `LANTERN_GLOW $05`, `LAVA_GLOW $06`, `SHRINE_LAMP_GLOW $08`: land.
    - `COLL_CAVE_MOUTH_GLOW $74`: a down-warp edge, like `WARP_CARPET_DOWN`.
    - `COLL_LADDER_GLOW $75`.
    - `COLL_RIGHT_WALL_GLOW $b8` / `LEFT_WALL_GLOW $b9`.
  - `COLL_STONE_WARP $61`: stone-table trigger, like `COLL_HOLE`.
  - `COLL_CHERRY_LEAVES $d0`: a wall; blossoms settle on it.
  - `COLL_OVERHEAD $1c` was renamed `COLL_VISUAL_GRASS`: it sets the grass-priority flag.
- **[MED] Radio channel IDs -1** (Pokédex Show removed); `RadioChannelSongs` lost its entry.
- **[MED] Other enum changes**
  - `PARTYMENUACTION_GIVE_MON_FEMALE` removed (later actions shift).
  - `RELEASE_*` reordered: OK, EGG, then `CANNOT_RELEASE` codes EGG_BEFORE_TOGEPI, LAST_HEALTHY, EMPTY; `RELEASE_HM` removed.
  - `CGB_*` layouts: -SUMMARY_SCREEN_HP_PALS, -MOVE_LIST, +TRADE_PIC, +TRADE_BG.
  - `PAL_BTLCUSTOM_ZAP_CANNON` inserted at `$31` (stat palettes shift +1).
  - `SUMMARY_TILE_*` renumbered: one shared arrow tile, PP tiles at `$41`.
  - `ERR_*` crash codes: +RST_38, PC_BOX_OLD/ZERO/COLLISION, WINDOW_OVERFLOW/UNDERFLOW, PEBKAC.
  - `SOUND_REST` flag renamed to `SOUND_CRY`.
- **[LOW] Sprite-movement enums**
  - `SPRITEMOVEDATA_*` appended (`$30-$38`): BIG_HO_OH, BIG_LUGIA, ADMIN_MEOWTH, SPINARAK_CART, RATTATA_BACK, AQUARIUM_TOP/BOTTOM, PAGODA_LEFT/RIGHT.
  - `SPRITEMOVEFN_*`, `OBJECT_ACTION_*`, `FACING_*` and `STEP_TYPE_*` were renumbered: CUT_TREE, POKECOM_NEWS and MICROPHONE handlers were removed; BIG_HO_OH/LUGIA and HALF steps added.
  - These values live in the object structs inside the save, so a v3.2.3 save's objects would misbehave.

### Save data and RAM layout

- **[HIGH] The save block keeps its size, but the meaning of some bytes changed; `SAVE_VERSION` is still 10** — `ram/wramx.asm`, `ram/sram.asm`, `constants/misc_constants.asm`
  - `sPlayerData`/`sMapData`/`sPokemonData` are straight copies of `wPlayerData`/`wCurMapData`/`wPokemonData`, and their sizes did not change.
  - Contents that changed:
    - `wPaletteSwapAddress(dw)`, `wPaletteSwapStates`, `wPaletteSwapInits` replace `ds 4` after `wTimeOfDayPal`.
    - `wFollowInSync` replaces `wUndergroundSwitchPositions`.
    - The former `ds 64` after `wEmotePal` now holds: `wOvercastRandomDay`, `wOvercastCurIntensity`, `wOvercastRandomMaps` (4 × {intensity, group, number}), `wNeededMonPalLight`, `wNeededPalType`, `wLoadedObjPalType`, `wLoadedObjPalGlows[8]`, `wLoadedObjPalPrevGlows[8]`, `wNeededObjPalGlow`, `wPrevNeededObjPalGlow`, `wObjectGlowTypes[13]`, `wObjectPrevGlowTypes[13]`, `wObjectGlowFadeActive`, `ds 2`.
- **[HIGH] Saved values that were re-encoded**
  - `wPlayerState` (enum above).
  - `wVisitedSpawns` bits: SPAWN_POKEMON_LEAGUE inserted.
  - `wEventFlags`: `NUM_EVENTS` is still 2303 and the slots are almost all unchanged; only `EVENT_BEAT_FIREBREATHER_DICK` moved (1070 -> 2268), and slots 610-620 changed meaning (see the maps section and `dev_changes/names.md`).
  - Map group/number IDs in `wMapGroup`, `wBackupMap*`, `wLastSpawnMap*` and `wDigMap*`: the map list changed.
  - `wDailyPhoneItemFlags` bit 8 is now Tiffany's Fairy Feather.
- **[MED] Scene variables renamed** — `ram/wramx.asm`, `data/maps/scenes.asm`
  - `wFarawayIslandSouthSceneID` and `wGoldenrodUndergroundSwitchRoomSceneID`, in the same slots. The scene map list follows the new map IDs.
- **[MED] Options** — `ram/wram0.asm`, `constants/ram_constants.asm`, `data/options/default_options.asm`
  - `wOptions3` (saved separately as `sOptions3`) bits 1/2 are now `NICKNAMES_ALWAYS`/`NICKNAMES_NEVER` (neither = Ask).
  - The DEBUG default is NICKNAMES_NEVER. The corrupt-save reset copies `DefaultOptions` starting at `wOptions3`.
- **[MED] `wOverworldMapBlocks` shrank from 1326 back to 1300 bytes** — `ram/wram0.asm`
  - Maps must fit `(w+6)*(h+6) <= 1300`. Navel Rock was split; Route 41 is the largest at 1254. A port may keep a larger buffer.
- **[LOW] WRAMX scratch unions**
  - `wBuffer1-6` became named per-feature unions: HP buffers, catch rate, Kurt, restart clock, Forewarn, buy/sell price, etc. (#1360).
  - New `wOptionsMenu*`, `wResurrectFossilScript*`, `wAbilityFlags`, `wAbilityDisplaySpeed`, `wPalFadeTotalSteps`, `wPalFadeStepValue`, `wPalGlow{Red,Green,Blue}Adjustment`, `wSpecialPalStart/Count`.
  - `wWeatherScratch` is 16 bytes larger.
- **[LOW] WRAM0/HRAM reshuffle**
  - The `Video` section (`wBGMapBuffer*`) moved; `wMPNotes` (music player) moved from WRAMX 2 into WRAM0 (`3*256`).
  - `wOverworldMapAnchor`, `wMetatileStanding*` and `wPlayerStepDirection` moved to HRAM (`hOverworldMapAnchor`, `hPlayerStepDirection`, …).
  - New `hLineOfSight*`, `hTrainerSeeing` and `hStreamMapWalkedPatch`. `wSPBuffer` moved to WRAM0.
  - The memory-game RAM was removed.

### Map engine: palettes, weather, overcast, glow

- **[HIGH] Overcast "weather everywhere"** — `engine/events/overcast.asm`, `data/maps/overcast_maps.asm`, `engine/events/weather.asm`
  - Nothing is overcast until `EVENT_AZALEA_TOWN_SLOWPOKES`.
  - A generic overcast applies to outdoor maps (env < `FIRST_INDOOR_ENV`). When `wCurDay` changes, it rolls 2 Johto and 2 Kanto maps (or "areas": aliased groups of maps such as `AREA_ROUTE_16`) with random intensity OVERCAST/RAIN/THUNDERSTORM.
  - Fixed rules:
    - Azalea/Route 33: Sun, Tue, Thu, Sat; rain.
    - Lake of Rage/Route 43: Mon, Wed, Fri, or always until the Rockets are beaten; thunderstorm.
    - Goldenrod/Route 34/Magnet Tunnel West while the Rockets hold Goldenrod: rain. Stormy Beach: always, thunderstorm.
    - Routes 9/10 North until Zapdos is caught: rain/thunderstorm.
  - Overworld rain or thunder now follows the intensity instead of the old 25% random roll.
- **[HIGH] Special BG palette table format** — `data/maps/palettes.asm`, `engine/tilesets/tileset_palettes.asm`, `maps/*.pal`, `gfx/tilesets/*.pal`
  - Each entry: `db PAL_FOR_{MAP,LANDMARK,TILESET,OVERCAST,DARKNESS}`, then key bytes, then `db (type<<6)|(firstPal<<3)|(count-1)`, then `dw source`.
  - Types: `PALTYPE_SINGLE=0`, `TIMEOFDAY=1` (4×count palettes: morn, day, nite, eve), `TIMEWEATHER=2` (4×count regular then 4×count overcast), `SPECIAL=3` (code handler: PokeCenter, Mart, MagnetTrain, HiddenGrotto).
  - The `.pal` sources now contain only the customized subset, not 7 or 8 palettes. `*_overcast.pal` files are new.
- **[HIGH] Palette-swap rectangles** — `home/palette_swap.asm`, `engine/gfx/color.asm`, `data/tileset_palettes.asm`, `gfx/tilesets/palette-swap/*.pal`
  - The CMDQUEUE callback installs a list. Each entry swaps BG palette slot `palID` between its "outside" and "inside" palette lists depending on the player's X/Y.
  - Each list is 8 palettes: 4 time-of-day regular + 4 overcast.
  - State bits live in `wPaletteSwapStates`/`Inits`. The swap fades with the palette-fade system.
  - It runs from `CheckTileEvent` (`HandlePaletteSwap`) and on full palette loads.
- **[HIGH] Object glow** — `data/collision/glow_collisions.asm`, `data/collision/glow_adjustments.asm`, `engine/gfx/sprite_palettes.asm`, `engine/overworld/events.asm` (`UpdateObjectGlowPals` each frame)
  - An object standing on a glow collision gets `OBJ_GLOW_{AQUARIUM,LANTERN,DRAGON_SHRINE,LAVA}`: additive RGB (2,5,9)/(5,4,2)/(0,4,4)/(8,1,0) on its palette. `OBJ_GLOW_DAY`/`NITE` use the day/night palette instead.
  - Changes fade in and out. The glow type is tracked per object struct and per loaded OBJ palette slot.
- **[HIGH] Weather OBJ palette slot 6 is reserved** — `constants/sprite_data_constants.asm` (`PAL_OW_WEATHER EQU 6`), `engine/gfx/sprite_palettes.asm`
  - Rain uses PAL_OW_RAIN, sand uses SAND, cherry blossoms use PINK, snow is all white.
  - Objects already using slot 6 are moved first (`CheckForUsedObjPals`).
- **[MED] New weather: cherry blossoms** — `constants/weather_constants.asm` (`OW_WEATHER_CHERRY_BLOSSOMS`), `engine/overworld/weather.asm`, `data/sprites/weather.asm`, `gfx/overworld/cherry_blossom.png`
  - Always in Cherrygrove City until the Mystery Egg is given to Elm; afterwards 10% in Cherrygrove City/Bay.
  - Petals settle on `COLL_CHERRY_LEAVES` tiles.
  - Snow now also falls on the Silver Cave Room 3 peak.
- **[MED] Weather intensity constants** — `OVERCAST_INTENSITY_OVERCAST/RAIN/THUNDERSTORM`. New overcast IDs `ROUTE_10_OVERCAST` and `GENERIC_OVERCAST`.
- **[MED] Connections without palette fade** — `data/maps/no_connection_palette_fades.asm`, `engine/overworld/warp_connection.asm`
  - Listed pairs (in both directions; currently Rugged Road N<->S) set `SKIP_MAP_CONNECTION_PAL_FADE_F` and apply the destination palettes immediately.
- **[MED] Dual object palettes** — `data/maps/dual_obj_pals.asm`
  - Per map, two `PAL_OW` palettes are loaded into adjacent OBJ slots for `NEXT_PALETTE` facings: Tin Tower Roof RED+GREEN (Big Ho-Oh), Lugia Chamber ENV_WHITE+BLUE (Big Lugia), Shamouti Island GREEN+BROWN (Alolan Exeggutor).
- **[MED] Map name signs** — `data/maps/map_name_signs.asm`, `engine/events/map_name_sign.asm`, `gfx/signs/*.png`, `gfx/signs/signs.pal`
  - Sign frames are now individual LZ-compressed graphics behind a `fardw` table. `SignPals` has one palette per sign.
  - Frames no longer come from the font bank.
  - New: no sign on `CHERRYGROVE_TRAIN_TRACK_DUAL`. The `UNDERGROUND` landmark was renamed `UNDERGROUND_PATH`.
- **[MED] Roofs** — `engine/tilesets/mapgroup_roofs.asm`, `data/maps/roofs.asm`, `gfx/tilesets/roofs*.pal`
  - Roof GFX: `ROOF_STATUE` removed; `ROOF_PARK` and `ROOF_SINJOH` added. The map-group assignments changed (Ecruteak=PARK, Violet=NEW_BARK, Goldenrod=PARK, Indigo=NEW_BARK, Ruins of Alph=VIOLET, …).
  - `RoofPals` and `OvercastRoofPals` have `NUM_MAP_GROUPS+1` entries (group count grew by 2).
- **[MED] Coast-sand tracks work on any tileset** — `constants/tileset_constants.asm`, `home/map.asm` (`_LoadCoastSandGFX`), `engine/overworld/events.asm`
  - 7 shared tiles `COAST_SAND_TILE..BIKE_V` at VRAM1 `$f0-$f6`, from `gfx/tilesets/animations/coast_sand`. It is no longer Shamouti-specific (`$58-$5d`).
- **[MED] Map palette constant `PALETTE_INDOOR`** was added (after EVE). `TilesetBGPalette` holds 5×8 + 4 palettes: morn, day, nite, eve, indoor, water.
- **[LOW] Faster step rendering** — `engine/overworld/stream_map_part.asm`
  - Walking streams only the entering edge and the walked 2×4 patch into the VBlank queue. `wTilemap`/`wAttrmap` are rebuilt only by `LoadMapPart`. This is only an implementation detail.

### Tilesets and tile animation

- **[HIGH] Tileset animation table format** — `data/tileset_anims.asm` (moved out of the engine), `engine/tilesets/tileset_anims.asm`
  - `tileframe Func, $b:xx` emits `dw vramAddr|bank, dw Func`: tile id < $80 -> vTiles2, >= $80 -> vTiles1; bit 0 = VRAM bank.
  - Frame data now lives inside the tileset's compressed graphics (functions copy from other VRAM tiles) or is embedded next to the function, instead of being passed as frame pointers.
  - A typical table is 8 frame slots + `StandingTileFrame8` + `DoneTileAnimation`.
  - Several tilesets share one table, e.g. `TilesetJohtoTraditionalAnim` = Outlands/Ancient/Sacred/BattleTowerOutside.
- **[HIGH] Tileset list and graphics sharing** — `data/tilesets.asm`
  - The 18-byte header is unchanged. The anim pointer is still a `dw`, now asserted to be in `_AnimateTileset`'s bank.
  - Tilesets share GFX0 (`johto_common`, `kanto_common`) and GFX1/2 (e.g. COAST reuses MODERN's GFX, SACRED reuses TRADITIONAL's) while having their own metatiles, attributes and collision. Each gets its own palettes and anim table.
- **[MED] New animation routines**
  - AnimateRainTiles (tile `$1c`), Buoy/KantoBuoy/Rock/TinyRock, TubeLight flicker, LampLight (flickers only at eve/nite), Turbine, Fire (charcoal kiln), Torch, Small/Big/Double stars (Karen), 4-part TowerPillar, Fountain, LavaBubble, CaveWater, `ScrollFourTilesUpDownLeftRight` (currents), GameCorner sign, WaterBubble, Faraway water.
  - Palette effects: JudgeMachine tiles/`CycleJudgeMachinePalette`, `FlickeringCaveEntrancePalette`.
  - The old `ScrollTileRightLeft`/`ScrollTileDown` were removed.
- **[MED] Field-move metatile tables are keyed by the new tileset IDs** — `data/collision/field_move_blocks.asm`
  - Cut-grass and whirlpool replacement blocks per tileset. New entries for COAST/OUTLANDS/ANCIENT/KANTO_NORTH/URBAN.

### Overworld objects, sprites and movement

- **[HIGH] Two-palette Pokémon icons and overworld mons** — `constants/sprite_data_constants.asm` (`ow_mon_pal_const`), `engine/gfx/sprite_palettes.asm` (`CopyMonIconLightColor`), `data/pokemon/overworld_icon_pals.asm`
  - For `SPRITE_MON_ICON`/`SPRITE_AQUARIUM_MON`, palette value `p` decodes as `p-1 = (lightPal<<4)|mainPal`, where both nybbles index RED..TAN (0-13).
  - Color 1 of the main palette is replaced with color 2 of `lightPal`. `PAL_MON_X` alone = `PAL_MON_TAN_X`.
  - `OverworldMonIconColors` is now 2 bytes per species (normal, shiny), each a `PAL_MON_*` byte. It used to be 1 byte of `dn normal, shiny` `PAL_OW` nybbles.
- **[HIGH] Object flag bits** — `constants/map_object_constants.asm`, `engine/overworld/map_objects.asm`
  - flags2: `IN_GRASS`(3) replaces OVERHEAD; `BG_OFFSET`(4) replaces USE_OBP1; `UNDER_TILES`(7) is new and sets OAM priority behind BG.
  - Palette byte: `BG_ALIGNED`(4) is new.
  - OAM Y offset: +12 normally, +16 if BG_ALIGNED, +8 if BG_OFFSET, +20 if both.
  - `IN_GRASS` is set on VISUAL_GRASS, LONG_GRASS and TALL_GRASS.
  - The `SpriteMovementData` source is now field-per-line; binary is still 6 bytes.
- **[HIGH] Running sprite** — `engine/overworld/player_movement.asm`, `engine/overworld/events.asm`, `data/player/state_sprites.asm`
  - With running shoes, the player enters `PLAYER_RUN` and uses a `*_RUN` sprite. It reverts to NORMAL when stopping.
  - Bike and skate stop running.
- **[MED] Half steps** — `engine/overworld/movement.asm` (`HalfStep`), `engine/overworld/map_objects.asm` (`STEP_TYPE_HALF1/NPC_HALF2/PLAYER_HALF2`)
  - The first `half_step_*` moves the sprite offset by 8px over 8 frames, with no tile change.
  - The next one does the real tile move over 16 frames while undoing the offset.
  - Used by the Azalea Gym Spinarak cart puzzle.
- **[MED] Big two-palette sprites** — Big Ho-Oh and Big Lugia (`SPRITEMOVEFN/OBJECT_ACTION/FACING_BIG_HO_OH/LUGIA`) with `NEXT_PALETTE` facings. They rely on `DualObjectPalettes`.
- **[MED] Cut trees and fruit trees are separate sprites** — `FACING_CUT_TREE`, `SPRITEMOVEFN_CUT_TREE` and `OBJECT_ACTION_CUT_TREE` were removed. `SPRITE_BALL_CUT_TREE` stands still; the fruit facings' tile offsets changed (Apricorn `$05`, Berry `$04`, Picked `$07`).
- **[MED] Trainer line of sight is blocked by other objects** (e.g. Strength boulders) — `home/trainers.asm` (`FacingPlayerDistance` returns distance and direction in b/c), `hLineOfSight*`.
- **[MED] Follow-in-sync** — `wFollowInSync` lets a follower move in lockstep with the player (the Azalea Gym cart).
- **[MED] Rooftop sprites and aquariums**
  - `SPRITE_PAGODA` with `PAGODA_LEFT/RIGHT` movement lets the player walk behind pagoda roofs.
  - `COPY_BG_WHITE` copies BG colors 0 and 3.
  - Aquarium top/bottom objects use `AQUA_*` palettes and glow.
- **[LOW] Stone tables** also trigger on `COLL_STONE_WARP`. The object must be STANDING before the collision is checked.
- **[LOW] Removed movement handlers** — PokeCom news and microphone animated objects. The `SPRITEMOVEDATA` IDs remain but now use the standing function.

### Battle engine and mechanics

- **[HIGH] Ability property flags table** — `data/abilities/flags.asm` (`AbilityFlags`), `constants/battle_constants.asm`
  - One byte per ability, with bits `NO_COPY` (Role Play/Receiver/Entrain), `NO_TRACE`, `NO_SWAP` (Skill Swap/Wandering Spirit), `NO_SUPPRESS` (Gastro Acid/Mummy/NGas/Simple Beam), `IGNORABLE` (Mold Breaker), `NO_TRANSFORM`, `NO_INTIMIDATE`.
  - Replaces `mold_breaker_suppressed_abilities.asm` and `no_intimidate_abilities.asm`.
  - Trace, Skill Swap, Neutralizing Gas and Intimidate all consult it.
- **[HIGH] New abilities** — `engine/battle/abilities.asm`, `home/battle.asm`, `data/moves/wind_moves.asm`
  - `BAD_DREAMS`: 1/8 max HP each turn to a sleeping foe.
  - `IRON_BARBS`: contact damage of 1/8 of the attacker's max HP, blocked by Magic Guard.
  - `FLUFFY`: ×2 from Fire, ×0.5 from contact; they stack; ignorable.
  - `WIND_RIDER`: immune to wind moves and gains +1 Atk (a "doesn't affect" message).
  - `MEGA_SOL`: `GetSolarizedWeather` treats weather as sun for the user's damage calc and skill checks (Fire/Water modifiers, Solar Beam charge, etc.).
- **[HIGH] Binding Band now latches when the trap is set** — `engine/battle/effect_commands.asm` (`BattleCommand_traptarget`), `engine/battle/endturn.asm` (`HandleWrap`)
  - Bit 3 of the wrap-turn counter stores "Binding Band held when inflicted" (1/6 instead of 1/8 damage). Turns are in bits 0-2.
  - The turn count is the `HELD_PROLONG_WRAP` item parameter (7) if held; otherwise 4-5.
  - Substitute no longer blocks the trap (it uses `CheckSubHit`) or the end-of-turn damage; it only skips the animation.
- **[MED] Move state byte** — `wMoveState` (`MOVESTATE_PHYSICAL/SPECIAL/IGNOREABIL/ENDED` + `OPP_*`)
  - Tracks category for Counter/Mirror Coat and Mold Breaker per turn. `MOVEHIT_*` are now masks.
  - Counter/Mirror Coat now return 1 damage when hit for 0.
- **[MED] Damage and effect changes**
  - Facade ignores the burn halving.
  - Will-O-Wisp (`DoBurn`) no longer gets STAB.
  - Infiltrator and sound moves hit through Substitute for damage.
  - Effect Spore sleep stops multi-hit moves.
  - Cursed Body doesn't activate through Substitute.
  - A fainted Mold Breaker user stops suppressing.
  - Mental Herb curing Encore no longer forces the move; Encore ticks like Disable.
  - Moody triggers Eject Pack.
  - Lum Berry activates on confusion.
  - Powder moves vs Sap Sipper fixed; Hail+Sandstorm double damage fixed.
  - Run Away's faithful-only check was removed.
  - The Flare Blitz crash was fixed properly (the extra `endmove` was removed).
- **[MED] Probability checks are exact** — the last `cp N percent` rolls became `BattleRandomRange`, so 20%/33%/50%/25% chances are exact, not approximations over 256.
- **[MED] Affection levels** — `data/battle/affection_thresholds.asm`: levels at happiness 0/180/220/255 (`AFFECTION_THRESHOLD_1/2`). Same values as before, now a shared table.
- **[MED] Automatic battle weather** — `engine/battle/core.asm` `AutomaticBattleWeather`
  - Hail on Snowtop Mountain inside and the Silver Cave Room 3 peak.
  - Sandstorm on Rugged Road South.
  - Rain when the overcast intensity is not 0.
- **[MED] Ability announcements** — `engine/battle/ability_gfx.asm`
  - `wInAbility` is a bitfield (active, player/enemy pending, player/enemy visible).
  - New `ShowPendingUserAbility` / `BeginAndShowOpponentAbility`. Trace and Skill Swap show the swapped abilities.
  - Status problem texts no longer wait for a button.
  - Focus Sash/Band play an item animation.
- **[LOW] Overworld ability effects** — `engine/overworld/wildmons.asm` (`ApplyAbilityEffectsOnEncounterMon`)
  - The Pressure/Hustle/Vital Spirit branch was rewritten to "50%: +round(level/8), at least 1" (was +1). As written, it stores round(c/8) into `c` (the lead mon's level), so check what the caller does with it before copying the behavior.
  - Roaming mons now keep and use their stored form (`wRoamMon*Form`).
- **[LOW] HP bar color comes from exact HP** — `engine/pokemon/health.asm` `GetHPPalFromHP`: the color is computed from HP/maxHP, not bar pixels, everywhere.
- **[LOW] Move data tweaks (non-faithful)** — Iron Tail 80% accuracy, X-Scissor high crit, Crabhammer 95%, Iron Head/Moonblast secondary chance lowered, Growth is Grass type. Slicing list: +Dragon Claw, Shadow Claw, Metal Claw.

### Items, Pokémon and event data formats

- **[HIGH] Item effect tables are indirect** — `data/items/effects.asm` (`ItemEffects`, 1 byte `ITEMEFFECT_*` per item), `data/items/key_effects.asm` (`KeyItemEffects`, 1 byte `KEYITEMEFFECT_*`), `engine/items/item_effects.asm`
  - Replaces the pointer-per-item tables. 26 item effect routines, 16 key-item effect routines.
- **[HIGH] Wild grass encounter data** — `constants/pokemon_data_constants.asm`, `engine/overworld/wildmons.asm`
  - Grass entry is now `map_id(2) + 1 rate byte + 3 times × 7 mons × 3 bytes` = 66 bytes.
  - It was 68: `map_id + 3 × (rate byte + 7 mons)`, with a separate rate for morn, day and nite.
  - On load, the one rate byte is copied to all of `wMorn/Day/NiteEncounterRate`.
  - The water entry layout (`2 + 1 + 3×3`) is unchanged.
  - Offsets used by phone rare-mon lookups changed accordingly.
- **[HIGH] Fishing** — `data/wild/fish.asm`, `engine/events/fish.asm`, `engine/events/overworld.asm`
  - Species 0 no longer means "Corsola in morn/day, Staryu in eve/nite". Shore groups now use CORSOLA, and `FISHGROUP_STARYU` was added (Route 41).
  - After "Not even a nibble!" the game asks "Keep fishing?".
  - Suction Cups and Sticky Hold still give 2 attempts (`TryFishEncounter`).
- **[HIGH] Cry data** — `data/pokemon/cries.asm`, `home/cry.asm`, `constants/pokemon_data_constants.asm`
  - `mon_cry` = `db cryIndex, dw pitch, dw length` (`MON_CRY_LENGTH=5`; was 6 with a `dw` index).
  - 38 new `CRY_*` (AZURILL..ANNIHILAPE). Gen 3+ species now point at their own cries instead of pitch-shifted Gen 2 cries.
- **[MED] NPC trade struct** — `constants/npc_trade_constants.asm`, `data/events/npc_trades.asm`: the OT name field is 7 bytes (`PLAYER_NAME_LENGTH-1`), so the struct is 1 byte shorter.
- **[MED] Battle Tower trainers** — `data/battle_tower/classes.asm`: 9-byte name + class = 10 bytes per entry (was 11).
- **[MED] Wonder Trade OT names** — `data/events/wonder_trade/ot_names.asm`: 7 bytes each (was 8).
- **[MED] Trade Pokémon struct** — `macros/ram.asm` `trademon`: `CaughtData` -> `CaughtBall`. The trade screen shows the actual caught ball; OT gender is no longer carried, and caught-data bit 7 is unused.
- **[MED] Item changes** — `PINK_BOW` was replaced in place by `FAIRYFEATHER` (same ID), and the Tiffany engine flag was renamed. TM/HM reuse no longer restores PP (#1624).
- **[MED] Happiness** — `engine/events/happiness_egg.asm`
  - `ChangeHappiness` treats table values >= `$80` as negative (was `$64`, so +100..+127 changes now apply as gains).
  - New `GetSelectedPokemonHappiness` (Goldenrod check after party selection).
- **[MED] Item Maniac quantity selling** — `engine/events/item_maniacs.asm`: new specials to pick a quantity (capped at the Bag count), multiply the price, and take N items.
- **[LOW] Initial events** — `data/events/initialize_events.asm`: adds `EVENT_BETA_IN_NAVEL_ROCK` and `EVENT_BURNED_TOWER_FIREBREATHER_DICK_ASHES`; renamed flags.
- **[LOW] Removed data** — the memory game and `data/party_menu_qualities.asm` (moved into the party-menu engine).

### Menus and screens

- **[HIGH] Options menu rewrite** — `engine/menus/options_menu.asm`, `options_menu_shared.asm`, `initial_options_menu.asm` (replaces `init_options.asm`), `data/options/*.asm`, `gfx/options/*`
  - One scrollable list of 13 options with a description box: Text Speed, Text Autoscroll, Frame, Typeface, Keyboard, Sound, Battle Effects, Battle Style, Nicknames (new: Ask/Yes/No), Running Shoes, Turning Speed, Clock Format, Pokédex Units.
  - Initial options: a scrollable list of 11 with descriptions: Natures, Abilities, Phys/Spcl split, EV gain, Experience gain, Affection bonus, RTC, Perfect stats, Traded mon obey, Evolve in battle, Color variation.
  - The underlying option bit layouts are unchanged except `wOptions3`.
- **[HIGH] Nickname option behavior** — `engine/pokemon/caught_data.asm`, `engine/pokemon/breeding.asm`, `engine/items/item_effects.asm`: the nickname prompt after catching, hatching or receiving a Pokémon is skipped (NEVER) or forced (ALWAYS).
- **[MED] Fourth player choice (Beta/Krys)** — `engine/menus/intro_menu.asm`, `engine/gfx/player_gfx.asm`, `engine/items/pack.asm`, `engine/pokegear/pokegear.asm`
  - The gender menu has 4 entries. New back pic, card pic (Euna), Bag graphics `pack_b0-5`, Pokégear palette `pokegear_b`, and fishing/surf-fish sprites.
- **[MED] Party-menu minis** — `engine/gfx/mon_icons.asm`, `data/sprite_anims/*`, `gfx/stats/held_items.png`
  - 5 OAM objects per party mon (`MINI_OAM_COUNT`).
  - Held-item icon by type: item, inert item, mail, berry. The framesets are PARTY_MON / WITH_ITEM / INERT_ITEM / MAIL / BERRY; the FAST variants were removed.
- **[MED] Summary screen**
  - Shows Hidden Power's real type. Hides 1/2/H when abilities are off.
  - One arrow tile. The "PP" label uses the right typeface and sits 4px closer to the numbers (`wSummaryScreenPPTileBuffer`).
  - Red FNT icon; the TOX-vs-FNT bug was fixed. Experience bar fixed.
  - Uses `<SHINY>`. It no longer uses the CGB layout system.
- **[MED] Judge Machine redesign** — `engine/events/judge_machine.asm`, `gfx/stats/judge.{tilemap,attrmap}` -> `.bin`, `judge_stats.png`
  - Summary-page style, animated screen, star when modern EVs are maxed. `hJumpFunction`.
- **[MED] New trade animation** — `engine/movie/trade_animation.asm`, `macros/scripts/trade_anims.asm`, `gfx/trade/*`
  - Mobile-adapter-style UI (by Zumi) with new `tradeanim_prepare_player_ball` (`$30`) and `tradeanim_prepare_ot_ball` (`$31`) commands.
  - New `background.{tilemap,attrmap,pal}` and `bubble.pal`. `ball.png` was removed; the actual ball is used.
- **[MED] Pokégear**
  - Phone scrolling is limited to the number of contacts (`wPokegearPhoneMaxContact`).
  - The Kanto map appears once Indigo Plateau or Pokémon League Gate is visited.
  - The Pokémon League flypoint has a special short name.
- **[MED] Bill's PC**
  - Releasing HM users is allowed. Eggs can be released after the Mystery Egg hatches.
  - The preview refreshes after deposit or withdraw. Box errors are distinguished (crash codes).
- **[MED] Title screen** — `engine/movie/title.asm`, `gfx/title/*`
  - Hovering Unown, redrawn crystal, `suicune_unowns` 2-bank tileset, rendered version string, "TM" restored.
  - The splash copyright is rendered from `data/copyright.asm`.
- **[LOW] Naming screen** — colored gender and shiny tiles (reusing the typeface's tiles in dark/light colors); white ball icon for box names.
- **[LOW] Evolution animation** — a spotlight effect (`gfx/evo/spotlight.*`); the large bubble was removed.
- **[LOW] Trainer Card** — the pic reuses the middle 5×7 tiles of the trainer pic (the separate card pics are gone). Money display fixed near ¥1,000,000.
- **[LOW] Minigames** — the Unown puzzle borders and cursor are 1bpp. The memory game was removed.
- **[LOW] Music player** — animated keyboard (`hNextMPState`). The notes buffer moved to WRAM0.
- **[LOW] Crash screen** — `engine/movie/bsod.asm`: `rst $00` and `rst $38` both crash (the predef system is gone), with new messages (window underflow, PEBKAC, 3 PC-box errors).

### Graphics asset formats and palettes

- **[HIGH] Every compressed graphic is LZP** (see the compression section). Mini, icon and item icon PNGs keep their dimensions (16×32 minis and icons) but were redrawn: 822 files for minis/icons, and item corners cleaned up.
- **[HIGH] Overworld palette files** — `gfx/overworld/npc_sprites.pal`, `npc_sprites_darkness.pal`, `npc_sprites_overcast.pal`, `npc_single_object.pal`
  - The order and count now follow the new `PAL_OW_*`: 28 time-of-day palettes × 4 times, then 23 single-object palettes.
- **[MED] Tileset palette sources** — `gfx/tilesets/*.pal`, `maps/*.pal`
  - Subsets only. New: `hideout`, `volcano`, `port`, `sprout_tower`, `hidden_grotto` (day + nite ×7), `fuchsia_aquarium`, `violet_ecruteak_overcast`, and `*_overcast.pal` per map.
  - `gfx/tilesets/palette-swap/*.pal`: 8 palettes each (4 regular + 4 overcast).
- **[MED] New stat and menu graphics**
  - `gfx/stats/held_items.png` replaces `item.png`/`mail.png`. `gfx/stats/shiny.png`.
  - Per-page summary palettes (`blue/green/orange/pink/egg_page.pal`, `summary_sprites.pal`, `blue_hp_bars.pal`, `ev_iv_cycle.pal`).
  - `gfx/options/{edge.png, options_bg.pal, initial_options_bg.pal}` replace `gfx/new_game/init_bg.*`.
- **[MED] Map-name sign graphics** — `gfx/signs/*.png` (now LZP, plus a new `painting.png`) + `signs.pal`.
- **[MED] Custom trainer palettes** — `gfx/trainers/{kimono_girl_*,elder_*,biker_*,dark_*}.pal` (27) for `TRAINERPAL_*`, plus `euna`, `larry` and `firebreather_ashes` pics and palettes.
- **[LOW] Font** — every typeface PNG was edited: `<BOLDH>` at `$cb`, Unown font half-closed eyes. `gfx/font.asm` no longer includes sign frames and adds `ShinyIconGFX`.
- **[LOW] Monochrome build** — uses the higher-contrast DMG palette (`macros/monochrome.asm`).

### Audio engine and data

- **[HIGH] Cries can live in any bank** — `audio/cry_pointers.asm` (`Cries`: `dba` = bank + pointer, 3 bytes per entry), `audio/engine.asm` `_PlayCry`
  - New ROM sections "Custom Cries", "Siren Cries 1" and "Siren Cries 2".
- **[HIGH] Siren-generated cries use channel 7 (wave)** — `audio/siren-cries/*.asm` (33), `audio/custom-cries/*.asm` (5: Wynaut, Leafeon, Glaceon, Porygon-Z, Sylveon)
  - Cries are `channel_count 3` over ch5/ch7/ch8 with SFX-style `square_note` on the wave channel: volume in the high nybble, waveform in the low nybble.
  - Old cries used only 5/6/8. The cry engine must support the wave channel.
- **[MED] Rests and channel stop reworked** — `audio/engine.asm`
  - `ClearChannel` was removed. Rests now set envelope-up plus a restart per channel; ch3 rests mute via `rAUD3LEVEL`.
  - The ch3 DAC is turned on at init and cycled in `ReloadWaveform`.
  - Duty writes no longer preserve the length bits.
  - The noise-sample pitch nybble check was fixed.
  - `SOUND_REST` was renamed `SOUND_CRY`; `CryPitch` was renamed `PitchOffset`; `PitchOffset` (octave) was renamed `Transposition`.
- **[MED] Music table** — Megalovania was removed, Marine Tube was moved (ID shift). New `SFX_THUNDERBOLT` (Thundershock with `pitch_offset 32`, appended).
- **[LOW] `WaveSamples` table assertions** moved out of `audio/wave_samples.asm` (for Crystal Tracker compatibility). `audio.asm` has the new sections.

### Home/core engine infrastructure

- **[MED] The predef system was removed** — `home/predef.asm`, `macros/predef.asm`, `data/predef_pointers.asm` deleted
  - `rst $38` is now `CrashRst38`; `rst $00` is `CrashRst0`.
  - Calls became `farcall`/`farjp`. `FlagPredef` is now `SmallFlagAction`, and `FrontpicPredef` is `PrepareAnimatedFrontpic`.
- **[MED] Named BG map transfer modes** — `constants/ram_constants.asm` (`hBGMapMode`)
  - `NO_BG_MAP_TRANSFER=0`, `TRANSFER_TILEMAP=1`, `ATTRMAP=2`, `TILEMAP1=3`, `ATTRMAP1=4`, `TILEMAP_OFS=5`, `ATTRMAP_OFS=6`.
  - `hBGMapCopyNRows` sets the rows for the `_OFS` modes.
- **[MED] Palette fades** — `engine/gfx/fade.asm`, `engine/gfx/dynamic_pals.asm`
  - Step counts and values (`wPalFadeTotalSteps`/`StepValue`) and prev/current palette states (`wPalState`, `PALSTATE_{WEATHER,DARKNESS,OVERCAST_INDEX,TIME_OF_DAY}`) let map-connection fades, palette swaps and object glow cross-fade consistently.
  - The "Dynamic Pals System" is pinned to ROMX `$4A`.
- **[LOW] VBlank/interrupt cleanup** — VBlank0 routine calls refactored (#1411) and interrupt cleanup (#1327).
  - `hFunction*` became `hLCDInterruptFunction*`; there is a new `hJumpFunction`.
  - The SGB border tilemap is decompressed to WRAM0.
- **[LOW] Code moved out of ROM0** — `FastPrintNum`, `CheckVBA` and `PrintWinLossText`; `home/gfx2.asm` merged into `home/gfx.asm`, `pokedex_flags` moved. No effect on behavior.
- **[LOW] Fixes** — Fly and Teleport are allowed on Silver Cave Room 3, Navel Rock Roof and Celadon Dept Store Roof (`data/maps/indoor_fly_maps.asm`). Resetting the clock inside Trainer House B1F no longer crashes. Items no longer disappear when the Bag is full.

## Maps, scripts, story events and text

Scope: `maps/` (.asm/.ablk/.pal), `data/maps/`, `data/events/`, `constants/map_constants.asm`,
`constants/event_flags.asm`, map-facing macros, collision/tileset changes only where they change map layouts.
Based on `dev_changes/map_events.md`, `dev_changes/names.md`, git log (342 commits on these paths) and scripted
comparisons of both checkouts (map ids, sizes, connections, scenes, warps, coordinate shifts, per-tile
collision).

### Maps added, removed, renamed, split or merged

- **[HIGH] Goldenrod Underground rebuilt (5 maps)** — `maps/GoldenrodUnderground*.asm`, `GoldenrodDeptStoreB1F.asm` — WAREHOUSE_ENTRANCE 3:43 is now GOLDENROD_UNDERGROUND (16x20 -> 11x20: shops, merchants, Coin Case). UNDERGROUND_PATH_SWITCH_ROOM_ENTRANCES 3:44 is split into GOLDENROD_UNDERGROUND_SWITCH_ROOM 3:44 (16x7) and GOLDENROD_UNDERGROUND_ENTRANCES 3:45 (5x19, the three stairwells from Goldenrod City). DEPT_STORE_B1F moves 3:45->3:46, and UNDERGROUND_WAREHOUSE 3:46 becomes GOLDENROD_UNDERGROUND_WAREHOUSE 3:47.
- **[HIGH] Route 23 split** — `maps/Route23North.asm`, `Route23South.asm` — ROUTE_23 (16:1, 12x70) becomes ROUTE_23_NORTH (16:2, 12x38; Victory Road entrances, badge checks 5-7, heal officer) and ROUTE_23_SOUTH (16:3, 12x32; League Gate, badge checks 0-4). South-half coordinates are y-76.
- **[HIGH] Route 13 merged** — `maps/Route13.asm`, `Route14LuckyIslandDual.asm` — ROUTE_13_EAST and ROUTE_13_WEST become ROUTE_13 (17:2, 35x10); objects from the old East map are x+24. New ROUTE_14_LUCKY_ISLAND_DUAL (17:21, 35x3) is only drawn as the view south of Route 13; which map you actually walk into is chosen by the dual-connection table.
- **[HIGH] Route 16/17 remapped** — `maps/Route16East.asm`, `Route16North.asm`, `Route17North.asm`, `Route17South.asm` — ROUTE_16_NORTHEAST, ROUTE_16_NORTHWEST and ROUTE_16_SOUTH all shared one 14x11 .ablk. They become ROUTE_16_EAST (21:2, 6x6), ROUTE_16_NORTH (25:21, 11x5) and ROUTE_17_NORTH (21:3, 9x10; landmark changes from Route 16 to Route 17, bicycle music). ROUTE_17 (10x63) becomes ROUTE_17_SOUTH (10x62, y-2).
- **[HIGH] Maps that shared one .ablk are separated** — `data/maps/blocks.asm` — DragonsDen1F, HiddenCaveGrotto and WhirlIslandCave (previously drawn inside NavelRockInside.ablk), GiovannisCave (inside UnionCave1F), SeafoamIslands1F (inside DimCave1F), SilverCaveItemRooms (inside DarkCaveVioletEntrance), WhirlIslandNW (inside DimCave2F), and SafariZoneWardensHome (shared PokemonFanClub.ablk) now each have their own small map. Their event coordinates all change (for example DragonsDen1F y-50, GiovannisCave x-10).
- **[MED] Fuchsia Aquarium added** — `maps/FuchsiaAquarium1F.asm`, `FuchsiaAquarium2F.asm` — new maps 17:22/23 (9x5) behind Fuchsia City (22,13)/(23,13), replacing the closed Safari Zone office.
- **[MED] Faraway Island split** — `maps/FarawayIslandNorth.asm`, `FarawayIslandSouth.asm` — FARAWAY_ISLAND (19:8, 17x23) becomes SOUTH (19:8, 13x8; ferry arrival at 12,12) and NORTH (19:7, 17x15; jungle warps).
- **[MED] Celadon Dept Store 6F becomes the Roof** — `maps/CeladonDeptStoreRoof.asm`, `CeladonDeptStoreElevator.asm` — CELADON_DEPT_STORE_ROOF (21:13, 13x6), outdoor palette, Fly allowed. The elevator now lists 5 floors (no 6F stop), and the roof is reached only by the 5F stairs.
- **[MED] Cherrygrove train track added** — `maps/CherrygroveTrainTrackDual.asm` — new walkable map CHERRYGROVE_TRAIN_TRACK_DUAL (26:13, 4x26) joining Cherrygrove Bay (east edge, y<30) to Route 30 (west edge). Has a hidden Premier Ball and two cut trees.
- **[LOW] Kanto Underground renamed** — `maps/UndergroundPath.asm`, `Route5/6UndergroundPathEntrance.asm` — UNDERGROUND 3:79 becomes UNDERGROUND_PATH 3:80 (3x18 -> 3x25, landmark "Underground Path"); the ROUTE_5/6 entrances are renamed *_UNDERGROUND_PATH_ENTRANCE and now use the gate tileset.

### Map ids, groups and sizes

- **[HIGH] Group membership changes** — `constants/map_constants.asm`, `data/maps/roofs.asm` — ROUTE_22/26/27/28 move into the Indigo group 16, YELLOW_FOREST(_GATE) moves to 27, CERULEAN_CAPE goes to the new group 38, and ROUTE_35/36 go to the new group 39. Roof and overcast lookups are per group; MapGroupRoofs now has 40 entries, ROOF_STATUE is removed, and ROOF_PARK and ROOF_SINJOH are added.
- **[HIGH] 53 maps resized** — `constants/map_constants.asm` — the main-path ones: AZALEA_GYM 5x8->7x12, CIANWOOD_GYM 5x9->14x9, ECRUTEAK_GYM 5x9->5x11, VIOLET_GYM 5x8->5x9, DRAGON_SHRINE 5x5->5x7, SILVER_CAVE_ROOM_3 10x17->8x16, ROUTE_36 32->23 wide, ROUTE_27 40->38, ROUTE_30 13->14, ROUTE_45 46->48 tall, NEW_BARK_TOWN 10->12 wide, CERULEAN/VERMILION/PEWTER re-laid.
- **[MED] Uniform coordinate shifts on kept maps** — `maps/*.asm` — for robots with hard-coded tiles: Route36 x-18/-20, Route13 x+24, Route27 x-4, Route30 x+2, LuckyIsland x+6, Route45 y+4, Route39 y+2, VermilionCity y-4/-2, CeruleanCity/Route24/Route25/Route17South y-2, PewterCity y+2, EcruteakGym y+4, DragonShrine y+4, SilverCaveRoom3 x-2 (Red now at 8,6), RuinsOfAlphOutside fully re-laid.
- **[MED] Map header changes** — `data/maps/maps.asm` — GoldenrodUnderground and GoldenrodDeptStoreB1F go DUNGEON -> INDOOR (no Escape Rope/Dig there any more). NavelRockRoof goes INDOOR -> CAVE. Silver Cave Room 3, the hidden grottoes, Valencia Port and the Celadon roof use PALETTE_AUTO. GoldenrodUndergroundWarehouse and the switch room use PALETTE_NITE.

### Connections and warps

- **[HIGH] Self-connected and one-way connections** — `data/maps/attributes.asm` — NavelRockInside connects to itself (north +11 and south -11, so it loops). RuinsOfAlphOutside has display-only connections: north to a "FakeRoute36" (Route 36 with height-1) and east to Route32 (+10). Neither Route 36 nor Route 32 connects back, and the MagnetTunnelEast<->RuinsOfAlphOutside link is gone.
- **[HIGH] New dual connections** — `data/maps/dual_connections.asm` — ROUTE_13 south: x<18 goes to Route14, otherwise to LuckyIsland (+9). CHERRYGROVE_BAY east: y<30 goes to CherrygroveTrainTrackDual, otherwise to CherrygroveCity (+15). The table format is unchanged.
- **[MED] Removed and changed connections** — `data/maps/attributes.asm` — Route10North and Route10South are no longer connected. Offsets change on about 25 edges because of map resizes: Cherrygrove/Route30/Route31, Ecruteak/Route38/Route39/Route42, Route35/36/37, Cerulean/Route4/Route9/Route24-25/Cape, Vermilion/Route6/Route11/Saffron, Pewter/Route3, Route45/46, Route32/MagnetTunnelEast. Border blocks change on 6 maps.
- **[MED] Warp lists with reordered or retargeted entries** — `maps/*.asm` — GoldenrodCity (targets are now GOLDENROD_UNDERGROUND_ENTRANCES 5/2/8), PokemonLeagueGate (wide doors; Route22 and Route28 now 2 warps each, Route26 a double door), VermilionCity 16->15 warps (Battle Factory is now warp 15), RuinsOfAlphOutside 13->14, GoldenrodDeptStoreB1F 3->2, SnowtopPokeCenter1F (2F stairs removed), plus the rebuilt/split maps.
- **[LOW] Warps only appended (double doors and similar)** — `maps/*.asm` — CeladonCity 16->19, FuchsiaCity 11->13 (aquarium), GoldenrodCity +3, PewterCity +1, SaffronCity +1, CianwoodGym +2 (stone-table holes), DragonShrine/DragonsDenB1F +2 (back door), EcruteakGym 33->49 (pits), Route39 +1 (barn double door). Existing indices are kept.
- **[LOW] Script warps retargeted** — `maps/SeagallopFerryVermilionGate.asm`, `engine/events/std_scripts.asm` — Faraway arrival is now FARAWAY_ISLAND_SOUTH (12,12). Grotto exits are now (3,9). The Giovanni's Cave warp is now (5,5). New `warpfacing UP, OLIVINE_LIGHTHOUSE_1F, 10, 17` for the lighthouse pan-up. New `digmod` exits in the Ruins of Alph Inner Chamber and Sinjoh Chamber.

### Main story: Johto

- **[HIGH] Azalea Gym is now the HGSS puzzle** — `maps/AzaleaGym.asm` — you ride 4 Spinarak carts (SPRITEMOVEDATA_SPINARAK_CART, half-step movement) and flip a red switch (1,10) and blue switches (3,4 / 8,5 / 8,10) that swap web blocks. Switch state lives in EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1/2, so it resets on reload. Bugsy is at (7,3), the exit at (6-7,23), and trainer positions and sight ranges changed.
- **[HIGH] Goldenrod Underground switch puzzle (HGSS)** — `maps/GoldenrodUndergroundSwitchRoom.asm` — the red (11,4), green (10,4) and blue (9,4) switches plus the emergency switch (25,8) each toggle a set of the 11 doors; door state persists in EVENT_DOOR_1..11_OPEN (via the new `toggleevent`). The rival battle is now in this room, with coord events at (23,1-3). The warehouse is reached through the switch-room warps (27-28,8).
- **[HIGH] Burned Tower forced battle** — `maps/BurnedTower1F.asm` — a new coord_event at (6,1) (scene 1, right after the Eusine scene) starts a battle with Firebreather Dick (moved here from Rock Tunnel B1F). The rival battle at (9,9) only arms after Dick is beaten; losing leaves the scene at 1. Hex Maniac Tamara moves from (1,1) to (3,6).
- **[HIGH] Ecruteak Gym redesigned** — `maps/EcruteakGym.asm` — the map is taller (5x11) and has 46 pit warps in a new layout, so the invisible-floor route through the gym is different. The entrance is at (4-5,21) and Morty is further north.
- **[HIGH] Cianwood Gym is the HGSS layout** — `maps/CianwoodGym.asm` — Chuck is training under a waterfall and cannot be battled until both Strength boulders, at (9,4) and (16,4), are pushed into the holes at (12,4)/(13,4) (stonetable; the holes are warps 3/4 with COLL_STONE_WARP). This persists as EVENT_BOULDERS_IN_CIANWOOD_GYM. The map is 14x9, the entrance at (12-13,17), and all Blackbelts moved.
- **[MED] Dragon Shrine and Dragon's Den** — `maps/DragonShrine.asm`, `DragonsDenB1F.asm` — the shrine is taller (5x7): front door at (4-5,13), new back door at (4-5,1) leading to DragonsDenB1F (19-20,26) (pagoda sprites). The test cutscene is skipped when you enter by the back door (callasm on wPrevWarp). Elder and Clair positions and movements are mirrored. Kimono Girl Mina (Ability Patch) moves into the shrine.
- **[MED] Olivine City re-laid** — `maps/OlivineCity.asm` — Mart at (21,17), Lighthouse at (33,21) with a new pan-up coord event and step-down scene, Port warps at (18-19,28), Good Rod house at (15,11). The hidden Rare Candy moves to (35,18).
- **[MED] Ruins of Alph redesigned (HGSS)** — `maps/RuinsOfAlphOutside.asm`, `RuinsOfAlph*Chamber.asm`, `RuinsOfAlphResearchCenter.asm` — the outside map is 12x19 with every chamber and gate warp moved. It uses the new johto_ancient tileset and has a new Hyper Potion item ball and hidden Nugget/Big Mushroom. The Research Center (5x4) can now resurrect fossils once EVENT_CAN_RESURRECT_FOSSILS_IN_RUINS_OF_ALPH is set (after all Unown are caught); the shared logic lives in `engine/events/fossils.asm`.
- **[MED] Team Rocket Base** — `maps/TeamRocketBase*.asm` — the maps use the new hideout tileset (some COUNTER tiles become WALL). After the three Electrodes, B2F turbine blocks switch off. Trap and camera coordinates are unchanged.
- **[LOW] Elm's Lab** — `maps/ElmsLab.asm` — same 8 scene values, now named. After the theft, Elm adds an emote and one more line (ElmAfterTheftText7). Several texts are inlined.
- **[LOW] Route 32 Togepi check** — `maps/Route32.asm` — new branch for when the Togepi egg has already hatched (EVENT_TOGEPI_HATCHED).
- **[LOW] Sprout Tower, Radio Tower, Tin Tower** — `maps/SproutTower1F.asm`, `RadioTower4F.asm`, `TinTower*.asm` — cosmetic only: pillar shakes more slowly; Mary gives a Fairy Feather instead of a Pink Bow; Ho-Oh and Lugia use big two-palette sprites (SPRITE_BIG_HO_OH/LUGIA plus dual_obj_pals). The Wise Trio room uses the sprout_tower tileset.

### Main story: Kanto, League and post-game

- **[HIGH] Route 23 badge gates now block** — `maps/Route23North.asm`, `Route23South.asm` — without the badge, the officer says so and pushes you back one tile (`applyonemovement PLAYER, step_down`). In v3.2.3 it only showed text. Presets or robots without all 8 Johto badges (Zephyr through Rising) cannot reach Victory Road.
- **[MED] Pokémon League Gate** — `maps/PokemonLeagueGate.asm`, `Route22.asm`, `Route26.asm`, `Route28.asm` — wide side gates and a double door to Route 26. Entering sets ENGINE_FLYPOINT_POKEMON_LEAGUE (new fly point, spawn on Route 26 at 8,6). Warps go to ROUTE_23_SOUTH.
- **[MED] Fuchsia City** — `maps/FuchsiaCity.asm` — layout edited: Gym door at (6,27), the Safari office is replaced by the Aquarium door (22-23,13), and there is a hidden Nugget at (26,12). The six zoo signs show a pokepic and mark the species as seen (SpecialSeenMon; Tauros form depends on time of day). Uses a paletteswap for the Safari roofs.
- **[MED] Fuchsia Aquarium content** — `maps/FuchsiaAquarium1F/2F.asm` — SPRITE_AQUARIUM_MON tank objects whose species varies by EVENT_TEMPORARY flags. The 2F PokéfanM gives an Eject Button (EVENT_GOT_EJECT_BUTTON_FROM_FUCHSIA_AQUARIUM).
- **[MED] Silver Cave Room 3 / Mt. Silver** — `maps/SilverCaveRoom3.asm` — peaks tileset, 8x16, Red at (8,6), entrance at (7,29), decorative arch objects added (object indices shift). Fly and Teleport are now allowed there (indoor_fly_maps).
- **[MED] Vermilion and Cerulean re-laid** — `maps/VermilionCity.asm`, `CeruleanCity.asm` — Vermilion: every door moves (mostly y-4), the Battle Factory is 1 warp (28,7), and there is a new sign for S.S. Aqua and the ferry. Cerulean: y-2, hidden Rare Candy, the Nugget Bridge coord events now drive wRoute24SceneID, and non-working coord events are removed.
- **[MED] Navel Rock** — `maps/NavelRockInside.asm`, `NavelRockRoof.asm` — the inside map shrank to 27x26 and wraps onto itself. The roof ending has a Beta-player branch, and Fly is allowed from the roof.
- **[LOW] Victory Road** — `maps/VictoryRoad1F.asm`, `VictoryRoad2F.asm` — only the warp targets change (ROUTE_23 -> ROUTE_23_NORTH).
- **[LOW] Power Plant / Route 10** — `maps/PowerPlant.asm`, `Route10North.asm` — the Zap Cannon tutor no longer takes a Silver Leaf. Route 10 North gets a static Lv50 Electrode (floating ball sprite, EVENT_ROUTE_10_NORTH_ELECTRODE), and its cut trees go from 4 to 2.

### Side content and optional events

- **[MED] Fourth player choice ("Beta"/Krys)** — `maps/CinnabarLab.asm`, `NavelRockRoof.asm`, `Route10North.asm`, `CopycatsHouse2F.asm`, `DayCare.asm`, `PokeCenter2F.asm`, `SnowtopMountainOutside.asm`, `TrainerHouseB1F.asm` — every gender dispatch table grows from 3 to 4 entries (NUM_PLAYER_GENDERS). New EVENT_BETA_IN_NAVEL_ROCK and EVENT_CINNABAR_LAB_BETA, and Trainer House opponent EUNA.
- **[MED] Rugged Road** — `maps/RuggedRoadNorth.asm`, `RuggedRoadSouth.asm` — five new trainers (Hikers Elijah and Maynard, Bird Keeper Salim, Fisher Carlos, Battle Girl Mei), a campfire with NPCs, and NPCs giving a PunchinGlove and an Oval Stone. North<->South crossing uses the no-fade palette table.
- **[LOW] Larry replaces Katy; Wilhomena replaces the Pikablu guy** — `maps/ShamoutiTouristCenter.asm`, `NoisyForest.asm`, `ShamoutiIsland.asm` — the Gen 9 leader cameo is now Larry in the Shamouti Tourist Center (EVENT_INTRODUCED_LARRY, Sweet Honey, EVENT_BEAT_LARRY in Katy's slot). Pokemaniac Larry's trainer id is renamed POKEMANIAC_LARRY.
- **[LOW] Moomoo Farm** — `maps/Route39Barn.asm`, `Route39.asm` — the barn is 7x4 with a double door. Miltanks are outside in the morning/day and inside in the evening/night. Hidden Moomoo Milk. The healing scene is reworked.
- **[LOW] Refactors with the same behaviour** — `maps/FightingDojo.asm`, `CopycatsHouse2F.asm` — Dojo rematches use 3 variable-sprite objects instead of 6 (flag slots 2184-2186 retired). Copycat scripts are rewritten (EVENT_COPYCAT_1-4 retired).
- **[LOW] Small additions** — `maps/GoldenrodHappinessRater.asm`, `Route32CoastHouse.asm`, `DiglettsCave.asm`, `ShamoutiTunnel.asm`, `GoldenrodMuseum2F.asm`, `Route35CoastNorth.asm`, `GoldenrodPokecomCenterOffice.asm` — the Happiness Rater lets you pick a Pokémon; Item Maniacs sell by quantity; museum paintings show from the start; the Pokéathlon construction site is removed; the dev office gains SourApple and Emi.
- **[LOW] Items moved or added on routes** — `maps/*.asm` — new hidden items: Cerulean Rare Candy, Route 13 Oval Stone, Vermilion Max Ether, Fuchsia Nugget, Moomoo Milk, train-track Premier Ball, Ruins items. The Route 27 whirlpool at block (33,7) is removed, so Whirlpool is no longer needed there. The Route 16 cut tree moves from the Celadon edge to Route16North/West (same flag slot).

### Scenes

- **[HIGH] Burned Tower 1F values shifted** — `maps/BurnedTower1F.asm`, `PlayersHouse2F.asm`, `GoldenrodUndergroundSwitchRoom.asm` — 0 meet Eusine, 1 Firebreather Dick (new), 2 rival battle (was 1), 3 noop (was 2). The Underground rival script sets 2 (was 1). A v3.2.3 value of 2 re-arms the rival battle in dev.
- **[HIGH] Shared or re-pointed scene variables** — `data/maps/scenes.asm` — ROUTE_23_NORTH and ROUTE_23_SOUTH both use wRoute23SceneID: South has checks 0-4 and noop 5; North has checks 5-7 and noop 8, with 0-4 as UNUSED. CERULEAN_CITY now uses wRoute24SceneID. wFarawayIslandSceneID becomes wFarawayIslandSouthSceneID, and wUndergroundPathSwitchRoomEntrancesSceneID becomes wGoldenrodUndergroundSwitchRoomSceneID; the RAM slots stay the same.
- **[MED] Olivine City scene 1 has a new meaning** — `maps/OlivineCity.asm` — 0 rival encounter, 1 STEP_DOWN (runs once after the lighthouse rival, then sets 2), 2 noop. In v3.2.3, 1 was "done"; loading it in dev is harmless.
- **[LOW] Scene constants everywhere** — `maps/*.asm` — 121 maps switched from numbers to SCENE_* names (pokecrystal style) and use DoNothingScript for no-op scenes. Apart from the items above, the values are unchanged (checked against every coord_event).

### Event flags

- **[HIGH] One kept flag changed value** — `constants/event_flags.asm` — EVENT_BEAT_FIREBREATHER_DICK moves 1070 -> 2268, and 1070 is now EVENT_BEAT_FIREBREATHER_CYD (the Rock Tunnel B1F trainer). The other 2192 shared names keep their numbers, and NUM_EVENTS is still $8ff (const_next), so wEventFlags keeps its size.
- **[HIGH] New defaults at game start** — `data/events/initialize_events.asm` — EVENT_BETA_IN_NAVEL_ROCK and EVENT_BURNED_TOWER_FIREBREATHER_DICK_ASHES are added. Without them, old saves show extra sprites in Navel Rock, Route 10 and Burned Tower. Renamed defaults stay in the same slots: RIVAL_GOLDENROD_UNDERGROUND, GOLDENROD_DEPT_STORE_B1F_LAYOUT_1, GOLDENROD_WAREHOUSE_BLOCKED_OFF.
- **[MED] Renames in place (same slot)** — `constants/event_flags.asm` — WAREHOUSE_ENTRANCE_*, UNDERGROUND_PATH_SWITCH_ROOM_ENTRANCES_* and UNDERGROUND_WAREHOUSE_* become GOLDENROD_UNDERGROUND_*; UNDERGROUND_* becomes UNDERGROUND_PATH_*; ROUTE_17_HIDDEN_* becomes ROUTE_17_SOUTH_*; KATY -> LARRY; PIKABLU_GUY -> WILHOMENA; PINK_BOW -> FAIRYFEATHER; ROUTE_16_CUT_TREE -> ROUTE_16_NORTH_CUT_TREE; ROUTE_30/CHERRYGROVE_BAY_CUT_TREE get a _1 suffix.
- **[MED] Reused slots with a new meaning** — `constants/event_flags.asm` — slots 610-620 were EVENT_SWITCH_4..14 and are now EVENT_DOOR_1..11_OPEN (Underground doors). An old save may start with some doors open.
- **[LOW] Retired slots (now const_skip)** — `constants/event_flags.asm` — 606-609 (old switches 1-3 and emergency), 1729-1730 (Copycat 1-2), 1860-1866 (Valerie's fairy books, now one object), 2184-2187 (rematch leaders 4-6, Copycat 3), 2217-2218 (Route 10 cut trees 3-4), 2260 (Copycat 4).
- **[LOW] New flags in previously unused slots** — `constants/event_flags.asm` — 2259 and 2261-2286: Beta sprites, Ruins items, EVENT_BOULDERS_IN_CIANWOOD_GYM, Route 10 Electrode, Dick flags, hidden items, the Route 30 and Cherrygrove Bay second cut trees, the train-track Premier Ball, Eject Button, PunchinGlove, Oval Stone, five Rugged Road trainers, and EVENT_CAN_RESURRECT_FOSSILS_IN_RUINS_OF_ALPH. EVENT_BEAT_LARRY (1485) and EVENT_BEAT_FIREBREATHER_CYD (1070) reuse old slots.

### Flags and indexes that maps depend on

- **[HIGH] Engine flags, spawns and flypoints** — `constants/engine_flags.asm`, `data/events/engine_flags.asm`, `data/maps/flypoints.asm` — the three Pokémon League insertions (see Top 10 #7). ENGINE_TIFFANY_HAS_PINK_BOW is renamed ENGINE_TIFFANY_HAS_FAIRYFEATHER (same bit).
- **[HIGH] No save migration exists** — `constants/misc_constants.asm` — SAVE_VERSION is still 10 and tools/bsp has no dev patch. A v3.2.3 save loads with the wrong map group/number, wrong visited spawns, and wrong Burned Tower scene.
- **[MED] Spawn coordinates** — `data/maps/spawn_points.asm` — Pewter (13,26->13,28), Cerulean (19,18->19,16), Vermilion (9,6->9,4), Snowtop (17,34->17,28), new ROUTE_26 (8,6).
- **[LOW] Landmark renamed** — `constants/landmark_constants.asm`, `data/maps/landmarks.asm` — UNDERGROUND becomes UNDERGROUND_PATH "Underground Path" (same value 53).
- **[LOW] Special music list** — `data/maps/special_music.asm` — Route 23 is now two entries; the cycling-road music entries are now ROUTE_17_NORTH and ROUTE_17_SOUTH.

### Script bytecode and map macros

- **[HIGH] Object sprite and palette encoding** — `macros/scripts/maps.asm`, `constants/sprite_data_constants.asm` — the PAL_NPC_*/PAL_OW_* list is renumbered (BROWN and PURPLE swapped; POKE_BALL, DECO_ITEM and KEY_ITEM replaced by ENV_RED, ENV_BLUE and ENV_GREEN; DARK_*, AQUA_*, COPY_BG_WHITE and others added). New PAL_MON_* values ($d1+) encode Pokémon-icon colours. SPRITE_AQUARIUM_MON packs species and form the way SPRITE_MON_ICON does.
- **[HIGH] Sprites used by map macros** — `macros/scripts/maps.asm`, `constants/sprite_constants.asm` — SPRITE_BALL_CUT_FRUIT is split: item balls and cut trees use SPRITE_BALL_CUT_TREE, fruit trees use SPRITE_BLANK_FRUIT. SPRITE_BOULDER_ROCK_FOSSIL becomes SPRITE_BOULDER_ROCK. New movement types SPRITEMOVEDATA $30-$38: BIG_HO_OH, BIG_LUGIA, ADMIN_MEOWTH, SPINARAK_CART, RATTATA_BACK, AQUARIUM_TOP/BOTTOM, PAGODA_LEFT/RIGHT.
- **[MED] Four new script commands (appended, existing ids unchanged)** — `macros/scripts/events.asm` — nooryes $dc (Celadon Mansion 3F), digmod $dd (warp id plus map: Dig/Escape Rope exit, Ruins chambers), toggleevent $de (flag toggle, switch room), usepaletteswap $df (palette-swap table in a MAPCALLBACK_CMDQUEUE callback, used by 12 maps).
- **[MED] Item-giving macros** — `macros/scripts/events.asm` — giveitem and verbosegiveitem now require a bag-full handler argument; plural forms carry the quantity; `_unsafe` variants exist. The bytecode is unchanged, but some scripts now stop with text when the bag is full.
- **[MED] paletteswap tables in map scripts** — `maps/FuchsiaCity.asm`, `GoldenrodCity.asm`, `LavenderTown.asm`, others — `paletteswap x1,x2,y1,y2,PAL_BG_x,outList,inList`, at most 8 per map, swaps BG palettes while the player is inside a rectangle.
- **[LOW] Scripts use RGBDS loops and inline asm** — `maps/GoldenrodUndergroundSwitchRoom.asm`, `DragonShrine.asm`, `AzaleaGym.asm` — `for` loops with interpolated labels (`.door_{d:n}_closed`), `callasm` reading wPrevWarp, and `rept` inside movement. A port that parses script source needs a macro evaluator.
- **[LOW] setmonval/checkpoke take a form** — `macros/scripts/events.asm` — `dp \#` allows `setmonval TAUROS, PALDEAN_FORM`.

### Map-engine data tables

- **[HIGH] SpecialBGPalettes format** — `data/maps/palettes.asm` — each entry is now a type<<6 | first-pal<<3 | count-1 byte plus a source pointer, so a palette can cover only part of the set (types SINGLE/TIMEOFDAY/TIMEWEATHER). 16 new per-map .pal files (including 6 *_overcast variants), 1 renamed (VioletGym), 2 deleted (grottoes), 26 changed.
- **[MED] New overcast/weather table** — `data/maps/overcast_maps.asm` — RandomOvercastMapsJohto/Kanto plus aliased multi-map areas (AREA_*, group ids > NUM_MAP_GROUPS). Overcast intensity (overcast, rain or thunderstorm) now decides overworld weather and automatic battle rain. New ROUTE_10_OVERCAST and GENERIC_OVERCAST constants.
- **[MED] dual_obj_pals** — `data/maps/dual_obj_pals.asm` — per-map pairs of object palettes for two-palette sprites: TIN_TOWER_ROOF (red+green Ho-Oh), WHIRL_ISLAND_LUGIA_CHAMBER, SHAMOUTI_ISLAND (Alolan Exeggutor).
- **[MED] NPC and Wonder Trade records one byte shorter** — `data/events/npc_trades.asm`, `data/events/wonder_trade/ot_names.asm` — OT names are now 7 bytes (PLAYER_NAME_LENGTH-1). Emy's trade item is now a Fairy Feather.
- **[LOW] no_connection_palette_fades** — `data/maps/no_connection_palette_fades.asm` — pairs that swap palettes instantly across a connection (currently only RUGGED_ROAD_NORTH<->SOUTH).
- **[LOW] map_name_signs** — `data/maps/map_name_signs.asm` — sign graphics pointer table (LZ-compressed sign gfx) and SignPals, per SIGN_* type.
- **[LOW] Connection setup script** — `data/maps/setup_scripts.asm`, `setup_script_pointers.asm` — MapSetupScript_Connection gains SavePrevPalStates ($39), BufferScreen and ClearSavedObjPals ($3a).
- **[LOW] Indoor Fly maps and grottoes** — `data/maps/indoor_fly_maps.asm`, `data/events/hidden_grottoes/grottoes.asm` — adds CELADON_DEPT_STORE_ROOF, SILVER_CAVE_ROOM_3 and NAVEL_ROCK_ROOF. The Ruins of Alph grotto uses warp 14 (was 13).

### Tilesets, blocks and collision

- **[HIGH] Tileset reassignments** — `data/maps/maps.asm` — johto_modern -> johto_coast (Olivine, Cianwood, Routes 38-41, Goldenrod Harbor); johto_overcast is renamed johto_outlands (Azalea, Lake of Rage, Routes 43-48, Blackthorn, Rugged Road, Snowtop inside); johto_ancient (Ruins outside, Sinjoh); johto_sacred (Dragon's Den B1F, Bellchime, Route 28, Silver Cave outside, Ecruteak Shrine); kanto_north (Cerulean area, Routes 4/5/9/10/24/25); kanto_urban (Vermilion, Celadon, Saffron, Routes 6/7/11/16); kanto_gym (8 Kanto gyms and pools); hideout (both Rocket bases); peaks (Silver Cave, Navel Rock); volcano (Cinnabar Volcano); hidden_grotto; alph_word_room -> ruins_of_alph.
- **[HIGH] New collision values** — `constants/collision_constants.asm`, `data/collision/collision_permissions.asm` — $03-$06 and $08 are glow floors (campfire, aquarium, lantern, lava, shrine lamp); $61 COLL_STONE_WARP (hole for stone tables); $74 COLL_CAVE_MOUTH_GLOW acts as a down-facing directional warp like $70 (Dark Cave, Rock Tunnel, Whirl Islands cave mouths switched to it); $75 COLL_LADDER_GLOW (Cinnabar Volcano and Fire Island ladders); $b8/$b9 glow walls; $d0 COLL_CHERRY_LEAVES is now WALL (was LAND); COLL_OVERHEAD is renamed COLL_VISUAL_GRASS.
- **[MED] Walkability changes on same-size maps** — `maps/*.ablk` — biggest: buoy lines on Kanto sea routes (Routes 12, 16W, 19-21, Uraga, Cinnabar, Cerulean Cape; WALL -> BUOY, still impassable); shoreline/sand edits (Routes 20/21/41, Cianwood, Stormy Beach, Route 32 Coast); Olivine, Ecruteak, Saffron, Route 8, Route 24, Cherrygrove Bay and Violet re-laid; Dark Cave Violet entrance, Dim Cave 1F and Union Cave 1F gain floor; Dragon's Den whirlpool moved.
- **[LOW] Object flags for map objects** — `constants/map_object_constants.asm` — the OBJECT_FLAGS2 bits are now IN_GRASS/BG_OFFSET/UNDER_TILES (walk behind pagoda roofs), and there is a BG_ALIGNED palette flag. Internal STEP_TYPE order changed (HALF1, NPC_HALF2 and PLAYER_HALF2 added).

### Text

- **[HIGH] ROM text encoding (only for ports that read text bytes from the ROM)** — `macros/scripts/text.asm`, `constants/charmap.asm`, `data/text/ngrams.asm` (deleted), `home/text.asm` — `text_far` is now `<FAR>` + big-endian pointer + bank, and the pointer's top bit means "text_farend" (end after the far text). Compression is now contextual Huffman with 3 contexts (after space/line-break, after a vowel, other), and the n-gram dictionary is gone. Source-level strings are unaffected.
- **[MED] Dialogue changes in maps** — `maps/*.asm` — of about 27.7k text lines, about 300 are removed and 700 added. Most come from new content (aquarium and zoo signs, underground switch texts, Burned Tower Dick, Rugged Road, Larry, the Celadon roof "Rooftop Square") and renames (Katy -> Larry, Pikablu guy -> Wilhomena, Pink Bow -> Fairy Feather, Safari Zone office -> Fuchsia Zoo/Aquarium, "Underground" -> "Underground Path").
- **[LOW] Smaller rewording** — `maps/*.asm` — Zap Cannon tutor no longer mentions a Silver Leaf; Route 23 "no badge" text; one extra Elm line; screen-relative direction words removed; Sweet Honey and binocular text fixes; Luna and SourApple office texts; typo fixes.
- **[LOW] Text labels inlined** — `maps/*.asm` — commit 94face39 moved about 135 maps' texts inline (`jumpthistext`, `writethistext`, `jumpthisopenedtext`), so many `...Text:` labels no longer exist. A port that looks texts up by label needs the new names.

## Game data: Pokémon, moves, items, abilities, trainers, wild

Paths are relative to the repo root. "NF" means the default non-Faithful build and "F" means `FAITHFUL`. Where a change applies to only one build, the bullet says so. Otherwise it applies to both. How it was checked: I parsed old and new `data/trainers/parties.asm`, every `data/pokemon/base_stats/*.asm` and `data/wild/*` in both build modes (`if DEF(FAITHFUL)` branches resolved) and compared them entry by entry. The other tables were compared diff by diff.

### Pokémon species, forms and per-species tables
- **[HIGH] New cosmetic form ARBOK_ORANGE_FORM shifts later ext indices** — `constants/pokemon_constants.asm`, `data/pokemon/variant_forms.asm`, `pic_pointers.asm`, `pic_sizes.asm`, `mini_icon_pointers.asm`, `overworld_icon_pals.asm` — ARBOK_ORANGE_FORM is form 3 at ext $140. KOGA/AGATHA/ARIANA move from forms 3/4/5 to 4/5/6, and everything after them (Pikachu forms, Pichu, Magikarp patterns, Red Gyarados, Armored Mewtwo, Dudunsparce, regional forms, Paldean Tauros, Bloodmoon Ursaluna) moves +1. `NUM_UNIQUE_POKEMON` is now $18a. Saves are safe unless a save holds a trainer-only Arbok form.
- **[HIGH] Overworld mon-icon palette table widened from 1 to 2 bytes per entry** — `data/pokemon/overworld_icon_pals.asm` — `iconpal` used to emit `dn PAL_OW_x, PAL_OW_y` and now emits `db PAL_MON_x, PAL_MON_y` with new TAN_* colour names. Some colours changed too: Hoothoot eyes, shiny Golem, Alolan Raichu, Suicune AZURE.
- **[MED] Footprint pointer table became fardw/farbank** — `data/pokemon/footprint_pointers.asm` — `dw XFootprint` became `farbank` + `fardw`, still 2 bytes per row, and the table gained an assert.
- **[MED] Pokédex entry text is now Huffman-compressed** — `data/pokemon/dex_entries.asm`, `macros/scripts/text.asm` — the first body line now uses `text` instead of `db`, and `page` now starts a new `text`. The strings themselves are unchanged. Decoding depends on the text engine (`constants/huffman_text.*`, `data/text/compressed_text.asm`).
- **[LOW] No species added or removed, no species renumbered** — `constants/pokemon_constants.asm` — 290 names. `dex_order_*`, `names.asm` and `body_data.asm` are unchanged.

### Base stats (`data/pokemon/base_stats/*.asm`, all 334 files touched)
- **[HIGH] New `bst` macro with reordered source columns** — `data/pokemon/base_stats.asm`, all base_stats files — `db hp,atk,def,spe,sat,sdf ; N BST` became `bst N, hp, atk, def, sat, sdf, spe`. The macro asserts the total and emits the old byte order, so the ROM layout is unchanged. Galarian Meowth's old comment total was wrong.
- **[MED] 89 NF stat rebalances (Blaze Black 2 Redux distributions)** — base_stats — examples:
  - Nidoking 81/102/77/85/75/85 → 81/**112**/77/85/75/85.
  - Pidgeot 93/80/75/90/70/102 → 83/60/70/115/70/101.
  - Charizard → 75/101/75/109/75/100.
  - Sentret 215 → 280 BST; Sunkern 180 → 240; Unown 336 → 360.
  - Full list of changed files: alakazam, ambipom, arbok, ariados, beedrill, blastoise, bonsly, butterfree, charizard, delibird, drowzee, farigiraf, fearow, feraligatr, flaaffy, flareon, furret, gengar, girafarig, glaceon, goldeen, golem (both forms), hoppip, hypno, jigglypuff, jumpluff, jynx, kleavor, lanturn, ledian, ledyba, machamp, magcargo, mareep, marill, meganium, meowth (plain, alolan, galarian), mime_jr, mr_mime (plain, galarian), nidoking, nidoqueen, ninetales_plain, octillery, onix, parasect, perrserker, persian (both forms), pidgey line, pikachu, politoed, poliwrath, raichu (both forms), raticate (both forms), seaking, sentret, skiploom, slugma, smoochum, spearow, spinarak, steelix, sudowoodo, sunflora, sunkern, tauros (plain + 3 Paldean), typhlosion (both forms), unown, venomoth, venonat, venusaur, voltorb (both forms), wigglytuff, wooper (both forms), xatu.
- **[MED] 3 F stat changes** — `kleavor.asm`, `meowth_galarian.asm`, `raichu_alolan.asm` — Kleavor Atk 130→135 and SDf 75→70 (both builds). Galarian Meowth Def 65→55. Alolan Raichu SDf 80→85.
- **[MED] NF type changes** — `goldeen.asm`, `seaking.asm`, `growlithe_plain.asm`, `arcanine_plain.asm`, `rapidash_plain.asm` — Goldeen and Seaking are now Water/Normal. Kanto Growlithe and Arcanine are now Fire/Normal (this arrived through the "Merge in v3.2.3" base). Kanto Rapidash went from Fire/Fairy back to pure Fire.
- **[MED] Ability slot changes** — base_stats:
  - Mareep, Flaaffy: slot 2 → FLUFFY (NF).
  - Hoppip, Skiploom, Jumpluff: slot 2 LEAF_GUARD → WIND_RIDER (NF).
  - Drowzee, Hypno: FOREWARN → BAD_DREAMS (NF).
  - Meganium: hidden ability → MEGA_SOL (both builds; F slot 2 is now LEAF_GUARD).
  - Raichu (plain): STATIC/STATIC/LIGHTNING_ROD → STATIC/LIGHTNING_ROD/NO_GUARD (both builds).
  - Persian (plain): LIMBER → SUPER_LUCK (NF).
  - Sandshrew and Sandslash, plain and Alolan: slot 2 → SHARPNESS, except Alolan Sandslash → IRON_BARBS (NF).
  - Dudunsparce: hidden RATTLED → SAND_STREAM (NF).
  - Sirfetch'd: slot 2 → INNER_FOCUS, but only in the **F** branch. The commit says "non-Faithful", so this looks inverted.
- **[LOW] Other per-species fields** — `sylveon.asm`, `venonat.asm`, `weezing_galarian.asm`, `mr__mime_galarian.asm` — Sylveon's held item is now FAIRYFEATHER. Venonat base exp 75→80 (NF). Galarian Weezing learns TM HYPER_BEAM. Galarian Mr. Mime now uses the `HATCH_MEDIUM_SLOW` name for the same value 4.

### Learnsets, evolutions, egg moves
- **[MED] Meganium line: DAZZLINGLEAM → GROWTH** — `data/pokemon/evos_attacks.asm` — Chikorita Lv31, Bayleef Lv36 and Meganium Lv40.
- **[MED] Pichu: SING → HEAL_BELL at Lv28** — `data/pokemon/evos_attacks.asm`.
- **[LOW] No evolution, egg-move or TM/HM-list changes** — `evos_attacks.asm` evo_data, `egg_moves.asm`, `tmhm_moves.asm` — the only other change is a comment: tutor MT29 is at the Route 17 North Gate. `tmhm_order.asm` gained table asserts only.

### Cries
- **[HIGH] mon_cry row is now `db index` + `dw pitch, length` (5 bytes)** — `data/pokemon/cries.asm`, `constants/pokemon_data_constants.asm` (`MON_CRY_LENGTH` 6→5).
- **[HIGH] 38 new cry indices** — `constants/cry_constants.asm` — CRY_AZURILL through CRY_ANNIHILAPE were appended after CRY_DONPHAN. Azurill, Wynaut, Ambipom, Mismagius … Annihilape now point at their own Gen 3+ cries (Siren converter, plus 5 custom cries from Pokémon Orange) instead of reused Gen 2 cries with a pitch shift.

### Moves
- **[MED] Stat changes** — `data/moves/moves.asm` (same column layout):
  - Growth: type NORMAL → GRASS.
  - Iron Head: flinch chance 30 → 20.
  - Moonblast: SpAtk-drop chance 30 → 10.
  - Crabhammer: accuracy 95 in both builds (F was 90).
  - Iron Tail: accuracy 75 → 80 (NF).
- **[MED] X-Scissor high crit (NF)** — `data/moves/critical_hit_moves.asm`, `descriptions.asm` — X-Scissor now shares the "high critical hit ratio" description in NF.
- **[MED] New WindMoves table** — `data/moves/wind_moves.asm` (new) — BLIZZARD, GUST, HURRICANE, ICY_WIND and SANDSTORM, terminated by -1. Used by Wind Rider.
- **[MED] Slicing moves extended** — `data/moves/slicing_moves.asm` — adds DRAGON_CLAW, METAL_CLAW and SHADOW_CLAW. Sharpness applies to them.
- **[LOW] Effect-script tweaks** — `data/moves/effects.asm` — DoBurn (Will-O-Wisp) no longer runs `stab`. The extra `endmove` hotfix after FlareBlitz was removed; the crash is now fixed properly in the engine.
- **[LOW] Thunder Wave description missing `done` was fixed; move animations tweaked** — `data/moves/descriptions.asm`, `data/moves/animations.asm` — animation changes cover Wrap, Frz/Par, Ice Beam, Blizzard and others.
- **[LOW] Move IDs unchanged** — `constants/move_constants.asm` — 287 moves, and the TM/HM/tutor constants are unchanged.

### Items
- **[HIGH] HELD_OTHER inserted at 1** — `constants/item_data_constants.asm`, `data/items/attributes.asm` — every later `HELD_*` value moves up by 1. HELD_OTHER marks non-inert items that have no battle effect code, for the party-menu icon: Lucky Egg, Soothe Bell, Light Ball, Leek, Thick Club, Lucky Punch, Armor Suit and all 10 Mails. New `HELDTYPE_*` constants cover the 4 held-item icons (item, inert, mail, berry).
- **[HIGH] Item use effects are now data tables** — `data/items/effects.asm` (new), `data/items/key_effects.asm` (new), `constants/item_data_constants.asm` — 1 byte per item: `ITEMEFFECT_*` (0 = NONE, "isn't the time") for NUM_ITEMS+1 rows including PARK_BALL, and `KEYITEMEFFECT_*` per key item. This replaced the `dw` jump table in `engine/items/item_effects.asm`. I checked that the item→effect mapping is identical.
- **[MED] PINK_BOW renamed to FAIRYFEATHER (id $8a unchanged)** — `constants/item_constants.asm`, `data/items/names.asm`, `descriptions.asm`, `icon_pointers.asm`, `attributes.asm` — name "FairyFeather", same Fairy-type boost attributes, new icon. All gifts and holders were updated: Mary's gift, Tiffany's phone gift, Emy's trade, Sylveon's wild item, Battle Tower Sylveon, trainers.
- **[MED] Alphabetical NAM_* order shifted** — `constants/item_constants.asm`, `data/items/name_order.asm` — NAM_FAIRYFEATHER was inserted after NAM_EXPERT_BELT and NAM_PINK_BOW removed, so NAM_ values from FAIRYFEATHER through PEWTERCRUNCH move up by 1.
- **[LOW] Prices, marts and shops unchanged** — `data/items/attributes.asm`, `marts.asm`, `bargain_shop.asm`, `rooftop_sale.asm`, `buena_prizes.asm` — no price changes and no mart inventory changes.

### Abilities
- **[HIGH] 5 new abilities with mid-list inserts** — `constants/ability_constants.asm`, `data/abilities/names.asm`, `descriptions.asm` — BAD_DREAMS ($69, after RECKLESS), IRON_BARBS ($85, after SAND_FORCE), FLUFFY ($91, after CORROSION), WIND_RIDER ($9a, after QUICK_DRAW), MEGA_SOL ($9f, at the end). NUM_ABILITIES went from 155 to 160. Mon structs store an ability slot, not an ID, so saves are not affected.
- **[HIGH] New per-ability flags table replaces the lists** — `data/abilities/flags.asm` (new), `constants/battle_constants.asm` — 1 flag byte per ability: `ABILFLAG_NO_COPY`/`NO_TRACE`/`NO_SWAP`/`NO_SUPPRESS`/`IGNORABLE`/`NO_TRANSFORM`/`NO_INTIMIDATE`. `mold_breaker_suppressed_abilities.asm` and `no_intimidate_abilities.asm` were deleted.
- **[MED] Mold-Breaker-ignorable set changed** — `data/abilities/flags.asm` — Bulletproof, Fluffy, Iron Barbs and Wind Rider are now ignorable. **Armor Tail is no longer ignorable** (it was in the old list; probably an oversight). The NO_INTIMIDATE set is identical to the old list.
- **[LOW] Sand Force description reworded** — `data/abilities/descriptions.asm` — now reads "Ups Rock, Ground, and Steel in sand."

### Trainers: classes, per-class tables, palettes
- **[HIGH] Class renumbering** — `constants/trainer_constants.asm` — CAL $02→$01 and CARRIE $01→$02, JACKY $03, new EUNA $04 (the "BETA" player), FALKNER $04→$05 … REI $93→$94. KATY $8c became LARRY $8d. New FIREBREATHER_ASHES is $95, which is also NUM_TRAINER_CLASSES. The pic-only classes OMASTAR_FOSSIL … SILHOUETTE moved from $94–$99 to $96–$9b.
- **[HIGH] Every per-class table gained rows** — `data/trainers/class_names.asm`, `attributes.asm`, `dvs.asm`, `party_pointers.asm`, `encounter_music.asm`, `pic_pointers.asm`, `palettes.asm`, `genders.asm`, `sprites.asm`, `final_text.asm` — Cal/Carrie rows swapped, Euna inserted, Katy→Larry, Ashes appended. The Ashes class reuses `FirebreatherGroup`, has a gray pic, DVs $CC, 48 EVs, and reward 15.
- **[HIGH] Trainer palettes split from classes** — `constants/trainer_constants.asm`, `data/trainers/palettes.asm` — `trainerpal` no longer runs once per class. The new `CustomTrainerPalettes` table is indexed 1-based by `TRAINERPAL_*`: NONE=0, 7 Kimono Girls, 3 Wise Trio elders, 3 Kanto bikers, and 14 DARK_* skin-tone variants, 27 in total. The old kimono pals were class-numbered $9a–$a0. Maps pass these in the existing optional 8th `trainer` argument (0 = class palette).
- **[HIGH] TRAINERTYPE bits shifted down** — `constants/trainer_data_constants.asm` — see Top 10 #3. The `tr_*` macro syntax in `data/trainers/macros.asm` is unchanged.
- **[MED] New trainer IDs, appended within their classes (no ID shifts)** — `constants/trainer_constants.asm`, `data/trainers/parties.asm` — new trainers:
  - Rugged Road: FISHER CARLOS, BIRD_KEEPER SALIM (custom pal), HIKER ELIJAH and MAYNARD, BATTLE_GIRL MEI.
  - FIREBREATHER CYD in Rock Tunnel B1F, with the old Dick party (Charmander 53, Charmeleon 55, Charizard 57).
  - EUNA 1: Meganium, Typhlosion, Feraligatr, Ampharos, Donphan and Slowking, all Lv60.
  - LARRY 1/2 (Sweet Honey cameo at Shamouti Tourist Center) replaced KATY 1/2 (Ariados/Butterfree/Shuckle/Kleavor/Heracross/Ursaring). Larry's team: Tauros, Fearow, Farigiraf, Arcanine, Alolan Raticate, Ursaring (Ursaluna in the rematch) and Dudunsparce, Lv 54–57 and 72–75.
  - POKEMANIAC LARRY was renamed POKEMANIAC_LARRY.
- **[MED] Class item changes** — `data/trainers/attributes.asm`:
  - Nurse: none → FULL_HEAL.
  - Super Nerd: DIRE_HIT → X_ATTACK.
  - Rich Boy and Lady: MAX_POTION → FULL_RESTORE.
  - Breeder: SUPER_POTION → none.
  - Scientist: FULL_RESTORE → X_SP_DEF.
  - Rocket Scientist: FULL_RESTORE → X_SP_ATK.
  - Engineer: none → DIRE_HIT.
- **[LOW] Other class-table value changes** — `class_names.asm`, `dvs.asm`, `encounter_music.asm`, `genders.asm`, `data/battle/music.asm`, `leaders.asm`, `data/events/trainer_house_opponents.asm`:
  - Larry: class name "Businessman", male, SwSh gym music, listed in BossTrainers.
  - Jacky's encounter music changed from Beauty to Hiker, and his BT gender bit changed from female to male.
  - Euna was added to the Trainer House rotation.

### Trainer parties: summary
- **[MED] 135 of 955 trainers changed, 9 added, 2 removed** — `data/trainers/parties.asm` — most changes come from #1300 "Update the mostly late-game leaders' teams": held items, EV spreads, `tr_extra` abilities and natures, and moves. Many parties now give genders explicitly on every mon. The lineup and level changes are listed below. Where a bullet says only "items/moves", the species and levels are unchanged.
- **[MED] Firebreather Dick restored from G/S** — `parties.asm`, `maps/BurnedTower1F.asm` — Dick is now a Burned Tower 1F battle with a single Charmeleon at Lv17, and his "ashes" version uses the new class pic. His old Rock Tunnel party moved to Cyd.
- **[LOW] Minor lineup changes** — `parties.asm`:
  - Petrel 1: Koffing → Ditto (Imposter, Choice Scarf).
  - Pokémaniac Aidan: Lv36 → LEVEL_FROM_BADGES+7.
  - Jacky: Togetic → Togekiss.
  - Carrie: Wigglytuff gets Flamethrower.
  - Cal: Weavile and Clefable moves changed; Clefable now holds FairyFeather.
  - Rival2 #4 Meganium line has a stray duplicate `MALE`, and Rival2 #5 Typhlosion has no gender. Both are harmless because MALE = 0.

### Trainer parties: Johto gym leaders (first fight / rematch)
- **[MED] Falkner** — `parties.asm` — first fight: genders only. Rematch: Xatu → Togekiss; items are now Wide Lens, Toxic Orb, Choice Band, Leftovers, Life Orb and Focus Sash; moves revised.
- **[MED] Bugsy** — `parties.asm` — first fight: Scyther (17) now leads (U-turn), moves/EVs revised. Rematch: Ledian leads, Heracross second; items Light Clay, Choice Scarf, Life Orb, Focus Sash, Leftovers, Eviolite.
- **[MED] Whitney** — `parties.asm` — first fight: Miltank nicknamed "Milky", abilities set. Rematch reworked: Stantler/Ursaring/Tauros out; new team is Lickilicky 71, Granbull 72, Clefable 74, Chansey 70 (Eviolite), Wigglytuff 72 and Miltank 75 (Metronome item).
- **[MED] Morty** — `parties.asm` — first fight: abilities only. Rematch: the lead Gengar 72 was replaced by Cursola 70 (Eject Button); then Ninetales 72, Alolan Marowak 71, Mismagius 73, Noctowl 74 (NF) or Haunter 74 (F), and Gengar 75.
- **[MED] Chuck** — `parties.asm` — first fight: Primeape Screech → Feint Attack. Rematch: same species; items Choice Scarf, Leek, Punching Glove, Mirror Herb, Focus Sash, Leftovers.
- **[MED] Jasmine** — `parties.asm` — first fight: genders and moves. Rematch shrank from **6 to 5**: Forretress 73, Skarmory 74, Magnezone 72 (Assault Vest), Rhyperior 72 (NF) or Alolan Dugtrio 72 (F), Steelix 75 (Life Orb). Scizor was dropped; in F the second Magnezone was also dropped.
- **[MED] Pryce** — `parties.asm` — first fight: genders. Rematch: Dewgong → Alolan Ninetales 73 (Icy Rock); items White Herb, Life Orb, Assault Vest, Leftovers, Focus Sash.
- **[MED] Clair** — `parties.asm` — first fight grew from **5 to 6**: Gyarados 43, Yanmega 45, Dragonair 44, Ampharos 44, Dragonair 44, Kingdra 47 in both builds (F previously had no Ampharos). Rematch: same species; items revised.

### Elite Four and Champion
- **[MED] Will** — `parties.asm` — first fight: Jynx Brightpowder → NeverMeltIce, genders, moves. Rematch: same species; items Assault Vest, Focus Sash, Room Service, Life Orb, Rocky Helmet, Leftovers.
- **[MED] Koga** — `parties.asm` — first fight: genders and moves. Rematch: Weezing → Galarian Weezing (Assault Vest); Tentacruel Black Sludge, Forretress Rocky Helmet, Koga-form Arbok Focus Sash.
- **[MED] Bruno** — `parties.asm` — first fight: genders and moves. Rematch: same species; items White Herb, Liechi Berry, Assault Vest, Life Orb, Leftovers.
- **[MED] Karen** — `parties.asm` — first fight: Alolan Persian now holds FairyFeather. Rematch: same species; items NeverMeltIce, Black Sludge, Assault Vest, Focus Sash.
- **[LOW] Lance** — `parties.asm` — first fight: Charizard's move order changed only. Rematch: same lineup and items; every mon gained an explicit EV spread; Kingdra and Gyarados gained abilities (Sniper, Intimidate); Charizard's nature and Aerodactyl's moves changed.

### Kanto gym leaders (first fight / rematch)
- **[MED] Brock** — `parties.asm` — same lineups in both fights. Rematch items: Custap Berry, Assault Vest, Air Balloon, Focus Sash, Life Orb, Leftovers.
- **[MED] Misty** — `parties.asm` — same lineups. Rematch items: Damp Rock, Leftovers, Life Orb, Assault Vest, Choice Specs, Expert Belt.
- **[MED] Lt. Surge** — `parties.asm` — first fight: Raichu now leads at Lv58 with no item, and Electabuzz is last at Lv60 with Eviolite (they swapped). Rematch: same species; items Air Balloon, Light Clay, Flame Orb, Leftovers, Assault Vest, Focus Sash.
- **[MED] Erika** — `parties.asm` — first fight shrank from **6 to 5** (Victreebel 64 dropped). Rematch: same species; Bellossom holds FairyFeather (NF) or Miracle Seed (F).
- **[MED] Janine** — `parties.asm` — same lineups. Rematch items: Choice Band, Focus Sash, Leftovers, Life Orb, Assault Vest.
- **[MED] Sabrina** — `parties.asm` — same lineups. Rematch items: Light Clay, Focus Sash, Assault Vest, Leftovers, Choice Specs, Life Orb.
- **[MED] Blaine** — `parties.asm` — first fight: Ninetales now leads at Lv65 with Heat Rock (sun setter), and Magcargo moved to Lv66. Rematch: in F, Flareon 74 was replaced by Ninetales 74 (Heat Rock); items revised in both builds.
- **[MED] Blue** — `parties.asm` — first fight: Pidgeot 67 (Focus Sash, now the lead) and Rhyperior 68 (Assault Vest) replace Machamp and Kabutops. Team: Pidgeot 67, Umbreon 69, Exeggutor 66, Rhyperior 68, Arcanine 68, Blastoise 70. Rematch: Pidgeot 73, Umbreon 74, Exeggutor 74, **Tyranitar** 74, Arcanine 74, Blastoise 75; Machamp and Kabutops are out.

### Rivals, Red, Green (Leaf), Lyra
- **[MED] Red** — `parties.asm` — was Pikachu 90, Espeon 84, Snorlax 85, Omastar 87, Gyarados 87, Charizard 88. Now **Lapras 86** (White Herb), Pikachu 90, Espeon 84 (Life Orb), **Machamp 85** (Assault Vest), Snorlax 87, Charizard 88 (Safety Goggles). Omastar and Gyarados are out.
- **[MED] Green (LEAF)** — `parties.asm` — was Lapras 96, Venusaur 100, Moltres 98, Sylveon 95, Aerodactyl 98, Mew 99. Now **Gengar 96**, **Kangaskhan 97**, Moltres 98, Venusaur 100, Sylveon 95, Mew 99. Lapras and Aerodactyl are out.
- **[MED] Rival (RIVAL1_4…15, RIVAL2_1…6)** — `parties.asm` — species and levels unchanged. Every mon gets a gender. Alakazam's BrightPowder → TwistedSpoon (RIVAL1_13–15 and RIVAL2_1–3). In the final fight (RIVAL2_4–6) all items changed: Weavile Focus Sash, Crobat Choice Band, Magnezone Assault Vest, Gengar Expert Belt, Alakazam Life Orb. Moves were revised in RIVAL1_4–9, 13–15 and all of RIVAL2; RIVAL1_10–12 only gained explicit abilities.
- **[LOW] Lyra (LYRA2 1–3)** — `parties.asm` — same species and levels. Every mon now holds an item (Sharp Beak, Expert Belt, White Herb, Assault Vest, Sitrus, Leftovers/Heat Rock/Life Orb). Genders and moves set. LYRA1 is unchanged.

### Other bosses (lineup-relevant only)
- **[MED] Agatha rematch** — `parties.asm` — Alolan Marowak (NF) or Muk (F) → **Hisuian Typhlosion** 72 (Focus Sash).
- **[MED] Steven rematch shrank from 6 to 5** — `parties.asm` — Magnezone dropped. Team: Skarmory, Rhyperior (NF) or Forretress (F), Alolan Sandslash, Aerodactyl, Steelix.
- **[LOW] Other cameo leaders** — `parties.asm` — Marlon 1: levels −6 (27–31). Marlon 3: Cloyster now leads. Buck: Golem → Alolan Golem. Anabel 2: Slowking now leads. Cheryl, Riley, Marley, Mira, Candela, Blanche, Flannery, Maylene, Valerie, Kukui, Piers, Bill, Yellow, Walker, Lawrence, Rei, Palmer, Ivy, Giovanni 2, Oak, Cynthia, Lorelei and Jessie & James: items, abilities and moves only.

### Wild encounters
- **[HIGH] Grass tables: one rate byte per map** — `data/wild/*_grass.asm`, `constants/pokemon_data_constants.asm` — `db a percent, b percent, c percent` became `db a percent`. GRASS_WILDDATA_LENGTH went from 68 to 66. The only map whose rates differed by time was DIGLETTS_CAVE (4/2/8 → 4). NAVEL_ROCK_INSIDE's raw `1` became `1 percent`.
- **[HIGH] Fishing time-of-day slot removed** — `data/wild/fish.asm`, `fishmon_maps.asm`, `constants/map_data_constants.asm` — the Shore group's species-0 slots (Corsola by day, Staryu by night) are now always Corsola. The new FISHGROUP_STARYU (appended) is Route 41's group; Route 41 was OCEAN.
- **[MED] Map renames and splits in the wild tables** — `kanto_grass.asm`, `kanto_water.asm`, `fishmon_maps.asm`:
  - ROUTE_13_EAST became ROUTE_13 (grass, water and fish).
  - ROUTE_14 lost its water and fish tables (merged into Route 13).
  - ROUTE_23 split: ROUTE_23_NORTH has grass, water and fish; ROUTE_23_SOUTH has water and fish.
  - ROUTE_16_NORTHWEST became ROUTE_16_NORTH.
  - ROUTE_17 grass was removed as impossible.
- **[MED] Silver Cave rebalanced** — `johto_grass.asm` — Rooms 1–3 and the item rooms were reshuffled: Larvitar added to Room 1, Donphan/Quagsire/Sneasel added, Machoke and Magmar moved around. Room 3's rate went from 6% to 3%.
- **[MED] Orange Islands** — `orange_grass.asm` — Noisy Forest's B+1 slot is now Orange-form Arbok (was Butterfree by morning, Beedrill by day, Ariados by night). NAVEL_ROCK_INSIDE levels were lowered (79–83). New NAVEL_ROCK_ROOF grass table: Dragonair/Dragonite Lv 80–85 at 2%.
- **[LOW] Headbutt trees added** — `data/wild/treemon_maps.asm` — CHERRYGROVE_BAY and CHERRYGROVE_TRAIN_TRACK_DUAL use TREEMON_SET_ROUTE.

### NPC trades, Battle Tower, Wonder Trade
- **[HIGH] NPC trade struct is 1 byte shorter** — `constants/npc_trade_constants.asm`, `data/events/npc_trades.asm` — NPCTRADE_OT_NAME is now `PLAYER_NAME_LENGTH-1` (7 bytes, so "Jacques" is unterminated). Emy's Mr. Mime holds FAIRYFEATHER. Otherwise the trades are identical.
- **[HIGH] Battle Tower trainer rows are 1 byte shorter** — `data/battle_tower/classes.asm` — the name field is now `NAME_LENGTH-2` (9 bytes) followed by the class byte. The names themselves are unchanged.
- **[MED] Wonder Trade OT names are 7 bytes** — `data/events/wonder_trade/ot_names.asm` — `table_width PLAYER_NAME_LENGTH-1`; same names.
- **[LOW] Battle Tower parties** — `data/battle_tower/parties.asm` — Sylveon holds FAIRYFEATHER. Dudunsparce's ability is SAND_STREAM in NF.

### Battle data, type chart, happiness
- **[LOW] Affection thresholds moved to a data table; values unchanged** — `data/battle/affection_thresholds.asm` (new), `constants/battle_constants.asm`, `pokemon_data_constants.asm` — thresholds 255/220/180/0 (AFFECTION_THRESHOLD_1/2 = 180/220), and the AFFECTION_LEVEL_0–3 bonuses are documented. `happiness_changes.asm` only changed a comment.
- **[LOW] Type chart, critical-hit chances and AI data unchanged** — `data/types/*`, `data/battle/critical_hit_chances.asm`, `data/battle/ai/*` — no diff.

### Phone and marts
- **[LOW] Tiffany's gift is now a FairyFeather** — `data/phone/text/tiffany_overworld.asm`, `engine/phone/scripts/tiffany.asm` — ENGINE_TIFFANY_HAS_PINK_BOW became ENGINE_TIFFANY_HAS_FAIRYFEATHER, and the text now says "my Clefairy's FairyFeather". No other phone data or contact changes.
- **[LOW] Marts unchanged** — `data/items/marts.asm` — no diff. Celadon's rooftop map moved, but that is covered by the maps area.

### Options data
- **[MED] Options are now one scrollable list with a new Nicknames option** — `data/options/option_names.asm` (new), `options_descriptions.asm` (new), `default_options.asm`, `constants/ram_constants.asm` — the order is Text Speed, Text Autoscroll, Frame, Typeface, Keyboard, Sound, Battle Effects, Battle Style, **Nicknames**, Running Shoes, Turning Speed, Clock Format, #dex Units (it was 2 pages of 6). wOptions3 gained the NICKNAMES_ALWAYS (bit 1) and NICKNAMES_NEVER (bit 2) bits. The DEBUG build defaults to NEVER.
- **[MED] Initial options are one list of 11** — `data/options/initial_option_names.asm` (new), `initial_options_descriptions.asm` (renamed from `descriptions.asm`) — the page-split tables and NextPage/PrevPage entries were removed.

### Player data
- **[HIGH] 4th player gender PLAYER_BETA ("Krys", trainer class EUNA)** — `constants/ram_constants.asm`, `data/player/*.asm` (new) — tables indexed by NUM_PLAYER_GENDERS (now 4): default names, fishing gfx, sprite gfx, card pic, backpic, pack gfx (4×6), pack pals, Pokégear pals, sprite anims.
- **[HIGH] wPlayerState renumbered and PLAYER_RUN added** — `constants/ram_constants.asm`, `data/player/state_sprites.asm` — NORMAL=0, RUN=1, BIKE=2, SKATE=3, SURF=4, SURF_PIKA=5 (was 0/1/2/4/8). The old per-gender `(state, sprite), -1` lists in `data/sprites/player_sprites.asm` became a dense `[gender][state]` 6-byte table. This is save-visible if `wPlayerState` is persisted.
- **[LOW] Default player names moved** — `data/default_player_names.asm` → `data/player/default_names.asm` — now an indexed table that adds "Krys".

### Names and text-as-data
- **[MED] Name strings** — `data/trainers/class_names.asm`, `data/items/names.asm`, `data/abilities/names.asm` — new class names "Businessman" (LARRY, replacing "Patissier") and "Firebreather" (ASHES), plus Euna's "<PK><MN> Trainer". Item "FairyFeather". 5 new ability names.
- **[LOW] Text compression** — `constants/huffman_text.*`, `data/text/compressed_text.asm`, `data/text/ngrams.asm` (deleted) — the text engine moved from n-grams to contextual Huffman. Details belong to the text area; they matter for dex entries and any `text` blocks inside data tables.

### Checked and unchanged
- **[LOW] No changes in these tables** — `constants/move_constants.asm`, `constants/type_constants.asm`, `constants/tmhm_constants.asm`, `constants/phone_constants.asm`, `data/pokemon/egg_moves.asm`, `evolution_moves.asm`, `names.asm`, `palettes.asm`, `data/items/marts.asm`, `data/types/*`, `data/wild/johto_water.asm`, `orange_water.asm`, `swarm_water.asm`, `probabilities.asm`, `roammon_maps.asm`, `bug_contest_mons.asm`, `data/trainers/macros.asm` — the `move` macro columns, `item_attribute` layout, `tr_mon`/`tr_*` syntax and water wild record size (12 bytes) are all unchanged.
