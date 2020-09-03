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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_DEKUNUTS,
    sizeof(EnSyatekiDekunuts),
    (ActorFunc)EnSyatekiDekunuts_Init,
    (ActorFunc)EnSyatekiDekunuts_Destroy,
    (ActorFunc)EnSyatekiDekunuts_Update,
    (ActorFunc)EnSyatekiDekunuts_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/EnSyatekiDekunuts_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/EnSyatekiDekunuts_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2BE54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2BF18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2BFC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C0F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C150.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C168.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C1AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C208.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C27C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C2E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C33C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C3AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C3F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C478.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C48C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C4D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C5DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/EnSyatekiDekunuts_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/func_80A2C8A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Dekunuts_0x80A2BC00/EnSyatekiDekunuts_Draw.asm")
