#include "z_en_tanron1.h"

#define FLAGS 0x00000035

#define THIS ((EnTanron1*)thisx)

void EnTanron1_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTanron1_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTanron1_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTanron1_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Tanron1_InitVars = {
    ACTOR_EN_TANRON1,
    ACTORCAT_ENEMY,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTanron1),
    (ActorFunc)EnTanron1_Init,
    (ActorFunc)EnTanron1_Destroy,
    (ActorFunc)EnTanron1_Update,
    (ActorFunc)EnTanron1_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron1_0x80BB4E00/EnTanron1_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron1_0x80BB4E00/EnTanron1_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron1_0x80BB4E00/func_80BB4E50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron1_0x80BB4E00/EnTanron1_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron1_0x80BB4E00/EnTanron1_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron1_0x80BB4E00/func_80BB5318.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron1_0x80BB4E00/func_80BB5AAC.asm")
