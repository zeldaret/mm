/*
 * File: z_en_ja.c
 * Overlay: ovl_En_Ja
 * Description: Juggler
 */

#include "z_en_ja.h"
#include "objects/object_boj/object_boj.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnJa*)thisx)

void EnJa_Init(Actor* thisx, GlobalContext* globalCtx);
void EnJa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnJa_Update(Actor* thisx, GlobalContext* globalCtx);
void EnJa_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BC21A8(EnJa* this, GlobalContext* globalCtx);
void func_80BC22F4(EnJa* this, GlobalContext* globalCtx);
void func_80BC2EA4(EnJa* this);
void func_80BC32D8(EnJa* this, GlobalContext* globalCtx);
void func_80BC3594(EnJa* this, GlobalContext* globalCtx);

s32 D_80BC35F0[] = {
    0x0C000301, 0x05020600, 0x1200080A, 0x00610304, 0x0002050A, 0x006C0304, 0x00010500,
};

s32 D_80BC360C[] = {
    0x0E29370C, 0x170E2938, 0x0C180E29, 0x390C170E, 0x293A0C09, 0x0000180E, 0x293B0C09, 0x00001000,
};

s32 D_80BC362C[] = {
    0x0E29400C, 0x170E2941, 0x0C180E29, 0x420C170E, 0x29430C09, 0x0000180E, 0x293B0C09, 0x00001000,
};

s32 D_80BC364C[] = {
    0x0E293C0C, 0x170E293D, 0x0C180E29, 0x3E0C170E, 0x293F0C09, 0x0000180E, 0x293B0C09, 0x00001000,
};

s32 D_80BC366C[] = {
    0x0E29440C, 0x170E2945, 0x0C180E29, 0x460C170E, 0x29470C09, 0x0000180E, 0x293B0C09, 0x00001000,
};

const ActorInit En_Ja_InitVars = {
    ACTOR_EN_JA,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BOJ,
    sizeof(EnJa),
    (ActorFunc)EnJa_Init,
    (ActorFunc)EnJa_Destroy,
    (ActorFunc)EnJa_Update,
    (ActorFunc)EnJa_Draw,
};

Vec3f D_80BC36AC = { -10.0f, 56.0f, 25.0f };
Vec3f D_80BC36B8 = { 0.0f, 60.0f, 20.0f };
Vec3f D_80BC36C4 = { 10.0f, 60.0f, 25.0f };
Vec3f D_80BC36D0 = { 0.0f, 58.0f, 20.0f };

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT1,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 12, 64, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

static AnimationInfoS sAnimations[] = {
    { &object_boj_Anim_002734, 1.0f, 0, -1, 0, 0 },  { &object_boj_Anim_0033B0, 1.0f, 0, -1, 0, 0 },
    { &object_boj_Anim_002734, 1.0f, 0, -1, 0, -4 }, { &object_boj_Anim_0033B0, 1.0f, 0, -1, 0, -4 },
    { &object_boj_Anim_004078, 1.0f, 0, -1, 0, 0 },  { &object_boj_Anim_005CE4, 1.0f, 0, -1, 0, 0 },
};

void func_80BC1900(EnJa* this) {
    this->skelAnime.playSpeed = this->unk_344;
    SkelAnime_Update(&this->skelAnime);
}

s32 func_80BC192C(EnJa* this, s32 arg1) {
    s32 ret = false;

    if (arg1 != this->unk_36C) {
        this->unk_36C = arg1;
        ret = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, arg1);
        this->unk_344 = this->skelAnime.playSpeed;
    }

    return ret;
}

