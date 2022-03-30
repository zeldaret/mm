/*
 * File: z_en_dns.c
 * Overlay: ovl_En_Dns
 * Description: Deku Palace - King's Chamber Deku Guard
 */

#include "z_en_dns.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnDns*)thisx)

void EnDns_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDns_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDns_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDns_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_8092D330(EnDns* this, GlobalContext* globalCtx);
void EnDns_DoNothing(EnDns* this, GlobalContext* globalCtx);
void func_8092D4D8(EnDns* this, GlobalContext* globalCtx);

typedef enum {
    /*  0 */ EN_DNS_ANIMATION_IDLE_1,
    /*  1 */ EN_DNS_ANIMATION_IDLE_2,
    /*  2 */ EN_DNS_ANIMATION_WALK_1,
    /*  3 */ EN_DNS_ANIMATION_WALK_2,
    /*  4 */ EN_DNS_ANIMATION_SURPRISE_START,
    /*  5 */ EN_DNS_ANIMATION_SURPRISE_LOOP,
    /*  6 */ EN_DNS_ANIMATION_RUN_START,
    /*  7 */ EN_DNS_ANIMATION_RUN_LOOP,
    /*  8 */ EN_DNS_ANIMATION_DANCE,
    /*  9 */ EN_DNS_ANIMATION_FLIP,
    /* 10 */ EN_DNS_ANIMATION_MAX,
} EnDnsAnimationIndex;

static s32 D_8092DCB0[] = {
    0x00172000, 0x050E082F, 0x0C100E08, 0x200C1000, 0x00172000, 0x050E0830, 0x0C100E08, 0x210C1000,
    0x00172000, 0x050E0831, 0x0C100E08, 0x220C1000, 0x00172000, 0x050E0832, 0x0C100E08, 0x230C1000,
    0x0E08330C, 0x09000015, 0x1C014016, 0x10000000, 0x0E082E0C, 0x10000000,
};

const ActorInit En_Dns_InitVars = {
    ACTOR_EN_DNS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNS,
    sizeof(EnDns),
    (ActorFunc)EnDns_Init,
    (ActorFunc)EnDns_Destroy,
    (ActorFunc)EnDns_Update,
    (ActorFunc)EnDns_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 18, 46, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 1, 0, 0, 0, MASS_IMMOVABLE };

static AnimationInfoS sAnimations[] = {
    { &gKingsChamberDekuGuardIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gKingsChamberDekuGuardIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gKingsChamberDekuGuardWalkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gKingsChamberDekuGuardWalkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gKingsChamberDekuGuardSurpriseStartAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gKingsChamberDekuGuardSurpriseLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gKingsChamberDekuGuardRunStartAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gKingsChamberDekuGuardRunLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gKingsChamberDekuGuardDanceAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gKingsChamberDekuGuardFlipAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
};

void func_8092C5C0(EnDns* this) {
    s32 pad;

    if (((this->animationIndex == EN_DNS_ANIMATION_WALK_1) || (this->animationIndex == EN_DNS_ANIMATION_WALK_2) ||
         (this->animationIndex == EN_DNS_ANIMATION_RUN_START) || (this->animationIndex == EN_DNS_ANIMATION_RUN_LOOP)) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 3.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_WALK);
    }
}

s32 func_8092C63C(EnDns* this, s32 arg1) {
    s32 phi_v1 = false;
    s32 ret = false;

    switch (arg1) {
        case EN_DNS_ANIMATION_IDLE_1:
        case EN_DNS_ANIMATION_IDLE_2:
            if ((this->animationIndex != EN_DNS_ANIMATION_IDLE_1) &&
                (this->animationIndex != EN_DNS_ANIMATION_IDLE_2)) {
                phi_v1 = true;
            }
            break;

        case EN_DNS_ANIMATION_WALK_1:
        case EN_DNS_ANIMATION_WALK_2:
            if ((this->animationIndex != EN_DNS_ANIMATION_WALK_1) &&
                (this->animationIndex != EN_DNS_ANIMATION_WALK_2)) {
                phi_v1 = true;
            }
            break;

        default:
            if (this->animationIndex != arg1) {
                phi_v1 = true;
            }
    }

    if (phi_v1) {
        this->animationIndex = arg1;
        ret = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, arg1);
    }

    return ret;
}

