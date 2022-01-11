/*
 * File: z_en_famos.c
 * Overlay: ovl_En_Famos
 * Description: Death Armos
 */

#include "z_en_famos.h"
#include "objects/object_famos/object_famos.h"

#define FLAGS 0x00000005

#define THIS ((EnFamos*)thisx)

void EnFamos_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFamos_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFamos_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFamos_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808ACB58(EnFamos *this);
void func_808ACD2C(EnFamos *this);
void func_808AD05C(EnFamos* this);
void func_808AD170(EnFamos* this);
void func_808AD1F0(EnFamos* this);
void func_808AD31C(EnFamos* this);
void func_808AD3E8(EnFamos* this);
void func_808AD54C(EnFamos* this);
void func_808AD66C(EnFamos* this);
void func_808AD7EC(EnFamos* this);
void func_808AD888(EnFamos* this);
void func_808ADA74(EnFamos* this);
void func_808ADB4C(EnFamos* this);
void func_808ADC40(EnFamos* this);
void func_808ADD20(EnFamos* this);
void func_808ADE00(EnFamos* this);
void func_808ADFA4(EnFamos* this);

// action funcs
void func_808ADFF0(EnFamos* this, GlobalContext* globalCtx);
void func_808AD18C(EnFamos* this, GlobalContext* globalCtx);
void func_808AD294(EnFamos* this, GlobalContext* globalCtx);
void func_808AD378(EnFamos* this, GlobalContext* globalCtx);
void func_808AD42C(EnFamos* this, GlobalContext* globalCtx);
void func_808AD5B0(EnFamos* this, GlobalContext* globalCtx);
void func_808AD68C(EnFamos* this, GlobalContext* globalCtx);
void func_808AD840(EnFamos* this, GlobalContext* globalCtx);
void func_808AD8B8(EnFamos* this, GlobalContext* globalCtx);
void func_808ADAE8(EnFamos* this, GlobalContext* globalCtx);
void func_808ADB70(EnFamos* this, GlobalContext* globalCtx);
void func_808ADC64(EnFamos* this, GlobalContext* globalCtx);
void func_808ADDA8(EnFamos* this, GlobalContext* globalCtx);
void func_808ADE74(EnFamos* this, GlobalContext* globalCtx);
void func_808ADFF0(EnFamos* this, GlobalContext* globalCtx);

s32 func_808ACF1C(EnFamos* this, GlobalContext* globalCtx);

void func_808AE304(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor);
void func_808AE3A8(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor);
// draw func extension
void func_808AE3FC(EnFamos* this, GlobalContext* globalCtx);


const ActorInit En_Famos_InitVars = {
    ACTOR_EN_FAMOS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_FAMOS,
    sizeof(EnFamos),
    (ActorFunc)EnFamos_Init,
    (ActorFunc)EnFamos_Destroy,
    (ActorFunc)EnFamos_Update,
    (ActorFunc)EnFamos_Draw,
};

static ColliderCylinderInit sCylinderInit1 = {
    { COLTYPE_METAL, AT_NONE | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0x20000000, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 80, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit sCylinderInit2 = {
    { COLTYPE_NONE, AT_NONE | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
    { 70, 10, 0, { 0, 0, 0 } },
};

static ColliderJntSphElementInit sJntSphElementsInit[2] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00002000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 2, { { 2500, 0, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00002000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 2, { { -1500, 0, 0 }, 20 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    2, sJntSphElementsInit,
};

static AnimatedMaterial* D_808AE6B0[] = {gFamosAnimTex1, gFamosAnimTex2};


static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, 15, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 3500, ICHAIN_STOP),
};

static s32 animatedMaterialsVirtualized = false;

void EnFamos_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnFamos *this = THIS;
    Path *path;
    s32 newValue = 1;
    int i;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    if (this->actor.params != 0xFF) {
        path = &globalCtx->setupPathList[this->actor.params];
        this->pathPoints = Lib_SegmentedToVirtual(path->points);
        this->unk1D6 = path->count;
        if (this->unk1D6 == 1) {
            this->pathPoints = NULL;
            this->unk1D6 = 0;
        }
    }
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawSquare, 30.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &gFamosSkeleton, &gFamosLowerSNSAnim, 
          this->limbDrawTbl, this->transitionDrawTbl, 6);
    Collider_InitAndSetCylinder(globalCtx, &this->collider1, &this->actor, &sCylinderInit1);
    Collider_InitAndSetCylinder(globalCtx, &this->collider2, &this->actor, &sCylinderInit2);
    Collider_InitAndSetJntSph(globalCtx, &this->collider3, &this->actor, &sJntSphInit, &this->collider3Elements);

    if( ! animatedMaterialsVirtualized ){
        for (i = 0; i < ARRAY_COUNT(D_808AE6B0); i++) {
            D_808AE6B0[i] = Lib_SegmentedToVirtual(D_808AE6B0[i]);
        }
        animatedMaterialsVirtualized = true;
    }
    
    this->actor.colChkInfo.mass = 0xFA;
    this->unk1EC = this->actor.world.pos.y;
    this->unk1F0 = (this->actor.shape.rot.x <= 0) ? 200.0f : this->actor.shape.rot.x * 40.0f * 0.1f;
    this->actor.shape.rot.x = 0;
    this->actor.world.rot.x = 0;
    this->unk1D5 = newValue;
    this->unk1D8 = newValue;
    if (this->pathPoints != NULL) {
        func_808AD1F0(this);
    } else {
        func_808AD170(this);
    }
}

void EnFamos_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnFamos *this = THIS;
    Collider_DestroyCylinder(globalCtx, &this->collider1);
    Collider_DestroyCylinder(globalCtx, &this->collider2);
    Collider_DestroyJntSph(globalCtx, &this->collider3);
}


