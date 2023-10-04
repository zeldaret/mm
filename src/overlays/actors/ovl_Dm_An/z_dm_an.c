/*
 * File: z_dm_an.c
 * Overlay: ovl_Dm_An
 * Description: Anju (cutscene)
 */

#include "z_dm_an.h"
#include "objects/object_an4/object_an4.h"
#include "objects/object_msmo/object_msmo.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY)

#define THIS ((DmAn*)thisx)

void DmAn_Init(Actor* thisx, PlayState* play);
void DmAn_Destroy(Actor* thisx, PlayState* play);
void DmAn_Update(Actor* thisx, PlayState* play);

void func_80C1C958(DmAn* this, PlayState* play);
void DmAn_HandleCutscene(DmAn* this, PlayState* play);
void DmAn_DoNothing(DmAn* this, PlayState* play);
void func_80C1D0B0(Actor* thisx, PlayState* play);

ActorInit Dm_An_InitVars = {
    ACTOR_DM_AN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AN1,
    sizeof(DmAn),
    (ActorFunc)DmAn_Init,
    (ActorFunc)DmAn_Destroy,
    (ActorFunc)DmAn_Update,
    (ActorFunc)NULL,
};

typedef enum {
    /*  -1 */ DMAN_ANIM_NONE = -1,
    /* 0x0 */ DMAN_ANIM_0,
    /* 0x1 */ DMAN_ANIM_1,
    /* 0x2 */ DMAN_ANIM_2,
    /* 0x3 */ DMAN_ANIM_3,
    /* 0x4 */ DMAN_ANIM_4,
    /* 0x5 */ DMAN_ANIM_5,
    /* 0x6 */ DMAN_ANIM_6,
    /* 0x7 */ DMAN_ANIM_7,
    /* 0x8 */ DMAN_ANIM_8,
    /* 0x9 */ DMAN_ANIM_9,
    /* 0xA */ DMAN_ANIM_10,
    /* 0xB */ DMAN_ANIM_11,
    /* 0xC */ DMAN_ANIM_12,
    /* 0xD */ DMAN_ANIM_13,
    /* 0xE */ DMAN_ANIM_MAX
} DmAnAnimation;

