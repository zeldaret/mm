/*
 * File: z_en_twig.c
 * Overlay: ovl_En_Twig
 * Description: Beaver Race Ring
 */

#include "z_en_twig.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnTwig*)thisx)

void EnTwig_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTwig_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTwig_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTwig_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Twig_InitVars = {
    ACTOR_EN_TWIG,
    ACTORCAT_MISC,
    FLAGS,
    OBJECT_TWIG,
    sizeof(EnTwig),
    (ActorFunc)EnTwig_Init,
    (ActorFunc)EnTwig_Destroy,
    (ActorFunc)EnTwig_Update,
    (ActorFunc)EnTwig_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AC10C0[] = {
    ICHAIN_F32(uncullZoneScale, 40, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 40, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80AC10C0[];

extern UNK_TYPE D_06001C38;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Twig/EnTwig_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Twig/EnTwig_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Twig/func_80AC0A54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Twig/func_80AC0A6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Twig/func_80AC0A7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Twig/func_80AC0AC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Twig/func_80AC0CC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Twig/func_80AC0D2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Twig/EnTwig_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Twig/EnTwig_Draw.s")
