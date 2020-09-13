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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_OF1D_MAP,
    sizeof(EnGeg),
    (ActorFunc)EnGeg_Init,
    (ActorFunc)EnGeg_Destroy,
    (ActorFunc)EnGeg_Update,
    (ActorFunc)EnGeg_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB16D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB178C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB18FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB19C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB1B14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB1C1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB1C8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB1D04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB1D64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB1FCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB2020.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB2088.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB217C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB221C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB2520.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB26EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB27D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB2944.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB2A54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB2B1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB2E00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB2F7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB30B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB31B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB32AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB3318.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB347C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/EnGeg_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/EnGeg_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/EnGeg_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB3728.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB3860.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB387C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB39F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB3BE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/func_80BB3CB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Geg_0x80BB16D0/EnGeg_Draw.asm")
