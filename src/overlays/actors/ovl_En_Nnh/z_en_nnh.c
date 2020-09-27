#include "z_en_nnh.h"

#define FLAGS 0x00000019

#define THIS ((EnNnh*)thisx)

void EnNnh_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNnh_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNnh_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNnh_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit D_80C089E0 = {
    ACTOR_EN_NNH,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_NNH,
    sizeof(EnNnh),
    (ActorFunc)EnNnh_Init,
    (ActorFunc)EnNnh_Destroy,
    (ActorFunc)EnNnh_Update,
    (ActorFunc)EnNnh_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Nnh_0x80C08760/EnNnh_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nnh_0x80C08760/EnNnh_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nnh_0x80C08760/func_80C08828.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nnh_0x80C08760/func_80C0883C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nnh_0x80C08760/func_80C088A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nnh_0x80C08760/func_80C088B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nnh_0x80C08760/EnNnh_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nnh_0x80C08760/EnNnh_Draw.asm")
