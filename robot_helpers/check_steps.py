#!/usr/bin/env python3
"""Check story_steps.lua against a Polished Crystal source checkout.

Usage:
    python check_steps.py <polishedcrystal folder> [story_steps.lua] [--presets story_presets.lua]

It checks every step: its kind and fields, that every map, sprite, trainer,
species, item, flag and phone name exists in the source's constants, that
`talk`/`read`/`step` coordinates are a real object_event / bg_event /
coord_event on that map (with the same sprite for `talk`), that other
coordinates are inside the map, and that every `sources` line exists.
Names in `expect` should appear on one of the step's cited lines or on its
event line; if not, it prints a warning.

With --presets, it also replays each chapter's steps and compares the net
flag and scene changes with the matching checkpoint in story_presets.lua
(differences are warnings).

Errors make it exit with status 1. Python 3.7+, standard library only.
"""

import os
import re
import sys

from check_presets import load_names, read, read_lua

KINDS = {"go", "talk", "read", "step", "answer", "battle", "use", "wait"}
CHAPTERS = ["C01_STARTER", "C02_ZEPHYR", "C03_HIVE", "C04_PLAIN", "C05_FOG", "C06_STORM", "C07_MINERAL",
            "C08_GLACIER", "C10_TOWER", "C09_RISING", "C11_CHAMPION", "C12_KANTO", "C13_POSTGAME"]
FIELD_MOVES = {"CUT", "SURF", "STRENGTH", "WHIRLPOOL", "WATERFALL", "ROCK_SMASH", "FLASH", "HEADBUTT",
               "FLY", "DIG", "TELEPORT", "SWEET_SCENT", "FRESH_WATER"}
WATER_MOVES = {"SURF", "WATERFALL", "WHIRLPOOL"}
# Actions that aren't an item or move: tune the Pokegear radio to the Poke Flute station.
SPECIAL_USES = {"POKE_FLUTE_RADIO"}

EVENT_LINE = re.compile(
    r"\s*(object_event|warp_event|coord_event|bg_event|itemball_event|keyitemball_event|tmhmball_event|"
    r"cuttree_event|fruittree_event|strengthboulder_event|smashrock_event|pokemon_event|pc_nurse_event|"
    r"mart_clerk_event)\s+(-?\d+)\s*,\s*(-?\d+)\s*(?:,\s*(\w+))?")


# ---------------------------------------------------------------------------
# Source facts


def map_files(src):
    """Map constant -> maps/<Name>.asm, pairing data/maps/maps.asm with
    constants/map_constants.asm group by group. Also returns map sizes."""
    def groups(rel, start, item):
        out, cur = [], None
        for line in read(src, rel):
            if re.match(start, line):
                cur = []
                out.append(cur)
            m = re.match(item, line)
            if m and cur is not None:
                cur.append(m.groups())
        return out
    names = groups("data/maps/maps.asm", r"^MapGroup\d+:", r"^\s+map\s+(\w+),")
    consts = groups("constants/map_constants.asm", r"^\s+newgroup\b",
                    r"^\s+map_const\s+(\w+),\s*(\d+),\s*(\d+)")
    files, sizes = {}, {}
    for ng, cg in zip(names, consts):
        for (name,), (const, w, h) in zip(ng, cg):
            files[const] = "maps/%s.asm" % name
            sizes[const] = (int(w) * 2, int(h) * 2)  # blocks are 2x2 tiles
    return files, sizes


def map_events(src, rel, cache):
    if rel not in cache:
        events = []
        path = os.path.join(src, rel)
        if os.path.isfile(path):
            for i, line in enumerate(read(src, rel), 1):
                m = EVENT_LINE.match(line)
                if m:
                    events.append({"kind": m.group(1), "x": int(m.group(2)), "y": int(m.group(3)),
                                   "arg": m.group(4), "line": i, "text": line})
        cache[rel] = events
    return cache[rel]


def trainers(src):
    classes, current = {}, None
    for line in read(src, "constants/trainer_constants.asm"):
        m = re.match(r"\s*trainerclass\s+(\w+)", line)
        if m:
            current = m.group(1)
            classes[current] = []
            continue
        m = re.match(r"\s*const\s+(\w+)", line)
        if m and current:
            classes[current].append(m.group(1))
    return classes


def simple_consts(src, rel, pattern):
    return {m.group(1) for line in read(src, rel) for m in [re.match(pattern, line)] if m}


# ---------------------------------------------------------------------------


class Report:
    def __init__(self):
        self.errors, self.warnings = [], []

    def error(self, where, msg):
        self.errors.append("%s: %s" % (where, msg))

    def warn(self, where, msg):
        self.warnings.append("%s: %s" % (where, msg))


