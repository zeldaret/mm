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
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BBA,
    sizeof(EnBaba),
    (ActorFunc)EnBaba_Init,
    (ActorFunc)EnBaba_Destroy,
    (ActorFunc)EnBaba_Update,
    (ActorFunc)EnBaba_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA8820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA886C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA8C4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA8C90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA8D2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA8DF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA8F88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA9110.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA9160.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA93AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA9480.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA9758.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA9848.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA98EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA9AB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA9B24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA9B80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA9CD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA9E00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA9E10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA9E48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/EnBaba_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/EnBaba_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/EnBaba_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BA9FB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BAA198.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/func_80BAA20C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baba/EnBaba_Draw.s")
