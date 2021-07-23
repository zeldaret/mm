#include "z_en_daiku.h"

#define FLAGS 0x00000009

#define THIS ((EnDaiku*)thisx)

void EnDaiku_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDaiku_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDaiku_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDaiku_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Daiku_InitVars = {
    ACTOR_EN_DAIKU,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DAIKU,
    sizeof(EnDaiku),
    (ActorFunc)EnDaiku_Init,
    (ActorFunc)EnDaiku_Destroy,
    (ActorFunc)EnDaiku_Update,
    (ActorFunc)EnDaiku_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80944078 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 20, 60, 0, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_80944078;
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku/EnDaiku_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku/EnDaiku_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku/func_8094373C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku/func_809437C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku/func_80943820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku/func_809438F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku/func_80943BC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku/func_80943BDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku/EnDaiku_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku/func_80943E18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku/func_80943E60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku/EnDaiku_Draw.s")
