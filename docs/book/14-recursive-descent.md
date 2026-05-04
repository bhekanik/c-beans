---
chapter: 14
session_id: M6-1
title: Recursive descent
phase: B
estimated_time_minutes: 90
artifact: A recursive-descent parser produces a `JsonValue` DOM (tagged union) from the token stream; nested objects and arrays parse correctly; errors carry line/column
status: stub
related_milestone: docs/implementation/tasks/M06-parser.md
---

# Chapter 14 — Recursive descent

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `M6-1` · Phase B · ~90 min · [Underlying milestone](../implementation/tasks/M06-parser.md)

## What you'll learn

Recursive descent as the standard parser shape; how errors propagate through return values without exceptions

## What you'll build

A recursive-descent parser produces a `JsonValue` DOM (tagged union) from the token stream; nested objects and arrays parse correctly; errors carry line/column

## Before you start

Run chapter 13's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/14-recursive-descent.md`](../teaching/notes/14-recursive-descent.md) gets filled during the live session.

## See also

- ← [Chapter 13 — Number tokens](13-number-tokens.md)
- → [Chapter 15 — DOM to typed Task](15-dom-to-task.md)
- [Underlying milestone](../implementation/tasks/M06-parser.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
