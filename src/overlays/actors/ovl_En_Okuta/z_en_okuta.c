/*
 * File: z_en_okuta.c
 * Overlay: ovl_En_Okuta
 * Description: Octorok
 */

#include "z_en_okuta.h"
#include "overlays/actors/ovl_En_Clear_Tag/z_en_clear_tag.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY)

#define THIS ((EnOkuta*)thisx)

void EnOkuta_Init(Actor* thisx, PlayState* play2);
void EnOkuta_Destroy(Actor* thisx, PlayState* play);
void EnOkuta_Update(Actor* thisx, PlayState* play2);
void EnOkuta_Draw(Actor* thisx, PlayState* play);

void EnOkuta_SetupWaitToAppear(EnOkuta* this);
void EnOkuta_WaitToAppear(EnOkuta* this, PlayState* play);
void EnOkuta_SetupAppear(EnOkuta* this, PlayState* play);
void EnOkuta_Appear(EnOkuta* this, PlayState* play);
void EnOkuta_SetupHide(EnOkuta* this);
void EnOkuta_Hide(EnOkuta* this, PlayState* play);
void EnOkuta_SetupFloat(EnOkuta* this);
void EnOkuta_Float(EnOkuta* this, PlayState* play);
void EnOkuta_SetupShoot(EnOkuta* this, PlayState* play);
void EnOkuta_Shoot(EnOkuta* this, PlayState* play);
void EnOkuta_Damaged(EnOkuta* this, PlayState* play);
void EnOkuta_SetupDie(EnOkuta* this);
void EnOkuta_Die(EnOkuta* this, PlayState* play);
void func_8086F434(EnOkuta* this, PlayState* play);
void func_8086F4B0(EnOkuta* this, PlayState* play);
void func_8086F57C(EnOkuta* this, PlayState* play);
void func_8086F694(EnOkuta* this, PlayState* play);
void func_808700C0(Actor* thisx, PlayState* play);

#include "assets/overlays/ovl_En_Okuta/ovl_En_Okuta.c"

ActorInit En_Okuta_InitVars = {
    /**/ ACTOR_EN_OKUTA,
    /**/ ACTORCAT_ENEMY,
    /**/ FLAGS,
    /**/ OBJECT_OKUTA,
    /**/ sizeof(EnOkuta),
    /**/ EnOkuta_Init,
    /**/ EnOkuta_Destroy,
    /**/ EnOkuta_Update,
    /**/ EnOkuta_Draw,
};

static ColliderCylinderInit sProjectileCylinderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK4,
        { 0xF7CFFFFF, 0x00, 0x04 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_HARD,
        BUMP_ON,
        OCELEM_ON,
    },
    { 13, 20, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit sOctorokCylinderInit = {
    {
        COLTYPE_HIT0,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0xF7CFFFFF, 0x00, 0x04 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_HARD,
        BUMP_ON,
        OCELEM_ON,
    },
    { 20, 40, -30, { 0, 0, 0 } },
};

static CollisionCheckInfoInit sColChkInfoInit = { 4, 15, 60, 100 };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
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

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, TATL_HINT_ID_OCTOROK, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 6500, ICHAIN_STOP),
};

void EnOkuta_Init(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnOkuta* this = THIS;
    WaterBox* waterBox;
    f32 waterSurface;
    s32 bgId;

    Actor_ProcessInitChain(thisx, sInitChain);
    this->unk190 = EN_OKUTA_GET_UNK190(thisx);
    thisx->params &= 0xFF;

    if ((EN_OKUTA_GET_TYPE(thisx) == EN_OKUTA_TYPE_RED_OCTOROK) ||
        (EN_OKUTA_GET_TYPE(thisx) == EN_OKUTA_TYPE_BLUE_OCTOROK)) {
        SkelAnime_Init(play, &this->skelAnime, &gOctorokSkel, &gOctorokAppearAnim, this->jointTable, this->morphTable,
                       OCTOROK_LIMB_MAX);
        Collider_InitAndSetCylinder(play, &this->collider, thisx, &sOctorokCylinderInit);
        CollisionCheck_SetInfo(&thisx->colChkInfo, &sDamageTable, &sColChkInfoInit);

        if (this->unk190 == 0xFF || this->unk190 == 0) {
            this->unk190 = 1;
        }

        thisx->floorHeight =
            BgCheck_EntityRaycastFloor5(&play->colCtx, &thisx->floorPoly, &bgId, thisx, &thisx->world.pos);

        if (!WaterBox_GetSurface1_2(play, &play->colCtx, thisx->world.pos.x, thisx->world.pos.z, &waterSurface,
                                    &waterBox) ||
            waterSurface <= thisx->floorHeight) {
            Actor_Kill(thisx);
        } else {
            thisx->home.pos.y = waterSurface;
        }

        if (EN_OKUTA_GET_TYPE(thisx) == EN_OKUTA_TYPE_BLUE_OCTOROK) {
            this->collider.base.colType = COLTYPE_HARD;
            this->collider.base.acFlags |= AC_HARD;
        }

        thisx->targetMode = TARGET_MODE_5;
        EnOkuta_SetupWaitToAppear(this);
    } else {
        ActorShape_Init(&thisx->shape, 1100.0f, ActorShadow_DrawCircle, 18.0f);
        thisx->flags &= ~ACTOR_FLAG_TARGETABLE;
        thisx->flags |= ACTOR_FLAG_10;
        Collider_InitAndSetCylinder(play, &this->collider, thisx, &sProjectileCylinderInit);
        Actor_ChangeCategory(play, &play->actorCtx, thisx, ACTORCAT_PROP);
        this->unk18E = 0x16;
        thisx->shape.rot.y = 0;
        thisx->world.rot.x = -thisx->shape.rot.x;
        thisx->shape.rot.x = 0;
        this->actionFunc = func_8086F694;
        thisx->update = func_808700C0;
        thisx->speed = 10.0f;
    }
}

