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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_808FC6C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_808FC770.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_808FC790.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_808FC8B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_808FC964.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_808FCABC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_808FCC0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_808FCDBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_808FCF60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_808FD054.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/EnFishing_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/EnFishing_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_808FDCDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_808FE3F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_808FEE1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_808FEF70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_808FF064.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_808FF5E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_808FF750.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_808FFC44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_808FFF3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_80900228.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_80900A04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_80901480.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_809033F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_809036BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_809038A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_80903C60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_80903E20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/EnFishing_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_80908554.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_80908674.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_809086B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_80908734.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/EnFishing_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_809089B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_80908A64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_80908B4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_80908E08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_80909234.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_80909AD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_80909CC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_8090AB6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_8090C884.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_8090C8BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fishing_0x808FC6C0/func_8090C96C.asm")
