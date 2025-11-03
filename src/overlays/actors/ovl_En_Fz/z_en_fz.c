/*
 * File: z_en_fz.c
 * Overlay: ovl_En_Fz
 * Description: Freezard
 */

#include "z_en_fz.h"
#include "attributes.h"
#include "overlays/actors/ovl_En_Wiz/z_en_wiz.h"
#include "assets/objects/object_fz/object_fz.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_ATTENTION_ENABLED | ACTOR_FLAG_HOSTILE | ACTOR_FLAG_UPDATE_CULLING_DISABLED)

void EnFz_Init(Actor* thisx, PlayState* play);
void EnFz_Destroy(Actor* thisx, PlayState* play);
void EnFz_Update(Actor* thisx, PlayState* play);
void EnFz_Draw(Actor* thisx, PlayState* play);

void func_80932784(EnFz* this, PlayState* play);
void func_80932AE8(EnFz* this);
void func_80932AF4(EnFz* this);
void func_80932BD4(EnFz* this);
void func_809330D4(EnFz* this);
void func_80933104(EnFz* this, PlayState* play);
void func_80933184(EnFz* this);
void func_809331F8(EnFz* this, PlayState* play);
void func_80933248(EnFz* this);
void func_80933274(EnFz* this, PlayState* play);
void func_80933324(EnFz* this);
void func_80933368(EnFz* this, PlayState* play);
void func_809333A4(EnFz* this);
void func_809333D8(EnFz* this, PlayState* play);
void func_80933414(EnFz* this);
void func_80933444(EnFz* this, PlayState* play);
void func_80933480(EnFz* this, PlayState* play);
void func_809334B8(EnFz* this, PlayState* play);
void func_809336C0(EnFz* this, PlayState* play);
void func_80933760(EnFz* this, PlayState* play);
void func_80933790(EnFz* this);
void func_809337D4(EnFz* this, PlayState* play);
void func_8093389C(EnFz* this);
void func_809338E0(EnFz* this, PlayState* play);
void func_80933AF4(EnFz* this);
void func_80933B38(EnFz* this, PlayState* play);
void func_80934018(EnFz* this, Vec3f* a, Vec3f* b, Vec3f* c, f32 arg4);
void func_809340BC(EnFz* this, Vec3f* a, Vec3f* b, Vec3f* c, f32 arg4, f32 arg5, s16 arg6, u8 arg7);
void func_80934178(EnFz* this, PlayState* play);
void func_80934464(EnFz* this, PlayState* play);

ActorProfile En_Fz_Profile = {
    /**/ ACTOR_EN_FZ,
    /**/ ACTORCAT_ENEMY,
    /**/ FLAGS,
    /**/ OBJECT_FZ,
    /**/ sizeof(EnFz),
    /**/ EnFz_Init,
    /**/ EnFz_Destroy,
    /**/ EnFz_Update,
    /**/ EnFz_Draw,
};

static s16 D_809346F0[] = { 0, 0x2000, 0x4000, 0 };

static ColliderCylinderInitType1 sCylinderInit1 = {
    {
        COL_MATERIAL_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        COLSHAPE_CYLINDER,
    },
    {
        ELEM_MATERIAL_UNK0,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0xF7CFEFDD, 0x00, 0x00 },
        ATELEM_ON | ATELEM_SFX_NORMAL,
        ACELEM_ON | ACELEM_HOOKABLE,
        OCELEM_ON,
    },
    { 30, 80, 0, { 0, 0, 0 } },
};

static ColliderCylinderInitType1 sCylinderInit2 = {
    {
        COL_MATERIAL_METAL,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEM_MATERIAL_UNK0,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0x00001022, 0x00, 0x00 },
        ATELEM_NONE | ATELEM_SFX_NORMAL,
        ACELEM_ON,
        OCELEM_NONE,
    },
    { 35, 80, 0, { 0, 0, 0 } },
};

static ColliderCylinderInitType1 sCylinderInit3 = {
    {
        COL_MATERIAL_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEM_MATERIAL_UNK0,
        { 0x20000000, 0x02, 0x04 },
        { 0x00000000, 0x00, 0x00 },
        ATELEM_ON | ATELEM_SFX_NORMAL,
        ACELEM_NONE,
        OCELEM_NONE,
    },
    { 20, 30, -15, { 0, 0, 0 } },
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0xD),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(2, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(0, 0xD),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0xF),
    /* Hookshot       */ DMG_ENTRY(3, 0xF),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(3, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0xE),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, TATL_HINT_ID_FREEZARD, ICHAIN_CONTINUE),
    ICHAIN_U8(attentionRangeType, ATTENTION_RANGE_2, ICHAIN_CONTINUE),
    ICHAIN_F32(cullingVolumeDistance, 1400, ICHAIN_CONTINUE),
    ICHAIN_F32(lockOnArrowOffset, 30, ICHAIN_STOP),
};

