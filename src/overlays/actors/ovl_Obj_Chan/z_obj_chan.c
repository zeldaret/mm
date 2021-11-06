/*
 * File: z_obj_chan.c
 * Overlay: ovl_Obj_Chan
 * Description: Goron Shrine chandelier
 */

#include "z_obj_chan.h"

#define FLAGS 0x00000030

#define THIS ((ObjChan*)thisx)

void ObjChan_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjChan_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjChan_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjChan_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BB9F24(ObjChan* this, GlobalContext* globalCtx);
void func_80BBA314(ObjChan* this, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Chan_InitVars = {
    ACTOR_OBJ_CHAN,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_OBJECT_UNSET_CHAN,
    sizeof(ObjChan),
    (ActorFunc)ObjChan_Init,
    (ActorFunc)ObjChan_Destroy,
    (ActorFunc)ObjChan_Update,
    (ActorFunc)ObjChan_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BBAB30 = {
    { COLTYPE_HARD, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 48, 76, -60, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80BBAB5C[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80BBAB30;
extern InitChainEntry D_80BBAB5C[];

extern UNK_TYPE D_06000AF0;
extern UNK_TYPE D_06001960;
extern UNK_TYPE D_06002358;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/ObjChan_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/ObjChan_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/func_80BB9A1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/func_80BB9B40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/func_80BB9C08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/func_80BB9F24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/func_80BBA2FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/func_80BBA314.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/func_80BBA488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/ObjChan_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/ObjChan_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/func_80BBA894.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chan/func_80BBA930.s")
