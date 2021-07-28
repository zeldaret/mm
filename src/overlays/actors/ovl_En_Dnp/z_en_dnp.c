#include "z_en_dnp.h"

#define FLAGS 0x00000019

#define THIS ((EnDnp*)thisx)

void EnDnp_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDnp_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDnp_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDnp_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Dnp_InitVars = {
    ACTOR_EN_DNP,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNP,
    sizeof(EnDnp),
    (ActorFunc)EnDnp_Init,
    (ActorFunc)EnDnp_Destroy,
    (ActorFunc)EnDnp_Update,
    (ActorFunc)EnDnp_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B3DC80 = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 14, 38, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B3DCAC = { 0, 0, 0, 0, MASS_IMMOVABLE };


extern ColliderCylinderInit D_80B3DC80;
extern CollisionCheckInfoInit2 D_80B3DCAC;
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/func_80B3CA20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/func_80B3CC38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/func_80B3CC80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/func_80B3CD1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/func_80B3CDA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/func_80B3CEC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/func_80B3CF60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/func_80B3D044.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/func_80B3D11C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/func_80B3D2D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/func_80B3D338.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/func_80B3D3F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/func_80B3D47C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/func_80B3D558.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/EnDnp_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/EnDnp_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/EnDnp_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/func_80B3D974.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/func_80B3DA88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/func_80B3DAA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnp/EnDnp_Draw.s")
