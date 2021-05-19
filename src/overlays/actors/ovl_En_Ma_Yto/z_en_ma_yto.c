#include "z_en_ma_yto.h"

#define FLAGS 0x02100009

#define THIS ((EnMaYto*)thisx)

void EnMaYto_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMaYto_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMaYto_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMaYto_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ma_Yto_InitVars = {
    ACTOR_EN_MA_YTO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MA2,
    sizeof(EnMaYto),
    (ActorFunc)EnMaYto_Init,
    (ActorFunc)EnMaYto_Destroy,
    (ActorFunc)EnMaYto_Update,
    (ActorFunc)EnMaYto_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/EnMaYto_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8E6E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8E84C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8E938.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EA38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EABC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/EnMaYto_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EBDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EBF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EC30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8ECAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8ED8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EDC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EEAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8EF4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F074.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F108.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F254.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F2D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F360.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F400.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F744.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F7F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F918.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8F998.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8FA14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8FE04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8FE74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8FF80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B8FF94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B9000C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B900AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B900C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90170.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90184.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B902B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B902CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90340.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B9037C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B904D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B904E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B9059C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B905B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B9061C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B9083C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90A78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90C08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90C78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90D98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90DF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90E50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90E84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90EC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90EF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B90F84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B91014.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B9109C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/EnMaYto_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B91154.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/func_80B91250.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma_Yto_0x80B8E520/EnMaYto_Draw.asm")
