#include "z_boss_hakugin.h"

#define FLAGS 0x00000035

#define THIS ((BossHakugin*)thisx)

void BossHakugin_Init(Actor* thisx, GlobalContext* globalCtx);
void BossHakugin_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BossHakugin_Update(Actor* thisx, GlobalContext* globalCtx);
void BossHakugin_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Boss_Hakugin_InitVars = {
    ACTOR_BOSS_HAKUGIN,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS_HAKUGIN,
    sizeof(BossHakugin),
    (ActorFunc)BossHakugin_Init,
    (ActorFunc)BossHakugin_Destroy,
    (ActorFunc)BossHakugin_Update,
    (ActorFunc)BossHakugin_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/BossHakugin_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/BossHakugin_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0573C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B057A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B058C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B05A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B05B04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B05CBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B05D4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B05EE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0607C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B06558.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B06600.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0696C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B06B20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B06C08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B06D38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B06F48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0728C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B07450.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B07700.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0791C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B07B88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B07BFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B07DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B07EEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B08018.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B08124.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0813C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0825C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B082AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B08550.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0863C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B08848.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B08960.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B08C1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B08CB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09178.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B091D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B093C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B094E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09840.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B098BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09A94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09C78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09DFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09E20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09E84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09EDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09F7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0A2A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0A5EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0A638.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0A87C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0A8C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0AC30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0ADFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0B238.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0B34C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0B3F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0B548.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0B660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/BossHakugin_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0C000.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0C1BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0C398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0C570.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0C7B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0CAF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0CCD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0CF24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/BossHakugin_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0D2B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0D69C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0D750.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0D9CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0DFA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0E548.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0E5A4.s")
