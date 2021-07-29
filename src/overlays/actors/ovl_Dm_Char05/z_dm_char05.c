#include "z_dm_char05.h"

#define FLAGS 0x00000030

#define THIS ((DmChar05*)thisx)

void DmChar05_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar05_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar05_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar05_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AAC990(DmChar05* this, GlobalContext* globalCtx);
void func_80AAC9DC(DmChar05* this, GlobalContext* globalCtx);
void func_80AACA98(DmChar05* this, GlobalContext* globalCtx);
void func_80AACAE4(DmChar05* this, GlobalContext* globalCtx);
void func_80AACBE4(DmChar05* this, GlobalContext* globalCtx);
void func_80AACC48(DmChar05* this, GlobalContext* globalCtx);
void func_80AACC6C(DmChar05* this, GlobalContext* globalCtx);
void func_80AACCD4(DmChar05* this, GlobalContext* globalCtx);
void func_80AACD0C(DmChar05* this, GlobalContext* globalCtx);
void func_80AACD1C(DmChar05* this, GlobalContext* globalCtx);
void func_80AACD68(DmChar05* this, GlobalContext* globalCtx);
void func_80AACE10(DmChar05* this, GlobalContext* globalCtx);
void func_80AACE5C(DmChar05* this, GlobalContext* globalCtx);

#if 0
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

#endif

extern UNK_TYPE D_060001D0;
extern UNK_TYPE D_060010B0;
extern UNK_TYPE D_060013D0;
extern UNK_TYPE D_06001E70;
extern UNK_TYPE D_060042B0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AAC5A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AAC63C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AAC6E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AAC770.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AAC7FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AAC888.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/DmChar05_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/DmChar05_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AAC990.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AAC9DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AACA98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AACAE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AACBE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AACC48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AACC6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AACCD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AACD0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AACD1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AACD68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AACE10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AACE5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AACF04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AAD3F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AAD450.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AAD4A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/DmChar05_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AAD964.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AAD980.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AAD998.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AADA90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AADB4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AADC00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/DmChar05_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AADD9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AADE78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AADF54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AAE030.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char05/func_80AAE114.s")
