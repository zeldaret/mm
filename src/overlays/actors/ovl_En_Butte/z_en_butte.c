#include "z_en_butte.h"

#define FLAGS 0x00000000

#define THIS ((EnButte*)thisx)

void EnButte_Init(Actor* thisx, GlobalContext* globalCtx);
void EnButte_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnButte_Update(Actor* thisx, GlobalContext* globalCtx);
void EnButte_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Butte_InitVars = {
    ACTOR_EN_BUTTE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_FIELD_KEEP,
    sizeof(EnButte),
    (ActorFunc)EnButte_Init,
    (ActorFunc)EnButte_Destroy,
    (ActorFunc)EnButte_Update,
    (ActorFunc)EnButte_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Butte_0x8091C0A0/func_8091C0A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Butte_0x8091C0A0/func_8091C124.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Butte_0x8091C0A0/func_8091C140.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Butte_0x8091C0A0/func_8091C178.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Butte_0x8091C0A0/EnButte_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Butte_0x8091C0A0/EnButte_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Butte_0x8091C0A0/func_8091C524.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Butte_0x8091C0A0/func_8091C5EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Butte_0x8091C0A0/func_8091C6B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Butte_0x8091C0A0/func_8091C748.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Butte_0x8091C0A0/func_8091C794.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Butte_0x8091C0A0/func_8091CB68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Butte_0x8091C0A0/func_8091CBB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Butte_0x8091C0A0/func_8091CF64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Butte_0x8091C0A0/func_8091CFB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Butte_0x8091C0A0/func_8091D070.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Butte_0x8091C0A0/func_8091D090.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Butte_0x8091C0A0/EnButte_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Butte_0x8091C0A0/EnButte_Draw.asm")
