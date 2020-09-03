#include "z_dm_hina.h"

#define FLAGS 0x00000030

#define THIS ((DmHina*)thisx)

void DmHina_Init(Actor* thisx, GlobalContext* globalCtx);
void DmHina_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmHina_Update(Actor* thisx, GlobalContext* globalCtx);
void DmHina_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_Hina_InitVars = {
    ACTOR_DM_HINA,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_BSMASK,
    sizeof(DmHina),
    (ActorFunc)DmHina_Init,
    (ActorFunc)DmHina_Destroy,
    (ActorFunc)DmHina_Update,
    (ActorFunc)DmHina_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Hina_0x80A1F410/DmHina_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Hina_0x80A1F410/DmHina_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Hina_0x80A1F410/func_80A1F470.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Hina_0x80A1F410/func_80A1F56C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Hina_0x80A1F410/func_80A1F5AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Hina_0x80A1F410/func_80A1F63C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Hina_0x80A1F410/func_80A1F75C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Hina_0x80A1F410/DmHina_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Hina_0x80A1F410/func_80A1F9AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Hina_0x80A1F410/DmHina_Draw.asm")
