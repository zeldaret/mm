#include "z_en_gm.h"

#define FLAGS 0x00000019

#define THIS ((EnGm*)thisx)

void EnGm_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGm_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGm_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Gm_InitVars = {
    ACTOR_EN_GM,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_IN2,
    sizeof(EnGm),
    (ActorFunc)EnGm_Init,
    (ActorFunc)EnGm_Destroy,
    (ActorFunc)EnGm_Update,
    (ActorFunc)EnGm_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094DEE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094DF90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094DFF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094E054.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094E0F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094E1DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094E278.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094E2D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094E454.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094E4D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094E52C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094E69C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094EA34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094EB1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094EDBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094EE84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094EFC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094F074.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094F0E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094F2E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094F3D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094F4EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094F53C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094F7D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094F904.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094FAC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094FCC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094FD88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094FE10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8094FF04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_80950088.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_80950120.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_809501B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_80950280.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_80950388.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_809503F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_80950490.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_80950690.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_80950804.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_8095097C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_80950C24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_80950CDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_80950DB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_80950F2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/EnGm_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/EnGm_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/EnGm_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_809513AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_809514BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/func_80951594.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gm/EnGm_Draw.s")
