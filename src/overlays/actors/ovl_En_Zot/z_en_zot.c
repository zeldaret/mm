/*
 * File: z_en_zot.c
 * Overlay: ovl_En_Zot
 * Description: Great Bay - Zora With Directions to Zora Hall / Pot Game Zora
 */

#include "z_en_zot.h"

#define FLAGS 0x00000019

#define THIS ((EnZot*)thisx)

void EnZot_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZot_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZot_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZot_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B96BEC(EnZot* this, s16 arg1, u8 arg2);
void func_80B97100(EnZot* this, GlobalContext* globalCtx);
void func_80B97240(EnZot* this, GlobalContext* globalCtx);
void func_80B97708(EnZot* this, GlobalContext* globalCtx);
void func_80B97B5C(EnZot* this, GlobalContext* globalCtx);
void func_80B97CC8(EnZot* this, GlobalContext* globalCtx);
void func_80B97FD0(EnZot* this, GlobalContext* globalCtx);
void func_80B980FC(EnZot* this, GlobalContext* globalCtx);
void func_80B98728(EnZot* this, GlobalContext* globalCtx);
void func_80B98998(EnZot* this, GlobalContext* globalCtx);
void func_80B98CA8(EnZot* this, GlobalContext* globalCtx);
void func_80B990A4(EnZot* this, GlobalContext* globalCtx);
void func_80B992C0(EnZot* this, GlobalContext* globalCtx);
void func_80B99384(EnZot* this, GlobalContext* globalCtx);

extern AnimationHeader D_06002898;
extern AnimationHeader D_06004248;
extern UNK_PTR D_060050A0;
extern UNK_PTR D_060058A0;
extern UNK_PTR D_060060A0;
extern FlexSkeletonHeader D_0600D208;
extern AnimationHeader D_0600DE20;
extern AnimationHeader D_0600DF54;
extern AnimationHeader D_0600E400;
extern AnimationHeader D_0600EDF0;
extern AnimationHeader D_0600F4E8;
extern AnimationHeader D_0600FDF0;
extern AnimationHeader D_06010B18;
extern AnimationHeader D_06011424;

const ActorInit En_Zot_InitVars = {
    ACTOR_EN_ZOT,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZO,
    sizeof(EnZot),
    (ActorFunc)EnZot_Init,
    (ActorFunc)EnZot_Destroy,
    (ActorFunc)EnZot_Update,
    (ActorFunc)EnZot_Draw,
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

void func_80B965D0(EnZot* this, GlobalContext* globalCtx) {
    s32 i;

    if ((this->path != NULL) && (this->path->count >= 5)) {
        Vec3s* points = (Vec3s*)Lib_SegmentedToVirtual(this->path->points);

        for (i = 0; i < ARRAY_COUNT(this->unk_2D8); i++, points++) {
            if (this->unk_2D8[i] == NULL) {
                this->unk_2D8[i] = Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_OBJ_TSUBO, points->x, points->y,
                                               points->z, 0, 0, 0, 0x13F);
            }
        }
    }
}

void EnZot_Init(Actor* thisx, GlobalContext* globalCtx2) {
    EnZot* this = THIS;
    GlobalContext* globalCtx = globalCtx2;
    s32 i;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80B97100;
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_0600D208, &D_06004248, this->jointTable, this->morphTable, 20);
    Animation_PlayLoop(&this->skelAnime, &D_0600DE20);
    this->unk_2F0 = 0;
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);

    this->unk_2F2 = 0;
    this->unk_2F4 = 0;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.world.rot.z = this->actor.shape.rot.z = 0;
    this->actor.targetMode = 6;
    this->actor.terminalVelocity = -4.0f;
    this->actor.gravity = -4.0f;

    switch (ENZOT_GET_1F(thisx)) {
        case 0:
            this->actionFunc = func_80B97240;
            this->actor.textId = 0;
            break;

        case 1:
            this->actionFunc = func_80B97708;
            for (i = 0; i < ARRAY_COUNT(this->unk_2D8); i++) {
                this->unk_2D8[i] = NULL;
            }
            if (ENZOT_GET_FC00(&this->actor) != 0x3F) {
                this->path = &globalCtx->setupPathList[ENZOT_GET_FC00(&this->actor)];
                this->unk_2D4 = 0;
                func_80B965D0(this, globalCtx);
            } else {
                this->path = NULL;
            }
            break;

        case 2:
        case 3:
        case 4:
            this->actionFunc = func_80B97B5C;
            if (ENZOT_GET_FC00(&this->actor) != 0x3F) {
                this->path = &globalCtx->setupPathList[ENZOT_GET_FC00(&this->actor)];
            } else {
                this->path = NULL;
            }
            break;

        case 5:
            this->unk_2F2 |= 4;
            this->actionFunc = func_80B97FD0;
            if (ENZOT_GET_FC00(&this->actor) != 0x3F) {
                this->path = &globalCtx->setupPathList[ENZOT_GET_FC00(&this->actor)];
            } else {
                this->path = NULL;
            }
            func_80B96BEC(this, 5, 0);
            break;

        case 6:
            this->actionFunc = func_80B98998;
            func_80B96BEC(this, 2, 0);
            this->actor.colChkInfo.cylRadius = 0;
            this->actor.shape.yOffset = -1400.0f;
            break;

        case 7:
            this->actionFunc = func_80B98998;
            func_80B96BEC(this, 0, 0);
            break;

        case 8:
            this->actor.flags |= 0x2000000;
            this->actionFunc = func_80B98CA8;
            func_80B96BEC(this, 5, 0);
            break;

        case 9:
            this->actionFunc = func_80B990A4;
            break;

        case 10:
            this->actionFunc = func_80B992C0;
            func_80B96BEC(this, 1, 0);
            if (ENZOT_GET_FC00(&this->actor) != 0x3F) {
                this->path = &globalCtx->setupPathList[ENZOT_GET_FC00(&this->actor)];
            } else {
                this->path = NULL;
            }
            break;

        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
            this->actionFunc = func_80B98998;
            func_80B96BEC(this, 2, 0);
            this->actor.colChkInfo.cylRadius = 0;
            this->actor.shape.yOffset = -1400.0f;
            if (!(gSaveContext.weekEventReg[55] & 0x80)) {
                Actor_MarkForDeath(&this->actor);
            }
            break;

        case 18:
            this->actionFunc = func_80B99384;
            if (!(gSaveContext.weekEventReg[55] & 0x80)) {
                Actor_MarkForDeath(&this->actor);
            }
            break;

        case 19:
            func_80B96BEC(this, 7, 0);
            break;

        case 20:
            func_80B96BEC(this, 8, 2);
            break;

        case 21:
            func_80B96BEC(this, 9, 2);
            break;

        case 22:
            this->actionFunc = func_80B980FC;
            if (ENZOT_GET_FC00(&this->actor) != 0x3F) {
                this->path = &globalCtx->setupPathList[ENZOT_GET_FC00(&this->actor)];
            } else {
                this->path = NULL;
            }
            this->actor.home.rot.x = this->actor.home.rot.z;
            break;
    }

    if ((ENZOT_GET_1F(thisx) >= 2) && (ENZOT_GET_1F(thisx) < 11) && (gSaveContext.weekEventReg[55] & 0x80)) {
        Actor_MarkForDeath(&this->actor);
    }
}

