/*
 * File: z_en_syateki_dekunuts.c
 * Overlay: ovl_En_Syateki_Dekunuts
 * Description: Shooting Gallery Deku Scrub
 */

#include "z_en_syateki_dekunuts.h"
#include "overlays/actors/ovl_En_Syateki_Man/z_en_syateki_man.h"
#include "overlays/effects/ovl_Effect_Ss_Hahen/z_eff_ss_hahen.h"
#include "objects/object_dekunuts/object_dekunuts.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_8000000)

#define THIS ((EnSyatekiDekunuts*)thisx)

void EnSyatekiDekunuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiDekunuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiDekunuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiDekunuts_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A2BE54(EnSyatekiDekunuts* this);
void func_80A2BF18(EnSyatekiDekunuts* this, GlobalContext* globalCtx);
void func_80A2BFC4(EnSyatekiDekunuts* this);
void func_80A2C0F8(EnSyatekiDekunuts* this, GlobalContext* globalCtx);
void func_80A2C150(EnSyatekiDekunuts* this);
void func_80A2C168(EnSyatekiDekunuts* this, GlobalContext* globalCtx);
void func_80A2C1AC(EnSyatekiDekunuts* this);
void func_80A2C208(EnSyatekiDekunuts* this, GlobalContext* globalCtx);
void func_80A2C27C(EnSyatekiDekunuts* this);
void func_80A2C2E0(EnSyatekiDekunuts* this, GlobalContext* globalCtx);
void func_80A2C33C(EnSyatekiDekunuts* this, GlobalContext* globalCtx);
void func_80A2C3AC(EnSyatekiDekunuts* this);
void func_80A2C3F0(EnSyatekiDekunuts* this, GlobalContext* globalCtx);
void func_80A2C478(EnSyatekiDekunuts* this);
void func_80A2C48C(EnSyatekiDekunuts* this, GlobalContext* globalCtx);
void func_80A2C5DC(EnSyatekiDekunuts* this, GlobalContext* globalCtx);

const ActorInit En_Syateki_Dekunuts_InitVars = {
    ACTOR_EN_SYATEKI_DEKUNUTS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DEKUNUTS,
    sizeof(EnSyatekiDekunuts),
    (ActorFunc)EnSyatekiDekunuts_Init,
    (ActorFunc)EnSyatekiDekunuts_Destroy,
    (ActorFunc)EnSyatekiDekunuts_Update,
    (ActorFunc)EnSyatekiDekunuts_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT6,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
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
        OCELEM_NONE,
    },
    { 48, 80, 0, { 0, 0, 0 } },
};

static Cylinder16 D_80A2CADC[] = { { 24, 40, 0, { 0, 0, 0 } } };

static AnimationInfo sAnimations[] = {
    { &object_dekunuts_Anim_003180, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &object_dekunuts_Anim_002A5C, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &object_dekunuts_Anim_00326C, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -1.0f },
    { &object_dekunuts_Anim_002FA4, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -1.0f },
    { &object_dekunuts_Anim_00259C, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &object_dekunuts_Anim_002BD4, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &object_dekunuts_Anim_002DD4, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, 77, ICHAIN_CONTINUE),
    ICHAIN_F32(gravity, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2600, ICHAIN_STOP),
};

void EnSyatekiDekunuts_Init(Actor* thisx, GlobalContext* globalCtx2) {
    static s32 D_80A2CB9C = 1;
    EnSyatekiDekunuts* this = THIS;
    GlobalContext* globalCtx = globalCtx2;
    s32 phi_v0;
    Path* path;
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;
    s32 i;

    path = syatekiMan->path;
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);

    if (EN_SYATEKI_DEKUNUTS_GET_PARAM_F(&this->actor) == 1) {
        Actor_SetScale(&this->actor, 0.01f);
        this->collider.dim = D_80A2CADC[0];
        phi_v0 = 3;
    } else {
        Actor_SetScale(&this->actor, 0.02f);
        phi_v0 = 1;
    }

    while (path->unk2 != phi_v0) {
        path = &globalCtx->setupPathList[path->unk1];
    }

    for (i = 0; i < EN_SYATEKI_DEKUNUTS_GET_PARAM_FF00(&this->actor); i++) {
        path = &globalCtx->setupPathList[path->unk1];
    }

    if (D_80A2CB9C == 1) {
        this->unk_1EC = 1;
        D_80A2CB9C = 0;
    } else {
        this->unk_1EC = 0;
    }

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 35.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_dekunuts_Skel_002468, &object_dekunuts_Anim_002A5C,
                   this->jointTable, this->morphTable, 10);
    if (path == NULL) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->unk_1E4 = Lib_SegmentedToVirtual(path->points);
    this->unk_1E8 = EN_SYATEKI_DEKUNUTS_GET_PARAM_F0(&this->actor);
    this->unk_1EA = path->count;
    this->unk_1D8 = 0;
    this->unk_1DC = 0;
    this->unk_1DA = 0;
    func_80A2BE54(this);
}

