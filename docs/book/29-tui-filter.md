---
chapter: 29
session_id: M12-1
title: Filter
phase: E
estimated_time_minutes: 60
artifact: Press `/` → opens filter prompt → typed text filters the visible list; ESC clears the filter
status: stub
related_milestone: docs/implementation/tasks/M12-tui-filter.md
---

# Chapter 29 — Filter

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `M12-1` · Phase E · ~60 min · [Underlying milestone](../implementation/tasks/M12-tui-filter.md)

## What you'll learn

Derived state (filter applied at view time, not stored); how the model/update/view pattern handles transient UI state

## What you'll build

Press `/` → opens filter prompt → typed text filters the visible list; ESC clears the filter

## Before you start

Run chapter 28's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/29-tui-filter.md`](../teaching/notes/29-tui-filter.md) gets filled during the live session.

## See also

- ← [Chapter 28 — Add tasks via TUI](28-tui-add.md)
- → [Chapter 30 — Wire CRUD](30-tui-crud.md)
- [Underlying milestone](../implementation/tasks/M12-tui-filter.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
