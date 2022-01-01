/*
 * File: z_en_ani.c
 * Overlay: ovl_En_Ani
 * Description: Part-time worker
 */

#include "z_en_ani.h"
#include "objects/object_ani/object_ani.h"

#define FLAGS 0x00000009

#define THIS ((EnAni*)thisx)

void EnAni_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAni_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAni_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAni_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80967D20(EnAni *this, GlobalContext *globalCtx, u16 textId);

//action func chain
void func_80968164(EnAni *this, GlobalContext *globalCtx);
void func_809680B0(EnAni *this, GlobalContext *globalCtx);
void func_80967FA4(EnAni *this, GlobalContext *globalCtx);
void func_80967F20(EnAni *this, GlobalContext *globalCtx);
void func_80967E90(EnAni *this, GlobalContext *globalCtx);
void func_80967E34(EnAni *this, GlobalContext *globalCtx);
void func_80967DCC(EnAni *this, GlobalContext *globalCtx);
void func_80967DA0(EnAni *this, GlobalContext *globalCtx);

const ActorInit En_Ani_InitVars = {
    ACTOR_EN_ANI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ANI,
    sizeof(EnAni),
    (ActorFunc)EnAni_Init,
    (ActorFunc)EnAni_Destroy,
    (ActorFunc)EnAni_Update,
    (ActorFunc)EnAni_Draw,
};

// two different colliders, but only one init for both
static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 30, 40, 0, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 850, ICHAIN_STOP),
};

static Vec3f D_809686A4 = {800.0f, 500.0f, 0.0f};

// todo: rename to eyetextures
static UNK_TYPE gEyeTextures[] = { gAniOpenEyeTex, gAniClosingEyeTex, gAniClosedEyeTex, 0x00000000 };

void func_80967AB4(EnAni *this);

// these three are function pointers, doing... what unknown
void func_809679D0(EnAni *this) {

    if (DECR(this->unkTimer2FA) == 0) {
        this->unkTimer2FA = Rand_S16Offset(0x3C, 0x3C);
    }
    this->blinkState = this->unkTimer2FA;
    if (this->blinkState >= 3) {
        this->blinkState = 0;
    }
}

void func_80967A48(EnAni *this) {

    if (this->unkTimer2FA > 0) {
        this->unkTimer2FA--;
    } else if (this->blinkState < 2) {
        this->blinkState++;
    } else {
        this->otherFunc = func_80967AB4;
        this->unkTimer2FA = Rand_S16Offset(0x14, 0x14);
    }
}

void func_80967AB4(EnAni *this) {
    if (this->unkTimer2FA > 0) {
        this->unkTimer2FA--;
    } else if (this->blinkState > 0) {
        this->blinkState--;
    } else {
        this->otherFunc = func_80967A48;
        this->unkTimer2FA = Rand_S16Offset(0xA, 0xA);
    }
}

void EnAni_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnAni *this = THIS;
    s32 pad;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 24.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gAniSkeleton, &gAniStandingNormalAnim, 
        &this->unk220, &this->unk280, 0x10);
    Animation_PlayOnce(&this->skelAnime, &gAniStandingNormalAnim);
    Collider_InitAndSetCylinder(globalCtx, &this->collider1, &this->actor, &sCylinderInit);
    Collider_InitAndSetCylinder(globalCtx, &this->collider2, &this->actor, &sCylinderInit);
    Collider_UpdateCylinder(&this->actor, &this->collider2);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->unk2EC = 0;
    this->unk2EE = 0;
    this->unk2F0 = 0;
    this->otherFunc = func_809679D0;
    if ((this->actor.params & 0xFF) == 1) {
        Animation_Change(&this->skelAnime, &gAniTreeHangingAnim, 1.0f, 0.0f, 
              Animation_GetLastFrame(&gAniTreeHangingAnim), 2, 0.0f);
        this->actionFunc = func_80968164;
        this->actor.velocity.y = 0.0f;
        this->actor.minVelocityY = 0.0f;
        this->actor.gravity = 0.0f;
        this->actor.flags |= 0x10;
        this->unk2EC |= 4;
        gSaveContext.eventInf[1] &= 0xEF;
    }else {
        this->collider2.dim.radius = 0x3C;
        this->actionFunc = func_80967DA0;
        this->actor.velocity.y = -25.0f;
        this->actor.minVelocityY = -25.0f;
        this->actor.gravity = -5.0f;
    }
}

