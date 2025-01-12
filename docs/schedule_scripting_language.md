# Schedule scripting language

The Schedule scripting language is a high level language that was made to help
reading and modifying the schedule scripts used by various actors.

It should be noted that the language discussed on this document was invented
and made up by the community. There's no presence of higher level abstraction
on the game ROM, neither it was used by the original development team at
Nintendo.

- [Schedule scripting language](#schedule-scripting-language)
  - [Features of the schedule system](#features-of-the-schedule-system)
    - [Short and long commands](#short-and-long-commands)
  - [How a schedule script looks like](#how-a-schedule-script-looks-like)
  - [Syntax](#syntax)
  - [Compiling](#compiling)
  - [Commands](#commands)
    - [Generics and non-generics](#generics-and-non-generics)
    - [Command arguments](#command-arguments)
    - [Conditional checks](#conditional-checks)
      - [`if_week_event_reg`](#if_week_event_reg)
        - [`if_week_event_reg` arguments](#if_week_event_reg-arguments)
        - [`if_week_event_reg` example](#if_week_event_reg-example)
        - [`if_week_event_reg` non-generics](#if_week_event_reg-non-generics)
      - [`if_time_range`](#if_time_range)
        - [`if_time_range` arguments](#if_time_range-arguments)
        - [`if_time_range` example](#if_time_range-example)
        - [`if_time_range` non-generics](#if_time_range-non-generics)
      - [`if_misc`](#if_misc)
        - [`if_misc` arguments](#if_misc-arguments)
        - [`if_misc` example](#if_misc-example)
        - [`if_misc` non-generics](#if_misc-non-generics)
      - [`if_scene`](#if_scene)
        - [`if_scene` arguments](#if_scene-arguments)
        - [`if_scene` example](#if_scene-example)
        - [`if_scene` non-generics](#if_scene-non-generics)
      - [`if_day`](#if_day)
        - [`if_day` arguments](#if_day-arguments)
        - [`if_day` example](#if_day-example)
        - [`if_day` non-generics](#if_day-non-generics)
      - [`if_before_time`](#if_before_time)
        - [`if_before_time` arguments](#if_before_time-arguments)
        - [`if_before_time` example](#if_before_time-example)
        - [`if_before_time` non-generics](#if_before_time-non-generics)
        - [`if_before_time` notes](#if_before_time-notes)
      - [`if_since_time`](#if_since_time)
        - [`if_since_time` arguments](#if_since_time-arguments)
        - [`if_since_time` example](#if_since_time-example)
        - [`if_since_time` non-generics](#if_since_time-non-generics)
        - [`if_since_time` notes](#if_since_time-notes)
    - [Unconditional branches](#unconditional-branches)
      - [`branch`](#branch)
        - [`branch` arguments](#branch-arguments)
        - [`branch` example](#branch-example)
        - [`branch` non-generics](#branch-non-generics)
    - [`else`](#else)
      - [`else` example](#else-example)
    - [Return commands](#return-commands)
      - [`return_s`](#return_s)
        - [`return_s` arguments](#return_s-arguments)
        - [`return_s` example](#return_s-example)
      - [`return_l`](#return_l)
        - [`return_l` arguments](#return_l-arguments)
        - [`return_l` example](#return_l-example)
      - [`return_none`](#return_none)
        - [`return_none` arguments](#return_none-arguments)
        - [`return_none` example](#return_none-example)
      - [`return_empty`](#return_empty)
        - [`return_empty` arguments](#return_empty-arguments)
        - [`return_empty` example](#return_empty-example)
      - [`return_time`](#return_time)
        - [`return_time` arguments](#return_time-arguments)
        - [`return_time` example](#return_time-example)
    - [Other commands](#other-commands)
      - [`nop`](#nop)
        - [`nop` arguments](#nop-arguments)
        - [`nop` example](#nop-example)
    - [Operators](#operators)
      - [`not`](#not)
        - [`not` example](#not-example)
    - [Labels](#labels)
  - [Formal grammar](#formal-grammar)
    - [Tokens](#tokens)

## Features of the schedule system

The Schedule system is a very simple scripting language, it is composed of a
series of commands that can check the state of the game and return a value
depending on said state. This system can't declare variables, hold its own
state or modify the game's state.

A schedule script can check the state of the following:

- Current in-game [day](#if_day).
- If a [WeekEventReg flag](#if_week_event_reg) is set or not.
- Current time is in a specified [time range](#if_time_range).
- Current time is [before](#if_before_time)/[after](#if_since_time) a specified
  time.
- Some other [miscellaneous](#if_misc) checks (see the `ScheduleCheckMisc`
  enum).

All of those checks act as conditional branches into some other command. The
schedule system also supports unconditional branches.

The schedule script is run until a return command is executed. There are various
return commands that allow different things:

- [Return none](#return_none): The schedule finished without returning a value.
- [Return empty](#return_empty): The schedule finished without changing the
  previous value.
- [Return s](#return_s): The script returns a value that's 1 byte long.
- [Return l](#return_l): The script returns a value that's 2 bytes long (Note
  this is bugged and will be truncated to 1 byte).
- [Return time](#return_time): Returns a time range and a 1 byte value.

Running an unknown command or branching to the middle of a command is undefined
behaviour.

A low level schedule script can be compared to a multi byte assembly language,
on which each command occupies 1 byte plus a variable number of arguments.

### Short and long commands

Due to the commands themselves using a variable amount of bytes it is possible
to do some small optimizations, like if a branch distance (which is the amount
of bytes the interpreter should skip if a check evaluates to true) can fit on a
signed byte then a **short** (noted with the `_S` suffix) command is used,
otherwise a **long** version (noted with the `_L` suffix) of the command is used
instead.

A long command uses two bytes to store the branch distance, meaning the command
itself will be one byte longer.

There are no commands that use more than 2 bytes to store the branch distance.

The short and long distinction also exists for the returned value, in case the
user wants to return a value that wouldn't fit on a single unsigned byte and
requires an unsigned short (two bytes) instead. Please note that the vanilla
built-in system interpreter has a bug on which the upper byte of a long returned
value will be discarded, so please ensure your returned values always fit on the
0-255 range.

## How a schedule script looks like

An extracted schedule script is just an array of raw data. A macroified version
looks like this:

```c
static ScheduleScript D_80BD3DB0[] = {
    /* 0x00 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_YADOYA, 0x21 - 0x04),
    /* 0x04 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(3, 0x0B - 0x08),
    /* 0x08 */ SCHEDULE_CMD_RET_VAL_L(1),
    /* 0x0B */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(2, 0x20 - 0x0F),
    /* 0x0F */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 0, 23, 0, 0x1D - 0x15),
    /* 0x15 */ SCHEDULE_CMD_CHECK_WEEK_EVENT_REG_S(WEEKEVENTREG_HAD_MIDNIGHT_MEETING, 0x1C - 0x19),
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

Having these scripts as arrays like this has two major flaws:

- The control flow is not clear at a first glance (this is especially problematic
  for larger scripts).
- The branch distances are hardcoded into each command, making the script itself
  hard to modify.

As a solution, the high level Schedule script language uses a C-like syntax to
better represent the control flow. The above script can be written as the
following:

```c
D_80BD3DB0 {
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
}
```

## Syntax

The syntax is simple, it consists on the name of the schedule script followed
by a succession of commands. Some commands require arguments (by using
parentheses) and some (conditional checks) can have bodies with subcommands and
an optional `else` with its corresponding body with subcommands.

Like in C, both whitespace and newlines are not part of the language and they
get ignored during compilation. At the same time, this language accepts both C
and C++ styles of comments, known as block comments (`/**/`) and line comments
(`//`).

Each top-level schedule script consists on its name, followed by a list of
commands delimited by braces  (`{` and `}`). A schedule script must always have
at least one command on its body.

A command's body is delimited by braces (`{` and `}`). A body must follow either
a [conditional check](#conditional-checks) command or an `else`, meaning
top-level bodies are not allowed. At the same time a conditional check must be
followed by a body. An `else` must be followed by either a body or another
conditional check command.

Even if this language's syntax is inspired by C, there are a few key differences:

- Commands are not separated by semicolons (`;`). Instead whitespace is used as
  separation.
- Instead of having a single `if` conditional of which its parameters should
  evaluate to non-zero, this language uses
  [conditional checks](#conditional-checks). These are commands that receive
  parameters and have a body with parameters that would be executed if the
  command itself evaluated to true. This commands may be followed by an `else`,
  which has its own body.
- There's no concept of functions, variables, loops, scopes, etc.
  - Each schedule script could be seen as a function itself, but said script
    can't "call" another scripts.

## Compiling

Compiling a high level schedule script should produce an array for each script
in the file. Each array should contain a series of macros that can be
`#include`d by a C preprocessor, like in the following example:

File: `build/src/overlays/actors/ovl_En_Ah/scheduleScripts.schl.inc`

```c
static ScheduleScript D_80BD3DB0[] = {
    /* 0x00 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_YADOYA, 0x21 - 0x04),
    /* 0x04 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(3, 0x0B - 0x08),
    /* 0x08 */ SCHEDULE_CMD_RET_VAL_L(1),
    /* 0x0B */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(2, 0x20 - 0x0F),
    /* 0x0F */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 0, 23, 0, 0x1D - 0x15),
    /* 0x15 */ SCHEDULE_CMD_CHECK_WEEK_EVENT_REG_S(WEEKEVENTREG_HAD_MIDNIGHT_MEETING, 0x1C - 0x19),
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

In the actor's C code:

```c
#include "src/overlays/actors/ovl_En_Ah/scheduleScripts.schl.inc"
```

## Commands

Commands are the fundamental (and almost only) building block of this language.
A schedule script file must always contain at least one script, and a schedule
script must always have at least one command. It's undefined behaviour if the
script's control flow doesn't always lead to a return command.

To see how the command arguments work, please see the
[corresponding section](#command-arguments).

Commands can be categorized in 4 major types:
[Conditional checks](#conditional-checks),
[unconditional branches](#unconditional-branches),
[return commands](#return-commands) and
[other commands](#other-commands).

### Generics and non-generics

Schedule scripts use both [short and long commands](#short-and-long-commands)
for most of the [conditional checks](#conditional-checks) and
[unconditional branches](#unconditional-branches) commands, making it optimal
space-wise, but terrible to worry about when actually writing a schedule script
from the user's point of view.

Due to this, this high level language allows for generic versions of those
commands (a.k.a. suffix-less versions) that allow not having to worry about how
many commands the body of a check has (and the byte length of them).

The rest of this section will mostly refer to the generic versions of the
commands. The non-generic versions of each command are available to be used too,
but their use is not recommended.

### Command arguments

Some commands require arguments. Arguments are used by checking commands to
check something specific of the state of the game (what's the current day? what's
the current scene? etc.) and take a decision based on it (branch to another
command).

Arguments are enclosed in parentheses (`(` and `)`) and passed verbatim to the
generated output, allowing a compiler for this language to not need to recognize
any identifier used in arguments, allowing to use any custom identifier
(specially useful for schedule result enums). Note this behaviour may
change in a future version of the language.

### Conditional checks

Conditional checks commands are commands that take a decision based on
the state of the game, allowing it to decide which set of subcommands to
execute.

All conditional checks require an argument and a body of subcommands. A
conditional check can optionally be followed by an `else`.

If the condition of a command is not satisfied and that command has
an `else`, then control jumps to the body of that `else`. If
there's no `else` and the condition isn't satisfied then control just
falls through into the next command.

#### `if_week_event_reg`

Checks if the passed WeekEventReg flag is set, and execute the body of the
command if it is set.

##### `if_week_event_reg` arguments

- Argument 0: A WeekEventReg flag. `WEEKEVENTREG_` macros are preferred.

##### `if_week_event_reg` example

```c
if_week_event_reg (WEEKEVENTREG_61_02) {
    return_s (31)
}
return_s (30)
```

##### `if_week_event_reg` non-generics

`if_week_event_reg_s` and `if_week_event_reg_l`

#### `if_time_range`

Checks if the current time is between the passed time range.

##### `if_time_range` arguments

- Argument 0: Hour component of the start time
- Argument 1: Minute component of the start time
- Argument 2: Hour component of the end time
- Argument 3: Minute component of the end time

##### `if_time_range` example

```c
// Checks if the current time is between 18:00 ~ 6:00
if_time_range (18, 0, 6, 0) {
    return_time (18, 0, 6, 0, 2)
} else {
    return_none
}
```

##### `if_time_range` non-generics

`if_time_range_s` and `if_time_range_l`

#### `if_misc`

Checks if the passed miscellaneous argument is true.

##### `if_misc` arguments

- Argument 0: A value of the `ScheduleCheckMisc` enum.

##### `if_misc` example

```c
if_misc (SCHEDULE_CHECK_MISC_MASK_ROMANI) {
    return_s (33)
} else {
    return_s (34)
}
```

##### `if_misc` non-generics

`if_misc_s`. Note there's no long version of this command. It is advised to
minimize the amount of commands used on a `ìf_misc` body and `else`'s body.

#### `if_scene`

Checks if the current scene matches the one passed as argument.

##### `if_scene` arguments

- Argument 0: A value of the `SceneId` enum.

##### `if_scene` example

```c
if_scene (SCENE_SECOM) {
    return_s (7)
}
```

##### `if_scene` non-generics

`if_scene_s` and `if_scene_l`

#### `if_day`

Checks if the current day matches the passed argument.

##### `if_day` arguments

- Argument 0: The day to check. For example, passing `1` will check for day 1.

##### `if_day` example

```c
if_day (3) {
    return_l (1)
}
```

##### `if_day` non-generics

`if_day_s` and `if_day_l`

#### `if_before_time`

Checks if the current time is before the time passed as argument.

##### `if_before_time` arguments

- Argument 0: The hour component of the time.
- Argument 1: The minute component of the time.

##### `if_before_time` example

```c
if_before_time (8, 0) {
    return_s (19)
} else {
    return_none
}
```

##### `if_before_time` non-generics

`if_before_time_s` and `if_before_time_l`

##### `if_before_time` notes

This command performs the opposite check of `if_since_time`.

#### `if_since_time`

Checks if the current time is after or equal to the time passed as argument.

##### `if_since_time` arguments

- Argument 0: The hour component of the time.
- Argument 1: The minute component of the time.

##### `if_since_time` example

```c
if_since_time (13, 0) {
    return_s (9)
} else {
    return_none
}
```

##### `if_since_time` non-generics

`if_since_time_s` and `if_since_time_l`

##### `if_since_time` notes

This command performs the contrary check to `if_before_time`.

### Unconditional branches

Unconditional branches are basically the equivalent of C's `goto`s. They require
a [label](#labels) to know where to branch to.

#### `branch`

Unconditionally transfer control to the passed label.

##### `branch` arguments

- Argument 0: The label to branch to.

##### `branch` example

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

##### `branch` non-generics

`branch_s` and `branch_l`

### `else`

An `else` signals which commands should be executed in case a
[conditional check](#conditional-checks) does not evaluates to true. The `else`
signals this by either having those instructions inside its own body (marked by
braces) or by not having those braces but being immediately followed by another
conditional check command, similar to C's `else if`.

#### `else` example

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

A return command signals the end of the script and halts its execution.

A return command allows to optionally return a value and/or a time range to the
calling actor so it can change behavior accordingly.

A schedule script with a control flow that leads to no return command is
undefined behaviour.

#### `return_s`

Allows to return a short (one byte) value.

##### `return_s` arguments

- Argument 0: The value to return. It must fit in a `u8`.

##### `return_s` example

```c
if_time_range (8, 0, 12, 0) {
    return_s (EN_NB_SCH_1)
}
```

#### `return_l`

Allows to return a long (two bytes) value.

Please note that the vanilla interpreter for the schedule scripts has a bug on
which the upper byte of a long returned value will be discarded (will be
truncated to a `u8`), so please ensure your returned values always fit in the
0-255 range.

##### `return_l` arguments

- Argument 0: The value to return. It must fit in a `u16`.

##### `return_l` example

```c
if_scene (SCENE_TOWN) {
    return_l (1)
} else {
    return_none
}
```

#### `return_none`

The schedule finished without returning a value. The internal `hasResult`
member of the `ScheduleOutput` struct will be set to `false`.

##### `return_none` arguments

No arguments.

##### `return_none` example

```c
if_week_event_reg (WEEKEVENTREG_HAD_MIDNIGHT_MEETING) {
    return_none
}
```

#### `return_empty`

The schedule finished without changing the previous value. The internal `hasResult`
member of the `ScheduleOutput` struct will be set to `true`.

##### `return_empty` arguments

No arguments.

##### `return_empty` example

```c
if_time_range (15, 50, 16, 15) {
    return_empty
}
```

#### `return_time`

Returns a time range and a 1 byte value.

##### `return_time` arguments

- Argument 0: Hour component of the start time
- Argument 1: Minute component of the start time
- Argument 2: Hour component of the end time
- Argument 3: Minute component of the end time
- Argument 4: A value to return. It must fit in a `u8`

##### `return_time` example

```c
if_time_range (0, 0, 6, 0) {
    return_time (0, 0, 6, 0, TOILET_HAND_SCH_AVAILABLE)
} else {
    return_none
}
```

### Other commands

#### `nop`

No operation. Doesn't perform an action or a check.

##### `nop` arguments

- Argument 0: Unknown meaning.
- Argument 1: Unknown meaning.
- Argument 2: Unknown meaning.

##### `nop` example

```c
nop (0, 1, 2)
```

### Operators

Operators can be applied to some commands.

Currently only one operator is allowed on the language, the [`not`](#not) operator.

#### `not`

A `not` is a special kind of command that doesn't get compiled into the actual
low level script, instead it changes the meaning of the check that's right next
to it by inverting the logic of the check. In other words, the subcommands of a
conditional check command will be executed if the check of said command
evaluates to false instead of true.

A `not` must always be followed by a [conditional check command](#conditional-checks).

##### `not` example

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

A label is a special kind of command that doesn't get compiled into the actual
low level script, instead it is used as a marker to be used for
[`branch`es](#branch).

A label is defined as an alphanumeric identifier (a to z, digits and
underscores) followed by a colon (`:`). The colon is not considered part of the
label's name.

A label must always be followed by another command that isn't another label.

## Formal grammar

This section presents the formal grammar for the Schedule scripting language.

```yac
<scriptFile>            : <functionList>
                        ;

<functionList>          : <functionScript>
                        | <functionList> <functionScript>
                        ;

<functionScript>        : IDENTIFIER '{' <cmdList> '}'
                        ;

<cmdList>               : <labeledCmd>
                        | <cmdList> <labeledCmd>
                        ;

<labeledCmd>            : <command>
                        | IDENTIFIER ':' <command>
                        ;

<command>               : <conditionalCmd>
                        | <unconditionalCmd>
                        | <returnCmd>
                        | <miscCmd>
                        ;

<conditionalCmd>        : <conditionalExprBody> <else>
                        | <conditionalExprBody>
                        ;

<unconditionalCmd>      : <tokenBranch> <args>
                        ;

<returnCmd>             : RETURN_S <args>
                        | RETURN_L <args>
                        | RETURN_NONE
                        | RETURN_EMPTY
                        | RETURN_TIME <args>
                        ;

<miscCmd>               : NOP <args>
                        ;

<conditionalExprBody>   : NOT <conditionalExpr> <body>
                        | <conditionalExpr> <body>
                        ;

<conditionalExpr>       : <tokenIfWeekEventReg> <args>
                        | <tokenIfTimeRange> <args>
                        | <tokenIfMisc> <args>
                        | <tokenIfScene> <args>
                        | <tokenIfDay> <args>
                        | <tokenIfBeforeTime> <args>
                        | <tokenIfSinceTime> <args>
                        ;

<else>                  : ELSE <body>
                        | ELSE <conditionalCmd>
                        ;

<tokenIfWeekEventReg>   : IF_WEEK_EVENT_REG
                        | IF_WEEK_EVENT_REG_S
                        | IF_WEEK_EVENT_REG_L
                        ;

<tokenIfTimeRange>      : IF_TIME_RANGE
                        | IF_TIME_RANGE_S
                        | IF_TIME_RANGE_L
                        ;

<tokenIfMisc>           : IF_MISC
                        | IF_MISC_S
                        ;

<tokenIfScene>          : IF_SCENE
                        | IF_SCENE_S
                        | IF_SCENE_L
                        ;

<tokenIfDay>            : IF_DAY
                        | IF_DAY_S
                        | IF_DAY_L
                        ;

<tokenIfBeforeTime>     : IF_BEFORE_TIME
                        | IF_BEFORE_TIME_S
                        | IF_BEFORE_TIME_L
                        ;

<tokenIfSinceTime>      : IF_SINCE_TIME
                        | IF_SINCE_TIME_S
                        | IF_SINCE_TIME_L
                        ;

<tokenBranch>           : BRANCH
                        | BRANCH_S
                        | BRANCH_L
                        ;

<body>                  : '{' '}'
                        | '{' <cmdList> '}'
                        ;

<args>                  : '(' ')'
                        | '(' <args_list> ')'
                        ;

<args_list>             : <arg_elem>
                        | <args_list> ',' <arg_elem>
                        ;

<arg_elem>              : NO_PARENTHESIS
                        | <args>
                        ;
```

### Tokens

The presented grammar expects a few tokens.

First column is the corresponding token and right is a regular expression to
match said token.

```regex
IDENTIFIER              [a-zA-Z0-9_]+

IF_WEEK_EVENT_REG       if_week_event_reg
IF_WEEK_EVENT_REG_S     if_week_event_reg_s
IF_WEEK_EVENT_REG_L     if_week_event_reg_l
IF_TIME_RANGE           if_time_range
IF_TIME_RANGE_S         if_time_range_s
IF_TIME_RANGE_L         if_time_range_l
IF_MISC                 if_misc
IF_MISC_S               if_misc_s
IF_SCENE                if_scene
IF_SCENE_S              if_scene_s
IF_SCENE_L              if_scene_l
IF_DAY                  if_day
IF_DAY_S                if_day_s
IF_DAY_L                if_day_l
IF_BEFORE_TIME          if_before_time
IF_BEFORE_TIME_S        if_before_time_s
IF_BEFORE_TIME_L        if_before_time_l
IF_SINCE_TIME           if_since_time
IF_SINCE_TIME_S         if_since_time_s
IF_SINCE_TIME_L         if_since_time_l

BRANCH                  branch
BRANCH_S                branch_s
BRANCH_L                branch_l

RETURN_S                return_s
RETURN_L                return_l
RETURN_NONE             return_none
RETURN_EMPTY            return_empty
RETURN_TIME             return_time

NOP                     nop

ELSE                    else
NOT                     not

NO_PARENTHESIS          [^\(\)]+
```
