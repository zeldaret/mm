/*
 * File: z_en_tanron3.c
 * Overlay: ovl_En_Tanron3
 * Description: Small Fish summoned by Gyorg
 */

#include "z_en_tanron3.h"
#include "overlays/actors/ovl_Boss_03/z_boss_03.h"

#define FLAGS 0x00000035

#define THIS ((EnTanron3*)thisx)

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ Vec3f unk_04;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ Vec3f unk_1C;
    /* 0x28 */ char unk_28[0xC];
    /* 0x34 */ Vec3f unk_34;
    /* 0x40 */ char unk_40[0x4];
} UnkTanron3Effect;

void EnTanron3_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTanron3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTanron3_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTanron3_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BB897C(EnTanron3* this, GlobalContext* globalCtx);
void func_80BB8A48(EnTanron3* this, GlobalContext* globalCtx);
void EnTanron3_Kill(EnTanron3* this, GlobalContext* globalCtx);

static Vec3f D_80BB9720[] = { 0.0f, 0.0f, 0.0f };

static Boss03* boss03Parent = NULL;

const ActorInit En_Tanron3_InitVars = {
    ACTOR_EN_TANRON3,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS03,
    sizeof(EnTanron3),
    (ActorFunc)EnTanron3_Init,
    (ActorFunc)EnTanron3_Destroy,
    (ActorFunc)EnTanron3_Update,
    (ActorFunc)EnTanron3_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK3,
        { 0xF7CFFFFF, 0x00, 0x02 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 7, 10, -5, { 0, 0, 0 } },
};

// This actor has two colliders (one for AC and one for AT), but uses the same
// ColliderCylinderInit for both of them, leaving this one totally unused.
static ColliderCylinderInit sUnusedCylinderInit = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK3,
        { 0xF7CFFFFF, 0x00, 0x02 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 20, 20, -10, { 0, 0, 0 } },
};

extern FlexSkeletonHeader D_0600DA20;
extern AnimationHeader D_0600DAAC;

void EnTanron3_CreateEffect(GlobalContext* globalCtx, Vec3f* pos) {
    UnkTanron3Effect* effectPtr;
    s16 i;

    effectPtr = (UnkTanron3Effect*)globalCtx->specialEffects;
    for (i = 0; i < 150; i++, effectPtr++) {
        if ((effectPtr->unk_00 == 0) || (effectPtr->unk_00 == 1)) {
            effectPtr->unk_00 = 2;
            effectPtr->unk_04 = *pos;
            effectPtr->unk_10 = *D_80BB9720;
            effectPtr->unk_1C = *D_80BB9720;
            effectPtr->unk_1C.y = -2.0f;
            effectPtr->unk_34.x = 0.1f;
            effectPtr->unk_34.y = 0.0f;
            effectPtr->unk_34.z = Rand_ZeroFloat(M_PI * 2);
            effectPtr->unk_02 = Rand_ZeroFloat(100.0f);
            effectPtr->unk_10.x = randPlusMinusPoint5Scaled(25.0f);
            effectPtr->unk_10.z = randPlusMinusPoint5Scaled(25.0f);
            return;
        }
    }
}

void EnTanron3_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTanron3* this = THIS;

    this->actor.gravity = -1.0f;
    Collider_InitAndSetCylinder(globalCtx, &this->atCollider, &this->actor, &sCylinderInit);
    Collider_InitAndSetCylinder(globalCtx, &this->acCollider, &this->actor, &sCylinderInit);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600DA20, &D_0600DAAC, this->jointTable, this->morphTable, 10);
    Actor_SetScale(&this->actor, 0.02f);
    func_80BB897C(this, globalCtx);
    this->actor.flags &= ~1;
    this->unk_250 = (s32)Rand_ZeroFloat(500000.0f);
    this->unk_244 = 430.0f;
    boss03Parent = (Boss03*)this->actor.parent;
}

void EnTanron3_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    boss03Parent->unk_252--;
}

