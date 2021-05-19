Contributing to the Majora's Mask Decompilation Project
=======================================================

Thanks for helping us reverse engineer *The Legend of Zelda: Majora's Mask* for the N64! 
All contributions are welcome. This is a group effort, and even small contributions can make a difference. Some tasks also don't require much knowledge to get started.

This document is meant to be a set of tips and guidelines for contributing to the project.
For general information about the project, see [our readme](https://github.com/zeldaret/mm/blob/master/README.md) or [our wiki](https://github.com/zeldaret/mm/wiki).

Most discussions happen on our [Discord Server](https://discord.zelda64.dev), where you are welcome to ask if you need help getting started, or if you have any questions regarding this project and other decompilation projects.


Useful Links
------------

- [Zelda 64 Reverse Engineering Website](https://zelda64.dev/) - Our homepage, with links to other resources.
- [Installation guide](https://github.com/zeldaret/mm/wiki/Installation) - Instructions for getting this repository set up and built on your machine.
- [Introduction to OOT decomp](https://github.com/zeldaret/oot/blob/master/docs/tutorial/contents.md) - A very detailed tutorial on how to get started with decomp. For OOT, but largely applicable to MM as well.

- [Discord](https://discord.zelda64.dev/) - Primary discussion platform.
- [Trello board](https://trello.com/b/ruxw9n6m/majoras-mask-decompilation) - We use this to track decompilation progress, not GitHub Issues.

Getting Started
---------------

### What should I know to take part?

Basic knowledge of C, particularly arrays and pointers, is extremely useful. Knowledge of MIPS is not required initially, you can pick it up as you work through some decompilation.

You should be familiar with using git and GitHub. There are a number of tutorials available online, [such as this one](https://github.com/firstcontributions/first-contributions), which can help you get started.

The most useful knowledge to have is a general understanding of how the game works. An afternoon of constructive mucking about in the [OOT Practice Rom](http://practicerom.com/) (aka GZ) or the [MM Practice Rom](https://kz.zeldacodes.org/) (aka KZ) will be very beneficial if you have not looked at either of the N64 Zelda's internals before.

This project only uses *publicly available code*. In particular, do not use any Nintendo source code leaks.

### Environment Setup

Get started by following our [installation guide](https://github.com/zeldaret/mm/wiki/Installation).
When successful, you should be able to build a matching ROM before you start making any changes.

### First Contribution

Usually, the best place to get started is to decompile an actor overlay. 
An *actor* is any thing in the game that moves or performs actions or interactions: Link is an actor, enemies are actors, NPCs are actors, etc.

You can [join the Discord](https://discord.zelda64.dev/) to say hello and get suggestions on where to start on the `#mm-decomp` channel.
We track who is working on what on the [Trello board](https://trello.com/b/ruxw9n6m/majoras-mask-decompilation).

Style Guide & Conventions
-------------------------

Most of the C formatting style is enforced by the `format.sh` script, which is based on `clang-format`.
Running `./format.sh` will apply our standard style to all `.c` files in the repository.

There are some conventions that cannot be automatically enforced.

(TODO)
- Naming scheme
- `ActorFunc` naming specifics
- Renaming symbols referenced by asm (?)

### `NON_MATCHING`

If you make significant progress on decompiling a function, but can't get it to match perfectly, you can use a `NON_MATCHING` block to commit your code but have it excluded from the build, like so:

```c
#ifdef NON_MATCHING
void CollisionCheck_SpawnWaterDroplets(GlobalContext* ctxt, Vec3f* v) {
    // ... 
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_collision_check/CollisionCheck_SpawnWaterDroplets.asm")
#endif
```

Pull Requests (PRs)
-------------------

### Checklist

Before opening a PR, walk through the following steps to ensure that your code confroms to the style guide & conventions.

- Run `./format.sh` to reformat your updated files.
- Ensure `make` successfully builds a matching ROM.
- Your changes should not introduce new warnings (TODO: See PR #150 for check)
- New variables & functions should follow the naming conventions above.
- Check spelling in comments & renamed symbols

### Pull Request Process

TODO: What should go in the pull request body?

After opening a PR, the Jenkins server will verify your changes.
If there is an error, double-check that you can successfully `make clean && make` locally and that all added/modified files were `git add`-ed to your commit.

Each PR needs a review from one reviewer, plus the project lead.

The PR author marks the comments as resolved, since they are the ones with permissions.
Once all comments are addressed, it is courteous to ping the reviewer on either Discord or GitHub via re-requesting a review.

After all the comments are addressed and at least one contributor has approved the review, the project lead can then merge the code.
The project lead is also responsible for ensuring that all of these procedures are followed.

Throughout the process, you should update the [Trello board](https://trello.com/b/ruxw9n6m/majoras-mask-decompilation) with the status of your PR.

Tools
-----

(NB: This should probably go in a different place)

- `mips_to_c` + `m2ctx.py`
- Decomp Permuter
- `diff.sh`, the `expected/` directory
- `rename_sym.sh`
- `overlayhelpers/actor_symbols.py` 
- `overlayhelpers/colliderinit.py`
- `overlayhelpers/ichaindis.py`

