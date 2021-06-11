#include "z_en_kaizoku.h"

#define FLAGS 0x00100015

#define THIS ((EnKaizoku*)thisx)

void EnKaizoku_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKaizoku_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKaizoku_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Kaizoku_InitVars = {
    ACTOR_EN_KAIZOKU,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_KZ,
    sizeof(EnKaizoku),
    (ActorFunc)EnKaizoku_Init,
    (ActorFunc)EnKaizoku_Destroy,
    (ActorFunc)EnKaizoku_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/EnKaizoku_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/EnKaizoku_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B85858.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B85900.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B85A00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B85E18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B85EA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B85F48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B85FA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B86804.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B868B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B86B58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B86B74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B872A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B872F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B874D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B8760C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B87900.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B8798C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B87C7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B87CF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B87D3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B87E28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B87E9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B87F70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B87FDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B88214.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B88278.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B8833C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B88378.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B88770.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B887AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B88910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B88964.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B88CD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B88D6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B891B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B89280.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B893CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B894C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B8960C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B8971C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B89A08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/EnKaizoku_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B8A318.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B8A468.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B8A6B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B8A718.s")
