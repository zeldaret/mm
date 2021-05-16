#include "z_en_syateki_okuta.h"

#define FLAGS 0x08000030

#define THIS ((EnSyatekiOkuta*)thisx)

void EnSyatekiOkuta_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiOkuta_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiOkuta_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiOkuta_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Syateki_Okuta_InitVars = {
    ACTOR_EN_SYATEKI_OKUTA,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_OKUTA,
    sizeof(EnSyatekiOkuta),
    (ActorFunc)EnSyatekiOkuta_Init,
    (ActorFunc)EnSyatekiOkuta_Destroy,
    (ActorFunc)EnSyatekiOkuta_Update,
    (ActorFunc)EnSyatekiOkuta_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/EnSyatekiOkuta_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/EnSyatekiOkuta_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36148.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A361B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A361F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36260.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A362A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A362F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36360.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A363B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36444.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A364C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36504.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A3657C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A365EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A368E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/EnSyatekiOkuta_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36CB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A370EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A37294.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/EnSyatekiOkuta_Draw.s")
