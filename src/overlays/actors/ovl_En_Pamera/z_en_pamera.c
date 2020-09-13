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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_PAMERA,
    sizeof(EnPamera),
    (ActorFunc)EnPamera_Init,
    (ActorFunc)EnPamera_Destroy,
    (ActorFunc)EnPamera_Update,
    (ActorFunc)EnPamera_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/EnPamera_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD84F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD8588.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD8658.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/EnPamera_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD8700.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD8758.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD8908.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD8964.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD8A38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD8A7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD8B50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD8B70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD8CCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD8D1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD8D80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD8DB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD8F0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD8F60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD8FF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD909C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD90AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD9234.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD92D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD9338.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD9384.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD93CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD93F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD94E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/EnPamera_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD9648.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD9690.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/EnPamera_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD9840.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD9904.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD9928.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD9938.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD994C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD9A9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD9AB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD9B4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD9C70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD9CB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD9E60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD9E78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD9E88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD9ED0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD9EE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BD9F3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BDA038.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BDA090.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BDA0A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BDA0FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BDA170.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BDA1C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BDA288.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BDA2E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pamera_0x80BD82B0/func_80BDA344.asm")
