---
chapter: 18
session_id: M7-3
title: JSONL read
phase: C
estimated_time_minutes: 60
artifact: `beans list` reads the JSONL file, runs each line through the parser, prints the tasks; malformed lines warn-and-skip
status: stub
related_milestone: docs/implementation/tasks/M07-store.md
---

# Chapter 18 — JSONL read

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `M7-3` · Phase C · ~60 min · [Underlying milestone](../implementation/tasks/M07-store.md)

## What you'll learn

Startup load; what to do with malformed lines; how this interacts with the Store interface; foreshadows the SQLite migration

## What you'll build

`beans list` reads the JSONL file, runs each line through the parser, prints the tasks; malformed lines warn-and-skip

## Before you start

Run chapter 17's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/18-jsonl-read.md`](../teaching/notes/18-jsonl-read.md) gets filled during the live session.

## See also

- ← [Chapter 17 — JSONL write](17-jsonl-write.md)
- → [Chapter 19 — Atomic file writes](19-atomic-writes.md)
- [Underlying milestone](../implementation/tasks/M07-store.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
