#include "z_en_bb.h"

#define FLAGS 0x00000205

#define THIS ((EnBb*)thisx)

void EnBb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBb_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bb_InitVars = {
    ACTOR_EN_BB,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BB,
    sizeof(EnBb),
    (ActorFunc)EnBb_Init,
    (ActorFunc)EnBb_Destroy,
    (ActorFunc)EnBb_Update,
    (ActorFunc)EnBb_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/EnBb_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/EnBb_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C1E94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C1F00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C1F74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C1FF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C20D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2238.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2344.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C23EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C254C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C25E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C272C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C28CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2A00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2B1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2B94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2BD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2C38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2CB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2CF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2D78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2E34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/EnBb_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C32EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C3324.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/EnBb_Draw.s")
