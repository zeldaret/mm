/*
 * File z_en_baguo.c
 * Overlay: ovl_En_Baguo
 * Description: Nejiron
 */

#include "z_en_baguo.h"

#define FLAGS 0x00000005

#define THIS ((EnBaguo*)thisx)

void EnBaguo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBaguo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBaguo_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A3B220(EnBaguo* this, GlobalContext* globalCtx);
void func_80A3B2CC(EnBaguo* this, GlobalContext* globalCtx);
void func_80A3B3E0(EnBaguo* this, GlobalContext* globalCtx);
void func_80A3B5E0(EnBaguo* this, GlobalContext* globalCtx);
void func_80A3B794(EnBaguo* this);
void func_80A3B7B8(EnBaguo* this, GlobalContext* globalCtx);
void func_80A3BE60(Actor* thisx, GlobalContext* globalCtx);
void func_80A3BE24(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);
void func_80A3C17C(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Baguo_InitVars = {
    ACTOR_EN_BAGUO,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_GMO,
    sizeof(EnBaguo),
    (ActorFunc)EnBaguo_Init,
    (ActorFunc)EnBaguo_Destroy,
    (ActorFunc)EnBaguo_Update,
    (ActorFunc)NULL,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80A3C2F0[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x04, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 1, { { 0, 0, 0 }, 0 }, 1 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A3C314 = {
    {
        COLTYPE_HARD,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    1,
    D_80A3C2F0, // sJntSphElementsInit,
};

// static DamageTable sDamageTable = {
static DamageTable D_80A3C324 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xE),
    /* Zora boomerang */ DMG_ENTRY(3, 0xE),
    /* Normal arrow   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(3, 0xE),
    /* Goron punch    */ DMG_ENTRY(2, 0xE),
    /* Sword          */ DMG_ENTRY(1, 0xE),
    /* Goron pound    */ DMG_ENTRY(1, 0xE),
    /* Fire arrow     */ DMG_ENTRY(0, 0xF),
    /* Ice arrow      */ DMG_ENTRY(0, 0xF),
    /* Light arrow    */ DMG_ENTRY(1, 0xE),
    /* Goron spikes   */ DMG_ENTRY(2, 0xE),
    /* Deku spin      */ DMG_ENTRY(0, 0xF),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0xF),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0xE),
    /* Spin attack    */ DMG_ENTRY(1, 0xE),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xE),
};

extern Gfx D_060014C8;
extern Gfx D_060018C8;
extern Gfx D_06001CC8;

s32 D_80A3C344[] = { 0x00000000, 0x00000000, 0x00000000 };

s32 D_80A3C350[] = { 0x00000000, 0x00000000, 0x00000000 };

static TexturePtr D_80A3C35C[] = { &D_060014C8, &D_060018C8, &D_06001CC8 };

extern SkeletonHeader D_060020E8;

void EnBaguo_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBaguo* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 0.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_060020E8, NULL, this->jointTable, this->morphTable, 3);
    this->actor.hintId = 0xB;
    this->unk_1BC = 240.0f;
    this->unk_1BC += this->actor.world.rot.z * 40.0f;
    this->actor.world.rot.z = 0;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.targetMode = 2;
    Collider_InitAndSetJntSph(globalCtx, &this->collider, &this->actor, &D_80A3C314, this->colliderElements);
    this->collider.elements[0].dim.modelSphere.radius = 30;
    this->collider.elements[0].dim.scale = 1.0f;
    this->collider.elements[0].dim.modelSphere.center.x = 80;
    this->collider.elements[0].dim.modelSphere.center.y = 80;
    this->collider.elements[0].dim.modelSphere.center.z = 0;
    this->actor.shape.yOffset = -3000.0f;
    this->actor.gravity = -3.0f;
    this->actor.colChkInfo.damageTable = &D_80A3C324;
    this->actor.flags |= 0x8000000;
    this->actor.flags &= ~1;
    this->collider.base.acFlags |= AC_HARD;
    this->actionFunc = func_80A3B220;
}