void EnOkuta_Destroy(Actor* thisx, PlayState* play) {
    EnOkuta* this = THIS;
    Collider_DestroyCylinder(play, &this->collider);
}

void func_8086E084(EnOkuta* this) {
    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX;
    this->drawDmgEffScale = 0.6f;
    this->drawDmgEffFrozenSteamScale = 9.0f * 0.1f;
    this->drawDmgEffAlpha = 1.0f;
    this->unk18E = 0x50;
    this->collider.base.colType = COLTYPE_HIT3;
    Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_RED, 255, COLORFILTER_BUFFLAG_OPA, 80);
}

void func_8086E0F0(EnOkuta* this, PlayState* play) {
    if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->drawDmgEffAlpha = 0.0f;
        Actor_SpawnIceEffects(play, &this->actor, this->bodyPartsPos, 0xA, 2, 0.3f, 0.2f);
        this->collider.base.colType = COLTYPE_HIT0;
    }
}

void EnOkuta_SpawnBubbles(EnOkuta* this, PlayState* play) {
    s32 i;

    for (i = 0; i != 10; i++) {
        EffectSsBubble_Spawn(play, &this->actor.world.pos, -10.0f, 10.0f, 30.0f, 0.25f);
    }
}

/**
 * Spawns the puff of smoke that appears at the Octorok's snout.
 */
void EnOkuta_SpawnDust(Vec3f* pos, Vec3f* velocity, s16 scaleStep, PlayState* play) {
    static Color_RGBA8 sDustPrimColor = { 255, 255, 255, 255 };
    static Color_RGBA8 sDustEnvColor = { 150, 150, 150, 255 };

    func_800B0DE0(play, pos, velocity, &gZeroVec3f, &sDustPrimColor, &sDustEnvColor, 400, scaleStep);
}

/**
 * Spawns the splash that appears when the Octorok appears from underwater, hides underwater, shoots a rock, or dies.
 */
void EnOkuta_SpawnSplash(EnOkuta* this, PlayState* play) {
    EffectSsGSplash_Spawn(play, &this->actor.home.pos, NULL, NULL, 0, 1300);
}

void EnOkuta_SpawnRipple(EnOkuta* this, PlayState* play) {
    f32 temp = this->actor.world.pos.y - this->actor.home.pos.y;
    Vec3f pos;

    if (((play->gameplayFrames % 7) == 0) && (temp < 50.0f) && (temp >= -20.0f)) {
        pos.x = this->actor.world.pos.x;
        pos.y = this->actor.home.pos.y;
        pos.z = this->actor.world.pos.z;
        EffectSsGRipple_Spawn(play, &pos, 250, 650, 0);
    }
}

f32 func_8086E378(EnOkuta* this) {
    f32 height = this->actor.world.pos.y + this->actor.playerHeightRel + 60.0f;

    if (this->actor.home.pos.y < height) {
        return this->actor.home.pos.y;
    }

    return height;
}

void EnOkuta_SpawnProjectile(EnOkuta* this, PlayState* play) {
    Vec3f pos;
    Vec3f velocity;
    f32 sin;
    f32 cos;

    sin = Math_SinS(this->actor.shape.rot.y);
    cos = Math_CosS(this->actor.shape.rot.y);
    pos.x = this->actor.world.pos.x + 25.0f * sin;
    pos.y = this->actor.world.pos.y - 6.0f;
    pos.z = this->actor.world.pos.z + 25.0f * cos;

    if (Actor_Spawn(&play->actorCtx, play, ACTOR_EN_OKUTA, pos.x, pos.y, pos.z, this->actor.shape.rot.x,
                    this->actor.shape.rot.y, this->actor.shape.rot.z,
                    EN_OKUTA_GET_TYPE(&this->actor) + EN_OKUTA_TYPE_PROJECTILE_BASE) != NULL) {
        pos.x = this->actor.world.pos.x + (40.0f * sin);
        pos.z = this->actor.world.pos.z + (40.0f * cos);
        pos.y = this->actor.world.pos.y;

        velocity.x = 1.5f * sin;
        velocity.y = 0.0f;
        velocity.z = 1.5f * cos;

        EnOkuta_SpawnDust(&pos, &velocity, 20, play);
    }

    Actor_PlaySfx(&this->actor, NA_SE_EN_NUTS_THROW);
}

void EnOkuta_SetupWaitToAppear(EnOkuta* this) {
    this->actor.draw = NULL;
    this->actor.world.pos.y = this->actor.home.pos.y;
    this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
    this->actionFunc = EnOkuta_WaitToAppear;
}