void EnZot_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnZot* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
    if (ENZOT_GET_1F(&this->actor) == 8) {
        gSaveContext.weekEventReg[41] &= (u8)~0x20;
    }
}

void func_80B96BEC(EnZot* this, s16 arg1, u8 arg2) {
    static AnimationHeader* sAnimations[] = {
        &D_0600DE20, &D_06002898, &D_0600F4E8, &D_0600E400, &D_0600FDF0,
        &D_06010B18, &D_06011424, &D_0600EDF0, &D_0600DF54, &D_0600DF54,
    };

    if ((arg1 >= 0) && (arg1 < 10)) {
        if (arg1 >= 8) {
            Animation_Change(&this->skelAnime, sAnimations[arg1], 0.0f, arg1 - 8, arg1 - 8, arg2, 0.0f);
        } else {
            Animation_Change(&this->skelAnime, sAnimations[arg1], 1.0f, 0.0f, Animation_GetLastFrame(sAnimations[arg1]),
                             arg2, -5.0f);
        }
        this->unk_2F0 = arg1;
    }
}

s32 func_80B96CE4(EnZot* this) {
    s32 i;
    s32 count = 0;

    for (i = 0; i < ARRAY_COUNT(this->unk_2D8); i++) {
        if (this->unk_2D8[i] == NULL) {
            count++;
        }
    }

    return count;
}

void func_80B96D4C(EnZot* this) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_2D8); i++) {
        if ((this->unk_2D8[i] != NULL) && (this->unk_2D8[i]->update == NULL)) {
            this->unk_2D8[i] = NULL;
        }
    }
}

s32 func_80B96DF0(EnZot* this, GlobalContext* globalCtx) {
    if (Player_IsFacingActor(&this->actor, 0x3000, globalCtx) && Actor_IsFacingPlayer(&this->actor, 0x3000) &&
        (this->actor.xzDistToPlayer < 100.0f)) {
        return true;
    }
    return false;
}

s32 func_80B96E5C(EnZot* this) {
    Path* path = this->path;
    Vec3s* points;
    f32 temp_f12;
    f32 temp_f14;
    f32 phi_f2;

    if (path == NULL) {
        return true;
    }

    points = &((Vec3s*)Lib_SegmentedToVirtual(path->points))[this->unk_2D4];
    temp_f12 = points->x - this->actor.world.pos.x;
    temp_f14 = points->z - this->actor.world.pos.z;
    this->actor.world.rot.y = Math_Atan2S(temp_f12, temp_f14);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 2, 2000, 200);
    phi_f2 = SQ(this->actor.speedXZ) * SQ(3.0f);

    if (this->unk_2D4 == 0) {
        phi_f2 = SQ(20.0f);
    }

    if ((SQ(temp_f12) + SQ(temp_f14)) < phi_f2) {
        this->unk_2D4++;
        if (this->unk_2D4 >= path->count) {
            this->actor.world.pos.x = points->x;
            this->actor.world.pos.z = points->z;
            return true;
        }
    }

    return false;
}

s32 func_80B96FB0(EnZot* this) {
    Path* path = this->path;
    Vec3s* points;
    f32 temp_f12;
    f32 temp_f14;

    if (path == NULL) {
        return true;
    }

    points = &((Vec3s*)Lib_SegmentedToVirtual(path->points))[this->unk_2D4];
    temp_f12 = points->x - this->actor.world.pos.x;
    temp_f14 = points->z - this->actor.world.pos.z;
    this->actor.world.rot.y = Math_Atan2S(temp_f12, temp_f14);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 2, 2000, 200);

    if ((SQ(temp_f12) + SQ(temp_f14)) < SQ(10.0f)) {
        if (this->unk_2F2 & 0x20) {
            this->unk_2D4--;
            if (this->unk_2D4 < 0) {
                this->unk_2D4 = 1;
                this->unk_2F2 &= ~0x20;
                return true;
            }
        } else {
            this->unk_2D4++;
            if (this->unk_2D4 >= path->count) {
                this->unk_2D4 = path->count - 1;
                this->unk_2F2 |= 0x20;
                return true;
            }
        }
    }

    return false;
}

