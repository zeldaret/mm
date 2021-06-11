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
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_FIREFLY,
    sizeof(EnFirefly),
    (ActorFunc)EnFirefly_Init,
    (ActorFunc)EnFirefly_Destroy,
    (ActorFunc)EnFirefly_Update,
    (ActorFunc)EnFirefly_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/EnFirefly_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/EnFirefly_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_808798C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_80879930.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_80879950.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_8087997C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_80879A98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_80879C14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_80879CC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_80879F28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_8087A110.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_8087A1C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_8087A1EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_8087A268.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_8087A2D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_8087A50C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_8087A548.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_8087A5DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_8087A60C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_8087A774.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_8087A818.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_8087A8FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_8087A920.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_8087A9E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_8087AA1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_8087AAF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/EnFirefly_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_8087AF48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/func_8087AF98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Firefly/EnFirefly_Draw.s")
