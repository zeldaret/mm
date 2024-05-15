# `diff.py` and the permuter

This document is intended as a step-by-step demonstration of matching a reasonably complex function using the diff script `diff.py` and the decomp permuter, both included in the repo. For general information on both see [the tools documentation](../tools.md).

Until such time as someone finds a suitable function, you can look at the OoT tutorial: [here for diff.py](https://github.com/zeldaret/oot/blob/main/docs/tutorial/beginning_decomp.md#diff) and [here for the permuter](https://github.com/zeldaret/oot/blob/main/docs/tutorial/other_functions.md#the-permuter).


<!-- 
The following is left here to give a rough idea of what the diff script doc could look like.


This gives the following:

<details>
<summary>
    Large image, click to show.
</summary>

![Init diff 1](images/init_diff1.png)
</details>

The code we want is on the left, current code on the right. To spot where the function ends, either look for where stuff is added and subtracted from the stack pointer in successive lines, or for a
```MIPS
jr      ra
nop
```

The colours mean the following:

- White/gray is matching lines
- Red is lines missing
- Green is extra lines
- Blue denotes significant differences in instructions, be they just numerical ones, or whole instructions
- Yellow/Gold denotes that instructions are correct but register usage is wrong
- Other colors are used to distinguish incorrectly used registers or stack variables, to make it easy to follow where they are used.
- The colored arrows denote branching. An arrow of one color on the right leads to the arrow of the same color on the left.

Obviously we want to make the whole thing white. This is the tricky bit: you have to have the imagination to try different things until you get the diff to match. You learn these with experience.

Generally, the order of what to fix should be:

1. Control flow (conditionals, where branches go)
2. Instruction ordering and type (functions cannot change order, which is a useful indicator)
3. Regalloc (register allocation) differences
4. Stack differences

(It is this order because the things that happen earlier can influence the things that happen later.)

You can keep the diff open in the terminal, and it will refresh when the C file (but not the H file) is changed with these settings.

In this case, we see that various branches are happening in the wrong place. Here I fear experience is necessary: notice that the function has three blocks that look quite similar, and three separate conditionals that depend on the same variable. This is a good indicator of a switch. Changing the function to use a switch,

```C
void EnJj_Init(Actor* thisx, PlayState* play) {
    EnJj* this = THIS;

    s32 sp4C;
    s16 temp_v0;

    sp4C = 0;
    Actor_ProcessInitChain(&this->dyna.actor, D_80A88CE0);
    ActorShape_Init(&this->dyna.actor.shape, 0.0f, NULL, 0.0f);
    temp_v0 = this->dyna.actor.params;

    switch (temp_v0) {
        case -1:
            SkelAnime_InitFlex(play, &this->skelAnime, &D_0600B9A8, &D_06001F4C, this->jointTable,
                               this->morphTable, 22);
            Animation_PlayLoop(&this->skelAnime, &D_06001F4C);
            this->unk_30A = 0;
            this->unk_30E = 0;
            this->unk_30F = 0;
            this->unk_310 = 0;
            this->unk_311 = 0;
            if ((gSaveContext.eventChkInf[3] & 0x400) != 0) {
                func_80A87800(this, func_80A87BEC);
            } else {
                func_80A87800(this, func_80A87C30);
            }
            this->childActor = Actor_SpawnAsChild(
                &play->actorCtx, &this->dyna.actor, play, ACTOR_EN_JJ, this->dyna.actor.world.pos.x - 10.0f,
                this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, 0, this->dyna.actor.world.rot.y, 0, 0);
            DynaPolyActor_Init(&this->dyna, 0);
            CollisionHeader_GetVirtual(&D_06000A1C, &sp4C);
            this->dyna.bgId =
                DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, sp4C);
            Collider_InitCylinder(play, &this->collider);
            Collider_SetCylinder(play, &this->collider, &this->dyna.actor, &D_80A88CB4);
            this->dyna.actor.colChkInfo.mass = 0xFF;
            break;
        case 0:
            DynaPolyActor_Init(&this->dyna, 0);
            CollisionHeader_GetVirtual(&D_06001830, &sp4C);
            // temp_a1_2 = &play->colCtx.dyna;
            // sp44 = temp_a1_2;
            this->dyna.bgId =
                DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, sp4C);
            func_8003ECA8(play, &play->colCtx.dyna, this->dyna.bgId);
            this->dyna.actor.update = func_80A87F44;
            this->dyna.actor.draw = NULL;
            Actor_SetScale(&this->dyna.actor, 0.087f);
            break;
        case 1:
            DynaPolyActor_Init(&this->dyna, 0);
            CollisionHeader_GetVirtual(&D_0600BA8C, &sp4C);
            this->dyna.bgId =
                DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, sp4C);
            this->dyna.actor.update = func_80A87F44;
            this->dyna.actor.draw = NULL;
            Actor_SetScale(&this->dyna.actor, 0.087f);
            break;
    }
}
```

we see that the diff is nearly correct (note that `-3` lets you compare current with previous):

<details>
<summary>
    Large image, click to show.
</summary>

![Init diff 2](images/init_diff2.png)
</details>

except we still have some stack issues. Now that `temp_v0` is only used once, it looks fake. Eliminating it actually seems to make the stack worse. To fix this, we employ something that we have evidence that the developers did: namely, we make a copy of `play` (the theory is that they actually used `gameState` as an argument of the main 4 functions, just like we used `Actor* thisx` as the first argument.) The quick way to do this is to change the top of the function to
```C
void EnJj_Init(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnJj* this = THIS;
	...
```

It turns out that this is enough to completely fix the diff:

![Init diff 2](images/init_diff3top.png)
(last two edits, only top shown for brevity)

Everything *looks* fine, but we only know for sure when we run `make`. Thankfully doing so gives
```
zelda_ocarina_mq_dbg.z64: OK
```

which is either a sense of triumph or relief depending on how long you've spent on a function. -->