def as_list(v):
    if v is None:
        return []
    if isinstance(v, dict):  # a Lua table with holes reads as a dict
        return [v[k] for k in sorted(v) if isinstance(k, int)]
    return v


def name_of(e):
    if isinstance(e, str):
        return e
    e = as_list(e)
    return e[0] if e else None


def check(src, steps, presets=None):
    rep = Report()
    names = load_names(src)
    files, sizes = map_files(src)
    tclasses = trainers(src)
    sprites = simple_consts(src, "constants/sprite_constants.asm", r"\s*const\s+(SPRITE_\w+)")
    moves = simple_consts(src, "constants/move_constants.asm", r"\s*const\s+([A-Z][A-Z0-9_]*)")
    ev_cache, line_cache = {}, {}

    def line(rel, n):
        if rel not in line_cache:
            path = os.path.join(src, rel)
            line_cache[rel] = read(src, rel) if os.path.isfile(path) else None
        lines = line_cache[rel]
        if lines is None or not 1 <= n <= len(lines):
            return None
        return lines[n - 1]

    if not isinstance(steps, list) or not steps:
        rep.error("file", "should return a non-empty list of steps")
        return rep

    seen_ids, last_chapter = set(), 0
    for i, st in enumerate(steps, 1):
        sid = st.get("id", "#%d" % i) if isinstance(st, dict) else "#%d" % i
        if not isinstance(st, dict):
            rep.error(sid, "step isn't a table")
            continue
        if st.get("id") != "S%04d" % i:
            rep.error(sid, "id should be S%04d (steps numbered in order)" % i)
        if sid in seen_ids:
            rep.error(sid, "duplicate id")
        seen_ids.add(sid)
        ch = st.get("checkpoint")
        if ch not in CHAPTERS:
            rep.error(sid, "unknown checkpoint %r" % ch)
        else:
            idx = CHAPTERS.index(ch)
            if idx < last_chapter:
                rep.error(sid, "checkpoint %s is out of order" % ch)
            last_chapter = idx
        kind = st.get("kind")
        if kind not in KINDS:
            rep.error(sid, "unknown kind %r" % kind)
            continue
        if not st.get("title"):
            rep.error(sid, "missing title")
        m = st.get("map")
        if m not in names["map"]:
            rep.error(sid, "map %r isn't a map constant" % m)
            continue
        rel = files.get(m)
        events = map_events(src, rel, ev_cache) if rel else []
        w, h = sizes.get(m, (0, 0))
        event_lines = []

        def at(xk, yk, kinds, what):
            x, y = st.get(xk), st.get(yk)
            if not isinstance(x, int) or not isinstance(y, int):
                rep.error(sid, "%s needs whole-number %s and %s" % (kind, xk, yk))
                return None
            hits = [e for e in events if e["x"] == x and e["y"] == y and e["kind"] in kinds]
            if not hits and what:
                rep.error(sid, "no %s at (%d,%d) in %s" % (what, x, y, rel))
            event_lines.extend(hits)
            return hits

        def in_bounds(xk, yk):
            x, y = st.get(xk), st.get(yk)
            if x is None and y is None:
                return
            if not isinstance(x, int) or not isinstance(y, int):
                rep.error(sid, "%s and %s must be whole numbers" % (xk, yk))
            elif w and not (-1 <= x <= w and -1 <= y <= h):
                rep.error(sid, "(%d,%d) is outside %s (%dx%d tiles)" % (x, y, m, w, h))

        objects = {"object_event", "itemball_event", "keyitemball_event", "tmhmball_event", "cuttree_event",
                   "fruittree_event", "strengthboulder_event", "smashrock_event", "pokemon_event",
                   "pc_nurse_event", "mart_clerk_event"}
        if kind == "go":
            in_bounds("x", "y")
        elif kind == "talk":
            hits = at("target_x", "target_y", objects, "person (object_event)")
            sp = st.get("sprite")
            if sp is not None and sp not in sprites:
                rep.error(sid, "sprite %s isn't a sprite constant" % sp)
            if hits and sp and not any(e["arg"] == sp for e in hits if e["kind"] == "object_event") \
                    and all(e["kind"] == "object_event" for e in hits):
                rep.error(sid, "the object at (%s,%s) is %s, not %s" % (
                    st.get("target_x"), st.get("target_y"), hits[0]["arg"], sp))
        elif kind == "read":
            at("target_x", "target_y", {"bg_event"}, "bg_event")
        elif kind == "step":
            at("x", "y", {"coord_event"}, "coord_event")
        elif kind == "answer":
            if not st.get("choice"):
                rep.error(sid, "answer needs a choice")
        elif kind == "battle":
            if st.get("wild"):
                if st["wild"] not in names["species"]:
                    rep.error(sid, "wild %s isn't a species" % st["wild"])
                if not isinstance(st.get("level"), int):
                    rep.error(sid, "wild battle needs a level")
            else:
                tc, tid = st.get("trainer"), st.get("trainer_id")
                if tc not in tclasses:
                    rep.error(sid, "trainer class %r isn't a trainer class" % tc)
                elif isinstance(tid, str) and tid not in tclasses[tc]:
                    rep.error(sid, "trainer id %s isn't in class %s" % (tid, tc))
                elif not isinstance(tid, (int, str)):
                    rep.error(sid, "battle needs trainer_id")
            if st.get("target_x") is not None:
                at("target_x", "target_y", objects, "trainer object")
        elif kind == "use":
            u = st.get("use")
            if u not in FIELD_MOVES | SPECIAL_USES and u not in moves and u not in names["item"] and u not in names["key_item"]:
                rep.error(sid, "use %r isn't a field move, move or item" % u)
            if st.get("target_x") is not None:
                hits = at("target_x", "target_y", objects | {"bg_event", "coord_event"}, None)
                if not hits:
                    in_bounds("target_x", "target_y")
                    if u not in WATER_MOVES and u != "FLASH":
                        rep.warn(sid, "no object or event at (%s,%s) to use %s on" % (
                            st.get("target_x"), st.get("target_y"), u))

        # expect
        ex = st.get("expect") or {}
        if not isinstance(ex, dict):
            rep.error(sid, "expect should be a table")
            ex = {}
        if ex.get("map") not in names["map"]:
            rep.error(sid, "expect.map %r isn't a map constant" % ex.get("map"))
        wanted = []
        for field, kind_name in (("events_set", "event"), ("events_clear", "event"), ("engine_set", "engine"),
                                 ("engine_clear", "engine"), ("key_items", "key_item"), ("tms_hms", "tmhm"),
                                 ("phone", "phone")):
            for n in as_list(ex.get(field)):
                if n not in names[kind_name]:
                    rep.error(sid, "expect.%s: %s isn't a known %s name" % (field, n, kind_name))
                wanted.append(n)
        for field in ("items", "taken"):
            for e in as_list(ex.get(field)):
                n = name_of(e)
                if not any(n in names[k] for k in ("item", "key_item", "tmhm")):
                    rep.error(sid, "expect.%s: %s isn't an item" % (field, n))
                wanted.append(n)
        for e in as_list(ex.get("pokemon")):
            n = name_of(e)
            if n not in names["species"]:
                rep.error(sid, "expect.pokemon: %s isn't a species" % n)
            wanted.append(n)
        for s in as_list(ex.get("scenes")):
            sm = s.get("map") if isinstance(s, dict) else None
            if sm not in names["scene_map"]:
                rep.error(sid, "expect.scenes: %r has no scene variable" % sm)

        # sources
        srcs = as_list(st.get("sources"))
        if not srcs:
            rep.error(sid, "no sources")
        cited = [e["text"] for e in event_lines]
        for ref in srcs:
            mm = re.match(r"^(.+?):(\d+)$", str(ref))
            if not mm:
                rep.error(sid, "source isn't file:line: %r" % ref)
                continue
            text = line(mm.group(1), int(mm.group(2)))
            if text is None:
                rep.error(sid, "source line doesn't exist: %s" % ref)
            else:
                cited.append(text)
        joined = "\n".join(cited)
        bits = names["engine_bits"]
        for n in wanted:
            hints = {n}
            if n.startswith("ENGINE_") and n.endswith("BADGE"):
                hints.add(n[len("ENGINE_"):])
            if n in bits and not bits[n].isdigit():
                hints.add(bits[n])
            if not any(re.search(r"\b%s\b" % re.escape(h), joined) for h in hints):
                rep.warn(sid, "%s isn't on any cited line" % n)

    if presets is not None:
        compare_with_presets(steps, presets, rep)
    return rep


