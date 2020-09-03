#include "z_en_guard_nuts.h"

#define FLAGS 0x80100009

#define THIS ((EnGuardNuts*)thisx)

void EnGuardNuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGuardNuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGuardNuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGuardNuts_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Guard_Nuts_InitVars = {
    ACTOR_EN_GUARD_NUTS,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_DNK,
    sizeof(EnGuardNuts),
    (ActorFunc)EnGuardNuts_Init,
    (ActorFunc)EnGuardNuts_Destroy,
    (ActorFunc)EnGuardNuts_Update,
    (ActorFunc)EnGuardNuts_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Guard_Nuts_0x80ABB0E0/EnGuardNuts_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Guard_Nuts_0x80ABB0E0/EnGuardNuts_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Guard_Nuts_0x80ABB0E0/func_80ABB210.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Guard_Nuts_0x80ABB0E0/func_80ABB29C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Guard_Nuts_0x80ABB0E0/func_80ABB2D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Guard_Nuts_0x80ABB0E0/func_80ABB540.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Guard_Nuts_0x80ABB0E0/func_80ABB590.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Guard_Nuts_0x80ABB0E0/func_80ABB854.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Guard_Nuts_0x80ABB0E0/func_80ABB91C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Guard_Nuts_0x80ABB0E0/func_80ABB990.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Guard_Nuts_0x80ABB0E0/EnGuardNuts_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Guard_Nuts_0x80ABB0E0/func_80ABBC60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Guard_Nuts_0x80ABB0E0/EnGuardNuts_Draw.asm")
