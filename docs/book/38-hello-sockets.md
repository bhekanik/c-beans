---
chapter: 38
session_id: M15-1
title: Hello, sockets
phase: H
estimated_time_minutes: 75
artifact: A server prints whatever a client sends; the client sends a hardcoded string; both close cleanly
status: stub
related_milestone: docs/implementation/tasks/M15-daemon-tcp.md
teaches:
  - network-programming
---

# Chapter 38 — Hello, sockets

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `M15-1` · Phase H · ~75 min · [Underlying milestone](../implementation/tasks/M15-daemon-tcp.md)

## What you'll learn

`socket` / `bind` / `listen` / `accept` / `recv` / `send`; the `sockaddr_in` cast dance; `SO_REUSEADDR`

## What you'll build

A server prints whatever a client sends; the client sends a hardcoded string; both close cleanly

## Before you start

Run chapter 37's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/38-hello-sockets.md`](../teaching/notes/38-hello-sockets.md) gets filled during the live session.

## See also

- ← [Chapter 37 — JSONL → SQLite migration](37-jsonl-sqlite-migrate.md)
- → [Chapter 39 — Length-prefixed framing](39-tcp-framing.md)
- [Underlying milestone](../implementation/tasks/M15-daemon-tcp.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
