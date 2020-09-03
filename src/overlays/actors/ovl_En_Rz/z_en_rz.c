#include "z_en_rz.h"

#define FLAGS 0x00000009

#define THIS ((EnRz*)thisx)

void EnRz_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRz_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRz_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRz_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Rz_InitVars = {
    ACTOR_EN_RZ,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_RZ,
    sizeof(EnRz),
    (ActorFunc)EnRz_Init,
    (ActorFunc)EnRz_Destroy,
    (ActorFunc)EnRz_Update,
    (ActorFunc)EnRz_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/EnRz_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFB780.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFB864.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFB9E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFBA1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFBA50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFBB44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFBC78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFBCEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFBD54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFBDA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFBDFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/EnRz_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFBE70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFBFAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFC058.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFC078.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFC19C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFC214.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFC270.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFC2F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFC36C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFC3F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFC608.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFC674.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFC728.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFC7E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFC8AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFC8F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/EnRz_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/func_80BFCAD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rz_0x80BFB480/EnRz_Draw.asm")
