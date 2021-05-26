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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/EnBat_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/EnBat_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A437CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A43810.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A43870.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A438D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A438F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A4392C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A43CA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A43CE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A43F60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A44114.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A44294.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A4431C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A443D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/EnBat_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/EnBat_Draw.asm")
