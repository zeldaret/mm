#include "z_en_light.h"

#define FLAGS 0x00000000

#define THIS ((EnLight*)thisx)

void EnLight_Init(Actor* thisx, GlobalContext* globalCtx);
void EnLight_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnLight_Update(Actor* thisx, GlobalContext* globalCtx);
void EnLight_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Light_InitVars = {
    ACTOR_EN_LIGHT,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnLight),
    (ActorFunc)EnLight_Init,
    (ActorFunc)EnLight_Destroy,
    (ActorFunc)EnLight_Update,
    (ActorFunc)EnLight_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Light_0x80865990/EnLight_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Light_0x80865990/EnLight_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Light_0x80865990/func_80865BF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Light_0x80865990/EnLight_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Light_0x80865990/func_80865F38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Light_0x80865990/EnLight_Draw.asm")
