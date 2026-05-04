---
chapter: 31
session_id: M13-1
title: XDG paths
phase: F
estimated_time_minutes: 60
artifact: Tasks live at `~/.local/share/beans/tasks.jsonl` (or `$XDG_DATA_HOME/beans/`); first-run creates the directory; existing flat-file deployments still work via opt-in
status: stub
related_milestone: docs/implementation/tasks/M13-polish.md
---

# Chapter 31 — XDG paths

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `M13-1` · Phase F · ~60 min · [Underlying milestone](../implementation/tasks/M13-polish.md)

## What you'll learn

XDG Base Directory spec; `getenv("XDG_DATA_HOME")` with fallback; portability of hardcoded paths; `mkdir -p` semantics via `mkdir(2)` + `EEXIST`

## What you'll build

Tasks live at `~/.local/share/beans/tasks.jsonl` (or `$XDG_DATA_HOME/beans/`); first-run creates the directory; existing flat-file deployments still work via opt-in

## Before you start

Run chapter 30's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/31-xdg-paths.md`](../teaching/notes/31-xdg-paths.md) gets filled during the live session.

## See also

- ← [Chapter 30 — Wire CRUD](30-tui-crud.md)
- → [Chapter 32 — Error rendering in TUI](32-tui-error-bar.md)
- [Underlying milestone](../implementation/tasks/M13-polish.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
