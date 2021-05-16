#include "z_en_prz.h"

#define FLAGS 0x00000015

#define THIS ((EnPrz*)thisx)

void EnPrz_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPrz_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPrz_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPrz_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Prz_InitVars = {
    ACTOR_EN_PRZ,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_PR,
    sizeof(EnPrz),
    (ActorFunc)EnPrz_Init,
    (ActorFunc)EnPrz_Destroy,
    (ActorFunc)EnPrz_Update,
    (ActorFunc)EnPrz_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Prz/EnPrz_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Prz/EnPrz_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Prz/func_80A75F18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Prz/func_80A75FA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Prz/func_80A76070.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Prz/func_80A762C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Prz/func_80A76388.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Prz/func_80A763E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Prz/func_80A76604.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Prz/func_80A76634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Prz/func_80A76748.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Prz/func_80A767A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Prz/func_80A76A1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Prz/func_80A76B14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Prz/EnPrz_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Prz/func_80A76F70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Prz/func_80A76FCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Prz/EnPrz_Draw.s")