void func_8092C6FC(EnDns* this, GlobalContext* globalCtx) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_8092C740(EnDns* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 temp = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    Vec3f sp34;
    Vec3f sp28;

    Math_ApproachS(&this->unk_2CE, temp, 4, 0x2AA8);
    this->unk_2CE = CLAMP(this->unk_2CE, -0x3FFC, 0x3FFC);

    Math_Vec3f_Copy(&sp28, &player->actor.world.pos);
    sp28.y = player->bodyPartsPos[7].y + 3.0f;
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    sp34.y += 10.0f;
    temp = Math_Vec3f_Pitch(&sp34, &sp28);
    Math_ApproachS(&this->unk_2CC, temp, 4, 0x2AA8);
    this->unk_2CC = CLAMP(this->unk_2CC, -0x16C0, 0xE38);
}

void func_8092C86C(EnDns* this, GlobalContext* globalCtx) {
    if ((this->unk_2C6 & 8) && (DECR(this->unk_2DC) == 0)) {
        func_8092C740(this, globalCtx);
        this->unk_2C6 &= ~0x10;
        this->unk_2C6 |= 0x20;
    } else if (this->unk_2C6 & 0x20) {
        this->unk_2C6 &= ~0x20;
        this->unk_2CC = 0;
        this->unk_2CE = 0;
        this->unk_2DC = 20;
    } else if (DECR(this->unk_2DC) == 0) {
        this->unk_2C6 |= 0x10;
    }
}

void func_8092C934(EnDns* this) {
    if ((this->unk_2C6 & 0x40) && (DECR(this->blinkTimer) == 0)) {
        this->eyeIndex++;
        if (this->eyeIndex >= 4) {
            this->blinkTimer = Rand_S16Offset(30, 30);
            this->eyeIndex = 0;
        }
    }
}

s32* func_8092C9BC(EnDns* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (!(gSaveContext.save.weekEventReg[23] & 0x20)) {
        if (player->transformation != PLAYER_FORM_DEKU) {
            return &D_8092DCB0[16];
        } else if (this->unk_2FC != 0) {
            return &D_8092DCB0[20];
        }
    }

    switch (ENDNS_GET_7(&this->actor)) {
        case ENDNS_GET_7_0:
            return &D_8092DCB0[0];

        case ENDNS_GET_7_1:
            return &D_8092DCB0[4];

        case ENDNS_GET_7_2:
            return &D_8092DCB0[8];

        case ENDNS_GET_7_3:
            return &D_8092DCB0[12];
    }

    return 0;
}

s32 func_8092CA74(EnDns* this) {
    switch (ENDNS_GET_7(&this->actor)) {
        case ENDNS_GET_7_0:
            return 465;

        case ENDNS_GET_7_1:
            return 466;

        case ENDNS_GET_7_2:
            return 467;

        case ENDNS_GET_7_3:
            return 468;
    }

    return 0;
}

s32 func_8092CAD0(EnDns* this, GlobalContext* globalCtx) {
    s32 ret = false;

    if (this->unk_2C6 & 7) {
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
            SubS_UpdateFlags(&this->unk_2C6, 0, 7);
            this->unk_2C6 &= ~0x10;
            if (ENDNS_GET_4000(&this->actor)) {
                this->unk_2F0 = 0.0f;
                if (this->unk_2D2 != 0) {
                    this->unk_2F0 = this->skelAnime.curFrame;
                    func_8092C63C(this, EN_DNS_ANIMATION_WALK_1);
                }
                this->unk_2DA = this->actor.world.rot.y;
            }
            this->unk_1E0 = func_8092C9BC(this, globalCtx);
            this->actionFunc = func_8092D4D8;
            ret = true;
        }
    }
    return ret;
}

s32 func_8092CB98(EnDns* this, GlobalContext* globalCtx) {
    s32 phi_v1 = 0;

    if (globalCtx->csCtx.state != 0) {
        if (!(this->unk_2C6 & 0x80)) {
            this->unk_2C8 = func_8092CA74(this);
            this->actor.flags &= ~ACTOR_FLAG_1;
            SubS_UpdateFlags(&this->unk_2C6, 0, 7);
            this->unk_2C6 |= 0x80;
            this->unk_1D8 = 0xFF;
        }
        phi_v1 = 1;
    } else if (this->unk_2C6 & 0x80) {
        this->actor.flags |= ACTOR_FLAG_1;
        SubS_UpdateFlags(&this->unk_2C6, 3, 7);
        this->unk_2C6 &= ~0x80;
    }
    return phi_v1;
}

s32 func_8092CC68(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad[2];
    s32 ret = false;
    s16 bgId;

    if (!Play_InCsMode(globalCtx) && (player->actor.bgCheckFlags & 1) && (player->transformation != PLAYER_FORM_DEKU)) {
        bgId = player->actor.floorBgId;
        if (SurfaceType_GetSceneExitIndex(&globalCtx->colCtx, player->actor.floorPoly, bgId) != 4) {
            ret = true;
        }
    }

    return ret;
}

