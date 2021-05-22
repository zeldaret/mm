#include "z_obj_yasi.h"

#define FLAGS 0x00000000

#define THIS ((ObjYasi*)thisx)

void ObjYasi_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjYasi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjYasi_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjYasi_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Yasi_InitVars = {
    ACTOR_OBJ_YASI,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_OBJECT_UNSET_YASI,
    sizeof(ObjYasi),
    (ActorFunc)ObjYasi_Init,
    (ActorFunc)ObjYasi_Destroy,
    (ActorFunc)ObjYasi_Update,
    (ActorFunc)ObjYasi_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Yasi_0x80BB4AF0/ObjYasi_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Yasi_0x80BB4AF0/ObjYasi_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Yasi_0x80BB4AF0/ObjYasi_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Yasi_0x80BB4AF0/ObjYasi_Draw.asm")
