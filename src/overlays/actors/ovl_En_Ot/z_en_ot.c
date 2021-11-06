/*
 * File: z_en_ot.c
 * Overlay: ovl_En_Ot
 * Description: Seahorse
 */

#include "z_en_ot.h"
#include "prevent_bss_reordering.h"

#define FLAGS 0x00000019

#define THIS ((EnOt*)thisx)

void EnOt_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOt_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOt_Update(Actor* thisx, GlobalContext* globalCtx);
void EnOt_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B5BDA8(EnOt* this, GlobalContext* globalCtx);
void func_80B5BE04(EnOt* this, GlobalContext* globalCtx);
void func_80B5BE88(EnOt* this, GlobalContext* globalCtx);
void func_80B5BED4(EnOt* this, GlobalContext* globalCtx);
void func_80B5BF60(EnOt* this, GlobalContext* globalCtx);
void func_80B5BFB8(EnOt* this, GlobalContext* globalCtx);
void func_80B5C1CC(EnOt* this, GlobalContext* globalCtx);
void func_80B5C244(EnOt* this, GlobalContext* globalCtx);
void func_80B5C25C(EnOt* this, GlobalContext* globalCtx);
void func_80B5C3B8(EnOt* this, GlobalContext* globalCtx);
void func_80B5C3D8(EnOt* this, GlobalContext* globalCtx);
void func_80B5C634(EnOt* this, GlobalContext* globalCtx);
void func_80B5C64C(EnOt* this, GlobalContext* globalCtx);
void func_80B5C684(EnOt* this, GlobalContext* globalCtx);
void func_80B5C6DC(EnOt* this, GlobalContext* globalCtx);
void func_80B5C910(EnOt* this, GlobalContext* globalCtx);
void func_80B5C950(EnOt* this, GlobalContext* globalCtx);
void func_80B5C9A8(EnOt* this, GlobalContext* globalCtx);
void func_80B5C9C0(EnOt* this, GlobalContext* globalCtx);
void func_80B5C9D0(EnOt* this, GlobalContext* globalCtx);
void func_80B5CA30(EnOt* this, GlobalContext* globalCtx);
void func_80B5CAD0(EnOt* this, GlobalContext* globalCtx);
void func_80B5CB0C(EnOt* this, GlobalContext* globalCtx);
void func_80B5CBEC(EnOt* this, GlobalContext* globalCtx);
void func_80B5CC88(EnOt* this, GlobalContext* globalCtx);
void func_80B5CCA0(EnOt* this, GlobalContext* globalCtx);
void func_80B5CCF4(EnOt* this, GlobalContext* globalCtx);
void func_80B5CD40(EnOt* this, GlobalContext* globalCtx);
void func_80B5CE6C(EnOt* this, GlobalContext* globalCtx);
void func_80B5CEC8(EnOt* this, GlobalContext* globalCtx);
void func_80B5D114(EnOt* this, GlobalContext* globalCtx);
void func_80B5D160(EnOt* this, GlobalContext* globalCtx);
void func_80B5D648(EnOt* this, GlobalContext* globalCtx);
void func_80B5D750(EnOt* this, GlobalContext* globalCtx);
void func_80B5DAEC(Actor* thisx, GlobalContext* globalCtx);
void func_80B5DB6C(Actor* thisx, GlobalContext* globalCtx);
void EnOt_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);
EnOtUnkStruct* func_80B5DF58(EnOtUnkStruct* arg0, u8 arg1, Vec3f* arg2, Vec3s* arg3, s32 arg4);
void func_80B5E078(GlobalContext* globalCtx, EnOtUnkStruct* arg1, s32 arg2);
void func_80B5E1D8(GlobalContext* globalCtx, EnOtUnkStruct* arg1, s32 arg2);

extern Gfx D_06000040[];
extern Gfx D_06000078[];
extern AnimationHeader D_06000420;
extern Gfx D_060004A0[];
extern AnimatedMaterial D_060005F8;
extern AnimationHeader D_060008D8;
extern FlexSkeletonHeader D_06004800;
extern AnimationHeader D_06004B30;

static EnOt* D_80B5E880;
static EnOt* D_80B5E884;
static EnOt* D_80B5E888;

const ActorInit En_Ot_InitVars = {
    ACTOR_EN_OT,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OT,
    sizeof(EnOt),
    (ActorFunc)EnOt_Init,
    (ActorFunc)EnOt_Destroy,
    (ActorFunc)EnOt_Update,
    (ActorFunc)EnOt_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER | AC_TYPE_ENEMY,
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
    { 5, 33, -20, { 0, 0, 0 } },
};

static struct_80B8E1A8 sAnimations[] = {
    { &D_06004B30, 1.0f, 0, -5.0f },
    { &D_060008D8, 1.0f, 0, -5.0f },
    { &D_06000420, 1.0f, 0, 0.0f },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 80, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 80, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_STOP),
};

void func_80B5B2E0(GlobalContext* globalCtx, Vec3f* pos, s16 params, Vec3f* vec, s32* index) {
    s32 i;
    Path* path = &globalCtx->setupPathList[params];
    f32 dist;
    Vec3f sp58;
    Vec3f sp4C;
    f32 minDist = FLT_MAX;

    for (i = 0; i < path->count; i++) {
        Math_Vec3s_ToVec3f(&sp58, &((Vec3s*)Lib_SegmentedToVirtual(path->points))[i]);
        dist = Math_Vec3f_DistXYZ(pos, &sp58);
        if (dist < minDist) {
            minDist = dist;
            Math_Vec3f_Copy(&sp4C, &sp58);
            *index = i;
        }
    }

    Math_Vec3f_Copy(vec, &sp4C);
}

