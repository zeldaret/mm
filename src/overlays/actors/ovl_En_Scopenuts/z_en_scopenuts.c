/*
 * File: z_en_scopenuts.c
 * Overlay: ovl_En_Scopenuts
 * Description: Business Scrub that sells you a Heart Piece
 */

#include "z_en_scopenuts.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_dnt/object_dnt.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnScopenuts*)thisx)

void EnScopenuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnScopenuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnScopenuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnScopenuts_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BCB078(EnScopenuts* this, GlobalContext* globalCtx);
void func_80BCB1C8(EnScopenuts* this, GlobalContext* globalCtx);
void func_80BCB4DC(EnScopenuts* this, GlobalContext* globalCtx);
void func_80BCB52C(EnScopenuts* this, GlobalContext* globalCtx);
void func_80BCB6D0(EnScopenuts* this, GlobalContext* globalCtx);
void func_80BCB90C(EnScopenuts* this, GlobalContext* globalCtx);
void func_80BCB980(EnScopenuts* this, GlobalContext* globalCtx);
void func_80BCBA00(EnScopenuts* this, GlobalContext* globalCtx);
void func_80BCBC60(EnScopenuts* this, GlobalContext* globalCtx);
void func_80BCBD28(EnScopenuts* this, GlobalContext* globalCtx);
void func_80BCBF0C(EnScopenuts* this, GlobalContext* globalCtx);
void func_80BCBFFC(EnScopenuts* this, GlobalContext* globalCtx);
void func_80BCC288(EnScopenuts* this, GlobalContext* globalCtx);
s32 func_80BCC2AC(EnScopenuts* this, Path* path, s32 arg2_);
f32 func_80BCC448(Path* path, s32 arg1, Vec3f* arg2, Vec3s* arg3);

const ActorInit En_Scopenuts_InitVars = {
    ACTOR_EN_SCOPENUTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNT,
    sizeof(EnScopenuts),
    (ActorFunc)EnScopenuts_Init,
    (ActorFunc)EnScopenuts_Destroy,
    (ActorFunc)EnScopenuts_Update,
    (ActorFunc)EnScopenuts_Draw,
};

static ColliderCylinderInitType1 sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 27, 32, 0, { 0, 0, 0 } },
};

static AnimationInfoS sAnimations[] = {
    { &object_dnt_Anim_005488, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dnt_Anim_00B0B4, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dnt_Anim_004AA0, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_004E38, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_0029E8, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_005CA8, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_0038CC, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dnt_Anim_003CC0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dnt_Anim_0012F4, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_004700, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_001BC8, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dnt_Anim_003438, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_001E2C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dnt_Anim_000994, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dnt_Anim_002268, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_002F08, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dnt_Anim_00577C, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_dnt_Anim_0029E8, 1.0f, 8, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_0029E8, 1.0f, 4, -1, ANIMMODE_ONCE, -4 },
    { &object_dnt_Anim_0029E8, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_001BC8, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dnt_Anim_0012F4, -1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_002670, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
};

Gfx* D_80BCCCDC[] = { gKakeraLeafMiddle, gKakeraLeafTip };

Vec3f D_80BCCCE4 = { 0.0f, -0.5f, 0.0f };

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(targetMode, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 30, ICHAIN_STOP),
};

s16 func_80BCABF0(Path* path) {
    Vec3s* sp34 = Lib_SegmentedToVirtual(path->points);
    Vec3f sp28;
    Vec3f sp1C;

    Math_Vec3s_ToVec3f(&sp28, &sp34[0]);
    Math_Vec3s_ToVec3f(&sp1C, &sp34[1]);
    return Math_Vec3f_Yaw(&sp28, &sp1C);
}

void func_80BCAC40(EnScopenuts* this, GlobalContext* globalCtx) {
    s16 i;
    Vec3f sp60;
    Vec3f sp54;

    sp60 = this->actor.world.pos;
    sp60.y += 100.0f;

    for (i = 0; i < 36; i++) {
        sp54.x = Rand_Centered() * 10.0f;
        sp54.y = 2.0f * Rand_Centered();
        sp54.z = Rand_Centered() * 10.0f;
        EffectSsHahen_Spawn(globalCtx, &sp60, &sp54, &D_80BCCCE4, 0, 0x96, 1, 0x10, D_80BCCCDC[i & 1]);
    }
}

