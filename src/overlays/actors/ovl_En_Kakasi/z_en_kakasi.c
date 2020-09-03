#include "z_en_kakasi.h"

#define FLAGS 0x02000019

#define THIS ((EnKakasi*)thisx)

void EnKakasi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKakasi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKakasi_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKakasi_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Kakasi_InitVars = {
    ACTOR_EN_KAKASI,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_KA,
    sizeof(EnKakasi),
    (ActorFunc)EnKakasi_Init,
    (ActorFunc)EnKakasi_Destroy,
    (ActorFunc)EnKakasi_Update,
    (ActorFunc)EnKakasi_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/EnKakasi_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/EnKakasi_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_8096F800.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_8096F88C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_8096F8D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_8096FA18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_8096FAAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_8096FBB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_8096FC8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_8096FCC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_8096FDE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_8096FE00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_80970008.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_8097006C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_809705E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_80970658.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_80970740.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_80970978.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_80970A10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_80970A9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_80970F20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_80970FF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_80971064.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_80971430.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_80971440.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_809714BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_80971794.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_809717D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_8097185C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_8097193C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_80971A38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_80971A64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_80971AD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/EnKakasi_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/func_80971CE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kakasi_0x8096F5E0/EnKakasi_Draw.asm")
