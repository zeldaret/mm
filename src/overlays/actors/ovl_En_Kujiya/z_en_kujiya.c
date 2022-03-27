/*
 * File: z_en_kujiya.c
 * Overlay: ovl_En_Kujiya
 * Description: Clock Town - Lottery Shop
 */

#include "z_en_kujiya.h"
#include "objects/object_kujiya/object_kujiya.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_8000000)

#define THIS ((EnKujiya*)thisx)

void EnKujiya_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKujiya_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKujiya_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKujiya_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BB09A8(EnKujiya* this);
void func_80BB09BC(EnKujiya* this, GlobalContext* globalCtx);
void func_80BB0E44(EnKujiya* this);
void func_80BB0E58(EnKujiya* this, GlobalContext* globalCtx);
void func_80BB0F24(EnKujiya* this);
void func_80BB0F38(EnKujiya* this, GlobalContext* globalCtx);
void func_80BB0F94(EnKujiya* this);
void func_80BB0FA8(EnKujiya* this, GlobalContext* globalCtx);
s32 func_80BB0FF8(void);
void func_80BB1088(void);
void func_80BB10F8(void);
void func_80BB1168(EnKujiya* this);
void func_80BB1180(EnKujiya* this, GlobalContext* globalCtx);
void func_80BB1250(EnKujiya* this);
void func_80BB1268(EnKujiya* this, GlobalContext* globalCtx);

const ActorInit En_Kujiya_InitVars = {
    ACTOR_EN_KUJIYA,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_KUJIYA,
    sizeof(EnKujiya),
    (ActorFunc)EnKujiya_Init,
    (ActorFunc)EnKujiya_Destroy,
    (ActorFunc)EnKujiya_Update,
    (ActorFunc)EnKujiya_Draw,
};

#define CHECK_LOTTERY_NUMBERS                                                     \
    (((u32)((void)0, gSaveContext.save.lotteryCodes[CURRENT_DAY - 1][0]) ==       \
      ((((void)0, gSaveContext.save.lotteryCodeGuess & 0xFFFF) & 0xF00) >> 8)) && \
     ((u32)((void)0, gSaveContext.save.lotteryCodes[CURRENT_DAY - 1][1]) ==       \
      ((((void)0, gSaveContext.save.lotteryCodeGuess & 0xFFFF) & 0xF0) >> 4)) &&  \
     ((u32)((void)0, gSaveContext.save.lotteryCodes[CURRENT_DAY - 1][2]) ==       \
      (((void)0, gSaveContext.save.lotteryCodeGuess & 0xFFFF) & 0xF)))

void EnKujiya_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnKujiya* this = THIS;

    Actor_SetScale(&this->actor, 0.1f);

    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actor.targetMode = 6;

    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 30.0f;

    if (func_80BB0FF8() && (gSaveContext.save.time >= CLOCK_TIME(6, 0)) &&
        (gSaveContext.save.time < CLOCK_TIME(18, 0))) {
        this->actor.shape.rot.y = 0;
    } else {
        this->actor.shape.rot.y = 0x7555;
    }
    func_80BB09A8(this);
}

void EnKujiya_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80BB09A8(EnKujiya* this) {
    this->actionFunc = func_80BB09BC;
}

void func_80BB09BC(EnKujiya* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        if ((gSaveContext.save.time >= CLOCK_TIME(6, 0)) && (gSaveContext.save.time < CLOCK_TIME(18, 0))) {
            if (func_80BB0FF8()) {
                Message_StartTextbox(globalCtx, 0x2B61, &this->actor);
                this->unk_14A = 0x2B61;
            } else {
                Message_StartTextbox(globalCtx, 0x2B5C, &this->actor);
                this->unk_14A = 0x2B5C;
            }
        } else if (func_80BB0FF8()) {
            Message_StartTextbox(globalCtx, 0x2B64, &this->actor);
            this->unk_14A = 0x2B64;
        } else {
            Message_StartTextbox(globalCtx, 0x2B63, &this->actor);
            this->unk_14A = 0x2B63;
        }
        func_80BB0E44(this);
    } else if ((gSaveContext.save.time >= CLOCK_TIME(18, 0)) && func_80BB0FF8() && (this->actor.shape.rot.y == 0)) {
        func_80BB1168(this);
    } else if (this->actor.xzDistToPlayer < 100.0f) {
        func_800B8614(&this->actor, globalCtx, 100.0f);
    }
}

