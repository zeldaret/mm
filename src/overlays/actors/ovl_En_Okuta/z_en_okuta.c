/*
 * File: z_en_okuta.c
 * Overlay: ovl_En_Okuta
 * Description: Octorok
 */

#include "z_en_okuta.h"

#include "objects/object_okuta/object_okuta.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY)

#define THIS ((EnOkuta*)thisx)

void EnOkuta_Init(Actor* thisx, PlayState* play2);
void EnOkuta_Destroy(Actor* thisx, PlayState* play);
void EnOkuta_Update(Actor* thisx, PlayState* play2);
void EnOkuta_Draw(Actor* thisx, PlayState* play);

void func_8086E4FC(EnOkuta* this);
void func_8086E52C(EnOkuta* this, PlayState* play);
void func_8086E5E8(EnOkuta* this, PlayState* play);
void func_8086E658(EnOkuta* this, PlayState* play);
void func_8086E7A8(EnOkuta* this);
void func_8086E7E8(EnOkuta* this, PlayState* play);
void func_8086E8E8(EnOkuta* this);
void func_8086E948(EnOkuta* this, PlayState* play);
void func_8086EAE0(EnOkuta* this, PlayState* play);
void func_8086EC00(EnOkuta* this, PlayState* play);
void func_8086EF14(EnOkuta* this, PlayState* play);
void func_8086EF90(EnOkuta* this);
void func_8086EFE8(EnOkuta* this, PlayState* play);
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

