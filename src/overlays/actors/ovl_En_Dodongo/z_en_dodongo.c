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
    (ActorFunc)EnDodongo_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/EnDodongo_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/EnDodongo_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80876930.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80876B08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80876BD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80876CAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80876D28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80876DC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_8087721C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80877278.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_808773C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80877424.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80877494.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80877500.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_808777A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_8087784C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80877D50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80877D90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80877DE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80877E60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80878354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80878424.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80878594.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_808785B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_8087864C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_808786C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80878724.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_808787B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80878910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/EnDodongo_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80878E44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/func_80878EB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dodongo/EnDodongo_Draw.s")
