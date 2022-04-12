/*
 * File: z_en_bomjimb.c
 * Overlay: ovl_En_Bomjimb
 * Description: Bombers when chasing them
 */

#include "z_en_bomjimb.h"
#include "overlays/actors/ovl_En_Niw/z_en_niw.h"
#include "objects/object_cs/object_cs.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnBomjimb*)thisx)

void EnBomjimb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBomjimb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBomjimb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBomjimb_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C01494(EnBomjimb* this);
void func_80C014E4(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C01984(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C01A24(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C01B40(EnBomjimb* this);
void func_80C01B74(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C01C18(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C01CD0(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C0201C(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C02108(EnBomjimb* this);
void func_80C0217C(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C0250C(EnBomjimb* this);
void func_80C02570(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C0267C(EnBomjimb* this);
void func_80C02704(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C02740(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C02A14(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C02BCC(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C02CA4(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C02DAC(EnBomjimb* this, GlobalContext* globalCtx);

static Actor* D_80C03170 = NULL;

const ActorInit En_Bomjimb_InitVars = {
    ACTOR_EN_BOMJIMB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_CS,
    sizeof(EnBomjimb),
    (ActorFunc)EnBomjimb_Init,
    (ActorFunc)EnBomjimb_Destroy,
    (ActorFunc)EnBomjimb_Update,
    (ActorFunc)EnBomjimb_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
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
    { 20, 30, 0, { 0, 0, 0 } },
};

void EnBomjimb_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBomjimb* this = THIS;

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 19.0f);
    this->actor.gravity = -2.0f;
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_cs_Skel_00F82C, &gBomberIdleAnim, this->jointTable,
                       this->morphTable, OBJECT_CS_LIMB_MAX);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->actor.targetMode = 6;
    Actor_SetScale(&this->actor, 0.01f);

    this->unk_2C6 = ENBOMJIMB_GET_F0(&this->actor);
    this->unk_2B2 = ENBOMJIMB_GET_FF00(&this->actor);

    if (this->unk_2C6 != ENBOMJIMB_F0_0) {
        this->unk_2C8 = ENBOMJIMB_GET_F(&this->actor) + 1;
    }

    if (this->unk_2C8 < ENBOMJIMB_F_0) {
        this->unk_2C8 = ENBOMJIMB_F_0;
    }

    if (this->unk_2C6 < ENBOMJIMB_F0_0) {
        this->unk_2C6 = ENBOMJIMB_F0_0;
    }

    if ((gSaveContext.save.weekEventReg[73] & 0x10) || (gSaveContext.save.weekEventReg[85] & 2)) {
        switch (this->unk_2C8) {
            case ENBOMJIMB_F_0:
                if (gSaveContext.save.weekEventReg[11] & 1) {
                    Actor_MarkForDeath(&this->actor);
                    return;
                }
                break;

            case ENBOMJIMB_F_1:
                if (gSaveContext.save.weekEventReg[11] & 2) {
                    Actor_MarkForDeath(&this->actor);
                    return;
                }
                break;

            case ENBOMJIMB_F_2:
                if (gSaveContext.save.weekEventReg[11] & 4) {
                    Actor_MarkForDeath(&this->actor);
                    return;
                }
                break;

            case ENBOMJIMB_F_3:
                if (gSaveContext.save.weekEventReg[11] & 8) {
                    Actor_MarkForDeath(&this->actor);
                    return;
                }
                break;

            case ENBOMJIMB_F_4:
                if (gSaveContext.save.weekEventReg[11] & 0x10) {
                    Actor_MarkForDeath(&this->actor);
                    return;
                }
                break;
        }
    }

    if ((!(gSaveContext.save.weekEventReg[73] & 0x10) && !(gSaveContext.save.weekEventReg[85] & 2)) ||
        (gSaveContext.save.weekEventReg[75] & 0x40)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    Math_Vec3f_Copy(&this->unk_2A0, &this->actor.home.pos);
    if ((this->unk_2C6 == ENBOMJIMB_F0_0) || (this->unk_2C6 == ENBOMJIMB_F0_1) || (this->unk_2C6 != ENBOMJIMB_F0_2)) {
        func_80C01494(this);
    } else {
        func_80C01984(this, globalCtx);
    }
}

void EnBomjimb_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBomjimb* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80C0113C(EnBomjimb* this, s32 arg1, f32 arg2) {
    static AnimationHeader* sAnimations[] = {
        &gBomberIdleAnim,       &object_cs_Anim_00FAF4, &object_cs_Anim_0057C8, &object_cs_Anim_0053F4,
        &object_cs_Anim_002044, &object_cs_Anim_01007C, &object_cs_Anim_00349C, &object_cs_Anim_004960,
        &object_cs_Anim_005128, &object_cs_Anim_004C1C, &object_cs_Anim_002930, &object_cs_Anim_001A1C,
        &object_cs_Anim_003EE4, &object_cs_Anim_00478C, &object_cs_Anim_00433C, &object_cs_Anim_0060E8,
        &object_cs_Anim_001708, &object_cs_Anim_005DC4, &object_cs_Anim_0026B0, &object_cs_Anim_0036B0,
        &object_cs_Anim_0031C4, &object_cs_Anim_010B68,
    };
    static u8 D_80C03218[] = {
        0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 2, 0, 0,
    };

    this->unk_2DC = arg1;
    this->unk_2B8 = Animation_GetLastFrame(sAnimations[arg1]);
    Animation_Change(&this->skelAnime, sAnimations[this->unk_2DC], arg2, 0.0f, this->unk_2B8, D_80C03218[this->unk_2DC],
                     -4.0f);
}

void func_80C011CC(EnBomjimb* this) {
    if ((this->unk_2DC == 5) &&
        (Animation_OnFrame(&this->skelAnime, 9.0f) || Animation_OnFrame(&this->skelAnime, 10.0f) ||
         Animation_OnFrame(&this->skelAnime, 17.0f) || Animation_OnFrame(&this->skelAnime, 18.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOMBERS_WALK);
    }

    if ((this->unk_2DC == 19) &&
        (Animation_OnFrame(&this->skelAnime, 2.0f) || Animation_OnFrame(&this->skelAnime, 6.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOMBERS_WALK);
    }

    if ((this->unk_2DC == 18) && Animation_OnFrame(&this->skelAnime, 15.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOMBERS_LAND);
    }

    if ((this->unk_2DC == 7) && Animation_OnFrame(&this->skelAnime, 8.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOMBERS_LAND);
    }
}

void func_80C012E0(EnBomjimb* this) {
    this->unk_2C0 = 0;
    this->unk_2AE = 0;
    this->unk_2B0 = 0;
    this->unk_2CC = 0;
    this->unk_290 = 0;
}

s32 func_80C012FC(EnBomjimb* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (!Play_InCsMode(globalCtx) && (this->actor.xzDistToPlayer < 40.0f) &&
        (fabsf(player->actor.world.pos.y - this->actor.world.pos.y) < 50.0f) && (globalCtx->msgCtx.unk11F10 == 0)) {
        this->actor.speedXZ = 0.0f;
        func_80C02740(this, globalCtx);
        return true;
    }
    return false;
}

s32 func_80C013B4(EnBomjimb* this) {
    if (this->collider.base.acFlags & AC_HIT) {
        func_80C0267C(this);
        return true;
    }
    return false;
}

s32 func_80C013F0(EnBomjimb* this, GlobalContext* globalCtx) {
    Actor* sp1C;

    if (this->collider.base.ocFlags1 & OC1_HIT) {
        sp1C = this->collider.base.oc;

        if ((sp1C->id == ACTOR_OBJ_KIBAKO) && (D_80C03170 == NULL) && (sp1C->update != NULL) &&
            !Actor_HasParent(sp1C, globalCtx)) {
            D_80C03170 = sp1C;
            this->unk_2E4 = sp1C;
            func_80C01C18(this, globalCtx);
            return true;
        }
    }
    return false;
}

void func_80C01494(EnBomjimb* this) {
    func_80C012E0(this);
    Math_Vec3f_Copy(&this->unk_2A0, &this->actor.world.pos);
    this->unk_2CA = 3;
    this->actionFunc = func_80C014E4;
}

void func_80C014E4(EnBomjimb* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 curFrame = this->skelAnime.curFrame;
    CollisionPoly* colPoly;
    s16 abs;
    f32 x;
    f32 z;
    f32 phi_f0;
    Vec3f sp60;
    Vec3f sp54;
    Vec3f sp48;
    s32 sp44;

    if (func_80C012FC(this, globalCtx) || func_80C013B4(this) || func_80C013F0(this, globalCtx)) {
        return;
    }

    switch (this->unk_2CC) {
        case 0:
            if (this->unk_2AE == 0) {
                Math_Vec3f_Copy(&sp48, &this->actor.home.pos);
                sp48.x += randPlusMinusPoint5Scaled(150.0f);
                sp48.z += randPlusMinusPoint5Scaled(150.0f);

                abs = ABS_ALT(BINANG_SUB(this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &sp48)));
                if ((abs < 0x4000) && !BgCheck_EntityLineTest1(&globalCtx->colCtx, &this->actor.world.pos, &sp48, &sp60,
                                                               &colPoly, true, false, false, true, &sp44)) {
                    func_80C0113C(this, 5, 1.0f);
                    Math_Vec3f_Copy(&this->unk_294, &sp48);
                    this->unk_2B0 = Rand_S16Offset(30, 50);
                    this->unk_2CC++;
                }
            }
            break;

        case 1:
            if (curFrame >= 0.0f) {
                this->unk_2D6 = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_294);
                Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_2D6, 10, 2000, 20);
            }

            if ((s16)ABS_ALT(BINANG_SUB(this->actor.world.rot.y, this->unk_2D6)) < 0x100) {
                Math_Vec3f_Copy(&sp54, &this->actor.world.pos);
                sp54.x += Math_SinS(this->actor.world.rot.y) * 60.0f;
                sp54.z += Math_CosS(this->actor.world.rot.y) * 60.0f;
                if (BgCheck_EntityLineTest1(&globalCtx->colCtx, &this->actor.world.pos, &sp54, &sp60, &colPoly, true,
                                            false, false, true, &sp44)) {
                    this->unk_2AE = 0;
                    if (Rand_ZeroOne() < 0.5f) {
                        func_80C0113C(this, 20, 1.0f);
                    } else {
                        func_80C0113C(this, 0, 1.0f);
                    }
                    this->unk_2CC = 0;
                    this->unk_2B4 = 0.0f;
                    break;
                }
            }

            x = this->unk_294.x - this->actor.world.pos.x;
            z = this->unk_294.z - this->actor.world.pos.z;

            if ((this->unk_2B0 == 0) || (sqrtf(SQ(x) + SQ(z)) < 4.0f)) {
                this->unk_2AE = Rand_S16Offset(20, 20);
                if (!(this->unk_2AE & 1)) {
                    func_80C0113C(this, 20, 1.0f);
                } else {
                    func_80C0113C(this, 0, 1.0f);
                }
                this->unk_2CC = 0;
                this->unk_2B4 = 0.0f;
            } else if (curFrame >= 0.0f) {
                Math_ApproachF(&this->actor.world.pos.x, this->unk_294.x, 0.3f, this->unk_2B4);
                Math_ApproachF(&this->actor.world.pos.z, this->unk_294.z, 0.3f, this->unk_2B4);
                Math_ApproachF(&this->unk_2B4, 1.0f, 0.3f, 0.5f);
            }
            break;
    }

    if (player->stateFlags3 != 0x1000000) {
        phi_f0 = 200.0f;

        abs = ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.world.rot.y));
        if (abs > 0x2890) {
            phi_f0 = 150.0f;
        }

        if (this->actor.xzDistToPlayer < phi_f0) {
            func_80C02108(this);
        }
    }
}

void func_80C01984(EnBomjimb* this, GlobalContext* globalCtx) {
    func_80C012E0(this);
    this->unk_2E4 =
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_NIW, this->actor.world.pos.x,
                    this->actor.world.pos.y + 30.0f, this->actor.world.pos.z, 0, this->actor.world.rot.y, 0, 2);
    if (this->unk_2E4 != NULL) {
        func_80C0113C(this, 11, 1.0f);
    }
    this->unk_2CA = 0;
    this->actionFunc = func_80C01A24;
}

void func_80C01A24(EnBomjimb* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    this->actor.gravity = -0.1f;
    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        if ((this->unk_2E4 != NULL) && (this->unk_2E4->update != NULL)) {
            ((EnNiw*)this->unk_2E4)->unk2BC.z = 90000.0f;
        }
        this->actor.speedXZ = 0.0f;
        this->unk_2E4 = NULL;
        this->actor.gravity = -2.0f;
        func_80C02108(this);
        return;
    }

    if ((this->actor.xzDistToPlayer < 200.0f) && (fabsf(player->actor.world.pos.y - this->actor.world.pos.y) < 40.0f)) {
        this->unk_2C0 = 1;
    }

    if (this->unk_2C0 != 0) {
        Math_ApproachF(&this->actor.speedXZ, 6.0f, 0.5f, 2.0f);
    }

    if ((this->unk_2C0 != 0) && !(this->actor.bgCheckFlags & 1)) {
        func_80C01B40(this);
    }
}

void func_80C01B40(EnBomjimb* this) {
    func_80C012E0(this);
    this->unk_2CA = 0;
    this->actionFunc = func_80C01B74;
}

void func_80C01B74(EnBomjimb* this, GlobalContext* globalCtx) {
    Math_ApproachF(&this->actor.speedXZ, 6.0f, 0.5f, 2.0f);
    if ((this->collider.base.acFlags & AC_HIT) || (this->actor.bgCheckFlags & 1)) {
        this->collider.base.acFlags &= ~AC_HIT;
        if ((this->unk_2E4 != NULL) && (this->unk_2E4->update != NULL)) {
            ((EnNiw*)this->unk_2E4)->unk2BC.z = 90000.0f;
        }
        this->actor.speedXZ = 0.0f;
        this->unk_2E4 = NULL;
        this->actor.gravity = -2.0f;
        func_80C02108(this);
    }
}

void func_80C01C18(EnBomjimb* this, GlobalContext* globalCtx) {
    func_80C012E0(this);
    if (this->unk_2E4 != NULL) {
        if (this->unk_2E4->update != NULL) {
            this->unk_2E4->velocity.y = 8.0f;
            this->unk_2E4->shape.rot.z = BINANG_SUB(4000, ((s16)(globalCtx->gameplayFrames & 2) * 4000));
            this->unk_294.x = this->unk_2E4->world.pos.x;
            this->unk_294.y = this->actor.world.pos.y;
            this->unk_294.z = this->unk_2E4->world.pos.z;
        }
    }
    this->actor.speedXZ = 0.0f;
    this->unk_2CA = 2;
    this->actionFunc = func_80C01CD0;
}

void func_80C01CD0(EnBomjimb* this, GlobalContext* globalCtx) {
    f32 sp3C = this->skelAnime.curFrame;
    s32 pad[2];

    if ((this->unk_2E4 != NULL) && ((this->unk_2E4->update == NULL) || Actor_HasParent(this->unk_2E4, globalCtx))) {
        this->actor.draw = EnBomjimb_Draw;
        D_80C03170 = NULL;
        this->unk_2E4 = NULL;
        func_80C02108(this);
        return;
    }

    if (this->unk_2DC != 7) {
        Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_294), 1, 3000,
                           0);
        Math_ApproachF(&this->actor.world.pos.x, this->unk_294.x, 0.3f, 2.0f);
        Math_ApproachF(&this->actor.world.pos.z, this->unk_294.z, 0.3f, 2.0f);
        if (sqrtf(SQ(this->actor.world.pos.x - this->unk_294.x) + SQ(this->actor.world.pos.z - this->unk_294.z)) <
            3.0f) {
            func_80C0113C(this, 7, 1.0f);
            Math_Vec3f_Copy(&this->actor.world.pos, &this->unk_294);
        }
    } else if (this->unk_2B8 <= sp3C) {
        this->actor.draw = NULL;
    }

    if ((this->unk_2C0 == 0) && (this->unk_2E4->bgCheckFlags & 1)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_PUT_DOWN_WOODBOX);
        this->unk_2C0 = 1;
    }

    if (this->unk_2AE == 0) {
        if (this->actor.draw == NULL) {
            this->unk_2AE = Rand_S16Offset(20, 30);
            this->unk_2E4->shape.rot.z = 1000;
            return;
        }

        this->unk_2AE = 10;
        if ((this->unk_2E4 != NULL) && (this->unk_2E4->update != NULL)) {
            if ((globalCtx->gameplayFrames % 16) == 0) {
                this->unk_2E4->shape.rot.z = -this->unk_2E4->shape.rot.z;
                this->unk_2E4->shape.rot.z *= 0.1f;
            }

            if (fabsf(this->unk_2E4->shape.rot.z) < 100.0f) {
                this->unk_2E4->shape.rot.z = 0;
            }
        }
        return;
    }

    if (this->actor.draw == 0) {
        this->unk_2E4->shape.rot.z = -this->unk_2E4->shape.rot.z;
        this->unk_2E4->shape.rot.z *= 0.1f;
        if (fabsf(this->unk_2E4->shape.rot.z) < 100.0f) {
            this->unk_2E4->shape.rot.z = 0;
        }
    }
}

void func_80C01FD4(EnBomjimb* this) {
    this->actor.textId = 0x72D;
    func_80C0113C(this, 9, 1.0f);
    this->unk_2CA = 4;
    this->actionFunc = func_80C0201C;
}

void func_80C0201C(EnBomjimb* this, GlobalContext* globalCtx) {
    s16 abs = ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.world.rot.y));

    this->unk_290 = 0;
    if ((this->actor.xzDistToPlayer < 200.0f) && (abs < 0x61A8)) {
        this->unk_290 = this->actor.yawTowardsPlayer - this->actor.world.rot.y;
        if (this->unk_290 > 10000) {
            this->unk_290 = 10000;
        } else if (this->unk_290 < -10000) {
            this->unk_290 = -10000;
        }
    }

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->unk_2CA = 10;
        this->actionFunc = func_80C02A14;
    } else {
        func_800B8614(&this->actor, globalCtx, 40.0f);
    }
}

void func_80C02108(EnBomjimb* this) {
    func_80C0113C(this, 6, 1.0f);
    this->unk_2D6 = BINANG_ROT180(this->actor.yawTowardsPlayer);
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    func_80C012E0(this);
    Math_Vec3f_Copy(&this->unk_2A0, &this->actor.world.pos);
    this->unk_2D4 = 0;
    this->unk_2CA = 5;
    this->actionFunc = func_80C0217C;
}

void func_80C0217C(EnBomjimb* this, GlobalContext* globalCtx) {
    Vec3f sp74;
    CollisionPoly* sp70;
    Vec3f sp64;
    s32 sp60;
    s32 sp5C = this->actor.floorBgId;
    CollisionPoly* sp58 = this->actor.floorPoly;
    Player* player = GET_PLAYER(globalCtx);
    s32 sp50 = false;

    if (func_80C012FC(this, globalCtx) || func_80C013B4(this) || func_80C013F0(this, globalCtx)) {
        return;
    }

    if (player->stateFlags3 == 0x1000000) {
        Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 1, 3000, 0);
        func_80C01494(this);
        return;
    }

    if (this->unk_2DC == 6) {
        f32 curFrame = this->skelAnime.curFrame;

        if (this->unk_2B8 <= curFrame) {
            func_80C0113C(this, 19, 2.0f);
        }
        return;
    }

    Math_ApproachF(&this->actor.speedXZ, 8.0f, 0.5f, 2.0f);
    Math_Vec3f_Copy(&sp74, &this->actor.world.pos);

    sp74.x += Math_SinS(this->actor.world.rot.y) * 50.0f;
    sp74.y += 20.0f;
    sp74.z += Math_CosS(this->actor.world.rot.y) * 50.0f;

    if (BgCheck_EntityLineTest1(&globalCtx->colCtx, &this->actor.world.pos, &sp74, &sp64, &sp70, true, false, false,
                                true, &sp60)) {
        s16 temp = BINANG_SUB((this->actor.world.rot.y - this->actor.yawTowardsPlayer), 0x8000);
        this->unk_2D6 = temp;

        if (temp < 0) {
            this->unk_2D6 += BINANG_ADD((s32)Rand_ZeroFloat(0x200), 0x4000);
            if (this->unk_2D0 != 0) {
                this->unk_2D6 += BINANG_ADD((s32)Rand_ZeroFloat(0x200), 0x4000);
            }
            this->unk_2D0 = 1;
        } else {
            this->unk_2D6 -= BINANG_ADD((s32)Rand_ZeroFloat(0x200), 0x4000);
            if (this->unk_2D0 != 0) {
                this->unk_2D6 -= BINANG_ADD((s32)Rand_ZeroFloat(0x200), 0x4000);
            }
            this->unk_2D0 = 1;
        }
        sp50 = true;
    }

    if (!sp50) {
        this->unk_2D0 = 0;
        if (this->actor.xzDistToPlayer < 60.0f) {
            this->unk_2D6 = BINANG_ROT180(this->actor.yawTowardsPlayer);
        }
    }

    this->actor.world.rot.y = this->unk_2D6 + this->unk_2D4;

    if (SurfaceType_GetSceneExitIndex(&globalCtx->colCtx, sp58, sp5C)) {
        s16 temp = BINANG_SUB(this->actor.world.rot.y, this->actor.yawTowardsPlayer - 0x8000);

        if (temp < 0) {
            this->unk_2D4 -= 0x1000;
        } else {
            this->unk_2D4 += 0x1000;
        }
        this->actor.world.rot.y = this->unk_2D6 + this->unk_2D4;
        return;
    }

    this->unk_2D4 = 0;
    if (!sp50 && (this->actor.xzDistToPlayer > 200.0f)) {
        func_80C0250C(this);
    }
}

