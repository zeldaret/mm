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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnh_0x80A50D40/func_80A50D40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnh_0x80A50D40/func_80A50DF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnh_0x80A50D40/func_80A50E40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnh_0x80A50D40/func_80A50EC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnh_0x80A50D40/func_80A50F38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnh_0x80A50D40/func_80A50F9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnh_0x80A50D40/EnDnh_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnh_0x80A50D40/EnDnh_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnh_0x80A50D40/EnDnh_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnh_0x80A50D40/func_80A51168.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnh_0x80A50D40/EnDnh_Draw.asm")
