/*
 * File: z_en_bat.c
 * Overlay: ovl_En_Bat
 * Description: Bad Bat
 */

#include "z_en_bat.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_1000 | ACTOR_FLAG_4000)

#define THIS ((EnBat*)thisx)

#define BAD_BAT_FLAP_FRAME 5

void EnBat_Init(Actor* thisx, PlayState* play);
void EnBat_Destroy(Actor* thisx, PlayState* play);
void EnBat_Update(Actor* thisx, PlayState* play);
void EnBat_Draw(Actor* thisx, PlayState* play);

s32 EnBat_IsGraveyardOnSecondDay(PlayState* play);
void func_80A43870(EnBat* this);
void func_80A438D4(EnBat* this, PlayState* play);
void func_80A438F8(EnBat* this);
void func_80A4392C(EnBat* this, PlayState* play);
void func_80A43CA0(EnBat* this);
void func_80A43CE8(EnBat* this, PlayState* play);
void func_80A44114(EnBat* this, PlayState* play);
void func_80A4431C(EnBat* this, PlayState* play);

const ActorInit En_Bat_InitVars = {
    ACTOR_EN_BAT,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BAT,
    sizeof(EnBat),
    (ActorFunc)EnBat_Init,
    (ActorFunc)EnBat_Destroy,
    (ActorFunc)EnBat_Update,
    (ActorFunc)EnBat_Draw,
};

static ColliderSphereInit sSphereInit = {
    {
        COLTYPE_HIT3,
        AT_NONE | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_SPHERE,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x04 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_HARD,
        BUMP_ON,
        OCELEM_ON,
    },
    { 1, { { 0, 0, 0 }, 15 }, 100 },
};

typedef enum {
    /* 0 */ BAD_BAT_DMGEFF_NONE,
    /* 1 */ BAD_BAT_DMGEFF_NUT,
    /* 2 */ BAD_BAT_DMGEFF_FIRE,
    /* 3 */ BAD_BAT_DMGEFF_ICE,
    /* 4 */ BAD_BAT_DMGEFF_LIGHT,
    /* 5 */ BAD_BAT_DMGEFF_ELECTRIC
} BatDamageEffect;

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, BAD_BAT_DMGEFF_NUT),
    /* Deku Stick     */ DMG_ENTRY(1, BAD_BAT_DMGEFF_NONE),
    /* Horse trample  */ DMG_ENTRY(1, BAD_BAT_DMGEFF_NONE),
    /* Explosives     */ DMG_ENTRY(1, BAD_BAT_DMGEFF_NONE),
    /* Zora boomerang */ DMG_ENTRY(1, BAD_BAT_DMGEFF_NONE),
    /* Normal arrow   */ DMG_ENTRY(1, BAD_BAT_DMGEFF_NONE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, BAD_BAT_DMGEFF_NONE),
    /* Hookshot       */ DMG_ENTRY(1, BAD_BAT_DMGEFF_NONE),
    /* Goron punch    */ DMG_ENTRY(1, BAD_BAT_DMGEFF_NONE),
    /* Sword          */ DMG_ENTRY(1, BAD_BAT_DMGEFF_NONE),
    /* Goron pound    */ DMG_ENTRY(1, BAD_BAT_DMGEFF_NONE),
    /* Fire arrow     */ DMG_ENTRY(2, BAD_BAT_DMGEFF_FIRE),
    /* Ice arrow      */ DMG_ENTRY(2, BAD_BAT_DMGEFF_ICE),
    /* Light arrow    */ DMG_ENTRY(2, BAD_BAT_DMGEFF_LIGHT),
    /* Goron spikes   */ DMG_ENTRY(1, BAD_BAT_DMGEFF_NONE),
    /* Deku spin      */ DMG_ENTRY(1, BAD_BAT_DMGEFF_NONE),
    /* Deku bubble    */ DMG_ENTRY(1, BAD_BAT_DMGEFF_NONE),
    /* Deku launch    */ DMG_ENTRY(2, BAD_BAT_DMGEFF_NONE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, BAD_BAT_DMGEFF_NUT),
    /* Zora barrier   */ DMG_ENTRY(0, BAD_BAT_DMGEFF_ELECTRIC),
    /* Normal shield  */ DMG_ENTRY(0, BAD_BAT_DMGEFF_NONE),
    /* Light ray      */ DMG_ENTRY(0, BAD_BAT_DMGEFF_NONE),
    /* Thrown object  */ DMG_ENTRY(1, BAD_BAT_DMGEFF_NONE),
    /* Zora punch     */ DMG_ENTRY(1, BAD_BAT_DMGEFF_NONE),
    /* Spin attack    */ DMG_ENTRY(1, BAD_BAT_DMGEFF_NONE),
    /* Sword beam     */ DMG_ENTRY(0, BAD_BAT_DMGEFF_NONE),
    /* Normal Roll    */ DMG_ENTRY(0, BAD_BAT_DMGEFF_NONE),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, BAD_BAT_DMGEFF_NONE),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, BAD_BAT_DMGEFF_NONE),
    /* Unblockable    */ DMG_ENTRY(0, BAD_BAT_DMGEFF_NONE),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, BAD_BAT_DMGEFF_NONE),
    /* Powder Keg     */ DMG_ENTRY(1, BAD_BAT_DMGEFF_NONE),
};

