#include "z_en_dnh.h"

#define FLAGS 0x00000009

#define THIS ((EnDnh*)thisx)

void EnDnh_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDnh_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDnh_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDnh_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Dnh_InitVars = {
    ACTOR_EN_DNH,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TRO,
    sizeof(EnDnh),
    (ActorFunc)EnDnh_Init,
    (ActorFunc)EnDnh_Destroy,
    (ActorFunc)EnDnh_Update,
    (ActorFunc)EnDnh_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A50D40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A50DF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A50E40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A50EC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A50F38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A50F9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/EnDnh_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/EnDnh_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/EnDnh_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A51168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/EnDnh_Draw.s")
