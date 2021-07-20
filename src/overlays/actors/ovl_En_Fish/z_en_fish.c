#include "z_en_fish.h"

#define FLAGS 0x00000000

#define THIS ((EnFish*)thisx)

void EnFish_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFish_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFish_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFish_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_8091FA60[1] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 5 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_8091FA84 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_8091FA60, // sJntSphElementsInit,
};


const ActorInit En_Fish_InitVars = {
    ACTOR_EN_FISH,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnFish),
    (ActorFunc)EnFish_Init,
    (ActorFunc)EnFish_Destroy,
    (ActorFunc)EnFish_Update,
    (ActorFunc)EnFish_Draw,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8091FAC0[] = {
    ICHAIN_F32(uncullZoneForward, 720, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 40, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 40, ICHAIN_STOP),
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091D630.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091D660.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091D6C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091D728.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091D7C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091D840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091D904.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091D944.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091DA14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/EnFish_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/EnFish_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091DD48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091DDF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091DEE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091DF68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091E070.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091E128.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091E2E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091E34C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091E5EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091E658.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091E810.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091E880.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091E9A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091EAF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091ECF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091ED70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091EF30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091EFE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091F344.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091F3BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091F5A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091F830.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/EnFish_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091F994.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/EnFish_Draw.asm")