static AnimationInfoS sAnimationInfo[DMAN_ANIM_MAX] = {
    { &object_an1_Anim_007E08, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // DMAN_ANIM_0
    { &object_an1_Anim_0071E8, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // DMAN_ANIM_1
    { &object_an4_Anim_006CC0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // DMAN_ANIM_2
    { &object_an1_Anim_013E1C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // DMAN_ANIM_3
    { &object_an4_Anim_007E3C, 1.0f, 0, -1, ANIMMODE_ONCE, 0 }, // DMAN_ANIM_4
    { &object_an4_Anim_0088C0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // DMAN_ANIM_5
    { &object_an4_Anim_0013C8, 1.0f, 0, -1, ANIMMODE_ONCE, 0 }, // DMAN_ANIM_6
    { &object_an4_Anim_002550, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // DMAN_ANIM_7
    { &object_an4_Anim_00353C, 1.0f, 0, -1, ANIMMODE_ONCE, 0 }, // DMAN_ANIM_8
    { &object_an4_Anim_004498, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // DMAN_ANIM_9
    { &object_an4_Anim_0060B4, 1.0f, 0, -1, ANIMMODE_ONCE, 0 }, // DMAN_ANIM_10
    { &object_an4_Anim_00041C, 1.0f, 0, -1, ANIMMODE_ONCE, 0 }, // DMAN_ANIM_11
    { &object_an4_Anim_004A78, 1.0f, 0, -1, ANIMMODE_ONCE, 0 }, // DMAN_ANIM_12
    { &object_an4_Anim_00506C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // DMAN_ANIM_13
};

s32 DmAn_UpdateSkelAnime(DmAn* this, PlayState* play) {
    s8 objectSlot = this->actor.objectSlot;
    s8 objectSlot2;
    s32 isAnimFinished = false;

    if (this->animIndex <= DMAN_ANIM_1) {
        objectSlot2 = this->actor.objectSlot;
    } else {
        objectSlot2 = this->an4ObjectSlot;
    }

    if (objectSlot2 >= 0) {
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.slots[objectSlot2].segment);
        isAnimFinished = SkelAnime_Update(&this->skelAnime);
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.slots[objectSlot].segment);
    }

    return isAnimFinished;
}

s32 DmAn_ChangeAnim(DmAn* this, PlayState* play, s32 animIndex) {
    s8 objectSlot = this->actor.objectSlot;
    s8 objectSlot2;
    s32 didAnimChange = false;

    if (animIndex <= DMAN_ANIM_1) {
        objectSlot2 = this->actor.objectSlot;
    } else {
        objectSlot2 = this->an4ObjectSlot;
    }

    if ((objectSlot2 >= 0) && (this->animIndex != animIndex)) {
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.slots[objectSlot2].segment);
        this->animIndex = animIndex;
        didAnimChange = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, animIndex);
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.slots[objectSlot].segment);
    }

    return didAnimChange;
}

void func_80C1C5B4(DmAn* this) {
    if (DECR(this->unk_2BA) == 0) {
        this->unk_2B8++;
        if (this->unk_2B8 >= 4) {
            this->unk_2BA = Rand_S16Offset(30, 30);
            this->unk_2B8 = 0;
        }
    }
}

s32 func_80C1C62C(DmAn* this, PlayState* play) {
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

s32 func_80C1C83C(DmAn* this, PlayState* play) {
    if (this->unk_2B4 != NULL) {
        func_80C1C62C(this, play);
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

Actor* func_80C1C8E8(PlayState* play) {
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

void func_80C1C958(DmAn* this, PlayState* play) {
    if ((this->an4ObjectSlot > OBJECT_SLOT_NONE) && SubS_IsObjectLoaded(this->an4ObjectSlot, play) &&
        (this->msmoObjectSlot > OBJECT_SLOT_NONE) && SubS_IsObjectLoaded(this->msmoObjectSlot, play)) {
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 14.0f);
        SkelAnime_InitFlex(play, &this->skelAnime, &object_an1_Skel_012618, NULL, this->jointTable, this->morphTable,
                           OBJECT_AN1_LIMB_MAX);

        this->animIndex = DMAN_ANIM_NONE;
        DmAn_ChangeAnim(this, play, DMAN_ANIM_0);
        this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
        Actor_SetScale(&this->actor, 0.01f);
        this->unk_2AE |= 1;
        this->actor.draw = func_80C1D0B0;

        if ((play->sceneId == SCENE_YADOYA) && (play->curSpawn == 4)) {
            this->unk_2B4 = func_80C1C8E8(play);
            DmAn_ChangeAnim(this, play, DMAN_ANIM_1);
            this->actionFunc = DmAn_DoNothing;
        } else {
            this->actionFunc = DmAn_HandleCutscene;
        }
    }
}

void DmAn_HandleCutscene(DmAn* this, PlayState* play) {
    s32 csAnimIndex[] = {
        DMAN_ANIM_0, DMAN_ANIM_0, DMAN_ANIM_12, DMAN_ANIM_2,  DMAN_ANIM_4,
        DMAN_ANIM_6, DMAN_ANIM_8, DMAN_ANIM_10, DMAN_ANIM_11, DMAN_ANIM_3,
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
                DmAn_ChangeAnim(this, play, csAnimIndex[cueId]);
            }

            switch (this->cueId) {
                case 2:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                    if ((this->animIndex == DMAN_ANIM_12) || (this->animIndex == DMAN_ANIM_4) ||
                        (this->animIndex == DMAN_ANIM_6) || (this->animIndex == DMAN_ANIM_8)) {
                        if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                            DmAn_ChangeAnim(this, play, this->animIndex + 1);
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
        DmAn_ChangeAnim(this, play, this->prevAnimIndex);
    }
}

void DmAn_DoNothing(DmAn* this, PlayState* play) {
}

void DmAn_Init(Actor* thisx, PlayState* play) {
    DmAn* this = THIS;

    this->an4ObjectSlot = SubS_GetObjectSlot(OBJECT_AN4, play);
    this->msmoObjectSlot = SubS_GetObjectSlot(OBJECT_MSMO, play);
    this->actionFunc = func_80C1C958;
}

void DmAn_Destroy(Actor* thisx, PlayState* play) {
}

void DmAn_Update(Actor* thisx, PlayState* play) {
    DmAn* this = THIS;

    this->actionFunc(this, play);

    func_80C1C83C(this, play);

    if (this->actor.draw != NULL) {
        DmAn_UpdateSkelAnime(this, play);
        func_80C1C5B4(this);
    }
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 12.0f, 0.0f, UPDBGCHECKINFO_FLAG_4);
}

Vec3f D_80C1D2C8 = { 450.0f, 700.0f, -760.0f };
Vec3s D_80C1D2D4 = { 0x238C, 0, -0x3FFC };
Vec3f D_80C1D2DC = { 1000.0f, 0.0f, 0.0f };

void func_80C1CD80(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    s32 pad[2];
    DmAn* this = THIS;
    s8 objectSlot = this->actor.objectSlot;
    s8 msmoObjectSlot = this->msmoObjectSlot;

    if ((limbIndex == OBJECT_AN1_LIMB_05) && this->didAnimChangeInCs) {
        OPEN_DISPS(play->state.gfxCtx);

        Matrix_Push();
        Matrix_TranslateRotateZYX(&D_80C1D2C8, &D_80C1D2D4);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[msmoObjectSlot].segment);
        gSPDisplayList(POLY_OPA_DISP++, gMoonMaskDL);
        gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[objectSlot].segment);

        Matrix_Pop();

        CLOSE_DISPS(play->state.gfxCtx);
    }

    if (limbIndex == OBJECT_AN1_LIMB_09) {
        Matrix_MultVec3f(&D_80C1D2DC, &this->actor.focus.pos);
        Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
    }
}

void func_80C1CEFC(PlayState* play, s32 limbIndex, Actor* thisx) {
    DmAn* this = THIS;
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

TexturePtr D_80C1D2E8[] = {
    object_an1_Tex_00E6E0,
    object_an1_Tex_00F7A0,
    object_an1_Tex_0101A0,
};

TexturePtr D_80C1D2F4[] = {
    object_an1_Tex_00E1E0, object_an1_Tex_00EFA0, object_an1_Tex_00F3A0, object_an1_Tex_00EFA0,
    object_an1_Tex_00FDA0, object_an1_Tex_00F9A0, object_an1_Tex_0103A0,
};

void func_80C1D0B0(Actor* thisx, PlayState* play) {
    DmAn* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80C1D2F4[this->unk_2B8]));
    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80C1D2E8[0]));

    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, NULL, func_80C1CD80, func_80C1CEFC, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