void EnFz_Init(Actor* thisx, PlayState* play) {
    EnFz* this = (EnFz*)thisx;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->actor.colChkInfo.damageTable = &sDamageTable;
    this->actor.colChkInfo.health = 3;

    Collider_InitCylinder(play, &this->collider1);
    Collider_SetCylinderType1(play, &this->collider1, &this->actor, &sCylinderInit1);
    Collider_InitCylinder(play, &this->collider2);
    Collider_SetCylinderType1(play, &this->collider2, &this->actor, &sCylinderInit2);
    Collider_InitCylinder(play, &this->collider3);
    Collider_SetCylinderType1(play, &this->collider3, &this->actor, &sCylinderInit3);

    Actor_SetScale(&this->actor, 0.008f);
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.flags &= ~ACTOR_FLAG_ATTENTION_ENABLED;
    this->unusedTimer = 0;
    this->unusedCounter = 0;
    this->unk_BCC = 1;
    this->isMoving = false;
    this->isFreezing = false;
    this->unk_BD7 = 1;
    this->isDespawning = false;
    this->actor.speed = 0.0f;
    this->actor.cullingVolumeScale = 400.0f;
    this->originPos.x = this->actor.world.pos.x;
    this->originPos.y = this->actor.world.pos.y;
    this->originPos.z = this->actor.world.pos.z;
    this->originPosY2 = this->actor.world.pos.y;
    this->actor.velocity.y = this->actor.gravity;
    this->unk_BB8 = 135.0f;

    if (ENFZ_GET_8000(&this->actor)) {
        this->envAlpha = 0;
        this->actor.scale.y = 0.0f;
        func_80933184(this);
    } else {
        this->envAlpha = 255;
        if (this->actor.shape.rot.z == 0) {
            this->counter = (s32)Rand_ZeroFloat(64.0f) + 192;
        } else {
            if (this->actor.shape.rot.z < 0) {
                this->actor.shape.rot.z = 1;
            } else if (this->actor.shape.rot.z > 0x10) {
                this->actor.shape.rot.z = 0x10;
            }
            this->actor.shape.rot.z += -1;
            this->counter = this->actor.shape.rot.z * 0x10;
        }

        this->actor.shape.rot.z = 0;
        if (ENFZ_GET_4000(&this->actor)) {
            this->envAlpha = 0;
            this->actor.scale.y = 0.0f;
            func_80933184(this);
        } else if (ENFZ_GET_F(&this->actor) == ENFZ_F_3) {
            func_80933AF4(this);
        } else {
            func_8093389C(this);
        }
    }

    this->drawDmgEffTimer = 0;
    this->drawDmgEffScale = 0.0f;
    this->drawDmgEffAlpha = 0.0f;
    func_80932784(this, play);
}

void EnFz_Destroy(Actor* thisx, PlayState* play) {
    EnFz* this = (EnFz*)thisx;

    Collider_DestroyCylinder(play, &this->collider1);
    Collider_DestroyCylinder(play, &this->collider2);
    Collider_DestroyCylinder(play, &this->collider3);

    if ((this->actor.parent != NULL) && (this->wizrobeFlag == 0) && (this->actor.parent->id == ACTOR_EN_WIZ) &&
        (this->actor.parent->update != NULL) && (((EnWiz*)this->actor.parent)->freezard != NULL)) {
        EnWiz* wiz = (EnWiz*)this->actor.parent;

        wiz->freezard = NULL;
    }
}

// UpdateTargetPos
void func_80932784(EnFz* this, PlayState* play) {
    Vec3f pos;
    Vec3f hitPos;
    Vec3f unkVec;
    s32 bgId;
    CollisionPoly* hitPoly;

    pos.x = this->actor.world.pos.x;
    pos.y = this->actor.world.pos.y + 20.0f;
    pos.z = this->actor.world.pos.z;

    Matrix_Translate(pos.x, pos.y, pos.z, MTXMODE_NEW);
    Matrix_RotateZYX(this->actor.shape.rot.x, this->actor.shape.rot.y, this->actor.shape.rot.z, MTXMODE_APPLY);

    unkVec.x = unkVec.y = 0.0f;
    unkVec.z = 440.0f;

    Matrix_MultVec3f(&unkVec, &this->wallHitPos);
    if (BgCheck_EntityLineTest1(&play->colCtx, &pos, &this->wallHitPos, &hitPos, &hitPoly, true, false, false, true, &bgId)) {
        Math_Vec3f_Copy(&this->wallHitPos, &hitPos);
    }

    pos.x = this->actor.world.pos.x - this->wallHitPos.x;
    pos.z = this->actor.world.pos.z - this->wallHitPos.z;
    this->distToTargetSq = SQ(pos.x) + SQ(pos.z);
}

