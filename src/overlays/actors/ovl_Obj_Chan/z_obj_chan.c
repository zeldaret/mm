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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Chan_0x80BB98E0/ObjChan_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Chan_0x80BB98E0/ObjChan_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Chan_0x80BB98E0/func_80BB9A1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Chan_0x80BB98E0/func_80BB9B40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Chan_0x80BB98E0/func_80BB9C08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Chan_0x80BB98E0/func_80BB9F24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Chan_0x80BB98E0/func_80BBA2FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Chan_0x80BB98E0/func_80BBA314.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Chan_0x80BB98E0/func_80BBA488.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Chan_0x80BB98E0/ObjChan_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Chan_0x80BB98E0/ObjChan_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Chan_0x80BB98E0/func_80BBA894.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Chan_0x80BB98E0/func_80BBA930.asm")
