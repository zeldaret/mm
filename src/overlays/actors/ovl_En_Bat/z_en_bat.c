/*
 * File: z_en_bat.c
 * Overlay: ovl_En_Bat
 * Description: Bad Bat
 */

#include "z_en_bat.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_1000 | ACTOR_FLAG_4000)

#define THIS ((EnBat*)thisx)

void EnBat_Init(Actor* thisx, PlayState* play);
void EnBat_Destroy(Actor* thisx, PlayState* play);
void EnBat_Update(Actor* thisx, PlayState* play);
void EnBat_Draw(Actor* thisx, PlayState* play);

void func_80A438D4(EnBat* this, PlayState* play);
void func_80A4392C(EnBat* this, PlayState* play);
void func_80A43CE8(EnBat* this, PlayState* play);
void func_80A44114(EnBat* this, PlayState* play);

s32 func_80A437CC(PlayState* play);
void func_80A43870(EnBat* this);
void func_80A438F8(EnBat* this);
void func_80A43CA0(EnBat* this);
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

static DamageTable sDamageTable = {
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
s32 D_80A44C74;

extern Gfx D_060000A0[];
extern Gfx D_060000C8[];

void EnBat_Init(Actor* thisx, PlayState* play) {
    EnBat* this = (EnBat*)thisx;

    Actor_ProcessInitChain(thisx, sInitChain);
    Collider_InitAndSetSphere(play, &this->collider, thisx, &sSphereInit);
    this->collider.dim.worldSphere.radius = sSphereInit.dim.modelSphere.radius;
    CollisionCheck_SetInfo(&thisx->colChkInfo, &sDamageTable, &sColChkInfoInit);
    ActorShape_Init(&thisx->shape, 2000.0f, ActorShadow_DrawCircle, 25.0f);

    this->unk152 = Rand_ZeroOne() * 9.0f;
    this->paramsE0 = BAT_GET_E0(thisx);
    this->switchFlag = BAT_GET_SWITCHFLAG(thisx);
    thisx->params = BAT_GET_TYPE(thisx);

    thisx->depthInWater = -32000.0f;
    Actor_SetFocus(thisx, 20.0f);

    if (D_80A44C74 != 0) {
        Actor_MarkForDeath(thisx);
    } else if (func_80A437CC(play)) {
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
            Actor_SpawnAsChildAndCutscene(
                &play->actorCtx, play, ACTOR_EN_BAT, thisx->world.pos.x + randPlusMinusPoint5Scaled(200.0f),
                thisx->world.pos.y + randPlusMinusPoint5Scaled(100.0f),
                thisx->world.pos.z + randPlusMinusPoint5Scaled(200.0f), randPlusMinusPoint5Scaled((f32)0x2000),
                Rand_ZeroOne() * ((f32)0xFFFF), 0, BAT_PARAMS(this->switchFlag, this->paramsE0, 0), -1, thisx->unk20, NULL);
            thisx->params--;
        }
    }
}

void EnBat_Destroy(Actor* thisx, PlayState* play) {
    EnBat* this = THIS;

    Collider_DestroySphere(play, &this->collider);
}

s32 func_80A437CC(PlayState* play) {
    if ((CURRENT_DAY == 2) && (play->sceneNum == SCENE_BOTI)) {
        return true;
    } else {
        return false;
    }
}

void func_80A43810(EnBat* this, s32 arg1) {
    s32 temp_v0 = this->unk152;

    this->unk152 += arg1;
    if (this->unk152 >= 9) {
        this->unk152 -= 9;
    }
    if ((temp_v0 < 5) && (this->unk152 >= 5)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FFLY_FLY);
    }
}

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
    func_80A43810(this, 1);
}

void func_80A438F8(EnBat* this) {
    this->unk14C = 100;
    this->collider.base.acFlags |= AC_ON;
    this->actor.speedXZ = 3.5f;
    this->actionFunc = func_80A4392C;
}

