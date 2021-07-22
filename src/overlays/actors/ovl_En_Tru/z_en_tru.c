#include "z_en_tru.h"

#define FLAGS 0x00000039

#define THIS ((EnTru*)thisx)

void EnTru_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTru_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTru_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTru_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
const ActorInit En_Tru_InitVars = {
    ACTOR_EN_TRU,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TRU,
    sizeof(EnTru),
    (ActorFunc)EnTru_Init,
    (ActorFunc)EnTru_Destroy,
    (ActorFunc)EnTru_Update,
    (ActorFunc)EnTru_Draw,
};


// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_80A8B2A0 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 0, { { 0, 0, 0 }, 32 }, 100 },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80A8B2CC = { 1, 20, 0, 0, MASS_IMMOVABLE };


extern ColliderSphereInit D_80A8B2A0;
extern CollisionCheckInfoInit2 D_80A8B2CC;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A85620.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A85788.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A85AA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A85BCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A85E2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A85F84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A86384.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A86460.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A86674.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A86770.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A868F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A86924.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A8697C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A869DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A86B0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A86BAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A86DB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A871E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A872AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A873B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A87400.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A875AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A8777C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A87880.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A87B48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A87DC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A87FD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A881E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/EnTru_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/EnTru_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/EnTru_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A885B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A88698.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/func_80A886D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_0x80A85620/EnTru_Draw.asm")