void EnOt_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnOt* this = THIS;
    s32 sp74;
    s32 pad2;
    Vec3f sp64;
    Vec3f sp58;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->unk_388 = 0;
    this->unk_33C = ENOT_GET_C000(&this->actor);
    if (this->unk_33C == 0) {
        D_80B5E880 = this;
        this->actor.flags |= 0x8000000;
        this->actor.flags &= ~(0x8 | 0x1);
        this->actor.update = func_80B5DB6C;
        this->actor.draw = NULL;
        return;
    }

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 30.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_06004800, &D_060008D8, this->jointTable, this->morphTable, 19);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    Animation_Change(&this->skelAnime, sAnimations[0].animationSeg, 1.0f,
                     Animation_GetLastFrame(&sAnimations[0].animationSeg->common) * Rand_ZeroOne(),
                     Animation_GetLastFrame(&sAnimations[0].animationSeg->common), sAnimations[0].mode,
                     sAnimations[0].transitionRate);
    this->unk_346 = ENOT_GET_7F(&this->actor);
    this->unk_344 = this->actor.world.rot.z;
    this->actor.world.rot.z = 0;
    this->actor.shape.rot.z = 0;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.gravity = 0.0f;
    func_8013E3B8(&this->actor, this->cutscenes, ARRAY_COUNT(this->cutscenes));
    func_8013E1C8(&this->skelAnime, sAnimations, 0, &this->animIdx);
    this->skelAnime.curFrame = Rand_ZeroOne() * this->skelAnime.endFrame;
    this->lightNode = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &this->lightInfo);
    this->unk_744.r = 255;
    this->unk_744.g = 200;
    this->unk_744.b = 80;

    switch (ENOT_GET_C000(&this->actor)) {
        case 1:
            D_80B5E884 = this;
            Actor_SetScale(&this->actor, 0.012999999f);

            switch (this->unk_344) {
                case 0:
                    this->actor.world.pos.y =
                        func_800C40B4(&globalCtx->colCtx, &this->actor.floorPoly, &sp74, &this->actor.world.pos) +
                        50.0f;
                    if (gSaveContext.weekEventReg[84] & 0x10) {
                        Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_NEW);
                        Matrix_GetStateTranslationAndScaledZ(52.519997f, &sp64);
                        Math_Vec3f_Sum(&this->actor.world.pos, &sp64, &sp64);
                        this->unk_360 = (EnOt*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_OT, sp64.x, sp64.y,
                                                           sp64.z, 0, BINANG_ROT180(this->actor.shape.rot.y), 1,
                                                           ENOT_GET_3FFF(&this->actor) | 0x8000);
                        if (this->unk_360 != NULL) {
                            this->unk_360->unk_360 = this;
                            this->unk_3A0 = 0;
                            this->unk_360->unk_3A0 = BINANG_ROT180(this->unk_3A0);
                            this->unk_394.x = (this->actor.world.pos.x + this->unk_360->actor.world.pos.x) * 0.5f;
                            this->unk_394.y = this->actor.world.pos.y;
                            this->unk_394.z = (this->actor.world.pos.z + this->unk_360->actor.world.pos.z) * 0.5f;
                            Math_Vec3f_Copy(&this->unk_360->unk_394, &this->unk_394);
                            if (gSaveContext.weekEventReg[32] & 1) {
                                func_80B5C244(this, globalCtx);
                            } else {
                                func_80B5C684(this, globalCtx);
                            }
                        } else {
                            Actor_MarkForDeath(&this->actor);
                        }
                    } else if ((D_80B5E888 != NULL) && (D_80B5E888->unk_32C & 1)) {
                        this->unk_360 = D_80B5E888;
                        this->unk_360->unk_360 = this;
                        Matrix_RotateY(this->actor.world.rot.y, MTXMODE_NEW);
                        Matrix_GetStateTranslationAndScaledZ(800.0f, &sp58);
                        Math_Vec3f_Sum(&this->actor.world.pos, &sp58, &sp58);
                        Math_Vec3f_Copy(&this->unk_360->actor.world.pos, &sp58);
                        Math_Vec3f_Copy(&this->unk_360->actor.prevPos, &sp58);
                        func_80B5BDA8(this, globalCtx);
                        func_80B5BE88(this->unk_360, globalCtx);
                    } else {
                        func_80B5CE6C(this, globalCtx);
                    }
                    break;

                case 1:
                    Actor_MarkForDeath(&this->actor);
                    break;
            }
            break;

        case 2:
            D_80B5E888 = this;

            switch (this->unk_344) {
                case 0:
                    Actor_SetScale(&this->actor, 0.0f);
                    if (!(gSaveContext.weekEventReg[13] & 1)) {
                        Actor_SetScale(&this->actor, 0.0f);
                        func_80B5C910(this, globalCtx);
                    } else {
                        Player* player = GET_PLAYER(globalCtx);

                        if (func_800C9B90(&globalCtx->colCtx, player->actor.floorPoly, player->actor.floorBgId)) {
                            Actor_SetScale(&this->actor, 0.0f);
                            func_80B5C910(this, globalCtx);
                        } else {
                            this->unk_360 = D_80B5E884;
                            this->unk_360->unk_360 = this;
                            func_80B5C9D0(this, globalCtx);
                        }
                    }
                    break;

                case 1:
                    Actor_SetScale(&this->actor, 0.012999999f);
                    if (gSaveContext.weekEventReg[84] & 0x10) {
                        if (gSaveContext.weekEventReg[32] & 1) {
                            func_80B5C244(this, globalCtx);
                        } else {
                            func_80B5C684(this, globalCtx);
                        }
                    } else {
                        func_80B5CE6C(this, globalCtx);
                    }
                    break;
            }
            break;

        case 3:
            if (!(gSaveContext.weekEventReg[26] & 8)) {
                this->actor.flags |= 0x8000000;
                this->actor.flags &= ~(0x8 | 0x1);
                Actor_SetScale(&this->actor, 0.0064999997f);
                this->collider.dim.radius *= 0.5f;
                this->collider.dim.height *= 0.5f;
                this->collider.dim.yShift *= 0.5f;
                this->actor.update = func_80B5DAEC;
                func_80B5C634(this, globalCtx);
            } else {
                Actor_MarkForDeath(&this->actor);
            }
            break;
    }
}

void EnOt_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnOt* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
    LightContext_RemoveLight(globalCtx, &globalCtx->lightCtx, this->lightNode);
}