// ReachedTarget
s32 func_809328A4(EnFz* this, Vec3f* vec) {
    f32 distX = this->actor.world.pos.x - vec->x;
    f32 distZ = this->actor.world.pos.z - vec->z;

    if (this->distToTargetSq <= (SQ(distX) + SQ(distZ))) {
        return true;
    } else {
        return false;
    }
}

// Damaged
void func_809328F4(EnFz* this, PlayState* play, Vec3f* vec, s32 numEffects, f32 randFloat) {
    s32 i;
    Vec3f pos;
    Vec3f velocity;
    Vec3f accel;
    Color_RGBA8 primColor;
    Color_RGBA8 envColor;
    f32 scale;
    s32 life;

    accel.x = accel.z = 0.0f;
    accel.y = -1.0f;
    primColor.r = 155;
    primColor.g = 255;
    primColor.b = 255;
    primColor.a = 255;
    envColor.r = 200;
    envColor.g = 200;
    envColor.b = 200;

    for (i = 0; i < numEffects; i++) {
        scale = Rand_CenteredFloat(0.3f) + 0.6f;
        life = (s32)Rand_CenteredFloat(5.0f) + 12;
        pos.x = Rand_CenteredFloat(randFloat) + vec->x;
        pos.y = Rand_ZeroFloat(randFloat) + vec->y;
        pos.z = Rand_CenteredFloat(randFloat) + vec->z;
        velocity.x = Rand_CenteredFloat(10.0f);
        velocity.y = Rand_ZeroFloat(10.0f) + 2.0f;
        velocity.z = Rand_CenteredFloat(10.0f);
        EffectSsEnIce_Spawn(play, &pos, scale, &velocity, &accel, &primColor, &envColor, life);
    }

    CollisionCheck_SpawnShieldParticles(play, vec);
}

// SpawnIceSmokeHiddenState
void func_80932AE8(EnFz* this) {
}

// Fully Grown
// SpawnIceSmokeGrowingState
void func_80932AF4(EnFz* this) {
    Vec3f pos;
    Vec3f velocity;
    Vec3f accel;

    if ((this->counter % 16) == 0) {
        pos.x = Rand_CenteredFloat(40.0f) + this->actor.world.pos.x;
        pos.y = Rand_CenteredFloat(40.0f) + this->actor.world.pos.y + 30.0f;
        pos.z = Rand_CenteredFloat(40.0f) + this->actor.world.pos.z;
        accel.x = accel.z = 0.0f;
        accel.y = 0.1f;
        velocity.x = velocity.y = velocity.z = 0.0f;
        func_80934018(this, &pos, &velocity, &accel, Rand_ZeroFloat(7.5f) + 15.0f);
    }
}

// (2) Growing or Shrinking to/from hiding or (3) melting from fire
// EnFz_SpawnIceSmokeActiveState
void func_80932BD4(EnFz* this) {
    Vec3f pos;
    Vec3f velocity;
    Vec3f accel;

    if ((this->counter % 4) == 0) {
        pos.x = Rand_CenteredFloat(40.0f) + this->actor.world.pos.x;
        pos.y = this->originPosY2;
        pos.z = Rand_CenteredFloat(40.0f) + this->actor.world.pos.z;
        accel.x = accel.z = 0.0f;
        accel.y = 0.1f;
        velocity.x = velocity.y = velocity.z = 0.0f;
        func_80934018(this, &pos, &velocity, &accel, Rand_ZeroFloat(7.5f) + 15.0f);
    }
}

