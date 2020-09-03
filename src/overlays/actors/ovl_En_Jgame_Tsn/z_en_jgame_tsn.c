#include "z_en_jgame_tsn.h"

#define FLAGS 0x02000019

#define THIS ((EnJgameTsn*)thisx)

void EnJgameTsn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnJgameTsn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnJgameTsn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnJgameTsn_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Jgame_Tsn_InitVars = {
    ACTOR_EN_JGAME_TSN,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_TSN,
    sizeof(EnJgameTsn),
    (ActorFunc)EnJgameTsn_Init,
    (ActorFunc)EnJgameTsn_Destroy,
    (ActorFunc)EnJgameTsn_Update,
    (ActorFunc)EnJgameTsn_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/EnJgameTsn_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C13A2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/EnJgameTsn_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C13B74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C13BB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C13E6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C13E90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C13F88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C13F9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C14030.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C14044.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C1410C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C1418C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C141DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C14230.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C144E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C144F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C14540.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C14554.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C145FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C14610.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C14684.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C1476C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C147B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C14960.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C149B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C14BCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C14D14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C14D58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/EnJgameTsn_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C14E64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/func_80C14EE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jgame_Tsn_0x80C13930/EnJgameTsn_Draw.asm")
