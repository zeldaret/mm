#include "z_en_tsn.h"

#define FLAGS 0x02000019

#define THIS ((EnTsn*)thisx)

void EnTsn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTsn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTsn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTsn_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Tsn_InitVars = {
    ACTOR_EN_TSN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TSN,
    sizeof(EnTsn),
    (ActorFunc)EnTsn_Init,
    (ActorFunc)EnTsn_Destroy,
    (ActorFunc)EnTsn_Update,
    (ActorFunc)EnTsn_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AE1190 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 30, 40, 0, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_80AE1190;
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80ADFCA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80ADFCEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/EnTsn_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/EnTsn_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80ADFF84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0010.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0304.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0418.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE04C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE04FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0698.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0704.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0C88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0D10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0D78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/EnTsn_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0F84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0FA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE1024.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/EnTsn_Draw.s")
