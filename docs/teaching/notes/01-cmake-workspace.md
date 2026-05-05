---
chapter: 1
session_id: WS-1
title: CMake workspace
sessions_run:
  - date: 2026-05-04
    status: paused-mid-session
    resumed: false
    coverage:
      done: [predict-Q1-JS-analogy, predict-Q2-min-CMake-categories, predict-Q3-missing-subdir-error, predict-Q4-empty-file-build, walkthrough-root-CMakeLists, walkthrough-src-core-CMakeLists, try-it-yourself-stage-A-build, try-it-yourself-stage-B-cleanup]
      pending: [compiler-conversation-deliberate-error, what-you-can-run-now-demo, teach-back-Q1-Q4, artifact-commit-and-tag]
    resume_at: "Compiler conversation: learner edits add_subdirectory to src/nonexistent, runs cmake -B build, reads error, stops at broken-state checkpoint for verification before restoring."
---

# Teaching notes — Chapter 01: CMake workspace

> **Status:** chapter file is complete and verified end-to-end (commands run, outputs captured verbatim 2026-05-04 on macOS arm64 with CMake 4.2.1, AppleClang 21.0.0). This notes file gets updated as the chapter is taught live.

## Concept anchor

The chapter teaches CMake workspace structure for a multi-module C project:

- The root `CMakeLists.txt` declares the project + standard + global options
- Each `src/<module>/` directory becomes its own CMake target via `add_subdirectory`
- Each module is a STATIC library; the architecture chapter explains why static
- `target_include_directories(... PUBLIC ...)` is the modern CMake style; consumers inherit include paths

**Edge-case scope creep to resist:** the chapter does NOT cover `find_package`, `FetchContent`, install rules, or test discovery. Those land in chapters 03 (conventions), 17 (atomic file writes — needs `find_package(Threads)` if it touches threading), and 34 (sqlite via FetchContent).

**One concept per session:** "modular CMake structure." Adjacent concepts (compiler warnings, sanitizers, format checks) are deliberately deferred to chapter 03 even though they would fit here. Don't fold them in.

## Common wrong predictions (anticipated, to be calibrated against real sessions)

| Predict question | Likely wrong answer | Why learners go there | How the chapter currently calibrates |
|---|---|---|---|
| Q: How is CMakeLists.txt analogous to JS? | "It's package.json" | both are at the root, both declare what to build | The chapter explicitly redirects: it's webpack.config.js, not package.json. Package management in C is a separate concern. |
| Q: What happens if I configure without src/core/CMakeLists.txt? | "Build error at compile time" | analogy with TS — type errors land at compile, not parse | CMake validates `add_subdirectory` at *configure* time. The chapter shows the verbatim error to anchor this. |
| Q: Will compiling an empty .c file work? | "No, every file needs at least one declaration" | mental model from TS where empty modules sometimes warn | Empty C compilation unit IS valid; produces zero-symbol object. Chapter shows the `ranlib: warning: ... has no symbols` to teach this. The follow-up trap is set up for chapter 02: empty `main.c` for a *binary* target won't link. |
| Q: PUBLIC vs PRIVATE include dirs? | "PUBLIC means anyone can read; PRIVATE means encapsulated" | analogy with class-visibility modifiers | Wrong frame. PUBLIC/PRIVATE here is about *propagation*: PUBLIC propagates to consumers via the linker; PRIVATE doesn't. The chapter calibrates with the consumer-link example (chapter 02 will need PUBLIC). |

## What surprised the learner

### 2026-05-04 (session 1, paused mid-session)

