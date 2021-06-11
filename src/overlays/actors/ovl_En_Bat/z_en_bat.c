#include "z_en_bat.h"

#define FLAGS 0x00005005

#define THIS ((EnBat*)thisx)

void EnBat_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBat_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBat_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBat_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bat_InitVars = {
    ACTOR_EN_BAT,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BAT,
    sizeof(EnBat),
    (ActorFunc)EnBat_Init,
    (ActorFunc)EnBat_Destroy,
    (ActorFunc)EnBat_Update,
    (ActorFunc)EnBat_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bat/EnBat_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bat/EnBat_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bat/func_80A437CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bat/func_80A43810.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bat/func_80A43870.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bat/func_80A438D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bat/func_80A438F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bat/func_80A4392C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bat/func_80A43CA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bat/func_80A43CE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bat/func_80A43F60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bat/func_80A44114.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bat/func_80A44294.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bat/func_80A4431C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bat/func_80A443D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bat/EnBat_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bat/EnBat_Draw.s")
