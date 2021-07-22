#include "z_en_guard_nuts.h"

#define FLAGS 0x80100009

#define THIS ((EnGuardNuts*)thisx)

void EnGuardNuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGuardNuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGuardNuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGuardNuts_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Guard_Nuts_InitVars = {
    ACTOR_EN_GUARD_NUTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNK,
    sizeof(EnGuardNuts),
    (ActorFunc)EnGuardNuts_Init,
    (ActorFunc)EnGuardNuts_Destroy,
    (ActorFunc)EnGuardNuts_Update,
    (ActorFunc)EnGuardNuts_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80ABBDF0 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON | OCELEM_UNK3, },
    { 50, 50, 0, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_80ABBDF0;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guard_Nuts_0x80ABB0E0/EnGuardNuts_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guard_Nuts_0x80ABB0E0/EnGuardNuts_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guard_Nuts_0x80ABB0E0/func_80ABB210.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guard_Nuts_0x80ABB0E0/func_80ABB29C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guard_Nuts_0x80ABB0E0/func_80ABB2D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guard_Nuts_0x80ABB0E0/func_80ABB540.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guard_Nuts_0x80ABB0E0/func_80ABB590.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guard_Nuts_0x80ABB0E0/func_80ABB854.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guard_Nuts_0x80ABB0E0/func_80ABB91C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guard_Nuts_0x80ABB0E0/func_80ABB990.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guard_Nuts_0x80ABB0E0/EnGuardNuts_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guard_Nuts_0x80ABB0E0/func_80ABBC60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Guard_Nuts_0x80ABB0E0/EnGuardNuts_Draw.asm")
