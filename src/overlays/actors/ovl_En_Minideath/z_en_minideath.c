/*
 * File: z_en_minideath.c
 * Overlay: ovl_En_Minideath
 * Description: Gomess's bats
 */

#include "z_en_minideath.h"
#include "overlays/actors/ovl_En_Death/z_en_death.h"
#include "objects/object_death/object_death.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY | ACTOR_FLAG_10)

#define THIS ((EnMinideath*)thisx)

void EnMinideath_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMinideath_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMinideath_Update(Actor* thisx, GlobalContext* globalCtx);

void func_808CA860(EnMinideath* this, GlobalContext* globalCtx);
void func_808CA8F4(EnMinideath* this, GlobalContext* globalCtx);
void func_808CAAEC(EnMinideath* this, GlobalContext* globalCtx);
void func_808CABB0(EnMinideath* this, GlobalContext* globalCtx);
void func_808CACD8(EnMinideath* this, GlobalContext* globalCtx);
void func_808CAE18(EnMinideath* this, GlobalContext* globalCtx);
void func_808CAF68(EnMinideath* this, GlobalContext* globalCtx);
void func_808CB094(EnMinideath* this, GlobalContext* globalCtx);
void func_808CB22C(EnMinideath* this, GlobalContext* globalCtx);
void func_808CB454(EnMinideath* this, GlobalContext* globalCtx);
void func_808CB59C(EnMinideath* this, GlobalContext* globalCtx);
void EnMinideath_Die(EnMinideath* this, GlobalContext* globalCtx);
void EnMinideath_Dead(EnMinideath* this, GlobalContext* globalCtx);

void func_808CA34C(EnMinideath* this);
void func_808CA7D4(EnMinideath* this);
void func_808CA8E0(EnMinideath* this);
void func_808CAAC8(EnMinideath* this);
void func_808CAB90(EnMinideath* this);
void func_808CAE00(EnMinideath* this);
void func_808CAF08(EnMinideath* this);
void EnMinideath_SetupDead(EnMinideath* this);

const ActorInit En_Minideath_InitVars = {
    ACTOR_EN_MINIDEATH,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DEATH,
    sizeof(EnMinideath),
    (ActorFunc)EnMinideath_Init,
    (ActorFunc)EnMinideath_Destroy,
    (ActorFunc)EnMinideath_Update,
    (ActorFunc)NULL,
};

// static ColliderJntSphElementInit sJntSphElementsInit[3] = {
static ColliderJntSphElementInit D_808CBF50[3] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_HARD,
            BUMP_ON,
            OCELEM_ON,
        },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_HARD,
            BUMP_ON,
            OCELEM_ON,
        },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_HARD,
            BUMP_ON,
            OCELEM_ON,
        },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_808CBFBC = {
    {
        COLTYPE_NONE,
        AT_NONE | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(D_808CBF50),
    D_808CBF50, // sJntSphElementsInit,
};

typedef enum {
    DMGEFF_NONE = 0,
    DMGEFF_STUN = 1,
    DMGEFF_FIRE_ARROW = 2,
    DMGEFF_ICE_ARROW = 3,
    DMGEFF_LIGHT_ARROW = 4,
    DMGEFF_ZORA_BARRIER = 5
} EnMinideathDamageEffect;

// static DamageTable sDamageTable = {
static DamageTable D_808CBFCC = {
    /* Deku Nut       */ DMG_ENTRY(0, DMGEFF_STUN),
    /* Deku Stick     */ DMG_ENTRY(1, DMGEFF_NONE),
    /* Horse trample  */ DMG_ENTRY(1, DMGEFF_NONE),
    /* Explosives     */ DMG_ENTRY(1, DMGEFF_NONE),
    /* Zora boomerang */ DMG_ENTRY(1, DMGEFF_NONE),
    /* Normal arrow   */ DMG_ENTRY(1, DMGEFF_NONE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, DMGEFF_NONE),
    /* Hookshot       */ DMG_ENTRY(1, DMGEFF_NONE),
    /* Goron punch    */ DMG_ENTRY(1, DMGEFF_NONE),
    /* Sword          */ DMG_ENTRY(1, DMGEFF_NONE),
    /* Goron pound    */ DMG_ENTRY(0, DMGEFF_NONE),
    /* Fire arrow     */ DMG_ENTRY(1, DMGEFF_FIRE_ARROW),
    /* Ice arrow      */ DMG_ENTRY(1, DMGEFF_ICE_ARROW),
    /* Light arrow    */ DMG_ENTRY(2, DMGEFF_LIGHT_ARROW),
    /* Goron spikes   */ DMG_ENTRY(1, DMGEFF_NONE),
    /* Deku spin      */ DMG_ENTRY(1, DMGEFF_NONE),
    /* Deku bubble    */ DMG_ENTRY(1, DMGEFF_NONE),
    /* Deku launch    */ DMG_ENTRY(2, DMGEFF_NONE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, DMGEFF_STUN),
    /* Zora barrier   */ DMG_ENTRY(1, DMGEFF_ZORA_BARRIER),
    /* Normal shield  */ DMG_ENTRY(0, DMGEFF_NONE),
    /* Light ray      */ DMG_ENTRY(0, DMGEFF_NONE),
    /* Thrown object  */ DMG_ENTRY(1, DMGEFF_NONE),
    /* Zora punch     */ DMG_ENTRY(1, DMGEFF_NONE),
    /* Spin attack    */ DMG_ENTRY(1, DMGEFF_NONE),
    /* Sword beam     */ DMG_ENTRY(0, DMGEFF_NONE),
    /* Normal Roll    */ DMG_ENTRY(0, DMGEFF_NONE),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, DMGEFF_NONE),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, DMGEFF_NONE),
    /* Unblockable    */ DMG_ENTRY(0, DMGEFF_NONE),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, DMGEFF_NONE),
    /* Powder Keg     */ DMG_ENTRY(1, DMGEFF_NONE),
};

