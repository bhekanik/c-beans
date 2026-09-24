---
chapter: 9
session_id: M3-1
title: Tagged unions
phase: A
estimated_time_minutes: 75
artifact: A `TaskEvent` tagged union with three variants; an exhaustive switch handles every variant; the compiler complains if you add a fourth without updating the switch
status: stub
related_milestone: docs/implementation/tasks/M03-tagged-unions.md
evidence:                       # rule 20 — fill when the chapter is drafted live
  status: exploratory           # consensus | tension | pitfall-heavy | misunderstanding | gap | exploratory
  sources: []                   # - { title, url, role }
  common_misunderstandings: []  # - <false model this chapter corrects>
  gaps: []                      # - <what this chapter deliberately does not cover yet>
---

# Chapter 09 — Tagged unions

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `M3-1` · Phase A · ~75 min · [Underlying milestone](../implementation/tasks/M03-tagged-unions.md)

## What you'll learn

Sum types in C — `enum` + `union` + manual discipline; the "free must check the tag" rule; `default:` as a footgun

## What you'll build

A `TaskEvent` tagged union with three variants; an exhaustive switch handles every variant; the compiler complains if you add a fourth without updating the switch

## Before you start

Run chapter 08's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/09-tagged-unions.md`](../teaching/notes/09-tagged-unions.md) gets filled during the live session.

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

- ← [Chapter 08 — Generic Vec via macros](08-generic-vec-macros.md)
- → [Chapter 10 — File I/O](10-file-io.md)
- [Underlying milestone](../implementation/tasks/M03-tagged-unions.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