void func_80BC1984(EnJa* this, GlobalContext* globalCtx) {
    s32 pad[2];

    Collider_UpdateCylinder(&this->actor, &this->collider);
    this->collider.dim.height = (s16)fabsf(this->actor.focus.pos.y - this->actor.world.pos.y) + 5;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

s32 func_80BC19FC(EnJa* this, GlobalContext* globalCtx) {
    s32 ret = false;

    if ((this->unk_340 & 7) && Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        SubS_UpdateFlags(&this->unk_340, 0, 7);
        this->actionFunc = func_80BC22F4;
        ret = true;
    }
    return ret;
}

void func_80BC1A68(EnJa* this) {
    if (DECR(this->unk_360) == 0) {
        this->unk_362++;
        if (this->unk_362 >= 4) {
            this->unk_360 = Rand_S16Offset(30, 30);
            this->unk_362 = 0;
        }
    }
}

s32 func_80BC1AE0(EnJa* this, GlobalContext* globalCtx) {
    Actor* ja = SubS_FindNearestActor(&this->actor, globalCtx, ACTORCAT_NPC, ACTOR_EN_JA);
    Vec3f sp30;
    Vec3f sp24;

    if (ja != NULL) {
        this->actor.child = ja;
        Math_Vec3f_Copy(&sp24, &ja->world.pos);
        Math_Vec3f_Copy(&sp30, &this->actor.world.pos);
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp30, &sp24);
    } else {
        this->actor.child = NULL;
    }
    return this->actor.child;
}

Player* func_80BC1B50(EnJa* this, GlobalContext* globalCtx) {
    return GET_PLAYER(globalCtx);
}

s32 func_80BC1B60(EnJa* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f sp40;
    Vec3f sp34;
    s16 sp32;

    Math_Vec3f_Copy(&sp40, &this->unk_1D8.player->actor.world.pos);
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    sp32 = Math_Vec3f_Yaw(&sp34, &sp40);
    Math_ApproachS(&this->unk_356, (sp32 - this->unk_35A) - this->actor.shape.rot.y, 4, 0x2AA8);
    this->unk_356 = CLAMP(this->unk_356, -0x1FFE, 0x1FFE);

    Math_ApproachS(&this->unk_35A, (sp32 - this->unk_356) - this->actor.shape.rot.y, 4, 0x2AA8);
    this->unk_35A = CLAMP(this->unk_35A, -0x1C70, 0x1C70);

    if (this->unk_1D8.player->actor.id == ACTOR_PLAYER) {
        sp40.y = this->unk_1D8.player->bodyPartsPos[7].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&sp40, &this->unk_1D8.player->actor.focus.pos);
    }

    Math_Vec3f_Copy(&sp34, &this->actor.focus.pos);
    Math_ApproachS(&this->unk_354, Math_Vec3f_Pitch(&sp34, &sp40) - this->unk_358, 4, 0x2AA8);
    this->unk_354 = CLAMP(this->unk_354, -0x1C70, 0x1C70);

    Math_ApproachS(&this->unk_358, Math_Vec3f_Pitch(&sp34, &sp40) - this->unk_354, 4, 0x2AA8);
    this->unk_358 = CLAMP(this->unk_358, -0x1C70, 0x1C70);

    return true;
}

s32 func_80BC1D70(EnJa* this, GlobalContext* globalCtx) {
    if (this->unk_340 & 8) {
        this->unk_1D8.player = func_80BC1B50(this, globalCtx);
        if (this->unk_1D8.player != NULL) {
            func_80BC1B60(this, globalCtx);
        }
        this->unk_340 &= ~0x10;
        this->unk_340 |= 0x20;
    } else if (this->unk_340 & 0x20) {
        this->unk_340 &= ~0x20;
        this->unk_354 = 0;
        this->unk_356 = 0;
        this->unk_358 = 0;
        this->unk_35A = 0;
        this->unk_35E = 20;
    } else if (DECR(this->unk_35E) == 0) {
        this->unk_340 |= 0x10;
        this->unk_35E = 20;
    }
    return true;
}

void func_80BC1E40(EnJa* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 sp20 = Message_GetState(&globalCtx->msgCtx);
    f32 phi_f0;

    if (((globalCtx->msgCtx.currentTextId < 0xFF) || (globalCtx->msgCtx.currentTextId > 0x200)) && (sp20 == 3) &&
        (this->unk_374 == 3) && (&this->actor == player->targetActor)) {
        if ((globalCtx->state.frames % 2) == 0) {
            if (this->unk_348 != 0.0f) {
                this->unk_348 = 0.0f;
            } else {
                this->unk_348 = 1.0f;
            }
        }
    } else {
        this->unk_348 = 0.0f;
    }

    this->unk_34C += (this->unk_348 != 0.0f) ? 60.0f : -60.0f;
    this->unk_34C = CLAMP(this->unk_34C, 0.0f, 120.0f);

    Matrix_InsertTranslation(this->unk_34C, 0.0f, 0.0f, MTXMODE_APPLY);
    this->unk_374 = sp20;
}

