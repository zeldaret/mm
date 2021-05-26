#include "z_en_hit_tag.h"

#define FLAGS 0x00000010

#define THIS ((EnHitTag*)thisx)

void EnHitTag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHitTag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHitTag_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Hit_Tag_InitVars = {
    ACTOR_EN_HIT_TAG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnHitTag),
    (ActorFunc)EnHitTag_Init,
    (ActorFunc)EnHitTag_Destroy,
    (ActorFunc)EnHitTag_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hit_Tag_0x80BE2030/EnHitTag_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hit_Tag_0x80BE2030/EnHitTag_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hit_Tag_0x80BE2030/func_80BE20E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hit_Tag_0x80BE2030/EnHitTag_Update.asm")