void func_80B5BAAC(LightInfo* lightInfo, Vec3f* arg1, Color_RGB8* arg2, s16 radius) {
    Lights_PointNoGlowSetInfo(lightInfo, arg1->x, arg1->y, arg1->z, arg2->r, arg2->g, arg2->b, radius);
}

void func_80B5BB38(Color_RGB8* arg0, Color_RGB8* arg1, f32 arg2) {
    f32 rand = Rand_ZeroOne();

    arg0->r = (arg1->r * arg2) + (arg1->r * (1.0f - arg2) * rand);
    arg0->g = (arg1->g * arg2) + (arg1->g * (1.0f - arg2) * rand);
    arg0->b = (arg1->b * arg2) + (arg1->b * (1.0f - arg2) * rand);
}

void func_80B5BDA8(EnOt* this, GlobalContext* globalCtx) {
    func_8013E1C8(&this->skelAnime, sAnimations, 1, &this->animIdx);
    func_8013E3B8(&this->actor, this->cutscenes, ARRAY_COUNT(this->cutscenes));
    this->actionFunc = func_80B5BE04;
}

void func_80B5BE04(EnOt* this, GlobalContext* globalCtx) {
    switch (this->unk_388) {
        case 0:
            if (func_8013E2D4(&this->actor, this->cutscenes[2], -1, 0)) {
                func_80B5BF60(this, globalCtx);
            }
            break;

        case 1:
            if (func_8013E2D4(&this->actor, this->cutscenes[3], -1, 0)) {
                func_80B5BF60(this, globalCtx);
            }
            break;
    }
}

void func_80B5BE88(EnOt* this, GlobalContext* globalCtx) {
    func_8013E1C8(&this->skelAnime, sAnimations, 1, &this->animIdx);
    this->actionFunc = func_80B5BED4;
}

void func_80B5BED4(EnOt* this, GlobalContext* globalCtx) {
    func_800BE33C(&this->actor.world.pos, &this->unk_360->actor.world.pos, &this->actor.world.rot, 0);
    Math_SmoothStepToS(&this->actor.shape.rot.y, Actor_YawBetweenActors(&this->actor, &this->unk_360->actor), 3, 0xE38,
                       0x38E);
    this->actor.speedXZ = 3.5f;
    this->actor.world.pos.y = this->unk_360->actor.world.pos.y;
    Actor_SetVelocityAndMoveXYRotationReverse(&this->actor);
}

void func_80B5BF60(EnOt* this, GlobalContext* globalCtx) {
    this->unk_32C |= 0x40;
    func_8013E1C8(&this->skelAnime, sAnimations, 0, &this->animIdx);
    this->actionFunc = func_80B5BFB8;
}

void func_80B5BFB8(EnOt* this, GlobalContext* globalCtx) {
    Vec3f sp34;
    f32 temp_f0 = this->actor.floorHeight + 50.0f;

    if (temp_f0 <= this->actor.world.pos.y) {
        Math_StepToF(&this->actor.world.pos.y, temp_f0, 2.0f);
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, Actor_YawBetweenActors(&this->actor, &this->unk_360->actor), 3, 0xE38,
                       0x38E);

    if (Actor_DistanceBetweenActors(&this->actor, &this->unk_360->actor) <= 52.519997f) {
        this->unk_73C = 50;
        Matrix_RotateY(this->actor.world.rot.y, MTXMODE_NEW);
        Matrix_GetStateTranslationAndScaledZ(52.519997f, &sp34);
        this->unk_360->actor.world.pos.x = this->actor.world.pos.x + sp34.x;
        this->unk_360->actor.world.pos.y = this->actor.world.pos.y + sp34.y;
        this->unk_360->actor.world.pos.z = this->actor.world.pos.z + sp34.z;

        this->unk_394.x = (this->unk_360->actor.world.pos.x + this->actor.world.pos.x) * 0.5f;
        this->unk_394.y = (this->unk_360->actor.world.pos.y + this->actor.world.pos.y) * 0.5f;
        this->unk_394.z = (this->unk_360->actor.world.pos.z + this->actor.world.pos.z) * 0.5f;

        this->unk_360->unk_394.x = this->unk_394.x;
        this->unk_360->unk_394.y = this->unk_394.y;
        this->unk_360->unk_394.z = this->unk_394.z;

        func_80B5C684(this->unk_360, globalCtx);
        func_80B5C684(this, globalCtx);
    } else {
        Actor_SetVelocityAndMoveXYRotationReverse(&this->actor);
    }
}

void func_80B5C154(EnOt* this, GlobalContext* globalCtx) {
    if (gSaveContext.weekEventReg[32] & 1) {
        this->unk_38C = 4;
    } else {
        this->unk_38C = 12;
        gSaveContext.weekEventReg[32] |= 1;
    }
    func_800B8A1C(&this->actor, globalCtx, this->unk_38C, this->actor.xzDistToPlayer, this->actor.playerHeightRel);
    this->actionFunc = func_80B5C1CC;
}

void func_80B5C1CC(EnOt* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        func_80B5C244(this, globalCtx);
        func_80B5C244(this->unk_360, globalCtx);
    } else {
        func_800B8A1C(&this->actor, globalCtx, this->unk_38C, this->actor.xzDistToPlayer, this->actor.playerHeightRel);
    }
}

void func_80B5C244(EnOt* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80B5C25C;
}

void func_80B5C25C(EnOt* this, GlobalContext* globalCtx) {
    this->unk_390 = Actor_YawBetweenActors(&this->actor, &this->unk_360->actor);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->unk_390, 3, 0xE38, 0x38E);
    if (SUB16(BINANG_ROT180(this->unk_360->actor.shape.rot.y), this->actor.shape.rot.y) < 0x38E) {
        this->unk_32C |= 0x80;
    }

    if ((this->unk_33C == 2) && (this->unk_32C & 0x80) && (this->unk_360->unk_32C & 0x80)) {
        this->unk_32C |= 0x100;
        this->unk_360->unk_32C |= 0x100;
        func_8013E1C8(&this->skelAnime, sAnimations, 2, &this->animIdx);
        func_8013E1C8(&this->unk_360->skelAnime, sAnimations, 2, &this->unk_360->animIdx);
        this->actor.flags |= 0x8000000;
        this->actor.flags &= ~(0x8 | 0x1);
        this->unk_360->actor.flags |= 0x8000000;
        this->unk_360->actor.flags &= ~(0x8 | 0x1);
        func_80B5C9A8(this->unk_360, globalCtx);
        func_80B5C3B8(this, globalCtx);
    }
}

