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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80997A90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80997AFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/EnGs_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/EnGs_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80997D14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80997D38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80997DEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80997E4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80997FF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80998040.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_8099807C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80998300.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80998334.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_809984F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_809985B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80998704.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_8099874C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_809989B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_809989F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80998A48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80998BBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80998D44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80998F9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80999584.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_809995A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80999A8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80999AC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80999B34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/func_80999BC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/EnGs_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gs_0x80997A90/EnGs_Draw.asm")
