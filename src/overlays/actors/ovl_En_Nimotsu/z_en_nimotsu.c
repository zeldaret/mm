#include "z_en_nimotsu.h"

#define FLAGS 0x00000010

#define THIS ((EnNimotsu*)thisx)

void EnNimotsu_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNimotsu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNimotsu_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNimotsu_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Nimotsu_InitVars = {
    ACTOR_EN_NIMOTSU,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_BOJ,
    sizeof(EnNimotsu),
    (ActorFunc)EnNimotsu_Init,
    (ActorFunc)EnNimotsu_Destroy,
    (ActorFunc)EnNimotsu_Update,
    (ActorFunc)EnNimotsu_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nimotsu_0x80BE1C80/func_80BE1C80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nimotsu_0x80BE1C80/EnNimotsu_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nimotsu_0x80BE1C80/EnNimotsu_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nimotsu_0x80BE1C80/EnNimotsu_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nimotsu_0x80BE1C80/EnNimotsu_Draw.asm")
