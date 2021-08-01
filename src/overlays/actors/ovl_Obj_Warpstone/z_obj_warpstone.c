#include "z_obj_warpstone.h"

#define FLAGS 0x00000009

#define THIS ((ObjWarpstone*)thisx)

void ObjWarpstone_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjWarpstone_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjWarpstone_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjWarpstone_Draw(Actor* thisx, GlobalContext* globalCtx);
void func_80B92B10(Actor* thisx, GlobalContext* globalCtx);
void func_80B92C00(Actor* thisx, s32 arg1);
void func_80B92DC4(Actor* thisx, s32 arg1);

#if 0
const ActorInit Obj_Warpstone_InitVars = {
    ACTOR_OBJ_WARPSTONE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_SEK,
    sizeof(ObjWarpstone),
    (ActorFunc)ObjWarpstone_Init,
    (ActorFunc)ObjWarpstone_Destroy,
    (ActorFunc)ObjWarpstone_Update,
    (ActorFunc)ObjWarpstone_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B93220 = {
    { COLTYPE_METAL, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0x00100000, 0x00, 0x00 }, { 0x01000202, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 20, 60, 0, { 0, 0, 0 } },
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B9324C[] = {
    ICHAIN_U8(targetMode, 1, ICHAIN_STOP),
};


#endif
extern ColliderCylinderInit D_80B93220;
extern InitChainEntry D_80B9324C[];

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Warpstone_0x80B92B10/func_80B92B10.asm")

/*#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Warpstone_0x80B92B10/ObjWarpstone_Init.asm")*/

void ObjWarpstone_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjWarpstone* this = THIS;

    Actor_ProcessInitChain(&this->actor, D_80B9324C);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_80B93220);
    Actor_SetHeight(&this->actor, 40.0f);
    if (!IS_OWL_HIT(GET_OWL_ID(this))) {
        func_80B92B10(&this->actor, func_80B92C00);
    } else {
        func_80B92B10(&this->actor, func_80B92DC4);
        this->unk1AA = 1;
    }
}

/*#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Warpstone_0x80B92B10/ObjWarpstone_Destroy.asm")*/

void ObjWarpstone_Destroy(Actor* thisx, GlobalContext *globalCtx) {
    ObjWarpstone* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Warpstone_0x80B92B10/func_80B92C00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Warpstone_0x80B92B10/func_80B92C48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Warpstone_0x80B92B10/func_80B92CD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Warpstone_0x80B92B10/func_80B92DC4.asm")

/*#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Warpstone_0x80B92B10/ObjWarpstone_Update.asm")*/

void ObjWarpstone_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjWarpstone* this = THIS;
    s32 pad;

    if (this->unk1A8 != 0) {
        if (func_800B867C(&this->actor, globalCtx) != 0) {
            this->unk1A8 = 0;
        } else if ((func_80152498(&globalCtx->msgCtx) == 4) && (func_80147624(globalCtx))) {
            if (globalCtx->msgCtx.choiceIndex != 0) {
                func_8019F208();
                globalCtx->msgCtx.unk11F22 = 0x4D;
                globalCtx->msgCtx.unk120D6 = 0;
                globalCtx->msgCtx.unk120D4 = 0;
                gSaveContext.owlSaveLocation = GET_OWL_ID(this);
            } else {
                func_801477B4(globalCtx);
            }
        }
    } else if (func_800B84D0(&this->actor, globalCtx)) {
        this->unk1A8 = 1;
    } else if (!this->actionFunc(this, globalCtx)) {
        func_800B863C(&this->actor, globalCtx);
    }
    Collider_ResetCylinderAC(globalCtx, &this->collider.base);
    Collider_UpdateCylinder(&this->actor, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Warpstone_0x80B92B10/ObjWarpstone_Draw.asm")