void EnOkuta_WaitToAppear(EnOkuta* this, PlayState* play) {
    this->actor.world.pos.y = this->actor.home.pos.y;

    if (this->actor.xzDistToPlayer < 480.0f && this->actor.xzDistToPlayer > 200.0f) {
        if (EN_OKUTA_GET_TYPE(&this->actor) == EN_OKUTA_TYPE_RED_OCTOROK) {
            EnOkuta_SetupAppear(this, play);
        } else if (ABS_ALT((s16)(this->actor.yawTowardsPlayer - this->actor.world.rot.y)) < 0x4000 &&
                   play->unk_1887C == 0) {
            EnOkuta_SetupAppear(this, play);
        }
    }
}

void EnOkuta_SetupAppear(EnOkuta* this, PlayState* play) {
    this->actor.draw = EnOkuta_Draw;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    this->actor.flags |= ACTOR_FLAG_TARGETABLE;
    Animation_PlayOnce(&this->skelAnime, &gOctorokAppearAnim);
    EnOkuta_SpawnBubbles(this, play);
    this->actionFunc = EnOkuta_Appear;
}

void EnOkuta_Appear(EnOkuta* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        if ((this->actor.xzDistToPlayer < 160.0f) && (EN_OKUTA_GET_TYPE(&this->actor) == EN_OKUTA_TYPE_RED_OCTOROK)) {
            EnOkuta_SetupHide(this);
        } else {
            EnOkuta_SetupFloat(this);
        }
    } else {
        f32 curFrame = this->skelAnime.curFrame;

        if (curFrame <= 4.0f) {
            Actor_SetScale(&this->actor, curFrame * 0.25f * 0.01f);
        } else if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
            Actor_SetScale(&this->actor, 0.01f);
        }
    }

    if (Animation_OnFrame(&this->skelAnime, 2.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_JUMP);
    }

    if (Animation_OnFrame(&this->skelAnime, 12.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_DAIOCTA_LAND);
    }

    if ((Animation_OnFrame(&this->skelAnime, 3.0f)) || (Animation_OnFrame(&this->skelAnime, 15.0f))) {
        EnOkuta_SpawnSplash(this, play);
    }
}

void EnOkuta_SetupHide(EnOkuta* this) {
    Animation_PlayOnce(&this->skelAnime, &gOctorokHideAnim);
    this->actionFunc = EnOkuta_Hide;
}

void EnOkuta_Hide(EnOkuta* this, PlayState* play) {
    Math_ApproachF(&this->actor.world.pos.y, this->actor.home.pos.y, 0.5f, 30.0f);

    if (SkelAnime_Update(&this->skelAnime)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_COMMON_WATER_MID);
        EnOkuta_SpawnBubbles(this, play);
        EnOkuta_SetupWaitToAppear(this);
    } else {
        f32 curFrame = this->skelAnime.curFrame;

        if (curFrame >= 4.0f) {
            Actor_SetScale(&this->actor, (6.0f - curFrame) * 0.5f * 0.01f);
        }
    }

    if (Animation_OnFrame(&this->skelAnime, 2.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_DAIOCTA_SINK);
    }

    if (Animation_OnFrame(&this->skelAnime, 4.0f)) {
        EnOkuta_SpawnSplash(this, play);
    }
}

void EnOkuta_SetupFloat(EnOkuta* this) {
    Animation_PlayLoop(&this->skelAnime, &gOctorokFloatAnim);
    if (this->actionFunc == EnOkuta_Shoot) {
        this->unk18E = 8;
    } else {
        this->unk18E = 0;
    }

    this->actionFunc = EnOkuta_Float;
}

void EnOkuta_Float(EnOkuta* this, PlayState* play) {
    if (EN_OKUTA_GET_TYPE(&this->actor) == EN_OKUTA_TYPE_RED_OCTOROK) {
        this->actor.world.pos.y = this->actor.home.pos.y;
    } else {
        this->actor.world.pos.y = func_8086E378(this);
    }

    SkelAnime_Update(&this->skelAnime);

    if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
        DECR(this->unk18E);
    }

    if (Animation_OnFrame(&this->skelAnime, 0.5f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_COMMON_WATER_SLW);
    }

    if ((this->actor.xzDistToPlayer > 560.0f) ||
        ((this->actor.xzDistToPlayer < 160.0f) && (EN_OKUTA_GET_TYPE(&this->actor) == EN_OKUTA_TYPE_RED_OCTOROK))) {
        EnOkuta_SetupHide(this);
    } else {
        s16 var_v1 = Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0xE38, 0x38E);

        if ((ABS_ALT(var_v1) < 0x38E) && ((((EN_OKUTA_GET_TYPE(&this->actor) == EN_OKUTA_TYPE_RED_OCTOROK)) &&
                                           (this->unk18E == 0) && (this->actor.playerHeightRel < 120.0f)) ||
                                          ((EN_OKUTA_GET_TYPE(&this->actor) == EN_OKUTA_TYPE_BLUE_OCTOROK) &&
                                           ((this->unk18E == 0) || (this->actor.xzDistToPlayer < 150.0f))))) {
            EnOkuta_SetupShoot(this, play);
        }
    }
}