void func_80BCAD64(EnScopenuts* this, s16 arg1) {
    f32 sp24 = Math_CosS(this->actor.world.rot.x) * this->actor.speedXZ;

    switch (arg1) {
        case 1:
            this->actor.velocity.y = this->actor.speedXZ;
            this->actor.velocity.x = 0.0f;
            this->actor.velocity.z = 0.0f;
            break;

        case 2:
            this->actor.velocity.x = Math_SinS(this->actor.world.rot.y) * this->actor.speedXZ;
            this->actor.velocity.y = 0.0f;
            this->actor.velocity.z = Math_CosS(this->actor.world.rot.y) * this->actor.speedXZ;
            break;

        case 3:
            this->actor.velocity.x = 0.0f;
            this->actor.velocity.y = 0.0f;
            this->actor.velocity.z = 0.0f;
            break;

        default:
            this->actor.velocity.x = Math_SinS(this->actor.world.rot.y) * sp24;
            this->actor.velocity.y = Math_SinS(this->actor.world.rot.x) * this->actor.speedXZ;
            this->actor.velocity.z = Math_CosS(this->actor.world.rot.y) * sp24;
            break;
    }
    Actor_UpdatePos(&this->actor);
}

void func_80BCAE78(EnScopenuts* this, GlobalContext* globalCtx) {
    if (this->unk_328 & 4) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }

    if (this->unk_328 & 2) {
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 20.0f, 5);
    }
}

s16 func_80BCAF0C(EnScopenuts* this) {
    switch (this->unk_33C) {
        case 0x0:
            if (gSaveContext.save.weekEventReg[53] & 2) {
                this->unk_328 |= 1;
                return 0x1638;
            }
            return 0x162F;
        case 0x162F:
            return 0x1630;
        case 0x1630:
            return 0x1631;
        case 0x1631:
            this->unk_358 = 150;
            return 0x1632;
        case 0x1633:
            this->unk_358 = 100;
            return 0x1634;
    }
    return 0;
}

void func_80BCAFA8(EnScopenuts* this, GlobalContext* globalCtx) {
    Vec3f sp1C;

    func_80169474(globalCtx, &this->actor.world.pos, &sp1C);
    if ((sp1C.x >= 130.0f) && (sp1C.x < 190.0f) && (sp1C.y >= 90.0f)) {
        if (sp1C.y < 150.0f) {
            this->actor.draw = EnScopenuts_Draw;
            this->unk_348 = 10;
            SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, 10);
            this->actionFunc = func_80BCB078;
        }
    }
}

void func_80BCB078(EnScopenuts* this, GlobalContext* globalCtx) {
    Vec3s sp30;

    if (this->path != NULL) {
        func_80BCC448(this->path, this->unk_334, &this->actor.world.pos, &sp30);
        if (this->actor.bgCheckFlags & 8) {
            sp30.y = this->actor.wallYaw;
        }
        Math_SmoothStepToS(&this->actor.world.rot.y, sp30.y, 10, 300, 0);
        this->actor.shape.rot.y = this->actor.world.rot.y;
        this->unk_33E = 0x1000;
        this->unk_340 += 0x1C71;
        this->actor.world.rot.x = -sp30.x;
        if (func_80BCC2AC(this, this->path, this->unk_334)) {
            if (this->unk_334 >= (this->path->count - 1)) {
                this->actionFunc = func_80BCB1C8;
                this->actor.speedXZ = 0.0f;
                this->actor.gravity = -1.0f;
                return;
            }
            this->unk_334++;
        }
    }

    if (this->unk_334 >= (this->path->count - 2)) {
        Math_ApproachF(&this->actor.speedXZ, 1.5f, 0.2f, 1.0f);
    } else {
        Math_ApproachF(&this->actor.speedXZ, 5.0f, 0.2f, 1.0f);
    }
    Actor_MoveWithoutGravity(&this->actor);
}