void func_80B5C3B8(EnOt* this, GlobalContext* globalCtx) {
    this->unk_740 = 0.0f;
    this->actionFunc = func_80B5C3D8;
}

void func_80B5C3D8(EnOt* this, GlobalContext* globalCtx) {
    static Color_RGB8 D_80B5E408 = { 255, 200, 80 };
    static Color_RGB8 D_80B5E40C = { 255, 60, 200 };
    s16 temp;
    s32 pad;
    Vec3f sp5C;
    Vec3f sp50;
    Vec3f sp44;
    Vec3f sp38;

    this->unk_3A0 += 0x2D8;
    Matrix_RotateY(this->unk_3A0, 0);
    Matrix_GetStateTranslationAndScaledZ(26.259998f, &sp5C);
    Matrix_GetStateTranslationAndScaledZ(-26.259998f, &sp50);
    this->unk_348.x = this->unk_394.x + sp5C.x;
    this->unk_348.y = this->unk_394.y;
    this->unk_348.z = this->unk_394.z + sp5C.z;

    this->unk_360->unk_348.x = this->unk_394.x + sp50.x;
    this->unk_360->unk_348.y = this->unk_394.y;
    this->unk_360->unk_348.z = this->unk_394.z + sp50.z;

    Math_Vec3f_Copy(&this->actor.world.pos, &this->unk_348);
    Math_Vec3f_Copy(&this->unk_360->actor.world.pos, &this->unk_360->unk_348);
    temp = Actor_YawBetweenActors(&this->actor, &this->unk_360->actor);
    this->actor.shape.rot.y = temp;
    this->unk_360->actor.shape.rot.y = BINANG_ROT180(temp);

    if (this->unk_740 < 1.0f) {
        Lib_LerpRGB(&D_80B5E408, &D_80B5E40C, this->unk_740, &this->unk_744);
        Lib_LerpRGB(&D_80B5E408, &D_80B5E40C, this->unk_740, &this->unk_360->unk_744);
        Math_StepToF(&this->unk_740, 1.0f, 0.05f);
    }

    if (Animation_OnFrame(&this->skelAnime, 12.0f)) {
        Matrix_RotateY(Camera_GetCamDirYaw(GET_ACTIVE_CAM(globalCtx)), 0);
        sp38.x = 1.0f;
        sp38.y = 8.1f;
        sp38.z = 0.0f;
        Matrix_MultiplyVector3fByState(&sp38, &sp44);
        Math_Vec3f_Sum(&this->unk_74C, &sp44, &sp44);
        func_80B5DF58(this->unk_3A4, 1, &sp44, &this->actor.shape.rot, 10);
        sp38.x = -1.0f;
        sp38.y = 8.1f;
        sp38.z = 0.0f;
        Matrix_MultiplyVector3fByState(&sp38, &sp44);
        Math_Vec3f_Sum(&this->unk_74C, &sp44, &sp44);
        func_80B5DF58(this->unk_3A4, 2, &sp44, &this->actor.shape.rot, 10);
    }
}

void func_80B5C634(EnOt* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80B5C64C;
}

void func_80B5C64C(EnOt* this, GlobalContext* globalCtx) {
    if (gSaveContext.weekEventReg[26] & 8) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80B5C684(EnOt* this, GlobalContext* globalCtx) {
    this->actor.speedXZ = 0.0f;
    func_8013E1C8(&this->skelAnime, sAnimations, 0, &this->animIdx);
    this->actionFunc = func_80B5C6DC;
}

void func_80B5C6DC(EnOt* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;
    s16 sp3E;
    Vec3f sp30;

    sp3E = Actor_YawToPoint(&player->actor, &this->unk_394);
    Matrix_RotateY(ADD16(sp3E, 0x4000), 0);
    if (this->unk_33C == 2) {
        Matrix_GetStateTranslationAndScaledZ(26.259998f, &sp30);
    } else {
        if (this->unk_73C == 0) {
            gSaveContext.weekEventReg[84] |= 0x10;
            switch (this->unk_388) {
                case 0:
                    ActorCutscene_Stop(this->cutscenes[2]);
                    break;

                case 1:
                    ActorCutscene_Stop(this->cutscenes[3]);
                    break;
            }
            this->unk_73C = -1;
        } else {
            this->unk_73C--;
        }
        Matrix_GetStateTranslationAndScaledZ(-26.259998f, &sp30);
    }
    this->unk_348.x = this->unk_394.x + sp30.x;
    this->unk_348.y = this->unk_394.y;
    this->unk_348.z = this->unk_394.z + sp30.z;
    Math_SmoothStepToF(&this->actor.world.pos.x, this->unk_348.x, 1.0f, 2.0f, 0.01f);
    Math_SmoothStepToF(&this->actor.world.pos.z, this->unk_348.z, 1.0f, 2.0f, 0.01f);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0xE38, 0x38E);
    if ((gSaveContext.weekEventReg[84] & 0x10) && (this->unk_33C == 1)) {
        this->actor.textId = 0;
        this->unk_384 = 1;
        if (func_800B84D0(&this->actor, globalCtx)) {
            this->unk_3A0 = ADD16(sp3E, 0x4000);
            this->unk_360->unk_3A0 = this->unk_3A0;
            func_80B5C9A8(this, globalCtx);
            func_80B5D114(this, globalCtx);
        } else if ((player->actor.bgCheckFlags & 1) && !func_801242B4(player) &&
                   (this->actor.xzDistToPlayer < 130.0f)) {
            func_800B8614(&this->actor, globalCtx, 130.0f);
        }
    }
}

