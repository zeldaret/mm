/*
 * File: z_en_fall2.c
 * Overlay: ovl_En_Fall2
 * Description: "Warp Beam" from Moon's Mouth in Cutscene?
 */

#include "z_en_fall2.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnFall2*)thisx)

void EnFall2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFall2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFall2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFall2_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Fall2_InitVars = {
    ACTOR_EN_FALL2,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_FALL2,
    sizeof(EnFall2),
    (ActorFunc)EnFall2_Init,
    (ActorFunc)EnFall2_Destroy,
    (ActorFunc)EnFall2_Update,
    (ActorFunc)EnFall2_Draw,
};

#endif

extern UNK_TYPE D_06005EF4;
extern UNK_TYPE D_06005F10;
extern UNK_TYPE D_06008840;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall2/EnFall2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall2/EnFall2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall2/func_80C1B724.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall2/func_80C1B8A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall2/func_80C1B8B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall2/func_80C1B8F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall2/func_80C1B9D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall2/EnFall2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall2/EnFall2_Draw.s")