static CollisionCheckInfoInit sColChkInfoInit = { 1, 15, 30, 10 };

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, 96, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 3000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -500, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_STOP),
};

Gfx* D_80A44A64[] = {
    0x060001B0, 0x060002A0, 0x06000390, 0x06000480, 0x06000570, 0x06000660, 0x06000750, 0x06000840, 0x06000930,
};

s32 D_80A44C70;
s32 sAlreadySpawned;

extern Gfx D_060000A0[];
extern Gfx D_060000C8[];

void EnBat_Init(Actor* thisx, PlayState* play) {
    EnBat* this = (EnBat*)thisx;

    Actor_ProcessInitChain(thisx, sInitChain);
    Collider_InitAndSetSphere(play, &this->collider, thisx, &sSphereInit);
    this->collider.dim.worldSphere.radius = sSphereInit.dim.modelSphere.radius;
    CollisionCheck_SetInfo(&thisx->colChkInfo, &sDamageTable, &sColChkInfoInit);
    ActorShape_Init(&thisx->shape, 2000.0f, ActorShadow_DrawCircle, 25.0f);

    this->animationFrame = Rand_ZeroOne() * 9.0f;
    this->paramsE0 = BAD_BAT_GET_E0(thisx);
    this->switchFlag = BAD_BAT_GET_SWITCHFLAG(thisx);
    thisx->params = BAD_BAT_GET_TYPE(thisx);

    thisx->depthInWater = -32000.0f;
    Actor_SetFocus(thisx, 20.0f);

    if (sAlreadySpawned) {
        Actor_MarkForDeath(thisx);
    } else if (EnBat_IsGraveyardOnSecondDay(play)) {
        if (Flags_GetSwitch(play, this->switchFlag)) {
            Actor_MarkForDeath(thisx);
        } else {
            this->actor.room = -1;
        }
    }

    if (this->paramsE0 & 4) {
        thisx->params = 0;
        func_80A43870(this);
    } else {
        if (thisx->params == 0x1F) {
            thisx->params = 0;
        }
        func_80A438F8(this);
        while (thisx->params >= 2) {
            Actor_SpawnAsChildAndCutscene(&play->actorCtx, play, ACTOR_EN_BAT,
                                          thisx->world.pos.x + randPlusMinusPoint5Scaled(200.0f),
                                          thisx->world.pos.y + randPlusMinusPoint5Scaled(100.0f),
                                          thisx->world.pos.z + randPlusMinusPoint5Scaled(200.0f),
                                          randPlusMinusPoint5Scaled((f32)0x2000), Rand_ZeroOne() * ((f32)0xFFFF), 0,
                                          BAD_BAT_PARAMS(this->switchFlag, this->paramsE0, 0), -1, thisx->unk20, NULL);
            thisx->params--;
        }
    }
}

