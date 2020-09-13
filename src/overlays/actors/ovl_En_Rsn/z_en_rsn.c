#include "z_en_rsn.h"

#define FLAGS 0x02000019

#define THIS ((EnRsn*)thisx)

void EnRsn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRsn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRsn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRsn_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Rsn_InitVars = {
    ACTOR_EN_RSN,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_RS,
    sizeof(EnRsn),
    (ActorFunc)EnRsn_Init,
    (ActorFunc)EnRsn_Destroy,
    (ActorFunc)EnRsn_Update,
    (ActorFunc)EnRsn_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Rsn_0x80C25D40/func_80C25D40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rsn_0x80C25D40/func_80C25D84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rsn_0x80C25D40/EnRsn_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rsn_0x80C25D40/EnRsn_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rsn_0x80C25D40/EnRsn_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rsn_0x80C25D40/func_80C25EB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rsn_0x80C25D40/func_80C25EF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rsn_0x80C25D40/EnRsn_Draw.asm")
