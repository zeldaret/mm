/*
 * File: z_en_test2.c
 * Overlay: ovl_En_Test2
 * Description: Objects affected by the Lens of Truth
 */

#include "z_en_test2.h"
#include "objects/object_dekucity_ana_obj/object_dekucity_ana_obj.h"
#include "objects/object_sichitai_obj/object_sichitai_obj.h"
#include "objects/object_yukimura_obj/object_yukimura_obj.h"
#include "objects/object_hakugin_obj/object_hakugin_obj.h"
#include "objects/object_meganeana_obj/object_meganeana_obj.h"
#include "objects/object_haka_obj/object_haka_obj.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_REACT_TO_LENS)

#define THIS ((EnTest2*)thisx)

void EnTest2_Init(Actor* thisx, PlayState* play);
void EnTest2_Update(Actor* thisx, PlayState* play);
void EnTest2_UpdateForLens(Actor* thisx, PlayState* play);
void EnTest2_Draw(Actor* thisx, PlayState* play);

typedef struct EnTest2ModelInfo {
    /* 0x0 */ Gfx* dList1;
    /* 0x4 */ Gfx* dList2;
    /* 0x8 */ AnimatedMaterial* animMat;
} EnTest2ModelInfo; // size = 0xC

ActorInit En_Test2_InitVars = {
    /**/ ACTOR_EN_TEST2,
    /**/ ACTORCAT_BG,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(EnTest2),
    /**/ EnTest2_Init,
    /**/ Actor_Noop,
    /**/ EnTest2_Update,
    /**/ NULL,
};

static EnTest2ModelInfo sModelInfo[] = {
    { object_dekucity_ana_obj_DL_000040, NULL, NULL },
    { object_sichitai_obj_DL_001820, NULL, NULL },
    { object_yukimura_obj_DL_0008C0, NULL, NULL },
    { object_hakugin_obj_DL_0016D8, NULL, object_hakugin_obj_Matanimheader_0017A8 },
    { object_hakugin_obj_DL_002018, NULL, object_hakugin_obj_Matanimheader_0020E8 },
    { object_hakugin_obj_DL_005268, NULL, object_hakugin_obj_Matanimheader_005338 },
    { object_meganeana_obj_DL_000110, object_meganeana_obj_DL_000080, NULL },
    { object_haka_obj_DL_000F70, NULL, NULL },
    { object_haka_obj_DL_001200, NULL, NULL },
    { object_hakugin_obj_DL_004928, NULL, object_hakugin_obj_Matanimheader_0049F8 },
    { object_hakugin_obj_DL_002978, NULL, object_hakugin_obj_Matanimheader_002A58 },
    { object_hakugin_obj_DL_000D38, NULL, object_hakugin_obj_Matanimheader_000E48 },
    { object_hakugin_obj_DL_0035A8, NULL, object_hakugin_obj_Matanimheader_003888 },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F(scale, 1, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 8000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 2500, ICHAIN_STOP),
};

static s16 sObjectIds[] = {
    OBJECT_DEKUCITY_ANA_OBJ, OBJECT_SICHITAI_OBJ,  OBJECT_YUKIMURA_OBJ, OBJECT_HAKUGIN_OBJ, OBJECT_HAKUGIN_OBJ,
    OBJECT_HAKUGIN_OBJ,      OBJECT_MEGANEANA_OBJ, OBJECT_HAKA_OBJ,     OBJECT_HAKA_OBJ,    OBJECT_HAKUGIN_OBJ,
    OBJECT_HAKUGIN_OBJ,      OBJECT_HAKUGIN_OBJ,   OBJECT_HAKUGIN_OBJ,
};

void EnTest2_Init(Actor* thisx, PlayState* play) {
    EnTest2* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    if ((this->actor.params == EN_TEST2_PARAM_B) || (this->actor.params == EN_TEST2_PARAM_C)) {
        this->actor.flags |= ACTOR_FLAG_20;
    }
}

void EnTest2_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    s32 objectIndex;
    EnTest2ModelInfo* modelInfo;
    EnTest2* this = THIS;

    objectIndex = Object_GetIndex(&play->objectCtx, sObjectIds[this->actor.params]);
    if (objectIndex < 0) {
        Actor_Kill(&this->actor);
        return;
    }
    if (Object_IsLoaded(&play->objectCtx, objectIndex)) {
        modelInfo = &sModelInfo[this->actor.params];
        this->actor.objBankIndex = objectIndex;
        this->actor.draw = EnTest2_Draw;
        if (modelInfo->animMat != NULL) {
            Actor_SetObjectDependency(play, &this->actor);
            this->animMat = Lib_SegmentedToVirtual(modelInfo->animMat);
        }
        if (play->roomCtx.curRoom.lensMode != LENS_MODE_HIDE_ACTORS) {
            this->actor.update = EnTest2_UpdateForLens;
        } else {
            this->actor.update = Actor_Noop;
        }
    }
}

void EnTest2_UpdateForLens(Actor* thisx, PlayState* play) {
    EnTest2* this = THIS;

    if (play->actorCtx.lensMaskSize == LENS_MASK_ACTIVE_SIZE) {
        this->actor.flags |= ACTOR_FLAG_REACT_TO_LENS;
    } else {
        this->actor.flags &= ~ACTOR_FLAG_REACT_TO_LENS;
    }
}

void EnTest2_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    EnTest2* this = THIS;
    Gfx* dList = sModelInfo[this->actor.params].dList2;

    if (this->animMat != NULL) {
        AnimatedMat_Draw(play, this->animMat);
    }
    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_REACT_TO_LENS)) {
        OPEN_DISPS(play->state.gfxCtx);

        Gfx_SetupDL25_Xlu(play->state.gfxCtx);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        if (dList != NULL) {
            gSPDisplayList(POLY_XLU_DISP++, dList);
        }
        gSPDisplayList(POLY_XLU_DISP++, sModelInfo[this->actor.params].dList1);

        CLOSE_DISPS(play->state.gfxCtx);
    } else {
        if (dList != NULL) {
            Gfx_DrawDListXlu(play, dList);
        }
        Gfx_DrawDListOpa(play, sModelInfo[this->actor.params].dList1);
    }
}
