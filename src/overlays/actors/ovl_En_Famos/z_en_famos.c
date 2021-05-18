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
    (ActorFunc)EnFamos_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/EnFamos_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/EnFamos_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ACB58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ACD2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ACF1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ACF98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD05C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD170.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD18C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD1F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD294.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD31C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD378.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD3E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD42C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD54C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD5B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD66C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD68C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD7EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD888.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD8B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADA74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADAE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADB4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADB70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADC40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADC64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADD20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADDA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADE00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADE74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADFA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADFF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AE030.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/EnFamos_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AE304.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AE3A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AE3FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/EnFamos_Draw.asm")
