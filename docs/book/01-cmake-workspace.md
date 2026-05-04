---
chapter: 1
session_id: WS-1
title: CMake workspace
phase: 0
estimated_time_minutes: 60
artifact: A CMake workspace with one member library that builds cleanly via `cmake --build build`
prerequisites:
  - C compiler installed (`clang --version` or `gcc --version` works)
  - CMake 3.20+ installed (`cmake --version`)
  - Git installed
new_concepts:
  - CMake workspace structure — root `CMakeLists.txt` with `project()` + `add_subdirectory()`
  - Module-as-library pattern — each `src/<module>/` is its own CMake target
  - Static libraries vs executables — what `STATIC` means and what gets produced
status: complete
related_milestone: docs/implementation/00-workspace-setup.md
---

# Chapter 01 — CMake workspace

> Session ID: `WS-1` · Phase 0 · ~60 min · [Underlying milestone](../implementation/00-workspace-setup.md)

## What you'll learn

The shape of a CMake workspace for a C project: a root `CMakeLists.txt` that declares the project, sets the C standard, and pulls in subdirectories — each of which is its own library. You'll learn the difference between a static library target and an executable target (the next chapter introduces the executable), and you'll learn why we structure the codebase as one library per concern instead of one big binary.

This chapter has nothing to say about pointers, memory, or any actual C semantics. Those start in chapter 04. The one new concept is build-system structure.

This is a **ceremony chapter**. The artifact is "your CMake setup builds an empty static library cleanly." Nothing user-visible. You can't `./build/something` and see output. The next chapter (02) is where the first runnable binary lands.

## What you'll build

A bare CMake workspace with one member library (`beans_core`) that compiles to an empty static archive. Nothing runs or prints yet. That's chapter 02.

> By the end of this chapter, running `cmake -B build && cmake --build build` will produce `build/src/core/libbeans_core.a`, and `file build/src/core/libbeans_core.a` will report it as `current ar archive random library`. That's something you couldn't do before chapter 01.

## Before you start

Prior knowledge assumed:

- You've used `npm`, `pnpm`, or some package-manager-with-build-script for at least one project. You know what `package.json` is.
- You've heard of compiled languages (Go, Rust, Java). You know that compiled code goes through a build step.
- You can read JSON, YAML, and a config-file dialect of choice.

Setup state required:

- `clang --version` or `gcc --version` should print a recent compiler version
- `cmake --version` should print `>= 3.20`
- An empty directory you can work in (this repo, after `git checkout chapter-01`)

If you skipped chapters, this is chapter 01. There's nothing to skip from. Start here.

What's already in the repo at chapter-01 start state:

- All the docs (`README.md`, `AGENTS.md`, `CLAUDE.md`, `CONTRIBUTING.md`, `ARCHITECTURE.md`)
- The `docs/` tree (book chapters as stubs, teaching plan, blueprint)
- The vendored skills under `.skills/`
- Lint and format configs (`.clang-format`, `.clang-tidy`)
- CI workflow (`.github/workflows/ci.yml`)
- `.gitignore`

What's NOT in the repo yet (and what you'll create during this chapter):

- The root `CMakeLists.txt`
- `src/core/CMakeLists.txt`
- `src/core/empty.c`

---

## Surface your model first

> 🤔 **Q:** How do you think a C project gets built? If you're coming from JavaScript, where does the analogy land — is `CMakeLists.txt` like `package.json`? Like `webpack.config.js`? Like neither?

Pause and answer in your head before continuing.

<details>
<summary>Click after you've answered</summary>

A common answer: "CMakeLists.txt is package.json — it's the manifest that says what to build." That's a half-truth.

The closer analogy: **CMakeLists.txt is like webpack.config.js**, not like package.json. It's the build *configuration*, not the dependency manifest. C has no equivalent of `npm install` baked into the build system. Dependencies in C are handled separately (system package managers, vendored copies, CMake's `FetchContent` for some libraries — we'll touch this in chapter 03 and again in chapter 34 for sqlite). CMake's job is purely "given these source files, produce these artifacts."

A more honest mapping:

