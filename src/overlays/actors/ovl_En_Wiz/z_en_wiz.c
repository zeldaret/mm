#include "z_en_wiz.h"

#define FLAGS 0x88101035

#define THIS ((EnWiz*)thisx)

void EnWiz_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWiz_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWiz_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWiz_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Wiz_InitVars = {
    ACTOR_EN_WIZ,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_WIZ,
    sizeof(EnWiz),
    (ActorFunc)EnWiz_Init,
    (ActorFunc)EnWiz_Destroy,
    (ActorFunc)EnWiz_Update,
    (ActorFunc)EnWiz_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/EnWiz_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/EnWiz_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A455C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A456A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A45CD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A460A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46280.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A462F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A4668C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46764.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A468CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46990.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46C88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46CC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46DDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46E24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A47000.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A470D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A47298.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A473B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A4767C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A476C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A477E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/EnWiz_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A47FCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A48138.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/EnWiz_Draw.s")