void EnBaguo_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBaguo* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void func_80A3B220(EnBaguo* this, GlobalContext* globalCtx) {
    this->unk_1B6 = 0;
    if (this->actor.xzDistToPlayer < 200.0f) {
        if (Player_GetMask(globalCtx) != 0x10) {
            this->actor.draw = func_80A3BE60;
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_BAKUO_APPEAR);
            this->actor.world.rot.z = 0;
            this->actor.world.rot.x = this->actor.world.rot.z;
            this->actor.flags &= ~0x8000000;
            this->actor.flags |= 1;
            this->actionFunc = func_80A3B2CC;
        }
    }
    this->actor.shape.rot.y = this->actor.world.rot.y;
}

void func_80A3B2CC(EnBaguo* this, GlobalContext* globalCtx) {
    this->actor.world.rot.y += 0x1518;
    this->actor.shape.rot.y = this->actor.world.rot.y;
    if (!(globalCtx->gameplayFrames & 7)) {
        func_800BBDAC(globalCtx, &this->actor, &this->actor.world.pos, this->actor.shape.shadowScale - 20.0f, 10, 8.0f,
                      500, 10, 1);
    }
    Math_ApproachF(&this->actor.shape.shadowScale, 50.0f, 0.3f, 5.0f);
    Math_ApproachF(&this->actor.shape.yOffset, 2700.0f, 100.0f, 500.0f);
    if (this->actor.shape.yOffset > 2650.0f) {
        this->unk_1B6 = 1;
        this->actor.shape.yOffset = 2700.0f;
        this->unk_1B4 = 0x3C;
        this->actionFunc = func_80A3B3E0;
    }
}

void func_80A3B3E0(EnBaguo* this, GlobalContext* globalCtx) {
    s16 phi_v1;
    s16 temp_v0;

    if (this->unk_1B4 != 0) {
        Math_SmoothStepToS(&this->actor.world.rot.x, 0, 10, 100, 1000);
        Math_SmoothStepToS(&this->actor.world.rot.z, 0, 10, 100, 1000);
        if (this->unk_1B4 & 8) {
            if (fabsf(this->actor.world.rot.y - this->actor.yawTowardsPlayer) > 200.0f) {
                Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 30, 300, 1000);
                if (!(globalCtx->gameplayFrames & 7)) {
                    func_800BBDAC(globalCtx, &this->actor, &this->actor.world.pos,
                                  this->actor.shape.shadowScale - 20.0f, 10, 8.0f, 500, 10, 1);
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_BAKUO_VOICE);
                }
            }
        }
        this->actor.shape.rot.y = this->actor.world.rot.y;
        return;
    }
    temp_v0 = this->actor.yawTowardsPlayer - this->actor.world.rot.y;
    if (temp_v0 < 0) {
        phi_v1 = -temp_v0;
    } else {
        phi_v1 = temp_v0;
    }
    Math_Vec3f_Copy(&this->unk_1D0, &D_801D15B0);
    Math_Vec3f_Copy(&this->unk_1C4, &D_801D15B0);
    if (phi_v1 < 0x2000) {
        this->unk_1D0.x = 2000.0f;
    } else {
        this->unk_1B8 = 0;
        this->unk_1D0.z = 2000.0f;
        if ((s16)(this->actor.yawTowardsPlayer - this->actor.world.rot.y) > 0) {
            this->unk_1B8 = 1;
        }
    }
    this->unk_1B4 = 0x26;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->unk_1C0 = 0;
    this->actionFunc = func_80A3B5E0;
}

void func_80A3B5E0(EnBaguo* this, GlobalContext* globalCtx) {
    f32 xDistanceFromHome = this->actor.home.pos.x - this->actor.world.pos.x;
    f32 zDistanceFromHome = this->actor.home.pos.z - this->actor.world.pos.z;

    if ((this->unk_1BC < sqrtf(SQ(xDistanceFromHome) + SQ(zDistanceFromHome))) || (Player_GetMask(globalCtx) == 0x10)) {
        func_80A3B794(this);
        return;
    }

    if (!this->unk_1B4) {
        this->unk_1B4 = 0x64;
        this->actor.world.rot.y = this->actor.shape.rot.y;
        this->actionFunc = func_80A3B3E0;
        this->actor.speedXZ = 0.0f;
        return;
    }

    if (!this->unk_1C0 && this->collider.base.atFlags & AC_HARD) {
        this->unk_1B8 ^= 1;
        this->unk_1C0 = 1;
        this->actor.speedXZ = -7.0f;
    }

    Math_ApproachF(&this->unk_1C4.x, this->unk_1D0.x, 0.2f, 1000.0f);
    Math_ApproachF(&this->unk_1C4.z, this->unk_1D0.z, 0.2f, 1000.0f);
    Math_ApproachF(&this->actor.speedXZ, 5.0f, 0.3f, 0.5f);
    this->actor.world.rot.x += (s16)this->unk_1C4.x;
    if (this->unk_1C4.z != 0.0f) {
        if (this->unk_1B8 == 0) {
            this->actor.world.rot.z += (s16)this->unk_1C4.z;
        } else {
            this->actor.world.rot.z -= (s16)this->unk_1C4.z;
        }
    }
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_BAKUO_ROLL - SFX_FLAG);
}

