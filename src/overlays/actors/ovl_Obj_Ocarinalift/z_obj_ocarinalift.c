/*
 * File: z_obj_ocarinalift.c
 * Overlay: ovl_Obj_Ocarinalift
 * Description: Elevator With Triforce Texture (unused?)
 */

#include "z_obj_ocarinalift.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjOcarinalift*)thisx)

void ObjOcarinalift_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjOcarinalift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjOcarinalift_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjOcarinalift_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Ocarinalift_InitVars = {
    ACTOR_OBJ_OCARINALIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_RAILLIFT,
    sizeof(ObjOcarinalift),
    (ActorFunc)ObjOcarinalift_Init,
    (ActorFunc)ObjOcarinalift_Destroy,
    (ActorFunc)ObjOcarinalift_Update,
    (ActorFunc)ObjOcarinalift_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AC9D70[] = {
    ICHAIN_U8(targetMode, 2, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80AC9D70[];

extern UNK_TYPE D_06001E40;
extern UNK_TYPE D_060048D0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC94C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/ObjOcarinalift_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/ObjOcarinalift_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC9680.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC96A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC96B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC96D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC99C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC99D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC9A68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC9A7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC9AB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC9AE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC9B48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC9B5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC9C20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC9C48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/ObjOcarinalift_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/ObjOcarinalift_Draw.s")
