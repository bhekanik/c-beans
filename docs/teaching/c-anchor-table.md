# C anchor table

Per teaching skill rule 7: when introducing a new C concept, anchor it to a pain the learner has already felt in a language they ship in production. The learner's primary background is **JavaScript / TypeScript** (8 years), with Python and infra-as-code on top.

There are two kinds of anchoring, both useful:

1. **Syntactic analog** — "this C thing is like that JS thing." Cheap. Gets the learner from zero to "I can read it."
2. **Pain anchor** — "you know how *X* is painful in JS? C has the same shape, but worse, because Y." Expensive. Gets the learner from "I can read it" to "I know why this exists."

The pain anchors land deeper. Lead with them when you can.

---

## Part 1 — Syntactic analogs (JS/TS → C)

A reading-comprehension table. When the learner sees C syntax for the first time, the analog gets them parsing the file faster.

| C feature | JS / TS analog | Where the analogy holds | Where it breaks |
|---|---|---|---|
| `int x = 5;` | `let x: number = 5;` | both bind a name to a typed value | C's `int` is fixed-width on a given platform; JS's `number` is always IEEE-754 double |
| `int x;` (uninitialised) | `let x;` | both reserve a name | C's `x` contains *garbage* (whatever was on the stack); JS's is `undefined`. Reading uninitialised C is UB. |
| `struct Point { int x; int y; };` | `interface Point { x: number; y: number; }` | both define a record shape | C struct has a memory layout; TS interface is purely a compile-time annotation that disappears |
| `Point p = { .x = 1, .y = 2 };` | `const p: Point = { x: 1, y: 2 };` | designated initialisers | C requires the type literal; TS infers from context |
| `int *p` | `let p: number \| null` (sort of) | "thing that points at a value or doesn't" | C pointers can point at *anywhere* — stack, heap, NULL, garbage. JS references are always to live objects or null. |
| `void *` | `unknown` | both opaque, both require a cast/check before use | `void *` has no runtime type info; `unknown` does (sort of, via `typeof`) |
| `enum TaskStatus { ACTIVE, COMPLETED };` | `enum TaskStatus { ACTIVE = 0, COMPLETED = 1 }` | both name integer constants | C enum values can collide silently (two members with same int); TS enum can't |
| `if (x) { ... }` | `if (x) { ... }` | both run the block when truthy | C's "truthy" is "non-zero int". No coercion of strings, objects, arrays — those don't exist as primitives. |
| `for (int i = 0; i < 10; i++)` | `for (let i = 0; i < 10; i++)` | identical loop | identical |
| `switch (x) { case 1: ...; break; }` | `switch (x) { case 1: ...; break; }` | identical syntax | C *requires* `break` or you fall through. JS does too, but TS gives you exhaustiveness. C gives you `default:` and fall-through silence. |
| `static int x = 5;` (file scope) | `// not really a thing` | "module-private state" | the static keyword in C also means "lifetime is whole-program" inside functions — confusing overload |
| `extern int x;` | `// import { x } from './mod'` (sort of) | "this name lives in another translation unit" | C linker resolves at link time, not at parse time. Forward declarations are common. |
| `#include "foo.h"` | `import foo from './foo'` | "pull in another file's stuff" | `#include` is **textual substitution** by the preprocessor. Not a module system. The include guard dance exists because of this. |
| `#define MAX 100` | `const MAX = 100` | "name a constant" | `#define` is textual replacement. No type-checking. Macro hygiene is your problem. |
| `void greet(const char *name)` | `function greet(name: string): void` | function with a string parameter | the C version: the caller owns `name`'s memory; `name` may be NULL; `name` may not be null-terminated; reading past the buffer is UB. |
| `char arr[10]` | `const arr = new Array(10)` (sort of) | "10 things" | C arrays decay to pointers when passed. The size info is gone at the callee. |
| `arr[i]` | `arr[i]` | indexed access | C: no bounds check. Out-of-bounds is UB. ASan catches some at runtime. JS: bounds check, returns `undefined`. |
| `malloc(n)` | `// no equivalent` | "give me n bytes of heap" | every `malloc` MUST be paired with a `free`. JS has GC; C doesn't. |
| `NULL` | `null` | "the absence value for a pointer" | dereferencing NULL in C is UB (typically segfault). JS throws. |
| `printf("hello %s\n", name)` | `console.log(\`hello ${name}\`)` | formatted output | C's `printf` family is variadic and type-unsafe — `%s` with an int crashes. The compiler catches some via `__attribute__((format))`. |