void func_80BCB1C8(EnScopenuts* this, GlobalContext* globalCtx) {
    this->unk_350 *= 0.92f;
    Actor_SetScale(&this->actor, this->unk_350);
    if (this->actor.bgCheckFlags & 1) {
        gSaveContext.save.weekEventReg[52] |= 0x40;
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80BCB230(EnScopenuts* this, GlobalContext* globalCtx) {
    s16 sp26 = this->skelAnime.curFrame;
    s16 sp24 = Animation_GetLastFrame(sAnimations[this->unk_348].animation);

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0xE38);

    if ((((this->actor.playerHeightRel < 50.0f) && (this->actor.playerHeightRel > -50.0f)) ? true : false) &&
        ((this->actor.xzDistToPlayer < 200.0f) ? true : false)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
        this->actionFunc = func_80BCB4DC;
        this->unk_348 = 3;
        this->collider.dim.height = 64;
        func_80BCAC40(this, globalCtx);
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, 3);
    } else if (sp26 == sp24) {
        if ((this->unk_348 == 4) || (this->unk_348 == 18)) {
            this->unk_348 = 17;
            this->collider.dim.height = 0;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_DOWN);
            SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, 17);
        } else if (this->unk_348 == 2) {
            this->unk_348 = 16;
            this->collider.dim.height = 32;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_UP);
            SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, 16);
        } else if (this->unk_348 == 17) {
            if (DECR(this->unk_34E) == 0) {
                this->unk_34E = Rand_ZeroOne() * 10.0f;
                this->unk_348 = 2;
                this->collider.dim.height = 32;
                SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, 2);
            }
        } else if ((this->unk_348 == 16) && (DECR(this->unk_34E) == 0)) {
            this->unk_34E = Rand_S16Offset(40, 40);
            this->unk_348 = 18;
            this->collider.dim.height = 32;
            SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, 18);
        }
    }
}

void func_80BCB4DC(EnScopenuts* this, GlobalContext* globalCtx) {
    if (this->skelAnime.curFrame == this->skelAnime.endFrame) {
        this->actionFunc = func_80BCB52C;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, 0);
    }
}

void func_80BCB52C(EnScopenuts* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 2000, 0);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->unk_33C = func_80BCAF0C(this);
        Message_StartTextbox(globalCtx, this->unk_33C, &this->actor);
        this->actionFunc = func_80BCB6D0;
    } else if (((this->actor.xzDistToPlayer < 100.0f) &&
                (((this->actor.playerHeightRel < 50.0f) && (this->actor.playerHeightRel > -50.0f)) ? true : false)) ||
               this->actor.isTargeted) {
        func_800B8614(&this->actor, globalCtx, 100.0f);
    } else if (!(((this->actor.playerHeightRel < 50.0f) && (this->actor.playerHeightRel > -50.0f)) ? true : false) ||
               !((this->actor.xzDistToPlayer < 200.0f) ? true : false)) {
        this->unk_348 = 4;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, 4);
        this->actionFunc = func_80BCB230;
    }
}

void func_80BCB6D0(EnScopenuts* this, GlobalContext* globalCtx) {
    u8 temp_v0 = Message_GetState(&globalCtx->msgCtx);

    if (temp_v0 == 5) {
        if (Message_ShouldAdvance(globalCtx)) {
            if (this->unk_328 & 1) {
                this->unk_328 &= ~1;
                globalCtx->msgCtx.msgMode = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->actor.flags &= ~ACTOR_FLAG_1;
                this->unk_328 &= ~4;
                this->unk_348 = 8;
                SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, 8);
                this->actionFunc = func_80BCBA00;
            } else {
                this->unk_33C = func_80BCAF0C(this);
                Message_StartTextbox(globalCtx, this->unk_33C, &this->actor);
            }
        }
    } else if (temp_v0 == 4) {
        if (Message_ShouldAdvance(globalCtx) != 0) {
            switch (globalCtx->msgCtx.choiceIndex) {
                case 0:
                    if (gSaveContext.save.playerData.rupees < this->unk_358) {
                        play_sound(NA_SE_SY_ERROR);
                        this->unk_33C = 0x1636;
                        this->unk_328 |= 1;
                        Message_StartTextbox(globalCtx, this->unk_33C, &this->actor);
                    } else {
                        func_8019F208();
                        globalCtx->msgCtx.msgMode = 0x43;
                        globalCtx->msgCtx.unk12023 = 4;
                        func_801159EC(this->unk_358 * -1);
                        this->actionFunc = func_80BCB90C;
                    }
                    break;
                case 1:
                    func_8019F230();
                    if (this->unk_358 == 150) {
                        this->unk_33C = 0x1633;
                    } else {
                        this->unk_33C = 0x1635;
                        this->unk_328 |= 1;
                    }
                    Message_StartTextbox(globalCtx, this->unk_33C, &this->actor);
                    break;
            }
        }
    } else if (temp_v0 == 6) {
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
        this->actionFunc = func_80BCB980;
    }
}

