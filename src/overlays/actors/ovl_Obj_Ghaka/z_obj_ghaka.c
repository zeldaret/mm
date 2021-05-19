#include "z_obj_ghaka.h"

#define FLAGS 0x00000029

#define THIS ((ObjGhaka*)thisx)

void ObjGhaka_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjGhaka_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjGhaka_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjGhaka_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Ghaka_InitVars = {
    ACTOR_OBJ_GHAKA,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_GHAKA,
    sizeof(ObjGhaka),
    (ActorFunc)ObjGhaka_Init,
    (ActorFunc)ObjGhaka_Destroy,
    (ActorFunc)ObjGhaka_Update,
    (ActorFunc)ObjGhaka_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/func_80B3C260.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/func_80B3C29C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/func_80B3C2B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/func_80B3C2C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/func_80B3C39C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/func_80B3C4E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/func_80B3C624.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/ObjGhaka_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/ObjGhaka_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/ObjGhaka_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/ObjGhaka_Draw.asm")
