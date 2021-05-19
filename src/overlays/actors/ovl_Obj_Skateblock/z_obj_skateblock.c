#include "z_obj_skateblock.h"

#define FLAGS 0x00000010

#define THIS ((ObjSkateblock*)thisx)

void ObjSkateblock_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjSkateblock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjSkateblock_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjSkateblock_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Skateblock_InitVars = {
    ACTOR_OBJ_SKATEBLOCK,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_DANGEON_KEEP,
    sizeof(ObjSkateblock),
    (ActorFunc)ObjSkateblock_Init,
    (ActorFunc)ObjSkateblock_Destroy,
    (ActorFunc)ObjSkateblock_Update,
    (ActorFunc)ObjSkateblock_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A21150.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A211F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A212F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A21370.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A21548.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A216D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A21934.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A21990.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A21C30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A21C88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A21CB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A21CD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A21D1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A21E9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A21F68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A21F74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/ObjSkateblock_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/ObjSkateblock_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A22308.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A22334.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A2244C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A224A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A22628.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A2264C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A22728.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A2273C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A227A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/func_80A227C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/ObjSkateblock_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Skateblock_0x80A21150/ObjSkateblock_Draw.asm")