void func_80B97100(EnZot* this, GlobalContext* globalCtx) {
}

void func_80B97110(EnZot* this, GlobalContext* globalCtx) {
    u16 textId;

    if (gSaveContext.playerForm == PLAYER_FORM_ZORA) {
        textId = 0x125F;
        if (gSaveContext.weekEventReg[28] & 0x80) {
            textId = 0x1261;
        } else {
            gSaveContext.weekEventReg[28] |= 0x80;
        }
    } else {
        textId = 0x125C;
        if (gSaveContext.weekEventReg[28] & 0x40) {
            textId = 0x125E;
        } else {
            gSaveContext.weekEventReg[28] |= 0x40;
        }
    }
    func_801518B0(globalCtx, textId, &this->actor);
}

void func_80B97194(EnZot* this, GlobalContext* globalCtx) {
    if ((func_80152498(&globalCtx->msgCtx) == 5) && func_80147624(globalCtx)) {
        switch (globalCtx->msgCtx.unk11F04) {
            case 0x125C:
            case 0x125F:
                func_80151938(globalCtx, globalCtx->msgCtx.unk11F04 + 1);
                break;

            case 0x125D:
            case 0x125E:
            case 0x1260:
            case 0x1261:
                func_801477B4(globalCtx);
                this->actionFunc = func_80B97240;
                break;
        }
    }
}

