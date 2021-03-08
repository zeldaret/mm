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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/EnPametfrog_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/EnPametfrog_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_80869FBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A024.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A068.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A0F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A1A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A238.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A2CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A428.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A4E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A554.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A6B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A724.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A80C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A878.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A8C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A964.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086AA60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086AAA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086AB04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086AB68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086AC0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086AD34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086AE48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086AEC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086AFC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086B140.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086B478.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086B570.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086B66C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086B794.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086B864.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086B8CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086B9D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086BA6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086BB4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086BB9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086BBE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086BDA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086BE60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086BEEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086BF90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086C088.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086C0CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086C1AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086C274.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086C4B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086C5A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086C618.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086C6D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086C72C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086C7C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086C81C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086C94C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086C99C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086CB4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086CC04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086CC84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086CD04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086CD6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086CEB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086CEF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086D084.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086D140.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086D1E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086D230.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/EnPametfrog_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086D730.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/EnPametfrog_Draw.asm")
