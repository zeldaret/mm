#include "z_en_dodongo.h"

#define FLAGS 0x00000405

#define THIS ((EnDodongo*)thisx)

void EnDodongo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDodongo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDodongo_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDodongo_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Dodongo_InitVars = {
    ACTOR_EN_DODONGO,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DODONGO,
    sizeof(EnDodongo),
    (ActorFunc)EnDodongo_Init,
    (ActorFunc)EnDodongo_Destroy,
    (ActorFunc)EnDodongo_Update,
    (ActorFunc)EnDodongo_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/EnDodongo_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/EnDodongo_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80876930.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80876B08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80876BD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80876CAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80876D28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80876DC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_8087721C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80877278.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_808773C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80877424.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80877494.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80877500.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_808777A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_8087784C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80877D50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80877D90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80877DE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80877E60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80878354.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80878424.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80878594.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_808785B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_8087864C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_808786C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80878724.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_808787B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80878910.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/EnDodongo_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80878E44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80878EB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/EnDodongo_Draw.asm")