void func_80BCB90C(EnScopenuts* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        gSaveContext.save.weekEventReg[53] |= 2;
        this->actionFunc = func_80BCB6D0;
    } else {
        Actor_PickUp(&this->actor, globalCtx, GI_HEART_PIECE, 300.0f, 300.0f);
    }
}

void func_80BCB980(EnScopenuts* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->unk_33C = 0x1637;
        this->unk_328 |= 1;
        Message_StartTextbox(globalCtx, this->unk_33C, &this->actor);
        this->actionFunc = func_80BCB6D0;
    } else {
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
    }
}

void func_80BCBA00(EnScopenuts* this, GlobalContext* globalCtx) {
    s16 sp26 = this->skelAnime.curFrame;
    s16 sp24 = Animation_GetLastFrame(sAnimations[this->unk_348].animation);

    switch (sp26) {
        case 10:
            this->unk_35A = 1;
            this->unk_35C = 0.1f;
            this->unk_360 = 0.1f;
            this->unk_364 = 0.1f;
            break;

        case 11:
        case 12:
            this->unk_35C += 0.15f;
            this->unk_360 += 0.32f;
            this->unk_364 += 0.15f;
            break;

        case 13:
            this->unk_35C = 0.55f;
            this->unk_360 = 1.05f;
            this->unk_364 = 0.55f;
            break;

        case 14:
            this->unk_35C = 1.0f;
            this->unk_360 = 2.0f;
            this->unk_364 = 1.0f;
            break;

        case 15:
        case 16:
            this->unk_360 -= 0.33f;
            break;

        case 17:
            this->unk_360 = 1.0f;
            break;

        case 18:
        case 19:
            this->unk_360 += 0.27f;
            break;

        case 20:
            this->unk_35A = 2;
            this->unk_360 = 1.8f;
            break;

        case 21:
        case 22:
        case 23:
            this->unk_360 -= 0.2f;
            break;

        case 24:
            this->unk_360 = 1.0f;
            break;
    }

    if (this->unk_36C == 0) {
        if (ActorCutscene_GetCanPlayNext(this->unk_338)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->unk_338, &this->actor);
            this->unk_36C = 1;
        } else {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            ActorCutscene_SetIntentToPlay(this->unk_338);
            return;
        }
    }

    if (sp26 == sp24) {
        this->unk_35A = 3;
        this->unk_348 = 19;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, 19);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_DOWN);
        this->unk_328 &= ~2;
        this->unk_34E = 50;
        this->unk_328 |= 8;
        this->unk_32C = this->actor.world.pos.y;
        this->actionFunc = func_80BCBC60;
    }
}

void func_80BCBC60(EnScopenuts* this, GlobalContext* globalCtx) {
    f32 sp24;
    Vec3f sp18;

    this->unk_340 += this->unk_34C;
    sp24 = this->unk_32C - this->actor.world.pos.y;

    if (!(this->unk_370 & 3)) {
        sp18.x = this->actor.world.pos.x;
        sp18.y = this->unk_32C;
        sp18.z = this->actor.world.pos.z;
        func_800B14D4(globalCtx, 20.0f, &sp18);
    }

    if (sp24 > 5.0f) {
        this->actor.velocity.y = 0.0f;
        this->actor.gravity = 0.0f;
        this->unk_372 = func_80BCABF0(this->path);
        this->actionFunc = func_80BCBD28;
    }
}

