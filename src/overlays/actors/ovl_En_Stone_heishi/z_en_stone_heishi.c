/*
 * File: z_en_stone_heishi.c
 * Overlay: ovl_En_Stone_heishi
 * Description: Shiro
 */

#include "z_en_stone_heishi.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_80)

#define THIS ((EnStoneheishi*)thisx)

void EnStoneheishi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnStoneheishi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnStoneheishi_Update(Actor* thisx, GlobalContext* globalCtx);
void EnStoneheishi_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BC9560(EnStoneheishi* this, GlobalContext* globalCtx);
void func_80BC9680(EnStoneheishi* this, GlobalContext* globalCtx);
void func_80BC9908(EnStoneheishi* this, GlobalContext* globalCtx);
void func_80BC9A2C(EnStoneheishi* this, GlobalContext* globalCtx);
void func_80BC9D28(EnStoneheishi* this, GlobalContext* globalCtx);
void func_80BC9E50(EnStoneheishi* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Stone_heishi_InitVars = {
    ACTOR_EN_STONE_HEISHI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SDN,
    sizeof(EnStoneheishi),
    (ActorFunc)EnStoneheishi_Init,
    (ActorFunc)EnStoneheishi_Destroy,
    (ActorFunc)EnStoneheishi_Update,
    (ActorFunc)EnStoneheishi_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BCA3A0 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 15, 70, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80BCA3A0;

extern UNK_TYPE D_06000768;
extern UNK_TYPE D_06003BFC;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/EnStoneheishi_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/EnStoneheishi_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC935C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC941C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC94B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC9560.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC9660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC9680.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC98EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC9908.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC9A10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC9A2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC9C88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC9D28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC9E50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/EnStoneheishi_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BCA0AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BCA104.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/EnStoneheishi_Draw.s")