void func_80BB0B28(EnKujiya* this, GlobalContext* globalCtx) {
    if (Message_ShouldAdvance(globalCtx)) {
        if (globalCtx->msgCtx.choiceIndex == 0) {
            if (gSaveContext.save.playerData.rupees < 10) {
                play_sound(NA_SE_SY_ERROR);
                Message_StartTextbox(globalCtx, 0x2B62, &this->actor);
                this->unk_14A = 0x2B62;
            } else {
                func_8019F208();
                func_801159EC(-10);
                Message_StartTextbox(globalCtx, 0x2B5F, &this->actor);
                this->unk_14A = 0x2B5F;
            }
        } else {
            func_8019F230();
            Message_StartTextbox(globalCtx, 0x2B5E, &this->actor);
            this->unk_14A = 0x2B5E;
        }
    }
}

void func_80BB0BF8(EnKujiya* this, GlobalContext* globalCtx) {
    u32 lotteryCode;
    s8 digit1;
    s8 digit2;
    s8 digit3;
    s8* lotteryCodes;

    if (this->unk_14A == 0x2B65) {
        if (this->unk_148 != 0) {
            this->unk_148--;
            return;
        }
    }

    if (Message_ShouldAdvance(globalCtx)) {
        switch (this->unk_14A) {
            case 0x2B5C:
                Message_StartTextbox(globalCtx, 0x2B5D, &this->actor);
                this->unk_14A = 0x2B5D;
                break;

            case 0x2B60:
                func_80BB1088();
                func_801477B4(globalCtx);
                func_80BB1250(this);
                break;

            case 0x2B64:
                func_80BB10F8();
                this->unk_148 = 0x14;
                Message_StartTextbox(globalCtx, 0x2B65, &this->actor);
                this->unk_14A = 0x2B65;
                break;

            case 0x2B65:
                if (CHECK_LOTTERY_NUMBERS) {
                    Message_StartTextbox(globalCtx, 0x2B66, &this->actor);
                    this->unk_14A = 0x2B66;
                } else {
                    Message_StartTextbox(globalCtx, 0x2B67, &this->actor);
                    this->unk_14A = 0x2B67;
                }
                break;

            case 0x2B66:
                func_801477B4(globalCtx);
                func_80BB0F24(this);
                func_80BB0F38(this, globalCtx);
                break;
        }
    }
}

void func_80BB0E44(EnKujiya* this) {
    this->actionFunc = func_80BB0E58;
}

void func_80BB0E58(EnKujiya* this, GlobalContext* globalCtx) {
    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 0:
            break;

        case 4:
            func_80BB0B28(this, globalCtx);
            break;

        case 5:
            func_80BB0BF8(this, globalCtx);
            break;

        case 6:
            if (Message_ShouldAdvance(globalCtx)) {
                func_80BB09A8(this);
            }
            break;

        case 17:
            if (Message_ShouldAdvance(globalCtx)) {
                Inventory_SaveLotteryCodeGuess(globalCtx);
                Message_StartTextbox(globalCtx, 0x2B60, &this->actor);
                this->unk_14A = 0x2B60;
            }
            break;
    }
}

void func_80BB0F24(EnKujiya* this) {
    this->actionFunc = func_80BB0F38;
}

void func_80BB0F38(EnKujiya* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        func_80BB0F94(this);
    } else {
        Actor_PickUp(&this->actor, globalCtx, GI_RUPEE_PURPLE, 500.0f, 100.0f);
    }
}

void func_80BB0F94(EnKujiya* this) {
    this->actionFunc = func_80BB0FA8;
}

void func_80BB0FA8(EnKujiya* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 6) && Message_ShouldAdvance(globalCtx)) {
        func_80BB09A8(this);
    }
}

