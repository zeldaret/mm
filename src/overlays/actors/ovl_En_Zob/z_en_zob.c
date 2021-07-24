#include "z_en_zob.h"

#define FLAGS 0x00000009

#define THIS ((EnZob*)thisx)

void EnZob_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZob_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZob_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZob_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Zob_InitVars = {
    ACTOR_EN_ZOB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZOB,
    sizeof(EnZob),
    (ActorFunc)EnZob_Init,
    (ActorFunc)EnZob_Destroy,
    (ActorFunc)EnZob_Update,
    (ActorFunc)EnZob_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BA10D0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 30, 40, 0, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_80BA10D0;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/EnZob_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/EnZob_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80B9F7E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80B9F86C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80B9FA3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80B9FC0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80B9FC70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80B9FCA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80B9FD24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80B9FDDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80B9FE1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80B9FE5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80B9FF20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80B9FF80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80BA005C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80BA00BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80BA0318.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80BA0374.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80BA0610.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80BA06BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80BA0728.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80BA08E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80BA09E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80BA0A04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80BA0AD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80BA0BB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80BA0C14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80BA0CF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/EnZob_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80BA0F64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/func_80BA0FAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zob_0x80B9F570/EnZob_Draw.asm")
