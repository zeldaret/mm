/*
 * File: z_dm_char08.c
 * Overlay: ovl_Dm_Char08
 * Description: Large Great Bay Turtle
 */

#include "z_dm_char08.h"

#define FLAGS (ACTOR_FLAG_2000000)

#define THIS ((DmChar08*)thisx)

void DmChar08_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar08_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar08_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar08_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Dm_Char08_InitVars = {
    ACTOR_DM_CHAR08,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KAMEJIMA,
    sizeof(DmChar08),
    (ActorFunc)DmChar08_Init,
    (ActorFunc)DmChar08_Destroy,
    (ActorFunc)DmChar08_Update,
    (ActorFunc)DmChar08_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AB1764[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 4000, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80AB1764[];

extern UNK_TYPE D_06002470;
extern UNK_TYPE D_06004E70;
extern UNK_TYPE D_0600E748;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AAF050.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AAF15C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/DmChar08_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/DmChar08_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AAF610.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AAF79C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AAF884.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AAF8F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AAFA18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AAFAC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AAFAE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AAFB04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AAFB94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AAFBA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AAFCCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AAFE78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AAFE88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AB01E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AB023C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AB032C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AB096C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AB0A10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/DmChar08_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AB0E3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AB0E7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/func_80AB0F90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char08/DmChar08_Draw.s")