// ApplyDamage
void func_80932C98(EnFz* this, PlayState* play) {
    Vec3f vec;

    if (this->isMoving && ((this->actor.bgCheckFlags & BGCHECKFLAG_WALL) || !Actor_TestFloorInDirection(&this->actor, play, 60.0f, this->actor.world.rot.y))) {
        this->actor.bgCheckFlags &= ~BGCHECKFLAG_WALL;
        this->isMoving = false;
        this->speedXZ = 0.0f;
        this->actor.speed = 0.0f;
    }

    if (this->actor.parent != NULL) {
        if ((this->wizrobeFlag != 5) && (this->actor.parent->id == ACTOR_EN_WIZ)) {
            Actor* parent = this->actor.parent;

            if ((parent->update == NULL) || (parent->colChkInfo.health <= 0)) {
                this->actor.colChkInfo.health = 0;
                this->wizrobeFlag = 5;
                Actor_PlaySfx(&this->actor, NA_SE_EN_FREEZAD_DEAD);
                Actor_PlaySfx(&this->actor, NA_SE_EV_ICE_BROKEN);
                vec.x = this->actor.world.pos.x;
                vec.y = this->actor.world.pos.y;
                vec.z = this->actor.world.pos.z;
                func_809328F4(this, play, &vec, 30, 10.0f);
                func_809336C0(this, play);
                return;
            }

            if ((this->actor.colChkInfo.health != 0) && (this->wizrobeFlag == 1)) {
                this->actor.colChkInfo.health = 0;
                this->wizrobeFlag = 5;
                Actor_PlaySfx(&this->actor, NA_SE_EN_FREEZAD_DEAD);
                Actor_PlaySfx(&this->actor, NA_SE_EV_ICE_BROKEN);
                vec.x = this->actor.world.pos.x;
                vec.y = this->actor.world.pos.y;
                vec.z = this->actor.world.pos.z;
                func_809328F4(this, play, &vec, 30, 10.0f);
                func_809336C0(this, play);
                return;
            }
        }
    }

    if (this->isFreezing) {
        if (ENFZ_GET_8000(&this->actor) && (this->collider1.base.atFlags & AT_HIT)) {
            this->isMoving = false;
            this->speedXZ = 0.0f;
            this->collider1.base.acFlags &= ~AC_HIT;
            this->actor.speed = 0.0f;
            this->mainTimer = 10;
            func_809330D4(this);
        } else if (this->collider2.base.acFlags & AC_BOUNCED) {
            this->collider2.base.acFlags &= ~AC_BOUNCED;
            this->collider1.base.acFlags &= ~AC_HIT;
        } else if (this->collider1.base.acFlags & AC_HIT) {
            this->collider1.base.acFlags &= ~AC_HIT;
            switch (this->actor.colChkInfo.damageEffect) {
                case 4:
                    this->drawDmgEffTimer = 40;
                    this->drawDmgEffAlpha = 1.0f;
                    FALLTHROUGH;
                case 15:
                    Actor_ApplyDamage(&this->actor);
                    Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_RED, 255, COLORFILTER_BUFFLAG_XLU, 8);
                    if (this->actor.colChkInfo.health != 0) {
                        Actor_PlaySfx(&this->actor, NA_SE_EN_FREEZAD_DAMAGE);
                        vec.x = this->actor.world.pos.x;
                        vec.y = this->actor.world.pos.y;
                        vec.z = this->actor.world.pos.z;
                        func_809328F4(this, play, &vec, 10, 0.0f);
                        this->unusedCounter++;
                        break;
                    }
                    Actor_PlaySfx(&this->actor, NA_SE_EN_FREEZAD_DEAD);
                    Actor_PlaySfx(&this->actor, NA_SE_EV_ICE_BROKEN);
                    vec.x = this->actor.world.pos.x;
                    vec.y = this->actor.world.pos.y;
                    vec.z = this->actor.world.pos.z;
                    func_809328F4(this, play, &vec, 30, 10.0f);
                    func_809336C0(this, play);
                    break;

                case 2:
                    Actor_PlaySfx(&this->actor, NA_SE_EN_FREEZAD_DEAD);
                    func_80933790(this);
                    break;
            }
        }
    }
}

