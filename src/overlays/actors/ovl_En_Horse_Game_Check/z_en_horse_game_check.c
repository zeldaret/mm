/*
 * File: z_en_horse_game_check.c
 * Overlay: ovl_En_Horse_Game_Check
 * Description:
 */

#include "z_en_horse_game_check.h"

#define FLAGS 0x00000010

#define THIS ((EnHorseGameCheck*)thisx)

void EnHorseGameCheck_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHorseGameCheck_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHorseGameCheck_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHorseGameCheck_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Horse_Game_Check_InitVars = {
    ACTOR_EN_HORSE_GAME_CHECK,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_HORSE_GAME_CHECK,
    sizeof(EnHorseGameCheck),
    (ActorFunc)EnHorseGameCheck_Init,
    (ActorFunc)EnHorseGameCheck_Destroy,
    (ActorFunc)EnHorseGameCheck_Update,
    (ActorFunc)EnHorseGameCheck_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808F9BDC[] = {
    ICHAIN_F32(uncullZoneScale, 2400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_808F9BDC[];

extern UNK_TYPE D_060014B0;
extern UNK_TYPE D_06002FB8;
extern UNK_TYPE D_06003030;
extern UNK_TYPE D_06003918;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/func_808F8AA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/func_808F8C24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/func_808F8C5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/func_808F8C70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/func_808F8CCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/func_808F8E94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/func_808F8EB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/func_808F8FAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/func_808F96E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/func_808F9830.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/func_808F9868.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/func_808F987C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/func_808F990C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/func_808F9944.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/func_808F9958.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/func_808F999C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/func_808F99B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/func_808F99C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/func_808F99D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/EnHorseGameCheck_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/EnHorseGameCheck_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/EnHorseGameCheck_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Game_Check/EnHorseGameCheck_Draw.s")
