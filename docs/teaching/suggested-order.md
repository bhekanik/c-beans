# Suggested chapter order (dependency-derived)

_Generated 2026-05-25T20:21:18.319294+00:00 from `/Users/bhekanik/code/bhekanik/c-beans` (regex-fallback). 3 files, 0 import edges._

This is a **starting order**, not a session plan. Derived by BFS from the entry point over the import graph (Understand-Anything's approach). Write `sessions.md` over it and **override the order on pedagogical grounds**: cap one new concept per session (rule 3), defer load multipliers (rule 8), and lead with pain anchors (rule 7). Trust the structure here; re-shape the *teaching* sequence.

**Entry point:** `cmake-build-debug/CMakeFiles/4.2.2/CompilerIdC/CMakeCCompilerId.c`

## Overview & entry point

| File | depth | fan-in | fan-out | key definitions |
|---|---|---|---|---|
| `cmake-build-debug/CMakeFiles/4.2.2/CompilerIdC/CMakeCCompilerId.c` | 0 | 0 | 0 | — |

## Unreached (no import path from entry) — order by fan-in

| File | depth | fan-in | fan-out | key definitions |
|---|---|---|---|---|
| `cmake-build-debug/CMakeFiles/4.2.2/CompilerIdC/apple-sdk.c` | — | 0 | 0 | — |
| `src/core/empty.c` | — | 0 | 0 | — |

## How to use this

1. README / overview first ("what is this?"), then the entry point ("how does it start?").
2. Walk outward by depth — each chapter should build on the prior depth's concepts.
3. Collapse or split buckets to honour the one-concept cap; a depth bucket is not a chapter.
4. Unreached files are usually utilities/tests — fold them in where their concept is needed.
