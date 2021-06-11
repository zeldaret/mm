#include "z_en_raf.h"

#define FLAGS 0x08000000

#define THIS ((EnRaf*)thisx)

void EnRaf_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRaf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRaf_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRaf_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Raf_InitVars = {
    ACTOR_EN_RAF,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_RAF,
    sizeof(EnRaf),
    (ActorFunc)EnRaf_Init,
    (ActorFunc)EnRaf_Destroy,
    (ActorFunc)EnRaf_Update,
    (ActorFunc)EnRaf_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A16D40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A16D6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/EnRaf_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/EnRaf_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17060.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A1712C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A171D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17464.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17530.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A175E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17848.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A178A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A179C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17C6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17D14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17D54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17DDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17E1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A18080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A180B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/EnRaf_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A1859C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/EnRaf_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A18A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A18B8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A18DA0.s")
