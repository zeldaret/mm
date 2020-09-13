#include "z_en_gb2.h"

#define FLAGS 0x00000039

#define THIS ((EnGb2*)thisx)

void EnGb2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGb2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGb2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGb2_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Gb2_InitVars = {
    ACTOR_EN_GB2,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_PS,
    sizeof(EnGb2),
    (ActorFunc)EnGb2_Init,
    (ActorFunc)EnGb2_Destroy,
    (ActorFunc)EnGb2_Update,
    (ActorFunc)EnGb2_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B0F5E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B0F660.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B0F6DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B0F728.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B0F7FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B0F8F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B0F97C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B0FA04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B0FA48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B0FB24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B0FBF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B0FD8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B0FE18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B0FE7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B0FEBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B0FFA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B10240.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B10344.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B10584.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B10634.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B10868.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B10924.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B109DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B10A48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B10B5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B10DAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B10E98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B11048.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B110F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B111AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B11268.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B11344.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/EnGb2_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/EnGb2_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/EnGb2_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B1179C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/func_80B117FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gb2_0x80B0F5E0/EnGb2_Draw.asm")
