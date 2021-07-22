#include "z_obj_switch.h"

#define FLAGS 0x00000010

#define THIS ((ObjSwitch*)thisx)

void ObjSwitch_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjSwitch_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjSwitch_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjSwitch_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093ABD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093AC6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093ADA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093AE1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093AE74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093AE88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093AEC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093AEF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093AF1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093AF54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/ObjSwitch_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/ObjSwitch_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093B648.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093B668.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093B6F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093B710.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093B92C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093B940.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093B9C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093B9E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BB5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BB70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BBD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BCC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BCDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BD34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BD4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BDAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BDC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BE10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BE2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BEF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BF04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BF50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BF70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C0A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C0B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C138.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C15C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C23C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C250.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C2B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C2D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C3C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C3DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C460.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C488.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C584.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C598.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/ObjSwitch_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C778.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C888.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C8B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C99C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093CA80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093CAC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/ObjSwitch_Draw.asm")
