#include "z_en_kanban.h"

#define FLAGS 0x00000019

#define THIS ((EnKanban*)thisx)

void EnKanban_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKanban_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKanban_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKanban_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
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


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80957300 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF3CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 50, 5, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_80957300;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kanban_0x80954960/func_80954960.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kanban_0x80954960/EnKanban_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kanban_0x80954960/EnKanban_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kanban_0x80954960/func_80954BE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kanban_0x80954960/EnKanban_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kanban_0x80954960/EnKanban_Draw.asm")