void EnBat_Destroy(Actor* thisx, PlayState* play) {
    EnBat* this = THIS;

    Collider_DestroySphere(play, &this->collider);
}

s32 EnBat_IsGraveyardOnSecondDay(PlayState* play) {
    if ((CURRENT_DAY == 2) && (play->sceneNum == SCENE_BOTI)) {
        return true;
    } else {
        return false;
    }
}

void EnBat_StepAnimation(EnBat* this, s32 frameStep) {
    s32 previousFrame = this->animationFrame;

    this->animationFrame += frameStep;
    if (this->animationFrame >= ARRAY_COUNT(D_80A44A64)) {
        this->animationFrame -= ARRAY_COUNT(D_80A44A64);
    }
    if ((previousFrame < BAD_BAT_FLAP_FRAME) && (this->animationFrame >= BAD_BAT_FLAP_FRAME)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FFLY_FLY);
    }
}

// Action functions

void func_80A43870(EnBat* this) {
    this->collider.base.acFlags |= AC_ON;
    this->collider.base.atFlags |= AT_ON;
    this->collider.dim.worldSphere.center.x = this->actor.focus.pos.x;
    this->collider.dim.worldSphere.center.y = this->actor.focus.pos.y;
    this->collider.dim.worldSphere.center.z = this->actor.focus.pos.z;
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_80A438D4;
}

void func_80A438D4(EnBat* this, PlayState* play) {
    EnBat_StepAnimation(this, 1);
}

void func_80A438F8(EnBat* this) {
    this->timer = 100;
    this->collider.base.acFlags |= AC_ON;
    this->actor.speedXZ = 3.5f;
    this->actionFunc = func_80A4392C;
}

void func_80A4392C(EnBat* this, PlayState* play) {
    s32 finishedRotStep;

    EnBat_StepAnimation(this, 1);

    finishedRotStep = Math_ScaledStepToS(&this->actor.shape.rot.y, this->targetYaw, 0x300);

    if (this->actor.bgCheckFlags & 8) {
        this->actor.bgCheckFlags &= ~8;
        this->targetYaw = this->actor.wallYaw;
    } else if (Math3D_XZDistanceSquared(this->actor.world.pos.x, this->actor.world.pos.z, this->actor.home.pos.x,
                                        this->actor.home.pos.z) > 90000.0f) {
        this->targetYaw = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    } else if (finishedRotStep && (Rand_ZeroOne() < 0.015f)) {
        this->targetYaw =
            (((s32)(4096.0f * Rand_ZeroOne()) + 0x1000) * ((Rand_ZeroOne() < 0.5f) ? -1 : 1)) + this->actor.shape.rot.y;
    }

    finishedRotStep = Math_ScaledStepToS(&this->actor.shape.rot.x, this->targetPitch, 0x100);

    if ((this->actor.bgCheckFlags & 1) || (this->actor.depthInWater > -40.0f)) {
        this->targetPitch = -0x1000;
    } else if (this->actor.world.pos.y < (this->actor.home.pos.y - 100.0f)) {
        this->targetPitch = -(s32)(Rand_ZeroOne() * 2048.0f) - 0x800;
    } else if ((this->actor.home.pos.y + 100.0f) < this->actor.world.pos.y) {
        this->targetPitch = (s32)(Rand_ZeroOne() * 2048.0f) + 0x800;
    } else if ((finishedRotStep) && (Rand_ZeroOne() < 0.015f)) {
        this->targetPitch += (s16)(((s32)(1024.0f * Rand_ZeroOne()) + 0x400) * ((Rand_ZeroOne() < 0.5f) ? -1 : 1));
        this->targetPitch = CLAMP(this->targetPitch, -0x1000, 0x1000);
    }

    if (this->timer != 0) {
        this->timer--;
    }
    if ((this->actor.xzDistToPlayer < 300.0f) && (this->timer == 0) && (Player_GetMask(play) != PLAYER_MASK_STONE) &&
        (D_80A44C70 < 3) && (!(this->paramsE0 & 2) || (fabsf(this->actor.playerHeightRel) < 150.0f))) {
        func_80A43CA0(this);
    }
}

