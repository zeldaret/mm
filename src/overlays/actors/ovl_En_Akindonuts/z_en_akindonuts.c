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


extern ColliderCylinderInit D_80BF02F0;
extern InitChainEntry D_80BF04B4[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BECBE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BECC7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BECD10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BECEAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BECF6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BECFBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BED034.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BED090.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BED140.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BED208.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BED27C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BED2FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BED35C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BED3BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BED680.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BED8A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEDB88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEDDAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEE070.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEE274.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEE530.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEE73C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEE938.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEEB20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEEDC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEEE10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEEFA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEF18C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEF20C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEF360.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEF450.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEF4B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEF518.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEF770.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEF83C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEF9F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEFAF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEFD74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/EnAkindonuts_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/EnAkindonuts_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/EnAkindonuts_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BEFFB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BF0178.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/func_80BF0190.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Akindonuts_0x80BECBE0/EnAkindonuts_Draw.asm")
