# Contributing to the Majora's Mask Decompilation Project

Thanks for helping us reverse engineer *The Legend of Zelda: Majora's Mask* for the N64!
All contributions are welcome. This is a group effort, and even small contributions can make a difference. Some tasks also don't require much knowledge to get started.

This document is meant to be a set of tips and guidelines for contributing to the project.
For general information about the project, see [our readme](https://github.com/zeldaret/mm/blob/main/README.md).

Most discussions happen on our [Discord Server](https://discord.zelda64.dev) where you are welcome to ask if you need help getting started, or if you have any questions regarding this project and other decompilation projects.

## Useful Links

- [Installation guide](https://github.com/zeldaret/mm/blob/main/README.md#installation) - Instructions for getting this repository set up and built on your machine.
- [Style Guide](STYLE.md) - Description of the project style that we ask contributors to adhere to.
- [Code Review Guidelines](REVIEWING.md) - These are the guidelines that reviewers will be using when reviewing your code. Good to be familiar with these before submitting your code.

- [Zelda 64 Reverse Engineering Website](https://zelda64.dev/games/mm) - Our homepage, with FAQ and progress graph :chart_with_upwards_trend:.
- [MM decomp tutorial](tutorial/contents.md) Detailed tutorial for learning in general how decomp works and how to decompile a small, simple file.
- [Introduction to OOT decomp](https://github.com/zeldaret/oot/blob/main/docs/tutorial/contents.md) - The tutorial the MM one was based on. For OOT, but largely applicable to MM as well. Covers slightly different topics, including how to get your data OK with `vbindiff`.
- The `#resources` channel on the Discord contains many more links on specific details of decompiling IDO MIPS code.

## Getting Started

### What should I know to take part?

Basic knowledge of C, particularly arrays and pointers, is extremely useful. Knowledge of MIPS is not required initially, you can pick it up as you work through some decompilation.

You should be familiar with using git and GitHub. There are a number of tutorials available online, [such as this one](https://github.com/firstcontributions/first-contributions) which can help you get started.

The most useful knowledge to have is a general understanding of how the game works. An afternoon of constructive mucking about in the [MM Practice Rom](https://kz.zeldacodes.org/) (aka KZ) or the [OoT Practice Rom](http://practicerom.com/) (aka GZ) will be very beneficial if you have not looked at either of the N64 Zelda's internals before.

The [OoT Decompilation Project](https://github.com/zeldaret/oot) is farther along than this project, so it can also be a great resource.

This project only uses *publicly available code*.

**N.B.** Anyone who wishes to contribute to the OOT or MM projects **must not have accessed leaked source code at any point in time** for Nintendo 64 SDK, iQue player SDK, libultra, Ocarina of Time, Majora's Mask, Animal Crossing/Animal Forest, or any other game that shares the same game engine or significant portions of code to a Zelda 64 game or any other console similar to the Nintendo 64.

### Environment Setup

Get started by following the [installation guide in the readme](https://github.com/zeldaret/mm/blob/main/README.md#installation).
You should be able to build a matching ROM before you start making any changes.

### First Contribution

Usually, the best place to get started is to decompile an actor overlay.
An *actor* is any thing in the game that moves or performs actions or interactions. This includes things like Link, enemies, NPCs, doors, pots, etc. Actors are good for a first file because they are generally small, self-contained systems.

We recommend that you [join the Discord](https://discord.zelda64.dev/) to say hello and get suggestions on where to start on the `#mm-decomp` channel.

We track who is working on what on some Google Sheets available in the Discord. Once you've decided on or been recommended a good first file, mark it as Reserved.

The workflow is:

- Reserve a file,
- decompile it,
- submit a PR,
- repeat while addressing review comments.

The expectation is that one reservation goes to one file which ends up in a one file PR, although naturally some files are more sensibly worked on as a group, for example two actors that work together. This also does not apply to large asset files like `gameplay_keep`: you can just reserve the parts that are used in your files.

If possible, we expect reserved files to be completed. If you find you cannot complete a file, because it is intractable for one reason or another, or real-life circumstances get in the way, please talk to one of the leads in Discord; we may find someone else interested in helping you finish, or who is happy to take over the file from you completely. If you unreserve a file on which you have useful progress, please leave a link to your branch in the Notes column on the Google Sheet that the next person who works on the file can use.

## Style Guide & Conventions

See the [Style Guide](STYLE.md).

## `NON_MATCHING` and `NON_EQUIVALENT`

If you make significant progress on decompiling a function, but can't get it to match perfectly, you can use a `NON_MATCHING` block to commit your code but have it excluded from the build, like so:

```c
#ifdef NON_MATCHING
void CollisionCheck_SpawnWaterDroplets(PlayState* play, Vec3f* v) {
    // ... 
}
#else
void CollisionCheck_SpawnWaterDroplets(PlayState* play, Vec3f* v);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_collision_check/CollisionCheck_SpawnWaterDroplets.s")
#endif
```

Before PRing with a `NON_MATCHING`, you can try

- using the [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) to find a closer match,
- Asking in `#mm-decomp-help` in Discord; the easiest way to allow other people to play around with the function you are stuck on is to make a scratch on [decomp.me](http://decomp.me).

`NON_EQUIVALENT` can be used with the same syntax as `NON_MATCHING`, but it is used to mark sections of code which do not match *and* do not have the same behavior as the original code.

## Matching and Documenting

Usually, the first step of decompiling a section of code is to get it *matching*: to produce a C version of the code that can be compiled into an identical ROM.

However, the goal of this project is to produce a codebase that can be understood and modified.
Therefore once C code produces matching assembly, the next step is to *document* the code.

Documenting is more than just adding comments. Documenting also includes:

- Renaming functions, variables, and struct members
- Using (or adding) constants, enums, and macros when possible
- Explaining sections of code that are not straightforward

Overlays are not required to be documented at this time, but files from `code/` and `boot/` should be documented. When documentation on a file has been started it should be as complete as reasonable.

See the [Style Guide](STYLE.md) for more details on documentation style.

## Pull Requests (PRs)

### Checklist

Before opening a PR, walk through the following steps to ensure that your code conforms to the style guide and conventions.

- `make` successfully builds a matching ROM.
- `./format.py` was run to apply standard formatting.
- No new compiler warnings were introduced during the build process.
    - Can be verified locally by running `tools/warnings_count/check_new_warnings.sh`
- New variables & functions should follow standard naming conventions.
- Comments and variables have correct spelling.

Feel free to reach out on the Discord if you have any questions about these steps or encounter any issues.

### Pull Request Process

After opening a PR, the Jenkins agent will test formatting, the contents of the spec, build the rom and check for warnings.
If there is an error, double-check that you can successfully

```bash
make disasm
./extract_assets.py -f
make clean
make
```

locally. If the build is `OK`, the next thing to check is that all added/modified files were `git add`-ed to your commit. The final check before posting on Discord for help is that there are no new warnings added to the code causing Jenkins to fail. You can check this by running: `tools/warnings_count/check_new_warnings.sh`.

Each PR needs a review from two reviewers, at least one a project lead, and final approval from Kenix.

If the PR author agrees with a reviewer's suggestion, they make the change and resolve the conversation. If they disagree, have a better idea, or want to comment on something, they should at least leave a comment, and discuss it in Discord if it's not going to be resolved quickly, since long conversations on GitHub are hard to read.

Once all comments is addressed and all reviewers have approved, the PR will be merged.

Project leads are responsible for ensuring that these conventions are followed.

### Some git notes

- You should work on a branch on your fork separate from your copy of main: it is always useful to have a clean main branch around if you need to fix something.
- When a PR is merged into main, it may conflict with your work. While your branch is private (in particular, not used for a PR), you can rebase, but when your branch is public/used for a PR always merge main instead of rebasing: it makes it much easier for people to understand what you changed since the last review.
- We squash commits when merging, so your commit history does not have to be completely spotless.

Throughout the PR process, you (the author) should update the rows on the appropriate Google Sheets with the appropriate information as the decompilation process progresses.
