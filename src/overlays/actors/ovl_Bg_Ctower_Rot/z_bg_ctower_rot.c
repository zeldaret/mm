#include "z_bg_ctower_rot.h"

#define FLAGS 0x00000030

#define THIS ((BgCtowerRot*)thisx)

void BgCtowerRot_Init(Actor* thisx, GlobalContext* globalCtx);
void BgCtowerRot_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgCtowerRot_Update(Actor* thisx, GlobalContext* globalCtx);
void BgCtowerRot_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Ctower_Rot_InitVars = {
    ACTOR_BG_CTOWER_ROT,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_CTOWER_ROT,
    sizeof(BgCtowerRot),
    (ActorFunc)BgCtowerRot_Init,
    (ActorFunc)BgCtowerRot_Destroy,
    (ActorFunc)BgCtowerRot_Update,
    (ActorFunc)BgCtowerRot_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ctower_Rot_0x808E2070/BgCtowerRot_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ctower_Rot_0x808E2070/BgCtowerRot_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ctower_Rot_0x808E2070/func_808E21FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ctower_Rot_0x808E2070/func_808E22DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ctower_Rot_0x808E2070/func_808E22EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ctower_Rot_0x808E2070/func_808E23D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ctower_Rot_0x808E2070/func_808E2444.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ctower_Rot_0x808E2070/BgCtowerRot_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ctower_Rot_0x808E2070/BgCtowerRot_Draw.asm")
