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
signed byte then a **short** (noted with the `_S` suffix) command is used, otherwise a **long** version (noted with the
`_L` suffix) of the command is used instead.

A long command uses two bytes to store the branch distance, meaning the command itself will be one byte longer.

There are no commands that use more than 2 bytes to store the branch distance.

The short and long distinction also exists for the returned value, in case the user wants to return a value that
wouldn't fit on a single unsigned byte and requires an unsgined short (two bytes) instead. Please note that the vanilla
built-in system interpreter has a bug on which the upper byte of a long returned value will be discarded, so please
ensure your returned values always fit on the 0-255 range.

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
[miscellaneous commands](#miscellaneous-commands).

### Generics and non-generics

Schedule scripts use both [short and long commands](#short-and-long-commands) for most of the
[conditional checks](#conditional-checks) and [unconditional branches](#unconditional-branches) commands, making it
optimal space-wise, but terrible to worry about when actually writing a schedule script from the user's point of view.

Due to this, this high level language allows for generic versions of those commands (a.k.a. suffix-less versions) that
allow not having to worry about how many commands the body of a check has (and the byte length of them).

The rest of this section will mostly refer to the generic versions of the commands. The non-generic versions of each
command are available to be used too, but their use is not recommended.

### Command's arguments

Some commands require arguments. Arguments are used by checking commands to check something specific of the stae of the
game (what's the current day? what's the current scene? etc) and take a decision based on it (branch to another
command).

Arguments are enclosed in parenthesis (`(` and `)`) and passed verbatim to the generated output, allowing a compiler
for this language to not need to recognize any identifier used in arguments, allowing to use any custom identifier
(specially useful for schedule result enums). Take in mind this behaviour may change in a future version of the
language.

### Conditional checks

Conditional checks commands consist on commands that take a decision based on the state of the game, allowing it to
decide which set of subcommands to execute.

All conditional checks require an argument and a body of subcommands. A conditional check can be optionally be followed
by an `else`.

If the condition of any of these commands is not satisfied and said command have an `else`, then said the control flow
jumps to the body of that `else`. If there's no `else` and the condition isn't satisfied then the control flow just
fallthroughs into the next command.

#### `if_week_event_reg`

Checks if the passed WeekEventReg flag is set, and execute the body of the command if it is set.

##### Arguments

- Argument 0: A WeekEventReg flag. `WEEKEVENTREG_` macros are preferred.

##### Example

```c
if_week_event_reg (WEEKEVENTREG_61_02) {
    return_s (31)
}
return_s (30)
```

##### Non generics

`if_week_event_reg_s` and `if_week_event_reg_l`

#### `if_time_range`

Checks if the current time is between the passed time range.

##### Arguments

- Argument 0: Hour component of the start time
- Argument 1: Minute component of the start time
- Argument 2: Hour component of the end time
- Argument 3: Minute component of the end time

##### Example

```c
// Checks if the current time is between 18:00 ~ 6:00
if_time_range (18, 0, 6, 0) {
    return_time (18, 0, 6, 0, 2)
} else {
    return_none
}
```

##### Non generics

`if_time_range_s` and `if_time_range_l`

#### `if_misc`

Checks if the passed miscellaneous argument is true.

##### Arguments

- Argument 0: A value of the `ScheduleCheckMisc` enum.

##### Example

```c
if_misc (SCHEDULE_CHECK_MISC_MASK_ROMANI) {
    return_s (33)
} else {
    return_s (34)
}
```

##### Non generics

`if_misc_s`. Note there's no long version of this command. It is advised to minimize the amount of commands used on a
`ìf_misc` body and `else`'s body.

#### `if_scene`

Checks if the current scene matches the one passed as parameter.

##### Arguments

- Argument 0: A value of the `SceneId` enum.

##### Example

```c
if_scene (SCENE_SECOM) {
    return_s (7)
}
```

##### Non generics

`if_scene_s` and `if_scene_l`

#### `if_day`

Checks if the current day matches the passed argument.

##### Arguments

- Argument 0: The day to check.

##### Example

```c
if_day (3) {
    return_l (1)
}
```

##### Non generics

`if_day_s` and `if_day_l`

#### `if_before_time`

Checks if the current time is before the time passed as parameter.

##### Arguments

- Argument 0: The hour component of the time.
- Argument 1: The minute component of the time.

##### Example

```c
if_before_time (8, 0) {
    return_s (19)
} else {
    return_none
}
```

##### Non generics

`if_before_time_s` and `if_before_time_l`

##### Notes

This command performs the contrary check to `if_since_time`.

#### `if_since_time`

Checks if the current time is after or equal to the time passed as parameter.

##### Arguments

- Argument 0: The hour component of the time.
- Argument 1: The minute component of the time.

##### Example

```c
if_since_time (13, 0) {
    return_s (9)
} else {
    return_none
}
```

##### Non generics

`if_since_time_s` and `if_since_time_l`

##### Notes

This command performs the contrary check to `if_before_time`.

### Unconditional branches

Unconditional branches are basically the equivalent of C's `goto`s. They require a [label](#labels) to know where to
branch to.

#### `branch`

Unconditionally move the control flow to the passed label.

##### Arguments

- Argument 0: The label to branch to.

##### Example

```c
if_day (3) {
    if_since_time (10, 0) {
        label_0x8:
        return_none
    } else {
        branch (label_0xF)
    }
} else {
    if_time_range (10, 0, 20, 0) {
        branch (label_0x8)
    } else {
        label_0xF:
        return_s (21)
    }
}
```

##### Non generics

`branch_s` and `branch_l`

### `else`

An `else` signals which commands should be executed in case a [conditional check](#conditional-checks) does not
evaluates to true. The `else` signals this by either having those instructions inside its own body (marked by braces)
or by not having those braces but being immediately followed by another conditional check command, similar to C's
`else if`.

##### Example

The following two scripts are equivalent:

```c
if_time_range (9, 50, 18, 1) {
    return_time (9, 50, 18, 1, 1)
} else {
    if_time_range (18, 0, 6, 0) {
        return_time (18, 0, 6, 0, 2)
    } else {
        return_l (0)
    }
}
```

```c
if_time_range (9, 50, 18, 1) {
    return_time (9, 50, 18, 1, 1)
} else if_time_range (18, 0, 6, 0) {
    return_time (18, 0, 6, 0, 2)
} else {
    return_l (0)
}
```

### Return commands

#### `return_s`

TODO

##### Arguments

- Argument 0: TODO.

##### Example

```c
TODO
```

#### `return_l`

TODO

##### Arguments

- Argument 0: TODO.

##### Example

```c
TODO
```

#### `return_none`

TODO

##### Arguments

- Argument 0: TODO.

##### Example

```c
TODO
```

#### `return_empty`

TODO

##### Arguments

- Argument 0: TODO.

##### Example

```c
TODO
```

#### `return_time`

TODO

##### Arguments

- Argument 0: TODO.

##### Example

```c
TODO
```

### Miscellaneous commands

#### `nop`

No operation. Doesn't perform an action or a check.

##### Arguments

- Argument 0: Unknown meaning. Ignored.
- Argument 1: Unknown meaning. Ignored.
- Argument 2: Unknown meaning. Ignored.

##### Example

```c
nop (0, 1, 2)
```

### Operators

Operators can be applied to some commands.

Currently only one operator is allowed on the language, the [`not`](#not) operator.

#### `not`

A label is a special kind of command that doesn't get compiled into the actual low level script, instead it changes the
meaning of the check that's right next ot it by inverting the logic of the check. In other words, the subcommands of a
conditional check command will be executed if the check of said command evaluates to false instead of true.

A `not` must always be followed by a [conditional check command](#conditional-checks).

##### Example

The following two scripts are equivalent:

```c
if_week_event_reg (WEEKEVENTREG_51_08) {
    if_since_time (22, 0) {
        return_s (12)
    } else {
        return_none
    }
} else {
    return_s (12)
}
```

```c
not if_week_event_reg (WEEKEVENTREG_51_08) {
    return_s (12)
} else {
    if_since_time (22, 0) {
        return_s (12)
    } else {
        return_none
    }
}
```

### Labels

A label is a special kind of command that doesn't get compiled into the actual low level script, instead it is used as
a marker to be used for [`branch`es](#branch).

A label is defined as an alphanumeric identifier (a to z, digits and underscores) followed by a colon (`:`). The colon
is not considered part of the label's name.

A label must always be followed by another command that isn't another label.
