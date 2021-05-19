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
    (ActorFunc)EnSyatekiOkuta_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/EnSyatekiOkuta_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/EnSyatekiOkuta_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A36148.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A361B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A361F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A36260.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A362A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A362F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A36350.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A36360.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A363B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A36444.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A36488.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A364C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A36504.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A3657C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A365EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A368E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A36A90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A36AF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/EnSyatekiOkuta_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A36CB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A370EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A37294.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Okuta_0x80A35FF0/EnSyatekiOkuta_Draw.asm")
