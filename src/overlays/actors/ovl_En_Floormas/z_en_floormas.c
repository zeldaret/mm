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
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_WALLMASTER,
    sizeof(EnFloormas),
    (ActorFunc)EnFloormas_Init,
    (ActorFunc)EnFloormas_Destroy,
    (ActorFunc)EnFloormas_Update,
    (ActorFunc)EnFloormas_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/EnFloormas_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/EnFloormas_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D08D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D0908.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D0930.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D09CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D0A48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D0B08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D0B50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D0C14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D0C58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D0CE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D0D70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D0ECC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D0F14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D0F50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D0F80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D108C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D11BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D1380.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D1458.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D14DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D161C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D1650.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D1740.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D17EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D19D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D1B44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D1BCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D1C1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D1D0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D1D6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D1ED4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D1F7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D1FD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D2040.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D217C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D22C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D2484.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D24F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D2700.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D2764.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D2A20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D2AA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D2AB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D2AF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D2B18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D2C08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D2CDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D2D30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D2D6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D2DC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D2E34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/EnFloormas_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D3488.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D34C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/EnFloormas_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Floormas_0x808D0680/func_808D3754.asm")
