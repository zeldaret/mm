/*
 * File: z_en_syateki_wf.c
 * Overlay: ovl_En_Syateki_Wf
 * Description: Shooting Gallery Wolfos
 */

#include "z_en_syateki_wf.h"
#include "overlays/actors/ovl_En_Syateki_Man/z_en_syateki_man.h"

#define FLAGS 0x08000030

#define THIS ((EnSyatekiWf*)thisx)

void EnSyatekiWf_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiWf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiWf_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiWf_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A20284(EnSyatekiWf* this, GlobalContext* globalCtx);
void func_80A20320(EnSyatekiWf* this, GlobalContext* globalCtx);
void func_80A203DC(EnSyatekiWf* this, GlobalContext* globalCtx);
void func_80A206DC(EnSyatekiWf* this, GlobalContext* globalCtx);
void func_80A2075C(EnSyatekiWf* this, GlobalContext* globalCtx);
void func_80A20800(EnSyatekiWf* this, GlobalContext* globalCtx);
void func_80A208F8(EnSyatekiWf* this, GlobalContext* globalCtx);
void func_80A201CC(EnSyatekiWf* this);
void func_80A2030C(EnSyatekiWf* this);
void func_80A20378(EnSyatekiWf* this);
void func_80A20670(EnSyatekiWf* this);
void func_80A2079C(EnSyatekiWf* this);

#if 0
// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80A20E50[1] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 17, { { 800, 0, 0 }, 25 }, 100 },
    },
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A20E74 = {
    { COLTYPE_HIT5, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 40, 60, 0, { 0, 0, 0 } },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A20EA0 = {
    { COLTYPE_HIT5, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_80A20E50, // sJntSphElementsInit,
};

static ColliderJntSphElementInit* D_80A20EAC = &D_80A20E50;

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A20EB0 = {
    { COLTYPE_HIT5, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 15, 20, -15, { 0, 0, 0 } },
};

const ActorInit En_Syateki_Wf_InitVars = {
    ACTOR_EN_SYATEKI_WF,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_WF,
    sizeof(EnSyatekiWf),
    (ActorFunc)EnSyatekiWf_Init,
    (ActorFunc)EnSyatekiWf_Destroy,
    (ActorFunc)EnSyatekiWf_Update,
    (ActorFunc)EnSyatekiWf_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A20FBC[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_STOP),
};

#endif

extern ColliderJntSphElementInit D_80A20E50[1];
extern ColliderCylinderInit D_80A20E74;
extern ColliderJntSphInit D_80A20EA0;
extern ColliderJntSphElementInit* D_80A20EAC;
extern ColliderCylinderInit D_80A20EB0;
extern AnimationInfo D_80A20F14;
extern InitChainEntry D_80A20FBC[];

extern FlexSkeletonHeader D_060095D0;
extern AnimationHeader D_0600A3CC;

void EnSyatekiWf_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnSyatekiWf* this = THIS;
    Path* path;
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;
    s32 temp;

    path = syatekiMan->path;
    if (path->unk2 != 2) {
        do {
            path = &globalCtx->setupPathList[path->unk1];
        } while (path->unk2 != 2);
    }

    temp = 0;
    if (EN_SYATEKI_WF_GET_PARAM_FF00(&this->actor) > 0) {
        do {
            temp++;
            path = &globalCtx->setupPathList[path->unk1];
        } while (temp < EN_SYATEKI_WF_GET_PARAM_FF00(&this->actor));
    }

    if (path == NULL) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->unk_2A0 = Lib_SegmentedToVirtual(path->points);
    this->unk_2A4 = 1;
    this->unk_2A6 = path->count;

    Actor_ProcessInitChain(&this->actor, D_80A20FBC);
    this->unk_29C = 0;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 0.0f);
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.colChkInfo.health = 2;
    this->actor.colChkInfo.cylRadius = 50;
    this->actor.colChkInfo.cylHeight = 100;
    this->unk_2B0 = 0;
    this->unk_2AC = 10.0f;

    Collider_InitCylinder(globalCtx, &this->unk_2B4);
    Collider_SetCylinder(globalCtx, &this->unk_2B4, &this->actor, &D_80A20E74);
    Collider_InitCylinder(globalCtx, &this->unk_300);
    Collider_SetCylinder(globalCtx, &this->unk_300, &this->actor, &D_80A20EB0);
    Collider_InitJntSph(globalCtx, &this->unk_34C);
    Collider_SetJntSph(globalCtx, &this->unk_34C, &this->actor, &D_80A20EA0, &this->unk_36C);
    this->unk_34C.elements->dim.worldSphere.radius = D_80A20EAC->dim.modelSphere.radius;

    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_060095D0, &D_0600A3CC, this->jointTable, this->morphTable, 22);
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.hintId = 0x4C;

    func_80A201CC(this);
}

void EnSyatekiWf_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnSyatekiWf* this = THIS;
    Collider_DestroyCylinder(globalCtx, &this->unk_2B4);
    Collider_DestroyCylinder(globalCtx, &this->unk_300);
}

