/*
 * File: z_en_sekihi.c
 * Overlay: ovl_En_Sekihi
 * Description: Mikau's Grave & Song Pedestals
 */

#include "z_en_sekihi.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnSekihi*)thisx)

void EnSekihi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSekihi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSekihi_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A44DE8(EnSekihi* this, GlobalContext* globalCtx);
void func_80A44F40(EnSekihi* this, GlobalContext* globalCtx);
void func_80A450B0(EnSekihi* this, GlobalContext* globalCtx);
void func_80A45130(EnSekihi* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Sekihi_InitVars = {
    ACTOR_EN_SEKIHI,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnSekihi),
    (ActorFunc)EnSekihi_Init,
    (ActorFunc)EnSekihi_Destroy,
    (ActorFunc)EnSekihi_Update,
    (ActorFunc)NULL,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sekihi/EnSekihi_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sekihi/EnSekihi_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sekihi/func_80A44DE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sekihi/func_80A44F40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sekihi/func_80A450B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sekihi/func_80A45130.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sekihi/EnSekihi_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sekihi/func_80A45164.s")