#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ACB58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ACD2C.s")

s32 func_808ACF1C(EnFamos *this, GlobalContext *globalCtx) {
    if ((Player_GetMask(globalCtx) != 0x10) && 
      (Actor_XZDistanceToPoint(&GET_PLAYER(globalCtx)->actor, &this->unk200) < this->unk1F0) && 
      (Actor_IsFacingPlayer(&this->actor, 0x5000) != 0)) {
      return true;
    }else{
      return false;
    }
    
}

void func_808ACF98(EnFamos *this) {
    if (this->unk1DA == 0) {
        this->unk1DA = 30;
    }

    this->unk1DA--;
    this->actor.world.pos.y = (Math_SinS((this->unk1DA * 2184)) * 10.0f) + this->unk1EC;

    if (ABS_ALT(this->unk1E6) >= 0x4001) {
        func_800B9010(&this->actor, NA_SE_EN_FAMOS_FLOAT_REVERSE - SFX_FLAG);
    } else { 
        func_800B9010(&this->actor, NA_SE_EN_FAMOS_FLOAT - SFX_FLAG);
    }
}

// todo sfx
void func_808AD05C(EnFamos *this) {
    u8 scalled1E6;

    if ((this->collider3.base.acFlags & AC_HIT)) {
        this->collider3.base.acFlags &= ~AC_HIT;
        if (this->unk1D5 == 1) {
            if (this->animatedMaterialIndex != 0) {
                this->animatedMaterialIndex = 0;
                Actor_PlaySfxAtPos(&this->actor, 0x3A92U);
            } else {
                this->animatedMaterialIndex = 1;
                this->unk1E0 = 0x64;
                Actor_PlaySfxAtPos(&this->actor, 0x3A91U);
                Actor_PlaySfxAtPos(&this->actor, 0x3847U);
            }
            this->unk1D5 = 0;
        }
    } else {
        // not DECR, good grief
        if (this->unk1E0 > 0) {
            this->unk1E0--;
            if (this->unk1E0 == 0) {
                if (this->animatedMaterialIndex != 0) {
                    Actor_PlaySfxAtPos(&this->actor, 0x3A92U);
                }
                this->animatedMaterialIndex = 0;
                this->unk1D5 = 0;
            }
        }
    }
    if (this->unk1D5 == 0) {
        if (this->animatedMaterialIndex != 0) {
            scalled1E6 = Math_ScaledStepToS(&this->unk1E6, -0x8000, 0x1000);
        } else {
            scalled1E6 = Math_ScaledStepToS(&this->unk1E6, 0, 0x1000);
        }
        this->unk1D5 = scalled1E6;
    }
}

void func_808AD170(EnFamos *this) {
    this->actionFunc = func_808AD18C;
    this->actor.speedXZ = 0.0f;
}

void func_808AD18C(EnFamos *this, GlobalContext *globalCtx) {
    func_808ACF98(this);
    if (this->unk1D8 != 0) {
        Math_Vec3f_Copy(&this->unk200, &this->actor.world.pos);
    }
    if (func_808ACF1C(this, globalCtx)) {
        func_808AD54C(this);
    }
}

