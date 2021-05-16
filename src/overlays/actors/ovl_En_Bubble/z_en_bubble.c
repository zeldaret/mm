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
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BUBBLE,
    sizeof(EnBubble),
    (ActorFunc)EnBubble_Init,
    (ActorFunc)EnBubble_Destroy,
    (ActorFunc)EnBubble_Update,
    (ActorFunc)EnBubble_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/func_8089F4E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/func_8089F59C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/func_8089F5D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/func_8089F5F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/func_8089F660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/func_8089F8BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/func_8089F908.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/func_8089F95C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/func_8089F9E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/func_8089FA54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/func_8089FF30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/func_8089FFCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/func_808A005C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/EnBubble_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/EnBubble_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/func_808A029C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/func_808A0350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/func_808A03A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/func_808A03E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/EnBubble_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bubble/EnBubble_Draw.s")
