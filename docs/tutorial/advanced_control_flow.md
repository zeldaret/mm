# Advanced control flow

Nice as `EnRecepgirl` was, she was somewhat lacking in complexity. In this document, we'll look at something rather more complicated than any of the functions she had.

Again our example will be taken from a small NPC: this time, `EnMs` (Bean Seller). Most of its functions are even simpler than `EnRecepgirl`'s, and fairly quickly we can get to

<details>
<summary>
    Large code block, click to show.
</summary>

```C
#include "z_en_ms.h"

#define FLAGS 0x00000009

#define THIS ((EnMs*)thisx)

void EnMs_Init(Actor* thisx, PlayState* play);
void EnMs_Destroy(Actor* thisx, PlayState* play);
void EnMs_Update(Actor* thisx, PlayState* play);
void EnMs_Draw(Actor* thisx, PlayState* play);

void func_80952734(EnMs* this, PlayState* play);
void func_809527F8(EnMs* this, PlayState* play);
void func_809529AC(EnMs* this, PlayState* play);
void func_80952A1C(EnMs* this, PlayState* play);

ActorInit En_Ms_InitVars = {
    /**/ ACTOR_EN_MS,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_MS,
    /**/ sizeof(EnMs),
    /**/ EnMs_Init,
    /**/ EnMs_Destroy,
    /**/ EnMs_Update,
    /**/ EnMs_Draw,
};

static ColliderCylinderInitType1 D_80952BA0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 22, 37, 0, { 0, 0, 0 } },
};

static InitChainEntry D_80952BCC[] = {
    ICHAIN_U8(targetMode, 2, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 500, ICHAIN_STOP),
};


extern ColliderCylinderInitType1 D_80952BA0;
extern InitChainEntry D_80952BCC[];

extern AnimationHeader D_060005EC;
extern FlexSkeletonHeader D_06003DC0;

void EnMs_Init(Actor* thisx, PlayState* play) {
    EnMs* this = THIS;

    Actor_ProcessInitChain(thisx, D_80952BCC);
    SkelAnime_InitFlex(play, &this->skelAnime, &D_06003DC0, &D_060005EC, this->jointTable, this->morphTable, 9);
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinderType1(play, &this->collider, &this->actor, &D_80952BA0);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 35.0f);
    Actor_SetScale(&this->actor, 0.015f);
    this->actor.colChkInfo.mass = 0xFF;
    this->actionFunc = func_80952734;
    this->actor.speed = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.gravity = -1.0f;
}

void EnMs_Destroy(Actor* thisx, PlayState* play) {
    EnMs* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void func_80952734(EnMs* this, PlayState* play) {
    s16 temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;

    if (gSaveContext.save.saveInfo.inventory.items[10] == ITEM_NONE) {
        this->actor.textId = 0x92E;
    } else {
        this->actor.textId = 0x932;
    }

    if (Actor_ProcessTalkRequest(&this->actor, &play->state) != 0) {
        this->actionFunc = func_809527F8;
        return;
    }

    if (this->actor.xzDistToPlayer < 90.0f) {
        if (ABS_ALT(temp_v1) < 0x2000) {
            Actor_OfferTalk(&this->actor, play, 90.0f);
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/func_809527F8.s")

void func_809529AC(EnMs* this, PlayState* play) {
    if (Actor_HasParent(&this->actor, play)) {
        this->actor.textId = 0;
        Actor_OfferTalkExchange(&this->actor, play, this->actor.xzDistToPlayer, this->actor.playerHeightRel, 0);
        this->actionFunc = func_80952A1C;
    } else {
        Actor_OfferGetItem(&this->actor, play, 0x35, this->actor.xzDistToPlayer, this->actor.playerHeightRel);
    }
}

void func_80952A1C(EnMs* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        Message_ContinueTextbox(play, 0x936U);
        this->actionFunc = func_809527F8;
    } else {
        Actor_OfferTalkExchange(&this->actor, play, this->actor.xzDistToPlayer, this->actor.playerHeightRel, -1);
    }
}

void EnMs_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnMs* this = THIS;

    Actor_SetFocus(&this->actor, 20.0f);
    this->actor.targetArrowOffset = 500.0f;
    Actor_SetScale(&this->actor, 0.015f);
    SkelAnime_Update(&this->skelAnime);
    this->actionFunc(this, play);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

void EnMs_Draw(Actor* thisx, PlayState* play) {
    EnMs* this = THIS;

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, NULL,
                     NULL, &this->actor);
}

```

