/*
 * File: z_en_zob.c
 * Overlay: ovl_En_Zob
 * Description: Zora Bassist Japas
 */

#include "z_en_zob.h"
#include "objects/object_zob/object_zob.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnZob*)thisx)

void EnZob_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZob_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZob_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZob_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B9F7E4(EnZob* this, s16 arg1, u8 arg2);
void func_80B9FD24(EnZob* this, GlobalContext* globalCtx);
void func_80B9FDDC(EnZob* this, GlobalContext* globalCtx);
void func_80B9FE1C(EnZob* this, GlobalContext* globalCtx);
void func_80B9FE5C(EnZob* this, GlobalContext* globalCtx);
void func_80B9FF20(EnZob* this, GlobalContext* globalCtx);
void func_80B9FF80(EnZob* this, GlobalContext* globalCtx);
void func_80BA005C(EnZob* this, GlobalContext* globalCtx);
void func_80BA00BC(EnZob* this, GlobalContext* globalCtx);
void func_80BA0318(EnZob* this, GlobalContext* globalCtx);
void func_80BA0374(EnZob* this, GlobalContext* globalCtx);
void func_80BA0610(EnZob* this, GlobalContext* globalCtx);
void func_80BA06BC(EnZob* this, GlobalContext* globalCtx);
void func_80BA0728(EnZob* this, GlobalContext* globalCtx);
void func_80BA09E0(EnZob* this, GlobalContext* globalCtx);
void func_80BA0A04(EnZob* this, GlobalContext* globalCtx);
void func_80BA0AD8(EnZob* this, GlobalContext* globalCtx);
void func_80BA0BB4(EnZob* this, GlobalContext* globalCtx);
void func_80BA0C14(EnZob* this, GlobalContext* globalCtx);
void func_80BA0CF4(EnZob* this, GlobalContext* globalCtx);

const ActorInit En_Zob_InitVars = {
    ACTOR_EN_ZOB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZOB,
    sizeof(EnZob),
    (ActorFunc)EnZob_Init,
    (ActorFunc)EnZob_Destroy,
    (ActorFunc)EnZob_Update,
    (ActorFunc)EnZob_Draw,
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
    { 30, 40, 0, { 0, 0, 0 } },
};

static AnimationHeader* sAnimations[] = {
    &object_zob_Anim_0027D0, &object_zob_Anim_002B38, &object_zob_Anim_0037A0,
    &object_zob_Anim_0043C4, &object_zob_Anim_005224, &object_zob_Anim_005E90,
    &object_zob_Anim_006998, &object_zob_Anim_011144, &object_zob_Anim_001FD4,
};

Vec3f D_80BA1120 = { 300.0f, 900.0f, 0.0f };

void EnZob_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnZob* this = THIS;
    s32 i;
    s16 cs;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    Actor_SetScale(&this->actor, 0.0115f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_zob_Skel_010810, &object_zob_Anim_006998, this->jointTable,
                       this->morphTable, 24);
    Animation_PlayLoop(&this->skelAnime, &object_zob_Anim_006998);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->unk_2F4 = 0;
    this->unk_30E = -1;
    this->unk_310 = 0;
    this->unk_302 = 9;
    this->unk_304 = 0;
    this->actor.terminalVelocity = -4.0f;
    this->actor.gravity = -4.0f;
    func_80B9F7E4(this, 6, 2);
    this->actionFunc = func_80BA0728;
    this->actor.textId = 0;

    cs = this->actor.cutscene;
    for (i = 0; i < ARRAY_COUNT(this->unk_306); i++) {
        this->unk_306[i] = cs;
        if (cs != -1) {
            this->actor.cutscene = cs;
            cs = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
        }
    }

    this->actor.cutscene = this->unk_306[0];
    this->actor.flags |= ACTOR_FLAG_2000000;

    switch (ENZOB_GET_F(&this->actor)) {
        case ENZOB_F_1:
            if (gSaveContext.save.weekEventReg[78] & 1) {
                this->actionFunc = func_80BA0BB4;
            } else {
                this->actionFunc = func_80BA0AD8;
            }

            if (!(gSaveContext.save.weekEventReg[55] & 0x80)) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            break;

        case ENZOB_F_2:
            this->actionFunc = func_80BA0CF4;
            this->unk_2F4 |= 0x20;
            this->unk_312 = -1;
            func_80B9F7E4(this, 0, 2);
            this->unk_304 = 5;
            break;

        default:
            if (gSaveContext.save.weekEventReg[55] & 0x80) {
                Actor_MarkForDeath(&this->actor);
            }
            this->actor.flags |= ACTOR_FLAG_10;
            break;
    }
}

