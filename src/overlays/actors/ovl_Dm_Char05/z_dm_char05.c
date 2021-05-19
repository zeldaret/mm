#include "z_dm_char05.h"

#define FLAGS 0x00000030

#define THIS ((DmChar05*)thisx)

void DmChar05_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar05_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar05_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar05_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_Char05_InitVars = {
    ACTOR_DM_CHAR05,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_DMASK,
    sizeof(DmChar05),
    (ActorFunc)DmChar05_Init,
    (ActorFunc)DmChar05_Destroy,
    (ActorFunc)DmChar05_Update,
    (ActorFunc)DmChar05_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AAC5A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AAC63C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AAC6E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AAC770.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AAC7FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AAC888.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/DmChar05_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/DmChar05_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AAC990.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AAC9DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AACA98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AACAE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AACBE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AACC48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AACC6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AACCD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AACD0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AACD1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AACD68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AACE10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AACE5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AACF04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AAD3F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AAD450.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AAD4A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/DmChar05_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AAD964.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AAD980.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AAD998.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AADA90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AADB4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AADC00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/DmChar05_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AADD9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AADE78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AADF54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AAE030.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char05_0x80AAC5A0/func_80AAE114.asm")
