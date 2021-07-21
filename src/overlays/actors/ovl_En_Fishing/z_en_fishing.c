/*
 * File: z_en_fishing.c
 * Overlay: ovl_En_Fishing
 * Description: Fishing
 */

#include "z_en_fishing.h"

#define FLAGS 0x00000010

#define THIS ((EnFishing*)thisx)

void EnFishing_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFishing_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFishing_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFishing_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Fishing_InitVars = {
    ACTOR_EN_FISHING,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_FISH,
    sizeof(EnFishing),
    (ActorFunc)EnFishing_Init,
    (ActorFunc)EnFishing_Destroy,
    (ActorFunc)EnFishing_Update,
    (ActorFunc)EnFishing_Draw,
};
 */

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FC6C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FC770.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FC790.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FC8B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FC964.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FCABC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FCC0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FCDBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FCF60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FD054.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/EnFishing_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/EnFishing_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FDCDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FE3F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FEE1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FEF70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FF064.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FF5E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FF750.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FFC44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FFF3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80900228.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80900A04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80901480.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_809033F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_809036BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_809038A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80903C60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80903E20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/EnFishing_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80908554.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80908674.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_809086B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80908734.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/EnFishing_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_809089B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80908A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80908B4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80908E08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80909234.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80909AD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80909CC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_8090AB6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_8090C884.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_8090C8BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_8090C96C.s")