s32 func_80BC1FC8(EnJa* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    s32 ret = false;

    if (func_80BC1AE0(this, globalCtx)) {
        SubS_UpdateFlags(&this->unk_340, 3, 7);
        this->unk_340 |= 0x10;
        func_80BC192C(this, 5);
        func_80BC2EA4(this);
        ret = true;
    }
    return ret;
}

s32 func_80BC203C(EnJa* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    s32 ret = false;

    if (func_80BC1AE0(this, globalCtx)) {
        if (ENJA_GET_3(&this->actor) == 0) {
            func_80BC192C(this, 1);
        } else {
            func_80BC192C(this, 4);
        }
        SubS_UpdateFlags(&this->unk_340, 3, 7);
        this->actor.shape.shadowDraw = NULL;
        this->unk_340 |= 0x50;
        ret = true;
    }
    return ret;
}

s32 func_80BC20D0(EnJa* this, GlobalContext* globalCtx, struct_80133038_arg2* arg2) {
    s32 ret = false;

    this->unk_340 = 0;

    switch (arg2->unk0) {
        case 1:
            ret = func_80BC1FC8(this, globalCtx, arg2);
            if (ret == 1) {}
            break;

        case 2:
            ret = func_80BC203C(this, globalCtx, arg2);
            break;
    }
    return ret;
}

s32 func_80BC213C(EnJa* this, GlobalContext* globalCtx) {
    return true;
}

void func_80BC2150(EnJa* this, GlobalContext* globalCtx) {
    if ((this->unk_1D8.unk_00 == 1) || (this->unk_1D8.unk_00 == 2)) {
        func_80BC213C(this, globalCtx);
    }
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 4, 0x1554);
}

void func_80BC21A8(EnJa* this, GlobalContext* globalCtx) {
    u32* unk_14 = &gSaveContext.save.daySpeed;
    struct_80133038_arg2 sp18;

    this->unk_35C = REG(15) + *unk_14;
    if (!func_80133038(globalCtx, D_80BC35F0, &sp18) ||
        ((this->unk_1D8.unk_00 != sp18.unk0) && !func_80BC20D0(this, globalCtx, &sp18))) {
        this->actor.shape.shadowDraw = NULL;
        this->actor.flags &= ~ACTOR_FLAG_1;
        sp18.unk0 = 0;
    } else {
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= ACTOR_FLAG_1;
    }
    this->unk_1D8.unk_00 = sp18.unk0;
    func_80BC2150(this, globalCtx);
}

s32* func_80BC2274(EnJa* this, GlobalContext* globalCtx) {
    switch (this->unk_1D8.unk_00) {
        case 1:
            if (ENJA_GET_3(&this->actor) == 0) {
                return D_80BC360C;
            }
            return D_80BC364C;

        case 2:
            if (ENJA_GET_3(&this->actor) == 0) {
                return D_80BC362C;
            }
            return D_80BC366C;
    }
    return D_80BC360C;
}

void func_80BC22F4(EnJa* this, GlobalContext* globalCtx) {
    if (func_8010BF58(&this->actor, globalCtx, func_80BC2274(this, globalCtx), this->unk_368, &this->unk_1D8.unk_04)) {
        this->unk_340 &= ~8;
        SubS_UpdateFlags(&this->unk_340, 3, 7);
        this->unk_1D8.unk_04 = 0;
        this->unk_340 |= 0x10;
        this->actor.shape.rot.y = this->actor.world.rot.y;
        this->actionFunc = func_80BC21A8;
    }
}

void EnJa_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnJa* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 18.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_boj_Skel_00C240, NULL, this->jointTable, this->morphTable,
                       16);
    this->unk_36C = -1;
    func_80BC192C(this, 0);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.targetMode = 0;
    this->actor.uncullZoneForward = 800.0f;
    this->actor.gravity = 0.0f;
    SubS_UpdateFlags(&this->unk_340, 0, 7);
    this->unk_340 |= 0x10;
    this->unk_1D8.unk_00 = 0;
    this->unk_368 = NULL;
    this->actionFunc = func_80BC21A8;
}

