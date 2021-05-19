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
    (ActorFunc)EnBigpamet_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/EnBigpamet_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/EnBigpamet_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A2768C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A276F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A2778C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A27970.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A27B58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A27DD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A27FE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A2811C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A281B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A281DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28274.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A282C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28378.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A283A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A283F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A2844C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A284E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A2855C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28618.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A2866C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A286C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28708.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28760.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A287E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28970.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A289C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28A28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28A98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28B98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28D0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28D80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28DC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28E40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28E98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28ED4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28EE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A29028.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A29094.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/EnBigpamet_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A292A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A293E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A29494.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/EnBigpamet_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A29580.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A29628.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A2966C.asm")
