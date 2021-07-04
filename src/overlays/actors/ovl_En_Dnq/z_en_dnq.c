#include "z_en_dnq.h"

#define FLAGS 0x00000009

#define THIS ((EnDnq*)thisx)

void EnDnq_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDnq_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDnq_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDnq_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Dnq_InitVars = {
    ACTOR_EN_DNQ,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNQ,
    sizeof(EnDnq),
    (ActorFunc)EnDnq_Init,
    (ActorFunc)EnDnq_Destroy,
    (ActorFunc)EnDnq_Update,
    (ActorFunc)EnDnq_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnq_0x80A52530/func_80A52530.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnq_0x80A52530/func_80A5257C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnq_0x80A52530/func_80A52604.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnq_0x80A52530/func_80A52648.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnq_0x80A52530/func_80A526F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnq_0x80A52530/func_80A52944.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnq_0x80A52530/func_80A52A78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnq_0x80A52530/func_80A52B68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnq_0x80A52530/func_80A52C6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnq_0x80A52530/func_80A52CF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnq_0x80A52530/func_80A52D44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnq_0x80A52530/func_80A52DC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnq_0x80A52530/func_80A52FB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnq_0x80A52530/func_80A53038.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnq_0x80A52530/EnDnq_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnq_0x80A52530/EnDnq_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnq_0x80A52530/EnDnq_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnq_0x80A52530/EnDnq_Draw.asm")
