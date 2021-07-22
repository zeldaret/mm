#include "z_en_stop_heishi.h"

#define FLAGS 0x00000009

#define THIS ((EnStopheishi*)thisx)

void EnStopheishi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnStopheishi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnStopheishi_Update(Actor* thisx, GlobalContext* globalCtx);
void EnStopheishi_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
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
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 50, 260, 0, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_80AE88B0;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stop_heishi_0x80AE73A0/EnStopheishi_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stop_heishi_0x80AE73A0/EnStopheishi_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stop_heishi_0x80AE73A0/func_80AE750C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stop_heishi_0x80AE73A0/func_80AE75C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stop_heishi_0x80AE73A0/func_80AE7718.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stop_heishi_0x80AE73A0/func_80AE77D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stop_heishi_0x80AE73A0/func_80AE795C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stop_heishi_0x80AE73A0/func_80AE7E9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stop_heishi_0x80AE73A0/func_80AE7F34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stop_heishi_0x80AE73A0/func_80AE854C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stop_heishi_0x80AE73A0/func_80AE85C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stop_heishi_0x80AE73A0/EnStopheishi_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stop_heishi_0x80AE73A0/func_80AE87A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stop_heishi_0x80AE73A0/func_80AE87EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stop_heishi_0x80AE73A0/EnStopheishi_Draw.asm")
