#include "z_en_door.h"

#define FLAGS 0x00000010

#define THIS ((EnDoor*)thisx)

void EnDoor_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDoor_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDoor_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDoor_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Door_InitVars = {
    ACTOR_EN_DOOR,
    ACTORCAT_DOOR,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnDoor),
    (ActorFunc)EnDoor_Init,
    (ActorFunc)EnDoor_Destroy,
    (ActorFunc)EnDoor_Update,
    (ActorFunc)EnDoor_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/EnDoor_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/EnDoor_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/func_80866A5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/func_80866B20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/func_80866F94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/func_8086704C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/func_80867080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/func_808670F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/func_80867144.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/EnDoor_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/func_80867350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/EnDoor_Draw.s")
