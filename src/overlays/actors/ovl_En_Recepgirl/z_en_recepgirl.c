/*
 * File: z_en_recepgirl.c
 * Overlay: ovl_En_Recepgirl
 * Description: Mayor's receptionist
 */

#include "z_en_recepgirl.h"

#define FLAGS 0x00000009

#define THIS ((EnRecepgirl*)thisx)

void EnRecepgirl_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRecepgirl_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRecepgirl_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRecepgirl_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Recepgirl_InitVars = {
    ACTOR_EN_RECEPGIRL,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BG,
    sizeof(EnRecepgirl),
    (ActorFunc)EnRecepgirl_Init,
    (ActorFunc)EnRecepgirl_Destroy,
    (ActorFunc)EnRecepgirl_Update,
    (ActorFunc)EnRecepgirl_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80C106C0[] = {
    ICHAIN_U8(targetMode, 6, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 1000, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80C106C0[];

extern UNK_TYPE D_06001384;
extern UNK_TYPE D_06009890;
extern UNK_TYPE D_0600A280;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/EnRecepgirl_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/EnRecepgirl_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/func_80C100DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/func_80C10148.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/func_80C1019C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/func_80C10290.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/func_80C102D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/EnRecepgirl_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/func_80C10558.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/func_80C10590.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Recepgirl/EnRecepgirl_Draw.s")