void func_80B97240(EnZot* this, GlobalContext* globalCtx) {
    if (Actor_RequestTalk(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80B97194;
        func_80B97110(this, globalCtx);
    } else if ((this->actor.xzDistToPlayer < 100.0f) && Player_IsFacingActor(&this->actor, 0x3000, globalCtx) &&
               Actor_IsFacingPlayer(&this->actor, 0x3000)) {
        func_800B8614(&this->actor, &globalCtx->state, 120.0f);
    }
}

void func_80B972E8(EnZot* this, GlobalContext* globalCtx) {
    u16 textId;

    if (gSaveContext.weekEventReg[29] & 0x10) {
        if (gSaveContext.playerForm == PLAYER_FORM_ZORA) {
            textId = 0x126A;
            if (gSaveContext.weekEventReg[29] & 1) {
                textId = 0x126D;
            } else {
                gSaveContext.weekEventReg[29] |= 1;
            }
        } else {
            textId = 0x1267;
            if (gSaveContext.weekEventReg[29] & 2) {
                textId = 0x1269;
            } else {
                gSaveContext.weekEventReg[29] |= 2;
            }
        }
    } else if (gSaveContext.playerForm == PLAYER_FORM_ZORA) {
        textId = 0x1265;
        if (gSaveContext.weekEventReg[29] & 4) {
            textId = 0x1266;
        } else {
            gSaveContext.weekEventReg[29] |= 4;
        }
    } else {
        textId = 0x1262;
        if (gSaveContext.weekEventReg[29] & 8) {
            textId = 0x1264;
        } else {
            gSaveContext.weekEventReg[29] |= 8;
        }
    }
    func_801518B0(globalCtx, textId, &this->actor);
}

void func_80B973BC(EnZot* this, GlobalContext* globalCtx) {
    func_80B96D4C(this);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0x800, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if ((func_80152498(&globalCtx->msgCtx) == 5) && func_80147624(globalCtx)) {
        switch (globalCtx->msgCtx.unk11F04) {
            case 0x126E:
            case 0x1270:
            case 0x1273:
            case 0x1274:
                func_80151938(globalCtx, globalCtx->msgCtx.unk11F04 + 1);
                break;

            case 0x1272:
                func_80151938(globalCtx, 0x126F);
                break;

            case 0x126F:
                func_801159EC(90);
                func_80151938(globalCtx, 0x1270);
                break;

            case 0x1275:
                if (gSaveContext.rupees < 10) {
                    func_80151938(globalCtx, 0x1277);
                } else {
                    func_80151938(globalCtx, 0x1278);
                    func_801159EC(-10);
                }
                break;

            case 0x1276:
                func_80151938(globalCtx, 0x1275);
                break;

            case 0x1271:
            case 0x1277:
            case 0x1278:
            case 0x1279:
                func_801477B4(globalCtx);
                func_80B965D0(this, globalCtx);
                this->actor.flags &= ~0x10000;
                this->actor.textId = 0;
                this->actionFunc = func_80B97708;
                if ((this->actor.cutscene != -1) && !(this->unk_2F2 & 1)) {
                    ActorCutscene_Stop(this->actor.cutscene);
                }
                this->unk_2F2 &= ~1;
                break;
        }
    }

    if (this->unk_2F2 & 1) {
        if (this->actor.cutscene == -1) {
            this->unk_2F2 &= ~1;
        } else if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
            this->unk_2F2 &= ~1;
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    }
}

void func_80B975F8(EnZot* this, GlobalContext* globalCtx) {
    func_80B96D4C(this);
    if (Actor_RequestTalk(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80B973BC;
    } else {
        func_800B8500(&this->actor, &globalCtx->state, 10000.0f, 1000.0f, EXCH_ITEM_NONE);
    }
}

void func_80B9765C(EnZot* this, GlobalContext* globalCtx) {
    if (1) {
        do { } while (0); }

    func_80B96D4C(this);
    if ((func_80152498(&globalCtx->msgCtx) == 5) && func_80147624(globalCtx)) {
        u16 temp = globalCtx->msgCtx.unk11F04;
        u32 temp2;

        if ((temp == 0x1262) || (temp == 0x1267) || (temp == 0x126A) || (temp == 0x126B)) {
            temp2 = temp;
            func_80151938(globalCtx, temp2 + 1);
        } else {
            func_801477B4(globalCtx);
            this->actionFunc = func_80B97708;
        }
    }
}

void func_80B97708(EnZot* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 phi_v1;

    func_80B96D4C(this);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 2, 0x400, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (Actor_RequestTalk(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80B9765C;
        func_80B972E8(this, globalCtx);
        return;
    }

    if (!(player->stateFlags1 & 0x2000000)) {
        phi_v1 = func_80B96CE4(this);
    } else {
        phi_v1 = 0;
    }

    if (phi_v1 != 0) {
        gSaveContext.weekEventReg[29] |= 0x10;
        this->actor.flags |= 0x10000;
        if (phi_v1 == 5) {
            if (gSaveContext.playerForm == PLAYER_FORM_ZORA) {
                this->actor.textId = 0x126E;
            } else {
                this->actor.textId = 0x1272;
            }
        } else if (gSaveContext.playerForm == PLAYER_FORM_ZORA) {
            this->actor.textId = 0x1273;
        } else {
            this->actor.textId = 0x1276;
        }
        this->unk_2F2 |= 1;
        func_80B975F8(this, globalCtx);
        this->actionFunc = func_80B975F8;
    } else if (func_80B96DF0(this, globalCtx)) {
        func_800B8614(&this->actor, &globalCtx->state, 120.0f);
    }
}

void func_80B9787C(EnZot* this, GlobalContext* globalCtx) {
    u16 textId;

    if (this->actor.textId == 0) {
        if (gSaveContext.playerForm == PLAYER_FORM_ZORA) {
            switch (ENZOT_GET_1F(&this->actor)) {
                case 2:
                    if (gSaveContext.weekEventReg[37] & 0x40) {
                        textId = 0x127E;
                    } else {
                        textId = 0x127C;
                        gSaveContext.weekEventReg[37] |= 0x40;
                    }
                    break;

                case 3:
                    if (gSaveContext.weekEventReg[38] & 1) {
                        textId = 0x1284;
                    } else {
                        textId = 0x1282;
                        gSaveContext.weekEventReg[38] |= 1;
                    }
                    break;

                default:
                    if (gSaveContext.weekEventReg[38] & 4) {
                        textId = 0x128A;
                    } else {
                        textId = 0x1288;
                        gSaveContext.weekEventReg[38] |= 4;
                    }
                    break;
            }
        } else {
            switch (ENZOT_GET_1F(&this->actor)) {
                case 2:
                    if (gSaveContext.weekEventReg[37] & 0x20) {
                        textId = 0x127B;
                    } else {
                        textId = 0x1279;
                        gSaveContext.weekEventReg[37] |= 0x20;
                    }
                    break;

                case 3:
                    if (gSaveContext.weekEventReg[37] & 0x80) {
                        textId = 0x1281;
                    } else {
                        textId = 0x127F;
                        gSaveContext.weekEventReg[37] |= 0x80;
                    }
                    break;

                default:
                    if (gSaveContext.weekEventReg[38] & 2) {
                        textId = 0x1287;
                    } else {
                        textId = 0x1285;
                        gSaveContext.weekEventReg[38] |= 2;
                    }
                    break;
            }
        }
        func_801518B0(globalCtx, textId, &this->actor);
    }
}

void func_80B979DC(EnZot* this, GlobalContext* globalCtx) {
    if (func_80B96E5C(this)) {
        this->actionFunc = func_80B97B5C;
        func_80B96BEC(this, 0, 0);
        this->actor.speedXZ = 0.0f;
    } else {
        this->actor.speedXZ = 1.5f;
    }
}

void func_80B97A44(EnZot* this, GlobalContext* globalCtx) {
    if ((func_80152498(&globalCtx->msgCtx) == 5) && func_80147624(globalCtx)) {
        switch (globalCtx->msgCtx.unk11F04) {
            case 0x1279:
            case 0x127C:
            case 0x127F:
            case 0x1282:
            case 0x1285:
            case 0x1288:
                func_80151938(globalCtx, globalCtx->msgCtx.unk11F04 + 1);
                break;

            case 0x127D:
            case 0x127E:
            case 0x1283:
            case 0x1284:
            case 0x1289:
            case 0x128A:
                func_801477B4(globalCtx);
                if (!(this->unk_2F2 & 2)) {
                    this->unk_2F2 |= 2;
                    this->actionFunc = func_80B979DC;
                    func_80B96BEC(this, 1, 0);
                } else {
                    this->actionFunc = func_80B97B5C;
                }
                break;

            default:
                func_801477B4(globalCtx);
                this->actionFunc = func_80B97B5C;
                break;
        }
    }
}

void func_80B97B5C(EnZot* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 2, 0x400, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (Actor_RequestTalk(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80B97A44;
        func_80B9787C(this, globalCtx);
    } else if (func_80B96DF0(this, globalCtx)) {
        func_800B8614(&this->actor, &globalCtx->state, 120.0f);
    }
}

void func_80B97BF8(EnZot* this, GlobalContext* globalCtx) {
    u16 textId;

    if (gSaveContext.playerForm == PLAYER_FORM_ZORA) {
        textId = 0x128C;
    } else {
        textId = 0x128B;
    }
    func_801518B0(globalCtx, textId, &this->actor);
}

void func_80B97C40(EnZot* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0x800, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if ((func_80152498(&globalCtx->msgCtx) == 5) && func_80147624(globalCtx)) {
        func_801477B4(globalCtx);
        this->actionFunc = func_80B97CC8;
    }
}

void func_80B97CC8(EnZot* this, GlobalContext* globalCtx) {
    if (Actor_RequestTalk(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80B97C40;
        func_801518B0(globalCtx, 0x128B, &this->actor);
    } else if (Player_IsFacingActor(&this->actor, 0x3000, globalCtx) && (this->actor.xzDistToPlayer < 100.0f)) {
        func_800B8614(&this->actor, &globalCtx->state, 120.0f);
    }
}

void func_80B97D6C(EnZot* this, GlobalContext* globalCtx) {
    if (func_80B96E5C(this)) {
        this->actionFunc = func_80B97CC8;
        this->actor.speedXZ = 0.0f;
        func_80B96BEC(this, 0, 0);
    } else {
        this->actor.speedXZ = 8.0f;
    }

    if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 5.0f)) {
        Actor_PlaySfxByPos2(&this->actor, NA_SE_EV_ZORA_WALK);
    }
}

void func_80B97E0C(EnZot* this, GlobalContext* globalCtx) {
    if (this->unk_2F2 & 0x40) {
        this->actionFunc = func_80B97D6C;
        func_80B96BEC(this, 3, 0);
    }
}

void func_80B97E4C(EnZot* this, GlobalContext* globalCtx) {
    if (1) {
        do { } while (0); }

    if (this->unk_2F2 & 0x40) {
        func_80B96BEC(this, 0, 0);
    }

    if (!(this->unk_2F2 & 4)) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0x800, 0x100);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }

    if ((func_80152498(&globalCtx->msgCtx) == 5) && func_80147624(globalCtx)) {
        switch (globalCtx->msgCtx.unk11F04) {
            case 0x128C:
                this->unk_2F2 &= ~4;
                func_80B96BEC(this, 6, 2);
                func_80151938(globalCtx, globalCtx->msgCtx.unk11F04 + 1);
                break;

            case 0x128D:
            case 0x128E:
            case 0x128F:
                func_80151938(globalCtx, globalCtx->msgCtx.unk11F04 + 1);
                break;

            case 0x1290:
                func_801477B4(globalCtx);
                this->actionFunc = func_80B97D6C;
                this->unk_2F2 |= 4;
                func_80B96BEC(this, 3, 0);
                gSaveContext.weekEventReg[38] |= 8;
                break;

            case 0x128B:
                func_801477B4(globalCtx);
                this->actionFunc = func_80B97FD0;
                break;
        }
    }
}

void func_80B97FD0(EnZot* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 2, 0x800, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (Actor_RequestTalk(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80B97E4C;
        func_80B97BF8(this, globalCtx);
    } else if (gSaveContext.weekEventReg[38] & 8) {
        if ((this->actor.xzDistToPlayer < 120.0f) && (gSaveContext.playerForm == PLAYER_FORM_ZORA)) {
            this->unk_2F2 |= 4;
            this->actionFunc = func_80B97E0C;
            func_80B96BEC(this, 6, 2);
        }
    } else if (Player_IsFacingActor(&this->actor, 0x3000, globalCtx) && (this->actor.xzDistToPlayer < 100.0f)) {
        func_800B8614(&this->actor, &globalCtx->state, 120.0f);
    }
}

void func_80B980FC(EnZot* this, GlobalContext* globalCtx) {
    if (this->actor.home.rot.x > 0) {
        this->actor.home.rot.x--;
    } else if (func_80B96E5C(this)) {
        this->actionFunc = func_80B97100;
        this->actor.speedXZ = 0.0f;
    } else {
        this->actor.speedXZ = 8.0f;
        if (this->unk_2F0 != 3) {
            func_80B96BEC(this, 3, 0);
        }
    }
}

void func_80B98178(EnZot* this, GlobalContext* globalCtx) {
    u16 textId;
    s32 phi_v0;

    switch (ENZOT_GET_1F(&this->actor)) {
        case 6:
            if (gSaveContext.playerForm == PLAYER_FORM_ZORA) {
                if (CURRENT_DAY == 3) {
                    textId = 0x129D;
                } else if (gSaveContext.weekEventReg[39] & 1) {
                    textId = 0x129C;
                } else {
                    textId = 0x129B;
                    gSaveContext.weekEventReg[39] |= 1;
                }
            } else if (gSaveContext.weekEventReg[38] & 0x80) {
                textId = 0x1293;
            } else {
                textId = 0x1291;
                gSaveContext.weekEventReg[38] |= 0x80;
            }
            break;

        case 7:
            if (gSaveContext.playerForm == PLAYER_FORM_ZORA) {
                if (gSaveContext.weekEventReg[39] & 4) {
                    textId = 0x12AA;
                } else {
                    textId = 0x12A6;
                    gSaveContext.weekEventReg[39] |= 4;
                }
            } else if (Flags_GetSwitch(globalCtx, this->actor.home.rot.z & 0x7F)) {
                textId = 0x12A0;
            } else if (gSaveContext.weekEventReg[39] & 2) {
                textId = 0x12A5;
            } else {
                textId = 0x12A2;
                gSaveContext.weekEventReg[39] |= 2;
            }
            break;

        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
            phi_v0 = (ENZOT_GET_1F(&this->actor) * 4) - 44;
            if (gSaveContext.weekEventReg[79] & 1) {
                phi_v0 += 2;
            }

            if (gSaveContext.playerForm != PLAYER_FORM_ZORA) {
                phi_v0++;
            }
            textId = phi_v0 + 0x1302;
            break;

        default:
            if (gSaveContext.playerForm == PLAYER_FORM_ZORA) {
                textId = 0x129F;
            } else {
                textId = 0x1295;
            }
            break;
    }
    func_801518B0(globalCtx, textId, &this->actor);
}

void func_80B98348(EnZot* this, GlobalContext* globalCtx) {
    s16 y;

    if (ENZOT_GET_1F(&this->actor) == 7) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0x800, 0x100);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    } else if (Actor_IsFacingPlayer(&this->actor, 0x3000)) {
        this->unk_2F2 &= ~8;
    } else {
        this->unk_2F2 |= 8;
        Math_SmoothStepToS(&this->unk_2C4.x, 0, 6, 6200, 100);
        Math_SmoothStepToS(&this->unk_2CA.x, 0, 6, 6200, 100);
        y = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
        if (y > 0) {
            Math_SmoothStepToS(&this->unk_2C4.y, 0x3000, 6, 6200, 100);
            Math_SmoothStepToS(&this->unk_2CA.y, 0x1000, 6, 6200, 100);
        } else {
            Math_SmoothStepToS(&this->unk_2C4.y, -0x3000, 6, 6200, 100);
            Math_SmoothStepToS(&this->unk_2CA.y, -0x1000, 6, 6200, 100);
        }
    }
}

