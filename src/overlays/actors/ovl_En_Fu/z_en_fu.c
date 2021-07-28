#include "z_en_fu.h"

#define FLAGS 0x0A000019

#define THIS ((EnFu*)thisx)

void EnFu_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFu_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFu_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Fu_InitVars = {
    ACTOR_EN_FU,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MU,
    sizeof(EnFu),
    (ActorFunc)EnFu_Init,
    (ActorFunc)EnFu_Destroy,
    (ActorFunc)EnFu_Update,
    (ActorFunc)EnFu_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80964BD8 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 50, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80964BD8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_809616E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_809619D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/EnFu_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/EnFu_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80961D10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80961D7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80961E88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80961EC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80961F00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80961F38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_8096209C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_809622FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80962340.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80962588.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80962660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_809628BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_809628D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_809629F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80962A10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80962BA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80962BCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80962D48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80962D60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80962EBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80962F10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80962F4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80963258.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_8096326C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_809632D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80963350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80963540.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80963560.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80963610.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80963630.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80963810.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_809638F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_809639D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80963DE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80963EAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80963F44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80963F88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80963FF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80964034.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_809640D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_8096413C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80964190.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_8096426C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_809642E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/EnFu_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_809643FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_8096450C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/EnFu_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80964694.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_809647EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu/func_80964950.s")
