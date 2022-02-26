/*
 * File: z_en_crow.c
 * Overlay: ovl_En_Crow
 * Description: Guay
 */

#include "z_en_crow.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_1000 | ACTOR_FLAG_4000)

#define THIS ((EnCrow*)thisx)

void EnCrow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnCrow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnCrow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnCrow_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_8099AC58(EnCrow* this);
void func_8099AC8C(EnCrow* this, GlobalContext* globalCtx);
void func_8099B098(EnCrow* this);
void func_8099B0CC(EnCrow* this, GlobalContext* globalCtx);
void func_8099B318(EnCrow* this, GlobalContext* globalCtx);
void func_8099B584(EnCrow* this, GlobalContext* globalCtx);
void func_8099B6AC(EnCrow* this);
void func_8099B6C4(EnCrow* this, GlobalContext* globalCtx);
void func_8099B8EC(EnCrow* this);
void func_8099B838(EnCrow* this, GlobalContext* globalCtx);
void func_8099B9E8(EnCrow* this, GlobalContext* globalCtx);

const ActorInit En_Crow_InitVars = {
    ACTOR_EN_CROW,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_CROW,
    sizeof(EnCrow),
    (ActorFunc)EnCrow_Init,
    (ActorFunc)EnCrow_Destroy,
    (ActorFunc)EnCrow_Update,
    (ActorFunc)EnCrow_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_8099C070[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_HARD,
            BUMP_ON,
            OCELEM_ON,
        },
        { 1, { { 0, 0, 0 }, 20 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_8099C094 = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    1,
    D_8099C070, // sJntSphElementsInit,
};

// sColChkInfoInit
static CollisionCheckInfoInit D_8099C0A4 = { 1, 15, 30, 30 };

// static DamageTable sDamageTable = {
static DamageTable D_8099C0AC = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

static s32 D_8099C0CC = 0;

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8099C0D0[] = {
    ICHAIN_F32(uncullZoneForward, 3000, ICHAIN_CONTINUE),
    ICHAIN_S8(hintId, 88, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -500, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_STOP),
};

extern ColliderJntSphElementInit D_8099C070[1];
extern ColliderJntSphInit D_8099C094;
extern CollisionCheckInfoInit D_8099C0A4;
extern DamageTable D_8099C0AC;
extern InitChainEntry D_8099C0D0[];

void EnCrow_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnCrow* this = THIS;

    Actor_ProcessInitChain(&this->actor, D_8099C0D0);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_crow_Skel_0010C0, &object_crow_Anim_0000F0,
                       this->jointTable, this->morphTable, 9);
    Collider_InitAndSetJntSph(globalCtx, &this->collider, &this->actor, &D_8099C094, &this->unk220);
    this->collider.elements->dim.worldSphere.radius = D_8099C094.elements[0].dim.modelSphere.radius;
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &D_8099C0AC, &D_8099C0A4);
    ActorShape_Init(&this->actor.shape, 2000.0f, ActorShadow_DrawCircle, 20.0f);
    D_8099C0CC = 0;
    if (this->actor.parent != 0) {
        this->actor.flags &= -2;
    }
    func_8099AC58(this);
}

void EnCrow_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnCrow* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void func_8099AC58(EnCrow* this) {
    this->timer = 100;
    this->collider.base.acFlags |= 1;
    this->actionFunc = func_8099AC8C;
    this->skelAnime.playSpeed = 1.0f;
}