void EnSyatekiDekunuts_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnSyatekiDekunuts* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80A2BE54(EnSyatekiDekunuts* this) {
    Animation_PlayOnceSetSpeed(&this->skelAnime, &object_dekunuts_Anim_003180, 0.0f);

    this->actor.speedXZ = 0.0f;
    this->actor.world = this->actor.home;
    this->actor.prevPos = this->actor.home.pos;
    this->actor.shape.rot = this->actor.world.rot;

    this->unk_1D8 = 0;
    this->unk_1DC = 0;

    if (EN_SYATEKI_DEKUNUTS_GET_PARAM_F(&this->actor) != 1) {
        this->unk_1E2 = 1;
    }

    this->actionFunc = func_80A2BF18;
}

void func_80A2BF18(EnSyatekiDekunuts* this, GlobalContext* globalCtx) {
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    if ((syatekiMan->unk_26A == 1) && (this->unk_1E2 == 1) && ((syatekiMan->unk_272 & (1 << this->unk_1E8)) != 0)) {
        func_80A2BFC4(this);
    } else if (syatekiMan->unk_26A != 1) {
        this->unk_1E2 = 1;
    }

    if ((syatekiMan->unk_272 == 0) && (syatekiMan->unk_274 == 0) &&
        (EN_SYATEKI_DEKUNUTS_GET_PARAM_F(&this->actor) != 1)) {
        this->unk_1E2 = 1;
    }
}

void func_80A2BFC4(EnSyatekiDekunuts* this) {
    Vec3f sp14;
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    this->unk_1D8 = 0;
    sp14.x = this->unk_1E4[this->unk_1E8].x;
    sp14.y = this->unk_1E4[this->unk_1E8].y;
    sp14.z = this->unk_1E4[this->unk_1E8].z;
    this->actor.world.pos = this->actor.prevPos = sp14;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    this->unk_1EE = 140 - (syatekiMan->unk_27C * 20);

    if ((syatekiMan->unk_27C & 1) != 0) {
        this->unk_1F0 = 1;
        this->unk_1F2 = 0;
    } else {
        this->unk_1F0 = 0;
    }

    this->actionFunc = func_80A2C0F8;
}

void func_80A2C0F8(EnSyatekiDekunuts* this, GlobalContext* globalCtx) {
    EnSyatekiMan* syatekiMan;

    if (this->unk_1DA > 20) {
        syatekiMan = (EnSyatekiMan*)this->actor.parent;
        Actor_PlaySfxAtPos(&syatekiMan->actor, NA_SE_EN_NUTS_DAMAGE);
        this->unk_1DA = 0;
        func_80A2C150(this);
    } else {
        this->unk_1DA++;
    }
}

void func_80A2C150(EnSyatekiDekunuts* this) {
    this->unk_1D8 = 0;
    this->actionFunc = func_80A2C168;
}

void func_80A2C168(EnSyatekiDekunuts* this, GlobalContext* globalCtx) {
    if (this->unk_1DA > 20) {
        func_80A2C1AC(this);
        this->unk_1DA = 0;
    } else {
        this->unk_1DA++;
    }
}

void func_80A2C1AC(EnSyatekiDekunuts* this) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_UP);
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actionFunc = func_80A2C208;
}

void func_80A2C208(EnSyatekiDekunuts* this, GlobalContext* globalCtx) {
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        func_80A2C27C(this);
    }

    if (this->unk_1F0 == 1) {
        Math_SmoothStepToS(&this->unk_1F2, -0x8000, 5, 0x1000, 0x100);
    }

    this->unk_1D8++;
}

void func_80A2C27C(EnSyatekiDekunuts* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
    if (EN_SYATEKI_DEKUNUTS_GET_PARAM_F(&this->actor) != 1) {
        this->actionFunc = func_80A2C2E0;
    } else {
        this->actionFunc = func_80A2C33C;
    }
}

void func_80A2C2E0(EnSyatekiDekunuts* this, GlobalContext* globalCtx) {
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    if ((this->unk_1EE < this->unk_1D8) || (syatekiMan->unk_26A != 1)) {
        func_80A2C3AC(this);
    }

    this->unk_1D8++;
}

void func_80A2C33C(EnSyatekiDekunuts* this, GlobalContext* globalCtx) {
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    if ((gSaveContext.unk_3DE0[1] <= 0) || (syatekiMan->unk_26A != 1)) {
        func_80A2C3AC(this);
    }

    if (this->unk_1D8 < 11) {
        this->unk_1D8++;
    }
}

void func_80A2C3AC(EnSyatekiDekunuts* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
    this->actionFunc = func_80A2C3F0;
}

void func_80A2C3F0(EnSyatekiDekunuts* this, GlobalContext* globalCtx) {
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    if (syatekiMan->unk_26A == 1) {
        if (this->unk_1D8 > 160 && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            this->unk_1D8 = 0;
            func_80A2C150(this);
        } else {
            this->unk_1D8++;
        }
    } else {
        func_80A2C478(this);
    }
}

void func_80A2C478(EnSyatekiDekunuts* this) {
    this->actionFunc = func_80A2C48C;
}

