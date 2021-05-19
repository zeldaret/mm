#include "z_en_encount3.h"

#define FLAGS 0x08000030

#define THIS ((EnEncount3*)thisx)

void EnEncount3_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEncount3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEncount3_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEncount3_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Encount3_InitVars = {
    ACTOR_EN_ENCOUNT3,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BIG_FWALL,
    sizeof(EnEncount3),
    (ActorFunc)EnEncount3_Init,
    (ActorFunc)EnEncount3_Destroy,
    (ActorFunc)EnEncount3_Update,
    (ActorFunc)EnEncount3_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount3_0x809ACF40/EnEncount3_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount3_0x809ACF40/EnEncount3_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount3_0x809ACF40/func_809AD058.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount3_0x809ACF40/func_809AD084.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount3_0x809ACF40/func_809AD194.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount3_0x809ACF40/func_809AD1EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount3_0x809ACF40/EnEncount3_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount3_0x809ACF40/EnEncount3_Draw.asm")
