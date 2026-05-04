---
chapter: 25
session_id: M10-2
title: Render the task list
phase: E
estimated_time_minutes: 75
artifact: `beans` (no args) opens the JSONL store and renders the task list (one task per row); no interaction yet
status: stub
related_milestone: docs/implementation/tasks/M10-hello-ncurses.md
---

# Chapter 25 — Render the task list

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `M10-2` · Phase E · ~75 min · [Underlying milestone](../implementation/tasks/M10-hello-ncurses.md)

## What you'll learn

ncurses windows as bounded drawing regions; the `mv*` (move-then-do) family; the `(y, x)` coordinate system

## What you'll build

`beans` (no args) opens the JSONL store and renders the task list (one task per row); no interaction yet

## Before you start

Run chapter 24's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/25-render-task-list.md`](../teaching/notes/25-render-task-list.md) gets filled during the live session.

## See also

- ← [Chapter 24 — Hello, ncurses](24-hello-ncurses.md)
- → [Chapter 26 — Navigation](26-tui-navigation.md)
- [Underlying milestone](../implementation/tasks/M10-hello-ncurses.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
