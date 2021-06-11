#include "z_en_pamera.h"

#define FLAGS 0x00000019

#define THIS ((EnPamera*)thisx)

void EnPamera_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPamera_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPamera_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPamera_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Pamera_InitVars = {
    ACTOR_EN_PAMERA,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_PAMERA,
    sizeof(EnPamera),
    (ActorFunc)EnPamera_Init,
    (ActorFunc)EnPamera_Destroy,
    (ActorFunc)EnPamera_Update,
    (ActorFunc)EnPamera_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/EnPamera_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD84F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD8588.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD8658.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/EnPamera_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD8700.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD8758.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD8908.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD8964.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD8A38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD8A7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD8B50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD8B70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD8CCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD8D1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD8D80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD8DB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD8F0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD8F60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD8FF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD909C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD90AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD9234.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD92D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD9338.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD9384.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD93CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD93F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD94E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/EnPamera_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD9648.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD9690.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/EnPamera_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD9840.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD9904.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD9928.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD9938.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD994C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD9A9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD9AB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD9B4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD9C70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD9CB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD9E60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD9E78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD9E88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD9ED0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD9EE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BD9F3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BDA038.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BDA090.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BDA0A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BDA0FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BDA170.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BDA1C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BDA288.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BDA2E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pamera/func_80BDA344.s")
