/*
 * File: z_en_invadepoh_demo.c
 * Overlay: ovl_En_Invadepoh_Demo
 * Description:
 */

#include "z_en_invadepoh_demo.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnInvadepohDemo*)thisx)

void EnInvadepohDemo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnInvadepohDemo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnInvadepohDemo_Update(Actor* thisx, GlobalContext* globalCtx);
void EnInvadepohDemo_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C19AB4(EnInvadepohDemo* this, GlobalContext* globalCtx);
void func_80C19D00(EnInvadepohDemo* this, GlobalContext* globalCtx);
void func_80C19D48(EnInvadepohDemo* this, GlobalContext* globalCtx);
void func_80C19E04(EnInvadepohDemo* this, GlobalContext* globalCtx);
void func_80C19EC0(EnInvadepohDemo* this, GlobalContext* globalCtx);
void func_80C19F7C(EnInvadepohDemo* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Invadepoh_Demo_InitVars = {
    ACTOR_EN_INVADEPOH_DEMO,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnInvadepohDemo),
    (ActorFunc)EnInvadepohDemo_Init,
    (ActorFunc)EnInvadepohDemo_Destroy,
    (ActorFunc)EnInvadepohDemo_Update,
    (ActorFunc)EnInvadepohDemo_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80C1AA74[] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 600, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 6000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80C1AA88[] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 1500, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 6, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80C1AAA0[] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80C1AAB0[] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1000, ICHAIN_CONTINUE),
    ICHAIN_VEC3S(shape.rot, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(terminalVelocity, -100, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 800, ICHAIN_STOP),
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80C1AAC8[] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80C1AA74[];
extern InitChainEntry D_80C1AA88[];
extern InitChainEntry D_80C1AAA0[];
extern InitChainEntry D_80C1AAB0[];
extern InitChainEntry D_80C1AAC8[];

extern UNK_TYPE D_06000560;
extern UNK_TYPE D_06001D80;
extern UNK_TYPE D_06004264;
extern UNK_TYPE D_06004E98;
extern UNK_TYPE D_06011FC8;
extern UNK_TYPE D_06016588;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C192A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C192B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19334.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C193A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19454.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19498.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1950C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19548.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19564.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19590.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1965C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19688.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19754.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1985C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1987C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C199BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C199EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19AB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19D00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19D48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19E04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19EC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19F7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1A038.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1A070.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1A168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1A244.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1A590.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1A650.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1A670.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1A6C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1A854.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/EnInvadepohDemo_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/EnInvadepohDemo_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/EnInvadepohDemo_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/EnInvadepohDemo_Draw.s")
