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
    (ActorFunc)EnPrz_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Prz_0x80A75DC0/EnPrz_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Prz_0x80A75DC0/EnPrz_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Prz_0x80A75DC0/func_80A75F18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Prz_0x80A75DC0/func_80A75FA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Prz_0x80A75DC0/func_80A76070.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Prz_0x80A75DC0/func_80A762C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Prz_0x80A75DC0/func_80A76388.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Prz_0x80A75DC0/func_80A763E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Prz_0x80A75DC0/func_80A76604.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Prz_0x80A75DC0/func_80A76634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Prz_0x80A75DC0/func_80A76748.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Prz_0x80A75DC0/func_80A767A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Prz_0x80A75DC0/func_80A76A1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Prz_0x80A75DC0/func_80A76B14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Prz_0x80A75DC0/EnPrz_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Prz_0x80A75DC0/func_80A76F70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Prz_0x80A75DC0/func_80A76FCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Prz_0x80A75DC0/EnPrz_Draw.asm")
