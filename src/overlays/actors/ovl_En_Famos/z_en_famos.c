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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_FAMOS,
    sizeof(EnFamos),
    (ActorFunc)EnFamos_Init,
    (ActorFunc)EnFamos_Destroy,
    (ActorFunc)EnFamos_Update,
    (ActorFunc)EnFamos_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/EnFamos_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/EnFamos_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808ACB58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808ACD2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808ACF1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808ACF98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AD05C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AD170.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AD18C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AD1F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AD294.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AD31C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AD378.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AD3E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AD42C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AD54C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AD5B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AD66C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AD68C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AD7EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AD840.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AD888.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AD8B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808ADA74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808ADAE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808ADB4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808ADB70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808ADC40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808ADC64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808ADD20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808ADDA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808ADE00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808ADE74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808ADFA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808ADFF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AE030.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/EnFamos_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AE304.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AE3A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/func_808AE3FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Famos_0x808AC920/EnFamos_Draw.asm")