void EnTanron3_SpawnBubbles(EnTanron3* this, GlobalContext* globalCtx) {
    static Color_RGBA8 sPrimColor = { 100, 55, 55, 255 };
    static Color_RGBA8 sEnvColor = { 50, 10, 10, 255 };
    s32 i;
    Vec3f sp98;
    Vec3f sp8C;

    for (i = 0; i < 20; i++) {
        SysMatrix_InsertYRotation_f(Rand_ZeroFloat(6.2831855f), 0);
        SysMatrix_RotateStateAroundXAxis(Rand_ZeroFloat(6.2831855f));
        SysMatrix_GetStateTranslationAndScaledZ(Rand_ZeroFloat(3.0f) + 2.0f, &sp98);
        sp8C.x = sp98.x * -0.05f;
        sp8C.y = sp98.y * -0.05f;
        sp8C.z = sp98.z * -0.05f;
        EffectSsDtBubble_SpawnCustomColor(globalCtx, &this->actor.world.pos, &sp98, &sp8C, &sPrimColor, &sEnvColor,
                                          Rand_ZeroFloat(30.0f) + 70.0f, Rand_ZeroFloat(5.0f) + 15.0f, 0);
    }
}

void func_80BB897C(EnTanron3* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80BB8A48;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_0600DAAC, -10.0f);
    this->unk_234 = 0;
    this->unk_238 = 5;
    this->unk_204[0] = 50;
    this->actor.speedXZ = 5.0f;
    this->unk_240 = 0.5f;
    this->unk_228.x = randPlusMinusPoint5Scaled(500.0f);
    this->unk_228.y = randPlusMinusPoint5Scaled(100.0f);
    this->unk_228.z = randPlusMinusPoint5Scaled(500.0f);
    Math_Vec3f_Copy(&this->unk_21C, &this->actor.world.pos);
    this->unk_200 = Rand_ZeroFloat(100.0f);
}

