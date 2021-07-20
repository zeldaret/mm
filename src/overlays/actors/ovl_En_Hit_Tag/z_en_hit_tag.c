#include "z_en_hit_tag.h"

#define FLAGS 0x00000010

#define THIS ((EnHitTag*)thisx)

void EnHitTag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHitTag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHitTag_Update(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit En_Hit_Tag_InitVars = {
    ACTOR_EN_HIT_TAG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnHitTag),
    (ActorFunc)EnHitTag_Init,
    (ActorFunc)EnHitTag_Destroy,
    (ActorFunc)EnHitTag_Update,
    (ActorFunc)NULL,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BE21F0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 16, 32, 0, { 0, 0, 0 } },
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hit_Tag_0x80BE2030/EnHitTag_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hit_Tag_0x80BE2030/EnHitTag_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hit_Tag_0x80BE2030/func_80BE20E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hit_Tag_0x80BE2030/EnHitTag_Update.asm")
