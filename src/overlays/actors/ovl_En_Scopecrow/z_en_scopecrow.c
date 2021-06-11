#include "z_en_scopecrow.h"

#define FLAGS 0x00000030

#define THIS ((EnScopecrow*)thisx)

void EnScopecrow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnScopecrow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnScopecrow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnScopecrow_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Scopecrow_InitVars = {
    ACTOR_EN_SCOPECROW,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_CROW,
    sizeof(EnScopecrow),
    (ActorFunc)EnScopecrow_Init,
    (ActorFunc)EnScopecrow_Destroy,
    (ActorFunc)EnScopecrow_Update,
    (ActorFunc)EnScopecrow_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/func_80BCD000.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/func_80BCD09C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/func_80BCD1AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/func_80BCD2BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/func_80BCD334.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/func_80BCD4D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/func_80BCD590.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/func_80BCD640.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/EnScopecrow_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/EnScopecrow_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/EnScopecrow_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopecrow/EnScopecrow_Draw.s")
