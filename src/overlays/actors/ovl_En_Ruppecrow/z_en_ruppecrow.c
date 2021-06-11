#include "z_en_ruppecrow.h"

#define FLAGS 0x00004030

#define THIS ((EnRuppecrow*)thisx)

void EnRuppecrow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRuppecrow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRuppecrow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRuppecrow_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ruppecrow_InitVars = {
    ACTOR_EN_RUPPECROW,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_CROW,
    sizeof(EnRuppecrow),
    (ActorFunc)EnRuppecrow_Init,
    (ActorFunc)EnRuppecrow_Destroy,
    (ActorFunc)EnRuppecrow_Update,
    (ActorFunc)EnRuppecrow_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2260.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2330.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE24CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2668.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2728.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2794.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2808.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2874.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2B80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2D4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2E18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2F6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE30F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE3178.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE32DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE3354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE348C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE35A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/EnRuppecrow_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/EnRuppecrow_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/EnRuppecrow_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/EnRuppecrow_Draw.s")
