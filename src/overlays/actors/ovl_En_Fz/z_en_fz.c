#include "z_en_fz.h"

#define FLAGS 0x00000015

#define THIS ((EnFz*)thisx)

void EnFz_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFz_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFz_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFz_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Fz_InitVars = {
    ACTOR_EN_FZ,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_FZ,
    sizeof(EnFz),
    (ActorFunc)EnFz_Init,
    (ActorFunc)EnFz_Destroy,
    (ActorFunc)EnFz_Update,
    (ActorFunc)EnFz_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/EnFz_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/EnFz_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80932784.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_809328A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_809328F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80932AE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80932AF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80932BD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80932C98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80933014.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_809330D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80933104.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80933184.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_809331F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80933248.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80933274.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80933324.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80933368.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_809333A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_809333D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80933414.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80933444.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80933480.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_809334B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_809336C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80933760.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80933790.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_809337D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_8093389C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_809338E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80933AF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80933B38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80933B48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/EnFz_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/EnFz_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80934018.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_809340BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80934178.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fz_0x80932490/func_80934464.asm")
