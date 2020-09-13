#include "z_en_insect.h"

#define FLAGS 0x00000000

#define THIS ((EnInsect*)thisx)

void EnInsect_Init(Actor* thisx, GlobalContext* globalCtx);
void EnInsect_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnInsect_Update(Actor* thisx, GlobalContext* globalCtx);
void EnInsect_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Insect_InitVars = {
    ACTOR_EN_INSECT,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnInsect),
    (ActorFunc)EnInsect_Init,
    (ActorFunc)EnInsect_Destroy,
    (ActorFunc)EnInsect_Update,
    (ActorFunc)EnInsect_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/func_8091A8A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/func_8091A8C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/func_8091A8F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/func_8091A9E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/EnInsect_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/EnInsect_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/func_8091AC78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/func_8091ACC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/func_8091AE10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/func_8091AE5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/func_8091B030.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/func_8091B07C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/func_8091B274.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/func_8091B2D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/func_8091B3D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/func_8091B440.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/func_8091B618.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/func_8091B670.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/func_8091B928.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/func_8091B984.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/EnInsect_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Insect_0x8091A8A0/EnInsect_Draw.asm")