void func_80BB8A48(EnTanron3* this, GlobalContext* globalCtx) {
    s32 atan_temp;
    f32 temp_f18;
    f32 sp54;
    f32 sp50;
    f32 dist;
    f32 sp48;
    Player* player;

    sp48 = 0.0f;
    player = GET_PLAYER(globalCtx);
    this->skelAnime.animCurrentFrame = 4.0f;
    if (((player->actor.bgCheckFlags & 1) != 0) && (player->actor.shape.feetPos[0].y >= 438.0f)) {
        this->unk_202 = 1;
    } else if (this->unk_202 != 0 && this->unk_204[2] == 0 && ((this->unk_200 & 0x1F) == 0)) {
        temp_f18 = this->unk_21C.x - player->actor.world.pos.x;
        sp50 = this->unk_21C.z - player->actor.world.pos.z;
        if (sqrtf(SQ(temp_f18) + SQ(sp50)) < 500.0f) {
            this->unk_202 = 0;
            this->unk_204[2] = 150;
        }
    }
    if (this->actor.world.pos.y < this->unk_244) {
        this->unk_203 = 0;
        switch (this->unk_202) {
            case 0:
                this->unk_23C = 5.0f;
                this->unk_236 = 0x1000;
                this->unk_254 = 0x3A98;
                Math_Vec3f_Copy(&this->unk_21C, &player->actor.world.pos);
                if ((this->unk_200 & 0xF) == 0) {
                    if ((Rand_ZeroOne() < 0.5f) && (this->actor.xzDistToPlayer <= 200.0f)) {
                        Audio_PlayActorSound2(&this->actor, NA_SE_EN_PIRANHA_ATTACK);
                    }
                }
                if ((this->unk_204[2] == 0) || ((player->stateFlags2 & 0x80) != 0)) {
                    this->unk_204[2] = 150;
                    this->unk_202 = 1;
                }
                break;
            case 1:
                if ((boss03Parent->unk_324 != 0) && ((this->unk_200 & 7) == 0)) {
                    this->unk_254 = 0x4E20;
                    this->actor.speedXZ = 6.0f;
                } else {
                    this->unk_254 = 0x1F40;
                }
                this->unk_236 = 0x200;
                this->unk_23C = 2.0f;
                atan_temp = Math_FAtan2F(this->unk_21C.z, this->unk_21C.x);
                Matrix_RotateY(atan_temp, 0);
                SysMatrix_GetStateTranslationAndScaledZ(700.0f, &this->unk_21C);
                this->unk_21C.y = 250.0f;
                sp48 = 150.0f;
                break;
        }
        if (this->unk_204[1] == 0) {
            if ((this->unk_204[0] == 0) && (this->actor.speedXZ > 1.0f)) {
                this->unk_204[0] = Rand_ZeroFloat(20.0f);
                this->unk_228.x = randPlusMinusPoint5Scaled(100.0f);
                this->unk_228.y = randPlusMinusPoint5Scaled(50.0f + sp48);
                this->unk_228.z = randPlusMinusPoint5Scaled(100.0f);
            }
            this->unk_210.y = this->unk_21C.y + this->unk_228.y + 50.0f;
        }
        this->unk_210.x = this->unk_21C.x + this->unk_228.x;
        this->unk_210.z = this->unk_21C.z + this->unk_228.z;
        temp_f18 = this->unk_210.x - this->actor.world.pos.x;
        sp54 = this->unk_210.y - this->actor.world.pos.y;
        sp50 = this->unk_210.z - this->actor.world.pos.z;
        dist = sqrtf(SQ(temp_f18) + SQ(sp50));
        atan_temp = Math_FAtan2F(dist, -sp54);
        Math_ApproachS(&this->actor.world.rot.x, atan_temp, this->unk_238, this->unk_234);
        atan_temp = Math_FAtan2F(sp50, temp_f18);
        Math_SmoothStepToS(&this->actor.world.rot.y, atan_temp, this->unk_238, this->unk_234, 0);
        Math_ApproachS(&this->unk_234, this->unk_236, 1, 0x100);
        Math_ApproachF(&this->actor.speedXZ, this->unk_23C, 1.0f, this->unk_240);
        Actor_SetVelocityAndMoveXYRotationReverse(&this->actor);
    } else {
        switch (this->unk_203) {
            case 0:
                this->actor.gravity = -1.0f;
                this->unk_210.y = (this->unk_244 - 50.0f);
                this->unk_204[1] = 25;
                Math_ApproachS(&this->actor.world.rot.x, 0x3000, 5, 0xBD0);
                if ((this->actor.bgCheckFlags & 8) != 0) {
                    this->actor.speedXZ = 0.0f;
                    if (this->actor.velocity.y > 0.0f) {
                        this->actor.velocity.y = -1.0f;
                    }
                }
                if ((this->actor.bgCheckFlags & 1) != 0) {
                    this->unk_203 = 1;
                }
                break;
            case 1:
                this->unk_254 = 0x3A98;
                this->actor.gravity = -1.5f;
                if ((this->actor.bgCheckFlags & 1) != 0) {
                    this->actor.velocity.y = Rand_ZeroFloat(5.0f) + 5.0f;
                    this->actor.speedXZ = Rand_ZeroFloat(2.0f) + 2.0f;
                    if (Rand_ZeroOne() < 0.5f) {
                        this->unk_248.x = ((s16)randPlusMinusPoint5Scaled(500.0f) + this->unk_248.x + 0x8000);
                    }
                    if (Rand_ZeroOne() < 0.5f) {
                        this->unk_248.z = ((s16)randPlusMinusPoint5Scaled(500.0f) + this->unk_248.z + 0x8000);
                    }
                    if (Rand_ZeroOne() < 0.5f) {
                        this->unk_248.y = (s16)Rand_ZeroFloat(65536.0f);
                    }
                    this->actor.world.rot.y = Math_FAtan2F(this->actor.world.pos.z, this->actor.world.pos.x) +
                                              (s16)randPlusMinusPoint5Scaled(52768.0f);
                }
                Math_ApproachS(&this->actor.shape.rot.y, this->unk_248.y, 3, 0x500);
                Math_ApproachS(&this->actor.shape.rot.x, this->unk_248.x, 3, 0xC00);
                Math_ApproachS(&this->actor.shape.rot.z, this->unk_248.z, 3, 0xC00);
                if (((Rand_ZeroOne() < 0.5f) & !(this->unk_200 & 3)) != 0) {
                    Vec3f sp38;

                    sp38.x = randPlusMinusPoint5Scaled(30.0f) + this->actor.world.pos.x;
                    sp38.y = this->actor.world.pos.y;
                    sp38.z = randPlusMinusPoint5Scaled(30.0f) + this->actor.world.pos.z;
                    EnTanron3_CreateEffect(globalCtx, &sp38);
                }
                break;
        }
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    }
    this->unk_250 += this->unk_254;
    this->unk_25A = (s16)(s32)(Math_SinS((s16)(this->unk_250)) * 5000.0f);
    this->unk_25C = (s16)(s32)(Math_SinS((s16)(this->unk_250 + 0x6978)) * 5000.0f);
    this->unk_258 = (s16)(s32)(Math_SinS((s16)(this->unk_250)) * 5000.0f);
    if (this->unk_203 == 0) {
        this->actor.shape.rot = this->actor.world.rot;
    }
}

