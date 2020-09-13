#include "z_en_bigpamet.h"

#define FLAGS 0x00000435

#define THIS ((EnBigpamet*)thisx)

void EnBigpamet_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBigpamet_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBigpamet_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBigpamet_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bigpamet_InitVars = {
    ACTOR_EN_BIGPAMET,
    ACTORTYPE_BOSS,
    FLAGS,
    OBJECT_TL,
    sizeof(EnBigpamet),
    (ActorFunc)EnBigpamet_Init,
    (ActorFunc)EnBigpamet_Destroy,
    (ActorFunc)EnBigpamet_Update,
    (ActorFunc)EnBigpamet_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/EnBigpamet_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/EnBigpamet_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A2768C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A276F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A2778C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A27970.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A27B58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A27DD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A27FE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A2811C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A281B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A281DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A28274.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A282C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A28378.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A283A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A283F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A2844C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A284E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A2855C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A28618.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A2866C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A286C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A28708.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A28760.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A287E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A28970.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A289C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A28A28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A28A98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A28B98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A28D0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A28D80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A28DC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A28E40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A28E98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A28ED4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A28EE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A29028.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A29094.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/EnBigpamet_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A292A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A293E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A29494.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/EnBigpamet_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A29580.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A29628.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpamet_0x80A27520/func_80A2966C.asm")
