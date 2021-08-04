#include "z_en_arrow.h"

#define FLAGS 0x00000030

#define THIS ((EnArrow*)thisx)

void EnArrow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnArrow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnArrow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnArrow_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_8088A594(EnArrow* this, GlobalContext* globalCtx);
void func_8088ACE0(EnArrow* this, GlobalContext* globalCtx);
void func_8088B630(EnArrow* this, GlobalContext* globalCtx);
void func_8088B6B0(EnArrow* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Arrow_InitVars = {
    ACTOR_EN_ARROW,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnArrow),
    (ActorFunc)EnArrow_Init,
    (ActorFunc)EnArrow_Destroy,
    (ActorFunc)EnArrow_Update,
    (ActorFunc)EnArrow_Draw,
};

// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_8088C1E0 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_PLAYER, AC_NONE, OC1_NONE, OC2_TYPE_PLAYER, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK2, { 0x00000020, 0x00, 0x02 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_NEAREST | TOUCH_SFX_NONE, BUMP_NONE, OCELEM_NONE, },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8088C230[] = {
    ICHAIN_F32(minVelocityY, -150, ICHAIN_STOP),
};

#endif

extern ColliderQuadInit D_8088C1E0;
extern InitChainEntry D_8088C230[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/EnArrow_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/EnArrow_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/func_8088A514.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/func_8088A594.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/func_8088A7D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/func_8088A894.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/func_8088AA98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/func_8088ACE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/func_8088B630.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/func_8088B6B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/EnArrow_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/func_8088B88C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/EnArrow_Draw.s")
