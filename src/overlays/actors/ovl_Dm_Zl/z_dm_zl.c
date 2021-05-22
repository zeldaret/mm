#include "z_dm_zl.h"

#define FLAGS 0x00000010

#define THIS ((DmZl*)thisx)

void DmZl_Init(Actor* thisx, GlobalContext* globalCtx);
void DmZl_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmZl_Update(Actor* thisx, GlobalContext* globalCtx);
void DmZl_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_Zl_InitVars = {
    ACTOR_DM_ZL,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_ZL4,
    sizeof(DmZl),
    (ActorFunc)DmZl_Init,
    (ActorFunc)DmZl_Destroy,
    (ActorFunc)DmZl_Update,
    (ActorFunc)DmZl_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Zl_0x80A38190/func_80A38190.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Zl_0x80A38190/DmZl_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Zl_0x80A38190/DmZl_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Zl_0x80A38190/func_80A382FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Zl_0x80A38190/func_80A3830C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Zl_0x80A38190/func_80A38468.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Zl_0x80A38190/DmZl_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Zl_0x80A38190/func_80A3862C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Zl_0x80A38190/func_80A38648.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Zl_0x80A38190/DmZl_Draw.asm")