// sColChkInfoInit
static CollisionCheckInfoInit D_808CBFEC = { 1, 15, 30, 10 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808CBFF4[] = {
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_STOP),
};

static s32 sItemDropTimer;
s32 D_808CC254;
s32 D_808CC258;
s32 D_808CC25C;

void EnMinideath_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnMinideath* this = THIS;
    s32 i;

    Actor_ProcessInitChain(thisx, D_808CBFF4);

    this->unk_158 = thisx->world.pos.y - thisx->parent->world.pos.y;
    this->spawnShapeRot = thisx->shape.rot.y;

    thisx->shape.rot.y = thisx->parent->shape.rot.y;
    thisx->world.rot.y = thisx->parent->shape.rot.y;
    thisx->flags &= ~ACTOR_FLAG_1;

    Collider_InitAndSetJntSph(globalCtx, &this->collider, thisx, &D_808CBFBC, this->colliderElements);
    CollisionCheck_SetInfo(&thisx->colChkInfo, &D_808CBFCC, &D_808CBFEC);

    for (i = 0; i < ARRAY_COUNT(this->colliderElements); i++) {
        this->collider.elements[i].dim.worldSphere.radius = this->collider.elements[i].dim.modelSphere.radius;
    }

    func_808CA34C(this);

    this->number = thisx->params;
    thisx->params = 0;
    this->unk_149 = false;

    if (gSaveContext.eventInf[6] & 8) {
        this->collider.base.atFlags |= AT_ON;
        this->unk_149 = true;

        func_808CABB0(this, globalCtx);

        for (i = 0; i < ARRAY_COUNT(this->unk_160); i++) {
            Math_Vec3f_Sum(&thisx->world.pos, &this->unk_160[i].unk_10, &this->unk_160[i].unk_4);
        }

        func_808CAB90(this);
    } else {
        func_808CA7D4(this);
    }
}

void EnMinideath_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnMinideath* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void EnMinideath_DropCollectible(Vec3f* spawnPos, GlobalContext* globalCtx) {
    if (sItemDropTimer == 0 && Rand_ZeroOne() < 0.3f) {
        if (Rand_ZeroOne() < 0.5f) {
            Item_DropCollectible(globalCtx, spawnPos, ITEM00_ARROWS_10);
        } else {
            Item_DropCollectible(globalCtx, spawnPos, ITEM00_MAGIC_LARGE);
        }
        sItemDropTimer = 800; // wait 40 seconds before next drop
    }
}

void func_808CA308(EnMinideath* this, s32 arg1) {
    if (this->unk_149 != arg1) {
        this->unk_149 = arg1;

        if (arg1 == true) {
            this->actor.parent->params++;
        } else {
            this->actor.parent->params--;
        }
    }
}

void func_808CA34C(EnMinideath* this) {
    MiniDeathStruct* phi_s0;
    s32 i;

    for (phi_s0 = this->unk_160, i = 0; i < ARRAY_COUNT(this->unk_160); i++, phi_s0++) {
        phi_s0->unk_10.x = randPlusMinusPoint5Scaled(80.0f);
        phi_s0->unk_10.y = Rand_ZeroFloat(40.0f);
        phi_s0->unk_10.z = randPlusMinusPoint5Scaled(80.0f);
        phi_s0->animFrame = (s32)Rand_ZeroFloat(9.0f) % MINIDEATH_ANIM_LENGTH;
        phi_s0->unk_1C = (Rand_Next() >> 17);
        phi_s0->unk_1E = (Rand_Next() >> 16);
        phi_s0->unk_1 = 0;
        phi_s0->unk_22 = 0;
    }
}

