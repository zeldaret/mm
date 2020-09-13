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
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_MAG,
    sizeof(EnMag),
    (ActorFunc)EnMag_Init,
    (ActorFunc)EnMag_Destroy,
    (ActorFunc)EnMag_Update,
    (ActorFunc)EnMag_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Mag_0x8096B310/EnMag_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mag_0x8096B310/EnMag_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mag_0x8096B310/func_8096B604.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mag_0x8096B310/EnMag_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mag_0x8096B310/func_8096C998.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mag_0x8096B310/func_8096CBB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mag_0x8096B310/func_8096CDC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mag_0x8096B310/func_8096D230.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mag_0x8096B310/func_8096D60C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mag_0x8096B310/func_8096D74C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mag_0x8096B310/EnMag_Draw.asm")
