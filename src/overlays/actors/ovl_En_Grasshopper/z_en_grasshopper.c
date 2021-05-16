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
    (ActorFunc)EnGrasshopper_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/EnGrasshopper_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/EnGrasshopper_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A6524.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A65D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A6628.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A6668.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A6754.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A67A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A6B6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A6E18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A6E74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A6F8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A700C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A7134.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A71CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A7494.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A753C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A7844.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A78EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A797C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A7A8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A7AE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A7BBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A7C98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A7CE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A8044.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/EnGrasshopper_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A847C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/EnGrasshopper_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A8870.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A8924.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Grasshopper/func_809A8A64.s")
