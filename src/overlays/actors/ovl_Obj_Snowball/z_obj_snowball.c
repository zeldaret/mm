#include "z_obj_snowball.h"

#define FLAGS 0x00000000

#define THIS ((ObjSnowball*)thisx)

void ObjSnowball_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjSnowball_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjSnowball_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjSnowball_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit Obj_Snowball_InitVars = {
    ACTOR_OBJ_SNOWBALL,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_GOROIWA,
    sizeof(ObjSnowball),
    (ActorFunc)ObjSnowball_Init,
    (ActorFunc)ObjSnowball_Destroy,
    (ActorFunc)ObjSnowball_Update,
    (ActorFunc)ObjSnowball_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80B04F50[1] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x81837FBE, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 73 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80B04F74 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_JNTSPH, },
    1, D_80B04F50, // sJntSphElementsInit,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B04FD4[] = {
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_STOP),
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B02CD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B02D58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B02DB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B02E54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B02EE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B030F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B03688.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B03A80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B03E2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B03FF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/ObjSnowball_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/ObjSnowball_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B04338.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B04350.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B04540.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B0457C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B04608.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B04648.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B046E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B047C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B04B48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B04B60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/ObjSnowball_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/ObjSnowball_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball_0x80B02CD0/func_80B04D34.asm")
