#include "z_en_estone.h"

#define FLAGS 0x00000030

#define THIS ((EnEstone*)thisx)

void EnEstone_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEstone_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEstone_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEstone_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Estone_InitVars = {
    ACTOR_EN_ESTONE,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_EG,
    sizeof(EnEstone),
    (ActorFunc)EnEstone_Init,
    (ActorFunc)EnEstone_Destroy,
    (ActorFunc)EnEstone_Update,
    (ActorFunc)EnEstone_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Estone_0x80A99EA0/EnEstone_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Estone_0x80A99EA0/EnEstone_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Estone_0x80A99EA0/func_80A9A1DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Estone_0x80A99EA0/func_80A9A4B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Estone_0x80A99EA0/EnEstone_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Estone_0x80A99EA0/EnEstone_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Estone_0x80A99EA0/func_80A9A774.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Estone_0x80A99EA0/func_80A9A870.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Estone_0x80A99EA0/func_80A9A9C0.asm")
