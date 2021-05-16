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
    (ActorFunc)EnMaYto_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/EnMaYto_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8E6E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8E84C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8E938.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8EA38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8EABC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/EnMaYto_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8EBDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8EBF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8EC30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8ECAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8ED8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8EDC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8EEAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8EF4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8F074.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8F108.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8F254.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8F2D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8F360.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8F400.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8F744.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8F7F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8F918.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8F998.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8FA14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8FE04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8FE74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8FF80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B8FF94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B9000C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B900AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B900C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B90170.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B90184.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B902B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B902CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B90340.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B9037C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B904D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B904E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B9059C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B905B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B9061C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B9083C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B90A78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B90C08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B90C78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B90D98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B90DF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B90E50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B90E84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B90EC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B90EF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B90F84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B91014.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B9109C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/EnMaYto_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B91154.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/func_80B91250.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma_Yto/EnMaYto_Draw.s")
