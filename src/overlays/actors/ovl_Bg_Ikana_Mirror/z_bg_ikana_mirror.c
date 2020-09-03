#include "z_bg_ikana_mirror.h"

#define FLAGS 0x00000010

#define THIS ((BgIkanaMirror*)thisx)

void BgIkanaMirror_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaMirror_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaMirror_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaMirror_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Ikana_Mirror_InitVars = {
    ACTOR_BG_IKANA_MIRROR,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_IKANA_OBJ,
    sizeof(BgIkanaMirror),
    (ActorFunc)BgIkanaMirror_Init,
    (ActorFunc)BgIkanaMirror_Destroy,
    (ActorFunc)BgIkanaMirror_Update,
    (ActorFunc)BgIkanaMirror_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Mirror_0x80B7F730/func_80B7F730.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Mirror_0x80B7F730/BgIkanaMirror_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Mirror_0x80B7F730/BgIkanaMirror_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Mirror_0x80B7F730/func_80B7FA84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Mirror_0x80B7F730/func_80B7FA9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Mirror_0x80B7F730/func_80B7FB84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Mirror_0x80B7F730/func_80B7FBA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Mirror_0x80B7F730/BgIkanaMirror_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Mirror_0x80B7F730/BgIkanaMirror_Draw.asm")