static ColliderCylinderInit sCylinderInit = {
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

static ColliderCylinderInit sCylinderInit2 = {
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

static Color_RGBA8 D_80870928 = { 255, 255, 255, 255 };

static Color_RGBA8 D_8087092C = { 150, 150, 150, 255 };

static Vec3f D_80870930 = { 0.0f, -0.5f, 0.0f };

static Color_RGBA8 D_8087093C = { 255, 255, 255, 255 };

static Color_RGBA8 D_80870940 = { 150, 150, 150, 0 };

static s8 D_80870944[16] = { -1, 0, -1, -1, 1, -1, -1, 2, -1, -1, 3, -1, -1, 4, 6, 5 };

static Vec3f D_80870954[3] = {
    { 1500.0f, 1000.0f, 0.0f },
    { -1500.0f, 1000.0f, 0.0f },
    { 0.0f, 1500.0f, -2000.0f },
};

static s32 D_80870978[] = { 0, 0 };

void EnOkuta_Init(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnOkuta* this = THIS;
    WaterBox* sp3C;
    f32 sp38;
    s32 sp34;

    Actor_ProcessInitChain(thisx, sInitChain);
    this->unk190 = (thisx->params >> 8) & 0xFF;
    thisx->params &= 0xFF;
    if (thisx->params == 0 || thisx->params == 1) {
        SkelAnime_Init(play, &this->unk144, &gOctorokSkel, &gOctorokAppearAnim, &this->unk192, &this->unk1F2, 0x10);
        Collider_InitAndSetCylinder(play, &this->unk2E8, thisx, &sCylinderInit2);
        CollisionCheck_SetInfo(&thisx->colChkInfo, &sDamageTable, &sColChkInfoInit);
        if (this->unk190 == 0xFF || this->unk190 == 0) {
            this->unk190 = 1;
        }
        thisx->floorHeight =
            BgCheck_EntityRaycastFloor5(&play->colCtx, &thisx->floorPoly, &sp34, thisx, &thisx->world.pos);
        if (!WaterBox_GetSurface1_2(play, &play->colCtx, thisx->world.pos.x, thisx->world.pos.z, &sp38, &sp3C) ||
            sp38 <= thisx->floorHeight) {
            Actor_Kill(thisx);
        } else {
            thisx->home.pos.y = sp38;
        }
        if (thisx->params == 1) {
            this->unk2E8.base.colType = 0xC;
            this->unk2E8.base.acFlags |= 4;
        }
        thisx->targetMode = 5;
        func_8086E4FC(this);
    } else {
        ActorShape_Init(&thisx->shape, 1100.0f, ActorShadow_DrawCircle, 18.0f);
        thisx->flags &= ~1;
        thisx->flags |= 0x10;
        Collider_InitAndSetCylinder(play, &this->unk2E8, thisx, &sCylinderInit);
        Actor_ChangeCategory(play, &play->actorCtx, thisx, 6);
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
    Collider_DestroyCylinder(play, &this->unk2E8);
}

void func_8086E084(EnOkuta* this) {
    this->unk18C = 0xA;
    this->unk258 = 0.6f;
    this->unk25C = 0.90000004f;
    this->unk254 = 1.0f;
    this->unk18E = 0x50;
    this->unk2E8.base.colType = 3;
    Actor_SetColorFilter(&this->actor, 0x4000U, 0xFFU, 0U, 0x50U);
}

void func_8086E0F0(EnOkuta* this, PlayState* play) {
    if (this->unk18C == 0xA) {
        this->unk18C = 0;
        this->unk254 = 0.0f;
        Actor_SpawnIceEffects(play, &this->actor, this->unk270, 0xA, 2, 0.3f, 0.2f);
        this->unk2E8.base.colType = 0;
    }
}

void func_8086E168(EnOkuta* this, PlayState* play) {
    s32 i;

    for (i = 0; i != 0xA; i++) {
        EffectSsBubble_Spawn(play, &this->actor.world.pos, -10.0f, 10.0f, 30.0f, 0.25f);
    }
}

void func_8086E214(Vec3f* pos, Vec3f* velocity, s32 arg2, PlayState* play) {
    func_800B0DE0(play, pos, velocity, &gZeroVec3f, &D_80870928, &D_8087092C, 0x190, (s16)(s32)(s16)arg2);
}

void func_8086E27C(EnOkuta* this, PlayState* play) {
    EffectSsGSplash_Spawn(play, &this->actor.home.pos, NULL, NULL, 0, 0x514);
}

void func_8086E2C0(EnOkuta* this, PlayState* play) {
    f32 temp;
    Vec3f sp28;

    temp = this->actor.world.pos.y - this->actor.home.pos.y;
    if (((play->gameplayFrames % 7) == 0) && (temp < 50.0f) && (temp >= -20.0f)) {

        sp28.x = this->actor.world.pos.x;
        sp28.y = this->actor.home.pos.y;
        sp28.z = this->actor.world.pos.z;
        EffectSsGRipple_Spawn(play, &sp28, 0xFA, 0x28A, 0);
    }
}

f32 func_8086E378(EnOkuta* this) {
    f32 height = this->actor.world.pos.y + this->actor.playerHeightRel + 60.0f;

    if (this->actor.home.pos.y < height) {
        return this->actor.home.pos.y;
    }
    return height;
}

void func_8086E3B8(EnOkuta* this, PlayState* play) {
    Vec3f sp4C;
    Vec3f sp40;
    f32 s;
    f32 c;

    s = Math_SinS(this->actor.shape.rot.y);
    c = Math_CosS(this->actor.shape.rot.y);
    sp4C.x = this->actor.world.pos.x + 25.0f * s;
    sp4C.y = this->actor.world.pos.y - 6.0f;
    sp4C.z = this->actor.world.pos.z + 25.0f * c;
    if (Actor_Spawn(&play->actorCtx, play, 8, sp4C.x, sp4C.y, sp4C.z, this->actor.shape.rot.x, this->actor.shape.rot.y,
                    this->actor.shape.rot.z, this->actor.params + 0x10) != NULL) {
        sp4C.x = this->actor.world.pos.x + (40.0f * s);
        sp4C.z = this->actor.world.pos.z + (40.0f * c);
        sp4C.y = this->actor.world.pos.y;

        sp40.x = 1.5f * s;
        sp40.y = 0.0f;
        sp40.z = 1.5f * c;
        func_8086E214(&sp4C, &sp40, 0x14, play);
    }
    Actor_PlaySfx(&this->actor, 0x387EU);
}

void func_8086E4FC(EnOkuta* this) {
    this->actor.draw = NULL;
    this->actor.world.pos.y = this->actor.home.pos.y;
    this->actor.flags &= ~1;
    this->actionFunc = func_8086E52C;
}

void func_8086E52C(EnOkuta* this, PlayState* play) {
    this->actor.world.pos.y = this->actor.home.pos.y;
    if (this->actor.xzDistToPlayer < 480.0f && this->actor.xzDistToPlayer > 200.0f) {
        if (this->actor.params == 0) {
            func_8086E5E8(this, play);
        } else if (ABS_ALT((s16)(this->actor.yawTowardsPlayer - this->actor.world.rot.y)) < 0x4000 &&
                   play->unk_1887C == 0) {
            func_8086E5E8(this, play);
        }
    }
}

void func_8086E5E8(EnOkuta* this, PlayState* play) {
    this->actor.draw = EnOkuta_Draw;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    this->actor.flags |= 1;
    Animation_PlayOnce(&this->unk144, &gOctorokAppearAnim);
    func_8086E168(this, play);
    this->actionFunc = func_8086E658;
}

void func_8086E658(EnOkuta* this, PlayState* play) {
    f32 curFrame;

    if (SkelAnime_Update(&this->unk144) != 0) {
        if ((this->actor.xzDistToPlayer < 160.0f) && (this->actor.params == 0)) {
            func_8086E7A8(this);
        } else {
            func_8086E8E8(this);
        }
    } else {
        curFrame = this->unk144.curFrame;
        if (curFrame <= 4.0f) {
            Actor_SetScale(&this->actor, curFrame * 0.25f * 0.01f);
        } else if (Animation_OnFrame(&this->unk144, 5.0f) != 0) {
            Actor_SetScale(&this->actor, 0.01f);
        }
    }
    if (Animation_OnFrame(&this->unk144, 2.0f) != 0) {
        Actor_PlaySfx(&this->actor, 0x38C2U);
    }
    if (Animation_OnFrame(&this->unk144, 12.0f) != 0) {
        Actor_PlaySfx(&this->actor, 0x38C3U);
    }
    if ((Animation_OnFrame(&this->unk144, 3.0f) != 0) || (Animation_OnFrame(&this->unk144, 15.0f) != 0)) {
        func_8086E27C(this, play);
    }
}

void func_8086E7A8(EnOkuta* this) {
    Animation_PlayOnce(&this->unk144, &gOctorokHideAnim);
    this->actionFunc = func_8086E7E8;
}

void func_8086E7E8(EnOkuta* this, PlayState* play) {
    f32 curFrame;

    Math_ApproachF(&this->actor.world.pos.y, this->actor.home.pos.y, 0.5f, 30.0f);
    if (SkelAnime_Update(&this->unk144) != 0) {
        Actor_PlaySfx(&this->actor, 0x38C5U);
        func_8086E168(this, play);
        func_8086E4FC(this);
    } else {
        curFrame = this->unk144.curFrame;
        if (curFrame >= 4.0f) {
            Actor_SetScale(&this->actor, (6.0f - curFrame) * 0.5f * 0.01f);
        }
    }
    if (Animation_OnFrame(&this->unk144, 2.0f) != 0) {
        Actor_PlaySfx(&this->actor, 0x38C4U);
    }
    if (Animation_OnFrame(&this->unk144, 4.0f) != 0) {
        func_8086E27C(this, play);
    }
}

void func_8086E8E8(EnOkuta* this) {
    Animation_PlayLoop(&this->unk144, &gOctorokFloatAnim);
    if (this->actionFunc == func_8086EC00) {
        this->unk18E = 8;
    } else {
        this->unk18E = 0;
    }
    this->actionFunc = func_8086E948;
}

void func_8086E948(EnOkuta* this, PlayState* play) {
    s16 var_v1;

    if (this->actor.params == 0) {
        this->actor.world.pos.y = this->actor.home.pos.y;
    } else {
        this->actor.world.pos.y = func_8086E378(this);
    }
    SkelAnime_Update(&this->unk144);
    if (Animation_OnFrame(&this->unk144, 0.0f) != 0) {
        if (this->unk18E != 0) {
            this->unk18E = this->unk18E - 1;
        }
    }
    if (Animation_OnFrame(&this->unk144, 0.5f) != 0) {
        Actor_PlaySfx(&this->actor, 0x38C1U);
    }
    if ((this->actor.xzDistToPlayer > 560.0f) || ((this->actor.xzDistToPlayer < 160.0f) && (this->actor.params == 0))) {
        func_8086E7A8(this);
    } else {
        var_v1 = Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0xE38, 0x38E);
        if ((ABS_ALT(var_v1) < 0x38E) &&
            ((((this->actor.params == 0)) && (this->unk18E == 0) && (this->actor.playerHeightRel < 120.0f)) ||
             ((this->actor.params == 1) && ((this->unk18E == 0) || (this->actor.xzDistToPlayer < 150.0f))))) {
            func_8086EAE0(this, play);
        }
    }
}

void func_8086EAE0(EnOkuta* this, PlayState* play) {
    Animation_PlayOnce(&this->unk144, &gOctorokShootAnim);
    if (this->actionFunc != func_8086EC00) {
        if (this->actor.params == 0) {
            this->unk18E = this->unk190;
        } else {
            this->unk18E = (560.0f - this->actor.xzDistToPlayer) * 0.005f + 1.0f;
        }
    }
    if (this->actor.params == 0) {
        this->unk260 = this->actor.playerHeightRel + 20.0f;
        if (this->unk260 < 10.0f) {
            this->unk260 = 10.0f;
        } else {
            this->unk260 = this->unk260;
        }
        if (this->unk260 > 50.0f) {
            func_8086E27C(this, play);
            Actor_PlaySfx(&this->actor, 0x38C2U);
        }
    }
    this->actionFunc = func_8086EC00;
}

void func_8086EC00(EnOkuta* this, PlayState* play) {
    f32 curFrame;   // 44
    Player* player; // 40
    Vec3f sp34;     // 34, 38, 3c
    s16 sp32;

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0x71C);
    if (SkelAnime_Update(&this->unk144) != 0) {
        if (this->unk18E != 0) {
            this->unk18E--;
        }
        if (this->unk18E == 0) {
            if ((this->actor.params != 1) || (this->actor.xzDistToPlayer > 150.0f)) {
                func_8086E8E8(this);
            } else {
                func_8086EAE0(this, play);
            }
        } else {
            func_8086EAE0(this, play);
        }
    } else {
        if (this->actor.params == 0) {
            if ((curFrame = this->unk144.curFrame) < 13.0f) {
                this->actor.world.pos.y = Math_SinF(0.2617889f * curFrame) * this->unk260 + this->actor.home.pos.y;
            }
            if (this->unk260 > 50.0f && Animation_OnFrame(&this->unk144, 13.0f)) {
                func_8086E27C(this, play);
                Actor_PlaySfx(&this->actor, 0x38C3U);
            }
        } else {
            this->actor.world.pos.y = func_8086E378(this);
            if ((curFrame = this->unk144.curFrame) < 13.0f) {
                player = GET_PLAYER(play);
                sp34.x = player->actor.world.pos.x;
                sp34.y = player->actor.world.pos.y + 20.0f;
                sp34.z = player->actor.world.pos.z;
                sp32 = Actor_WorldPitchTowardPoint(&this->actor, &sp34);
                sp32 = CLAMP(sp32, -0x2AAA, 0);
                this->actor.shape.rot.x = Math_SinF(0.2617889f * curFrame) * sp32;
            }
        }
        if (Animation_OnFrame(&this->unk144, 6.0f) != 0) {
            func_8086E3B8(this, play);
        }
    }
    if (this->actor.params == 0 && this->actor.xzDistToPlayer < 160.0f) {
        func_8086E7A8(this);
    }
}

void func_8086EE8C(EnOkuta* this) {
    Animation_MorphToPlayOnce(&this->unk144, &gOctorokHitAnim, -5.0f);
    Actor_SetColorFilter(&this->actor, 0x4000U, 0xFFU, 0U, 0xBU);
    this->unk2E8.base.acFlags &= ~1;
    Actor_SetScale(&this->actor, 0.01f);
    Actor_PlaySfx(&this->actor, 0x38C6U);
    this->actionFunc = func_8086EF14;
}

void func_8086EF14(EnOkuta* this, PlayState* play) {
    if (SkelAnime_Update(&this->unk144) != 0) {
        if (this->actor.colChkInfo.health == 0) {
            func_8086EF90(this);
        } else {
            this->unk2E8.base.acFlags |= 1;
            func_8086E8E8(this);
        }
    }
    Math_ApproachF(&this->actor.world.pos.y, this->actor.home.pos.y, 0.5f, 5.0f);
}

void func_8086EF90(EnOkuta* this) {
    Animation_MorphToPlayOnce(&this->unk144, &gOctorokDieAnim, -3.0f);
    this->unk18E = 0;
    this->actor.flags &= ~1;
    this->actionFunc = func_8086EFE8;
}

void func_8086EFE8(EnOkuta* this, PlayState* play) {
    Vec3f sp7C;
    Vec3f sp70;
    SkelAnime* temp_s0;
    s32 i;

    temp_s0 = &this->unk144;
    if (SkelAnime_Update(temp_s0) != 0) {
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
        func_8086E214(&sp70, &sp7C, -0x14, play);
        Actor_PlaySfx(&this->actor, 0x38C7U);
    }
    if (Animation_OnFrame(temp_s0, 15.0f) != 0) {
        func_8086E27C(this, play);
        Actor_PlaySfx(&this->actor, 0x38C3U);
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
    if (Math_StepToF(&this->actor.scale.x, 0.0f, 0.0005f) != 0) {
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 0x1EU, 0x38C5U);
        Item_DropCollectibleRandom(play, &this->actor, &this->actor.world.pos, 0xA0);
        for (i = 0; i != 0x14; i++) {
            sp7C.x = (Rand_ZeroOne() - 0.5f) * 7.0f;
            sp7C.y = Rand_ZeroOne() * 7.0f;
            sp7C.z = (Rand_ZeroOne() - 0.5f) * 7.0f;
            EffectSsDtBubble_SpawnCustomColor(play, &this->actor.world.pos, (Vec3f*)&sp7C, &D_80870930, &D_8087093C,
                                              &D_80870940, (s16)Rand_S16Offset(0x64, 0x32), 0x19, 0);
        }
        Actor_Kill(&this->actor);
    }
    this->actor.scale.z = this->actor.scale.x;
    this->actor.scale.y = this->actor.scale.x;
}

void func_8086F2FC(EnOkuta* this, PlayState* play) {
    this->unk18E = 0xA;
    Actor_SetColorFilter(&this->actor, 0x8000U, 0x80FFU, 0U, 0xAU);
    this->actor.child = Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, 0x143, this->actor.world.pos.x,
                                           this->actor.world.pos.y + this->unk144.jointTable->y * this->actor.scale.y +
                                               25.0f * this->unk264.y,
                                           this->actor.world.pos.z, 0, this->actor.home.rot.y, 0, 3);
    if (this->actor.child != NULL) {
        this->actor.flags &= ~1;
        this->actor.flags |= 0x10;
        this->actor.child->csId = this->actor.csId;
        this->actionFunc = func_8086F434;
        return;
    }
    func_8086E084(this);
    if (Actor_ApplyDamage(&this->actor) == 0) {
        Enemy_StartFinishingBlow(play, &this->actor);
        this->unk2E8.base.acFlags &= 0xFFFE;
        this->unk18E = 3;
    }
    this->actionFunc = func_8086F4B0;
}

