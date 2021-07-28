#include "z_en_sob1.h"

#define FLAGS 0x00000019

#define THIS ((EnSob1*)thisx)

void EnSob1_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSob1_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSob1_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Sob1_InitVars = {
    ACTOR_EN_OSSAN,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnSob1),
    (ActorFunc)EnSob1_Init,
    (ActorFunc)EnSob1_Destroy,
    (ActorFunc)EnSob1_Update,
    (ActorFunc)NULL,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A109E8[] = {
    ICHAIN_F32(targetArrowOffset, 500, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80A109E8[];

extern UNK_TYPE D_06000970;
extern UNK_TYPE D_06005458;
extern UNK_TYPE D_06008268;
extern UNK_TYPE D_06009120;
extern UNK_TYPE D_0600D208;
extern UNK_TYPE D_06011AC8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/D_80A10A50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0C810.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0C8AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0C8B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0C938.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0CA38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0CC88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0CCEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0CD48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0CE10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/EnSob1_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/EnSob1_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0D034.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0D0B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0D188.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0D1F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0D258.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0D2B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0D320.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0D388.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0D3C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0D414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0D4A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0D628.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0D74C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0D77C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0D850.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0D904.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0DA5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0DAAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0DB78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0DCC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0DD40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0DE64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0DFD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0E0C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0E1B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0E258.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0E330.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0E420.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0E4DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0E518.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0E554.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0E884.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0E96C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0E9E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0EA84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0EAF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0EBC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0EC98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0ED7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0EDA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0EE3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0EEC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0EF48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0F014.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0F1C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0F284.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0F2C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0F2FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0F39C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0F3D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0F470.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0F554.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0F638.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0F6B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/EnSob1_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0FADC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0FD4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A0FEE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A10290.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A102C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A10308.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A10344.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A10368.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A104E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sob1/func_80A10608.s")
