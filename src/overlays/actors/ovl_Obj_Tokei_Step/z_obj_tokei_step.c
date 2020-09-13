#include "z_obj_tokei_step.h"

#define FLAGS 0x00400010

#define THIS ((ObjTokeiStep*)thisx)

void ObjTokeiStep_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeiStep_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeiStep_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeiStep_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Tokei_Step_InitVars = {
    ACTOR_OBJ_TOKEI_STEP,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_TOKEI_STEP,
    sizeof(ObjTokeiStep),
    (ActorFunc)ObjTokeiStep_Init,
    (ActorFunc)ObjTokeiStep_Destroy,
    (ActorFunc)ObjTokeiStep_Update,
    (ActorFunc)ObjTokeiStep_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Tokei_Step_0x80AD5BB0/func_80AD5BB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Tokei_Step_0x80AD5BB0/func_80AD5BE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Tokei_Step_0x80AD5BB0/func_80AD5C70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Tokei_Step_0x80AD5BB0/func_80AD5DFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Tokei_Step_0x80AD5BB0/func_80AD5EB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Tokei_Step_0x80AD5BB0/func_80AD5F70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Tokei_Step_0x80AD5BB0/func_80AD5FB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Tokei_Step_0x80AD5BB0/ObjTokeiStep_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Tokei_Step_0x80AD5BB0/ObjTokeiStep_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Tokei_Step_0x80AD5BB0/func_80AD6348.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Tokei_Step_0x80AD5BB0/func_80AD635C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Tokei_Step_0x80AD5BB0/func_80AD63D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Tokei_Step_0x80AD5BB0/func_80AD63E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Tokei_Step_0x80AD5BB0/func_80AD63F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Tokei_Step_0x80AD5BB0/func_80AD642C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Tokei_Step_0x80AD5BB0/func_80AD6480.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Tokei_Step_0x80AD5BB0/func_80AD64A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Tokei_Step_0x80AD5BB0/ObjTokeiStep_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Tokei_Step_0x80AD5BB0/ObjTokeiStep_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Tokei_Step_0x80AD5BB0/func_80AD6508.asm")
