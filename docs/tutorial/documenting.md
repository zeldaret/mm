# Documenting

Up: [Contents](contents.md)
Previous: [Data](data.md)

Decompilation is only the first step: since the point of this project is to understand the game better than ever before, the code needs documentation. In this document, we will go through the basic stuff that it's good to do for any actor: we will not try to understand every single thing the actor does in full detail, but try to name the functions and variables usefully for a full documentation pass later to take advantage of.

It is helpful to document the functions and variables in the actor before you Pull Request it. The aim is to provide code that is sufficiently clear to be self-documenting, but it is worth leaving a comment on anything you find obscure or confusing. (Pull Request reviews will let you know if you are leaving too many comments.) Useful things to do documentation-wise:

- Name all (or most) of the functions.
- Name all the variables in the actor struct.
- Create enums for params, and any other numbers that would benefit from that sort of clarity.

You can test things using the practice rom for a retail version (watches and memory view is especially helpful), as well as the generated rom with Project 64 and something like Spectrum.

If you want to use `diff.py` after renaming anything, particularly functions, remember to rerun `make diff-init` so it can use the correct symbols.

Finally, *if you are not sure what something does, either ask or leave it unnamed: it will be less confusing later if things are unnamed than if they are wrongly named*


## Renaming things

Because MM needs to regenerate the assembly code, it is necessary to tell the disassembler the names of functions and variables, so it knows what symbols to assign in the code. This is done via `functions.txt` and `variables.txt`. The best way to rename functions and symbols is via global rename in an editor like VSCode. The next best way is to run `tools/rename_sym.sh`. You should be careful with this script: it has no error-checking!

Renaming symbols in theory requires re-disassembly. This can often be avoided in the case of functions by running `tools/rename_global_asm.py`, which will rename any individual functions' assembly files with the wrong names, so that the `GLOBAL_ASM`s can spot them. Renaming variables *may* require redisassembly (and if fake symbols are removed, it *will*).


## EnRecepgirl

Currently, the file looks like this:
<details>
<summary>
Large code block, click to show
</summary>

