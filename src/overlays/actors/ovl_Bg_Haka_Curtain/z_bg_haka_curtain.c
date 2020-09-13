#include "z_bg_haka_curtain.h"

#define FLAGS 0x00000010

#define THIS ((BgHakaCurtain*)thisx)

void BgHakaCurtain_Init(Actor* thisx, GlobalContext* globalCtx);
void BgHakaCurtain_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgHakaCurtain_Update(Actor* thisx, GlobalContext* globalCtx);
void BgHakaCurtain_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Haka_Curtain_InitVars = {
    ACTOR_BG_HAKA_CURTAIN,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_HAKA_OBJ,
    sizeof(BgHakaCurtain),
    (ActorFunc)BgHakaCurtain_Init,
    (ActorFunc)BgHakaCurtain_Destroy,
    (ActorFunc)BgHakaCurtain_Update,
    (ActorFunc)BgHakaCurtain_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Haka_Curtain_0x80B6DBE0/BgHakaCurtain_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Haka_Curtain_0x80B6DBE0/BgHakaCurtain_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Haka_Curtain_0x80B6DBE0/func_80B6DC98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Haka_Curtain_0x80B6DBE0/func_80B6DCAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Haka_Curtain_0x80B6DBE0/func_80B6DCEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Haka_Curtain_0x80B6DBE0/func_80B6DD00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Haka_Curtain_0x80B6DBE0/func_80B6DD5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Haka_Curtain_0x80B6DBE0/func_80B6DD70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Haka_Curtain_0x80B6DBE0/func_80B6DD80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Haka_Curtain_0x80B6DBE0/func_80B6DD9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Haka_Curtain_0x80B6DBE0/func_80B6DE80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Haka_Curtain_0x80B6DBE0/func_80B6DEA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Haka_Curtain_0x80B6DBE0/BgHakaCurtain_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Haka_Curtain_0x80B6DBE0/BgHakaCurtain_Draw.asm")
