#include "z_dm_tag.h"

#define FLAGS 0x00000010

#define THIS ((DmTag*)thisx)

void DmTag_Init(Actor* thisx, GlobalContext* globalCtx);
void DmTag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmTag_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_Tag_InitVars = {
    ACTOR_DM_TAG,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DmTag),
    (ActorFunc)DmTag_Init,
    (ActorFunc)DmTag_Destroy,
    (ActorFunc)DmTag_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Tag_0x80C22350/func_80C22350.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Tag_0x80C22350/func_80C22400.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Tag_0x80C22350/func_80C2247C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Tag_0x80C22350/func_80C224D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Tag_0x80C22350/func_80C227E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Tag_0x80C22350/func_80C22880.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Tag_0x80C22350/func_80C2291C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Tag_0x80C22350/func_80C229AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Tag_0x80C22350/func_80C229EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Tag_0x80C22350/func_80C229FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Tag_0x80C22350/DmTag_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Tag_0x80C22350/DmTag_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Tag_0x80C22350/DmTag_Update.asm")
