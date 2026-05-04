---
chapter: "0c"
title: Why I'm learning C
status: complete
estimated_time_minutes: 6
---

# Chapter 00c — Why I'm learning C

> Optional. ~6 minutes. Skip to [Chapter 01](01-cmake-workspace.md) if you just want to learn C by building a thing. The technical context you need is in [Chapter 00b](00b-what-is-c-beans.md).

This is a longer answer than most book introductions need. If you read it, the design choices in c-beans and the way this book teaches will make a different kind of sense. If you skip it, you'll still learn C just fine.

## The gym for the brain

I have a theory that everyone needs a hobby that is *deliberately difficult*. Not a trade, not something you'll be paid for, not something with a deadline. Something that pushes your brain past what it can comfortably do, the way the gym pushes your body past what it can comfortably lift. Reading classical literature. Learning math. Learning a low-level programming language. Speaking a new natural language. Chess against humans. The category is wide.

Most of us want to *have done* the difficult thing. We want to be the person who reads in three languages, plays competent chess, can derive things from first principles, has shipped a kernel module. We just don't want to pay the tax. Modern life makes the avoidance easy. Work, home, chores, parenting, sleep — none of it stretches the mind in the particular way that learning a hard new thing stretches it. You can have a successful, productive career and still feel that your brain has plateaued.

Most people overestimate what they can do in a year and underestimate what they can do in ten. That gap is where compounding lives. The only way to get the ten-year compound is to put in the daily ten minutes, the daily hour, the daily uncomfortable reach, when there's no deadline forcing you to.

I've felt this before. When I first learned to code I'd struggle with a concept, push hard, read a thing, get it; come back the next day, find I'd lost most of it; push again, lose it again. For weeks, sometimes months, with the brain-hurts-because-it's-actually-stretching feeling. Then one day something clicked, the fragments fused into something solid, and suddenly I could read code I couldn't have read a month before. Once you cross that threshold, the gains compound exponentially. But you have to walk through the not-getting-it part to get there.

## What AI did to that practice

I lost it. Honestly.

For years I had it. I had a SaaS product I was building, I had a job, but I was *also* learning French — not because I was moving to France, just because I was curious. I learned ML for a while. The point of all of those was the *learning*, not a deliverable.

Then AI showed up, and somewhere between "this is a useful tool" and "this is how I work now" I stopped doing the difficult thing for its own sake. Why would I? I could prompt for a solution faster than I could reason my way to one. Why would I read a book on structured logging when I could ask an LLM for a comprehensive guide and paste it into the next prompt? I caught myself doing exactly that recently — generated a guide, didn't read it, fed it to a coding agent, the work got done. Comprehensive guide on my disk. I don't know what was in it.

That's not a usage of AI I want to keep. It works. It even produces decent output. But it skips the part where I learn, and over time the thing I'm bringing to the next prompt is less and less. That's a slow plateau and I can feel it.

There are two ways to use AI when you're learning. The first is the way I just described: AI as a solution provider. Fast, productive, you produce more output, you understand less of it. The second is AI as a *thinking companion*. You bring a half-formed thought; the AI plays it back and stress-tests it; you push back; you both refine; you walk away with a better thought *that you actually had*. The AI didn't give you the answer; it pulled it out of you. This is closer to a Socratic dialogue than to a Q&A. It's slower than the first mode, by a lot. But what you keep is yours.

This book is built around the second mode. The predict-before-run prompts, the surface-your-model prompts, the let-the-compiler-and-ASan-be-the-teacher discipline — those aren't pedagogy decoration. They're the operational difference between "the agent gives you C" and "you understand C, with the agent's help."

## Why C, of all things

I want to fill in CS foundations. I came to programming through web development. Civil engineering degree, no computer science degree. Eight years of shipping production software in TypeScript, Python, JavaScript, infra-as-code. Plenty of tacit knowledge about how to make systems work. Almost no formal mental model of what's *underneath* — how memory actually works, what the kernel boundary is, why my React app is fast or slow, why a SQL query plans the way it does, what undefined behaviour really means as a category.

I also want to learn Rust, properly. Not "I can ship Rust code at work" — I do that already — but "I understand why every feature exists." I've used lifetimes; I couldn't articulate them. I've used `Result<T, E>`; I couldn't tell you why exception-throwing is the wrong design for systems software. That's a particular kind of plateau, and it bothers me.

The route I picked: go down a level. Learn C. Feel the problems first-hand. Then come back to Rust and have every feature land as a fix for a pain I'd actually felt. Use-after-free. The `errno` dance. NULL dereferences. Switch fall-through. Manual memory. Header file dance. Once those are *experiences* and not Wikipedia entries, Rust's ergonomics stop being trivia and start being a gift.