void EnOkuta_SetupShoot(EnOkuta* this, PlayState* play) {
    Animation_PlayOnce(&this->skelAnime, &gOctorokShootAnim);

    if (this->actionFunc != EnOkuta_Shoot) {
        if (EN_OKUTA_GET_TYPE(&this->actor) == EN_OKUTA_TYPE_RED_OCTOROK) {
            this->unk18E = this->unk190;
        } else {
            this->unk18E = (560.0f - this->actor.xzDistToPlayer) * 0.005f + 1.0f;
        }
    }

    if (EN_OKUTA_GET_TYPE(&this->actor) == EN_OKUTA_TYPE_RED_OCTOROK) {
        this->unk260 = this->actor.playerHeightRel + 20.0f;
        this->unk260 = CLAMP_MIN(this->unk260, 10.0f);

        if (this->unk260 > 50.0f) {
            EnOkuta_SpawnSplash(this, play);
            Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_JUMP);
        }
    }

    this->actionFunc = EnOkuta_Shoot;
}

void EnOkuta_Shoot(EnOkuta* this, PlayState* play) {
    f32 curFrame;
    Player* player;
    Vec3f sp34;
    s16 sp32;

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0x71C);

    if (SkelAnime_Update(&this->skelAnime)) {
        DECR(this->unk18E);

        if (this->unk18E == 0) {
            if ((EN_OKUTA_GET_TYPE(&this->actor) != EN_OKUTA_TYPE_BLUE_OCTOROK) ||
                (this->actor.xzDistToPlayer > 150.0f)) {
                EnOkuta_SetupFloat(this);
            } else {
                EnOkuta_SetupShoot(this, play);
            }
        } else {
            EnOkuta_SetupShoot(this, play);
        }
    } else {
        if (EN_OKUTA_GET_TYPE(&this->actor) == EN_OKUTA_TYPE_RED_OCTOROK) {
            if ((curFrame = this->skelAnime.curFrame) < 13.0f) {
                this->actor.world.pos.y = Math_SinF(0.2617889f * curFrame) * this->unk260 + this->actor.home.pos.y;
            }

            if (this->unk260 > 50.0f && Animation_OnFrame(&this->skelAnime, 13.0f)) {
                EnOkuta_SpawnSplash(this, play);
                Actor_PlaySfx(&this->actor, NA_SE_EN_DAIOCTA_LAND);
            }
        } else {
            this->actor.world.pos.y = func_8086E378(this);

            if ((curFrame = this->skelAnime.curFrame) < 13.0f) {
                player = GET_PLAYER(play);
                sp34.x = player->actor.world.pos.x;
                sp34.y = player->actor.world.pos.y + 20.0f;
                sp34.z = player->actor.world.pos.z;
                sp32 = Actor_WorldPitchTowardPoint(&this->actor, &sp34);
                sp32 = CLAMP(sp32, -0x2AAA, 0);
                this->actor.shape.rot.x = Math_SinF(0.2617889f * curFrame) * sp32;
            }
        }

        if (Animation_OnFrame(&this->skelAnime, 6.0f)) {
            EnOkuta_SpawnProjectile(this, play);
        }
    }

    if ((EN_OKUTA_GET_TYPE(&this->actor) == EN_OKUTA_TYPE_RED_OCTOROK) && (this->actor.xzDistToPlayer < 160.0f)) {
        EnOkuta_SetupHide(this);
    }
}

void EnOkuta_SetupDamaged(EnOkuta* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &gOctorokHitAnim, -5.0f);
    Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_RED, 255, COLORFILTER_BUFFLAG_OPA, 11);
    this->collider.base.acFlags &= ~AC_ON;
    Actor_SetScale(&this->actor, 0.01f);
    Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_DEAD1);
    this->actionFunc = EnOkuta_Damaged;
}

void EnOkuta_Damaged(EnOkuta* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->actor.colChkInfo.health == 0) {
            EnOkuta_SetupDie(this);
        } else {
            this->collider.base.acFlags |= AC_ON;
            EnOkuta_SetupFloat(this);
        }
    }

    Math_ApproachF(&this->actor.world.pos.y, this->actor.home.pos.y, 0.5f, 5.0f);
}

void EnOkuta_SetupDie(EnOkuta* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &gOctorokDieAnim, -3.0f);
    this->unk18E = 0;
    this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
    this->actionFunc = EnOkuta_Die;
}

