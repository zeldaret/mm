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
    (ActorFunc)BossHakugin_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/BossHakugin_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/BossHakugin_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0573C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B057A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B058C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B05A64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B05B04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B05CBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B05D4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B05EE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0607C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B06558.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B06600.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0696C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B06B20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B06C08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B06D38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B06F48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0728C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B07450.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B07700.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0791C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B07B88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B07BFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B07DA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B07EEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B08018.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B08124.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0813C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0825C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B082AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B08550.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0863C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B08848.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B08960.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B08C1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B08CB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B09178.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B091D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B093C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B094E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B09840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B098BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B09A94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B09C78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B09DFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B09E20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B09E84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B09EDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B09F7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0A2A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0A5EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0A638.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0A87C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0A8C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0AC30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0ADFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0B238.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0B34C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0B3F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0B548.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0B660.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/BossHakugin_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0C000.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0C1BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0C398.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0C570.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0C7B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0CAF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0CCD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0CF24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/BossHakugin_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0D2B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0D69C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0D750.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0D9CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0DFA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0E548.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0E5A4.asm")
