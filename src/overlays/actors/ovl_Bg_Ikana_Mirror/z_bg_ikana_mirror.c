/*
 * File: z_bg_ikana_mirror.c
 * Overlay: ovl_Bg_Ikana_Mirror
 * Description: Stone Tower Temple - Mirror
 */

#include "z_bg_ikana_mirror.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgIkanaMirror*)thisx)

void BgIkanaMirror_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaMirror_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaMirror_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaMirror_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Ikana_Mirror_InitVars = {
    ACTOR_BG_IKANA_MIRROR,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_IKANA_OBJ,
    sizeof(BgIkanaMirror),
    (ActorFunc)BgIkanaMirror_Init,
    (ActorFunc)BgIkanaMirror_Destroy,
    (ActorFunc)BgIkanaMirror_Update,
    (ActorFunc)BgIkanaMirror_Draw,
};

// static ColliderTrisElementInit sTrisElementsInit[9] = {
static ColliderTrisElementInit D_80B7FF50[9] = {
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 21.600000381469727f, 13.699999809265137f }, { -25.299999237060547f, 6.0f, 8.399999618530273f }, { 25.299999237060547f, 6.0f, 8.399999618530273f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.699999809265137f }, { -25.299999237060547f, 6.0f, 8.399999618530273f }, { 0.0f, 21.600000381469727f, 13.699999809265137f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.699999809265137f }, { 0.0f, 21.600000381469727f, 13.699999809265137f }, { 25.299999237060547f, 6.0f, 8.399999618530273f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.699999809265137f }, { -25.299999237060547f, 45.0f, 8.399999618530273f }, { -25.299999237060547f, 6.0f, 8.399999618530273f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.699999809265137f }, { 25.299999237060547f, 6.0f, 8.399999618530273f }, { 25.299999237060547f, 45.0f, 8.399999618530273f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.699999809265137f }, { -17.899999618530273f, 64.0999984741211f, 8.399999618530273f }, { -25.299999237060547f, 45.0f, 8.399999618530273f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.699999809265137f }, { 25.299999237060547f, 45.0f, 8.399999618530273f }, { 17.899999618530273f, 64.0999984741211f, 8.399999618530273f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.699999809265137f }, { 0.0f, 72.0f, 8.399999618530273f }, { -17.899999618530273f, 64.0999984741211f, 8.399999618530273f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 45.0f, 13.699999809265137f }, { 17.899999618530273f, 64.0999984741211f, 8.399999618530273f }, { 0.0f, 72.0f, 8.399999618530273f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_80B8016C = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER | AC_TYPE_OTHER, OC1_NONE, OC2_NONE, COLSHAPE_TRIS, },
    9, D_80B7FF50, // sTrisElementsInit,
};

// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_80B8017C = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_OTHER, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK0, { 0x00200000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_NONE, OCELEM_NONE, },
    { { { 0.0f, 72.0f, 20.0f }, { 0.0f, 72.0f, 240.0f }, { 0.0f, 6.0f, 20.0f }, { 0.0f, 6.0f, 240.0f } } },
};

// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_80B801FC = {
    { 0x41, AT_NONE | AT_TYPE_OTHER, AC_NONE, OC1_NONE, OC2_FIRST_ONLY | OC2_UNK1 | OC2_HIT_PLAYER, 0x70, },
    { 0xC1, { 0x41A00000, 0x41, 0xA0 }, { 0xC1CA6666, 0x41, 0xA0 }, TOUCH_ON | TOUCH_HIT | TOUCH_SFX_NORMAL | TOUCH_DREW_HITMARK, BUMP_NONE | BUMP_NO_DAMAGE | BUMP_NO_SWORD_SFX | BUMP_NO_HITMARK, OCELEM_NONE, },
    { { { -1.8339854079840734e-09f, -1.8626939990440405e-09f, -1.9208972190654094e-09f }, { 221185.5625f, 0.0f, 0.003921568859368563f }, { 0.0f, 0.0f, 0.0f }, { 2.8698592549372254e-42f, 1.0761972206014595e-42f, 2.2420775429197073e-44f } } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B8021C[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 220, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

#endif

extern ColliderTrisElementInit D_80B7FF50[9];
extern ColliderTrisInit D_80B8016C;
extern ColliderQuadInit D_80B8017C;
extern ColliderQuadInit D_80B801FC;
extern InitChainEntry D_80B8021C[];

extern UNK_TYPE D_06001E18;
extern UNK_TYPE D_06002358;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Mirror/func_80B7F730.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Mirror/BgIkanaMirror_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Mirror/BgIkanaMirror_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Mirror/func_80B7FA84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Mirror/func_80B7FA9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Mirror/func_80B7FB84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Mirror/func_80B7FBA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Mirror/BgIkanaMirror_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Mirror/BgIkanaMirror_Draw.s")
