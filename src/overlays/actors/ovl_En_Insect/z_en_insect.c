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
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnInsect),
    (ActorFunc)EnInsect_Init,
    (ActorFunc)EnInsect_Destroy,
    (ActorFunc)EnInsect_Update,
    (ActorFunc)EnInsect_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091A8A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091A8C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091A8F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091A9E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/EnInsect_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/EnInsect_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091AC78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091ACC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091AE10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091AE5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091B030.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091B07C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091B274.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091B2D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091B3D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091B440.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091B618.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091B670.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091B928.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091B984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/EnInsect_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/EnInsect_Draw.s")
