/*
 * File: z_en_honotrap.c
 * Overlay: ovl_En_Honotrap
 * Description: Eye switch that shoots fire
 */

#include "z_en_honotrap.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnHonotrap*)thisx)

void EnHonotrap_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHonotrap_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHonotrap_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHonotrap_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_8092EBDC(EnHonotrap* this, GlobalContext* globalCtx);
void func_8092ECF0(EnHonotrap* this, GlobalContext* globalCtx);
void func_8092EDD8(EnHonotrap* this, GlobalContext* globalCtx);
void func_8092EE1C(EnHonotrap* this, GlobalContext* globalCtx);
void func_8092EE90(EnHonotrap* this, GlobalContext* globalCtx);
void func_8092EF98(EnHonotrap* this, GlobalContext* globalCtx);
void func_8092F074(EnHonotrap* this, GlobalContext* globalCtx);
void func_8092F0B8(EnHonotrap* this, GlobalContext* globalCtx);
void func_8092F10C(EnHonotrap* this, GlobalContext* globalCtx);
void func_8092F208(EnHonotrap* this, GlobalContext* globalCtx);
void func_8092F3D8(EnHonotrap* this, GlobalContext* globalCtx);
void func_8092F5EC(EnHonotrap* this, GlobalContext* globalCtx);
void func_8092F7BC(EnHonotrap* this, GlobalContext* globalCtx);
void func_8092F878(EnHonotrap* this, GlobalContext* globalCtx);

#if 0
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

#endif

extern ColliderTrisElementInit D_80930424[2];
extern ColliderTrisInit D_8093049C;
extern ColliderCylinderInit D_809304AC;
extern CollisionCheckInfoInit D_809304D8;
extern InitChainEntry D_809304E0[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092E510.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092E5A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092E638.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092E840.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092E988.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/EnHonotrap_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/EnHonotrap_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EBC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EBDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EC9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092ECF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EDC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EDD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EE08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EE1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EE68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EE90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EF3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EF98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F05C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F074.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F0A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F0B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F0F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F10C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F1A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F208.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F34C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F3D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F5AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F5EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F7A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F7BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F854.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F878.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/EnHonotrap_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092FE44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092FEFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/EnHonotrap_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_80930030.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_80930190.s")
