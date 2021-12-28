/*
 * File: z_en_zoraegg.c
 * Overlay: ovl_En_Zoraegg
 * Description: Zora Egg
 */

#include "z_en_zoraegg.h"

#define FLAGS 0x00000010

#define THIS ((EnZoraegg*)thisx)

void EnZoraegg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZoraegg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZoraegg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZoraegg_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Zoraegg_InitVars = {
    ACTOR_EN_ZORAEGG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_ZORAEGG,
    sizeof(EnZoraegg),
    (ActorFunc)EnZoraegg_Init,
    (ActorFunc)EnZoraegg_Destroy,
    (ActorFunc)EnZoraegg_Update,
    (ActorFunc)EnZoraegg_Draw,
};

#endif

extern UNK_TYPE D_060005D4;
extern UNK_TYPE D_06004D20;
extern UNK_TYPE D_06004FE4;
extern UNK_TYPE D_06005098;
extern UNK_TYPE D_06005250;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B31590.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/EnZoraegg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/EnZoraegg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B319A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B319D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B31A34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B31C40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B31CB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B31D14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B31D64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B31E00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B32084.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B32094.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B320E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B321D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B32228.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B322BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B32390.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B324B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B32644.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B326F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B32820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B32928.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B32A88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B32B10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B32B3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B32B70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B32BB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B32C34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B32D08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/EnZoraegg_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B32F04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B331C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B3336C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B333DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B33480.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/func_80B33818.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zoraegg/EnZoraegg_Draw.s")
