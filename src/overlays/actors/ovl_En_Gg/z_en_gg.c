#include "z_en_gg.h"

#define FLAGS 0x00000089

#define THIS ((EnGg*)thisx)

void EnGg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGg_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Gg_InitVars = {
    ACTOR_EN_GG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GG,
    sizeof(EnGg),
    (ActorFunc)EnGg_Init,
    (ActorFunc)EnGg_Destroy,
    (ActorFunc)EnGg_Update,
    (ActorFunc)EnGg_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B34F70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B34FB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B35108.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B351A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B35250.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B352A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B35450.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B3556C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B35634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B357F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B3584C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B358D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B35968.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B359DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B35B24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B35B44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B35C84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B3610C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B363E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B364D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/EnGg_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/EnGg_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/EnGg_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B368B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/func_80B368F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg_0x80B34F70/EnGg_Draw.asm")