s32 func_80BB0FF8(void) {
    switch (CURRENT_DAY) {
        case 1:
            if (gSaveContext.save.weekEventReg[33] & 0x10) {
                return true;
            }
            break;

        case 2:
            if (gSaveContext.save.weekEventReg[33] & 0x20) {
                return true;
            }
            break;

        case 3:
            if (gSaveContext.save.weekEventReg[33] & 0x40) {
                return true;
            }
            break;
    }
    return false;
}

void func_80BB1088(void) {
    switch (CURRENT_DAY) {
        case 1:
            gSaveContext.save.weekEventReg[33] |= 0x10;
            break;

        case 2:
            gSaveContext.save.weekEventReg[33] |= 0x20;
            break;

        case 3:
            gSaveContext.save.weekEventReg[33] |= 0x40;
            break;
    }
}

void func_80BB10F8(void) {
    switch (CURRENT_DAY) {
        case 1:
            gSaveContext.save.weekEventReg[33] &= (u8)~0x10;
            break;

        case 2:
            gSaveContext.save.weekEventReg[33] &= (u8)~0x20;
            break;

        case 3:
            gSaveContext.save.weekEventReg[33] &= (u8)~0x40;
            break;
    }
}

void func_80BB1168(EnKujiya* this) {
    this->unk_148 = 0;
    this->actionFunc = func_80BB1180;
}

void func_80BB1180(EnKujiya* this, GlobalContext* globalCtx) {
    if (this->actor.cutscene != -1) {
        if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    }

    if (!Math_SmoothStepToS(&this->actor.shape.rot.y, 0x7555, 0xA, 0x16C, 0x16C)) {
        if (this->unk_148 > 20) {
            if (ActorCutscene_GetCurrentIndex() == this->actor.cutscene) {
                ActorCutscene_Stop(this->actor.cutscene);
            }
            func_80BB09A8(this);
        } else {
            this->unk_148++;
        }
    } else {
        func_800B9010(&this->actor, NA_SE_EV_WINDMILL_LEVEL - SFX_FLAG);
    }
}

void func_80BB1250(EnKujiya* this) {
    this->unk_148 = 0;
    this->actionFunc = func_80BB1268;
}

void func_80BB1268(EnKujiya* this, GlobalContext* globalCtx) {
    if (this->actor.cutscene != -1) {
        if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    }

    if (!Math_SmoothStepToS(&this->actor.shape.rot.y, 0, 0xA, 0x16C, 0x16C)) {
        if (this->unk_148 > 20) {
            if (ActorCutscene_GetCurrentIndex() == this->actor.cutscene) {
                ActorCutscene_Stop(this->actor.cutscene);
            }
            func_80BB09A8(this);
        } else {
            this->unk_148++;
        }
    } else {
        func_800B9010(&this->actor, NA_SE_EV_WINDMILL_LEVEL - SFX_FLAG);
    }
}

void EnKujiya_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnKujiya* this = THIS;

    this->actionFunc(this, globalCtx);
}

void EnKujiya_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnKujiya* this = THIS;

    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(object_kujiya_Matanimheader_006198));

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_kujiya_DL_002A80);
    gSPDisplayList(POLY_OPA_DISP++, object_kujiya_DL_003030);
    gSPDisplayList(POLY_OPA_DISP++, object_kujiya_DL_003248);
    gSPDisplayList(POLY_OPA_DISP++, object_kujiya_DL_003358);
    gSPDisplayList(POLY_OPA_DISP++, object_kujiya_DL_0034A8);
    gSPDisplayList(POLY_OPA_DISP++, object_kujiya_DL_0035B8);
    gSPDisplayList(POLY_OPA_DISP++, object_kujiya_DL_0036B0);
    gSPDisplayList(POLY_OPA_DISP++, object_kujiya_DL_0037C0);
    gSPDisplayList(POLY_OPA_DISP++, object_kujiya_DL_003C80);
    gSPDisplayList(POLY_OPA_DISP++, object_kujiya_DL_003D58);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