void EnJa_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnJa* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnJa_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnJa* this = THIS;
    f32 height;
    f32 radius;

    func_80BC19FC(this, globalCtx);

    this->actionFunc(this, globalCtx);

    if (this->unk_1D8.unk_00 != 0) {
        func_80BC1900(this);
        func_80BC1A68(this);
        func_80BC1D70(this, globalCtx);

        radius = this->collider.dim.radius + 30;
        height = this->collider.dim.height + 10;
        func_8013C964(&this->actor, globalCtx, radius, height, 0, this->unk_340 & 7);

        if (this->unk_1D8.unk_00 != 2) {
            Actor_MoveWithGravity(&this->actor);
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 12.0f, 0.0f, 4);
        }
        func_80BC1984(this, globalCtx);
    }

    if (this->unk_1D8.unk_00 == 1) {
        func_80BC32D8(this, globalCtx);
    }
}

s32 EnJa_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnJa* this = THIS;

    if (limbIndex == 15) {
        func_80BC1E40(this, globalCtx);
    }
    return false;
}

void EnJa_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80BC3774 = { -87.0f, 444.0f, -49.0f };
    static Vec3f D_80BC3780 = { 600.0f, 0.0f, 0.0f };
    static Vec3f D_80BC378C = { 400.0f, 0.0f, -400.0f };
    static Vec3f D_80BC3798 = { 400.0, 0.0f, 400.0f };
    static Vec3s D_80BC37A4 = { 0x7770, -0x4BC, -0x251C };
    s32 pad;
    EnJa* this = THIS;
    s32 pad2;

    if (limbIndex == 15) {
        Matrix_MultiplyVector3fByState(&D_80BC3780, &this->actor.focus.pos);
        Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
    } else if ((this->unk_340 & 0x40) && (limbIndex == 11)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        Matrix_StatePush();
        Matrix_JointPosition(&D_80BC3774, &D_80BC37A4);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, object_boj_DL_00BA30);

        Matrix_StatePop();

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }

    if (this->unk_1D8.unk_00 == 1) {
        if ((limbIndex == 11) && (((this->skelAnime.curFrame >= 0.0f) && (this->skelAnime.curFrame <= 6.0f)) ||
                                  ((this->skelAnime.curFrame >= 35.0f) && (this->skelAnime.curFrame <= 47.0f)))) {
            OPEN_DISPS(globalCtx->state.gfxCtx);

            Matrix_StatePush();
            Matrix_InsertTranslation(D_80BC378C.x, D_80BC378C.y, D_80BC378C.z, MTXMODE_APPLY);
            Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);

            gDPPipeSync(POLY_OPA_DISP++);

            switch (this->unk_364) {
                case 0:
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 255, 255);
                    break;

                case 1:
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 0, 0, 255);
                    break;

                case 2:
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 255, 255);
                    break;

                case 3:
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 0, 255);
                    break;

                default:
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
                    break;
            }

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, object_boj_DL_00BCC8);

            Matrix_StatePop();

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        } else if (limbIndex == 14) {
            if ((this->skelAnime.curFrame >= 0.0f) && (this->skelAnime.curFrame <= 18.0f)) {
                OPEN_DISPS(globalCtx->state.gfxCtx);

                Matrix_StatePush();

                Matrix_InsertTranslation(D_80BC3798.x, D_80BC3798.y, D_80BC3798.z, MTXMODE_APPLY);
                Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);

                gDPPipeSync(POLY_OPA_DISP++);

                switch (this->unk_366) {
                    case 0:
                        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 255, 255);
                        break;

                    case 1:
                        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 0, 0, 255);
                        break;

                    case 2:
                        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 255, 255);
                        break;

                    case 3:
                        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 0, 255);
                        break;

                    default:
                        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
                        break;
                }

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, object_boj_DL_00BCC8);

                Matrix_StatePop();

                CLOSE_DISPS(globalCtx->state.gfxCtx);
            }
        }
    }
}

