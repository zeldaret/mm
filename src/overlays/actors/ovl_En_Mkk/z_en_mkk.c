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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_MKK,
    sizeof(EnMkk),
    (ActorFunc)EnMkk_Init,
    (ActorFunc)EnMkk_Destroy,
    (ActorFunc)EnMkk_Update,
    (ActorFunc)EnMkk_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/EnMkk_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/EnMkk_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/func_80A4E0CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/func_80A4E100.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/func_80A4E190.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/func_80A4E1F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/func_80A4E22C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/func_80A4E2B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/func_80A4E2E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/func_80A4E58C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/func_80A4E60C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/func_80A4E67C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/func_80A4E72C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/func_80A4E84C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/func_80A4EBBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/EnMkk_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/func_80A4EDF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/func_80A4EE48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/func_80A4EEF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/func_80A4EF74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/func_80A4F16C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/EnMkk_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mkk_0x80A4DED0/func_80A4F4C8.asm")
