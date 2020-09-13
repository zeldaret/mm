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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_IN2,
    sizeof(EnGm),
    (ActorFunc)EnGm_Init,
    (ActorFunc)EnGm_Destroy,
    (ActorFunc)EnGm_Update,
    (ActorFunc)EnGm_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094DEE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094DF90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094DFF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094E054.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094E0F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094E1DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094E278.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094E2D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094E454.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094E4D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094E52C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094E69C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094EA34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094EB1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094EDBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094EE84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094EFC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094F074.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094F0E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094F2E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094F3D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094F4EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094F53C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094F7D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094F904.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094FAC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094FCC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094FD88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094FE10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8094FF04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_80950088.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_80950120.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_809501B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_80950280.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_80950388.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_809503F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_80950490.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_80950690.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_80950804.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_8095097C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_80950C24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_80950CDC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_80950DB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_80950F2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/EnGm_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/EnGm_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/EnGm_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_809513AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_809514BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/func_80951594.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gm_0x8094DEE0/EnGm_Draw.asm")
