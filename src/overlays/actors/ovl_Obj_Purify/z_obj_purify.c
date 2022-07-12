/*
 * File: z_obj_purify.c
 * Overlay: ovl_Obj_Purify
 * Description: Poisoned/Purified Water Elements
 */

#include "z_obj_purify.h"
#include "objects/object_numa_obj/object_numa_obj.h"
#include "objects/object_dekucity_obj/object_dekucity_obj.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjPurify*)thisx)

void ObjPurify_Init(Actor* thisx, PlayState* play);
void ObjPurify_Destroy(Actor* thisx, PlayState* play);
void ObjPurify_Update(Actor* thisx, PlayState* play);

void func_80A84EC0(ObjPurify* this, PlayState* play);
void func_80A851C8(Actor* thisx, PlayState* play);
void func_80A85074(ObjPurify* this, PlayState* play);
void func_80A850B0(ObjPurify* this);
void func_80A850E8(ObjPurify* this, PlayState* play);
void func_80A85304(Actor* thisx, PlayState* play);
void func_80A84FB4(ObjPurify* this, PlayState* play);
void func_80A85010(ObjPurify* this, PlayState* play);
void ObjPurify_DoNothing(ObjPurify* this, PlayState* play);
void func_80A85048(ObjPurify* this);
void func_80A84FA0(ObjPurify* this);
void func_80A8515C(ObjPurify* this);
void func_80A84FEC(ObjPurify* this);
void func_80A84EAC(ObjPurify* this);

const ActorInit Obj_Purify_InitVars = {
    ACTOR_OBJ_PURIFY,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjPurify),
    (ActorFunc)ObjPurify_Init,
    (ActorFunc)ObjPurify_Destroy,
    (ActorFunc)ObjPurify_Update,
    (ActorFunc)NULL,
};

ObjPurifyInfo ObjPurifyInfoList[] = {
    {
        0x164,
        0.1f,
        { NULL, NULL },
        { object_numa_obj_DL_0128E0, object_numa_obj_DL_012D90 },
        { object_numa_obj_Matanimheader_012CF8, object_numa_obj_Matanimheader_0131A8 },
        &object_numa_obj_Colheader_012818,
        0,
    },
    {
        0x19A,
        1.0f,
        { NULL, NULL },
        { object_dekucity_obj_DL_0004E0, object_dekucity_obj_DL_001030 },
        { object_dekucity_obj_Matanimheader_000E28, object_dekucity_obj_Matanimheader_001978 },
        &object_dekucity_obj_Colheader_0002AC,
        1,
    },
    {
        0x19A,
        1.0f,
        { object_dekucity_obj_DL_001ED8, object_dekucity_obj_DL_003998 },
        { object_dekucity_obj_DL_001D80, NULL },
        { object_dekucity_obj_Matanimheader_003820, NULL },
        NULL,
        1,
    },
    {
        0x164,
        0.1f,
        { NULL, NULL },
        { object_numa_obj_DL_012A60, object_numa_obj_DL_012F10 },
        { object_numa_obj_Matanimheader_012B58, object_numa_obj_Matanimheader_013008 },
        &object_numa_obj_Colheader_012818,
        0,
    },
    {
        0x164,
        0.1f,
        { NULL, NULL },
        { object_numa_obj_DL_012BF0, object_numa_obj_DL_0130A0 },
        { object_numa_obj_Matanimheader_012CE8, object_numa_obj_Matanimheader_013198 },
        &object_numa_obj_Colheader_012818,
        0,
    },
};

void ObjPurify_SetSysMatrix(f32 ypos) {
    Matrix_GetCurrent()->yw = ypos;
}

s32 ObjPurify_IsPurified(ObjPurify* this) {
    ObjPurifyInfo* info;
    info = &ObjPurifyInfoList[this->dyna.actor.params & 0xF];
    if (!info->isDekuCity) {
        // woodfall temple wood flower unraveled
        if ((gSaveContext.save.weekEventReg[12] & 1)) {
            return true;
        }
    }
    // woodfall temple purification cutscene watched
    else if (gSaveContext.save.weekEventReg[20] & 2) {
        return true;
    }
    return false;
}

void ObjPurify_Init(Actor* thisx, PlayState* play) {
    ObjPurify* this = THIS;
    s32 pad;
    ObjPurifyInfo* info;
    s32 sp20;

    info = &ObjPurifyInfoList[this->dyna.actor.params & 0xF];
    sp20 = (this->dyna.actor.params >> 0xC) & 1;
    Actor_SetScale(&this->dyna.actor, info->scale);
    if (sp20 == 1) {
        DynaPolyActor_Init((DynaPolyActor*)this, 0);
    }
    this->objIndex = Object_GetIndex(&play->objectCtx, info->objectId);
    if (this->objIndex < 0) {
        Actor_MarkForDeath(&this->dyna.actor);
    } else if (sp20 == 0) {
        func_80A84EAC(this);
    } else if (ObjPurify_IsPurified(this)) {
        Actor_MarkForDeath(&this->dyna.actor);
    } else {
        func_80A84EAC(this);
    }
}

