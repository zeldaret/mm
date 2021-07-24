#include "z_en_jgame_tsn.h"

#define FLAGS 0x02000019

#define THIS ((EnJgameTsn*)thisx)

void EnJgameTsn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnJgameTsn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnJgameTsn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnJgameTsn_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
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


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80C15078 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 30, 40, 0, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_80C15078;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/EnJgameTsn_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C13A2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/EnJgameTsn_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C13B74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C13BB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C13E6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C13E90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C13F88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C13F9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C14030.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C14044.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C1410C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C1418C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C141DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C14230.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C144E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C144F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C14540.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C14554.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C145FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C14610.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C14684.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C1476C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C147B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C14960.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C149B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C14BCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C14D14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C14D58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/EnJgameTsn_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C14E64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/func_80C14EE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jgame_Tsn_0x80C13930/EnJgameTsn_Draw.asm")
