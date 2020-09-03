#include "z_en_look_nuts.h"

#define FLAGS 0x80000000

#define THIS ((EnLookNuts*)thisx)

void EnLookNuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnLookNuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnLookNuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnLookNuts_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Look_Nuts_InitVars = {
    ACTOR_EN_LOOK_NUTS,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_DNK,
    sizeof(EnLookNuts),
    (ActorFunc)EnLookNuts_Init,
    (ActorFunc)EnLookNuts_Destroy,
    (ActorFunc)EnLookNuts_Update,
    (ActorFunc)EnLookNuts_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Look_Nuts_0x80A678B0/EnLookNuts_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Look_Nuts_0x80A678B0/EnLookNuts_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Look_Nuts_0x80A678B0/func_80A67A34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Look_Nuts_0x80A678B0/func_80A67AA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Look_Nuts_0x80A678B0/func_80A67C48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Look_Nuts_0x80A678B0/func_80A67D0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Look_Nuts_0x80A678B0/func_80A67F30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Look_Nuts_0x80A678B0/func_80A67FC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Look_Nuts_0x80A678B0/func_80A68080.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Look_Nuts_0x80A678B0/func_80A680FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Look_Nuts_0x80A678B0/EnLookNuts_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Look_Nuts_0x80A678B0/EnLookNuts_Draw.asm")