void EnAni_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnAni *this = THIS;
    Collider_DestroyCylinder(globalCtx, &this->collider1);
    Collider_DestroyCylinder(globalCtx, &this->collider2);
}

// set text ID and check rotation?
void func_80967D20(EnAni *this, GlobalContext *globalCtx, u16 textId) {
    s16 diffAngle = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    this->actor.textId = textId;
    if ((this->unk2EC & 2) != 0 || ABS_ALT(diffAngle) < 0x4301) {
        if (this->actor.xzDistToPlayer < 100.0f) {
            func_800B8614(&this->actor, globalCtx, 120.0f);
        }
    }
}

void func_80967DA0(EnAni *this, GlobalContext *globalCtx) {
    SkelAnime_Update(&this->skelAnime);
}

void func_80967DCC(EnAni *this, GlobalContext *globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if ((func_80152498(&globalCtx->msgCtx) == 2) && (globalCtx->msgCtx.unk11F04 == 0x6DE)) {
        this->actionFunc = func_80967E34;
    }
}

void func_80967E34(EnAni *this, GlobalContext *globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        this->actionFunc = func_80967DCC;
    } else {
        func_80967D20(this, globalCtx, 0x6DE);
    }
}

void func_80967E90(EnAni *this, GlobalContext *globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        this->otherFunc = func_80967AB4;
        this->actionFunc = func_80967E34;
        Animation_Change(&this->skelAnime, &gAniHoldingFootPainWrithingAnim, 1.0f, 0.0f, 
            Animation_GetLastFrame(&gAniHoldingFootPainWrithingAnim), 0, 0.0f);
    }
}

void func_80967F20(EnAni *this, GlobalContext *globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        this->actionFunc = func_80967E90;
        Animation_Change(&this->skelAnime, &gAniFallOverHoldingFootAnim, 
            1.0f, 0.0f, (f32) Animation_GetLastFrame(&gAniFallOverHoldingFootAnim), 2, 0.0f);
    }
}

