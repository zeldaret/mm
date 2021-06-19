#include "z_en_mag.h"

#define FLAGS 0x00000030

#define THIS ((EnMag*)thisx)

void EnMag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMag_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMag_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Mag_InitVars = {
    ACTOR_EN_MAG,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_MAG,
    sizeof(EnMag),
    (ActorFunc)EnMag_Init,
    (ActorFunc)EnMag_Destroy,
    (ActorFunc)EnMag_Update,
    (ActorFunc)EnMag_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mag_0x8096B310/EnMag_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mag_0x8096B310/EnMag_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mag_0x8096B310/func_8096B604.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mag_0x8096B310/EnMag_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mag_0x8096B310/func_8096C998.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mag_0x8096B310/func_8096CBB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mag_0x8096B310/func_8096CDC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mag_0x8096B310/func_8096D230.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mag_0x8096B310/func_8096D60C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mag_0x8096B310/func_8096D74C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mag_0x8096B310/EnMag_Draw.asm")
