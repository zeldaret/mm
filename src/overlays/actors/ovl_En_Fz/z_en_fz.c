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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/EnFz_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/EnFz_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80932784.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809328A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809328F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80932AE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80932AF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80932BD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80932C98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933014.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809330D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933104.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933184.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809331F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933248.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933274.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933324.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933368.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809333A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809333D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933444.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933480.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809334B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809336C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933760.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933790.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809337D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_8093389C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809338E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933AF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933B38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933B48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/EnFz_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/EnFz_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80934018.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809340BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80934178.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80934464.asm")
