/*
 * File: z_bg_hakugin_elvpole.c
 * Overlay: ovl_Bg_Hakugin_Elvpole
 * Description: Raisable pillar in Snowhead Temple Map room
 */

#include "z_bg_hakugin_elvpole.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgHakuginElvpole*)thisx)

void BgHakuginElvpole_Init(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginElvpole_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginElvpole_Update(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginElvpole_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80ABD92C(BgHakuginElvpole* this, GlobalContext* globalCtx);

#if 0
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

#endif

extern UNK_TYPE D_0600ACB8;
extern UNK_TYPE D_0600BF40;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Elvpole/BgHakuginElvpole_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Elvpole/BgHakuginElvpole_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Elvpole/func_80ABD92C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Elvpole/BgHakuginElvpole_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Elvpole/BgHakuginElvpole_Draw.s")
