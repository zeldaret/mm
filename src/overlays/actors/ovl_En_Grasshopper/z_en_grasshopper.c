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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_GRASSHOPPER,
    sizeof(EnGrasshopper),
    (ActorFunc)EnGrasshopper_Init,
    (ActorFunc)EnGrasshopper_Destroy,
    (ActorFunc)EnGrasshopper_Update,
    (ActorFunc)EnGrasshopper_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/EnGrasshopper_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/EnGrasshopper_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A6524.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A65D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A6628.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A6668.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A6754.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A67A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A6B6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A6E18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A6E74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A6F8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A700C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A7134.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A71CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A7494.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A753C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A7844.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A78EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A797C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A7A8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A7AE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A7BBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A7C98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A7CE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A8044.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/EnGrasshopper_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A847C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/EnGrasshopper_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A8870.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A8924.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Grasshopper_0x809A6280/func_809A8A64.asm")