void func_80A43CA0(EnBat* this) {
    this->collider.base.atFlags |= AT_ON;
    this->timer = 300;
    this->actor.speedXZ = 4.0f;
    D_80A44C70++;
    this->actionFunc = func_80A43CE8;
}

void func_80A43CE8(EnBat* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 facingPlayer;
    Vec3f preyPos;

    EnBat_StepAnimation(this, 2);
    facingPlayer = Actor_IsFacingPlayer(&this->actor, 0x2800);

    if (facingPlayer) {
        s16 targetPitch;

        preyPos.x = player->actor.world.pos.x;
        preyPos.y = player->actor.world.pos.y + 20.0f;
        preyPos.z = player->actor.world.pos.z;

        targetPitch = Actor_PitchToPoint(&this->actor, &preyPos);
        targetPitch = CLAMP(targetPitch, -0x3000, 0x3000);
        Math_SmoothStepToS(&this->actor.shape.rot.x, targetPitch, 2, 0x400, 0x40);
    } else {
        Math_SmoothStepToS(&this->actor.shape.rot.x, -0x800, 2, 0x100, 0x10);
    }
    if (facingPlayer || (this->actor.xzDistToPlayer > 80.0f)) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 0xC00, 0xC0);
    }

    this->timer--;

    if ((this->timer == 0) || (this->collider.base.atFlags & AT_HIT) || (Player_GetMask(play) == PLAYER_MASK_STONE) ||
        (this->actor.bgCheckFlags & 1) || (player->stateFlags1 & 0x800000) || (this->actor.depthInWater > -40.0f)) {
        if (this->collider.base.atFlags & AT_HIT) {
            this->collider.base.atFlags &= ~AT_HIT;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FFLY_ATTACK);
        }
        this->collider.base.atFlags &= ~AT_ON;
        D_80A44C70--;
        func_80A438F8(this);
    } else if (this->actor.bgCheckFlags & 8) {
        if (ABS_ALT(BINANG_SUB(this->actor.wallYaw, this->actor.yawTowardsPlayer)) > 0x6800) {
            D_80A44C70--;
            this->collider.base.atFlags &= ~AT_ON;
            this->actor.bgCheckFlags &= ~8;
            this->targetYaw = this->actor.wallYaw;
            func_80A438F8(this);
        }
    }
}

// Update-related functions

void func_80A43F60(EnBat* this, PlayState* play) {
    this->actor.flags &= ~ACTOR_FLAG_1;
    Enemy_StartFinishingBlow(play, &this->actor);
    this->actor.speedXZ *= Math_CosS(this->actor.world.rot.x);
    this->actor.bgCheckFlags &= ~1;
    this->actor.velocity.y = 0.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FFLY_DEAD);

    if (this->actor.colChkInfo.damageEffect == BAD_BAT_DMGEFF_ICE) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX;
        this->drawDmgEffAlpha = 1.0f;
        this->drawDmgEffFrozenSteamScale = 60.0f * (0.45f / 40.0f);
        this->drawDmgEffScale = 0.45f;
    } else if (this->actor.colChkInfo.damageEffect == BAD_BAT_DMGEFF_LIGHT) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
        this->drawDmgEffAlpha = 4.0f;
        this->drawDmgEffScale = 0.45f;
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->collider.info.bumper.hitPos.x,
                    this->collider.info.bumper.hitPos.y, this->collider.info.bumper.hitPos.z, 0, 0, 0,
                    CLEAR_TAG_SMALL_LIGHT_RAYS);
    } else if (this->actor.colChkInfo.damageEffect == BAD_BAT_DMGEFF_FIRE) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->drawDmgEffAlpha = 4.0f;
        this->drawDmgEffScale = 0.45f;
    }

    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 40);

    if (this->actor.flags & ACTOR_FLAG_8000) {
        this->actor.speedXZ = 0.0f;
    }

    this->collider.base.acFlags &= ~AC_ON;
    this->actor.flags |= ACTOR_FLAG_10;
    this->actionFunc = func_80A44114;
}

