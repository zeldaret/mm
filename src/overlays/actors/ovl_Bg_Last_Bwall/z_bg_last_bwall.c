#include "z_bg_last_bwall.h"

#define FLAGS 0x00000000

#define THIS ((BgLastBwall*)thisx)

void BgLastBwall_Init(Actor* thisx, GlobalContext* globalCtx);
void BgLastBwall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgLastBwall_Update(Actor* thisx, GlobalContext* globalCtx);
void BgLastBwall_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit Bg_Last_Bwall_InitVars = {
    ACTOR_BG_LAST_BWALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_LAST_OBJ,
    sizeof(BgLastBwall),
    (ActorFunc)BgLastBwall_Init,
    (ActorFunc)BgLastBwall_Destroy,
    (ActorFunc)BgLastBwall_Update,
    (ActorFunc)BgLastBwall_Draw,
};


// static ColliderTrisElementInit sTrisElementsInit[2] = {
static ColliderTrisElementInit D_80C189C0[2] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000008, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -70.0f, 0.0f, 3.0f }, { 70.0f, 0.0f, 3.0f }, { -70.0f, 200.0f, 3.0f } } },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000008, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 70.0f, 0.0f, 3.0f }, { 70.0f, 200.0f, 3.0f }, { -70.0f, 200.0f, 3.0f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_80C18A38 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_TRIS, },
    2, D_80C189C0, // sTrisElementsInit,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80C18AC8[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/func_80C18240.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/BgLastBwall_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/BgLastBwall_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/func_80C184EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/func_80C187E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/func_80C187F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/func_80C1886C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/func_80C18884.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/func_80C188C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/func_80C18928.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/BgLastBwall_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/BgLastBwall_Draw.asm")