void func_808CA458(EnMinideath* this, GlobalContext* globalCtx) {
    s16 temp_s1;
    MiniDeathStruct* phi_s0;
    f32 phi_fv0;
    f32 phi_fa0;
    s32 i;
    s32 phi_s7;
    s32 phi_s3;

    phi_s3 = 0;
    phi_s7 = 0;

    phi_s0 = this->unk_160;
    for (i = 0; i < ARRAY_COUNT(this->unk_160); i++, phi_s0++) {
        if (phi_s0->unk_1 == 0) {
            phi_s0->unk_10.x += 3.0f * Math_CosS(phi_s0->unk_1C) * Math_SinS(phi_s0->unk_1E);
            phi_s0->unk_10.y += 3.0f * Math_SinS(phi_s0->unk_1C);
            phi_s0->unk_10.z += 3.0f * Math_CosS(phi_s0->unk_1C) * Math_CosS(phi_s0->unk_1E);

            if (this->actionFunc == func_808CA860) {
                phi_fv0 = 100.0f;
                phi_fa0 = SQ(phi_fv0);
            } else if (this->actionFunc == func_808CB094 || this->actionFunc == func_808CB454) {
                phi_fv0 = 20.0f;
                phi_fa0 = SQ(20.0f);
            } else {
                phi_fv0 = 40.0f;
                phi_fa0 = SQ(40.0f);
            }

            if (phi_s0->unk_10.y < 0.0f || phi_fv0 < phi_s0->unk_10.y ||
                phi_fa0 < SQ(phi_s0->unk_10.x) + SQ(phi_s0->unk_10.z)) {
                temp_s1 = Math_FAtan2F(sqrtf(SQ(phi_s0->unk_10.x) + SQ(phi_s0->unk_10.z)), phi_s0->unk_10.y);
                phi_s0->unk_1C = -1 * temp_s1 + (Rand_Next() >> 19);
                temp_s1 = Math_FAtan2F(phi_s0->unk_10.z, phi_s0->unk_10.x);
                phi_s0->unk_1E = temp_s1 + (Rand_Next() >> 19) + 0x8000;
            }

            phi_s3++;
        } else if (phi_s0->unk_1 == 1) {
            phi_s0->unk_4.y += phi_s0->unk_10.y;
            phi_s0->unk_1E += 0x1800;
            phi_s0->unk_10.y -= 1.0f;

            if (phi_s0->unk_4.y < this->actor.parent->home.pos.y) {
                phi_s0->unk_4.y = this->actor.parent->home.pos.y;
                func_800B3030(globalCtx, &phi_s0->unk_4, &gZeroVec3f, &gZeroVec3f, 100, 0, 0);
                SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &phi_s0->unk_4, 11, NA_SE_EN_EXTINCT);
                EnMinideath_DropCollectible(&phi_s0->unk_4, globalCtx);
                phi_s0->unk_1 = 2;
            }
        } else if (phi_s0->unk_1 == 2) {
            if (phi_s0->unk_22 > 0) {
                phi_s0->unk_22--;
            } else if (this->actionFunc == func_808CABB0) {
                Math_Vec3f_Diff(&this->actor.parent->focus.pos, &this->actor.world.pos, &phi_s0->unk_10);
                phi_s0->unk_1 = 0;
                this->collider.elements[i].info.bumperFlags |= BUMP_ON;
                this->collider.elements[i].info.toucherFlags |= TOUCH_ON;
                phi_s7 = 1;
                phi_s3++;
            }
        }
    }

    if (phi_s7 && phi_s3 > 1) {
        func_808CA308(this, true);
    }
}

void func_808CA7D4(EnMinideath* this) {
    this->actor.speedXZ = 6.0f;
    this->actor.world.pos.x = randPlusMinusPoint5Scaled(600.0f) + this->actor.parent->world.pos.x;
    this->actor.world.pos.z = randPlusMinusPoint5Scaled(600.0f) + this->actor.parent->world.pos.z;
    this->actor.shape.rot.y = Rand_Next() >> 16;
    this->actor.shape.rot.x = 0;
    this->unk_150.y = this->actor.shape.rot.y;
    this->actionFunc = func_808CA860;
}

void func_808CA860(EnMinideath* this, GlobalContext* globalCtx) {
    if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->unk_150.y, 0x480) && (this->actor.bgCheckFlags & 8)) {
        // Fly away from walls
        this->unk_150.y = (Rand_Next() >> 18) + this->actor.wallYaw;
    }
    if (this->actor.params == MINIDEATH_ACTION_7) {
        func_808CA8E0(this);
    }
}

