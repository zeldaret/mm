#include "z_en_giant.h"

#define FLAGS 0x00000030

#define THIS ((EnGiant*)thisx)

void EnGiant_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGiant_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGiant_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGiant_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Giant_InitVars = {
    ACTOR_EN_GIANT,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GIANT,
    sizeof(EnGiant),
    (ActorFunc)EnGiant_Init,
    (ActorFunc)EnGiant_Destroy,
    (ActorFunc)EnGiant_Update,
    (ActorFunc)EnGiant_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Giant_0x80B01990/func_80B01990.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Giant_0x80B01990/func_80B01A74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Giant_0x80B01990/EnGiant_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Giant_0x80B01990/EnGiant_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Giant_0x80B01990/func_80B01E84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Giant_0x80B01990/func_80B01EE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Giant_0x80B01990/func_80B020A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Giant_0x80B01990/func_80B0211C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Giant_0x80B01990/func_80B02234.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Giant_0x80B01990/func_80B02354.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Giant_0x80B01990/func_80B023D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Giant_0x80B01990/func_80B024AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Giant_0x80B01990/func_80B024D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Giant_0x80B01990/EnGiant_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Giant_0x80B01990/func_80B02688.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Giant_0x80B01990/func_80B026C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Giant_0x80B01990/EnGiant_Draw.asm")
