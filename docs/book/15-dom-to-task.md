---
chapter: 15
session_id: M6-2
title: DOM to typed Task
phase: B
estimated_time_minutes: 60
artifact: `task_from_json(JsonValue *)` produces a `Task` from a JSON object; missing required fields return a typed error; unknown fields warn but don't fail
status: stub
related_milestone: docs/implementation/tasks/M06-parser.md
---

# Chapter 15 — DOM to typed Task

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `M6-2` · Phase B · ~60 min · [Underlying milestone](../implementation/tasks/M06-parser.md)

## What you'll learn

Parsing/validation distinction; surfacing errors that point at line/column; the typed-domain layer

## What you'll build

`task_from_json(JsonValue *)` produces a `Task` from a JSON object; missing required fields return a typed error; unknown fields warn but don't fail

## Before you start

Run chapter 14's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/15-dom-to-task.md`](../teaching/notes/15-dom-to-task.md) gets filled during the live session.

## See also

- ← [Chapter 14 — Recursive descent](14-recursive-descent.md)
- → [Chapter 16 — The Store interface](16-store-interface.md)
- [Underlying milestone](../implementation/tasks/M06-parser.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
