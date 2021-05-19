#include "z_en_fu.h"

#define FLAGS 0x0A000019

#define THIS ((EnFu*)thisx)

void EnFu_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFu_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFu_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Fu_InitVars = {
    ACTOR_EN_FU,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MU,
    sizeof(EnFu),
    (ActorFunc)EnFu_Init,
    (ActorFunc)EnFu_Destroy,
    (ActorFunc)EnFu_Update,
    (ActorFunc)EnFu_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_809616E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_809619D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/EnFu_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/EnFu_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80961D10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80961D7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80961E88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80961EC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80961F00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80961F38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_8096209C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_809622FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80962340.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80962588.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80962660.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_809628BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_809628D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_809629F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80962A10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80962BA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80962BCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80962D48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80962D60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80962EBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80962F10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80962F4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80963258.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_8096326C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_809632D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80963350.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80963540.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80963560.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80963610.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80963630.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80963810.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_809638F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_809639D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80963DE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80963EAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80963F44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80963F88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80963FF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80964034.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_809640D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_8096413C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80964190.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_8096426C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_809642E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/EnFu_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_809643FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_8096450C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/EnFu_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80964694.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_809647EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_0x809616E0/func_80964950.asm")
