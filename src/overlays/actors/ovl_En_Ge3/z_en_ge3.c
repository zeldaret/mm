/*
 * File: z_en_ge3.c
 * Overlay: ovl_En_Ge3
 * Description: Aviel
 */

#include "z_en_ge3.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_80000000)

#define THIS ((EnGe3*)thisx)

void EnGe3_Init(Actor* thisx, PlayState* play);
void EnGe3_Destroy(Actor* thisx, PlayState* play);
void EnGe3_Update(Actor* thisx, PlayState* play);
void EnGe3_Draw(Actor* thisx, PlayState* play);

void func_809A0070(EnGe3* this, s16 arg1, u8 arg2, f32 arg3);
void func_809A020C(EnGe3* this, PlayState* play);
void func_809A03AC(EnGe3* this, PlayState* play);
void func_809A04D0(EnGe3* this, PlayState* play);
s32 func_809A096C(PlayState* play, Actor* thisx);

void func_809A00F8(EnGe3* this, PlayState* play);

void func_809A0350(EnGe3* this);

#if 0
const ActorInit En_Ge3_InitVars = {
    ACTOR_EN_GE3,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GELDB,
    sizeof(EnGe3),
    (ActorFunc)EnGe3_Init,
    (ActorFunc)EnGe3_Destroy,
    (ActorFunc)EnGe3_Update,
    (ActorFunc)EnGe3_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809A0DA0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x01000222, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 50, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_809A0DA0;

extern FlexSkeletonHeader D_0600A808;

extern AnimationHeader D_06001EFC;
extern AnimationHeader* D_809A0DCC[9];
extern Vec3f D_809A0DF0;
extern TexturePtr D_809A0DFC[];

void EnGe3_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnGe3* this = (EnGe3*)thisx;

    ActorShape_Init(&this->picto.actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &D_0600A808, NULL, this->jointTable, this->morphTable, 24);
    Animation_PlayLoop(&this->skelAnime, &D_06001EFC);
    Collider_InitAndSetCylinder(play, &this->collider, &this->picto.actor, &D_809A0DA0);
    this->picto.actor.colChkInfo.mass = MASS_IMMOVABLE;
    Actor_SetScale(&this->picto.actor, 0.01f);

    this->unk312 = -1;
    this->unk314 = -1;
    this->picto.validationFunc = func_809A096C;
    func_809A020C(this, play);

    if ((this->picto.actor.params & 1) == 1) {
        func_809A0070(this, 2, 0, 0.0f);
        this->actionFunc = func_809A04D0;
        if (gSaveContext.save.weekEventReg[83] & 2) {
            Actor_MarkForDeath(&this->picto.actor);
            return;
        }
    } else {
        func_809A0070(this, 1, 0, 0.0f);
        this->actionFunc = func_809A03AC;
        this->picto.actor.speedXZ = 1.5f;
    }

    this->unk310 = 0;
    this->picto.actor.targetMode = 6;
    this->picto.actor.terminalVelocity = -4.0f;
    this->picto.actor.gravity = -1.0f;
    gSaveContext.save.weekEventReg[80] &= (u8)~8;
}

void EnGe3_Destroy(Actor* thisx, PlayState* play) {
    EnGe3* this = (EnGe3*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
}

void func_809A0070(EnGe3* this, s16 index, u8 mode, f32 morphFrames) {
    Animation_Change(&this->skelAnime, D_809A0DCC[index], 1.0f, 0.0f, Animation_GetLastFrame(D_809A0DCC[index]), mode,
                     morphFrames);
    this->unk312 = index;
}

void func_809A00F8(EnGe3* this, PlayState* play) {
    s16 yawDiff = this->picto.actor.yawTowardsPlayer - this->picto.actor.shape.rot.y;

    if ((ABS_ALT(yawDiff) <= 0x2300) && (this->picto.actor.xzDistToPlayer < 100.0f)) {
        Actor_TrackPlayer(play, &this->picto.actor, &this->unk304, &this->unk30A, this->picto.actor.focus.pos);
    } else {
        Math_SmoothStepToS(&this->unk304.x, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->unk304.y, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->unk30A.x, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->unk30A.y, 0, 6, 0x1838, 0x64);
    }
}

#define GERUDO_AVEIL_GET_PATH(thisx) (((thisx)->params & 0xFC00) >> 10)

void func_809A020C(EnGe3* this, PlayState* play) {
    this->unk300 = 0;

    if (GERUDO_AVEIL_GET_PATH(&this->picto.actor) != 0x3F) {
        this->unk2FC = &play->setupPathList[GERUDO_AVEIL_GET_PATH(&this->picto.actor)];
    } else {
        this->unk2FC = NULL;
    }
}

s32 func_809A024C(EnGe3* this) {
    Path* path;
    Vec3s* curPoint;
    f32 diffX;
    f32 diffZ;

    path = this->unk2FC;

    if (path == NULL) {
        return true;
    }

    curPoint = Lib_SegmentedToVirtual(path->points);
    curPoint += this->unk300;
    diffX = curPoint->x - this->picto.actor.world.pos.x;
    diffZ = curPoint->z - this->picto.actor.world.pos.z;
    this->picto.actor.world.rot.y = Math_Atan2S(diffX, diffZ);
    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.world.rot.y, 2, 0x7D0, 0xC8);

    if ((SQ(diffX) + SQ(diffZ)) < 100.0f) {
        this->unk300++;
        if (this->unk300 >= path->count) {
            return true;
        }
    }
    return false;
}

