#include "z_en_dnb.h"

#define FLAGS 0x000000B0

#define THIS ((EnDnb*)thisx)

void EnDnb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDnb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDnb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDnb_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Dnb_InitVars = {
    ACTOR_EN_DNB,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_HANAREYAMA_OBJ,
    sizeof(EnDnb),
    (ActorFunc)EnDnb_Init,
    (ActorFunc)EnDnb_Destroy,
    (ActorFunc)EnDnb_Update,
    (ActorFunc)EnDnb_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnb_0x80A4FDD0/func_80A4FDD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnb_0x80A4FDD0/func_80A4FEBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnb_0x80A4FDD0/func_80A4FFE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnb_0x80A4FDD0/func_80A500F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnb_0x80A4FDD0/EnDnb_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnb_0x80A4FDD0/EnDnb_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnb_0x80A4FDD0/EnDnb_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnb_0x80A4FDD0/func_80A50510.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnb_0x80A4FDD0/func_80A5063C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnb_0x80A4FDD0/EnDnb_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnb_0x80A4FDD0/func_80A507C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnb_0x80A4FDD0/func_80A5086C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnb_0x80A4FDD0/func_80A50950.asm")
