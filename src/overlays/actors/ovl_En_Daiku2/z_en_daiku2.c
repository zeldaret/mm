#include "z_en_daiku2.h"

#define FLAGS 0x00000009

#define THIS ((EnDaiku2*)thisx)

void EnDaiku2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDaiku2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDaiku2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDaiku2_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Daiku2_InitVars = {
    ACTOR_EN_DAIKU2,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DAIKU,
    sizeof(EnDaiku2),
    (ActorFunc)EnDaiku2_Init,
    (ActorFunc)EnDaiku2_Destroy,
    (ActorFunc)EnDaiku2_Update,
    (ActorFunc)EnDaiku2_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BE7900 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 20, 60, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80BE7900;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/func_80BE61D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/EnDaiku2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/EnDaiku2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/func_80BE6408.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/func_80BE64C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/func_80BE65B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/func_80BE66E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/func_80BE6B40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/func_80BE6BC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/func_80BE6CFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/func_80BE6D40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/func_80BE6EB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/func_80BE6EF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/func_80BE71A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/func_80BE71D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/EnDaiku2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/func_80BE738C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/EnDaiku2_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/func_80BE7504.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/func_80BE7600.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Daiku2/func_80BE7718.s")
