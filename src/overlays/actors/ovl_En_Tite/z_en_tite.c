#include "z_en_tite.h"

#define FLAGS 0x00000205

#define THIS ((EnTite*)thisx)

void EnTite_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTite_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTite_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTite_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Tite_InitVars = {
    ACTOR_EN_TITE,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_TITE,
    sizeof(EnTite),
    (ActorFunc)EnTite_Init,
    (ActorFunc)EnTite_Destroy,
    (ActorFunc)EnTite_Update,
    (ActorFunc)EnTite_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/EnTite_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/EnTite_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80893A18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80893A34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80893A9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80893ADC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80893B10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80893B70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80893BCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80893DD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80893E54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80893ED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80893F30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80893FD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80894024.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_8089408C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_808942B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80894414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80894454.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_8089452C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_808945B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_808945EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80894638.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_8089484C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80894910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80894B2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80894BC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80894DD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80894E0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80895020.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_808951B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_808952EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80895424.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_808955E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80895640.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_808956B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_808956FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80895738.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_8089595C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80895A10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80895AC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80895CB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80895D08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80895DE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80895E28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80895FF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_808963B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/EnTite_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80896750.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/func_80896788.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tite/EnTite_Draw.s")
