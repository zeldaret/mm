#include "z_en_famos.h"

#define FLAGS 0x00000005

#define THIS ((EnFamos*)thisx)

void EnFamos_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFamos_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFamos_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFamos_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Famos_InitVars = {
    ACTOR_EN_FAMOS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_FAMOS,
    sizeof(EnFamos),
    (ActorFunc)EnFamos_Init,
    (ActorFunc)EnFamos_Destroy,
    (ActorFunc)EnFamos_Update,
    (ActorFunc)EnFamos_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/EnFamos_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/EnFamos_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ACB58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ACD2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ACF1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ACF98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AD05C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AD170.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AD18C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AD1F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AD294.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AD31C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AD378.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AD3E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AD42C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AD54C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AD5B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AD66C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AD68C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AD7EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AD840.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AD888.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AD8B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADA74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADAE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADB4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADB70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADC40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADC64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADD20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADDA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADE00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADE74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADFA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808ADFF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AE030.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/EnFamos_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AE304.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AE3A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/func_808AE3FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Famos/EnFamos_Draw.s")
