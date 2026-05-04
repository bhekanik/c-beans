---
chapter: 1
session_id: WS-1
title: CMake workspace
sessions_run: []
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

(To be filled after the first live teach.)

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

## Refinement ideas

- [ ] **Add a sidebar on `compile_commands.json`** if the learner is using clangd / a C-aware editor and asks about completion. (Skip if they don't ask — staying focused.)
- [ ] **Show the generated Makefile briefly** if the learner is curious about what CMake actually produces. The view of `cat build/Makefile` is a "wow" moment for many learners and demystifies CMake. (Optional side-quest; don't insist.)
- [ ] **If the learner has used Cargo:** explicitly compare `[workspace]` + `add_subdirectory()`. Lazydap's chapter 01 is the Rust counterpart; offer to read it side-by-side after the teach-back.
- [ ] **Watch for the "but my IDE handles this" reflex.** Some IDEs (CLion, VS Code with a CMake extension) hide the configure step. Make sure the learner runs `cmake -B build` from the terminal at least once so they understand the seams.

## Notes for future sessions on this chapter

(Empty — first teach hasn't run yet.)

## Did the artifact land?

(Empty — first teach hasn't run yet.)

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