void func_8086F434(EnOkuta* this, PlayState* play) {
    this->actor.colorFilterTimer = 0xA;
    if ((this->actor.child == NULL) || (this->actor.child->update == NULL)) {
        this->actor.flags |= 1;
        if (Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y, 10.0f) != 0) {
            this->actor.flags &= ~0x10;
            func_8086E8E8(this);
        }
    }
}

void func_8086F4B0(EnOkuta* this, PlayState* play) {
    if (this->unk18E != 0) {
        this->unk18E--;
    }
    if (this->unk18E == 0) {
        func_8086E0F0(this, play);
        func_8086EE8C(this);
    }
}

void func_8086F4F4(EnOkuta* this) {
    Animation_Change(&this->unk144, &gOctorokHitAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gOctorokHitAnim) - 3.0f, 2U,
                     -3.0f);
    this->unk18E = 0x14;
    this->actionFunc = func_8086F57C;
}

void func_8086F57C(EnOkuta* this, PlayState* play) {
    this->unk18E -= 1;
    Math_ScaledStepToS(&this->actor.shape.rot.x, 0, 0x400);
    if (SkelAnime_Update(&this->unk144) != 0) {
        Animation_Change(&this->unk144, &gOctorokHitAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gOctorokHitAnim) - 3.0f,
                         2U, -3.0f);
    }
    if (this->unk18E < 0xA) {
        this->actor.shape.rot.y += (s16)(8192.0f * Math_SinF(this->unk18E * 0.15707964f));
    } else {
        this->actor.shape.rot.y += 0x2000;
    }
    if (this->unk18E == 0) {
        func_8086E8E8(this);
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
    if ((this->actor.bgCheckFlags & 8) || (this->actor.bgCheckFlags & 1) || (this->actor.bgCheckFlags & 0x10) ||
        (this->unk2E8.base.atFlags & 2) || (this->unk2E8.base.acFlags & 2) || (this->unk2E8.base.ocFlags1 & 2) ||
        (this->actor.floorHeight == -32000.0f)) {
        if (player->currentShield == 1) {
            if ((this->unk2E8.base.atFlags & 2) && (this->unk2E8.base.atFlags & 0x10)) {
                if (this->unk2E8.base.atFlags & 4) {
                    this->unk2E8.base.atFlags &= ~0x16;
                    this->unk2E8.base.atFlags |= 8;
                    this->unk2E8.info.toucher.dmgFlags = 0x400000;
                    this->unk2E8.info.toucher.damage = 2;
                    Matrix_MtxFToYXZRot(&player->shieldMf, &sp48, 0);
                    this->actor.world.rot.y = sp48.y + 0x8000;
                    this->unk18E = 0x16;
                    return;
                }
            }
        }
        sp54.x = this->actor.world.pos.x;
        sp54.y = this->actor.world.pos.y + 11.0f;
        sp54.z = this->actor.world.pos.z;
        EffectSsHahen_SpawnBurst(play, &sp54, 6.0f, 0, 1, 2, 0xF, 5, 0xA, gOctorokProjectileDL);
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 0x14U, 0x38C0U);
        if ((this->unk2E8.base.atFlags & 2) && (this->unk2E8.base.atFlags & 0x10) && !(this->unk2E8.base.atFlags & 4) &&
            (this->actor.params == 0x11)) {
            func_800B8D98(play, &this->actor, 8.0f, this->actor.world.rot.y, 6.0f);
        }
        Actor_Kill(&this->actor);
        return;
    }
    if (this->unk18E == -0x12C) {
        Actor_Kill(&this->actor);
    }
}