</details>

(Skipping any documentation we might have done.) Indeed, this actor is so simple so far that you can see why it wasn't worth using most of it for the rest of the tutorial. `func_809527F8` is a different story, however. We know it's an action function since it's set to the `actionFunc` in `func_80952A1C`. But mips2c gives us

```bash
$ ../mips_to_c/mips_to_c.py asm/non_matchings/overlays/ovl_En_Ms/func_809527F8.s --context ctx.c --gotos-only
```

```C
void func_809527F8(EnMs* this, PlayState* play) {
    u8 temp_v0;
    u8 temp_v0_2;

    temp_v0 = Message_GetState(&play->msgCtx);
    if (temp_v0 != 4) {
        if (temp_v0 != 5) {
            if ((temp_v0 == 6) && (Message_ShouldAdvance(play) != 0)) {
                this->actionFunc = func_80952734;
                return;
            }
            // Duplicate return node #17. Try simplifying control flow for better match
            return;
        }
        if (Message_ShouldAdvance(play) != 0) {
            Message_CloseTextbox(play);
            Actor_OfferGetItem((Actor *) this, play, 0x35, this->actor.xzDistToPlayer, this->actor.playerHeightRel);
            this->actionFunc = func_809529AC;
            return;
        }
        // Duplicate return node #17. Try simplifying control flow for better match
        return;
    }
    if (Message_ShouldAdvance(play) != 0) {
        temp_v0_2 = play->msgCtx.choiceIndex;
        if (temp_v0_2 != 0) {
            if (temp_v0_2 != 1) {

            }
            Audio_PlaySfx_MessageCancel();
            Message_ContinueTextbox(play, 0x934U);
            // Duplicate return node #17. Try simplifying control flow for better match
            return;
        }
        Message_CloseTextbox(play);
        if ((s32) gSaveContext.save.saveInfo.playerData.rupees < 0xA) {
            Audio_PlaySfx(0x4806U);
            Message_ContinueTextbox(play, 0x935U);
            return;
        }
        if ((s32) gSaveContext.save.saveInfo.inventory.ammo[gItemSlots[0xA]] >= 0x14) {
            Audio_PlaySfx(0x4806U);
            Message_ContinueTextbox(play, 0x937U);
            return;
        }
        Audio_PlaySfx_MessageDecide();
        Actor_OfferGetItem((Actor *) this, play, 0x35, 90.0f, 10.0f);
        Rupees_ChangeBy(-0xA);
        this->actionFunc = func_809529AC;
    }
}
```

which is long, messy, and contains some rather nasty-looking control flow, including horrors like

```C
    temp_v0 = Message_GetState(&play->msgCtx);
    if (temp_v0 != 4) {
        if (temp_v0 != 5) {
            if ((temp_v0 == 6) && (Message_ShouldAdvance(play) != 0)) {
                this->actionFunc = func_80952734;
                return;
            }
            // Duplicate return node #17. Try simplifying control flow for better match
            return;
        }
```

If you read the OoT tutorial, you'll know these nested negated ifs all using the same variable are a good indicator that there's a switch. The problem is working out how to write it.

## Goto-only mode

For didactic purposes, we'll use a feature of mips2c called goto-only mode to examine this. *This is not the only way of doing it*, but it is good practice for a beginner to this sort of control flow. Running

```bash
../mips_to_c/mips_to_c.py asm/non_matchings/overlays/ovl_En_Ms/func_809527F8.s --context ctx.c --gotos-only
```

instead will produce