void EnZob_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnZob* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80B9F7E4(EnZob* this, s16 arg1, u8 arg2) {
    Animation_Change(&this->skelAnime, sAnimations[arg1], 1.0f, 0.0f, Animation_GetLastFrame(sAnimations[arg1]), arg2,
                     -5.0f);
    this->unk_302 = arg1;
}

void func_80B9F86C(EnZob* this) {
    if (SkelAnime_Update(&this->skelAnime)) {
        switch (this->unk_304) {
            case 0:
                if (Rand_ZeroFloat(1.0f) > 0.7f) {
                    if (this->unk_302 == 6) {
                        func_80B9F7E4(this, 7, 2);
                    } else {
                        func_80B9F7E4(this, 6, 2);
                    }
                } else {
                    func_80B9F7E4(this, this->unk_302, 2);
                }
                break;

            case 1:
                func_80B9F7E4(this, 3, 0);
                break;

            case 2:
                func_80B9F7E4(this, 4, 0);
                break;

            case 3:
                func_80B9F7E4(this, 5, 0);
                break;

            case 4:
                if (this->unk_302 == 3) {
                    func_80B9F7E4(this, 0, 0);
                } else {
                    func_80B9F7E4(this, 3, 2);
                }
                break;

            case 5:
                if (Rand_ZeroFloat(1.0f) < 0.8f) {
                    func_80B9F7E4(this, this->unk_302, 2);
                } else if (this->unk_302 == 0) {
                    func_80B9F7E4(this, 1, 2);
                } else {
                    func_80B9F7E4(this, 0, 2);
                }
                break;
        }

        SkelAnime_Update(&this->skelAnime);
    }
}

void func_80B9FA3C(EnZob* this, GlobalContext* globalCtx) {
    u16 textId;

    this->unk_2F4 |= 1;

    if (gSaveContext.save.playerForm != PLAYER_FORM_ZORA) {
        if (gSaveContext.save.weekEventReg[30] & 2) {
            textId = 0x11F9;
        } else {
            textId = 0x11F8;
        }
        this->unk_304 = 3;
        func_80B9F7E4(this, 5, 0);
    } else if (this->unk_2F4 & 0x10) {
        textId = 0x1210;
        this->unk_304 = 3;
        func_80B9F7E4(this, 5, 2);
    } else if (gSaveContext.save.weekEventReg[31] & 8) {
        textId = 0x1205;
        this->unk_304 = 1;
        func_80B9F7E4(this, 3, 0);
    } else if (this->unk_2F4 & 8) {
        textId = 0x1215;
        this->unk_304 = 3;
        func_80B9F7E4(this, 5, 2);
    } else if (this->unk_2F4 & 2) {
        textId = 0x1203;
        this->unk_304 = 1;
        func_80B9F7E4(this, 2, 2);
    } else if (gSaveContext.save.weekEventReg[30] & 8) {
        textId = 0x11FA;
        this->unk_304 = 1;
        func_80B9F7E4(this, 2, 2);
    } else if (!(gSaveContext.save.weekEventReg[30] & 4)) {
        gSaveContext.save.weekEventReg[30] |= 4;
        textId = 0x11FB;
        this->unk_304 = 1;
        func_80B9F7E4(this, 2, 2);
    } else {
        textId = 0x1201;
        this->unk_304 = 3;
        func_80B9F7E4(this, 4, 2);
    }

    Message_StartTextbox(globalCtx, textId, &this->actor);
}

void func_80B9FC0C(EnZob* this) {
    if (this->unk_30E != -1) {
        if (ActorCutscene_GetCurrentIndex() == this->unk_306[this->unk_30E]) {
            ActorCutscene_Stop(this->unk_306[this->unk_30E]);
        }
        this->unk_30E = -1;
    }
}

