/*
 * File: z_en_ge3.c
 * Overlay: ovl_En_Ge3
 * Description: Aviel, leader of the Gerudo Pirates
 */

#include "z_en_ge3.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_80000000)

#define THIS ((EnGe3*)thisx)

void EnGe3_Init(Actor* thisx, PlayState* play);
void EnGe3_Destroy(Actor* thisx, PlayState* play);
void EnGe3_Update(Actor* thisx, PlayState* play);
void EnGe3_Draw(Actor* thisx, PlayState* play);

void EnGe3_ChangeAnim(EnGe3* this, s16 arg1, u8 arg2, f32 arg3);
void EnGe3_SetupPath(EnGe3* this, PlayState* play);
void EnGe3_Idle(EnGe3* this, PlayState* play);
void EnGe3_PerformCutsceneActions(EnGe3* this, PlayState* play);
s32 EnGe3_ValidatePictograph(PlayState* play, Actor* thisx);

typedef enum {
    /* -1 */ GERUDO_AVEIL_ANIM_NONE = -1,
    /*  0 */ GERUDO_AVEIL_ANIM_0,
    /*  1 */ GERUDO_AVEIL_ANIM_1,
    /*  2 */ GERUDO_AVEIL_ANIM_2,
    /*  3 */ GERUDO_AVEIL_ANIM_3,
    /*  4 */ GERUDO_AVEIL_ANIM_4,
    /*  5 */ GERUDO_AVEIL_ANIM_5,
    /*  6 */ GERUDO_AVEIL_ANIM_6,
    /*  7 */ GERUDO_AVEIL_ANIM_7,
    /*  8 */ GERUDO_AVEIL_ANIM_8,
} GerudoAveilAnimation;

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

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x01000222, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 20, 50, 0, { 0, 0, 0 } },
};

extern FlexSkeletonHeader D_0600A808;
extern AnimationHeader D_06001EFC;

void EnGe3_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnGe3* this = (EnGe3*)thisx;

    ActorShape_Init(&this->picto.actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &D_0600A808, NULL, this->jointTable, this->morphTable, 24);
    Animation_PlayLoop(&this->skelAnime, &D_06001EFC);
    Collider_InitAndSetCylinder(play, &this->collider, &this->picto.actor, &sCylinderInit);
    this->picto.actor.colChkInfo.mass = MASS_IMMOVABLE;
    Actor_SetScale(&this->picto.actor, 0.01f);

    this->animIndex = GERUDO_AVEIL_ANIM_NONE;
    this->csAction = -1;
    this->picto.validationFunc = EnGe3_ValidatePictograph;
    EnGe3_SetupPath(this, play);

    if (GERUDO_AVEIL_GET_TYPE(&this->picto.actor) == GERUDO_AVEIL_TYPE_1) {
        EnGe3_ChangeAnim(this, GERUDO_AVEIL_ANIM_2, ANIMMODE_LOOP, 0.0f);
        this->actionFunc = EnGe3_PerformCutsceneActions;
        if (gSaveContext.save.weekEventReg[83] & 2) {
            Actor_MarkForDeath(&this->picto.actor);
            return;
        }
    } else {
        EnGe3_ChangeAnim(this, GERUDO_AVEIL_ANIM_1, ANIMMODE_LOOP, 0.0f);
        this->actionFunc = EnGe3_Idle;
        this->picto.actor.speedXZ = 1.5f;
    }

    this->stateFlags = 0;
    this->picto.actor.targetMode = 6;
    this->picto.actor.terminalVelocity = -4.0f;
    this->picto.actor.gravity = -1.0f;
    gSaveContext.save.weekEventReg[80] &= (u8)~8;
}

