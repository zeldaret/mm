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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/EnSlime_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/EnSlime_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2EFAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F028.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F0A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F110.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F140.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F180.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F1A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F354.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F418.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F684.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F6CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F8B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F8E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F9A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2FA88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2FB60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2FBA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2FD94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2FE38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30018.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30344.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30454.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A304B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A3072C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30778.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30820.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30924.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30944.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A309C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30A20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30A90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30AE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30BE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30C2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30C68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30CEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30F98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/EnSlime_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/EnSlime_Draw.asm")
