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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_OKUTA,
    sizeof(EnSyatekiOkuta),
    (ActorFunc)EnSyatekiOkuta_Init,
    (ActorFunc)EnSyatekiOkuta_Destroy,
    (ActorFunc)EnSyatekiOkuta_Update,
    (ActorFunc)EnSyatekiOkuta_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/EnSyatekiOkuta_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/EnSyatekiOkuta_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A36148.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A361B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A361F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A36260.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A362A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A362F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A36350.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A36360.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A363B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A36444.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A36488.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A364C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A36504.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A3657C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A365EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A368E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A36A90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A36AF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/EnSyatekiOkuta_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A36CB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A370EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/func_80A37294.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Syateki_Okuta_0x80A35FF0/EnSyatekiOkuta_Draw.asm")
