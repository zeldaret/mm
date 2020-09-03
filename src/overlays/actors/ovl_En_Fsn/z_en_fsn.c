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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_FSN,
    sizeof(EnFsn),
    (ActorFunc)EnFsn_Init,
    (ActorFunc)EnFsn_Destroy,
    (ActorFunc)EnFsn_Update,
    (ActorFunc)EnFsn_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE1B70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE1BF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE1C54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE1E58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE1EF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE1F5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE2028.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE2074.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE21C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE2234.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE2298.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE2340.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE2438.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE2524.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE25D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE2670.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE26D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE2760.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE28B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE2974.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE2A98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE2B44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE2BE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE2C6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE2CFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE2DC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE2F78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE30F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE32D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE3474.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE352C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE3644.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE3880.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE38E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE3A68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE3BC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE3CF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE3D50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE3E4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE3F40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE4028.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE4120.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE41FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE4424.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE44DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE45C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE4638.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE4828.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE4A1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE4B20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE4B70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE4BF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE4CD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE4D28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/EnFsn_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/EnFsn_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/EnFsn_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE502C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE52A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE5440.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE57E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/func_80AE5910.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fsn_0x80AE1B70/EnFsn_Draw.asm")
