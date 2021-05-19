#include "z_en_osk.h"

#define FLAGS 0x00000009

#define THIS ((EnOsk*)thisx)

void EnOsk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOsk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOsk_Update(Actor* thisx, GlobalContext* globalCtx);
void EnOsk_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osk_0x80BF5C20/EnOsk_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osk_0x80BF5C20/EnOsk_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osk_0x80BF5C20/func_80BF5E00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osk_0x80BF5C20/func_80BF5E68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osk_0x80BF5C20/func_80BF5EBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osk_0x80BF5C20/func_80BF5F60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osk_0x80BF5C20/func_80BF5F70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osk_0x80BF5C20/func_80BF609C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osk_0x80BF5C20/func_80BF61EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osk_0x80BF5C20/func_80BF6314.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osk_0x80BF5C20/func_80BF6478.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osk_0x80BF5C20/func_80BF656C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osk_0x80BF5C20/func_80BF67A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osk_0x80BF5C20/func_80BF68E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osk_0x80BF5C20/func_80BF6A20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osk_0x80BF5C20/EnOsk_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osk_0x80BF5C20/func_80BF6C54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osk_0x80BF5C20/EnOsk_Draw.asm")
