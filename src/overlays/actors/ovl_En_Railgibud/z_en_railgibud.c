#include "z_en_railgibud.h"

#define FLAGS 0x00000415

#define THIS ((EnRailgibud*)thisx)

void EnRailgibud_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRailgibud_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRailgibud_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRailgibud_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Railgibud_InitVars = {
    ACTOR_EN_RAILGIBUD,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_RD,
    sizeof(EnRailgibud),
    (ActorFunc)EnRailgibud_Init,
    (ActorFunc)EnRailgibud_Destroy,
    (ActorFunc)EnRailgibud_Update,
    (ActorFunc)EnRailgibud_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA5400.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/EnRailgibud_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/EnRailgibud_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA57A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA57F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA59F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA5A34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA5AF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA5B64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA5DBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA5E18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA6054.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA60B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA6158.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA61A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA6284.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA62D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA6440.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA64AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA6584.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA6604.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA6664.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA66C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA6800.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA6974.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA6B30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA6B9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA6D10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA6DAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA6DF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA7088.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA71E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA7234.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA7388.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA7434.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA7578.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA76C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/EnRailgibud_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA7878.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA789C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA78F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/EnRailgibud_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA7B6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA7C78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA7CF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA7D04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA7D14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA7D30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA7DC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Railgibud_0x80BA5400/func_80BA8050.asm")
