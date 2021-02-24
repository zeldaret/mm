#include "z_en_tag_obj.h"

#define FLAGS 0x00000000

#define THIS ((EnTagObj*)thisx)

void EnTagObj_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTagObj_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTagObj_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Tag_Obj_InitVars = {
    ACTOR_EN_TAG_OBJ,
    ACTORTYPE_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTagObj),
    (ActorFunc)EnTagObj_Init,
    (ActorFunc)EnTagObj_Destroy,
    (ActorFunc)EnTagObj_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Tag_Obj_0x80B12870/EnTagObj_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Tag_Obj_0x80B12870/EnTagObj_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Tag_Obj_0x80B12870/EnTagObj_Update.asm")
