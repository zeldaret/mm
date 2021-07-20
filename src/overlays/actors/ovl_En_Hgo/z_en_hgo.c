#include "z_en_hgo.h"

#define FLAGS 0x02000019

#define THIS ((EnHgo*)thisx)

void EnHgo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHgo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHgo_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHgo_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit En_Hgo_InitVars = {
    ACTOR_EN_HGO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_HARFGIBUD,
    sizeof(EnHgo),
    (ActorFunc)EnHgo_Init,
    (ActorFunc)EnHgo_Destroy,
    (ActorFunc)EnHgo_Update,
    (ActorFunc)EnHgo_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BD0F48 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 18, 46, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80BD0F74 = { 0, 0, 0, 0, MASS_IMMOVABLE };

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/EnHgo_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/EnHgo_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD03EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD0410.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD0420.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD0434.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD049C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD04E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD064C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD0660.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD06FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD0898.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD0B8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/EnHgo_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD0CF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD0D38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/EnHgo_Draw.asm")
