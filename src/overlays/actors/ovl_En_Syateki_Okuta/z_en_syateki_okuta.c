/*
 * File: z_en_syateki_okuta.c
 * Overlay: ovl_En_Syateki_Okuta
 * Description: Shooting Gallery Octorok
 */

#include "z_en_syateki_okuta.h"
#include "overlays/actors/ovl_En_Syateki_Man/z_en_syateki_man.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_8000000)

#define THIS ((EnSyatekiOkuta*)thisx)

void EnSyatekiOkuta_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiOkuta_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiOkuta_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiOkuta_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A362A8(EnSyatekiOkuta* this, GlobalContext* globalCtx);
void func_80A36350(EnSyatekiOkuta* this, GlobalContext* globalCtx);
void func_80A363B4(EnSyatekiOkuta* this, GlobalContext* globalCtx);
void func_80A36488(EnSyatekiOkuta* this, GlobalContext* globalCtx);
void func_80A36504(EnSyatekiOkuta* this, GlobalContext* globalCtx);
void func_80A365EC(EnSyatekiOkuta* this, GlobalContext* globalCtx);
void func_80A36260(EnSyatekiOkuta* this);
void func_80A362F8(EnSyatekiOkuta* this);
void func_80A36CB0(EnSyatekiOkuta* this);