void func_8086F8FC(EnOkuta* this) {
    f32 curFrame = this->unk144.curFrame;

    if (this->actionFunc == func_8086E658) {
        if (curFrame < 8.0f) {
            this->unk264.x = this->unk264.y = this->unk264.z = 1.0f;
        } else if (curFrame < 10.0f) {
            this->unk264.x = this->unk264.z = 1.0f;
            this->unk264.y = ((curFrame - 7.0f) * 0.4f) + 1.0f;
        } else if (curFrame < 14.0f) {
            this->unk264.x = this->unk264.z = ((curFrame - 9.0f) * 0.075f) + 1.0f;
            this->unk264.y = 1.8f - ((curFrame - 9.0f) * 0.25f);
        } else {
            this->unk264.x = this->unk264.z = 1.3f - ((curFrame - 13.0f) * 0.05f);
            this->unk264.y = ((curFrame - 13.0f) * 0.0333f) + 0.8f;
        }
    } else if (this->actionFunc == func_8086E7E8) {
        if (curFrame < 3.0f) {
            this->unk264.y = 1.0f;
        } else {
            if (curFrame < 4.0f) {
                this->unk264.y = (curFrame - 2.0f) + 1.0f;
            } else {
                this->unk264.y = 2.0f - ((curFrame - 3.0f) * 0.333f);
            }
        }
        this->unk264.x = this->unk264.z = 1.0f;
    } else if (this->actionFunc == func_8086EC00) {
        if (curFrame < 5.0f) {
            this->unk264.x = this->unk264.y = this->unk264.z = (curFrame * 0.125f) + 1.0f;
        } else if (curFrame < 7.0f) {
            this->unk264.x = this->unk264.y = this->unk264.z = 1.5f - ((curFrame - 4.0f) * 0.35f);
        } else if (curFrame < 17.0f) {
            this->unk264.x = this->unk264.z = ((curFrame - 6.0f) * 0.05f) + 0.8f;
            this->unk264.y = 0.8f;
        } else {
            this->unk264.x = this->unk264.z = 1.3f - ((curFrame - 16.0f) * 0.1f);
            this->unk264.y = ((curFrame - 16.0f) * 0.0666f) + 0.8f;
        }
    } else if (this->actionFunc == func_8086E948) {
        this->unk264.x = this->unk264.z = 1.0f;
        this->unk264.y = Math_SinF(0.19634955f * curFrame) * 0.2f + 1.0f;
    } else {
        this->unk264.x = this->unk264.y = this->unk264.z = 1.0f;
    }
}