void func_80B9849C(EnZot* this, GlobalContext* globalCtx) {
    func_80B98348(this, globalCtx);
    if (Actor_RequestTalk(&this->actor, &globalCtx->state)) {
        if (this->unk_2D4 == 2) {
            func_801518B0(globalCtx, 0x12AD, &this->actor);
        } else {
            func_801518B0(globalCtx, 0x12B0, &this->actor);
        }
        this->actionFunc = func_80B98728;
    } else {
        func_800B8500(&this->actor, &globalCtx->state, 1000.0f, 1000.0f, EXCH_ITEM_MINUS1);
    }
}

void func_80B9854C(EnZot* this, GlobalContext* globalCtx) {
    func_80B98348(this, globalCtx);
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->actionFunc = func_80B9849C;
        this->actor.flags |= 0x10000;
        func_800B8500(&this->actor, &globalCtx->state, 1000.0f, 1000.0f, EXCH_ITEM_MINUS1);
    } else {
        Actor_PickUp(&this->actor, globalCtx, this->unk_2D4, 10000.0f, 50.0f);
    }
}

void func_80B985EC(EnZot* this, GlobalContext* globalCtx) {
    s32 temp_v0;
    Player* player = GET_PLAYER(globalCtx);

    func_80B98348(this, globalCtx);
    if (func_80152498(&globalCtx->msgCtx) == 0x10) {
        temp_v0 = func_80123810(globalCtx);
        if (temp_v0 > 0) {
            func_801477B4(globalCtx);
            if ((temp_v0 == 0x13) && CHECK_QUEST_ITEM(25) && func_8013A4C4(4)) {
                if (func_8013A4C4(5) && func_8013A4C4(6)) {
                    player->actor.textId = 0x12AE;
                } else {
                    player->actor.textId = 0x12AC;
                }
                REMOVE_QUEST_ITEM(25);
            } else {
                player->actor.textId = 0x12AB;
            }
            this->actionFunc = func_80B98728;
        } else if (temp_v0 < 0) {
            func_80151938(globalCtx, 0x12AB);
            this->actionFunc = func_80B98728;
        }
    }
}

