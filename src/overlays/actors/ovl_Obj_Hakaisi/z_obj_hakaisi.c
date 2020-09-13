#include "z_obj_hakaisi.h"

#define FLAGS 0x00000029

#define THIS ((ObjHakaisi*)thisx)

void ObjHakaisi_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHakaisi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHakaisi_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHakaisi_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Hakaisi_InitVars = {
    ACTOR_OBJ_HAKAISI,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_HAKAISI,
    sizeof(ObjHakaisi),
    (ActorFunc)ObjHakaisi_Init,
    (ActorFunc)ObjHakaisi_Destroy,
    (ActorFunc)ObjHakaisi_Update,
    (ActorFunc)ObjHakaisi_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/ObjHakaisi_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/ObjHakaisi_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/func_80B1444C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/func_80B14460.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/func_80B14510.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/func_80B14524.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/func_80B14558.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/func_80B1456C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/func_80B145F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/func_80B14648.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/func_80B149A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/func_80B149C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/func_80B14A24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/func_80B14B6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/func_80B14CF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/func_80B14F4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/ObjHakaisi_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/ObjHakaisi_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/func_80B151E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/func_80B15254.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/func_80B15264.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/func_80B15330.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/func_80B1544C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hakaisi_0x80B14180/func_80B154A0.asm")
