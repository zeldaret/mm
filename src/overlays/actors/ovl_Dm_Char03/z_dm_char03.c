#include "z_dm_char03.h"

#define FLAGS 0x00000030

#define THIS ((DmChar03*)thisx)

void DmChar03_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar03_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar03_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar03_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_Char03_InitVars = {
    ACTOR_DM_CHAR03,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_OSN,
    sizeof(DmChar03),
    (ActorFunc)DmChar03_Init,
    (ActorFunc)DmChar03_Destroy,
    (ActorFunc)DmChar03_Update,
    (ActorFunc)DmChar03_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char03_0x80AAB4A0/func_80AAB4A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char03_0x80AAB4A0/DmChar03_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char03_0x80AAB4A0/DmChar03_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char03_0x80AAB4A0/func_80AAB5F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char03_0x80AAB4A0/func_80AAB644.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char03_0x80AAB4A0/func_80AAB700.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char03_0x80AAB4A0/func_80AAB710.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char03_0x80AAB4A0/func_80AAB838.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char03_0x80AAB4A0/DmChar03_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char03_0x80AAB4A0/func_80AAB974.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char03_0x80AAB4A0/func_80AAB990.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char03_0x80AAB4A0/func_80AAB9A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char03_0x80AAB4A0/DmChar03_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char03_0x80AAB4A0/func_80AABA84.asm")