void func_8086FCA4(EnOkuta* this, PlayState* play) {
    if ((this->unk2E8.base.acFlags & 2) == 0) {
        return;
    }
    this->unk2E8.base.acFlags = this->unk2E8.base.acFlags & ~2;
    if (this->unk18C != 0xA || !(this->unk2E8.info.acHitInfo->toucher.dmgFlags & 0xDB0B3)) {
        Actor_SetDropFlag(&this->actor, &this->unk2E8.info);
        func_8086E0F0(this, play);
        if (this->actor.colChkInfo.damageEffect == 3) {
            func_8086F2FC(this, play);
            return;
        }
        if (this->actor.colChkInfo.damageEffect == 4) {
            this->unk254 = 4.0f;
            this->unk258 = 0.6f;
            this->unk18C = 0x14;
            Actor_Spawn(&play->actorCtx, play, 0xA2, this->unk2E8.info.bumper.hitPos.x,
                        this->unk2E8.info.bumper.hitPos.y, this->unk2E8.info.bumper.hitPos.z, 0, 0, 0, 4);
        }
        if (Actor_ApplyDamage(&this->actor) == 0) {
            Enemy_StartFinishingBlow(play, &this->actor);
        }
        func_8086EE8C(this);
    }
}

void EnOkuta_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnOkuta* this = THIS;
    s32 pad[2];

    if (this->actor.params == 0) {
        func_8086FCA4(this, play);
    } else if ((this->unk2E8.base.atFlags & 2) || (this->unk2E8.base.acFlags & 2)) {
        if (this->unk2E8.base.atFlags & 2) {
            func_800B8D98(play, &this->actor, 8.0f, this->actor.world.rot.y, 6.0f);
        }
        func_8086F4F4(this);
    }

    this->actionFunc(this, play);
    if (this->actionFunc != func_8086F434) {
        func_8086F8FC(this);
        this->unk2E8.dim.height =
            (sCylinderInit2.dim.height * this->unk264.y - this->unk2E8.dim.yShift) * this->actor.scale.y * 100.0f;
        Collider_UpdateCylinder(&this->actor, &this->unk2E8);
        if (this->actionFunc == func_8086E658 || this->actionFunc == func_8086E7E8) {
            this->unk2E8.dim.pos.y = this->actor.world.pos.y + this->unk144.jointTable->y * this->actor.scale.y;
            this->unk2E8.dim.radius = sCylinderInit2.dim.radius * this->actor.scale.x * 100.0f;
        }
        if (this->actor.draw != NULL) {
            if (this->actor.params == 1) {
                CollisionCheck_SetAT(play, &play->colChkCtx, &this->unk2E8.base);
            }
            if (this->unk2E8.base.acFlags & 1) {
                CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk2E8.base);
            }
            CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk2E8.base);
            func_8086E2C0(this, play);
        }
        Actor_SetFocus(&this->actor, 15.0f);
        if (this->unk254 > 0.0f) {
            if (this->unk18C != 0xA) {
                Math_StepToF(&this->unk254, 0.0f, 0.05f);
                this->unk258 = (this->unk254 + 1.0f) * 0.3f;
                this->unk258 = this->unk258 > 0.6f ? 0.6f : this->unk258;
                return;
            }
            if (Math_StepToF(&this->unk25C, 0.6f, 0.015000001f) == 0) {
                Actor_PlaySfx_Flagged(&this->actor, 0x20B2U);
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

    if (!(player->stateFlags1 & 0x300002C2)) {
        this->actionFunc(this, play);
        Actor_MoveWithoutGravity(&this->actor);
        Math_Vec3f_Copy(&sp38, &this->actor.world.pos);
        Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, 15.0f, 30.0f, 7U);
        if ((this->actor.bgCheckFlags & 8) &&
            (SurfaceType_IsIgnoredByProjectiles(&play->colCtx, this->actor.wallPoly, (s32)this->actor.wallBgId) != 0)) {
            sp34 = 1;
            this->actor.bgCheckFlags &= ~8;
        }
        if ((this->actor.bgCheckFlags & 1) && (SurfaceType_IsIgnoredByProjectiles(&play->colCtx, this->actor.floorPoly,
                                                                                  (s32)this->actor.floorBgId) != 0)) {
            sp34 = 1;
            this->actor.bgCheckFlags &= ~1;
        }
        if (sp34 && (this->actor.bgCheckFlags & 9) == 0) {
            Math_Vec3f_Copy(&this->actor.world.pos, &sp38);
        }
        Collider_UpdateCylinder(&this->actor, &this->unk2E8);
        this->actor.flags |= 0x01000000;
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->unk2E8.base);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk2E8.base);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk2E8.base);
    }
}

