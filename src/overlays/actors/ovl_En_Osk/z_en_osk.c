#include "z_en_osk.h"

#define FLAGS 0x00000009

#define THIS ((EnOsk*)thisx)

void EnOsk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOsk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOsk_Update(Actor* thisx, GlobalContext* globalCtx);
void EnOsk_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Osk_InitVars = {
    ACTOR_EN_OSK,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_IKN_DEMO,
    sizeof(EnOsk),
    (ActorFunc)EnOsk_Init,
    (ActorFunc)EnOsk_Destroy,
    (ActorFunc)EnOsk_Update,
    (ActorFunc)EnOsk_Draw,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osk/EnOsk_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osk/EnOsk_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osk/func_80BF5E00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osk/func_80BF5E68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osk/func_80BF5EBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osk/func_80BF5F60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osk/func_80BF5F70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osk/func_80BF609C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osk/func_80BF61EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osk/func_80BF6314.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osk/func_80BF6478.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osk/func_80BF656C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osk/func_80BF67A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osk/func_80BF68E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osk/func_80BF6A20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osk/EnOsk_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osk/func_80BF6C54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osk/EnOsk_Draw.s")
