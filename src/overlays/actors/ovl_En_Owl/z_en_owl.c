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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_OWL,
    sizeof(EnOwl),
    (ActorFunc)EnOwl_Init,
    (ActorFunc)EnOwl_Destroy,
    (ActorFunc)EnOwl_Update,
    (ActorFunc)EnOwl_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095A510.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/EnOwl_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/EnOwl_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095A920.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095A978.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095A9FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095AA70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095AAD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095AB1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095AB4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095ABA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095ABF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095AC50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095ACEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095AD54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095AE00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095AE60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095AEC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095AF2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095AFEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095B06C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095B0C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095B158.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095B1E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095B254.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095B2F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095B3DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095B480.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095B574.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095B650.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095B6C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095B76C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095B960.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095B9FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095BA84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095BE0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095BF20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095BF58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095BF78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095C09C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095C1C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095C258.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095C328.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095C408.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095C484.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095C510.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095C568.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/EnOwl_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095CCF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095CE18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095CF44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/EnOwl_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095D074.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Owl_0x8095A510/func_8095D24C.asm")
