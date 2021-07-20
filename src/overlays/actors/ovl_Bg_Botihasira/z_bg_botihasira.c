#include "z_bg_botihasira.h"

#define FLAGS 0x00000000

#define THIS ((BgBotihasira*)thisx)

void BgBotihasira_Init(Actor* thisx, GlobalContext* globalCtx);
void BgBotihasira_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgBotihasira_Update(Actor* thisx, GlobalContext* globalCtx);
void BgBotihasira_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit Bg_Botihasira_InitVars = {
    ACTOR_BG_BOTIHASIRA,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BOTIHASIRA,
    sizeof(BgBotihasira),
    (ActorFunc)BgBotihasira_Init,
    (ActorFunc)BgBotihasira_Destroy,
    (ActorFunc)BgBotihasira_Update,
    (ActorFunc)BgBotihasira_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B282F0 = {
    { COLTYPE_METAL, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 27, 80, 0, { 0, 0, 0 } },
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Botihasira_0x80B28080/BgBotihasira_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Botihasira_0x80B28080/BgBotihasira_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Botihasira_0x80B28080/func_80B2815C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Botihasira_0x80B28080/BgBotihasira_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Botihasira_0x80B28080/BgBotihasira_Draw.asm")
