#include "z_en_demo_heishi.h"

#define FLAGS 0x00000009

#define THIS ((EnDemoheishi*)thisx)

void EnDemoheishi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDemoheishi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDemoheishi_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDemoheishi_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit En_Demo_heishi_InitVars = {
    ACTOR_EN_DEMO_HEISHI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SDN,
    sizeof(EnDemoheishi),
    (ActorFunc)EnDemoheishi_Init,
    (ActorFunc)EnDemoheishi_Destroy,
    (ActorFunc)EnDemoheishi_Update,
    (ActorFunc)EnDemoheishi_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BE9A50 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 40, 40, 0, { 0, 0, 0 } },
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Demo_heishi_0x80BE9510/EnDemoheishi_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Demo_heishi_0x80BE9510/EnDemoheishi_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Demo_heishi_0x80BE9510/func_80BE95EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Demo_heishi_0x80BE9510/func_80BE9678.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Demo_heishi_0x80BE9510/func_80BE970C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Demo_heishi_0x80BE9510/func_80BE975C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Demo_heishi_0x80BE9510/func_80BE97F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Demo_heishi_0x80BE9510/func_80BE980C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Demo_heishi_0x80BE9510/EnDemoheishi_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Demo_heishi_0x80BE9510/func_80BE9974.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Demo_heishi_0x80BE9510/EnDemoheishi_Draw.asm")