void func_8099AC8C(EnCrow* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 sp38;
    s32 skelanimeUpdated;
    s16 temp;

    SkelAnime_Update(&this->skelAnime);
    skelanimeUpdated = Animation_OnFrame(&this->skelAnime, 0.0f);
    this->actor.speedXZ = (Rand_ZeroOne() * 1.5f) + 3.0f;

    if ((this->actor.parent != NULL) && ((this->actor.parent->home.rot.z) == 0)) {
        this->actor.home.pos.x = this->actor.parent->world.pos.x;
        this->actor.home.pos.z = this->actor.parent->world.pos.z;
        sp38 = Actor_XZDistanceToPoint(&this->actor, &this->actor.parent->world.pos);
    } else {
        sp38 = 450.0f;
        this->actor.flags |= 1;
    }

    if ((this->actor.bgCheckFlags & 8) != 0) {
        this->unk192 = this->actor.wallYaw;
    } else if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) > 300.0f) {
        this->unk192 = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    }

    if ((Math_SmoothStepToS(&this->actor.shape.rot.y, this->unk192, 5, 0x300, (s16)0x10) == 0) && (skelanimeUpdated) &&
        (Rand_ZeroOne() < 0.1f)) {

        temp = (Actor_YawToPoint(&this->actor, &this->actor.home.pos) - this->actor.shape.rot.y);
        if (temp > 0) {
            this->unk192 += Rand_S16Offset(0x1000, 0x1000);
        } else {
            this->unk192 -= Rand_S16Offset(0x1000, 0x1000);
        }
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_KAICHO_CRY);
    }

    if ((this->actor.depthInWater > -40.0f) || ((this->actor.bgCheckFlags & 1) != 0)) {
        this->unk190 = -0x1000;
    } else if (this->actor.world.pos.y < (this->actor.home.pos.y - 50.0f)) {
        this->unk190 = -Rand_S16Offset(0x800, 0x800);
    } else if (this->actor.world.pos.y > (this->actor.home.pos.y + 50.0f)) {
        this->unk190 = Rand_S16Offset(0x800, 0x800);
    }

    if ((Math_SmoothStepToS(&this->actor.shape.rot.x, this->unk190, 0xA, 0x100, 8) == 0) && skelanimeUpdated &&
        (Rand_ZeroOne() < 0.1f)) {
        if (this->actor.home.pos.y < this->actor.world.pos.y) {
            this->unk190 -= Rand_S16Offset(0x400, 0x400);
        } else {
            this->unk190 += Rand_S16Offset(0x400, 0x400);
        }

        this->unk190 = CLAMP(this->unk190, -0x1000, 0x1000);
    }

    if ((this->actor.bgCheckFlags & 1) != 0) {
        Math_ScaledStepToS(&this->actor.shape.rot.x, -0x100, 0x400);
    }

    DECR(this->timer);
    if ((this->timer == 0) &&
        (((this->actor.xzDistToPlayer < 300.0f) && !(player->stateFlags1 & 0x800000)) || (sp38 < 300.0f)) &&
        (this->actor.depthInWater < -40.0f) && (Player_GetMask(globalCtx) != PLAYER_MASK_STONE)) {
        if (sp38 < this->actor.xzDistToPlayer) {
            this->actor.child = this->actor.parent;
        } else {
            this->actor.child = &player->actor;
        }
        func_8099B098(this);
    }
}

void func_8099B098(EnCrow* this) {
    this->timer = 0x12C;
    this->actionFunc = func_8099B0CC;
    this->actor.speedXZ = 4.0f;
    this->skelAnime.playSpeed = 2.0f;
}

void func_8099B0CC(EnCrow* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 facingPlayer;
    Vec3f pos;
    s16 target;
    s16 phi_a1;

    SkelAnime_Update(&this->skelAnime);
    DECR(this->timer);
    facingPlayer = Actor_ActorAIsFacingActorB(&this->actor, this->actor.child, 0x2800);
    if (facingPlayer) {
        if (&player->actor == this->actor.child) {
            pos.y = this->actor.child->world.pos.y + 20.0f;
        } else {
            pos.y = this->actor.child->world.pos.y + 40.0f;
        }
        pos.x = this->actor.child->world.pos.x;
        pos.z = this->actor.child->world.pos.z;
        target = Actor_PitchToPoint(&this->actor, &pos);
        phi_a1 = CLAMP(target, -0x3000, 0x3000);
        Math_SmoothStepToS(&this->actor.shape.rot.x, phi_a1, 2, 0x400, (s16)0x40);
    } else {
        Math_SmoothStepToS(&this->actor.shape.rot.x, -0x800, 2, 0x100, (s16)0x10);
    }

    if ((facingPlayer) || (Actor_XZDistanceBetweenActors(&this->actor, this->actor.child) > 80.0f)) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, Actor_YawBetweenActors(&this->actor, this->actor.child), 4, 0xC00,
                           0xC0);
    }
    if (((this->timer == 0) || (((&player->actor) != this->actor.child) && (this->actor.child->home.rot.z != 0)) ||
         (&player->actor == this->actor.child) &&
             ((Player_GetMask(globalCtx) == PLAYER_MASK_STONE) || (player->stateFlags1 & 0x800000)) ||
         (this->collider.base.atFlags & 2) || (this->actor.bgCheckFlags & 9)) ||
        this->actor.depthInWater > (-40.0f)) {

        if (this->collider.base.atFlags & AT_HIT) {
            this->collider.base.atFlags &= ~AT_HIT;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_KAICHO_ATTACK);
        }
        func_8099AC58(this);
    }
}

