/*
 * File: z_en_kujiya.c
 * Overlay: ovl_En_Kujiya
 * Description: Clock Town - Lottery Shop
 * 
 * (kuji = lottery, ya = shop)
 */

#include "z_en_kujiya.h"
#include "objects/object_kujiya/object_kujiya.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_8000000)

#define THIS ((EnKujiya*)thisx)

void EnKujiya_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKujiya_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKujiya_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKujiya_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnKujiya_SetupWait(EnKujiya* this);
void EnKujiya_Wait(EnKujiya* this, GlobalContext* globalCtx);
void EnKujiya_SetupTalk(EnKujiya* this);
void EnKujiya_Talk(EnKujiya* this, GlobalContext* globalCtx);
void EnKujiya_SetupGivePrize(EnKujiya* this);
void EnKujiya_GivePrize(EnKujiya* this, GlobalContext* globalCtx);
void EnKujiya_SetupFinishGivePrize(EnKujiya* this);
void EnKujiya_FinishGivePrize(EnKujiya* this, GlobalContext* globalCtx);
s32 EnKujiya_CheckBoughtTicket(void);
void EnKujiya_SetBoughtTicket(void);
void EnKujiya_UnsetBoughtTicket(void);
void EnKujiya_SetupTurnToOpen(EnKujiya* this);
void EnKujiya_TurnToOpen(EnKujiya* this, GlobalContext* globalCtx);
void EnKujiya_SetupTurnToClosed(EnKujiya* this);
void EnKujiya_TurnToClosed(EnKujiya* this, GlobalContext* globalCtx);

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

    if (EnKujiya_CheckBoughtTicket() && (gSaveContext.save.time >= CLOCK_TIME(6, 0)) &&
        (gSaveContext.save.time < CLOCK_TIME(18, 0))) {
        this->actor.shape.rot.y = 0;
    } else {
        this->actor.shape.rot.y = 0x7555;
    }
    EnKujiya_SetupWait(this);
}

void EnKujiya_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnKujiya_SetupWait(EnKujiya* this) {
    this->actionFunc = EnKujiya_Wait;
}

void EnKujiya_Wait(EnKujiya* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        if ((gSaveContext.save.time >= CLOCK_TIME(6, 0)) && (gSaveContext.save.time < CLOCK_TIME(18, 0))) {
            if (EnKujiya_CheckBoughtTicket()) {
                Message_StartTextbox(globalCtx, 0x2B61, &this->actor);
                this->textId = 0x2B61; // Come back tomorrow
            } else {
                Message_StartTextbox(globalCtx, 0x2B5C, &this->actor);
                this->textId = 0x2B5C; // Pick 3 numbers
            }
        } else if (EnKujiya_CheckBoughtTicket()) {
            Message_StartTextbox(globalCtx, 0x2B64, &this->actor);
            this->textId = 0x2B64; // Announce winning numbers
        } else {
            Message_StartTextbox(globalCtx, 0x2B63, &this->actor);
            this->textId = 0x2B63; // Exchanging winning tickets
        }

        EnKujiya_SetupTalk(this);
    } else if ((gSaveContext.save.time >= CLOCK_TIME(18, 0)) && EnKujiya_CheckBoughtTicket() && (this->actor.shape.rot.y == 0)) {
        EnKujiya_SetupTurnToOpen(this);
    } else if (this->actor.xzDistToPlayer < 100.0f) {
        func_800B8614(&this->actor, globalCtx, 100.0f);
    }
}

void EnKujiya_HandlePlayerChoice(EnKujiya* this, GlobalContext* globalCtx) {
    if (Message_ShouldAdvance(globalCtx)) {
        if (globalCtx->msgCtx.choiceIndex == 0) { // Buy
            if (gSaveContext.save.playerData.rupees < 10) {
                play_sound(NA_SE_SY_ERROR);
                Message_StartTextbox(globalCtx, 0x2B62, &this->actor);
                this->textId = 0x2B62; // Not enough Rupees
            } else {
                func_8019F208();
                func_801159EC(-10);
                Message_StartTextbox(globalCtx, 0x2B5F, &this->actor);
                this->textId = 0x2B5F; // Enter number
            }
        } else { // Don't buy
            func_8019F230();
            Message_StartTextbox(globalCtx, 0x2B5E, &this->actor);
            this->textId = 0x2B5E; // Too bad
        }
    }
}

void EnKujiya_ChooseNextDialogue(EnKujiya* this, GlobalContext* globalCtx) {
    // Build suspense
    if (this->textId == 0x2B65) { // Your numbers vs winning numbers
        if (this->timer != 0) {
            this->timer--;
            return;
        }
    }

    if (Message_ShouldAdvance(globalCtx)) {
        switch (this->textId) {
            case 0x2B5C:
                Message_StartTextbox(globalCtx, 0x2B5D, &this->actor);
                this->textId = 0x2B5D; // Buy or not
                break;

            case 0x2B60:
                EnKujiya_SetBoughtTicket();
                func_801477B4(globalCtx);
                EnKujiya_SetupTurnToClosed(this);
                break;

            case 0x2B64:
                EnKujiya_UnsetBoughtTicket();
                this->timer = 20;
                Message_StartTextbox(globalCtx, 0x2B65, &this->actor);
                this->textId = 0x2B65; // Your numbers vs winning numbers
                break;

            case 0x2B65:
                if (CHECK_LOTTERY_NUMBERS) {
                    Message_StartTextbox(globalCtx, 0x2B66, &this->actor);
                    this->textId = 0x2B66; // Won 50 Rupees
                } else {
                    Message_StartTextbox(globalCtx, 0x2B67, &this->actor);
                    this->textId = 0x2B67; // Lost, come back tomorrow
                }
                break;

            case 0x2B66:
                func_801477B4(globalCtx);
                EnKujiya_SetupGivePrize(this);
                EnKujiya_GivePrize(this, globalCtx);
                break;
        }
    }
}

