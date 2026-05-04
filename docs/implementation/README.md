# Implementation — ship-mode milestones

This directory is **how we track work**. Source-controlled, agent-readable. No GitHub Issues, no Linear.

**Intentionally clean of teaching content.** If at any point the learner decides to hand the project to a coding agent for fast shipping, this directory works as-is.

For the parallel **teaching session breakdowns**, see [`../teaching/`](../teaching/).

## Layout

- [`00-workspace-setup.md`](00-workspace-setup.md) — prerequisite to chapter 01
- [`tasks/MNN-*.md`](tasks/) — one MD file per milestone (filled lazily as chapters land)

## How to work with these

1. **Pick the next task.** [`/TODO.md`](../../TODO.md) shows the current state.
2. **Read the task file.** Each milestone is self-contained: what / why / how / success criteria / files / verify / depends on.
3. **Confirm dependencies.** The task file lists what must be complete first.
4. **Do the work.** In teaching mode, this is paced by the session plan in `../teaching/sessions.md`.
5. **Mark the task done.** Check the box in `/TODO.md`. Add a brief completion note.

The implementation directory is the project's working memory. Treat it that way: write to it, read from it, keep it current.

## See also

- [`/AGENTS.md`](../../AGENTS.md) — pedagogy and conventions
- [`/TODO.md`](../../TODO.md) — current state index
- [`../teaching/sessions.md`](../teaching/sessions.md) — teaching-mode session plan
- [`../blueprint/00-overview.md`](../blueprint/00-overview.md) — full project vision
