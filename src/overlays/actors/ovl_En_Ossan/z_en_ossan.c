#include "z_en_ossan.h"

#define FLAGS 0x00000019

#define THIS ((EnOssan*)thisx)

void EnOssan_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOssan_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOssan_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ossan_InitVars = {
    ACTOR_EN_OSSAN,
    ACTORTYPE_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnOssan),
    (ActorFunc)EnOssan_Init,
    (ActorFunc)EnOssan_Destroy,
    (ActorFunc)EnOssan_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A80A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A80AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A812C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A8218.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A82F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/EnOssan_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/EnOssan_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A849C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A8500.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A85FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A8644.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A86A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A8708.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A875C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A8798.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A890C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A8B74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A8CC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A8DF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A8E84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A8EEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A90A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A91B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A935C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A9400.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A94FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A95F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A980C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A98E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A9AB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A9C8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A9D64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A9E20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A9E5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808A9E98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AA0C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AA1B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AA224.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AA2C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AA33C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AA404.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AA5E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AA6D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AA79C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AA7C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AA85C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AA8E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AAA64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AAB30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AACE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AAD14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AADB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AAE1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AAE84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AAFB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AB0B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AB16C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AB404.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/EnOssan_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AB52C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AB78C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808AB928.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808ABCD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808ABD10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808ABD60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808ABE18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808ABE58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ossan_0x808A80A0/func_808ABF30.asm")
