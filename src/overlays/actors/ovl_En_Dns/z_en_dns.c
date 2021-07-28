#include "z_en_dns.h"

#define FLAGS 0x00000019

#define THIS ((EnDns*)thisx)

void EnDns_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDns_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDns_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDns_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Dns_InitVars = {
    ACTOR_EN_DNS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNS,
    sizeof(EnDns),
    (ActorFunc)EnDns_Init,
    (ActorFunc)EnDns_Destroy,
    (ActorFunc)EnDns_Update,
    (ActorFunc)EnDns_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_8092DD28 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 18, 46, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_8092DD54 = { 1, 0, 0, 0, MASS_IMMOVABLE };


extern ColliderCylinderInit D_8092DD28;
extern CollisionCheckInfoInit2 D_8092DD54;
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092C5C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092C63C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092C6FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092C740.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092C86C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092C934.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092C9BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092CA74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092CAD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092CB98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092CC68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092CCEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092CE38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092D068.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092D108.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092D1B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092D320.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092D330.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092D4D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092D5E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/EnDns_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/EnDns_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/EnDns_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092D954.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092DA68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/func_8092DA94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dns/EnDns_Draw.s")
