/*
 * File z_en_box.c
 * Overlay: ovl_En_Box
 * Description: Chest
 */

#include "z_en_box.h"

#define FLAGS 0x00000000

#define THIS ((EnBox*)thisx)

void EnBox_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBox_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBox_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBox_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Box_InitVars = {
    ACTOR_EN_BOX,
    ACTORCAT_CHEST,
    FLAGS,
    OBJECT_BOX,
    sizeof(EnBox),
    (ActorFunc)EnBox_Init,
    (ActorFunc)EnBox_Destroy,
    (ActorFunc)EnBox_Update,
    (ActorFunc)EnBox_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80869B50[] = {
    ICHAIN_U8(targetMode, 0, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80869B50[];

extern UNK_TYPE D_0600043C;
extern UNK_TYPE D_06000DB0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_80867BD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_80867BDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_80867C14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_80867C8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_80867FBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_80867FE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_8086800C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/EnBox_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/EnBox_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_80868630.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_80868734.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_808687E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_80868944.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_808689E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_80868A6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_80868AFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_80868B74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_80868CC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_80869020.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_808692E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/EnBox_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_80869600.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_80869850.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_80869874.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_808698B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/EnBox_Draw.s")
