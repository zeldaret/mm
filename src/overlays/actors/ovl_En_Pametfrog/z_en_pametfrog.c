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
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BIGSLIME,
    sizeof(EnPametfrog),
    (ActorFunc)EnPametfrog_Init,
    (ActorFunc)EnPametfrog_Destroy,
    (ActorFunc)EnPametfrog_Update,
    (ActorFunc)EnPametfrog_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/EnPametfrog_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/EnPametfrog_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_80869FBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086A024.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086A068.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086A0F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086A1A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086A238.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086A2CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086A428.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086A4E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086A554.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086A6B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086A724.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086A80C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086A878.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086A8C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086A964.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086AA60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086AAA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086AB04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086AB68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086AC0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086AD34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086AE48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086AEC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086AFC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086B140.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086B478.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086B570.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086B66C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086B794.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086B864.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086B8CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086B9D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086BA6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086BB4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086BB9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086BBE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086BDA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086BE60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086BEEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086BF90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086C088.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086C0CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086C1AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086C274.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086C4B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086C5A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086C618.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086C6D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086C72C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086C7C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086C81C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086C94C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086C99C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086CB4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086CC04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086CC84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086CD04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086CD6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086CEB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086CEF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086D084.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086D140.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086D1E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086D230.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/EnPametfrog_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/func_8086D730.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pametfrog/EnPametfrog_Draw.s")
