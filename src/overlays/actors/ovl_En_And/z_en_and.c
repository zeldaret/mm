#include "z_en_and.h"

#define FLAGS 0x00000039

#define THIS ((EnAnd*)thisx)

void EnAnd_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAnd_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAnd_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAnd_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_And_InitVars = {
    ACTOR_EN_AND,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AND,
    sizeof(EnAnd),
    (ActorFunc)EnAnd_Init,
    (ActorFunc)EnAnd_Destroy,
    (ActorFunc)EnAnd_Update,
    (ActorFunc)EnAnd_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_And_0x80C18B90/func_80C18B90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_And_0x80C18B90/func_80C18BD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_And_0x80C18B90/func_80C18C50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_And_0x80C18B90/EnAnd_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_And_0x80C18B90/EnAnd_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_And_0x80C18B90/EnAnd_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_And_0x80C18B90/func_80C18ED0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_And_0x80C18B90/EnAnd_Draw.asm")
