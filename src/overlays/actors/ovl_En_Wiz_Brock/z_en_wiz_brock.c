/*
 * File: z_en_wiz_brock.c
 * Overlay: ovl_En_Wiz_Brock
 * Description: Wizzrobe Warp Platform
 */

#include "z_en_wiz_brock.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_8000000)

#define THIS ((EnWizBrock*)thisx)

void EnWizBrock_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWizBrock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWizBrock_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWizBrock_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Wiz_Brock_InitVars = {
    ACTOR_EN_WIZ_BROCK,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_WIZ,
    sizeof(EnWizBrock),
    (ActorFunc)EnWizBrock_Init,
    (ActorFunc)EnWizBrock_Destroy,
    (ActorFunc)EnWizBrock_Update,
    (ActorFunc)EnWizBrock_Draw,
};

#endif

extern UNK_TYPE D_060010E8;
extern UNK_TYPE D_06001690;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Brock/EnWizBrock_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Brock/EnWizBrock_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Brock/func_80A490E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Brock/func_80A490FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Brock/EnWizBrock_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Brock/EnWizBrock_Draw.s")
