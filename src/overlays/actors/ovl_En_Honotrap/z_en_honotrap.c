#include "z_en_honotrap.h"

#define FLAGS 0x00000010

#define THIS ((EnHonotrap*)thisx)

void EnHonotrap_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHonotrap_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHonotrap_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHonotrap_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit En_Honotrap_InitVars = {
    ACTOR_EN_HONOTRAP,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_DANGEON_KEEP,
    sizeof(EnHonotrap),
    (ActorFunc)EnHonotrap_Init,
    (ActorFunc)EnHonotrap_Destroy,
    (ActorFunc)EnHonotrap_Update,
    (ActorFunc)EnHonotrap_Draw,
};


// static ColliderTrisElementInit sTrisElementsInit[2] = {
static ColliderTrisElementInit D_80930424[2] = {
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
static ColliderTrisInit D_8093049C = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_TRIS, },
    2, D_80930424, // sTrisElementsInit,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809304AC = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x01, 0x04 }, { 0x00100000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
    { 10, 25, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit D_809304D8 = { 0, 9, 23, 1 };


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_809304E0[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_STOP),
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092E510.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092E5A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092E638.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092E840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092E988.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/EnHonotrap_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/EnHonotrap_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EBC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EBDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EC9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092ECF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EDC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EDD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EE08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EE1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EE68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EE90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EF3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EF98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F05C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F074.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F0A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F0B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F0F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F10C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F1A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F208.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F34C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F3D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F5AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F5EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F7A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F7BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F854.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F878.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/EnHonotrap_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092FE44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092FEFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/EnHonotrap_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_80930030.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_80930190.asm")