void func_80B5C910(EnOt* this, GlobalContext* globalCtx) {
    this->actor.shape.rot.x = 0;
    this->actor.shape.rot.z = 0;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    // This is weird
    this->actor.world.rot.x = this->actor.world.rot.x;
    this->actor.world.rot.y = this->actor.world.rot.y;
    this->actor.world.rot.z = this->actor.world.rot.z;
    this->actionFunc = func_80B5C950;
}

void func_80B5C950(EnOt* this, GlobalContext* globalCtx) {
    if (this->unk_32C & 8) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_SEAHORSE_OUT_BOTTLE);
        gSaveContext.weekEventReg[25] |= 4;
        func_80B5CAD0(this, globalCtx);
    }
}

void func_80B5C9A8(EnOt* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80B5C9C0;
}

void func_80B5C9C0(EnOt* this, GlobalContext* globalCtx) {
}

void func_80B5C9D0(EnOt* this, GlobalContext* globalCtx) {
    this->actor.shape.rot.x = 0;
    this->actor.shape.rot.z = 0;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    // This is weird
    this->actor.world.rot.x = this->actor.world.rot.x;
    this->actor.world.rot.y = this->actor.world.rot.y;
    this->actor.world.rot.z = this->actor.world.rot.z;
    Audio_PlayActorSound2(&this->actor, NA_SE_EV_SEAHORSE_OUT_BOTTLE);
    this->actionFunc = func_80B5CA30;
}

void func_80B5CA30(EnOt* this, GlobalContext* globalCtx) {
    Math_SmoothStepToF(&this->actor.scale.x, 0.012999999f, 0.7f, 0.0001f, 0.01f);
    Actor_SetScale(&this->actor, this->actor.scale.x);
    if (this->actor.scale.x == 0.012999999f) {
        this->unk_360->unk_32C |= 0x1000;
        this->unk_360->unk_360 = this;
        func_80B5C9A8(this, globalCtx);
    }
}

void func_80B5CAD0(EnOt* this, GlobalContext* globalCtx) {
    func_8013E3B8(&this->actor, this->cutscenes, ARRAY_COUNT(this->cutscenes) / 2);
    this->actionFunc = func_80B5CB0C;
}

void func_80B5CB0C(EnOt* this, GlobalContext* globalCtx) {
    Math_SmoothStepToF(&this->actor.scale.x, 0.012999999f, 0.7f, 0.0001f, 0.01f);
    Actor_SetScale(&this->actor, this->actor.scale.x);
    if (this->actor.scale.x == 0.012999999f) {
        this->unk_32C |= 0x800;
        func_80B5CE6C(this, globalCtx);
    }
}

void func_80B5CBA0(EnOt* this, GlobalContext* globalCtx) {
    this->actor.flags |= 0x10000;
    func_800B8500(&this->actor, globalCtx, this->actor.xzDistToPlayer, this->actor.playerHeightRel, 0);
    this->actionFunc = func_80B5CBEC;
}

void func_80B5CBEC(EnOt* this, GlobalContext* globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx)) {
        this->actor.flags &= ~0x10000;
        func_80B5CC88(this, globalCtx);
    } else {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0xE38, 0x38E);
        this->actor.world.rot.y = this->actor.shape.rot.y;
        func_800B8500(&this->actor, globalCtx, this->actor.xzDistToPlayer, this->actor.playerHeightRel, 0);
    }
}

void func_80B5CC88(EnOt* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80B5CCA0;
}

void func_80B5CCA0(EnOt* this, GlobalContext* globalCtx) {
    if (func_8013E2D4(&this->actor, this->cutscenes[0], 0x7C, 1)) {
        Player* player = GET_PLAYER(globalCtx);

        player->stateFlags2 |= 0x20000000;
        func_80B5CCF4(this, globalCtx);
    }
}

void func_80B5CCF4(EnOt* this, GlobalContext* globalCtx) {
    func_8013E1C8(&this->skelAnime, sAnimations, 0, &this->animIdx);
    this->actionFunc = func_80B5CD40;
}

void func_80B5CD40(EnOt* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 temp;

    switch (func_80152498(&globalCtx->msgCtx)) {
        case 0:
            temp = Math_SmoothStepToS(&this->actor.shape.rot.y, BINANG_ROT180(Camera_GetCamDirYaw(GET_ACTIVE_CAM(globalCtx))),
                                      3, 0xE38, 0x38E);
            this->actor.world.rot.y = this->actor.shape.rot.y;
            if (1) {}
            if (!temp) {
                gSaveContext.weekEventReg[23] |= 0x10;
                func_801518B0(globalCtx, 0x1069, NULL);
            }
            break;

        case 1:
        case 2:
        case 3:
            break;

        case 4:
        case 5:
        case 6:
            if (func_80147624(globalCtx) && (globalCtx->msgCtx.unk11F04 == 0x1069)) {
                this->unk_32C |= 4;
                ActorCutscene_Stop(this->cutscenes[0]);
                player->stateFlags2 &= ~0x20000000;
                func_80B5CE6C(this, globalCtx);
            }
            break;
    }
}

void func_80B5CE6C(EnOt* this, GlobalContext* globalCtx) {
    this->unk_384 = 0;
    this->unk_32C |= 0x20;
    func_8013E1C8(&this->skelAnime, sAnimations, 0, &this->animIdx);
    this->actionFunc = func_80B5CEC8;
}

