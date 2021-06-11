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
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_THIEFBIRD,
    sizeof(EnThiefbird),
    (ActorFunc)EnThiefbird_Init,
    (ActorFunc)EnThiefbird_Destroy,
    (ActorFunc)EnThiefbird_Update,
    (ActorFunc)EnThiefbird_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/EnThiefbird_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/EnThiefbird_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C10984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C10B0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C10DE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C10E98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C11338.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C11454.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C114C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C11538.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C11590.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C118E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C1193C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C11C60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C11D14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C11DC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C11DF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C11F6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C1215C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C12308.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C12378.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C1242C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C124B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C126A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C126D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C12744.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C127F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C12B1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C12D00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/EnThiefbird_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C130EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C1315C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/func_80C13354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Thiefbird/EnThiefbird_Draw.s")
