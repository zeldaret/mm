#include "z_obj_syokudai.h"

#define FLAGS 0x00000410

#define THIS ((ObjSyokudai*)thisx)

void ObjSyokudai_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjSyokudai_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjSyokudai_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjSyokudai_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Syokudai_InitVars = {
    ACTOR_OBJ_SYOKUDAI,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_SYOKUDAI,
    sizeof(ObjSyokudai),
    (ActorFunc)ObjSyokudai_Init,
    (ActorFunc)ObjSyokudai_Destroy,
    (ActorFunc)ObjSyokudai_Update,
    (ActorFunc)ObjSyokudai_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808BCCC0 = {
    { COLTYPE_METAL, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0x00100000, 0x00, 0x00 }, { 0xF6CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 12, 45, 0, { 0, 0, 0 } },
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808BCCEC = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0x00000000, 0x00, 0x00 }, { 0x00000820, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 15, 45, 45, { 0, 0, 0 } },
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808BCD18[] = {
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 800, ICHAIN_STOP),
};


extern ColliderCylinderInit D_808BCCC0;
extern ColliderCylinderInit D_808BCCEC;
extern InitChainEntry D_808BCD18[];
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Syokudai/ObjSyokudai_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Syokudai/ObjSyokudai_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Syokudai/ObjSyokudai_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Syokudai/ObjSyokudai_Draw.s")