void func_80BCBD28(EnScopenuts* this, GlobalContext* globalCtx) {
    Vec3f sp44;
    s16 sp42 = this->skelAnime.curFrame;
    s16 sp40 = Animation_GetLastFrame(sAnimations[this->unk_348].animation);
    Vec3s sp38;

    func_80BCC448(this->path, this->unk_334, &this->actor.world.pos, &sp38);
    if (sp42 == sp40) {
        Math_SmoothStepToS(&this->unk_34C, 0x1C71, 3, 0x100, 0);
        this->unk_340 += this->unk_34C;
        this->actor.shape.yOffset = 1500.0f;
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->unk_372, 3, 2000, 0);
    this->actor.world.rot.y = this->actor.shape.rot.y;

    if (DECR(this->unk_34E) == 0) {
        if (!(this->unk_370 & 3)) {
            sp44 = this->actor.world.pos;
            func_800B14D4(globalCtx, 20.0f, &sp44);
        }
        this->actor.velocity.y = 5.0f;
    } else if (!(this->unk_370 & 3)) {
        sp44.x = this->actor.world.pos.x;
        sp44.y = this->unk_32C;
        sp44.z = this->actor.world.pos.z;
        func_800B14D4(globalCtx, 20.0f, &sp44);
    }

    if ((this->actor.home.pos.y + 22.5f) < this->actor.world.pos.y) {
        this->unk_368 = 0.3f;
        this->unk_348 = 9;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, 9);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
        func_80BCAC40(this, globalCtx);
        this->actionFunc = func_80BCBF0C;
    }
}

void func_80BCBF0C(EnScopenuts* this, GlobalContext* globalCtx) {
    this->unk_340 += this->unk_34C;
    if (this->unk_368 >= 1.0f) {
        this->unk_368 = 1.0f;
        this->actor.velocity.y = 5.0f;
    } else {
        this->actor.velocity.y = 5.0f;
        this->unk_368 += 0.1f;
    }

    if ((this->actor.home.pos.y + 50.0f) < this->actor.world.pos.y) {
        Math_ApproachF(&this->actor.velocity.y, 0.0f, 0.2f, 1.0f);
        this->unk_348 = 10;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, 10);
        this->unk_328 |= 2;
        this->unk_36E = 0;
        this->actionFunc = func_80BCBFFC;
    }
}

void func_80BCBFFC(EnScopenuts* this, GlobalContext* globalCtx) {
    Vec3s sp38;
    f32 sp34;
    s16 sp32 = 0;

    this->actor.velocity.y = 0.0f;
    this->actor.gravity = 0.0f;

    if (this->path != NULL) {
        sp34 = func_80BCC448(this->path, this->unk_334, &this->actor.world.pos, &sp38);
        if (this->actor.bgCheckFlags & 8) {
            sp38.y = this->actor.wallYaw;
        }

        if (this->unk_334 < 6) {
            Math_SmoothStepToS(&this->actor.world.rot.y, sp38.y, 10, 300, 0);
        } else {
            Math_SmoothStepToS(&this->actor.world.rot.y, sp38.y, 10, 1500, 0);
        }

        this->actor.shape.rot.y = this->actor.world.rot.y;
        this->unk_33E = 0x1000;
        this->unk_340 += this->unk_34C;
        this->actor.world.rot.x = -sp38.x;

        if (func_80BCC2AC(this, this->path, this->unk_334)) {
            sp32 = 1;
        }

        if (sp34 < 10.0f) {
            if (sp32 == 1) {
                sp32 = 3;
            } else {
                sp32 = 2;
            }
        }

        if (sp32 == 3) {
            if (this->unk_334 >= (this->path->count - 1)) {
                ActorCutscene_Stop(this->unk_338);
                gSaveContext.save.weekEventReg[52] &= (u8)~0x40;
                this->actionFunc = func_80BCC288;
            } else {
                this->unk_334++;
            }
        }
    } else if (this->actor.playerHeightRel > 500.0f) {
        ActorCutscene_Stop(this->unk_338);
        this->actionFunc = func_80BCC288;
    }

    Math_ApproachF(&this->actor.speedXZ, 1.0f, 0.2f, 1.0f);
    func_80BCAD64(this, sp32);

    if (this->unk_36C == 2) {
        if (ActorCutscene_GetCanPlayNext(this->unk_338)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->unk_338, &this->actor);
            this->unk_36C = 3;
        } else {
            ActorCutscene_SetIntentToPlay(this->unk_338);
            return;
        }
    } else if ((this->unk_36C == 1) && (this->unk_36E == 20)) {
        ActorCutscene_Stop(this->unk_338);
        this->unk_338 = ActorCutscene_GetAdditionalCutscene(this->unk_338);
        ActorCutscene_SetIntentToPlay(this->unk_338);
        this->unk_36C = 2;
    }
    this->unk_36E++;
}