void func_808CA8E0(EnMinideath* this) {
    this->actionFunc = func_808CA8F4;
}

void func_808CA8F4(EnMinideath* this, GlobalContext* globalCtx) {
    EnDeath* parent;
    Vec3f sp38;
    s32 phi_v0;
    s16 angle;

    Math_StepToF(&this->actor.speedXZ, 15.0f, 0.5f);

    if (this->actor.child == NULL) {
        phi_v0 = 0;
        angle = 0;
    } else {
        angle = 0x5555;
        if (this->number == 6) {
            phi_v0 = 1;
        } else if (this->number == 12) {
            phi_v0 = 2;
            angle = -0x5556;
        } else {
            phi_v0 = -1;
            Math_Vec3f_Copy(&sp38, &this->actor.child->world.pos);
            angle = 0;
        }
    }

    if (phi_v0 != -1) {
        parent = (EnDeath*)this->actor.parent;

        angle += parent->coreRotation;
        sp38.x = this->actor.parent->world.pos.x + Math_SinS(angle) * parent->coreVelocity;
        sp38.z = this->actor.parent->world.pos.z + Math_CosS(angle) * parent->coreVelocity;
        sp38.y = this->actor.parent->world.pos.y + phi_v0 * 20;
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, Actor_YawToPoint(&this->actor, &sp38), 2, 0x1000, 0x100);
    if (this->actor.parent->scale.z > 0.0f) {
        sp38.y = this->actor.parent->world.pos.y + this->unk_158;
    }
    Math_SmoothStepToS(&this->actor.shape.rot.x, Actor_PitchToPoint(&this->actor, &sp38), 2, 0x1000, 0x100);
    if (this->actor.params == MINIDEATH_ACTION_8) {
        func_808CAAC8(this);
    }
}

void func_808CAAC8(EnMinideath* this) {
    this->actor.params = MINIDEATH_ACTION_CONTINUE;
    this->actionFunc = func_808CAAEC;
    this->actor.speedXZ = 5.0f;
}

void func_808CAAEC(EnMinideath* this, GlobalContext* globalCtx) {
    Actor_DistanceToPoint(&this->actor, &this->actor.parent->focus.pos);
    Math_ScaledStepToS(&this->actor.shape.rot.y, Actor_YawToPoint(&this->actor, &this->actor.parent->focus.pos), 0x800);
    Math_ScaledStepToS(&this->actor.shape.rot.x, Actor_PitchToPoint(&this->actor, &this->actor.parent->focus.pos),
                       0x800);
    if (this->actor.params == MINIDEATH_ACTION_9) {
        this->collider.base.atFlags |= AT_ON;
        func_808CAF08(this);
    }
}

void func_808CAB90(EnMinideath* this) {
    this->actor.shape.rot.x = 0;
    this->actionFunc = func_808CABB0;
    this->actor.speedXZ = 0.0f;
}

void func_808CABB0(EnMinideath* this, GlobalContext* globalCtx) {
    s16 sp1E = this->spawnShapeRot + this->actor.parent->shape.rot.y;

    this->actor.world.pos.x = this->actor.parent->world.pos.x + Math_SinS(sp1E) * 60.0f;
    this->actor.world.pos.z = this->actor.parent->world.pos.z + Math_CosS(sp1E) * 60.0f;
    this->actor.world.pos.y = this->actor.parent->world.pos.y + this->unk_158;
    this->actor.shape.rot.y = this->actor.parent->shape.rot.y;
}

void func_808CAC54(EnMinideath* this) {
    this->actor.params = MINIDEATH_ACTION_CONTINUE;
    this->actor.speedXZ = 8.0f;
    func_800BE33C(&this->actor.parent->world.pos, &this->actor.world.pos, &this->unk_150, false);
    if (D_808CC258 != 0) {
        this->timer = D_808CC258;
    } else {
        this->timer = 200;
    }
    func_808CA308(this, false);
    this->actionFunc = func_808CACD8;
}

void func_808CACD8(EnMinideath* this, GlobalContext* globalCtx) {
    f32 temp_fv0;
    f32 temp_fv1;

    Math_StepToF(&this->actor.speedXZ, 6.0f, 0.5f);

    if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->unk_150.y, 0x480) && (this->actor.bgCheckFlags & 8)) {
        // Fly away from walls
        this->unk_150.y = (Rand_Next() >> 18) + this->actor.wallYaw;
    }

    if (Math_ScaledStepToS(&this->actor.shape.rot.x, this->unk_150.x, 0x480)) {
        temp_fv0 = this->actor.world.pos.y;
        temp_fv1 = this->actor.parent->home.pos.y;

        if (temp_fv0 < temp_fv1 + 50.0f) {
            this->unk_150.x = -0x800 - ((u32)Rand_Next() >> 20);
        } else if (temp_fv0 > temp_fv1 + 200.0f) {
            this->unk_150.x = ((u32)Rand_Next() >> 20) + 0x800;
        }
    }

    if (this->timer == 0) {
        func_808CAE00(this);
    } else {
        this->timer--;
    }
}

