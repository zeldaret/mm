#include "z_en_wood02.h"

#define FLAGS 0x00000000

#define THIS ((EnWood02*)thisx)

void EnWood02_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWood02_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWood02_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWood02_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Wood02_InitVars = {
    ACTOR_EN_WOOD02,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_WOOD02,
    sizeof(EnWood02),
    (ActorFunc)EnWood02_Init,
    (ActorFunc)EnWood02_Destroy,
    (ActorFunc)EnWood02_Update,
    (ActorFunc)EnWood02_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808C4D00 = {
    { COLTYPE_TREE, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK5, { 0x00000000, 0x00, 0x00 }, { 0x0100020A, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 18, 60, 0, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_808C4D00;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wood02_0x808C3C00/func_808C3C00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wood02_0x808C3C00/func_808C3D28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wood02_0x808C3C00/EnWood02_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wood02_0x808C3C00/EnWood02_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wood02_0x808C3C00/func_808C4458.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wood02_0x808C3C00/EnWood02_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wood02_0x808C3C00/EnWood02_Draw.asm")
