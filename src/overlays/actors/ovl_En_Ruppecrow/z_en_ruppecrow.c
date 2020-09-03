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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_CROW,
    sizeof(EnRuppecrow),
    (ActorFunc)EnRuppecrow_Init,
    (ActorFunc)EnRuppecrow_Destroy,
    (ActorFunc)EnRuppecrow_Update,
    (ActorFunc)EnRuppecrow_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/func_80BE2260.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/func_80BE2330.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/func_80BE24CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/func_80BE2668.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/func_80BE2728.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/func_80BE2794.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/func_80BE2808.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/func_80BE2874.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/func_80BE2B80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/func_80BE2D4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/func_80BE2E18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/func_80BE2F6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/func_80BE30F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/func_80BE3178.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/func_80BE32DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/func_80BE3354.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/func_80BE348C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/func_80BE35A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/EnRuppecrow_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/EnRuppecrow_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/EnRuppecrow_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ruppecrow_0x80BE2260/EnRuppecrow_Draw.asm")
