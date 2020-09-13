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
    ACTORTYPE_DOOR,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnDoor),
    (ActorFunc)EnDoor_Init,
    (ActorFunc)EnDoor_Destroy,
    (ActorFunc)EnDoor_Update,
    (ActorFunc)EnDoor_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_0x80866800/EnDoor_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_0x80866800/EnDoor_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_0x80866800/func_80866A5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_0x80866800/func_80866B20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_0x80866800/func_80866F94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_0x80866800/func_8086704C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_0x80866800/func_80867080.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_0x80866800/func_808670F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_0x80866800/func_80867144.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_0x80866800/EnDoor_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Door_0x80866800/func_80867350.asm")
