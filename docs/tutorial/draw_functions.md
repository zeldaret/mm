# Draw functions

- Up: [Contents](contents.md)
- Previous: [The rest of the functions in the actor](other_functions.md)

Draw functions behave completely differently from the other functions in an actor. They often use a lot of macros.

This document will be a bit different: we will look at the draw functions in EnRecepgirl, then consider some more complicated examples.

## A first example

Unless it is completely invisible, an actor usually has a draw function as one of the main four actor functions. Hence its prototype looks like

```C
void EnRecepgirl_Draw(Actor* thisx, GlobalContext* globalCtx);
```

From now on, the process is rather different from the decompilation process used for the other functions. Here is the output of mips2c after sorting out the actor struct from Init, and with the arguments set back to `Actor* thisx`:
```C
s32 func_80C10558(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *actor); // extern
void func_80C10590(GlobalContext *globalCtx, s32 limbIndex, Actor *actor); // extern
void *D_80C106B0[4] = {(void *)0x600F8F0, (void *)0x600FCF0, (void *)0x60100F0, (void *)0x600FCF0};

void EnRecepgirl_Draw(Actor *thisx, GlobalContext *globalCtx) {
    EnRecepgirl* this = (EnRecepgirl *) thisx;
    GraphicsContext *sp30;
    Gfx *temp_v1;
    GraphicsContext *temp_a0;

    temp_a0 = globalCtx->state.gfxCtx;
    sp30 = temp_a0;
    func_8012C28C(temp_a0);
    temp_v1 = sp30->polyOpa.p;
    sp30->polyOpa.p = temp_v1 + 8;
    temp_v1->words.w0 = 0xDB060020;
    temp_v1->words.w1 = (u32) D_80C106B0[this->unk_2AC];
    SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, (s32) this->skelAnime.dListCount, func_80C10558, NULL, func_80C10590, (Actor *) this);
}
```


Notable features are the GraphicsContext temps, and blocks of the form

```C
    temp_v1 = sp30->polyOpa.p;
    sp30->polyOpa.p = temp_v1 + 8;
    temp_v1->words.w0 = 0xDB060020;
    temp_v1->words.w1 = (u32) D_80C106B0[this->unk_2AC];
```

