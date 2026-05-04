---
chapter: 4
session_id: M0-1
title: First segfault on purpose
phase: A
estimated_time_minutes: 75
artifact: Run a deliberately broken program; ASan diagnoses the use-after-free with a stack trace
status: stub
related_milestone: docs/implementation/tasks/M00-first-segfault.md
---

# Chapter 04 — First segfault on purpose

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `M0-1` · Phase A · ~75 min · [Underlying milestone](../implementation/tasks/M00-first-segfault.md)

## What you'll learn

Undefined behaviour as a category; ASan and UBSan as co-teachers; the "it ran fine" trap

## What you'll build

Run a deliberately broken program; ASan diagnoses the use-after-free with a stack trace

## Before you start

Run chapter 03's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/04-first-segfault.md`](../teaching/notes/04-first-segfault.md) gets filled during the live session.

## See also

- ← [Chapter 03 — Conventions as code](03-conventions-as-code.md)
- → [Chapter 05 — Owned String](05-owned-string.md)
- [Underlying milestone](../implementation/tasks/M00-first-segfault.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