void func_808AD1F0(EnFamos *this) {
    if (this->unk1D8 != 0) {
        if ( ++this->unk1D7 == this->unk1D6) {
            this->unk1D7 = 0;
        }
    } else {
        this->unk1D8 = 1;
    }
    Math_Vec3s_ToVec3f(&this->unk1F4, &this->pathPoints[this->unk1D7]);
    this->unk1E4 = Actor_YawToPoint(&this->actor, &this->unk1F4);
    this->actionFunc = func_808AD294;
    this->actor.speedXZ = 0.0f;
}

void func_808AD294(EnFamos *this, GlobalContext *globalCtx) {
    func_808ACF98(this);
    if (this->unk1D8 != 0) {
        Math_Vec3f_Copy(&this->unk200, &this->actor.world.pos);
    }
    if (func_808ACF1C(this, globalCtx)) {
        func_808AD54C(this);
        return;
    }
    if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->unk1E4, 0x200) != 0) {
        func_808AD3E8(this);
    }
}

void func_808AD31C(EnFamos *this) {
    this->unk1E4 = Actor_YawToPoint(&this->actor, &this->unk200);
    Math_Vec3f_Copy(&this->unk1F4, &this->unk200);
    this->actionFunc = func_808AD378;
    this->actor.speedXZ = 0.0f;
}

void func_808AD378(EnFamos *this, GlobalContext *globalCtx) {
    func_808ACF98(this);
    if (func_808ACF1C(this, globalCtx)) {
        func_808AD54C(this);
    } else if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->unk1E4, 0x200) != 0) {
        func_808AD3E8(this);
    }
}

void func_808AD3E8(EnFamos *this) {
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actor.world.rot.x = -Actor_PitchToPoint(&this->actor, &this->unk1F4);
    this->actionFunc = func_808AD42C;
}

void func_808AD42C(EnFamos *this, GlobalContext *globalCtx) {
    f32 sp24 = Actor_XZDistanceToPoint((Actor *) this, &this->unk1F4);

    this->actor.shape.rot.y = Actor_YawToPoint((Actor *) this, &this->unk1F4);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    func_808ACF98(this);
    if (this->unk1D8 != 0) {
        Math_Vec3f_Copy(&this->unk200, &this->actor.world.pos);
    }
    if (func_808ACF1C(this, globalCtx)) {
        func_808AD54C(this);
    } else if (sp24 < 20.0f) {
        if (this->pathPoints != 0) {
            func_808AD1F0(this);
        } else {
            func_808AD170(this);
        }
    } else if (sp24 < 40.0f) {
        Math_StepToF(&this->actor.speedXZ, 0.5f, 0.3f);
    } else {
        Math_StepToF(&this->actor.speedXZ, 3.0f, 0.3f);
    }
}

void func_808AD54C(EnFamos *this) {
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->unk1DC = 8;
    this->actor.speedXZ = 0.0f;
    if (this->unk1D8 == 1) {
        this->unk1D8 = 0;
        Math_Vec3f_Copy(&this->unk200, &this->actor.world.pos);
    }
    this->actionFunc = func_808AD5B0;
}

void func_808AD5B0(EnFamos *this, GlobalContext *globalCtx) {
    s32 v0;
    s32 temp1DC;

    v0 = this->unk1E6 < 0 ? -this->unk1E6 : this->unk1E6;
    if (v0 >= 0x4001) {
        func_800B9010((Actor *) this, 0x3294);
    } else {
        func_800B9010((Actor *) this, 0x3293);
    }

    this->unk1DC--;
    if (this->unk1DC == 0) {
        this->actor.world.pos.y = this->unk1EC;
        func_808AD66C(this);
    } else {
        this->actor.world.pos.y = (Math_SinS( (this->unk1DC) * 0x1000) * 30.0f) + this->unk1EC;
    }
}

void func_808AD66C(EnFamos *this) {
    this->unk1DA = 0;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_808AD68C;
}

