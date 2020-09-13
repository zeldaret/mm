#include "z_en_door_etc.h"

#define FLAGS 0x00000010

#define THIS ((EnDoorEtc*)thisx)

void EnDoorEtc_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDoorEtc_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDoorEtc_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Door_Etc_InitVars = {
    ACTOR_EN_DOOR_ETC,
    ACTORTYPE_DOOR,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnDoorEtc),
    (ActorFunc)EnDoorEtc_Init,
    (ActorFunc)EnDoorEtc_Destroy,
    (ActorFunc)EnDoorEtc_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_Etc_0x80AC1ED0/EnDoorEtc_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_Etc_0x80AC1ED0/EnDoorEtc_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_Etc_0x80AC1ED0/func_80AC2044.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_Etc_0x80AC1ED0/func_80AC20A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_Etc_0x80AC1ED0/func_80AC2118.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_Etc_0x80AC1ED0/func_80AC2154.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_Etc_0x80AC1ED0/func_80AC21A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_Etc_0x80AC1ED0/func_80AC2354.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_Etc_0x80AC1ED0/EnDoorEtc_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_Etc_0x80AC1ED0/func_80AC24A8.asm")