void func_80B5CEC8(EnOt* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;

    this->actor.textId = 0;
    if (func_800B84D0(&this->actor, globalCtx)) {
        func_80B5D114(this, globalCtx);
        return;
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0xE38, 0x38E);
    if (this->unk_32C & 0x800) {
        this->actor.flags |= 0x10000;
        func_800B8500(&this->actor, globalCtx, this->actor.xzDistToPlayer, this->actor.playerHeightRel, 0);
    } else {
        this->actor.flags &= ~0x10000;
        if ((player->actor.bgCheckFlags & 1) && !func_801242B4(player) && (this->actor.xzDistToPlayer < 130.0f)) {
            func_800B8614(&this->actor, globalCtx, 130.0f);
        }
    }

    if (!(gSaveContext.weekEventReg[84] & 0x10) && (ENOT_GET_C000(&this->actor) == 1)) {
        if ((fabsf(this->actor.xzDistToPlayer) <= 130.0f) && (fabsf(this->actor.playerHeightRel) <= 130.0f)) {
            player->unk_B2B = 29;
        }

        if ((D_80B5E888 != NULL) && (D_80B5E888->unk_32C & 1)) {
            Vec3f sp2C;

            this->unk_360 = D_80B5E888;
            this->unk_360->unk_360 = this;
            Matrix_RotateY(this->actor.home.rot.y, MTXMODE_NEW);
            Matrix_GetStateTranslationAndScaledZ(800.0f, &sp2C);
            Math_Vec3f_Sum(&this->actor.world.pos, &sp2C, &this->unk_360->actor.world.pos);
            Math_Vec3f_Copy(&this->unk_360->actor.prevPos, &this->unk_360->actor.world.pos);
            this->unk_32C &= ~0x800;
            this->unk_360->unk_32C &= ~0x800;
            func_80B5BDA8(this, globalCtx);
            func_80B5BE88(this->unk_360, globalCtx);
            return;
        }
    }

    if (this->unk_32C & 0x1000) {
        this->unk_388 = 1;
        func_80B5BDA8(this, globalCtx);
        func_80B5BE88(this->unk_360, globalCtx);
    }
}

void func_80B5D114(EnOt* this, GlobalContext* globalCtx) {
    func_8013E1C8(&this->skelAnime, sAnimations, 0, &this->animIdx);
    this->actionFunc = func_80B5D160;
}

void func_80B5D160(EnOt* this, GlobalContext* globalCtx) {
    u16 phi_a1;
    s32 temp;

    switch (func_80152498(&globalCtx->msgCtx)) {
        case 0:
            temp = Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0xE38, 0x38E);
            this->actor.world.rot.y = this->actor.shape.rot.y;
            if (!temp) {
                switch (this->unk_384) {
                    case 0:
                        if ((this->unk_33C != 1) && (this->unk_33C == 2)) {
                            if (this->unk_32C & 1) {
                                if (this->unk_32C & 4) {
                                    phi_a1 = 0x106A;
                                } else {
                                    phi_a1 = 0x1069;
                                }
                            } else if (Flags_GetSwitch(globalCtx, ENOT_GET_3F80(&this->actor))) {
                                if (gSaveContext.weekEventReg[23] & 0x10) {
                                    phi_a1 = 0x106C;
                                } else {
                                    phi_a1 = 0x106B;
                                }
                            } else {
                                phi_a1 = 0x1068;
                            }
                        } else {
                            phi_a1 = 0x10A5;
                        }
                        func_801518B0(globalCtx, phi_a1, &this->actor);
                        func_80B5D114(this, globalCtx);
                        break;

                    case 1:
                        func_801518B0(globalCtx, 0x106D, &this->actor);
                        func_80B5D114(this, globalCtx);
                        break;
                }
                break;
            }
            break;

        case 1:
        case 2:
        case 3:
            break;

        case 4:
        case 5:
        case 6:
            if (func_80147624(globalCtx)) {
                switch (globalCtx->msgCtx.unk11F04) {
                    default:
                    case 0x1068:
                    case 0x106B:
                    case 0x106C:
                        func_80B5D648(this, globalCtx);
                        break;

                    case 0x1069:
                        this->unk_32C |= 4;

                    case 0x106A:
                        func_80B5CE6C(this, globalCtx);
                        break;

                    case 0x10A5:
                        func_801477B4(globalCtx);
                        func_80B5CE6C(this, globalCtx);
                        break;

                    case 0x106D:
                        func_801477B4(globalCtx);
                        func_80B5C154(this, globalCtx);
                        break;
                }
            }
            break;
    }
}

s32 func_80B5D37C(GlobalContext* globalCtx, EnDno_ActorUnkStruct* arg1) {
    s32 pad;
    EnOt* temp_s0 = (EnOt*)arg1->unk_48;
    f32 sp24;
    f32 sp20;

    sp24 = Math_CosS(temp_s0->actor.world.rot.x * -1) * temp_s0->actor.speedXZ;
    sp20 = gFramerateDivisorHalf;

    temp_s0->actor.velocity.x = Math_SinS(temp_s0->actor.world.rot.y) * sp24;
    temp_s0->actor.velocity.y = Math_SinS(temp_s0->actor.world.rot.x * -1) * temp_s0->actor.speedXZ;
    do {
        temp_s0->actor.velocity.z = Math_CosS(temp_s0->actor.world.rot.y) * sp24;
        temp_s0->unk_330.x += (temp_s0->actor.velocity.x * sp20) + temp_s0->actor.colChkInfo.displacement.x;
        temp_s0->unk_330.y += (temp_s0->actor.velocity.y * sp20) + temp_s0->actor.colChkInfo.displacement.y;
    } while (0);
    temp_s0->unk_330.z += (temp_s0->actor.velocity.z * sp20) + temp_s0->actor.colChkInfo.displacement.z;

    return false;
}

s32 func_80B5D470(GlobalContext* globalCtx, EnDno_ActorUnkStruct* arg1) {
    s32 pad;
    s32 ret;
    Actor* temp_s1 = arg1->unk_48;
    Vec3f sp50;
    Vec3f sp44;
    f32 temp;
    s32 sp2C;
    s32 sp30;
    s32 sp34;

    ret = false;
    temp_s1->gravity = 0.0f;
    Math_SmoothStepToF(&temp_s1->speedXZ, 10.0f, 0.8f, 2.0f, 0.0f);

    sp50.x = arg1->unk_20.x - temp_s1->world.pos.x;
    sp50.y = arg1->unk_20.y - temp_s1->world.pos.y;
    sp50.z = arg1->unk_20.z - temp_s1->world.pos.z;

    sp44.x = arg1->unk_20.x - arg1->unk_38.x;
    sp44.y = arg1->unk_20.y - arg1->unk_38.y;
    sp44.z = arg1->unk_20.z - arg1->unk_38.z;

    temp = Math3D_Parallel(&sp50, &sp44);
    if ((arg1->unk_4C < SQ(temp_s1->speedXZ)) || (temp <= 0.0f)) {
        ret = true;
    } else {
        temp = SQ(temp_s1->speedXZ) / arg1->unk_50;
        sp34 = ABS(arg1->unk_54 - temp_s1->world.rot.x);
        sp2C = (s32)(sp34 * temp) + 0xAAA;

        sp34 = ABS(arg1->unk_56 - temp_s1->world.rot.y);

        Math_SmoothStepToS(&temp_s1->world.rot.x, arg1->unk_54, 1, sp2C, 0);
        sp2C = (s32)(sp34 * temp) + 0xAAA;
        Math_SmoothStepToS(&temp_s1->world.rot.y, arg1->unk_56, 1, sp2C, 0);
        Math_SmoothStepToS(&temp_s1->shape.rot.y, temp_s1->world.rot.y, 2, sp2C, 0);
    }

    return ret;
}

