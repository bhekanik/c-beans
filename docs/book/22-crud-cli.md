---
chapter: 22
session_id: M8-2
title: CRUD via CLI
phase: D
estimated_time_minutes: 75
artifact: `beans add` / `beans list` / `beans complete <id-prefix>` / `beans delete <id-prefix>` all work end-to-end through the Store interface; `beans` with no args prints help (chapter 24 swaps that branch to launching the TUI)
status: stub
related_milestone: docs/implementation/tasks/M08-task-model.md
---

# Chapter 22 — CRUD via CLI

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `M8-2` · Phase D · ~75 min · [Underlying milestone](../implementation/tasks/M08-task-model.md)

## What you'll learn

Command dispatch via manual `argv[1]` switch (no fancy parser); the CLI as a thin caller of Store ops; foreshadow "every TUI action has a CLI equivalent"

## What you'll build

`beans add` / `beans list` / `beans complete <id-prefix>` / `beans delete <id-prefix>` all work end-to-end through the Store interface; `beans` with no args prints help (chapter 24 swaps that branch to launching the TUI)

## Before you start

Run chapter 21's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/22-crud-cli.md`](../teaching/notes/22-crud-cli.md) gets filled during the live session.

## See also

- ← [Chapter 21 — Task model + ULID](21-task-model.md)
- → [Chapter 23 — Errors as values](23-errors.md)
- [Underlying milestone](../implementation/tasks/M08-task-model.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
