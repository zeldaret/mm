/*
 * File: z_dm_gm.c
 * Overlay: ovl_Dm_Gm
 * Description: Complete duplicate of Dm_An
 */

#include "z_dm_gm.h"
#include "objects/object_an4/object_an4.h"
#include "objects/object_msmo/object_msmo.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY)

#define THIS ((DmGm*)thisx)

void DmGm_Init(Actor* thisx, PlayState* play);
void DmGm_Destroy(Actor* thisx, PlayState* play);
void DmGm_Update(Actor* thisx, PlayState* play);

void func_80C248A8(DmGm* this, PlayState* play);
void DmGm_HandleCutscene(DmGm* this, PlayState* play);
void DmGm_DoNothing(DmGm* this, PlayState* play);
void func_80C25000(Actor* thisx, PlayState* play);

ActorInit Dm_Gm_InitVars = {
    ACTOR_DM_GM,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AN1,
    sizeof(DmGm),
    (ActorFunc)DmGm_Init,
    (ActorFunc)DmGm_Destroy,
    (ActorFunc)DmGm_Update,
    (ActorFunc)NULL,
};

typedef enum {
    /*  -1 */ DMGM_ANIM_NONE = -1,
    /* 0x0 */ DMGM_ANIM_0,
    /* 0x1 */ DMGM_ANIM_1,
    /* 0x2 */ DMGM_ANIM_2,
    /* 0x3 */ DMGM_ANIM_3,
    /* 0x4 */ DMGM_ANIM_4,
    /* 0x5 */ DMGM_ANIM_5,
    /* 0x6 */ DMGM_ANIM_6,
    /* 0x7 */ DMGM_ANIM_7,
    /* 0x8 */ DMGM_ANIM_8,
    /* 0x9 */ DMGM_ANIM_9,
    /* 0xA */ DMGM_ANIM_10,
    /* 0xB */ DMGM_ANIM_11,
    /* 0xC */ DMGM_ANIM_12,
    /* 0xD */ DMGM_ANIM_13,
    /* 0xE */ DMGM_ANIM_MAX
} DmGmAnimation;

static AnimationInfoS sAnimationInfo[DMGM_ANIM_MAX] = {
    { &object_an1_Anim_007E08, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // DMGM_ANIM_0
    { &object_an1_Anim_0071E8, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // DMGM_ANIM_1
    { &object_an4_Anim_006CC0, 1.0f, 0, -1, ANIMMODE_LOOP, -4 }, // DMGM_ANIM_2
    { &object_an1_Anim_013E1C, 1.0f, 0, -1, ANIMMODE_LOOP, -4 }, // DMGM_ANIM_3
    { &object_an4_Anim_007E3C, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },  // DMGM_ANIM_4
    { &object_an4_Anim_0088C0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // DMGM_ANIM_5
    { &object_an4_Anim_0013C8, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },  // DMGM_ANIM_6
    { &object_an4_Anim_002550, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // DMGM_ANIM_7
    { &object_an4_Anim_00353C, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },  // DMGM_ANIM_8
    { &object_an4_Anim_004498, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // DMGM_ANIM_9
    { &object_an4_Anim_0060B4, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },  // DMGM_ANIM_10
    { &object_an4_Anim_00041C, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },  // DMGM_ANIM_11
    { &object_an4_Anim_004A78, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },  // DMGM_ANIM_12
    { &object_an4_Anim_00506C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // DMGM_ANIM_13
};

s32 DmGm_UpdateSkelAnime(DmGm* this, PlayState* play) {
    s8 objectIndex = this->actor.objBankIndex;
    s8 objectIndex2;
    s32 isAnimFinished = false;

    if (this->animIndex <= DMGM_ANIM_1) {
        objectIndex2 = this->actor.objBankIndex;
    } else {
        objectIndex2 = this->unk_2AC;
    }

    if (objectIndex2 >= 0) {
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[objectIndex2].segment);
        isAnimFinished = SkelAnime_Update(&this->skelAnime);
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[objectIndex].segment);
    }

    return isAnimFinished;
}

s32 DmGm_ChangeAnim(DmGm* this, PlayState* play, s32 animIndex) {
    s8 objectIndex = this->actor.objBankIndex;
    s8 objectIndex2;
    s32 didAnimChange = false;

    if (animIndex <= DMGM_ANIM_1) {
        objectIndex2 = this->actor.objBankIndex;
    } else {
        objectIndex2 = this->unk_2AC;
    }

    if ((objectIndex2 >= 0) && (this->animIndex != animIndex)) {
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[objectIndex2].segment);
        this->animIndex = animIndex;
        didAnimChange = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, animIndex);
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[objectIndex].segment);
    }

    return didAnimChange;
}

void func_80C24504(DmGm* this) {
    if (DECR(this->unk_2BA) == 0) {
        this->unk_2B8++;
        if (this->unk_2B8 >= 4) {
            this->unk_2BA = Rand_S16Offset(30, 30);
            this->unk_2B8 = 0;
        }
    }
}

s32 func_80C2457C(DmGm* this, PlayState* play) {
    s32 pad;
    Vec3f sp40;
    Vec3f sp34;
    s16 sp32;

    Math_Vec3f_Copy(&sp40, &this->unk_2B4->world.pos);
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    sp32 = Math_Vec3f_Yaw(&sp34, &sp40);

    Math_ApproachS(&this->unk_2C0, (sp32 - this->unk_2C4) - this->actor.shape.rot.y, 4, 0x2AA8);
    this->unk_2C0 = CLAMP(this->unk_2C0, -0x1FFE, 0x1FFE);

    Math_ApproachS(&this->unk_2C4, (sp32 - this->unk_2C0) - this->actor.shape.rot.y, 4, 0x2AA8);
    this->unk_2C4 = CLAMP(this->unk_2C4, -0x1C70, 0x1C70);

    if (this->unk_2B4->id == ACTOR_PLAYER) {
        sp40.y = ((Player*)this->unk_2B4)->bodyPartsPos[PLAYER_BODYPART_HEAD].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&sp40, &this->unk_2B4->focus.pos);
    }

    Math_Vec3f_Copy(&sp34, &this->actor.focus.pos);
    Math_ApproachS(&this->unk_2BE, Math_Vec3f_Pitch(&sp34, &sp40) - this->unk_2C2, 4, 0x2AA8);
    this->unk_2BE = CLAMP(this->unk_2BE, -0x1C70, 0x1C70);

    Math_ApproachS(&this->unk_2C2, Math_Vec3f_Pitch(&sp34, &sp40) - this->unk_2BE, 4, 0x2AA8);
    this->unk_2C2 = CLAMP(this->unk_2C2, -0x1C70, 0x1C70);
    return true;
}

