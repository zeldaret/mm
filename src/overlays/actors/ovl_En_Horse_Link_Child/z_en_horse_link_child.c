#include "z_en_horse_link_child.h"

#define FLAGS 0x02000010

#define THIS ((EnHorseLinkChild*)thisx)

void EnHorseLinkChild_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHorseLinkChild_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHorseLinkChild_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHorseLinkChild_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Horse_Link_Child_InitVars = {
    ACTOR_EN_HORSE_LINK_CHILD,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_HORSE_LINK_CHILD,
    sizeof(EnHorseLinkChild),
    (ActorFunc)EnHorseLinkChild_Init,
    (ActorFunc)EnHorseLinkChild_Destroy,
    (ActorFunc)EnHorseLinkChild_Update,
    (ActorFunc)EnHorseLinkChild_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DE5C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DE660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DE728.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/EnHorseLinkChild_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/EnHorseLinkChild_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DE9A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DEA0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DEA54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DEB14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DECA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DED40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DEFE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DF088.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DF194.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DF560.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DF620.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DF788.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DF838.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/EnHorseLinkChild_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DFC3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DFDC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/EnHorseLinkChild_Draw.s")
