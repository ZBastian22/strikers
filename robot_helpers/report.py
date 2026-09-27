#!/usr/bin/env python3
"""Turn the test robot's results into a report page and a short summary.

Usage:
    python report.py <results dir> [<more results dirs> ...]

Each results dir holds a `results.jsonl` (one JSON object per line) and a
`shots/` folder with pictures. The robot runs in several windows at once, so
there is one dir per window. This script merges them (one record per
`(map, n)`) and writes, into the FIRST dir:

    report.html         a self-contained page (inline CSS/JS, no internet)
    report_summary.md   a compact text summary for a quick read

Python 3.7+, standard library only.
"""

import html
import json
import os
import pathlib
import sys
import time
import urllib.parse
from collections import Counter, OrderedDict

SEVERITY = [
    "ERROR", "STUCK", "NOTHING", "EXTRA", "BATTLE", "TEXT", "YESNO", "MENU",
    "WARP", "FLAG", "ENGINE", "ITEM", "PARTY", "MONEY", "SCENE", "MUSIC",
    "CRY", "SFX", "UISFX",
]
SEVERITY_RANK = {k: i for i, k in enumerate(SEVERITY)}
HIDDEN_BY_DEFAULT = {"UISFX"}
TOP_CAUSES = 40
EXAMPLES_PER_CAUSE = 3
MAX_VALUE_CHARS = 70  # for values in the summary


# ---------------------------------------------------------------------------
# Loading and merging


def load_dir(folder):
    """Read <folder>/results.jsonl. Returns (records, bad_line_count)."""
    path = os.path.join(folder, "results.jsonl")
    records, bad = [], 0
    if not os.path.isfile(path):
        print("warning: no results.jsonl in %s" % folder, file=sys.stderr)
        return records, bad
    with open(path, encoding="utf-8", errors="replace") as f:
        for line_no, line in enumerate(f, 1):
            line = line.strip()
            if not line:
                continue
            try:
                rec = json.loads(line)
            except ValueError:
                bad += 1
                continue
            if not isinstance(rec, dict):
                bad += 1
                continue
            rec["_dir"] = folder
            rec["_line"] = line_no
            records.append(rec)
    return records, bad


def case_of(rec):
    c = rec.get("case")
    return c if isinstance(c, dict) else {}


def record_key(rec):
    c = case_of(rec)
    m = str(rec.get("map") or c.get("map") or "?")
    n = rec.get("n", c.get("n"))
    if n is None:
        # No case number: never merge it with anything else.
        return (m, "line %s:%d" % (rec["_dir"], rec["_line"]))
    return (m, n)


def merge(all_records):
    """One record per (map, n). A later record replaces an earlier one,
    except that a skipped record never replaces one that actually ran."""
    merged = OrderedDict()
    dropped = 0
    for rec in all_records:
        k = record_key(rec)
        old = merged.get(k)
        if old is not None:
            dropped += 1
            if rec.get("skipped") and not old.get("skipped"):
                continue
        merged[k] = rec
    return list(merged.values()), dropped


def sort_key(rec):
    m, n = rec["_map"], rec["_n"]
    if isinstance(n, (int, float)):
        return (m, 0, n, "")
    return (m, 1, 0, str(n))


# ---------------------------------------------------------------------------
# Helpers


def fmt(v):
    """A value from the results as short plain text."""
    if v is None:
        return ""
    if isinstance(v, str):
        return v
    if isinstance(v, bool):
        return "true" if v else "false"
    if isinstance(v, (int, float)):
        return str(v)
    return json.dumps(v, ensure_ascii=False, separators=(",", ":"))


def clip(s, n=MAX_VALUE_CHARS):
    s = s.replace("\n", " ")
    return s if len(s) <= n else s[: n - 1] + "…"


def esc(v):
    return html.escape(fmt(v), quote=True)


def kind_rank(kind):
    return SEVERITY_RANK.get(kind, len(SEVERITY))


def kind_order(kinds):
    return sorted(kinds, key=lambda k: (kind_rank(k), k))


def sev_class(kind):
    r = kind_rank(kind)
    if r <= 1:
        return "sev0"  # ERROR, STUCK
    if r <= 4:
        return "sev1"  # NOTHING, EXTRA, BATTLE
    if r <= 8:
        return "sev2"  # TEXT, YESNO, MENU, WARP
    if r <= 14:
        return "sev3"  # FLAG .. SCENE
    return "sev4"      # sounds and anything unknown


