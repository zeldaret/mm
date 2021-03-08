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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/EnMinifrog_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/EnMinifrog_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A3930.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A3980.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A39EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A3A44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A3B04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A3B3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A3B74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A3DA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A3F88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A4040.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A410C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A41A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A4214.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A42D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A4328.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A43A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A44BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A45A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A4634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A46E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A4914.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/EnMinifrog_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A4AC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A4AF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/func_808A4B3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minifrog_0x808A3670/EnMinifrog_Draw.asm")
