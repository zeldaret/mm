/*
 * File: z_en_stop_heishi.c
 * Overlay: ovl_En_Stop_heishi
 * Description: Clock Town - Gate-Blocking Soldier
 */

#include "z_en_stop_heishi.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnStopheishi*)thisx)

void EnStopheishi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnStopheishi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnStopheishi_Update(Actor* thisx, GlobalContext* globalCtx);
void EnStopheishi_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AE7F34(EnStopheishi* this, GlobalContext* globalCtx);
void func_80AE85C4(EnStopheishi* this, GlobalContext* globalCtx);

const ActorInit En_Stop_heishi_InitVars = {
    ACTOR_EN_STOP_HEISHI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SDN,
    sizeof(EnStopheishi),
    (ActorFunc)EnStopheishi_Init,
    (ActorFunc)EnStopheishi_Destroy,
    (ActorFunc)EnStopheishi_Update,
    (ActorFunc)EnStopheishi_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AE88B0 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 50, 260, 0, { 0, 0, 0 } },
};

s32 D_80AE88DC[] = {
    0x05160517, 0x051A0000, 0x051C0000, 0x051E0000, 0x05200521, 0x05240000, 0x05260000, 0x05280000,
    0x052A052B, 0x052E0000, 0x05300000, 0x05320000, 0x05340535, 0x05380000, 0x053A0000, 0x053C0000,
    0x05180519, 0x051B0000, 0x051D0000, 0x051F0000, 0x05220523, 0x05250000, 0x05270000, 0x05290000,
    0x052C052D, 0x052F0000, 0x05310000, 0x05330000, 0x05360537, 0x05390000, 0x053B0000, 0x053D0000,
    0x05140000, 0x05600000, 0x05620000, 0x05640000, 0x05150000, 0x05610000, 0x05630000, 0x05650000,
};

s32 D_80AE897C[] = {
    0x05400541, 0x05420000, 0x05430000, 0x05430000, 0x05470548, 0x05490000, 0x054A0000, 0x054B0000,
    0x054F0550, 0x05510000, 0x05520000, 0x05530000, 0x05570558, 0x05590000, 0x055A0000, 0x055A0000,
    0x05440545, 0x05460000, 0x05460000, 0x05460000, 0x054C054D, 0x054E0000, 0x054E0000, 0x054E0000,
    0x05540555, 0x05560000, 0x05560000, 0x05560000, 0x055B055C, 0x055D0000, 0x055D0000, 0x055D0000,
    0x053E0000, 0x053E0000, 0x053E0000, 0x053E0000, 0x053F0000, 0x053F0000, 0x053F0000, 0x053F0000,
};

s32 D_80AE8A1C[] = {
0x06004AC0,
0x06005320,
};

s32 D_80AE8A24[] = {
0x06006C18,
0x0600DC7C,
};

s32 D_80AE8A2C = 0x060057BC;

s32 D_80AE8A30[] = {
0x06005D28,
0x060064C0,
0x06000A54,
0x00000000,
};

extern ColliderCylinderInit D_80AE88B0;

extern UNK_TYPE D_06006C18;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/EnStopheishi_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/EnStopheishi_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE750C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE75C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE7718.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE77D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE795C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE7E9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE7F34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE854C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE85C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/EnStopheishi_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE87A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE87EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/EnStopheishi_Draw.s")
