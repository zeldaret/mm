#include "z_en_owl.h"

#define FLAGS 0x00000019

#define THIS ((EnOwl*)thisx)

void EnOwl_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOwl_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOwl_Update(Actor* thisx, GlobalContext* globalCtx);
void EnOwl_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Owl_InitVars = {
    ACTOR_EN_OWL,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OWL,
    sizeof(EnOwl),
    (ActorFunc)EnOwl_Init,
    (ActorFunc)EnOwl_Destroy,
    (ActorFunc)EnOwl_Update,
    (ActorFunc)EnOwl_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095A510.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/EnOwl_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/EnOwl_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095A920.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095A978.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095A9FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AA70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AAD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AB1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AB4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095ABA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095ABF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AC50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095ACEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AD54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AE00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AE60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AEC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AF2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AFEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B06C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B0C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B158.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B1E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B254.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B2F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B3DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B480.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B574.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B650.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B6C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B76C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B960.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B9FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095BA84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095BE0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095BF20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095BF58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095BF78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095C09C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095C1C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095C258.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095C328.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095C408.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095C484.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095C510.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095C568.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/EnOwl_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095CCF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095CE18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095CF44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/EnOwl_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095D074.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095D24C.s")