```C
void func_809527F8(EnMs* this, PlayState* play) {
    u8 temp_v0;
    u8 temp_v0_2;

    temp_v0 = Message_GetState(&play->msgCtx);
    if (temp_v0 == 4) {
        goto block_7;
    }
    if (temp_v0 == 5) {
        goto block_5;
    }
    if (temp_v0 != 6) {
        goto block_17;
    }
    if (Message_ShouldAdvance(play) == 0) {
        goto block_17;
    }
    this->actionFunc = func_80952734;
    return;
block_5:
    if (Message_ShouldAdvance(play) == 0) {
        goto block_17;
    }
    Message_CloseTextbox(play);
    Actor_OfferGetItem((Actor *) this, play, 0x35, this->actor.xzDistToPlayer, this->actor.playerHeightRel);
    this->actionFunc = func_809529AC;
    return;
block_7:
    if (Message_ShouldAdvance(play) == 0) {
        goto block_17;
    }
    temp_v0_2 = play->msgCtx.choiceIndex;
    if (temp_v0_2 == 0) {
        goto block_11;
    }
    if (temp_v0_2 == 1) {
        goto block_16;
    }
    goto block_16;
block_11:
    Message_CloseTextbox(play);
    if ((s32) gSaveContext.save.saveInfo.playerData.rupees >= 0xA) {
        goto block_13;
    }
    Audio_PlaySfx(0x4806U);
    Message_ContinueTextbox(play, 0x935U);
    return;
block_13:
    if ((s32) gSaveContext.save.saveInfo.inventory.ammo[gItemSlots[0xA]] < 0x14) {
        goto block_15;
    }
    Audio_PlaySfx(0x4806U);
    Message_ContinueTextbox(play, 0x937U);
    return;
block_15:
    Audio_PlaySfx_MessageDecide();
    Actor_OfferGetItem((Actor *) this, play, 0x35, 90.0f, 10.0f);
    Rupees_ChangeBy(-0xA);
    this->actionFunc = func_809529AC;
    return;
block_16:
    Audio_PlaySfx_MessageCancel();
    Message_ContinueTextbox(play, 0x934U);
block_17:
    return;
}
```

which in many ways looks worse: you can see why the use of gotos in code is strongly discouraged. However, if you throw this in `diff.py`, you'll find it's rather closer than you'd have thought. Goto-only mode has the advantages that

- code is always in the right order: mips2c has not had to reorder anything to get the ifs to work out
- it is often possible to get quite close with gotos, then start removing them, checking the matching status at each point. This is usually easier than trying to puzzle out the way it's trying to jump out of an `if ( || )` or similar.
- if you're trying to keep track of where you are in the code, the gotos mean that it is closer to the assembly in the first place.

## Eliminating the gotos

The simplest sort of block label to eliminate is one that is only used once, and where the corresponding goto jumps over a simple block of code with no extra internal control flow structure. There are two obvious examples of this here, the first being

```C
    if ((s32) gSaveContext.save.saveInfo.playerData.rupees >= 0xA) {
        goto block_13;
    }
    Audio_PlaySfx(0x4806U);
    Message_ContinueTextbox(play, 0x935U);
    return;
block_13:
```

Currently, this says to jump over the code block `Audio_PlaySfx...` if the condition in the if is satisfied. In non-goto terms, this means that the block should be run if the condition is *not* satisfied. This also illustrates a general property of goto-only mode: you have to reverse the senses of all of the ifs. Therefore the appropriate approach is to swap the if round, put the code block inside, and remove the goto and the label:

```C
    if (gSaveContext.save.saveInfo.playerData.rupees < 0xA) {
        Audio_PlaySfx(0x4806U);
        Message_ContinueTextbox(play, 0x935U);
        return;
    }
```

Likewise, one can do this with `block_15`.

If you examine appropriate part of the diff, you will usually find that such eliminations make no, or very little, difference to the compiled code.

