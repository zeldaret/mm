/*
 * File: z_en_dai.c
 * Overlay: ovl_En_Dai
 * Description: Biggoron
 */

#include "z_en_dai.h"

#define FLAGS 0x02000039

#define THIS ((EnDai*)thisx)

void EnDai_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDai_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDai_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDai_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B3EE8C(EnDai* this, GlobalContext* globalCtx);
void func_80B3EF90(EnDai* this, GlobalContext* globalCtx);
void func_80B3F00C(EnDai* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Dai_InitVars = {
    ACTOR_EN_DAI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DAI,
    sizeof(EnDai),
    (ActorFunc)EnDai_Init,
    (ActorFunc)EnDai_Destroy,
    (ActorFunc)EnDai_Update,
    (ActorFunc)EnDai_Draw,
};

#endif

extern UNK_TYPE D_060002E8;
extern UNK_TYPE D_0600C538;
extern UNK_TYPE D_060130D0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3DFF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3E168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3E460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3E5B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3E5DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3E69C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3E7C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3E834.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3E8BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3E96C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3EC10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3EC84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3ED88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3EE8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3EEDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3EF90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3F00C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3F044.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/EnDai_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/EnDai_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/EnDai_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3F598.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3F614.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3F6EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3F78C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/func_80B3F920.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dai/EnDai_Draw.s")