void func_80B9FC70(EnZob* this, s16 arg1) {
    func_80B9FC0C(this);
    this->unk_30E = arg1;
}

void func_80B9FCA0(EnZob* this, GlobalContext* globalCtx) {
    func_801477B4(globalCtx);
    globalCtx->msgCtx.ocarinaMode = 4;
    func_80B9FC0C(this);
    this->unk_2F4 &= ~1;
    this->actionFunc = func_80BA0728;
    this->unk_304 = 0;
    func_80B9F7E4(this, 6, 2);
    func_800B8718(&this->actor, &globalCtx->state);
}

void func_80B9FD24(EnZob* this, GlobalContext* globalCtx) {
    s32 actionIndex;
    s16 action;

    func_80B9F86C(this);

    if (Cutscene_CheckActorAction(globalCtx, 500)) {
        this->unk_30E = -1;
        actionIndex = Cutscene_GetActorActionIndex(globalCtx, 500);
        action = globalCtx->csCtx.actorActions[actionIndex]->action;

        if (action != this->unk_310) {
            this->unk_310 = action;
            switch (action) {
                case 1:
                    func_80B9F7E4(this, 8, 0);
                    break;

                case 2:
                    func_80B9F7E4(this, 7, 0);
                    break;
            }
        }
    }
}

void func_80B9FDDC(EnZob* this, GlobalContext* globalCtx) {
    Message_StartTextbox(globalCtx, 0x120C, &this->actor);
    this->actionFunc = func_80BA00BC;
}

void func_80B9FE1C(EnZob* this, GlobalContext* globalCtx) {
    Message_StartTextbox(globalCtx, 0x1211, &this->actor);
    this->actionFunc = func_80BA00BC;
}

void func_80B9FE5C(EnZob* this, GlobalContext* globalCtx) {
    func_80B9F86C(this);
    if (globalCtx->msgCtx.ocarinaMode == 3) {
        globalCtx->msgCtx.unk11F10 = 0;
        this->actionFunc = func_80B9FDDC;
        func_80B9FC70(this, 0);
    } else if (Message_GetState(&globalCtx->msgCtx) == 11) {
        globalCtx->msgCtx.unk11F10 = 0;
        this->actionFunc = func_80B9FE1C;
        this->unk_304 = 3;
        func_80B9F7E4(this, 5, 2);
        func_80B9FC70(this, 0);
    }
}

void func_80B9FF20(EnZob* this, GlobalContext* globalCtx) {
    func_80B9F86C(this);
    if (Message_GetState(&globalCtx->msgCtx) == 7) {
        func_80152434(globalCtx, 0x42);
        this->actionFunc = func_80B9FE5C;
        func_80B9FC70(this, 2);
    }
}

void func_80B9FF80(EnZob* this, GlobalContext* globalCtx) {
    func_80B9F86C(this);
    if (globalCtx->msgCtx.ocarinaMode == 3) {
        this->actionFunc = func_80B9FF20;
        this->unk_304 = 6;
        func_80B9F7E4(this, 1, 0);
        func_80152434(globalCtx, 0x3E);
        func_80B9FC70(this, 1);
    } else if (Message_GetState(&globalCtx->msgCtx) == 11) {
        globalCtx->msgCtx.unk11F10 = 0;
        this->actionFunc = func_80B9FE1C;
        this->unk_304 = 3;
        func_80B9F7E4(this, 5, 2);
        func_80B9FC70(this, 0);
    }
}

void func_80BA005C(EnZob* this, GlobalContext* globalCtx) {
    func_80B9F86C(this);
    if (Message_GetState(&globalCtx->msgCtx) == 7) {
        func_80152434(globalCtx, 0x41);
        this->actionFunc = func_80B9FF80;
        func_80B9FC70(this, 2);
    }
}

