#include "z_en_peehat.h"

#define FLAGS 0x00000015

#define THIS ((EnPeehat*)thisx)

void EnPeehat_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPeehat_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPeehat_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPeehat_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Peehat_InitVars = {
    ACTOR_EN_PEEHAT,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_PH,
    sizeof(EnPeehat),
    (ActorFunc)EnPeehat_Init,
    (ActorFunc)EnPeehat_Destroy,
    (ActorFunc)EnPeehat_Update,
    (ActorFunc)EnPeehat_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/EnPeehat_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/EnPeehat_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80897170.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_808971DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80897258.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80897390.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80897498.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80897520.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80897648.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_808976DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80897864.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80897910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80897A34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80897A94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80897D00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80897D48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80897EAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80897F44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80898124.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80898144.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_808982E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80898338.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80898414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80898454.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_808984E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80898594.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80898654.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_808986A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_8089874C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/EnPeehat_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80898E74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/func_80899024.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Peehat/EnPeehat_Draw.s")
