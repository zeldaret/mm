#include "z_bg_astr_bombwall.h"

#define FLAGS 0x00000000

#define THIS ((BgAstrBombwall*)thisx)

void BgAstrBombwall_Init(Actor* thisx, GlobalContext* globalCtx);
void BgAstrBombwall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgAstrBombwall_Update(Actor* thisx, GlobalContext* globalCtx);
void BgAstrBombwall_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Astr_Bombwall_InitVars = {
    ACTOR_BG_ASTR_BOMBWALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_ASTR_OBJ,
    sizeof(BgAstrBombwall),
    (ActorFunc)BgAstrBombwall_Init,
    (ActorFunc)BgAstrBombwall_Destroy,
    (ActorFunc)BgAstrBombwall_Update,
    (ActorFunc)BgAstrBombwall_Draw,
};


// static ColliderTrisElementInit sTrisElementsInit[2] = {
static ColliderTrisElementInit D_80C0A620[2] = {
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
static ColliderTrisInit D_80C0A698 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_TRIS, },
    2, D_80C0A620, // sTrisElementsInit,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80C0A6A8[] = {
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};


extern ColliderTrisElementInit D_80C0A620[2];
extern ColliderTrisInit D_80C0A698;
extern InitChainEntry D_80C0A6A8[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/func_80C09ED0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/BgAstrBombwall_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/BgAstrBombwall_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/func_80C0A120.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/func_80C0A378.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/func_80C0A38C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/func_80C0A400.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/func_80C0A418.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/func_80C0A458.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/func_80C0A4BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/BgAstrBombwall_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/BgAstrBombwall_Draw.asm")
