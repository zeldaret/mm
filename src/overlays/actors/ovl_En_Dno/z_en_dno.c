#include "z_en_dno.h"

#define FLAGS 0x00000039

#define THIS ((EnDno*)thisx)

void EnDno_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDno_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDno_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDno_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit En_Dno_InitVars = {
    ACTOR_EN_DNO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNO,
    sizeof(EnDno),
    (ActorFunc)EnDno_Init,
    (ActorFunc)EnDno_Destroy,
    (ActorFunc)EnDno_Update,
    (ActorFunc)EnDno_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A73B00 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 17, 58, 0, { 0, 0, 0 } },
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A73B38[] = {
    ICHAIN_F32(uncullZoneDownward, 80, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_STOP),
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A711D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A71424.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A714B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A7153C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A715DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A71788.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/EnDno_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/EnDno_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A71B04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A71B58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A71B68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A71C3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A71E54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A71F18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A72438.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A724B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A7256C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A72598.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A725E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A725F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A72AE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A72B3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A72B84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A72BA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A72C04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A72CF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A72D8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A72FAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A730A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A73244.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A732C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A73408.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/EnDno_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/EnDno_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A7361C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dno_0x80A711D0/func_80A73654.asm")
