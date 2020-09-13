#include "z_en_floormas.h"

#define FLAGS 0x00000405

#define THIS ((EnFloormas*)thisx)

void EnFloormas_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFloormas_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFloormas_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFloormas_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Floormas_InitVars = {
    ACTOR_EN_FLOORMAS,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_WALLMASTER,
    sizeof(EnFloormas),
    (ActorFunc)EnFloormas_Init,
    (ActorFunc)EnFloormas_Destroy,
    (ActorFunc)EnFloormas_Update,
    (ActorFunc)EnFloormas_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/EnFloormas_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/EnFloormas_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D08D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D0908.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D0930.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D09CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D0A48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D0B08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D0B50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D0C14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D0C58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D0CE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D0D70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D0ECC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D0F14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D0F50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D0F80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D108C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D11BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D1380.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D1458.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D14DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D161C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D1650.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D1740.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D17EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D19D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D1B44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D1BCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D1C1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D1D0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D1D6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D1ED4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D1F7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D1FD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D2040.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D217C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D22C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D2484.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D24F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D2700.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D2764.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D2A20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D2AA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D2AB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D2AF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D2B18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D2C08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D2CDC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D2D30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D2D6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D2DC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D2E34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/EnFloormas_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D3488.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D34C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/EnFloormas_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Floormas_0x808D0680/func_808D3754.asm")
