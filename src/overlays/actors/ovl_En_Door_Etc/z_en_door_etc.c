#include "z_en_door_etc.h"

#define FLAGS 0x00000010

#define THIS ((EnDoorEtc*)thisx)

void EnDoorEtc_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDoorEtc_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDoorEtc_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Door_Etc_InitVars = {
    ACTOR_EN_DOOR_ETC,
    ACTORCAT_DOOR,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnDoorEtc),
    (ActorFunc)EnDoorEtc_Init,
    (ActorFunc)EnDoorEtc_Destroy,
    (ActorFunc)EnDoorEtc_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door_Etc/EnDoorEtc_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door_Etc/EnDoorEtc_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door_Etc/func_80AC2044.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door_Etc/func_80AC20A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door_Etc/func_80AC2118.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door_Etc/func_80AC2154.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door_Etc/func_80AC21A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door_Etc/func_80AC2354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door_Etc/EnDoorEtc_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door_Etc/func_80AC24A8.s")
