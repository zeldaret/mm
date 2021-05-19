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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/func_80BE2260.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/func_80BE2330.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/func_80BE24CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/func_80BE2668.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/func_80BE2728.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/func_80BE2794.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/func_80BE2808.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/func_80BE2874.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/func_80BE2B80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/func_80BE2D4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/func_80BE2E18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/func_80BE2F6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/func_80BE30F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/func_80BE3178.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/func_80BE32DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/func_80BE3354.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/func_80BE348C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/func_80BE35A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/EnRuppecrow_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/EnRuppecrow_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/EnRuppecrow_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ruppecrow_0x80BE2260/EnRuppecrow_Draw.asm")
