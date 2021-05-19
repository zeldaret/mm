#include "z_en_zov.h"

#define FLAGS 0x00000009

#define THIS ((EnZov*)thisx)

void EnZov_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZov_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZov_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZov_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Zov_InitVars = {
    ACTOR_EN_ZOV,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZOV,
    sizeof(EnZov),
    (ActorFunc)EnZov_Init,
    (ActorFunc)EnZov_Destroy,
    (ActorFunc)EnZov_Update,
    (ActorFunc)EnZov_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/EnZov_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/EnZov_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD13DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1440.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1470.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1570.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD15A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD160C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1764.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD187C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD19FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1AE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1BF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1C38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1C84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1D30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1D94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1DB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1F1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1FC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/EnZov_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD2380.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD2404.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/EnZov_Draw.asm")
