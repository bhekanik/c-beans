---
chapter: 41
session_id: M15-4
title: Multi-client poll
phase: H
estimated_time_minutes: 75
artifact: Two clients connect to the server simultaneously; one client's slow read doesn't block the other; `poll(2)` over the listener + each client socket
status: stub
related_milestone: docs/implementation/tasks/M15-daemon-tcp.md
evidence:                       # rule 20 — fill when the chapter is drafted live
  status: exploratory           # consensus | tension | pitfall-heavy | misunderstanding | gap | exploratory
  sources: []                   # - { title, url, role }
  common_misunderstandings: []  # - <false model this chapter corrects>
  gaps: []                      # - <what this chapter deliberately does not cover yet>
---

# Chapter 41 — Multi-client poll

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `M15-4` · Phase H · ~75 min · [Underlying milestone](../implementation/tasks/M15-daemon-tcp.md)

## What you'll learn

Blocking vs non-blocking I/O; `O_NONBLOCK`; why `select` is deprecated; why `poll` is pragmatic vs `epoll`/`kqueue`

## What you'll build

Two clients connect to the server simultaneously; one client's slow read doesn't block the other; `poll(2)` over the listener + each client socket

## Before you start

Run chapter 40's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/41-multi-client-poll.md`](../teaching/notes/41-multi-client-poll.md) gets filled during the live session.

## What people usually get wrong

*Stub — filled when the chapter is drafted live. Capture the reusable false models a learner brings here (often from JS/TS/Python) and the corrected model. See [chapter 01](01-cmake-workspace.md) for shape.*

---

## What this chapter does not cover yet

*Stub — list what is deliberately deferred to keep the one-concept-per-session cap honest. See [chapter 01](01-cmake-workspace.md) for shape.*

---

## Sources

*Stub — primary docs/specs/code references that shape the chapter. Use when you say "this is consensus" (rule 20). See [chapter 01](01-cmake-workspace.md) for shape.*

---

## See also

- ← [Chapter 40 — Protocol design](40-protocol-design.md)
- → [Chapter 42 — Daemon extraction](42-daemon-extraction.md)
- [Underlying milestone](../implementation/tasks/M15-daemon-tcp.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
