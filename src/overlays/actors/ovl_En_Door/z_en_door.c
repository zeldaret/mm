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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Door_0x80866800/EnDoor_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Door_0x80866800/EnDoor_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Door_0x80866800/func_80866A5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Door_0x80866800/func_80866B20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Door_0x80866800/func_80866F94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Door_0x80866800/func_8086704C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Door_0x80866800/func_80867080.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Door_0x80866800/func_808670F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Door_0x80866800/func_80867144.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Door_0x80866800/EnDoor_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Door_0x80866800/func_80867350.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Door_0x80866800/EnDoor_Draw.asm")
