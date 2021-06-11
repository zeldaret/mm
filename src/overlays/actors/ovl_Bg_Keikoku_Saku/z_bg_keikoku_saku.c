#include "z_bg_keikoku_saku.h"

#define FLAGS 0x00000000

#define THIS ((BgKeikokuSaku*)thisx)

void BgKeikokuSaku_Init(Actor* thisx, GlobalContext* globalCtx);
void BgKeikokuSaku_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgKeikokuSaku_Update(Actor* thisx, GlobalContext* globalCtx);
void BgKeikokuSaku_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Keikoku_Saku_InitVars = {
    ACTOR_BG_KEIKOKU_SAKU,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_KEIKOKU_OBJ,
    sizeof(BgKeikokuSaku),
    (ActorFunc)BgKeikokuSaku_Init,
    (ActorFunc)BgKeikokuSaku_Destroy,
    (ActorFunc)BgKeikokuSaku_Update,
    (ActorFunc)BgKeikokuSaku_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Keikoku_Saku/BgKeikokuSaku_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Keikoku_Saku/BgKeikokuSaku_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Keikoku_Saku/func_80A5389C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Keikoku_Saku/func_80A538E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Keikoku_Saku/func_80A53994.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Keikoku_Saku/BgKeikokuSaku_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Keikoku_Saku/BgKeikokuSaku_Draw.s")
