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
    (ActorFunc)EnFg_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2D280.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2D348.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2D3D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2D400.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2D42C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2D4B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2D778.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2D9CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2D9DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/EnFg_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/EnFg_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/EnFg_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2DCE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2DD34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/EnFg_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2DFC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2E0A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2E268.asm")
