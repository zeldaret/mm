#include "z_en_goroiwa.h"

#define FLAGS 0x80000010

#define THIS ((EnGoroiwa*)thisx)

void EnGoroiwa_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGoroiwa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGoroiwa_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGoroiwa_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Goroiwa_InitVars = {
    ACTOR_EN_GOROIWA,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_GOROIWA,
    sizeof(EnGoroiwa),
    (ActorFunc)EnGoroiwa_Init,
    (ActorFunc)EnGoroiwa_Destroy,
    (ActorFunc)EnGoroiwa_Update,
    (ActorFunc)EnGoroiwa_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093E8A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093E91C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093E938.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093E9B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093EAB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093EAD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093EB58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093EB74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093EC50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093ECD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093ED80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093EDB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093EDD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093EE18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093EE64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093EEBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093EEDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093EF54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093F198.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093F34C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093F498.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093F5EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093F6F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093FAA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093FC00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8093FC6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_80940090.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_80940588.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_80940A1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_80940E38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_80941060.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_80941274.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/EnGoroiwa_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/EnGoroiwa_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8094156C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_809419D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_80941A10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_80941DB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_80941E28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_80941EB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_80941F10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_80941F54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_80941FA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_80942084.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_809420F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_809421E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_8094220C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_809425CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_80942604.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/EnGoroiwa_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/func_80942B1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Goroiwa_0x8093E8A0/EnGoroiwa_Draw.asm")
