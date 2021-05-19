#include "z_en_grasshopper.h"

#define FLAGS 0x00000015

#define THIS ((EnGrasshopper*)thisx)

void EnGrasshopper_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGrasshopper_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGrasshopper_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGrasshopper_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Grasshopper_InitVars = {
    ACTOR_EN_GRASSHOPPER,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_GRASSHOPPER,
    sizeof(EnGrasshopper),
    (ActorFunc)EnGrasshopper_Init,
    (ActorFunc)EnGrasshopper_Destroy,
    (ActorFunc)EnGrasshopper_Update,
    (ActorFunc)EnGrasshopper_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/EnGrasshopper_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/EnGrasshopper_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A6524.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A65D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A6628.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A6668.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A6754.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A67A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A6B6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A6E18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A6E74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A6F8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A700C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A7134.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A71CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A7494.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A753C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A7844.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A78EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A797C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A7A8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A7AE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A7BBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A7C98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A7CE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A8044.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/EnGrasshopper_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A847C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/EnGrasshopper_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A8870.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A8924.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A8A64.asm")
