/*
 * File: z_obj_mure2.c
 * Overlay: ovl_Obj_Mure2
 * Description: Circle of rocks spawner
 */

#include "z_obj_mure2.h"

#define FLAGS 0x00000000

#define THIS ((ObjMure2*)thisx)

void ObjMure2_Init(Actor* thisx, PlayState* play);
void ObjMure2_Update(Actor* thisx, PlayState* play);

void func_809613C4(ObjMure2* this, PlayState* play);
void func_809613FC(ObjMure2* this, PlayState* play);
void func_80961490(ObjMure2* this, PlayState* play);

void func_80960CF0(Vec3f*, Vec3f*);
void func_80960E0C(Vec3f*, Vec3f*);
void func_80960F0C(Vec3f*, Vec3f*);

#if 1
ActorInit Obj_Mure2_InitVars = {
    /**/ ACTOR_OBJ_MURE2,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(ObjMure2),
    /**/ ObjMure2_Init,
    /**/ Actor_Noop,
    /**/ ObjMure2_Update,
    /**/ NULL,
};

Vec3f D_80961590 = {
2560000.0,
2560000.0,
2560000.0,
};

Vec3f D_8096159C = {
2907025.0,
2907025.0,
2907025.0,
};

s16 D_809615A8[] = {
0x0009,0x000C,
0x0008,0x0000,
};

s16 D_809615B0[] = {
0x0090,0x0090,
0x00B0,0x0000,
};

s16 D_809615B8[] = {
0x0028,0x0666,
0x0028,0x2CCC,
0x0028,0x5999,
0x0028,0x8666,
0x0014,0xC000,
0x0050,0x1333,
0x0050,0x4000,
0x0050,0x6CCC,
0x0050,0x9333,
0x0050,0xACCC,
0x0050,0xC666,
0x003C,0xE000,
};

typedef void (*ObjMure2UnkFunc)(Vec3f*, Vec3f*);
ObjMure2UnkFunc D_809615E8[] = {
func_80960CF0,
func_80960E0C,
func_80960F0C,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_809615F4[] = {
    ICHAIN_F32(uncullZoneForward, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 2100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_809615F4[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure2/func_80960CF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure2/func_80960E0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure2/func_80960F0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure2/func_80961018.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure2/func_8096104C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure2/func_809611BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure2/func_809612BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure2/ObjMure2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure2/func_809613B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure2/func_809613C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure2/func_809613E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure2/func_809613FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure2/func_8096147C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure2/func_80961490.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure2/ObjMure2_Update.s")
