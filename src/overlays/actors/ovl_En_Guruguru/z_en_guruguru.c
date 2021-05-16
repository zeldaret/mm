#include "z_en_guruguru.h"

#define FLAGS 0x00000019

#define THIS ((EnGuruguru*)thisx)

void EnGuruguru_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGuruguru_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGuruguru_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGuruguru_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Guruguru_InitVars = {
    ACTOR_EN_GURUGURU,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_FU,
    sizeof(EnGuruguru),
    (ActorFunc)EnGuruguru_Init,
    (ActorFunc)EnGuruguru_Destroy,
    (ActorFunc)EnGuruguru_Update,
    (ActorFunc)EnGuruguru_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Guruguru/EnGuruguru_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Guruguru/EnGuruguru_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Guruguru/func_80BC6D64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Guruguru/func_80BC6E00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Guruguru/func_80BC6E10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Guruguru/func_80BC6F14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Guruguru/func_80BC701C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Guruguru/func_80BC7068.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Guruguru/func_80BC73F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Guruguru/func_80BC7440.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Guruguru/func_80BC7520.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Guruguru/EnGuruguru_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Guruguru/func_80BC77EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Guruguru/EnGuruguru_Draw.s")
