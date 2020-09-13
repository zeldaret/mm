#include "z_dm_char08.h"

#define FLAGS 0x02000000

#define THIS ((DmChar08*)thisx)

void DmChar08_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar08_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar08_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar08_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_Char08_InitVars = {
    ACTOR_DM_CHAR08,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_KAMEJIMA,
    sizeof(DmChar08),
    (ActorFunc)DmChar08_Init,
    (ActorFunc)DmChar08_Destroy,
    (ActorFunc)DmChar08_Update,
    (ActorFunc)DmChar08_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AAF050.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AAF15C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/DmChar08_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/DmChar08_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AAF610.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AAF79C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AAF884.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AAF8F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AAFA18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AAFAC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AAFAE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AAFB04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AAFB94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AAFBA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AAFCCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AAFE78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AAFE88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AB01E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AB023C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AB032C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AB096C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AB0A10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/DmChar08_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AB0E3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AB0E7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/func_80AB0F90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char08_0x80AAF050/DmChar08_Draw.asm")
