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
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_TL,
    sizeof(EnBigpamet),
    (ActorFunc)EnBigpamet_Init,
    (ActorFunc)EnBigpamet_Destroy,
    (ActorFunc)EnBigpamet_Update,
    (ActorFunc)EnBigpamet_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/EnBigpamet_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/EnBigpamet_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A2768C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A276F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A2778C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A27970.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A27B58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A27DD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A27FE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A2811C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A281B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A281DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28274.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A282C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28378.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A283A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A283F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A2844C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A284E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A2855C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28618.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A2866C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A286C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A287E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28970.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A289C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28A28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28A98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28B98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28D0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28D80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28DC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28E40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28E98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28ED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A28EE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A29028.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A29094.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/EnBigpamet_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A292A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A293E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A29494.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/EnBigpamet_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A29580.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A29628.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpamet/func_80A2966C.s")
