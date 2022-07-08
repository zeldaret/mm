/*
 * File: z_en_hgo.c
 * Overlay: ovl_En_Hgo
 * Description: Pamela's Father (Gibdo)
 */

#include "z_en_hgo.h"
#include "objects/object_harfgibud/object_harfgibud.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((EnHgo*)thisx)

void EnHgo_Init(Actor* thisx, PlayState* play);
void EnHgo_Destroy(Actor* thisx, PlayState* play);
void EnHgo_Update(Actor* thisx, PlayState* play);
void EnHgo_Draw(Actor* thisx, PlayState* play);

void func_80BD03EC(EnHgo* this);
void func_80BD0410(EnHgo* this, PlayState* play);
void func_80BD0434(EnHgo* this, PlayState* play);
void func_80BD049C(EnHgo* this);
void func_80BD04E0(EnHgo* this, PlayState* play);
void EnHgo_SetupDialogueHandler(EnHgo* this);
void EnHgo_DefaultDialogueHandler(EnHgo* this, PlayState* play);
void func_80BD06FC(EnHgo* this, PlayState* play);
s32 func_80BD0898(EnHgo* this, PlayState* play);
s32 EnHgo_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void EnHgo_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* pos, Actor* thisx);

const ActorInit En_Hgo_InitVars = {
    ACTOR_EN_HGO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_HARFGIBUD,
    sizeof(EnHgo),
    (ActorFunc)EnHgo_Init,
    (ActorFunc)EnHgo_Destroy,
    (ActorFunc)EnHgo_Update,
    (ActorFunc)EnHgo_Draw,
};

