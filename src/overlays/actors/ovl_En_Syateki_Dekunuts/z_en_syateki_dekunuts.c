#include "z_en_syateki_dekunuts.h"

#define FLAGS 0x08000030

#define THIS ((EnSyatekiDekunuts*)thisx)

void EnSyatekiDekunuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiDekunuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiDekunuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiDekunuts_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit En_Syateki_Dekunuts_InitVars = {
    ACTOR_EN_SYATEKI_DEKUNUTS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DEKUNUTS,
    sizeof(EnSyatekiDekunuts),
    (ActorFunc)EnSyatekiDekunuts_Init,
    (ActorFunc)EnSyatekiDekunuts_Destroy,
    (ActorFunc)EnSyatekiDekunuts_Update,
    (ActorFunc)EnSyatekiDekunuts_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A2CAB0 = {
    { COLTYPE_HIT6, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 48, 80, 0, { 0, 0, 0 } },
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A2CB90[] = {
    ICHAIN_S8(hintId, 77, ICHAIN_CONTINUE),
    ICHAIN_F32(gravity, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2600, ICHAIN_STOP),
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/EnSyatekiDekunuts_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/EnSyatekiDekunuts_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2BE54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2BF18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2BFC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C0F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C150.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C168.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C1AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C208.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C27C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C2E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C33C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C3AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C3F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C478.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C48C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C4D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C5DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/EnSyatekiDekunuts_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C8A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts_0x80A2BC00/EnSyatekiDekunuts_Draw.asm")
