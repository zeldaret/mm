/*
 * File: z_en_scopecrow.c
 * Overlay: ovl_En_Scopecrow
 * Description: Astral Observatory - Guay in Telescope
 */

#include "z_en_scopecrow.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnScopecrow*)thisx)

void EnScopecrow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnScopecrow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnScopecrow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnScopecrow_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BCD590(EnScopecrow* this, GlobalContext* globalCtx);
void func_80BCD640(EnScopecrow* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Scopecrow_InitVars = {
    ACTOR_EN_SCOPECROW,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_CROW,
    sizeof(EnScopecrow),
    (ActorFunc)EnScopecrow_Init,
    (ActorFunc)EnScopecrow_Destroy,
    (ActorFunc)EnScopecrow_Update,
    (ActorFunc)EnScopecrow_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80BCDB70[1] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 60, 0 }, 50 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80BCDB94 = {
    { COLTYPE_HIT3, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_80BCDB70, // sJntSphElementsInit,
};

#endif

extern ColliderJntSphElementInit D_80BCDB70[1];
extern ColliderJntSphInit D_80BCDB94;

extern UNK_TYPE D_060010C0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/func_80BCD000.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/func_80BCD09C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/func_80BCD1AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/func_80BCD2BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/func_80BCD334.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/func_80BCD4D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/func_80BCD590.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/func_80BCD640.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/EnScopecrow_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/EnScopecrow_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/EnScopecrow_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/EnScopecrow_Draw.s")
