/*
 * File: z_en_zos.c
 * Overlay: ovl_En_Zos
 * Description: Zora Synthesizer - Evan
 */

#include "z_en_zos.h"
#include "objects/object_zos/object_zos.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_2000000)

#define THIS ((EnZos*)thisx)

void EnZos_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZos_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZos_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZos_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BBAE84(EnZos* this, s16 arg1, u8 arg2);
void func_80BBB2C4(EnZos* this, GlobalContext* globalCtx);
void func_80BBB354(EnZos* this, GlobalContext* globalCtx);
void func_80BBB4CC(EnZos* this, GlobalContext* globalCtx);
void func_80BBB574(EnZos* this, GlobalContext* globalCtx);
void func_80BBB718(EnZos* this, GlobalContext* globalCtx);
void func_80BBB8AC(EnZos* this, GlobalContext* globalCtx);
void func_80BBBB84(EnZos* this, GlobalContext* globalCtx);
void func_80BBBCBC(EnZos* this, GlobalContext* globalCtx);
void func_80BBBD5C(EnZos* this, GlobalContext* globalCtx);
void func_80BBBDE0(EnZos* this, GlobalContext* globalCtx);
void func_80BBC070(EnZos* this, GlobalContext* globalCtx);
void func_80BBC14C(EnZos* this, GlobalContext* globalCtx);
void func_80BBC22C(EnZos* this, GlobalContext* globalCtx);
void func_80BBC24C(EnZos* this, GlobalContext* globalCtx);
void func_80BBC298(EnZos* this, GlobalContext* globalCtx);
void func_80BBC37C(EnZos* this, GlobalContext* globalCtx);

const ActorInit En_Zos_InitVars = {
    ACTOR_EN_ZOS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZOS,
    sizeof(EnZos),
    (ActorFunc)EnZos_Init,
    (ActorFunc)EnZos_Destroy,
    (ActorFunc)EnZos_Update,
    (ActorFunc)EnZos_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 60, 40, 0, { 0, 0, 0 } },
};

void EnZos_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnZos* this = THIS;

    Actor_SetScale(&this->actor, 0.0115f);
    this->actionFunc = func_80BBBDE0;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_zos_Skel_015238, &object_zos_Anim_00A164, this->jointTable,
                       this->morphTable, 18);
    Animation_PlayLoop(&this->skelAnime, &object_zos_Anim_00A164);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->unk_2B6 = 0;
    this->actor.terminalVelocity = -4.0f;
    this->actor.gravity = -4.0f;
    func_80BBAE84(this, 0, 2);

    switch (ENZOS_GET_F(&this->actor)) {
        case ENZOS_F_1:
            if (!(gSaveContext.save.weekEventReg[55] & 0x80)) {
                Actor_MarkForDeath(&this->actor);
            }

            if (gSaveContext.save.weekEventReg[78] & 1) {
                this->actionFunc = func_80BBC24C;
            } else {
                this->actionFunc = func_80BBC14C;
            }
            func_80BBAE84(this, 0, 2);
            break;

        case ENZOS_F_2:
            this->actionFunc = func_80BBC37C;
            func_80BBAE84(this, 7, 2);
            this->unk_2BC = -1;
            this->unk_2B6 |= 0x40;
            break;

        default:
            if (gSaveContext.save.weekEventReg[55] & 0x80) {
                Actor_MarkForDeath(&this->actor);
            }
            this->actor.flags |= ACTOR_FLAG_10;
            break;
    }
}

void EnZos_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnZos* this = THIS;

    gSaveContext.save.weekEventReg[52] &= (u8)~0x10;
}

void func_80BBAE84(EnZos* this, s16 arg1, u8 arg2) {
    static AnimationHeader* sAnimations[] = {
        &object_zos_Anim_00A164, &object_zos_Anim_01621C, &object_zos_Anim_016980, &object_zos_Anim_007C40,
        &object_zos_Anim_008630, &object_zos_Anim_0090CC, &object_zos_Anim_009830, &object_zos_Anim_005E04,
        &object_zos_Anim_007334, &object_zos_Anim_0048D4, &object_zos_Anim_001CFC, &object_zos_Anim_005E04,
        &object_zos_Anim_007334,
    };
    f32 phi_f0;

    if ((arg1 != this->unk_2B8) && (arg1 >= 0) && (arg1 < 13)) {
        if (arg1 > 10) {
            phi_f0 = 29.0f;
        } else {
            phi_f0 = Animation_GetLastFrame(sAnimations[arg1]);
        }
        Animation_Change(&this->skelAnime, sAnimations[arg1], 1.0f, 0.0f, phi_f0, arg2, -5.0f);
        this->unk_2B8 = arg1;
        this->unk_2B6 &= ~0x80;
    }
}

