#include "z_en_owl.h"

#define FLAGS 0x00000019

#define THIS ((EnOwl*)thisx)

void EnOwl_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOwl_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOwl_Update(Actor* thisx, GlobalContext* globalCtx);
void EnOwl_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Owl_InitVars = {
    ACTOR_EN_OWL,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OWL,
    sizeof(EnOwl),
    (ActorFunc)EnOwl_Init,
    (ActorFunc)EnOwl_Destroy,
    (ActorFunc)EnOwl_Update,
    (ActorFunc)EnOwl_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_8095D2F0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 30, 40, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8095D31C[] = {
    ICHAIN_VEC3F_DIV1000(scale, 25, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 2400, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_8095D2F0;
extern InitChainEntry D_8095D31C[];

extern UNK_TYPE D_06001168;
extern UNK_TYPE D_06001200;
extern UNK_TYPE D_06001ADC;
extern UNK_TYPE D_0600C6D4;
extern UNK_TYPE D_0600CB94;
extern UNK_TYPE D_0600CDB0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095A510.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/EnOwl_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/EnOwl_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095A920.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095A978.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095A9FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AA70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AAD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AB1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AB4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095ABA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095ABF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AC50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095ACEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AD54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AE00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AE60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AEC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AF2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095AFEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B06C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B0C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B158.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B1E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B254.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B2F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B3DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B480.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B574.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B650.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B6C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B76C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B960.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095B9FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095BA84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095BE0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095BF20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095BF58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095BF78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095C09C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095C1C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095C258.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095C328.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095C408.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095C484.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095C510.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095C568.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/EnOwl_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095CCF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095CE18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095CF44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/EnOwl_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095D074.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Owl/func_8095D24C.s")
