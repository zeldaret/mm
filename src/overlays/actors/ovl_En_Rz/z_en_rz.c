/*
 * File: z_en_rz.c
 * Overlay: ovl_En_Rz
 * Description: Rosa Sisters, Judo (red) and Marilla (blue)
 */

#include "z_en_rz.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnRz*)thisx)

void EnRz_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRz_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRz_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRz_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BFC058(EnRz* this, GlobalContext* globalCtx);
void func_80BFC078(EnRz* this, GlobalContext* globalCtx);
void func_80BFC19C(EnRz* this, GlobalContext* globalCtx);
void func_80BFC214(EnRz* this, GlobalContext* globalCtx);
void func_80BFC270(EnRz* this, GlobalContext* globalCtx);
void func_80BFC2F4(EnRz* this, GlobalContext* globalCtx);
void func_80BFC36C(EnRz* this, GlobalContext* globalCtx);
void func_80BFC3F8(EnRz* this, GlobalContext* globalCtx);
void func_80BFC608(EnRz* this, GlobalContext* globalCtx);
void func_80BFC674(EnRz* this, GlobalContext* globalCtx);
void func_80BFC728(EnRz* this, GlobalContext* globalCtx);
void func_80BFC7E0(EnRz* this, GlobalContext* globalCtx);
void func_80BFC8F8(EnRz* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Rz_InitVars = {
    ACTOR_EN_RZ,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_RZ,
    sizeof(EnRz),
    (ActorFunc)EnRz_Init,
    (ActorFunc)EnRz_Destroy,
    (ActorFunc)EnRz_Update,
    (ActorFunc)EnRz_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BFCCF4 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 40, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80BFCCF4;

extern UNK_TYPE D_06003A20;
extern UNK_TYPE D_0600D768;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/EnRz_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFB780.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFB864.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFB9E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFBA1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFBA50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFBB44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFBC78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFBCEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFBD54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFBDA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFBDFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/EnRz_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFBE70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFBFAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC058.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC078.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC19C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC214.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC270.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC2F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC36C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC3F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC608.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC674.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC728.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC7E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC8AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC8F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/EnRz_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFCAD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/EnRz_Draw.s")
