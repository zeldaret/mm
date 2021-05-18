#include "z_obj_tokei_tobira.h"

#define FLAGS 0x00000000

#define THIS ((ObjTokeiTobira*)thisx)

void ObjTokeiTobira_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeiTobira_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeiTobira_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeiTobira_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Tokei_Tobira_InitVars = {
    ACTOR_OBJ_TOKEI_TOBIRA,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_TOKEI_TOBIRA,
    sizeof(ObjTokeiTobira),
    (ActorFunc)ObjTokeiTobira_Init,
    (ActorFunc)ObjTokeiTobira_Destroy,
    (ActorFunc)ObjTokeiTobira_Update,
    (ActorFunc)ObjTokeiTobira_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokei_Tobira_0x80ABD1D0/ObjTokeiTobira_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokei_Tobira_0x80ABD1D0/ObjTokeiTobira_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokei_Tobira_0x80ABD1D0/func_80ABD3B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokei_Tobira_0x80ABD1D0/ObjTokeiTobira_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokei_Tobira_0x80ABD1D0/ObjTokeiTobira_Draw.asm")
