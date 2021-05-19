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
    (ActorFunc)EnWiz_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/EnWiz_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/EnWiz_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A455C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A456A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A45CD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A460A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A46280.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A462F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A46414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A4668C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A46764.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A468CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A46990.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A46C88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A46CC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A46DDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A46E24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A47000.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A470D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A47298.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A473B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A4767C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A476C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A477E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/EnWiz_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A47FCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/func_80A48138.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wiz_0x80A45360/EnWiz_Draw.asm")
