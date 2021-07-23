#include "z_obj_sound.h"

#define FLAGS 0x00000030

#define THIS ((ObjSound*)thisx)

void ObjSound_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjSound_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjSound_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Sound_InitVars = {
    ACTOR_OBJ_SOUND,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjSound),
    (ActorFunc)ObjSound_Init,
    (ActorFunc)ObjSound_Destroy,
    (ActorFunc)ObjSound_Update,
    (ActorFunc)NULL,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Sound/ObjSound_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Sound/ObjSound_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Sound/ObjSound_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Sound/func_8099AA84.s")
