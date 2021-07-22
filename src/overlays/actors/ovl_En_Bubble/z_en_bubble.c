#include "z_en_bubble.h"

#define FLAGS 0x00000001

#define THIS ((EnBubble*)thisx)

void EnBubble_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBubble_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBubble_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBubble_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
const ActorInit En_Bubble_InitVars = {
    ACTOR_EN_BUBBLE,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BUBBLE,
    sizeof(EnBubble),
    (ActorFunc)EnBubble_Init,
    (ActorFunc)EnBubble_Destroy,
    (ActorFunc)EnBubble_Update,
    (ActorFunc)EnBubble_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[2] = {
static ColliderJntSphElementInit D_808A0700[2] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x04 }, { 0xF7CFD757, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 16 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00002820, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_AT_INFO | BUMP_NO_DAMAGE | BUMP_NO_SWORD_SFX | BUMP_NO_HITMARK, OCELEM_NONE, },
        { 0, { { 0, 0, 0 }, 16 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_808A0748 = {
    { COLTYPE_HIT6, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    2, D_808A0700, // sJntSphElementsInit,
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_808A0758 = { 1, 2, 25, 25, MASS_IMMOVABLE };


extern ColliderJntSphElementInit D_808A0700[2];
extern ColliderJntSphInit D_808A0748;
extern CollisionCheckInfoInit2 D_808A0758;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/func_8089F4E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/func_8089F59C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/func_8089F5D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/func_8089F5F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/func_8089F660.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/func_8089F8BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/func_8089F908.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/func_8089F95C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/func_8089F9E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/func_8089FA54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/func_8089FF30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/func_8089FFCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/func_808A005C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/EnBubble_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/EnBubble_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/func_808A029C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/func_808A0350.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/func_808A03A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/func_808A03E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/EnBubble_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bubble_0x8089F4E0/EnBubble_Draw.asm")
