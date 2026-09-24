#!/usr/bin/env python3
"""
One-shot backfill: bring stub chapters + notes up to the chapter/teaching-notes
template introduced with rules 20–23 of the teaching skill.

Adds (idempotent):
- chapter frontmatter:  evidence: block
- chapter body:         "What people usually get wrong" / "What this chapter does not cover yet" / "Sources" sections, before "See also"
- notes frontmatter:    learner_state: block
- notes body:           "Common misunderstandings" / "Probe bank" / "Expectations and graduated hints", before "What surprised the learner"

Skips:
- docs/book/01-cmake-workspace.md (taught — has real content from the manual reconcile)
- docs/teaching/notes/01-cmake-workspace.md (same)
- intro chapters 00*, 00b*, 00c* (no session_id; not session-driven)
"""
from __future__ import annotations
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent  # repo root
BOOK = ROOT / "docs" / "book"
NOTES = ROOT / "docs" / "teaching" / "notes"

CHAPTER_EVIDENCE_BLOCK = """evidence:                       # rule 20 — fill when the chapter is drafted live
  status: exploratory           # consensus | tension | pitfall-heavy | misunderstanding | gap | exploratory
  sources: []                   # - { title, url, role }
  common_misunderstandings: []  # - <false model this chapter corrects>
  gaps: []                      # - <what this chapter deliberately does not cover yet>
"""

CHAPTER_NEW_SECTIONS = """## What people usually get wrong

*Stub — filled when the chapter is drafted live. Capture the reusable false models a learner brings here (often from JS/TS/Python) and the corrected model. See [chapter 01](01-cmake-workspace.md) for shape.*

---

## What this chapter does not cover yet

*Stub — list what is deliberately deferred to keep the one-concept-per-session cap honest. See [chapter 01](01-cmake-workspace.md) for shape.*

---

## Sources

*Stub — primary docs/specs/code references that shape the chapter. Use when you say "this is consensus" (rule 20). See [chapter 01](01-cmake-workspace.md) for shape.*

---

"""

NOTES_LEARNER_STATE_BLOCK = """learner_state:        # rule 22 — persisted snapshot; reconcile at session end
  mastered: []        # concepts demonstrated unaided
  shaky: []           # met but not solid; re-probe and retrieve early
  recent_errors: []   # specific wrong predictions / compiler conversations, last few turns
  priors: []          # opinionated prior-language models that shape predictions
"""

NOTES_NEW_SECTIONS = """## Common misunderstandings

Reusable false models that fire here regardless of which predict-pause surfaces them. *Empty until the first live teach — see [notes/01](01-cmake-workspace.md) for the table shape.*

| Misunderstanding | Why it is tempting | Corrected model | Where the chapter addresses it |
|---|---|---|---|
| *(stub)* | *(stub)* | *(stub)* | *(stub)* |

## Probe bank

Diagnostic questions a future teacher can fire to test whether each misunderstanding is active (rule 21). *Empty until the first live teach.*

| Misunderstanding / pitfall | Diagnostic probe | Expected wrong answer | Calibration if wrong | Mastery signal (Aware / Confident) |
|---|---|---|---|---|
| *(stub)* | *(stub)* | *(stub)* | *(stub)* | *(stub)* |

## Expectations and graduated hints

For each predict-pause and exercise, hold (a) the expectations a correct answer must contain and (b) a hint ladder L1 → L2 → L3 (rule 21). Start at L1 every time; drop a level only after a real attempt fails. *Empty until the first live teach — see [notes/01](01-cmake-workspace.md) for shape.*

"""


def split_frontmatter(text: str) -> tuple[str, str] | None:
    """Return (frontmatter_inner, rest_after_closing_---) or None if no frontmatter."""
    if not text.startswith("---\n"):
        return None
    end = text.find("\n---\n", 4)
    if end == -1:
        return None
    return text[4:end + 1], text[end + 5:]


def has_top_level_key(frontmatter: str, key: str) -> bool:
    """Match a YAML top-level key like `evidence:` at start of line."""
    return re.search(rf"(?m)^{re.escape(key)}\s*:", frontmatter) is not None