#if 0
const ActorInit En_Syateki_Okuta_InitVars = {
    ACTOR_EN_SYATEKI_OKUTA,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_OKUTA,
    sizeof(EnSyatekiOkuta),
    (ActorFunc)EnSyatekiOkuta_Init,
    (ActorFunc)EnSyatekiOkuta_Destroy,
    (ActorFunc)EnSyatekiOkuta_Update,
    (ActorFunc)EnSyatekiOkuta_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A37570 = {
    { COLTYPE_HIT3, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 40, -30, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A37B88[] = {
    ICHAIN_S8(hintId, 66, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 6500, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80A37570;
extern InitChainEntry D_80A37B88[];

extern SkeletonHeader D_060033D0;
extern AnimationHeader D_0600466C;
extern AnimationInfo D_80A3759C;
extern Color_RGBA8 D_80A37B90;
extern Color_RGBA8 D_80A37B94;

void EnSyatekiOkuta_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnSyatekiOkuta* this = THIS;
    WaterBox* waterbox;
    f32 ySurface;
    s32 bgId;

    Actor_ProcessInitChain(&this->actor, D_80A37B88);
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_060033D0, &D_0600466C, this->jointTable, this->morphTable, 16);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_80A37570);

    this->actor.floorHeight = BgCheck_EntityRaycastFloor5(&globalCtx->colCtx, &this->actor.floorPoly, &bgId,
                                                          &this->actor, &this->actor.world.pos);

    if (!(WaterBox_GetSurface1_2(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z,
                                 &ySurface, &waterbox)) ||
        (ySurface <= this->actor.floorHeight)) {
        Actor_MarkForDeath(&this->actor);
    } else {
        this->actor.world.pos.y = this->actor.home.pos.y = ySurface;
    }

    this->unk_2A4 = 0;
    this->unk_2AA = 0;
    func_80A36260(this);
}

void EnSyatekiOkuta_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnSyatekiOkuta* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80A36148(Vec3f* pos, Vec3f* velocity, s16 scaleStep, GlobalContext* globalCtx) {
    func_800B0DE0(globalCtx, pos, velocity, &gZeroVec3f, &D_80A37B90, &D_80A37B94, 400, scaleStep);
}

void func_80A361B0(EnSyatekiOkuta* this, GlobalContext* globalCtx) {
    EffectSsGSplash_Spawn(globalCtx, &this->actor.home.pos, NULL, NULL, 0, 800);
}

s32 func_80A361F4(EnSyatekiOkuta* this) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v1;
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    temp_v1 = this->actor.params & 0xF;
    if ((temp_v1 == 1) || (temp_v1 == 4)) {
        temp_a0 = syatekiMan->unk_190;
        temp_a1 = (temp_v1 * 2) + 6;

        if ((temp_a0 >> temp_a1) & 3) {
            return 1;
        }

        if ((temp_a1 == 8) && ((temp_a0 >> 0xE) & 3)) {
            return 1;
        }
    }

    return 0;
}

void func_80A36260(EnSyatekiOkuta* this) {
    Animation_PlayOnceSetSpeed(&this->skelAnime, &D_0600466C, 0.0f);
    this->actor.draw = NULL;
    this->actionFunc = func_80A362A8;
}

void func_80A362A8(EnSyatekiOkuta* this, GlobalContext* globalCtx) {
    Actor* actorIt = globalCtx->actorCtx.actorLists[ACTORCAT_NPC].first;

    while (actorIt != NULL) {
        if (actorIt->id == ACTOR_EN_SYATEKI_MAN) {
            this->actor.parent = actorIt;
            func_80A362F8(this);
            break;
        } else {
            actorIt = actorIt->next;
        }
    }
}

void func_80A362F8(EnSyatekiOkuta* this) {
    Animation_PlayOnceSetSpeed(&this->skelAnime, &D_0600466C, 0.0f);
    this->actor.draw = NULL;
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80A36350;
}

void func_80A36350(EnSyatekiOkuta* this, GlobalContext* globalCtx) {
}

void func_80A36360(EnSyatekiOkuta* this) {
    this->actor.draw = EnSyatekiOkuta_Draw;
    this->unk_2AA = 0;
    Actor_ChangeAnimationByInfo(&this->skelAnime, &D_80A3759C, 4);
    this->actionFunc = func_80A363B4;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A363B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36444.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A364C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36504.s")

void func_80A3657C(EnSyatekiOkuta* this) {
    this->unk_2A4 = 0;
    this->unk_2AA = 0x12C;
    if (this->unk_2A6 == 1) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_OCTAROCK_DEAD1);
    }

    Actor_ChangeAnimationByInfo(&this->skelAnime, &D_80A3759C, 1);
    this->actionFunc = func_80A365EC;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A365EC.s")

void func_80A368E0(EnSyatekiOkuta* this, GlobalContext* globalCtx) {
    Actor* new_var = &this->actor;

    this->collider.dim.height =
        (D_80A37570.dim.height - this->collider.dim.yShift) * this->unk_1D8.y * this->actor.scale.y * 100.0f;
    this->collider.dim.radius = D_80A37570.dim.radius * this->actor.scale.x * 100.0f;

    if (this->actionFunc == func_80A363B4) {
        if ((this->unk_2A6 == 2) && func_80A361F4(this)) {
            return;
        }

        if (this->skelAnime.curFrame < (this->skelAnime.endFrame - 5.0f)) {
            this->collider.dim.height *= 1.35f;
        }
    }

    if (this->unk_2A6 == 1) {
        this->collider.dim.radius += 10;
        this->collider.dim.height += 15;
    }

    this->collider.dim.pos.x = this->actor.world.pos.x;
    // jointTable->y is the y-translation of the skeleton root
    this->collider.dim.pos.y = this->actor.world.pos.y + (this->skelAnime.jointTable->y * this->actor.scale.y);
    this->collider.dim.pos.z = this->actor.world.pos.z;
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

s32 func_80A36A90(EnSyatekiOkuta* this, GlobalContext* globalCtx) {
    if ((this->actionFunc == func_80A365EC) || (this->actionFunc == func_80A36350)) {
        return 0;
    }

    if ((this->collider.base.acFlags & AC_HIT) != 0) {
        this->collider.base.acFlags &= ~AC_HIT;
        return 1;
    }

    func_80A368E0(this, globalCtx);
    return 0;
}

void func_80A36AF8(EnSyatekiOkuta* this, GlobalContext* globalCtx) {
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;
    s16 temp_v1_2;

    if ((this->actionFunc != func_80A36488) && (this->actionFunc != func_80A363B4) && (syatekiMan->unk_26A == 1) &&
        (syatekiMan->unk_26C == 0)) {
        temp_v1_2 = (syatekiMan->unk_190 >> ((this->actor.params & 0xF) * 2)) & 3;
        if (temp_v1_2 > 0) {
            Actor_SetScale(&this->actor, 0.01f);
            this->unk_2A6 = temp_v1_2;
            func_80A36360(this);
        }
    }
}

void EnSyatekiOkuta_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnSyatekiOkuta* this = THIS;
    EnSyatekiMan* syatekiMan;

    this->actionFunc(this, globalCtx);

    if (this->actionFunc != func_80A36350) {
        SkelAnime_Update(&this->skelAnime);
    }

    func_80A36AF8(this, globalCtx);

    if (func_80A36A90(this, globalCtx) != 0) {
        syatekiMan = (EnSyatekiMan*)this->actor.parent;
        if (this->unk_2A6 == 1) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_SY_TRE_BOX_APPEAR);
            globalCtx->interfaceCtx.unk_25C++;
            syatekiMan->unk_280++;
            syatekiMan->unk_26E = 1;
        } else {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_SY_ERROR);
            syatekiMan->unk_26E = 2;
        }

        func_80A3657C(this);
    } else {
        this->collider.base.acFlags &= ~AC_HIT;
    }

    func_80A36CB0(this);
}

