/*
 * File: z_en_fall2.c
 * Overlay: ovl_En_Fall2
 * Description: "Warp Beam" from Moon's Mouth in Cutscene?
 */

#include "z_en_fall2.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnFall2*)thisx)

void EnFall2_Init(Actor* thisx, PlayState* play);
void EnFall2_Destroy(Actor* thisx, PlayState* play);
void EnFall2_Update(Actor* thisx, PlayState* play);
void EnFall2_Draw(Actor* thisx, PlayState* play);

void EnFall2_DoNothing(EnFall2* this, PlayState* play);
void EnFall2_HandleCutscene(EnFall2* this, PlayState* play);

ActorInit En_Fall2_InitVars = {
    /**/ ACTOR_EN_FALL2,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ OBJECT_FALL2,
    /**/ sizeof(EnFall2),
    /**/ EnFall2_Init,
    /**/ EnFall2_Destroy,
    /**/ EnFall2_Update,
    /**/ EnFall2_Draw,
};

void EnFall2_Init(Actor* thisx, PlayState* play) {
    EnFall2* this = THIS;

    Actor_SetScale(&this->actor, 1.0f);
    this->actionFunc = EnFall2_DoNothing;
    func_80183430(&this->skeletonInfo, object_fall2_Blob_008898, object_fall2_Blob_005EF4, this->unk174, this->unk228,
                  NULL);
    func_801835EC(&this->skeletonInfo, object_fall2_Blob_005EF4);
    this->unk2DC = Lib_SegmentedToVirtual(object_fall2_Matanimheader_008840);
    Actor_SetScale(&this->actor, 0.02f);
    this->actionFunc = EnFall2_HandleCutscene;
    this->cueType = CS_CMD_ACTOR_CUE_561;
    this->alphaLevel = 0.0f;
}

void EnFall2_Destroy(Actor* thisx, PlayState* play) {
    EnFall2* this = THIS;

    func_8018349C(&this->skeletonInfo);
}

static u8 sAlphaTableIndices[] = {
    0, 2, 0, 0, 4, 0, 4, 4, 2, 0, 0, 0, 0, 0, 0, 2, 4, 4, 4, 2, 0, 4, 2, 2, 0, 4, 4, 4, 4, 0, 2, 2, 4, 0, 2,
    0, 4, 4, 2, 0, 2, 4, 4, 4, 2, 0, 4, 4, 4, 2, 2, 0, 4, 4, 2, 4, 0, 2, 0, 0, 2, 4, 4, 2, 0, 2, 4, 4, 4, 2,
    0, 4, 4, 4, 4, 4, 2, 2, 0, 2, 4, 0, 2, 0, 0, 2, 4, 4, 2, 0, 2, 4, 4, 4, 2, 0, 0, 2, 2, 4, 4, 4, 4, 4, 4,
    2, 0, 2, 0, 0, 2, 4, 4, 2, 0, 2, 4, 4, 4, 2, 0, 2, 0, 5, 2, 5, 5, 5, 5, 0, 2, 5, 0, 2, 0, 2, 5, 5, 2, 0,
    2, 5, 5, 5, 2, 0, 3, 3, 3, 2, 2, 0, 0, 3, 3, 0, 2, 2, 3, 0, 2, 3, 3, 2, 0, 2, 3, 3, 3, 2, 0, 2, 2, 2, 2,
    0, 2, 2, 2, 2, 2, 0, 0, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

void func_80C1B724(f32 arg0) {
    Vtx* vertex = Lib_SegmentedToVirtual(object_fall2_Vtx_005F10);
    u8 perVertexAlphaTable[6];
    s32 i;

    if (arg0 > 1.0f) {
        arg0 = 1.0f;
    }
    if (arg0 < 0.0f) {
        arg0 = 0.0f;
    }
    perVertexAlphaTable[0] = 0;
    perVertexAlphaTable[1] = (s8)(54.0f * arg0);
    perVertexAlphaTable[2] = (s8)(104.0f * arg0);
    perVertexAlphaTable[3] = (s8)(155.0f * arg0);
    perVertexAlphaTable[4] = (s8)(255.0f * arg0);
    perVertexAlphaTable[5] = (s8)(205.0f * arg0);

    for (i = 0; i < ARRAY_COUNT(sAlphaTableIndices); i++, vertex++) {
        vertex->v.cn[3] = perVertexAlphaTable[sAlphaTableIndices[i]];
    }
}

void EnFall2_DoNothing(EnFall2* this, PlayState* play) {
}

void func_80C1B8B4(EnFall2* this) {
    this->actor.draw = EnFall2_Draw;
    if (this->cueId == 1) {
        Actor_SetScale(&this->actor, 0.02f);
    }
}

void func_80C1B8F0(EnFall2* this) {
    switch (this->cueId) {
        case 1:
            if (this->alphaLevel < 1.0f) {
                this->alphaLevel += 1.0f / 30.0f;
            } else {
                this->alphaLevel = 1.0f;
            }
            break;

        case 2:
            if (this->alphaLevel > 0.0f) {
                this->alphaLevel -= 0.1f;
                if (this->alphaLevel < 0.0f) {
                    this->alphaLevel = 0.0f;
                }
            }
            if (this->actor.scale.x > 0.0f) {
                this->actor.scale.x -= 20.0f * 0.0001f;
                if (this->actor.scale.x < 0.0f) {
                    this->actor.scale.x = 0.0f;
                }
                this->actor.scale.z = this->actor.scale.x;
            }

        default:
            break;
    }
}

void EnFall2_HandleCutscene(EnFall2* this, PlayState* play) {
    func_80183DE0(&this->skeletonInfo);
    if (Cutscene_IsCueInChannel(play, this->cueType)) {
        Cutscene_ActorTranslateAndYaw(&this->actor, play, Cutscene_GetCueChannel(play, this->cueType));
        if (this->cueId != play->csCtx.actorCues[Cutscene_GetCueChannel(play, this->cueType)]->id) {
            this->cueId = play->csCtx.actorCues[Cutscene_GetCueChannel(play, this->cueType)]->id;
            func_80C1B8B4(this);
        }
        func_80C1B8F0(this);
        if (this->alphaLevel > 0.0f) {
            Actor_PlaySfx_Flagged(&this->actor, NA_SE_EV_MOON_LIGHT_PILLAR - SFX_FLAG);
        }
    } else {
        this->actor.draw = NULL;
    }
    func_80C1B724(this->alphaLevel);
}

void EnFall2_Update(Actor* thisx, PlayState* play) {
    EnFall2* this = THIS;

    this->actionFunc(this, play);
}

void EnFall2_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    EnFall2* this = THIS;
    Mtx* mtx;

    if (!(this->alphaLevel <= 0.0f)) {
        Gfx_SetupDL25_Xlu(play->state.gfxCtx);
        AnimatedMat_DrawXlu(play, Lib_SegmentedToVirtual(object_fall2_Matanimheader_008840));

        mtx = GRAPH_ALLOC(play->state.gfxCtx, this->skeletonInfo.unk_18->unk_1 * sizeof(Mtx));

        if (mtx != NULL) {
            Gfx_SetupDL25_Xlu(play->state.gfxCtx);
            Matrix_RotateYS((s16)(Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)) + 0x8000), MTXMODE_APPLY);
            func_8018450C(play, &this->skeletonInfo, mtx, NULL, NULL, &this->actor);
        }
    }
}
