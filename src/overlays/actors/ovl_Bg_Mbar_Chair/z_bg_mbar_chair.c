#include "z_bg_mbar_chair.h"

#define FLAGS 0x00000000

#define THIS ((BgMbarChair*)thisx)

void BgMbarChair_Init(Actor* thisx, GlobalContext* globalCtx);
void BgMbarChair_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgMbarChair_Update(Actor* thisx, GlobalContext* globalCtx);
void BgMbarChair_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Mbar_Chair_InitVars = {
    ACTOR_BG_MBAR_CHAIR,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_MBAR_OBJ,
    sizeof(BgMbarChair),
    (ActorFunc)BgMbarChair_Init,
    (ActorFunc)BgMbarChair_Destroy,
    (ActorFunc)BgMbarChair_Update,
    (ActorFunc)BgMbarChair_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Mbar_Chair_0x80B7E930/BgMbarChair_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Mbar_Chair_0x80B7E930/BgMbarChair_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Mbar_Chair_0x80B7E930/BgMbarChair_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Mbar_Chair_0x80B7E930/BgMbarChair_Draw.asm")
