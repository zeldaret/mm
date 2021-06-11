#include "z_en_js.h"

#define FLAGS 0x00000019

#define THIS ((EnJs*)thisx)

void EnJs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnJs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnJs_Update(Actor* thisx, GlobalContext* globalCtx);
void EnJs_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Js_InitVars = {
    ACTOR_EN_JS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OB,
    sizeof(EnJs),
    (ActorFunc)EnJs_Init,
    (ActorFunc)EnJs_Destroy,
    (ActorFunc)EnJs_Update,
    (ActorFunc)EnJs_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/EnJs_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/EnJs_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968A5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968B18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968B8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968CB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968DD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968E38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968F48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_809691B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_809692A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096933C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969400.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969494.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_809694E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969530.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_809695FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969688.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_809696EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096971C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969748.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969898.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969AA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969B5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969C54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A104.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A184.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A1E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A2C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A38C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A6F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/EnJs_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A9F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/EnJs_Draw.s")
