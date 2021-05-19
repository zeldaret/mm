#include "z_en_bomjimb.h"

#define FLAGS 0x00000009

#define THIS ((EnBomjimb*)thisx)

void EnBomjimb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBomjimb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBomjimb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBomjimb_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bomjimb_InitVars = {
    ACTOR_EN_BOMJIMB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_CS,
    sizeof(EnBomjimb),
    (ActorFunc)EnBomjimb_Init,
    (ActorFunc)EnBomjimb_Destroy,
    (ActorFunc)EnBomjimb_Update,
    (ActorFunc)EnBomjimb_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/EnBomjimb_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/EnBomjimb_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C0113C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C011CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C012E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C012FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C013B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C013F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C01494.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C014E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C01984.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C01A24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C01B40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C01B74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C01C18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C01CD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C01FD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C0201C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C02108.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C0217C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C0250C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C02570.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C0267C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C02704.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C02740.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C02A14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C02BCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C02CA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C02DAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/EnBomjimb_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/func_80C02FA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjimb_0x80C00EA0/EnBomjimb_Draw.asm")
