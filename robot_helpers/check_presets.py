#!/usr/bin/env python3
"""Check story_presets.lua against a Polished Crystal 3.2.3 source checkout.

Usage:
    python check_presets.py <polishedcrystal folder> [story_presets.lua]

It checks that every event flag, engine flag, item, key item, TM/HM, map,
species and phone name exists in the source's constants, that every
`sources` entry points at a real file and line that mentions the name, and
it replays the checkpoints in order to spot odd sequences (a flag set twice,
an item taken that was never given). Errors make it exit with status 1;
warnings are printed but don't fail.

Python 3.7+, standard library only.
"""

import os
import re
import sys

# ---------------------------------------------------------------------------
# A small reader for the Lua subset story_presets.lua uses:
# `return` + tables, strings, numbers, true/false/nil and -- comments.

TOKEN = re.compile(r"""
    (?P<ws>\s+|--[^\n]*)
  | (?P<str>"(?:[^"\\\n]|\\.)*"|'(?:[^'\\\n]|\\.)*')
  | (?P<num>-?(?:0[xX][0-9a-fA-F]+|\d+(?:\.\d+)?))
  | (?P<name>[A-Za-z_][A-Za-z0-9_]*)
  | (?P<sym>[{}\[\]=,;])
""", re.VERBOSE)

ESCAPES = {"n": "\n", "t": "\t", "r": "\r", "\\": "\\", '"': '"', "'": "'", "\n": "\n"}


def tokenize(text):
    pos, out = 0, []
    while pos < len(text):
        m = TOKEN.match(text, pos)
        if not m:
            line = text.count("\n", 0, pos) + 1
            raise ValueError("line %d: can't read %r" % (line, text[pos:pos + 20]))
        pos = m.end()
        kind = m.lastgroup
        if kind == "ws":
            continue
        v = m.group()
        if kind == "str":
            v = re.sub(r"\\(.)", lambda e: ESCAPES.get(e.group(1), e.group(1)), v[1:-1], flags=re.S)
        elif kind == "num":
            v = int(v, 16) if v.lower().startswith(("0x", "-0x")) else (float(v) if "." in v else int(v))
        out.append((kind, v))
    return out


class Reader:
    def __init__(self, tokens):
        self.t, self.i = tokens, 0

    def peek(self, k=0):
        return self.t[self.i + k] if self.i + k < len(self.t) else (None, None)

    def take(self, sym=None):
        tok = self.peek()
        if sym is not None and tok != ("sym", sym):
            raise ValueError("expected %r, got %r" % (sym, tok[1]))
        self.i += 1
        return tok

    def value(self):
        kind, v = self.peek()
        if (kind, v) == ("sym", "{"):
            return self.table()
        self.take()
        if kind in ("str", "num"):
            return v
        if kind == "name" and v in ("true", "false", "nil"):
            return {"true": True, "false": False, "nil": None}[v]
        raise ValueError("unexpected %r" % (v,))

    def table(self):
        self.take("{")
        items, keyed = [], {}
        while self.peek() != ("sym", "}"):
            kind, v = self.peek()
            if (kind, v) == ("sym", "["):
                self.take()
                k = self.value()
                self.take("]")
                self.take("=")
                keyed[k] = self.value()
            elif kind == "name" and self.peek(1) == ("sym", "="):
                self.take()
                self.take("=")
                keyed[v] = self.value()
            else:
                items.append(self.value())
            if self.peek() in (("sym", ","), ("sym", ";")):
                self.take()
        self.take("}")
        if keyed and items:
            keyed.update({i + 1: x for i, x in enumerate(items)})
            return keyed
        return keyed if keyed else items


def read_lua(path):
    with open(path, encoding="utf-8") as f:
        tokens = tokenize(f.read())
    r = Reader(tokens)
    if r.peek() == ("name", "return"):
        r.take()
    value = r.value()
    if r.peek() != (None, None):
        raise ValueError("extra text after the returned table")
    return value


# ---------------------------------------------------------------------------
# Names defined in the Polished Crystal source


def read(src, rel):
    with open(os.path.join(src, rel), encoding="utf-8", errors="replace") as f:
        return f.read().splitlines()


def consts(lines, prefix=""):
    names = set()
    for line in lines:
        m = re.match(r"\s*const\s+(%s[A-Z0-9_]+)" % prefix, line) or \
            re.match(r"\s*DEF\s+(%s[A-Z0-9_]+)\s+EQU" % prefix, line)
        if m:
            names.add(m.group(1))
    return names


def engine_bits(src):
    """ENGINE_* name -> the bit name that stores it (data/events/engine_flags.asm),
    because engine code often sets the bit directly (e.g. STATUSFLAGS_HALL_OF_FAME_F)."""
    names = []
    for line in read(src, "constants/engine_flags.asm"):
        m = re.match(r"\s*const\s+([A-Z0-9_]+)", line)
        if m:
            names.append(m.group(1))
        m = re.match(r"\s*const_skip\b\s*(\d*)", line)
        if m:
            names += [None] * int(m.group(1) or 1)
    bits = []
    for line in read(src, "data/events/engine_flags.asm"):
        m = re.match(r"\s*engine_flag\s+\w+\s*,\s*([A-Za-z0-9_]+)", line)
        if m:
            bits.append(m.group(1))
    if len(names) != len(bits):
        return {}
    return {n: b for n, b in zip(names, bits) if n}