void func_80A4392C(EnBat* this, PlayState* play) {
    s32 temp_v0;

    func_80A43810(this, 1);

    temp_v0 = Math_ScaledStepToS(&this->actor.shape.rot.y, this->unk150, 0x300);

    if (this->actor.bgCheckFlags & 8) {
        this->actor.bgCheckFlags &= ~8;
        this->unk150 = this->actor.wallYaw;
    } else if (Math3D_XZDistanceSquared(this->actor.world.pos.x, this->actor.world.pos.z, this->actor.home.pos.x,
                                        this->actor.home.pos.z) > 90000.0f) {
        this->unk150 = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    } else if (temp_v0 && (Rand_ZeroOne() < 0.015f)) {
        this->unk150 =
            (((s32)(4096.0f * Rand_ZeroOne()) + 0x1000) * ((Rand_ZeroOne() < 0.5f) ? -1 : 1)) + this->actor.shape.rot.y;
    }

    temp_v0 = Math_ScaledStepToS(&this->actor.shape.rot.x, this->unk14E, 0x100);

    if ((this->actor.bgCheckFlags & 1) || (this->actor.depthInWater > -40.0f)) {
        this->unk14E = -0x1000;
    } else if (this->actor.world.pos.y < (this->actor.home.pos.y - 100.0f)) {
        this->unk14E = -0x800 - (s32)(Rand_ZeroOne() * 2048.0f);
    } else if ((this->actor.home.pos.y + 100.0f) < this->actor.world.pos.y) {
        this->unk14E = (s32)(Rand_ZeroOne() * 2048.0f) + 0x800;
    } else if ((temp_v0) && (Rand_ZeroOne() < 0.015f)) {
        this->unk14E += (s16)(((s32)(1024.0f * Rand_ZeroOne()) + 0x400) * ((Rand_ZeroOne() < 0.5f) ? -1 : 1));
        this->unk14E = CLAMP(this->unk14E, -0x1000, 0x1000);
    }

    if (this->unk14C != 0) {
        this->unk14C--;
    }
    if ((this->actor.xzDistToPlayer < 300.0f) && (this->unk14C == 0) && (Player_GetMask(play) != PLAYER_MASK_STONE) &&
        (D_80A44C70 < 3) && (!(this->paramsE0 & 2) || (fabsf(this->actor.playerHeightRel) < 150.0f))) {
        func_80A43CA0(this);
    }
}

void func_80A43CA0(EnBat* this) {
    this->collider.base.atFlags |= AT_ON;
    this->unk14C = 300;
    this->actor.speedXZ = 4.0f;
    D_80A44C70++;
    this->actionFunc = func_80A43CE8;
}

void func_80A43CE8(EnBat* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 facingPlayer;
    Vec3f preyPos;

    func_80A43810(this, 2);
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

    this->unk14C--;

    if ((this->unk14C == 0) || (this->collider.base.atFlags & 2) || (Player_GetMask(play) == PLAYER_MASK_STONE) ||
        (this->actor.bgCheckFlags & 1) || (player->stateFlags1 & 0x800000) || (this->actor.depthInWater > -40.0f)) {
        if (this->collider.base.atFlags & AT_HIT) {
            this->collider.base.atFlags &= ~AT_HIT;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FFLY_ATTACK);
        }
        this->collider.base.atFlags &= ~AT_ON;
        D_80A44C70--;
        func_80A438F8(this);
    } else if (this->actor.bgCheckFlags & 8) {
        if (ABS_ALT((s16)(this->actor.wallYaw - this->actor.yawTowardsPlayer)) > 0x6800) {
            D_80A44C70--;
            this->collider.base.atFlags &= ~AT_ON;
            this->actor.bgCheckFlags &= ~8;
            this->unk150 = this->actor.wallYaw;
            func_80A438F8(this);
        }
    }
}

