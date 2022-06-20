/*
 * File: z_dm_hina.c
 * Overlay: ovl_Dm_Hina
 * Description: Boss mask cutscene objects
 */

#include "z_dm_hina.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmHina*)thisx)

void DmHina_Init(Actor* thisx, GlobalContext* globalCtx);
void DmHina_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmHina_Update(Actor* thisx, GlobalContext* globalCtx);
void DmHina_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A1F470(DmHina* this, GlobalContext* globalCtx);
void func_80A1F56C(DmHina* this, GlobalContext* globalCtx);
void func_80A1F5AC(DmHina* this, GlobalContext* globalCtx);
void func_80A1F63C(DmHina* this, GlobalContext* globalCtx);

#if 0
const ActorInit Dm_Hina_InitVars = {
    ACTOR_DM_HINA,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BSMASK,
    sizeof(DmHina),
    (ActorFunc)DmHina_Init,
    (ActorFunc)DmHina_Destroy,
    (ActorFunc)DmHina_Update,
    (ActorFunc)DmHina_Draw,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Hina/DmHina_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Hina/DmHina_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Hina/func_80A1F470.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Hina/func_80A1F56C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Hina/func_80A1F5AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Hina/func_80A1F63C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Hina/func_80A1F75C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Hina/DmHina_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Hina/func_80A1F9AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Hina/DmHina_Draw.s")
