#include "z_dm_tag.h"

#define FLAGS 0x00000010

#define THIS ((DmTag*)thisx)

void DmTag_Init(Actor* thisx, GlobalContext* globalCtx);
void DmTag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmTag_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Dm_Tag_InitVars = {
    ACTOR_DM_TAG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DmTag),
    (ActorFunc)DmTag_Init,
    (ActorFunc)DmTag_Destroy,
    (ActorFunc)DmTag_Update,
    (ActorFunc)NULL,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Tag/func_80C22350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Tag/func_80C22400.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Tag/func_80C2247C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Tag/func_80C224D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Tag/func_80C227E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Tag/func_80C22880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Tag/func_80C2291C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Tag/func_80C229AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Tag/func_80C229EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Tag/func_80C229FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Tag/DmTag_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Tag/DmTag_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Tag/DmTag_Update.s")