s32 func_80C2478C(DmGm* this, PlayState* play) {
    if (this->unk_2B4 != NULL) {
        func_80C2457C(this, play);
        this->unk_2AE &= ~1;
        this->unk_2AE |= 2;
    } else if (this->unk_2AE & 2) {
        this->unk_2AE &= ~2;
        this->unk_2BE = 0;
        this->unk_2C0 = 0;
        this->unk_2C2 = 0;
        this->unk_2C4 = 0;
        this->unk_2BC = 20;
    } else if (DECR(this->unk_2BC) == 0) {
        this->unk_2AE |= 1;
    }
    return true;
}

Actor* func_80C24838(PlayState* play) {
    Actor* tempActor;
    Actor* foundActor = NULL;

    while (true) {
        foundActor = SubS_FindActor(play, foundActor, ACTORCAT_NPC, ACTOR_DM_AH);

        if ((foundActor == NULL) || (foundActor->update != NULL)) {
            break;
        }

        tempActor = foundActor->next;
        if ((tempActor == NULL) || false) {
            foundActor = NULL;
            break;
        }
        foundActor = tempActor;
    }
    return foundActor;
}

void func_80C248A8(DmGm* this, PlayState* play) {
    if ((this->unk_2AC >= 0) && SubS_IsObjectLoaded(this->unk_2AC, play) && (this->unk_2AD >= 0) &&
        SubS_IsObjectLoaded(this->unk_2AD, play)) {
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 14.0f);
        SkelAnime_InitFlex(play, &this->skelAnime, &object_an1_Skel_012618, NULL, this->jointTable, this->morphTable,
                           OBJECT_AN1_LIMB_MAX);

        this->animIndex = DMGM_ANIM_NONE;
        DmGm_ChangeAnim(this, play, DMGM_ANIM_0);
        this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
        Actor_SetScale(&this->actor, 0.01f);
        this->unk_2AE |= 1;
        this->actor.draw = func_80C25000;

        if ((play->sceneId == SCENE_YADOYA) && (play->curSpawn == 4)) {
            this->unk_2B4 = func_80C24838(play);
            DmGm_ChangeAnim(this, play, DMGM_ANIM_1);
            this->actionFunc = DmGm_DoNothing;
        } else {
            this->actionFunc = DmGm_HandleCutscene;
        }
    }
}

void DmGm_HandleCutscene(DmGm* this, PlayState* play) {
    s32 csAnimIndex[] = {
        DMGM_ANIM_0, DMGM_ANIM_0, DMGM_ANIM_12, DMGM_ANIM_2,  DMGM_ANIM_4,
        DMGM_ANIM_6, DMGM_ANIM_8, DMGM_ANIM_10, DMGM_ANIM_11, DMGM_ANIM_3,
    };
    u16 cueId;
    s32 cueChannel;

    if (play->csCtx.state != CS_STATE_IDLE) {
        if (!this->isCutscenePlaying) {
            this->cueId = 255;
            this->isCutscenePlaying = true;
            this->didAnimChangeInCs = false;
            this->prevAnimIndex = this->animIndex;
        }

        if (Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_557)) {
            cueChannel = Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_557);
            cueId = play->csCtx.actorCues[cueChannel]->id;

            if (this->cueId != (u8)cueId) {
                this->cueId = cueId;
                this->didAnimChangeInCs = true;
                DmGm_ChangeAnim(this, play, csAnimIndex[cueId]);
            }

            switch (this->cueId) {
                case 2:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                    if ((this->animIndex == DMGM_ANIM_12) || (this->animIndex == DMGM_ANIM_4) ||
                        (this->animIndex == DMGM_ANIM_6) || (this->animIndex == DMGM_ANIM_8)) {
                        if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                            DmGm_ChangeAnim(this, play, this->animIndex + 1);
                        }
                    }
                    break;

                default:
                    break;
            }
            Cutscene_ActorTranslateAndYaw(&this->actor, play, cueChannel);
        }
    } else if (this->isCutscenePlaying) {
        this->isCutscenePlaying = false;
        this->didAnimChangeInCs = false;
        DmGm_ChangeAnim(this, play, this->prevAnimIndex);
    }
}

