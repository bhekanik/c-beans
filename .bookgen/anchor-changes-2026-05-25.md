# Anchor changes since last update — 2026-05-25

**Anchor repo:** `/Users/bhekanik/code/bhekanik/c-beans`
**Range:** `162a71b840ae12aecf8363a71d4aae18deef4051..HEAD`
**Anchor HEAD now:** `abe2aecaf4481da73ec3a92d3d03b50c4a126823`
**Book last vendored:** 2026-05-05T00:00:00Z

## Commits

```
Good "git" signature with ED25519 key SHA256:FkAu8FhMvjqfuGtBtW5Na06E8D1cgS3gTghYaVN3Too
No principal matched.
abe2aec  docs: symlink CLAUDE.md to AGENTS.md  (bhekanik, 3 days ago)
Good "git" signature with ED25519 key SHA256:FkAu8FhMvjqfuGtBtW5Na06E8D1cgS3gTghYaVN3Too
No principal matched.
1b395be  build: scaffold CMake build with beans_core static library  (bhekanik, 3 days ago)
Good "git" signature with ED25519 key SHA256:FkAu8FhMvjqfuGtBtW5Na06E8D1cgS3gTghYaVN3Too
No principal matched.
2b0673d  teaching: re-vendor source updates + capture WS-1 session pause state  (bhekanik, 3 weeks ago)
Good "git" signature with ED25519 key SHA256:FkAu8FhMvjqfuGtBtW5Na06E8D1cgS3gTghYaVN3Too
No principal matched.
00f321f  teaching: rule 4 checkpoint discipline for multi-stage exercises  (bhekanik, 3 weeks ago)
Good "git" signature with ED25519 key SHA256:FkAu8FhMvjqfuGtBtW5Na06E8D1cgS3gTghYaVN3Too
No principal matched.
0539b5a  docs: backfill teaches frontmatter on concept entry-chapters  (bhekanik, 3 weeks ago)
Good "git" signature with ED25519 key SHA256:FkAu8FhMvjqfuGtBtW5Na06E8D1cgS3gTghYaVN3Too
No principal matched.
5c2b172  bookgen: refresh infrastructure (build-philosophy, drift, anchor-diff)  (bhekanik, 3 weeks ago)
Good "git" signature with ED25519 key SHA256:FkAu8FhMvjqfuGtBtW5Na06E8D1cgS3gTghYaVN3Too
No principal matched.
84ad519  teaching: vendor rule 19 (varied practice / exercises)  (bhekanik, 3 weeks ago)
```

## Files touched

```
.bookgen/anchor-changes-2026-05-04.md
.gitignore
.skills/teaching/references/chapter-template.md
.skills/teaching/references/exercise-answers-template.md
.skills/teaching/references/exercises-template.md
.skills/teaching/references/operating-rules.md
.skills/teaching/references/teaching-notes-template.md
.skills/teaching/SKILL.md
.skills/VERSION
AGENTS.md
CLAUDE.md
CMakeLists.txt
docs/book/01-cmake-workspace.md
docs/book/05-owned-string.md
docs/book/11-tokenizer.md
docs/book/16-store-interface.md
docs/book/17-jsonl-write.md
docs/book/20-testing-discipline.md
docs/book/24-hello-ncurses.md
docs/book/34-embed-sqlite.md
docs/book/38-hello-sockets.md
docs/book/42-daemon-extraction.md
docs/book/exercises/README.md
docs/book/README.md
docs/chain/chain-summary.md
docs/chain/concept-index.md
docs/chain/concepts/daemon-architecture.md
docs/chain/concepts/embedded-databases.md
docs/chain/concepts/file-persistence.md
docs/chain/concepts/hand-rolled-parsing.md
docs/chain/concepts/manual-memory.md
docs/chain/concepts/network-programming.md
docs/chain/concepts/polymorphism-in-c.md
docs/chain/concepts/testing-in-c.md
docs/chain/concepts/tui-with-ncurses.md
docs/chain/prerequisites-graph.md
docs/issues/0001-drift-2026-05-04.md
docs/teaching/build-philosophy.md
docs/teaching/notes/01-cmake-workspace.md
Good "git" signature with ED25519 key SHA256:FkAu8FhMvjqfuGtBtW5Na06E8D1cgS3gTghYaVN3Too
No principal matched.
src/core/CMakeLists.txt
src/core/empty.c
TODO.md

```

## What to do with this

Look at the file list. Any chapter in this book that toured one of those files might be drifting. Cross-reference with `docs/issues/NNNN-drift-*.md` (the latest drift report should also have flagged the high-severity ones).

Once you've reviewed and updated the affected chapters, the next `update.sh` run will start fresh from `abe2aecaf4481da73ec3a92d3d03b50c4a126823`.