void EnJa_TransformLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
    EnJa* this = THIS;
    s32 phi_v1;
    s32 phi_v0;

    if (this->unk_340 & 0x10) {
        phi_v1 = false;
    } else {
        phi_v1 = true;
    }

    if (this->unk_340 & 0x20) {
        phi_v0 = true;
    } else {
        phi_v0 = false;
    }

    if (!phi_v1) {
        phi_v0 = false;
    }

    if (limbIndex != 8) {
        if (limbIndex == 15) {
            func_8013AD9C(this->unk_354 + this->unk_358 + 0x4000,
                          this->unk_356 + this->unk_35A + this->actor.shape.rot.y + 0x4000, &this->unk_1EC,
                          &this->unk_274, phi_v1, phi_v0);
            Matrix_StatePop();
            Matrix_InsertTranslation(this->unk_1EC.x, this->unk_1EC.y, this->unk_1EC.z, MTXMODE_NEW);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            Matrix_RotateY(this->unk_274.y, MTXMODE_APPLY);
            Matrix_InsertXRotation_s(this->unk_274.x, MTXMODE_APPLY);
            Matrix_InsertZRotation_s(this->unk_274.z, MTXMODE_APPLY);
            Matrix_StatePush();
        }
    } else {
        func_8013AD9C(this->unk_358 + 0x4000, this->unk_35A + this->actor.shape.rot.y + 0x4000, &this->unk_1F8,
                      &this->unk_27A, phi_v1, phi_v0);
        Matrix_StatePop();
        Matrix_InsertTranslation(this->unk_1F8.x, this->unk_1F8.y, this->unk_1F8.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateY(this->unk_27A.y, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->unk_27A.x, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_27A.z, MTXMODE_APPLY);
        Matrix_StatePush();
    }
}

void EnJa_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static Color_RGBA8 D_80BC37AC[] = {
        { 200, 0, 80, 0 },
        { 0, 130, 220, 0 },
    };
    static Color_RGBA8 D_80BC37B4[] = {
        { 255, 255, 255, 0 },
        { 255, 255, 255, 0 },
    };
    static TexturePtr D_80BC37BC[] = {
        object_boj_Tex_0062B0,
        object_boj_Tex_0063B0,
        object_boj_Tex_0064B0,
        object_boj_Tex_0063B0,
    };
    s32 pad;
    EnJa* this = THIS;
    s32 phi_t2;

    if (ENJA_GET_3(&this->actor) == 0) {
        phi_t2 = 0;
    } else {
        phi_t2 = 1;
    }

    if (this->unk_1D8.unk_00 != 0) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C28C(globalCtx->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x08,
                   Gfx_EnvColor(globalCtx->state.gfxCtx, D_80BC37AC[phi_t2].r, D_80BC37AC[phi_t2].g,
                                D_80BC37AC[phi_t2].b, D_80BC37AC[phi_t2].a));
        gSPSegment(POLY_OPA_DISP++, 0x09,
                   Gfx_EnvColor(globalCtx->state.gfxCtx, D_80BC37B4[phi_t2].r, D_80BC37B4[phi_t2].g,
                                D_80BC37B4[phi_t2].b, D_80BC37B4[phi_t2].a));
        gSPSegment(POLY_OPA_DISP++, 0x0A, Lib_SegmentedToVirtual(D_80BC37BC[this->unk_362]));
        gDPPipeSync(POLY_OPA_DISP++);

        SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, EnJa_OverrideLimbDraw, EnJa_PostLimbDraw,
                                       EnJa_TransformLimbDraw, &this->actor);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }

    if (this->unk_1D8.unk_00 == 1) {
        func_80BC3594(this, globalCtx);
    }
}

void func_80BC2EA4(EnJa* this) {
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    s32 i;
    Vec3f sp28;

    sp44 = Math_SinS(this->actor.shape.rot.y);
    sp40 = Math_CosS(this->actor.shape.rot.y);
    sp3C = Math_SinS(this->actor.child->shape.rot.y);
    sp38 = Math_CosS(this->actor.child->shape.rot.y);

    for (i = 0; i < ARRAY_COUNT(this->unk_234); i++) {
        this->unk_234[i].unk_0E = i * 0x30;
        this->unk_234[i].unk_0C = i;
    }

    sp28 = this->actor.world.pos;
    this->unk_210 = sp28;
    this->unk_204 = sp28;

    sp28 = this->actor.child->world.pos;
    this->unk_228 = sp28;
    this->unk_21C = sp28;

    this->unk_204.x += (D_80BC36AC.z * sp44) + (D_80BC36AC.x * sp40);
    this->unk_204.y += D_80BC36AC.y;
    this->unk_204.z += (D_80BC36AC.z * sp40) - (D_80BC36AC.x * sp44);

    this->unk_210.x += (D_80BC36B8.z * sp44) + (D_80BC36B8.x * sp40);
    this->unk_210.y += D_80BC36B8.y;
    this->unk_210.z += (D_80BC36B8.z * sp40) - (D_80BC36B8.x * sp44);

    this->unk_21C.x += (D_80BC36C4.z * sp3C) + (D_80BC36C4.x * sp38);
    this->unk_21C.y += D_80BC36C4.y;
    this->unk_21C.z += (D_80BC36C4.z * sp38) - (D_80BC36C4.x * sp3C);

    this->unk_228.x += (D_80BC36D0.z * sp3C) + (D_80BC36D0.x * sp38);
    this->unk_228.y += D_80BC36D0.y;
    this->unk_228.z += (D_80BC36D0.z * sp38) - (D_80BC36D0.x * sp3C);

    this->unk_364 = 2;
    this->unk_366 = 0;
}