def insert_frontmatter_block(text: str, block: str, key: str) -> tuple[str, bool]:
    """Insert `block` into frontmatter unless `key` already present.
    Returns (new_text, modified)."""
    parts = split_frontmatter(text)
    if parts is None:
        return text, False
    fm, rest = parts
    if has_top_level_key(fm, key):
        return text, False
    # Ensure trailing newline on fm
    if not fm.endswith("\n"):
        fm += "\n"
    new_text = "---\n" + fm + block + "---\n" + rest
    return new_text, True


def insert_sections(text: str, new_sections: str, anchor_heading: str, sentinel_heading: str) -> tuple[str, bool]:
    """Insert new_sections immediately before the line that matches anchor_heading,
    but only if sentinel_heading is not already present anywhere in the doc."""
    if re.search(rf"(?m)^{re.escape(sentinel_heading)}\s*$", text):
        return text, False  # already backfilled
    pattern = re.compile(rf"(?m)^{re.escape(anchor_heading)}\s*$")
    m = pattern.search(text)
    if not m:
        return text, False  # no anchor — skip this file
    insert_at = m.start()
    new_text = text[:insert_at] + new_sections + text[insert_at:]
    return new_text, True


def process_chapter(path: Path) -> dict:
    text = path.read_text()
    modified = False
    actions = []

    new_text, did = insert_frontmatter_block(text, CHAPTER_EVIDENCE_BLOCK, "evidence")
    if did:
        text = new_text
        modified = True
        actions.append("+evidence frontmatter")

    new_text, did = insert_sections(
        text,
        CHAPTER_NEW_SECTIONS,
        anchor_heading="## See also",
        sentinel_heading="## Sources",
    )
    if did:
        text = new_text
        modified = True
        actions.append("+body sections")

    if modified:
        path.write_text(text)
    return {"path": str(path.relative_to(ROOT)), "actions": actions}


def process_notes(path: Path) -> dict:
    text = path.read_text()
    modified = False
    actions = []

    new_text, did = insert_frontmatter_block(text, NOTES_LEARNER_STATE_BLOCK, "learner_state")
    if did:
        text = new_text
        modified = True
        actions.append("+learner_state frontmatter")

    new_text, did = insert_sections(
        text,
        NOTES_NEW_SECTIONS,
        anchor_heading="## What surprised the learner",
        sentinel_heading="## Common misunderstandings",
    )
    if did:
        text = new_text
        modified = True
        actions.append("+body sections")

    if modified:
        path.write_text(text)
    return {"path": str(path.relative_to(ROOT)), "actions": actions}


def main() -> int:
    skip_chapters = {"01-cmake-workspace.md"}
    skip_notes = {"01-cmake-workspace.md"}

    chapter_files = sorted(
        p for p in BOOK.glob("*.md")
        if p.name not in skip_chapters
        and p.name != "README.md"
        and re.match(r"^\d{2}-", p.name)  # 01-…, 02-…  (excludes 00b-…, 00c-…)
        and not p.name.startswith("00-")  # exclude 00-introduction.md
    )
    notes_files = sorted(
        p for p in NOTES.glob("*.md")
        if p.name not in skip_notes
    )

    print(f"== Chapters to scan: {len(chapter_files)}")
    chapter_changes = [process_chapter(p) for p in chapter_files]
    for r in chapter_changes:
        if r["actions"]:
            print(f"  {r['path']}: {', '.join(r['actions'])}")
        else:
            print(f"  {r['path']}: (no changes — already current)")

    print(f"\n== Notes to scan: {len(notes_files)}")
    notes_changes = [process_notes(p) for p in notes_files]
    for r in notes_changes:
        if r["actions"]:
            print(f"  {r['path']}: {', '.join(r['actions'])}")
        else:
            print(f"  {r['path']}: (no changes — already current)")

    touched = sum(1 for r in chapter_changes + notes_changes if r["actions"])
    print(f"\nDone. {touched} files modified.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
