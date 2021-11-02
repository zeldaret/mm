#include "z_arrow_light.h"

#define FLAGS 0x02000010

#define THIS ((ArrowLight*)thisx)

void ArrowLight_Init(Actor* thisx, GlobalContext* globalCtx);
void ArrowLight_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ArrowLight_Update(Actor* thisx, GlobalContext* globalCtx);
void ArrowLight_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809243AC(ArrowLight* this, GlobalContext* globalCtx);
void func_809244F8(ArrowLight* this, GlobalContext* globalCtx);
void func_809246C4(ArrowLight* this, GlobalContext* globalCtx);

void ArrowLight_SetupAction(ArrowLight* this, ArrowLightActionFunc actionFunc);

#if 0
const ActorInit Arrow_Light_InitVars = {
    ACTOR_ARROW_LIGHT,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ArrowLight),
    (ActorFunc)ArrowLight_Init,
    (ActorFunc)ArrowLight_Destroy,
    (ActorFunc)ArrowLight_Update,
    (ActorFunc)ArrowLight_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_809260A0[] = {
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_809260A0[];

// there are uses of D_0E000000.fillRect (appearing as D_0E0002E0) in this file
extern GfxMasterList D_0E000000;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Light/D_809260B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Light/ArrowLight_SetupAction.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Light/ArrowLight_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Light/ArrowLight_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Light/func_809243AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Light/func_809244A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Light/func_809244F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Light/func_809246C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Light/ArrowLight_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Light/ArrowLight_Draw.s")
