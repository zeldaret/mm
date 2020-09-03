#include "z_obj_iceblock.h"

#define FLAGS 0x00000010

#define THIS ((ObjIceblock*)thisx)

void ObjIceblock_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjIceblock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjIceblock_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjIceblock_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Iceblock_InitVars = {
    ACTOR_OBJ_ICEBLOCK,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_ICE_BLOCK,
    sizeof(ObjIceblock),
    (ActorFunc)ObjIceblock_Init,
    (ActorFunc)ObjIceblock_Destroy,
    (ActorFunc)ObjIceblock_Update,
    (ActorFunc)ObjIceblock_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A23090.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A2311C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A2319C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A232C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A23370.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A2339C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A23690.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A236D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A237A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A23938.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A23B88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A23D08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A23F90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A24118.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A24384.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A243E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A24680.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A246D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A2491C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A24954.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A24A48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A24AA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A24B74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A24BDC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A24DC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A24DD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A2508C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A25238.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A252DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A25404.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A2541C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A25440.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/ObjIceblock_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/ObjIceblock_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A257A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A257B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A25824.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A2586C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A25978.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A25994.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A25A8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A25AA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A25BA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A25BBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A25C5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A25C70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A25CF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A25D28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A25E3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A25E50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A25FA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A25FD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A260E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A26144.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A262BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A262EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A26574.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A265C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A266C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A266E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/ObjIceblock_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A26B64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A26B74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/func_80A26BF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Iceblock_0x80A23090/ObjIceblock_Draw.asm")
