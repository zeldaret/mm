#include "z_en_wdhand.h"

#define FLAGS 0x00000005

#define THIS ((EnWdhand*)thisx)

void EnWdhand_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWdhand_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWdhand_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWdhand_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Wdhand_InitVars = {
    ACTOR_EN_WDHAND,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_WDHAND,
    sizeof(EnWdhand),
    (ActorFunc)EnWdhand_Init,
    (ActorFunc)EnWdhand_Destroy,
    (ActorFunc)EnWdhand_Update,
    (ActorFunc)EnWdhand_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/EnWdhand_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/EnWdhand_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/func_80AF4608.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/func_80AF4670.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/func_80AF46F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/func_80AF488C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/func_80AF48D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/func_80AF4964.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/func_80AF4A88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/func_80AF4C18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/func_80AF4C64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/func_80AF4ED0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/func_80AF4F30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/func_80AF4F6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/func_80AF4FF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/func_80AF5130.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/func_80AF520C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/func_80AF5650.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/func_80AF56A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/func_80AF5820.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/func_80AF5E3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/EnWdhand_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/func_80AF5FE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wdhand_0x80AF43F0/EnWdhand_Draw.asm")