void func_80BC3154(EnJa* this, EnJaStruct* ptr) {
    if ((ptr->unk_0E >= 18) && (ptr->unk_0E < 83)) {
        f32 temp_f0 = ptr->unk_0E - 18;

        ptr->unk_00.x = (((65.0f - temp_f0) * this->unk_204.x) + (temp_f0 * this->unk_228.x)) / 65.0f;
        ptr->unk_00.y = (((65.0f - temp_f0) * this->unk_204.y) + (temp_f0 * this->unk_228.y)) / 65.0f;
        ptr->unk_00.z = (((65.0f - temp_f0) * this->unk_204.z) + (temp_f0 * this->unk_228.z)) / 65.0f;

        temp_f0 -= 32.5f;
        temp_f0 = SQ(temp_f0);

        ptr->unk_00.y += -0.11360947f * temp_f0 + 120.0f;
    } else if ((ptr->unk_0E >= 102) && (ptr->unk_0E < 191)) {
        f32 temp_f0 = ptr->unk_0E - 102;

        ptr->unk_00.x = (((89.0f - temp_f0) * this->unk_21C.x) + (temp_f0 * this->unk_210.x)) / 89.0f;
        ptr->unk_00.y = (((89.0f - temp_f0) * this->unk_21C.y) + (temp_f0 * this->unk_210.y)) / 89.0f;
        ptr->unk_00.z = (((89.0f - temp_f0) * this->unk_21C.z) + (temp_f0 * this->unk_210.z)) / 89.0f;

        temp_f0 -= 44.5f;
        temp_f0 = SQ(temp_f0);

        ptr->unk_00.y += -0.08079788f * temp_f0 + 160.0f;
    }
}

void func_80BC32D8(EnJa* this, GlobalContext* globalCtx) {
    EnJaStruct* phi_s0 = &this->unk_234[0];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_234); i++, phi_s0++) {
        func_80BC3154(this, phi_s0);
        if (phi_s0->unk_0E != 191) {
            phi_s0->unk_0E++;
        } else {
            phi_s0->unk_0E = 0;
        }
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        if (this->unk_366 > 0) {
            this->unk_366--;
        } else {
            this->unk_366 = 3;
        }
    } else if (Animation_OnFrame(&this->skelAnime, 34.0f)) {
        if (this->unk_364 > 0) {
            this->unk_364--;
        } else {
            this->unk_364 = 3;
        }
    }
}

void func_80BC33C0(EnJaStruct* ptr, GlobalContext* globalCtx) {
    s32 pad;

    if (((ptr->unk_0E < 0) || (ptr->unk_0E >= 19)) && ((ptr->unk_0E < 83) || (ptr->unk_0E >= 103))) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        Matrix_InsertTranslation(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, MTXMODE_NEW);
        Matrix_InsertMatrix(&globalCtx->billboardMtxF, MTXMODE_APPLY);
        Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);

        switch (ptr->unk_0C) {
            case 0:
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 255, 255);
                break;

            case 1:
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 0, 0, 255);
                break;

            case 2:
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 255, 255);
                break;

            case 3:
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 0, 255);
                break;

            default:
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
                break;
        }

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, object_boj_DL_00BCC8);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void func_80BC3594(EnJa* this, GlobalContext* globalCtx) {
    EnJaStruct* phi_s0 = this->unk_234;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_234); i++, phi_s0++) {
        func_80BC33C0(phi_s0, globalCtx);
    }
}