- **`package.json`** ≈ nothing in vanilla C. Closest is `vcpkg.json` or `conan.toml` if you use those package managers. Most C projects (including c-beans) skip both.
- **`webpack.config.js`** / `tsconfig.json` ≈ `CMakeLists.txt`. Build configuration: what to compile, with what flags, into what shape.
- **`npm run build`** ≈ `cmake --build build`. The driver command.

The key difference: CMake is a **meta-build system**. It generates Makefiles (or Ninja files, or Visual Studio projects), and those drive the actual compiler. You'll see this in a moment when `cmake -B build` produces a `build/Makefile` and `cmake --build build` runs `make` underneath.

Hold this mental model — config-not-manifest — through the rest of the chapter.

</details>

---

## The pain CMake solves

If you've read any C project's README, you've probably seen build instructions that range from "`make`" to a four-page wiki page with platform-specific shell snippets. There is no canonical answer to "how do I build a C project" in the way `npm install && npm run build` is canonical for Node.

| CMake feature | The pain it fixes | Where you've felt it |
|---|---|---|
| `project()` + `LANGUAGES C` | C's build-system zoo: `make`, `autotools`, hand-rolled bash, "see ./INSTALL", "see Makefile.in" | Every C project's README |
| `add_subdirectory()` | "How do I split a C project into multiple files without a giant Makefile?" | Multi-file C projects |
| Generator-based output (Make / Ninja / Xcode) | "Each of my coworkers uses a different IDE/build tool" | Cross-IDE C teams |
| `target_link_libraries()` | "I built a library; how do I link a binary against it without manually plumbing -L paths?" | Manual linker flag dance |
| `set(CMAKE_C_STANDARD 11)` | "Was that compiled with C89 or C99 or C11? Different platforms, different defaults" | Standard-version drift |
| `CMAKE_EXPORT_COMPILE_COMMANDS ON` | "My language server has no idea what flags to use for completion" | clangd / IDE setup |

CMake is not a C language feature. It's a build tool. The C compiler doesn't know CMake exists. But CMake is how essentially every modern C project is structured (or its rival Meson, which is similar in shape), so you'll touch it every day.

---

## The starting state

Open a terminal in the c-beans directory.

```bash
ls
```

> 🔮 **Predict:** What do you expect to see at chapter-01 start state? Is there a `CMakeLists.txt`?

<details>
<summary>Click after you've predicted</summary>

There is **not** a `CMakeLists.txt`. You'll create one in this chapter. What's already there:

```
AGENTS.md  CLAUDE.md  CONTRIBUTING.md  ARCHITECTURE.md  README.md  TODO.md
book-chain.toml  docs/  .skills/  .github/  .clang-format  .clang-tidy  .gitignore
```

The build system is what you're about to add. Everything else exists to support the chapters.

</details>

---

## Step 1 — Create the root `CMakeLists.txt`

Create the file `CMakeLists.txt` at the repo root with these contents:

```cmake
cmake_minimum_required(VERSION 3.20)

project(c_beans
    VERSION 0.0.1
    DESCRIPTION "Terminal task manager — learn-by-LLM book"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src/core)
```

Walk through it line by line.

### `cmake_minimum_required(VERSION 3.20)`

The first line of any modern `CMakeLists.txt`. It tells CMake "fail loudly if the user has a version older than this." 3.20 is a reasonable floor for 2026 — old enough that every package manager ships it, new enough that we can use `target_*` discipline (the modern CMake style) without defensive workarounds.

The line is *not* optional. Without it, CMake assumes you wrote the file for whatever the user happens to have installed, and pre-3.0 behaviour creeps in for backward compatibility. Always set it.

### `project(c_beans VERSION 0.0.1 DESCRIPTION "..." LANGUAGES C)`

Declares the project. Four pieces:

- **`c_beans`** — the project name. CMake variables like `PROJECT_NAME` and `c_beans_SOURCE_DIR` get set from this. Note the underscore: CMake doesn't enforce identifier syntax, but hyphens cause friction in some places, so underscore-naming is the convention.
- **`VERSION 0.0.1`** — sets `PROJECT_VERSION`. Mostly cosmetic at this point; later (chapter 33, when we ship v0.1) it'll feed into the install steps.
- **`DESCRIPTION "..."`** — same: cosmetic for now, useful when the project gets packaged.
- **`LANGUAGES C`** — explicit. The default is `C CXX` (both C and C++), which makes CMake check for a C++ compiler at configure time. We don't have C++; saying so makes configure faster and the failure mode (no C compiler) clearer.