void EnGe3_Destroy(Actor* thisx, PlayState* play) {
    EnGe3* this = (EnGe3*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
}

static AnimationHeader* sAnimations[] = {
    0x0600AA8C, 0x060028A0, 0x06001EFC, 0x06000EE0, 0x060014CC, 0x06001AC8, 0x06000CB0, 0x06000734, 0x06001DFC,
};

void EnGe3_ChangeAnim(EnGe3* this, s16 index, u8 mode, f32 morphFrames) {
    Animation_Change(&this->skelAnime, sAnimations[index], 1.0f, 0.0f, Animation_GetLastFrame(sAnimations[index]), mode,
                     morphFrames);
    this->animIndex = index;
}

void EnGe3_LookAtPlayer(EnGe3* this, PlayState* play) {
    s16 yawDiff = this->picto.actor.yawTowardsPlayer - this->picto.actor.shape.rot.y; // temp not required

    if ((ABS_ALT(yawDiff) <= 0x2300) && (this->picto.actor.xzDistToPlayer < 100.0f)) {
        Actor_TrackPlayer(play, &this->picto.actor, &this->headRot, &this->torsoRot, this->picto.actor.focus.pos);
    } else {
        Math_SmoothStepToS(&this->headRot.x, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->headRot.y, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->torsoRot.x, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->torsoRot.y, 0, 6, 0x1838, 0x64);
    }
}

void EnGe3_SetupPath(EnGe3* this, PlayState* play) {
    this->curPointIndex = 0;

    if (GERUDO_AVEIL_GET_PATH(&this->picto.actor) != GERUDO_AVEIL_PATH_NONE) {
        this->path = &play->setupPathList[GERUDO_AVEIL_GET_PATH(&this->picto.actor)];
    } else {
        this->path = NULL;
    }
}

/**
 * @return true if no path or reached end of path
 */
s32 EnGe3_FollowPath(EnGe3* this) {
    Path* path;
    Vec3s* curPoint;
    f32 diffX;
    f32 diffZ;

    path = this->path;

    if (path == NULL) {
        return true;
    }

    curPoint = Lib_SegmentedToVirtual(path->points);
    curPoint += this->curPointIndex;
    diffX = curPoint->x - this->picto.actor.world.pos.x;
    diffZ = curPoint->z - this->picto.actor.world.pos.z;
    this->picto.actor.world.rot.y = Math_Atan2S(diffX, diffZ);
    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.world.rot.y, 2, 0x7D0, 0xC8);

    if ((SQ(diffX) + SQ(diffZ)) < 100.0f) {
        this->curPointIndex++;
        if (this->curPointIndex >= path->count) {
            return true;
        }
    }
    return false;
}

void EnGe3_Scream(EnGe3* this) {
    if ((s32)Rand_ZeroFloat(2.0f) == 0) {
        Actor_PlaySfxAtPos(&this->picto.actor, NA_SE_VO_FPVO00);
    } else {
        Actor_PlaySfxAtPos(&this->picto.actor, NA_SE_VO_FPVO01);
    }
}

void EnGe3_Idle(EnGe3* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    EnGe3_LookAtPlayer(this, play);

    if (EnGe3_FollowPath(this)) {
        EnGe3_SetupPath(this, play);
    }
}

void EnGe3_ThrowPlayerOut(EnGe3* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.yawTowardsPlayer, 2, 0x400, 0x100);

    if (this->actionTimer > 0) {
        this->actionTimer--;
    } else {
        if (play->nextEntrance != play->setupExitList[GERUDO_AVEIL_GET_EXIT(&this->picto.actor)]) {
            play->nextEntrance = play->setupExitList[GERUDO_AVEIL_GET_EXIT(&this->picto.actor)];
            play->transitionTrigger = TRANS_TRIGGER_START;
            play->transitionType = TRANS_TYPE_38;
            gSaveContext.save.weekEventReg[80] &= (u8)~8;
        }
    }
}