I'm not learning C to become a C programmer. I'm using C as a forcing function to internalise what's underneath higher-level languages. Once I have that, Rust's rules will read as constraints with reasons rather than ceremony. (Then maybe I'll go further down — assembly, computer architecture, the kernel. Or maybe I'll come back up. The point is the practice, not the destination.)

## Why a task manager

I learn best with a project. Just reading a book cover-to-cover doesn't stick. I needed a project that would naturally hit the things I want to learn — and that I'd actually use.

A task manager is a perfect surface area for C learning:

- **Strings** show up everywhere — task titles, ids, file paths, error messages. C's `char *` ambiguity gets felt within the first hour.
- **Memory ownership** shows up the moment a task struct holds a string and gets copied around. Shallow vs deep copies. Who frees what.
- **File I/O** shows up the moment you want to persist anything. JSONL because it's the smallest format that's also a parser exercise. SQLite later because the database stuff is its own teaching.
- **Parsing** shows up because JSONL lines need to come back as typed structs. Hand-roll the parser; that's six chapters of the densest C teaching the project has.
- **TUI** shows up because terminal task managers should be navigable from the keyboard. ncurses is the standard, idiomatic, on every Mac and Linux box.
- **Network programming** shows up at the end when the daemon extraction lands. Sockets, framing, multi-client servers — the same patterns lazydap walks in Rust.

And it's something I'll actually use. I've cycled through five task managers in the last decade. None of them quite fit. The fact that this one will live on my own machine, accept my keyboard shortcuts, store my data in a format I can grep — that matters more than I'd have predicted. You build different software when you're the first user.

## Why "build it instead of using cJSON / sqlite-cli / one of the existing terminal task managers"

I asked myself this. Forking an existing terminal task manager would have been faster.

Honest answer: I'm building this primarily as a learning project. Using `cJSON` would have skipped Phase B entirely — the densest C teaching the book has. Using an existing TUI task manager would have meant reading code, not writing it. Using SQLite from day one would have skipped the JSONL chapters where the parser teaching pays off.

The book is structured to maximise the *teaching surface* of every concept, not to ship the binary fast. Every line of `cJSON` you'd otherwise depend on, I want you to write yourself, slowly, with predict-pauses, until the parser code feels obvious. Same for the Store interface. Same for the daemon. The dependency budget is small on purpose.

The companion book to this one is [lazydap](https://github.com/planetaryescape/lazydap). It's the same person (me) doing the same thing one level up: building a Rust DAP debugger, slowly, with the same pedagogy. The C journey here gives me the motivation; the Rust journey gives me the tooling. Together, they make every "Rust solves *this* pain" moment a real conversation in my head, not a slogan from a tutorial.

## The principle behind the book's structure

If the *practice* is doing one difficult thing, daily, with no deadline — the book has to support that.

Each chapter is one teaching session. Each session is one new concept. Each concept lands with a runnable artifact at the end. The chapters are cumulative — chapter 04 builds on what chapter 03 left you with — so progress feels like motion, not theory piling up.

The predict-pauses and the teach-back questions exist because the *thinking-companion mode* requires them. If you read passively, the book degrades into a flat tutorial. If you stop at every 🔮 Predict and actually predict — even when you're alone with the book and no one's checking — you get the brain-hurts-because-it's-stretching feeling that the difficult-thing practice depends on. That feeling is the entire point. You can't have it on autopilot.

If you have an LLM agent driving the book live, the agent's job is to be the *thinking companion*, not the *solution provider* — the chapter is the curriculum, the agent's job is to add live responsiveness inside that script (calibrate to your actual prediction, run the actual code, read the actual compiler/ASan output). It does not freestyle, does not skip ahead, does not invent new concepts. It is, deliberately, slower than asking the same agent to "just write me a C task manager." That's the trade.

## What you should take from this chapter

Two things, both optional:

**Build the thing you wished existed.** Better fuel than "ship a portfolio piece." Tends to produce better code, because you're the first user.

**Pick a difficult thing and do it daily.** Doesn't have to be C. Doesn't have to be programming at all. The point is the practice, the gym for the brain. A year of it doesn't get you much. Ten years gets you a different version of yourself. The trick is showing up when there's no deadline forcing you to.

That's why this book exists, and why it teaches the way it does.

Next up: [Chapter 01 — CMake workspace](01-cmake-workspace.md). The book's setup is done; we start building.