void func_80A2C48C(EnSyatekiDekunuts* this, GlobalContext* globalCtx) {
    if (this->unk_1DA > 20) {
        func_80A2BE54(this);
        this->unk_1DA = 0;
    } else {
        this->unk_1DA++;
    }
}

void func_80A2C4D0(EnSyatekiDekunuts* this, GlobalContext* globalCtx) {
    static Vec3f D_80A2CBA0 = { 0.0f, 20.0f, 0.0f };
    static Vec3f D_80A2CBAC = { 0.0f, 0.0f, 0.0f };
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    if (EN_SYATEKI_DEKUNUTS_GET_PARAM_F(&this->actor) == 1) {
        EffectSsExtra_Spawn(globalCtx, &this->actor.world.pos, &D_80A2CBA0, &D_80A2CBAC, 5, 2);
        syatekiMan->unk_280 += 100;
        syatekiMan->unk_26E++;
    } else {
        EffectSsExtra_Spawn(globalCtx, &this->actor.world.pos, &D_80A2CBA0, &D_80A2CBAC, 5, 0);
        syatekiMan->unk_280 += 30;
        syatekiMan->unk_278++;
    }

    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_DAMAGE);
    this->unk_1E2 = 0;
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 4);
    this->unk_1D8 = 160;
    this->actionFunc = func_80A2C5DC;
}

void func_80A2C5DC(EnSyatekiDekunuts* this, GlobalContext* globalCtx) {
    static Color_RGBA8 D_80A2CBB8 = { 255, 255, 255, 255 };
    static Color_RGBA8 D_80A2CBBC = { 150, 150, 150, 0 };
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        if (this->unk_1D8 == 160) {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 5);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_DEAD);
            this->unk_1D8--;
        } else if (this->unk_1D8 < 160) {
            Vec3f sp40;

            sp40.x = this->actor.world.pos.x;
            sp40.y = this->actor.world.pos.y + 18.0f;
            sp40.z = this->actor.world.pos.z;
            EffectSsDeadDb_Spawn(globalCtx, &sp40, &gZeroVec3f, &gZeroVec3f, &D_80A2CBB8, &D_80A2CBBC, 200, 0, 13);
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 30, NA_SE_EN_EXTINCT);
            sp40.y = this->actor.world.pos.y + 10.0f;
            EffectSsHahen_SpawnBurst(globalCtx, &sp40, 3.0f, 0, 12, 3, 15, HAHEN_OBJECT_DEFAULT, 10, NULL);

            if (EN_SYATEKI_DEKUNUTS_GET_PARAM_F(&this->actor) != 1) {
                syatekiMan->unk_272 &= ~(1 << this->unk_1E8);
            }

            func_80A2BE54(this);
        }
    } else if (this->unk_1D8 < 160) {
        this->unk_1D8--;
    }
}

void EnSyatekiDekunuts_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnSyatekiDekunuts* this = THIS;

    this->actionFunc(this, globalCtx);

    if ((this->actionFunc != func_80A2BF18) && (this->unk_1D8 < this->unk_1EE) && (this->unk_1D8 > 10)) {
        if ((this->collider.base.acFlags & AC_HIT) && (this->unk_1E2 == 1)) {
            if (EN_SYATEKI_DEKUNUTS_GET_PARAM_F(&this->actor) == 1) {
                func_801A3098(NA_BGM_GET_ITEM | 0x900);
            } else {
                play_sound(NA_SE_SY_TRE_BOX_APPEAR);
            }

            this->collider.base.acFlags &= ~AC_HIT;
            func_80A2C4D0(this, globalCtx);
        }

        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    } else {
        this->collider.base.acFlags &= ~AC_HIT;
    }

    SkelAnime_Update(&this->skelAnime);
}

s32 EnSyatekiDekunuts_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                       Actor* thisx) {
    EnSyatekiDekunuts* this = THIS;

    if ((limbIndex == OBJECT_DEKUNUTS_LIMB_03) && (this->unk_1F0 == 1)) {
        rot->z += this->unk_1F2;
    }

    return false;
}

void EnSyatekiDekunuts_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnSyatekiDekunuts* this = THIS;
    Vec3f temp_f20;
    s32 i;

    if (this->actionFunc != func_80A2BF18) {
        SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                          EnSyatekiDekunuts_OverrideLimbDraw, NULL, &this->actor);
    }

    if (this->unk_1EC == 1) {
        for (i = 0; i < this->unk_1EA; i++) {
            temp_f20.x = this->unk_1E4[i].x;
            temp_f20.y = this->unk_1E4[i].y;
            temp_f20.z = this->unk_1E4[i].z;

            OPEN_DISPS(globalCtx->state.gfxCtx);

            func_8012C28C(globalCtx->state.gfxCtx);
            Matrix_InsertTranslation(temp_f20.x, temp_f20.y, temp_f20.z, MTXMODE_NEW);
            Matrix_Scale(0.02f, 0.02f, 0.02f, MTXMODE_APPLY);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, &object_dekunuts_DL_001E50);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}
