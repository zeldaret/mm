#include "z_en_gb2.h"

#define FLAGS 0x00000039

#define THIS ((EnGb2*)thisx)

void EnGb2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGb2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGb2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGb2_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Gb2_InitVars = {
    ACTOR_EN_GB2,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_PS,
    sizeof(EnGb2),
    (ActorFunc)EnGb2_Init,
    (ActorFunc)EnGb2_Destroy,
    (ActorFunc)EnGb2_Update,
    (ActorFunc)EnGb2_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B11A40 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_HIT_PLAYER, COLSHAPE_JNTSPH, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 40, 75, 0, { 0, 0, 0 } },
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B11AC4[] = {
    ICHAIN_U8(targetMode, 4, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2200, ICHAIN_STOP),
};


extern ColliderCylinderInit D_80B11A40;
extern InitChainEntry D_80B11AC4[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B0F5E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B0F660.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B0F6DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B0F728.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B0F7FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B0F8F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B0F97C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B0FA04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B0FA48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B0FB24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B0FBF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B0FD8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B0FE18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B0FE7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B0FEBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B0FFA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B10240.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B10344.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B10584.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B10634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B10868.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B10924.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B109DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B10A48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B10B5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B10DAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B10E98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B11048.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B110F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B111AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B11268.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B11344.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/EnGb2_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/EnGb2_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/EnGb2_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B1179C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/func_80B117FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gb2_0x80B0F5E0/EnGb2_Draw.asm")