```C
void func_809527F8(EnMs* this, PlayState* play) {
    u8 temp_v0;
    u8 temp_v0_2;

    temp_v0 = Message_GetState(&play->msgCtx);
    if (temp_v0 == 4) {
        goto block_7;
    }
    if (temp_v0 == 5) {
        goto block_5;
    }
    if (temp_v0 != 6) {
        goto block_17;
    }
    if (Message_ShouldAdvance(play) == 0) {
        goto block_17;
    }
    this->actionFunc = func_80952734;
    return;
block_5:
    if (Message_ShouldAdvance(play) == 0) {
        goto block_17;
    }
    Message_CloseTextbox(play);
    Actor_OfferGetItem((Actor *) this, play, 0x35, this->actor.xzDistToPlayer, this->actor.playerHeightRel);
    this->actionFunc = func_809529AC;
    return;
block_7:
    if (Message_ShouldAdvance(play) == 0) {
        goto block_17;
    }
    temp_v0_2 = play->msgCtx.choiceIndex;
    if (temp_v0_2 == 0) {
        goto block_11;
    }
    if (temp_v0_2 == 1) {
        goto block_16;
    }
    goto block_16;
block_11:
    Message_CloseTextbox(play);
    
    if (gSaveContext.save.saveInfo.playerData.rupees < 0xA) {
        Audio_PlaySfx(0x4806U);
        Message_ContinueTextbox(play, 0x935U);
        return;
    }
    if (gSaveContext.save.saveInfo.inventory.ammo[gItemSlots[0xA]] >= 0x14) {
        Audio_PlaySfx(0x4806U);
        Message_ContinueTextbox(play, 0x937U);
        return;
    }

    Audio_PlaySfx_MessageDecide();
    Actor_OfferGetItem((Actor *) this, play, 0x35, 90.0f, 10.0f);
    Rupees_ChangeBy(-0xA);
    this->actionFunc = func_809529AC;
    return;
block_16:
    Audio_PlaySfx_MessageCancel();
    Message_ContinueTextbox(play, 0x934U);
block_17:
    return;
}
```

We can't apply this rule any more, so we need to move on to the next: `block_17` just contains a `return`. So we can replace it by `return` everywhere it appears.

```C
void func_809527F8(EnMs* this, PlayState* play) {
    u8 temp_v0;
    u8 temp_v0_2;

    temp_v0 = Message_GetState(&play->msgCtx);
    if (temp_v0 == 4) {
        goto block_7;
    }
    if (temp_v0 == 5) {
        goto block_5;
    }
    if (temp_v0 != 6) {
        return;
    }
    if (Message_ShouldAdvance(play) == 0) {
        return;
    }
    this->actionFunc = func_80952734;
    return;
block_5:
    if (Message_ShouldAdvance(play) == 0) {
        return;
    }
    Message_CloseTextbox(play);
    Actor_OfferGetItem((Actor *) this, play, 0x35, this->actor.xzDistToPlayer, this->actor.playerHeightRel);
    this->actionFunc = func_809529AC;
    return;
block_7:
    if (Message_ShouldAdvance(play) == 0) {
        return;
    }
    temp_v0_2 = play->msgCtx.choiceIndex;
    if (temp_v0_2 == 0) {
        goto block_11;
    }
    if (temp_v0_2 == 1) {
        goto block_16;
    }
    goto block_16;
block_11:
    Message_CloseTextbox(play);
    
    if (gSaveContext.save.saveInfo.playerData.rupees < 0xA) {
        Audio_PlaySfx(0x4806U);
        Message_ContinueTextbox(play, 0x935U);
        return;
    }
    if (gSaveContext.save.saveInfo.inventory.ammo[gItemSlots[0xA]] >= 0x14) {
        Audio_PlaySfx(0x4806U);
        Message_ContinueTextbox(play, 0x937U);
        return;
    }

    Audio_PlaySfx_MessageDecide();
    Actor_OfferGetItem((Actor *) this, play, 0x35, 90.0f, 10.0f);
    Rupees_ChangeBy(-0xA);
    this->actionFunc = func_809529AC;
    return;
block_16:
    Audio_PlaySfx_MessageCancel();
    Message_ContinueTextbox(play, 0x934U);   
}
```

Our next rule is about non-crossing blocks. If two code blocks do not contain any jumps between them, we can treat them separately. This is *almost* true for the code after `block_7`, were it not for the returns; of course returns are a special case because they can be used to be escape from a function at any point. This doesn't get us very far in this case, unfortunately, but it *does* tell us we can look at the second half of the function separately.

Now let's start thinking about switches. A good indicator of a switch in goto-only mode is something like

```C
    temp_v0_2 = play->msgCtx.choiceIndex;
    if (temp_v0_2 == 0) {
        goto block_11;
    }
    if (temp_v0_2 == 1) {
        goto block_16;
    }
    goto block_16;
```

because

- there are multiple ifs that are simple numeric comparisons of the same argument
- the goto blocks are in the same order as the ifs
- there is one last goto at the end that triggers if none of the ifs does: this sounds an awful lot like a `default`!

So let us rewrite the entire second half as a switch:

