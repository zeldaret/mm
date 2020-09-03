#include "z_en_bsb.h"

#define FLAGS 0x02000035

#define THIS ((EnBsb*)thisx)

void EnBsb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBsb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBsb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBsb_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bsb_InitVars = {
    ACTOR_EN_BSB,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_BSB,
    sizeof(EnBsb),
    (ActorFunc)EnBsb_Init,
    (ActorFunc)EnBsb_Destroy,
    (ActorFunc)EnBsb_Update,
    (ActorFunc)EnBsb_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0B290.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0B31C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/EnBsb_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/EnBsb_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0B888.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0B970.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0BA58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0BC30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0BE1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0BF2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0BFE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0C0F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0C238.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0C32C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0C364.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0C430.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0C484.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0C610.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0C6A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0C86C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0C8EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0CA28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0CB3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0CCCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0CD04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0CD90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0CDE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0CF4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0CFDC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0D00C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0D10C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0D214.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0D27C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0D334.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0D384.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0D3C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0D51C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0D964.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0D9B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0DA58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0DB18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0E178.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0E1C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0E3B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0E480.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0E4FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0E618.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0E9CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/EnBsb_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0EEA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0F078.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0F170.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/EnBsb_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0F544.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0F640.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bsb_0x80C0B290/func_80C0F758.asm")
