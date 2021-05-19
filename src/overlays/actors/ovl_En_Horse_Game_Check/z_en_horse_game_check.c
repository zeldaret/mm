#include "z_en_horse_game_check.h"

#define FLAGS 0x00000010

#define THIS ((EnHorseGameCheck*)thisx)

void EnHorseGameCheck_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHorseGameCheck_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHorseGameCheck_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHorseGameCheck_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/func_808F8AA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/func_808F8C24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/func_808F8C5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/func_808F8C70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/func_808F8CCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/func_808F8E94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/func_808F8EB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/func_808F8FAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/func_808F96E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/func_808F9830.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/func_808F9868.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/func_808F987C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/func_808F990C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/func_808F9944.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/func_808F9958.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/func_808F999C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/func_808F99B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/func_808F99C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/func_808F99D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/EnHorseGameCheck_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/EnHorseGameCheck_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/EnHorseGameCheck_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_Game_Check_0x808F8AA0/EnHorseGameCheck_Draw.asm")
