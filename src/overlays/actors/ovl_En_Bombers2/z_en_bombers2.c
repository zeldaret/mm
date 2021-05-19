#include "z_en_bombers2.h"

#define FLAGS 0x00000009

#define THIS ((EnBombers2*)thisx)

void EnBombers2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBombers2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBombers2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBombers2_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bombers2_InitVars = {
    ACTOR_EN_BOMBERS2,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_CS,
    sizeof(EnBombers2),
    (ActorFunc)EnBombers2_Init,
    (ActorFunc)EnBombers2_Destroy,
    (ActorFunc)EnBombers2_Update,
    (ActorFunc)EnBombers2_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombers2_0x80C04930/EnBombers2_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombers2_0x80C04930/EnBombers2_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombers2_0x80C04930/func_80C04AAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombers2_0x80C04930/func_80C04B40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombers2_0x80C04930/func_80C04BA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombers2_0x80C04930/func_80C04D00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombers2_0x80C04930/func_80C04D8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombers2_0x80C04930/func_80C050B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombers2_0x80C04930/func_80C0520C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombers2_0x80C04930/EnBombers2_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombers2_0x80C04930/func_80C056D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombers2_0x80C04930/EnBombers2_Draw.asm")