```C
    switch (play->msgCtx.choiceIndex) {
        case 0:
            Message_CloseTextbox(play);
            
            if (gSaveContext.save.saveInfo.playerData.rupees < 0xA) {
                Audio_PlaySfx(0x4806U);
                Message_ContinueTextbox(play, 0x935U);
                return;
            }
            if (gSaveContext.save.saveInfo.inventory.ammo[gItemSlots[0xA]] >= 0x14) {
                Audio_PlaySfx(0x4806U);
                Message_ContinueTextbox(play, 0x937U);
                return;
            }

            Audio_PlaySfx_MessageDecide();
            Actor_OfferGetItem((Actor *) this, play, 0x35, 90.0f, 10.0f);
            Rupees_ChangeBy(-0xA);
            this->actionFunc = func_809529AC;
            return;
            break;

        case 1:
        default:
            Audio_PlaySfx_MessageCancel();
            Message_ContinueTextbox(play, 0x934U);
            break;
    }
```

There's a couple of other obvious things here:

- the last `return` in `case 0` is unnecessary since there is no other code after the switch, so breaking is equivalent to the return`
- a common pattern everywhere, a sequence of ifs with returns as the last thing inside is the same as an if-else chain, so we can rewrite these as

```C
    switch (play->msgCtx.choiceIndex) {
        case 0:
            Message_CloseTextbox(play);
            
            if (gSaveContext.save.saveInfo.playerData.rupees < 0xA) {
                Audio_PlaySfx(0x4806U);
                Message_ContinueTextbox(play, 0x935U);
            } else if (gSaveContext.save.saveInfo.inventory.ammo[gItemSlots[0xA]] >= 0x14) {
                Audio_PlaySfx(0x4806U);
                Message_ContinueTextbox(play, 0x937U);
            } else {
                Audio_PlaySfx_MessageDecide();
                Actor_OfferGetItem((Actor *) this, play, 0x35, 90.0f, 10.0f);
                Rupees_ChangeBy(-0xA);
                this->actionFunc = func_809529AC;
            }
            break;

        case 1:
        default:
            Audio_PlaySfx_MessageCancel();
            Message_ContinueTextbox(play, 0x934U);
            break;
    }
```

Well, at least the bottom half looks respectable now. Again, there is no code after the switch, so the next thing up, namely

```C
    if (Message_ShouldAdvance(play) == 0) {
        return;
    }
```

can be swapped round and made to wrap the switch. This leaves us with

```C
void func_809527F8(EnMs* this, PlayState* play) {
    u8 temp_v0;

    temp_v0 = Message_GetState(&play->msgCtx);
    if (temp_v0 == 4) {
        goto block_7;
    }
    if (temp_v0 == 5) {
        goto block_5;
    }
    if (temp_v0 != 6) {
        return;
    }
    if (Message_ShouldAdvance(play) == 0) {
        return;
    }
    this->actionFunc = func_80952734;
    return;
block_5:
    if (Message_ShouldAdvance(play) == 0) {
        return;
    }
    Message_CloseTextbox(play);
    Actor_OfferGetItem((Actor *) this, play, 0x35, this->actor.xzDistToPlayer, this->actor.playerHeightRel);
    this->actionFunc = func_809529AC;
    return;
block_7:
    if (Message_ShouldAdvance(play) != 0) {
        switch (play->msgCtx.choiceIndex) {
            case 0:
                Message_CloseTextbox(play);
                
                if (gSaveContext.save.saveInfo.playerData.rupees < 0xA) {
                    Audio_PlaySfx(0x4806U);
                    Message_ContinueTextbox(play, 0x935U);
                } else if (gSaveContext.save.saveInfo.inventory.ammo[gItemSlots[0xA]] >= 0x14) {
                    Audio_PlaySfx(0x4806U);
                    Message_ContinueTextbox(play, 0x937U);
                } else {
                    Audio_PlaySfx_MessageDecide();
                    Actor_OfferGetItem((Actor *) this, play, 0x35, 90.0f, 10.0f);
                    Rupees_ChangeBy(-0xA);
                    this->actionFunc = func_809529AC;
                }
                break;

            case 1:
            default:
                Audio_PlaySfx_MessageCancel();
                Message_ContinueTextbox(play, 0x934U);
                break;
        }
    }
}
```

Now, the top of the function also looks like a switch:

```C
    temp_v0 = Message_GetState(&play->msgCtx);
    if (temp_v0 == 4) {
        goto block_7;
    }
    if (temp_v0 == 5) {
        goto block_5;
    }
    if (temp_v0 != 6) {
        return;
    }
