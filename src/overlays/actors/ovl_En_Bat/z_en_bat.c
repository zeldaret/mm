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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_BAT,
    sizeof(EnBat),
    (ActorFunc)EnBat_Init,
    (ActorFunc)EnBat_Destroy,
    (ActorFunc)EnBat_Update,
    (ActorFunc)EnBat_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Bat_0x80A434E0/EnBat_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bat_0x80A434E0/EnBat_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bat_0x80A434E0/func_80A437CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bat_0x80A434E0/func_80A43810.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bat_0x80A434E0/func_80A43870.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bat_0x80A434E0/func_80A438D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bat_0x80A434E0/func_80A438F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bat_0x80A434E0/func_80A4392C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bat_0x80A434E0/func_80A43CA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bat_0x80A434E0/func_80A43CE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bat_0x80A434E0/func_80A43F60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bat_0x80A434E0/func_80A44114.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bat_0x80A434E0/func_80A44294.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bat_0x80A434E0/func_80A4431C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bat_0x80A434E0/func_80A443D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bat_0x80A434E0/EnBat_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bat_0x80A434E0/EnBat_Draw.asm")
