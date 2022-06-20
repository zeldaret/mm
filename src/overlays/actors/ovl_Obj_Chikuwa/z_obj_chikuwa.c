/*
 * File: z_obj_chikuwa.c
 * Overlay: ovl_Obj_Chikuwa
 * Description: Falling row of blocks (unused)
 */

#include "z_obj_chikuwa.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjChikuwa*)thisx)

void ObjChikuwa_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjChikuwa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjChikuwa_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjChikuwa_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Chikuwa_InitVars = {
    ACTOR_OBJ_CHIKUWA,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_D_LIFT,
    sizeof(ObjChikuwa),
    (ActorFunc)ObjChikuwa_Init,
    (ActorFunc)ObjChikuwa_Destroy,
    (ActorFunc)ObjChikuwa_Update,
    (ActorFunc)ObjChikuwa_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_809B1FC0[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 1500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1500, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_809B1FC0[];

extern UNK_TYPE D_06000D10;
extern UNK_TYPE D_06000F00;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chikuwa/func_809B1550.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chikuwa/ObjChikuwa_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chikuwa/ObjChikuwa_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chikuwa/func_809B17D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chikuwa/func_809B1AA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chikuwa/ObjChikuwa_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chikuwa/ObjChikuwa_Draw.s")
