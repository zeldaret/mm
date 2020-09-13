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
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnViewer),
    (ActorFunc)EnViewer_Init,
    (ActorFunc)EnViewer_Destroy,
    (ActorFunc)EnViewer_Update,
    (ActorFunc)EnViewer_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Viewer_0x8089EE20/func_8089EE20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Viewer_0x8089EE20/EnViewer_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Viewer_0x8089EE20/EnViewer_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Viewer_0x8089EE20/func_8089F014.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Viewer_0x8089EE20/func_8089F0A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Viewer_0x8089EE20/func_8089F17C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Viewer_0x8089EE20/func_8089F218.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Viewer_0x8089EE20/func_8089F2C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Viewer_0x8089EE20/EnViewer_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Viewer_0x8089EE20/EnViewer_Draw.asm")
