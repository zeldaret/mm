#include "z_en_baba.h"

#define FLAGS 0x00000019

#define THIS ((EnBaba*)thisx)

void EnBaba_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBaba_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBaba_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBaba_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Baba_InitVars = {
    ACTOR_EN_BABA,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_BBA,
    sizeof(EnBaba),
    (ActorFunc)EnBaba_Init,
    (ActorFunc)EnBaba_Destroy,
    (ActorFunc)EnBaba_Update,
    (ActorFunc)EnBaba_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA8820.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA886C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA8C4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA8C90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA8D2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA8DF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA8F88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA9110.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA9160.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA93AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA9480.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA9758.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA9848.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA98EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA9AB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA9B24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA9B80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA9CD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA9E00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA9E10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA9E48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/EnBaba_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/EnBaba_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/EnBaba_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BA9FB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BAA198.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/func_80BAA20C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baba_0x80BA8820/EnBaba_Draw.asm")