void func_80B98728(EnZot* this, GlobalContext* globalCtx) {
    func_80B98348(this, globalCtx);

    switch (func_80152498(&globalCtx->msgCtx)) {
        case 4:
            if (func_80147624(globalCtx) && (globalCtx->msgCtx.unk11F04 == 0x1293)) {
                switch (globalCtx->msgCtx.choiceIndex) {
                    case 0:
                        func_8019F208();
                        func_80151938(globalCtx, 0x1294);
                        break;

                    case 1:
                        func_8019F230();
                        func_80151938(globalCtx, 0x1298);
                        break;
                }
            }
            break;

        case 5:
            if (func_80147624(globalCtx)) {
                switch (globalCtx->msgCtx.unk11F04) {
                    case 0x1291:
                    case 0x1292:
                    case 0x1296:
                    case 0x1298:
                    case 0x1299:
                    case 0x129B:
                    case 0x129D:
                    case 0x129E:
                    case 0x12A0:
                    case 0x12A2:
                    case 0x12A3:
                    case 0x12A4:
                    case 0x12A6:
                    case 0x12A7:
                    case 0x12A8:
                    case 0x12AE:
                        func_80151938(globalCtx, globalCtx->msgCtx.unk11F04 + 1);
                        break;

                    case 0x12A9:
                    case 0x12AA:
                        func_80151938(globalCtx, 0xFF);
                        this->actionFunc = func_80B985EC;
                        break;

                    case 0x1294:
                        if (CURRENT_DAY == 3) {
                            func_80151938(globalCtx, 0x1296);
                        } else {
                            func_80151938(globalCtx, 0x1295);
                        }
                        break;

                    case 0x12AB:
                        func_801477B4(globalCtx);
                        this->actionFunc = func_80B98998;
                        break;

                    case 0x12AC:
                        func_801477B4(globalCtx);
                        this->unk_2D4 = 2;
                        this->actionFunc = func_80B9854C;
                        func_80B9854C(this, globalCtx);
                        break;

                    case 0x12AF:
                        func_801477B4(globalCtx);
                        this->unk_2D4 = 4;
                        this->actionFunc = func_80B9854C;
                        func_80B9854C(this, globalCtx);
                        break;

                    default:
                        func_801477B4(globalCtx);
                        this->actionFunc = func_80B98998;
                        this->actor.flags &= ~0x10000;
                        break;
                }
            }
            break;
    }
}

