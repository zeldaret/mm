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
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RB,
    sizeof(EnNeoReeba),
    (ActorFunc)EnNeoReeba_Init,
    (ActorFunc)EnNeoReeba_Destroy,
    (ActorFunc)EnNeoReeba_Update,
    (ActorFunc)EnNeoReeba_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/EnNeoReeba_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/EnNeoReeba_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7CA34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7CA70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7CB3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7CB88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7CCE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7CD28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7CE34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7CE94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7CFA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7CFFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D130.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D150.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D254.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D2E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D360.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D398.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D3EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D47C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D4FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D5A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D6D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D788.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7D9B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7DC80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7DD7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7DF34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7E0BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7E260.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/EnNeoReeba_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/func_80B7E378.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Neo_Reeba_0x80B7C890/EnNeoReeba_Draw.asm")
