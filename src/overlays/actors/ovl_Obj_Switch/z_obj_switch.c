#include "z_obj_switch.h"

#define FLAGS 0x00000010

#define THIS ((ObjSwitch*)thisx)

void ObjSwitch_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjSwitch_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjSwitch_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjSwitch_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Switch_InitVars = {
    ACTOR_OBJ_SWITCH,
    ACTORCAT_SWITCH,
    FLAGS,
    GAMEPLAY_DANGEON_KEEP,
    sizeof(ObjSwitch),
    (ActorFunc)ObjSwitch_Init,
    (ActorFunc)ObjSwitch_Destroy,
    (ActorFunc)ObjSwitch_Update,
    (ActorFunc)ObjSwitch_Draw,
};


// static ColliderTrisElementInit sTrisElementsInit[2] = {
static ColliderTrisElementInit D_8093CCD4[2] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000400, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -20.0f, 19.0f, -20.0f }, { -20.0f, 19.0f, 20.0f }, { 20.0f, 19.0f, 20.0f } } },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000400, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 20.0f, 19.0f, 20.0f }, { 20.0f, 19.0f, -20.0f }, { -20.0f, 19.0f, -20.0f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_8093CD4C = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_TRIS, },
    2, D_8093CCD4, // sTrisElementsInit,
};


// static ColliderTrisElementInit sTrisElementsInit[2] = {
static ColliderTrisElementInit D_8093CD5C[2] = {
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00003820, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 23.0f, 8.5f }, { -23.0f, 0.0f, 8.5f }, { 0.0f, -23.0f, 8.5f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00003820, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 23.0f, 8.5f }, { 0.0f, -23.0f, 8.5f }, { 23.0f, 0.0f, 8.5f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_8093CDD4 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_TRIS, },
    2, D_8093CD5C, // sTrisElementsInit,
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_8093CDE4[1] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x01CBFFBE, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 300, 0 }, 20 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_8093CE08 = {
    { COLTYPE_METAL, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_JNTSPH, },
    1, D_8093CDE4, // sJntSphElementsInit,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8093CE18[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_STOP),
};


extern ColliderTrisElementInit D_8093CCD4[2];
extern ColliderTrisInit D_8093CD4C;
extern ColliderTrisElementInit D_8093CD5C[2];
extern ColliderTrisInit D_8093CDD4;
extern ColliderJntSphElementInit D_8093CDE4[1];
extern ColliderJntSphInit D_8093CE08;
extern InitChainEntry D_8093CE18[];
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093ABD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093AC6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093ADA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093AE1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093AE74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093AE88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093AEC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093AEF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093AF1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093AF54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/ObjSwitch_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/ObjSwitch_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093B648.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093B668.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093B6F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093B710.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093B92C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093B940.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093B9C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093B9E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BB5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BB70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BBD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BCC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BCDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BD34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BD4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BDAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BDC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BE10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BE2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BEF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BF04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BF50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BF70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C0A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C0B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C138.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C15C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C23C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C250.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C2B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C2D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C3C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C3DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C584.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C598.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/ObjSwitch_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C778.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C888.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C8B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C99C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093CA80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093CAC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/ObjSwitch_Draw.s")
