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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/EnJs_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/EnJs_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_80968A5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_80968B18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_80968B8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_80968CB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_80968DD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_80968E38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_80968F48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_809691B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_809692A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_8096933C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_80969400.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_80969494.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_809694E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_80969530.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_809695FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_80969688.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_809696EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_8096971C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_80969748.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_80969898.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_80969AA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_80969B5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_80969C54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_80969DA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_8096A080.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_8096A104.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_8096A184.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_8096A1E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_8096A2C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_8096A38C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_8096A6F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/EnJs_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/func_8096A9F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Js_0x809687B0/EnJs_Draw.asm")
