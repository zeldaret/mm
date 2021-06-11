#include "z_en_dt.h"

#define FLAGS 0x00000009

#define THIS ((EnDt*)thisx)

void EnDt_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDt_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDt_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDt_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Dt_InitVars = {
    ACTOR_EN_DT,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DT,
    sizeof(EnDt),
    (ActorFunc)EnDt_Init,
    (ActorFunc)EnDt_Destroy,
    (ActorFunc)EnDt_Update,
    (ActorFunc)EnDt_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/EnDt_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/EnDt_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BE9C74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BE9CE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BE9D9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BE9DF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BE9E94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BE9EF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEA088.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEA254.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEA394.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEA8F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEAAF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEAB44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEABF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEAC84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEAD2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEADB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEADD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/EnDt_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEB06C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/EnDt_Draw.s")