void func_8099B318(EnCrow* this, GlobalContext* globalCtx) {
    if (this->unk18C == 0xA) {
        this->unk18C = 0;
        this->unk290 = 0.0f;
        Actor_SpawnIceEffects(globalCtx, &this->actor, this->unk260, 4, 2, 0.2f, 0.2f);
    }
}

void func_8099B384(EnCrow* this, GlobalContext* globalCtx) {
    f32 temp;

    this->actor.speedXZ *= Math_CosS(this->actor.world.rot.x);
    this->actor.velocity.y = 0.0f;
    Animation_Change(&this->skelAnime, &object_crow_Anim_0000F0, 0.4f, 0.0f, 0.0f, 1, -3.0f);
    this->actor.shape.yOffset = 0.0f;
    this->actor.targetArrowOffset = 0.0f;
    this->actor.bgCheckFlags &= ~1;
    temp = (this->actor.scale.x * 100.0f);
    this->actor.world.pos.y += 20.0f * temp;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_KAICHO_DEAD);
    if (this->actor.colChkInfo.damageEffect == 3) {
        this->unk18C = 0xA;
        this->unk290 = 1.0f;
        this->unk298 = 0.75f;
        this->unk294 = 0.5f;
    } else if (this->actor.colChkInfo.damageEffect == 4) {
        this->unk18C = 0x14;
        this->unk290 = 4.0f;
        this->unk294 = 0.5f;
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xA2, this->collider.elements->info.bumper.hitPos.x,
                    this->collider.elements->info.bumper.hitPos.y, this->collider.elements->info.bumper.hitPos.z, 0, 0,
                    0, 3);
    } else if (this->actor.colChkInfo.damageEffect == 2) {
        this->unk18C = 0;
        this->unk290 = 4.0f;
        this->unk294 = 0.5f;
    }
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 0x28);
    if ((this->actor.flags & 0x8000) != 0) {
        this->actor.speedXZ = 0.0f;
    }
    this->collider.base.acFlags &= ~1;
    this->actor.flags |= 0x10;

    this->actionFunc = func_8099B584;
}

void func_8099B584(EnCrow* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
    this->actor.colorFilterTimer = 40;

    if (!(this->actor.flags & 0x8000)) {
        if (this->unk18C != 0xA) {
            Math_ScaledStepToS(&this->actor.shape.rot.x, 0x4000, 0x200);
            this->actor.shape.rot.z += 0x1780;
        }
        if ((this->actor.bgCheckFlags & 1) || (this->actor.floorHeight == BGCHECK_Y_MIN)) {
            func_8099B318(this, globalCtx);
            func_800B3030(globalCtx, &this->actor.world.pos, &gZeroVec3f, &gZeroVec3f, this->actor.scale.x * 10000.0f,
                          0, 0);
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 0xBU, NA_SE_EN_EXTINCT);

            if (this->actor.parent != NULL) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            func_8099B6AC(this);
        }
    }
}

void func_8099B6AC(EnCrow* this) {
    this->actor.colorFilterTimer = 0;
    this->actionFunc = func_8099B6C4;
}

