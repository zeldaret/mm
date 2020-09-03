#include "z_en_wood02.h"

#define FLAGS 0x00000000

#define THIS ((EnWood02*)thisx)

void EnWood02_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWood02_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWood02_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWood02_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Wood02_InitVars = {
    ACTOR_EN_WOOD02,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_WOOD02,
    sizeof(EnWood02),
    (ActorFunc)EnWood02_Init,
    (ActorFunc)EnWood02_Destroy,
    (ActorFunc)EnWood02_Update,
    (ActorFunc)EnWood02_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Wood02_0x808C3C00/func_808C3C00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wood02_0x808C3C00/func_808C3D28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wood02_0x808C3C00/EnWood02_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wood02_0x808C3C00/EnWood02_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wood02_0x808C3C00/func_808C4458.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wood02_0x808C3C00/EnWood02_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wood02_0x808C3C00/EnWood02_Draw.asm")
