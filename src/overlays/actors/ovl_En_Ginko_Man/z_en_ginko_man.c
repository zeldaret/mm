#include "z_en_ginko_man.h"

#define FLAGS 0x00000009

#define THIS ((EnGinkoMan*)thisx)

void EnGinkoMan_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGinkoMan_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGinkoMan_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGinkoMan_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ginko_Man_InitVars = {
    ACTOR_EN_GINKO_MAN,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_BOJ,
    sizeof(EnGinkoMan),
    (ActorFunc)EnGinkoMan_Init,
    (ActorFunc)EnGinkoMan_Destroy,
    (ActorFunc)EnGinkoMan_Update,
    (ActorFunc)EnGinkoMan_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/EnGinkoMan_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/EnGinkoMan_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/func_80A64554.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/func_80A645A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/func_80A646F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/func_80A64DC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/func_80A65364.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/func_80A65490.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/func_80A654A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/func_80A6557C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/func_80A65590.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/func_80A656C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/func_80A656D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/func_80A65800.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/func_80A65844.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/func_80A65988.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/func_80A65A5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/EnGinkoMan_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/func_80A65B44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/func_80A65C18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ginko_Man_0x80A644A0/EnGinkoMan_Draw.asm")
