#include "z_en_pametfrog.h"

#define FLAGS 0x00000035

#define THIS ((EnPametfrog*)thisx)

void EnPametfrog_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPametfrog_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPametfrog_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPametfrog_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Pametfrog_InitVars = {
    ACTOR_EN_PAMETFROG,
    ACTORTYPE_BOSS,
    FLAGS,
    OBJECT_BIGSLIME,
    sizeof(EnPametfrog),
    (ActorFunc)EnPametfrog_Init,
    (ActorFunc)EnPametfrog_Destroy,
    (ActorFunc)EnPametfrog_Update,
    (ActorFunc)EnPametfrog_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/EnPametfrog_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/EnPametfrog_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_80869FBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086A024.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086A068.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086A0F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086A1A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086A238.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086A2CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086A428.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086A4E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086A554.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086A6B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086A724.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086A80C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086A878.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086A8C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086A964.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086AA60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086AAA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086AB04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086AB68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086AC0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086AD34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086AE48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086AEC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086AFC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086B140.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086B478.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086B570.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086B66C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086B794.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086B864.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086B8CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086B9D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086BA6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086BB4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086BB9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086BBE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086BDA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086BE60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086BEEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086BF90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086C088.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086C0CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086C1AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086C274.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086C4B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086C5A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086C618.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086C6D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086C72C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086C7C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086C81C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086C94C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086C99C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086CB4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086CC04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086CC84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086CD04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086CD6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086CEB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086CEF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086D084.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086D140.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086D1E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086D230.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/EnPametfrog_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/func_8086D730.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pametfrog_0x80869D90/EnPametfrog_Draw.asm")
