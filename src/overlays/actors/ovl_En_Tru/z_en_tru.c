/*
 * File: z_en_tru.c
 * Overlay: ovl_En_Tru
 * Description: Koume in Woods of Mystery
 */

#include "z_en_tru.h"

#define FLAGS 0x00000039

#define THIS ((EnTru*)thisx)

void EnTru_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTru_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTru_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTru_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A87FD0(EnTru* this, GlobalContext* globalCtx);
void func_80A881E0(EnTru* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Tru_InitVars = {
    ACTOR_EN_TRU,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TRU,
    sizeof(EnTru),
    (ActorFunc)EnTru_Init,
    (ActorFunc)EnTru_Destroy,
    (ActorFunc)EnTru_Update,
    (ActorFunc)EnTru_Draw,
};

// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_80A8B2A0 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 0, { { 0, 0, 0 }, 32 }, 100 },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80A8B2CC = { 1, 20, 0, 0, MASS_IMMOVABLE };

#endif

extern ColliderSphereInit D_80A8B2A0;
extern CollisionCheckInfoInit2 D_80A8B2CC;

extern UNK_TYPE D_060020C8;
extern UNK_TYPE D_0601A830;
extern UNK_TYPE D_0601AA60;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A85620.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A85788.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A85AA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A85BCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A85E2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A85F84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A86384.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A86460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A86674.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A86770.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A868F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A86924.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A8697C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A869DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A86B0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A86BAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A86DB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A871E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A872AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A873B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A87400.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A875AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A8777C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A87880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A87B48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A87DC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A87FD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A881E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/EnTru_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/EnTru_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/EnTru_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A885B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A88698.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/func_80A886D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru/EnTru_Draw.s")
