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
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_KGY,
    sizeof(EnKgy),
    (ActorFunc)EnKgy_Init,
    (ActorFunc)EnKgy_Destroy,
    (ActorFunc)EnKgy_Update,
    (ActorFunc)EnKgy_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/EnKgy_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/EnKgy_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B40B38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B40BC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B40BFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B40C38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B40C74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B40D00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B40D30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B40D64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B40D8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B40DB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B40E18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B40E38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B40E54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B40E74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B40EBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B40EE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B411DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B41368.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B413C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B41460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B41528.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B415A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B4163C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B417B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B41858.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B418C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B419B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B41A48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B41ACC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B41C30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B41C54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B41CBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B41D64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B41E18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B42508.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B425A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B42660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B42714.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B427C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B4296C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B42A8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B42D28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/EnKgy_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B42FA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B43008.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/func_80B43074.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kgy/EnKgy_Draw.s")