void func_80B98998(EnZot* this, GlobalContext* globalCtx) {
    this->unk_2F2 &= ~8;
    if (Actor_RequestTalk(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80B98728;
        func_80B98178(this, globalCtx);
    } else if ((this->actor.xzDistToPlayer < 100.0f) && Player_IsFacingActor(&this->actor, 0x3000, globalCtx) &&
               Actor_IsFacingPlayer(&this->actor, 0x7000)) {
        func_800B8614(&this->actor, &globalCtx->state, 120.0f);
    }
}

void func_80B98A4C(EnZot* this, GlobalContext* globalCtx) {
    u16 textId;

    if (gSaveContext.playerForm == PLAYER_FORM_ZORA) {
        if (gSaveContext.weekEventReg[39] & 0x80) {
            textId = 0x12B6;
        } else {
            textId = 0x12B4;
            gSaveContext.weekEventReg[39] |= 0x80;
        }
    } else if (gSaveContext.weekEventReg[39] & 0x40) {
        textId = 0x12B3;
    } else {
        textId = 0x12B1;
        gSaveContext.weekEventReg[39] |= 0x40;
    }
    func_801518B0(globalCtx, textId, &this->actor);
}

void func_80B98AD0(EnZot* this, GlobalContext* globalCtx) {
    if ((func_80152498(&globalCtx->msgCtx) == 5) && func_80147624(globalCtx)) {
        switch (globalCtx->msgCtx.unk11F04) {
            case 0x12B1:
            case 0x12B4:
            case 0x12B7:
            case 0x12B9:
                func_80151938(globalCtx, globalCtx->msgCtx.unk11F04 + 1);
                break;

            case 0x12B8:
                func_801477B4(globalCtx);
                this->actionFunc = func_80B98CA8;
                gSaveContext.weekEventReg[41] &= (u8)~0x20;
                func_8019C300(0);
                break;

            case 0x12BA:
                func_801477B4(globalCtx);
                this->actionFunc = func_80B98CA8;
                gSaveContext.weekEventReg[41] |= 0x20;
                func_8019C300(0);
                break;

            default:
                func_801477B4(globalCtx);
                this->actionFunc = func_80B98CA8;
                break;
        }
    }
}

void func_80B98BF4(EnZot* this, GlobalContext* globalCtx) {
    if (Actor_RequestTalk(&this->actor, &globalCtx->state)) {
        this->actor.flags &= ~0x10000;
        if (gSaveContext.weekEventReg[41] & 0x20) {
            func_801518B0(globalCtx, 0x12B7, &this->actor);
            this->actionFunc = func_80B98AD0;
        } else {
            func_801518B0(globalCtx, 0x12B9, &this->actor);
            this->actionFunc = func_80B98AD0;
        }
    } else {
        func_800B8614(&this->actor, &globalCtx->state, 120.0f);
    }
}

void func_80B98CA8(EnZot* this, GlobalContext* globalCtx) {
    if (func_800B8718(&this->actor, &globalCtx->state)) {
        globalCtx->msgCtx.unk1202A = 4;
        func_8019B544(0xFFFF);
        this->actionFunc = func_80B98BF4;
        this->actor.flags |= 0x10000;
        func_800B8614(&this->actor, &globalCtx->state, 120.0f);
    } else if (Actor_RequestTalk(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80B98AD0;
        func_80B98A4C(this, globalCtx);
    } else {
        if ((this->actor.xzDistToPlayer < 100.0f) && Player_IsFacingActor(&this->actor, 0x3000, globalCtx)) {
            func_800B8614(&this->actor, &globalCtx->state, 120.0f);
        }

        if ((gSaveContext.playerForm == PLAYER_FORM_ZORA) || (this->actor.xzDistToPlayer < 100.0f)) {
            func_800B874C(&this->actor, &globalCtx->state, 120.0, 100.0f);
        }
    }

    if (this->actor.xzDistToPlayer > 100.0f) {
        gSaveContext.weekEventReg[41] &= (u8)~0x20;
    }
}

void func_80B98E10(EnZot* this, GlobalContext* globalCtx) {
    u16 textId;

    if (gSaveContext.playerForm == PLAYER_FORM_ZORA) {
        if (Flags_GetSwitch(globalCtx, this->actor.home.rot.z & 0x7F)) {
            if (gSaveContext.weekEventReg[40] & 4) {
                textId = 0x12C5;
            } else {
                textId = 0x12C3;
                gSaveContext.weekEventReg[40] |= 4;
            }
        } else if (gSaveContext.weekEventReg[40] & 2) {
            textId = 0x12C2;
        } else {
            textId = 0x12C0;
            gSaveContext.weekEventReg[40] |= 2;
        }
    } else {
        if (Flags_GetSwitch(globalCtx, this->actor.home.rot.z & 0x7F)) {
            if (this->unk_2F2 & 0x10) {
                textId = 0x12BF;
            } else {
                textId = 0x12BE;
                this->unk_2F2 |= 0x10;
            }
        } else if (gSaveContext.weekEventReg[40] & 1) {
            textId = 0x12BC;
        } else {
            gSaveContext.weekEventReg[40] |= 1;
            this->unk_2F2 |= 4;
            textId = 0x12BB;
        }
    }
    func_801518B0(globalCtx, textId, &this->actor);
}

void func_80B98F30(EnZot* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->actionFunc = func_80B990A4;
    } else {
        Actor_PickUp(&this->actor, globalCtx, 2, 10000.0f, 50.0f);
    }
}

void func_80B98F94(EnZot* this, GlobalContext* globalCtx) {
    if (!(this->unk_2F2 & 4)) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0x800, 0x100);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }

    if ((func_80152498(&globalCtx->msgCtx) == 5) && func_80147624(globalCtx)) {
        switch (globalCtx->msgCtx.unk11F04) {
            case 0x12BB:
                this->unk_2F2 &= ~4;

            case 0x12BC:
            case 0x12C0:
            case 0x12C3:
                func_80151938(globalCtx, globalCtx->msgCtx.unk11F04 + 1);
                break;

            case 0x12BE:
                func_801477B4(globalCtx);
                this->actionFunc = func_80B98F30;
                func_80B98F30(this, globalCtx);
                break;

            default:
                func_801477B4(globalCtx);
                this->actionFunc = func_80B990A4;
                break;
        }
    }
}

