#include "z_en_ossan.h"

#define FLAGS 0x00000019

#define THIS ((EnOssan*)thisx)

void EnOssan_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOssan_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOssan_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ossan_InitVars = {
    ACTOR_EN_OSSAN,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnOssan),
    (ActorFunc)EnOssan_Init,
    (ActorFunc)EnOssan_Destroy,
    (ActorFunc)EnOssan_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A80A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A80AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A812C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A8218.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A82F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/EnOssan_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/EnOssan_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A849C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A8500.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A85FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A8644.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A86A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A8708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A875C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A8798.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A890C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A8B74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A8CC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A8DF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A8E84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A8EEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A90A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A91B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A935C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A9400.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A94FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A95F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A980C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A98E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A9AB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A9C8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A9D64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A9E20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A9E5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808A9E98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AA0C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AA1B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AA224.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AA2C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AA33C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AA404.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AA5E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AA6D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AA79C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AA7C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AA85C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AA8E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AAA64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AAB30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AACE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AAD14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AADB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AAE1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AAE84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AAFB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AB0B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AB16C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AB404.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/EnOssan_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AB52C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AB78C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808AB928.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808ABCD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808ABD10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808ABD60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808ABE18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808ABE58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ossan/func_808ABF30.s")