s32 func_80BBAF5C(EnZos* this, GlobalContext* globalCtx) {
    if (Player_IsFacingActor(&this->actor, 0x3000, globalCtx) &&
        ((!Actor_IsFacingPlayer(&this->actor, 0x4000) && (this->actor.home.rot.y == this->actor.shape.rot.y)) ||
         (Actor_IsFacingPlayer(&this->actor, 0x3000) && (this->actor.home.rot.y != this->actor.shape.rot.y))) &&
        (this->actor.xzDistToPlayer < 100.0f)) {
        return true;
    }
    return false;
}

s32 func_80BBAFFC(EnZos* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        switch ((s16)Rand_ZeroFloat(4.0f)) {
            case 0:
                func_80BBAE84(this, 7, 2);
                break;

            case 1:
                func_80BBAE84(this, 8, 2);
                break;

            case 2:
                func_80BBAE84(this, 11, 2);
                break;

            default:
                func_80BBAE84(this, 12, 2);
                break;
        }
        return true;
    }
    return false;
}

void func_80BBB0D4(EnZos* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        if (Rand_ZeroFloat(1.0f) < 0.9f) {
            func_80BBAE84(this, 0, 2);
        } else {
            func_80BBAE84(this, 1, 2);
        }
        SkelAnime_Update(&this->skelAnime);
    }
}

void func_80BBB15C(EnZos* this, GlobalContext* globalCtx) {
    s32 textId;

    if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
        if (this->unk_2B6 & 8) {
            textId = 0x1235;
            func_80BBAE84(this, 6, 0);
            this->unk_2B6 |= 2;
        } else if (this->unk_2B6 & 4) {
            textId = 0x123E;
            func_80BBAE84(this, 6, 0);
            this->unk_2B6 |= 2;
        } else if (gSaveContext.save.weekEventReg[40] & 0x20) {
            textId = 0x1236;
            func_80BBAE84(this, 6, 0);
            this->unk_2B6 |= 0x80;
        } else {
            textId = 0x1231;
            func_80BBAE84(this, 6, 0);
            this->unk_2B6 |= 0x80;
        }
    } else {
        this->unk_2B6 &= ~2;
        if (gSaveContext.save.weekEventReg[39] & 0x10) {
            textId = 0x1243;
            func_80BBAE84(this, 6, 0);
            this->unk_2B6 |= 0x80;
        } else {
            textId = 0x1244;
            gSaveContext.save.weekEventReg[39] |= 0x10;
            func_80BBAE84(this, 4, 0);
            this->unk_2B6 |= 0x10;
        }
    }
    Message_StartTextbox(globalCtx, textId, &this->actor);
}

void func_80BBB2C4(EnZos* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        Message_StartTextbox(globalCtx, 0x124F, &this->actor);
        this->actionFunc = func_80BBB8AC;
        this->actor.flags &= ~ACTOR_FLAG_10000;
    } else {
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, -1);
    }
}

void func_80BBB354(EnZos* this, GlobalContext* globalCtx) {
    s32 item;

    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->actionFunc = func_80BBB2C4;
        gSaveContext.save.weekEventReg[39] |= 0x20;
        this->actor.flags |= ACTOR_FLAG_10000;
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, -1);
    } else {
        if (gSaveContext.save.weekEventReg[39] & 0x20) {
            item = GI_RUPEE_PURPLE;
        } else {
            item = GI_HEART_PIECE;
        }
        Actor_PickUp(&this->actor, globalCtx, item, 10000.0f, 50.0f);
    }
}

void func_80BBB414(EnZos* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);

    if (Cutscene_CheckActorAction(globalCtx, 501)) {
        s16 action = globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 501)]->action;

        if (action != this->unk_2BA) {
            this->unk_2BA = action;

            switch (action) {
                case 1:
                    func_80BBAE84(this, 1, 0);
                    break;

                case 2:
                    func_80BBAE84(this, 10, 0);
                    break;
            }
        }
    }
}

void func_80BBB4CC(EnZos* this, GlobalContext* globalCtx) {
    func_80BBB414(this, globalCtx);

    if ((this->actor.cutscene != -1) && (ActorCutscene_GetCurrentIndex() != this->actor.cutscene)) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
            ActorCutscene_Start(this->actor.cutscene, &this->actor);
            this->actor.cutscene = -1;
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    }
}

