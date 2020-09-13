#include "z_en_gamelupy.h"

#define FLAGS 0x00000010

#define THIS ((EnGamelupy*)thisx)

void EnGamelupy_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGamelupy_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGamelupy_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGamelupy_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Gamelupy_InitVars = {
    ACTOR_EN_GAMELUPY,
    ACTORTYPE_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnGamelupy),
    (ActorFunc)EnGamelupy_Init,
    (ActorFunc)EnGamelupy_Destroy,
    (ActorFunc)EnGamelupy_Update,
    (ActorFunc)EnGamelupy_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Gamelupy_0x80AF6760/EnGamelupy_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gamelupy_0x80AF6760/EnGamelupy_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gamelupy_0x80AF6760/func_80AF6854.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gamelupy_0x80AF6760/func_80AF6944.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gamelupy_0x80AF6760/func_80AF6958.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gamelupy_0x80AF6760/func_80AF6994.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gamelupy_0x80AF6760/func_80AF69A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gamelupy_0x80AF6760/func_80AF6A38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gamelupy_0x80AF6760/func_80AF6A78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gamelupy_0x80AF6760/func_80AF6B40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gamelupy_0x80AF6760/EnGamelupy_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gamelupy_0x80AF6760/EnGamelupy_Draw.asm")
