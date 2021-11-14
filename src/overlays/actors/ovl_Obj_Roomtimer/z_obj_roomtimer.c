/*
 * File: z_obj_roomtimer.c
 * Overlay: ovl_Obj_Roomtimer
 * Description:
 */

#include "z_obj_roomtimer.h"

#define FLAGS 0x00000010

#define THIS ((ObjRoomtimer*)thisx)

void ObjRoomtimer_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjRoomtimer_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjRoomtimer_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80973CD8(ObjRoomtimer* this, GlobalContext* globalCtx);
void func_80973D3C(ObjRoomtimer* this, GlobalContext* globalCtx);
void func_80973DE0(ObjRoomtimer* this, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Roomtimer_InitVars = {
    ACTOR_OBJ_ROOMTIMER,
    ACTORCAT_ENEMY,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjRoomtimer),
    (ActorFunc)ObjRoomtimer_Init,
    (ActorFunc)ObjRoomtimer_Destroy,
    (ActorFunc)ObjRoomtimer_Update,
    (ActorFunc)NULL,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Roomtimer/ObjRoomtimer_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Roomtimer/ObjRoomtimer_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Roomtimer/func_80973CD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Roomtimer/func_80973D3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Roomtimer/func_80973DE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Roomtimer/ObjRoomtimer_Update.s")
