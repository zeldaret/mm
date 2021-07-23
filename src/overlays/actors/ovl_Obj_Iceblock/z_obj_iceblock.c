#include "z_obj_iceblock.h"

#define FLAGS 0x00000010

#define THIS ((ObjIceblock*)thisx)

void ObjIceblock_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjIceblock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjIceblock_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjIceblock_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Iceblock_InitVars = {
    ACTOR_OBJ_ICEBLOCK,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_ICE_BLOCK,
    sizeof(ObjIceblock),
    (ActorFunc)ObjIceblock_Init,
    (ActorFunc)ObjIceblock_Destroy,
    (ActorFunc)ObjIceblock_Update,
    (ActorFunc)ObjIceblock_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A26E50 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_NO_PUSH | OC1_TYPE_PLAYER, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000800, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 44, 62, -31, { 0, 0, 0 } },
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A26FA4[] = {
    ICHAIN_F32_DIV1000(speedXZ, 16000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1800, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(minVelocityY, -26000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 150, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_STOP),
};


extern ColliderCylinderInit D_80A26E50;
extern InitChainEntry D_80A26FA4[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A23090.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A2311C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A2319C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A232C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A23370.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A2339C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A23690.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A236D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A237A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A23938.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A23B88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A23D08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A23F90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A24118.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A24384.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A243E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A24680.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A246D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A2491C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A24954.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A24A48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A24AA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A24B74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A24BDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A24DC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A24DD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A2508C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A25238.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A252DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A25404.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A2541C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A25440.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/ObjIceblock_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/ObjIceblock_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A257A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A257B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A25824.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A2586C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A25978.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A25994.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A25A8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A25AA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A25BA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A25BBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A25C5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A25C70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A25CF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A25D28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A25E3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A25E50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A25FA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A25FD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A260E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A26144.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A262BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A262EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A26574.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A265C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A266C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A266E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/ObjIceblock_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A26B64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A26B74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/func_80A26BF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Iceblock_0x80A23090/ObjIceblock_Draw.asm")
