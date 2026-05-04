---
chapter: 36
session_id: M14-3
title: Transactions, WAL
phase: G
estimated_time_minutes: 75
artifact: A multi-statement bulk operation in a `BEGIN`/`COMMIT` block is all-or-nothing; WAL journal mode is enabled; a simulated crash mid-transaction leaves the db consistent
status: stub
related_milestone: docs/implementation/tasks/M14-sqlite.md
---

# Chapter 36 — Transactions, WAL

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `M14-3` · Phase G · ~75 min · [Underlying milestone](../implementation/tasks/M14-sqlite.md)

## What you'll learn

ACID, what each letter buys; why WAL is the default for embedded sqlite; crash-safety guarantees vs JSONL atomic-rename

## What you'll build

A multi-statement bulk operation in a `BEGIN`/`COMMIT` block is all-or-nothing; WAL journal mode is enabled; a simulated crash mid-transaction leaves the db consistent

## Before you start

Run chapter 35's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/36-transactions-wal.md`](../teaching/notes/36-transactions-wal.md) gets filled during the live session.

## See also

- ← [Chapter 35 — Prepared statements](35-prepared-statements.md)
- → [Chapter 37 — JSONL → SQLite migration](37-jsonl-sqlite-migrate.md)
- [Underlying milestone](../implementation/tasks/M14-sqlite.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