// EnFz_SetYawTowardsPlayer
void func_80933014(EnFz* this) {
    s16 yaw = this->actor.yawTowardsPlayer;
    s32 temp_a2 = ENFZ_GET_3000(&this->actor);
    s16 temp;
    s16 homeYawDiff;
    s32 homeYaw;

    if (!ENFZ_GET_8000(&this->actor)) {
        homeYaw = this->actor.home.rot.y;
        if (temp_a2 != 3) {
            homeYawDiff = yaw - homeYaw;
            if (D_809346F0[temp_a2] < ABS_ALT(homeYawDiff)) {
                temp = (homeYawDiff > 0) ? D_809346F0[temp_a2] : -D_809346F0[temp_a2];
                yaw = this->actor.home.rot.y + temp;
            }
        }
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, yaw, 10, 0x7D0, 0);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

// SetupDisappear
void func_809330D4(EnFz* this) {
    this->state = 2;
    this->isFreezing = false;
    this->actor.flags &= ~ACTOR_FLAG_ATTENTION_ENABLED;
    this->actionFunc = func_80933104;
}

void func_80933104(EnFz* this, PlayState* play) {
    this->envAlpha -= 16;
    if (this->envAlpha > 255) {
        this->envAlpha = 0;
    }

    if (Math_SmoothStepToF(&this->actor.scale.y, 0, 1.0f, 0.0005f, 0.0f) == 0.0f) {
        func_80933184(this);
    }
}

void func_80933184(EnFz* this) {
    this->state = 0;
    this->unk_BD2 = 0;
    this->unk_BD0 = 0;
    this->mainTimer = 100;

    this->actor.world.pos.x = this->originPos.x;
    this->actor.world.pos.y = this->originPos.y;
    this->actor.world.pos.z = this->originPos.z;

    if (ENFZ_GET_4000(&this->actor)) {
        this->state = 2;
        this->mainTimer = 10;
        this->unk_BD2 = 4000;
        this->actionFunc = func_80933274;
    } else {
        this->actionFunc = func_809331F8;
    }
}

// EnFz_Wait
void func_809331F8(EnFz* this, PlayState* play) {
    if ((this->mainTimer == 0) && (this->actor.xzDistToPlayer < 400.0f)) {
        func_80933248(this);
    }
}

void func_80933248(EnFz* this) {
    this->state = 2;
    this->mainTimer = 20;
    this->unk_BD2 = 4000;
    this->actionFunc = func_80933274;
}

// EnFz_Appear
void func_80933274(EnFz* this, PlayState* play) {
    if (this->mainTimer == 0) {

        this->envAlpha += 8;
        if (this->envAlpha > 255) {
            this->envAlpha = 255;
        }

        if (Math_SmoothStepToF(&this->actor.scale.y, 0.008f, 1.0f, 0.0005f, 0.0f) == 0.0f) {
            if (ENFZ_GET_4000(&this->actor)) {
                func_8093389C(this);
            } else {
                func_80933324(this);
            }
        }
    }
}

void func_80933324(EnFz* this) {
    this->state = 1;
    this->mainTimer = 40;
    this->unk_BCC = 1;
    this->isFreezing = true;
    this->actor.flags |= ACTOR_FLAG_ATTENTION_ENABLED;
    this->actor.gravity = -1.0f;
    this->actionFunc = func_80933368;
}

// AimForMove
void func_80933368(EnFz* this, PlayState* play) {
    func_80933014(this);
    if (this->mainTimer == 0) {
        func_809333A4(this);
    }
}

void func_809333A4(EnFz* this) {
    this->state = 1;
    this->isMoving = true;
    this->mainTimer = 100;
    this->speedXZ = 4.0f;
    this->actionFunc = func_809333D8;
}

// MoveTowardPlayer ?
void func_809333D8(EnFz* this, PlayState* play) {
    if ((this->mainTimer == 0) || (! this->isMoving)) {
        func_80933414(this);
    }
}

void func_80933414(EnFz* this) {
    this->state = 1;
    this->speedXZ = 0.0f;
    this->actor.speed = 0.0f;
    this->mainTimer = 40;
    this->actionFunc = func_80933444;
}

// AimForFreeze ?
void func_80933444(EnFz* this, PlayState* play) {
    func_80933014(this);
    if (this->mainTimer == 0) {
        func_80933480(this, play);
    }
}

void func_80933480(EnFz* this, PlayState* play) {
    this->state = 1;
    this->mainTimer = 80;
    this->actionFunc = func_809334B8;
    func_80932784(this, play);
}

// BlowSmoke
void func_809334B8(EnFz* this, PlayState* play) {
    Vec3f vec1;
    Vec3f pos;
    Vec3f velocity;
    Vec3f accel;
    u8 sp3F;
    s16 primAlpha;

    if (this->mainTimer == 0) {
        func_809330D4(this);
        return;
    }

    if (this->mainTimer > 10) {
        sp3F = 0;
        primAlpha = 150;
        Actor_PlaySfx_Flagged(&this->actor, NA_SE_EN_FREEZAD_BREATH - SFX_FLAG);
        if ((this->mainTimer - 10) < 16) {
            primAlpha = (this->mainTimer * 10) - 100;
        }

        accel.x = accel.z = 0.0f;
        accel.y = 0.6f;

        pos.x = this->actor.world.pos.x;
        pos.y = this->actor.world.pos.y + 20.0f;
        pos.z = this->actor.world.pos.z;

        Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_NEW);

        vec1.x = 0.0f;
        vec1.y = -2.0f;
        vec1.z = ((ENFZ_GET_F(&this->actor) == ENFZ_F_1)   ? 10.0f
                  : (ENFZ_GET_F(&this->actor) == ENFZ_F_2) ? 20.0f
                                                           : 0.0f) +
                 20;

        Matrix_MultVec3f(&vec1, &velocity);

        if ((this->mainTimer & 7) == 0) {
            sp3F = 1;
        }

        func_809340BC(this, &pos, &velocity, &accel, 2.0f, 25.0f, primAlpha, sp3F);

        pos.x += velocity.x * 0.5f;
        pos.y += velocity.y * 0.5f;
        pos.z += velocity.z * 0.5f;

        func_809340BC(this, &pos, &velocity, &accel, 2.0f, 25.0f, primAlpha, 0);
    }
}

