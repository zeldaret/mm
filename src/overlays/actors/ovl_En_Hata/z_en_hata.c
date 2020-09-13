#include "z_en_hata.h"

#define FLAGS 0x00000000

#define THIS ((EnHata*)thisx)

void EnHata_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHata_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHata_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHata_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Hata_InitVars = {
    ACTOR_EN_HATA,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_HATA,
    sizeof(EnHata),
    (ActorFunc)EnHata_Init,
    (ActorFunc)EnHata_Destroy,
    (ActorFunc)EnHata_Update,
    (ActorFunc)EnHata_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Hata_0x8089E8E0/EnHata_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hata_0x8089E8E0/EnHata_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hata_0x8089E8E0/EnHata_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hata_0x8089E8E0/func_8089EC68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hata_0x8089E8E0/EnHata_Draw.asm")
