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
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_GOROIWA,
    sizeof(EnGoroiwa),
    (ActorFunc)EnGoroiwa_Init,
    (ActorFunc)EnGoroiwa_Destroy,
    (ActorFunc)EnGoroiwa_Update,
    (ActorFunc)EnGoroiwa_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093E8A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093E91C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093E938.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093E9B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093EAB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093EAD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093EB58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093EB74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093EC50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093ECD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093ED80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093EDB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093EDD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093EE18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093EE64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093EEBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093EEDC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093EF54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093F198.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093F34C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093F498.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093F5EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093F6F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093FAA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093FC00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8093FC6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_80940090.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_80940588.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_80940A1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_80940E38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_80941060.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_80941274.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/EnGoroiwa_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/EnGoroiwa_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8094156C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_809419D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_80941A10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_80941DB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_80941E28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_80941EB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_80941F10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_80941F54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_80941FA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_80942084.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_809420F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_809421E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_8094220C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_809425CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_80942604.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/EnGoroiwa_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/func_80942B1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Goroiwa_0x8093E8A0/EnGoroiwa_Draw.asm")
