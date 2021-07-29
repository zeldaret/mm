#include "z_en_gb2.h"

#define FLAGS 0x00000039

#define THIS ((EnGb2*)thisx)

void EnGb2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGb2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGb2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGb2_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B0FEBC(EnGb2* this, GlobalContext* globalCtx);
void func_80B0FFA8(EnGb2* this, GlobalContext* globalCtx);
void func_80B10240(EnGb2* this, GlobalContext* globalCtx);
void func_80B10344(EnGb2* this, GlobalContext* globalCtx);
void func_80B10584(EnGb2* this, GlobalContext* globalCtx);
void func_80B10634(EnGb2* this, GlobalContext* globalCtx);
void func_80B10868(EnGb2* this, GlobalContext* globalCtx);
void func_80B10924(EnGb2* this, GlobalContext* globalCtx);
void func_80B109DC(EnGb2* this, GlobalContext* globalCtx);
void func_80B10A48(EnGb2* this, GlobalContext* globalCtx);
void func_80B10B5C(EnGb2* this, GlobalContext* globalCtx);
void func_80B10DAC(EnGb2* this, GlobalContext* globalCtx);
void func_80B10E98(EnGb2* this, GlobalContext* globalCtx);
void func_80B11048(EnGb2* this, GlobalContext* globalCtx);
void func_80B111AC(EnGb2* this, GlobalContext* globalCtx);
void func_80B11268(EnGb2* this, GlobalContext* globalCtx);
void func_80B11344(EnGb2* this, GlobalContext* globalCtx);

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

#endif

extern ColliderCylinderInit D_80B11A40;
extern InitChainEntry D_80B11AC4[];

extern UNK_TYPE D_0600049C;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B0F5E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B0F660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B0F6DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B0F728.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B0F7FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B0F8F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B0F97C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B0FA04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B0FA48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B0FB24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B0FBF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B0FD8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B0FE18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B0FE7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B0FEBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B0FFA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B10240.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B10344.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B10584.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B10634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B10868.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B10924.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B109DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B10A48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B10B5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B10DAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B10E98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B11048.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B110F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B111AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B11268.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B11344.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/EnGb2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/EnGb2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/EnGb2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B1179C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/func_80B117FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gb2/EnGb2_Draw.s")
