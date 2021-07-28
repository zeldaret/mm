#include "z_en_kakasi.h"

#define FLAGS 0x02000019

#define THIS ((EnKakasi*)thisx)

void EnKakasi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKakasi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKakasi_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKakasi_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80971D80 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 20, 70, 0, { 0, 0, 0 } },
};


const ActorInit En_Kakasi_InitVars = {
    ACTOR_EN_KAKASI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_KA,
    sizeof(EnKakasi),
    (ActorFunc)EnKakasi_Init,
    (ActorFunc)EnKakasi_Destroy,
    (ActorFunc)EnKakasi_Update,
    (ActorFunc)EnKakasi_Draw,
};


extern ColliderCylinderInit D_80971D80;
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/EnKakasi_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/EnKakasi_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_8096F800.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_8096F88C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_8096F8D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_8096FA18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_8096FAAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_8096FBB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_8096FC8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_8096FCC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_8096FDE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_8096FE00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_80970008.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_8097006C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_809705E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_80970658.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_80970740.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_80970978.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_80970A10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_80970A9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_80970F20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_80970FF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_80971064.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_80971430.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_80971440.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_809714BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_80971794.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_809717D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_8097185C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_8097193C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_80971A38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_80971A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_80971AD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/EnKakasi_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/func_80971CE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kakasi/EnKakasi_Draw.s")
