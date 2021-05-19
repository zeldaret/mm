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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/EnKaizoku_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/EnKaizoku_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B85858.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B85900.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B85A00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B85E18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B85EA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B85F48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B85FA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B86804.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B868B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B86B58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B86B74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B872A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B872F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B874D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B8760C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B87900.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B8798C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B87C7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B87CF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B87D3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B87E28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B87E9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B87F70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B87FDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B88214.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B88278.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B8833C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B88378.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B88770.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B887AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B88910.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B88964.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B88CD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B88D6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B891B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B89280.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B893CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B894C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B8960C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B8971C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B89A08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/EnKaizoku_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B8A318.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B8A468.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B8A6B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kaizoku_0x80B85590/func_80B8A718.asm")