def lines_of(rec, side):
    v = rec.get(side + "Lines")
    return [fmt(x) for x in v] if isinstance(v, list) else []


def first_diff_line(rec):
    """Index of the first line where cart and port text differ, or -1."""
    cart, port = lines_of(rec, "cart"), lines_of(rec, "port")
    for i in range(max(len(cart), len(port))):
        a = cart[i] if i < len(cart) else None
        b = port[i] if i < len(port) else None
        if a != b:
            return i
    return -1


def diffs_of(rec):
    out = []
    for d in rec.get("diffs") or []:
        if isinstance(d, dict):
            d = dict(d)
            d["kind"] = str(d.get("kind") or "?").upper()
            out.append(d)
    return out


def cause_key(diff, rec):
    """What a difference is grouped by in "likely causes"."""
    kind = diff["kind"]
    if kind == "TEXT":
        i = rec["_first_diff"]
        if i >= 0:
            cart, port = rec["_cart_lines"], rec["_port_lines"]
            a = cart[i] if i < len(cart) else "(no line)"
            b = port[i] if i < len(port) else "(no line)"
        else:
            a, b = fmt(diff.get("cart")), fmt(diff.get("port"))
        return (kind, "cart: “%s” / port: “%s”" % (a, b))
    # FLAG, ENGINE, ITEM and SCENE carry the flag/item/map name in `detail`.
    return (kind, fmt(diff.get("detail")))


def value_of(diff):
    v = "cart: %s → port: %s" % (fmt(diff.get("cart")) or "-", fmt(diff.get("port")) or "-")
    if "before" in diff:
        v += " (before: %s)" % (fmt(diff.get("before")) or "-")
    return v


def where_text(w):
    if not isinstance(w, dict):
        return "?"
    return "%s %s,%s %s" % (w.get("map", "?"), fmt(w.get("x")), fmt(w.get("y")), fmt(w.get("facing")))


def shots_url(rec_dir, first_dir):
    """URL of rec_dir/shots as seen from the report in first_dir."""
    target = os.path.join(os.path.abspath(rec_dir), "shots")
    try:
        rel = os.path.relpath(target, os.path.abspath(first_dir))
    except ValueError:  # e.g. another drive on Windows
        return pathlib.Path(target).as_uri()
    parts = rel.replace(os.sep, "/").split("/")
    return "/".join(urllib.parse.quote(p) for p in parts)


# ---------------------------------------------------------------------------
# Analysis


def analyse(records):
    stats = {
        "cases": len(records),
        "skipped": 0,
        "run": 0,
        "with_diffs": 0,
        "kind_cases": Counter(),
        "kind_diffs": Counter(),
        "maps": OrderedDict(),
        "skip_reasons": Counter(),
        "skip_examples": {},
        "case_kinds": Counter(),
    }
    groups = {}
    for rec in records:
        m = rec["_map"]
        ms = stats["maps"].setdefault(m, {"cases": 0, "skipped": 0, "diffs": 0})
        ms["cases"] += 1
        stats["case_kinds"][rec["_ckind"]] += 1
        if rec.get("skipped"):
            stats["skipped"] += 1
            ms["skipped"] += 1
            reason = fmt(rec.get("skipped"))
            stats["skip_reasons"][reason] += 1
            stats["skip_examples"].setdefault(reason, []).append(rec)
            continue
        stats["run"] += 1
        if not rec["_diffs"]:
            continue
        stats["with_diffs"] += 1
        ms["diffs"] += 1
        for kind in {d["kind"] for d in rec["_diffs"]}:
            stats["kind_cases"][kind] += 1
        for d in rec["_diffs"]:
            stats["kind_diffs"][d["kind"]] += 1
            key = cause_key(d, rec)
            g = groups.get(key)
            if g is None:
                g = groups[key] = {"kind": key[0], "label": key[1], "cases": OrderedDict(), "values": Counter()}
            g["cases"][rec["_id"]] = rec
            g["values"][value_of(d)] += 1
    ordered = sorted(groups.values(), key=lambda g: (-len(g["cases"]), kind_rank(g["kind"]), g["label"]))
    return stats, ordered


# ---------------------------------------------------------------------------
# HTML

