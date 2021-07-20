#include "z_obj_spinyroll.h"

#define FLAGS 0x00000010

#define THIS ((ObjSpinyroll*)thisx)

void ObjSpinyroll_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjSpinyroll_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjSpinyroll_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjSpinyroll_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit Obj_Spinyroll_InitVars = {
    ACTOR_OBJ_SPINYROLL,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_SPINYROLL,
    sizeof(ObjSpinyroll),
    (ActorFunc)ObjSpinyroll_Init,
    (ActorFunc)ObjSpinyroll_Destroy,
    (ActorFunc)ObjSpinyroll_Update,
    (ActorFunc)ObjSpinyroll_Draw,
};


// static ColliderTrisElementInit sTrisElementsInit[6] = {
static ColliderTrisElementInit D_80A1F040[6] = {
    {
        { ELEMTYPE_UNK0, { 0x20000000, 0x00, 0x04 }, { 0x01C37BB6, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -60.0f, 0.0f, 17.0f }, { 60.0f, 0.0f, 17.0f }, { 60.0f, 40.0f, 17.0f } } },
    },
    {
        { ELEMTYPE_UNK0, { 0x20000000, 0x00, 0x04 }, { 0x01C37BB6, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -60.0f, 0.0f, 17.0f }, { 60.0f, 40.0f, 17.0f }, { -60.0f, 40.0f, 17.0f } } },
    },
    {
        { ELEMTYPE_UNK0, { 0x20000000, 0x00, 0x04 }, { 0x01C37BB6, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 60.0f, 0.0f, -17.0f }, { -60.0f, 0.0f, -17.0f }, { -60.0f, 40.0f, -17.0f } } },
    },
    {
        { ELEMTYPE_UNK0, { 0x20000000, 0x00, 0x04 }, { 0x01C37BB6, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 60.0f, 0.0f, -17.0f }, { -60.0f, 40.0f, -17.0f }, { 60.0f, 40.0f, -17.0f } } },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x04 }, { 0x01C37BB6, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 60.0f, 20.0f, -12.0f }, { -60.0f, 20.0f, -12.0f }, { -60.0f, 20.0f, 12.0f } } },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x04 }, { 0x01C37BB6, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 60.0f, 20.0f, -12.0f }, { -60.0f, 20.0f, 12.0f }, { 60.0f, 20.0f, 12.0f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_80A1F1A8 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_TRIS, },
    6, D_80A1F040, // sTrisElementsInit,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A1F204[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 500, ICHAIN_STOP),
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DA50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DAAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DB2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DC5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DCCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DD18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DE10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DE58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DE84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DEB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DFA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E074.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E2D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E334.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E394.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E3D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E648.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E694.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E6D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/ObjSpinyroll_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/ObjSpinyroll_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E9C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E9E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EA10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EA4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EAAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EAE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EB40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EB54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EC24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EC38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1ECC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1ECD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/ObjSpinyroll_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/ObjSpinyroll_Draw.asm")