void func_80A3B794(EnBaguo* this) {
    this->unk_1B6 = 2;
    this->actionFunc = func_80A3B7B8;
    this->actor.speedXZ = 0.0f;
}

void func_80A3B7B8(EnBaguo* this, GlobalContext* globalCtx) {
    this->actor.world.rot.y += -0x1518;
    this->actor.shape.rot.y = this->actor.world.rot.y;
    if (!(globalCtx->gameplayFrames & 7)) {
        func_800BBDAC(globalCtx, &this->actor, &this->actor.world.pos, this->actor.shape.shadowScale - 20.0f, 10, 8.0f,
                      500, 10, 1);
    }
    Math_ApproachF(&this->actor.shape.yOffset, -3000.0f, 100.0f, 500.0f);
    Math_ApproachZeroF(&this->actor.shape.shadowScale, 0.3f, 5.0f);
    if (this->actor.shape.yOffset < -2970.0f) {
        this->actor.shape.yOffset = -3000.0f;
        this->actor.draw = func_80A3BE60;
        Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.home.pos);
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_BAKUO_APPEAR);
        this->actor.flags |= 0x8000000;
        this->actor.flags &= ~1;
        this->actionFunc = func_80A3B220;
    }
}

void func_80A3B8F8(EnBaguo* this, GlobalContext* globalCtx) {
    if (this->unk_1B4 == 0) {
        Actor_MarkForDeath(&this->actor);
    }
    if (this->unk_1B4 >= 0x1A) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3B958.s")

void EnBaguo_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnBaguo* this = THIS;

    Actor_SetHeight(&this->actor, 30.0f);
    func_80A3C008(this, globalCtx);
    func_80A3B958(this, globalCtx);
    this->actionFunc(this, globalCtx);

    if (this->unk_1B2 != 0) {
        this->unk_1B2--;
    }

    if (this->unk_1B4 != 0) {
        this->unk_1B4--;
    }

    if ((this->unk_1B6 != 3) && (this->unk_1B6 != 0)) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider);
    }

    if (this->unk_1B6 != 3) {
        this->actor.shape.rot.x = this->actor.world.rot.x;
        this->actor.shape.rot.z = this->actor.world.rot.z;
        if (this->unk_1B2 == 0) {
            this->unk_1B0++;
            if (this->unk_1B0 >= 3) {
                this->unk_1B0 = 0;
                this->unk_1B2 = Rand_ZeroFloat(60.0f) + 20.0f;
            }
        }
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 60.0f, 0x1D);
        if (this->unk_1B6 != 0) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider);
        }
        if (this->unk_1B6 != 3) {
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider);
        }
    }
}

void func_80A3BE24(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnBaguo* this = THIS;

    Collider_UpdateSpheres(limbIndex, &this->collider);
}

void func_80A3BE60(Actor* thisx, GlobalContext* globalCtx) {
    EnBaguo* this = THIS;
    Gfx* tempPolyOpa;
    s32 pad;
    s32 eyeIndexTemp;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    void* virtualAddress;

    func_8012C28C(gfxCtx);
    tempPolyOpa = gfxCtx->polyOpa.p;
    eyeIndexTemp = this->unk_1B0;
    virtualAddress = Lib_SegmentedToVirtual(D_80A3C35C[eyeIndexTemp]);
    gSPSegment(tempPolyOpa, 0x08, virtualAddress);
    gfxCtx->polyOpa.p = tempPolyOpa + 1;
    SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, NULL, func_80A3BE24, &this->actor);
    func_80A3C17C(this, globalCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3BF0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3C008.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3C17C.s")