def compare_with_presets(steps, presets, rep):
    """Replay each chapter's steps and compare net changes with the checkpoint."""
    by_id = {c.get("id"): c for c in presets if isinstance(c, dict)}
    events, engine = set(), set()
    scenes = {}
    for ch in CHAPTERS:
        cp = by_id.get(ch)
        chapter = [s for s in steps if isinstance(s, dict) and s.get("checkpoint") == ch]
        if not cp:
            continue
        before_ev, before_en, before_sc = set(events), set(engine), dict(scenes)
        # Flags the game sets itself at a new game come from InitializeEvents, not from steps.
        init = {k for k, v in (cp.get("sources") or {}).items() if "initialize_events.asm" in str(v)}
        if not chapter:
            events = (before_ev | set(as_list(cp.get("events_set")))) - set(as_list(cp.get("events_clear")))
            engine = (before_en | set(as_list(cp.get("engine_set")))) - set(as_list(cp.get("engine_clear")))
            for s in as_list(cp.get("scenes")):
                scenes[s["map"]] = s["scene"]
            continue
        if ch == CHAPTERS[0]:
            events |= {n for n in as_list(cp.get("events_set")) if n in init}
            engine |= {n for n in as_list(cp.get("engine_set")) if n in init}
            for s in as_list(cp.get("scenes")):
                if "scene:" + s["map"] in init:
                    scenes[s["map"]] = s["scene"]
        for st in chapter:
            ex = st.get("expect") or {}
            for n in as_list(ex.get("events_set")):
                events.add(n)
            for n in as_list(ex.get("events_clear")):
                events.discard(n)
            for n in as_list(ex.get("engine_set")):
                engine.add(n)
            for n in as_list(ex.get("engine_clear")):
                engine.discard(n)
            for s in as_list(ex.get("scenes")):
                if isinstance(s, dict):
                    scenes[s.get("map")] = s.get("scene")
        got = {
            "events_set": (events - before_ev), "events_clear": (before_ev - events),
            "engine_set": (engine - before_en), "engine_clear": (before_en - engine),
        }
        for field, have in got.items():
            want = set(as_list(cp.get(field)))
            # A preset may clear or set a flag that was already in that state; ignore those.
            if field == "events_clear":
                want = {n for n in want if n in before_ev}
            if field == "engine_clear":
                want = {n for n in want if n in before_en}
            if field == "events_set":
                want = {n for n in want if n not in before_ev}
            if field == "engine_set":
                want = {n for n in want if n not in before_en}
            missing, extra = sorted(want - have), sorted(have - want)
            if missing:
                rep.warn(ch, "%s: in the checkpoint but not in the steps: %s" % (field, ", ".join(missing)))
            if extra:
                rep.warn(ch, "%s: in the steps but not in the checkpoint: %s" % (field, ", ".join(extra)))
        for s in as_list(cp.get("scenes")):
            if scenes.get(s["map"], 0) != s["scene"]:
                rep.warn(ch, "scene %s: checkpoint says %s, steps end at %s" % (s["map"], s["scene"], scenes.get(s["map"], 0)))
        # Keep the replay in step with the checkpoint, so one chapter's gap
        # doesn't repeat in every later chapter.
        events = (before_ev | set(as_list(cp.get("events_set")))) - set(as_list(cp.get("events_clear")))
        engine = (before_en | set(as_list(cp.get("engine_set")))) - set(as_list(cp.get("engine_clear")))
        scenes = dict(before_sc)
        for s in as_list(cp.get("scenes")):
            scenes[s["map"]] = s["scene"]
        last = chapter[-1] if chapter else None
        at = cp.get("at") or {}
        if last and not (last.get("kind") == "go" and last.get("map") == at.get("map")
                         and last.get("x") == at.get("x") and last.get("y") == at.get("y")):
            rep.warn(ch, "the chapter doesn't end with a go to the checkpoint's at (%s %s,%s)" % (
                at.get("map"), at.get("x"), at.get("y")))


