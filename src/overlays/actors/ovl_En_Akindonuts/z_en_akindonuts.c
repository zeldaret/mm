#include "z_en_akindonuts.h"

#define FLAGS 0x00000039

#define THIS ((EnAkindonuts*)thisx)

void EnAkindonuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAkindonuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAkindonuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAkindonuts_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Akindonuts_InitVars = {
    ACTOR_EN_AKINDONUTS,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_DNT,
    sizeof(EnAkindonuts),
    (ActorFunc)EnAkindonuts_Init,
    (ActorFunc)EnAkindonuts_Destroy,
    (ActorFunc)EnAkindonuts_Update,
    (ActorFunc)EnAkindonuts_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BECBE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BECC7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BECD10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BECEAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BECF6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BECFBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BED034.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BED090.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BED140.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BED208.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BED27C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BED2FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BED35C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BED3BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BED680.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BED8A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEDB88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEDDAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEE070.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEE274.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEE530.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEE73C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEE938.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEEB20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEEDC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEEE10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEEFA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEF18C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEF20C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEF360.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEF450.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEF4B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEF518.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEF770.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEF83C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEF9F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEFAF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEFD74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/EnAkindonuts_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/EnAkindonuts_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/EnAkindonuts_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BEFFB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BF0178.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/func_80BF0190.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Akindonuts_0x80BECBE0/EnAkindonuts_Draw.asm")
