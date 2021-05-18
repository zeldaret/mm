#include "z_en_kanban.h"

#define FLAGS 0x00000019

#define THIS ((EnKanban*)thisx)

void EnKanban_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKanban_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKanban_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKanban_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Kanban_InitVars = {
    ACTOR_EN_KANBAN,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_KANBAN,
    sizeof(EnKanban),
    (ActorFunc)EnKanban_Init,
    (ActorFunc)EnKanban_Destroy,
    (ActorFunc)EnKanban_Update,
    (ActorFunc)EnKanban_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kanban_0x80954960/func_80954960.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kanban_0x80954960/EnKanban_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kanban_0x80954960/EnKanban_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kanban_0x80954960/func_80954BE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kanban_0x80954960/EnKanban_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kanban_0x80954960/EnKanban_Draw.asm")
