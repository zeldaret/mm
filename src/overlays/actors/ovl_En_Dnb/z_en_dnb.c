#include "z_en_dnb.h"

#define FLAGS 0x000000B0

#define THIS ((EnDnb*)thisx)

void EnDnb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDnb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDnb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDnb_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Dnb_InitVars = {
    ACTOR_EN_DNB,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_HANAREYAMA_OBJ,
    sizeof(EnDnb),
    (ActorFunc)EnDnb_Init,
    (ActorFunc)EnDnb_Destroy,
    (ActorFunc)EnDnb_Update,
    (ActorFunc)EnDnb_Draw,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnb/func_80A4FDD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnb/func_80A4FEBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnb/func_80A4FFE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnb/func_80A500F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnb/EnDnb_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnb/EnDnb_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnb/EnDnb_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnb/func_80A50510.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnb/func_80A5063C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnb/EnDnb_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnb/func_80A507C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnb/func_80A5086C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnb/func_80A50950.s")
