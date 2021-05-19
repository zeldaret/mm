#include "z_en_gakufu.h"

#define FLAGS 0x02000010

#define THIS ((EnGakufu*)thisx)

void EnGakufu_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGakufu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGakufu_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGakufu_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Gakufu_InitVars = {
    ACTOR_EN_GAKUFU,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnGakufu),
    (ActorFunc)EnGakufu_Init,
    (ActorFunc)EnGakufu_Destroy,
    (ActorFunc)EnGakufu_Update,
    (ActorFunc)EnGakufu_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gakufu_0x80AFC960/func_80AFC960.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gakufu_0x80AFC960/EnGakufu_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gakufu_0x80AFC960/EnGakufu_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gakufu_0x80AFC960/func_80AFCB94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gakufu_0x80AFC960/func_80AFCBD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gakufu_0x80AFC960/func_80AFCC14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gakufu_0x80AFC960/func_80AFCC24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gakufu_0x80AFC960/func_80AFCC58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gakufu_0x80AFC960/func_80AFCD44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gakufu_0x80AFC960/func_80AFCDC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gakufu_0x80AFC960/EnGakufu_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gakufu_0x80AFC960/EnGakufu_Draw.asm")
