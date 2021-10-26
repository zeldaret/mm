/*
 * File: z_en_mag.c
 * Overlay: ovl_En_Mag
 * Description: Title Logo
 */

#include "z_en_mag.h"

#define FLAGS 0x00000030

#define THIS ((EnMag*)thisx)

void EnMag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMag_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMag_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
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

#endif

extern UNK_TYPE D_06011E48;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/EnMag_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/EnMag_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/func_8096B604.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/EnMag_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/func_8096C998.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/func_8096CBB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/func_8096CDC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/func_8096D230.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/func_8096D60C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/func_8096D74C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/EnMag_Draw.s")