void func_80C0250C(EnBomjimb* this) {
    func_80C0113C(this, 15, 1.0f);
    this->unk_2D4 = 0;
    this->actor.speedXZ = 0.0f;
    this->unk_2D6 = BINANG_ROT180(this->actor.yawTowardsPlayer);
    func_80C012E0(this);
    this->unk_2CA = 6;
    this->actionFunc = func_80C02570;
}

void func_80C02570(EnBomjimb* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (func_80C012FC(this, globalCtx) || func_80C013B4(this) || func_80C013F0(this, globalCtx)) {
        return;
    }

    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 1, 5000, 0);

    if (this->actor.xzDistToPlayer < 200.0f) {
        this->unk_2D6 = BINANG_ROT180(this->actor.yawTowardsPlayer);
        func_80C0113C(this, 19, 2.0f);
        this->actionFunc = func_80C0217C;
    } else if ((player->stateFlags3 == 0x1000000) || (this->actor.xzDistToPlayer > 410.0f)) {
        Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 1, 3000, 0);
        func_80C01494(this);
    }
}

void func_80C0267C(EnBomjimb* this) {
    func_80C012E0(this);
    func_80C0113C(this, 8, 1.0f);
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->unk_2AE = 40;
    this->unk_2C2 = 0;
    this->unk_2C4 = (s32)Rand_ZeroFloat(60.0f) + 20;
    this->unk_2CA = 7;
    this->actionFunc = func_80C02704;
}

