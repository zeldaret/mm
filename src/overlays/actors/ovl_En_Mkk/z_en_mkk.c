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
    (ActorFunc)EnMkk_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/EnMkk_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/EnMkk_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/func_80A4E0CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/func_80A4E100.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/func_80A4E190.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/func_80A4E1F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/func_80A4E22C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/func_80A4E2B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/func_80A4E2E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/func_80A4E58C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/func_80A4E60C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/func_80A4E67C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/func_80A4E72C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/func_80A4E84C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/func_80A4EBBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/EnMkk_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/func_80A4EDF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/func_80A4EE48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/func_80A4EEF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/func_80A4EF74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/func_80A4F16C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/EnMkk_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mkk_0x80A4DED0/func_80A4F4C8.asm")