void func_808CAE00(EnMinideath* this) {
    this->actor.params = MINIDEATH_ACTION_CONTINUE;
    this->actionFunc = func_808CAE18;
}

void func_808CAE18(EnMinideath* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 temp_fv0 = Actor_DistanceToPoint(&this->actor, &this->actor.parent->focus.pos);
    f32 phi_fa0 = temp_fv0 * 0.016666668f;

    if (phi_fa0 > 1.0f) {
        phi_fa0 = 1.0f;
    }
    Math_StepToF(&this->actor.speedXZ, 6.0f * phi_fa0, 0.5f);
    Math_ScaledStepToS(&this->actor.shape.rot.y, Actor_YawToPoint(&this->actor, &this->actor.parent->focus.pos), 0x800);
    Math_ScaledStepToS(&this->actor.shape.rot.x, Actor_PitchToPoint(&this->actor, &this->actor.parent->focus.pos),
                       0x800);
    if (temp_fv0 < 30.0f) {
        func_808CAF08(this);
    }
}

void func_808CAF08(EnMinideath* this) {
    s32 phi_v0;

    this->actor.speedXZ = 0.0f;
    func_808CA308(this, true);

    for (phi_v0 = 0; phi_v0 < ARRAY_COUNT(this->unk_160); phi_v0++) {
        this->unk_160[phi_v0].unk_22 = 0;
    }
    this->actionFunc = func_808CAF68;
}

void func_808CAF68(EnMinideath* this, GlobalContext* globalCtx) {
    Vec3f target;
    f32 dist;
    s16 sp26;
    s32 done;

    done = Math_ScaledStepToS(&this->actor.shape.rot.y, this->spawnShapeRot + this->actor.parent->shape.rot.y, 0x800);
    Math_ScaledStepToS(&this->actor.shape.rot.x, 0, 0x800);
    sp26 = this->spawnShapeRot + this->actor.parent->shape.rot.y;
    target.x = this->actor.parent->world.pos.x + Math_SinS(sp26) * 60.0f;
    target.z = this->actor.parent->world.pos.z + Math_CosS(sp26) * 60.0f;
    target.y = this->actor.parent->world.pos.y + this->unk_158;

    dist = Math_Vec3f_StepTo(&this->actor.world.pos, &target, 10.0f);
    if (done && dist < 20.0f) {
        func_808CAB90(this);
    }
}

void func_808CB07C(EnMinideath* this) {
    this->actor.params = MINIDEATH_ACTION_CONTINUE;
    this->actionFunc = func_808CB094;
}

void func_808CB094(EnMinideath* this, GlobalContext* globalCtx) {
    Math_Vec3f_StepTo(&this->actor.world.pos, &this->actor.parent->focus.pos, 5.0f);
}

void func_808CB0C8(EnMinideath* this, GlobalContext* globalCtx) {
    s32 phi_a2;
    s32 phi_v1;
    s32 phi_a1;

    this->actor.params = MINIDEATH_ACTION_CONTINUE;
    this->actor.speedXZ = 8.0f;

    if (this->number >= 10) {
        phi_v1 = 19 - this->number;
        phi_a1 = 1;
        phi_a2 = 0;
    } else {
        phi_v1 = 9 - this->number;
        phi_a1 = -1;
        phi_a2 = 0x200;
    }
    this->actor.shape.rot.y = this->actor.parent->shape.rot.y + (phi_a1 * 0x4000) + ((phi_v1 * 0x2000) * phi_a1);
    this->actor.shape.rot.x = (phi_a2 - phi_v1 * 0x400) + 0xC00;

    this->actor.world.pos.x = this->actor.parent->focus.pos.x + Math_SinS(this->actor.shape.rot.y) * 60.0f;
    this->actor.world.pos.z = this->actor.parent->focus.pos.z + Math_CosS(this->actor.shape.rot.y) * 60.0f;
    this->actor.world.pos.y = this->actor.parent->focus.pos.y - Math_SinS(this->actor.shape.rot.x) * 60.0f;

    func_808CA34C(this);
    this->timer = 100;
    func_808CA308(this, false);

    D_808CC254 = 0;

    if (this->actor.child == NULL || this->number == 9) {
        this->unk_15C = &GET_PLAYER(globalCtx)->actor;
    } else {
        this->unk_15C = this->actor.child;
    }
    this->actionFunc = func_808CB22C;
}