CSS = r"""
:root {
  --bg: #f6f7f9; --panel: #ffffff; --panel2: #eef0f4; --text: #1d2330; --muted: #5e6778;
  --line: #d8dce4; --accent: #2f6fdb; --hl: #fff1b8; --hltext: #1d2330;
  --sev0: #c62828; --sev1: #d9730d; --sev2: #9a7b00; --sev3: #2f6fdb; --sev4: #6b7280;
  color-scheme: light;
}
@media (prefers-color-scheme: dark) {
  :root:not([data-theme="light"]) {
    --bg: #14171d; --panel: #1c2028; --panel2: #252a34; --text: #e4e7ee; --muted: #9aa3b5;
    --line: #333a47; --accent: #6ea0ff; --hl: #5a4a10; --hltext: #fff4c8;
    --sev0: #ff6b6b; --sev1: #ffa24d; --sev2: #e3c34d; --sev3: #6ea0ff; --sev4: #9aa3b5;
    color-scheme: dark;
  }
}
:root[data-theme="dark"] {
  --bg: #14171d; --panel: #1c2028; --panel2: #252a34; --text: #e4e7ee; --muted: #9aa3b5;
  --line: #333a47; --accent: #6ea0ff; --hl: #5a4a10; --hltext: #fff4c8;
  --sev0: #ff6b6b; --sev1: #ffa24d; --sev2: #e3c34d; --sev3: #6ea0ff; --sev4: #9aa3b5;
  color-scheme: dark;
}
* { box-sizing: border-box; }
body { margin: 0; background: var(--bg); color: var(--text);
  font: 14px/1.45 system-ui, -apple-system, "Segoe UI", Roboto, sans-serif; }
header, main { max-width: 1200px; margin: 0 auto; padding: 0 16px; }
header { padding-top: 16px; display: flex; gap: 12px; align-items: baseline; flex-wrap: wrap; }
h1 { font-size: 22px; margin: 0; }
h2 { font-size: 18px; margin: 28px 0 10px; }
h3 { font-size: 15px; margin: 16px 0 8px; }
.muted { color: var(--muted); }
.mono, code, td.v, .lines td { font-family: ui-monospace, "Cascadia Mono", Consolas, monospace; font-size: 12.5px; }
a { color: var(--accent); }
button, select, input { font: inherit; color: var(--text); background: var(--panel);
  border: 1px solid var(--line); border-radius: 6px; padding: 4px 8px; }
button { cursor: pointer; }
#theme { margin-left: auto; }
.filters { position: sticky; top: 0; z-index: 5; background: var(--bg); border-bottom: 1px solid var(--line);
  padding: 8px 0; display: flex; flex-wrap: wrap; gap: 8px 14px; align-items: center; }
.filters .kinds { display: flex; flex-wrap: wrap; gap: 4px 10px; }
.filters label { white-space: nowrap; }
#q { min-width: 200px; flex: 1; }
.tiles { display: flex; flex-wrap: wrap; gap: 10px; }
.tile { background: var(--panel); border: 1px solid var(--line); border-radius: 8px; padding: 10px 14px; min-width: 130px; }
.tile b { display: block; font-size: 22px; }
table { border-collapse: collapse; width: 100%; }
th, td { text-align: left; padding: 4px 8px; border-bottom: 1px solid var(--line); vertical-align: top; }
th { color: var(--muted); font-weight: 600; }
td.num, th.num { text-align: right; }
.tablewrap { overflow-x: auto; background: var(--panel); border: 1px solid var(--line); border-radius: 8px; }
.tablewrap.scroll { max-height: 360px; overflow-y: auto; }
.cols { display: grid; grid-template-columns: repeat(auto-fit, minmax(260px, 1fr)); gap: 14px; align-items: start; }
.cols td, .cols th { padding: 2px 8px; }
.chip { display: inline-block; padding: 0 6px; border-radius: 4px; font-weight: 700; font-size: 12px;
  color: #fff; background: var(--sev4); }
.chip.sev0 { background: var(--sev0); } .chip.sev1 { background: var(--sev1); }
.chip.sev2 { background: var(--sev2); } .chip.sev3 { background: var(--sev3); }
:root[data-theme="dark"] .chip { color: #111; }
@media (prefers-color-scheme: dark) { :root:not([data-theme="light"]) .chip { color: #111; } }
details.cause { background: var(--panel); border: 1px solid var(--line); border-radius: 8px; margin: 6px 0; }
details.cause > summary { cursor: pointer; padding: 8px 10px; }
details.cause .sample { display: block; margin: 2px 0 0 44px; word-break: break-word; }
details.cause > div { padding: 0 12px 10px 28px; }
.count { display: inline-block; min-width: 36px; font-weight: 700; }
.label { word-break: break-word; }
.caselist { columns: 3 220px; margin: 6px 0 0; padding-left: 18px; }
.card { background: var(--panel); border: 1px solid var(--line); border-radius: 10px; padding: 12px 14px; margin: 12px 0; }
.card.pinned { outline: 2px solid var(--accent); }
.card h3 { margin: 14px 0 6px; }
.card > h3:first-child { margin: 0 0 4px; }
.card .meta { color: var(--muted); margin-bottom: 8px; word-break: break-word; }
.lines { width: 100%; }
.lines td { border: none; padding: 1px 6px; white-space: pre-wrap; word-break: break-word; width: 50%; }
.lines td.n { width: 2em; color: var(--muted); text-align: right; }
.lines tr.first td { background: var(--hl); color: var(--hltext); }
.shots { display: grid; grid-template-columns: repeat(2, minmax(0, 320px)); gap: 12px; }
.shots figure { margin: 0; }
.shots img { width: 100%; image-rendering: pixelated; border: 1px solid var(--line); border-radius: 4px; }
.shots figcaption { color: var(--muted); font-size: 12px; }
.missing { display: block; padding: 20px; border: 1px dashed var(--line); color: var(--muted); border-radius: 4px; }
.differs { color: var(--sev1); font-weight: 600; }
.empty { color: var(--muted); font-style: italic; }
[hidden] { display: none !important; }
@media (max-width: 640px) { .shots { grid-template-columns: 1fr; } .caselist { columns: 1; } }
"""

