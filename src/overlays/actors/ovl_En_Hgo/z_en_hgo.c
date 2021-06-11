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
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_HARFGIBUD,
    sizeof(EnHgo),
    (ActorFunc)EnHgo_Init,
    (ActorFunc)EnHgo_Destroy,
    (ActorFunc)EnHgo_Update,
    (ActorFunc)EnHgo_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hgo/EnHgo_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hgo/EnHgo_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hgo/func_80BD03EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hgo/func_80BD0410.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hgo/func_80BD0420.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hgo/func_80BD0434.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hgo/func_80BD049C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hgo/func_80BD04E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hgo/func_80BD064C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hgo/func_80BD0660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hgo/func_80BD06FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hgo/func_80BD0898.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hgo/func_80BD0B8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hgo/EnHgo_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hgo/func_80BD0CF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hgo/func_80BD0D38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hgo/EnHgo_Draw.s")