void func_80A44114(EnBat* this, PlayState* play) {
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
    this->actor.colorFilterTimer = 40;
    if (!(this->actor.flags & ACTOR_FLAG_8000)) {
        if (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
            Math_ScaledStepToS(&this->actor.shape.rot.x, 0x4000, 0x200);
            this->actor.shape.rot.z += 0x1780;
        }

        if ((this->actor.bgCheckFlags & 1) || (this->actor.floorHeight == -32000.0f)) {
            if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
                Actor_SpawnIceEffects(play, &this->actor, this->bodyPartPoss, ARRAY_COUNT(this->bodyPartPoss), 2, 0.2f,
                                      0.2f);
            }

            func_800B3030(play, &this->actor.world.pos, &gZeroVec3f, &gZeroVec3f, 100, 0, 0);
            SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 11, NA_SE_EN_EXTINCT);
            Actor_MarkForDeath(&this->actor);

            if (this->actor.room == -1) {
                Actor* actor = NULL;

                do {
                    actor = SubS_FindActor(play, actor, ACTORCAT_ENEMY, ACTOR_EN_BAT);
                    if (actor != NULL) {
                        if (actor == &this->actor) {
                            actor = actor->next;
                        } else {
                            break;
                        }
                    }
                } while (actor != NULL);

                if (actor == NULL) {
                    Flags_SetSwitch(play, this->switchFlag);
                }
            }
        }
    }
}

void func_80A44294(EnBat* this) {
    if (this->actionFunc != func_80A4431C) {
        this->actor.shape.yOffset = 700.0f;
        this->actor.velocity.y = 0.0f;
        this->actor.speedXZ = 0.0f;
        this->actor.world.pos.y += 13.0f;
    }
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
    Actor_SetColorFilter(&this->actor, 0, 255, 0, this->timer);
    this->actionFunc = func_80A4431C;
}

void func_80A4431C(EnBat* this, PlayState* play) {
    Math_ScaledStepToS(&this->actor.shape.rot.x, 0, 0x100);
    if ((this->actor.bgCheckFlags & 1) || (this->actor.floorHeight == -32000.0f)) {
        if (this->timer != 0) {
            this->timer--;
        }
        if (this->timer == 0) {
            func_80A438F8(this);
        }
    } else {
        this->actor.colorFilterTimer = 40;
        if (this->drawDmgEffAlpha > 0.0f) {
            this->drawDmgEffAlpha = 2.0f;
        }
    }
}

void func_80A443D8(EnBat* this, PlayState* play) {
    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;

        Actor_SetDropFlag(&this->actor, &this->collider.info);
        this->collider.base.atFlags &= ~AT_ON;

        if (this->actionFunc == func_80A43CE8) {
            D_80A44C70--;
        }

        if (this->actor.colChkInfo.damageEffect == BAD_BAT_DMGEFF_ELECTRIC) {
            this->timer = 40;
            this->drawDmgEffType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_LARGE;
            this->drawDmgEffAlpha = 2.0f;
            this->drawDmgEffScale = 0.45f;
            func_80A44294(this);
        } else if (this->actor.colChkInfo.damageEffect == BAD_BAT_DMGEFF_NUT) {
            this->timer = 40;
            func_80A44294(this);
        } else {
            Actor_ApplyDamage(&this->actor);
            func_80A43F60(this, play);
        }
    }
}