HEAD_JS = r"""
function imgMissing(img) {
  var s = document.createElement('span');
  s.className = 'missing';
  s.textContent = 'no picture: ' + img.getAttribute('src');
  img.replaceWith(s);
}
(function () {
  try {
    var t = localStorage.getItem('robot-report-theme');
    if (t === 'light' || t === 'dark') document.documentElement.setAttribute('data-theme', t);
  } catch (e) {}
})();
"""

BODY_JS = r"""
(function () {
  var root = document.documentElement;
  var themeBtn = document.getElementById('theme');
  function themeLabel() {
    var t = root.getAttribute('data-theme') || 'auto';
    themeBtn.textContent = 'Theme: ' + t;
  }
  themeBtn.addEventListener('click', function () {
    var t = root.getAttribute('data-theme');
    var next = t === 'light' ? 'dark' : t === 'dark' ? null : 'light';
    if (next) root.setAttribute('data-theme', next); else root.removeAttribute('data-theme');
    try { if (next) localStorage.setItem('robot-report-theme', next); else localStorage.removeItem('robot-report-theme'); } catch (e) {}
    themeLabel();
  });
  themeLabel();

  var kindBoxes = Array.prototype.slice.call(document.querySelectorAll('input.kind'));
  var mapSel = document.getElementById('map');
  var ckindSel = document.getElementById('ckind');
  var q = document.getElementById('q');
  var cards = Array.prototype.slice.call(document.querySelectorAll('.card'));
  var causes = Array.prototype.slice.call(document.querySelectorAll('details.cause'));
  var shown = document.getElementById('shown');

  function text(el) {
    if (el._text === undefined) el._text = el.textContent.toLowerCase();
    return el._text;
  }

  function apply() {
    var kinds = {};
    kindBoxes.forEach(function (b) { if (b.checked) kinds[b.value] = true; });
    var map = mapSel.value, ck = ckindSel.value, needle = q.value.trim().toLowerCase();
    var visible = 0;
    cards.forEach(function (card) {
      card.classList.remove('pinned');
      var ok = (!map || card.dataset.map === map) && (!ck || card.dataset.ckind === ck);
      if (ok && needle) ok = text(card).indexOf(needle) >= 0;
      var anyRow = false;
      card.querySelectorAll('tr.diff').forEach(function (tr) {
        var vis = !!kinds[tr.dataset.kind];
        tr.hidden = !vis;
        if (vis) anyRow = true;
      });
      card.hidden = !(ok && anyRow);
      if (!card.hidden) visible++;
    });
    shown.textContent = visible + ' of ' + cards.length + ' cases with differences shown';
    causes.forEach(function (g) {
      if (!kinds[g.dataset.kind]) { g.hidden = true; return; }
      var labelHit = !needle || text(g.querySelector('summary')).indexOf(needle) >= 0;
      var any = 0;
      g.querySelectorAll('li[data-map]').forEach(function (li) {
        var ok = (!map || li.dataset.map === map) && (!ck || li.dataset.ckind === ck);
        if (ok && needle && !labelHit) {
          var card = document.getElementById(li.dataset.card);
          ok = text(li).indexOf(needle) >= 0 || (!!card && text(card).indexOf(needle) >= 0);
        }
        li.hidden = !ok;
        if (ok) any++;
      });
      g.hidden = any === 0;
    });
  }

  kindBoxes.forEach(function (b) { b.addEventListener('change', apply); });
  mapSel.addEventListener('change', apply);
  ckindSel.addEventListener('change', apply);
  q.addEventListener('input', apply);
  document.getElementById('allkinds').addEventListener('click', function () {
    kindBoxes.forEach(function (b) { b.checked = true; }); apply();
  });
  document.getElementById('nokinds').addEventListener('click', function () {
    kindBoxes.forEach(function (b) { b.checked = false; }); apply();
  });
  document.querySelectorAll('[data-onlykind]').forEach(function (a) {
    a.addEventListener('click', function (e) {
      e.preventDefault();
      kindBoxes.forEach(function (b) { b.checked = b.value === a.dataset.onlykind; });
      apply();
      document.getElementById('causes').scrollIntoView();
    });
  });
  document.querySelectorAll('[data-setmap]').forEach(function (a) {
    a.addEventListener('click', function (e) {
      e.preventDefault();
      mapSel.value = a.dataset.setmap;
      apply();
      document.getElementById('causes').scrollIntoView();
    });
  });
  // A link to a case always shows that case, even when filters hide it.
  document.addEventListener('click', function (e) {
    var a = e.target.closest ? e.target.closest('a[href^="#case-"]') : null;
    if (!a) return;
    var card = document.getElementById(a.getAttribute('href').slice(1));
    if (card && card.hidden) {
      card.hidden = false;
      card.classList.add('pinned');
      card.querySelectorAll('tr.diff').forEach(function (tr) { tr.hidden = false; });
    }
  });
  apply();
})();
"""


