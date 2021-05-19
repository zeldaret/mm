#include "z_dm_al.h"

#define FLAGS 0x00000009

#define THIS ((DmAl*)thisx)

void DmAl_Init(Actor* thisx, GlobalContext* globalCtx);
void DmAl_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmAl_Update(Actor* thisx, GlobalContext* globalCtx);
void DmAl_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_Al_InitVars = {
    ACTOR_EN_AL,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AL,
    sizeof(DmAl),
    (ActorFunc)DmAl_Init,
    (ActorFunc)DmAl_Destroy,
    (ActorFunc)DmAl_Update,
    (ActorFunc)DmAl_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Al_0x80C1BD90/func_80C1BD90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Al_0x80C1BD90/func_80C1BDD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Al_0x80C1BD90/DmAl_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Al_0x80C1BD90/DmAl_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Al_0x80C1BD90/DmAl_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Al_0x80C1BD90/func_80C1C028.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Al_0x80C1BD90/func_80C1C064.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Al_0x80C1BD90/func_80C1C11C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Al_0x80C1BD90/DmAl_Draw.asm")
