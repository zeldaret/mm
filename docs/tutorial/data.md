# Data

Up: [Contents](contents.md)
Previous: [Draw functions](draw_functions.md)

## Table of Contents

- [Data first](#data-first)
- [Extern and data last](#extern-and-data-last)
- [Segmented pointers](#segmented-pointers)
- [Fake symbols](#fake-symbols)
- [Inlining](#inlining)

Each actor's data is stored in a separate file. EnRecepgirl's data is in `data/overlays/ovl_En_Recepgirl/ovl_En_Recepgirl.data.s`, for example. At some point in the decompilation process we need to convert this raw data into recognisable information for the C to use.

There are two main ways to do this: either 
1. import the data first and type it later, or 
2. wait until the data appears in functions, extern it, then import it at the end

Sometimes something between these two is appropriate: wait until the largest or strangest bits of data appear in functions, get some typing information out of that, and then import it, but for now, let's stick to both of these.

Both approaches have their advantages and disadvantages.

## Data first

This way is good for smaller actors with little data. The OoT tutorial [covers this in plenty of detail](https://github.com/zeldaret/oot/blob/master/docs/tutorial/data.md), and the process in MM is essentially identical, so we won't go over it here.


## Extern and data last

Externing is explained in detail in the document about the [Init function](beginning_decomp.md). To summarize, every time a `D_address` appears that is in the data file, we put a
```C
extern UNK_TYPE D_address;
```
at the top of the file, in the same order that the data appears in the data file. We can also give it a type if we know what the type actually is (e.g. for colliders, initchains, etc.), and convert the actual data and place it commented-out under the corresponding line. This means we don't have to do everything at once at the end.

Once we have decompiled enough things to know what the data is, we can import it. The advantage of doing it this way is we should know what type everything is already: in our work on EnRecepgirl, for example, we ended up with the following data at the top of the file
```C
#if 0
const ActorInit En_Recepgirl_InitVars = {
    ACTOR_EN_RECEPGIRL,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BG,
    sizeof(EnRecepgirl),
    (ActorFunc)EnRecepgirl_Init,
    (ActorFunc)EnRecepgirl_Destroy,
    (ActorFunc)EnRecepgirl_Update,
    (ActorFunc)EnRecepgirl_Draw,
};

static void* D_80C106B0[4] = { (void*)0x600F8F0, (void*)0x600FCF0, (void*)0x60100F0, (void*)0x600FCF0 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80C106C0[] = {
    ICHAIN_U8(targetMode, 6, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 1000, ICHAIN_STOP),
};

static s32 D_80C106C8 = 0;

#endif
```
and the main thing we need to understand is `D_80C106B0`

*Before doing anything else, make sure `make` gives `OK`.*

First, we tell the compiler to ignore the original data file. To do this, open the file called `spec` in the main directory of the repository, and search for the actor name. You will find a section that looks like
```
beginseg
    name "ovl_En_Recepgirl"
    compress
    include "build/src/overlays/actors/ovl_En_Recepgirl/z_en_recepgirl.o"
    include "build/data/ovl_En_Recepgirl/ovl_En_Recepgirl.data.o"
    include "build/data/ovl_En_Recepgirl/ovl_En_Recepgirl.reloc.o"
endseg
```
We will eventually remove both of the bottom two lines and replace them with our own reloc file, but for now, just comment out the data line:
```
beginseg
    name "ovl_En_Recepgirl"
    compress
    include "build/src/overlays/actors/ovl_En_Recepgirl/z_en_recepgirl.o"
    //include "build/data/ovl_En_Recepgirl/ovl_En_Recepgirl.data.o"
    include "build/data/ovl_En_Recepgirl/ovl_En_Recepgirl.reloc.o"
endseg
```

Next remove all the externs, and uncomment their corresponding commented data:
```C
const ActorInit En_Recepgirl_InitVars = {
    ACTOR_EN_RECEPGIRL,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BG,
    sizeof(EnRecepgirl),
    (ActorFunc)EnRecepgirl_Init,
    (ActorFunc)EnRecepgirl_Destroy,
    (ActorFunc)EnRecepgirl_Update,
    (ActorFunc)EnRecepgirl_Draw,
};

static void* D_80C106B0[4] = { (void*)0x600F8F0, (void*)0x600FCF0, (void*)0x60100F0, (void*)0x600FCF0 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80C106C0[] = {
    ICHAIN_U8(targetMode, 6, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 1000, ICHAIN_STOP),
};

static s32 D_80C106C8 = 0;
```

That should be everything, and we should now be able to `make` without the data file with no issues. 


## Segmented pointers

The game has a convenient system that allows it to sometimes effectively use offsets into a file instead of raw memory addresses to reference things. This is done by setting a file address to a *segment*. A segmented address is of the form `0x0XYYYYYY`, where `X` is the segment number. There are 16 available segments, and actors always set segment 6 to their object file, which is a file containing assets (skeleton, animations, textures, etc.) that they use. This is what all those `D_06...` are, and it is also what the entries in `D_80C106B0` are: they are currently raw numbers instead of symbols, though, and we would like to replace them.

There is an obvious problem here, which is that is that these symbols have to be defined *somewhere*, or the linker will complain (indeed, if we change the ones in the array to `D_...`, even if we extern them, we get 
```
mips-linux-gnu-ld: build/src/overlays/actors/ovl_En_Recepgirl/z_en_recepgirl.o:(.data+0x20): undefined reference to `D_0600F8F0'
````
As we'd expect, of course: we didn't fulfil our promise that they were defined elsewhere.)

This is mitigated by use of the file `undefined_syms.txt`, which feeds the linker the raw addresses to use as the symbol definitions. If you find a segmented address that is not in already externed, `extern` it at the top of the file and add it to the actor's section in undefined_syms:
```C
extern void* D_0600F8F0;
extern void* D_0600FCF0;
extern void* D_060100F0;
extern void* D_0600FCF0;

static void* D_80C106B0[4] = { &D_0600F8F0, &D_0600FCF0, &D_060100F0, &D_0600FCF0 };
```
and in undefined_syms.txt:
```
// ovl_En_Recepgirl
D_06000968 = 0x06000968;
D_06001384 = 0x06001384;
D_06009890 = 0x06009890;
D_0600A280 = 0x0600A280;
D_0600AD98 = 0x0600AD98;
D_0600F8F0 = 0x0600F8F0;
D_0600FCF0 = 0x0600FCF0;
D_060100F0 = 0x060100F0;
D_06011B60 = 0x06011B60;
```

We will come back and name these later when we do the object.


## Fake symbols

Some symbols in the data have been decompiled wrongly, being incorrectly separated from the previous symbol due to how it was accessed by the actor's functions. However, most of these have now been fixed. Some more detail is given in [Types, structs and padding](types_structs_padding.md) If you are unsure, ask!


## Inlining

After the file is finished, it is possible to move some static data into functions. This requires that:
1. The data is used in only one function
2. The ordering of the data can be maintained

Additionally, we prefer to keep larger data (more than a line or two) out of functions anyway.


# Finally: .bss

A .bss contains data that is uninitialised (actually initialised to `0`). For most actors all you need to do is declare it at the top of the actor file without giving it a value, once you find out what type it is. In `code`, it's much more of a problem.

Next: [Documenting](documenting.md)