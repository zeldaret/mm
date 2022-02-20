/*
 * File: z_en_mnk.c
 * Overlay: ovl_En_Mnk
 * Description: Monkey
 */

#include "z_en_mnk.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnMnk*)thisx)

void EnMnk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMnk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMnk_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMnk_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Mnk_InitVars = {
    ACTOR_EN_MNK,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MNK,
    sizeof(EnMnk),
    (ActorFunc)EnMnk_Init,
    (ActorFunc)EnMnk_Destroy,
    (ActorFunc)EnMnk_Update,
    (ActorFunc)EnMnk_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AB9D10 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x01000200, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 15, 30, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80AB9D10;

extern UNK_TYPE D_06003584;
extern UNK_TYPE D_060082C8;
extern UNK_TYPE D_06008814;
extern UNK_TYPE D_06009CC0;
extern UNK_TYPE D_060105DC;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB4D10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB4E34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB4E58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB4E88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB4F68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB4F8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB50B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB50D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB5148.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB51C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB52E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/EnMnk_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/EnMnk_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB5A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB5B38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB5B84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB5BCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB5C14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB5C74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB5CD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB5F6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB60FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB61E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB6304.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB63CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB64B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB65F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB675C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB6870.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB6920.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB69C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB6AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB6B78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB6BE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB6E08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB6EB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB6F98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB7108.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB7204.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB72BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB7354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB740C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB7488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB7504.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB75A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB7620.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB76B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB794C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB7AC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB7B20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB7DCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB7E50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB8040.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB80BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB81D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB8478.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB852C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB85C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB8644.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB86AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB8750.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB8878.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB8968.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB89F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB8A74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB8B18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB8BD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB8C60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB8CFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB8E4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB8EF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB8FD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB9084.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB92CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB94E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/EnMnk_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB96A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB96E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB9708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB973C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB977C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB97B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB99D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/EnMnk_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB9BAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mnk/func_80AB9C4C.s")