void EnBat_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnBat* this = THIS;

    if (this->actor.room == -1) {
        sAlreadySpawned = true;
    }

    func_80A443D8(this, play);
    this->actionFunc(this, play);

    if (this->actionFunc != func_80A4431C) {
        Math_StepToF(&this->actor.shape.yOffset, 2000.0f, 200.0f);
    }

    if (this->actionFunc != func_80A438D4) {
        Vec3f prevPos;

        this->actor.world.rot.y = this->actor.shape.rot.y;
        this->actor.world.rot.x = -this->actor.shape.rot.x;
        Math_Vec3f_Copy(&prevPos, &this->actor.prevPos);

        if ((this->actor.colChkInfo.health != 0) && (this->actionFunc != func_80A4431C)) {
            Actor_MoveWithoutGravity(&this->actor);
        } else {
            Actor_MoveWithGravity(&this->actor);
        }

        if (this->actionFunc == func_80A43CE8) {
            Actor_UpdateBgCheckInfo(play, &this->actor, 12.0f, 15.0f, 50.0f, 5);
        } else if ((this->actionFunc != func_80A4392C) ||
                   ((this->actor.xzDistToPlayer < 400.0f) && (this->actor.projectedPos.z > 0.0f))) {
            if (this->paramsE0 & 1) {
                Actor_UpdateBgCheckInfo(play, &this->actor, 12.0f, 15.0f, 50.0f, 5);
            } else {
                Actor_UpdateBgCheckInfo(play, &this->actor, 12.0f, 15.0f, 50.0f, 4);
            }
        } else {
            Math_Vec3f_Copy(&this->actor.prevPos, &prevPos);
        }

        Actor_SetFocus(&this->actor, this->actor.shape.yOffset * 0.01f);
        this->collider.dim.worldSphere.center.x = this->actor.focus.pos.x;
        this->collider.dim.worldSphere.center.y = this->actor.focus.pos.y;
        this->collider.dim.worldSphere.center.z = this->actor.focus.pos.z;
    }

    if (this->collider.base.atFlags & AT_ON) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
    }
    if (this->actionFunc == func_80A43CE8) {
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
    if (this->collider.base.acFlags & AC_ON) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    }

    if (this->drawDmgEffAlpha > 0.0f) {
        if (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
            Math_StepToF(&this->drawDmgEffAlpha, 0.0f, 0.05f);
            this->drawDmgEffScale = (this->drawDmgEffAlpha + 1.0f) * 0.225f;
            this->drawDmgEffScale = CLAMP_MAX(this->drawDmgEffScale, 0.45f);
        } else if (!Math_StepToF(&this->drawDmgEffFrozenSteamScale, 0.45f, 0.45f / 40.0f)) {
            func_800B9010(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
        }
    }
}

void EnBat_Draw(Actor* thisx, PlayState* play) {
    EnBat* this = THIS;
    Gfx* gfx;

    // Draw body and wings
    if (this->actor.projectedPos.z > 0.0f) {
        OPEN_DISPS(play->state.gfxCtx);

        gfx = POLY_OPA_DISP;

        gSPDisplayList(&gfx[0], &sSetupDL[150]);
        gSPMatrix(&gfx[1], Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(&gfx[2], D_060000A0);
        gSPDisplayList(&gfx[3], D_060000C8);
        gSPDisplayList(&gfx[4], D_80A44A64[this->animationFrame]);

        POLY_OPA_DISP = &gfx[5];

        CLOSE_DISPS(play->state.gfxCtx);
    }

    // Draw damage effects
    if (this->drawDmgEffAlpha > 0.0f) {
        s16 rollAngle;

        if (this->animationFrame < BAD_BAT_FLAP_FRAME - 1) {
            rollAngle = this->animationFrame * (15 * (0x10000 / 360));
        } else {
            rollAngle = (this->animationFrame >= BAD_BAT_FLAP_FRAME)
                       ? (this->animationFrame * (15 * (0x10000 / 360))) - (120 * (0x10000 / 360))
                       : 0;
        }
        Matrix_MultZero(&this->bodyPartPoss[0]);
        Matrix_RotateZS(rollAngle, MTXMODE_APPLY);
        Matrix_MultVecX(1700.0f, &this->bodyPartPoss[1]);
        Matrix_RotateZS(-2 * rollAngle, MTXMODE_APPLY);
        Matrix_MultVecX(-1700.0f, &this->bodyPartPoss[2]);
        Actor_DrawDamageEffects(play, &this->actor, this->bodyPartPoss, ARRAY_COUNT(this->bodyPartPoss),
                                this->drawDmgEffScale, this->drawDmgEffFrozenSteamScale, this->drawDmgEffAlpha,
                                this->drawDmgEffType);
    }
}
