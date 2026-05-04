---
chapter: 17
session_id: M7-2
title: JSONL write
phase: C
estimated_time_minutes: 60
artifact: `beans add "feed the cat"` opens the JSONL file in `O_APPEND`, serialises the task, writes one line; the file persists across runs
status: stub
related_milestone: docs/implementation/tasks/M07-store.md
teaches:
  - file-persistence
requires:
  - polymorphism-in-c
---

# Chapter 17 — JSONL write

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `M7-2` · Phase C · ~60 min · [Underlying milestone](../implementation/tasks/M07-store.md)

## What you'll learn

`O_APPEND` atomicity; serialisation as the inverse of parsing; JSONL's append-only shape

## What you'll build

`beans add "feed the cat"` opens the JSONL file in `O_APPEND`, serialises the task, writes one line; the file persists across runs

## Before you start

Run chapter 16's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/17-jsonl-write.md`](../teaching/notes/17-jsonl-write.md) gets filled during the live session.

## See also

- ← [Chapter 16 — The Store interface](16-store-interface.md)
- → [Chapter 18 — JSONL read](18-jsonl-read.md)
- [Underlying milestone](../implementation/tasks/M07-store.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
