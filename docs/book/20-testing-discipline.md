---
chapter: 20
session_id: TDD-1
title: Testing as a discipline
phase: D
estimated_time_minutes: 90
artifact: `ctest --test-dir build --output-on-failure` runs all chapter 04-19 smoke tests; they pass
status: stub
related_milestone: docs/implementation/tasks/M07b-test-harness.md
teaches:
  - testing-in-c
---

# Chapter 20 — Testing as a discipline

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `TDD-1` · Phase D · ~90 min · [Underlying milestone](../implementation/tasks/M07b-test-harness.md)

## What you'll learn

The dedicated meta-session: tiny assert + TEST + RUN harness; Implementation Swap Test; behaviour-vs-implementation testing; deferred-load infrastructure becomes explicit

## What you'll build

`ctest --test-dir build --output-on-failure` runs all chapter 04-19 smoke tests; they pass

## Before you start

Run chapter 19's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/20-testing-discipline.md`](../teaching/notes/20-testing-discipline.md) gets filled during the live session.

## See also

- ← [Chapter 19 — Atomic file writes](19-atomic-writes.md)
- → [Chapter 21 — Task model + ULID](21-task-model.md)
- [Underlying milestone](../implementation/tasks/M07b-test-harness.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
