#include "z_door_ana.h"

#define FLAGS 0x02000000

#define THIS ((DoorAna*)thisx)

void DoorAna_Init(Actor* thisx, GlobalContext* globalCtx);
void DoorAna_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DoorAna_Update(Actor* thisx, GlobalContext* globalCtx);
void DoorAna_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Door_Ana_InitVars = {
    ACTOR_DOOR_ANA,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_FIELD_KEEP,
    sizeof(DoorAna),
    (ActorFunc)DoorAna_Init,
    (ActorFunc)DoorAna_Destroy,
    (ActorFunc)DoorAna_Update,
    (ActorFunc)DoorAna_Draw
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Ana_0x808E01A0/func_808E01A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Ana_0x808E01A0/DoorAna_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Ana_0x808E01A0/DoorAna_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Ana_0x808E01A0/func_808E02A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Ana_0x808E01A0/func_808E03B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Ana_0x808E01A0/func_808E05C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Ana_0x808E01A0/DoorAna_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Ana_0x808E01A0/DoorAna_Draw.asm")
