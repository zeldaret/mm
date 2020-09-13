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

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/EnFirefly_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/EnFirefly_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_808798C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_80879930.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_80879950.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087997C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_80879A98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_80879C14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_80879CC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_80879F28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A110.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A1C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A1EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A268.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A2D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A50C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A548.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A5DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A60C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A774.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A818.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A8FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A920.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087A9E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087AA1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087AAF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/EnFirefly_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087AF48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/func_8087AF98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Firefly_0x808796F0/EnFirefly_Draw.asm")