void func_80BA00BC(EnZob* this, GlobalContext* globalCtx) {
    func_80B9F86C(this);

    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 4:
            if (Message_ShouldAdvance(globalCtx) && (globalCtx->msgCtx.currentTextId == 0x1212)) {
                switch (globalCtx->msgCtx.choiceIndex) {
                    case 1:
                        func_8019F208();
                        func_80151938(globalCtx, 0x1209);
                        this->unk_304 = 1;
                        func_80B9F7E4(this, 2, 2);
                        break;

                    case 0:
                        func_8019F230();
                        func_80151938(globalCtx, 0x1213);
                        break;
                }
            }
            break;

        case 5:
            if (Message_ShouldAdvance(globalCtx)) {
                switch (globalCtx->msgCtx.currentTextId) {
                    case 0x1208:
                    case 0x120E:
                    case 0x1216:
                        func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                        break;

                    case 0x120C:
                        globalCtx->msgCtx.unk11F10 = 0;
                        this->actionFunc = func_80B9FD24;
                        func_80B9F7E4(this, 8, 0);
                        func_80B9FC70(this, 3);
                        break;

                    case 0x120D:
                    case 0x1211:
                    case 0x1213:
                    case 0x1217:
                        func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                        this->unk_304 = 3;
                        func_80B9F7E4(this, 4, 2);
                        break;

                    case 0x1218:
                        func_80B9FCA0(this, globalCtx);
                        break;

                    case 0x1214:
                        this->unk_2F4 |= 8;
                        func_80B9FCA0(this, globalCtx);
                        break;

                    case 0x120F:
                        gSaveContext.save.weekEventReg[31] |= 8;
                        this->unk_2F4 |= 0x10;
                        func_80B9FCA0(this, globalCtx);
                        break;

                    case 0x1209:
                        func_80152434(globalCtx, 0x3D);
                        this->unk_304 = 4;
                        func_80B9F7E4(this, 0, 0);
                        this->actionFunc = func_80BA005C;
                        func_80B9FC70(this, 1);
                        break;
                }
            }
            break;
    }
}

void func_80BA0318(EnZob* this, GlobalContext* globalCtx) {
    func_80152434(globalCtx, 0x3D);
    this->unk_304 = 4;
    func_80B9F7E4(this, 0, 0);
    this->actionFunc = func_80BA005C;
    func_80B9FC70(this, 1);
}

void func_80BA0374(EnZob* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    func_80B9F86C(this);

    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 4:
            if (Message_ShouldAdvance(globalCtx) && (globalCtx->msgCtx.currentTextId == 0x1205)) {
                switch (globalCtx->msgCtx.choiceIndex) {
                    case 0:
                        func_8019F208();
                        func_80151938(globalCtx, 0x1207);
                        func_80B9F7E4(this, 2, 2);
                        break;

                    case 1:
                        func_8019F230();
                        func_80151938(globalCtx, 0x1206);
                        break;
                }
            }
            break;

        case 5:
            if (Message_ShouldAdvance(globalCtx)) {
                switch (globalCtx->msgCtx.currentTextId) {
                    case 0x11F8:
                        gSaveContext.save.weekEventReg[30] |= 2;
                        func_80151938(globalCtx, 0x11F9);
                        break;

                    case 0x11F9:
                        func_801477B4(globalCtx);
                        this->actionFunc = func_80BA0728;
                        this->unk_304 = 0;
                        func_80B9F7E4(this, 6, 2);
                        this->unk_2F4 &= ~1;
                        break;

                    case 0x11FB:
                    case 0x11FC:
                    case 0x11FF:
                    case 0x1201:
                    case 0x1203:
                        func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                        break;

                    case 0x11FD:
                        this->unk_304 = 3;
                        func_80B9F7E4(this, 4, 2);
                        func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                        break;

                    case 0x11FE:
                        this->unk_304 = 1;
                        func_80B9F7E4(this, 3, 0);
                        func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                        break;

                    case 0x11FA:
                    case 0x1200:
                    case 0x1202:
                    case 0x1204:
                    case 0x1206:
                    case 0x120F:
                    case 0x1210:
                    case 0x1215:
                        func_801477B4(globalCtx);
                        this->actionFunc = func_80BA0728;
                        this->unk_304 = 0;
                        func_80B9F7E4(this, 6, 2);
                        this->unk_2F4 &= ~1;
                        this->unk_2F4 |= 2;
                        break;

                    case 0x1207:
                        func_801477B4(globalCtx);
                        this->actionFunc = func_80BA0318;
                        player->unk_A90 = &this->actor;
                        player->stateFlags3 |= 0x20;
                        break;
                }
            }
            break;
    }
}

