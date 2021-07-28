#include "z_en_akindonuts.h"

#define FLAGS 0x00000039

#define THIS ((EnAkindonuts*)thisx)

void EnAkindonuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAkindonuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAkindonuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAkindonuts_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Akindonuts_InitVars = {
    ACTOR_EN_AKINDONUTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNT,
    sizeof(EnAkindonuts),
    (ActorFunc)EnAkindonuts_Init,
    (ActorFunc)EnAkindonuts_Destroy,
    (ActorFunc)EnAkindonuts_Update,
    (ActorFunc)EnAkindonuts_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BF02F0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_HIT_PLAYER, COLSHAPE_JNTSPH, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 27, 32, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80BF04B4[] = {
    ICHAIN_U8(targetMode, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 30, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80BF02F0;
extern InitChainEntry D_80BF04B4[];

extern UNK_TYPE D_06001350;
extern UNK_TYPE D_06005488;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BECBE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BECC7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BECD10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BECEAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BECF6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BECFBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BED034.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BED090.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BED140.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BED208.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BED27C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BED2FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BED35C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BED3BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BED680.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BED8A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEDB88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEDDAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEE070.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEE274.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEE530.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEE73C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEE938.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEEB20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEEDC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEEE10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEEFA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEF18C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEF20C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEF360.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEF450.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEF4B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEF518.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEF770.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEF83C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEF9F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEFAF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEFD74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/EnAkindonuts_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/EnAkindonuts_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/EnAkindonuts_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BEFFB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BF0178.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/func_80BF0190.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Akindonuts/EnAkindonuts_Draw.s")