void func_80BBB574(EnZos* this, GlobalContext* globalCtx) {
    if (!(this->unk_2B6 & 0x10)) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0x1000, 0x200);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }

    if (func_80BBAFFC(this, globalCtx)) {
        if (this->unk_2B6 & 0x20) {
            this->unk_2B6 &= ~0x20;
            func_80151938(globalCtx, 0x124C);
        }
    }

    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        switch (globalCtx->msgCtx.currentTextId) {
            case 0x124B:
                if (this->unk_2B8 == 9) {
                    globalCtx->msgCtx.unk11F10 = 0;
                    this->unk_2B6 |= 0x20;
                } else {
                    func_80151938(globalCtx, 0x124C);
                }
                break;

            case 0x124C:
                globalCtx->msgCtx.unk11F10 = 0;
                this->actionFunc = func_80BBB4CC;
                func_80BBAE84(this, 10, 0);
                break;

            case 0x124D:
                this->unk_2B6 &= ~0x10;
                func_80BBAE84(this, 6, 0);
                func_80151938(globalCtx, 0x124E);
                break;

            case 0x124E:
                func_801477B4(globalCtx);
                this->actionFunc = func_80BBB354;
                func_80BBB354(this, globalCtx);
                break;
        }
    }
}

void func_80BBB718(EnZos* this, GlobalContext* globalCtx) {
    s32 sp24;
    Player* player = GET_PLAYER(globalCtx);

    SkelAnime_Update(&this->skelAnime);

    if (Message_GetState(&globalCtx->msgCtx) == 0x10) {
        sp24 = func_80123810(globalCtx);
        if (sp24 > 0) {
            func_801477B4(globalCtx);

            if (sp24 == 25) {
                player->actor.textId = 0x1232;
                func_80BBAE84(this, 5, 0);
                this->unk_2B6 |= 8;
                gSaveContext.save.weekEventReg[40] |= 0x20;
            } else if (gSaveContext.save.weekEventReg[39] & 8) {
                player->actor.textId = 0x1241;
            } else {
                player->actor.textId = 0x1237;
                gSaveContext.save.weekEventReg[39] |= 8;
                func_80BBAE84(this, 4, 0);
                this->unk_2B6 |= 4;
            }
            this->actionFunc = func_80BBB8AC;
        } else if (sp24 < 0) {
            if (gSaveContext.save.weekEventReg[39] & 8) {
                func_80151938(globalCtx, 0x1241);
            } else {
                func_80151938(globalCtx, 0x1237);
                gSaveContext.save.weekEventReg[39] |= 8;
                func_80BBAE84(this, 4, 0);
                this->unk_2B6 |= 4;
            }
            this->actionFunc = func_80BBB8AC;
        }
    }
}

void func_80BBB8AC(EnZos* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);

    SkelAnime_Update(&this->skelAnime);

    if (!(this->unk_2B6 & 0x10)) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0x1000, 0x200);
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if ((this->unk_2B6 & 0x80) && (this->actor.yawTowardsPlayer == this->actor.shape.rot.y)) {
            func_80BBAE84(this, 3, 0);
        }
    }

    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        switch (globalCtx->msgCtx.currentTextId) {
            case 0x1237:
                player->exchangeItemId = 0;

            case 0x1238:
            case 0x123A:
            case 0x123B:
            case 0x123C:
            case 0x123E:
            case 0x123F:
                func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                break;

            case 0x1244:
                this->unk_2B6 &= ~0x10;
                func_80BBAE84(this, 6, 0);
                func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                break;

            case 0x1232:
            case 0x1241:
                player->exchangeItemId = 0;

            case 0x1239:
            case 0x1246:
                func_80BBAE84(this, 6, 0);
                func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                break;

            case 0x1233:
                func_80BBAE84(this, 5, 0);
                func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                break;

            case 0x1245:
            case 0x1248:
                func_80BBAE84(this, 3, 0);
                func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                break;

            case 0x1231:
                func_80151938(globalCtx, 0xFF);
                this->actionFunc = func_80BBB718;
                break;

            case 0x1243:
            case 0x1249:
                func_80BBAE84(this, 2, 0);
                func_801477B4(globalCtx);
                this->actionFunc = func_80BBBDE0;
                this->unk_2B6 |= 1;
                break;

            case 0x1234:
            case 0x123D:
            case 0x1242:
                func_80BBAE84(this, 2, 0);
                Actor_ProcessTalkRequest(&this->actor, &globalCtx->state);
                func_801477B4(globalCtx);
                this->actionFunc = func_80BBBDE0;
                this->unk_2B6 |= 1;
                break;

            case 0x1236:
                func_80BBAE84(this, 2, 0);
                func_801477B4(globalCtx);
                this->actionFunc = func_80BBBDE0;
                this->unk_2B6 |= 1;
                break;

            default:
                if (0) {}
                func_801477B4(globalCtx);
                this->actionFunc = func_80BBBDE0;
                this->unk_2B6 |= 1;
                break;
        }
    }
}

