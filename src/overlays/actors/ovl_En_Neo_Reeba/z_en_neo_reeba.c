#include "z_en_neo_reeba.h"

#define FLAGS 0x00000205

#define THIS ((EnNeoReeba*)thisx)

void EnNeoReeba_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNeoReeba_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNeoReeba_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNeoReeba_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Neo_Reeba_InitVars = {
    ACTOR_EN_NEO_REEBA,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_RB,
    sizeof(EnNeoReeba),
    (ActorFunc)EnNeoReeba_Init,
    (ActorFunc)EnNeoReeba_Destroy,
    (ActorFunc)EnNeoReeba_Update,
    (ActorFunc)EnNeoReeba_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/EnNeoReeba_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/EnNeoReeba_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7CA34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7CA70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7CB3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7CB88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7CCE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7CD28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7CE34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7CE94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7CFA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7CFFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D130.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D150.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D254.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D2E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D360.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D398.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D3EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D47C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D4FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D5A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D6D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D788.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D9B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7DC80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7DD7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7DF34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7E0BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7E260.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/EnNeoReeba_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/func_80B7E378.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Neo_Reeba_0x80B7C890/EnNeoReeba_Draw.asm")
