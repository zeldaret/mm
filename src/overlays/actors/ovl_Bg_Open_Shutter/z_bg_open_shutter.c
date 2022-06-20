/*
 * File: z_bg_open_shutter.c
 * Overlay: ovl_Bg_Open_Shutter
 * Description: Sliding doors in opening dungeon
 */

#include "z_bg_open_shutter.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgOpenShutter*)thisx)

void BgOpenShutter_Init(Actor* thisx, GlobalContext* globalCtx);
void BgOpenShutter_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgOpenShutter_Update(Actor* thisx, GlobalContext* globalCtx);
void BgOpenShutter_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80ACAD88(BgOpenShutter* this, GlobalContext* globalCtx);
void func_80ACAE5C(BgOpenShutter* this, GlobalContext* globalCtx);
void func_80ACAEF0(BgOpenShutter* this, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Open_Shutter_InitVars = {
    ACTOR_BG_OPEN_SHUTTER,
    ACTORCAT_DOOR,
    FLAGS,
    OBJECT_OPEN_OBJ,
    sizeof(BgOpenShutter),
    (ActorFunc)BgOpenShutter_Init,
    (ActorFunc)BgOpenShutter_Destroy,
    (ActorFunc)BgOpenShutter_Update,
    (ActorFunc)BgOpenShutter_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80ACB140[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 350, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 350, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80ACB140[];

extern UNK_TYPE D_060003E8;
extern UNK_TYPE D_06001640;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Shutter/func_80ACAB10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Shutter/func_80ACABA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Shutter/BgOpenShutter_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Shutter/BgOpenShutter_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Shutter/func_80ACAD88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Shutter/func_80ACAE5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Shutter/func_80ACAEF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Shutter/BgOpenShutter_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Shutter/BgOpenShutter_Draw.s")
