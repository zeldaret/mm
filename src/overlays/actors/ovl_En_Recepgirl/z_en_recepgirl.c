#include "z_en_recepgirl.h"

#define FLAGS 0x00000009

#define THIS ((EnRecepgirl*)thisx)

void EnRecepgirl_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRecepgirl_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRecepgirl_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRecepgirl_Draw(Actor* thisx, GlobalContext* globalCtx);

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

TexturePtr D_80C106B0[] = { 0x600F8F0, 0x600FCF0, 0x60100F0, 0x600FCF0 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80C106C0[] = {
    ICHAIN_U8(targetMode, 6, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 1000, ICHAIN_STOP),
};

s32 D_80C106C8 = 0;

void func_80C100DC(EnRecepgirl* this);
void func_80C10148(EnRecepgirl* this);
void func_80C1019C(EnRecepgirl* this, GlobalContext* globalCtx);
void func_80C10290(EnRecepgirl* this);
void func_80C102D4(EnRecepgirl* this, GlobalContext* globalCtx);

extern AnimationHeader D_06000968;
extern AnimationHeader D_0600AD98;

extern FlexSkeletonHeader D_06011B60;
extern AnimationHeader D_06001384;
extern AnimationHeader D_06009890;
extern AnimationHeader D_0600A280;

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

void EnRecepgirl_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80C100DC(EnRecepgirl* this) {
    if (this->unk_2AC != 0) {
        this->unk_2AC++;
        if (this->unk_2AC == 4) {
            this->unk_2AC = 0;
        }
    } else if (Rand_ZeroOne() < 0.02f) {
        this->unk_2AC += 1;
    }
}

void func_80C10148(EnRecepgirl* this) {
    if (this->skelAnime.animCurrentSeg == &D_06001384) {
        SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_0600AD98, 5.0f);
    }
    this->actionFunc = func_80C1019C;
}

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

void func_80C10290(EnRecepgirl* this) {
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_0600A280, -4.0f);
    this->actionFunc = func_80C102D4;
}

void func_80C102D4(EnRecepgirl* this, GlobalContext* globalCtx) {
    u8 temp_v0_2;

    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime)) {
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
    } else if ((temp_v0_2 == 5) && (func_80147624(globalCtx) != 0)) {

        if (this->actor.textId == 0x2AD9) {
            Actor_SetSwitchFlag(globalCtx, this->actor.params);
            SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_0600AD98, 10.0f);
            if (gSaveContext.weekEventReg[63] & 0x80) {
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

void EnRecepgirl_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnRecepgirl* this = THIS;
    Vec3s sp30;

    this->actionFunc(this, globalCtx);
    func_800E9250(globalCtx, &this->actor, &this->unk_2AE, &sp30, this->actor.focus.pos);
    func_80C100DC(this);
}

s32 func_80C10558(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnRecepgirl* this = THIS;

    if (limbIndex == 5) {
        rot->x += this->unk_2AE.y;
    }
    return false;
}

void func_80C10590(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
    EnRecepgirl* this = THIS;

    if (limbIndex == 5) {
        Matrix_RotateY(0x400 - this->unk_2AE.x, MTXMODE_APPLY);
        SysMatrix_GetStateTranslationAndScaledX(500.0f, &this->actor.focus.pos);
    }
}

void EnRecepgirl_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnRecepgirl* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, D_80C106B0[this->unk_2AC]);

    func_801343C0(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                  func_80C10558, NULL, func_80C10590, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
