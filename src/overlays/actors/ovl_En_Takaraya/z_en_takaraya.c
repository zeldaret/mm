/*
 * File: z_en_takaraya.c
 * Overlay: ovl_En_Takaraya
 * Description: Treasure Chest Shop Gal
 */

#include "z_en_takaraya.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnTakaraya*)thisx)

void EnTakaraya_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTakaraya_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTakaraya_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTakaraya_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Takaraya_InitVars = {
    ACTOR_EN_TAKARAYA,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BG,
    sizeof(EnTakaraya),
    (ActorFunc)EnTakaraya_Init,
    (ActorFunc)EnTakaraya_Destroy,
    (ActorFunc)EnTakaraya_Update,
    (ActorFunc)EnTakaraya_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80ADFB20[] = {
    ICHAIN_U8(targetMode, 6, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 1000, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80ADFB20[];

extern UNK_TYPE D_06001384;
extern UNK_TYPE D_06009890;
extern UNK_TYPE D_0600A280;
extern UNK_TYPE D_0600AD98;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/EnTakaraya_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/EnTakaraya_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADED8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADEDF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADEE4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADEF74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF03C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF050.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF2D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF338.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF4E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF520.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF608.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF654.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF6DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF730.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF7B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF7CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/EnTakaraya_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF94C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/EnTakaraya_Draw.s")
