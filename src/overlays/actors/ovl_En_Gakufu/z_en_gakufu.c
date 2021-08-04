#include "z_en_gakufu.h"

#define FLAGS 0x02000010

#define THIS ((EnGakufu*)thisx)

void EnGakufu_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGakufu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGakufu_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGakufu_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AFCB94(EnGakufu* this, GlobalContext* globalCtx);
void func_80AFCBD4(EnGakufu* this, GlobalContext* globalCtx);
void func_80AFCC14(EnGakufu* this, GlobalContext* globalCtx);
void func_80AFCD44(EnGakufu* this, GlobalContext* globalCtx);
void func_80AFCDC8(EnGakufu* this, GlobalContext* globalCtx);

#if 0
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

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gakufu/func_80AFC960.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gakufu/EnGakufu_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gakufu/EnGakufu_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gakufu/func_80AFCB94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gakufu/func_80AFCBD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gakufu/func_80AFCC14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gakufu/func_80AFCC24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gakufu/func_80AFCC58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gakufu/func_80AFCD44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gakufu/func_80AFCDC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gakufu/EnGakufu_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gakufu/EnGakufu_Draw.s")
