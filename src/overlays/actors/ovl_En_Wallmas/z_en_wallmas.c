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
    (ActorFunc)EnWallmas_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/EnWallmas_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/EnWallmas_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_80874A88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_80874B04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_80874B88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_80874BE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_80874D1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_80874DE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_80874F14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_80874FD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_80875014.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_80875054.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_808750B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_80875108.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_808751C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_8087520C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_80875248.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_808752CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_808753F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_80875484.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_80875518.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_8087556C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_808755A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_80875638.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_808756AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_8087571C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_808758C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_80875910.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_8087596C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_808759B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_80875A0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_80875A74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/EnWallmas_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_80875F04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_808760A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/func_80876118.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wallmas_0x80874810/EnWallmas_Draw.asm")
