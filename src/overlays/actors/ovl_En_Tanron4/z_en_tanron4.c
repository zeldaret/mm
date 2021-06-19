#include "z_en_tanron4.h"

#define FLAGS 0x02000010

#define THIS ((EnTanron4*)thisx)

void EnTanron4_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTanron4_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTanron4_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTanron4_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Tanron4_InitVars = {
    ACTOR_EN_TANRON4,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_TANRON4,
    sizeof(EnTanron4),
    (ActorFunc)EnTanron4_Init,
    (ActorFunc)EnTanron4_Destroy,
    (ActorFunc)EnTanron4_Update,
    (ActorFunc)EnTanron4_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron4_0x80BE3B80/EnTanron4_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron4_0x80BE3B80/EnTanron4_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron4_0x80BE3B80/func_80BE3DC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron4_0x80BE3B80/func_80BE3DFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron4_0x80BE3B80/func_80BE4268.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron4_0x80BE3B80/func_80BE42A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron4_0x80BE3B80/EnTanron4_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron4_0x80BE3B80/EnTanron4_Draw.asm")
