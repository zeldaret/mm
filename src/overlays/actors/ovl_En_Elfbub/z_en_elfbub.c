#include "z_en_elfbub.h"

#define FLAGS 0x00000001

#define THIS ((EnElfbub*)thisx)

void EnElfbub_Init(Actor* thisx, GlobalContext* globalCtx);
void EnElfbub_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnElfbub_Update(Actor* thisx, GlobalContext* globalCtx);
void EnElfbub_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Elfbub_InitVars = {
    ACTOR_EN_ELFBUB,
    ACTORCAT_MISC,
    FLAGS,
    OBJECT_BUBBLE,
    sizeof(EnElfbub),
    (ActorFunc)EnElfbub_Init,
    (ActorFunc)EnElfbub_Destroy,
    (ActorFunc)EnElfbub_Update,
    (ActorFunc)EnElfbub_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfbub/EnElfbub_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfbub/EnElfbub_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfbub/func_80ACDE60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfbub/func_80ACE030.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfbub/EnElfbub_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfbub/EnElfbub_Draw.s")
