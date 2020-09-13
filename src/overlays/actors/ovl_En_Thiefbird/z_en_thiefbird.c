#include "z_en_thiefbird.h"

#define FLAGS 0x80001205

#define THIS ((EnThiefbird*)thisx)

void EnThiefbird_Init(Actor* thisx, GlobalContext* globalCtx);
void EnThiefbird_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnThiefbird_Update(Actor* thisx, GlobalContext* globalCtx);
void EnThiefbird_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Thiefbird_InitVars = {
    ACTOR_EN_THIEFBIRD,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_THIEFBIRD,
    sizeof(EnThiefbird),
    (ActorFunc)EnThiefbird_Init,
    (ActorFunc)EnThiefbird_Destroy,
    (ActorFunc)EnThiefbird_Update,
    (ActorFunc)EnThiefbird_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/EnThiefbird_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/EnThiefbird_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C10984.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C10B0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C10DE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C10E98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C11338.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C11454.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C114C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C11538.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C11590.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C118E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C1193C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C11C60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C11D14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C11DC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C11DF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C11F6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C1215C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C12308.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C12378.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C1242C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C124B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C126A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C126D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C12744.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C127F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C12B1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C12D00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/EnThiefbird_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C130EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C1315C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/func_80C13354.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Thiefbird_0x80C10770/EnThiefbird_Draw.asm")
