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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA5400.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/EnRailgibud_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/EnRailgibud_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA57A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA57F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA59F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA5A34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA5AF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA5B64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA5DBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA5E18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6054.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA60B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6158.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA61A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6284.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA62D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6440.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA64AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6584.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6604.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6664.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA66C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6800.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6974.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6B30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6B9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6D10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6DAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA6DF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7088.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA71E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7234.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7388.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7434.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7578.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA76C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/EnRailgibud_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7878.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA789C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA78F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/EnRailgibud_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7B6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7C78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7CF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7D04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7D14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7D30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA7DC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Railgibud_0x80BA5400/func_80BA8050.asm")
