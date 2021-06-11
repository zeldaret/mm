#include "z_en_osn.h"

#define FLAGS 0x00000019

#define THIS ((EnOsn*)thisx)

void EnOsn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOsn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOsn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnOsn_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Osn_InitVars = {
    ACTOR_EN_OSN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OSN,
    sizeof(EnOsn),
    (ActorFunc)EnOsn_Init,
    (ActorFunc)EnOsn_Destroy,
    (ActorFunc)EnOsn_Update,
    (ActorFunc)EnOsn_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD0830.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD08B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD0998.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD0A24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD0AB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD0B38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD0E10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD10FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD1398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD144C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD14C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD1634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD16A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD19A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD1A4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/EnOsn_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/EnOsn_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/EnOsn_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD1DA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/func_80AD1E28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Osn/EnOsn_Draw.s")
