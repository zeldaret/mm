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
    (ActorFunc)EnFloormas_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/EnFloormas_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/EnFloormas_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D08D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0908.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0930.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D09CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0A48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0B08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0B50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0C14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0C58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0CE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0D70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0ECC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0F14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0F50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D0F80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D108C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D11BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1380.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1458.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D14DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D161C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1650.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1740.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D17EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D19D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1B44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1BCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1C1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1D0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1D6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1ED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1F7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D1FD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2040.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D217C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D22C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2484.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D24F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2700.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2764.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2A20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2AA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2AB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2AF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2B18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2C08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2CDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2D30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2D6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2DC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D2E34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/EnFloormas_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D3488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D34C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/EnFloormas_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Floormas/func_808D3754.s")
