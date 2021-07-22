#include "z_bg_spout_fire.h"

#define FLAGS 0x00000000

#define THIS ((BgSpoutFire*)thisx)

void BgSpoutFire_Init(Actor* thisx, GlobalContext* globalCtx);
void BgSpoutFire_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgSpoutFire_Update(Actor* thisx, GlobalContext* globalCtx);

#if(0)
const ActorInit Bg_Spout_Fire_InitVars = {
    ACTOR_BG_SPOUT_FIRE,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_FWALL,
    sizeof(BgSpoutFire),
    (ActorFunc)BgSpoutFire_Init,
    (ActorFunc)BgSpoutFire_Destroy,
    (ActorFunc)BgSpoutFire_Update,
    (ActorFunc)NULL,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A61160 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x20000000, 0x01, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_NONE, OCELEM_ON, },
    { 30, 83, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit D_80A6118C = { 1, 80, 100, MASS_IMMOVABLE };


extern ColliderCylinderInit D_80A61160;
extern CollisionCheckInfoInit D_80A6118C;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spout_Fire_0x80A60B20/BgSpoutFire_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spout_Fire_0x80A60B20/BgSpoutFire_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spout_Fire_0x80A60B20/func_80A60C24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spout_Fire_0x80A60B20/func_80A60C94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spout_Fire_0x80A60B20/func_80A60CDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spout_Fire_0x80A60B20/func_80A60D10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spout_Fire_0x80A60B20/func_80A60DA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spout_Fire_0x80A60B20/func_80A60E08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spout_Fire_0x80A60B20/BgSpoutFire_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spout_Fire_0x80A60B20/func_80A61040.asm")
