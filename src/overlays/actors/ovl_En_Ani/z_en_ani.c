#include "z_en_ani.h"

#define FLAGS 0x00000009

#define THIS ((EnAni*)thisx)

void EnAni_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAni_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAni_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAni_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Ani_InitVars = {
    ACTOR_EN_ANI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ANI,
    sizeof(EnAni),
    (ActorFunc)EnAni_Init,
    (ActorFunc)EnAni_Destroy,
    (ActorFunc)EnAni_Update,
    (ActorFunc)EnAni_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80968670 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 30, 40, 0, { 0, 0, 0 } },
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8096869C[] = {
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 850, ICHAIN_STOP),
};


extern ColliderCylinderInit D_80968670;
extern InitChainEntry D_8096869C[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ani_0x809679D0/func_809679D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ani_0x809679D0/func_80967A48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ani_0x809679D0/func_80967AB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ani_0x809679D0/EnAni_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ani_0x809679D0/EnAni_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ani_0x809679D0/func_80967D20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ani_0x809679D0/func_80967DA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ani_0x809679D0/func_80967DCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ani_0x809679D0/func_80967E34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ani_0x809679D0/func_80967E90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ani_0x809679D0/func_80967F20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ani_0x809679D0/func_80967FA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ani_0x809679D0/func_809680B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ani_0x809679D0/func_80968164.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ani_0x809679D0/EnAni_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ani_0x809679D0/func_80968504.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ani_0x809679D0/func_8096854C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ani_0x809679D0/EnAni_Draw.asm")