void ObjPurify_Destroy(Actor* thisx, PlayState* play) {
    ObjPurify* this = THIS;
    if (((this->dyna.actor.params >> 0xC) & 1) == 1) {
        DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
    }
}

void func_80A84EAC(ObjPurify* this) {
    this->actionFunc = func_80A84EC0;
}

void func_80A84EC0(ObjPurify* this, PlayState* play) {
    s16 pad;
    s32 sp28;
    s32 sp24;

    if (Object_IsLoaded(&play->objectCtx, this->objIndex) != 0) {
        sp28 = (this->dyna.actor.params >> 0xC) & 1;
        sp24 = this->dyna.actor.params & 0xF;
        this->dyna.actor.objBankIndex = this->objIndex;
        Actor_SetObjectDependency(play, &this->dyna.actor);
        if (sp28 == 1) {
            DynaPolyActor_LoadMesh(play, &this->dyna, ObjPurifyInfoList[sp24].colHeader);
            func_80A84FA0(this);
        } else if (ObjPurify_IsPurified(this)) {
            func_80A8515C(this);
        } else {
            func_80A84FEC(this);
        }
    }
}

void func_80A84FA0(ObjPurify* this) {
    this->actionFunc = func_80A84FB4;
}

void func_80A84FB4(ObjPurify* this, PlayState* play) {
    if (ObjPurify_IsPurified(this)) {
        Actor_MarkForDeath(&this->dyna.actor);
    }
}

void func_80A84FEC(ObjPurify* this) {
    this->dyna.actor.draw = func_80A851C8;
    this->gfxIndex = 0;
    this->actionFunc = func_80A85010;
}

void func_80A85010(ObjPurify* this, PlayState* play) {
    if (ObjPurify_IsPurified(this)) {
        func_80A85048(this);
    }
}

void func_80A85048(ObjPurify* this) {
    this->dyna.actor.draw = func_80A851C8;
    this->gfxIndex = 0;
    this->actionFunc = func_80A85074;
    this->timer = 30;
}

void func_80A85074(ObjPurify* this, PlayState* play) {
    this->timer--;
    if (this->timer <= 0) {
        func_80A850B0(this);
    }
}

void func_80A850B0(ObjPurify* this) {
    f32 ypos = this->dyna.actor.home.pos.y;
    this->dyna.actor.draw = func_80A85304;
    this->unk168[1] = ypos - 90.0f;
    this->actionFunc = func_80A850E8;
    this->unk168[0] = ypos;
}

void func_80A850E8(ObjPurify* this, PlayState* play) {
    Math_StepToF(&this->unk168[0], this->dyna.actor.home.pos.y - 90.0f, 0.9f);
    if (Math_StepToF(&this->unk168[1], this->dyna.actor.home.pos.y, 0.9f)) {
        func_80A8515C(this);
    }
}

void func_80A8515C(ObjPurify* this) {
    this->dyna.actor.flags &= ~0x10;
    this->dyna.actor.draw = func_80A851C8;
    this->gfxIndex = 1;
    this->actionFunc = ObjPurify_DoNothing;
}

void ObjPurify_DoNothing(ObjPurify* this, PlayState* play) {
}

void ObjPurify_Update(Actor* thisx, PlayState* play) {
    ObjPurify* this = THIS;
    this->actionFunc(this, play);
}

void func_80A851C8(Actor* thisx, PlayState* play) {
    s32 pad;
    ObjPurify* this = THIS;
    ObjPurifyInfo* info;
    Gfx* opaDList;
    Gfx* xluDList;
    AnimatedMaterial* animMat;

    info = &ObjPurifyInfoList[this->dyna.actor.params & 0xF];
    opaDList = info->opaDLists[this->gfxIndex];
    xluDList = info->xluDLists[this->gfxIndex];
    animMat = info->animMat[this->gfxIndex];

    OPEN_DISPS(play->state.gfxCtx);

    if (animMat != NULL) {
        AnimatedMat_Draw(play, Lib_SegmentedToVirtual(animMat));
    }
    if (opaDList != 0) {
        func_8012C28C(play->state.gfxCtx);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, opaDList);
    }
    if (xluDList != 0) {
        func_8012C2DC(play->state.gfxCtx);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, xluDList);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_80A85304(Actor* thisx, PlayState* play) {
    s32 pad;
    ObjPurify* this = THIS;
    ObjPurifyInfo* info = &ObjPurifyInfoList[this->dyna.actor.params & 0xF];
    s32 sp6C[2];
    s32 i;
    s32 index;

    if (this->unk168[1] < this->unk168[0]) {
        sp6C[0] = 1;
        sp6C[1] = 0;
    } else {
        sp6C[0] = 0;
        sp6C[1] = 1;
    }

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    for (i = 0; i < 2; i++) {
        index = sp6C[i];
        AnimatedMat_Draw(play, Lib_SegmentedToVirtual(info->animMat[index]));
        ObjPurify_SetSysMatrix(this->unk168[index]);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, info->xluDLists[index]);
    };
    CLOSE_DISPS(play->state.gfxCtx);
}
