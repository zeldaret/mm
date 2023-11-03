#include "z_en_invadepoh.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnInvadepoh*)thisx)

void EnInvadepoh_Init(Actor* thisx, PlayState* play);
void EnInvadepoh_Destroy(Actor* thisx, PlayState* play);
void EnInvadepoh_Update(Actor* thisx, PlayState* play);

#if 0
ActorInit En_Invadepoh_InitVars = {
    /**/ ACTOR_EN_INVADEPOH,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(EnInvadepoh),
    /**/ EnInvadepoh_Init,
    /**/ EnInvadepoh_Destroy,
    /**/ EnInvadepoh_Update,
    /**/ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B439B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43A24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43A74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43A9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43AB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43AF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43B80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43BC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43DD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43E6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43F0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43F70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44024.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4407C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B440B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44234.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B442E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B443A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B444BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B444F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44514.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44540.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44570.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44620.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44640.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44664.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44690.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B446D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44700.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B447C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44B78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44B84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44C24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44C80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44E90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44EFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44F58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44FEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B450C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4516C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B451A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B452EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B453F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B454BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45518.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45550.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4560C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45648.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B456A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B457A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B458D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45980.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B459E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45A4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45A94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45B1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45BB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45C04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45CE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45EC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46118.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46184.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B461DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4627C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46520.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B465CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46644.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B468B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B469C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46A80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/EnInvadepoh_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46BB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46BC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46C08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46C34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46C50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46C7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46C94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46CC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46CF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46D28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/EnInvadepoh_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46DA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46DC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46E20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46E44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46EC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46EE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46F88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46FA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47064.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47084.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B470E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47108.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B471C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B471E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47248.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47268.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47278.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47298.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47304.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47324.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/EnInvadepoh_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47380.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B473E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47478.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B474DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47568.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47600.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4770C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B477B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47830.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B478F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47938.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B479E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47BAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47D30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47FA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48060.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B481C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4827C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B482D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48324.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48374.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B483CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4843C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B484EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48588.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48610.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48620.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4873C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B487B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48848.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48948.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48AD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48DE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48E4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48FB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B490F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B491EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49228.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B492FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4934C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49404.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49454.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49628.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49670.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B497A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B497EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49904.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4994C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B499BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49A00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49B1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49BD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49C38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49DA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49DFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49F88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A1B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A2C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A570.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A5E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A614.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A67C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A7C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A81C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A9C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4AB8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4ABDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4ACDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4ACF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4AD3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4AD60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4ADB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4ADCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4AEC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4AEDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4AF80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4AF94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B024.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B048.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B0C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B218.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B3DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B430.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B484.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B510.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B564.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B724.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B768.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B864.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B8BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4BA30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4BA84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4BBE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4BC4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4BFFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4C058.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4C1BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4C218.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4C3A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4C568.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4C5C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4C6C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4C730.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4CAB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4CB0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4CC70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4CCCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4CE54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4CFFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D054.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D15C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D290.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D3E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D480.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D670.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D7B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D9B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D9D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D9F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4DB14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E120.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E158.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E1B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E200.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E2AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E324.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E3F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E5B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E61C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E6E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E784.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E7BC.s")