void DmGm_DoNothing(DmGm* this, PlayState* play) {
}

void DmGm_Init(Actor* thisx, PlayState* play) {
    DmGm* this = THIS;

    this->unk_2AC = SubS_GetObjectIndex(OBJECT_AN4, play);
    this->unk_2AD = SubS_GetObjectIndex(OBJECT_MSMO, play);
    this->actionFunc = func_80C248A8;
}

void DmGm_Destroy(Actor* thisx, PlayState* play) {
}

void DmGm_Update(Actor* thisx, PlayState* play) {
    DmGm* this = THIS;

    this->actionFunc(this, play);

    func_80C2478C(this, play);

    if (this->actor.draw != NULL) {
        DmGm_UpdateSkelAnime(this, play);
        func_80C24504(this);
    }
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 12.0f, 0.0f, UPDBGCHECKINFO_FLAG_4);
}

Vec3f D_80C25218 = { 450.0f, 700.0f, -760.0f };
Vec3s D_80C25224 = { 0x238C, 0, -0x3FFC };
Vec3f D_80C2522C = { 1000.0f, 0.0f, 0.0f };

void DmGm_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    s32 pad[2];
    DmGm* this = THIS;
    s8 sp2B = this->actor.objBankIndex;
    s8 sp2A = this->unk_2AD;

    if ((limbIndex == OBJECT_AN1_LIMB_05) && this->didAnimChangeInCs) {
        OPEN_DISPS(play->state.gfxCtx);

        Matrix_Push();
        Matrix_TranslateRotateZYX(&D_80C25218, &D_80C25224);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.status[sp2A].segment);
        gSPDisplayList(POLY_OPA_DISP++, gMoonMaskDL);
        gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.status[sp2B].segment);

        Matrix_Pop();

        CLOSE_DISPS(play->state.gfxCtx);
    }

    if (limbIndex == OBJECT_AN1_LIMB_09) {
        Matrix_MultVec3f(&D_80C2522C, &this->actor.focus.pos);
        Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
    }
}

void DmGm_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
    DmGm* this = THIS;
    s16 stepRot;
    s16 overrideRot;

    if (!(this->unk_2AE & 1)) {
        if (this->unk_2AE & 2) {
            overrideRot = true;
        } else {
            overrideRot = false;
        }
        stepRot = true;
    } else {
        stepRot = false;
        overrideRot = false;
    }

    if (limbIndex == OBJECT_AN1_LIMB_09) {
        SubS_UpdateLimb(this->unk_2BE + this->unk_2C2 + 0x4000,
                        this->unk_2C0 + this->unk_2C4 + this->actor.shape.rot.y + 0x4000, &this->unk_18C,
                        &this->unk_1A4, stepRot, overrideRot);
        Matrix_Pop();
        Matrix_Translate(this->unk_18C.x, this->unk_18C.y, this->unk_18C.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateYS(this->unk_1A4.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->unk_1A4.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->unk_1A4.z, MTXMODE_APPLY);
        Matrix_Push();
    } else if (limbIndex == OBJECT_AN1_LIMB_02) {
        SubS_UpdateLimb(this->unk_2C2 + 0x4000, this->unk_2C4 + this->actor.shape.rot.y + 0x4000, &this->unk_194,
                        &this->unk_1AA, stepRot, overrideRot);
        Matrix_Pop();
        Matrix_Translate(this->unk_194.x, this->unk_194.y, this->unk_194.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateYS(this->unk_1AA.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->unk_1AA.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->unk_1AA.z, MTXMODE_APPLY);
        Matrix_Push();
    }
}

TexturePtr D_80C25238[] = {
    object_an1_Tex_00E6E0,
    object_an1_Tex_00F7A0,
    object_an1_Tex_0101A0,
};

TexturePtr D_80C25244[] = {
    object_an1_Tex_00E1E0, object_an1_Tex_00EFA0, object_an1_Tex_00F3A0, object_an1_Tex_00EFA0,
    object_an1_Tex_00FDA0, object_an1_Tex_00F9A0, object_an1_Tex_0103A0,
};

void func_80C25000(Actor* thisx, PlayState* play) {
    DmGm* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80C25244[this->unk_2B8]));
    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80C25238[0]));

    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, NULL, DmGm_PostLimbDraw, DmGm_TransformLimbDraw,
                                   &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
