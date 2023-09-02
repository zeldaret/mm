# Majora's Mask decompilation style guide

In general, completed documented files are a good place to look to understand project style in general.

## Types

Use the types from `ultratypes.h`, not the standard C types: i.e. `u8`,`s8`,`s16`,`u16`,`s32`,`u32`,`f32` rather than `char`, `short`, `int`, `float` and their `signed`/`unsigned` varieties.

We always write our enums and structs as `typedef`s. (Usually one can't use an enum typedef as a function argument since enum typedefs are implicitly `s32`.)

## Naming

Names are "big-endian": the most significant/largest part of the system goes first, e.g. `DM_RAVINE_STATE_ACTIVE` rather than `DM_RAVINE_ACTIVE_STATE`.

| Type                 | Style                   | Example                 |
| -------------------- | ----------------------- | ----------------------- |
| Local variables      | camelCase               | `yawToPlayer`           |
| Global variables     | gCamelCase              | `gSaveContext`          |
| Static variables[^1] | sCamelCase              | `sZeroVec`              |
| Struct members       | camelCase               | `actionFunc`            |
| Struct names         | PascalCase              | `EnFirefly`             |
| Enum types           | PascalCase              | `EnFireflyMainType`     |
| Enum values          | SCREAMING_SNAKE_CASE    | `AT_ON`                 |
| Defines/macros       | SCREAMING_SNAKE_CASE    | `SCREEN_WIDTH`,`ABS(x)` |
| Functions            | SystemName_FunctionName | `Actor_SpawnAsChild`    |
| Files                | snake_case              | `z_en_firefly.c`        |

[^1]: including in-function static

Action functions are usually named with a simple present-tense verb or verb phrase: `{...}_Talk`, `{...}_Wait`, `{...}_FallToGround`, etc. Setup functions are `Setup{name of action}`.

Ideally names should be both short and clear, although it's better to be clear than short.

## Formatting

A lot of formatting is done by clang-format, such as

- indent is 4 spaces, tabs are not used
- case labels indented
- 120 column limit
- brackets go on the same line (`if (1) {`)
- pointer goes on type (`s32* var;` not `s32 *var;`)

There are various other conventions that it does not catch, though:

- Blank line between declarations and code:

  ```c
  s32 var;
  
  func();
  ```

- combine declarations and definitions if possible:

  ```c
  s32 var = 0;
  
  func();
  ```

  instead of

  ```c
  s32 var;
  
  var = 0;
  func();
  ```

- blank lines between switch cases if they're long (use your judgement).

## Numbers

### dec(imal)

- timers
- colours and alpha
- Usually array accesses and sizes

### hex(adecimal)

- angles (for now; the code itself is very inconsistent with round hex, round dec, and degrees)
- Addresses
- Bitmasks (i.e. `& 0x80` etc.)
- Struct offset comments

Numbers below `10`/`0xA` do not need the `0x` if by themselves in code.

### Booleans

If a function returns only `0` or `1`, and is used as a boolean (i.e. in conditionals), replace the returns by `false` and `true`. (We do not use `bool`, partly because is a C99 thing, and partly because the original has used almost every integer type as a boolean return at some point!)

### Floats

Floats usually need an `f` on the end to match, or IDO will use doubles. Our floats are always of the form `1.0f`, even when the decimal part is zero.

## Conditionals/Loops

- Spacing out conditional or loop blocks from surrounding code often makes them easier to read.
- Avoid assigning or mutating variables in conditionals if possible (including `++`/`--`), avoid side effects in the loop increment slot (i.e. incrementing/assigning to loop variables is fine, something like `*a = b++` is not).
- We *always* use `{}` on conditional/loop blocks, even if they're one line (clang-tidy will enforce this).
- When conditions are `&&`d or `||`d together, use brackets around each that includes an arithmetic comparison or bitwise operator (i.e. not `!var` or `func()`, but ones with `==` or `&` etc.)
- Flag checks or functions that return booleans do not need the `== 0`/`!= 0`.
- Prefer `if-else` over `if { return; }`, i.e.

  ```c
  if (cond) {
      foo();
  } else {
      bar();
  }
  ```

  over

  ```c
  if (cond) {
      foo();
      return;
  }
  bar();
  ```

**Exception**: After `Actor_Kill` or sometimes setting the action function, if it makes sense to do so (this expresses the finality a bit better).

## Macros and enums

Become familiar with the various defines and enums we have available. There are too many to list all of them here, but the following are common:

- Those in `macros.h`
  - `ABS`, `ABS_ALT`,
  - `CLAMP` and friends,
  - `BINANG_*`, which are used for angles, especially when there's a lot of `s16` casts around
- `MTXMODE` for many of the `sys_matrix` functions
- CollisionCheck flags: `AT_ON` and so on. Pick the appropriate one for the collider type.
- Actor flags, `ACTOR_FLAG_N`.

Damage flag enums are not being used at present: we want to wait until we have a better idea what the common groupings should be.

Pre-C99, commas at the end of the last item in an enum will cause a compiler warning, so leave them off.

All compound flag lists (e.g. `ACTOR_FLAG_UNFRIENDLY | ACTOR_FLAG_FRIENDLY`) should be listed in *ascending* order

## Arrays

- It's better to not hardcode array sizes (easier to mod)
- Use `sizeof` or `ARRAY_COUNT`/`ARRAY_COUNTU` where it makes sense, e.g. in loops that are using an array.
- clang-format sometimes does weird things to array formatting. Experiment with and without a comma after the last element and see which looks better.

## Play2

In some particular instances, IDO requires the function argument `play` to be cast to a second variable of the same type to match. In these particular instances, the function argument should be renamed to `play2` and than this `play2` just assigned to a stack variable called `play`. This cast should occur before the actor `THIS` cast is made. For example in `z_en_firefly.c`
```c
void EnFirefly_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnFirefly* this = THIS;
```

In other places the cast is actually not explictly needed, but a stack `pad` variable is still needed. For this there should just be a stack variable called `pad` of type `s32` before the actor `THIS` cast. For example in `z_bg_goron_oyu`

```c
void BgGoronOyu_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    BgGoronOyu* this = THIS;
    CollisionHeader* colHeader = NULL;
```

In general, pads should be `s32`, or `s16`/`s8` if required.

## Documentation and Comments

Documentation includes:

- Naming functions
- Naming struct variables
- Naming data
- Naming local variables
- Describing the general purpose of the file
- Describing any unusual, interesting or strange features of how the file or parts of its content work
- Labelling and explaining bugs
- Making enums or defines for significant numbers for the file, like actor params values.
- Naming the contents of the asset file(s) the file may use (for an actor, the object(s) it uses)

If you are not sure what something does, it is better to leave it unnamed than name it wrongly. It is fine to make a note of something you are not sure about when PRing, it means the reviewers will pay special attention to it.

We use comments for:

- Top of file: a short description of the system. For actors there is already a brief description of our current understanding, but feel free to add to it.
- For function descriptions, we use multiline comments,

  ```c
  /**
   * Describe what the function does
   */
  ```

  These are *optional*: if you think the code is clear enough, you do not need to put a comment. You can use Doxygen formatting if you think it adds something, but it is also not required.
- If something in a function is strange, or unintuitive, do leave a comment explaining what's going on. We use `//` for this.
- We also use `//` for temporary comments above a function. Feel free to use `TODO:` in these if appropriate.
- A bug should be commented with an `//! @bug Bug description` above the code that causes the bug.

## What goes where

This section mostly applies to actors.

### Functions

All functions should go in the main C file in the same order as the assembly (the latter is required to match anyway). (We may make exceptions for particularly large files with a particular organisational structure, but we ask that you check on Discord first before doing this)

### Data

- If in doubt, leave all the data at the top of the file. Reviewers will decide for you.
- Data must go in the same order as in the assembly files, but is only constrained by other data, not functions or rodata.
- Some data has to be inline static to match. Generally it's better to not use `static` on data outside funtions until the file is matching, since `static` data is left out of the mapfile and this makes debugging harder.
- *This is even more true of bss, where we have trouble with IDO unpredictably reordering it in certain files.*
- For small arrays or simple data that is used in only one function, we usually inline it, if it fits in the ordering.
- Generally data that is only used by the draw functions is put down near them: this is one of the few consistencies in ordering of actors' functions.

### Enums and defines

- Actors that bitpack params should have macros made for each access or write that is made. `z_en_dg.h` has an undocumented example,

  ```c
  #define ENDG_GET_FC00(thisx) (((thisx)->params & 0xFC00) >> 0xA)
  #define ENDG_GET_3E0(thisx) (((thisx)->params & 0x3E0) >> 5)
  ```

  while `z_en_firefly.h` has a documented one,

  ```c
  #define KEESE_INVISIBLE (1 << 0xF)
  #define KEESE_GET_MAIN_TYPE(thisx) ((thisx)->params & 0x7FFF)
  ```

- In a similar manner, actors that use `home.rot.(x|y|z)` like params should also macros made for accesses and writes. (See, e.g. `z_obj_bean.h`.)
- Stuff that only the actor itself will use goes in the C file unless needed in the header.
- Anything actor-specific that might be used by another file goes in the header, in particular params access macros.
- Anything that is expected to have widespread use should go in `macros.h` or an appropriate header in `include`.

### Objects

Are covered in the [ZAPD extraction xml spec](../tools/ZAPD/docs/zapd_extraction_xml_reference.md). Symbol names are `gPrefixDescriptionSuffix` for symbols accessed from the header (they will be global). Texture OutNames are in snake_case since they are filenames.

## Above all else

*All of the above is subservient to matching.* Sometimes IDO cares about newlines, for example.

If you are not sure about any of the above, please ask in Discord.