void func_809A0350(EnGe3* this) {
    if ((s32)Rand_ZeroFloat(2.0f) == 0) {
        Actor_PlaySfxAtPos(&this->picto.actor, NA_SE_VO_FPVO00);
        return;
    } else {
        Actor_PlaySfxAtPos(&this->picto.actor, NA_SE_VO_FPVO01);
    }
}

void func_809A03AC(EnGe3* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    func_809A00F8(this, play);
    if (func_809A024C(this)) {
        func_809A020C(this, play);
    }
}

#define GERUDO_AVEIL_GET_EXIT(thisx) (((thisx)->params & 0x1F0) >> 4)

void func_809A03FC(EnGe3* this, PlayState* play) {

    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.yawTowardsPlayer, 2, 0x400, 0x100);

    if (this->unk316 > 0) {
        this->unk316--;
        return;
    } else {
        if (play->nextEntrance != play->setupExitList[GERUDO_AVEIL_GET_EXIT(&this->picto.actor)]) {
            play->nextEntrance = play->setupExitList[GERUDO_AVEIL_GET_EXIT(&this->picto.actor)];
            play->transitionTrigger = 0x14;
            play->transitionType = 0x26;
            gSaveContext.save.weekEventReg[80] &= (u8)~8;
        }
    }
}

void func_809A04D0(EnGe3* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime) && (this->unk314 == 3)) {
        func_809A0070(this, 4, 2, 0.0f);
    }
    if (Cutscene_CheckActorAction(play, 108)) {
        s16 csAction = play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x6CU)]->action;

        if (this->unk314 != 7) {
            Cutscene_ActorTranslateAndYaw(&this->picto.actor, play, Cutscene_GetActorActionIndex(play, 108));
        }

        if (this->unk314 != csAction) {
            this->unk314 = csAction;
            switch (this->unk314) {
                case 1:
                    func_809A0070(this, 2, 0, 0.0f);
                    break;
                case 2:
                    func_809A0070(this, 3, 2, 0.0f);
                    this->skelAnime.playSpeed = 0.0f;
                    break;
                case 3:
                    func_809A0070(this, 3, 2, 0.0f);
                    break;
                case 4:
                    func_809A0070(this, 5, 0, 0.0f);
                    break;
                case 5:
                    func_809A0070(this, 6, 2, 0.0f);
                    break;
                case 6:
                    func_809A0070(this, 7, 0, 0.0f);
                    break;
                case 7:
                    func_809A0070(this, 8, 0, 0.0f);
                    this->picto.actor.speedXZ = 5.0f;
                    this->unk318 = (s32)(Rand_ZeroFloat(10.0f) + 20.0f);
                    break;
                case 8:
                    Actor_MarkForDeath(&this->picto.actor);
                    break;
            }

            SkelAnime_Update(&this->skelAnime);
        }
    } else if ((this->picto.actor.xzDistToPlayer < 700.0f) && (fabsf(this->picto.actor.playerHeightRel) < 100.0f) &&
               !Play_InCsMode(play)) {
        func_800B7298(play, &this->picto.actor, 0x1A);
        func_801000A4(NA_SE_SY_FOUND);

        if (Player_GetMask(play) == PLAYER_MASK_STONE) { // Not fooled by Stone Mask
            Message_StartTextbox(play, 0x11AF, &this->picto.actor);
        } else {
            Message_StartTextbox(play, 0x11AE, &this->picto.actor);
        }

        this->actionFunc = func_809A03FC;
        this->unk316 = 50;
        gSaveContext.save.weekEventReg[80] |= 8;
    }

    if (this->unk314 == 7) {
        this->picto.actor.speedXZ = 5.0f;
        func_809A024C(this);
        if (Animation_OnFrame(&this->skelAnime, 2.0f) || Animation_OnFrame(&this->skelAnime, 6.0f)) {
            Actor_PlaySfxAtPos(&this->picto.actor, NA_SE_EV_PIRATE_WALK);
        }

        if (this->unk318 > 0) {
            this->unk318--;
        } else {
            this->unk318 = (s32)(Rand_ZeroFloat(10.0f) + 20.0f);
            func_809A0350(this);
        }
    }
}

