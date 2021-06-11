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
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_FZ,
    sizeof(EnFz),
    (ActorFunc)EnFz_Init,
    (ActorFunc)EnFz_Destroy,
    (ActorFunc)EnFz_Update,
    (ActorFunc)EnFz_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/EnFz_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/EnFz_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80932784.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_809328A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_809328F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80932AE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80932AF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80932BD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80932C98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80933014.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_809330D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80933104.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80933184.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_809331F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80933248.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80933274.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80933324.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80933368.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_809333A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_809333D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80933414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80933444.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80933480.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_809334B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_809336C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80933760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80933790.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_809337D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_8093389C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_809338E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80933AF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80933B38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80933B48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/EnFz_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/EnFz_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80934018.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_809340BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80934178.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fz/func_80934464.s")