s32 func_8092CCEC(EnDns* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;
    Vec3f sp3C = player->actor.world.pos;
    Vec3f sp30 = this->actor.world.pos;
    s16 sp2E;

    Math_Vec3f_Copy(&sp30, &this->actor.world.pos);
    Math_Vec3f_Copy(&sp3C, &player->actor.world.pos);
    this->unk_2D6 = Math_Vec3f_Yaw(&gZeroVec3f, &sp3C);
    this->unk_2D4 = Math_Vec3f_Yaw(&gZeroVec3f, &sp30);
    this->unk_2EC = Math_Vec3f_DistXZ(&sp30, &gZeroVec3f);
    sp2E = Math_Vec3f_Yaw(&gZeroVec3f, &sp3C);
    sp2E -= Math_Vec3f_Yaw(&gZeroVec3f, &sp30);
    this->unk_2D8 = (Rand_ZeroOne() * 182.0f) + 182.0f;
    this->unk_2D8 = (sp2E > 0) ? this->unk_2D8 : -this->unk_2D8;
    this->unk_2D0 = 0x28;
    this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
    return 1;
}

s32 func_8092CE38(EnDns* this) {
    static s32 D_8092DE00[] = { EN_DNS_ANIMATION_DANCE, EN_DNS_ANIMATION_DANCE, EN_DNS_ANIMATION_FLIP };
    s16 frame;
    s32 pad;
    Vec3f sp2C;
    s32 ret = false;

    if ((this->unk_2C6 & 0x200) || Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        func_8092C63C(this, D_8092DE00[this->unk_2D2]);
        this->unk_2C6 &= ~0x200;
        this->skelAnime.curFrame = 0.0f;
        if (this->unk_2D2 == 2) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_JUMP);
        }
        this->unk_2D2++;
        if (this->unk_2D2 >= 3) {
            this->unk_2D2 = 0;
        }
        ret = true;
    } else {
        if (this->unk_2D2 == 0) {
            if (Animation_OnFrame(&this->skelAnime, 13.0f)) {
                this->actor.world.rot.y = BINANG_ROT180(this->actor.world.rot.y);
                this->unk_2E4 = 0.0f;
                this->actor.shape.rot.y = this->actor.world.rot.y;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_JUMP);
            } else if (this->skelAnime.curFrame < 13.0f) {
                frame = this->skelAnime.curFrame;
                this->actor.shape.rot.y = this->actor.world.rot.y;
                frame *= 2520;
                this->actor.shape.rot.y += frame;
                this->unk_2E4 -= -(40.0f / 13.0f);
            }
        } else {
            if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 6.0f) ||
                Animation_OnFrame(&this->skelAnime, 13.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_WALK);
            }

            if (this->skelAnime.curFrame > 7.0f) {
                this->unk_2E4 += -(20.0f / 13.0f);
            }
        }
        sp2C.x = this->unk_2E4;
        sp2C.y = 0.0f;
        sp2C.z = 0.0f;
        Lib_Vec3f_TranslateAndRotateY(&this->actor.home.pos, this->actor.world.rot.y, &sp2C, &this->actor.world.pos);
    }

    return ret;
}

s32 func_8092D068(EnDns* this) {
    s32 ret = false;

    if (ENDNS_GET_8000(&this->actor)) {
        if (gSaveContext.save.weekEventReg[23] & 0x20) {
            ret = true;
        }
    } else if (ENDNS_GET_4000(&this->actor)) {
        if ((gSaveContext.save.weekEventReg[9] & 0x80) && !(gSaveContext.save.weekEventReg[23] & 0x20)) {
            ret = true;
        }
    } else if (!(gSaveContext.save.weekEventReg[9] & 0x80) && !(gSaveContext.save.weekEventReg[23] & 0x20)) {
        ret = true;
    }

    return ret;
}