void func_809336C0(EnFz* this, PlayState* play) {
    this->state = 0;
    this->speedXZ = 0.0f;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.speed = 0.0f;
    this->unk_BCC = 1;
    this->isFreezing = 0;
    this->isDespawning = true;
    this->actor.flags &= ~ACTOR_FLAG_ATTENTION_ENABLED;
    this->unk_BD7 = 0;
    this->mainTimer = 60;
    Actor_ChangeCategory(play, &play->actorCtx, &this->actor, ACTORCAT_PROP);
    Item_DropCollectibleRandom(play, &this->actor, &this->actor.world.pos, 0xA0);
    this->actionFunc = func_80933760;
}

// Despawn
void func_80933760(EnFz* this, PlayState* play) {
    if (this->mainTimer == 0) {
        Actor_Kill(&this->actor);
    }
}


void func_80933790(EnFz* this) {
    this->state = 3;
    this->isFreezing = false;
    this->isDespawning = true;
    this->actor.flags &= ~ACTOR_FLAG_ATTENTION_ENABLED;
    this->actor.speed = 0.0f;
    this->speedXZ = 0.0f;
    this->actionFunc = func_809337D4;
}

// Melt
void func_809337D4(EnFz* this, PlayState* play) {
    Math_StepToF(&this->actor.scale.y, 0.0006f, 0.0006f);

    if (this->actor.scale.y < 0.006f) {
        this->actor.scale.x += 0.001f;
        this->actor.scale.z += 0.001f;
    }

    if (this->actor.scale.y < 0.004f) {
        this->envAlpha -= 20;
        if (this->envAlpha > 255) {
            this->envAlpha = 0;
        }
    }

    if (this->envAlpha == 0) {
        func_809336C0(this, play);
    }
}

void func_8093389C(EnFz* this) {
    this->state = 1;
    this->mainTimer = 40;
    this->unk_BCC = 1;
    this->isFreezing = true;
    this->actor.flags |= ACTOR_FLAG_ATTENTION_ENABLED;
    this->actor.gravity = -1.0f;
    this->actionFunc = func_809338E0;
}

// EnFz_BlowSmokeStationary
void func_809338E0(EnFz* this, PlayState* play) {
    Vec3f vec1;
    Vec3f pos;
    Vec3f velocity;
    Vec3f accel;
    u8 flag;
    s16 primAlpha;

    if (this->counter & 0xC0) {
        func_80933014(this);
        func_80932784(this, play);
        return;
    }

    flag = false;
    primAlpha = 150;
    Actor_PlaySfx_Flagged(&this->actor, NA_SE_EN_FREEZAD_BREATH - SFX_FLAG);

    if ((this->counter & 0x3F) >= 0x30) {
        primAlpha = 630 - ((this->counter & 0x3F) * 10);
    }

    accel.x = accel.z = 0.0f;
    accel.y = 0.6f;

    pos.x = this->actor.world.pos.x;
    pos.y = this->actor.world.pos.y + 20.0f;
    pos.z = this->actor.world.pos.z;

    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_NEW);

    vec1.x = 0.0f;
    vec1.y = -2.0f;
    vec1.z = ((ENFZ_GET_F(&this->actor) == ENFZ_F_1)   ? 10.0f
              : (ENFZ_GET_F(&this->actor) == ENFZ_F_2) ? 20.0f
                                                       : 0.0f) +
             20;

    Matrix_MultVec3f(&vec1, &velocity);

    if (!(this->counter & 7)) {
        flag = true;
    }

    func_809340BC(this, &pos, &velocity, &accel, 2.0f, 25.0f, primAlpha, flag);
    pos.x += velocity.x * 0.5f;
    pos.y += velocity.y * 0.5f;
    pos.z += velocity.z * 0.5f;
    func_809340BC(this, &pos, &velocity, &accel, 2.0f, 25.0f, primAlpha, false);
}

// EnFz_SetupType3
void func_80933AF4(EnFz* this) {
    this->state = 1;
    this->mainTimer = 40;
    this->unk_BCC = 1;
    this->isFreezing = true;
    this->actor.flags |= ACTOR_FLAG_ATTENTION_ENABLED;
    this->actor.gravity = -1.0f;
    this->actionFunc = func_80933B38;
}

// EnFz_Type3
void func_80933B38(EnFz* this, PlayState* play) {
}