- **The "empty .c → no output" prediction.** Learner predicted Q4b ("`cmake --build build` will print nothing since the file is empty"). Actual: three stages of work print regardless — compile to `.o`, archive to `.a`, ranlib symbol-index pass. Plus the doubled `ranlib: warning: ... has no symbols` quirk on macOS. The model bug was conflating "empty source" with "no work to do." The build tool's choreography runs whether or not there are symbols to dance with. Learner caught the lesson cleanly once we ran it. *(This was anticipated in the wrong-predictions table; confirmed in live data.)*
- **The `add_subdirectory` two-arg form.** Learner attempted Stage A while the agent was off updating skill rules; produced `add_subdirectory(src/core src/string_)` (treating it as "include both"). Actual semantics: `add_subdirectory(<source-dir> [<binary-dir>])`. The misuse caused a "weird success" — `src/core` was processed but its build output landed under `build/src/string_/`, while `src/string_/CMakeLists.txt` was never read. Surfaced post-fact via the leftover `build/src/string_/libbeans_core.a` after the user fixed the line. Worth flagging in the chapter as a teach-able failure mode.
- **Build dir state survives schema changes.** Concrete consequence of the above: after fixing `add_subdirectory`, an incremental rebuild (no `rm -rf build`) left the misplaced `libbeans_core.a` artifact behind. Surfaced the "out-of-source build is your reset" lesson live. Worth promoting from sidebar to inline note in Step 4 of the chapter.

## Sticky points (concepts that needed a second pass)

### 2026-05-04

- **The two-phase CMake build (configure vs build).** Learner's Q3 wrong prediction was "fail at build time" (model: one-phase tool that discovers things on the way). Calibration via the live `cmake -B build` error landed the configure/build distinction; the JS-world analog (no clean two-phase model in tsc/webpack; closest is Bazel) helped frame why this is alien. Worth retaining the calibration story in the chapter.

Anticipated surprises based on the learner's profile (8yr JS/TS, current Rust learner, has felt some C pain on the pre-bookgen-archive parser):

- **The ranlib "has no symbols" warning is FINE.** A learner reading "warning" twice in the build output may stop and try to fix it. The chapter calls it out explicitly so they don't.
- **There's no `npm install` analogue.** A learner who's only ever done `npm install && npm run build` may look for the install step. The chapter explicitly says CMake is the build *configuration*, not the dependency manifest.
- **The trailing underscore in `src/string_/` is deliberate, not a typo.** Calls out the `string` standard-library shadow.

## Sticky points (concepts that needed a second pass)

(To be filled after the first live teach.)

Anticipated based on the C anchor table:

- **What "static library" means.** A learner who has only thought of libraries as `.dll` / `.so` (or `node_modules/`) may miss that `.a` is "compile this code, bundle it for later linking." The chapter walks the three options (STATIC / SHARED / OBJECT) but may need a side conversation in-session.
- **The configure-vs-build distinction.** `cmake -B build` vs `cmake --build build` are two separate steps. Why? Because CMake is a *generator* — it produces Makefiles (or Ninja files) that then run the actual compiler. This double-stepping is alien to npm-world (`npm run build` is one command). May warrant an extra verbal explanation.
- **Out-of-source builds.** Why `build/` and not `dist/` or just compiling in place? The `-B` flag's significance. The chapter mentions it; live, may want to demo `rm -rf build` and rebuild to show how clean the source tree stays.

## Refinement landed

### 2026-05-04 — Checkpoint discipline added to "Try it yourself" + "Compiler conversation"

**Surfaced by:** WS-1 live session, the learner.

**Problem:** Both the "Try it yourself" exercise (build a second library, then delete it) and the "Compiler conversation" walkthrough (modify a line, see the error, restore) were structured as collapsed sequences — "do all of this then tell me." The cleanup / restore step destroys the evidence the agent needs to verify the prior stage actually worked. By the time the learner reports done, the second library is gone, the broken `add_subdirectory` line is restored, and the agent can only verify the *final* state — not the construction the lesson was actually about.

**Fix:** split both sections into Stage A → checkpoint → Stage B, with explicit "tell me when you're at this point" pauses for the learner to verify with the LLM-as-teacher before tearing down or restoring.

