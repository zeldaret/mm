#include "z_en_nb.h"

#define FLAGS 0x00000039

#define THIS ((EnNb*)thisx)

void EnNb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNb_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Nb_InitVars = {
    ACTOR_EN_NB,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_NB,
    sizeof(EnNb),
    (ActorFunc)EnNb_Init,
    (ActorFunc)EnNb_Destroy,
    (ActorFunc)EnNb_Update,
    (ActorFunc)EnNb_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BBFDB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BBFE60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BBFE8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BBFF24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BBFF90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BBFFD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC0050.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC00AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC01DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC045C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC04FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC05A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC06C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC0800.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC08E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC0978.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC0A18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC0B98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC0C0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC0C80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC0D08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC0D1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC0D84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC0EAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/EnNb_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/EnNb_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/EnNb_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC1174.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC11B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/func_80BC1278.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Nb_0x80BBFDB0/EnNb_Draw.asm")
