#include "z_obj_sound.h"

#define FLAGS 0x00000030

#define THIS ((ObjSound*)thisx)

void ObjSound_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjSound_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjSound_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Sound_InitVars = {
    ACTOR_OBJ_SOUND,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjSound),
    (ActorFunc)ObjSound_Init,
    (ActorFunc)ObjSound_Destroy,
    (ActorFunc)ObjSound_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Sound_0x8099A920/ObjSound_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Sound_0x8099A920/ObjSound_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Sound_0x8099A920/ObjSound_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Sound_0x8099A920/func_8099AA84.asm")
