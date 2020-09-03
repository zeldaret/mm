#include "z_obj_roomtimer.h"

#define FLAGS 0x00000010

#define THIS ((ObjRoomtimer*)thisx)

void ObjRoomtimer_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjRoomtimer_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjRoomtimer_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Roomtimer_InitVars = {
    ACTOR_OBJ_ROOMTIMER,
    ACTORTYPE_ENEMY,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjRoomtimer),
    (ActorFunc)ObjRoomtimer_Init,
    (ActorFunc)ObjRoomtimer_Destroy,
    (ActorFunc)ObjRoomtimer_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Roomtimer_0x80973C50/ObjRoomtimer_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Roomtimer_0x80973C50/ObjRoomtimer_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Roomtimer_0x80973C50/func_80973CD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Roomtimer_0x80973C50/func_80973D3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Roomtimer_0x80973C50/func_80973DE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Roomtimer_0x80973C50/ObjRoomtimer_Update.asm")
