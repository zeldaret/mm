#include "z_en_hgo.h"

#define FLAGS 0x02000019

#define THIS ((EnHgo*)thisx)

void EnHgo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHgo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHgo_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHgo_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Hgo_InitVars = {
    ACTOR_EN_HGO,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_HARFGIBUD,
    sizeof(EnHgo),
    (ActorFunc)EnHgo_Init,
    (ActorFunc)EnHgo_Destroy,
    (ActorFunc)EnHgo_Update,
    (ActorFunc)EnHgo_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Hgo_0x80BD02B0/EnHgo_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hgo_0x80BD02B0/EnHgo_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hgo_0x80BD02B0/func_80BD03EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hgo_0x80BD02B0/func_80BD0410.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hgo_0x80BD02B0/func_80BD0420.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hgo_0x80BD02B0/func_80BD0434.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hgo_0x80BD02B0/func_80BD049C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hgo_0x80BD02B0/func_80BD04E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hgo_0x80BD02B0/func_80BD064C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hgo_0x80BD02B0/func_80BD0660.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hgo_0x80BD02B0/func_80BD06FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hgo_0x80BD02B0/func_80BD0898.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hgo_0x80BD02B0/func_80BD0B8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hgo_0x80BD02B0/EnHgo_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hgo_0x80BD02B0/func_80BD0CF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hgo_0x80BD02B0/func_80BD0D38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hgo_0x80BD02B0/EnHgo_Draw.asm")
