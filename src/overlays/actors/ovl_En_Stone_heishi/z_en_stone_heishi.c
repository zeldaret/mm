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
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SDN,
    sizeof(EnStoneheishi),
    (ActorFunc)EnStoneheishi_Init,
    (ActorFunc)EnStoneheishi_Destroy,
    (ActorFunc)EnStoneheishi_Update,
    (ActorFunc)EnStoneheishi_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stone_heishi_0x80BC9270/EnStoneheishi_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stone_heishi_0x80BC9270/EnStoneheishi_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stone_heishi_0x80BC9270/func_80BC935C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stone_heishi_0x80BC9270/func_80BC941C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stone_heishi_0x80BC9270/func_80BC94B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stone_heishi_0x80BC9270/func_80BC9560.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stone_heishi_0x80BC9270/func_80BC9660.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stone_heishi_0x80BC9270/func_80BC9680.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stone_heishi_0x80BC9270/func_80BC98EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stone_heishi_0x80BC9270/func_80BC9908.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stone_heishi_0x80BC9270/func_80BC9A10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stone_heishi_0x80BC9270/func_80BC9A2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stone_heishi_0x80BC9270/func_80BC9C88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stone_heishi_0x80BC9270/func_80BC9D28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stone_heishi_0x80BC9270/func_80BC9E50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stone_heishi_0x80BC9270/EnStoneheishi_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stone_heishi_0x80BC9270/func_80BCA0AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stone_heishi_0x80BC9270/func_80BCA104.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stone_heishi_0x80BC9270/EnStoneheishi_Draw.asm")
