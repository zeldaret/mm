#include "z_en_heishi.h"

#define FLAGS 0x00000009

#define THIS ((EnHeishi*)thisx)

void EnHeishi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHeishi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHeishi_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHeishi_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Heishi_InitVars = {
    ACTOR_EN_HEISHI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SDN,
    sizeof(EnHeishi),
    (ActorFunc)EnHeishi_Init,
    (ActorFunc)EnHeishi_Destroy,
    (ActorFunc)EnHeishi_Update,
    (ActorFunc)EnHeishi_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Heishi/EnHeishi_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Heishi/EnHeishi_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Heishi/func_80BE90BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Heishi/func_80BE9148.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Heishi/func_80BE91DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Heishi/func_80BE9214.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Heishi/EnHeishi_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Heishi/func_80BE9380.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Heishi/EnHeishi_Draw.s")
