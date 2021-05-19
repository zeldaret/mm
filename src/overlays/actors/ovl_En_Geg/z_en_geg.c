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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB16D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB178C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB18FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB19C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB1B14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB1C1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB1C8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB1D04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB1D64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB1FCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB2020.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB2088.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB217C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB221C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB2520.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB26EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB27D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB2944.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB2A54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB2B1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB2E00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB2F7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB30B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB31B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB32AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB3318.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB347C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/EnGeg_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/EnGeg_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/EnGeg_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB3728.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB3860.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB387C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB39F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB3BE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB3CB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/EnGeg_Draw.asm")
