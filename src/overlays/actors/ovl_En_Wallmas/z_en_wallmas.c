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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_WALLMASTER,
    sizeof(EnWallmas),
    (ActorFunc)EnWallmas_Init,
    (ActorFunc)EnWallmas_Destroy,
    (ActorFunc)EnWallmas_Update,
    (ActorFunc)EnWallmas_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/EnWallmas_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/EnWallmas_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_80874A88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_80874B04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_80874B88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_80874BE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_80874D1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_80874DE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_80874F14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_80874FD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_80875014.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_80875054.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_808750B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_80875108.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_808751C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_8087520C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_80875248.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_808752CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_808753F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_80875484.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_80875518.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_8087556C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_808755A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_80875638.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_808756AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_8087571C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_808758C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_80875910.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_8087596C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_808759B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_80875A0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_80875A74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/EnWallmas_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_80875F04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_808760A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/func_80876118.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Wallmas_0x80874810/EnWallmas_Draw.asm")