### The `CMAKE_C_STANDARD` block

```cmake
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
```

Three lines, doing three different things:

- **`CMAKE_C_STANDARD 11`** — compile with C11. The 2011 standard. Modern enough for `_Generic`, atomics, and threads (which we won't use). Old enough to be on every compiler.
- **`CMAKE_C_STANDARD_REQUIRED ON`** — fail the build if the compiler doesn't support C11, instead of silently falling back to C99. Always set this; the silent fallback is a common source of confusion.
- **`CMAKE_C_EXTENSIONS OFF`** — disable GNU extensions. With this off, the compiler flag is `-std=c11`. With it on, the flag is `-std=gnu11`, which enables non-portable GCC/clang extensions (some pretty good ones, like statement expressions and labels-as-values). Turning extensions off keeps c-beans portable. If you ever need a GNU extension, `#ifdef __GNUC__` and document it.

### `set(CMAKE_EXPORT_COMPILE_COMMANDS ON)`

Tells CMake to write a `compile_commands.json` file in the build directory. This file lists every source file, the flags used to compile it, and the working directory. Language servers (clangd, ccls) and analysis tools (clang-tidy) read it to understand your project.

If you've ever used `tsconfig.json` to make TypeScript's language server happy, this is the C equivalent. We turn it on early because the language server experience is the difference between "I can complete struct fields" and "I am editing C in Notepad."

### `add_subdirectory(src/core)`

The interesting line. It tells CMake: "look for a `CMakeLists.txt` inside `src/core/` and process it as part of this project." That nested file will define library targets that the root project pulls in.

This is the modular structure. Each `src/<module>/` directory becomes its own CMake "scope" with its own libraries. The root file orchestrates; each subdirectory does its own job. As c-beans grows, the root file gets a longer `add_subdirectory(...)` list, but each individual `CMakeLists.txt` stays small.

> 🔮 **Predict:** What happens if you try to configure CMake right now, without creating `src/core/CMakeLists.txt` first?

<details>
<summary>Click after you've predicted</summary>

CMake will fail with an error pointing at the `add_subdirectory` line:

```
CMake Error at CMakeLists.txt:8 (add_subdirectory):
  add_subdirectory given source "src/nonexistent" which is not an existing
  directory.
```

(Verbatim output from `cmake -B build` when `src/core/` doesn't exist. You'll see this exact error in the compiler-conversation section below.)

The lesson: CMake validates `add_subdirectory` paths at configure time, not at build time. Misspelled directory names fail loudly and immediately. Good. Some build systems would defer this to compile time; CMake catches it before any compiler runs.

</details>

---

## Step 2 — Create the first member library

Create the directory and files.

```bash
mkdir -p src/core
touch src/core/empty.c
```

Yes, literally an empty file called `empty.c`. We need one source file to satisfy CMake (a library has to have *something* to compile, even if that something contributes zero symbols). Future chapters will add real code; for chapter 01 the empty file is the placeholder.

Now create `src/core/CMakeLists.txt`:

```cmake
add_library(beans_core STATIC
    empty.c
)

target_include_directories(beans_core
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)
```

Read this carefully.

### `add_library(beans_core STATIC empty.c)`

Defines a target called `beans_core`. Three pieces:

- **`beans_core`** — the target name. By convention, library names are prefix-namespaced (`beans_*`) so when c-beans grows multiple libraries, none collide with system libraries or each other.
- **`STATIC`** — what kind of library. Three options exist:
  - `STATIC` — produces a `.a` file (a "static archive"). The library code gets copied into any binary that links it. No runtime dependency on the `.a` file once the binary is built.
  - `SHARED` — produces a `.so` (Linux) / `.dylib` (macOS) / `.dll` (Windows). The library is loaded at runtime; binaries that link it depend on the library file being present at run time.
  - `OBJECT` — produces just the object files, no archive at all. Used when you want a "library" that gets baked into other libraries without producing its own artifact.

c-beans uses `STATIC` everywhere. Reasons: simpler distribution (one binary, no library-path issues), faster startup (no dynamic linker work), simpler deployment (no `LD_LIBRARY_PATH` confusion). We're not building a system that needs runtime swappability of libraries.

- **`empty.c`** — the source file(s). One per line, indented. Future chapters add more files here.

### `target_include_directories(beans_core PUBLIC ${CMAKE_SOURCE_DIR}/include)`

Tells CMake where this library's public headers live. Two parts:

- **`PUBLIC`** — anyone who links against `beans_core` also gets this include path. The alternative is `PRIVATE` (only `beans_core`'s own source can `#include` from this path) or `INTERFACE` (the library has no source, only headers; consumers get the include path but the library itself doesn't).
- **`${CMAKE_SOURCE_DIR}/include`** — the path itself. `CMAKE_SOURCE_DIR` is a built-in CMake variable pointing at the directory of the root `CMakeLists.txt`. So this resolves to `c-beans/include/`.

We don't have any header files yet — `include/` doesn't even exist. That's fine; the path being on the include search list doesn't require it to exist. When chapter 02 adds `include/beans/core.h`, the path is already wired up.

> 🔮 **Predict:** What's the difference between `PUBLIC` and `PRIVATE` here? Does it matter for `beans_core` specifically?

<details>
<summary>Click after you've predicted</summary>

`PUBLIC` vs `PRIVATE` matters when other targets *link against* `beans_core`. With `PUBLIC`, those linker-consumers automatically inherit the include path; they can `#include "beans/core.h"` without re-declaring it. With `PRIVATE`, the include path is for `beans_core`'s own source only; consumers would need to add their own `target_include_directories` for it.

For `beans_core` specifically: `PUBLIC` is right because chapter 02's `beans` binary will link against `beans_core` and need to `#include "beans/core.h"`. If we made it `PRIVATE`, the binary's CMakeLists would have to redundantly declare the include path, which means two sources of truth.

The discipline: include paths that consumers need are `PUBLIC`; include paths only the library itself uses internally are `PRIVATE`. Most module include paths are `PUBLIC` for c-beans.

</details>

---

## Step 3 — Build it

Configure the project:

```bash
cmake -B build
```

> 🔮 **Predict:** What will this print? Will it succeed?

<details>
<summary>Click after you've predicted</summary>

It succeeds. CMake's configure step produces:

```
-- The C compiler identification is AppleClang 21.0.0.21000099
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Configuring done (0.8s)
-- Generating done (0.0s)
-- Build files have been written to: /tmp/c-beans-verify-ch01/build
```

(Your compiler version line will differ depending on whether you're on macOS / Linux / WSL. The shape is the same.)

What happened: CMake found a C compiler (`/usr/bin/cc`), detected its ABI (calling convention, type sizes, etc.), figured out which features it supports, and then *generated* the actual build files — by default a `Makefile` (with the Make generator) under `build/`.

Note the directory: `build/`. The `-B build` flag tells CMake "put the generated build files in this directory." This is the **out-of-source build** convention: source files in the project root, build artifacts in a separate directory. It keeps the source tree clean and lets you have multiple build configurations side by side (`build-debug`, `build-release`, etc.).

</details>

Now compile:

```bash
cmake --build build
```

> 🔮 **Predict:** What gets compiled? What's the output?

<details>
<summary>Click after you've predicted</summary>

A common prediction: "compile errors, because `empty.c` has nothing in it."

It compiles. With one warning. Verbatim output:

```
[ 50%] Building C object src/core/CMakeFiles/beans_core.dir/empty.c.o
[100%] Linking C static library libbeans_core.a
ranlib: warning: 'libbeans_core.a(empty.c.o)' has no symbols
ranlib: warning: 'libbeans_core.a(empty.c.o)' has no symbols
[100%] Built target beans_core
```

What happened, line by line:

- `[ 50%] Building C object ...empty.c.o`: clang compiled `empty.c` into an object file. An empty file is a valid C compilation unit; it produces an object file with zero symbols (no functions, no global variables, just header metadata).
- `[100%] Linking C static library libbeans_core.a`: the linker bundled `empty.c.o` into a static archive at `build/src/core/libbeans_core.a`.
- `ranlib: warning: 'libbeans_core.a(empty.c.o)' has no symbols`: `ranlib` (the tool that builds the symbol index inside an archive) noticed the only object file in this archive contributes zero symbols. Worth flagging, but not an error.

The warning prints twice on macOS — once during the link, once during the archive index pass. Both warnings refer to the same object file. This is a quirk of macOS's `ranlib`, not a bug.

The companion fact, which is the trap waiting in chapter 02: an empty `main.c` for a *binary* target does NOT compile. A binary needs a `fn main`. The linker will refuse: `Undefined symbols: _main`. Empty library OK, empty binary no.

</details>

---

## Step 4 — Verify the artifact

Check the output:

```bash
ls build/src/core/
```

Verbatim output:

```
cmake_install.cmake
CMakeFiles
libbeans_core.a
Makefile
```

Four entries:

- `cmake_install.cmake` — instructions CMake uses for `cmake --install` (we're not using that yet).
- `CMakeFiles/` — internal CMake bookkeeping. Don't touch.
- `libbeans_core.a` — **the artifact**. The static library you just built. The `lib` prefix and `.a` suffix are conventions: every static library on Unix follows them.
- `Makefile` — the actual Makefile CMake generated, which `cmake --build` invoked.

Confirm what kind of file it is:

```bash
file build/src/core/libbeans_core.a
```

Verbatim output:

```
build/src/core/libbeans_core.a: current ar archive random library
```

`current ar archive`: produced by `ar` (the archive tool) in its current format. `random library`: a library with a randomized symbol index for fast lookup at link time. This is exactly what a working static library should look like.

You've shipped chapter 01's artifact. There's no `./build/something` to run because nothing executes yet — `beans_core` is a library waiting for a binary to link it. Chapter 02 builds that binary.

---

## Try it yourself

> 🛠️ **Your turn:** Add a second library, `beans_string`, that has the same shape as `beans_core` (its own subdirectory, its own `CMakeLists.txt`, an empty `.c` file, an `add_library(... STATIC ...)` declaration with the same `target_include_directories` line). Don't write any code in it. Just the manifest and an empty `.c` file.

Steps:

1. `mkdir -p src/string_` (the trailing underscore is intentional — `string` collides with C standard library name; we'll use this naming convention for any module whose name shadows a standard one).
2. Create `src/string_/empty.c` as an empty file.
3. Create `src/string_/CMakeLists.txt` matching the shape of `src/core/CMakeLists.txt`, but with `beans_string` as the library name.
4. Add `add_subdirectory(src/string_)` to the root `CMakeLists.txt`.
5. Run `cmake -B build && cmake --build build`.

Expected output:

```
[ 25%] Building C object src/core/CMakeFiles/beans_core.dir/empty.c.o
[ 50%] Linking C static library libbeans_core.a
ranlib: warning: 'libbeans_core.a(empty.c.o)' has no symbols
ranlib: warning: 'libbeans_core.a(empty.c.o)' has no symbols
[ 50%] Built target beans_core
[ 75%] Building C object src/string_/CMakeFiles/beans_string.dir/empty.c.o
[100%] Linking C static library libbeans_string.a
ranlib: warning: 'libbeans_string.a(empty.c.o)' has no symbols
ranlib: warning: 'libbeans_string.a(empty.c.o)' has no symbols
[100%] Built target beans_string
```

If you got something different, common causes:

- "no source given to target": the `add_library` line lists no source files, or the source file referenced doesn't exist. Check that `empty.c` exists in `src/string_/`.
- "add_subdirectory given source ... not an existing directory": typo in the path or you forgot to `mkdir`.
- The root `CMakeLists.txt` has the wrong path on the `add_subdirectory` line.

When you've confirmed it builds, **delete the string_ directory and remove its `add_subdirectory` line**. You don't need it yet. The exercise was the build, not the artifact. The real `beans_string` library lands in chapter 05, properly motivated.

```bash
rm -rf src/string_
# Then edit CMakeLists.txt and remove the `add_subdirectory(src/string_)` line.
```

Confirm the project still builds with just `beans_core`:

```bash
rm -rf build
cmake -B build
cmake --build build
```

The build should produce just `beans_core` as before.

---

## Compiler conversation

Try this deliberate mistake. In the root `CMakeLists.txt`, change the last line:

```cmake
add_subdirectory(src/core)
```

to:

```cmake
add_subdirectory(src/nonexistent)
```

Re-configure:

```bash
rm -rf build && cmake -B build
```

Read the error.

```
-- The C compiler identification is AppleClang 21.0.0.21000099
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
CMake Error at CMakeLists.txt:8 (add_subdirectory):
  add_subdirectory given source "src/nonexistent" which is not an existing
  directory.
```

What this tells you:

1. CMake validates `add_subdirectory` paths at **configure time**, not build time. The error fires before any compiler runs.
2. The error message tells you the exact line (`CMakeLists.txt:8`) and the exact missing path. This is good error reporting.
3. Compiler detection still ran first. CMake doesn't bail at the first sign of trouble; it gathers configure-time information and then reports all the issues.

Restore the line to `add_subdirectory(src/core)` and re-configure to confirm everything works again.

---

## What you can run now

```bash
cmake -B build
cmake --build build
ls build/src/core/libbeans_core.a
```

Output (after the build):

```
build/src/core/libbeans_core.a
```

(Or you'll get a "no such file" error, which means the build didn't produce the artifact — go back to step 3.)

`file build/src/core/libbeans_core.a` reports it as `current ar archive random library`. The build system you wrote, with one library you declared, produced a real static archive. The skeleton c-beans will grow into is sitting in front of you, ready for code.

**Ladder check.** This is chapter 01, so there's no previous chapter to ladder back to. The starting position was a directory full of docs. The ending position is a working CMake workspace with one buildable static library. The rest of the project layers libraries into this skeleton.

Forward look: chapter 02 adds an *executable* target (`beans`) that links `beans_core` and prints `hello, beans` when you run it. That's the first time you'll see something user-visible run.

This was a ceremony chapter — the build philosophy ([`docs/teaching/build-philosophy.md`](../teaching/build-philosophy.md)) names it as such. There's nothing user-visible to demo. But the next chapter has nothing to land on without this one. The workshop is set up; tomorrow we use it.

---

## Teach-back

Before moving on, answer these in your own words. If you can't, re-read the relevant section.

> 📣 **Q1:** Explain CMake to a colleague who knows JavaScript / TypeScript but not C. What's the analogy that holds, and where does it break? (Hint: not `package.json`.)

> 📣 **Q2:** Why does c-beans use one library per `src/<module>/` instead of compiling everything into a single big archive?

> 📣 **Q3:** A teammate adds a third library and writes `add_library(my_lib SHARED my_file.c)`. They ask why the deployment is breaking. What's the first thing you check, and why?

> 📣 **Q4:** Walk through what happens, second by second, when you run `cmake --build build`. What does CMake do? What does the underlying build tool do? What does the compiler do?

---

## Pain anchors covered

| New construct | The pain it solves | In which language |
|---|---|---|
| `cmake_minimum_required` + `project()` | C's "what build system do I use, what version" sprawl across every project | Every C project's README |
| `add_subdirectory(...)` | "How do I split a C project across files without a giant single Makefile?" | Multi-file C projects |
| `add_library(... STATIC ...)` | Hand-rolling `ar rcs libfoo.a foo.o bar.o` and the index step yourself | Manual library bundling |
| `target_include_directories(... PUBLIC ...)` | "Every consumer of this library has to redundantly add `-I` paths" | Manual `-I` flag dance |
| `CMAKE_EXPORT_COMPILE_COMMANDS ON` | "My language server has no idea what flags this file is compiled with" | clangd / IDE setup |
| Out-of-source build (`-B build`) | `make clean` not actually cleaning everything; `.o` files scattered through the source tree | In-source builds |

---

## See also

- → [Chapter 02 — Hello, beans](02-hello-beans.md) — the first executable
- [Underlying milestone](../implementation/00-workspace-setup.md) — the ship-mode view of this work
- [`docs/teaching/build-philosophy.md`](../teaching/build-philosophy.md) — what "ceremony chapter" means and why naming it matters
- [CMake docs: cmake-buildsystem(7)](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html) — the modern-CMake reference
- [Effective Modern CMake (Manuel Binna)](https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1) — opinionated guide; aligns with the conventions used here
- Sister chapter: lazydap's [`01-cargo-workspaces.md`](https://github.com/planetaryescape/lazydap/blob/main/docs/book/01-cargo-workspaces.md) — Rust's Cargo equivalent, shows how Rust solves the "what build system" problem differently