void func_80C02704(EnBomjimb* this, GlobalContext* globalCtx) {
    if (!func_80C012FC(this, globalCtx) && (this->unk_2AE == 0)) {
        func_80C0250C(this);
    }
}

void func_80C02740(EnBomjimb* this, GlobalContext* globalCtx) {
    static u16 D_80C03230[] = {
        0x0721, 0x0722, 0x0723, 0x0724, 0x072C,
    };
    Player* player = GET_PLAYER(globalCtx);
    s16 idx;

    func_80C012E0(this);
    func_80C0113C(this, 21, 1.0f);
    if ((player->transformation != PLAYER_FORM_DEKU) && (player->transformation != PLAYER_FORM_HUMAN)) {
        func_80C0113C(this, 17, 1.0f);
        Message_StartTextbox(globalCtx, 0x72E, &this->actor);
        player->stateFlags1 |= 0x10000000;
        player->actor.freezeTimer = 3;
        func_80C012E0(this);
        this->unk_2CA = 9;
        this->actionFunc = func_80C02BCC;
        return;
    }

    if (((player->transformation == PLAYER_FORM_DEKU) && !(gSaveContext.save.weekEventReg[73] & 0x10)) ||
        ((player->transformation == PLAYER_FORM_HUMAN) && !(gSaveContext.save.weekEventReg[85] & 2))) {
        func_80C0113C(this, 17, 1.0f);
        Message_StartTextbox(globalCtx, 0x72E, &this->actor);
        player->stateFlags1 |= 0x10000000;
        player->actor.freezeTimer = 3;
        func_80C012E0(this);
        this->unk_2CA = 9;
        this->actionFunc = func_80C02BCC;
        return;
    }

    idx = gSaveContext.save.bombersCaughtNum;
    Message_StartTextbox(globalCtx, D_80C03230[idx], &this->actor);
    idx = gSaveContext.save.bombersCaughtNum;
    gSaveContext.save.bombersCaughtOrder[idx] = this->unk_2C8 + 1;
    gSaveContext.save.bombersCaughtNum++;

    if (gSaveContext.save.bombersCaughtNum > 4) {
        func_801A3098(0x922);
    } else {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_SY_PIECE_OF_HEART);
    }

    switch (this->unk_2C8) {
        case ENBOMJIMB_F_0:
            gSaveContext.save.weekEventReg[76] |= 1;
            gSaveContext.save.weekEventReg[11] |= 1;
            break;

        case ENBOMJIMB_F_1:
            gSaveContext.save.weekEventReg[76] |= 2;
            gSaveContext.save.weekEventReg[11] |= 2;
            break;

        case ENBOMJIMB_F_2:
            gSaveContext.save.weekEventReg[76] |= 4;
            gSaveContext.save.weekEventReg[11] |= 4;
            break;

        case ENBOMJIMB_F_3:
            gSaveContext.save.weekEventReg[76] |= 8;
            gSaveContext.save.weekEventReg[11] |= 8;
            break;

        case ENBOMJIMB_F_4:
            gSaveContext.save.weekEventReg[76] |= 0x10;
            gSaveContext.save.weekEventReg[11] |= 0x10;
            break;
    }

    if (!Play_InCsMode(globalCtx)) {
        Player* player = GET_PLAYER(globalCtx);

        player->stateFlags1 |= 0x10000000;
        player->actor.freezeTimer = 3;
    }
    this->unk_2CA = 8;
    this->actionFunc = func_80C02A14;
}

