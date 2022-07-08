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

void func_80C1B8A4(EnFall2*, PlayState*);
void func_80C1B9D4(EnFall2*, PlayState*);

extern void* D_06008898;
extern void* D_06005EF4;
extern void* D_06008840;
extern void* D_06005F10;

const ActorInit En_Fall2_InitVars = {
    ACTOR_EN_FALL2,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_FALL2,
    sizeof(EnFall2),
    (ActorFunc)EnFall2_Init,
    (ActorFunc)EnFall2_Destroy,
    (ActorFunc)EnFall2_Update,
    (ActorFunc)EnFall2_Draw,
};

void EnFall2_Init(Actor* thisx, PlayState* play) {
    EnFall2* this = THIS;

    Actor_SetScale(&this->actor, 1.0f);
    this->actionFunc = func_80C1B8A4;
    func_80183430(&this->skeletonInfo, &D_06008898, &D_06005EF4, &this->unk174, &this->unk228, NULL);
    func_801835EC(&this->skeletonInfo, &D_06005EF4);
    this->unk2DC = Lib_SegmentedToVirtual(&D_06008840);
    Actor_SetScale(&this->actor, 0.02f);
    this->actionFunc = func_80C1B9D4;
    this->unk2E6 = 0x231;
    this->unk2E0 = 0.0f;
}

void EnFall2_Destroy(Actor* thisx, PlayState* play) {
    EnFall2* this = THIS;

    func_8018349C(&this->skeletonInfo);
}

void func_80C1B724(f32 arg0) {
    static u8 sAlphaTableIndex[] = { 0, 2, 0, 0, 4, 0, 4, 4, 2, 0, 0, 0, 0, 0, 0, 2, 4, 4, 4, 2, 0, 4, 2, 2, 0, 4, 4,
                                     4, 4, 0, 2, 2, 4, 0, 2, 0, 4, 4, 2, 0, 2, 4, 4, 4, 2, 0, 4, 4, 4, 2, 2, 0, 4, 4,
                                     2, 4, 0, 2, 0, 0, 2, 4, 4, 2, 0, 2, 4, 4, 4, 2, 0, 4, 4, 4, 4, 4, 2, 2, 0, 2, 4,
                                     0, 2, 0, 0, 2, 4, 4, 2, 0, 2, 4, 4, 4, 2, 0, 0, 2, 2, 4, 4, 4, 4, 4, 4, 2, 0, 2,
                                     0, 0, 2, 4, 4, 2, 0, 2, 4, 4, 4, 2, 0, 2, 0, 5, 2, 5, 5, 5, 5, 0, 2, 5, 0, 2, 0,
                                     2, 5, 5, 2, 0, 2, 5, 5, 5, 2, 0, 3, 3, 3, 2, 2, 0, 0, 3, 3, 0, 2, 2, 3, 0, 2, 3,
                                     3, 2, 0, 2, 3, 3, 3, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 0, 2, 0, 2, 2, 2, 2,
                                     0, 2, 2, 2, 2, 2, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1,
                                     1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Vtx* vertices = Lib_SegmentedToVirtual(&D_06005F10);
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

    for (i = 0; i < ARRAY_COUNT(sAlphaTableIndex); i++, vertices++) {
        vertices->v.cn[3] = perVertexAlphaTable[sAlphaTableIndex[i]];
    }
}

void func_80C1B8A4(EnFall2* this, PlayState* play) {
}

void func_80C1B8B4(Actor* thisx) {
    EnFall2* this = THIS;
    thisx->draw = EnFall2_Draw;
    if (this->unk2E4 == 1) {
        Actor_SetScale(thisx, 0.02f);
    }
}

void func_80C1B8F0(Actor* thisx) {
    EnFall2* this = THIS;

    switch (this->unk2E4) {
        case 1:
            if (this->unk2E0 < 1.0f) {
                this->unk2E0 += 0.033333335f;
            } else {
                this->unk2E0 = 1.0f;
            }
            break;
        case 2:
            if (this->unk2E0 > 0.0f) {
                this->unk2E0 -= 0.1f;
                if (this->unk2E0 < 0.0f) {
                    this->unk2E0 = 0.0f;
                }
            }
            if (thisx->scale.x > 0.0f) {
                thisx->scale.x -= 0.0019999999f;
                if (thisx->scale.x < 0.0f) {
                    thisx->scale.x = 0.0f;
                }
                thisx->scale.z = thisx->scale.x;
            }
    }
}

void func_80C1B9D4(EnFall2* this, PlayState* play) {
    func_80183DE0(&this->skeletonInfo);
    if (Cutscene_CheckActorAction(play, this->unk2E6)) {
        Cutscene_ActorTranslateAndYaw(&this->actor, play, Cutscene_GetActorActionIndex(play, this->unk2E6));
        if (this->unk2E4 != play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, this->unk2E6)]->action) {
            this->unk2E4 = play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, this->unk2E6)]->action;
            func_80C1B8B4(&this->actor);
        }
        func_80C1B8F0(&this->actor);
        if (this->unk2E0 > 0.0f) {
            func_800B9010(&this->actor, NA_SE_EV_MOON_LIGHT_PILLAR - SFX_FLAG);
        }
    } else {
        this->actor.draw = NULL;
    }
    func_80C1B724(this->unk2E0);
}

void EnFall2_Update(Actor* thisx, PlayState* play) {
    EnFall2* this = THIS;
    this->actionFunc(this, play);
}

void EnFall2_Draw(Actor* thisx, PlayState* play) {
    EnFall2* this = THIS;
    u8 pad;
    Mtx* mtx;

    if (!(this->unk2E0 <= 0.0f)) {
        func_8012C2DC(play->state.gfxCtx);
        AnimatedMat_DrawXlu(play, Lib_SegmentedToVirtual(&D_06008840));

        mtx = GRAPH_ALLOC(play->state.gfxCtx, ALIGN16(this->skeletonInfo.unk_18->unk_1 * sizeof(Mtx)));

        if (mtx != NULL) {
            func_8012C2DC(play->state.gfxCtx);
            Matrix_RotateYS((s16)(Camera_GetCamDirYaw(play->cameraPtrs[play->activeCamera]) + 0x8000), MTXMODE_APPLY);
            func_8018450C(play, &this->skeletonInfo, mtx, NULL, NULL, &this->actor);
        }
    }
}
