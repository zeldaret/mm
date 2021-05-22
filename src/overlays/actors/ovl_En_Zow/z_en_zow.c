#include "z_en_zow.h"

#define FLAGS 0x00000019

#define THIS ((EnZow*)thisx)

void EnZow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZow_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Zow_InitVars = {
    ACTOR_EN_ZOW,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZO,
    sizeof(EnZow),
    (ActorFunc)EnZow_Init,
    (ActorFunc)EnZow_Destroy,
    (ActorFunc)EnZow_Update,
    (ActorFunc)EnZow_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDC270.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDC2D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDC3C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDC50C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDC5C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDC6F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDC830.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDC9DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDCB84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDCD38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDCDA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/EnZow_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/EnZow_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDD04C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDD154.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDD1E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDD350.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDD490.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDD570.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDD634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDD6BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDD79C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/EnZow_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDDA7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDDAA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/func_80BDDAE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zow_0x80BDC270/EnZow_Draw.asm")
