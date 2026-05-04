# Workspace setup (pre-M0)

Sets up the build system, conventions, and CI that everything else stands on. Three chapters: 01 (CMake workspace), 02 (first binary), 03 (conventions as code).

## What

A buildable C project with:

- Modular CMake structure (each module its own library, linked into a single binary)
- `clang-format` + `.clang-tidy`
- ASan/UBSan toggle for debug builds
- GitHub Actions CI (Ubuntu + macOS)
- Chapter-tag release workflow

## Why

Without the workspace and conventions, every later chapter is also implicitly teaching build-system concepts. Splitting them out keeps later chapters focused on their actual concept.

## How

| Chapter | Concept | Artifact |
|---|---|---|
| [01](../book/01-cmake-workspace.md) | CMake workspace structure | `cmake -B build && cmake --build build` succeeds; produces `libbeans_core.a` |
| [02](../book/02-hello-beans.md) | First binary linking a library | `./build/bin/beans` prints `hello, beans` |
| [03](../book/03-conventions-as-code.md) | clang-format, sanitizers, CI | `BEANS_SANITIZERS=ON` build runs cleanly; `clang-format --dry-run --Werror` passes |

## Success criteria

- [ ] `cmake -B build -DCMAKE_BUILD_TYPE=Debug -DBEANS_SANITIZERS=ON` configures cleanly
- [ ] `cmake --build build` succeeds with `-Wall -Wextra -Wpedantic -Werror` enabled
- [ ] `clang-format --dry-run --Werror` passes on every committed `.c` / `.h` file
- [ ] CI green on Ubuntu and macOS

## Files

After chapter 01:

- `CMakeLists.txt` (root)
- `src/core/CMakeLists.txt`
- `src/core/empty.c`

After chapter 02:

- `src/cli/CMakeLists.txt`
- `src/cli/main.c`
- `include/beans/core.h`

After chapter 03:

- `cmake/Sanitizers.cmake`
- `cmake/CompilerWarnings.cmake`
- `Makefile` (thin wrapper)
- (existing `.clang-format`, `.clang-tidy`, `.github/workflows/*` already in place)

## See also

- [`../book/01-cmake-workspace.md`](../book/01-cmake-workspace.md) — chapter 01
- [`../teaching/sessions.md`](../teaching/sessions.md) — session plan
- [`../../ARCHITECTURE.md`](../../ARCHITECTURE.md) — module layout this scaffolds
