#include "z_en_nb.h"

#define FLAGS 0x00000039

#define THIS ((EnNb*)thisx)

void EnNb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNb_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
const ActorInit En_Nb_InitVars = {
    ACTOR_EN_NB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_NB,
    sizeof(EnNb),
    (ActorFunc)EnNb_Init,
    (ActorFunc)EnNb_Destroy,
    (ActorFunc)EnNb_Update,
    (ActorFunc)EnNb_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BC15F0 = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 10, 68, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80BC161C = { 0, 0, 0, 0, MASS_IMMOVABLE };


extern ColliderCylinderInit D_80BC15F0;
extern CollisionCheckInfoInit2 D_80BC161C;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BBFDB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BBFE60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BBFE8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BBFF24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BBFF90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BBFFD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC0050.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC00AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC01DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC045C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC04FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC05A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC06C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC0800.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC08E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC0978.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC0A18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC0B98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC0C0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC0C80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC0D08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC0D1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC0D84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC0EAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/EnNb_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/EnNb_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/EnNb_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC1174.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC11B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/func_80BC1278.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nb_0x80BBFDB0/EnNb_Draw.asm")
