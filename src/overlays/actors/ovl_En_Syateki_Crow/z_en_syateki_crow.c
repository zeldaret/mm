#include "z_en_syateki_crow.h"

#define FLAGS 0x08000030

#define THIS ((EnSyatekiCrow*)thisx)

void EnSyatekiCrow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiCrow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiCrow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiCrow_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Syateki_Crow_InitVars = {
    ACTOR_EN_SYATEKI_CROW,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_CROW,
    sizeof(EnSyatekiCrow),
    (ActorFunc)EnSyatekiCrow_Init,
    (ActorFunc)EnSyatekiCrow_Destroy,
    (ActorFunc)EnSyatekiCrow_Update,
    (ActorFunc)EnSyatekiCrow_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Crow_0x809CA3F0/EnSyatekiCrow_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Crow_0x809CA3F0/EnSyatekiCrow_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Crow_0x809CA3F0/func_809CA5D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Crow_0x809CA3F0/func_809CA67C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Crow_0x809CA3F0/func_809CA71C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Crow_0x809CA3F0/func_809CA840.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Crow_0x809CA3F0/func_809CA8E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Crow_0x809CA3F0/func_809CAAF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Crow_0x809CA3F0/func_809CABC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Crow_0x809CA3F0/func_809CACD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Crow_0x809CA3F0/EnSyatekiCrow_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Crow_0x809CA3F0/func_809CAE5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Crow_0x809CA3F0/func_809CAF2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Crow_0x809CA3F0/EnSyatekiCrow_Draw.asm")