void func_80967FA4(EnAni *this, GlobalContext *globalCtx) {
    s32 pad;
    s16 quakeValue;

    if ((this->actor.bgCheckFlags & 1) != 0) {
        this->actor.flags &= ~0x10; // todo
        this->actionFunc = func_80967F20;
        this->actor.velocity.x = 0.0f;
        this->actor.velocity.z = 0.0f;
        Animation_Change(&this->skelAnime, &gAniUnusedLandingThenStandingUpAnim, 1.0f, 0.0f, 16.0f, 2, 0.0f);
        this->unk2EC |= 2;
        quakeValue = Quake_Add(globalCtx->cameraPtrs[0], 3);
        Quake_SetSpeed(quakeValue, 0x6978);
        Quake_SetQuakeValues(quakeValue, 7, 0, 0, 0);
        Quake_SetCountdown(quakeValue, 0x14);
        Audio_PlayActorSound2(&this->actor, NA_SE_IT_HAMMER_HIT);
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0x7D0, (s16) 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void func_809680B0(EnAni *this, GlobalContext *globalCtx) {
    s32 pad;

    if (SkelAnime_Update(&this->skelAnime)) {
        this->actor.minVelocityY = -20.0f;
        this->actor.gravity = -5.0f;
        this->actor.velocity.y = 0.0f;
        this->actor.velocity.z = -4.0f;
        Animation_Change(&this->skelAnime, &gAniUnusedLandingThenStandingUpAnim, 0.0f, 0.0f, 0.0f, 2, 5.0f);
        this->actionFunc = func_80967FA4;
        gSaveContext.eventInf[1] |= 0x10;
    }
}

void func_80968164(EnAni *this, GlobalContext *globalCtx) {

    if (SkelAnime_Update(&this->skelAnime) != 0) {
        // DECR?
        if (this->unk2F0 > 0) {
            this->unk2F0--;
            if (this->unk2F0 > 0) {
                Animation_PlayOnce(&this->skelAnime, &gAniTreeHangingReachAnim);
            } else {
                Animation_PlayOnce(&this->skelAnime, &gAniTreeHangingAnim);
            }
        } else if (Rand_ZeroFloat(1.0f) < 0.4f) {
            Animation_PlayOnce(&this->skelAnime, &gAniTreeHangingReachAnim);
            this->unk2F0 = 2;
        } else {
            Animation_PlayOnce(&this->skelAnime, &gAniTreeHangingAnim);
        }
    }
    if (this->actor.home.rot.x != 0) {
        this->unk2EC |= 8;
        this->actionFunc = func_809680B0;
        Animation_Change(&this->skelAnime, &gAniTreeHangLosingBalanceAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gAniTreeHangLosingBalanceAnim), 2, -5.0f);
    }
}

void EnAni_Update(Actor *thisx, GlobalContext *globalCtx) {
    EnAni *this = THIS;
    f32 minVelocity;

    Collider_UpdateCylinder(&this->actor, &this->collider1);
    Collider_UpdateCylinder(&this->actor, &this->collider2);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    if ((this->unk2EC & 1) == 0) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
    }

    this->actor.velocity.y += this->actor.gravity;
    minVelocity = this->actor.minVelocityY;
    if (this->actor.velocity.y < minVelocity) {
        this->actor.velocity.y = minVelocity;
    }

    Actor_ApplyMovement(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    this->actionFunc(this, globalCtx);
    if (this->actor.xzDistToPlayer < 100.0f && (this->unk2EC & 4) == 0) {
        func_800E9250(globalCtx, &this->actor, &this->unk2E0, &this->unk2E6, 
            this->actor.focus.pos);
        this->unk2E6.x = this->unk2E6.y = this->unk2E6.z = 0;
    } else {
        Math_SmoothStepToS(&this->unk2E0.x, 0, 6, 0x1838, (s16) 0x64);
        Math_SmoothStepToS(&this->unk2E0.y, 0, 6, 0x1838, (s16) 0x64);
        Math_SmoothStepToS(&this->unk2E6.x, 0, 6, 0x1838, (s16) 0x64);
        Math_SmoothStepToS(&this->unk2E6.y, 0, 6, 0x1838, (s16) 0x64);
    }
    this->otherFunc(this);
    if ((this->unk2EC & 8) != 0) {
        if (this->actor.cutscene == -1) {
            this->unk2EC &= ~0x8;
        } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
            this->actor.cutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
            func_800E02AC(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(this->actor.cutscene)), &this->actor);
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    }
}

s32 func_80968504(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *actor) {
    EnAni* this = (EnAni*) actor;
    if (limbIndex == 15) {
        rot->x += this->unk2E0.y;
        rot->z += this->unk2E0.x;
    }
    return 0;
}

void func_8096854C(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor *actor) {
    if (limbIndex == 15) {
        Matrix_MultiplyVector3fByState(&D_809686A4, &actor->focus.pos);
    }
}

void EnAni_Draw(Actor *thisx, GlobalContext *globalCtx) {
    EnAni *this = THIS;
    s32 pad;
    
    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_InsertTranslation(0.0f, 0.0f, -1000.0f, 1);
    func_8012C5B0(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(gEyeTextures[this->blinkState]));

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
       (s32) this->skelAnime.dListCount, func_80968504, func_8096854C, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/EnAni_Draw.s")
