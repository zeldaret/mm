#include "z_obj_chan.h"

#define FLAGS 0x00000030

#define THIS ((ObjChan*)thisx)

void ObjChan_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjChan_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjChan_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjChan_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Chan_InitVars = {
    ACTOR_OBJ_CHAN,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_OBJECT_UNSET_CHAN,
    sizeof(ObjChan),
    (ActorFunc)ObjChan_Init,
    (ActorFunc)ObjChan_Destroy,
    (ActorFunc)ObjChan_Update,
    (ActorFunc)ObjChan_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/ObjChan_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/ObjChan_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/func_80BB9A1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/func_80BB9B40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/func_80BB9C08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/func_80BB9F24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/func_80BBA2FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/func_80BBA314.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/func_80BBA488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/ObjChan_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/ObjChan_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/func_80BBA894.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/func_80BBA930.s")
