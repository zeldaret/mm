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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/EnWdhand_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/EnWdhand_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/func_80AF4608.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/func_80AF4670.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/func_80AF46F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/func_80AF488C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/func_80AF48D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/func_80AF4964.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/func_80AF4A88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/func_80AF4C18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/func_80AF4C64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/func_80AF4ED0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/func_80AF4F30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/func_80AF4F6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/func_80AF4FF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/func_80AF5130.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/func_80AF520C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/func_80AF5650.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/func_80AF56A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/func_80AF5820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/func_80AF5E3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/EnWdhand_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/func_80AF5FE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wdhand/EnWdhand_Draw.s")
