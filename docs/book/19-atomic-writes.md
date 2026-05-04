---
chapter: 19
session_id: M7-4
title: Atomic file writes
phase: C
estimated_time_minutes: 75
artifact: A simulated crash mid-rewrite (Ctrl-C while `beans complete` runs) leaves the JSONL file intact; subsequent reads succeed
status: stub
related_milestone: docs/implementation/tasks/M07-store.md
---

# Chapter 19 — Atomic file writes

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `M7-4` · Phase C · ~75 min · [Underlying milestone](../implementation/tasks/M07-store.md)

## What you'll learn

The tmp + fsync + rename pattern; what `fsync` does; why `rename` is atomic on POSIX; failure modes you survive vs ones you don't

## What you'll build

A simulated crash mid-rewrite (Ctrl-C while `beans complete` runs) leaves the JSONL file intact; subsequent reads succeed

## Before you start

Run chapter 18's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/19-atomic-writes.md`](../teaching/notes/19-atomic-writes.md) gets filled during the live session.

## See also

- ← [Chapter 18 — JSONL read](18-jsonl-read.md)
- → [Chapter 20 — Testing as a discipline](20-testing-discipline.md)
- [Underlying milestone](../implementation/tasks/M07-store.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
