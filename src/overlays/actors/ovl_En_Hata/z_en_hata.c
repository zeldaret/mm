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
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_HATA,
    sizeof(EnHata),
    (ActorFunc)EnHata_Init,
    (ActorFunc)EnHata_Destroy,
    (ActorFunc)EnHata_Update,
    (ActorFunc)EnHata_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hata_0x8089E8E0/EnHata_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hata_0x8089E8E0/EnHata_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hata_0x8089E8E0/EnHata_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hata_0x8089E8E0/func_8089EC68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hata_0x8089E8E0/EnHata_Draw.asm")