void func_80B5D648(EnOt* this, GlobalContext* globalCtx) {
    func_80B5B2E0(globalCtx, &this->actor.world.pos, this->unk_346, &this->unk_348, &this->unk_340);
    Math_Vec3f_Copy(&this->unk_330, &this->actor.world.pos);
    func_8013DCE0(globalCtx, &this->unk_330, &this->actor, &this->unk_2C0, globalCtx->setupPathList, this->unk_346, 0,
                  0, this->unk_340, 0);
    this->unk_32C = 0;
    this->unk_2C0.unk_2C.x = 0.0f;
    this->unk_2C0.unk_2C.y = 0.0f;
    this->unk_2C0.unk_2C.z = 0.0f;
    this->actor.gravity = 0.0f;
    this->actor.speedXZ = 0.0f;
    func_8013E1C8(&this->skelAnime, sAnimations, 1, &this->animIdx);
    this->actor.flags |= 0x8000000;
    this->actor.flags &= ~(0x8 | 0x1);
    Actor_SetSwitchFlag(globalCtx, ENOT_GET_3F80(&this->actor));
    this->actionFunc = func_80B5D750;
}

void func_80B5D750(EnOt* this, GlobalContext* globalCtx) {
    if (!(this->unk_32C & 1) && !(this->unk_32C & 2)) {
        func_8013DE04(globalCtx, &this->unk_2C0, func_8013DF3C, func_80B5D470, func_80B5D37C, func_8013E0A4);
    }

    Math_Vec3f_Copy(&this->actor.world.pos, &this->unk_330);

    if (this->unk_2C0.unk_1C & 0x40) {
        this->unk_32C |= 2;
    }

    if (this->unk_2C0.unk_1C & 0x80) {
        this->unk_32C |= 1;
    }

    if ((this->unk_32C & 2) && (this->actor.xyzDistToPlayerSq <= SQ(120.0f))) {
        this->unk_32C &= ~2;
    }

    if ((this->unk_32C & 1) && (this->actor.xzDistToPlayer <= 180.0f)) {
        this->actor.flags &= ~0x8000000;
        this->actor.flags |= (0x8 | 0x1);
        if (D_80B5E884 != 0) {
            func_80B5C9A8(this, globalCtx);
        } else {
            func_80B5CBA0(this, globalCtx);
        }
    }
}

void EnOt_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnOt* this = THIS;

    if ((this->animIdx == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_SEAHORSE_SWIM);
    }

    this->actionFunc(this, globalCtx);
    if (this->actor.bgCheckFlags & 0x20) {
        if (DECR(this->unk_354) == 0) {
            if (this->actor.flags & 0x40) {
                s32 i;

                for (i = 0; i < 2; i++) {
                    EffectSsBubble_Spawn(globalCtx, &this->actor.world.pos, 0.0f, 20.0f, 5.0f, 0.1f);
                }
                this->unk_354 = (Rand_ZeroOne() * 10.0f) + 10.0f;
            }
        }
    }

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 10.0f, 0.0f, 4);

    if (this->actor.world.pos.y <= this->actor.floorHeight + 50.0f) {
        this->actor.world.pos.y = this->actor.floorHeight + 50.0f;
        this->actor.prevPos.y = this->actor.floorHeight + 50.0f;
    }

    Actor_SetHeight(&this->actor, 12.0f);
    SkelAnime_Update(&this->skelAnime);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    func_80B5BB38(&this->unk_747, &this->unk_744, 0.7f);

    if (this->unk_32C & 0x400) {
        func_80B5BAAC(&this->lightInfo, &this->unk_378, &this->unk_747, 0xD2);
    }

    func_80B5E078(globalCtx, this->unk_3A4, 10);
}

void func_80B5DAEC(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnOt* this = THIS;

    this->actionFunc(this, globalCtx);
    Actor_SetHeight(&this->actor, 12.0f);
    SkelAnime_Update(&this->skelAnime);
    func_80B5BB38(&this->unk_747, &this->unk_744, 0.7f);
    if (this->unk_32C & 0x400) {
        func_80B5BAAC(&this->lightInfo, &this->unk_378, &this->unk_747, 210);
    }
}

void func_80B5DB6C(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnOt* this = THIS;
    Player* player = GET_PLAYER(globalCtx);

    if (!(gSaveContext.weekEventReg[84] & 0x10) && !(this->unk_32C & 8)) {
        if (gSaveContext.weekEventReg[25] & 4) {
            Vec3f sp50;

            func_80B5B2E0(globalCtx, &this->actor.world.pos, ENOT_GET_7F(&this->actor), &sp50, &this->unk_340);
            if (Actor_SpawnAsChildAndCutscene(&globalCtx->actorCtx, globalCtx, ACTOR_EN_OT, sp50.x, sp50.y, sp50.z, 0,
                                              this->actor.shape.rot.y, 1, ENOT_GET_3FFF(&this->actor) | 0x8000,
                                              this->actor.cutscene, this->actor.unk20, NULL) != NULL) {
                this->unk_32C |= 8;
            }
        } else if (D_80B5E888 != NULL) {
            s32 sp4C = false;

            if (gSaveContext.weekEventReg[13] & 1) {
                if (!func_800C9B90(&globalCtx->colCtx, player->actor.floorPoly, player->actor.floorBgId)) {
                    sp4C = true;
                }
            }

            if (!sp4C) {
                EnOt* temp = D_80B5E888;

                temp->unk_32C |= 8;
                temp->unk_346 = ENOT_GET_7F(&this->actor);
                temp->actor.params = this->actor.params;
                temp->actor.cutscene = this->actor.cutscene;
                this->unk_32C |= 8;
            }
        } else if (func_800C9B90(&globalCtx->colCtx, player->actor.floorPoly, player->actor.floorBgId)) {
            player->unk_B2B = 29;
        }
    }
}

