#include "z_obj_milk_bin.h"

#define FLAGS 0x00000000

#define THIS ((ObjMilkBin*)thisx)

void ObjMilkBin_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMilkBin_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMilkBin_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjMilkBin_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

// D_80C09050
extern ColliderCylinderInit sCylinderInit;

/*
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
*/

void ObjMilkBin_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjMilkBin* this = THIS;

    Collider_InitAndSetCylinder(globalCtx, &this->unk_148, &this->actor, &sCylinderInit);
    Collider_UpdateCylinder(&this->actor, &this->unk_148);

    this->actor.shape.yOffset = 1100.0f;
    this->unk_194 = 0;
    this->unk_198 = thisx->params;

    if ((this->unk_198 == 2) && !(gSaveContext.perm.weekEventReg[0x34] & 1)) {
        this->unk_194 += 1;
    }
}

void ObjMilkBin_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjMilkBin* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->unk_148);
}

void ObjMilkBin_Update(Actor* thisx, GlobalContext* globalCtx2) {
    ObjMilkBin* this = THIS;
    GlobalContext* globalCtx = globalCtx2;

    if (this->unk_198 == 1) {
        if (gSaveContext.perm.weekEventReg[0x16] & 1) {
            if (((gSaveContext.perm.day == 2) && (gSaveContext.perm.isNight == 1)) || (gSaveContext.perm.day >= 3)) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
        }
    } else if (this->unk_198 == 2) {
        if (gSaveContext.perm.weekEventReg[0x34] & 1) {
            this->unk_194 &= ~1;
        } else {
            this->unk_194 |= 1;
        }
    }

    if (!(this->unk_194 & 1)) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->unk_148.base);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->unk_148.base);
    }
}

// gMilkBinMilkJarDL
extern Gfx D_060004B0[];

void ObjMilkBin_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjMilkBin* this = THIS;

    if (!(this->unk_194 & 1)) {
        func_800BDFC0(globalCtx, D_060004B0);
    }
}