def render_case_header(rec):
    c = case_of(rec)
    parts = ["<b>%s</b>" % esc(rec["_ckind"] or "?")]
    if "x" in c or "y" in c:
        s = "stood at (%s,%s)" % (esc(c.get("x")), esc(c.get("y")))
        if c.get("facing"):
            s += " facing %s" % esc(c.get("facing"))
        parts.append(s)
    if "tx" in c or "ty" in c:
        parts.append("target (%s,%s)" % (esc(c.get("tx")), esc(c.get("ty"))))
    shown = {"map", "n", "kind", "x", "y", "facing", "tx", "ty"}
    extra = ["%s=%s" % (esc(k), esc(v)) for k, v in c.items() if k not in shown]
    if extra:
        parts.append('<span class="mono">%s</span>' % " ".join(extra))
    return " · ".join(parts)


def render_lines(rec):
    cart, port = rec["_cart_lines"], rec["_port_lines"]
    if not cart and not port:
        return '<p class="empty">No text on either side.</p>'
    first = rec["_first_diff"]
    rows = []
    for i in range(max(len(cart), len(port))):
        a = cart[i] if i < len(cart) else ""
        b = port[i] if i < len(port) else ""
        cls = ' class="first"' if i == first else ""
        rows.append('<tr%s><td class="n">%d</td><td>%s</td><td>%s</td></tr>'
                    % (cls, i + 1, html.escape(a), html.escape(b)))
    return ('<table class="lines"><tr><th></th><th>cartridge text</th><th>port text</th></tr>%s</table>'
            % "".join(rows))


def render_shots(rec, first_dir):
    stem = rec.get("shot")
    if not stem:
        return '<p class="empty">No pictures for this case.</p>'
    base = shots_url(rec["_dir"], first_dir)
    figs = []
    for side, name in (("cart", "cartridge"), ("port", "port")):
        src = "%s/%s" % (base, urllib.parse.quote("%s_%s.png" % (fmt(stem), side)))
        figs.append('<figure><img loading="lazy" src="%s" alt="%s picture" onerror="imgMissing(this)">'
                    '<figcaption>%s</figcaption></figure>' % (html.escape(src, quote=True), name, name))
    return '<div class="shots">%s</div>' % "".join(figs)


