#include "z_bg_lotus.h"

#define FLAGS 0x00000000

#define THIS ((BgLotus*)thisx)

void BgLotus_Init(Actor* thisx, GlobalContext* globalCtx);
void BgLotus_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgLotus_Update(Actor* thisx, GlobalContext* globalCtx);
void BgLotus_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Lotus_InitVars = {
    ACTOR_BG_LOTUS,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_LOTUS,
    sizeof(BgLotus),
    (ActorFunc)BgLotus_Init,
    (ActorFunc)BgLotus_Destroy,
    (ActorFunc)BgLotus_Update,
    (ActorFunc)BgLotus_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Lotus_0x80AD6760/BgLotus_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Lotus_0x80AD6760/BgLotus_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Lotus_0x80AD6760/func_80AD6830.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Lotus_0x80AD6760/func_80AD68DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Lotus_0x80AD6760/func_80AD6A88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Lotus_0x80AD6760/func_80AD6B68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Lotus_0x80AD6760/BgLotus_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Lotus_0x80AD6760/BgLotus_Draw.asm")
