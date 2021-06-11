#include "z_en_fsn.h"

#define FLAGS 0x00000019

#define THIS ((EnFsn*)thisx)

void EnFsn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFsn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFsn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFsn_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Fsn_InitVars = {
    ACTOR_EN_FSN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_FSN,
    sizeof(EnFsn),
    (ActorFunc)EnFsn_Init,
    (ActorFunc)EnFsn_Destroy,
    (ActorFunc)EnFsn_Update,
    (ActorFunc)EnFsn_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE1B70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE1BF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE1C54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE1E58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE1EF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE1F5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE2028.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE2074.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE21C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE2234.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE2298.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE2340.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE2438.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE2524.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE25D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE2670.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE26D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE2760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE28B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE2974.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE2A98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE2B44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE2BE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE2C6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE2CFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE2DC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE2F78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE30F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE32D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE3474.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE352C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE3644.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE3880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE38E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE3A68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE3BC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE3CF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE3D50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE3E4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE3F40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE4028.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE4120.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE41FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE4424.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE44DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE45C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE4638.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE4828.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE4A1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE4B20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE4B70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE4BF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE4CD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE4D28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/EnFsn_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/EnFsn_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/EnFsn_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE502C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE52A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE5440.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE57E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/func_80AE5910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fsn/EnFsn_Draw.s")
