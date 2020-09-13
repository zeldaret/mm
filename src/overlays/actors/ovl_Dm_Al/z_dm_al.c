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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_AL,
    sizeof(DmAl),
    (ActorFunc)DmAl_Init,
    (ActorFunc)DmAl_Destroy,
    (ActorFunc)DmAl_Update,
    (ActorFunc)DmAl_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Al_0x80C1BD90/func_80C1BD90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Al_0x80C1BD90/func_80C1BDD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Al_0x80C1BD90/DmAl_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Al_0x80C1BD90/DmAl_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Al_0x80C1BD90/DmAl_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Al_0x80C1BD90/func_80C1C028.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Al_0x80C1BD90/func_80C1C064.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Al_0x80C1BD90/func_80C1C11C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Al_0x80C1BD90/DmAl_Draw.asm")
