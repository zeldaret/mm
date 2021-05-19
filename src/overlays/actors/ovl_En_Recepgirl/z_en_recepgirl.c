#include "z_en_recepgirl.h"

#define FLAGS 0x00000009

#define THIS ((EnRecepgirl*)thisx)

void EnRecepgirl_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRecepgirl_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRecepgirl_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRecepgirl_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Recepgirl_InitVars = {
    ACTOR_EN_RECEPGIRL,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BG,
    sizeof(EnRecepgirl),
    (ActorFunc)EnRecepgirl_Init,
    (ActorFunc)EnRecepgirl_Destroy,
    (ActorFunc)EnRecepgirl_Update,
    (ActorFunc)EnRecepgirl_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Recepgirl_0x80C0FFD0/EnRecepgirl_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Recepgirl_0x80C0FFD0/EnRecepgirl_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Recepgirl_0x80C0FFD0/func_80C100DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Recepgirl_0x80C0FFD0/func_80C10148.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Recepgirl_0x80C0FFD0/func_80C1019C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Recepgirl_0x80C0FFD0/func_80C10290.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Recepgirl_0x80C0FFD0/func_80C102D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Recepgirl_0x80C0FFD0/EnRecepgirl_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Recepgirl_0x80C0FFD0/func_80C10558.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Recepgirl_0x80C0FFD0/func_80C10590.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Recepgirl_0x80C0FFD0/EnRecepgirl_Draw.asm")
