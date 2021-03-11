#include "z_en_bu.h"

#define FLAGS 0x00000001

#define THIS ((EnBu*)thisx)

void EnBu_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBu_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBu_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bu_InitVars = {
    ACTOR_EN_BU,
    ACTORCAT_ENEMY,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBu),
    (ActorFunc)EnBu_Init,
    (ActorFunc)EnBu_Destroy,
    (ActorFunc)EnBu_Update,
    (ActorFunc)EnBu_Draw
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bu_0x809ACD90/EnBu_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bu_0x809ACD90/EnBu_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bu_0x809ACD90/func_809ACDB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bu_0x809ACD90/EnBu_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bu_0x809ACD90/EnBu_Draw.asm")