def load_names(src):
    items_lines = read(src, "constants/item_constants.asm")
    key_start = next(i for i, l in enumerate(items_lines) if l.startswith("; key item ids"))
    items = {n for n in consts(items_lines[:key_start]) if not n.startswith(("NAM_", "NUM_", "FIRST_"))}
    key_items = {n for n in consts(items_lines[key_start:]) if not n.startswith(("NAM_", "NUM_"))}
    tmhm = set()
    for line in read(src, "constants/tmhm_constants.asm"):
        m = re.match(r"\s*add_(tm|hm)\s+([A-Z0-9_]+)", line)
        if m:
            tmhm.add("%s_%s" % (m.group(1).upper(), m.group(2)))
    maps = set()
    for line in read(src, "constants/map_constants.asm"):
        m = re.match(r"\s*map_const\s+([A-Z0-9_]+)", line)
        if m:
            maps.add(m.group(1))
    scene_maps = set()
    for line in read(src, "data/maps/scenes.asm"):
        m = re.match(r"\s*scene_var\s+([A-Z0-9_]+)", line)
        if m:
            scene_maps.add(m.group(1))
    return {
        "engine_bits": engine_bits(src),
        "event": consts(read(src, "constants/event_flags.asm"), "EVENT_"),
        "engine": consts(read(src, "constants/engine_flags.asm"), "ENGINE_"),
        "item": items,
        "key_item": key_items,
        "tmhm": tmhm,
        "map": maps,
        "scene_map": scene_maps,
        "species": consts(read(src, "constants/pokemon_constants.asm")),
        "phone": consts(read(src, "constants/phone_constants.asm"), "PHONE_"),
    }


# ---------------------------------------------------------------------------


class Report:
    def __init__(self):
        self.errors, self.warnings = [], []

    def error(self, where, msg):
        self.errors.append("%s: %s" % (where, msg))

    def warn(self, where, msg):
        self.warnings.append("%s: %s" % (where, msg))


def names_in(entries):
    """A list of names, or of {name, count} pairs, as plain names."""
    out = []
    for e in entries or []:
        if isinstance(e, str):
            out.append(e)
        elif isinstance(e, list) and e and isinstance(e[0], str):
            out.append(e[0])
        elif isinstance(e, dict) and isinstance(e.get("name") or e.get("species"), str):
            out.append(e.get("name") or e.get("species"))
    return out


def check_source(src, where, key, ref, rep, cache, bits):
    m = re.match(r"^(.+?):(\d+)$", str(ref))
    if not m:
        rep.error(where, "source for %s isn't file:line: %r" % (key, ref))
        return
    rel, line_no = m.group(1), int(m.group(2))
    if rel not in cache:
        path = os.path.join(src, rel)
        cache[rel] = read(src, rel) if os.path.isfile(path) else None
    lines = cache[rel]
    if lines is None:
        rep.error(where, "source file for %s doesn't exist: %s" % (key, rel))
        return
    if not 1 <= line_no <= len(lines):
        rep.error(where, "source line for %s is past the end of %s" % (key, rel))
        return
    text = lines[line_no - 1]
    name = key.split(":", 1)[-1]
    hints = {name}
    if name.startswith("ENGINE_") and name.endswith("BADGE"):
        hints.add(name[len("ENGINE_"):])        # givebadge FOGBADGE, ...
    if name in bits and not bits[name].isdigit():
        hints.add(bits[name])                   # set STATUSFLAGS_HALL_OF_FAME_F, [hl]
    if key.startswith("scene:"):
        hints |= {"setscene", "setmapscene"}
        if "sceneid" in text.lower():  # dwb wGoldenrodCitySceneID, $1
            return
    if not any(h in text for h in hints):
        rep.warn(where, "%s: %s doesn't mention it: %s" % (key, ref, text.strip()[:80]))
    elif re.match(r"\s*(checkevent|checkflag|checkitem|checkkeyitem|checkscene|checkmapscene|iftrue|iffalse)\b", text):
        rep.warn(where, "%s: %s only checks it, it doesn't change it: %s" % (key, ref, text.strip()[:80]))


