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
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_WDHAND,
    sizeof(EnWdhand),
    (ActorFunc)EnWdhand_Init,
    (ActorFunc)EnWdhand_Destroy,
    (ActorFunc)EnWdhand_Update,
    (ActorFunc)EnWdhand_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/EnWdhand_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/EnWdhand_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF4608.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF4670.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF46F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF488C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF48D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF4964.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF4A88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF4C18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF4C64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF4ED0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF4F30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF4F6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF4FF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF5130.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF520C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF5650.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF56A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF5820.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF5E3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/EnWdhand_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/func_80AF5FE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wdhand_0x80AF43F0/EnWdhand_Draw.asm")
