#include "z_en_bigslime.h"

#define FLAGS 0x00000235

#define THIS ((EnBigslime*)thisx)

void EnBigslime_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBigslime_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBigslime_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBigslime_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bigslime_InitVars = {
    ACTOR_EN_BIGSLIME,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BIGSLIME,
    sizeof(EnBigslime),
    (ActorFunc)EnBigslime_Init,
    (ActorFunc)EnBigslime_Destroy,
    (ActorFunc)EnBigslime_Update,
    (ActorFunc)EnBigslime_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/EnBigslime_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/EnBigslime_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E5388.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E5430.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E5484.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E574C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E5988.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E5A00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E5BB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E5ED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E601C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E616C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E62B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E64D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E6538.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E6570.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E670C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E6828.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E68AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E69AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E69F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E6A70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E6B08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E6B68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E6C18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E6C44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E6C70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E6CC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E6D58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E6E80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E6F08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E6F50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E6FE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E7048.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E7154.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E71FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E732C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E7354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E75D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E7770.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E7AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E7B80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E7D68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E8064.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E836C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E844C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E84DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E88B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E89CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E8C38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E8CCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E90A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E91EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E9778.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E97D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E994C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E9AE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E9DA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E9DD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E9F38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808E9FC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EA14C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EA1C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EA264.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EA2D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EA538.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EA5E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EA748.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EA7A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EA80C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EA860.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EA8FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EA9B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EAA40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EAA8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EAAF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EAB74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EABCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EACEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EAEBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EB0A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EB178.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EB24C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EB328.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EB574.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EB690.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EB708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EB7F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EB804.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EB83C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EB8B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EB9E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EBBE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EBED0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EC158.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EC354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/EnBigslime_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EC708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808EC990.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808ECD14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808ED07C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/EnBigslime_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigslime/func_808ED3F4.s")
