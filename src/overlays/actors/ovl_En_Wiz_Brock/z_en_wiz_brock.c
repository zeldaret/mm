#include "z_en_wiz_brock.h"

#define FLAGS 0x08000010

#define THIS ((EnWizBrock*)thisx)

void EnWizBrock_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWizBrock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWizBrock_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWizBrock_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_Brock_0x80A48FE0/EnWizBrock_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_Brock_0x80A48FE0/EnWizBrock_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_Brock_0x80A48FE0/func_80A490E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_Brock_0x80A48FE0/func_80A490FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_Brock_0x80A48FE0/EnWizBrock_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_Brock_0x80A48FE0/EnWizBrock_Draw.asm")
