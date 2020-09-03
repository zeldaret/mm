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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_DNP,
    sizeof(EnDnp),
    (ActorFunc)EnDnp_Init,
    (ActorFunc)EnDnp_Destroy,
    (ActorFunc)EnDnp_Update,
    (ActorFunc)EnDnp_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/func_80B3CA20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/func_80B3CC38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/func_80B3CC80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/func_80B3CD1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/func_80B3CDA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/func_80B3CEC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/func_80B3CF60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/func_80B3D044.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/func_80B3D11C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/func_80B3D2D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/func_80B3D338.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/func_80B3D3F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/func_80B3D47C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/func_80B3D558.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/EnDnp_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/EnDnp_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/EnDnp_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/func_80B3D974.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/func_80B3DA88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/func_80B3DAA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnp_0x80B3CA20/EnDnp_Draw.asm")
