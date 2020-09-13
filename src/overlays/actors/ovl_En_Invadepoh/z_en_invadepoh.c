#include "z_en_invadepoh.h"

#define FLAGS 0x00000010

#define THIS ((EnInvadepoh*)thisx)

void EnInvadepoh_Init(Actor* thisx, GlobalContext* globalCtx);
void EnInvadepoh_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnInvadepoh_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Invadepoh_InitVars = {
    ACTOR_EN_INVADEPOH,
    ACTORTYPE_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnInvadepoh),
    (ActorFunc)EnInvadepoh_Init,
    (ActorFunc)EnInvadepoh_Destroy,
    (ActorFunc)EnInvadepoh_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B439B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B43A24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B43A74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B43A9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B43AB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B43AF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B43B80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B43BC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B43DD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B43E6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B43F0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B43F70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B44024.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4407C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B440B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B44234.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B442E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B443A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B444BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B444F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B44514.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B44540.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B44570.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B44620.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B44640.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B44664.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B44690.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B446D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B44700.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B447C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B44A90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B44B78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B44B84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B44C24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B44C80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B44E90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B44EFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B44F58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B44FEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B45080.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B450C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4516C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B451A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B452EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B453F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B45460.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B454BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B45518.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B45550.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4560C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B45648.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B456A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B457A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B458D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B45980.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B459E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B45A4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B45A94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B45B1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B45BB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B45C04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B45CE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B45EC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46118.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46184.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B461DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4627C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46414.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46520.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B465CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46644.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B468B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B469C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46A80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/EnInvadepoh_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46BB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46BC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46C08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46C34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46C50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46C7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46C94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46CC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46CF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46D28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/EnInvadepoh_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46DA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46DC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46E20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46E44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46EC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46EE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46F88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B46FA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B47064.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B47084.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B470E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B47108.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B471C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B471E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B47248.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B47268.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B47278.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B47298.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B47304.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B47324.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/EnInvadepoh_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B47380.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B473E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B47478.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B474DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B47568.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B47600.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4770C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B477B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B47830.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B478F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B47938.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B479E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B47BAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B47D30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B47FA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B48060.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B481C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4827C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B482D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B48324.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B48374.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B483CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4843C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B484EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B48588.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B48610.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B48620.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4873C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B487B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B48848.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B48948.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B48AD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B48DE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B48E4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B48FB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B490F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B491EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B49228.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B492FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4934C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B49404.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B49454.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B49628.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B49670.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B497A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B497EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B49904.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4994C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B499BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B49A00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B49B1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B49BD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B49C38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B49DA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B49DFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B49F88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4A168.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4A1B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4A2C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4A350.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4A570.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4A5E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4A614.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4A67C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4A7C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4A81C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4A9C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4AB8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4ABDC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4ACDC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4ACF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4AD3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4AD60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4ADB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4ADCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4AEC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4AEDC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4AF80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4AF94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4B024.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4B048.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4B0C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4B218.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4B3DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4B430.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4B484.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4B510.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4B564.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4B724.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4B768.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4B820.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4B864.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4B8BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4BA30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4BA84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4BBE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4BC4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4BFFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4C058.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4C1BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4C218.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4C3A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4C568.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4C5C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4C6C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4C730.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4CAB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4CB0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4CC70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4CCCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4CE54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4CFFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4D054.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4D15C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4D290.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4D3E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4D480.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4D670.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4D760.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4D7B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4D9B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4D9D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4D9F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4DB14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4E120.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4E158.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4E1B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4E200.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4E2AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4E324.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4E3F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4E5B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4E61C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4E660.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4E6E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4E784.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_0x80B439B0/func_80B4E7BC.asm")
