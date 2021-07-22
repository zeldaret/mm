#include "z_en_muto.h"

#define FLAGS 0x00000009

#define THIS ((EnMuto*)thisx)

void EnMuto_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMuto_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMuto_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMuto_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Muto_InitVars = {
    ACTOR_EN_MUTO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TORYO,
    sizeof(EnMuto),
    (ActorFunc)EnMuto_Init,
    (ActorFunc)EnMuto_Destroy,
    (ActorFunc)EnMuto_Update,
    (ActorFunc)EnMuto_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BE841C = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 20, 60, 0, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_80BE841C;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Muto_0x80BE7B00/EnMuto_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Muto_0x80BE7B00/EnMuto_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Muto_0x80BE7B00/func_80BE7C94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Muto_0x80BE7B00/func_80BE7D20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Muto_0x80BE7B00/func_80BE7DB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Muto_0x80BE7B00/func_80BE7DEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Muto_0x80BE7B00/func_80BE7F88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Muto_0x80BE7B00/func_80BE7FEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Muto_0x80BE7B00/EnMuto_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Muto_0x80BE7B00/func_80BE8328.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Muto_0x80BE7B00/EnMuto_Draw.asm")