def check(src, presets):
    names = load_names(src)
    rep = Report()
    cache = {}
    if not isinstance(presets, list) or not presets:
        rep.error("file", "should return a non-empty list of checkpoints")
        return rep
    events, engine, bag = set(), set(), {}
    seen_ids = set()
    for cp in presets:
        cid = cp.get("id", "?") if isinstance(cp, dict) else "?"
        if not isinstance(cp, dict):
            rep.error(cid, "checkpoint isn't a table")
            continue
        if cid in seen_ids:
            rep.error(cid, "duplicate id")
        seen_ids.add(cid)
        for field in ("id", "title", "at", "events_set", "events_clear", "engine_set", "engine_clear",
                      "scenes", "key_items", "tms_hms", "items", "money_hint", "party_hint", "sources", "unsure"):
            if field not in cp:
                rep.error(cid, "missing field %s" % field)
        at = cp.get("at") or {}
        if at.get("map") not in names["map"]:
            rep.error(cid, "at.map %r isn't a map constant" % at.get("map"))
        if not isinstance(at.get("x"), int) or not isinstance(at.get("y"), int):
            rep.error(cid, "at needs whole-number x and y")

        wanted = []  # (source key, kind of name)
        for field, kind in (("events_set", "event"), ("events_clear", "event"),
                            ("engine_set", "engine"), ("engine_clear", "engine"),
                            ("key_items", "key_item"), ("tms_hms", "tmhm"), ("items", "item"),
                            ("phone_numbers", "phone")):
            for n in names_in(cp.get(field)):
                if n not in names[kind]:
                    # An item can live in either list; say which one it belongs to.
                    other = [k for k in ("item", "key_item", "tmhm") if n in names[k]]
                    rep.error(cid, "%s: %s isn't a known %s name%s" % (
                        field, n, kind, (" (it is a %s)" % other[0]) if other else ""))
                wanted.append(n)
        for n in names_in(cp.get("taken")):
            if not any(n in names[k] for k in ("item", "key_item", "tmhm")):
                rep.error(cid, "taken: %s isn't a known item name" % n)
            wanted.append("taken:" + n)
        for s in cp.get("scenes") or []:
            m = s.get("map") if isinstance(s, dict) else None
            if m not in names["map"]:
                rep.error(cid, "scenes: %r isn't a map constant" % m)
            elif m not in names["scene_map"]:
                rep.error(cid, "scenes: %s has no scene variable (data/maps/scenes.asm)" % m)
            if not isinstance(s.get("scene") if isinstance(s, dict) else None, (int, str)):
                rep.error(cid, "scenes: %s needs a scene value" % m)
            wanted.append("scene:%s" % m)
        for p in cp.get("party_hint") or []:
            if not (isinstance(p, list) and len(p) >= 2 and p[0] in names["species"] and isinstance(p[1], int)):
                rep.error(cid, "party_hint entry %r should be { SPECIES, level }" % (p,))
        for p in names_in(cp.get("pokemon_received")):
            if p not in names["species"]:
                rep.error(cid, "pokemon_received: %s isn't a species" % p)
            wanted.append("pokemon:" + p)

        sources = cp.get("sources") or {}
        for key in wanted:
            if key not in sources:
                rep.warn(cid, "no source for %s" % key)
        for key, ref in sources.items():
            check_source(src, cid, str(key), ref, rep, cache, names["engine_bits"])

        # Replay the checkpoints in order.
        for n in names_in(cp.get("events_set")):
            if n in events:
                rep.warn(cid, "%s is already set by an earlier checkpoint" % n)
            events.add(n)
        for n in names_in(cp.get("events_clear")):
            events.discard(n)
        for n in names_in(cp.get("engine_set")):
            if n in engine:
                rep.warn(cid, "%s is already set by an earlier checkpoint" % n)
            engine.add(n)
        for n in names_in(cp.get("engine_clear")):
            engine.discard(n)
        for field in ("key_items", "tms_hms", "items"):
            for e in cp.get(field) or []:
                n = names_in([e])[0] if names_in([e]) else None
                count = e[1] if isinstance(e, list) and len(e) > 1 else 1
                if field != "items" and bag.get(n):
                    rep.warn(cid, "%s was already given by an earlier checkpoint" % n)
                bag[n] = bag.get(n, 0) + count
        for e in cp.get("taken") or []:
            n = names_in([e])[0] if names_in([e]) else None
            count = e[1] if isinstance(e, list) and len(e) > 1 else 1
            if bag.get(n, 0) < count:
                rep.warn(cid, "takes %s, which no earlier checkpoint gave" % n)
            bag[n] = max(0, bag.get(n, 0) - count)
    return rep


def main(argv):
    if len(argv) < 2 or argv[1] in ("-h", "--help"):
        print(__doc__.strip())
        return 0 if len(argv) >= 2 else 2
    src = argv[1]
    lua = argv[2] if len(argv) > 2 else os.path.join(os.path.dirname(os.path.abspath(__file__)), "story_presets.lua")
    if not os.path.isfile(os.path.join(src, "constants/event_flags.asm")):
        print("error: %s doesn't look like a Polished Crystal source folder" % src, file=sys.stderr)
        return 2
    try:
        presets = read_lua(lua)
    except (OSError, ValueError) as e:
        print("error: can't read %s: %s" % (lua, e), file=sys.stderr)
        return 1
    rep = check(src, presets)
    for w in rep.warnings:
        print("warning: " + w)
    for e in rep.errors:
        print("ERROR: " + e)
    print("%d checkpoints, %d errors, %d warnings" % (len(presets), len(rep.errors), len(rep.warnings)))
    return 1 if rep.errors else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
