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
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_KEIKOKU_OBJ,
    sizeof(BgKeikokuSaku),
    (ActorFunc)BgKeikokuSaku_Init,
    (ActorFunc)BgKeikokuSaku_Destroy,
    (ActorFunc)BgKeikokuSaku_Update,
    (ActorFunc)BgKeikokuSaku_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Keikoku_Saku_0x80A537D0/BgKeikokuSaku_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Keikoku_Saku_0x80A537D0/BgKeikokuSaku_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Keikoku_Saku_0x80A537D0/func_80A5389C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Keikoku_Saku_0x80A537D0/func_80A538E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Keikoku_Saku_0x80A537D0/func_80A53994.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Keikoku_Saku_0x80A537D0/BgKeikokuSaku_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Keikoku_Saku_0x80A537D0/BgKeikokuSaku_Draw.asm")
