#include "z_en_mnk.h"

#define FLAGS 0x00000019

#define THIS ((EnMnk*)thisx)

void EnMnk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMnk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMnk_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMnk_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Mnk_InitVars = {
    ACTOR_EN_MNK,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_MNK,
    sizeof(EnMnk),
    (ActorFunc)EnMnk_Init,
    (ActorFunc)EnMnk_Destroy,
    (ActorFunc)EnMnk_Update,
    (ActorFunc)EnMnk_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB4D10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB4E34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB4E58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB4E88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB4F68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB4F8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB50B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB50D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB5148.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB51C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB52E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/EnMnk_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/EnMnk_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB5A64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB5B38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB5B84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB5BCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB5C14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB5C74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB5CD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB5F6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB60FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB61E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB6304.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB63CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB64B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB65F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB675C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB6870.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB6920.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB69C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB6AF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB6B78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB6BE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB6E08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB6EB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB6F98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB7108.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB7204.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB72BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB7354.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB740C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB7488.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB7504.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB75A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB7620.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB76B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB794C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB7AC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB7B20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB7DCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB7E50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB8040.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB80BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB81D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB8478.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB852C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB85C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB8644.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB86AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB8750.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB8878.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB8968.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB89F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB8A74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB8B18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB8BD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB8C60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB8CFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB8E4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB8EF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB8FD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB9084.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB92CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB94E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/EnMnk_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB96A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB96E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB9708.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB973C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB977C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB97B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB99D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/EnMnk_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB9BAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mnk_0x80AB4D10/func_80AB9C4C.asm")
