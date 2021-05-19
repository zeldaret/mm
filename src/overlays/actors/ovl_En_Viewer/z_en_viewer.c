#include "z_en_viewer.h"

#define FLAGS 0x00200030

#define THIS ((EnViewer*)thisx)

void EnViewer_Init(Actor* thisx, GlobalContext* globalCtx);
void EnViewer_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnViewer_Update(Actor* thisx, GlobalContext* globalCtx);
void EnViewer_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Viewer_InitVars = {
    ACTOR_EN_VIEWER,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnViewer),
    (ActorFunc)EnViewer_Init,
    (ActorFunc)EnViewer_Destroy,
    (ActorFunc)EnViewer_Update,
    (ActorFunc)EnViewer_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Viewer_0x8089EE20/func_8089EE20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Viewer_0x8089EE20/EnViewer_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Viewer_0x8089EE20/EnViewer_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Viewer_0x8089EE20/func_8089F014.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Viewer_0x8089EE20/func_8089F0A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Viewer_0x8089EE20/func_8089F17C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Viewer_0x8089EE20/func_8089F218.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Viewer_0x8089EE20/func_8089F2C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Viewer_0x8089EE20/EnViewer_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Viewer_0x8089EE20/EnViewer_Draw.asm")