def render_card(rec, first_dir):
    rows = []
    for d in rec["_diffs"]:
        k = d["kind"]
        before = esc(d["before"]) if "before" in d else '<span class="muted">–</span>'
        rows.append('<tr class="diff" data-kind="%s"><td><span class="chip %s">%s</span></td>'
                    '<td class="v">%s</td><td class="v">%s</td><td class="v">%s</td><td class="v">%s</td></tr>'
                    % (esc(k), sev_class(k), esc(k), esc(d.get("detail")), esc(d.get("cart")),
                       esc(d.get("port")), before))
    cw, pw = where_text(rec.get("cartWhere")), where_text(rec.get("portWhere"))
    where_cls = ' class="differs"' if cw != pw else ""
    ends = []
    for side, name in (("cart", "cartridge"), ("port", "port")):
        end = rec.get(side + "End")
        frames = rec.get("frames") if isinstance(rec.get("frames"), dict) else {}
        ends.append("%s stopped: %s, %s frames" % (name, esc(end) if end else "normally", esc(frames.get(side, "?"))))
    return (
        '<article class="card" id="%s" data-map="%s" data-ckind="%s">'
        '<h3>%s #%s</h3><div class="meta">%s</div>'
        '<div class="tablewrap"><table><tr><th>kind</th><th>detail</th><th>cartridge</th><th>port</th><th>before</th></tr>%s</table></div>'
        '<h3>Text</h3>%s'
        '<h3>Pictures</h3>%s'
        '<h3>Where each side ended</h3>'
        '<table><tr><th>cartridge</th><th>port</th></tr><tr%s><td class="v">%s</td><td class="v">%s</td></tr></table>'
        '<p class="muted">%s · %s</p>'
        '</article>'
        % (rec["_id"], esc(rec["_map"]), esc(rec["_ckind"]), esc(rec["_map"]), esc(rec["_n"]),
           render_case_header(rec), "".join(rows), render_lines(rec), render_shots(rec, first_dir),
           where_cls, html.escape(cw), html.escape(pw), ends[0], ends[1])
    )


def case_link(rec):
    return ('<li data-map="%s" data-ckind="%s" data-card="%s"><a href="#%s">%s #%s</a> <span class="muted">%s</span></li>'
            % (esc(rec["_map"]), esc(rec["_ckind"]), rec["_id"], rec["_id"], esc(rec["_map"]), esc(rec["_n"]),
               esc(rec["_ckind"])))