void EnOkuta_Die(EnOkuta* this, PlayState* play) {
    static Vec3f sBubbleAccel = { 0.0f, -0.5f, 0.0f };
    static Color_RGBA8 sBubblePrimColor = { 255, 255, 255, 255 };
    static Color_RGBA8 sBubbleEnvColor = { 150, 150, 150, 0 };
    Vec3f sp7C;
    Vec3f sp70;
    s32 i;

    if (SkelAnime_Update(&this->skelAnime)) {
        this->unk18E += 1;
    }

    Math_ApproachF(&this->actor.world.pos.y, this->actor.home.pos.y, 0.5f, 5.0f);

    if (this->unk18E == 5) {
        sp70.x = this->actor.world.pos.x;
        sp70.y = this->actor.world.pos.y + 40.0f;
        sp70.z = this->actor.world.pos.z;

        sp7C.x = 0.0f;
        sp7C.y = -0.5f;
        sp7C.z = 0.0f;

        EnOkuta_SpawnDust(&sp70, &sp7C, -20, play);
        Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_DEAD2);
    }

    if (Animation_OnFrame(&this->skelAnime, 15.0f)) {
        EnOkuta_SpawnSplash(this, play);
        Actor_PlaySfx(&this->actor, NA_SE_EN_DAIOCTA_LAND);
    }

    if (this->unk18E < 3) {
        Actor_SetScale(&this->actor, (((f32)this->unk18E * 0.25f) + 1.0f) * 0.01f);
        return;
    }

    if (this->unk18E < 6) {
        Actor_SetScale(&this->actor, (1.5f - ((f32)(this->unk18E - 2) * 0.2333f)) * 0.01f);
        return;
    }

    if (this->unk18E < 0xB) {
        Actor_SetScale(&this->actor, (((f32)(this->unk18E - 5) * 0.04f) + 0.8f) * 0.01f);
        return;
    }

    if (Math_StepToF(&this->actor.scale.x, 0.0f, 0.0005f)) {
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 30, NA_SE_EN_COMMON_WATER_MID);
        Item_DropCollectibleRandom(play, &this->actor, &this->actor.world.pos, 0xA0);

        for (i = 0; i != 20; i++) {
            sp7C.x = (Rand_ZeroOne() - 0.5f) * 7.0f;
            sp7C.y = Rand_ZeroOne() * 7.0f;
            sp7C.z = (Rand_ZeroOne() - 0.5f) * 7.0f;
            EffectSsDtBubble_SpawnCustomColor(play, &this->actor.world.pos, &sp7C, &sBubbleAccel, &sBubblePrimColor,
                                              &sBubbleEnvColor, Rand_S16Offset(100, 50), 25, false);
        }

        Actor_Kill(&this->actor);
    }

    this->actor.scale.z = this->actor.scale.x;
    this->actor.scale.y = this->actor.scale.x;
}

void func_8086F2FC(EnOkuta* this, PlayState* play) {
    this->unk18E = 0xA;
    Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_GRAY, COLORFILTER_INTENSITY_FLAG | 255,
                         COLORFILTER_BUFFLAG_OPA, 10);
    this->actor.child = Actor_SpawnAsChild(
        &play->actorCtx, &this->actor, play, ACTOR_OBJ_ICEBLOCK, this->actor.world.pos.x,
        this->actor.world.pos.y + this->skelAnime.jointTable->y * this->actor.scale.y + 25.0f * this->headScale.y,
        this->actor.world.pos.z, 0, this->actor.home.rot.y, 0, 3);

    if (this->actor.child != NULL) {
        this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
        this->actor.flags |= ACTOR_FLAG_10;
        this->actor.child->csId = this->actor.csId;
        this->actionFunc = func_8086F434;
        return;
    }

    func_8086E084(this);

    if (Actor_ApplyDamage(&this->actor) == 0) {
        Enemy_StartFinishingBlow(play, &this->actor);
        this->collider.base.acFlags &= ~AC_ON;
        this->unk18E = 3;
    }

    this->actionFunc = func_8086F4B0;
}

void func_8086F434(EnOkuta* this, PlayState* play) {
    this->actor.colorFilterTimer = 10;

    if ((this->actor.child == NULL) || (this->actor.child->update == NULL)) {
        this->actor.flags |= ACTOR_FLAG_TARGETABLE;

        if (Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y, 10.0f)) {
            this->actor.flags &= ~ACTOR_FLAG_10;
            EnOkuta_SetupFloat(this);
        }
    }
}

void func_8086F4B0(EnOkuta* this, PlayState* play) {
    DECR(this->unk18E);

    if (this->unk18E == 0) {
        func_8086E0F0(this, play);
        EnOkuta_SetupDamaged(this);
    }
}

void func_8086F4F4(EnOkuta* this) {
    Animation_Change(&this->skelAnime, &gOctorokHitAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gOctorokHitAnim) - 3.0f,
                     ANIMMODE_ONCE, -3.0f);
    this->unk18E = 0x14;
    this->actionFunc = func_8086F57C;
}

void func_8086F57C(EnOkuta* this, PlayState* play) {
    this->unk18E -= 1;
    Math_ScaledStepToS(&this->actor.shape.rot.x, 0, 0x400);

    if (SkelAnime_Update(&this->skelAnime)) {
        Animation_Change(&this->skelAnime, &gOctorokHitAnim, 1.0f, 0.0f,
                         Animation_GetLastFrame(&gOctorokHitAnim) - 3.0f, ANIMMODE_ONCE, -3.0f);
    }

    if (this->unk18E < 0xA) {
        this->actor.shape.rot.y += (s16)(0x2000 * Math_SinF(this->unk18E * (M_PI / 20.0f)));
    } else {
        this->actor.shape.rot.y += 0x2000;
    }

    if (this->unk18E == 0) {
        EnOkuta_SetupFloat(this);
    }
}

