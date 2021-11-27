/*
 * File: z_obj_milk_bin.c
 * Overlay: ovl_Obj_Milk_Bin
 * Description: Milk jar
 */

#include "z_obj_milk_bin.h"

#define FLAGS 0x00000000

#define THIS ((ObjMilkBin*)thisx)

void ObjMilkBin_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMilkBin_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMilkBin_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjMilkBin_Draw(Actor* thisx, GlobalContext* globalCtx);

// gMilkBinMilkJarDL
extern Gfx D_060004B0[];

const ActorInit Obj_Milk_Bin_InitVars = {
    ACTOR_OBJ_MILK_BIN,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_OBJECT_UNSET_MILK_BIN,
    sizeof(ObjMilkBin),
    (ActorFunc)ObjMilkBin_Init,
    (ActorFunc)ObjMilkBin_Destroy,
    (ActorFunc)ObjMilkBin_Update,
    (ActorFunc)ObjMilkBin_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HARD,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 12, 30, 0, { 0, 0, 0 } },
};

void ObjMilkBin_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjMilkBin* this = THIS;

    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    Collider_UpdateCylinder(&this->actor, &this->collider);

    this->actor.shape.yOffset = 1100.0f;
    this->disableDraw = 0;
    this->type = thisx->params;

    if ((this->type == OBJ_MILK_BIN_TYPE_2) && !(gSaveContext.weekEventReg[0x34] & 1)) {
        this->disableDraw |= 1;
    }
}

void ObjMilkBin_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjMilkBin* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void ObjMilkBin_Update(Actor* thisx, GlobalContext* globalCtx2) {
    ObjMilkBin* this = THIS;
    GlobalContext* globalCtx = globalCtx2;

    if (this->type == OBJ_MILK_BIN_TYPE_1) {
        if (gSaveContext.weekEventReg[0x16] & 1) {
            if (((gSaveContext.day == 2) && (gSaveContext.isNight == 1)) || (gSaveContext.day >= 3)) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
        }
    } else if (this->type == OBJ_MILK_BIN_TYPE_2) {
        if (gSaveContext.weekEventReg[0x34] & 1) {
            this->disableDraw &= ~1;
        } else {
            this->disableDraw |= 1;
        }
    }

    if (!(this->disableDraw & 1)) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void ObjMilkBin_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjMilkBin* this = THIS;

    if (!(this->disableDraw & 1)) {
        func_800BDFC0(globalCtx, D_060004B0);
    }
}
