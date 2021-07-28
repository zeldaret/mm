#include "z_en_water_effect.h"

#define FLAGS 0x00000035

#define THIS ((EnWaterEffect*)thisx)

void EnWaterEffect_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWaterEffect_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWaterEffect_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWaterEffect_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Water_Effect_InitVars = {
    ACTOR_EN_WATER_EFFECT,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_WATER_EFFECT,
    sizeof(EnWaterEffect),
    (ActorFunc)EnWaterEffect_Init,
    (ActorFunc)EnWaterEffect_Destroy,
    (ActorFunc)EnWaterEffect_Update,
    (ActorFunc)EnWaterEffect_Draw,
};

#endif

extern UNK_TYPE D_06000DE0;
extern UNK_TYPE D_060042B0;
extern UNK_TYPE D_060043E8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Water_Effect/func_80A587A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Water_Effect/func_80A58908.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Water_Effect/EnWaterEffect_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Water_Effect/EnWaterEffect_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Water_Effect/EnWaterEffect_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Water_Effect/EnWaterEffect_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Water_Effect/func_80A599E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Water_Effect/func_80A59C04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Water_Effect/func_80A5A184.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Water_Effect/func_80A5A534.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Water_Effect/func_80A5A6B8.s")
