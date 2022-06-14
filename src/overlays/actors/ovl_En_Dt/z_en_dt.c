/*
 * File: z_en_dt.c
 * Overlay: ovl_En_Dt
 * Description: Mayor Dotour
 */

#include "z_en_dt.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnDt*)thisx)

void EnDt_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDt_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDt_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDt_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Dt_InitVars = {
    ACTOR_EN_DT,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DT,
    sizeof(EnDt),
    (ActorFunc)EnDt_Init,
    (ActorFunc)EnDt_Destroy,
    (ActorFunc)EnDt_Update,
    (ActorFunc)EnDt_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BEB29C = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 25, 70, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80BEB29C;

extern UNK_TYPE D_0600112C;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/EnDt_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/EnDt_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BE9C74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BE9CE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BE9D9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BE9DF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BE9E94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BE9EF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEA088.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEA254.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEA394.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEA8F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEAAF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEAB44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEABF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEAC84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEAD2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEADB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEADD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/EnDt_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEB06C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/EnDt_Draw.s")
