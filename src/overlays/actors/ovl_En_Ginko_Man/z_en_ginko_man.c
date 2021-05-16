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
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BOJ,
    sizeof(EnGinkoMan),
    (ActorFunc)EnGinkoMan_Init,
    (ActorFunc)EnGinkoMan_Destroy,
    (ActorFunc)EnGinkoMan_Update,
    (ActorFunc)EnGinkoMan_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/EnGinkoMan_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/EnGinkoMan_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/func_80A64554.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/func_80A645A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/func_80A646F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/func_80A64DC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/func_80A65364.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/func_80A65490.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/func_80A654A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/func_80A6557C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/func_80A65590.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/func_80A656C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/func_80A656D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/func_80A65800.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/func_80A65844.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/func_80A65988.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/func_80A65A5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/EnGinkoMan_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/func_80A65B44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/func_80A65C18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ginko_Man/EnGinkoMan_Draw.s")
