#include "z_obj_snowball2.h"

#define FLAGS 0x00800000

#define THIS ((ObjSnowball2*)thisx)

void ObjSnowball2_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjSnowball2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjSnowball2_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjSnowball2_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Snowball2_InitVars = {
    ACTOR_OBJ_SNOWBALL2,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_GOROIWA,
    sizeof(ObjSnowball2),
    (ActorFunc)ObjSnowball2_Init,
    (ActorFunc)ObjSnowball2_Destroy,
    (ActorFunc)ObjSnowball2_Update,
    (ActorFunc)ObjSnowball2_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80B3A8E0[1] = {
    {
        { ELEMTYPE_UNK0, { 0x00400000, 0x00, 0x02 }, { 0x0583FFBE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 15 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80B3A904 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_PLAYER, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_JNTSPH, },
    1, D_80B3A8E0, // sJntSphElementsInit,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B3A93C[] = {
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(minVelocityY, -20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 25, ICHAIN_STOP),
};


extern ColliderJntSphElementInit D_80B3A8E0[1];
extern ColliderJntSphInit D_80B3A904;
extern InitChainEntry D_80B3A93C[];
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B38E20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B38E88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B38EFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39108.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39470.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B395C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B395EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39638.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39834.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39908.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39B28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39B5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/ObjSnowball2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/ObjSnowball2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39C78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39C9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39F60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39FA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B3A0D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B3A13C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B3A498.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B3A500.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/ObjSnowball2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/ObjSnowball2_Draw.s")
