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
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_BOMBF,
    sizeof(EnBombf),
    (ActorFunc)EnBombf_Init,
    (ActorFunc)EnBombf_Destroy,
    (ActorFunc)EnBombf_Update,
    (ActorFunc)EnBombf_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombf_0x808AE8C0/func_808AE8C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombf_0x808AE8C0/EnBombf_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombf_0x808AE8C0/EnBombf_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombf_0x808AE8C0/func_808AEAB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombf_0x808AE8C0/func_808AEAE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombf_0x808AE8C0/func_808AEE3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombf_0x808AE8C0/func_808AEF68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombf_0x808AE8C0/func_808AEFD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombf_0x808AE8C0/EnBombf_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombf_0x808AE8C0/func_808AF86C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombf_0x808AE8C0/EnBombf_Draw.asm")
