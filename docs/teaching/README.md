# Teaching mode for c-beans

This directory exists when c-beans is being built in **teaching mode** — the deliberately slow, one-concept-per-session learning project the repo is structured around.

If you're an agent: start at [`/AGENTS.md`](../../AGENTS.md). If you're a human reader: start at [`/docs/book/README.md`](../book/README.md).

## What lives here

| File | Purpose |
|---|---|
| [`sessions.md`](sessions.md) | Session-by-session plan. One row per session, one concept per session. Cross-references the chapter file and the underlying milestone. |
| [`build-philosophy.md`](build-philosophy.md) | Reproduce-mode artifact contract. What "the artifact at chapter close" means here, vs lazydap's tour mode. |
| [`c-anchor-table.md`](c-anchor-table.md) | The JS/TS → C pain anchor table. Used to lead chapters with felt pain (rule 7 of the teaching skill). |
| [`notes/`](notes/) | Per-chapter teaching notes — companion to each `docs/book/NN-*.md` chapter. Each carries a `learner_state:` frontmatter snapshot (rule 22) plus common misunderstandings, the probe bank, expectations and graduated hints, and the verification record. |
| [`suggested-order.md`](suggested-order.md) | **Generated** by `bookgen/scripts/update.sh` — a suggested teaching order derived from the anchor codebase. Do not hand-edit; regenerated on every update. |
| [`dep-skeleton.json`](dep-skeleton.json) | **Generated** dependency skeleton for the anchor codebase. Machine-readable companion to `suggested-order.md`. |
| [`../chain/concept-dag.json`](../chain/concept-dag.json) | **Generated** prerequisite graph across all chapters from their `requires:` / `teaches:` frontmatter. This is the map you walk during rule-23 prerequisite descent. |

## Plan ≠ log

This directory is the **plan**. Session **logs** live in Obsidian (the `C-Beans Teaching Sessions.md` hub + per-session children). Plan ≠ log; both are useful, neither replaces the other.

When teaching mode ends (the learner says "let's go fast" or hands off to a build agent for shipping), this directory becomes archive. The `docs/implementation/` tasks remain canonical.

## See also

- [`/AGENTS.md`](../../AGENTS.md) — teaching mode setup, learner profile, agent startup checklist
- [`.skills/teaching/SKILL.md`](../../.skills/teaching/SKILL.md) — the portable pedagogy this teaching is built on
- [`docs/book/README.md`](../book/README.md) — the chapter table of contents
- [`docs/implementation/README.md`](../implementation/README.md) — the ship-mode milestones (parallel to teaching sessions)