s32 func_80870254(EnOkuta* this, f32 curFrame, Vec3f* scale) {
    if (this->actionFunc == func_8086E948) {
        scale->z = scale->y = 1.0f;
        scale->x = Math_SinF(0.19634955f * curFrame) * 0.4f + 1.0f;
    } else if (this->actionFunc == func_8086EC00) {
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
    } else if (this->actionFunc == func_8086EFE8) {
        if (curFrame >= 35.0f || curFrame < 25.0f) {
            return 0;
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
        return 0;
    }
    return 1;
}

s32 func_808704DC(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnOkuta* this = THIS;
    f32 curFrame;
    Vec3f scale;
    s32 var_v1;

    var_v1 = 0;
    curFrame = this->unk144.curFrame;
    if (this->actionFunc == func_8086EFE8) {
        curFrame += this->unk18E;
    }
    if (limbIndex == 14) {
        if (this->unk264.x != 1.0f || this->unk264.y != 1.0f || this->unk264.z != 1.0f) {
            Math_Vec3f_Copy(&scale, &this->unk264);
            var_v1 = 1;
        }
    } else if (limbIndex == 15) {
        var_v1 = func_80870254(this, curFrame, &scale);
    }
    if (var_v1) {
        Matrix_Scale(scale.x, scale.y, scale.z, MTXMODE_APPLY);
    }
    return 0;
}

void func_808705C8(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnOkuta* this = THIS;
    s32 limb = D_80870944[limbIndex];
    s32 i;

    if (limb != -1) {
        if (limb == 5) {
            Matrix_MultVecX(1500.0f, &this->unk270[limb]);
        } else if (limb == 6) {
            Matrix_MultVecY(2800.0f, &this->unk270[limb]);
            limb++;
            for (i = 0; i < ARRAY_COUNT(D_80870954); i++) {
                Matrix_MultVec3f(&D_80870954[i], &this->unk270[limb + i]);
            }
        } else {
            Matrix_MultZero(&this->unk270[limb]);
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

    if (this->actor.params < 0x10) {
        if (this->actor.params == 0) {
            gSPSegment(&gfx[1], 0x08, D_801AEFA0);
        } else {
            gSPSegment(&gfx[1], 0x08, ovl_En_Okuta_DL_2A50);
        }
        POLY_OPA_DISP = &gfx[2];
        SkelAnime_DrawOpa(play, this->unk144.skeleton, this->unk144.jointTable, func_808704DC, func_808705C8,
                          &this->actor);
    } else {
        Matrix_Mult(&play->billboardMtxF, MTXMODE_APPLY);
        Matrix_RotateZS(this->actor.home.rot.z, MTXMODE_APPLY);
        gSPMatrix(&gfx[1], Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(&gfx[2], gOctorokProjectileDL);
        POLY_OPA_DISP = &gfx[3];
    }

    CLOSE_DISPS(play->state.gfxCtx);

    Actor_DrawDamageEffects(play, &this->actor, this->unk270, 10, this->unk258 * this->actor.scale.y * 100.0f,
                            this->unk25C, this->unk254, this->unk18C);
}
