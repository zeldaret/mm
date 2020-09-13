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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_KUJIYA,
    sizeof(EnKujiya),
    (ActorFunc)EnKujiya_Init,
    (ActorFunc)EnKujiya_Destroy,
    (ActorFunc)EnKujiya_Update,
    (ActorFunc)EnKujiya_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/EnKujiya_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/EnKujiya_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/func_80BB09A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/func_80BB09BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/func_80BB0B28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/func_80BB0BF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/func_80BB0E44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/func_80BB0E58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/func_80BB0F24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/func_80BB0F38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/func_80BB0F94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/func_80BB0FA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/func_80BB0FF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/func_80BB1088.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/func_80BB10F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/func_80BB1168.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/func_80BB1180.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/func_80BB1250.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/func_80BB1268.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/EnKujiya_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kujiya_0x80BB08E0/EnKujiya_Draw.asm")
