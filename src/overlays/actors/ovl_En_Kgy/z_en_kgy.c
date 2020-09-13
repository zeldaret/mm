#include "z_en_kgy.h"

#define FLAGS 0x00000009

#define THIS ((EnKgy*)thisx)

void EnKgy_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKgy_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKgy_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKgy_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Kgy_InitVars = {
    ACTOR_EN_KGY,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_KGY,
    sizeof(EnKgy),
    (ActorFunc)EnKgy_Init,
    (ActorFunc)EnKgy_Destroy,
    (ActorFunc)EnKgy_Update,
    (ActorFunc)EnKgy_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/EnKgy_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/EnKgy_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B40B38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B40BC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B40BFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B40C38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B40C74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B40D00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B40D30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B40D64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B40D8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B40DB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B40E18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B40E38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B40E54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B40E74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B40EBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B40EE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B411DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B41368.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B413C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B41460.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B41528.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B415A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B4163C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B417B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B41858.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B418C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B419B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B41A48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B41ACC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B41C30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B41C54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B41CBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B41D64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B41E18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B42508.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B425A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B42660.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B42714.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B427C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B4296C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B42A8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B42D28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/EnKgy_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B42FA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B43008.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/func_80B43074.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kgy_0x80B40800/EnKgy_Draw.asm")
