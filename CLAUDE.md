# CLAUDE.md — Claude Code specific guidance

You are working on **c-beans**, a deliberate-learning C project. Read [`AGENTS.md`](AGENTS.md) first — that's the canonical pedagogy and project conventions. This file adds Claude-Code-specific notes on top.

## Mode

**Teaching mode is the default.** Don't write code without checking the chapter.

When a fresh session starts cold (no conversation history), follow the AGENTS.md "fresh session" checklist (steps 1-10) before writing anything.

## Anti-patterns to avoid

- **Apologetic prose.** "I apologize for the confusion. Let me try again." → just try again. The user reads the diff, not the apology.
- **Assuming a tool exists because docs mention it.** `clang-tidy` is not installed on this machine; check `which clang-tidy` before trying to run it. (`brew install llvm` makes it available; document, don't assume.)
- **Refactoring "for consistency" while fixing a bug.** Don't. Smallest possible diff. Mention adjacent observations at the end of the response.
- **Writing tests that pass without exercising the code path.** A test that asserts `result != NULL` when the implementation always returns a non-null fixed pointer is sycophantic. Re-read the `tdd` skill's Implementation Swap Test before writing tests.
- **Generating boilerplate to fill chapter / task files.** Stub chapters have a deliberate shape (frontmatter + outline + see-also). Don't pad them with prose that hasn't been verified live.
- **Pre-empting compiler / ASan errors.** Don't write "correct" code from the start to avoid an instructive error. The error IS the curriculum.

## Tooling on this machine (verified 2026-05-04)

```
cmake     4.2.1            ✓
clang     21.0.0 (Apple)   ✓
make      3.81 (GNU)       ✓ (older — chapter 01 sticks to plain make rules; Phase C may want a newer make for some patterns)
clang-format installed at /opt/homebrew/bin/clang-format ✓
clang-tidy NOT installed — `brew install llvm` and add `/opt/homebrew/opt/llvm/bin` to PATH if needed
ncurses headers available system-wide ✓
gh CLI    2.88.1           ✓
```

When chapter steps assume a tool, verify it's actually installed before claiming the chapter is verified. Capture verbatim version strings in the chapter so a learner can spot drift.

## Two modes of work in this repo

- **Building c-beans** — writing the chapter's example code. Default; in teaching mode, paced by the chapter.
- **Documenting c-beans** — editing chapter files, teaching notes, the session plan, the anchor table. Always allowed; doesn't require a teaching session in progress.

If you're documenting (writing chapters, fixing chapter bugs), apply the **humanizer** rules from `.skills/humanizer/`. Specifically: em-dashes ≤1 per paragraph; avoid "delve, leverage, garner, pivotal, tapestry, intricate, showcase, foster"; avoid promotional language ("vibrant", "robust", "comprehensive", "powerful"); use second person for instructions; vary sentence length aggressively.

## Specific Claude Code conventions

- **No emojis in code or chapters unless the user asks.** The chapter template uses `🤔`, `🔮`, `📣`, `🛠️`, `🚀`, `🔀`, `✍️` as discrete predict/teach-back/exercise markers — those are part of the curriculum format, not decoration.
- **Match the lazydap chapter format exactly.** The shape is paid for in pain. New chapters look like the lazydap chapters look. Diverging "to improve" almost always degrades.
- **Prefer surgical edits to rewrites.** Use `Edit` for known-shape changes; reserve `Write` for new files or full rewrites.
- **Use `TaskCreate` / `TaskUpdate` for multi-step session work.** Especially during chapter-write sessions where you're: writing chapter prose, writing teaching-notes, writing example code, running verification, capturing output, writing exercises (rule 19) + answer key, committing, tagging.
- **Exercises are sibling files, never inline.** `docs/book/exercises/<NN>-<title>-exercises.md` + `…-answers.md`. Chapter narrative gets a "preview" linking to them (per the chapter-template "Exercises" section). Skip exercises for ceremony chapters; ship 2–3 graded exercises elsewhere when there's transfer to drill.

## Sanitizer flags (for chapter-level CMake examples)

The `BEANS_SANITIZERS=ON` CMake option (from chapter 03) wires `-fsanitize=address,undefined -fno-omit-frame-pointer` for debug builds. Keep this consistent in chapter examples that introduce new sanitizer-relevant code.

For Linux CI, ASan + UBSan run cleanly. On macOS, leak detection requires `MallocStackLogging` env vars; document this in the chapter where it first matters.

## See also

- [`AGENTS.md`](AGENTS.md) — canonical pedagogy and conventions
- [`.skills/teaching/SKILL.md`](.skills/teaching/SKILL.md) — the portable pedagogy
- [`.skills/humanizer/SKILL.md`](.skills/humanizer/SKILL.md) — chapter prose rules
- [`docs/teaching/sessions.md`](docs/teaching/sessions.md) — session plan
- [`docs/teaching/c-anchor-table.md`](docs/teaching/c-anchor-table.md) — JS → C pain anchors
- [`docs/book/exercises/`](docs/book/exercises/) — varied-practice exercise sets per chapter (rule 19)
