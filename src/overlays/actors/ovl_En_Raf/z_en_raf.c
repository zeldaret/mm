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
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_RAF,
    sizeof(EnRaf),
    (ActorFunc)EnRaf_Init,
    (ActorFunc)EnRaf_Destroy,
    (ActorFunc)EnRaf_Update,
    (ActorFunc)EnRaf_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A16D40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A16D6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/EnRaf_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/EnRaf_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A17060.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A1712C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A171D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A17414.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A17464.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A17530.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A175E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A17848.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A178A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A179C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A17C6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A17D14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A17D54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A17DDC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A17E1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A18080.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A180B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/EnRaf_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A1859C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/EnRaf_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A18A90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A18B8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Raf_0x80A16D40/func_80A18DA0.asm")