```

Interestingly, this time the blocks are the other way round. Also, the last statement is a `!=` rather than an `==`: this should be the default this time. The code order takes priority over the check order, because the compiler likes to put those in numerical order. There will be cases 4,5,6, but in the order 6,5,4, because that's how the code ordering goes. Also, notice that every case returns at the end: this means there's nothing else in the function after this switch, so everything after `block_7` is actually part of `case 4`.

Putting all this together, we write down a function with no gotos in it:

```C
void func_809527F8(EnMs* this, PlayState* play) {
    switch (Message_GetState(&play->msgCtx)) {
        case 6:
            this->actionFunc = func_80952734;
            break;

        case 5:
            if (Message_ShouldAdvance(play) == 0) {
                return;
            }
            Message_CloseTextbox(play);
            Actor_OfferGetItem((Actor *) this, play, 0x35, this->actor.xzDistToPlayer, this->actor.playerHeightRel);
            this->actionFunc = func_809529AC;
            break;

        case 4:
            if (Message_ShouldAdvance(play) != 0) {
                switch (play->msgCtx.choiceIndex) {
                    case 0:
                        Message_CloseTextbox(play);

                        if (gSaveContext.save.saveInfo.playerData.rupees < 0xA) {
                            Audio_PlaySfx(0x4806U);
                            Message_ContinueTextbox(play, 0x935U);
                        } else if (gSaveContext.save.saveInfo.inventory.ammo[gItemSlots[0xA]] >= 0x14) {
                            Audio_PlaySfx(0x4806U);
                            Message_ContinueTextbox(play, 0x937U);
                        } else {
                            Audio_PlaySfx_MessageDecide();
                            Actor_OfferGetItem((Actor *) this, play, 0x35, 90.0f, 10.0f);
                            Rupees_ChangeBy(-0xA);
                            this->actionFunc = func_809529AC;
                        }
                        break;

                    case 1:
                    default:
                        Audio_PlaySfx_MessageCancel();
                        Message_ContinueTextbox(play, 0x934U);
                        break;
                }
            }
            break;

        default:
            break;
    }
}
```

Lastly, we can simplify `case 5` to replace the return in the if by the rest of the code, and we end up with

```C
void func_809527F8(EnMs* this, PlayState* play) {
    switch (Message_GetState(&play->msgCtx)) {
        case 6:
            this->actionFunc = func_80952734;
            break;

        case 5:
            if (Message_ShouldAdvance(play) != 0) {
                Message_CloseTextbox(play);
                Actor_OfferGetItem((Actor *) this, play, 0x35, this->actor.xzDistToPlayer, this->actor.playerHeightRel);
                this->actionFunc = func_809529AC;
            }
            break;

        case 4:
            if (Message_ShouldAdvance(play) != 0) {
                switch (play->msgCtx.choiceIndex) {
                    case 0:
                        Message_CloseTextbox(play);

                        if (gSaveContext.save.saveInfo.playerData.rupees < 0xA) {
                            Audio_PlaySfx(0x4806U);
                            Message_ContinueTextbox(play, 0x935U);
                        } else if (gSaveContext.save.saveInfo.inventory.ammo[gItemSlots[0xA]] >= 0x14) {
                            Audio_PlaySfx(0x4806U);
                            Message_ContinueTextbox(play, 0x937U);
                        } else {
                            Audio_PlaySfx_MessageDecide();
                            Actor_OfferGetItem((Actor *) this, play, 0x35, 90.0f, 10.0f);
                            Rupees_ChangeBy(-0xA);
                            this->actionFunc = func_809529AC;
                        }
                        break;

                    case 1:
                    default:
                        Audio_PlaySfx_MessageCancel();
                        Message_ContinueTextbox(play, 0x934U);
                        break;
                }
            }
            break;

        default:
            break;
    }
}
```

And this matches!

We will not document this now, although even with so few function named it seems pretty clear that it's to do with buying beans (and indeed, Magic Beans cost 10 Rupees and have Get Item ID `0x35`) You might like to try to match this function without using goto-only mode, to compare. It is also an interesting exercise to see what each elimination does to the diff: sometimes it will stray surprisingly far for a small change.