void func_80BCC288(EnScopenuts* this, GlobalContext* globalCtx) {
    Actor_MarkForDeath(&this->actor);
}

s32 func_80BCC2AC(EnScopenuts* this, Path* path, s32 arg2_) {
    Vec3s* sp5C = Lib_SegmentedToVirtual(path->points);
    s32 sp58 = path->count;
    s32 arg2 = arg2_;
    s32 sp50 = false;
    f32 phi_f12;
    f32 phi_f14;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    Vec3f sp30;

    Math_Vec3s_ToVec3f(&sp30, &sp5C[arg2]);

    if (arg2 == 0) {
        phi_f12 = sp5C[1].x - sp5C[0].x;
        phi_f14 = sp5C[1].z - sp5C[0].z;
    } else if ((sp58 - 1) == arg2) {
        phi_f12 = sp5C[sp58 - 1].x - sp5C[sp58 - 2].x;
        phi_f14 = sp5C[sp58 - 1].z - sp5C[sp58 - 2].z;
    } else {
        phi_f12 = sp5C[arg2 + 1].x - sp5C[arg2 - 1].x;
        phi_f14 = sp5C[arg2 + 1].z - sp5C[arg2 - 1].z;
    }

    func_8017B7F8(&sp30, RADF_TO_BINANG(func_80086B30(phi_f12, phi_f14)), &sp44, &sp40, &sp3C);

    if (((this->actor.world.pos.x * sp44) + (sp40 * this->actor.world.pos.z) + sp3C) > 0.0f) {
        sp50 = true;
    }
    return sp50;
}

f32 func_80BCC448(Path* path, s32 arg1, Vec3f* arg2, Vec3s* arg3) {
    Vec3s* temp_v1;
    Vec3f sp20;

    if (path != NULL) {
        temp_v1 = Lib_SegmentedToVirtual(path->points);
        temp_v1 = &temp_v1[arg1];
        sp20.x = temp_v1[0].x;
        sp20.y = temp_v1[0].y;
        sp20.z = temp_v1[0].z;
    }

    arg3->y = Math_Vec3f_Yaw(arg2, &sp20);
    arg3->x = Math_Vec3f_Pitch(arg2, &sp20);

    return sp20.y - arg2->y;
}

