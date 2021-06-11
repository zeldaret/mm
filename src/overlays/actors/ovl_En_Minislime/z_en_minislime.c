#include "z_en_minislime.h"

#define FLAGS 0x00000235

#define THIS ((EnMinislime*)thisx)

void EnMinislime_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMinislime_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMinislime_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Minislime_InitVars = {
    ACTOR_EN_MINISLIME,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BIGSLIME,
    sizeof(EnMinislime),
    (ActorFunc)EnMinislime_Init,
    (ActorFunc)EnMinislime_Destroy,
    (ActorFunc)EnMinislime_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/EnMinislime_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/EnMinislime_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_8098399C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80983B38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80983DBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80983E9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80983EB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80983F1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80984030.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_809840A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_8098419C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_8098420C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80984248.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80984410.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80984450.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_809844FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_809845A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_8098470C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80984748.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80984964.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_809849C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80984B34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80984C28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80984CA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80984D08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80984E38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80984ECC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80985018.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80985088.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80985154.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80985168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_8098518C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_809851E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_809852DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_8098537C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/func_80985480.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minislime/EnMinislime_Update.s")
