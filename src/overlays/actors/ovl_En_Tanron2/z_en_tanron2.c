#include "z_en_tanron2.h"

#define FLAGS 0x00000035

#define THIS ((EnTanron2*)thisx)

void EnTanron2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTanron2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTanron2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTanron2_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Tanron2_InitVars = {
    ACTOR_EN_TANRON2,
    ACTORTYPE_BOSS,
    FLAGS,
    OBJECT_BOSS04,
    sizeof(EnTanron2),
    (ActorFunc)EnTanron2_Init,
    (ActorFunc)EnTanron2_Destroy,
    (ActorFunc)EnTanron2_Update,
    (ActorFunc)EnTanron2_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron2_0x80BB67D0/EnTanron2_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron2_0x80BB67D0/EnTanron2_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron2_0x80BB67D0/func_80BB69C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron2_0x80BB67D0/func_80BB69FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron2_0x80BB67D0/func_80BB6B80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron2_0x80BB67D0/func_80BB6BD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron2_0x80BB67D0/func_80BB6F64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron2_0x80BB67D0/func_80BB6F78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron2_0x80BB67D0/func_80BB71C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron2_0x80BB67D0/func_80BB7398.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron2_0x80BB67D0/func_80BB7408.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron2_0x80BB67D0/func_80BB7578.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron2_0x80BB67D0/EnTanron2_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron2_0x80BB67D0/func_80BB7B90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron2_0x80BB67D0/EnTanron2_Draw.asm")
