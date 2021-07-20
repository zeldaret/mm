#include "z_en_warp_tag.h"

#define FLAGS 0x0A000011

#define THIS ((EnWarptag*)thisx)

void EnWarptag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWarptag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWarptag_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit En_Warp_tag_InitVars = {
    ACTOR_EN_WARP_TAG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnWarptag),
    (ActorFunc)EnWarptag_Init,
    (ActorFunc)EnWarptag_Destroy,
    (ActorFunc)EnWarptag_Update,
    (ActorFunc)NULL,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_809C1008[] = {
    ICHAIN_VEC3F(scale, 1, ICHAIN_CONTINUE),
    ICHAIN_VEC3S(shape, 0, ICHAIN_STOP),
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Warp_tag_0x809C0760/EnWarptag_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Warp_tag_0x809C0760/EnWarptag_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Warp_tag_0x809C0760/func_809C085C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Warp_tag_0x809C0760/func_809C08E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Warp_tag_0x809C0760/func_809C09A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Warp_tag_0x809C0760/func_809C0A20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Warp_tag_0x809C0760/func_809C0AB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Warp_tag_0x809C0760/func_809C0E30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Warp_tag_0x809C0760/EnWarptag_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Warp_tag_0x809C0760/func_809C0F3C.asm")