void func_808AD68C(EnFamos *this, GlobalContext *globalCtx) {
    Player *player;
    Vec3f abovePlayerPos;
    u32 floorValue; // name is a guess

    player = GET_PLAYER(globalCtx);
    func_808ACF98(this);
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x800);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    abovePlayerPos.x = player->actor.world.pos.x;
    abovePlayerPos.y = player->actor.world.pos.y + 100.0f;
    abovePlayerPos.z = player->actor.world.pos.z;
    this->actor.world.rot.x = -Actor_PitchToPoint((Actor *) this, &abovePlayerPos);
    Math_StepToF(&this->actor.speedXZ, 6.0f, 0.5f);

    floorValue = func_800C9B18(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId);
    if (this->actor.xzDistToPlayer < 30.0f && this->actor.floorHeight > -32000.0f 
      && floorValue != 0xC && floorValue != 0xD) {
        func_808AD7EC(this);

    } else if ((Player_GetMask(globalCtx) == 0x10) 
      || this->unk1F0 < Actor_XZDistanceToPoint(&GET_PLAYER(globalCtx)->actor, &this->unk200)
      || Actor_IsFacingPlayer(&this->actor, 0x6000) == 0) {
        func_808ADC40(this);
    }
}

void func_808AD7EC(EnFamos *this) {
    Animation_PlayOnce(&this->skelAnime, &gFamosShakeAnim);
    this->actor.speedXZ = 0.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_AMOS_VOICE);
    this->actionFunc = func_808AD840;
}


void func_808AD840(EnFamos *this, GlobalContext *globalCtx) {
    func_800B9010((Actor *) this, NA_SE_EN_LAST1_FALL_OLD - SFX_FLAG);
    if (SkelAnime_Update(&this->skelAnime)) {
        func_808AD888(this);
    }
}

void func_808AD888(EnFamos *this) {
    this->actor.world.rot.x = -0x4000;
    this->collider1.base.atFlags |= 1;
    this->unk1DC = 4;
    this->actionFunc = func_808AD8B8;
}

void func_808AD8B8(EnFamos *this, GlobalContext *globalCtx) {
    s32 bgflags; // temp name, should be more psecific
    u32 floorValue; // name is a guess

    Math_StepToF(&this->actor.speedXZ, 20.0f, 2.0f);
    this->unk1DC--;
    if (this->unk1DC == 0) {
        this->collider3.base.acFlags = this->collider3.base.acFlags & 0xFFFE;
    }
    floorValue = func_800C9B18(&globalCtx->colCtx, (CollisionPoly *) this->actor.floorPoly, (s32) this->actor.floorBgId);
    bgflags = this->actor.bgCheckFlags & 1;
    if (( bgflags != 0) 
      || (this->actor.floorHeight == -32000.0f)
      || (floorValue == 0xC)
      || (floorValue == 0xD)) {
        this->collider1.base.atFlags = this->collider1.base.atFlags & 0xFFFE;
        this->collider2.base.atFlags |= 1;
        if ( bgflags != 0) {
            func_800DFD04(globalCtx->cameraPtrs[globalCtx->activeCamera], 2, 0xF, 0xA);
            func_8013ECE0(this->actor.xyzDistToPlayerSq, 0xB4, 0x14, 0x64);
            func_808ACB58(this);
            Actor_SpawnAsChild(&globalCtx->actorCtx, (Actor *) this, globalCtx, 
                (u16)1, this->actor.world.pos.x, this->actor.floorHeight, this->actor.world.pos.z, 0, 0, 0, 0);

            if (this->actor.child != NULL) {
                Actor_SetScale(this->actor.child, 0.015f);
            }

            if (this->animatedMaterialIndex != 0) {
                this->unk1E2 = 0x46;
                func_808ADD20(this);
                return;
            } else {
                this->unk1E2 = 0x14;
                func_808ADA74(this);
                return;
            }
        }
        else {
            this->collider3.base.acFlags = this->collider3.base.acFlags | 1;
            func_808ADB4C(this);
            return;

        }
    }

    func_800B9010((Actor *) this, NA_SE_EN_LAST1_FALL_OLD - SFX_FLAG);
}


#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADA74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADAE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADB4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADB70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADC40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADC64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADD20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADDA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADE00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADE74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADFA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADFF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AE030.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/EnFamos_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AE304.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AE3A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AE3FC.s")

void EnFamos_Draw(Actor *thisx, GlobalContext *globalCtx) {
    EnFamos *this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    if (this->actionFunc != func_808ADFF0) {
        AnimatedMat_Draw(globalCtx, D_808AE6B0[this->animatedMaterialIndex]);
        SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, 
            this->skelAnime.jointTable, 
            func_808AE304, func_808AE3A8, &this->actor);
        if (this->actor.colorFilterTimer != 0) {
            func_800AE5A0(globalCtx);
        }
    }
    func_808AE3FC(this, globalCtx);
}
