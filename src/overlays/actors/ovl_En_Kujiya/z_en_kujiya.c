#include "z_en_kujiya.h"

#define FLAGS 0x08000009

#define THIS ((EnKujiya*)thisx)

void EnKujiya_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKujiya_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKujiya_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKujiya_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Kujiya_InitVars = {
    ACTOR_EN_KUJIYA,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_KUJIYA,
    sizeof(EnKujiya),
    (ActorFunc)EnKujiya_Init,
    (ActorFunc)EnKujiya_Destroy,
    (ActorFunc)EnKujiya_Update,
    (ActorFunc)EnKujiya_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/EnKujiya_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/EnKujiya_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/func_80BB09A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/func_80BB09BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/func_80BB0B28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/func_80BB0BF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/func_80BB0E44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/func_80BB0E58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/func_80BB0F24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/func_80BB0F38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/func_80BB0F94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/func_80BB0FA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/func_80BB0FF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/func_80BB1088.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/func_80BB10F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/func_80BB1168.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/func_80BB1180.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/func_80BB1250.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/func_80BB1268.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/EnKujiya_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kujiya_0x80BB08E0/EnKujiya_Draw.asm")
