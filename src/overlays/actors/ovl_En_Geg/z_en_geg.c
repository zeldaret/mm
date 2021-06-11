#include "z_en_geg.h"

#define FLAGS 0x00000019

#define THIS ((EnGeg*)thisx)

void EnGeg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGeg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGeg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGeg_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Geg_InitVars = {
    ACTOR_EN_GEG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OF1D_MAP,
    sizeof(EnGeg),
    (ActorFunc)EnGeg_Init,
    (ActorFunc)EnGeg_Destroy,
    (ActorFunc)EnGeg_Update,
    (ActorFunc)EnGeg_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB16D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB178C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB18FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB19C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB1B14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB1C1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB1C8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB1D04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB1D64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB1FCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB2020.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB2088.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB217C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB221C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB2520.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB26EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB27D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB2944.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB2A54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB2B1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB2E00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB2F7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB30B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB31B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB32AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB3318.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB347C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/EnGeg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/EnGeg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/EnGeg_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB3728.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB3860.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB387C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB39F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB3BE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/func_80BB3CB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Geg/EnGeg_Draw.s")
