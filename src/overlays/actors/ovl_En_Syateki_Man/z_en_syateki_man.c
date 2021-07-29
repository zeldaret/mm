#include "z_en_syateki_man.h"

#define FLAGS 0x08000019

#define THIS ((EnSyatekiMan*)thisx)

void EnSyatekiMan_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiMan_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiMan_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiMan_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809C6810(EnSyatekiMan* this, GlobalContext* globalCtx);
void func_809C6848(EnSyatekiMan* this, GlobalContext* globalCtx);
void func_809C6E30(EnSyatekiMan* this, GlobalContext* globalCtx);
void func_809C72D8(EnSyatekiMan* this, GlobalContext* globalCtx);
void func_809C7990(EnSyatekiMan* this, GlobalContext* globalCtx);
void func_809C7A90(EnSyatekiMan* this, GlobalContext* globalCtx);
void func_809C7C14(EnSyatekiMan* this, GlobalContext* globalCtx);
void func_809C7D14(EnSyatekiMan* this, GlobalContext* globalCtx);
void func_809C7EB4(EnSyatekiMan* this, GlobalContext* globalCtx);
void func_809C7FFC(EnSyatekiMan* this, GlobalContext* globalCtx);
void func_809C80C0(EnSyatekiMan* this, GlobalContext* globalCtx);
void func_809C81D0(EnSyatekiMan* this, GlobalContext* globalCtx);
void func_809C8488(EnSyatekiMan* this, GlobalContext* globalCtx);
void func_809C8610(EnSyatekiMan* this, GlobalContext* globalCtx);
void func_809C8710(EnSyatekiMan* this, GlobalContext* globalCtx);
void func_809C8808(EnSyatekiMan* this, GlobalContext* globalCtx);
void func_809C898C(EnSyatekiMan* this, GlobalContext* globalCtx);
void func_809C8BF0(EnSyatekiMan* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Syateki_Man_InitVars = {
    ACTOR_EN_SYATEKI_MAN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SHN,
    sizeof(EnSyatekiMan),
    (ActorFunc)EnSyatekiMan_Init,
    (ActorFunc)EnSyatekiMan_Destroy,
    (ActorFunc)EnSyatekiMan_Update,
    (ActorFunc)EnSyatekiMan_Draw,
};

#endif

extern UNK_TYPE D_060062C8;
extern UNK_TYPE D_0600D2F8;
extern UNK_TYPE D_0600DFEC;
extern UNK_TYPE D_0600F2D0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C64C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/EnSyatekiMan_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/EnSyatekiMan_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C6720.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C6810.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C6848.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C6A04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C6C2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C6E30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C6F98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C72D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C7380.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C7620.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C7990.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C7A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C7C14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C7D14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C7EB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C7FFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C80C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C81D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C8488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C8610.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C8710.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C8808.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C898C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C8BF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C8DE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/EnSyatekiMan_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C8EE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/func_809C8FAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Man/EnSyatekiMan_Draw.s")