void EnOt_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad[2];
    EnOt* this = THIS;
    Gfx* gfx;

    Matrix_StatePush();
    func_80B5E1D8(globalCtx, this->unk_3A4, 10);
    Matrix_StatePop();

    OPEN_DISPS(globalCtx->state.gfxCtx);

    POLY_OPA_DISP = Gfx_CallSetupDL(POLY_OPA_DISP, 25);
    POLY_XLU_DISP = func_8012C2B4(POLY_XLU_DISP);

    CLOSE_DISPS(globalCtx->state.gfxCtx);

    AnimatedMat_Draw(globalCtx, (AnimatedMaterial*)Lib_SegmentedToVirtual(&D_060005F8));
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          NULL, EnOt_PostLimbDraw, &this->actor);
    Matrix_InsertTranslation(this->unk_378.x, this->unk_378.y, this->unk_378.z, MTXMODE_NEW);
    Matrix_Scale(0.0882f, 0.0882f, 0.0882f, MTXMODE_APPLY);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gfx = func_8012C7FC(POLY_XLU_DISP);

    gSPSetOtherMode(&gfx[0], G_SETOTHERMODE_H, 4, 4, 0x00000080);
    gDPSetCombineLERP(&gfx[1], 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE,
                      0);
    gSPDisplayList(&gfx[2], D_04029CB0);
    gDPSetPrimColor(&gfx[3], 0, 0, this->unk_747.r, this->unk_747.g, this->unk_747.b, 50);
    gSPMatrix(&gfx[4], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(&gfx[5], D_04029CF0);

    POLY_XLU_DISP = &gfx[6];

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnOt_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80B5E410 = { 400.0f, 600.0f, 0.0f };
    EnOt* this = THIS;

    if (limbIndex == 4) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        Gfx* gfx = POLY_OPA_DISP;

        gSPDisplayList(&gfx[0], D_060004A0);
        POLY_OPA_DISP = &gfx[1];
        Matrix_MultiplyVector3fByState(&D_80B5E410, &this->unk_74C);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    } else if (limbIndex == 1) {
        Matrix_GetStateTranslation(&this->unk_378);
        this->unk_32C |= 0x400;
    }
}

EnOtUnkStruct* func_80B5DF58(EnOtUnkStruct* arg0, u8 arg1, Vec3f* arg2, Vec3s* arg3, s32 arg4) {
    s32 i = 0;

    while (i < arg4 && arg0->unk_00) {
        i++;
        arg0++;
    }

    if ((i < arg4) && ((arg1 == 1) || (arg1 == 2))) {
        arg0->unk_00 = arg1;
        Math_Vec3f_Copy(&arg0->unk_0C, arg2);
        Math_Vec3f_Copy(&arg0->unk_50, arg2);
        arg0->unk_04 = 0.009f;
        arg0->unk_30 = 0.0f;
        arg0->unk_34 = 0.0f;
        arg0->unk_38 = 0.3f;
        arg0->unk_3C = 1.4f;
        arg0->unk_40 = -0.05f;
        arg0->unk_4C = 40;

        if (arg0->unk_00 == 2) {
            arg0->unk_30 = -arg0->unk_30;
            arg0->unk_38 = -arg0->unk_38;
        }
    }

    return arg0;
}

void func_80B5E078(GlobalContext* globalCtx, EnOtUnkStruct* arg1, s32 arg2) {
    Vec3f sp54;
    s32 i;
    s16 temp = Camera_GetInputDirYaw(GET_ACTIVE_CAM(globalCtx));

    for (i = 0; i < arg2; i++, arg1++) {
        if ((arg1->unk_00 == 1) || (arg1->unk_00 == 2)) {
            if (DECR(arg1->unk_4C) == 0) {
                arg1->unk_00 = 0;
            }

            arg1->unk_30 += arg1->unk_38;
            arg1->unk_34 += arg1->unk_3C;
            arg1->unk_3C += arg1->unk_40;
            sp54.x = arg1->unk_30;
            sp54.y = arg1->unk_34;
            sp54.z = 0.0f;
            Matrix_RotateY(temp, 0);
            Matrix_MultiplyVector3fByState(&sp54, &arg1->unk_0C);
            Math_Vec3f_Sum(&arg1->unk_0C, &arg1->unk_50, &arg1->unk_0C);
            arg1->unk_4C--;
        }
    }
}

void func_80B5E1D8(GlobalContext* globalCtx, EnOtUnkStruct* arg1, s32 arg2) {
    s32 i;
    s32 flag = 0;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
    POLY_OPA_DISP = func_8012C724(POLY_OPA_DISP);

    for (i = 0; i < arg2; i++, arg1++) {
        if (arg1->unk_00) {
            if (!flag) {
                gSPDisplayList(POLY_OPA_DISP++, D_06000040);
                flag = true;
                if (globalCtx) {}
            }

            Matrix_InsertTranslation(arg1->unk_0C.x, arg1->unk_0C.y, arg1->unk_0C.z, MTXMODE_NEW);
            Matrix_RotateY(BINANG_ROT180(Camera_GetCamDirYaw(GET_ACTIVE_CAM(globalCtx))), MTXMODE_APPLY);
            Matrix_Scale(arg1->unk_04, arg1->unk_04, arg1->unk_04, MTXMODE_APPLY);

            gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(&D_0405E6F0));
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, D_06000078);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
