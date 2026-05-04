---
chapter: 5
session_id: M1-1
title: Owned String
phase: A
estimated_time_minutes: 90
artifact: A `String` struct (data + len + cap) round-trips through alloc + append + free with no leaks under ASan
status: stub
related_milestone: docs/implementation/tasks/M01-owned-string.md
teaches:
  - manual-memory
---

# Chapter 05 — Owned String

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `M1-1` · Phase A · ~90 min · [Underlying milestone](../implementation/tasks/M01-owned-string.md)

## What you'll learn

The Owned String — `struct String { char *data; size_t len; size_t cap; }` — init, free, append, debug; `char *` ambiguity as the central pain

## What you'll build

A `String` struct (data + len + cap) round-trips through alloc + append + free with no leaks under ASan

## Before you start

Run chapter 04's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/05-owned-string.md`](../teaching/notes/05-owned-string.md) gets filled during the live session.

## See also

- ← [Chapter 04 — First segfault on purpose](04-first-segfault.md)
- → [Chapter 06 — String views](06-string-view.md)
- [Underlying milestone](../implementation/tasks/M01-owned-string.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
