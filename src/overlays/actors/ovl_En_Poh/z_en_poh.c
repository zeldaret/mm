#include "z_en_poh.h"

#define FLAGS 0x00001205

#define THIS ((EnPoh*)thisx)

void EnPoh_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPoh_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPoh_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPoh_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Poh_InitVars = {
    ACTOR_EN_POH,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_PO,
    sizeof(EnPoh),
    (ActorFunc)EnPoh_Init,
    (ActorFunc)EnPoh_Destroy,
    (ActorFunc)EnPoh_Update,
    (ActorFunc)EnPoh_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/EnPoh_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/EnPoh_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2C910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2C9B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2CA4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2CAA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2CB60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2CBBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2CD14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2CD64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2CEC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2CF28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2CFF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D07C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D0E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D140.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D2C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D300.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D5DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D628.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D694.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D6EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D76C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D7D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D924.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2D980.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2DAD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2DB44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2DC50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2DD2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2DDF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2E0B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2E180.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2E1D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2E230.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2E3B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2E3F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2E438.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2E55C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2E6C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2E8E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/EnPoh_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2ED14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2EDD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/EnPoh_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2F328.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Poh/func_80B2F37C.s")
