#include "z_en_suttari.h"

#define FLAGS 0x00000019

#define THIS ((EnSuttari*)thisx)

void EnSuttari_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSuttari_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSuttari_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSuttari_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Suttari_InitVars = {
    ACTOR_EN_SUTTARI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BOJ,
    sizeof(EnSuttari),
    (ActorFunc)EnSuttari_Init,
    (ActorFunc)EnSuttari_Destroy,
    (ActorFunc)EnSuttari_Update,
    (ActorFunc)EnSuttari_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAA6D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAA848.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAA88C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAA8D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAA904.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAA9B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAAA94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAAB78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAAF1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAAFDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAB1A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAB374.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAB434.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAB490.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAB4F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAB698.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAB758.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAB8F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BABA90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BABB90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BABC48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BABDD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BABF64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BABFD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAC220.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAC2FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAC6E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BACA14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BACBB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BACD2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BACE4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BACEE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAD004.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAD130.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAD230.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAD2B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAD380.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAD5F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAD7F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BADA08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BADA9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BADD0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BADDB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BADE14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BADE8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BADF3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/EnSuttari_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/EnSuttari_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/EnSuttari_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAE250.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAE3C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAE524.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/EnSuttari_Draw.asm")