void func_808CB22C(EnMinideath* this, GlobalContext* globalCtx) {
    Vec3f sp34;
    s16 sp32 = 0;

    Math_StepToF(&this->actor.speedXZ, 6.0f, 0.2f);
    if (this->timer > 0) {
        this->timer--;
    }

    if (this->unk_15C->id != ACTOR_EN_MINIDEATH) {
        if (this->timer == 0) {
            this->unk_15C = this->actor.parent;
        }
        Math_Vec3f_Copy(&sp34, &this->unk_15C->focus.pos);
        if (Actor_DistanceToPoint(&this->actor, &sp34) > 200.0f) {
            if (this->number < 10) {
                sp32 = -0x1C00;
            } else {
                sp32 = 0x1C00;
            }
            sp34.y += 50.0f;
        }
    } else if (((EnMinideath*)this->unk_15C)->actionFunc != func_808CB22C) {
        Math_Vec3f_Copy(&sp34, &this->actor.parent->focus.pos);
    } else {
        Math_Vec3f_Copy(&sp34, &this->unk_15C->focus.pos);
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, Actor_YawToPoint(&this->actor, &sp34) + sp32, 5, 0xC00, 0x80);
    Math_SmoothStepToS(&this->actor.shape.rot.x, Actor_PitchToPoint(&this->actor, &sp34), 5, 0xC00, 0x80);
    if ((this->collider.base.atFlags & AT_HIT) && this->timer > 0) {
        D_808CC254 += 1;
    }
    if (this->timer == 0 && Actor_DistanceToPoint(&this->actor, &this->actor.parent->focus.pos) < 50.0f) {
        func_808CAF08(this);
    }
}

void func_808CB418(EnMinideath* this) {
    this->actor.params = MINIDEATH_ACTION_CONTINUE;
    this->timer = 10;
    func_808CA34C(this);
    this->actionFunc = func_808CB454;
}

void func_808CB454(EnMinideath* this, GlobalContext* globalCtx) {
    Vec3f target;

    if (this->timer > 0) {
        this->timer--;
    }
    target.x = (Math_SinS(this->actor.parent->shape.rot.y) * 20.0f) + this->actor.parent->focus.pos.x;
    target.z = (Math_CosS(this->actor.parent->shape.rot.y) * 20.0f) + this->actor.parent->focus.pos.z;
    target.y = this->actor.parent->focus.pos.y;
    Math_Vec3f_StepTo(&this->actor.world.pos, &target, 5.0f);
    if (this->timer == 0 && ((EnMinideath*)this->actor.child)->actionFunc != func_808CB22C) {
        func_808CAB90(this);
    }
}

void func_808CB524(EnMinideath* this) {
    s32 i;

    this->actor.params = MINIDEATH_ACTION_CONTINUE;
    func_808CA308(this, false);
    this->collider.base.atFlags &= ~AT_ON;

    for (i = 0; i < ARRAY_COUNT(this->unk_160); i++) {
        this->unk_160[i].unk_1 = 0;
    }

    this->unk_150.y = this->actor.shape.rot.y;
    this->unk_150.x = this->actor.shape.rot.x;
    this->actionFunc = func_808CB59C;
}

void func_808CB59C(EnMinideath* this, GlobalContext* globalCtx) {
    f32 temp_fv0;
    f32 temp_fv1;

    Math_StepToF(&this->actor.speedXZ, 5.0f, 0.2f);
    if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->unk_150.y, 0x480) && (this->actor.bgCheckFlags & 8)) {
        // Fly away from walls
        this->unk_150.y = (Rand_Next() >> 0x12) + this->actor.wallYaw;
    }
    if (Math_ScaledStepToS(&this->actor.shape.rot.x, this->unk_150.x, 0x480)) {
        temp_fv0 = this->actor.world.pos.y;
        temp_fv1 = this->actor.parent->home.pos.y;
        if (temp_fv0 < (temp_fv1 + 50.0f)) {
            this->unk_150.x = -0x800 - ((u32)Rand_Next() >> 20);
        } else if (temp_fv0 > (temp_fv1 + 200.0f)) {
            this->unk_150.x = ((u32)Rand_Next() >> 20) + 0x800;
        }
    }
}

void EnMinideath_SetupDie(EnMinideath* this) {
    this->actor.params = MINIDEATH_ACTION_CONTINUE;
    this->unk_150.x = 0x4000;
    this->actionFunc = EnMinideath_Die;
    this->actor.gravity = -0.5f;
}