```C
#include "z_en_recepgirl.h"

#define FLAGS 0x00000009

#define THIS ((EnRecepgirl*)thisx)

void EnRecepgirl_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRecepgirl_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRecepgirl_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRecepgirl_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C10148(EnRecepgirl* this);
void func_80C1019C(EnRecepgirl* this, GlobalContext* globalCtx);
void func_80C10290(EnRecepgirl* this);
void func_80C102D4(EnRecepgirl * this, GlobalContext * globalCtx);

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

extern void* D_0600F8F0;
extern void* D_0600FCF0;
extern void* D_060100F0;

static void* D_80C106B0[4] = { &D_0600F8F0, &D_0600FCF0, &D_060100F0, &D_0600FCF0 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80C106C0[] = {
    ICHAIN_U8(targetMode, 6, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 1000, ICHAIN_STOP),
};

static s32 D_80C106C8 = 0;

extern AnimationHeader D_06000968;
extern AnimationHeader D_06001384;
extern AnimationHeader D_06009890;
extern AnimationHeader D_0600A280;
extern AnimationHeader D_0600AD98;
extern FlexSkeletonHeader D_06011B60;


// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/EnRecepgirl_Init.s")
void EnRecepgirl_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnRecepgirl* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->actor, D_80C106C0);
    ActorShape_Init(&this->actor.shape, -60.0f, NULL, 0.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06011B60, &D_06009890, this->jointTable, this->morphTable, 24);

    if (D_80C106C8 == 0) {
    for (i = 0; i < 4; i++) {
        D_80C106B0[i] = Lib_SegmentedToVirtual(D_80C106B0[i]);
    }
        D_80C106C8 = 1;
    }

    this->unk_2AC = 2;

    if (Flags_GetSwitch(globalCtx, this->actor.params)) {
        this->actor.textId = 0x2ADC;
    } else {
        this->actor.textId = 0x2AD9;
    }

    func_80C10148(this);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/EnRecepgirl_Destroy.s")
void EnRecepgirl_Destroy(Actor* thisx, GlobalContext* globalCtx) {

}

// void func_80C100DC(EnRecepgirl * this);
// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/func_80C100DC.s")
void func_80C100DC(EnRecepgirl *this) {
    if (this->unk_2AC != 0) {
        this->unk_2AC++;
        if (this->unk_2AC == 4) {
            this->unk_2AC = 0;
            return;
        }
        return;
    }
    if (Rand_ZeroOne() < 0.02f) {
        this->unk_2AC++;
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/func_80C10148.s")
void func_80C10148(EnRecepgirl *this) {
    if (this->skelAnime.animCurrentSeg == &D_06001384) {
        SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_0600AD98, 5.0f);
    }
    this->actionFunc = func_80C1019C;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/func_80C1019C.s")
void func_80C1019C(EnRecepgirl* this, GlobalContext* globalCtx) {
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        if (this->skelAnime.animCurrentSeg == &D_0600A280) {
            SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_0600AD98, 5.0f);
        } else {
            SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06009890, -4.0f);
        }
    }

    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        func_80C10290(this);
    } else if (Actor_IsActorFacingLink(&this->actor, 0x2000)) {
        func_800B8614(&this->actor, globalCtx, 60.0f);
        if (Player_GetMask(globalCtx) == 2) {
            this->actor.textId = 0x2367;
        } else if (Flags_GetSwitch(globalCtx, this->actor.params)) {
            this->actor.textId = 0x2ADC;
        } else {
            this->actor.textId = 0x2AD9;
        }
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/func_80C10290.s")
void func_80C10290(EnRecepgirl *this) {
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_0600A280, -4.0f);
    this->actionFunc = func_80C102D4;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/func_80C102D4.s")
void func_80C102D4(EnRecepgirl *this, GlobalContext *globalCtx) {
    u8 temp_v0_2;

    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        if (this->skelAnime.animCurrentSeg == &D_0600A280) {
            SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_06001384);
        } else if (this->skelAnime.animCurrentSeg == &D_0600AD98) {
            if (this->actor.textId == 0x2ADA) {
                SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_06000968, 10.0f);
            } else {
                SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06009890, 10.0f);
            }
        } else if (this->actor.textId == 0x2ADA) {
            SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06009890, 10.0f);
        } else {
            SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_0600A280, -4.0f);
        }
    }

    temp_v0_2 = func_80152498(&globalCtx->msgCtx);
    if (temp_v0_2 == 2) {
        this->actor.textId = 0x2ADC;
        func_80C10148(this);
        return;
    }
    
    if ((temp_v0_2 == 5) && (func_80147624(globalCtx) != 0)) {
        if (this->actor.textId == 0x2AD9) {
            Actor_SetSwitchFlag(globalCtx, this->actor.params);
            SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_0600AD98, 10.0f);
            if ((gSaveContext.weekEventReg[63] & 0x80)) {
                this->actor.textId = 0x2ADF;
            } else {
                this->actor.textId = 0x2ADA;
            }
        } else if (this->actor.textId == 0x2ADC) {
            SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_0600AD98, 10.0f);
            this->actor.textId = 0x2ADD;
        } else {
            SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_06000968, 10.0f);
            if (this->actor.textId == 0x2ADD) {
                this->actor.textId = 0x2ADE;
            } else if (this->actor.textId == 0x2ADA) {
                this->actor.textId = 0x2ADB;
            } else {
                this->actor.textId = 0x2AE0;
            }
        }
        func_80151938(globalCtx, this->actor.textId);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/EnRecepgirl_Update.s")
void EnRecepgirl_Update(Actor *thisx, GlobalContext *globalCtx) {
    s32 pad;
    EnRecepgirl* this = THIS;
    Vec3s sp30;

    this->actionFunc(this, globalCtx);
    func_800E9250(globalCtx, &this->actor, &this->unk_2AE, &sp30, this->actor.focus.pos);
    func_80C100DC(this);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/func_80C10558.s")
s32 func_80C10558(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *thisx) {
    EnRecepgirl* this = THIS;

    if (limbIndex == 5) {
        rot->x += this->unk_2AE.y;
    }
    return false;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/func_80C10590.s")
void func_80C10590(GlobalContext *globalCtx, s32 limbIndex, Actor *thisx) {
    EnRecepgirl* this = THIS;

    if (limbIndex == 5) {
        Matrix_RotateY(0x400 - this->unk_2AE.x, MTXMODE_APPLY);
        SysMatrix_GetStateTranslationAndScaledX(500.0f, &this->actor.focus.pos);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/EnRecepgirl_Draw.s")
void EnRecepgirl_Draw(Actor *thisx, GlobalContext *globalCtx) {
    EnRecepgirl* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, D_80C106B0[this->unk_2AC]);

    func_801343C0(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, func_80C10558, NULL, func_80C10590, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

```
</details>

(We can delete the `GLOBAL_ASM` lines now.)

The worst part of documentation is finding somewhere to start. We have a decent place to start here, though, in that we already know the function (or rather, the use) of a couple of the functions, namely the LimbDraws. So we can rename `func_80C10558` to `EnRecepgirl_OverrideLimbDraw` and `func_80C10590` to `EnRecepgirl_UnkLimbDraw`.



Next: [The merging process](merging.md)