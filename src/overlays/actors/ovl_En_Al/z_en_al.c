#include "z_en_al.h"

#define FLAGS 0x00000039

#define THIS ((EnAl*)thisx)

void EnAl_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAl_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAl_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAl_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Al_InitVars = {
    ACTOR_EN_AL,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_AL,
    sizeof(EnAl),
    (ActorFunc)EnAl_Init,
    (ActorFunc)EnAl_Destroy,
    (ActorFunc)EnAl_Update,
    (ActorFunc)EnAl_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDE1A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDE250.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDE27C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDE318.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDE384.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDE408.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDE484.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDE4E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDE678.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDE7FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDE92C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDEA14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDEABC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDEC2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDED20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDEE5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDEF3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDEFE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDF064.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDF244.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDF308.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDF390.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDF414.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDF568.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDF578.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDF5E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDF6C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/EnAl_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/EnAl_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/EnAl_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDF914.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDF950.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/func_80BDFA34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Al_0x80BDE1A0/EnAl_Draw.asm")