**Lifted to rule level:** propagated up to teaching skill rule 4 (gradual release / checkpoint discipline) and into chapter-template's "Try it yourself" + "Compiler conversation" sections. Future chapters with multi-stage exercises now have a template to follow. Recorded in `~/.dotfiles/.skills/teaching/SKILL.md` and `references/operating-rules.md` as originating from this session.

## Refinement ideas

- [ ] **Add a sidebar on `compile_commands.json`** if the learner is using clangd / a C-aware editor and asks about completion. (Skip if they don't ask — staying focused.)
- [ ] **Show the generated Makefile briefly** if the learner is curious about what CMake actually produces. The view of `cat build/Makefile` is a "wow" moment for many learners and demystifies CMake. (Optional side-quest; don't insist.)
- [ ] **If the learner has used Cargo:** explicitly compare `[workspace]` + `add_subdirectory()`. Lazydap's chapter 01 is the Rust counterpart; offer to read it side-by-side after the teach-back.
- [ ] **Watch for the "but my IDE handles this" reflex.** Some IDEs (CLion, VS Code with a CMake extension) hide the configure step. Make sure the learner runs `cmake -B build` from the terminal at least once so they understand the seams.

## Exercises authoring notes

Per rule 19. **This chapter ships zero exercises.**

**Why:** ceremony chapter. The single "you do" task (add a second library, then remove it) lives inline as round 3 of gradual release per rule 4. Any far-transfer exercise would either:

- Rewrite the chapter's example with surface-level renaming (zero transfer) — anti-pattern.
- Reach for territory the chapter doesn't cover (e.g., a binary target, `find_package`, install rules) — violates rule 3 by smuggling in a new concept.

The bar is *reinforcement*, not coverage. Empty is the right state.

**When the chapter would earn exercises:** if a future revision of chapter 03 (conventions as code) splits and pushes some CMake content here — e.g., header-only library targets, INTERFACE libraries, or `target_compile_features` — the surface broadens enough to drill. Revisit then.

## Notes for future sessions on this chapter

(Empty — first teach hasn't run yet.)

## Did the artifact land?

### 2026-05-04 (paused mid-session)

Artifact landed in Stage A of "Try it yourself": both `libbeans_core.a` and `libbeans_string.a` built, `file` confirmed `current ar archive random library`. Stage B verified clean teardown — back to single-library state. The chapter's outcome promise ("`cmake -B build && cmake --build build` produces `build/src/core/libbeans_core.a`") is met as of session pause.

What's NOT done: the deliberate-error walkthrough (compiler conversation), the final "what you can run now" demo, and the teach-back questions. Resume at the compiler-conversation predict.

The artifact for this chapter is "the learner can `cmake -B build && cmake --build build` and produce `libbeans_core.a`." Verifiable with `file build/src/core/libbeans_core.a` reporting `current ar archive random library`. The chapter provides this exact verification command.

**Ceremony framing:** the chapter is named as ceremony in its own opening. Watch for the learner expecting a meatier artifact than "library exists." Confirm at chapter close: "we don't have anything to demo today because this was setup. Tomorrow's binary is what makes this real."

## Reuse log

(Empty — first run only. Update on next teach.)

## Verification record

| Date | What was verified | Output captured | Result |
|---|---|---|---|
| 2026-05-04 | `cmake -B build && cmake --build build` end-to-end | See chapter Step 3 + Step 4 verbatim outputs | ✓ matches |
| 2026-05-04 | Try-it-yourself exercise (second library) | See "Try it yourself" expected output | ✓ matches |
| 2026-05-04 | Compiler-conversation deliberate mistake (`add_subdirectory(src/nonexistent)`) | See compiler-conversation section verbatim error | ✓ matches |

Verification environment: macOS 25.4.0 arm64, CMake 4.2.1, AppleClang 21.0.0.21000099 (`/usr/bin/cc`), GNU Make 3.81.

Re-verify if any of: CMake major version changes, AppleClang major version changes, or the `add_library STATIC` default behaviour changes (unlikely but possible).
