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
    (ActorFunc)EnGuruguru_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guruguru_0x80BC6BF0/EnGuruguru_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guruguru_0x80BC6BF0/EnGuruguru_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guruguru_0x80BC6BF0/func_80BC6D64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guruguru_0x80BC6BF0/func_80BC6E00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guruguru_0x80BC6BF0/func_80BC6E10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guruguru_0x80BC6BF0/func_80BC6F14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guruguru_0x80BC6BF0/func_80BC701C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guruguru_0x80BC6BF0/func_80BC7068.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guruguru_0x80BC6BF0/func_80BC73F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guruguru_0x80BC6BF0/func_80BC7440.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guruguru_0x80BC6BF0/func_80BC7520.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guruguru_0x80BC6BF0/EnGuruguru_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guruguru_0x80BC6BF0/func_80BC77EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guruguru_0x80BC6BF0/EnGuruguru_Draw.asm")
