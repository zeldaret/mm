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
    (ActorFunc)EnHonotrap_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092E510.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092E5A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092E638.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092E840.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092E988.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/EnHonotrap_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/EnHonotrap_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EBC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EBDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EC9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092ECF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EDC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EDD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EE08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EE1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EE68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EE90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EF3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EF98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F05C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F074.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F0A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F0B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F0F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F10C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F1A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F208.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F34C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F3D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F5AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F5EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F7A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F7BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F854.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F878.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/EnHonotrap_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092FE44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092FEFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/EnHonotrap_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_80930030.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_80930190.s")
