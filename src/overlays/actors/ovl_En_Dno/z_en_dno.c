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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_DNO,
    sizeof(EnDno),
    (ActorFunc)EnDno_Init,
    (ActorFunc)EnDno_Destroy,
    (ActorFunc)EnDno_Update,
    (ActorFunc)EnDno_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A711D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A71424.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A714B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A7153C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A715DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A71788.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/EnDno_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/EnDno_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A71B04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A71B58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A71B68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A71C3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A71E54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A71F18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A72438.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A724B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A7256C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A72598.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A725E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A725F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A72AE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A72B3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A72B84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A72BA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A72C04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A72CF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A72D8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A72FAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A730A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A73244.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A732C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A73408.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/EnDno_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/EnDno_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A7361C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dno_0x80A711D0/func_80A73654.asm")
