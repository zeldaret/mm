/*
 * File: z_en_part.c
 * Overlay: ovl_En_Part
 * Description: Enemy body parts (spawned when dying)
 */

#include "z_en_part.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnPart*)thisx)

void EnPart_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPart_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPart_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPart_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Part_InitVars = {
    ACTOR_EN_PART,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnPart),
    (ActorFunc)EnPart_Init,
    (ActorFunc)EnPart_Destroy,
    (ActorFunc)EnPart_Update,
    (ActorFunc)EnPart_Draw,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Part/EnPart_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Part/EnPart_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Part/func_80865390.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Part/func_808654C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Part/EnPart_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Part/EnPart_Draw.s")
