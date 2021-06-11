#include "z_en_syateki_dekunuts.h"

#define FLAGS 0x08000030

#define THIS ((EnSyatekiDekunuts*)thisx)

void EnSyatekiDekunuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiDekunuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiDekunuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiDekunuts_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Syateki_Dekunuts_InitVars = {
    ACTOR_EN_SYATEKI_DEKUNUTS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DEKUNUTS,
    sizeof(EnSyatekiDekunuts),
    (ActorFunc)EnSyatekiDekunuts_Init,
    (ActorFunc)EnSyatekiDekunuts_Destroy,
    (ActorFunc)EnSyatekiDekunuts_Update,
    (ActorFunc)EnSyatekiDekunuts_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/EnSyatekiDekunuts_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/EnSyatekiDekunuts_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2BE54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2BF18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2BFC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C0F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C150.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C1AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C208.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C27C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C2E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C33C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C3AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C3F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C478.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C48C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C4D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C5DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/EnSyatekiDekunuts_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C8A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/EnSyatekiDekunuts_Draw.s")
