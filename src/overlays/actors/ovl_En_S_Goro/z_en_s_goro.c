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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBCA80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBD348.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBD8F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBD93C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBD98C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBDACC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBDC34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBDCFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBDDF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBDE78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBDF28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBDFA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBE05C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBE0E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBE144.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBE374.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBE498.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBE73C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBE844.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBE904.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBE9F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBEAD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBEBF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBECBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBEEB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBEF34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBEFA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBF01C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/EnSGoro_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/EnSGoro_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/EnSGoro_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBF298.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBF3D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBF3EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBF5F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/func_80BBF6BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_S_Goro_0x80BBCA80/EnSGoro_Draw.asm")
