#include "z_en_mkk.h"

#define FLAGS 0x00000005

#define THIS ((EnMkk*)thisx)

void EnMkk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMkk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMkk_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMkk_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Mkk_InitVars = {
    ACTOR_EN_MKK,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_MKK,
    sizeof(EnMkk),
    (ActorFunc)EnMkk_Init,
    (ActorFunc)EnMkk_Destroy,
    (ActorFunc)EnMkk_Update,
    (ActorFunc)EnMkk_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/EnMkk_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/EnMkk_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E0CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E100.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E190.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E1F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E22C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E2B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E2E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E58C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E60C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E67C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E72C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E84C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4EBBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/EnMkk_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4EDF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4EE48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4EEF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4EF74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4F16C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/EnMkk_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4F4C8.s")
