---
chapter: 8
session_id: M2-2
title: Generic Vec via macros
phase: A
estimated_time_minutes: 75
artifact: `Vec_String` and `Vec_Task` (forward-declared) generated from a single `DEFINE_VEC(T)` macro
status: stub
related_milestone: docs/implementation/tasks/M02-vec.md
---

# Chapter 08 — Generic Vec via macros

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `M2-2` · Phase A · ~75 min · [Underlying milestone](../implementation/tasks/M02-vec.md)

## What you'll learn

Macros as the only generic mechanism C has; trade-offs (no type-checked generics, no runtime cost); `_Generic` for type-dispatched calls

## What you'll build

`Vec_String` and `Vec_Task` (forward-declared) generated from a single `DEFINE_VEC(T)` macro

## Before you start

Run chapter 07's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/08-generic-vec-macros.md`](../teaching/notes/08-generic-vec-macros.md) gets filled during the live session.

## See also

- ← [Chapter 07 — Vec_int](07-vec-int.md)
- → [Chapter 09 — Tagged unions](09-tagged-unions.md)
- [Underlying milestone](../implementation/tasks/M02-vec.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
