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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_AZ,
    sizeof(EnAz),
    (ActorFunc)EnAz_Init,
    (ActorFunc)EnAz_Destroy,
    (ActorFunc)EnAz_Update,
    (ActorFunc)EnAz_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A94A30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A94A64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A94A90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A94AB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A94B20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A94B98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/EnAz_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/EnAz_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A954AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A95534.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A9565C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A95730.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A958B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A95B34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A95C5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A95CEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A95DA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A95E88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A95F94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A95FE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A9617C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A97114.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A97274.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A973B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A97410.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A979DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A979F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A97A28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A97A40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A97A9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A97AB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A97C0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A97C24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A97C4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A97D5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A97E48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A97EAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A97F9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A982E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A98414.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/EnAz_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/EnAz_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A98DA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A98E48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A98EFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Az_0x80A94A30/func_80A98F94.asm")
