#include "z_en_paper.h"

#define FLAGS 0x02100010

#define THIS ((EnPaper*)thisx)

void EnPaper_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPaper_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPaper_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPaper_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Paper_InitVars = {
    ACTOR_EN_PAPER,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BAL,
    sizeof(EnPaper),
    (ActorFunc)EnPaper_Init,
    (ActorFunc)EnPaper_Destroy,
    (ActorFunc)EnPaper_Update,
    (ActorFunc)EnPaper_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Paper_0x80C1F3D0/EnPaper_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Paper_0x80C1F3D0/EnPaper_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Paper_0x80C1F3D0/func_80C1F46C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Paper_0x80C1F3D0/func_80C1F480.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Paper_0x80C1F3D0/func_80C1F4E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Paper_0x80C1F3D0/func_80C1F4FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Paper_0x80C1F3D0/func_80C1F55C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Paper_0x80C1F3D0/func_80C1F6E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Paper_0x80C1F3D0/func_80C1F87C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Paper_0x80C1F3D0/EnPaper_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Paper_0x80C1F3D0/EnPaper_Draw.asm")
