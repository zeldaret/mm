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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_FR,
    sizeof(EnFg),
    (ActorFunc)EnFg_Init,
    (ActorFunc)EnFg_Destroy,
    (ActorFunc)EnFg_Update,
    (ActorFunc)EnFg_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Fg_0x80A2D280/func_80A2D280.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fg_0x80A2D280/func_80A2D348.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fg_0x80A2D280/func_80A2D3D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fg_0x80A2D280/func_80A2D400.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fg_0x80A2D280/func_80A2D42C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fg_0x80A2D280/func_80A2D4B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fg_0x80A2D280/func_80A2D778.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fg_0x80A2D280/func_80A2D9CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fg_0x80A2D280/func_80A2D9DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fg_0x80A2D280/EnFg_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fg_0x80A2D280/EnFg_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fg_0x80A2D280/EnFg_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fg_0x80A2D280/func_80A2DCE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fg_0x80A2D280/func_80A2DD34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fg_0x80A2D280/EnFg_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fg_0x80A2D280/func_80A2DFC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fg_0x80A2D280/func_80A2E0A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fg_0x80A2D280/func_80A2E268.asm")
