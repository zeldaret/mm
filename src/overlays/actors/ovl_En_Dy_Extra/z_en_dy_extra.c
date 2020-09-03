#include "z_en_dy_extra.h"

#define FLAGS 0x00000030

#define THIS ((EnDyExtra*)thisx)

void EnDyExtra_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDyExtra_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDyExtra_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDyExtra_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Dy_Extra_InitVars = {
    ACTOR_EN_DY_EXTRA,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_DY_OBJ,
    sizeof(EnDyExtra),
    (ActorFunc)EnDyExtra_Init,
    (ActorFunc)EnDyExtra_Destroy,
    (ActorFunc)EnDyExtra_Update,
    (ActorFunc)EnDyExtra_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Dy_Extra_0x80A612B0/EnDyExtra_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dy_Extra_0x80A612B0/EnDyExtra_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dy_Extra_0x80A612B0/func_80A61334.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dy_Extra_0x80A612B0/func_80A613C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dy_Extra_0x80A612B0/EnDyExtra_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dy_Extra_0x80A612B0/EnDyExtra_Draw.asm")