def render_html(stats, groups, records, dirs, extra):
    first_dir = dirs[0]
    kinds_present = kind_order(set(stats["kind_diffs"]))
    # Kind checkboxes: every known kind that occurs, plus unknown ones.
    kind_boxes = []
    for k in kinds_present:
        checked = "" if k in HIDDEN_BY_DEFAULT else " checked"
        kind_boxes.append('<label><input type="checkbox" class="kind" value="%s"%s> <span class="chip %s">%s</span> %d</label>'
                          % (esc(k), checked, sev_class(k), esc(k), stats["kind_cases"][k]))
    maps = sorted(stats["maps"])
    map_opts = "".join('<option value="%s">%s</option>' % (esc(m), esc(m)) for m in maps)
    ckind_opts = "".join('<option value="%s">%s</option>' % (esc(k), esc(k)) for k in sorted(stats["case_kinds"]))

    tiles = "".join('<div class="tile"><b>%s</b>%s</div>' % (v, t) for t, v in (
        ("cases", stats["cases"]), ("run", stats["run"]), ("skipped", stats["skipped"]),
        ("with differences", stats["with_diffs"]), ("identical", stats["run"] - stats["with_diffs"]),
        ("likely causes", len(groups))))

    kind_rows = "".join(
        '<tr><td><a href="#" data-onlykind="%s"><span class="chip %s">%s</span></a></td><td class="num">%d</td><td class="num">%d</td></tr>'
        % (esc(k), sev_class(k), esc(k), stats["kind_cases"][k], stats["kind_diffs"][k]) for k in kinds_present
    ) or '<tr><td colspan="3" class="empty">No differences.</td></tr>'

    map_rows = "".join(
        '<tr><td><a href="#" data-setmap="%s">%s</a></td><td class="num">%d</td><td class="num">%d</td><td class="num">%d</td></tr>'
        % (esc(m), esc(m), s["cases"], s["skipped"], s["diffs"])
        for m, s in sorted(stats["maps"].items(), key=lambda kv: (-kv[1]["diffs"], kv[0]))
    )

    skip_rows = "".join(
        '<tr><td>%s</td><td class="num">%d</td><td class="mono">%s</td></tr>'
        % (esc(r), c, " ".join("%s #%s" % (esc(x["_map"]), esc(x["_n"])) for x in stats["skip_examples"][r][:5]))
        for r, c in stats["skip_reasons"].most_common()
    ) or '<tr><td colspan="3" class="empty">Nothing skipped.</td></tr>'

    cause_html = []
    for g in groups:
        (value, vcount), = g["values"].most_common(1)
        more = len(g["values"]) - 1
        values_html = "".join('<li class="mono">%s <span class="muted">× %d</span></li>' % (html.escape(v), c)
                              for v, c in g["values"].most_common(8))
        cause_html.append(
            '<details class="cause" data-kind="%s"><summary><span class="count">%d</span> '
            '<span class="chip %s">%s</span> <span class="label mono">%s</span> '
            '<span class="sample muted mono">%s%s</span></summary><div>'
            '<h3>Values seen</h3><ul>%s</ul><h3>Cases</h3><ul class="caselist">%s</ul></div></details>'
            % (esc(g["kind"]), len(g["cases"]), sev_class(g["kind"]), esc(g["kind"]), html.escape(g["label"]),
               html.escape(clip(value, 120)), (" (+%d other values)" % more) if more else "",
               values_html, "".join(case_link(r) for r in g["cases"].values()))
        )

    cards = [render_card(r, first_dir) for r in records if r["_diffs"] and not r.get("skipped")]

    note = "Merged %d records from %d folder(s); %d duplicate(s) replaced; %d unreadable line(s)." % (
        extra["loaded"], len(dirs), extra["dropped"], extra["bad"])
    return """<!doctype html>
<html lang="en"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Robot Test Report</title>
<style>%(css)s</style>
<script>%(head_js)s</script>
</head><body>
<header><h1>Robot test report</h1>
<span class="muted">%(when)s · %(dirs)s</span>
<button id="theme" type="button">Theme</button></header>
<main>
<p class="muted">%(note)s</p>
<div class="filters">
  <div class="kinds">%(kind_boxes)s</div>
  <button type="button" id="allkinds">all kinds</button>
  <button type="button" id="nokinds">no kinds</button>
  <label>map <select id="map"><option value="">all maps</option>%(map_opts)s</select></label>
  <label>case <select id="ckind"><option value="">all</option>%(ckind_opts)s</select></label>
  <input id="q" type="search" placeholder="search text, flags, maps…">
  <span id="shown" class="muted"></span>
</div>

<h2>Summary</h2>
<div class="tiles">%(tiles)s</div>
<p><a href="#causes">Jump to likely causes</a></p>
<div class="cols">
  <div><h3>Differences per kind</h3><div class="tablewrap"><table>
    <tr><th>kind</th><th class="num">cases</th><th class="num">differences</th></tr>%(kind_rows)s</table></div></div>
  <div><h3>Per map (%(nmaps)d maps)</h3><div class="tablewrap scroll"><table>
    <tr><th>map</th><th class="num">cases</th><th class="num">skip</th><th class="num">differ</th></tr>%(map_rows)s</table></div></div>
  <div><h3>Skipped</h3><div class="tablewrap"><table>
    <tr><th>reason</th><th class="num">cases</th><th>examples</th></tr>%(skip_rows)s</table></div></div>
</div>

<h2 id="causes">Likely causes</h2>
<p class="muted">Differences grouped by kind and detail (the flag or item name for FLAG, ENGINE, ITEM and SCENE;
the first pair of lines that differ for TEXT), most shared first. Open one to see its cases.</p>
%(causes)s

<h2>Cases with differences</h2>
%(cards)s
</main>
<script>%(body_js)s</script>
</body></html>
""" % {
        "css": CSS, "head_js": HEAD_JS, "body_js": BODY_JS,
        "when": html.escape(time.strftime("%Y-%m-%d %H:%M")),
        "dirs": html.escape(", ".join(dirs)), "note": html.escape(note),
        "kind_boxes": "".join(kind_boxes), "map_opts": map_opts, "ckind_opts": ckind_opts,
        "tiles": tiles, "kind_rows": kind_rows, "skip_rows": skip_rows, "map_rows": map_rows,
        "nmaps": len(maps),
        "causes": "".join(cause_html) or '<p class="empty">No differences.</p>',
        "cards": "".join(cards) or '<p class="empty">No cases with differences.</p>',
    }


# ---------------------------------------------------------------------------
# Summary for a quick read


