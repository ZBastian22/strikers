# robot_helpers

Helpers for the test robot of the Polished Crystal 3.2.3 PC port. The robot
presses A on every person and sign, steps on every trigger tile and walks
into every door, once in the port and once in the original game, and
records any difference. Everything here is Python 3 (standard library only)
or plain data.

**`story_presets.lua`**: saved-game checkpoints along the main story
(female player, Chikorita), from getting the starter (C01_STARTER) to
beating Red (C13_POSTGAME), so the robot can test each map at several
points in the story. `dofile("story_presets.lua")` returns a list. Start
from a blank save and apply the entries in list order, up to and including
the checkpoint you want. Each entry holds only the change since the one
before it: event and engine flags to set or clear, map scene values, items
received and taken back, plus a total `money_hint`, a plausible
`party_hint`, a place to stand (`at`), and a `sources` table giving the
file and line in the 3.2.3 source for each entry. The comment at the top
of the file describes every field. Note that C10_TOWER comes before
C09_RISING, because that is the game's real order.

**`STORY_PRESETS_NOTES.md`**: how the checkpoints were traced from the
3.2.3 scripts, where Polished differs from the original task description
(for example, Oak gives the Pokédex and Fly is not on the main path), the
choices made along the way, what a save needs that isn't a flag, and the
uncertainties. The step-by-step trace of each checkpoint is at the end.

**`check_presets.py`**: re-checks `story_presets.lua` against a Polished
Crystal source checkout. Run `python check_presets.py <polishedcrystal
folder> [story_presets.lua]`. It checks that every flag, item, map, species
and phone name exists in the source's constants, that every `sources`
entry points at a real line that mentions the name, and it replays the
checkpoints in order to catch oddities (a flag set twice, an item taken
that was never given). It exits with status 1 if it finds errors. Use it
after editing the presets, or to check them against another version of the
game.

**`report.py`**: turns the robot's results into a report. Run
`python report.py <results dir> [<more results dirs> ...]`, one dir per
robot window. Each dir holds `results.jsonl` and a `shots/` folder. The
script merges the dirs (one record per `(map, n)`: a later record replaces
an earlier one, but a skipped record never replaces one that ran) and
writes two files into the first dir. `report.html` is a single
self-contained page (no internet needed) with a summary, the "likely
causes" (differences grouped by kind and flag name or first differing text
line, most shared first), a card per case with its differences, text,
pictures and end positions, filters by kind, map and text, and light and
dark themes. `report_summary.md` is a short plain-text summary with the
totals and the top 40 likely causes, for a quick read. UISFX differences
are hidden in the page by default and left out of the summary's top 40.

**`test_data/`**: two sample result folders (`window1`, `window2`) with the
four sample lines from the robot's format plus invented cases covering
every difference kind, duplicates across windows, a skipped case, an
unreadable line and a missing picture. Try the report with
`python report.py test_data/window1 test_data/window2` and open
`test_data/window1/report.html`. The generated files are git-ignored.
