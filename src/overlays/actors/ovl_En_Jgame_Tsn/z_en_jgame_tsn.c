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
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TSN,
    sizeof(EnJgameTsn),
    (ActorFunc)EnJgameTsn_Init,
    (ActorFunc)EnJgameTsn_Destroy,
    (ActorFunc)EnJgameTsn_Update,
    (ActorFunc)EnJgameTsn_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/EnJgameTsn_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C13A2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/EnJgameTsn_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C13B74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C13BB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C13E6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C13E90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C13F88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C13F9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C14030.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C14044.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C1410C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C1418C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C141DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C14230.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C144E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C144F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C14540.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C14554.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C145FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C14610.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C14684.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C1476C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C147B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C14960.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C149B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C14BCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C14D14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C14D58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/EnJgameTsn_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C14E64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/func_80C14EE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jgame_Tsn/EnJgameTsn_Draw.s")
