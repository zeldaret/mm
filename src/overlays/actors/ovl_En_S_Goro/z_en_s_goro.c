#include "z_en_s_goro.h"

#define FLAGS 0x00000019

#define THIS ((EnSGoro*)thisx)

void EnSGoro_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSGoro_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSGoro_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSGoro_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_S_Goro_InitVars = {
    ACTOR_EN_S_GORO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OF1D_MAP,
    sizeof(EnSGoro),
    (ActorFunc)EnSGoro_Init,
    (ActorFunc)EnSGoro_Destroy,
    (ActorFunc)EnSGoro_Update,
    (ActorFunc)EnSGoro_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBCA80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBD348.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBD8F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBD93C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBD98C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBDACC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBDC34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBDCFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBDDF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBDE78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBDF28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBDFA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBE05C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBE0E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBE144.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBE374.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBE498.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBE73C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBE844.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBE904.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBE9F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBEAD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBEBF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBECBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBEEB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBEF34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBEFA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBF01C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/EnSGoro_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/EnSGoro_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/EnSGoro_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBF298.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBF3D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBF3EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBF5F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBF6BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/EnSGoro_Draw.s")