static AnimationInfo sAnimations[] = {
    { &object_harfgibud_Anim_00B644, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    { &object_harfgibud_Anim_013684, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &object_harfgibud_Anim_0152EC, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f },
    { &object_harfgibud_Anim_015C70, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &object_harfgibud_Anim_0165F0, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &object_harfgibud_Anim_014220, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f },
    { &object_harfgibud_Anim_014A9C, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 18, 46, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

static TexturePtr sEyeTextures[] = {
    object_harfgibud_Tex_011138,
    object_harfgibud_Tex_011938,
    object_harfgibud_Tex_012138,
};

void EnHgo_Init(Actor* thisx, PlayState* play) {
    EnHgo* this = THIS;
    s32 pad;

    ActorShape_Init(&thisx->shape, 0.0f, ActorShadow_DrawCircle, 36.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_harfgibud_Skel_012A58, &object_harfgibud_Anim_00B644,
                       this->jointTable, this->morphTable, HGO_LIMB_MAX);
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&thisx->colChkInfo, NULL, &sColChkInfoInit);
    thisx->targetMode = 6;
    this->unk_30C = 0;
    this->unk_30E = 0;
    this->unk_314 = 0;
    this->unk_310 = 0;
    this->unk_312 = 0;
    if ((gSaveContext.save.weekEventReg[75] & 0x20) || (gSaveContext.save.weekEventReg[52] & 0x20)) {
        func_80BD049C(this);
    } else {
        thisx->draw = NULL;
        func_80BD03EC(this);
    }
}

void EnHgo_Destroy(Actor* thisx, PlayState* play) {
    EnHgo* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void func_80BD03EC(EnHgo* this) {
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actionFunc = func_80BD0410;
}

void func_80BD0410(EnHgo* this, PlayState* play) {
}

void func_80BD0420(EnHgo* this) {
    this->actionFunc = func_80BD0434;
}

void func_80BD0434(EnHgo* this, PlayState* play) {
    this->collider.dim.pos.x = this->actor.focus.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.focus.pos.z;
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

void func_80BD049C(EnHgo* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
    this->actionFunc = func_80BD04E0;
}

void func_80BD04E0(EnHgo* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        if (Player_GetMask(play) == PLAYER_MASK_GIBDO) {
            if (!(this->unk_310 & 4)) {
                this->unk_310 |= 4;
                Message_StartTextbox(play, 0x15A5, &this->actor);
                this->unk_314 = 0x15A5; // That mask is a gibdo

            } else {
                Message_StartTextbox(play, 0x15A7, &this->actor);
                this->unk_314 = 0x15A7; // can I research that mask
            }
        } else if (gSaveContext.save.playerForm == PLAYER_FORM_HUMAN) {
            if (!(this->unk_310 & 1)) {
                this->unk_310 |= 1;
                Message_StartTextbox(play, 0x158F, &this->actor);
                this->unk_314 = 0x158F; // Isn't this a fairy
            } else {
                Message_StartTextbox(play, 0x1593, &this->actor);
                this->unk_314 = 0x1593; // Never seen a fairy this lively
            }
        } else {
            if (!(this->unk_310 & 2)) {
                this->unk_310 |= 2;
                Message_StartTextbox(play, 0x1595, &this->actor);
                this->unk_314 = 0x1595; // ghost radar is reacting
            } else {
                Message_StartTextbox(play, 0x1598, &this->actor);
                this->unk_314 = 0x1598; // you seem to be similar to a ghost
            }
        }
        EnHgo_SetupDialogueHandler(this);
    } else {
        func_800B8614(&this->actor, play, 100.0f);
    }
}

void EnHgo_SetupDialogueHandler(EnHgo* this) {
    this->actionFunc = EnHgo_DefaultDialogueHandler;
}

void EnHgo_DefaultDialogueHandler(EnHgo* this, PlayState* play) {
    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_NONE:
        case TEXT_STATE_1:
        case TEXT_STATE_CLOSING:
        case TEXT_STATE_3:
        case TEXT_STATE_CHOICE:
            break;

        case TEXT_STATE_5:
            func_80BD06FC(this, play);
            break;

        case TEXT_STATE_DONE:
            if (Message_ShouldAdvance(play)) {
                func_80BD049C(this);
            }
            break;
    }

    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x71C, 0xB6);
    this->actor.shape.rot.y = this->actor.world.rot.y;
}

void func_80BD06FC(EnHgo* this, PlayState* play) {
    if (Message_ShouldAdvance(play)) {
        switch (this->unk_314) {
            case 0x158F:
                Message_StartTextbox(play, 0x1590, &this->actor);
                this->unk_314 = 0x1590;
                break;
            case 0x1590:
                if (gSaveContext.save.weekEventReg[14] & 4) {
                    Message_StartTextbox(play, 0x1591, &this->actor);
                    this->unk_314 = 0x1591;
                    break;
                }
                Message_StartTextbox(play, 0x1592, &this->actor);
                this->unk_314 = 0x1592;
                break;
            case 0x1591:
                Message_StartTextbox(play, 0x1592, &this->actor);
                this->unk_314 = 0x1592;
                break;
            case 0x1593:
                Message_StartTextbox(play, 0x1594, &this->actor);
                this->unk_314 = 0x1594;
                break;
            case 0x1595:
                Message_StartTextbox(play, 0x1596, &this->actor);
                this->unk_314 = 0x1596;
                break;
            case 0x1596:
                Message_StartTextbox(play, 0x1597, &this->actor);
                this->unk_314 = 0x1597;
                break;
            case 0x1598:
                Message_StartTextbox(play, 0x1599, &this->actor);
                this->unk_314 = 0x1599;
                break;
            case 0x15A5:
                Message_StartTextbox(play, 0x15A6, &this->actor);
                this->unk_314 = 0x15A6;
                break;
            case 0x15A6:
                Message_StartTextbox(play, 0x15A7, &this->actor);
                this->unk_314 = 0x15A7;
                break;
            case 0x15A7:
                func_801477B4(play);
                func_80BD049C(this);
                break;
        }
    }
}

s32 func_80BD0898(EnHgo* this, PlayState* play) {
    s32 actionIndex;

    if (Cutscene_CheckActorAction(play, 486)) {
        actionIndex = Cutscene_GetActorActionIndex(play, 486);
        if (this->unk_316 != play->csCtx.actorActions[actionIndex]->action) {
            this->unk_316 = play->csCtx.actorActions[actionIndex]->action;
            switch (play->csCtx.actorActions[actionIndex]->action) {
                case 1:
                    this->unk_218 = 0;
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
                    break;
                case 2:
                    this->actor.draw = EnHgo_Draw;
                    this->unk_218 = 1;
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
                    break;
                case 3:
                    this->unk_218 = 2;
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
                    break;
                case 4:
                    this->unk_218 = 3;
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
                    break;
                case 5:
                    this->unk_218 = 4;
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 4);
                    break;
                case 6:
                    this->unk_218 = 5;
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 5);
                    break;
            }
        } else if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            switch (this->unk_218) {
                case 1:
                    if ((Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) && (this->unk_312 == 0)) {
                        this->unk_312 = 1;
                        if ((gSaveContext.sceneSetupIndex == 0) &&
                            ((play->csCtx.currentCsIndex == 2) || (play->csCtx.currentCsIndex == 4))) {
                            Actor_PlaySfxAtPos(&this->actor, NA_SE_VO_GBVO02);
                        }
                    }
                    break;
                case 2:
                    this->unk_218 = 3;
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
                    break;
                case 5:
                    this->unk_218 = 6;
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 6);
            }
        }

        Cutscene_ActorTranslateAndYaw(&this->actor, play, actionIndex);
        return true;
    }
    if ((play->csCtx.state == 0) && (((gSaveContext.save.weekEventReg[75]) & 0x20)) &&
        (this->actionFunc == func_80BD0410)) {
        this->actor.shape.rot.y = this->actor.world.rot.y;
        Actor_Spawn(&play->actorCtx, play, ACTOR_ELF_MSG2, this->actor.focus.pos.x, this->actor.focus.pos.y,
                    this->actor.focus.pos.z, 7, 0, 0, 0x7F5A);
        func_80BD0420(this);
    }
    this->unk_316 = 0x63;
    return false;
}

