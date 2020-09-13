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
    ACTORTYPE_BOSS,
    FLAGS,
    OBJECT_BIGSLIME,
    sizeof(EnBigslime),
    (ActorFunc)EnBigslime_Init,
    (ActorFunc)EnBigslime_Destroy,
    (ActorFunc)EnBigslime_Update,
    (ActorFunc)EnBigslime_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/EnBigslime_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/EnBigslime_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E5388.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E5430.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E5484.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E574C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E5988.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E5A00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E5BB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E5ED4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E601C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E616C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E62B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E64D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E6538.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E6570.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E670C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E6828.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E68AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E69AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E69F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E6A70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E6B08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E6B68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E6C18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E6C44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E6C70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E6CC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E6D58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E6E80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E6F08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E6F50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E6FE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E7048.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E7154.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E71FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E732C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E7354.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E75D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E7770.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E7AF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E7B80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E7D68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E8064.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E836C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E844C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E84DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E88B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E89CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E8C38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E8CCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E90A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E91EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E9778.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E97D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E994C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E9AE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E9DA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E9DD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E9F38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808E9FC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EA14C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EA1C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EA264.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EA2D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EA538.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EA5E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EA748.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EA7A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EA80C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EA860.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EA8FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EA9B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EAA40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EAA8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EAAF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EAB74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EABCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EACEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EAEBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EB0A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EB178.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EB24C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EB328.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EB574.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EB690.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EB708.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EB7F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EB804.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EB83C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EB8B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EB9E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EBBE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EBED0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EC158.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EC354.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/EnBigslime_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EC708.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808EC990.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808ECD14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808ED07C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/EnBigslime_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigslime_0x808E4FC0/func_808ED3F4.asm")
