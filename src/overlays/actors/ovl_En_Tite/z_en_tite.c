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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/EnTite_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/EnTite_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893A18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893A34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893A9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893ADC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893B10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893B70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893BCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893DD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893E54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893ED4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893F30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893FD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80894024.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_8089408C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_808942B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80894414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80894454.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_8089452C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_808945B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_808945EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80894638.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_8089484C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80894910.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80894B2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80894BC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80894DD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80894E0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895020.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_808951B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_808952EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895424.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_808955E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895640.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_808956B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_808956FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895738.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_8089595C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895A10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895AC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895CB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895D08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895DE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895E28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895FF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_808963B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/EnTite_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80896750.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80896788.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/EnTite_Draw.asm")