void EnTanron3_SetupKill(EnTanron3* this, GlobalContext* globalCtx) {
    f32 xDistance;
    f32 yDistance;
    f32 zDistance;
    Player* player = GET_PLAYER(globalCtx);

    this->actionFunc = EnTanron3_Kill;
    xDistance = this->actor.world.pos.x - player->actor.world.pos.x;
    yDistance = this->actor.world.pos.y - player->actor.world.pos.y + 30.0f;
    zDistance = this->actor.world.pos.z - player->actor.world.pos.z;
    this->actor.world.rot.x = Math_FAtan2F(sqrtf(SQ(xDistance) + SQ(zDistance)), -yDistance);
    this->actor.world.rot.y = Math_FAtan2F(zDistance, xDistance);
    this->unk_204[0] = 6;
    this->actor.speedXZ = 10.0f;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_KONB_MINI_DEAD);
}

void EnTanron3_Kill(EnTanron3* this, GlobalContext* globalCtx) {
    Actor_SetVelocityAndMoveXYRotationReverse(&this->actor);
    if (this->unk_204[0] == 0) {
        EnTanron3_SpawnBubbles(this, globalCtx);
        Actor_MarkForDeath(&this->actor);
        if (Rand_ZeroOne() < 0.3f) {
            Item_DropCollectibleRandom(globalCtx, NULL, &this->actor.world.pos, 0x60);
        }
    }
}

void EnTanron3_CheckCollisions(EnTanron3* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (player->actor.world.pos.y > 350.0f) {
        if (this->atCollider.base.atFlags & AT_HIT) {
            this->atCollider.base.atFlags &= ~AT_HIT;
            func_800B8D50(globalCtx, NULL, 3.0f, Math_FAtan2F(-player->actor.world.pos.z, -player->actor.world.pos.x),
                          5.0f, 0);
        }
    }
    if (this->acCollider.base.acFlags & AC_HIT) {
        this->acCollider.base.acFlags &= ~AC_HIT;
        if (this->unk_20A == 0) {
            this->unk_20A = 15;
            this->unk_20C = 15;
            EnTanron3_SetupKill(this, globalCtx);
            boss03Parent->unk_324 = 20;
        }
    }
}

void EnTanron3_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnTanron3* this = THIS;
    s16 i;
    Vec3f splashPos;

    if (KREG(63) == 0) {
        this->unk_200 += 1;
        for (i = 0; i < 3; i++) {
            if (this->unk_204[i] != 0) {
                this->unk_204[i]--;
            }
        }
        if (this->unk_20A != 0) {
            this->unk_20A--;
        }
        if (this->unk_20C != 0) {
            this->unk_20C--;
        }
        this->actionFunc(this, globalCtx);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 10.0f, 10.0f, 20.0f, 5);
        if (((this->actor.prevPos.y < this->unk_244) && (this->unk_244 <= this->actor.world.pos.y)) ||
            ((this->actor.prevPos.y > this->unk_244) && (this->unk_244 >= this->actor.world.pos.y))) {
            splashPos.x = this->actor.world.pos.x;
            splashPos.y = this->unk_244 + 10.0f;
            splashPos.z = this->actor.world.pos.z;
            EffectSsGSplash_Spawn(globalCtx, &splashPos, NULL, NULL, 1, 500);
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_OUT_OF_WATER);
        }
    }
    EnTanron3_CheckCollisions(this, globalCtx);
    Collider_UpdateCylinder(&this->actor, &this->atCollider);
    Collider_UpdateCylinder(&this->actor, &this->acCollider);
    CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->atCollider.base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->acCollider.base);
    if (((s8)boss03Parent->actor.colChkInfo.health <= 0) && (this->actionFunc != EnTanron3_Kill)) {
        EnTanron3_SetupKill(this, globalCtx);
        this->unk_204[0] = 0;
    }
}

s32 EnTanron3_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                               Actor* actor) {
    EnTanron3* this = (EnTanron3*)actor;

    if (limbIndex == 1) {
        rot->y += this->unk_25C;
    }
    if (limbIndex == 3) {
        rot->y += this->unk_258;
    }
    if (limbIndex == 4) {
        rot->y += this->unk_25A;
    }
    return 0;
}

void EnTanron3_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnTanron3* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    if ((this->unk_20C & 1) != 0) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
    }
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     EnTanron3_OverrideLimbDraw, NULL, &this->actor);
    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