void func_80B990A4(EnZot* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 2, 0x400, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (Actor_RequestTalk(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80B98F94;
        func_80B98E10(this, globalCtx);
    } else if (Player_IsFacingActor(&this->actor, 0x3000, globalCtx) && (this->actor.xzDistToPlayer < 100.0f)) {
        func_800B8614(&this->actor, &globalCtx->state, 120.0f);
    }
}

void func_80B99160(EnZot* this, GlobalContext* globalCtx) {
    u16 textId;

    if (gSaveContext.playerForm == PLAYER_FORM_ZORA) {
        if (gSaveContext.weekEventReg[40] & 0x10) {
            textId = 0x12CD;
        } else {
            textId = 0x12CA;
            gSaveContext.weekEventReg[40] |= 0x10;
        }
    } else if (gSaveContext.weekEventReg[40] & 8) {
        textId = 0x12C9;
    } else {
        textId = 0x12C6;
        gSaveContext.weekEventReg[40] |= 8;
    }
    func_801518B0(globalCtx, textId, &this->actor);
}

void func_80B991E4(EnZot* this, GlobalContext* globalCtx) {
    if (1) {
        do { } while (0); }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0x800, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if ((func_80152498(&globalCtx->msgCtx) == 5) && func_80147624(globalCtx)) {
        u16 temp = globalCtx->msgCtx.unk11F04;
        u32 temp2;

        if ((temp == 0x12C6) || (temp == 0x12C7) || (temp == 0x12CA) || (temp == 0x12CB)) {
            temp2 = temp;
            func_80151938(globalCtx, temp2 + 1);
        } else {
            func_801477B4(globalCtx);
            this->actionFunc = func_80B992C0;
            func_80B96BEC(this, 1, 0);
        }
    }
}

void func_80B992C0(EnZot* this, GlobalContext* globalCtx) {
    if (Actor_RequestTalk(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80B991E4;
        func_80B99160(this, globalCtx);
        this->actor.speedXZ = 0.0f;
        func_80B96BEC(this, 0, 0);
    } else {
        if (Player_IsFacingActor(&this->actor, 0x3000, globalCtx) && (this->actor.xzDistToPlayer < 100.0f)) {
            func_800B8614(&this->actor, &globalCtx->state, 120.0f);
        }
        this->actor.speedXZ = 1.5f;
        func_80B96FB0(this);
    }
}

void func_80B99384(EnZot* this, GlobalContext* globalCtx) {
}

void EnZot_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnZot* this = THIS;

    Actor_MoveWithGravity(&this->actor);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 15.0f, 30.0f, 5);

    this->unk_2F2 &= ~0x40;
    if (SkelAnime_Update(&this->skelAnime) && (this->unk_2F0 != 0)) {
        this->unk_2F2 |= 0x40;
    }

    this->actionFunc(this, globalCtx);
    if (!(this->unk_2F2 & 8)) {
        if (!(this->unk_2F2 & 4) && func_80B96DF0(this, globalCtx)) {
            func_800E9250(globalCtx, &this->actor, &this->unk_2C4, &this->unk_2CA, this->actor.focus.pos);
        } else {
            Math_SmoothStepToS(&this->unk_2C4.x, 0, 6, 6200, 100);
            Math_SmoothStepToS(&this->unk_2C4.y, 0, 6, 6200, 100);
            Math_SmoothStepToS(&this->unk_2CA.x, 0, 6, 6200, 100);
            Math_SmoothStepToS(&this->unk_2CA.y, 0, 6, 6200, 100);
        }
    }

    if (DECR(this->unk_2EE) == 0) {
        this->unk_2EE = Rand_S16Offset(60, 60);
    }

    this->unk_2EC = this->unk_2EE;
    if (this->unk_2EC > 2) {
        this->unk_2EC = 0;
    }
}

Gfx* func_80B99580(GraphicsContext* gfxCtx) {
    Gfx* dList = GRAPH_ALLOC(gfxCtx, sizeof(Gfx) * 2);

    gSPEndDisplayList(dList);

    return dList;
}

s32 EnZot_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnZot* this = THIS;
    s32 pad;

    if (limbIndex == 15) {
        Matrix_InsertTranslation(1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->unk_2C4.y, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_2C4.x, MTXMODE_APPLY);
        Matrix_InsertTranslation(-1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    }

    if (limbIndex == 8) {
        Matrix_InsertXRotation_s(this->unk_2CA.y * -1, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_2CA.x * -1, MTXMODE_APPLY);
    }

    if (((this->unk_2F0 == 8) || (this->unk_2F0 == 9)) &&
        ((limbIndex == 8) || (limbIndex == 10) || (limbIndex == 13))) {
        rot->y += (s16)(Math_SinS(globalCtx->state.frames * ((limbIndex * 50) + 0x814)) * 200.0f);
        rot->z += (s16)(Math_CosS(globalCtx->state.frames * ((limbIndex * 50) + 0x940)) * 200.0f);
    }
    return false;
}

void EnZot_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80B99934 = { 400.0f, 0.0f, 0.0f };
    EnZot* this = THIS;

    if (limbIndex == 15) {
        Matrix_MultiplyVector3fByState(&D_80B99934, &this->actor.focus.pos);
    }
}

void EnZot_Draw(Actor* thisx, GlobalContext* globalCtx) {
    UNK_PTR sp4C[] = {
        &D_060050A0,
        &D_060058A0,
        &D_060060A0,
    };
    EnZot* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sp4C[this->unk_2EC]));
    gSPSegment(POLY_OPA_DISP++, 0x0C, func_80B99580(globalCtx->state.gfxCtx));

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnZot_OverrideLimbDraw, EnZot_PostLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