void func_80BA0610(EnZob* this, GlobalContext* globalCtx) {
    func_80B9F86C(this);
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actor.flags &= ~ACTOR_FLAG_10000;
        Message_StartTextbox(globalCtx, 0x120D, &this->actor);
        this->unk_304 = 3;
        func_80B9F7E4(this, 5, 2);
        func_80B9FC70(this, 0);
        this->actionFunc = func_80BA00BC;
    } else {
        func_800B8614(&this->actor, globalCtx, 500.0f);
    }
}

void func_80BA06BC(EnZob* this, GlobalContext* globalCtx) {
    func_80B9FD24(this, globalCtx);
    if (!Cutscene_CheckActorAction(globalCtx, 500)) {
        this->actionFunc = func_80BA0610;
        this->actor.flags |= ACTOR_FLAG_10000;
        func_80BA0610(this, globalCtx);
    }
}

void func_80BA0728(EnZob* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f sp28;

    func_80B9F86C(this);

    if (func_800B8718(&this->actor, &globalCtx->state)) {
        if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
            Message_StartTextbox(globalCtx, 0x1208, NULL);
            gSaveContext.save.weekEventReg[30] |= 8;
        } else {
            Message_StartTextbox(globalCtx, 0x1216, NULL);
        }
        this->actionFunc = func_80BA00BC;
        this->unk_304 = 1;
        func_80B9F7E4(this, 2, 2);
        this->unk_30E = 0;
        this->unk_2F4 |= 1;
    } else if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80BA0374;
        func_80B9FA3C(this, globalCtx);
    } else if (Cutscene_CheckActorAction(globalCtx, 500)) {
        this->actionFunc = func_80BA06BC;
    } else if ((this->actor.xzDistToPlayer < 180.0f) && (this->actor.xzDistToPlayer > 60.0f) &&
               Player_IsFacingActor(&this->actor, 0x3000, globalCtx) && Actor_IsFacingPlayer(&this->actor, 0x3000)) {
        func_800B8614(&this->actor, globalCtx, 150.0f);
        func_800B874C(&this->actor, globalCtx, 200.0f, 150.0f);
    }

    sp28.x = this->actor.projectedPos.x;
    sp28.y = this->actor.projectedPos.y;
    sp28.z = this->actor.projectedPos.z;
    func_801A1FB4(3, &sp28, 0x6C, 1000.0f);
}

void func_80BA08E8(EnZob* this, GlobalContext* globalCtx) {
    s32 textId;

    if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
        if (gSaveContext.save.weekEventReg[79] & 1) {
            textId = 0x1257;
            this->unk_304 = 3;
            func_80B9F7E4(this, 4, 2);
        } else if (gSaveContext.save.weekEventReg[78] & 0x40) {
            textId = 0x1256;
            this->unk_304 = 1;
            func_80B9F7E4(this, 2, 2);
        } else {
            textId = 0x1255;
            gSaveContext.save.weekEventReg[78] |= 0x40;
            this->unk_304 = 1;
            func_80B9F7E4(this, 2, 2);
        }
    } else {
        textId = 0x1254;
        this->unk_304 = 3;
        func_80B9F7E4(this, 5, 2);
    }

    Message_StartTextbox(globalCtx, textId, &this->actor);
}

void func_80BA09E0(EnZob* this, GlobalContext* globalCtx) {
    func_80B9F86C(this);
}

void func_80BA0A04(EnZob* this, GlobalContext* globalCtx) {
    u8 temp_v0;

    func_80B9F86C(this);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0x1000, 0x200);
    this->actor.world.rot.y = this->actor.shape.rot.y;

    temp_v0 = Message_GetState(&globalCtx->msgCtx);
    if (temp_v0 != 2) {
        if ((temp_v0 == 5) && Message_ShouldAdvance(globalCtx)) {
            func_801477B4(globalCtx);
            this->actionFunc = func_80BA0AD8;
            this->unk_304 = 0;
            func_80B9F7E4(this, 6, 2);
        }
    } else {
        this->actionFunc = func_80BA0AD8;
        this->unk_304 = 0;
        func_80B9F7E4(this, 6, 2);
    }
}

