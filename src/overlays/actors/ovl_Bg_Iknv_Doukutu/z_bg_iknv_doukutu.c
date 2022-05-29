/*
 * File: z_bg_iknv_doukutu.c
 * Overlay: ovl_Bg_Iknv_Doukutu
 * Description: Sharp's Cave
 */

#include "z_bg_iknv_doukutu.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((BgIknvDoukutu*)thisx)

void BgIknvDoukutu_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIknvDoukutu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIknvDoukutu_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIknvDoukutu_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BD716C(BgIknvDoukutu* this, GlobalContext* globalCtx);
void func_80BD71BC(BgIknvDoukutu* this, GlobalContext* globalCtx);
void func_80BD7250(BgIknvDoukutu* this, GlobalContext* globalCtx);
void func_80BD72BC(BgIknvDoukutu* this, GlobalContext* globalCtx);
void func_80BD7360(BgIknvDoukutu* this, GlobalContext* globalCtx);
void func_80BD73D0(BgIknvDoukutu* this, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Iknv_Doukutu_InitVars = {
    ACTOR_BG_IKNV_DOUKUTU,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_IKNV_OBJ,
    sizeof(BgIknvDoukutu),
    (ActorFunc)BgIknvDoukutu_Init,
    (ActorFunc)BgIknvDoukutu_Destroy,
    (ActorFunc)BgIknvDoukutu_Update,
    (ActorFunc)BgIknvDoukutu_Draw,
};

#endif

extern UNK_TYPE D_0600F1C0;
extern UNK_TYPE D_06010D98;
extern UNK_TYPE D_060117A0;
extern UNK_TYPE D_06012728;
extern UNK_TYPE D_06012788;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu/BgIknvDoukutu_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu/BgIknvDoukutu_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu/func_80BD716C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu/func_80BD71BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu/func_80BD7250.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu/func_80BD72BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu/func_80BD7360.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu/func_80BD73D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu/BgIknvDoukutu_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu/BgIknvDoukutu_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu/func_80BD7538.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu/func_80BD7768.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu/func_80BD7820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu/func_80BD78C4.s")
