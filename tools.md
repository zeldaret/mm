# Table of Contnets

- [Table of Contnets](#table-of-contnets)
  - [Introduction](#introduction)
  - [Regconvert](#regconvert)
  - [Gfxdis](#gfxdis)
  - [How to add new warnings](#how-to-add-new-warnings)
  - [`Diff.py`](#diffpy)
  - [Permuter](#permuter)
  - [`fixle.sh`](#fixlesh)
  - [`format.sh`](#formatsh)
  - [mips_to_c](#mips_to_c)
  - [`m2ctx.py`](#m2ctxpy)
  - [`ichaindis.py`](#ichaindispy)
  - [`colliderinit.py`](#colliderinitpy)
  - [`actor_symbols.py`](#actor_symbolspy)

## Introduction

There are a variety of tools that are used to assist in the decompilation process. This guide is an introduction to some of the tools that are used. Some of these tools are located in the `mm/tools` directory, others will be in varying locations. (List may not be complete...)

## Regconvert

Converts a gGameInfo->data index to a REG macro.

## Gfxdis

Gfxdis is part of a library that can be found here: <https://github.com/glankk/n64>. Follow the instructions in the README for how to install. We use gfxdis when decompiling the draw functions for actors.

## How to add new warnings

## `Diff.py`

This tool aids in comparing the original assembly from a ROM with the assembly generated from code written.

You can run the tool by running:

```zsh
./diff.py -mwo3 <Actor_Name>
```

The colours mean the following:

- White/gray is matching lines
- Red is lines missing
- Green is extra lines
- Blue denotes significant differences in instructions, be they just numerical ones, or wholeinstructions
- Yellow/Gold denotes that instructions are correct but register usage is wrong
- Other colors are used to distinguish incorrectly used registers or stack variables, to make it easy to follow where they are used.
- The colored arrows denote branching. An arrow of one color on the right leads to the arrow of the same color on the left.

For a complete list of functionality run `./diff.py -h`

## Permuter

When all hope is lost, fear not the permuter is here! This is a brute force attempt at creating matching the target binary.

To set up the permuter, clone the repository <https://github.com/simonlindholm/decomp-permuter> in a directory of your choice. Follow the usage section of the README and ensure you have all the prerequisites installed.

To use the permuter you will need to mport the c file and the asm

```zsh
./import.py <path/to/file.c> <path/to/file.s>
```

The command above will create a file in the `nonmatching` directory, so next step will be to run the permuter:

```zsh
./permuter/nonmatching/<directory_of_interest> -jX
```

**NOTE:** the `-j` will by default use the amount of threads available, if you want to assign it a specific amount, make sure you specify e.g `-j2`

For more info see: <https://github.com/simonlindholm/decomp-permuter>

## `fixle.sh`

## `format.sh`

With a project that has several contributors, it is useful to have a common formatting guide. For this project we use `clang-format-11`. Before submitting any PR, ensure that you have run `./format.sh`.

## mips_to_c

Mips to C (m2c) is a tool that takes MIPS assembly and will attempt to convert it to C.

There are different ways you can run m2c:

- Clone the repo and run it loclly on your own machine. Follow set up instructions at <https://github.com/matt-kempster/mips_to_c>
- An online version is available at <https://simonsoftware.se/other/mips_to_c.py>.

M2c's accuracy could be improved when some context to what the existing C source code is like. See more on how to generate this in [m2ctx](#m2ctx.py)

## `m2ctx.py`

This tool creates a context file `ctx.c` in the root folder of the project. Common usage is to run (assuming you are in the root dir) `./tools/m2ctx.py <path_to_actor_file>.c`.

For more info run `m2ctx.py -h` for a complete list of arguments

## `ichaindis.py`

Used for decompiling the InitChain.

## `colliderinit.py`

Used for decompliling the Collider struct of an actor. To use colliderinit, you will need to know the address (VRAM or VROM) of the struct, and the type of collider. There are different types of colliders: `ColliderJntSph, ColliderTrisInit, ColliderQuadInit, ColliderSphereInit`.

For more info run `colliderinit.py -h`

## `actor_symbols.py`

Takes a VRAM or VROM address to get overlay file and offset for an Actor.