void func_8099B6C4(EnCrow* this, GlobalContext* globalCtx) {
    f32 stepScale;

    if (this->actor.params != 0) {
        stepScale = 0.006f;
    } else {
        stepScale = 0.002f;
    }
    if (Math_StepToF(&this->actor.scale.x, 0.0f, stepScale) != 0) {
        if (this->actor.params == 0) {
            D_8099C0CC++;
            Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0x80);
        } else {
            Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0x90);
        }
        func_8099B8EC(this);
    }
    this->actor.scale.z = this->actor.scale.y = this->actor.scale.x;
}

void func_8099B778(EnCrow* this) {
    this->timer = 0x64;
    this->unk190 = -0x1000;
    this->actor.speedXZ = 3.5f;
    this->unk192 = this->actor.yawTowardsPlayer + 0x8000;
    this->skelAnime.playSpeed = 2.0f;
    if (this->actor.colChkInfo.damageEffect == 1) {
        Actor_SetColorFilter(&this->actor, 0, 255, 0, 40);
    } else {
        Actor_SetColorFilter(&this->actor, 0, 255, 0, 40);
    }
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
    this->actionFunc = func_8099B838;
}

void func_8099B838(EnCrow* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if ((this->actor.bgCheckFlags & 8) != 0) {
        this->unk192 = this->actor.wallYaw;
    } else {
        this->unk192 = this->actor.yawTowardsPlayer + 0x8000;
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->unk192, 3, 0xC00, 0xC0);
    Math_SmoothStepToS(&this->actor.shape.rot.x, this->unk190, 5, 0x100, 0x10);
    DECR(this->timer);
    if (this->timer == 0) {
        func_8099AC58(this);
    }
}

void func_8099B8EC(EnCrow* this) {
    if (D_8099C0CC == 0xA) {
        this->actor.params = 1;
        D_8099C0CC = 0;
        this->collider.elements->dim.worldSphere.radius =
            (D_8099C094.elements->dim.modelSphere.radius * 0.03f * 100.0f);
    } else {
        this->actor.params = 0;
        this->collider.elements->dim.worldSphere.radius = D_8099C094.elements->dim.modelSphere.radius;
    }
    Animation_PlayLoop(&this->skelAnime, &object_crow_Anim_0000F0);
    Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.home.pos);
    this->actor.shape.rot.x = 0;
    this->actor.shape.rot.z = 0;
    this->timer = 0x12C;
    this->actor.draw = NULL;
    this->actor.shape.yOffset = 2000.0f;
    this->actionFunc = func_8099B9E8;
    this->actor.targetArrowOffset = (f32)(2000); // Possible bug with the float here
    this->unk290 = 0.0f;
}

void func_8099B9E8(EnCrow* this, GlobalContext* globalCtx) {
    f32 phi_f0;

    DECR(this->timer);
    if (this->timer == 0) {
        SkelAnime_Update(&this->skelAnime);
        this->actor.draw = EnCrow_Draw;
        if (this->actor.params != 0) {
            phi_f0 = 0.03f;
        } else {
            phi_f0 = 0.01f;
        }
        if (Math_StepToF(&this->actor.scale.x, phi_f0, phi_f0 * 0.1f)) {
            this->actor.flags |= 1;
            this->actor.flags &= ~0x10;
            this->actor.colChkInfo.health = 1;
            func_8099AC58(this);
        }
        this->actor.scale.y = this->actor.scale.x;
        this->actor.scale.z = this->actor.scale.x;
    }
}

void func_8099BAB4(EnCrow* this, GlobalContext* globalCtx) {

    if (this->collider.base.acFlags & 2) {
        this->collider.base.acFlags &= ~AT_HIT;
        Actor_SetDropFlag(&this->actor, &this->collider.elements->info);

        if (this->actor.colChkInfo.damageEffect == 1) {
            func_8099B778(this);

        } else if (this->actor.colChkInfo.damageEffect == 5) {
            this->unk18C = 0x1F;
            this->unk290 = 2.0f;
            this->unk294 = 0.5f;
            func_8099B778(this);

        } else {
            this->actor.colChkInfo.health = 0;
            this->actor.flags &= -2;
            Enemy_StartFinishingBlow(globalCtx, &this->actor);
            func_8099B384(this, globalCtx);
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/EnCrow_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099BE48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099BF20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/EnCrow_Draw.s")
