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
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_BSB,
    sizeof(EnBsb),
    (ActorFunc)EnBsb_Init,
    (ActorFunc)EnBsb_Destroy,
    (ActorFunc)EnBsb_Update,
    (ActorFunc)EnBsb_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0B290.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0B31C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/EnBsb_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/EnBsb_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0B888.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0B970.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0BA58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0BC30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0BE1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0BF2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0BFE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0C0F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0C238.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0C32C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0C364.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0C430.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0C484.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0C610.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0C6A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0C86C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0C8EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0CA28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0CB3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0CCCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0CD04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0CD90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0CDE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0CF4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0CFDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0D00C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0D10C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0D214.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0D27C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0D334.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0D384.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0D3C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0D51C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0D964.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0D9B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0DA58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0DB18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0E178.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0E1C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0E3B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0E480.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0E4FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0E618.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0E9CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/EnBsb_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0EEA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0F078.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0F170.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/EnBsb_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0F544.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0F640.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0F758.s")