(This is a particularly simple example, since there's only one of these blocks. We will give a more involved example later.)

Each of these blocks converts into a graphics macro. They are usually (but not always) straightforward, but manually converting them is a pain, and there are sometimes special cases. To deal with them easily, we will use a tool from glank's N64 tools. To install these, follow the instructions [here](https://practicerom.com/public/packages/debian/howto.txt).

For our purposes, we only need one of the programs this provides: `gfxdis.f3dex2`.


Graphics are actually 64-bit on the Nintendo 64. This code block is a result of instructions telling the processor what to do with the graphics pointer. There are two main types of graphics pointer (there are a couple of others used in `code`, but actors will only use these two),
- polyOpa ("opaque") for solid textures
- polyXlu ("Xlucent" i.e. "translucent") for translucent textures

Our example is polyOpa, not surprisingly since our receptionist is solid.

`words.w0` and `words.w1` contain the actual graphics instruction, in hex format. Usually, `w0` is constant and `w1` contains the arguments. To find out what sort of macro we are dealing with, we use `gfxdis.f3dex2`. `w1` is variable, but we need to give the program a constant placeholder. A common word to use is 12345678, so in this case we run
```
gfxdis.f3dex2 -x -g "POLY_OPA_DISP++" -d DB06002012345678
```

- `-x` uses hex instead of the default qu macros (never mind what those are, MM doesn't use them)
- `-g` is used to specify which graphics pointer macro to use
- `-d` is for the graphics dword

Our standard now is to use decimal colors. If you have a constant second argument rather than a variable one, you can also use `-dc` to get decimal colors instead of the default hex.

The output looks like
```
gSPSegment(POLY_OPA_DISP++, 0x08, 0x12345678);
```

We can now replace the `0x12345678` by the actual second word, namely `D_80C106B0[this->unk_2AC]`. We can see mips2c has pulled in this data again: we saw it before in the `Init`.

The words look like pointers to assets in the actor's object segment, which would make sense if we're looking for textures to draw. Because this data is used in a graphics macro, it will be either a displaylist or a texture; it may as well stay as `void*` until we come back to it later.

```C
gSPSegment(POLY_OPA_DISP++, 0x08, D_80C106B0[this->unk_2AC]);
```

You repeat this for every block in the function.

If you have worked on OoT, you will be aware of the functions `Graph_OpenDisps` and `Graph_CloseDisps`, and might be surprised to see them missing here. These functions are actually a debug feature: the `OPEN_DISPS` and `CLOSE_DISPS` macros still exist, but they don't expand to functions. Of course this means you have to guess where they go. A sensible guess for `OPEN_DISPS` is where the `gfxCtx` temp assignment first happens; `CLOSE_DISPS` is a bit harder, although it's basically just a `}`, so it *shouldn't* matter as much.

It's sensible to eliminate all the `gfxCtx` temps and reintroduce as needed. Also remember to change the prototype and function definition back!
```C
s32 func_80C10558(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *actor);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/func_80C10558.s")

void func_80C10590(GlobalContext *globalCtx, s32 limbIndex, Actor *actor);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/func_80C10590.s")

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/EnRecepgirl_Draw.s")
void EnRecepgirl_Draw(Actor *thisx, GlobalContext *globalCtx) {
    EnRecepgirl* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, D_80C106B0[this->unk_2AC]);

    SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, func_80C10558, NULL, func_80C10590, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
```

And this matches.

The last two functions in the actor are used as arguments in `SkelAnime_DrawTransformFlexOpa`. This is a `SkelAnime` function, except unlike the OoT ones, it has three function callback arguments instead of two: in `functions.h` or `z_skelanime.c`, we find
```C
void SkelAnime_DrawTransformFlexOpa(GlobalContext* globalCtx, void** skeleton, Vec3s* jointTable, s32 dListCount,
                   OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, TransformLimbDrawOpa transformLimbDraw, Actor* actor)
```
The typedefs of the callbacks it uses are in `z64animation.h`:
```C
typedef s32 (*OverrideLimbDrawOpa)(struct GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                struct Actor* thisx);

typedef void (*PostLimbDrawOpa)(struct GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot,
                             struct Actor* thisx);

[...]

typedef void (*TransformLimbDrawOpa)(struct GlobalContext* globalCtx, s32 limbIndex, struct Actor* thisx);
```
which is where mips2c got them from.

In this case, only two of them are used, and it is these that are the last functions standing between us and a decompiled actor.

## OverrideLimbDraw, PostLimbDraw, TransformLimbDraw

Well, we don't have a PostLimbDraw here, but as we see from the prototype, it's much the same as the OverrideLimbDraw but without the `pos` argument and no return value.
```C
s32 func_80C10558(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *actor) {
    if (limbIndex == 5) {
        rot->x += actor->unk2B0;
    }
    return 0;
}
```
Only two things to do here: we need to use `EnRecepgirl` to get to `actor + 0x2B0`, and the return value is used as a boolean, so we replace `0` by `false` (`true` means "don't draw the limb", and is hardly ever used).
```C
s32 func_80C10558(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *thisx) {
    EnRecepgirl* this = THIS;

    if (limbIndex == 5) {
        rot->x += this->unk_2AE.y;
    }
    return false;
}
```

As for the TransformLimbDraw, it has a much simpler prototype. mips2c gives
```C
void func_80C10590(GlobalContext *globalCtx, s32 limbIndex, Actor *actor) {
    if (limbIndex == 5) {
        Matrix_RotateY((s16) (0x400 - actor->unk2AE), 1);
        Matrix_GetStateTranslationAndScaledX(500.0f, (Vec3f *) &actor->focus);
    }
}
```
There is only minor cleanup needed here: 
- recasting the last argument, 
- replacing the last argument of `Matrix_RotateY` by the enum `MTXMODE_APPLY` (which means "use the current matrix instead of starting from a new identity matrix"), and the first argument by `0x400 - this->unk_2AE.x`.
- `(Vec3f *) &actor->focus` to `&actor->focus.pos` (this is the same issue as `(Actor*)this`, where mips2c doesn't climb deep enough into the struct).
```C
void func_80C10590(GlobalContext *globalCtx, s32 limbIndex, Actor *thisx) {
    EnRecepgirl* this = THIS;

    if (limbIndex == 5) {
        Matrix_RotateY(0x400 - this->unk_2AE.x, MTXMODE_APPLY);
        Matrix_GetStateTranslationAndScaledX(500.0f, &this->actor.focus.pos);
    }
}
```

## Some more examples: ObjTree

Since EnRecepgirl was a bit light on graphics macros, we will look at an example that has a few more. A nice simple one is `ObjTree_Draw`: the original mips2c output is
```C
void ObjTree_Draw(Actor *thisx, GlobalContext *globalCtx) {
    s16 sp36;
    s16 sp34;
    Gfx *sp28;
    Gfx *sp20;
    Gfx *temp_v0;
    Gfx *temp_v0_2;
    Gfx *temp_v0_3;
    Gfx *temp_v0_4;
    GraphicsContext *temp_a0;
    GraphicsContext *temp_s0;

    sp36 = (s16) (s32) (f32) thisx->shape.rot.x;
    sp34 = (s16) (s32) (f32) thisx->shape.rot.z;
    temp_a0 = globalCtx->state.gfxCtx;
    temp_s0 = temp_a0;
    func_8012C28C(temp_a0);
    temp_v0 = temp_s0->polyOpa.p;
    temp_s0->polyOpa.p = temp_v0 + 8;
    temp_v0->words.w0 = 0xDA380003;
    sp28 = temp_v0;
    sp28->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx);
    temp_v0_2 = temp_s0->polyOpa.p;
    temp_s0->polyOpa.p = temp_v0_2 + 8;
    temp_v0_2->words.w1 = (u32) &D_06000680;
    temp_v0_2->words.w0 = 0xDE000000;
    Matrix_InsertRotation(sp36, 0, sp34, 1);
    temp_v0_3 = temp_s0->polyOpa.p;
    temp_s0->polyOpa.p = temp_v0_3 + 8;
    temp_v0_3->words.w0 = 0xDA380003;
    sp20 = temp_v0_3;
    sp20->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx);
    temp_v0_4 = temp_s0->polyOpa.p;
    temp_s0->polyOpa.p = temp_v0_4 + 8;
    temp_v0_4->words.w1 = (u32) &D_060007C8;
    temp_v0_4->words.w0 = 0xDE000000;
}
```
We can see there are four blocks here, although only two different macros:
```C
    temp_v0 = temp_s0->polyOpa.p;
    temp_s0->polyOpa.p = temp_v0 + 8;
    temp_v0->words.w0 = 0xDA380003;
    sp28 = temp_v0;
    sp28->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx);
```
gfxdis gives
```
$ gfxdis.f3dex2 -x -g POLY_OPA_DISP++ -d DA38000312345678
gSPMatrix(POLY_OPA_DISP++, 0x12345678, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
```
so it becomes
```C
gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
```

```C
    temp_v0_2 = temp_s0->polyOpa.p;
    temp_s0->polyOpa.p = temp_v0_2 + 8;
    temp_v0_2->words.w1 = (u32) &D_06000680;
    temp_v0_2->words.w0 = 0xDE000000;
```
```
$ gfxdis.f3dex2 -x -g POLY_OPA_DISP++ -d DE00000012345678
gSPDisplayList(POLY_OPA_DISP++, 0x12345678);
```
so this one is
```C
gSPDisplayList(POLY_OPA_DISP++, D_06000680);
```

```C
    temp_v0_3 = temp_s0->polyOpa.p;
    temp_s0->polyOpa.p = temp_v0_3 + 8;
    temp_v0_3->words.w0 = 0xDA380003;
    sp20 = temp_v0_3;
    sp20->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx);
```
This is the same as the first one. Indeed, it's identical.
```C
    temp_v0_4 = temp_s0->polyOpa.p;
    temp_s0->polyOpa.p = temp_v0_4 + 8;
    temp_v0_4->words.w1 = (u32) &D_060007C8;
    temp_v0_4->words.w0 = 0xDE000000;
```
This is the same as the second one, but with a different second word.

Tidying up and inserting `OPEN_DISPS` and `CLOSE_DISPS`, we end up with
```C
void ObjTree_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s16 sp36 = (f32) thisx->shape.rot.x;
    s16 sp34 = (f32) thisx->shape.rot.z;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_06000680);

    Matrix_InsertRotation(sp36, 0, sp34, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_060007C8);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
```

## RGB macros and bitpacking

TODO: find some examples for this one.

For even more examples, you can consult [the OoT tutorial](https://github.com/zeldaret/oot/blob/master/docs/tutorial/draw_functions.md)

Next: [Data](data.md)