void func_809A0820(Actor* thisx, PlayState* play) {
    s32 pad;
    EnGe3* this = (EnGe3*)thisx;

    Collider_UpdateCylinder(&this->picto.actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    Actor_MoveWithGravity(&this->picto.actor);
    Actor_UpdateBgCheckInfo(play, &this->picto.actor, 40.0f, 25.0f, 40.0f, 4);
}

void func_809A08A4(EnGe3* this, PlayState* play) {
    if (DECR(this->blinkTimer) == 0) {
        this->blinkTimer = Rand_S16Offset(60, 60);
    }

    this->eyeIndex = this->blinkTimer;

    if (this->eyeIndex >= 3) {
        this->eyeIndex = 0;
    }
}

void EnGe3_Update(Actor* thisx, PlayState* play) {
    EnGe3* this = (EnGe3*)thisx;

    func_809A0820(&this->picto.actor, play);
    this->actionFunc(this, play);
    func_809A08A4(this, play);
}

s32 func_809A096C(PlayState* play, Actor* thisx) {
    s32 sp34 = Snap_ValidatePictograph(play, thisx, 9, &thisx->focus.pos, &thisx->shape.rot, 10.0f, 400.0f, -1);

    sp34 |= Snap_ValidatePictograph(play, thisx, 0xB, &thisx->focus.pos, &thisx->shape.rot, 10.0f, 1200.0f, -1);

    return sp34;
}

s32 func_809A0A14(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnGe3* this = THIS;

    switch (limbIndex) {
        case 5:
        case 11:
        case 16:
            *dList = NULL;
            return false;
        case 6:
            rot->x += this->unk304.y;
            // fallthrough
        default:
            // This is required since EnGe3 shares a skeleton with EnKaizoku; it avoids stale colours being used in the
            // displaylists.
            OPEN_DISPS(play->state.gfxCtx);

            switch (limbIndex) {
                case 3:
                    break;
                case 6:
                    gDPPipeSync(POLY_OPA_DISP++);
                    gDPSetEnvColor(POLY_OPA_DISP++, 80, 60, 10, 255);
                    break;
                case 11:
                case 16:
                    gDPPipeSync(POLY_OPA_DISP++);
                    gDPSetEnvColor(POLY_OPA_DISP++, 140, 170, 230, 255);
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
                    break;
                default:
                    gDPPipeSync(POLY_OPA_DISP++);
                    gDPSetEnvColor(POLY_OPA_DISP++, 140, 0, 0, 255);
                    break;
            }

            CLOSE_DISPS(play->state.gfxCtx);

            if ((this->unk312 == 2) && (((limbIndex == 8) || (limbIndex == 13)) || (limbIndex == 2))) {
                s32 temp = limbIndex * 50;

                rot->y = rot->y + (s32)(Math_SinS(play->state.frames * (temp + 0x814)) * 200.0f);
                rot->z = rot->z + (s32)(Math_CosS(play->state.frames * (temp + 0x940)) * 200.0f);
            }
            break;
    }
    return false;
}

void func_809A0C60(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnGe3* this = THIS;
    Vec3f sp18 = D_809A0DF0; // non-static in-function data

    if (limbIndex == 6) {
        Matrix_MultVec3f(&sp18, &this->picto.actor.focus.pos);
    }
}

void EnGe3_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    EnGe3* this = (EnGe3*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C5B0(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_809A0DFC[this->eyeIndex]));
    func_800B8050(&this->picto.actor, play, 0);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          func_809A0A14, func_809A0C60, &this->picto.actor);

    CLOSE_DISPS(play->state.gfxCtx);
}

// void func_809A0070(EnGe3 *arg0, s16 arg1, u8 arg2, f32 arg3); /* static */
// void func_809A020C(EnGe3 *arg0, PlayState *arg1);   /* static */
// void func_809A03AC(EnGe3 *arg0, PlayState *arg1);   /* static */
// void func_809A04D0(EnGe3 *arg0, PlayState *arg1);   /* static */
// s32 func_809A096C(PlayState *, Actor *);            /* static */
// extern AnimationHeader D_06001EFC;
// ColliderCylinderInit D_809A0DA0 = {
//     { 0xA, 0, 9, 0x39, 0x10, 1 },
//     { 0, { 0, 0, 0 }, { 0x01000222, 0, 0 }, 0, 1, 1 },
//     { 0x14, 0x32, 0, { 0, 0, 0 } },
// };
// AnimationHeader *D_809A0DCC[9] = {
//     (AnimationHeader *)0x0600AA8C,
//     (AnimationHeader *)0x060028A0,
//     (AnimationHeader *)0x06001EFC,
//     (AnimationHeader *)0x06000EE0,
//     (AnimationHeader *)0x060014CC,
//     (AnimationHeader *)0x06001AC8,
//     (AnimationHeader *)0x06000CB0,
//     (AnimationHeader *)0x06000734,
//     (AnimationHeader *)0x06001DFC,
// };
// Vec3f D_809A0DF0 = { 600.0f, 700.0f, 0.0f };
// void *D_809A0DFC[5] = { (void *)0x06006398, (void *)0x06006958, (void *)0x060070D8, NULL, NULL };
