#include "z_en_bombf.h"

#define FLAGS 0x00000011

#define THIS ((EnBombf*)thisx)

void EnBombf_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBombf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBombf_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBombf_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bombf_InitVars = {
    ACTOR_EN_BOMBF,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_BOMBF,
    sizeof(EnBombf),
    (ActorFunc)EnBombf_Init,
    (ActorFunc)EnBombf_Destroy,
    (ActorFunc)EnBombf_Update,
    (ActorFunc)EnBombf_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombf_0x808AE8C0/func_808AE8C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombf_0x808AE8C0/EnBombf_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombf_0x808AE8C0/EnBombf_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombf_0x808AE8C0/func_808AEAB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombf_0x808AE8C0/func_808AEAE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombf_0x808AE8C0/func_808AEE3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombf_0x808AE8C0/func_808AEF68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombf_0x808AE8C0/func_808AEFD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombf_0x808AE8C0/EnBombf_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombf_0x808AE8C0/func_808AF86C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombf_0x808AE8C0/EnBombf_Draw.asm")
