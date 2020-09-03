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
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_HORSE_LINK_CHILD,
    sizeof(EnHorseLinkChild),
    (ActorFunc)EnHorseLinkChild_Init,
    (ActorFunc)EnHorseLinkChild_Destroy,
    (ActorFunc)EnHorseLinkChild_Update,
    (ActorFunc)EnHorseLinkChild_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/func_808DE5C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/func_808DE660.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/func_808DE728.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/EnHorseLinkChild_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/EnHorseLinkChild_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/func_808DE9A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/func_808DEA0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/func_808DEA54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/func_808DEB14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/func_808DECA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/func_808DED40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/func_808DEFE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/func_808DF088.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/func_808DF194.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/func_808DF560.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/func_808DF620.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/func_808DF788.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/func_808DF838.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/EnHorseLinkChild_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/func_808DFC3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/func_808DFDC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Horse_Link_Child_0x808DE5C0/EnHorseLinkChild_Draw.asm")
