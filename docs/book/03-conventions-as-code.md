---
chapter: 3
session_id: WS-3
title: Conventions as code
phase: 0
estimated_time_minutes: 75
artifact: `BEANS_SANITIZERS=ON` debug build runs cleanly; clang-format check passes; CI is green
status: stub
related_milestone: docs/implementation/00-workspace-setup.md
evidence:                       # rule 20 — fill when the chapter is drafted live
  status: exploratory           # consensus | tension | pitfall-heavy | misunderstanding | gap | exploratory
  sources: []                   # - { title, url, role }
  common_misunderstandings: []  # - <false model this chapter corrects>
  gaps: []                      # - <what this chapter deliberately does not cover yet>
---

# Chapter 03 — Conventions as code

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `WS-3` · Phase 0 · ~75 min · [Underlying milestone](../implementation/00-workspace-setup.md)

## What you'll learn

`.clang-format` + `.clang-tidy` + sanitizer CMake module + warning module + GitHub Actions CI walkthrough; ceremony chapter

## What you'll build

`BEANS_SANITIZERS=ON` debug build runs cleanly; clang-format check passes; CI is green

## Before you start

Run chapter 02's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/03-conventions-as-code.md`](../teaching/notes/03-conventions-as-code.md) gets filled during the live session.

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

- ← [Chapter 02 — Hello, beans](02-hello-beans.md)
- → [Chapter 04 — First segfault on purpose](04-first-segfault.md)
- [Underlying milestone](../implementation/00-workspace-setup.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
