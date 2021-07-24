#include "z_bg_spdweb.h"

#define FLAGS 0x00000000

#define THIS ((BgSpdweb*)thisx)

void BgSpdweb_Init(Actor* thisx, GlobalContext* globalCtx);
void BgSpdweb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgSpdweb_Update(Actor* thisx, GlobalContext* globalCtx);
void BgSpdweb_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Spdweb_InitVars = {
    ACTOR_BG_SPDWEB,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_SPDWEB,
    sizeof(BgSpdweb),
    (ActorFunc)BgSpdweb_Init,
    (ActorFunc)BgSpdweb_Destroy,
    (ActorFunc)BgSpdweb_Update,
    (ActorFunc)BgSpdweb_Draw,
};


// static ColliderTrisElementInit sTrisElementsInit[2] = {
static ColliderTrisElementInit D_809CF080[2] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0x00000C00, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 75.0f, -8.0f, 75.0f }, { 75.0f, -8.0f, -75.0f }, { -75.0f, -8.0f, -75.0f } } },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0x00000C00, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 75.0f, -8.0f, 75.0f }, { -75.0f, -8.0f, -75.0f }, { -75.0f, -8.0f, 75.0f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_809CF0F8 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_2, COLSHAPE_TRIS, },
    2, D_809CF080, // sTrisElementsInit,
};


// static ColliderTrisElementInit sTrisElementsInit[4] = {
static ColliderTrisElementInit D_809CF108[4] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0x00000800, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 70.0f, 160.0f, 15.0f }, { -70.0f, 160.0f, 15.0f }, { -70.0f, 20.0f, 15.0f } } },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0x00000800, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 70.0f, 160.0f, 15.0f }, { -70.0f, 20.0f, 15.0f }, { 70.0f, 20.0f, 15.0f } } },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0x00000800, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -70.0f, 160.0f, -15.0f }, { 70.0f, 160.0f, -15.0f }, { 70.0f, 20.0f, -15.0f } } },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0x00000800, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -70.0f, 160.0f, -15.0f }, { 70.0f, 20.0f, -15.0f }, { -70.0f, 20.0f, -15.0f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_809CF1F8 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_2, COLSHAPE_TRIS, },
    4, D_809CF108, // sTrisElementsInit,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_809CF210[] = {
    ICHAIN_F32(uncullZoneForward, 1500, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};


extern ColliderTrisElementInit D_809CF080[2];
extern ColliderTrisInit D_809CF0F8;
extern ColliderTrisElementInit D_809CF108[4];
extern ColliderTrisInit D_809CF1F8;
extern InitChainEntry D_809CF210[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/BgSpdweb_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/BgSpdweb_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/func_809CE068.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/func_809CE15C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/func_809CE1D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/func_809CE234.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/func_809CE4C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/func_809CE830.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/func_809CEBC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/func_809CEE74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/func_809CEEAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/BgSpdweb_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/BgSpdweb_Draw.asm")