void func_80C02A14(EnBomjimb* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 curFrame = this->skelAnime.curFrame;

    if (this->unk_2DC == 21) {
        player->actor.freezeTimer = 3;
        if (this->unk_2B8 <= curFrame) {
            func_80C0113C(this, 9, 1.0f);
        }
        return;
    }

    if ((this->unk_2CA == 8) && (this->unk_2DC == 9)) {
        player->actor.freezeTimer = 3;
        if (this->unk_2E0 == 0) {
            if (Animation_OnFrame(&this->skelAnime, 7.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_HUMAN_BOUND);
                this->unk_2E0 = 1;
            }
        }
    }

    if ((this->unk_2DC == 15) && (this->unk_2CA == 8)) {
        player->actor.freezeTimer = 3;
    }

    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        func_801477B4(globalCtx);
        if ((this->unk_2CA == 8) && (gSaveContext.save.bombersCaughtNum >= 5)) {
            func_80C02CA4(this, globalCtx);
        } else {
            if (this->unk_2CA == 8) {
                player->stateFlags1 &= ~0x10000000;
            }
            func_80C01FD4(this);
        }
    }
}

void func_80C02BCC(EnBomjimb* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 1, 5000, 0);
    if (this->unk_2C0 == 0) {
        player->actor.freezeTimer = 3;
        if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
            func_801477B4(globalCtx);
            this->unk_2C0 = 1;
            player->stateFlags1 &= ~0x10000000;
        }
    } else if (this->actor.xzDistToPlayer > 200.0f) {
        func_80C01494(this);
    }
}

