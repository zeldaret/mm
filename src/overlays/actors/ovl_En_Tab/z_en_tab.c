#include "z_en_tab.h"

#define FLAGS 0x00000039

#define THIS ((EnTab*)thisx)

void EnTab_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTab_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTab_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTab_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Tab_InitVars = {
    ACTOR_EN_TAB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TAB,
    sizeof(EnTab),
    (ActorFunc)EnTab_Init,
    (ActorFunc)EnTab_Destroy,
    (ActorFunc)EnTab_Update,
    (ActorFunc)EnTab_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE04E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE0590.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE05BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE0620.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE0664.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE06DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE0778.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE07A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE09A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE0A98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE0C04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE0D38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE0D60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE0E04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE0F04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE0FC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE1060.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE10BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE1224.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE127C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE1348.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/EnTab_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/EnTab_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/EnTab_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE1648.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE16B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/func_80BE1704.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tab/EnTab_Draw.s")
