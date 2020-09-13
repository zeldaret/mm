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
    ACTORTYPE_PROP,
    FLAGS,
    GAMEPLAY_DANGEON_KEEP,
    sizeof(EnHonotrap),
    (ActorFunc)EnHonotrap_Init,
    (ActorFunc)EnHonotrap_Destroy,
    (ActorFunc)EnHonotrap_Update,
    (ActorFunc)EnHonotrap_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092E510.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092E5A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092E638.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092E840.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092E988.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/EnHonotrap_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/EnHonotrap_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092EBC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092EBDC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092EC9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092ECF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092EDC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092EDD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092EE08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092EE1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092EE68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092EE90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092EF3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092EF98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092F05C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092F074.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092F0A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092F0B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092F0F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092F10C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092F1A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092F208.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092F34C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092F3D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092F5AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092F5EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092F7A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092F7BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092F854.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092F878.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/EnHonotrap_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092FE44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_8092FEFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/EnHonotrap_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_80930030.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Honotrap_0x8092E510/func_80930190.asm")