void func_8086F694(EnOkuta* this, PlayState* play) {
    Vec3f sp54;
    Player* player = GET_PLAYER(play);
    Vec3s sp48;

    this->unk18E -= 1;

    if (this->unk18E < 0) {
        this->actor.velocity.y -= 0.5f;
        this->actor.world.rot.x =
            Math_Atan2S_XY(sqrtf(SQ(this->actor.velocity.x) + SQ(this->actor.velocity.z)), this->actor.velocity.y);
    }

    this->actor.home.rot.z += 0x1554;

    if ((this->actor.bgCheckFlags & BGCHECKFLAG_WALL) || (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) ||
        (this->actor.bgCheckFlags & BGCHECKFLAG_CEILING) || (this->collider.base.atFlags & AT_HIT) ||
        (this->collider.base.acFlags & AC_HIT) || (this->collider.base.ocFlags1 & OC1_HIT) ||
        (this->actor.floorHeight == BGCHECK_Y_MIN)) {
        if (player->currentShield == PLAYER_SHIELD_HEROS_SHIELD) {
            if ((this->collider.base.atFlags & AT_HIT) && (this->collider.base.atFlags & AT_TYPE_ENEMY)) {
                if (this->collider.base.atFlags & AT_BOUNCED) {
                    this->collider.base.atFlags &= ~(AT_HIT | AT_BOUNCED | AT_TYPE_ENEMY);
                    this->collider.base.atFlags |= AT_TYPE_PLAYER;
                    this->collider.info.toucher.dmgFlags = 0x400000;
                    this->collider.info.toucher.damage = 2;
                    Matrix_MtxFToYXZRot(&player->shieldMf, &sp48, false);
                    this->actor.world.rot.y = sp48.y + 0x8000;
                    this->unk18E = 0x16;
                    return;
                }
            }
        }

        sp54.x = this->actor.world.pos.x;
        sp54.y = this->actor.world.pos.y + 11.0f;
        sp54.z = this->actor.world.pos.z;
        EffectSsHahen_SpawnBurst(play, &sp54, 6.0f, 0, 1, 2, 15, OBJECT_OKUTA, 10, gOctorokProjectileDL);
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 20, NA_SE_EN_OCTAROCK_ROCK);

        if ((this->collider.base.atFlags & AT_HIT) && (this->collider.base.atFlags & AT_TYPE_ENEMY) &&
            !(this->collider.base.atFlags & AT_BOUNCED) &&
            (EN_OKUTA_GET_TYPE(&this->actor) == EN_OKUTA_TYPE_BLUE_PROJECTILE)) {
            func_800B8D98(play, &this->actor, 8.0f, this->actor.world.rot.y, 6.0f);
        }

        Actor_Kill(&this->actor);
        return;
    }

    if (this->unk18E == -0x12C) {
        Actor_Kill(&this->actor);
    }
}

/**
 * Adjusts the scale of the Octorok's head based on their current action and their current animation frame.
 */
void EnOkuta_UpdateHeadScale(EnOkuta* this) {
    f32 curFrame = this->skelAnime.curFrame;

    if (this->actionFunc == EnOkuta_Appear) {
        if (curFrame < 8.0f) {
            this->headScale.x = this->headScale.y = this->headScale.z = 1.0f;
        } else if (curFrame < 10.0f) {
            this->headScale.x = this->headScale.z = 1.0f;
            this->headScale.y = ((curFrame - 7.0f) * 0.4f) + 1.0f;
        } else if (curFrame < 14.0f) {
            this->headScale.x = this->headScale.z = ((curFrame - 9.0f) * 0.075f) + 1.0f;
            this->headScale.y = 1.8f - ((curFrame - 9.0f) * 0.25f);
        } else {
            this->headScale.x = this->headScale.z = 1.3f - ((curFrame - 13.0f) * 0.05f);
            this->headScale.y = ((curFrame - 13.0f) * 0.0333f) + 0.8f;
        }
    } else if (this->actionFunc == EnOkuta_Hide) {
        if (curFrame < 3.0f) {
            this->headScale.y = 1.0f;
        } else {
            if (curFrame < 4.0f) {
                this->headScale.y = (curFrame - 2.0f) + 1.0f;
            } else {
                this->headScale.y = 2.0f - ((curFrame - 3.0f) * 0.333f);
            }
        }
        this->headScale.x = this->headScale.z = 1.0f;
    } else if (this->actionFunc == EnOkuta_Shoot) {
        if (curFrame < 5.0f) {
            this->headScale.x = this->headScale.y = this->headScale.z = (curFrame * 0.125f) + 1.0f;
        } else if (curFrame < 7.0f) {
            this->headScale.x = this->headScale.y = this->headScale.z = 1.5f - ((curFrame - 4.0f) * 0.35f);
        } else if (curFrame < 17.0f) {
            this->headScale.x = this->headScale.z = ((curFrame - 6.0f) * 0.05f) + 0.8f;
            this->headScale.y = 0.8f;
        } else {
            this->headScale.x = this->headScale.z = 1.3f - ((curFrame - 16.0f) * 0.1f);
            this->headScale.y = ((curFrame - 16.0f) * 0.0666f) + 0.8f;
        }
    } else if (this->actionFunc == EnOkuta_Float) {
        this->headScale.x = this->headScale.z = 1.0f;
        this->headScale.y = Math_SinF((M_PI / 16) * curFrame) * 0.2f + 1.0f;
    } else {
        this->headScale.x = this->headScale.y = this->headScale.z = 1.0f;
    }
}

