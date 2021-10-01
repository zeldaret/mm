#include "z_en_giant.h"

#define FLAGS 0x00000030

#define THIS ((EnGiant*)thisx)

void EnGiant_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGiant_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGiant_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGiant_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B023D0(EnGiant* this, GlobalContext* globalCtx);
void func_80B024AC(EnGiant* this, GlobalContext* globalCtx);
void func_80B024D8(EnGiant* this, GlobalContext* globalCtx);

const ActorInit En_Giant_InitVars = {
    ACTOR_EN_GIANT,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GIANT,
    sizeof(EnGiant),
    (ActorFunc)EnGiant_Init,
    (ActorFunc)EnGiant_Destroy,
    (ActorFunc)EnGiant_Update,
    (ActorFunc)EnGiant_Draw,
};

extern UNK_TYPE D_06002168;
extern UNK_TYPE D_06007610;
extern UNK_TYPE D_060116E4;

s32 D_80B02950[] = {
    0x06008394, 0x060096E4, 0x060102A4, 0x060116E4, 0x06012A38, 0x06013004, 0x06013FE8, 0x06015334,
    0x06017944, 0x0600A1C4, 0x0600D040, 0x0600DE84, 0x0600ACA4, 0x0600B784, 0x0600C5D4,
};

s32 D_80B0298C[] = { 0x06005A80, 0x06006280, 0x06006A80, 0x00000000, 0x00000000 };

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B01990.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B01A74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/EnGiant_Init.s")

void EnGiant_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B01E84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B01EE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B020A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B0211C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B02234.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B02354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B023D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B024AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B024D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/EnGiant_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B02688.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/func_80B026C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Giant/EnGiant_Draw.s")
