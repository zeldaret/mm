#include "z_obj_comb.h"

#define FLAGS 0x00000000

#define THIS ((ObjComb*)thisx)

void ObjComb_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjComb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjComb_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjComb_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit Obj_Comb_InitVars = {
    ACTOR_OBJ_COMB,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_COMB,
    sizeof(ObjComb),
    (ActorFunc)ObjComb_Init,
    (ActorFunc)ObjComb_Destroy,
    (ActorFunc)ObjComb_Update,
    (ActorFunc)ObjComb_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_8098E440[1] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x05CBFFBE, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 15 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_8098E464 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_2, COLSHAPE_JNTSPH, },
    1, D_8098E440, // sJntSphElementsInit,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8098E474[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_STOP),
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Comb_0x8098CE40/func_8098CE40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Comb_0x8098CE40/func_8098CEAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Comb_0x8098CE40/func_8098D19C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Comb_0x8098CE40/func_8098D47C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Comb_0x8098CE40/func_8098D6E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Comb_0x8098CE40/func_8098D870.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Comb_0x8098CE40/func_8098D8C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Comb_0x8098CE40/func_8098D99C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Comb_0x8098CE40/func_8098DA74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Comb_0x8098CE40/ObjComb_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Comb_0x8098CE40/ObjComb_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Comb_0x8098CE40/func_8098DC44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Comb_0x8098CE40/func_8098DC60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Comb_0x8098CE40/func_8098DE58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Comb_0x8098CE40/func_8098DEA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Comb_0x8098CE40/func_8098E098.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Comb_0x8098CE40/func_8098E0B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Comb_0x8098CE40/ObjComb_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Comb_0x8098CE40/ObjComb_Draw.asm")