void func_80933B48(EnFz* this, PlayState* play) {
    if (this->drawDmgEffTimer != 0) {
        if (this->drawDmgEffTimer > 0) {
            this->drawDmgEffTimer--;
        }

        if (this->drawDmgEffTimer < 20) {
            Math_SmoothStepToF(&this->drawDmgEffScale, 0.0f, 0.5f, 0.03f, 0.0f);
            this->drawDmgEffAlpha = this->drawDmgEffTimer * 0.05f;
        } else {
            Math_SmoothStepToF(&this->drawDmgEffScale, 0.5f, 0.1f, 0.02f, 0.0f);
        }
    }
}

void EnFz_Update(Actor* thisx, PlayState* play) {
    static EnFzUnkFunc sIceSmokeSpawnFunctions[] = { func_80932AE8, func_80932AF4, func_80932BD4, func_80932BD4 };
    s32 pad;
    EnFz* this = (EnFz*)thisx;

    this->counter++;
    if (this->unusedTimer != 0) {
        this->unusedTimer--;
    }

    if (this->mainTimer != 0) {
        this->mainTimer--;
    }

    if (this->timerBD9 != 0) {
        this->timerBD9--;
    }

    Actor_SetFocus(&this->actor, 50.0f);
    func_80932C98(this, play);

    this->actionFunc(this, play);

    if (! this->isDespawning) {
        Collider_UpdateCylinder(&this->actor, &this->collider1);
        Collider_UpdateCylinder(&this->actor, &this->collider2);
        if (this->isFreezing) {
            if (this->actor.colorFilterTimer == 0) {
                CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider1.base);
                CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider2.base);
            }
            CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider1.base);
        }
    }

    Math_StepToF(&this->actor.speed, this->speedXZ, 0.2f);
    Actor_MoveWithGravity(&this->actor);
    if (this->unk_BCC != 0) {
        Actor_UpdateBgCheckInfo(play, &this->actor, 20.0f, 20.0f, 20.0f, UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_4);
    }

    sIceSmokeSpawnFunctions[this->state](this);
    func_80933B48(this, play);
    func_80934178(this, play);
}