def render_summary(stats, groups, dirs, extra):
    out = ["# Robot test summary", ""]
    out.append("Folders: %s (%d records, %d duplicates replaced, %d unreadable lines)"
               % (", ".join(dirs), extra["loaded"], extra["dropped"], extra["bad"]))
    out.append("Cases: %d | run: %d | skipped: %d | with differences: %d | identical: %d"
               % (stats["cases"], stats["run"], stats["skipped"], stats["with_diffs"],
                  stats["run"] - stats["with_diffs"]))
    kinds = kind_order(set(stats["kind_diffs"]))
    if kinds:
        out.append("Kinds (cases/diffs): " + ", ".join(
            "%s %d/%d" % (k, stats["kind_cases"][k], stats["kind_diffs"][k]) for k in kinds))
    worst = [(m, s) for m, s in stats["maps"].items() if s["diffs"]]
    worst.sort(key=lambda kv: (-kv[1]["diffs"], kv[0]))
    if worst:
        out.append("Maps with most differing cases: " + ", ".join(
            "%s %d/%d" % (m, s["diffs"], s["cases"]) for m, s in worst[:10])
            + (" (+%d more maps)" % (len(worst) - 10) if len(worst) > 10 else ""))
    if stats["skip_reasons"]:
        out.append("Skipped: " + ", ".join(
            "%s ×%d" % (clip(r, 40), c) for r, c in stats["skip_reasons"].most_common(5)))

    shown = [g for g in groups if g["kind"] not in HIDDEN_BY_DEFAULT]
    hidden = [g for g in groups if g["kind"] in HIDDEN_BY_DEFAULT]
    out += ["", "## Top likely causes", ""]
    if hidden:
        out.append("(UISFX left out: %d group%s, %d diffs)" % (
            len(hidden), "" if len(hidden) == 1 else "s", sum(stats["kind_diffs"][k] for k in HIDDEN_BY_DEFAULT)))
        out.append("")
    if not shown:
        out.append("No differences.")
    for i, g in enumerate(shown[:TOP_CAUSES], 1):
        (value, _), = g["values"].most_common(1)
        more = len(g["values"]) - 1
        examples = ", ".join("%s #%s" % (r["_map"], fmt(r["_n"])) for r in list(g["cases"].values())[:EXAMPLES_PER_CAUSE])
        out.append("%d. [%s] %s — %d case%s — %s%s — e.g. %s" % (
            i, g["kind"], clip(g["label"], 110), len(g["cases"]), "" if len(g["cases"]) == 1 else "s",
            clip(value), " (+%d other values)" % more if more else "", examples))
    if len(shown) > TOP_CAUSES:
        out.append("")
        out.append("(%d more groups in report.html)" % (len(shown) - TOP_CAUSES))
    return "\n".join(out) + "\n"


# ---------------------------------------------------------------------------


def main(argv):
    if len(argv) < 2 or argv[1] in ("-h", "--help"):
        print(__doc__.strip())
        return 0 if len(argv) >= 2 else 2
    dirs = argv[1:]
    for d in dirs:
        if not os.path.isdir(d):
            print("error: %s is not a folder" % d, file=sys.stderr)
            return 2

    all_records, bad = [], 0
    for d in dirs:
        recs, b = load_dir(d)
        all_records += recs
        bad += b
    if not all_records:
        print("error: no results found in %s" % ", ".join(dirs), file=sys.stderr)
        return 1

    records, dropped = merge(all_records)
    for rec in records:
        c = case_of(rec)
        rec["_map"] = str(rec.get("map") or c.get("map") or "?")
        rec["_n"] = rec.get("n", c.get("n", "?"))
        rec["_ckind"] = fmt(rec.get("kind") or c.get("kind") or "")
        rec["_diffs"] = diffs_of(rec)
        rec["_cart_lines"] = lines_of(rec, "cart")
        rec["_port_lines"] = lines_of(rec, "port")
        rec["_first_diff"] = first_diff_line(rec)
    records.sort(key=sort_key)
    for i, rec in enumerate(records):
        rec["_id"] = "case-%d" % i

    stats, groups = analyse(records)
    extra = {"loaded": len(all_records), "dropped": dropped, "bad": bad}

    page = os.path.join(dirs[0], "report.html")
    with open(page, "w", encoding="utf-8") as f:
        f.write(render_html(stats, groups, records, dirs, extra))
    summary = os.path.join(dirs[0], "report_summary.md")
    with open(summary, "w", encoding="utf-8") as f:
        f.write(render_summary(stats, groups, dirs, extra))

    print("%d cases (%d skipped, %d with differences, %d likely causes)"
          % (stats["cases"], stats["skipped"], stats["with_diffs"], len(groups)))
    print("wrote %s" % page)
    print("wrote %s" % summary)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