void func_80C02CA4(EnBomjimb* this, GlobalContext* globalCtx) {
    if (BREG(13) == 0) {
        globalCtx->nextEntranceIndex = globalCtx->setupExitList[this->unk_2B2];
        gSaveContext.nextCutsceneIndex = 0;
        Scene_SetExitFade(globalCtx);
        globalCtx->sceneLoadFlag = 0x14;
    } else {
        globalCtx->nextEntranceIndex = Entrance_CreateIndexFromSpawn(5);
        gSaveContext.nextCutsceneIndex = 0;
        globalCtx->sceneLoadFlag = 0x14;
        globalCtx->unk_1887F = 0x56;
        gSaveContext.nextTransition = 3;
    }
    gSaveContext.save.weekEventReg[75] |= 0x40;
    gSaveContext.save.weekEventReg[83] |= 4;
    this->actionFunc = func_80C02DAC;
}

void func_80C02DAC(EnBomjimb* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    player->actor.freezeTimer = 3;
}

void EnBomjimb_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnBomjimb* this = THIS;

    if (this->unk_2B0 != 0) {
        this->unk_2B0--;
    }

    if (this->unk_2AE != 0) {
        this->unk_2AE--;
    }

    if (this->unk_2AC != 0) {
        this->unk_2AC--;
    }

    SkelAnime_Update(&this->skelAnime);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    func_80C011CC(this);
    Actor_SetFocus(&this->actor, 20.0f);

    this->actionFunc(this, globalCtx);

    Actor_MoveWithGravity(&this->actor);

    if (this->unk_2CA == 0) {
        if ((this->unk_2E4 != NULL) && (this->unk_2E4->update != NULL)) {
            Math_Vec3f_Copy(&this->unk_2E4->world.pos, &this->actor.world.pos);
            if (this->actor.bgCheckFlags & 1) {
                this->unk_2E4->world.pos.y = this->actor.world.pos.y + 35.0f;
            } else {
                this->unk_2E4->world.pos.y = this->actor.world.pos.y + 25.0f;
            }
        }
    }

    Math_SmoothStepToS(&this->unk_28A, this->unk_290, 1, 5000, 0);

    if (this->unk_2C4 == 0) {
        this->unk_2C2++;
        if (this->unk_2C2 > 2) {
            this->unk_2C2 = 0;
            this->unk_2C4 = (s16)Rand_ZeroFloat(60.0f) + 20;
        }
    }

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 50.0f, 0x1D);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);

    if (this->unk_2CA != 2) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

