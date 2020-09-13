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
    ACTORTYPE_BG,
    FLAGS,
    GAMEPLAY_DANGEON_KEEP,
    sizeof(ObjSkateblock),
    (ActorFunc)ObjSkateblock_Init,
    (ActorFunc)ObjSkateblock_Destroy,
    (ActorFunc)ObjSkateblock_Update,
    (ActorFunc)ObjSkateblock_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A21150.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A211F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A212F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A21370.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A21548.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A216D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A21934.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A21990.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A21C30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A21C88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A21CB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A21CD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A21D1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A21E9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A21F68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A21F74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/ObjSkateblock_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/ObjSkateblock_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A22308.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A22334.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A2244C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A224A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A22628.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A2264C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A22728.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A2273C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A227A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/func_80A227C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/ObjSkateblock_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Skateblock_0x80A21150/ObjSkateblock_Draw.asm")