void EnGe3_PerformCutsceneActions(EnGe3* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime) && (this->csAction == 3)) {
        EnGe3_ChangeAnim(this, GERUDO_AVEIL_ANIM_4, ANIMMODE_ONCE, 0.0f);
    }

    if (Cutscene_CheckActorAction(play, 108)) {
        s16 csAction = play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 108)]->action;

        if (this->csAction != 7) {
            Cutscene_ActorTranslateAndYaw(&this->picto.actor, play, Cutscene_GetActorActionIndex(play, 108));
        }

        if (this->csAction != csAction) {
            this->csAction = csAction;
            switch (this->csAction) {
                case 1:
                    EnGe3_ChangeAnim(this, GERUDO_AVEIL_ANIM_2, ANIMMODE_LOOP, 0.0f);
                    break;

                case 2:
                    EnGe3_ChangeAnim(this, GERUDO_AVEIL_ANIM_3, ANIMMODE_ONCE, 0.0f);
                    this->skelAnime.playSpeed = 0.0f;
                    break;

                case 3:
                    EnGe3_ChangeAnim(this, GERUDO_AVEIL_ANIM_3, ANIMMODE_ONCE, 0.0f);
                    break;

                case 4:
                    EnGe3_ChangeAnim(this, GERUDO_AVEIL_ANIM_5, ANIMMODE_LOOP, 0.0f);
                    break;

                case 5:
                    EnGe3_ChangeAnim(this, GERUDO_AVEIL_ANIM_6, ANIMMODE_ONCE, 0.0f);
                    break;

                case 6:
                    EnGe3_ChangeAnim(this, GERUDO_AVEIL_ANIM_7, ANIMMODE_LOOP, 0.0f);
                    break;

                case 7:
                    EnGe3_ChangeAnim(this, GERUDO_AVEIL_ANIM_8, ANIMMODE_LOOP, 0.0f);
                    this->picto.actor.speedXZ = 5.0f;
                    this->screamTimer = (s32)(Rand_ZeroFloat(10.0f) + 20.0f);
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

        this->actionFunc = EnGe3_ThrowPlayerOut;
        this->actionTimer = 50;
        gSaveContext.save.weekEventReg[80] |= 8;
    }

    if (this->csAction == 7) {
        this->picto.actor.speedXZ = 5.0f;
        EnGe3_FollowPath(this);

        if (Animation_OnFrame(&this->skelAnime, 2.0f) || Animation_OnFrame(&this->skelAnime, 6.0f)) {
            Actor_PlaySfxAtPos(&this->picto.actor, NA_SE_EV_PIRATE_WALK);
        }

        if (this->screamTimer > 0) {
            this->screamTimer--;
        } else {
            this->screamTimer = (s32)(Rand_ZeroFloat(10.0f) + 20.0f);
            EnGe3_Scream(this);
        }
    }
}

void EnGe3_UpdateColliderAndMove(Actor* thisx, PlayState* play) {
    s32 pad;
    EnGe3* this = (EnGe3*)thisx;

    Collider_UpdateCylinder(&this->picto.actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    Actor_MoveWithGravity(&this->picto.actor);
    Actor_UpdateBgCheckInfo(play, &this->picto.actor, 40.0f, 25.0f, 40.0f, 4);
}

void EnGe3_Blink(EnGe3* this, PlayState* play) {
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

    EnGe3_UpdateColliderAndMove(&this->picto.actor, play);
    this->actionFunc(this, play);
    EnGe3_Blink(this, play);
}

s32 EnGe3_ValidatePictograph(PlayState* play, Actor* thisx) {
    s32 ret = Snap_ValidatePictograph(play, thisx, PICTOGRAPH_PIRATE_GOOD, &thisx->focus.pos, &thisx->shape.rot, 10.0f,
                                      400.0f, -1);

    ret |= Snap_ValidatePictograph(play, thisx, PICTOGRAPH_PIRATE_TOO_FAR, &thisx->focus.pos, &thisx->shape.rot, 10.0f,
                                   1200.0f, -1);

    return ret;
}

s32 EnGe3_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnGe3* this = THIS;

    switch (limbIndex) {
        case 5:
        case 11:
        case 16:
            *dList = NULL;
            return false;
        case 6:
            rot->x += this->headRot.y;
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

            if (this->animIndex == GERUDO_AVEIL_ANIM_2) {
                // Fidget
                if ((limbIndex == 8) || (limbIndex == 13) || (limbIndex == 2)) {
                    s32 temp = limbIndex * 50;

                    // required to match
                    rot->y = rot->y + (s32)(Math_SinS(play->state.frames * (temp + 0x814)) * 200.0f);
                    rot->z = rot->z + (s32)(Math_CosS(play->state.frames * (temp + 0x940)) * 200.0f);
                }
            }
            break;
    }
    return false;
}

void EnGe3_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnGe3* this = THIS;
    Vec3f sFocusOffset = { 600.0f, 700.0f, 0.0f };

    if (limbIndex == 6) {
        Matrix_MultVec3f(&sFocusOffset, &this->picto.actor.focus.pos);
    }
}

void EnGe3_Draw(Actor* thisx, PlayState* play) {
    static TexturePtr sEyeTextures[] = {
        0x06006398,
        0x06006958,
        0x060070D8,
    };
    s32 pad;
    EnGe3* this = (EnGe3*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C5B0(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeIndex]));
    func_800B8050(&this->picto.actor, play, 0);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnGe3_OverrideLimbDraw, EnGe3_PostLimbDraw, &this->picto.actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
