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
    (ActorFunc)EnKgy_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/EnKgy_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/EnKgy_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B40B38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B40BC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B40BFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B40C38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B40C74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B40D00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B40D30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B40D64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B40D8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B40DB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B40E18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B40E38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B40E54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B40E74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B40EBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B40EE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B411DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B41368.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B413C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B41460.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B41528.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B415A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B4163C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B417B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B41858.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B418C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B419B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B41A48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B41ACC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B41C30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B41C54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B41CBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B41D64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B41E18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B42508.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B425A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B42660.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B42714.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B427C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B4296C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B42A8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B42D28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/EnKgy_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B42FA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B43008.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/func_80B43074.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kgy_0x80B40800/EnKgy_Draw.asm")
