# Exercises

Varied-practice exercise sets per chapter. Per **rule 19** of the [`teaching` skill](../../../.skills/teaching/SKILL.md).

## What lives here

For each chapter that ships exercises, two sibling files:

```
<NN>-<title>-exercises.md   # prompts: problem statement, contract, test command, hints
<NN>-<title>-answers.md     # reference solutions + commentary + common wrong attempts
```

Same `NN` and slug as the chapter (e.g., chapter `05-owned-string.md` → `05-owned-string-exercises.md` + `05-owned-string-answers.md`).

## Why exercises (and why sibling files)

Rule 4's "you do" round verifies the learner can wield a concept *in the chapter's context*. **Exercises verify they can wield it elsewhere** — varied surface, different problem shapes, sometimes a different language.

Sibling files (rather than inline-in-chapter) buy three things:

1. **Chapter stays scannable.** The narrative isn't padded with drill problems.
2. **Exercise sets can grow.** As yield data accumulates, exercises get added / replaced / refined without touching the chapter.
3. **Spoiler protection by filename.** A learner who wants to try an exercise opens the `-exercises.md` file; the answer key is one click away but not in their face.

## When a chapter ships exercises (and when it doesn't)

**Ships exercises:**
- Concept transfers — there's a non-trivial way to apply it in a different surface.
- Sticky points exist (per the teaching-notes companion). Exercises target specific stickies.
- The "you do" round in the chapter felt like the floor, not the ceiling.

**Skips exercises:**
- Ceremony chapter (workspace setup, dependency declaration, license choice). Nothing to drill.
- Concept doesn't generalise enough to drill in varied contexts without contrivance.
- Every exercise idea you can think of is just a rewrite of the chapter's example.

The bar is **reinforcement**, not coverage. **Don't backfill stubs to "fill out the directory"** — empty is the right state until a chapter earns its set.

## Exercise grades

| Grade | Marker | What it is |
|---|---|---|
| Wield | 🛠️ | Near-context variation. Same shape as the chapter's example, different surface. |
| Stretch | 🚀 | Different domain — different protocol, different data, sometimes a different language entirely. |
| Synthesise | 🔀 | Combines this chapter's concept with a prior chapter's. The combination is the lesson. |
| Prose | ✍️ | Decision-flavoured. Written answer (200–400 words). For when the concept is a judgment, not a function. |

Typical chapter ships **2–3 exercises**. Pick what reinforces; ignore what doesn't.

## How a learner uses this

- **Solo:** open the `-exercises.md` file, write code, run the test command, see green. Stuck? Hint section first; answer key as last resort.
- **LLM-as-teacher:** the agent reading the chapter also reads the `-exercises.md` file's frontmatter; learner picks an exercise, agent grades the solution against the deterministic test, surfaces what the solution reveals.
- **Live in-session:** learner says "let's do exercise 2 now," agent runs the prompt + grades + diagnoses in real time.

## Authoring contract (when an agent writes a new exercise set)

1. **One exercise per sticky-point at most.** Each exercise has a `Sticky-point targeted:` line referencing the chapter's teaching-notes companion. If you can't articulate which sticky-point an exercise drills, drop it.
2. **Contracts are explicit.** Function signature, file location, test command, expected behaviour. The learner thinks about the concept, not about scaffolding.
3. **Tests deterministic where possible.** Behaviour-through-the-contract by default — Implementation Swap Test from the project's `tdd` skill applies. Exception: when *the implementation* IS the lesson, test the implementation directly **and label this** in the prose.
4. **Run-before-publish discipline.** Answer-key code must run; tests must pass against the answer key before the exercise set ships. Same as rule 16 for chapters.
5. **No new concepts.** Rule 3 still caps. Exercises drill what's been taught, never smuggle in something new.

Templates: [`exercises-template.md`](../../../.skills/teaching/references/exercises-template.md) and [`exercise-answers-template.md`](../../../.skills/teaching/references/exercise-answers-template.md) in the vendored teaching skill.

## See also

- [`.skills/teaching/SKILL.md`](../../../.skills/teaching/SKILL.md) — rule 19 in full
- [`.skills/teaching/references/exercises-template.md`](../../../.skills/teaching/references/exercises-template.md) — exercise file template
- [`.skills/teaching/references/exercise-answers-template.md`](../../../.skills/teaching/references/exercise-answers-template.md) — answer-key template
- [`docs/teaching/notes/`](../../teaching/notes/) — teaching-notes companions; the sticky-points exercises target live here
