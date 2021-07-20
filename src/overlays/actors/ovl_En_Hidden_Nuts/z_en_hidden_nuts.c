#include "z_en_hidden_nuts.h"

#define FLAGS 0x02000009

#define THIS ((EnHiddenNuts*)thisx)

void EnHiddenNuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHiddenNuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHiddenNuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHiddenNuts_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit En_Hidden_Nuts_InitVars = {
    ACTOR_EN_HIDDEN_NUTS,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_HINTNUTS,
    sizeof(EnHiddenNuts),
    (ActorFunc)EnHiddenNuts_Init,
    (ActorFunc)EnHiddenNuts_Destroy,
    (ActorFunc)EnHiddenNuts_Update,
    (ActorFunc)EnHiddenNuts_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BDC0D0 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 30, 20, 0, { 0, 0, 0 } },
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hidden_Nuts_0x80BDB040/EnHiddenNuts_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hidden_Nuts_0x80BDB040/EnHiddenNuts_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hidden_Nuts_0x80BDB040/func_80BDB1B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hidden_Nuts_0x80BDB040/func_80BDB268.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hidden_Nuts_0x80BDB040/func_80BDB2B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hidden_Nuts_0x80BDB040/func_80BDB580.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hidden_Nuts_0x80BDB040/func_80BDB59C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hidden_Nuts_0x80BDB040/func_80BDB788.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hidden_Nuts_0x80BDB040/func_80BDB7E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hidden_Nuts_0x80BDB040/func_80BDB8F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hidden_Nuts_0x80BDB040/func_80BDB930.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hidden_Nuts_0x80BDB040/func_80BDB978.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hidden_Nuts_0x80BDB040/func_80BDBA28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hidden_Nuts_0x80BDB040/func_80BDBB48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hidden_Nuts_0x80BDB040/func_80BDBE70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hidden_Nuts_0x80BDB040/func_80BDBED4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hidden_Nuts_0x80BDB040/EnHiddenNuts_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hidden_Nuts_0x80BDB040/EnHiddenNuts_Draw.asm")
