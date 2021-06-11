#include "z_en_slime.h"

#define FLAGS 0x00000215

#define THIS ((EnSlime*)thisx)

void EnSlime_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSlime_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSlime_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSlime_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Slime_InitVars = {
    ACTOR_EN_SLIME,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_SLIME,
    sizeof(EnSlime),
    (ActorFunc)EnSlime_Init,
    (ActorFunc)EnSlime_Destroy,
    (ActorFunc)EnSlime_Update,
    (ActorFunc)EnSlime_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/EnSlime_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/EnSlime_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2EFAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F028.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F0A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F110.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F140.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F180.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F1A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F418.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F684.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F6CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F8B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F8E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2F9A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2FA88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2FB60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2FBA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2FD94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A2FE38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30018.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30344.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30454.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A304B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A3072C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30778.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30924.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30944.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A309C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30A20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30AE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30BE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30C2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30C68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30CEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/func_80A30F98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/EnSlime_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Slime/EnSlime_Draw.s")