void func_80BBBB84(EnZos* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actor.flags &= ~ACTOR_FLAG_10000;
        if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
            Message_StartTextbox(globalCtx, 0x1248, &this->actor);
            this->actionFunc = func_80BBB8AC;
            func_80BBAE84(this, 6, 0);
            this->unk_2B6 |= 2;
        } else if (gSaveContext.save.weekEventReg[41] & 0x10) {
            Message_StartTextbox(globalCtx, 0x124A, &this->actor);
            this->actionFunc = func_80BBB8AC;
            func_80BBAE84(this, 6, 0);
        } else {
            gSaveContext.save.weekEventReg[41] |= 0x10;
            Message_StartTextbox(globalCtx, 0x124B, &this->actor);
            this->actionFunc = func_80BBB574;
            func_80BBAE84(this, 9, 2);
            this->unk_2B6 |= 0x10;
        }
    } else {
        func_800B8614(&this->actor, globalCtx, 300.0f);
    }
}

void func_80BBBCBC(EnZos* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actor.flags &= ~ACTOR_FLAG_10000;
        func_80BBAE84(this, 5, 0);
        Message_StartTextbox(globalCtx, 0x124D, &this->actor);
        this->actionFunc = func_80BBB574;
    } else {
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, -1);
    }
}

void func_80BBBD5C(EnZos* this, GlobalContext* globalCtx) {
    func_80BBB414(this, globalCtx);
    if (!Cutscene_CheckActorAction(globalCtx, 0x1F5)) {
        this->actionFunc = func_80BBBCBC;
        this->actor.flags |= ACTOR_FLAG_10000;
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, -1);
    }
}

void func_80BBBDE0(EnZos* this, GlobalContext* globalCtx) {
    Actor* thisx = &this->actor;
    Vec3f sp28;

    if (this->unk_2B6 & 1) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 2, 0x1000, 0x200);
        this->actor.world.rot.y = thisx->shape.rot.y;
        if (this->actor.home.rot.y == thisx->shape.rot.y) {
            func_80BBAE84(this, 0, 2);
            this->unk_2B6 &= ~1;
        }
    }

    func_80BBB0D4(this, globalCtx);

    if (globalCtx->msgCtx.ocarinaMode == 0x2A) {
        globalCtx->msgCtx.ocarinaMode = 4;
        this->actionFunc = func_80BBBB84;
        this->actor.flags |= ACTOR_FLAG_10000;
        func_800B8614(&this->actor, globalCtx, 120.0f);
        return;
    }

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80BBB8AC;
        func_80BBB15C(this, globalCtx);
    } else if (Cutscene_CheckActorAction(globalCtx, 0x1F5)) {
        this->actionFunc = func_80BBBD5C;
    } else if (func_80BBAF5C(this, globalCtx)) {
        func_800B8614(&this->actor, globalCtx, 120.0f);
    }

    if (!Actor_IsFacingPlayer(&this->actor, 0x4000) && (this->actor.xzDistToPlayer < 100.0f)) {
        gSaveContext.save.weekEventReg[52] |= 0x10;
    } else {
        gSaveContext.save.weekEventReg[52] &= (u8)~0x10;
    }

    sp28.x = this->actor.projectedPos.x;
    sp28.y = this->actor.projectedPos.y;
    sp28.z = this->actor.projectedPos.z;
    func_801A1FB4(3, &sp28, 110, 1000.0f);
}

void func_80BBBFBC(EnZos* this, GlobalContext* globalCtx) {
    u16 textId;

    if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
        if (gSaveContext.save.weekEventReg[79] & 1) {
            textId = 0x125B;
        } else if (gSaveContext.save.weekEventReg[78] & 0x80) {
            textId = 0x125A;
        } else {
            textId = 0x1259;
            gSaveContext.save.weekEventReg[78] |= 0x80;
        }
        func_80BBAE84(this, 5, 0);
    } else {
        textId = 0x1258;
        func_80BBAE84(this, 6, 0);
    }
    Message_StartTextbox(globalCtx, textId, &this->actor);
}