void EnOkuta_UpdateDamage(EnOkuta* this, PlayState* play) {
    if (!(this->collider.base.acFlags & AC_HIT)) {
        return;
    }

    this->collider.base.acFlags &= ~AC_HIT;

    if (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX ||
        !(this->collider.info.acHitInfo->toucher.dmgFlags & 0xDB0B3)) {
        Actor_SetDropFlag(&this->actor, &this->collider.info);
        func_8086E0F0(this, play);

        if (this->actor.colChkInfo.damageEffect == 3) {
            func_8086F2FC(this, play);
            return;
        }

        if (this->actor.colChkInfo.damageEffect == 4) {
            this->drawDmgEffAlpha = 4.0f;
            this->drawDmgEffScale = 0.6f;
            this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
            Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->collider.info.bumper.hitPos.x,
                        this->collider.info.bumper.hitPos.y, this->collider.info.bumper.hitPos.z, 0, 0, 0,
                        CLEAR_TAG_PARAMS(CLEAR_TAG_LARGE_LIGHT_RAYS));
        }

        if (Actor_ApplyDamage(&this->actor) == 0) {
            Enemy_StartFinishingBlow(play, &this->actor);
        }

        EnOkuta_SetupDamaged(this);
    }
}

void EnOkuta_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnOkuta* this = THIS;
    s32 pad[2];

    if (EN_OKUTA_GET_TYPE(&this->actor) == EN_OKUTA_TYPE_RED_OCTOROK) {
        EnOkuta_UpdateDamage(this, play);
    } else if ((this->collider.base.atFlags & AT_HIT) || (this->collider.base.acFlags & AC_HIT)) {
        if (this->collider.base.atFlags & AT_HIT) {
            func_800B8D98(play, &this->actor, 8.0f, this->actor.world.rot.y, 6.0f);
        }

        func_8086F4F4(this);
    }

    this->actionFunc(this, play);

    if (this->actionFunc != func_8086F434) {
        EnOkuta_UpdateHeadScale(this);
        this->collider.dim.height =
            (sOctorokCylinderInit.dim.height * this->headScale.y - this->collider.dim.yShift) * this->actor.scale.y * 100.0f;
        Collider_UpdateCylinder(&this->actor, &this->collider);

        if (this->actionFunc == EnOkuta_Appear || this->actionFunc == EnOkuta_Hide) {
            this->collider.dim.pos.y = this->actor.world.pos.y + this->skelAnime.jointTable->y * this->actor.scale.y;
            this->collider.dim.radius = sOctorokCylinderInit.dim.radius * this->actor.scale.x * 100.0f;
        }

        if (this->actor.draw != NULL) {
            if (EN_OKUTA_GET_TYPE(&this->actor) == EN_OKUTA_TYPE_BLUE_OCTOROK) {
                CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
            }

            if (this->collider.base.acFlags & AC_ON) {
                CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
            }

            CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
            EnOkuta_SpawnRipple(this, play);
        }

        Actor_SetFocus(&this->actor, 15.0f);

        if (this->drawDmgEffAlpha > 0.0f) {
            if (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
                Math_StepToF(&this->drawDmgEffAlpha, 0.0f, 0.05f);
                this->drawDmgEffScale = (this->drawDmgEffAlpha + 1.0f) * 0.3f;
                this->drawDmgEffScale = CLAMP_MAX(this->drawDmgEffScale, 0.6f);
                return;
            }

            if (!Math_StepToF(&this->drawDmgEffFrozenSteamScale, 0.6f, 15.0f * 0.001f)) {
                Actor_PlaySfx_Flagged(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
            }
        }
    }
}

void func_808700C0(Actor* thisx, PlayState* play) {
    EnOkuta* this = THIS;
    Player* player = GET_PLAYER(play);
    s32 pad;
    Vec3f sp38;
    s32 sp34 = 0;

    if (!(player->stateFlags1 & (PLAYER_STATE1_2 | PLAYER_STATE1_40 | PLAYER_STATE1_80 | PLAYER_STATE1_200 |
                                 PLAYER_STATE1_10000000 | PLAYER_STATE1_20000000))) {
        this->actionFunc(this, play);
        Actor_MoveWithoutGravity(&this->actor);
        Math_Vec3f_Copy(&sp38, &this->actor.world.pos);
        Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, 15.0f, 30.0f,
                                UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_4);

        if ((this->actor.bgCheckFlags & BGCHECKFLAG_WALL) &&
            (SurfaceType_IsIgnoredByProjectiles(&play->colCtx, this->actor.wallPoly, this->actor.wallBgId))) {
            sp34 = 1;
            this->actor.bgCheckFlags &= ~BGCHECKFLAG_WALL;
        }

        if ((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) &&
            (SurfaceType_IsIgnoredByProjectiles(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId))) {
            sp34 = 1;
            this->actor.bgCheckFlags &= ~BGCHECKFLAG_GROUND;
        }

        if (sp34 && (this->actor.bgCheckFlags & (BGCHECKFLAG_GROUND | BGCHECKFLAG_WALL)) == 0) {
            Math_Vec3f_Copy(&this->actor.world.pos, &sp38);
        }

        Collider_UpdateCylinder(&this->actor, &this->collider);
        this->actor.flags |= ACTOR_FLAG_1000000;
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
}

/**
 * Returns true if the snout scale should be updated, false otherwise. The snout scale is returned via the scale
 * parameter.
 */