---

## Part 2 — Pain anchors (the deeper move)

For each C pain the learner is about to hit, there's an experienced pain in JS/TS (or a hypothetical one we can construct). The framing **"You know how X is painful in JS? C has the same shape, but worse, because Y"** lands much deeper than **"In C, you have to do Z."**

| C pain | JS / TS analog (felt) | C version (worse, because…) | Where it lands in this book |
|---|---|---|---|
| `char *` ambiguity — pointer with no length | `string` operations on `unknown` after a JSON parse | …the pointer might also be NULL, point at freed memory, or have no `\0` terminator. There's no runtime to catch it. | M1-1 (Owned String) |
| `malloc` / `free` pairing | manually unsubscribing event listeners and forgetting | …forgetting `free` leaks memory; calling it twice crashes; calling it after a use-after-free is silent corruption that surfaces as a different bug somewhere else. | M0-1 (segfault), M1-1 (owned strings) |
| Use-after-free (return pointer to stack local) | accessing `this.x` in a callback after the component unmounted | …the C version may not crash *at all* for thousands of runs; the memory just silently contains a different value when something else allocates over it. Heisenbug factory. | M0-1 (first segfault) |
| Manual array growth | spreading into a new array repeatedly because you don't trust mutation | …you have to write the realloc-on-full code yourself, every codebase, slightly differently. | M2-1 (Vec_int) |
| `switch` fall-through | TS `switch` without exhaustiveness checking on a union | …C's switch silently falls through if you forget `break`. New `enum` member added → `default:` swallows it → bug ships. | M3-1 (tagged unions) |
| Header file dance | exporting from `index.ts` and forgetting one of three places to update | …the `.h` declares, the `.c` defines, and if they diverge the linker error is from another file. The fix is far from the bug. | WS-1 / WS-2 (hello-beans) |
| Undefined behaviour | "this works on Chrome but crashes on Safari" | …UB in C means the **compiler is allowed to do anything**. Optimisations may delete entire branches because they "couldn't legally be reached" given UB elsewhere. The bug is in code you didn't write. | M0-1 (first segfault, ASan) |
| NULL dereference | "Cannot read property 'x' of undefined" | …NULL deref in C is UB; on most systems it segfaults, but the compiler may have already optimised away the NULL check because "what kind of fool would dereference a NULL pointer?" | throughout |
| `errno` dance | promise rejection that doesn't carry context | …functions return -1 on error, you check `errno` separately, and `errno` may have been clobbered by anything else you called between the failing call and the check. | M9-1 (errors), Phase H (sockets) |
| No namespaces | global symbol pollution in pre-modules JS | …everything is in one global namespace at link time. `init()` from your store and `init()` from sqlite both link, neither is qualified, you find out at runtime. | M10-1 (`beans_` prefix discipline) |
| Lack of polymorphism | wishing for traits/interfaces in old JS | …C has function pointers and that's it. You either build a vtable struct yourself, or you compile-time-monomorphise via macros. Both are explicit and verbose. | M7-1 (Store interface) |
| String concatenation everywhere | template literals with user input → XSS | …`sprintf` to a fixed-size buffer overflows; `strcat` to a buffer that's too small overflows; both are silent until ASan finds them or someone exploits them. | M5-2 (escape decoding), Phase G (SQL) |
| Manual buffer management | `Buffer.alloc(n)` but you have to free it | …every codebase grows its own conventions. Some put the size next to the buffer, some don't. Some null-terminate, some don't. Some treat empty as NULL, some don't. None of them agree. | M1-1, M2-1 |
| Tokenising / parsing without exceptions | error handling in a recursive parser without `try/catch` | …you propagate errors through return values manually. Every recursive call needs to check + bubble up. The "happy path" code is buried in error checks. | M5-1, M6-1 |
| File I/O partial reads | `fetch` returning a partial body and you didn't handle it | …`read(2)` may return fewer bytes than asked, even on regular files. You write the loop yourself, every time. | M4-1, M15-2 (TCP framing) |
| TCP message boundaries | WebSocket vs HTTP: WebSocket gives messages, raw socket gives bytes | …TCP gives you a byte stream. Two `send`s may merge into one `recv`; one `send` may split across two `recv`s. You build your own framing protocol. | M15-2 (length-prefixed framing) |
| SQL injection via string concatenation | template-literal SQL in JS where you didn't use a query builder | …in C you write the concatenation by hand; the type system gives you no help; the moment your input contains `'` you're owned. | M14-2 (prepared statements) |
| Race conditions across processes | two tabs writing to localStorage | …two processes writing the same JSONL file get interleaved partial lines; data loss is deterministic if you don't design around it. | M7-4 (atomic file writes), M14-3 (SQLite WAL) |

---

## How to use this table in a session

When teaching a new C concept:

1. Look up the row in part 2 (pain anchor).
2. Lead with the JS/TS pain: "You know how *X* hurts in JS?"
3. Explain why C has the same shape but worse: "C has the same shape, but…"
4. Introduce the C concept as the explicit-but-not-fixed version. We're not solving the pain in C; we're naming it. (Rust solves it. That's the next book.)
5. Capture the pain anchor in the chapter's own pain-anchor table at the bottom of the chapter file.

The point isn't to scare the learner away from C. It's to build the muscle of "what guarantees am I trading away when I write this line?" That muscle is what makes Rust's borrow checker feel like a gift instead of a tax.

---

## Pains specifically the learner has already hit on the existing parser

(These came up in the preliminary parser work — `tokenizer.c`, `json_decoder.c`, `task_parser.c`, `owned_string.c` in the `pre-bookgen-archive` branch. Use them aggressively as anchors when the relevant chapter lands.)

| Pain | Where it surfaced | Chapter that addresses it |
|---|---|---|
| String ownership confusion — who frees `data` when struct copies happen | `owned_string.c` shallow-copy moments | M1-1 (owned String), M1-2 (StringView vs String) |
| Manual realloc bookkeeping — needing length AND capacity | `owned_string.c`'s grow path | M2-1 (Vec_int) |
| Off-by-one in length-bounded copies (`memcpy` vs `strncpy` vs `strlcpy`) | tokenizer string handling | M5-2 (escape decoding) |
| Indexing a buffer past its end without ASan catching it | tokenizer character lookahead | M0-1 (ASan introduction) |
| The "build my own dynamic array" treadmill | `Vec`-shaped code throughout the parser | M2-1, M2-2 (generic via macros) |
| Result-vs-error-code conventions diverging across functions | parser error-bubbling | M9-1 (Result-shaped returns) |
| The header file dance — declaring in `.h`, defining in `.c`, forgetting one | `tokenizer.h` / `tokenizer.c` divergence | WS-1, WS-2 (project structure) |

The original parser code (in branch `pre-bookgen-archive`) is good reference material for "when this chapter lands, here's what the learner already half-built." The chapters do it again, more carefully, anchored.

---

## See also

- `.skills/teaching/SKILL.md` — rule 7 (anchor on experienced pain)
- `.skills/teaching/references/operating-rules.md` — long-form rules
- `docs/book/00-introduction.md` — the book's how-learning-works framing
- Lazydap's `docs/teaching/rust-anchor-table.md` — the Rust counterpart that c-beans's pains feed into
