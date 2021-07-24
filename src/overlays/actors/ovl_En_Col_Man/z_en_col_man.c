#include "z_en_col_man.h"

#define FLAGS 0x00100000

#define THIS ((EnColMan*)thisx)

void EnColMan_Init(Actor* thisx, GlobalContext* globalCtx);
void EnColMan_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnColMan_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AFE730 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 10, 11, 1, { 0, 0, 0 } },
};


const ActorInit En_Col_Man_InitVars = {
    ACTOR_EN_COL_MAN,
    ACTORCAT_MISC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnColMan),
    (ActorFunc)EnColMan_Init,
    (ActorFunc)EnColMan_Destroy,
    (ActorFunc)EnColMan_Update,
    (ActorFunc)NULL,
};


extern ColliderCylinderInit D_80AFE730;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Col_Man_0x80AFDC40/EnColMan_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Col_Man_0x80AFDC40/EnColMan_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Col_Man_0x80AFDC40/func_80AFDD60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Col_Man_0x80AFDC40/func_80AFDE00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Col_Man_0x80AFDC40/func_80AFDF00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Col_Man_0x80AFDC40/func_80AFDF60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Col_Man_0x80AFDC40/func_80AFDFB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Col_Man_0x80AFDC40/func_80AFE234.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Col_Man_0x80AFDC40/func_80AFE25C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Col_Man_0x80AFDC40/EnColMan_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Col_Man_0x80AFDC40/func_80AFE414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Col_Man_0x80AFDC40/func_80AFE4AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Col_Man_0x80AFDC40/func_80AFE584.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Col_Man_0x80AFDC40/func_80AFE650.asm")
