#include "z_en_invadepoh_demo.h"

#define FLAGS 0x00000010

#define THIS ((EnInvadepohDemo*)thisx)

void EnInvadepohDemo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnInvadepohDemo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnInvadepohDemo_Update(Actor* thisx, GlobalContext* globalCtx);
void EnInvadepohDemo_Draw(Actor* thisx, GlobalContext* globalCtx);

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
    ICHAIN_F32(minVelocityY, -100, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 800, ICHAIN_STOP),
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80C1AAC8[] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};


extern InitChainEntry D_80C1AA74[];
extern InitChainEntry D_80C1AA88[];
extern InitChainEntry D_80C1AAA0[];
extern InitChainEntry D_80C1AAB0[];
extern InitChainEntry D_80C1AAC8[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C192A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C192B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19334.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C193A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19454.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19498.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1950C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19548.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19564.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19590.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1965C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19688.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19754.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1985C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1987C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C199BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C199EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19AB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19D00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19D48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19E04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19EC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19F7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A038.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A070.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A168.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A244.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A590.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A650.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A670.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A6C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A854.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/EnInvadepohDemo_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/EnInvadepohDemo_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/EnInvadepohDemo_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/EnInvadepohDemo_Draw.asm")
