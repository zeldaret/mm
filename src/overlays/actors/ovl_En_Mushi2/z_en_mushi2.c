#include "z_en_mushi2.h"

#define FLAGS 0x00000010

#define THIS ((EnMushi2*)thisx)

void EnMushi2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMushi2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMushi2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMushi2_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Mushi2_InitVars = {
    ACTOR_EN_MUSHI2,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnMushi2),
    (ActorFunc)EnMushi2_Init,
    (ActorFunc)EnMushi2_Destroy,
    (ActorFunc)EnMushi2_Update,
    (ActorFunc)EnMushi2_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80A6B950[1] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 5 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A6B974 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_PLAYER | OC1_TYPE_1, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_80A6B950, // sJntSphElementsInit,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A6BA04[] = {
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 700, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 20, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 20, ICHAIN_STOP),
};


extern ColliderJntSphElementInit D_80A6B950[1];
extern ColliderJntSphInit D_80A6B974;
extern InitChainEntry D_80A6BA04[];
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A687A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A68808.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A68860.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A68910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A68A78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A68B3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A68B6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A68BA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A68BC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A68C5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A68CE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A68DD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A68ED8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A68F24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A68F9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A690C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A691EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A69388.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A69424.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A69468.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A6958C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A6969C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A697C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A699E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A69AA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A69ADC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A69CE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A69D3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A69EE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A69F5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A6A024.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A6A058.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A6A094.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A6A0D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/EnMushi2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/EnMushi2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A6A300.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A6A36C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A6A508.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A6A5C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A6A794.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A6A824.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A6A984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A6A9E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A6AAA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A6AB08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A6AE14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A6AE7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A6B078.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/func_80A6B0D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/EnMushi2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mushi2/EnMushi2_Draw.s")
