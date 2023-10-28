# Schedule scripting language

The Schedule scripting language is a high level language that was made to help reading and modifying the schedule
scripts used by various actors.

## Features of the schedule system

The Schedule system is a very simple scripting language, it is composed of a series of commands that can check the
state of the game and return a value depending on said state. This system can't declare variables, hold its own state
or modify the game's state.

A schedule script can check the state of the following:

- Current in-game day
- If a WeekEventReg flag is set or not
- Current time is in a specified time range
- Current time is before/after a specified time
- Some other miscellaneous checks (see the `ScheduleCheckMisc` enum).

All of those checks act as conditional branches into some other command. The schedule system also supports
unconditional branches.

The schedule script is run until a return command is executed. There are various return commands that allow different
things:

- Return none: The schedule finished without returning a value.
- Return empty: The schedule finished without changing the previous value.
- Return s: The script returns a value that's 1 byte long.
- Return l: The script returns a value that's 2 bytes long (Note this is bugged and will be truncated to 1 byte).
- Return time: Returns a time range and a 1 byte value.

Running an unknown command or branching to the middle of a command is undefined behaviour.

A low level schedule script can be compared to a multi byte assembly language, on which each command occupies 1 byte
plus a variable number of arguments.

### Short and long commands

Due to the commands themselves using a variable amount of bytes it is possible to do some small optimizations, like if
a branch distance (which is the amount of bytes the interpreter should skip if a check evaluates to true) can fit on a
signed byte then a short command is used, otherwise a long version of the command is used, one that uses two bytes to
store the branch distance, meaning the command itself will be one byte longer. There are no commands  hat use more than
2 bytes to store the branch distance.

## How a schedule script looks like

An extracted schedule script is just an array of raw data. A macroified version looks like this:

```c
static u8 D_80BD3DB0[] = {
    /* 0x00 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_YADOYA, 0x21 - 0x04),
    /* 0x04 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(3, 0x0B - 0x08),
    /* 0x08 */ SCHEDULE_CMD_RET_VAL_L(1),
    /* 0x0B */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(2, 0x20 - 0x0F),
    /* 0x0F */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 0, 23, 0, 0x1D - 0x15),
    /* 0x15 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_HAD_MIDNIGHT_MEETING, 0x1C - 0x19),
    /* 0x19 */ SCHEDULE_CMD_RET_VAL_L(1),
    /* 0x1C */ SCHEDULE_CMD_RET_NONE(),
    /* 0x1D */ SCHEDULE_CMD_RET_VAL_L(3),
    /* 0x20 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x21 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_OMOYA, 0x37 - 0x25),
    /* 0x25 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(3, 0x36 - 0x29),
    /* 0x29 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(18, 0, 6, 0, 0x30 - 0x2F),
    /* 0x2F */ SCHEDULE_CMD_RET_NONE(),
    /* 0x30 */ SCHEDULE_CMD_RET_TIME(18, 0, 6, 0, 2),
    /* 0x36 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x37 */ SCHEDULE_CMD_RET_NONE(),
};
```

Having this scripts as arrays like this have two major flaws:

- The control flow is not clear at a first glance (this is specially problematic for larger scripts).
- The branch distances are hardcoded into each command, making the script itself hard to modify.

As a solution, the high level Schedule script language uses a C-like syntax to better represent the control flow. The
above script can be written as the following:

```c
if_scene (SCENE_YADOYA) {
    if_day (3) {
        return_l (1)
    } else if_day (2) {
        if_time_range (21, 0, 23, 0) {
            return_l (3)
        } else if_week_event_reg (WEEKEVENTREG_HAD_MIDNIGHT_MEETING) {
            return_none
        } else {
            return_l (1)
        }
    } else {
        return_none
    }
} else if_scene (SCENE_OMOYA) {
    if_day (3) {
        if_time_range (18, 0, 6, 0) {
            return_time (18, 0, 6, 0, 2)
        } else {
            return_none
        }
    } else {
        return_none
    }
} else {
    return_none
}
```

## Syntax

The syntax is very simple, it consist on a sucession of commands. Some commands require arguments (by using
parenthesis) and some (conditional checks) can have bodies with subcommands and an optional `else` with its
correspnding body with subcommands.

Like in C, both whitespace and newlines are not part of the language and they get ignored during compilation. At the
same time, this language accepts both C and C++ styles of comments, known as block comments (`/**/`) and line comments
(`//`).

A command's body is delimited by braces (`{` and `}`). A body must follow either a
[conditional check](#conditional-checks) command or an `else`, meaning top-level bodies are not allowed. At the same
time a conditional check must be followed by a body. An `else` must be followed by either a body or another conditional
check command.

Even if this language's syntax is inspired by C, there are a few key differences:

- Commands are not separated by semicolons (`;`). Instead just a whitespace is used as separation.
- Instead of having a single `if` conditional of which its parameters should evaluate to non-zero, this language uses
  [conditional checks](#conditional-checks). These are commands that receive parameters and have a body with parameters
  that would be executed if the command itself evaluated to true. This commands may be followed by an `else`, which has
  its own body.
- There's no concept of functions, variables, loops, scopes, etc.

## Compiling

Compiling a high level schedule script should produce a series of macros that can be `#include`d by a C preprocessor,
like in the following example:

File: `build/src/overlays/actors/ovl_En_Ah/scheduleScript.schedule.inc`

```c
    /* 0x00 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_YADOYA, 0x21 - 0x04),
    /* 0x04 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(3, 0x0B - 0x08),
    /* 0x08 */ SCHEDULE_CMD_RET_VAL_L(1),
    /* 0x0B */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(2, 0x20 - 0x0F),
    /* 0x0F */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 0, 23, 0, 0x1D - 0x15),
    /* 0x15 */ SCHEDULE_CMD_CHECK_FLAG_S(WEEKEVENTREG_HAD_MIDNIGHT_MEETING, 0x1C - 0x19),
    /* 0x19 */ SCHEDULE_CMD_RET_VAL_L(1),
    /* 0x1C */ SCHEDULE_CMD_RET_NONE(),
    /* 0x1D */ SCHEDULE_CMD_RET_VAL_L(3),
    /* 0x20 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x21 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_OMOYA, 0x37 - 0x25),
    /* 0x25 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(3, 0x36 - 0x29),
    /* 0x29 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(18, 0, 6, 0, 0x30 - 0x2F),
    /* 0x2F */ SCHEDULE_CMD_RET_NONE(),
    /* 0x30 */ SCHEDULE_CMD_RET_TIME(18, 0, 6, 0, 2),
    /* 0x36 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x37 */ SCHEDULE_CMD_RET_NONE(),
```

On actor's C code:

```c
static u8 D_80BD3DB0[] = {
#include "build/src/overlays/actors/ovl_En_Ah/scheduleScript.schedule.inc"
};
```

## Commands

Commands are the fundamental (and almost only) building block of this language. A schedule script must always have at
least one command. It's undefined behaviour if script's control flow doesn't always lead to a return command.

To see how the command's arguments work, please see the [corresponding section](#commands-arguments).

Commands can be categorized in 4 major types: [Conditional checks](#conditional-checks),
[unconditional branches](#unconditional-branches), [return commands](#return-commands) and
[miscellaneous commands](#miscellaneous commands).

### Generics and non-generics

TODO

### Command's arguments

TODO

### Conditional checks

TODO

### Unconditional branches

TODO

### Return commands

TODO

### Miscellaneous commands

TODO

### Operators

TODO

### Labels

TODO
