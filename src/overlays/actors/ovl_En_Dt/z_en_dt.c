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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/EnDt_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/EnDt_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/func_80BE9C74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/func_80BE9CE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/func_80BE9D9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/func_80BE9DF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/func_80BE9E94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/func_80BE9EF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/func_80BEA088.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/func_80BEA254.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/func_80BEA394.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/func_80BEA8F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/func_80BEAAF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/func_80BEAB44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/func_80BEABF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/func_80BEAC84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/func_80BEAD2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/func_80BEADB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/func_80BEADD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/EnDt_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/func_80BEB06C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dt_0x80BE9B20/EnDt_Draw.asm")
