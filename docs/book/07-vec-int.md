---
chapter: 7
session_id: M2-1
title: Vec_int
phase: A
estimated_time_minutes: 75
artifact: A `Vec_int` with 100 pushes prints in order; growth policy doubles capacity; no leaks
status: stub
related_milestone: docs/implementation/tasks/M02-vec.md
---

# Chapter 07 — Vec_int

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `M2-1` · Phase A · ~75 min · [Underlying milestone](../implementation/tasks/M02-vec.md)

## What you'll learn

Dynamic array — realloc-on-full pattern, doubling for amortised O(1), what happens to existing pointers when realloc moves memory

## What you'll build

A `Vec_int` with 100 pushes prints in order; growth policy doubles capacity; no leaks

## Before you start

Run chapter 06's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/07-vec-int.md`](../teaching/notes/07-vec-int.md) gets filled during the live session.

## See also

- ← [Chapter 06 — String views](06-string-view.md)
- → [Chapter 08 — Generic Vec via macros](08-generic-vec-macros.md)
- [Underlying milestone](../implementation/tasks/M02-vec.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
