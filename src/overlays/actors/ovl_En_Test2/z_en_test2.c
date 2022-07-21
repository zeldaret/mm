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

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_80)

#define THIS ((EnTest2*)thisx)

void EnTest2_Init(Actor* thisx, PlayState* play);
void EnTest2_Update(Actor* thisx, PlayState* play);
void EnTest2_SetActorFlags(Actor* thisx, PlayState* play);
void EnTest2_Draw(Actor* thisx, PlayState* play);

typedef struct EnTest2DisplayObjs {
    Gfx* DList1;
    Gfx* DList2;
    AnimatedMaterial* animMat;
} EnTest2DisplayObjs;

const ActorInit En_Test2_InitVars = {
    ACTOR_EN_TEST2,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTest2),
    (ActorFunc)EnTest2_Init,
    (ActorFunc)Actor_Noop,
    (ActorFunc)EnTest2_Update,
    (ActorFunc)NULL,
};

EnTest2DisplayObjs sDisplayObjects[] = {
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

static InitChainEntry D_80A3E74C[] = {
    ICHAIN_VEC3F(scale, 1, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 8000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 2500, ICHAIN_STOP),
};

static s16 sTest2Objects[] = {
    OBJECT_DEKUCITY_ANA_OBJ, OBJECT_SICHITAI_OBJ,  OBJECT_YUKIMURA_OBJ, OBJECT_HAKUGIN_OBJ, OBJECT_HAKUGIN_OBJ,
    OBJECT_HAKUGIN_OBJ,      OBJECT_MEGANEANA_OBJ, OBJECT_HAKA_OBJ,     OBJECT_HAKA_OBJ,    OBJECT_HAKUGIN_OBJ,
    OBJECT_HAKUGIN_OBJ,      OBJECT_HAKUGIN_OBJ,   OBJECT_HAKUGIN_OBJ,
};

void EnTest2_Init(Actor* thisx, PlayState* play) {
    EnTest2* this = THIS;

    Actor_ProcessInitChain(&this->actor, D_80A3E74C);
    if ((this->actor.params == 0xB) || (this->actor.params == 0xC)) {
        this->actor.flags |= 0x20;
    }
}

void EnTest2_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    s32 objectIndex;
    EnTest2DisplayObjs* dispObjects;
    EnTest2* this = THIS;
    objectIndex = Object_GetIndex(&play->objectCtx, sTest2Objects[this->actor.params]);

    if (objectIndex < 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    if (Object_IsLoaded(&play->objectCtx, objectIndex)) {
        dispObjects = &sDisplayObjects[this->actor.params];
        this->actor.objBankIndex = objectIndex;
        this->actor.draw = EnTest2_Draw;
        if ((dispObjects->animMat) != 0) {
            Actor_SetObjectDependency(play, &this->actor);
            this->animMat = Lib_SegmentedToVirtual(dispObjects->animMat);
        }
        if (play->roomCtx.currRoom.unk5 != 0) {
            this->actor.update = EnTest2_SetActorFlags;
        } else {
            this->actor.update = Actor_Noop;
        }
    }
}

void EnTest2_SetActorFlags(Actor* thisx, PlayState* play) {
    if (play->actorCtx.unk4 == 0x64) {
        thisx->flags |= 0x80;
    } else {
        thisx->flags &= -0x81;
    }
}

void EnTest2_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    EnTest2* this = THIS;
    Gfx* dispObjects = sDisplayObjects[this->actor.params].DList2;

    if (this->animMat != NULL) {
        AnimatedMat_Draw(play, this->animMat);
    }
    if ((this->actor.flags & 0x80) == 0x80) {
        OPEN_DISPS(play->state.gfxCtx);

        func_8012C2DC(play->state.gfxCtx);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        if (dispObjects != 0) {
            gSPDisplayList(POLY_XLU_DISP++, dispObjects);
        }
        gSPDisplayList(POLY_XLU_DISP++, sDisplayObjects[this->actor.params].DList1);

        CLOSE_DISPS(play->state.gfxCtx);
        return;
    }
    if (dispObjects != 0) {
        Gfx_DrawDListXlu(play, dispObjects);
    }
    Gfx_DrawDListOpa(play, sDisplayObjects[this->actor.params].DList1);
}