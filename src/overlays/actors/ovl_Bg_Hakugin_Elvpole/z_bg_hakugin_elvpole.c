#include "z_bg_hakugin_elvpole.h"

#define FLAGS 0x00000010

#define THIS ((BgHakuginElvpole*)thisx)

void BgHakuginElvpole_Init(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginElvpole_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginElvpole_Update(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginElvpole_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Hakugin_Elvpole_InitVars = {
    ACTOR_BG_HAKUGIN_ELVPOLE,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_HAKUGIN_OBJ,
    sizeof(BgHakuginElvpole),
    (ActorFunc)BgHakuginElvpole_Init,
    (ActorFunc)BgHakuginElvpole_Destroy,
    (ActorFunc)BgHakuginElvpole_Update,
    (ActorFunc)BgHakuginElvpole_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Elvpole_0x80ABD830/BgHakuginElvpole_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Elvpole_0x80ABD830/BgHakuginElvpole_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Elvpole_0x80ABD830/func_80ABD92C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Elvpole_0x80ABD830/BgHakuginElvpole_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Hakugin_Elvpole_0x80ABD830/BgHakuginElvpole_Draw.asm")
