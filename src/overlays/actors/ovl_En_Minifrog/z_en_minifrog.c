#include "z_en_minifrog.h"

#define FLAGS 0x00000019

#define THIS ((EnMinifrog*)thisx)

void EnMinifrog_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMinifrog_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMinifrog_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMinifrog_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Minifrog_InitVars = {
    ACTOR_EN_MINIFROG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_FR,
    sizeof(EnMinifrog),
    (ActorFunc)EnMinifrog_Init,
    (ActorFunc)EnMinifrog_Destroy,
    (ActorFunc)EnMinifrog_Update,
    (ActorFunc)EnMinifrog_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/EnMinifrog_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/EnMinifrog_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A3930.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A3980.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A39EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A3A44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A3B04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A3B3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A3B74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A3DA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A3F88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A4040.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A410C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A41A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A4214.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A42D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A4328.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A43A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A44BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A45A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A4634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A46E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A4914.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/EnMinifrog_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A4AC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A4AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/func_808A4B3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minifrog/EnMinifrog_Draw.s")