void EnFz_Draw(Actor* thisx, PlayState* play) {
    static Gfx* sDisplayLists[] = { object_fz_DL_001130, object_fz_DL_0021A0, object_fz_DL_002CA0 };
    s32 pad;
    EnFz* this = (EnFz*)thisx;
    s32 dlIndex = 3 - this->actor.colChkInfo.health;

    OPEN_DISPS(play->state.gfxCtx);

    if (this->actor.colChkInfo.health == 0) {
        dlIndex = 2;
    }

    if (this->unk_BD7 != 0) {
        func_800B8118(&this->actor, play, 0);
        Gfx_SetupDL25_Xlu(play->state.gfxCtx);

        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, play->state.frames % 128, 0x20, 0x20, 1, 0,
                                    (play->state.frames * 2) % 128, 0x20, 0x20));
        MATRIX_FINALIZE_AND_LOAD(POLY_XLU_DISP++, play->state.gfxCtx);
        gDPSetCombineLERP(POLY_XLU_DISP++, TEXEL1, PRIMITIVE, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, PRIMITIVE, TEXEL0,
                          PRIMITIVE, ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, ENVIRONMENT, 0);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 155, 255, 255, 255);
        gDPSetEnvColor(POLY_XLU_DISP++, 200, 200, 200, this->envAlpha);
        gSPDisplayList(POLY_XLU_DISP++, sDisplayLists[dlIndex]);
    }

    func_80934464(this, play);

    if (this->drawDmgEffTimer > 0) {
        s32 pad2[6];
        Vec3f bodyPartsPos[2];
        s32 pad3;

        bodyPartsPos[0] = this->actor.world.pos;
        bodyPartsPos[1] = this->actor.world.pos;
        bodyPartsPos[0].y += 20.0f;
        bodyPartsPos[1].y += 40.0f;
        Actor_DrawDamageEffects(play, NULL, bodyPartsPos, ARRAY_COUNT(bodyPartsPos), this->drawDmgEffScale * 4.0f, 0.5f,
                                this->drawDmgEffAlpha, ACTOR_DRAW_DMGEFF_LIGHT_ORBS);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

// SpawnIceSmokeNoFreeze
void func_80934018(EnFz* this, Vec3f* pos, Vec3f* velocity, Vec3f* accel, f32 xyScale) {
    s16 i;
    EnFzEffect* effect = &this->effects[0];

    for (i = 0; i < ARRAY_COUNT(this->effects); i++, effect++) {
        if (effect->type == 0) {
            effect->type = 1;
            effect->pos = *pos;
            effect->velocity = *velocity;
            effect->accel = *accel;
            effect->primAlphaState = 0;
            effect->xyScale = xyScale / 1000.0f;
            effect->primAlpha = 0;
            effect->timer = 0;
            break;
        }
    }
}

// SpawnIceSmokeFreeze
void func_809340BC(EnFz* this, Vec3f* pos, Vec3f* velocity, Vec3f* accel,
     f32 xyScale, f32 xyScaleTarget, s16 primAlpha, u8 arg7) {
    s16 i;
    EnFzEffect* effect = &this->effects[0];

    for (i = 0; i < ARRAY_COUNT(this->effects); i++, effect++) {
        if (effect->type == 0) {
            effect->type = 2;
            effect->pos = *pos;
            effect->velocity = *velocity;
            effect->accel = *accel;
            effect->primAlphaState = 0;
            effect->xyScale = xyScale / 1000.0f;
            effect->xyScaleTarget = xyScaleTarget / 1000.0f;
            effect->primAlpha = primAlpha;
            effect->timer = 0;
            effect->unk_38 = arg7;
            break;
        }
    }
}

// UpdateIceSmoke
void func_80934178(EnFz* this, PlayState* play) {
    s16 i;
    EnFzEffect* effect = this->effects;
    Vec3f pos;

    for (i = 0; i < ARRAY_COUNT(this->effects); i++, effect++) {
        if (effect->type != 0) {
            effect->pos.x += effect->velocity.x;
            effect->pos.y += effect->velocity.y;
            effect->pos.z += effect->velocity.z;

            effect->timer++;

            effect->velocity.x += effect->accel.x;
            effect->velocity.y += effect->accel.y;
            effect->velocity.z += effect->accel.z;

            if (effect->type == 1) {
                if (effect->primAlphaState == 0) {
                    effect->primAlpha += 10;
                    if (effect->primAlpha >= 100) {
                        effect->primAlphaState++;
                    }
                } else {
                    effect->primAlpha -= 3;
                    if (effect->primAlpha <= 0) {
                        effect->primAlpha = 0;
                        effect->type = 0;
                    }
                }
            } else if (effect->type == 2) {
                Math_ApproachF(&effect->xyScale, effect->xyScaleTarget, 0.1f, effect->xyScaleTarget / 10.0f);
                if (effect->primAlphaState == 0) {
                    if (effect->timer >= 7) {
                        effect->primAlphaState++;
                    }
                } else {
                    effect->velocity.x *= 0.75f;
                    effect->accel.y = 2.0f;
                    effect->velocity.z *= 0.75f;
                    effect->primAlpha -= 17;
                    if (effect->primAlpha <= 0) {
                        effect->primAlpha = 0;
                        effect->type = 0;
                    }
                }

                if ((this->timerBD9 == 0) && (effect->primAlpha > 100) && (effect->unk_38 != 0)) {
                    this->collider3.dim.pos.x = effect->pos.x;
                    this->collider3.dim.pos.y = effect->pos.y;
                    this->collider3.dim.pos.z = effect->pos.z;
                    CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider3.base);
                }

                pos.x = effect->pos.x;
                pos.y = effect->pos.y + 10.0f;
                pos.z = effect->pos.z;

                if ((effect->primAlphaState != 2) && func_809328A4(this, &pos)) {
                    effect->primAlphaState = 2;
                    effect->velocity.x = 0.0f;
                    effect->velocity.z = 0.0f;
                }
            }
        }
    }
}


//  DrawEffects
void func_80934464(EnFz* this, PlayState* play) {
    GraphicsContext* gfxCtx = play->state.gfxCtx;
    s16 i;
    u8 materialFlag = 0;
    EnFzEffect* effect = this->effects;

    OPEN_DISPS(gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);

    gDPSetColorDither(POLY_XLU_DISP++, G_CD_BAYER);
    gDPSetAlphaDither(POLY_XLU_DISP++, G_AD_PATTERN);

    for (i = 0; i < ARRAY_COUNT(this->effects); i++, effect++) {
        if (effect->type > 0) {
            gDPPipeSync(POLY_XLU_DISP++);

            if (materialFlag == 0) {
                gSPDisplayList(POLY_XLU_DISP++, gFrozenSteamMaterialDL);
                materialFlag++;
            }

            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 195, 225, 235, effect->primAlpha);
            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(play->state.gfxCtx, 0, (effect->timer + (i * 3)) * 3,
                                        (effect->timer + (i * 3)) * 15, 0x20, 0x40, 1, 0, 0, 0x20, 0x20));

            Matrix_Translate(effect->pos.x, effect->pos.y, effect->pos.z, MTXMODE_NEW);
            Matrix_ReplaceRotation(&play->billboardMtxF);
            Matrix_Scale(effect->xyScale, effect->xyScale, 1.0f, MTXMODE_APPLY);

            MATRIX_FINALIZE_AND_LOAD(POLY_XLU_DISP++, gfxCtx);
            gSPDisplayList(POLY_XLU_DISP++, gFrozenSteamModelDL);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
