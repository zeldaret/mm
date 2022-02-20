/*
 * File: z_en_nb.c
 * Overlay: ovl_En_Nb
 * Description: Anju's Grandma
 */

#include "z_en_nb.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnNb*)thisx)

void EnNb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNb_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BC0D84(EnNb* this, GlobalContext* globalCtx);
void func_80BC0EAC(EnNb* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Nb_InitVars = {
    ACTOR_EN_NB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_NB,
    sizeof(EnNb),
    (ActorFunc)EnNb_Init,
    (ActorFunc)EnNb_Destroy,
    (ActorFunc)EnNb_Update,
    (ActorFunc)EnNb_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BC15F0 = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 10, 68, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80BC161C = { 0, 0, 0, 0, MASS_IMMOVABLE };

#endif

extern ColliderCylinderInit D_80BC15F0;
extern CollisionCheckInfoInit2 D_80BC161C;

extern UNK_TYPE D_06008C40;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BBFDB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BBFE60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BBFE8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BBFF24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BBFF90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BBFFD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0050.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC00AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC01DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC045C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC04FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC05A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC06C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0800.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC08E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0978.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0A18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0B98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0C0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0C80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0D08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0D1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0D84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0EAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/EnNb_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/EnNb_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/EnNb_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC1174.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC11B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC1278.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/EnNb_Draw.s")
