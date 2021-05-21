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

extern ColliderCylinderInit D_80C09050;

/*
void ObjMilkBin_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjMilkBin* this = THIS;
    //ColliderCylinder *sp18;
    ColliderCylinder *temp_a1;
    Actor *temp_a2;
    s16 temp_t6;

    //temp_a2 = this;
    //temp_a1 = temp_a2 + 0x148;
    //sp18 = temp_a1;
    //this = temp_a2;
    Collider_InitAndSetCylinder(globalCtx, temp_a1, this->unk_148, &D_80C09050);
    Collider_UpdateCylinder(&this->actor, temp_a1);
    //temp_t6 = this->actor.params;
    this->unk_194 = 0;
    this->actor.shape.yOffset = 1100.0f;
    this->unk_198 = this->actor.params;
    if ((temp_t6 == 2) && (((gSaveContext.perm.weekEventReg[0x34]) & 1) == 0)) {
        this->unk_194 = 1;
    }
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Milk_Bin_0x80C08E40/ObjMilkBin_Init.asm")

void ObjMilkBin_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    ObjMilkBin* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->unk_148);
}
/*
void ObjMilkBin_Update(Actor *thisx, GlobalContext *globalCtx) {
    ObjMilkBin* this = THIS;

    ColliderCylinder *temp_a2;
    CollisionCheckContext *temp_a1;
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = this->unk_198;
    if (temp_v0 == 1) {
        if ((gSaveContext.perm.weekEventReg[0x16] & 1) != 0) {
            temp_v0_2 = gSaveContext.perm.day;
            if (((temp_v0_2 == 2) && (gSaveContext.perm.isNight == 1)) || temp_v0_2 >= 3) {
                Actor_MarkForDeath((Actor *) this);
                return;
            }
        }
    } else if (temp_v0 == 2) {
        if ((gSaveContext.perm.weekEventReg[0x34] & 1) != 0) {
            this->unk_194 = this->unk_194 & ~1;
        } else {
            this->unk_194 = this->unk_194 | 1;
        }
    }
    if ((this->unk_194 & 1) == 0) {
        temp_a1 = &globalCtx->colCheckCtx;
        temp_a2 = &this->unk_148;
        CollisionCheck_SetAC(globalCtx, temp_a1, &temp_a2->base);
        CollisionCheck_SetOC(globalCtx, temp_a1, &temp_a2->base);
    }
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Milk_Bin_0x80C08E40/ObjMilkBin_Update.asm")

// gMilkBinMilkJarDL
extern Gfx D_060004B0[];

void ObjMilkBin_Draw(Actor *thisx, GlobalContext *globalCtx) {
    ObjMilkBin* this = THIS;

    if (!(this->unk_194 & 1)) {
        func_800BDFC0(globalCtx, &D_060004B0);
    }
}
