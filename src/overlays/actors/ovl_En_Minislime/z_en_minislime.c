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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/EnMinislime_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/EnMinislime_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_8098399C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80983B38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80983DBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80983E9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80983EB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80983F1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984030.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_809840A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_8098419C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_8098420C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984248.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984410.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984450.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_809844FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_809845A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_8098470C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984748.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984964.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_809849C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984B34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984C28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984CA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984D08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984E38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984ECC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80985018.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80985088.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80985154.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80985168.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_8098518C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_809851E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_809852DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_8098537C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80985480.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/EnMinislime_Update.asm")
