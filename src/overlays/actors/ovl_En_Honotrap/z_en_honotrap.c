#include "z_en_honotrap.h"

#define FLAGS 0x00000010

#define THIS ((EnHonotrap*)thisx)

void EnHonotrap_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHonotrap_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHonotrap_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHonotrap_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Honotrap_InitVars = {
    ACTOR_EN_HONOTRAP,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_DANGEON_KEEP,
    sizeof(EnHonotrap),
    (ActorFunc)EnHonotrap_Init,
    (ActorFunc)EnHonotrap_Destroy,
    (ActorFunc)EnHonotrap_Update,
    (ActorFunc)EnHonotrap_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092E510.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092E5A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092E638.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092E840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092E988.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/EnHonotrap_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/EnHonotrap_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EBC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EBDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EC9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092ECF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EDC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EDD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EE08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EE1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EE68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EE90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EF3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092EF98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F05C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F074.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F0A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F0B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F0F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F10C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F1A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F208.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F34C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F3D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F5AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F5EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F7A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F7BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F854.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092F878.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/EnHonotrap_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092FE44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_8092FEFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/EnHonotrap_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_80930030.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Honotrap_0x8092E510/func_80930190.asm")
