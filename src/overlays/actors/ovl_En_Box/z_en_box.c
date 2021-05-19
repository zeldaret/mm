#include "z_en_box.h"

#define FLAGS 0x00000000

#define THIS ((EnBox*)thisx)

void EnBox_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBox_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBox_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBox_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Box_InitVars = {
    ACTOR_EN_BOX,
    ACTORCAT_CHEST,
    FLAGS,
    OBJECT_BOX,
    sizeof(EnBox),
    (ActorFunc)EnBox_Init,
    (ActorFunc)EnBox_Destroy,
    (ActorFunc)EnBox_Update,
    (ActorFunc)EnBox_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_80867BD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_80867BDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_80867C14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_80867C8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_80867FBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_80867FE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_8086800C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/EnBox_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/EnBox_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_80868630.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_80868734.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_808687E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_80868944.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_808689E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_80868A6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_80868AFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_80868B74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_80868CC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_80869020.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_808692E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/EnBox_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_80869600.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_80869850.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_80869874.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/func_808698B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Box_0x80867BD0/EnBox_Draw.asm")
