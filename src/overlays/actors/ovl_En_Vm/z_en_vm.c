/*
 * File: z_en_vm.c
 * Overlay: ovl_En_Vm
 * Description: Beamos
 */

#include "z_en_vm.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_vm/object_vm.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_400)

#define THIS ((EnVm*)thisx)

void EnVm_Init(Actor* thisx, GlobalContext* globalCtx);
void EnVm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnVm_Update(Actor* thisx, GlobalContext* globalCtx);
void EnVm_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808CC420(EnVm* this);
void func_808CC490(EnVm* this, GlobalContext* globalCtx);
void func_808CC5C4(EnVm* this);
void func_808CC610(EnVm* this, GlobalContext* globalCtx);
void func_808CC788(EnVm* this);
void func_808CC820(EnVm* this, GlobalContext* globalCtx);
void func_808CCAA4(EnVm* this, GlobalContext* globalCtx);
void func_808CCB08(EnVm* this);
void func_808CCB50(EnVm* this, GlobalContext* globalCtx);
void func_808CCCF0(EnVm* this, GlobalContext* globalCtx);

const ActorInit En_Vm_InitVars = {
    ACTOR_EN_VM,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_VM,
    sizeof(EnVm),
    (ActorFunc)EnVm_Init,
    (ActorFunc)EnVm_Destroy,
    (ActorFunc)EnVm_Update,
    (ActorFunc)EnVm_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 2, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 10, { { 0, 2300, 0 }, 33 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_METAL,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    2,
    sJntSphElementsInit,
};

static ColliderTrisElementInit sTrisElementsInit[] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x10 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
    },
};

