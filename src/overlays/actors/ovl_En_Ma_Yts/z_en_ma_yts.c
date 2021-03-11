#include "z_en_ma_yts.h"

#define FLAGS 0x02100009

#define THIS ((EnMaYts*)thisx)

void EnMaYts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMaYts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMaYts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMaYts_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ma_Yts_InitVars = {
    ACTOR_EN_MA_YTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MA1,
    sizeof(EnMaYts),
    (ActorFunc)EnMaYts_Init,
    (ActorFunc)EnMaYts_Destroy,
    (ActorFunc)EnMaYts_Update,
    (ActorFunc)EnMaYts_Draw
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D030.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D0BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D12C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D1E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D2D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/EnMaYts_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/EnMaYts_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D698.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D6AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D6BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D6F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D95C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D970.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8D9E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8DA28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8DBB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8DD88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/EnMaYts_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8DE44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8DF18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/EnMaYts_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yts_0x80B8D030/func_80B8E0BC.asm")