void func_80A200E0(EnSyatekiWf* this) {
    Vec3f sp24;
    s16 temp;

    this->actor.world.pos.x = this->unk_2A0[0].x;
    this->actor.world.pos.y = this->unk_2A0[0].y;
    this->actor.world.pos.z = this->unk_2A0[0].z;
    sp24.x = this->unk_2A0[this->unk_2A4].x;
    sp24.y = this->unk_2A0[this->unk_2A4].y;
    sp24.z = this->unk_2A0[this->unk_2A4].z;
    temp = Math_Vec3f_Yaw(&this->actor.world.pos, &sp24);
    this->actor.shape.rot.y = temp;
    this->actor.world.rot.y = temp;
}

void func_80A201CC(EnSyatekiWf* this) {
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;
    this->actor.speedXZ = 0.0f;
    this->actor.world = this->actor.home;
    this->actor.prevPos = this->actor.home.pos;
    this->actor.shape.rot = this->actor.world.rot;
    this->actor.colChkInfo.health = 2;
    this->actor.draw = NULL;
    this->unk_2A4 = 1;
    this->unk_298 = 0;
    syatekiMan->unk_276 &= ~(1 << EN_SYATEKI_WF_GET_PARAM_FF00(&this->actor));
    this->actionFunc = func_80A20284;
}

void func_80A20284(EnSyatekiWf* this, GlobalContext* globalCtx) {
    EnSyatekiMan* syatekiMan;

    if (this->actor.parent != NULL) {
        syatekiMan = (EnSyatekiMan*)this->actor.parent;
        if ((syatekiMan->unk_26A == 1) && (this->unk_298 == 1)) {
            func_80A200E0(this);
            func_80A2030C(this);
        } else if (syatekiMan->unk_276 & (1 << EN_SYATEKI_WF_GET_PARAM_FF00(&this->actor))) {
            this->unk_298 = 1;
        }
    }
}

void func_80A2030C(EnSyatekiWf* this) {
    this->actionFunc = func_80A20320;
}

void func_80A20320(EnSyatekiWf* this, GlobalContext* globalCtx) {
    if (this->unk_29C >= 11) {
        Actor_PlaySfxAtPos(this->actor.parent, NA_SE_EN_WOLFOS_APPEAR);
        this->unk_29C = 0;
        func_80A20378(this);
    } else {
        this->unk_29C++;
    }
}

void func_80A20378(EnSyatekiWf* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, &D_80A20F14, 1);
    this->actor.speedXZ = 10.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actor.draw = EnSyatekiWf_Draw;
    this->actionFunc = func_80A203DC;
}

void func_80A203DC(EnSyatekiWf* this, GlobalContext* globalCtx) {
    Vec3f sp54;
    f32 sp50;
    s16 temp_v0;
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    if (syatekiMan->unk_26A != 1) {
        func_80A201CC(this);
    }

    sp54.x = this->unk_2A0[this->unk_2A4].x;
    sp54.y = this->unk_2A0[this->unk_2A4].y;
    sp54.z = this->unk_2A0[this->unk_2A4].z;
    temp_v0 = (this->actor.wallYaw - this->actor.world.rot.y) + 0x8000;

    if (this->actor.bgCheckFlags & 1) {
        if (this->actor.bgCheckFlags & 8) {
            if ((ABS(temp_v0) < 0x1555) && (this->actor.wallPoly != this->actor.floorPoly)) {
                func_80A20670(this);
                return;
            }
        }

        if (this->actor.bgCheckFlags & 4) {
            this->actor.velocity.y = 2.0f;
        }

        sp50 = Math_Vec3f_DistXZ(&this->actor.world.pos, &sp54);
        this->unk_2A8 = Math_Vec3f_Yaw(&this->actor.world.pos, &sp54);

        if (sp50 > 15.0f) {
            Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_2A8, 5, 0x3000, 0x100);
            this->actor.shape.rot.y = this->actor.world.rot.y;
            if (sp50 < 50.0f) {
                if (this->actor.speedXZ > 3.0f) {
                    this->actor.speedXZ = this->actor.speedXZ - 0.5f;
                } else {
                    this->actor.speedXZ = this->actor.speedXZ;
                }
            }
        } else {
            if (this->unk_2A4 < (this->unk_2A6 - 1)) {
                if (this->unk_2A4 == ((this->actor.params & 0xF0) >> 4)) {
                    func_80A2079C(this);
                }

                this->unk_2A4++;
            } else {
                this->unk_298 = 0;
                this->unk_2A4 = 1;
                func_80A201CC(this);
            }
        }

        if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            Actor_SpawnFloorDustRing(globalCtx, &this->actor, &this->actor.world.pos, 10.0f, 3, 2.0f, 0, 0, 0);
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20670.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A206DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20710.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A2075C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A2079C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20800.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20858.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A208F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/EnSyatekiWf_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20CF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20D10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/EnSyatekiWf_Draw.s")
