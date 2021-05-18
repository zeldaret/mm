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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/func_80BCD000.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/func_80BCD09C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/func_80BCD1AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/func_80BCD2BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/func_80BCD334.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/func_80BCD4D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/func_80BCD590.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/func_80BCD640.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/EnScopecrow_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/EnScopecrow_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/EnScopecrow_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/EnScopecrow_Draw.asm")
