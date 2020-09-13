#include "z_en_syateki_man.h"

#define FLAGS 0x08000019

#define THIS ((EnSyatekiMan*)thisx)

void EnSyatekiMan_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiMan_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiMan_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiMan_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Syateki_Man_InitVars = {
    ACTOR_EN_SYATEKI_MAN,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_SHN,
    sizeof(EnSyatekiMan),
    (ActorFunc)EnSyatekiMan_Init,
    (ActorFunc)EnSyatekiMan_Destroy,
    (ActorFunc)EnSyatekiMan_Update,
    (ActorFunc)EnSyatekiMan_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C64C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/EnSyatekiMan_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/EnSyatekiMan_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C6720.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C6810.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C6848.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C6A04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C6C2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C6E30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C6F98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C72D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C7380.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C7620.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C7990.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C7A90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C7C14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C7D14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C7EB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C7FFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C80C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C81D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C8488.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C8610.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C8710.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C8808.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C898C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C8BF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C8DE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/EnSyatekiMan_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C8EE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/func_809C8FAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Man_0x809C64C0/EnSyatekiMan_Draw.asm")
