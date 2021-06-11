#include "z_en_kame.h"

#define FLAGS 0x00000405

#define THIS ((EnKame*)thisx)

void EnKame_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKame_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKame_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKame_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Kame_InitVars = {
    ACTOR_EN_KAME,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_TL,
    sizeof(EnKame),
    (ActorFunc)EnKame_Init,
    (ActorFunc)EnKame_Destroy,
    (ActorFunc)EnKame_Update,
    (ActorFunc)EnKame_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/EnKame_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/EnKame_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD6F34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD6F9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD7018.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD70A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD70EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD71B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD7254.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD73A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD7424.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD7568.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD75A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD76CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD7798.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD792C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD7948.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD7B18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD7B90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD7C54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD7D40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD7DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD7E0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD7EC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD7F10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD7FA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD7FF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD8060.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD810C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD8148.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD825C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD8364.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD8388.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD84C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/EnKame_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD8A48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD8AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/EnKame_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD8CEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kame/func_80AD8D64.s")
