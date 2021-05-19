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
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A80A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A80AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A812C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A8218.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A82F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/EnOssan_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/EnOssan_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A849C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A8500.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A85FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A8644.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A86A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A8708.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A875C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A8798.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A890C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A8B74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A8CC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A8DF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A8E84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A8EEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A90A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A91B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A935C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A9400.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A94FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A95F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A980C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A98E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A9AB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A9C8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A9D64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A9E20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A9E5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A9E98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AA0C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AA1B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AA224.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AA2C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AA33C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AA404.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AA5E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AA6D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AA79C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AA7C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AA85C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AA8E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AAA64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AAB30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AACE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AAD14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AADB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AAE1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AAE84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AAFB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AB0B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AB16C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AB404.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/EnOssan_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AB52C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AB78C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AB928.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808ABCD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808ABD10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808ABD60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808ABE18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808ABE58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808ABF30.asm")
