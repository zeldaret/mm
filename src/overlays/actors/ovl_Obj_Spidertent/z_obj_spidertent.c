#include "z_obj_spidertent.h"

#define FLAGS 0x10000000

#define THIS ((ObjSpidertent*)thisx)

void ObjSpidertent_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjSpidertent_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjSpidertent_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjSpidertent_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit Obj_Spidertent_InitVars = {
    ACTOR_OBJ_SPIDERTENT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_SPIDERTENT,
    sizeof(ObjSpidertent),
    (ActorFunc)ObjSpidertent_Init,
    (ActorFunc)ObjSpidertent_Destroy,
    (ActorFunc)ObjSpidertent_Update,
    (ActorFunc)ObjSpidertent_Draw,
};


// static ColliderTrisElementInit sTrisElementsInit[6] = {
static ColliderTrisElementInit D_80B31060[6] = {
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00000800, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 68.80000305175781f, 0.0f, 18.799999237060547f }, { 76.30000305175781f, 0.0f, -63.79999923706055f }, { 1.2999999523162842f, 40.0f, -3.799999952316284f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00000800, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 76.30000305175781f, 0.0f, -63.79999923706055f }, { 23.799999237060547f, 0.0f, -116.30000305175781f }, { 1.2999999523162842f, 40.0f, -3.799999952316284f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00000800, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 23.799999237060547f, 0.0f, -116.30000305175781f }, { -111.30000305175781f, 0.0f, -26.299999237060547f }, { 1.2999999523162842f, 40.0f, -3.799999952316284f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00000800, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -111.30000305175781f, 0.0f, -26.299999237060547f }, { -81.30000305175781f, 0.0f, 78.80000305175781f }, { 1.2999999523162842f, 40.0f, -3.799999952316284f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00000800, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -81.30000305175781f, 0.0f, 78.80000305175781f }, { 23.799999237060547f, 0.0f, 108.80000305175781f }, { 1.2999999523162842f, 40.0f, -3.799999952316284f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00000800, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 23.799999237060547f, 0.0f, 108.80000305175781f }, { 68.80000305175781f, 0.0f, 18.799999237060547f }, { 1.2999999523162842f, 40.0f, -3.799999952316284f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_80B311C8 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_TRIS, },
    6, D_80B31060, // sTrisElementsInit,
};


// static ColliderTrisElementInit sTrisElementsInit[6] = {
static ColliderTrisElementInit D_80B311D8[6] = {
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00000800, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 17.799999237060547f, 0.0f, 81.5999984741211f }, { 51.599998474121094f, 0.0f, 14.100000381469727f }, { 0.8999999761581421f, 30.0f, -2.799999952316284f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00000800, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -60.900001525878906f, 0.0f, 59.099998474121094f }, { 17.799999237060547f, 0.0f, 81.5999984741211f }, { 0.8999999761581421f, 30.0f, -2.799999952316284f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00000800, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -83.4000015258789f, 0.0f, -19.700000762939453f }, { -60.900001525878906f, 0.0f, 59.099998474121094f }, { 0.8999999761581421f, 30.0f, -2.799999952316284f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00000800, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 17.799999237060547f, 0.0f, -87.19999694824219f }, { -83.4000015258789f, 0.0f, -19.700000762939453f }, { 0.8999999761581421f, 30.0f, -2.799999952316284f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00000800, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 57.20000076293945f, 0.0f, -47.79999923706055f }, { 17.799999237060547f, 0.0f, -87.19999694824219f }, { 0.8999999761581421f, 30.0f, -2.799999952316284f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00000800, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 51.599998474121094f, 0.0f, 14.100000381469727f }, { 57.20000076293945f, 0.0f, -47.79999923706055f }, { 0.8999999761581421f, 30.0f, -2.799999952316284f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_80B31340 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_TRIS, },
    6, D_80B311D8, // sTrisElementsInit,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B31418[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B2FB10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B2FB94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B2FC98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B300F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B30410.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B30480.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/ObjSpidertent_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/ObjSpidertent_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B307E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B30808.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B30A2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B30A4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B30AD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B30AF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/ObjSpidertent_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/ObjSpidertent_Draw.asm")
