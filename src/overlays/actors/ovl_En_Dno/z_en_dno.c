#include "z_en_dno.h"

#define FLAGS 0x00000039

#define THIS ((EnDno*)thisx)

void EnDno_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDno_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDno_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDno_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Dno_InitVars = {
    ACTOR_EN_DNO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNO,
    sizeof(EnDno),
    (ActorFunc)EnDno_Init,
    (ActorFunc)EnDno_Destroy,
    (ActorFunc)EnDno_Update,
    (ActorFunc)EnDno_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A711D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A71424.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A714B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A7153C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A715DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A71788.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/EnDno_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/EnDno_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A71B04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A71B58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A71B68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A71C3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A71E54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A71F18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A72438.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A724B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A7256C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A72598.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A725E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A725F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A72AE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A72B3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A72B84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A72BA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A72C04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A72CF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A72D8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A72FAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A730A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A73244.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A732C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A73408.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/EnDno_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/EnDno_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A7361C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dno/func_80A73654.s")
