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
    (ActorFunc)EnPeehat_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/EnPeehat_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/EnPeehat_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897170.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_808971DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897258.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897390.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897498.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897520.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897648.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_808976DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897864.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897910.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897A34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897A94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897D00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897D48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897EAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80897F44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80898124.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80898144.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_808982E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80898338.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80898414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80898454.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_808984E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80898594.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80898654.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_808986A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_8089874C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/EnPeehat_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80898E74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/func_80899024.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Peehat_0x80896F30/EnPeehat_Draw.asm")
