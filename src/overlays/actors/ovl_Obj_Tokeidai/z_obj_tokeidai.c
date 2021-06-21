#include "z_obj_tokeidai.h"

#define FLAGS 0x00000030

#define THIS ((ObjTokeidai*)thisx)

void ObjTokeidai_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Tokeidai_InitVars = {
    ACTOR_OBJ_TOKEIDAI,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_OBJECT_UNSET_TOKEIDAI,
    sizeof(ObjTokeidai),
    (ActorFunc)ObjTokeidai_Init,
    (ActorFunc)ObjTokeidai_Destroy,
    (ActorFunc)ObjTokeidai_Update,
    (ActorFunc)ObjTokeidai_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB2790.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB27B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB2834.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB28C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB29F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB2BBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/ObjTokeidai_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/ObjTokeidai_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB3010.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB319C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB3240.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB32F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB3370.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB34CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB3544.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB3598.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB363C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB365C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB36C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB3808.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB3880.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB38B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB39BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB3A7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB3B34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB3BB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB3BD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB3BE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB3C50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB3CCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB3ED0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB4040.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB4080.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB4160.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/ObjTokeidai_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/ObjTokeidai_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB4394.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB4664.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokeidai_0x80AB2790/func_80AB4894.asm")
