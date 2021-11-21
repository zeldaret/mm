/*
 * File: z_en_drs.c
 * Overlay: ovl_En_Drs
 * Description: Wedding dress manequin
 */

#include "z_en_drs.h"

#define FLAGS 0x00000000

#define THIS ((EnDrs*)thisx)

void EnDrs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDrs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDrs_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80C1E2D4(EnDrs* this, GlobalContext* globalCtx);
void func_80C1E3DC(EnDrs* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Drs_InitVars = {
    ACTOR_EN_DRS,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_DRS,
    sizeof(EnDrs),
    (ActorFunc)EnDrs_Init,
    (ActorFunc)EnDrs_Destroy,
    (ActorFunc)EnDrs_Update,
    (ActorFunc)NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80C1E5E0 = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 16, 62, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80C1E60C = { 0, 0, 0, 0, MASS_IMMOVABLE };

#endif

extern ColliderCylinderInit D_80C1E5E0;
extern CollisionCheckInfoInit2 D_80C1E60C;

extern UNK_TYPE D_06000E70;
extern UNK_TYPE D_06005A78;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Drs/func_80C1E290.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Drs/func_80C1E2D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Drs/func_80C1E3DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Drs/EnDrs_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Drs/EnDrs_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Drs/EnDrs_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Drs/func_80C1E4B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Drs/func_80C1E568.s")
