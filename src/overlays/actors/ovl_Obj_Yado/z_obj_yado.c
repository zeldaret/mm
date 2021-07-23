#include "z_obj_yado.h"

#define FLAGS 0x00000030

#define THIS ((ObjYado*)thisx)

void ObjYado_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjYado_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjYado_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjYado_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Yado_InitVars = {
    ACTOR_OBJ_YADO,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_YADO_OBJ,
    sizeof(ObjYado),
    (ActorFunc)ObjYado_Init,
    (ActorFunc)ObjYado_Destroy,
    (ActorFunc)ObjYado_Update,
    (ActorFunc)ObjYado_Draw,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80C16420[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};


extern InitChainEntry D_80C16420[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Yado_0x80C161E0/ObjYado_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Yado_0x80C161E0/ObjYado_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Yado_0x80C161E0/ObjYado_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Yado_0x80C161E0/ObjYado_Draw.asm")
