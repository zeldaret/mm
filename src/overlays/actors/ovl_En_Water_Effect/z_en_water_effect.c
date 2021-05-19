#include "z_en_water_effect.h"

#define FLAGS 0x00000035

#define THIS ((EnWaterEffect*)thisx)

void EnWaterEffect_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWaterEffect_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWaterEffect_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWaterEffect_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Water_Effect_0x80A587A0/func_80A587A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Water_Effect_0x80A587A0/func_80A58908.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Water_Effect_0x80A587A0/EnWaterEffect_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Water_Effect_0x80A587A0/EnWaterEffect_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Water_Effect_0x80A587A0/EnWaterEffect_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Water_Effect_0x80A587A0/EnWaterEffect_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Water_Effect_0x80A587A0/func_80A599E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Water_Effect_0x80A587A0/func_80A59C04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Water_Effect_0x80A587A0/func_80A5A184.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Water_Effect_0x80A587A0/func_80A5A534.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Water_Effect_0x80A587A0/func_80A5A6B8.asm")
