#include "z_en_syateki_crow.h"

#define FLAGS 0x08000030

#define THIS ((EnSyatekiCrow*)thisx)

void EnSyatekiCrow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiCrow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiCrow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiCrow_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Syateki_Crow_InitVars = {
    ACTOR_EN_SYATEKI_CROW,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_CROW,
    sizeof(EnSyatekiCrow),
    (ActorFunc)EnSyatekiCrow_Init,
    (ActorFunc)EnSyatekiCrow_Destroy,
    (ActorFunc)EnSyatekiCrow_Update,
    (ActorFunc)EnSyatekiCrow_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_809CB07C[1] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 60, 0 }, 50 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809CB0A0 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_809CB07C, // sJntSphElementsInit,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_809CB0B0[] = {
    ICHAIN_F32(uncullZoneScale, 3000, ICHAIN_CONTINUE),
    ICHAIN_S8(hintId, 88, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -500, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_STOP),
};


extern ColliderJntSphElementInit D_809CB07C[1];
extern ColliderJntSphInit D_809CB0A0;
extern InitChainEntry D_809CB0B0[];
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/EnSyatekiCrow_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/EnSyatekiCrow_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/func_809CA5D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/func_809CA67C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/func_809CA71C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/func_809CA840.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/func_809CA8E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/func_809CAAF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/func_809CABC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/func_809CACD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/EnSyatekiCrow_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/func_809CAE5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/func_809CAF2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/EnSyatekiCrow_Draw.s")
