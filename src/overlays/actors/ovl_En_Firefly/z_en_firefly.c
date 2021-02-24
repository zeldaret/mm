#include "z_en_firefly.h"

#define FLAGS 0x00005005

#define THIS ((EnFirefly*)thisx)

void EnFirefly_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFirefly_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFirefly_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFirefly_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Firefly_InitVars = {
    ACTOR_EN_FIREFLY,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_FIREFLY,
    sizeof(EnFirefly),
    (ActorFunc)EnFirefly_Init,
    (ActorFunc)EnFirefly_Destroy,
    (ActorFunc)EnFirefly_Update,
    (ActorFunc)EnFirefly_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/EnFirefly_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/EnFirefly_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_808798C4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_80879930.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_80879950.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087997C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_80879A98.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_80879C14.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_80879CC0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_80879F28.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A110.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A1C8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A1EC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A268.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A2D8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A50C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A548.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A5DC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A60C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A774.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A818.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A8FC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A920.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A9E0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087AA1C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087AAF4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/EnFirefly_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087AF48.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087AF98.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/EnFirefly_Draw.asm")