def main(argv):
    args = [a for a in argv[1:] if not a.startswith("--")]
    if not args or "-h" in argv or "--help" in argv:
        print(__doc__.strip())
        return 0 if args else 2
    presets_path = None
    if "--presets" in argv:
        i = argv.index("--presets")
        presets_path = argv[i + 1] if i + 1 < len(argv) else None
        if presets_path in args:
            args.remove(presets_path)
    src = args[0]
    here = os.path.dirname(os.path.abspath(__file__))
    lua = args[1] if len(args) > 1 else os.path.join(here, "story_steps.lua")
    if not os.path.isfile(os.path.join(src, "constants/event_flags.asm")):
        print("error: %s doesn't look like a Polished Crystal source folder" % src, file=sys.stderr)
        return 2
    try:
        steps = read_lua(lua)
        presets = read_lua(presets_path) if presets_path else None
    except (OSError, ValueError) as e:
        print("error: %s" % e, file=sys.stderr)
        return 1
    rep = check(src, steps, presets)
    for w in rep.warnings:
        print("warning: " + w)
    for e in rep.errors:
        print("ERROR: " + e)
    print("%d steps, %d errors, %d warnings" % (len(steps), len(rep.errors), len(rep.warnings)))
    return 1 if rep.errors else 0


if __name__ == "__main__":
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    sys.exit(main(sys.argv))