void func_80A43F60(EnBat* this, PlayState* play) {
    this->actor.flags &= ~ACTOR_FLAG_1;
    Enemy_StartFinishingBlow(play, &this->actor);
    this->actor.speedXZ *= Math_CosS(this->actor.world.rot.x);
    this->actor.bgCheckFlags &= ~1;
    this->actor.velocity.y = 0.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FFLY_DEAD);

    if (this->actor.colChkInfo.damageEffect == 3) {
        this->drawDmgEffType = 0xA;
        this->drawDmgEffAlpha = 1.0f;
        this->drawDmgEffFrozenSteamScale = 0.67499995f; // 60.0f * (0.45f / 40.0f);
        this->drawDmgEffScale = 0.45f;
    } else if (this->actor.colChkInfo.damageEffect == 4) {
        this->drawDmgEffType = 0x14;
        this->drawDmgEffAlpha = 4.0f;
        this->drawDmgEffScale = 0.45f;
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->collider.info.bumper.hitPos.x,
                    this->collider.info.bumper.hitPos.y, this->collider.info.bumper.hitPos.z, 0, 0, 0,
                    CLEAR_TAG_SMALL_LIGHT_RAYS);
    } else if (this->actor.colChkInfo.damageEffect == 2) {
        this->drawDmgEffType = 0;
        this->drawDmgEffAlpha = 4.0f;
        this->drawDmgEffScale = 0.45f;
    }

    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 40);

    if (this->actor.flags & ACTOR_FLAG_8000) {
        this->actor.speedXZ = 0.0f;
    }

    this->collider.base.acFlags &= ~1;
    this->actor.flags |= ACTOR_FLAG_10;
    this->actionFunc = func_80A44114;
}

void func_80A44114(EnBat* this, PlayState* play) {
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
    this->actor.colorFilterTimer = 40;
    if (!(this->actor.flags & ACTOR_FLAG_8000)) {
        if (this->drawDmgEffType != 0xA) {
            Math_ScaledStepToS(&this->actor.shape.rot.x, 0x4000, 0x200);
            this->actor.shape.rot.z += 0x1780;
        }
        if ((this->actor.bgCheckFlags & 1) || (this->actor.floorHeight == -32000.0f)) {
            if (this->drawDmgEffType == 0xA) {
                Actor_SpawnIceEffects(play, &this->actor, this->bodyPartPoss, ARRAY_COUNT(this->bodyPartPoss), 2, 0.2f, 0.2f);
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
    Actor_SetColorFilter(&this->actor, 0, 255, 0, this->unk14C);
    this->actionFunc = func_80A4431C;
}

void func_80A4431C(EnBat* this, PlayState* play) {
    Math_ScaledStepToS(&this->actor.shape.rot.x, 0, 0x100);
    if ((this->actor.bgCheckFlags & 1) || (this->actor.floorHeight == -32000.0f)) {
        if (this->unk14C != 0) {
            this->unk14C--;
        }
        if (this->unk14C == 0) {
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
        if (this->actor.colChkInfo.damageEffect == 5) {
            this->unk14C = 40;
            this->drawDmgEffType = 0x20;
            this->drawDmgEffAlpha = 2.0f;
            this->drawDmgEffScale = 0.45f;
            func_80A44294(this);
        } else if (this->actor.colChkInfo.damageEffect == 1) {
            this->unk14C = 40;
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
        D_80A44C74 = 1;
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
        if (this->drawDmgEffType != 0xA) {
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

    if (this->actor.projectedPos.z > 0.0f) {
        OPEN_DISPS(play->state.gfxCtx);

        gfx = POLY_OPA_DISP;

        gSPDisplayList(&gfx[0], &sSetupDL[150]);
        gSPMatrix(&gfx[1], Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(&gfx[2], D_060000A0);
        gSPDisplayList(&gfx[3], D_060000C8);
        gSPDisplayList(&gfx[4], D_80A44A64[this->unk152]);

        POLY_OPA_DISP = &gfx[5];

        CLOSE_DISPS(play->state.gfxCtx);
    }

    if (this->drawDmgEffAlpha > 0.0f) {
        s16 zRot;

        if (this->unk152 < 4) {
            zRot = this->unk152 * (15 * (0x10000 / 360));
        } else {
            zRot = (this->unk152 >= 5) ? (this->unk152 * (15 * (0x10000 / 360))) - (120 * (0x10000 / 360)) : 0;
        }
        Matrix_MultZero(&this->bodyPartPoss[0]);
        Matrix_RotateZS(zRot, MTXMODE_APPLY);
        Matrix_MultVecX(1700.0f, &this->bodyPartPoss[1]);
        Matrix_RotateZS(-2 * zRot, MTXMODE_APPLY);
        Matrix_MultVecX(-1700.0f, &this->bodyPartPoss[2]);
        Actor_DrawDamageEffects(play, &this->actor, this->bodyPartPoss, ARRAY_COUNT(this->bodyPartPoss), this->drawDmgEffScale, this->drawDmgEffFrozenSteamScale, this->drawDmgEffAlpha,
                                this->drawDmgEffType);
    }
}
