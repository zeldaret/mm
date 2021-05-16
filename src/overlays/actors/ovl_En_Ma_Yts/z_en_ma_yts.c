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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/func_80B8D030.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/func_80B8D0BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/func_80B8D12C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/func_80B8D1E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/func_80B8D2D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/EnMaYts_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/EnMaYts_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/func_80B8D698.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/func_80B8D6AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/func_80B8D6BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/func_80B8D6F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/func_80B8D95C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/func_80B8D970.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/func_80B8D9E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/func_80B8DA28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/func_80B8DBB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/func_80B8DD88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/EnMaYts_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/func_80B8DE44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/func_80B8DF18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/EnMaYts_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yts/func_80B8E0BC.s")
