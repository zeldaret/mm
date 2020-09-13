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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_PR,
    sizeof(EnPrz),
    (ActorFunc)EnPrz_Init,
    (ActorFunc)EnPrz_Destroy,
    (ActorFunc)EnPrz_Update,
    (ActorFunc)EnPrz_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Prz_0x80A75DC0/EnPrz_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Prz_0x80A75DC0/EnPrz_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Prz_0x80A75DC0/func_80A75F18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Prz_0x80A75DC0/func_80A75FA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Prz_0x80A75DC0/func_80A76070.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Prz_0x80A75DC0/func_80A762C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Prz_0x80A75DC0/func_80A76388.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Prz_0x80A75DC0/func_80A763E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Prz_0x80A75DC0/func_80A76604.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Prz_0x80A75DC0/func_80A76634.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Prz_0x80A75DC0/func_80A76748.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Prz_0x80A75DC0/func_80A767A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Prz_0x80A75DC0/func_80A76A1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Prz_0x80A75DC0/func_80A76B14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Prz_0x80A75DC0/EnPrz_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Prz_0x80A75DC0/func_80A76F70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Prz_0x80A75DC0/func_80A76FCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Prz_0x80A75DC0/EnPrz_Draw.asm")