void EnMinideath_Die(EnMinideath* this, GlobalContext* globalCtx) {
    MiniDeathStruct* phi_s0;
    s32 i;
    s32 phi_s2 = 0;

    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.2f);
    Math_ScaledStepToS(&this->actor.shape.rot.x, this->unk_150.x, 0x480);
    func_800B9010(&this->actor, NA_SE_EN_COMMON_EXTINCT_LEV - SFX_FLAG);

    if (this->actor.bgCheckFlags & 1) {
        this->actor.speedXZ = 0.0f;

        for (phi_s0 = this->unk_160, i = 0; i < ARRAY_COUNT(this->unk_160); i++, phi_s0++) {
            if (Math_StepToF(&phi_s0->unk_10.y, 0.0f, 7.0f)) {
                phi_s2++;
            }
        }

        if (phi_s2 == ARRAY_COUNT(this->unk_160)) {
            EnMinideath_SetupDead(this);
        }
    }
}

void EnMinideath_SetupDead(EnMinideath* this) {
    this->actionFunc = EnMinideath_Dead;
}

void EnMinideath_Dead(EnMinideath* this, GlobalContext* globalCtx) {
    if (this->actor.parent->update == NULL) {
        Actor_MarkForDeath(&this->actor);
    } else {
        func_800B9010(&this->actor, NA_SE_EN_COMMON_EXTINCT_LEV - SFX_FLAG);
    }
}

void EnMinideath_SetNextAction(EnMinideath* this, GlobalContext* globalCtx) {
    s16 action = this->actor.params;

    if (action == MINIDEATH_ACTION_6) {
        func_808CB524(this);
    } else if (action == MINIDEATH_ACTION_2) {
        func_808CAE00(this);
    } else if (action == MINIDEATH_ACTION_3) {
        func_808CB07C(this);
    } else if (action == MINIDEATH_ACTION_4) {
        if (this->number == 0 || this->number == 10) {
            func_808CB418(this);
        } else {
            func_808CB0C8(this, globalCtx);
        }
    } else if (action == MINIDEATH_ACTION_1) {
        func_808CAC54(this);
    } else if (action == MINIDEATH_ACTION_DIE) {
        EnMinideath_SetupDie(this);
    }
}

void func_808CB8F4(EnMinideath* this, GlobalContext* globalCtx) {
    s32 temp_a0_2;
    EnMinideath* temp_a0_3;
    s32 phi_a2;
    s32 phi_v0_2;
    s32 phi_a0;

    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;

        if (this->actor.colChkInfo.damageEffect == DMGEFF_STUN) {
            if (this->actionFunc == func_808CABB0 || this->actionFunc == func_808CAF68) {
                D_808CC258 = 5;
            } else if (this->actionFunc == func_808CB22C) {
                EnMinideath** miniDeaths = (EnMinideath**)((EnDeath*)this->actor.parent)->miniDeaths;

                for (temp_a0_2 = this->number - 1; temp_a0_2 >= 0; temp_a0_2--) {
                    temp_a0_3 = miniDeaths[temp_a0_2];

                    if (temp_a0_3->unk_15C == &this->actor) {
                        temp_a0_3->unk_15C = this->unk_15C;
                        break;
                    }
                }

                this->timer = 0;
                this->unk_15C = &GET_PLAYER(globalCtx)->actor;
            }
        } else {
            for (phi_a2 = 0; phi_a2 < ARRAY_COUNT(this->colliderElements); phi_a2++) {
                if (this->collider.elements[phi_a2].info.bumperFlags & BUMP_HIT) {
                    this->collider.elements[phi_a2].info.bumperFlags &= ~(BUMP_ON | BUMP_HIT);
                    this->collider.elements[phi_a2].info.toucherFlags &= ~(TOUCH_ON | TOUCH_HIT);
                    this->unk_160[phi_a2].unk_10.y = -1.0f;
                    this->unk_160[phi_a2].unk_1 = 1;
                    this->unk_160[phi_a2].unk_1E = this->actor.shape.rot.y;
                    this->unk_160[phi_a2].unk_22 = 60;

                    if ((this->actionFunc == func_808CABB0 || this->actionFunc == func_808CAF68) &&
                        this->actor.colChkInfo.damageEffect == DMGEFF_LIGHT_ARROW) {
                        D_808CC258 = 200;
                    }
                }
            }

            phi_a0 = 0;
            for (phi_v0_2 = 0; phi_v0_2 < ARRAY_COUNT(this->unk_160); phi_v0_2++) {
                if (this->unk_160[phi_v0_2].unk_1 != 0) {
                    phi_a0++;
                }
            }

            if (phi_a0 > 1) {
                func_808CA308(this, false);
            }

            if (D_808CC25C == 0) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FFLY_DEAD);
                D_808CC25C = 1;
            }
        }
    }
}

