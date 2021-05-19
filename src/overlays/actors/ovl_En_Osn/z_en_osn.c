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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD0830.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD08B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD0998.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD0A24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD0AB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD0B38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD0E10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD10FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD1398.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD144C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD14C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD1634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD16A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD19A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD1A4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/EnOsn_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/EnOsn_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/EnOsn_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD1DA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/func_80AD1E28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Osn_0x80AD0830/EnOsn_Draw.asm")
