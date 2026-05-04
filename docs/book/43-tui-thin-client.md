---
chapter: 43
session_id: M15-6
title: TUI as thin client
phase: H
estimated_time_minutes: 90
artifact: The TUI subscribes to events; mutations from `beans` in another shell trigger the TUI to re-render automatically; **the architecture clicks**
status: stub
related_milestone: docs/implementation/tasks/M15-daemon-tcp.md
---

# Chapter 43 — TUI as thin client

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `M15-6` · Phase H · ~90 min · [Underlying milestone](../implementation/tasks/M15-daemon-tcp.md)

## What you'll learn

Pub/sub over a duplex socket; how the TUI's update loop folds incoming events alongside keypresses; **v0.3.0 ships**

## What you'll build

The TUI subscribes to events; mutations from `beans` in another shell trigger the TUI to re-render automatically; **the architecture clicks**

## Before you start

Run chapter 42's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/43-tui-thin-client.md`](../teaching/notes/43-tui-thin-client.md) gets filled during the live session.

## See also

- ← [Chapter 42 — Daemon extraction](42-daemon-extraction.md)
- → No next chapter (you've reached v0.3).
- [Underlying milestone](../implementation/tasks/M15-daemon-tcp.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
