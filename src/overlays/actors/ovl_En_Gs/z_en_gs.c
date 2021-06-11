#include "z_en_gs.h"

#define FLAGS 0x02000019

#define THIS ((EnGs*)thisx)

void EnGs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGs_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGs_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Gs_InitVars = {
    ACTOR_EN_GS,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_GS,
    sizeof(EnGs),
    (ActorFunc)EnGs_Init,
    (ActorFunc)EnGs_Destroy,
    (ActorFunc)EnGs_Update,
    (ActorFunc)EnGs_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_80997A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_80997AFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/EnGs_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/EnGs_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_80997D14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_80997D38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_80997DEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_80997E4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_80997FF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_80998040.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_8099807C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_80998300.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_80998334.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_809984F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_809985B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_80998704.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_8099874C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_809989B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_809989F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_80998A48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_80998BBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_80998D44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_80998F9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_80999584.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_809995A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_80999A8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_80999AC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_80999B34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/func_80999BC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/EnGs_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gs/EnGs_Draw.s")
