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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_TAB,
    sizeof(EnTab),
    (ActorFunc)EnTab_Init,
    (ActorFunc)EnTab_Destroy,
    (ActorFunc)EnTab_Update,
    (ActorFunc)EnTab_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE04E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE0590.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE05BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE0620.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE0664.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE06DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE0778.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE07A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE09A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE0A98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE0C04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE0D38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE0D60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE0E04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE0F04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE0FC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE1060.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE10BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE1224.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE127C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE1348.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/EnTab_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/EnTab_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/EnTab_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE1648.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE16B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/func_80BE1704.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tab_0x80BE04E0/EnTab_Draw.asm")
