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
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RD,
    sizeof(EnRailgibud),
    (ActorFunc)EnRailgibud_Init,
    (ActorFunc)EnRailgibud_Destroy,
    (ActorFunc)EnRailgibud_Update,
    (ActorFunc)EnRailgibud_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA5400.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/EnRailgibud_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/EnRailgibud_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA57A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA57F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA59F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA5A34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA5AF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA5B64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA5DBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA5E18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6054.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA60B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6158.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA61A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6284.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA62D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6440.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA64AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6584.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6604.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6664.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA66C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6800.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6974.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6B30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6B9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6D10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6DAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA6DF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7088.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA71E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7234.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7388.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7434.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7578.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA76C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/EnRailgibud_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7878.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA789C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA78F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/EnRailgibud_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7B6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7C78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7CF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7D04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7D14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7D30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA7DC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Railgibud/func_80BA8050.s")
