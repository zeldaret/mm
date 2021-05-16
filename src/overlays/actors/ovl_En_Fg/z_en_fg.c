#include "z_en_fg.h"

#define FLAGS 0x00004209

#define THIS ((EnFg*)thisx)

void EnFg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFg_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Fg_InitVars = {
    ACTOR_EN_FG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_FR,
    sizeof(EnFg),
    (ActorFunc)EnFg_Init,
    (ActorFunc)EnFg_Destroy,
    (ActorFunc)EnFg_Update,
    (ActorFunc)EnFg_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fg/func_80A2D280.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fg/func_80A2D348.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fg/func_80A2D3D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fg/func_80A2D400.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fg/func_80A2D42C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fg/func_80A2D4B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fg/func_80A2D778.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fg/func_80A2D9CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fg/func_80A2D9DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fg/EnFg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fg/EnFg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fg/EnFg_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fg/func_80A2DCE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fg/func_80A2DD34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fg/EnFg_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fg/func_80A2DFC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fg/func_80A2E0A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fg/func_80A2E268.s")
