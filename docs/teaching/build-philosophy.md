# Build philosophy for c-beans (reproduce-mode)

c-beans is a **reproduce-mode** book: the learner builds the project from zero, chapter by chapter. Each chapter ends with a runnable artifact. This is the opposite of lazydap's tour mode (where the artifact is *understanding* of existing code).

## What "artifact" means here

In reproduce mode, the artifact is **a thing the learner can run**, not just a paragraph of understanding:

- A binary that prints something, accepts input, writes a file, or renders a TUI screen.
- A test that passes (after the test harness lands in TDD-1).
- A demonstration of a behaviour: ASan catching a deliberate UB, the daemon receiving a TCP message, the JSONL file being parsed back correctly.

If chapter N's artifact is "you can `./build/beans add 'feed cat'` and the task gets stored", then that command must literally work at the end of the session, on the learner's machine, with output the learner can see.

## Ceremony chapters

Some chapters are ceremony — they set up infrastructure that *enables* future user-visible features but produce nothing the learner would brag about. These exist; pretending they have a meaty artifact is dishonest.

For c-beans, the ceremony chapters are:

- **Chapter 01 (CMake workspace)** — the artifact is "your CMake setup builds an empty static library cleanly." That's it. **Name it as ceremony in the chapter**: "today we set up the workshop. Tomorrow we build the first real thing."
- **Chapter 03 (conventions as code)** — the artifact is "your formatter, linter, sanitizers, and CI workflow are wired up." Name it as ceremony.
- **TDD-1 (Phase D)** — meta-session. The artifact is "the assert harness exists and chapters 04-19's smoke tests now run from `ctest`." Name it as ceremony plus retroactive explanation.

For ceremony chapters, the chapter must explicitly say: *this is ceremony — there's nothing user-visible to demo today, but here's what's now possible because of it*. Don't dress it up as a feature ship; that erodes trust.

For every other chapter, the artifact is real and runnable. Demo it at chapter close.

## The chapter-close ritual

**Open every chapter** by stating the artifact:

> "Today's concept is X. By the end of this chapter, you'll be able to run `./build/beans <command>` and see `<expected output>`."

Make the verb concrete. "Add a task." "Render the task list." "Survive a crash mid-write."

**Close every chapter** by demonstrating it:

```bash
$ ./build/beans add "feed the cat"
✓ added: 01HXV2... feed the cat

$ ./build/beans list
01HXV2... [ ] feed the cat
```

Run the command in front of the learner. Don't have them go run it on their own. The demo is the chapter's punctuation.

**Make the ladder visible** at chapter close:

> "Last chapter you had X. Now you have X plus Y. Next chapter, X+Y enables Z."

Concrete example for chapter 02:

> "Last chapter you had a CMake workspace that builds an empty library. Now you have a `beans` binary that runs and prints arguments. Next chapter, `beans` will fail loudly under ASan when given malformed input — and that failure is going to teach you what UB really means."

This is what makes the chapter sequence feel like real motion instead of theory accumulation.

## What if the learner gets ahead of the chapter?

Some chapters land fast — the learner sees the pattern, they're done in 30 minutes, they want to do the *next* thing right now. Don't let them — and also don't fight too hard.

Compromise: **stop the chapter at its boundary, do the teach-back, then ask if they want to continue into the next chapter as a second session in the same evening**. That preserves the cognitive-load discipline (one new concept per session) while letting the learner ride momentum.

What you do *not* do: silently roll two concepts into one chapter because the first felt light. Two concepts per chapter is two chapters' worth of teaching with one chapter's worth of teach-back, and the second concept doesn't land properly. The post-mortem reads "the learner can't remember what was in chapter 09" because chapter 09 had two things in it.

## What if the learner gets stuck?

The pedagogy depends on productive struggle. Sometimes you let them sit with a compiler error or a segfault for five minutes before stepping in. The point is: they're learning what *they* would do without you, and *that* is what they'll remember.

Step in when:
- They've tried the same approach twice and it's not working
- They're frustrated to the point of demoralisation (different from frustration-as-learning)
- They've named a hypothesis that's wrong in a way that will compound into the next chapter

Don't step in when:
- They're confused but actively forming a hypothesis
- They're reading the compiler error
- They're reaching for `man 3 strtol`

The compiler is a co-teacher (rule 6). Let it teach. You're there to disambiguate when its lesson is unclear, not to pre-empt it.

## What if the chapter is wrong?

Sometimes the chapter has a bug — a wrong expected output, a missing step, a stale command, an ASan diagnostic that prints differently on the learner's macOS version than what the chapter quotes. When this happens:

1. **Capture the discrepancy as a learn-by-LLM observation.** Add it to the chapter's companion `docs/teaching/notes/NN-*.md` file under "What surprised the learner."
2. **Fix the chapter file.** Update the expected output, the missing step, the stale command. Use the verbatim output from the learner's machine.
3. **Keep going.** A chapter bug isn't a session-killer; it's a chapter-improvement opportunity. The book improves.

This is the rule-16 discipline ("verify before publishing"). When verification reveals environment-specific behaviour, capture it as `docs/issues/NNNN-<slug>.md` and update the chapter. Future learners benefit.

## Failure mode to watch for

If the learner finishes three chapters in a row and can't articulate what each chapter taught them, they're chapter-skimming, not learning. Slow down. Ask the predict-questions out loud. Ask the teach-back questions out loud. The pedagogy depends on the learner doing the work; it's easier to fake doing the work in reproduce mode than tour mode (you have a binary to point at; you don't necessarily understand it).

The teach-back is the diagnostic. If the learner can demo the binary but can't explain what the new code does that the previous chapter's binary didn't, the concept didn't land. Re-read together.

## See also

- `.skills/teaching/SKILL.md` — rule 13 (artifact per chapter, reproduce-mode adapted) and rule 15 (chapter-as-curriculum)
- `.skills/teaching/references/operating-rules.md` — long-form rules
- The lazydap counterpart at `~/code/planetaryescape/lazydap/docs/teaching/build-philosophy.md` (tour-mode equivalent)
- `docs/teaching/sessions.md` — the session plan with each chapter's artifact named
