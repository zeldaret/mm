#include "z_en_bubble.h"

#define FLAGS 0x00000001

#define THIS ((EnBubble*)thisx)

void EnBubble_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBubble_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBubble_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBubble_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bubble_InitVars = {
    ACTOR_EN_BUBBLE,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_BUBBLE,
    sizeof(EnBubble),
    (ActorFunc)EnBubble_Init,
    (ActorFunc)EnBubble_Destroy,
    (ActorFunc)EnBubble_Update,
    (ActorFunc)EnBubble_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/func_8089F4E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/func_8089F59C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/func_8089F5D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/func_8089F5F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/func_8089F660.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/func_8089F8BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/func_8089F908.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/func_8089F95C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/func_8089F9E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/func_8089FA54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/func_8089FF30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/func_8089FFCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/func_808A005C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/EnBubble_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/EnBubble_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/func_808A029C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/func_808A0350.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/func_808A03A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/func_808A03E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/EnBubble_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bubble_0x8089F4E0/EnBubble_Draw.asm")