void func_80BD0B8C(EnHgo* this, PlayState* play) {
    Actor_TrackPlayer(play, &this->actor, &this->unk_300, &this->unk_306, this->actor.focus.pos);
    if (this->unk_30E > 2) {
        this->unk_30E--;
    } else if (this->unk_30E == 2) {
        this->unk_30C = 1;
        this->unk_30E = 1;
    } else if (this->unk_30E == 1) {
        this->unk_30C = 2;
        this->unk_30E = 0;
    } else {
        this->unk_30C = 0;
        this->unk_30E = 60;
    }
}

void EnHgo_Update(Actor* thisx, PlayState* play) {
    EnHgo* this = THIS;
    s32 pad;

    this->actionFunc(this, play);
    SkelAnime_Update(&this->skelAnime);
    if (func_80BD0898(this, play)) {
        Actor_TrackNone(&this->unk_300, &this->unk_306);
    } else if (this->actionFunc != func_80BD0410) {
        if (this->actionFunc != func_80BD0434) {
            Collider_UpdateCylinder(&this->actor, &this->collider);
            CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
            func_80BD0B8C(this, play);
        }
    }
}

s32 EnHgo_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnHgo* this = THIS;

    if (limbIndex == HGO_LIMB_PELVIS) {
        rot->x += this->unk_300.y;
        rot->z += this->unk_300.x;
    }
    return false;
}

void EnHgo_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* pos, Actor* thisx) {
    EnHgo* this = THIS;

    if (limbIndex == HGO_LIMB_PELVIS) {
        Matrix_Get(&this->unk_1D8);
        Matrix_MultZero(&this->actor.focus.pos);
    }
}

void EnHgo_Draw(Actor* thisx, PlayState* play) {
    EnHgo* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->unk_30C]));
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnHgo_OverrideLimbDraw, &EnHgo_PostLimbDraw, &this->actor);
    Matrix_Put(&this->unk_1D8);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_harfgibud_DL_00F248);
    CLOSE_DISPS(play->state.gfxCtx);
}