s32 EnOkuta_GetSnoutScale(EnOkuta* this, f32 curFrame, Vec3f* scale) {
    if (this->actionFunc == EnOkuta_Float) {
        scale->z = scale->y = 1.0f;
        scale->x = Math_SinF((M_PI / 16) * curFrame) * 0.4f + 1.0f;
    } else if (this->actionFunc == EnOkuta_Shoot) {
        if (curFrame < 5.0f) {
            scale->z = 1.0f;
            scale->x = scale->y = (curFrame * 0.25f) + 1.0f;
        } else if (curFrame < 7.0f) {
            scale->z = (curFrame - 4.0f) * 0.5f + 1.0f;
            scale->x = scale->y = 2.0f - (curFrame - 4.0f) * 0.5f;
        } else {
            scale->z = 2.0f - ((curFrame - 6.0f) * 0.0769f);
            scale->x = scale->y = 1.0f;
        }
    } else if (this->actionFunc == EnOkuta_Die) {
        if (curFrame >= 35.0f || curFrame < 25.0f) {
            return false;
        }

        if (curFrame < 27.0f) {
            scale->z = 1.0f;
            scale->x = scale->y = (curFrame - 24.0f) * 0.5f + 1.0f;
        } else if (curFrame < 30.0f) {
            scale->z = (curFrame - 26.0f) * 0.333f + 1.0f;
            scale->x = scale->y = 2.0f - (curFrame - 26.0f) * 0.333f;
        } else {
            scale->z = 2.0f - ((curFrame - 29.0f) * 0.2f);
            scale->x = scale->y = 1.0f;
        }
    } else {
        return false;
    }

    return true;
}

s32 EnOkuta_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnOkuta* this = THIS;
    f32 curFrame;
    Vec3f scale;
    s32 var_v1;

    var_v1 = 0;
    curFrame = this->skelAnime.curFrame;
    if (this->actionFunc == EnOkuta_Die) {
        curFrame += this->unk18E;
    }
    if (limbIndex == OCTOROK_LIMB_HEAD) {
        if (this->headScale.x != 1.0f || this->headScale.y != 1.0f || this->headScale.z != 1.0f) {
            Math_Vec3f_Copy(&scale, &this->headScale);
            var_v1 = 1;
        }
    } else if (limbIndex == OCTOROK_LIMB_SNOUT) {
        var_v1 = EnOkuta_GetSnoutScale(this, curFrame, &scale);
    }
    if (var_v1) {
        Matrix_Scale(scale.x, scale.y, scale.z, MTXMODE_APPLY);
    }
    return 0;
}

static s8 D_80870944[16] = { -1, 0, -1, -1, 1, -1, -1, 2, -1, -1, 3, -1, -1, 4, 6, 5 };

static Vec3f D_80870954[3] = {
    { 1500.0f, 1000.0f, 0.0f },
    { -1500.0f, 1000.0f, 0.0f },
    { 0.0f, 1500.0f, -2000.0f },
};

void EnOkuta_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnOkuta* this = THIS;
    s32 limb = D_80870944[limbIndex];
    s32 i;

    if (limb != -1) {
        if (limb == 5) {
            Matrix_MultVecX(1500.0f, &this->bodyPartsPos[limb]);
        } else if (limb == 6) {
            Matrix_MultVecY(2800.0f, &this->bodyPartsPos[limb]);
            limb++;
            for (i = 0; i < ARRAY_COUNT(D_80870954); i++) {
                Matrix_MultVec3f(&D_80870954[i], &this->bodyPartsPos[limb + i]);
            }
        } else {
            Matrix_MultZero(&this->bodyPartsPos[limb]);
        }
    }
}

void EnOkuta_Draw(Actor* thisx, PlayState* play) {
    EnOkuta* this = THIS;
    s32 pad;
    Gfx* gfx;

    OPEN_DISPS(play->state.gfxCtx);

    gfx = POLY_OPA_DISP;

    gSPDisplayList(&gfx[0], gSetupDLs[SETUPDL_25]);

    if (EN_OKUTA_GET_TYPE(&this->actor) < EN_OKUTA_TYPE_PROJECTILE_BASE) {
        if (EN_OKUTA_GET_TYPE(&this->actor) == EN_OKUTA_TYPE_RED_OCTOROK) {
            gSPSegment(&gfx[1], 0x08, D_801AEFA0);
        } else {
            gSPSegment(&gfx[1], 0x08, ovl_En_Okuta_DL_2A50);
        }

        POLY_OPA_DISP = &gfx[2];
        SkelAnime_DrawOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, EnOkuta_OverrideLimbDraw,
                          EnOkuta_PostLimbDraw, &this->actor);
    } else {
        Matrix_Mult(&play->billboardMtxF, MTXMODE_APPLY);
        Matrix_RotateZS(this->actor.home.rot.z, MTXMODE_APPLY);
        gSPMatrix(&gfx[1], Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(&gfx[2], gOctorokProjectileDL);
        POLY_OPA_DISP = &gfx[3];
    }

    CLOSE_DISPS(play->state.gfxCtx);

    Actor_DrawDamageEffects(play, &this->actor, this->bodyPartsPos, 10,
                            this->drawDmgEffScale * this->actor.scale.y * 100.0f, this->drawDmgEffFrozenSteamScale,
                            this->drawDmgEffAlpha, this->drawDmgEffType);
}
