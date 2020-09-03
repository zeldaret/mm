#include "z_en_stone_heishi.h"

#define FLAGS 0x00000089

#define THIS ((EnStoneheishi*)thisx)

void EnStoneheishi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnStoneheishi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnStoneheishi_Update(Actor* thisx, GlobalContext* globalCtx);
void EnStoneheishi_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Stone_heishi_InitVars = {
    ACTOR_EN_STONE_HEISHI,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_SDN,
    sizeof(EnStoneheishi),
    (ActorFunc)EnStoneheishi_Init,
    (ActorFunc)EnStoneheishi_Destroy,
    (ActorFunc)EnStoneheishi_Update,
    (ActorFunc)EnStoneheishi_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Stone_heishi_0x80BC9270/EnStoneheishi_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stone_heishi_0x80BC9270/EnStoneheishi_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stone_heishi_0x80BC9270/func_80BC935C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stone_heishi_0x80BC9270/func_80BC941C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stone_heishi_0x80BC9270/func_80BC94B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stone_heishi_0x80BC9270/func_80BC9560.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stone_heishi_0x80BC9270/func_80BC9660.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stone_heishi_0x80BC9270/func_80BC9680.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stone_heishi_0x80BC9270/func_80BC98EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stone_heishi_0x80BC9270/func_80BC9908.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stone_heishi_0x80BC9270/func_80BC9A10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stone_heishi_0x80BC9270/func_80BC9A2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stone_heishi_0x80BC9270/func_80BC9C88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stone_heishi_0x80BC9270/func_80BC9D28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stone_heishi_0x80BC9270/func_80BC9E50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stone_heishi_0x80BC9270/EnStoneheishi_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stone_heishi_0x80BC9270/func_80BCA0AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stone_heishi_0x80BC9270/func_80BCA104.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stone_heishi_0x80BC9270/EnStoneheishi_Draw.asm")