static ColliderTrisInit sTrisInit = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_TRIS,
    },
    1,
    sTrisElementsInit,
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0xF),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0xF),
    /* Normal arrow   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(0, 0xF),
    /* Sword          */ DMG_ENTRY(0, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(0, 0xF),
    /* Ice arrow      */ DMG_ENTRY(0, 0xF),
    /* Light arrow    */ DMG_ENTRY(0, 0xF),
    /* Goron spikes   */ DMG_ENTRY(0, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0xF),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0xF),
    /* Zora barrier   */ DMG_ENTRY(0, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0xF),
    /* Light ray      */ DMG_ENTRY(0, 0xF),
    /* Thrown object  */ DMG_ENTRY(0, 0xF),
    /* Zora punch     */ DMG_ENTRY(0, 0xF),
    /* Spin attack    */ DMG_ENTRY(0, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0xF),
    /* Normal Roll    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0xF),
    /* Unblockable    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0xF),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

static CollisionCheckInfoInit sColChkInfoInit = { 2, 25, 100, MASS_IMMOVABLE };

TexturePtr D_808CD58C[] = {
    gameplay_keep_Tex_03F300, gameplay_keep_Tex_03FB00, gameplay_keep_Tex_040300, gameplay_keep_Tex_040B00,
    gameplay_keep_Tex_041300, gameplay_keep_Tex_041B00, gameplay_keep_Tex_042300, gameplay_keep_Tex_042B00,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 14, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 1000, ICHAIN_CONTINUE),
    ICHAIN_S8(hintId, 57, ICHAIN_STOP),
};

s32 D_808CD5B8 = false;

Color_RGBA8 D_808CD5BC = { 0, 0, 255, 0 };

Color_RGBA8 D_808CD5C0 = { 255, 255, 255, 255 };

void EnVm_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnVm* this = THIS;
    s32 i;
    s32 params;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 35.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_vm_Skel_003F60, &object_vm_Anim_000068, this->jointTable,
                   this->morphTable, 11);
    Collider_InitAndSetTris(globalCtx, &this->colliderTris, &this->actor, &sTrisInit, this->colliderTrisElements);
    Collider_InitAndSetJntSph(globalCtx, &this->colliderJntSph, &this->actor, &sJntSphInit,
                              this->colliderJntSphElements);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

    params = ENVM_GET_FF00(thisx);
    if ((params == ENVM_FF00_FF) || (params == ENVM_FF00_0)) {
        params = ENVM_FF00_5;
    }

    this->unk_21C = params * 40.0f;
    thisx->params &= 0xFF;
    this->actor.bgCheckFlags |= 0x400;

    if (!D_808CD5B8) {
        for (i = 0; i < ARRAY_COUNT(D_808CD58C); i++) {
            D_808CD58C[i] = Lib_SegmentedToVirtual(D_808CD58C[i]);
        }
        D_808CD5B8 = true;
    }
    func_808CC420(this);
}

void EnVm_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnVm* this = THIS;

    Collider_DestroyTris(globalCtx, &this->colliderTris);
    Collider_DestroyJntSph(globalCtx, &this->colliderJntSph);
}

void func_808CC420(EnVm* this) {
    f32 lastFrame = Animation_GetLastFrame(&object_vm_Anim_000068);

    Animation_Change(&this->skelAnime, &object_vm_Anim_000068, 1.0f, lastFrame, lastFrame, ANIMMODE_ONCE, 0.0f);
    this->actionFunc = func_808CC490;
}

void func_808CC490(EnVm* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 sp22;
    s16 temp_v0;

    Math_ApproachS(&this->unk_216, 0, 0xA, 0x5DC);
    this->unk_218 -= 0x1F4;
    func_800B9010(&this->actor, NA_SE_EN_BIMOS_ROLL_HEAD - SFX_FLAG);

    if (this->actor.xzDistToPlayer <= this->unk_21C) {
        if ((this->actor.playerHeightRel <= 80.0f) && (this->actor.playerHeightRel >= -160.0f)) {
            sp22 = BINANG_SUB(this->actor.yawTowardsPlayer - this->unk_218, this->actor.shape.rot.y);

            temp_v0 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.world.pos);
            if (temp_v0 > 0x1B91) {
                temp_v0 = 0x1B91;
            }

            if ((ABS_ALT(sp22) <= 0x2710) && (temp_v0 >= 0xE38) && (Player_GetMask(globalCtx) != PLAYER_MASK_STONE)) {
                func_808CC5C4(this);
            }
        }
    }
}

void func_808CC5C4(EnVm* this) {
    Animation_PlayLoopSetSpeed(&this->skelAnime, &object_vm_Anim_000068, 2.0f);
    this->unk_214 = 10;
    this->actionFunc = func_808CC610;
}

void func_808CC610(EnVm* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 sp3A;
    s16 sp38;

    SkelAnime_Update(&this->skelAnime);

    sp38 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.world.pos);
    sp38 = CLAMP_MAX(sp38, 0x1B91);

    sp3A = BINANG_ADD((s32)((this->unk_21C - this->actor.xzDistToPlayer) * 60.0f), 4000);
    sp3A = CLAMP_MAX(sp3A, 0x1000);

    Math_SmoothStepToS(&this->unk_216, sp38, 10, 4000, 0);

    if ((sp38 < 0xAAA) || (sp3A <= 0)) {
        func_808CC420(this);
    } else if (Math_ScaledStepToS(&this->unk_218, BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y),
                                  sp3A)) {
        this->unk_214--;
        if (this->unk_214 == 0) {
            EffectSsDeadDd_Spawn(globalCtx, &this->unk_228, &gZeroVec3f, &gZeroVec3f, &D_808CD5BC, &D_808CD5C0, 150,
                                 -25, 16, 20);
            func_808CC788(this);
        }
    }
}

void func_808CC788(EnVm* this) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BIMOS_AIM);
    Animation_Change(&this->skelAnime, &object_vm_Anim_000068, 3.0f, 3.0f, 7.0f, ANIMMODE_ONCE, 0.0f);
    this->unk_214 = 305;
    this->unk_220 = 0.06f;
    this->colliderTris.base.atFlags &= ~AT_HIT;
    this->actionFunc = func_808CC820;
}

void func_808CC820(EnVm* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 sp32;
    f32 temp_f2;

    if (SkelAnime_Update(&this->skelAnime)) {
        this->skelAnime.curFrame = this->skelAnime.startFrame;
    }

    sp32 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.world.pos);
    sp32 = CLAMP_MAX(sp32, 0x1B91);

    if (this->colliderTris.base.atFlags & AT_HIT) {
        this->colliderTris.base.atFlags &= ~AT_HIT;
        this->unk_214 = 0;
        if (this->unk_220 > 0.01f) {
            this->unk_220 = 0.01f;
        }
    }

    if ((this->unk_216 < 0xAAA) || (Player_GetMask(globalCtx) == PLAYER_MASK_STONE) || (this->unk_214 == 0)) {
        this->unk_214 = 0;
        if (Math_StepToF(&this->unk_220, 0.0f, 0.003f)) {
            this->unk_210 = 0;
            this->unk_224 = 0.0f;
            func_808CC420(this);
        }
    } else {
        this->unk_214--;
        if (this->unk_214 <= 300) {
            Math_ApproachS(&this->unk_218, this->actor.yawTowardsPlayer - this->actor.shape.rot.y, 0xA, 0xDAC);
            Math_ApproachS(&this->unk_216, sp32, 0xA, 0xDAC);

            temp_f2 = Math_Vec3f_DistXYZ(&this->actor.focus.pos, &player->actor.world.pos) + 40.0f;
            if (this->unk_224 < temp_f2) {
                Math_StepToF(&this->unk_224, temp_f2, 40.0f);
            }

            Math_StepToF(&this->unk_220, 0.01f, 0.012f);
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->colliderTris.base);

            if (this->unk_210 == 0) {
                this->unk_210 = 1;
            }
        }
    }
}

void func_808CCA10(EnVm* this) {
    Animation_Change(&this->skelAnime, &object_vm_Anim_000068, -1.0f, Animation_GetLastFrame(&object_vm_Anim_000068),
                     0.0f, ANIMMODE_ONCE, 0.0f);
    this->unk_214 = 100;
    this->unk_210 = 0;
    this->unk_224 = 0.0f;
    this->unk_220 = 0.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
    this->actionFunc = func_808CCAA4;
}

void func_808CCAA4(EnVm* this, GlobalContext* globalCtx) {
    Math_ApproachS(&this->unk_216, 0, 0xA, 0x5DC);
    SkelAnime_Update(&this->skelAnime);
    if (this->unk_214 == 0) {
        func_808CCB08(this);
    } else {
        this->unk_214--;
    }
}

void func_808CCB08(EnVm* this) {
    Animation_PlayOnce(&this->skelAnime, &object_vm_Anim_000068);
    this->unk_214 = -1;
    this->actionFunc = func_808CCB50;
}

void func_808CCB50(EnVm* this, GlobalContext* globalCtx) {
    Math_ApproachS(&this->unk_216, 0, 0xA, 0x5DC);

    if (this->unk_214 > 0) {
        this->unk_214--;
    } else if (SkelAnime_Update(&this->skelAnime)) {
        if (this->unk_214 == -1) {
            this->unk_214 = 10;
            this->skelAnime.curFrame = 0.0f;
            this->skelAnime.playSpeed = 2.0f;
        } else {
            func_808CC420(this);
        }
    }
}

void func_808CCBE4(EnVm* this, GlobalContext* globalCtx) {
    Animation_Change(&this->skelAnime, &object_vm_Anim_000068, -1.0f, Animation_GetLastFrame(&object_vm_Anim_000068),
                     0.0f, ANIMMODE_ONCE, 0.0f);
    Enemy_StartFinishingBlow(globalCtx, &this->actor);
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 33);
    this->unk_214 = 33;
    this->unk_220 = 0.0f;
    this->unk_224 = 0.0f;
    this->actor.shape.yOffset = (this->actor.world.pos.y - this->actor.focus.pos.y) * 71.428566f;
    this->actor.world.pos.y = this->actor.focus.pos.y;
    this->actor.velocity.y = 8.0f;
    this->actor.gravity = -0.5f;
    this->actor.speedXZ = Rand_ZeroOne() + 1.0f;
    this->unk_210 = 0;
    this->actor.flags |= ACTOR_FLAG_10;
    this->actionFunc = func_808CCCF0;
}

void func_808CCCF0(EnVm* this, GlobalContext* globalCtx) {
    this->unk_216 += 0x5DC;
    this->unk_218 += 0x9C4;
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 20.0f, 40.0f, 7);

    this->unk_214--;
    if (this->unk_214 == 1) {
        EnBom* bomb = (EnBom*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOM, this->actor.world.pos.x,
                                          this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0x6FF, 0);

        if (bomb != NULL) {
            bomb->timer = 0;
        }
    } else if (this->unk_214 == 0) {
        Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0xB0);
        Actor_MarkForDeath(&this->actor);
    }
}

void func_808CCDE4(EnVm* this, GlobalContext* globalCtx) {
    s32 i;
    s16 temp_v0;

    if (this->colliderJntSph.base.acFlags & AC_HIT) {
        this->colliderJntSph.base.acFlags &= ~AC_HIT;

        for (i = 0; i < ARRAY_COUNT(this->colliderJntSphElements); i++) {
            if (this->colliderJntSph.elements[i].info.bumperFlags & BUMP_HIT) {
                break;
            }
        }

        if (i != ARRAY_COUNT(this->colliderJntSphElements)) {
            func_800BE5CC(&this->actor, &this->colliderJntSph, i);
            if (this->actor.colChkInfo.damageEffect == 0) {
                func_808CCBE4(this, globalCtx);
            } else if ((i == 0) && (this->actionFunc != func_808CCAA4)) {
                temp_v0 = (this->actor.world.rot.y - this->actor.shape.rot.y) - this->unk_218;
                if (ABS_ALT(temp_v0) > 0x6000) {
                    func_808CCA10(this);
                }
            }
        }
    }
}

void EnVm_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnVm* this = THIS;

    func_808CCDE4(this, globalCtx);

    if (this->unk_210 == 2) {
        func_800B31BC(globalCtx, &this->unk_234, 20, -1, 155, 10);
        if ((globalCtx->gameplayFrames % 2) != 0) {
            func_800BBFB0(globalCtx, &this->unk_234, 6.0f, 1, 120, 20, 1);
        }
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BIMOS_LAZER_GND - SFX_FLAG);
    }

    if (this->unk_224 > 0.0f) {
        func_800B9010(&this->actor, NA_SE_EN_BIMOS_LAZER - SFX_FLAG);
    }

    this->actionFunc(this, globalCtx);

    this->unk_212 += 12;

    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderJntSph.base);
    if (this->actionFunc != func_808CCCF0) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderJntSph.base);
    }
}

s32 EnVm_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnVm* this = THIS;

    if (limbIndex == OBJECT_VM_LIMB_02) {
        rot->x += this->unk_216;
        rot->y += this->unk_218;
    } else if ((limbIndex == OBJECT_VM_LIMB_0A) && (this->actionFunc == func_808CCCF0)) {
        *dList = NULL;
    }
    return false;
}

void EnVm_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    s32 pad;
    EnVm* this = THIS;
    Vec3f sp5C;
    Vec3f sp50;
    CollisionPoly* sp4C;
    s32 sp48;

    Collider_UpdateSpheres(limbIndex, &this->colliderJntSph);

    if (limbIndex == OBJECT_VM_LIMB_02) {
        sp4C = NULL;

        Matrix_GetStateTranslation(&this->actor.focus.pos);
        Matrix_GetStateTranslationAndScaledZ(1600.0f, &this->unk_228);
        Matrix_GetStateTranslationAndScaledZ(this->unk_224 * 71.428566f, &this->unk_234);

        if (BgCheck_EntityLineTest1(&globalCtx->colCtx, &this->actor.focus.pos, &this->unk_234, &sp5C, &sp4C, true,
                                    true, false, true, &sp48)) {
            this->unk_224 = Math_Vec3f_DistXYZ(&this->actor.focus.pos, &sp5C) - 5.0f;
            this->unk_210 = 2;
            Math_Vec3f_Copy(&this->unk_234, &sp5C);
        } else if (this->unk_210 != 0) {
            this->unk_210 = 1;
        }

        sp50.x = this->unk_234.x + (Math_CosS(this->actor.shape.rot.y + this->unk_218) * 5.0f);
        sp50.y = this->unk_234.y;
        sp50.z = this->unk_234.z - (Math_SinS(this->actor.shape.rot.y + this->unk_218) * 5.0f);

        Collider_SetTrisVertices(&this->colliderTris, 0, &this->actor.focus.pos, &this->unk_234, &sp50);
    }
}

void EnVm_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnVm* this = THIS;
    Gfx* gfx;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gfx = POLY_OPA_DISP;

    gSPDisplayList(&gfx[0], &sSetupDL[6 * 25]);

    POLY_OPA_DISP = &gfx[1];

    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, EnVm_OverrideLimbDraw,
                      EnVm_PostLimbDraw, &this->actor);

    if (this->unk_210 == 2) {
        gfx = POLY_XLU_DISP;

        gSPDisplayList(&gfx[0], &sSetupDL[6 * 60]);
        gDPSetColorDither(&gfx[1], G_CD_DISABLE);

        Matrix_InsertTranslation(this->unk_234.x, this->unk_234.y + 10.0f, this->unk_234.z, MTXMODE_NEW);
        Matrix_Scale(0.8f, 0.8f, 0.8f, MTXMODE_APPLY);

        gSPMatrix(&gfx[2], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(&gfx[3], 0, 0, 255, 255, 255, 168);
        gDPSetEnvColor(&gfx[4], 0, 0, 255, 0);
        gSPSegment(&gfx[5], 0x08, D_808CD58C[globalCtx->gameplayFrames & 7]);
        gSPDisplayList(&gfx[6], gameplay_keep_DL_044300);

        POLY_XLU_DISP = &gfx[7];
    }

    if (this->unk_224 > 0.0f) {
        gfx = POLY_OPA_DISP;

        gSPSegment(&gfx[0], 0x08, func_8012CB28(globalCtx->state.gfxCtx, 0, this->unk_212));

        Matrix_InsertTranslation(this->actor.focus.pos.x, this->actor.focus.pos.y, this->actor.focus.pos.z,
                                 MTXMODE_NEW);
        Matrix_InsertRotation(this->unk_216, this->unk_218 + this->actor.shape.rot.y, 0, MTXMODE_APPLY);
        Matrix_Scale(this->unk_220, this->unk_220, this->unk_224 * 0.0015f, MTXMODE_APPLY);

        gSPMatrix(&gfx[1], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(&gfx[2], object_vm_DL_002728);

        POLY_OPA_DISP = &gfx[3];
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
