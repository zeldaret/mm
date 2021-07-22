#include "z_en_mk.h"

#define FLAGS 0x00000019

#define THIS ((EnMk*)thisx)

void EnMk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMk_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMk_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
const ActorInit En_Mk_InitVars = {
    ACTOR_EN_MK,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MK,
    sizeof(EnMk),
    (ActorFunc)EnMk_Init,
    (ActorFunc)EnMk_Destroy,
    (ActorFunc)EnMk_Update,
    (ActorFunc)EnMk_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_8095A260 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 30, 40, 0, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_8095A260;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mk_0x809592E0/func_809592E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mk_0x809592E0/EnMk_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mk_0x809592E0/EnMk_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mk_0x809592E0/func_80959524.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mk_0x809592E0/func_8095954C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mk_0x809592E0/func_80959624.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mk_0x809592E0/func_809596A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mk_0x809592E0/func_80959774.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mk_0x809592E0/func_80959844.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mk_0x809592E0/func_80959A24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mk_0x809592E0/func_80959C94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mk_0x809592E0/func_80959D28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mk_0x809592E0/func_80959E18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mk_0x809592E0/EnMk_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mk_0x809592E0/func_8095A150.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mk_0x809592E0/func_8095A198.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mk_0x809592E0/EnMk_Draw.asm")