void EnScopenuts_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnScopenuts* this = THIS;

    if (!(gSaveContext.save.weekEventReg[74] & 0x40) &&
        (gSaveContext.save.inventory.items[ITEM_OCARINA] == ITEM_NONE)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    Actor_ProcessInitChain(&this->actor, sInitChain);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_dnt_Skel_00AC70, &object_dnt_Anim_005488, this->jointTable,
                       this->morphTable, 28);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinderType1(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 35.0f);
    this->unk_350 = 0.01f;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.colChkInfo.cylRadius = 0;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->unk_328 |= 2;
    this->unk_328 |= 4;
    this->actor.speedXZ = 0.0f;

    if (ENSCOPENUTS_GET_3E0(&this->actor) == ENSCOPENUTS_3E0_0) {
        if (gSaveContext.save.weekEventReg[52] & 0x40) {
            Actor_MarkForDeath(&this->actor);
        } else if (globalCtx->actorCtx.unk5 & 2) {
            this->path = SubS_GetPathByIndex(globalCtx, ENSCOPENUTS_GET_FC00(&this->actor), 0x3F);
            this->actor.draw = NULL;
            this->actionFunc = func_80BCAFA8;
            this->actor.gravity = 0.0f;
        } else {
            Actor_MarkForDeath(&this->actor);
        }
    } else if (ENSCOPENUTS_GET_3E0(&this->actor) == ENSCOPENUTS_3E0_1) {
        if (gSaveContext.save.weekEventReg[52] & 0x40) {
            this->path = SubS_GetPathByIndex(globalCtx, ENSCOPENUTS_GET_FC00(&this->actor), 0x3F);
            if (this->path == NULL) {
                Actor_MarkForDeath(&this->actor);
            } else {
                this->actor.gravity = -1.0f;
                this->actor.draw = EnScopenuts_Draw;
                this->unk_338 = this->actor.cutscene;
                this->unk_33C = 0;
                this->unk_358 = 150;
                this->unk_348 = 4;
                this->unk_35A = 0;
                SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, 4);
                this->actionFunc = func_80BCB230;
            }
        } else {
            Actor_MarkForDeath(&this->actor);
        }
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void EnScopenuts_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnScopenuts* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnScopenuts_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnScopenuts* this = THIS;

    Actor_SetFocus(&this->actor, 60.0f);
    SkelAnime_Update(&this->skelAnime);
    Actor_MoveWithGravity(&this->actor);

    this->actionFunc(this, globalCtx);

    if (this->unk_328 & 8) {
        func_800B9010(&this->actor, NA_SE_EN_AKINDO_FLY - SFX_FLAG);
    }
    func_80BCAE78(this, globalCtx);
}

s32 EnScopenuts_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                 Actor* thisx) {
    EnScopenuts* this = THIS;

    if (((this->unk_348 == 4) && (this->unk_35A == 0)) || ((this->unk_348 == 8) && (this->unk_35A == 0)) ||
        (this->unk_348 == 18) || (this->unk_348 == 2) || (this->unk_348 == 3) || (this->unk_348 == 17) ||
        (this->unk_348 == 16)) {
        if ((limbIndex == 16) || (limbIndex == 21) || (limbIndex == 27) || (limbIndex == 23) || (limbIndex == 24) ||
            (limbIndex == 15)) {
            *dList = NULL;
        }
    } else if ((this->unk_348 == 8) || (this->unk_348 == 19)) {
        switch (this->unk_35A) {
            case 1:
                if ((limbIndex == 16) || (limbIndex == 21) || (limbIndex == 27) || (limbIndex == 25)) {
                    *dList = NULL;
                }
                break;

            case 2:
            case 3:
                if ((limbIndex == 16) || (limbIndex == 21) || (limbIndex == 27) || (limbIndex == 15) ||
                    (limbIndex == 25)) {
                    *dList = NULL;
                }
                break;
        }
    } else if (((this->unk_348 == 9) || (this->unk_348 == 10)) && ((limbIndex == 15) || (limbIndex == 25))) {
        *dList = NULL;
    }

    if (limbIndex == 26) {
        if ((this->unk_33C == 0x162F) || (this->unk_33C == 0x1630)) {
            *dList = object_dnt_DL_001420;
        } else {
            *dList = object_dnt_DL_008290;
        }
    }

    return false;
}

void EnScopenuts_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
}

void EnScopenuts_TransformLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
    EnScopenuts* this = THIS;

    if (((this->unk_35A == 1) || (this->unk_35A == 2)) && ((limbIndex == 23) || (limbIndex == 24))) {
        Matrix_Scale(this->unk_35C, this->unk_360, this->unk_364, MTXMODE_APPLY);
    }

    if ((this->unk_348 == 9) && ((limbIndex == 16) || (limbIndex == 21) || (limbIndex == 27))) {
        Matrix_Scale(this->unk_368, this->unk_368, this->unk_368, MTXMODE_APPLY);
    }

    if (limbIndex == 24) {
        Matrix_RotateY(this->unk_340, MTXMODE_APPLY);
    }
}

void EnScopenuts_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnScopenuts* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, EnScopenuts_OverrideLimbDraw, EnScopenuts_PostLimbDraw,
                                   EnScopenuts_TransformLimbDraw, &this->actor);
}
