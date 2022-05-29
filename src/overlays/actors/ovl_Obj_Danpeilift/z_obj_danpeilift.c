/*
 * File: z_obj_danpeilift.c
 * Overlay: ovl_Obj_Danpeilift
 * Description: Deku Shrine & Snowhead Temple floating blocks
 */

#include "z_obj_danpeilift.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjDanpeilift*)thisx)

void ObjDanpeilift_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjDanpeilift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjDanpeilift_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjDanpeilift_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Danpeilift_InitVars = {
    ACTOR_OBJ_DANPEILIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_OBJ_DANPEILIFT,
    sizeof(ObjDanpeilift),
    (ActorFunc)ObjDanpeilift_Init,
    (ActorFunc)ObjDanpeilift_Destroy,
    (ActorFunc)ObjDanpeilift_Update,
    (ActorFunc)ObjDanpeilift_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80C1B540[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 400, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80C1B540[];

extern UNK_TYPE D_06000180;
extern UNK_TYPE D_06000BA0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Danpeilift/func_80C1ADC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Danpeilift/ObjDanpeilift_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Danpeilift/ObjDanpeilift_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Danpeilift/func_80C1AF84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Danpeilift/func_80C1AF94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Danpeilift/func_80C1B210.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Danpeilift/func_80C1B26C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Danpeilift/ObjDanpeilift_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Danpeilift/ObjDanpeilift_Draw.s")