void func_8092D108(EnDns* this, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    Matrix_SetStateRotationAndTranslation(this->actor.home.pos.x, this->actor.home.pos.y, this->actor.home.pos.z,
                                          &this->actor.home.rot);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gKingsChamberDekuGuardDekuFlower);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_8092D1B8(EnDns* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 sp22 = this->actor.world.rot.y;

    if (ENDNS_GET_4000(&this->actor)) {
        func_8092CE38(this);
    }

    if (!ENDNS_GET_4000(&this->actor) || (this->unk_2D2 != 0)) {
        if (!(gSaveContext.save.weekEventReg[23] & 0x20) && !(gSaveContext.eventInf[1] & 0x20) &&
            func_8092CC68(globalCtx)) {
            player->stateFlags1 |= 0x20;
            this->unk_2C6 |= 0x100;
            SubS_UpdateFlags(&this->unk_2C6, 4, 7);
            play_sound(NA_SE_SY_FOUND);
            gSaveContext.eventInf[1] |= 0x20;
            this->unk_2F4 = func_8092CCEC;
            func_8092C63C(this, EN_DNS_ANIMATION_WALK_1);
            this->actionFunc = EnDns_DoNothing;
        } else if (gSaveContext.eventInf[1] & 0x40) {
            func_8092CCEC(this, globalCtx);
            func_8092C63C(this, EN_DNS_ANIMATION_WALK_1);
            this->actionFunc = func_8092D330;
        }
        Math_ApproachS(&this->actor.shape.rot.y, sp22, 3, 0x2AA8);
    }
}

void EnDns_DoNothing(EnDns* this, GlobalContext* globalCtx) {
}

void func_8092D330(EnDns* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f sp30 = gZeroVec3f;
    s16 temp = this->unk_2D6 - this->unk_2D4;

    if (ABS_ALT(temp) < 0xC16) {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0x2AA8);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    } else {
        this->actor.world.pos.x = Math_SinS(this->unk_2D4) * this->unk_2EC;
        this->actor.world.pos.z = Math_CosS(this->unk_2D4) * this->unk_2EC;
        this->unk_2D4 += this->unk_2D8;
        sp30.x = Math_SinS(this->unk_2D4) * this->unk_2EC;
        sp30.z = Math_CosS(this->unk_2D4) * this->unk_2EC;
        Math_ApproachS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &sp30), 3, 0x2AA8);
        Actor_MoveWithGravity(&this->actor);
    }
    if ((this->unk_2C6 & 0x100) && (DECR(this->unk_2D0) == 0)) {
        this->unk_2C6 &= ~0x100;
        globalCtx->nextEntranceIndex = 0x5010;
        gSaveContext.nextCutsceneIndex = 0;
        globalCtx->sceneLoadFlag = 0x14;
        globalCtx->unk_1887F = 3;
        gSaveContext.nextTransition = 3;
    }
}

void func_8092D4D8(EnDns* this, GlobalContext* globalCtx) {
    s16 sp2E = this->actor.yawTowardsPlayer;

    if (ENDNS_GET_4000(&this->actor) && (this->unk_2D2 == 0)) {
        if (func_8092CE38(this)) {
            func_8092C63C(this, EN_DNS_ANIMATION_WALK_1);
        }
    } else if (func_8010BF58(&this->actor, globalCtx, this->unk_1E0, this->unk_2F4, &this->unk_1DC)) {
        SubS_UpdateFlags(&this->unk_2C6, 3, 7);
        this->unk_2F4 = NULL;
        if (ENDNS_GET_4000(&this->actor)) {
            if (!(gSaveContext.eventInf[1] & 0x20)) {
                this->skelAnime.curFrame = this->unk_2F0;
                this->actor.world.rot.y = this->unk_2DA;
                func_8092C63C(this, EN_DNS_ANIMATION_DANCE);
            }
            this->unk_2CC = 0;
            this->unk_2CE = 0;
            this->unk_2C6 |= 0x10;
        }
        this->actionFunc = func_8092D1B8;
    } else {
        Math_ApproachS(&this->actor.shape.rot.y, sp2E, 3, 0x2AA8);
    }
}

void func_8092D5E8(EnDns* this, GlobalContext* globalCtx) {
    static s32 D_8092DE0C[] = {
        EN_DNS_ANIMATION_IDLE_1,
        EN_DNS_ANIMATION_IDLE_1,
        EN_DNS_ANIMATION_SURPRISE_START,
        EN_DNS_ANIMATION_RUN_START,
    };
    s32 temp_v0;
    u32 temp_v1;

    if (Cutscene_CheckActorAction(globalCtx, this->unk_2C8)) {
        temp_v0 = Cutscene_GetActorActionIndex(globalCtx, this->unk_2C8);
        temp_v1 = globalCtx->csCtx.actorActions[temp_v0]->action;
        if (this->unk_1D8 != (u8)temp_v1) {
            func_8092C63C(this, D_8092DE0C[temp_v1]);
            this->unk_1D8 = temp_v1;
        }

        if (((this->animationIndex == EN_DNS_ANIMATION_SURPRISE_START) ||
             (this->animationIndex == EN_DNS_ANIMATION_RUN_START)) &&
            Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            func_8092C63C(this, this->animationIndex + 1);
        }

        Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, temp_v0);
    }
}

