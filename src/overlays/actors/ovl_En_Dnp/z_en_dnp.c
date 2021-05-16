#include "z_en_dnp.h"

#define FLAGS 0x00000019

#define THIS ((EnDnp*)thisx)

void EnDnp_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDnp_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDnp_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDnp_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Dnp_InitVars = {
    ACTOR_EN_DNP,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNP,
    sizeof(EnDnp),
    (ActorFunc)EnDnp_Init,
    (ActorFunc)EnDnp_Destroy,
    (ActorFunc)EnDnp_Update,
    (ActorFunc)EnDnp_Draw
};
*/

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