void EnMinideath_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnMinideath* this = THIS;
    s32 pad;
    ColliderJntSphElement* elem;
    s32 temp;
    s32 i;
    MiniDeathStruct* phi_s0;
    EnMinideath* phi_s0_3;

    if (sItemDropTimer > 0) {
        sItemDropTimer--;
    }

    if (this->actionFunc != EnMinideath_Dead) {
        for (i = 0; i < ARRAY_COUNT(this->unk_160); i++) {
            if (this->unk_160[i].unk_1 == 0) {
                func_800B9010(&this->actor, NA_SE_EV_BAT_FLY - SFX_FLAG);
                break;
            }
        }
    }

    func_808CB8F4(this, globalCtx);

    EnMinideath_SetNextAction(this, globalCtx);
    this->actionFunc(this, globalCtx);

    if (this->actionFunc != EnMinideath_Dead) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        this->actor.world.rot.x = -this->actor.shape.rot.x;

        if (this->actionFunc == EnMinideath_Die) {
            Actor_MoveWithGravity(&this->actor);
        } else {
            Actor_MoveWithoutGravity(&this->actor);
        }

        if (this->actionFunc != func_808CABB0 && this->actionFunc != func_808CAF68) {
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 50.0f, 80.0f, 7);
        }

        if (this->actionFunc != EnMinideath_Die) {
            func_808CA458(this, globalCtx);
        }

        Actor_SetFocus(&this->actor, 0.0f);

        phi_s0 = this->unk_160;
        elem = this->collider.elements;
        for (i = 0; i != ARRAY_COUNT(this->colliderElements); i++) {
            if (phi_s0->unk_1 == 0) {
                Math_Vec3f_Sum(&this->actor.world.pos, &phi_s0->unk_10, &phi_s0->unk_4);

                if (this->actionFunc != EnMinideath_Die) {
                    phi_s0->animFrame++;
                    if (phi_s0->animFrame == MINIDEATH_ANIM_LENGTH) {
                        phi_s0->animFrame = 0;
                    }
                }

                elem->dim.worldSphere.center.x = phi_s0->unk_4.x;
                elem->dim.worldSphere.center.y = phi_s0->unk_4.y;
                elem->dim.worldSphere.center.z = phi_s0->unk_4.z;
            }
            phi_s0++;
            elem++;
        }

        if (this->collider.base.atFlags & AT_HIT) {
            this->collider.base.atFlags &= ~AT_HIT;
            this->attackTimer = 40;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FFLY_ATTACK);
        }
        if (this->collider.base.atFlags & AT_ON) {
            temp = (this->actionFunc == func_808CABB0) ? (globalCtx->gameplayFrames % 4) : 4;

            if (temp == 4 || temp == (this->number & 3)) {
                if (this->attackTimer == 0 && this->actor.parent->shape.rot.x == 0) {
                    CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
                }
                if (this->actionFunc != func_808CB094) {
                    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
                }
            }
        }
        if (this->attackTimer > 0) {
            this->attackTimer--;
        }
        if (this->number == 19) {
            phi_s0_3 = NULL;
            D_808CC25C = 0;

            if (D_808CC258 != 0) {
                do {
                    phi_s0_3 =
                        (EnMinideath*)SubS_FindActor(globalCtx, &phi_s0_3->actor, ACTORCAT_ENEMY, ACTOR_EN_MINIDEATH);
                    if (phi_s0_3 != NULL) {
                        func_808CAC54(phi_s0_3);
                        phi_s0_3 = (EnMinideath*)phi_s0_3->actor.next;
                    }
                } while (phi_s0_3 != NULL);

                globalCtx->envCtx.lightSettingOverride = 28;

                if (D_808CC258 == 5) {
                    ((EnDeath*)this->actor.parent)->unk_2FC = 5;
                } else {
                    ((EnDeath*)this->actor.parent)->unk_2FC = 20;
                }
                D_808CC258 = 0;
            } else if (D_808CC254 >= 5) {
                do {
                    phi_s0_3 =
                        (EnMinideath*)SubS_FindActor(globalCtx, &phi_s0_3->actor, ACTORCAT_ENEMY, ACTOR_EN_MINIDEATH);
                    if (phi_s0_3 != NULL) {
                        phi_s0_3->timer = 0;
                        phi_s0_3 = (EnMinideath*)phi_s0_3->actor.next;
                    }
                } while (phi_s0_3 != NULL);
                D_808CC254 = 0;
            }
        }
    }
}
