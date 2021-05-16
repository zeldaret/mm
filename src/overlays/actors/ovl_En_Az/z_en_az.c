#include "z_en_az.h"

#define FLAGS 0x80000010

#define THIS ((EnAz*)thisx)

void EnAz_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAz_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAz_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAz_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Az_InitVars = {
    ACTOR_EN_AZ,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AZ,
    sizeof(EnAz),
    (ActorFunc)EnAz_Init,
    (ActorFunc)EnAz_Destroy,
    (ActorFunc)EnAz_Update,
    (ActorFunc)EnAz_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A94A30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A94A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A94A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A94AB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A94B20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A94B98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/EnAz_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/EnAz_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A954AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A95534.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A9565C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A95730.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A958B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A95B34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A95C5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A95CEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A95DA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A95E88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A95F94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A95FE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A9617C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A97114.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A97274.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A973B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A97410.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A979DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A979F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A97A28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A97A40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A97A9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A97AB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A97C0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A97C24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A97C4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A97D5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A97E48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A97EAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A97F9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A982E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A98414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/EnAz_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/EnAz_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A98DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A98E48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A98EFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Az/func_80A98F94.s")
