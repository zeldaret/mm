/*
 * File: z_en_syateki_wf.c
 * Overlay: ovl_En_Syateki_Wf
 * Description: Shooting Gallery Wolfos
 */

#include "z_en_syateki_wf.h"
#include "overlays/actors/ovl_En_Syateki_Man/z_en_syateki_man.h"
#include "objects/object_wf/object_wf.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_8000000)

#define THIS ((EnSyatekiWf*)thisx)

void EnSyatekiWf_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiWf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiWf_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiWf_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A201CC(EnSyatekiWf* this);
void func_80A20284(EnSyatekiWf* this, GlobalContext* globalCtx);
void func_80A2030C(EnSyatekiWf* this);
void func_80A20320(EnSyatekiWf* this, GlobalContext* globalCtx);
void func_80A20378(EnSyatekiWf* this);
void func_80A203DC(EnSyatekiWf* this, GlobalContext* globalCtx);
void func_80A20670(EnSyatekiWf* this);
void func_80A206DC(EnSyatekiWf* this, GlobalContext* globalCtx);
void func_80A20710(EnSyatekiWf* this);
void func_80A2075C(EnSyatekiWf* this, GlobalContext* globalCtx);
void func_80A2079C(EnSyatekiWf* this);
void func_80A20800(EnSyatekiWf* this, GlobalContext* globalCtx);
void func_80A208F8(EnSyatekiWf* this, GlobalContext* globalCtx);

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 17, { { 800, 0, 0 }, 25 }, 100 },
    },
};

static ColliderCylinderInit sCylinderInit1 = {
    {
        COLTYPE_HIT5,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 40, 60, 0, { 0, 0, 0 } },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HIT5,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit,
};

static ColliderCylinderInit sCylinderInit2 = {
    {
        COLTYPE_HIT5,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 15, 20, -15, { 0, 0, 0 } },
};

static Vec3f D_80A20EDC = { 0.0f, 20.0f, 0.0f };

static Vec3f D_80A20EE8 = { 0.0f, 0.0f, 0.0f };

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

static AnimationInfo sAnimations[] = {
    { &object_wf_Anim_00A3CC, 2.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -1.0f },
    { &object_wf_Anim_005700, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -8.0f },
    { &object_wf_Anim_005700, 1.0f, 0.0f, 4.0f, ANIMMODE_ONCE, 1.0f },
    { &object_wf_Anim_005700, 1.0f, 4.0f, 8.0f, ANIMMODE_ONCE, 1.0f },
    { &object_wf_Anim_004A90, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &object_wf_Anim_009A50, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 8.0f },
    { &object_wf_Anim_0053D0, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_STOP),
};

static Vec3f D_80A20FC4 = { 0.0f, 0.5f, 0.0f };

static Vec3f D_80A20FD0 = { 1200.0f, 0.0f, 0.0f };

static TexturePtr sEyeTextures[] = {
    object_wf_Tex_007AA8,
    object_wf_Tex_0082A8,
    object_wf_Tex_0084A8,
    object_wf_Tex_0082A8,
};

void EnSyatekiWf_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnSyatekiWf* this = THIS;
    Path* path;
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;
    s32 i;

    path = syatekiMan->path;
    while (path->unk2 != 2) {
        path = &globalCtx->setupPathList[path->unk1];
    }

    for (i = 0; i < EN_SYATEKI_WF_GET_PARAM_FF00(&this->actor); i++) {
        path = &globalCtx->setupPathList[path->unk1];
    }

    if (path == NULL) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->unk_2A0 = Lib_SegmentedToVirtual(path->points);
    this->unk_2A4 = 1;
    this->unk_2A6 = path->count;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->unk_29C = 0;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 0.0f);
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.colChkInfo.health = 2;
    this->actor.colChkInfo.cylRadius = 50;
    this->actor.colChkInfo.cylHeight = 100;
    this->eyeIndex = 0;
    this->unk_2AC = 10.0f;

    Collider_InitCylinder(globalCtx, &this->unk_2B4);
    Collider_SetCylinder(globalCtx, &this->unk_2B4, &this->actor, &sCylinderInit1);
    Collider_InitCylinder(globalCtx, &this->unk_300);
    Collider_SetCylinder(globalCtx, &this->unk_300, &this->actor, &sCylinderInit2);
    Collider_InitJntSph(globalCtx, &this->unk_34C);
    Collider_SetJntSph(globalCtx, &this->unk_34C, &this->actor, &sJntSphInit, &this->unk_36C);
    this->unk_34C.elements->dim.worldSphere.radius = sJntSphInit.elements[0].dim.modelSphere.radius;

    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_wf_Skel_0095D0, &object_wf_Anim_00A3CC, this->jointTable,
                       this->morphTable, 22);
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
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
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
                if (this->unk_2A4 == EN_SYATEKI_WF_GET_PARAM_F0(&this->actor)) {
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

void func_80A20670(EnSyatekiWf* this) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_TEKU_JUMP);
    this->actor.velocity.y = 20.0f;
    this->actor.speedXZ = 5.0f;
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
    this->actionFunc = func_80A206DC;
}

