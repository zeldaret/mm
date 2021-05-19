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
    (ActorFunc)EnBb_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/EnBb_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/EnBb_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C1E94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C1F00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C1F74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C1FF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C20D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C2238.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C2344.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C23EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C254C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C25E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C272C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C28CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C2A00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C2B1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C2B94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C2BD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C2C38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C2CB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C2CF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C2D78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C2E34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/EnBb_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C32EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/func_808C3324.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bb_0x808C1D40/EnBb_Draw.asm")