void func_80BBC070(EnZos* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0x1000, 0x200);
    this->actor.world.rot.y = this->actor.shape.rot.y;

    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 5:
            if (Message_ShouldAdvance(globalCtx)) {
                func_80BBAE84(this, 2, 0);
                func_801477B4(globalCtx);
                this->actionFunc = func_80BBC14C;
                this->unk_2B6 |= 1;
            }
            break;

        case 2:
            func_80BBAE84(this, 2, 0);
            this->actionFunc = func_80BBC14C;
            this->unk_2B6 |= 1;
            break;
    }
}

void func_80BBC14C(EnZos* this, GlobalContext* globalCtx) {
    Actor* thisx = &this->actor;

    if (this->unk_2B6 & 1) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 2, 0x1000, 0x200);
        this->actor.world.rot.y = thisx->shape.rot.y;
        if (this->actor.home.rot.y == this->actor.shape.rot.y) {
            func_80BBAE84(this, 0, 2);
            this->unk_2B6 &= ~1;
        }
    }

    func_80BBB0D4(this, globalCtx);

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80BBC070;
        func_80BBBFBC(this, globalCtx);
    } else if (func_80BBAF5C(this, globalCtx)) {
        func_800B8614(&this->actor, globalCtx, 120.0f);
    }
}

void func_80BBC22C(EnZos* this, GlobalContext* globalCtx) {
    func_80BBAFFC(this, globalCtx);
}

void func_80BBC24C(EnZos* this, GlobalContext* globalCtx) {
    func_80BBB0D4(this, globalCtx);
    if (gSaveContext.save.weekEventReg[79] & 1) {
        this->actionFunc = func_80BBC22C;
        func_80BBAE84(this, 7, 2);
    }
}

void func_80BBC298(EnZos* this, GlobalContext* globalCtx) {
    func_80BBAFFC(this, globalCtx);

    if (this->unk_2BC < 799) {
        this->unk_2BC += 200;
    } else {
        this->unk_2BC += 30;
    }

    if (this->unk_2BC > 999) {
        this->unk_2BC = 999;
    }

    if (Cutscene_CheckActorAction(globalCtx, 515)) {
        if (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 515)]->action == 1) {
            this->actionFunc = func_80BBC37C;
            this->unk_2BC = -1;
        }
    } else {
        this->actionFunc = func_80BBC37C;
        this->unk_2BC = -1;
    }
}

void func_80BBC37C(EnZos* this, GlobalContext* globalCtx) {
    func_80BBAFFC(this, globalCtx);
    if (Cutscene_CheckActorAction(globalCtx, 515) &&
        (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 515)]->action == 3)) {
        this->actionFunc = func_80BBC298;
    }
}

void EnZos_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnZos* this = THIS;

    Actor_MoveWithGravity(&this->actor);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 10.0f, 10.0f, 30.0f, 4);

    this->actionFunc(this, globalCtx);

    if (DECR(this->unk_2AE) == 0) {
        this->unk_2AE = Rand_S16Offset(60, 60);
    }

    this->unk_2AC = this->unk_2AE;
    if (this->unk_2AC >= 3) {
        this->unk_2AC = 0;
    }
}

s32 func_80BBC4E4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return false;
}

void func_80BBC500(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80BBC750 = { 0.0f, 0.0f, 0.0f };

    if (limbIndex == 9) {
        Matrix_MultiplyVector3fByState(&D_80BBC750, &thisx->focus.pos);
    }
}

void EnZos_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static TexturePtr D_80BBC75C[] = {
        object_zos_Tex_010918,
        object_zos_Tex_011118,
        object_zos_Tex_011918,
    };
    EnZos* this = THIS;
    Gfx* gfx;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    if (this->unk_2B6 & 0x40) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 0, 0, 0, 0, this->unk_2BC, 1000);
    }

    gfx = POLY_OPA_DISP;

    gSPSegment(&gfx[0], 0x08, Lib_SegmentedToVirtual(D_80BBC75C[this->unk_2AC]));

    Matrix_StatePush();
    Matrix_RotateY(this->actor.home.rot.y - this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_InsertTranslation(0.0f, 0.0f, -974.4f, MTXMODE_APPLY);

    gSPMatrix(&gfx[1], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(&gfx[2], object_zos_DL_0136E0);
    gSPDisplayList(&gfx[3], object_zos_DL_013088);

    POLY_OPA_DISP = &gfx[4];

    Matrix_StatePop();

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          func_80BBC4E4, func_80BBC500, &this->actor);

    if (this->unk_2B6 & 0x40) {
        POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