s32 EnBomjimb_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                               Actor* thisx) {
    EnBomjimb* this = THIS;

    if (limbIndex == 15) {
        *dList = NULL;
    }

    if (limbIndex == 17) {
        rot->x += this->unk_28A;
        rot->z += this->unk_288;
    }

    if ((limbIndex == 19) && (this->unk_2C8 != ENBOMJIMB_F_0)) {
        *dList = NULL;
    }

    if ((limbIndex == 20) && (this->unk_2C8 == ENBOMJIMB_F_0)) {
        *dList = NULL;
    }

    return false;
}

#include "overlays/ovl_En_Bomjimb/ovl_En_Bomjimb.c"

void EnBomjimb_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static Gfx* D_80C03260[] = {
        gEnBomjimb_D_80C03240, gEnBomjimb_D_80C03250, gEnBomjimb_D_80C03250,
        gEnBomjimb_D_80C03250, gEnBomjimb_D_80C03250,
    };
    static TexturePtr D_80C03274[] = {
        object_cs_Tex_00C520,
        object_cs_Tex_00CD20,
        object_cs_Tex_00D520,
    };
    static TexturePtr D_80C03280[] = {
        object_cs_Tex_00E620, object_cs_Tex_00EA20, object_cs_Tex_00EE20, object_cs_Tex_00DD20, object_cs_Tex_00F220,
    };
    EnBomjimb* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80C03274[this->unk_2C2]));
    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80C03280[this->unk_2C8]));
    gSPSegment(POLY_OPA_DISP++, 0x0A, Lib_SegmentedToVirtual(D_80C03260[this->unk_2C8]));

    Scene_SetRenderModeXlu(globalCtx, 0, 1);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnBomjimb_OverrideLimbDraw, NULL, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
