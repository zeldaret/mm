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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/func_80B3CA20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/func_80B3CC38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/func_80B3CC80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/func_80B3CD1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/func_80B3CDA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/func_80B3CEC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/func_80B3CF60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/func_80B3D044.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/func_80B3D11C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/func_80B3D2D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/func_80B3D338.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/func_80B3D3F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/func_80B3D47C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/func_80B3D558.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/EnDnp_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/EnDnp_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/EnDnp_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/func_80B3D974.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/func_80B3DA88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/func_80B3DAA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnp_0x80B3CA20/EnDnp_Draw.asm")