void EnDns_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnDns* this = THIS;

    if (!func_8092D068(this)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 18.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &gKingsChamberDekuGuardSkel, NULL, this->jointTable, this->morphTable,
                   KINGS_CHAMBER_DEKU_GUARD_LIMB_MAX);
    this->animationIndex = -1;
    func_8092C63C(this, EN_DNS_ANIMATION_WALK_1);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.targetMode = 0;
    this->actor.gravity = -0.8f;
    this->unk_2D2 = 0;
    this->unk_2C6 = 0;
    SubS_UpdateFlags(&this->unk_2C6, 3, 7);
    this->unk_2C6 |= (0x40 | 0x10);
    this->unk_2C6 |= 0x200;
    if (gSaveContext.save.weekEventReg[9] & 0x80) {
        this->unk_2FC = 1;
    } else {
        this->unk_2FC = 0;
    }
    this->actionFunc = func_8092D1B8;
    gSaveContext.eventInf[1] &= (u8)~0x20;
    gSaveContext.eventInf[1] &= (u8)~0x40;
}

void EnDns_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnDns* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnDns_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnDns* this = THIS;

    if (!func_8092CAD0(this, globalCtx) && func_8092CB98(this, globalCtx)) {
        func_8092D5E8(this, globalCtx);
        SkelAnime_Update(&this->skelAnime);
        func_8092C5C0(this);
    } else {
        this->actionFunc(this, globalCtx);
        SkelAnime_Update(&this->skelAnime);
        func_8092C934(this);
        func_8092C86C(this, globalCtx);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 12.0f, 0.0f, 4);
        func_8013C964(&this->actor, globalCtx, 80.0f, 40.0f, 0, this->unk_2C6 & 7);
        Actor_SetFocus(&this->actor, 34.0f);
        func_8092C6FC(this, globalCtx);
        func_8092C5C0(this);
    }
}

s32 func_8092D954(s16 arg0, s16 arg1, Vec3f* arg2, Vec3s* arg3, s32 arg4, s32 arg5) {
    Vec3f sp74;
    Vec3s sp6C;
    MtxF sp2C;

    Matrix_MultiplyVector3fByState(&gZeroVec3f, &sp74);
    Matrix_CopyCurrentState(&sp2C);
    func_8018219C(&sp2C, &sp6C, 0);
    *arg2 = sp74;

    if (arg4 == 0) {
        if (arg5 != 0) {
            sp6C.z = arg0;
            sp6C.y = arg1;
        }
        Math_SmoothStepToS(&arg3->x, sp6C.x, 3, 0x2AA8, 0xB6);
        Math_SmoothStepToS(&arg3->y, sp6C.y, 3, 0x2AA8, 0xB6);
        Math_SmoothStepToS(&arg3->z, sp6C.z, 3, 0x2AA8, 0xB6);
    } else {
        arg3->x = sp6C.x;
        arg3->y = sp6C.y;
        arg3->z = sp6C.z;
    }

    return 1;
}

s32 EnDns_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnDns* this = THIS;

    this->unk_1E4[limbIndex] = *dList;
    *dList = NULL;
    return false;
}

void EnDns_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnDns* this = THIS;
    s32 pad;
    s32 phi_v1;
    s32 phi_v0;

    if (this->unk_2C6 & 0x10) {
        phi_v1 = 1;
        phi_v0 = 0;
    } else {
        phi_v1 = 0;
        if (this->unk_2C6 & 0x20) {
            phi_v0 = 1;
        } else {
            phi_v0 = 0;
        }
    }

    if (limbIndex == KINGS_CHAMBER_DEKU_GUARD_LIMB_HEAD) {
        func_8092D954(this->unk_2CC, this->unk_2CE + this->actor.shape.rot.y, &this->unk_218, &this->unk_224, phi_v1,
                      phi_v0);
        Matrix_InsertTranslation(this->unk_218.x, this->unk_218.y, this->unk_218.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateY(this->unk_224.y, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->unk_224.z, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_224.x, MTXMODE_APPLY);
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, this->unk_1E4[limbIndex]);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnDns_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static TexturePtr sEyeTextures[] = {
        gKingsChamberDekuGuardEyeOpenTex,
        gKingsChamberDekuGuardEyeHalfTex,
        gKingsChamberDekuGuardEyeClosedTex,
        gKingsChamberDekuGuardEyeHalfTex,
    };
    EnDns* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeIndex]));
    gDPPipeSync(POLY_OPA_DISP++);

    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, EnDns_OverrideLimbDraw,
                      EnDns_PostLimbDraw, &this->actor);
    func_8092D108(this, globalCtx);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