void func_80A36CB0(EnSyatekiOkuta* this) {
    f32 curFrame = this->skelAnime.curFrame;

    if (this->actionFunc == func_80A363B4) {
        if (curFrame < 8.0f) {
            this->unk_1D8.x = this->unk_1D8.y = this->unk_1D8.z = 1.0f;
        } else if (curFrame < 10.0f) {
            this->unk_1D8.x = this->unk_1D8.z = 1.0f;
            this->unk_1D8.y = ((curFrame - 7.0f) * 0.4f) + 1.0f;
        } else if (curFrame < 14.0f) {
            this->unk_1D8.x = this->unk_1D8.z = ((curFrame - 9.0f) * 0.075f) + 1.0f;
            this->unk_1D8.y = 1.8f - ((curFrame - 9.0f) * 0.25f);
        } else {
            this->unk_1D8.x = this->unk_1D8.z = 1.3f - ((curFrame - 13.0f) * 0.05f);
            this->unk_1D8.y = ((curFrame - 13.0f) * 0.0333f) + 0.8f;
        }
    } else if (this->actionFunc == func_80A36488) {
        this->unk_1D8.x = this->unk_1D8.z = 1.0f;
        this->unk_1D8.y = (sin_rad((M_PI / 16) * curFrame) * 0.2f) + 1.0f;
    } else if (this->actionFunc == func_80A36504) {
        if (curFrame < 3.0f) {
            this->unk_1D8.y = 1.0f;
        } else if (curFrame < 4.0f) {
            this->unk_1D8.y = (curFrame - 2.0f) + 1.0f;
        } else {
            this->unk_1D8.y = 2.0f - ((curFrame - 3.0f) * 0.333f);
        }
        this->unk_1D8.x = this->unk_1D8.z = 1.0f;
    } else if (this->actionFunc == func_80A365EC) {
        curFrame += this->unk_2A4;
        if (curFrame >= 35.0f) {
            this->unk_1D8.x = this->unk_1D8.y = this->unk_1D8.z = 1.0f;
        } else if (curFrame < 4.0f) {
            this->unk_1D8.x = this->unk_1D8.z = 1.0f - (curFrame * 0.0666f);
            this->unk_1D8.y = (curFrame * 0.1666f) + 1.0f;
        } else if (curFrame < 25.0f) {
            this->unk_1D8.x = this->unk_1D8.z = ((curFrame - 4.0f) * 0.01f) + 0.8f;
            this->unk_1D8.y = 1.5f - ((curFrame - 4.0f) * 0.025f);
        } else if (curFrame < 27.0f) {
            this->unk_1D8.x = this->unk_1D8.y = this->unk_1D8.z = ((curFrame - 24.0f) * 0.25f) + 1.0f;
        } else if (curFrame < 30.0f) {
            this->unk_1D8.x = this->unk_1D8.y = this->unk_1D8.z = 1.5f - ((curFrame - 26.0f) * 0.233f);
        } else {
            this->unk_1D8.x = this->unk_1D8.y = this->unk_1D8.z = ((curFrame - 29.0f) * 0.04f) + 0.8f;
        }
    } else {
        this->unk_1D8.x = this->unk_1D8.y = this->unk_1D8.z = 1.0f;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A370EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A37294.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/EnSyatekiOkuta_Draw.s")
