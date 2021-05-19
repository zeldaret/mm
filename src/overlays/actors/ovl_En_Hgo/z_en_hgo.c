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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/EnHgo_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/EnHgo_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD03EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD0410.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD0420.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD0434.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD049C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD04E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD064C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD0660.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD06FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD0898.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD0B8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/EnHgo_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD0CF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD0D38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/EnHgo_Draw.asm")
