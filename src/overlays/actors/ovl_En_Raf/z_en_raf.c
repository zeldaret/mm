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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A16D40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A16D6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/EnRaf_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/EnRaf_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A17060.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A1712C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A171D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A17414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A17464.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A17530.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A175E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A17848.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A178A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A179C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A17C6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A17D14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A17D54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A17DDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A17E1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A18080.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A180B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/EnRaf_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A1859C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/EnRaf_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A18A90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A18B8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A18DA0.asm")
