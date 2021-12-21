# Types, structs, and padding

Reminders:
- In N64 MIPS, 1 word is 4 bytes (yes, the N64 is meant to be 64-bit, but it mostly isn't used like it in MM or OoT)
- A byte is 8 bits, or 2 hex digits


## Types

The following are the common data types used everywhere:

| Name      | Size            | Comment        |
| ----      | -----           | --------       |
| char      | 1 byte          | character      |
| u8        | 1 byte          | unsigned byte  |
| s8        | 1 byte          | signed byte    |
| u16       | 2 bytes         | unsigned short | 
| s16       | 2 bytes         | signed short   |
| u32       | 4 bytes/1 word  | unsigned int   |
| s32       | 4 bytes/1 word  | signed int     |
| void*     | 4 bytes/1 word  | pointer        |
| uintptr_t | 4 bytes/1 word  | pointer^       |
| intptr_t  | 4 bytes/1 word  | pointer^       |

A pointer is sometimes mistaken for an `s32`. The last two, marked with `^`, are special types allowing for arithmetic on generic pointers, and are to be used over `u32`.

`s32` is the default thing to use in the absence of any other information about the data.

Useful data for guessing types:
- `u8` is about 7 times more common than `s8`
- `s16` is about 16 times more common than `u16`
- `s32` is about 8 times more common than `u32`

Another useful thing to put here: the typedef for an action function is
```C
typedef void (*ActorNameActionFunc)(struct ActorName*, GlobalContext*);
```
where you replace `ActorName` by the actual actor name as used elsewhere in the actor, e.g. `EnRecepgirl`. In MM these typedefs have been automatically generated, so you don't need to constantly copy from here or another actor any more.


## Some Common Structs

Here are the usual names and the sizes of some of the most common structs used in actors and their structs:
| Type                    | Usual name            | Size            |
| ----------------------- | --------------------- | --------------- |
| `Actor`                 | `actor`               | 0x144           |
| `DynaPolyActor`         | `dyna`                | 0x15C           |
| `Vec3f`                 |                       | 0xC             | 
| `Vec3s`                 |                       | 0x6             | 
| `SkelAnime`             | `skelAnime`           | 0x44            |
| `Vec3s[limbCount]`      | `jointTable`          | 0x6 * limbCount |
| `Vec3s[limbCount]`      | `morphTable`          | 0x6 * limbCount |
| `ColliderCylinder`      | `collider`            | 0x4C            |
| `ColliderQuad`          | `collider`            | 0x80            |
| `ColliderJntSph`        | `collider`            | 0x20            |
| `ColliderJntSphElement` | `colliderElements[n]` | 0x40 * n        |
| `ColliderTris`          | `collider`            | 0x20            |
| `ColliderTrisElement`   | `colliderElements[n]` | 0x5C * n        |

Note that `Actor` and `DynaPolyActor` have changed size from OoT.


## Padding

### Alignment

A stored variable or piece of data does not always start immediately after the previous one: there may be padding in between: `0`s that are never written or referred to, and so ignored. This is to do with how the processor accesses memory: it reads 1 word at a time, so multibyte objects are aligned so they cross as few word boundaries as possible.

The clearest example of this is that variables with types that are 1 word in size (`s32`s and pointers, for example) are automatically shifted so that they start at the beginning of the next word, i.e. at an offset ending with one of `0,4,8,C`: this is called 4-alignment. This will also happen to `s16`s, but with 2-alignment

### Struct padding

In actor structs, this manifests as some of the char arrays not being completely replaced by actual variables. 

```C
typedef struct EnRecepgirl {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[24];
    /* 0x0218 */ Vec3s morphTable[24];
    /* 0x02A8 */ EnRecepgirlActionFunc actionFunc;
    /* 0x02AC */ u8 unk_2AC;
    /* 0x02AE */ Vec3s unk_2AE;
} EnRecepgirl; // size = 0x2B4
```

Notice that even though `unk_2AC` is a `u8`, `unk_2AE` is at `this + 0x2AE`, rather than `0x2AD`: we removed the extra char of padding while working on this actor.

How do structs themselves align? A struct has the same alignment properties as its longest constituent (that is not itself a struct). For example, a `Vec3f` has 4-alignment, while a `Vec3s` has 2-alignment.

A struct may also pad at the end: it will pad to the size of its largest non-struct element. Notably, every actor struct has size a whole number of words as well, so this phenomenon also occurs at the ends of structs. For example, ObjTree has the following actor struct:

```C
typedef struct ObjTree {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ ColliderCylinder collider;
    /* 0x01A8 */ ObjTreeActionFunc actionFunc;
    /* 0x01AC */ f32 unk_1AC;
    /* 0x01B0 */ s16 unk_1B0;
    /* 0x01B2 */ s16 unk_1B2;
    /* 0x01B4 */ s16 unk_1B4;
} ObjTree; // size = 0x1B8
```

The struct pads to be `0x1B8` in size even though the last actual variable ends at `0x1B6`.

For more information on this topic, there are plenty of guides elsewhere on the Internet, for example [The Lost Art of Structure Packing](http://www.catb.org/esr/structure-packing/). *The main thing to bear in mind for decomp purposes is that after finishing the functions, there may be some small parts of the actor struct that are just not used, because they were originally just struct padding.*

### Padding at the end of sections

In the ROM, each actor is layed out in the following order:

- .text (Function instructions, separated into .s files, aka .text)
- .data (contents of the .data.s file)
- .rodata (read-only data, includes strings, floats, jumptables etc., almost entirely moved to the appropriate function files in the MM repo)
- .bss (varibles initialised to 0, not assigned a value when declared)
- .reloc (relocation information: you can ignore this)

Each section is 0x10/16-aligned (qword aligned), i.e. each new section begins at an address with last digit `0`. This means that there can occur up to three words of padding at the end of each section.

(The same occurs with any object divided into multiple .c files: each new file becomes 0x10 aligned.)

#### Padding at the end of .text (function instructions)

In function instructions, this manifests as a set of `nop`s at the end of the last function: for example, in EnRecepGirl,
```
/* 0006B0 80C10680 27BD0038 */  addiu       $sp, $sp, 0x38
/* 0006B4 80C10684 03E00008 */  jr          $ra
/* 0006B8 80C10688 00000000 */   nop        
/* 0006BC 80C1068C 00000000 */  nop
```

the second `nop` is just extra `0`s of padding, as you can see in the machine code (third column in the comment)

Once the rest of the functions match, this is automatic. So you never need to worry about these.

#### Padding at the end of .data

In data, the last entry may contain up to 3 words of 0s as padding. These can safely be removed when migrating data, but make sure that you don't remove something that actually is accessed by the function and happens to be 0!

For example, in `ObjTree` we found that the last symbol in the data,
```
glabel D_80B9A5BC
/* 00006C 80B9A5BC */ .word 0x08000000
/* 000070 80B9A5C0 */ .word 0x00000000
/* 000074 80B9A5C4 */ .word 0xFE000000
/* 000078 80B9A5C8 */ .word 0x00000000
/* 00007C 80B9A5CC */ .word 0x00000000
```
had 2 words of padding: only the first 3 words are actually used in the `CollisionCheckInfoInit2`.

### Padding within the .data section

Every distinct symbol in data is 4-aligned (word-aligned). So in the data, even if you have two `u8`s, they will be stored in addresses starting successive words:

```C
u8 byte1 = 1 // will go to address ending in 0
u8 byte2 = 2 // Will go to address ending in 4
```
