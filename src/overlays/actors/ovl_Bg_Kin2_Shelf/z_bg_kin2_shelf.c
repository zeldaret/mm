#include "z_bg_kin2_shelf.h"

#define FLAGS 0x00000000

#define THIS ((BgKin2Shelf*)thisx)

void BgKin2Shelf_Init(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Shelf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Shelf_Update(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Shelf_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Kin2_Shelf_InitVars = {
    ACTOR_BG_KIN2_SHELF,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_KIN2_OBJ,
    sizeof(BgKin2Shelf),
    (ActorFunc)BgKin2Shelf_Init,
    (ActorFunc)BgKin2Shelf_Destroy,
    (ActorFunc)BgKin2Shelf_Update,
    (ActorFunc)BgKin2Shelf_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Shelf_0x80B6FB30/func_80B6FB30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Shelf_0x80B6FB30/func_80B6FCA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Shelf_0x80B6FB30/func_80B6FE08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Shelf_0x80B6FB30/func_80B6FE48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Shelf_0x80B6FB30/func_80B6FEBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Shelf_0x80B6FB30/func_80B6FF28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Shelf_0x80B6FB30/BgKin2Shelf_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Shelf_0x80B6FB30/BgKin2Shelf_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Shelf_0x80B6FB30/func_80B700A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Shelf_0x80B6FB30/func_80B700C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Shelf_0x80B6FB30/func_80B70214.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Shelf_0x80B6FB30/func_80B70230.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Shelf_0x80B6FB30/func_80B70498.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Shelf_0x80B6FB30/func_80B704B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Shelf_0x80B6FB30/BgKin2Shelf_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Shelf_0x80B6FB30/BgKin2Shelf_Draw.asm")