void func_80A206DC(EnSyatekiWf* this, GlobalContext* globalCtx) {
    if (this->actor.bgCheckFlags & 2) {
        func_80A20710(this);
    }
}

void func_80A20710(EnSyatekiWf* this) {
    this->actor.speedXZ = 0.0f;
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
    this->actionFunc = func_80A2075C;
}

void func_80A2075C(EnSyatekiWf* this, GlobalContext* globalCtx) {
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        func_80A20378(this);
    }
}

void func_80A2079C(EnSyatekiWf* this) {
    this->unk_29A = 40;
    this->actor.speedXZ = 0.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WOLFOS_APPEAR);
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 5);
    this->actionFunc = func_80A20800;
}

void func_80A20800(EnSyatekiWf* this, GlobalContext* globalCtx) {
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        this->unk_29A--;
        if (this->unk_29A == 0) {
            func_80A20378(this);
        }
    }
}

void func_80A20858(EnSyatekiWf* this, GlobalContext* globalCtx) {
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    this->unk_298 = 0;
    this->actor.speedXZ = 0.0f;
    EffectSsExtra_Spawn(globalCtx, &this->actor.world.pos, &D_80A20EDC, &D_80A20EE8, 5, 2);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WOLFOS_DEAD);
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 6);
    syatekiMan->unk_280 += 100;
    this->actionFunc = func_80A208F8;
}

void func_80A208F8(EnSyatekiWf* this, GlobalContext* globalCtx) {
    s32 pad;

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        func_80A201CC(this);
    } else {
        Vec3f sp68;
        Vec3f sp5C = D_80A20FC4;
        s32 i;

        for (i = (s32)this->skelAnime.animLength - (s32)this->skelAnime.curFrame; i >= 0; i--) {
            sp68.x = randPlusMinusPoint5Scaled(60.0f) + this->actor.world.pos.x;
            sp68.z = randPlusMinusPoint5Scaled(60.0f) + this->actor.world.pos.z;
            sp68.y = randPlusMinusPoint5Scaled(50.0f) + (this->actor.world.pos.y + 20.0f);
            func_800B3030(globalCtx, &sp68, &sp5C, &sp5C, 0x64, 0, 2);
        }
    }
}

void EnSyatekiWf_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnSyatekiWf* this = THIS;

    if (this->actionFunc != func_80A20284) {
        SkelAnime_Update(&this->skelAnime);
    }

    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 32.0f, 30.0f, 60.0f, 5);
    this->actionFunc(this, globalCtx);

    if (this->actor.bgCheckFlags & 3) {
        func_800BE3D0(&this->actor, this->actor.shape.rot.y, &this->actor.shape.rot);
    } else {
        Math_SmoothStepToS(&this->actor.shape.rot.x, 0, 1, 0x3E8, 0);
        Math_SmoothStepToS(&this->actor.shape.rot.z, 0, 1, 0x3E8, 0);
    }

    if ((this->unk_2B4.base.acFlags & AC_HIT) || (this->unk_300.base.acFlags & AC_HIT) ||
        (this->unk_34C.base.acFlags & AC_HIT)) {
        this->unk_2B4.base.acFlags &= ~AC_HIT;
        this->unk_300.base.acFlags &= ~AC_HIT;
        this->unk_34C.base.acFlags &= ~AC_HIT;
        this->actor.colChkInfo.health -= 2;
        if (this->actor.colChkInfo.health == 0) {
            func_801A3098(NA_BGM_GET_ITEM | 0x900);
            func_80A20858(this, globalCtx);
        } else {
            play_sound(NA_SE_SY_TRE_BOX_APPEAR);
            EffectSsExtra_Spawn(globalCtx, &this->actor.world.pos, &D_80A20EDC, &D_80A20EE8, 3, 0);
        }
    }

    Collider_UpdateCylinder(&this->actor, &this->unk_2B4);
    if ((this->actionFunc != func_80A20284) && (this->actionFunc != func_80A208F8) && (this->actor.draw != NULL)) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->unk_300.base);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->unk_2B4.base);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->unk_34C.base);
        this->actor.focus.pos = this->actor.world.pos;
        this->actor.focus.pos.y += 25.0f;
    }

    if (this->eyeIndex == 0) {
        if ((Rand_ZeroOne() < 0.2f) && ((globalCtx->gameplayFrames & 3) == 0) && (this->actor.colorFilterTimer == 0)) {
            this->eyeIndex++;
        }
    } else {
        this->eyeIndex = (this->eyeIndex + 1) & 3;
    }
}

s32 EnSyatekiWf_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                 Actor* thisx) {
    return false;
}

void EnSyatekiWf_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnSyatekiWf* this = THIS;
    Vec3f sp18;

    Collider_UpdateSpheres(limbIndex, &this->unk_34C);
    if (limbIndex == OBJECT_WF_2_LIMB_06) {
        Matrix_MultiplyVector3fByState(&D_80A20FD0, &sp18);
        this->unk_300.dim.pos.x = sp18.x;
        this->unk_300.dim.pos.y = sp18.y;
        this->unk_300.dim.pos.z = sp18.z;
    }
}

void EnSyatekiWf_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnSyatekiWf* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeIndex]));
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnSyatekiWf_OverrideLimbDraw, EnSyatekiWf_PostLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
