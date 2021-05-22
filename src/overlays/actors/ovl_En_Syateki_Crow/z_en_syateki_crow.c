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
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_CROW,
    sizeof(EnSyatekiCrow),
    (ActorFunc)EnSyatekiCrow_Init,
    (ActorFunc)EnSyatekiCrow_Destroy,
    (ActorFunc)EnSyatekiCrow_Update,
    (ActorFunc)EnSyatekiCrow_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Crow_0x809CA3F0/EnSyatekiCrow_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Crow_0x809CA3F0/EnSyatekiCrow_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Crow_0x809CA3F0/func_809CA5D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Crow_0x809CA3F0/func_809CA67C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Crow_0x809CA3F0/func_809CA71C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Crow_0x809CA3F0/func_809CA840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Crow_0x809CA3F0/func_809CA8E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Crow_0x809CA3F0/func_809CAAF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Crow_0x809CA3F0/func_809CABC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Crow_0x809CA3F0/func_809CACD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Crow_0x809CA3F0/EnSyatekiCrow_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Crow_0x809CA3F0/func_809CAE5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Crow_0x809CA3F0/func_809CAF2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Crow_0x809CA3F0/EnSyatekiCrow_Draw.asm")
