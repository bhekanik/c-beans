# Exercises template

Each chapter that has something worth reinforcing ships a sibling exercises file under `docs/book/exercises/<NN>-<title>-exercises.md`. Per **rule 19 — varied practice for transfer**.

## When to ship exercises (and when not to)

**Ship them when** the chapter teaches a concept the learner could plausibly fail to wield in a different context. That's most chapters.

**Skip them when**:
- The chapter is pure ceremony (workspace setup, dependency declaration, license choice, etc.) and there's nothing to drill.
- Every exercise idea you can think of is contrived — the chapter's concept doesn't generalise enough to drill in varied contexts.

The bar is **reinforcement**, not coverage. An exercise set with 1 strong exercise beats one with 3 generic exercises.

## Filename convention

```
docs/book/exercises/<NN>-<kebab-case-title>-exercises.md
docs/book/exercises/<NN>-<kebab-case-title>-answers.md
```

Same `NN` and title slug as the chapter. Example: chapter 07's exercises live in `docs/book/exercises/07-dap-transport-and-seq-exercises.md` and `…-answers.md`.

## Required frontmatter

```yaml
---
chapter: 7
session_id: M2-2
title: DAP transport and atomic seq — exercises
exercises:
  - grade: wield
    targets: thiserror::Error and ?-propagation
  - grade: stretch
    targets: AtomicI64 across language boundary (C _Atomic)
  - grade: synthesise
    targets: combine generic <T, R> with serde-typed structs from chapter 06
test_command: cargo test --workspace --test chapter_07_exercises
---
```

The `exercises` array is the agent's index — agents reading this file before a session use it to pick which exercise the learner picks.

## Suggested file structure

```markdown
# Chapter NN — Exercises

> Per rule 19. Pick what reinforces; skip what doesn't.

## How to use this set

- **Solo**: write the code, run the test command, see green. Stuck? Hint section first.
- **With LLM-as-teacher**: pick an exercise, share your solution, the agent runs the test and surfaces what your choices reveal.
- **In-session**: tell the agent during the live session that you'd like to do an exercise; they'll author the prompt + grade your solution + diagnose patterns in real time.

Answer key is in [`<NN>-<title>-answers.md`](<NN>-<title>-answers.md). Try first; peek when you've taken your swing.

---

## 🛠️ Exercise 1 — Wield: <one-line concept being drilled>

**Sticky-point targeted**: <which confusion from the teaching-notes companion this drill is aimed at, e.g. "From-vs-Display conflation">

### Problem

<Problem statement. Concrete enough that a learner sitting cold can start. Avoid open-ended "build a thing" — give the *contract* (signature, expected behaviour, where the file goes).>

### Contract

```rust
// crates/<crate>/tests/chapter_NN_exercises/wield.rs (or equivalent)
pub fn <function_name>(<args>) -> <return_type> {
    todo!()
}
```

The function must satisfy:
- <invariant 1>
- <invariant 2>

### Test command

```bash
cargo test --workspace --test chapter_NN_exercises wield
```

### Hint (peek if stuck for >10 minutes)

<details>
<summary>Click for hint</summary>

<One paragraph hint. Doesn't give away the answer; nudges past the sticking point. Often: "look at how the chapter solved a related problem at line X.">

</details>

---

## 🚀 Exercise 2 — Stretch: <cross-domain concept drill>

**Sticky-point targeted**: <which confusion this drill addresses>

### Problem

<Problem statement, framed in a different domain than the chapter's example. If the cross-domain stretch is to a different language, say so explicitly and give the language's setup.>

> **Note**: this exercise is in <language> rather than <chapter's language>. Set up: `<setup command>`. The point is to feel how <chapter concept> shows up in another language — what's the same, what's different, where the pain lives in each.

### Contract

```<language>
<contract>
```

### Test command

```bash
<test command — for cross-language exercises this might be a different test runner>
```

### Hint

<details>
<summary>Click for hint</summary>

<hint>

</details>

---

## 🔀 Exercise 3 — Synthesise: <combining concepts>

**Sticky-point targeted**: <which confusion this drill addresses>

**Combines this chapter with**: chapter <prev-NN> — <concept>.

### Problem

<Problem statement that requires using both this chapter's concept and a prior chapter's concept together. The combination is the lesson — neither concept alone is enough.>

### Contract

```rust
<contract>
```

### Test command

```bash
cargo test --workspace --test chapter_NN_exercises synthesise
```

### Hint

<details>
<summary>Click for hint</summary>

<hint>

</details>

---

## ✍️ Exercise 4 — Prose: <decision question>

**Sticky-point targeted**: <which confusion this drill addresses>

This is a written exercise — answer in 200–400 words. No code expected. The point is to drill the *judgment* the chapter teaches.

### Question

<A genuinely-answerable-wrong design question. "Why X over Y?" or "When would you choose Z?" Avoid leading questions where the answer is in the question itself.>

### What a good answer covers

- <criterion 1>
- <criterion 2>
- <criterion 3>

(Reference answer + commentary in the answer key.)

---

## See also

- ← [Chapter NN — <title>](../<NN>-<title>.md)
- → [Chapter NN+1 — <title>](../<NN+1>-<title>.md)
- [Answer key](<NN>-<title>-answers.md)
```

## Style notes

- **Each exercise has a `Sticky-point targeted` line.** This is what justifies the exercise existing. If you can't articulate which sticky point an exercise drills, it probably shouldn't exist — drop it rather than ship a generic drill.
- **Contracts are explicit.** Function signature, file location, expected behaviour. The learner shouldn't waste time scaffolding — they should spend time *thinking about the concept*.
- **Tests deterministic where possible.** Behavioural through the contract by default. When the implementation IS the lesson (e.g., "use `AtomicI64`, not `Mutex<i64>`"), test the implementation explicitly **and label this** in the prose so the learner knows their freedom is bounded and why.
- **Hints stay non-spoiling.** A good hint says "look at section X of the chapter" or "consider what happens when the input is empty." It does not give the answer.
- **Cross-language exercises specify setup.** Don't assume the reader has a C toolchain or a Python interpreter ready — give the one-line setup command.

## Anti-patterns

- **Exercises that just rewrite the chapter's example.** Zero transfer; learner doesn't have to think.
- **Open-ended "build a thing" prompts.** Without a contract, the learner spends time on incidental design choices instead of the concept.
- **Exercises with no test.** Without a deterministic check, the learner can't tell green from red, and the LLM-as-teacher mode loses its grading signal. (Prose exercises are the only exception — graded by reference answer + commentary, with the LLM as judge.)
- **Quota-filling.** "Each chapter must have 3 exercises." No. Ship what reinforces, skip what doesn't.
- **Smuggling new concepts via exercises.** If the exercise needs a concept the chapter didn't teach, it violates rule 3. Use only concepts already covered.