void func_80BA0AD8(EnZob* this, GlobalContext* globalCtx) {
    func_80B9F86C(this);

    if (this->actor.home.rot.y != this->actor.shape.rot.y) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 2, 0x1000, 0x200);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80BA0A04;
        func_80BA08E8(this, globalCtx);
    } else if ((this->actor.xzDistToPlayer < 120.0f) && Player_IsFacingActor(&this->actor, 0x3000, globalCtx) &&
               Actor_IsFacingPlayer(&this->actor, 0x3000)) {
        func_800B8614(&this->actor, globalCtx, 120.0f);
    }
}

void func_80BA0BB4(EnZob* this, GlobalContext* globalCtx) {
    func_80B9F86C(this);
    if (gSaveContext.save.weekEventReg[79] & 1) {
        this->actionFunc = func_80BA09E0;
        func_80B9F7E4(this, 0, 2);
        this->unk_304 = 5;
    }
}

void func_80BA0C14(EnZob* this, GlobalContext* globalCtx) {
    func_80B9F86C(this);

    if (this->unk_312 < 799) {
        this->unk_312 += 200;
    } else {
        this->unk_312 += 30;
    }

    if (this->unk_312 > 999) {
        this->unk_312 = 999;
    }

    if (Cutscene_CheckActorAction(globalCtx, 515)) {
        if (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 515)]->action == 1) {
            this->actionFunc = func_80BA0CF4;
            this->unk_312 = -1;
        }
    } else {
        this->actionFunc = func_80BA0CF4;
        this->unk_312 = -1;
    }
}

void func_80BA0CF4(EnZob* this, GlobalContext* globalCtx) {
    func_80B9F86C(this);
    if (Cutscene_CheckActorAction(globalCtx, 515) &&
        (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 515)]->action == 2)) {
        this->actionFunc = func_80BA0C14;
    }
}

void EnZob_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnZob* this = THIS;

    Actor_MoveWithGravity(&this->actor);

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 10.0f, 10.0f, 10.0f, 4);

    this->actionFunc(this, globalCtx);

    if ((this->unk_30E != -1) && (ActorCutscene_GetCurrentIndex() != this->unk_306[this->unk_30E])) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->unk_306[this->unk_30E]);
        } else if (ActorCutscene_GetCanPlayNext(this->unk_306[this->unk_30E])) {
            ActorCutscene_Start(this->unk_306[this->unk_30E], &this->actor);
        } else {
            ActorCutscene_SetIntentToPlay(this->unk_306[this->unk_30E]);
        }
    }

    if (this->unk_2F4 & 1) {
        func_800E9250(globalCtx, &this->actor, &this->unk_2F6, &this->unk_2FC, this->actor.focus.pos);
    } else {
        Math_SmoothStepToS(&this->unk_2F6.x, 0, 6, 6200, 100);
        Math_SmoothStepToS(&this->unk_2F6.y, 0, 6, 6200, 100);
        Math_SmoothStepToS(&this->unk_2FC.x, 0, 6, 6200, 100);
        Math_SmoothStepToS(&this->unk_2FC.y, 0, 6, 6200, 100);
    }
}

s32 func_80BA0F64(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnZob* this = THIS;

    if (limbIndex == 9) {
        rot->x += this->unk_2F6.y;
        rot->y += this->unk_2F6.x;
    }
    return false;
}

void func_80BA0FAC(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnZob* this = THIS;

    if (limbIndex == 9) {
        Matrix_MultiplyVector3fByState(&D_80BA1120, &this->actor.focus.pos);
    }
}

void EnZob_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnZob* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    if (this->unk_2F4 & 0x20) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 0, 0, 0, 0, this->unk_312, 1000);
    }

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          func_80BA0F64, func_80BA0FAC, &this->actor);

    if (this->unk_2F4 & 0x20) {
        POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