void EnKujiya_SetupTalk(EnKujiya* this) {
    this->actionFunc = EnKujiya_Talk;
}

void EnKujiya_Talk(EnKujiya* this, GlobalContext* globalCtx) {
    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 0:
            break;

        case 4:
            EnKujiya_HandlePlayerChoice(this, globalCtx);
            break;

        case 5:
            EnKujiya_ChooseNextDialogue(this, globalCtx);
            break;

        case 6:
            if (Message_ShouldAdvance(globalCtx)) {
                EnKujiya_SetupWait(this);
            }
            break;

        case 17:
            if (Message_ShouldAdvance(globalCtx)) {
                Inventory_SaveLotteryCodeGuess(globalCtx);
                Message_StartTextbox(globalCtx, 0x2B60, &this->actor);
                this->textId = 0x2B60; // Will announce winning numbers after 6
            }
            break;
    }
}

void EnKujiya_SetupGivePrize(EnKujiya* this) {
    this->actionFunc = EnKujiya_GivePrize;
}

void EnKujiya_GivePrize(EnKujiya* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        EnKujiya_SetupFinishGivePrize(this);
    } else {
        Actor_PickUp(&this->actor, globalCtx, GI_RUPEE_PURPLE, 500.0f, 100.0f);
    }
}

void EnKujiya_SetupFinishGivePrize(EnKujiya* this) {
    this->actionFunc = EnKujiya_FinishGivePrize;
}

void EnKujiya_FinishGivePrize(EnKujiya* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 6) && Message_ShouldAdvance(globalCtx)) {
        EnKujiya_SetupWait(this);
    }
}

s32 EnKujiya_CheckBoughtTicket(void) {
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

void EnKujiya_SetBoughtTicket(void) {
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

/**
 * Used when player turns in a ticket
 */
void EnKujiya_UnsetBoughtTicket(void) {
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

void EnKujiya_SetupTurnToOpen(EnKujiya* this) {
    this->timer = 0;
    this->actionFunc = EnKujiya_TurnToOpen;
}

void EnKujiya_TurnToOpen(EnKujiya* this, GlobalContext* globalCtx) {
    if (this->actor.cutscene != -1) {
        if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    }

    if (!Math_SmoothStepToS(&this->actor.shape.rot.y, 0x7555, 0xA, 0x16C, 0x16C)) {
        if (this->timer > 20) {
            if (ActorCutscene_GetCurrentIndex() == this->actor.cutscene) {
                ActorCutscene_Stop(this->actor.cutscene);
            }
            EnKujiya_SetupWait(this);
        } else {
            this->timer++;
        }
    } else {
        func_800B9010(&this->actor, NA_SE_EV_WINDMILL_LEVEL - SFX_FLAG);
    }
}

void EnKujiya_SetupTurnToClosed(EnKujiya* this) {
    this->timer = 0;
    this->actionFunc = EnKujiya_TurnToClosed;
}

void EnKujiya_TurnToClosed(EnKujiya* this, GlobalContext* globalCtx) {
    if (this->actor.cutscene != -1) {
        if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    }

    if (!Math_SmoothStepToS(&this->actor.shape.rot.y, 0, 0xA, 0x16C, 0x16C)) {
        if (this->timer > 20) {
            if (ActorCutscene_GetCurrentIndex() == this->actor.cutscene) {
                ActorCutscene_Stop(this->actor.cutscene);
            }
            EnKujiya_SetupWait(this);
        } else {
            this->timer++;
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

    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(gLotteryShopTexAnim));

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gLotteryShopCylinderDL);
    gSPDisplayList(POLY_OPA_DISP++, gLotteryShopBackSignDL);
    gSPDisplayList(POLY_OPA_DISP++, gLotteryShopOpenBoxDL);
    gSPDisplayList(POLY_OPA_DISP++, gLotteryShopScrollingEffectsDL);
    gSPDisplayList(POLY_OPA_DISP++, gLotteryShopRedRupeesDL);
    gSPDisplayList(POLY_OPA_DISP++, gLotteryShopGreenRupeesDL);
    gSPDisplayList(POLY_OPA_DISP++, gLotteryShopBlueRupeesDL);
    gSPDisplayList(POLY_OPA_DISP++, gLotteryShopTargetArrowAndSignDL);
    gSPDisplayList(POLY_OPA_DISP++, gLotteryShopScrollingArrowDL);
    gSPDisplayList(POLY_OPA_DISP++, gLotteryShopMaskDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
