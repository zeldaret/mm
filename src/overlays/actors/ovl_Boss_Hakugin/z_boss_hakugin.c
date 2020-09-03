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
    ACTORTYPE_BOSS,
    FLAGS,
    OBJECT_BOSS_HAKUGIN,
    sizeof(BossHakugin),
    (ActorFunc)BossHakugin_Init,
    (ActorFunc)BossHakugin_Destroy,
    (ActorFunc)BossHakugin_Update,
    (ActorFunc)BossHakugin_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/BossHakugin_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/BossHakugin_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0573C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B057A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B058C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B05A64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B05B04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B05CBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B05D4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B05EE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0607C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B06558.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B06600.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0696C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B06B20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B06C08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B06D38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B06F48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0728C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B07450.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B07700.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0791C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B07B88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B07BFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B07DA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B07EEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B08018.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B08124.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0813C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0825C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B082AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B08550.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0863C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B08848.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B08960.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B08C1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B08CB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B09178.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B091D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B093C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B094E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B09840.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B098BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B09A94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B09C78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B09DFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B09E20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B09E84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B09EDC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B09F7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0A2A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0A5EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0A638.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0A87C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0A8C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0AC30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0ADFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0B238.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0B34C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0B3F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0B548.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0B660.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/BossHakugin_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0C000.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0C1BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0C398.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0C570.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0C7B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0CAF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0CCD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0CF24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/BossHakugin_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0D2B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0D69C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0D750.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0D9CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0DFA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0E548.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_Hakugin_0x80B05290/func_80B0E5A4.asm")
