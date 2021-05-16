#include "z_en_wallmas.h"

#define FLAGS 0x00000415

#define THIS ((EnWallmas*)thisx)

void EnWallmas_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWallmas_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWallmas_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWallmas_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Wallmas_InitVars = {
    ACTOR_EN_WALLMAS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_WALLMASTER,
    sizeof(EnWallmas),
    (ActorFunc)EnWallmas_Init,
    (ActorFunc)EnWallmas_Destroy,
    (ActorFunc)EnWallmas_Update,
    (ActorFunc)EnWallmas_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/EnWallmas_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/EnWallmas_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80874A88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80874B04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80874B88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80874BE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80874D1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80874DE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80874F14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80874FD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875014.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875054.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808750B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875108.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808751C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_8087520C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875248.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808752CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808753F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875484.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875518.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_8087556C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808755A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875638.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808756AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_8087571C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808758C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_8087596C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808759B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875A0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875A74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/EnWallmas_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80875F04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_808760A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/func_80876118.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wallmas/EnWallmas_Draw.s")
