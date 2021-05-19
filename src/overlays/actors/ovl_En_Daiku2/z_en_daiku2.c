#include "z_en_daiku2.h"

#define FLAGS 0x00000009

#define THIS ((EnDaiku2*)thisx)

void EnDaiku2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDaiku2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDaiku2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDaiku2_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Daiku2_InitVars = {
    ACTOR_EN_DAIKU2,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DAIKU,
    sizeof(EnDaiku2),
    (ActorFunc)EnDaiku2_Init,
    (ActorFunc)EnDaiku2_Destroy,
    (ActorFunc)EnDaiku2_Update,
    (ActorFunc)EnDaiku2_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/func_80BE61D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/EnDaiku2_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/EnDaiku2_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/func_80BE6408.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/func_80BE64C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/func_80BE65B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/func_80BE66E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/func_80BE6B40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/func_80BE6BC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/func_80BE6CFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/func_80BE6D40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/func_80BE6EB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/func_80BE6EF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/func_80BE71A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/func_80BE71D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/EnDaiku2_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/func_80BE738C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/EnDaiku2_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/func_80BE7504.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/func_80BE7600.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Daiku2_0x80BE61D0/func_80BE7718.asm")
