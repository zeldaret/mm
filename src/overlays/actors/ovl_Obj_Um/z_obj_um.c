/*
 * File: z_obj_um.c
 * Overlay: ovl_Obj_Um
 * Description: Cremia's cart and milk run quest
 */

#include "z_obj_um.h"
#include "overlays/actors/ovl_En_In/z_en_in.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjUm*)thisx)

void ObjUm_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjUm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjUm_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjUm_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B79A50(ObjUm* this, GlobalContext* globalCtx);
void func_80B79F10(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A070(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A0E0(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A144(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A2AC(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A394(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A400(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A494(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A614(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A7AC(ObjUm* this, GlobalContext* globalCtx);
void func_80B7ABE4(ObjUm* this, GlobalContext* globalCtx);
void func_80B7AC94(ObjUm* this, GlobalContext* globalCtx);
void func_80B7AD34(ObjUm* this, GlobalContext* globalCtx);
void func_80B7AE58(ObjUm* this, GlobalContext* globalCtx);

void ObjUm_SetupAction(ObjUm* this, ObjUmActionFunc actionFunc);

const ActorInit Obj_Um_InitVars = {
    ACTOR_OBJ_UM,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_UM,
    sizeof(ObjUm),
    (ActorFunc)ObjUm_Init,
    (ActorFunc)ObjUm_Destroy,
    (ActorFunc)ObjUm_Update,
    (ActorFunc)ObjUm_Draw,
};


extern FlexSkeletonHeader D_06011DF8;
extern AnimationHeader D_06012CC0;
extern CollisionHeader D_06007E20;
extern CollisionHeader D_06007F50;

extern Gfx D_06000040[];
extern Gfx D_06000910[];
extern Gfx D_060011E0[];

extern Gfx D_04075A40[];



extern TexturePtr D_060164D0;
extern TexturePtr D_060168D0;
extern TexturePtr D_06016CD0;
extern TexturePtr D_060170D0;
extern TexturePtr D_060174D0;
extern TexturePtr D_060178D0;

TexturePtr D_80B7C110[] = {
    &D_060164D0,
    &D_060168D0,
    &D_06016CD0,
    &D_060170D0,
    &D_060174D0,
    &D_060178D0,
};

extern TexturePtr D_06017CD0;
extern TexturePtr D_06017ED0;
extern TexturePtr D_060182D0;
extern TexturePtr D_060180D0;

TexturePtr D_80B7C128[] = {
    &D_06017CD0,
    &D_06017ED0,
    &D_060182D0,
    &D_060180D0,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_HIT3, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000020, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 40, 64, 0, { 0, 0, 0 } },
};

typedef struct {
    /* 0x00 */ UNK_TYPE unk_00;
    /* 0x04 */ UNK_TYPE unk_04;
    /* 0x08 */ UNK_TYPE unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ UNK_TYPE unk_10;
} struct_80B7C254; // size = 0x14

// TODO
struct_80B7C254 D_80B7C164[12] = {
    {2, 0, 0, 1.0f, 0x28},
    {4, 1, 0, 1.0f, 0x28},
    {3, 2, 0, 1.0f, 0x28},
    {3, 4, 0, 1.0f, 0x28},
    {5, 3, 1, -1.0f, 0x1E},
    {7, 3, 1, 1.0f, 0x1E},
    {0, 0xD, 1, -1.0f, 0x3C},
    {1, 0xE, 1, 1.0f, 0x3C},
    {0xD, 0xA, 0, 1.0f, 0x28},
    {0xE, 8, 0, 1.0f, 0x28},
    {8, 5, 0, 1.0f, 0x1E},
    {0xA, 7, 0, 1.0f, 0x1E},
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_STOP),
};

typedef struct {
    /* 0x00 */ AnimationHeader* unk_00;
    /* 0x04 */ s32 unk_04;
} struct_80B7C25C; // size = 0x08

extern AnimationHeader D_06012CC0;
extern AnimationHeader D_0601213C;
extern AnimationHeader D_06019E10;
extern AnimationHeader D_060126C4;


// [3]? [5]?
struct_80B7C25C D_80B7C25C[] = {
    {&D_06012CC0, 1},
    {&D_0601213C, 1},
    {&D_06019E10, 0}
};

struct_80B7C25C D_80B7C274[] = {
    {NULL, 0},
    {&D_060126C4, 0}
};

Vec3f D_80B7C284 = {4223.0f, -979.0f, 4098.0f};
Vec3f D_80B7C290 = {4223.0f, -980.0f, -4083.0f};


// actionfuncs
void func_80B7A144(ObjUm* this, GlobalContext* globalCtx);
void func_80B79A50(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A400(ObjUm* this, GlobalContext* globalCtx);
void func_80B7AC94(ObjUm* this, GlobalContext* globalCtx);
void func_80B7AE58(ObjUm* this, GlobalContext* globalCtx);
void func_80B7AEFC(ObjUm* this, GlobalContext* globalCtx);
void func_80B7AC94(ObjUm* this, GlobalContext* globalCtx);
void func_80B79F10(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A0E0(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A070(ObjUm* this, GlobalContext* globalCtx);
void func_80B79FFC(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A2AC(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A240(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A2AC(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A394(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A494(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A614(ObjUm* this, GlobalContext* globalCtx);
void func_80B7ABE4(ObjUm* this, GlobalContext* globalCtx);
void func_80B7AB78(ObjUm* this, GlobalContext* globalCtx);
void func_80B7ABE4(ObjUm* this, GlobalContext* globalCtx);
void func_80B7AD34(ObjUm* this, GlobalContext* globalCtx);


void func_80B7B154(ObjUm* this, GlobalContext* globalCtx);

void func_80B7B18C(ObjUm* this, GlobalContext* globalCtx, s32);

s32 func_80B78D08(ObjUm* this, GlobalContext* globalCtx);
void func_80B78E88(ObjUm* this, GlobalContext* globalCtx, s16 arg2);
void func_80B77770(ObjUm* this, GlobalContext* globalCtx);

void func_80B77770(ObjUm* this, GlobalContext* globalCtx) {
    s16 rotY = this->dyna.actor.shape.rot.y;
    Vec3f sp108;
    Vec3f spFC;
    Vec3f spF0;
    Vec3f spE4;
    Vec3f spD8;
    Vec3f spCC;
    Vec3f spC0;
    Vec3f spB4;
    Vec3f spA8;
    Vec3f sp9C;
    Vec3f sp90;
    Vec3f sp84;
    Vec3f sp78;
    Vec3f sp6C;
    Vec3f sp60 = this->dyna.actor.world.pos;

    this->unk_360[15] = sp60;
    sp6C = sp60;
    this->unk_360[14] = sp6C;
    sp78 = sp6C;
    this->unk_360[13] = sp78;
    sp84 = sp78;
    this->unk_360[12] = sp84;
    sp90 = sp84;
    this->unk_360[11] = sp90;
    sp9C = sp90;
    this->unk_360[10] = sp9C;
    spA8 = sp9C;
    this->unk_360[9] = spA8;
    spB4 = spA8;
    this->unk_360[8] = spB4;
    spC0 = spB4;
    this->unk_360[7] = spC0;
    spCC = spC0;
    this->unk_360[6] = spCC;
    spD8 = spCC;
    this->unk_360[5] = spD8;
    spE4 = spD8;
    this->unk_360[4] = spE4;
    spF0 = spE4;
    this->unk_360[3] = spF0;
    spFC = spF0;
    this->unk_360[2] = spFC;
    sp108 = spFC;
    this->unk_360[1] = sp108;
    this->unk_360[0] = sp108;

    this->unk_360[0].x += 110.0f * Math_SinS(rotY + 0x4000);
    this->unk_360[0].z += 110.0f * Math_CosS(rotY + 0x4000);
    this->unk_360[1].x += 110.0f * Math_SinS(rotY - 0x4000);
    this->unk_360[1].z += 110.0f * Math_CosS(rotY - 0x4000);
    Math_Vec3f_Copy(&this->unk_360[2], &this->unk_360[0]);
    this->unk_360[2].x -= 200.0f * Math_SinS(rotY);
    this->unk_360[2].z -= 200.0f * Math_CosS(rotY);
    Math_Vec3f_Copy(&this->unk_360[4], &this->unk_360[1]);
    this->unk_360[4].x -= 200.0f * Math_SinS(rotY);
    this->unk_360[4].z -= 200.0f * Math_CosS(rotY);
    this->unk_360[3].x -= 220.0f * Math_SinS(rotY);
    this->unk_360[3].z -= 220.0f * Math_CosS(rotY);
    Math_Vec3f_Copy(&this->unk_360[5], &this->unk_360[0]);
    this->unk_360[5].x -= 500.0f * Math_SinS(rotY);
    this->unk_360[5].z -= 500.0f * Math_CosS(rotY);
    Math_Vec3f_Copy(&this->unk_360[7], &this->unk_360[1]);
    this->unk_360[7].x -= 500.0f * Math_SinS(rotY);
    this->unk_360[7].z -= 500.0f * Math_CosS(rotY);
    this->unk_360[6].x -= 500.0f * Math_SinS(rotY);
    this->unk_360[6].z -= 500.0f * Math_CosS(rotY);
    Math_Vec3f_Copy(&this->unk_360[8], &this->unk_360[0]);
    this->unk_360[8].x -= 700.0f * Math_SinS(rotY);
    this->unk_360[8].z -= 700.0f * Math_CosS(rotY);
    Math_Vec3f_Copy(&this->unk_360[10], &this->unk_360[1]);
    this->unk_360[10].x -= 700.0f * Math_SinS(rotY);
    this->unk_360[10].z -= 700.0f * Math_CosS(rotY);
    this->unk_360[9].x -= 700.0f * Math_SinS(rotY);
    this->unk_360[9].z -= 700.0f * Math_CosS(rotY);
    this->unk_360[11] = this->unk_360[3];
    this->unk_360[11].x += 40.0f * Math_SinS(rotY + 0x4000);
    this->unk_360[11].z += 40.0f * Math_CosS(rotY + 0x4000);
    this->unk_360[12] = this->unk_360[3];
    this->unk_360[12].x += 40.0f * Math_SinS(rotY - 0x4000);
    this->unk_360[12].z += 40.0f * Math_CosS(rotY - 0x4000);
    this->unk_360[13] = this->unk_360[2];
    this->unk_360[14] = this->unk_360[4];
}

#ifdef NON_MATCHING
// regalloc
s32 func_80B77FA4(ObjUm* this, GlobalContext* globalCtx) {
    s32 pad[2];
    Vec3s* sp44;
    EnHorse* temp_v0;
    EnHorse* temp_v0_2;

    sp44 = Lib_SegmentedToVirtual(globalCtx->setupPathList[this->unk_2BC].points);
    func_801A89A8(0x8003);

    temp_v0 = Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_HORSE, sp44[0].x, sp44[0].y, sp44[0].z, 0, this->dyna.actor.shape.rot.y, 0, 0x2013);
    this->unk_358 = temp_v0;

    temp_v0->unk_540 = temp_v0->actor.world.pos;

    temp_v0->unk_54C = 0xF;
    temp_v0->unk_550 = 0xA;

    temp_v0->unk_554 = this->unk_2BC;
    temp_v0->unk_568 = 0.0f;
    temp_v0->unk_56C = 0.0f;
    temp_v0->unk_558 = 0;
    temp_v0->unk_55C = 0x28;
    temp_v0->unk_560 = 0x28;

    temp_v0->unk_570 = D_801D15B0;
    temp_v0->unk_57C = D_801D15B0;

    temp_v0->unk_588 = this->dyna.actor.shape.rot.y;
    temp_v0->curRaceWaypoint = 1;


    temp_v0_2 = Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_HORSE, (f32) sp44[1].x, (f32) sp44[1].y, (f32) sp44[1].z, (s16) 0, (s16) (s32) this->dyna.actor.shape.rot.y, (s16) 0, (s16) 0x2014);
    this->unk_35C = temp_v0_2;

    temp_v0_2->unk_540 = temp_v0_2->actor.world.pos;

    temp_v0_2->unk_54C = 0xF;
    temp_v0_2->unk_550 = 8;

    temp_v0_2->unk_554 = (s32) this->unk_2BC;
    temp_v0_2->unk_568 = 0.0f;
    temp_v0_2->unk_56C = 0.0f;
    temp_v0_2->unk_55C = 0x28;
    temp_v0_2->unk_560 = 0x28;

    temp_v0_2->unk_57C = D_801D15B0;

    temp_v0_2->unk_588 = this->dyna.actor.shape.rot.y;
    temp_v0_2->curRaceWaypoint = 2;

    this->unk_314[0] = 4;
    this->unk_314[1] = 4;
    this->unk_314[2] = 4;
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B77FA4.s")
#endif

#ifdef NON_EQUIVALENT
s32 func_80B781DC(ObjUm* this, EnHorse* arg2, EnHorse* arg3, GlobalContext* globalCtx) {
    struct_80B7C254* phi_s0 = D_80B7C164;
    s32 phi_s3;
    s32 phi_s2;
    s32 phi_s4;
    f32 phi_f20;
    s32 i;

    phi_s3 = -1;
    phi_s2 = 0;
    phi_s4 = 0;
    phi_f20 = 0.0f;
    for (i = 0; i < ARRAY_COUNT(D_80B7C164); i++) {
        if (arg2->unk_550 == phi_s0->unk_00) {
            if (arg3->unk_550 != phi_s0->unk_04) {
                if (phi_s0->unk_00 != 3) {
                    if (phi_s0->unk_04 != 3 || Player_GetMask(globalCtx) != PLAYER_MASK_CIRCUS_LEADERS_MASK) {
                        phi_s3 = phi_s0->unk_04;
                        phi_s4 = phi_s0->unk_08;
                        phi_f20 = phi_s0->unk_0C;
                        phi_s2 = phi_s0->unk_10;
                    }
                } else {
                    if (((arg2->unk_54C != 5) || (phi_s0->unk_04 != 2)) && ((arg2->unk_54C != 7) || (phi_s0->unk_04 != 4))) {
                        phi_s3 = phi_s0->unk_04;
                        phi_s4 = phi_s0->unk_08;
                        phi_f20 = phi_s0->unk_0C;
                        if ((2.0f * Rand_ZeroOne()) < 1.0f) {
                            phi_f20 = phi_s0->unk_0C * -1.0f;
                        }
                        phi_s2 = phi_s0->unk_10;
                    }
                }
            }
        }
        phi_s0++;
    }

    if (phi_s3 != -1) {
        arg2->unk_540 = arg2->actor.world.pos;
        arg2->unk_550 = phi_s3;
        arg2->unk_55C = phi_s2;
        arg2->unk_560 = phi_s2;
        arg2->unk_564 = phi_s4;
        arg2->unk_568 = phi_f20;
        arg2->unk_54C = arg2->unk_550;
        if (phi_s3 == 3) {
            arg2->unk_558 = Rand_ZeroOne() * 3.0f;
        } else {
            arg2->unk_558 = 0;
        }
    }

    return 0;
}
#else
s32 func_80B781DC(ObjUm* this, EnHorse* arg2, EnHorse* arg3, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B781DC.s")
#endif

s32 func_80B783E0(ObjUm* this, GlobalContext* globalCtx, s32 arg2, EnHorse* arg3) {
    Path* sp6C = &globalCtx->setupPathList[this->unk_2BC];
    s32 sp68;
    Vec3s* sp64;
    f32 phi_f12;
    s32 phi_v1_2;
    Vec3f sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s32 temp_a1;
    f32 sp3C;
    f32 phi_f14;

    sp68 = sp6C->count;
    sp64 = Lib_SegmentedToVirtual(sp6C->points);

    if (sp68 == 0) {
        return 0;
    }

    if (Math3D_Distance(&arg3->actor.world.pos, &this->dyna.actor.world.pos) < 800.0f) {
        if (arg2 == 0) {
            this->unk_2F4 |= 0x200;
        } else {
            this->unk_2F4 |= 0x400;
        }
        arg3->unk_540 = arg3->actor.world.pos;
        arg3->unk_55C = 0x32;
        arg3->unk_560 = 0x32;
        arg3->unk_564 = 1;
    }

    Math_Vec3s_ToVec3f(&sp50, &sp64[arg3->unk_200]);

    if (arg3->unk_200 == 0) {
        phi_f12 = (f32) (sp64[1].x - sp64[0].x);
        phi_f14 = (f32) (sp64[1].z - sp64[0].z);
    } else {
        if ((arg3->unk_200 + 1) == sp6C->count) {
            phi_f12 = (f32) (sp64[sp6C->count-1].x - sp64[sp6C->count-2].x);
            phi_f14 = (f32) (sp64[sp6C->count-1].z - sp64[sp6C->count-2].z);
        } else {
            phi_f12 = (f32) (sp64[arg3->unk_200+1].x - sp64[arg3->unk_200-1].x);
            phi_f14 = (f32) (sp64[arg3->unk_200+1].z - sp64[arg3->unk_200-1].z);
        }
    }

    temp_a1 = Math_Atan2S(phi_f12, phi_f14);

    func_8017B7F8(&sp50, (s16)temp_a1, &sp4C, &sp48, &sp44);
    if (((arg3->actor.world.pos.x * sp4C) + (sp48 * arg3->actor.world.pos.z) + sp44) > 0.0f) {
        arg3->unk_200++;
        if (arg3->unk_200 >= sp68) {
            arg3->unk_200 = 0;
        }
        Math_Vec3s_ToVec3f(&sp50, &sp64[arg3->unk_200]);
    }

    arg3->actor.world.rot.y = Math_Vec3f_Yaw(&arg3->actor.world.pos, &sp50);
    arg3->actor.speedXZ = 45.0f;

    sp3C = Math_CosS(arg3->actor.world.rot.x) * arg3->actor.speedXZ;
    arg3->actor.velocity.x = Math_SinS(arg3->actor.world.rot.y) * sp3C;
    arg3->actor.velocity.y = Math_SinS(arg3->actor.world.rot.x) * arg3->actor.speedXZ;
    arg3->actor.velocity.z = Math_CosS(arg3->actor.world.rot.y) * sp3C;

    arg3->unk_570.x = arg3->actor.world.pos.x + (arg3->actor.velocity.x * 0.5f) + arg3->actor.colChkInfo.displacement.x;
    arg3->unk_570.y = arg3->actor.world.pos.y + (arg3->actor.velocity.y * 0.5f) + arg3->actor.colChkInfo.displacement.y;
    arg3->unk_570.z = arg3->actor.world.pos.z + (arg3->actor.velocity.z * 0.5f) + arg3->actor.colChkInfo.displacement.z;

    phi_v1_2 = (s16) (arg3->actor.world.rot.y - arg3->actor.shape.rot.y);

    if (phi_v1_2 > 0x190) {
        phi_v1_2 = 0x190;
    } else {
        if (phi_v1_2 < -0x190) {
            phi_v1_2 = -0x190;
        }
    }

    arg3->actor.shape.rot.y = arg3->actor.shape.rot.y + phi_v1_2;
    return 0;
}

s32 func_80B78764(ObjUm* this, GlobalContext* globalCtx, EnHorse* arg2, EnHorse* arg3) {
    s32 pad;
    Vec3f sp30;
    s16 phi_v1_5;

    arg2->unk_55C--;
    if (arg2->unk_55C <= 0) {
        arg2->unk_55C = 0;

        if ((arg2->unk_550 == 3) && !(this->unk_2F4 & 0x2000)) {
            s32 phi_v1_2 = -1;
            if (this->unk_314[0] != 1) {
                phi_v1_2 = 0;
            }

            if (this->unk_314[1] != 1) {
                if ((phi_v1_2 == -1) || (phi_v1_2 == 0 && Rand_ZeroOne() < 0.3f)) {
                    phi_v1_2 = 1;
                }
            }

            if (this->unk_314[2] != 1) {
                if ((phi_v1_2 == -1) || (phi_v1_2 != -1 && Rand_ZeroOne() < 0.3f)) {
                    phi_v1_2 = 2;
                }
            }

            if (this->unk_314[phi_v1_2] != 1) {
                this->unk_320[phi_v1_2] = 1;
                if (this->unk_314[phi_v1_2] == 2) {
                    func_8019F1C0(&this->unk_32C[phi_v1_2], 0x2891);
                } else {
                    func_8019F1C0(&this->unk_32C[phi_v1_2], 0x297E);
                }

                this->unk_314[phi_v1_2]--;
                if (this->unk_314[phi_v1_2] <= 0) {
                    this->unk_314[phi_v1_2] = 1;
                }
            }
        }

        func_80B781DC(this, arg2, arg3, globalCtx);
    }


    Math3D_Lerp(&arg2->unk_540, &this->unk_360[arg2->unk_550], 1.0f - ((f32) arg2->unk_55C / arg2->unk_560), &sp30);
    arg2->unk_570 = sp30;
    arg2->unk_588 = this->dyna.actor.shape.rot.y;

    if ((arg2->unk_550 == 0xA) || ((arg2->unk_550 == 8))) {
        phi_v1_5 = arg2->unk_588;
    } else if (Math3D_Distance(&arg2->actor.prevPos, &arg2->actor.world.pos) < 10.0f) {
        phi_v1_5 = arg2->unk_588;
    } else {
        phi_v1_5 = Math_Vec3f_Yaw(&arg2->actor.prevPos, &arg2->actor.world.pos);
    }

    if (1) { }

    phi_v1_5 -= arg2->actor.shape.rot.y;
    if (phi_v1_5 > 0x190) {
        arg2->actor.shape.rot.y += 0x190;
    } else if (phi_v1_5 < -0x190) {
        arg2->actor.shape.rot.y += -0x190;
    } else {
        arg2->actor.shape.rot.y += phi_v1_5;
    }

    return 0;
}

s32 func_80B78A54(ObjUm* this, GlobalContext* globalCtx, s32 arg2, EnHorse* arg3, EnHorse* arg4) {
    if (this->unk_424[arg2].base.acFlags & 2) {
        if (arg3->unk_550 == 3) {
            s16 sp36 = Math_Vec3f_Yaw(&this->dyna.actor.world.pos, &arg3->actor.world.pos) - this->dyna.actor.shape.rot.y;

            this->unk_424[arg2].base.acFlags &= ~0x02;
            func_8019F1C0(&arg3->actor.projectedPos, 0x393B);
            arg3->unk_54C = 0xF;

            if (Math_SinS(sp36) > 0.0f) {
                arg3->unk_550 = arg4->unk_550 != 0xA ? 0xA : 8;
                arg3->unk_568 = -1.0f;
            } else {
                arg3->unk_550 = arg4->unk_550 != 8 ? 8 : 0xA;
                arg3->unk_568 = 1.0f;
            }

            arg3->unk_540 = arg3->actor.world.pos;
            arg3->unk_55C = 0x28;
            arg3->unk_560 = 0x28;
            arg3->unk_564 = 1;
            if (arg3->rider != NULL) {
                arg3->rider->actor.colorFilterTimer = 20;
                func_800BCB70(arg3->rider, 0x4000, 0xFF, 0, (s16) 0x28);
            }
        } else {
            if (arg3->rider != 0) {
                arg3->rider->actor.colorFilterTimer = 20;
                func_800BCB70(arg3->rider, 0x4000, 0xFF, 0, (s16) 0x28);
            }
            func_8019F1C0(&arg3->actor.projectedPos, 0x393BU);
        }
    }

    return 0;
}

s32 func_80B78C18(ObjUm* this, GlobalContext* globalCtx) {
    EnHorse* temp_s1 = this->unk_358;
    EnHorse* temp_s2 = this->unk_35C;

    if (!(this->unk_2F4 & 0x200)) {
        func_80B783E0(this, globalCtx, 0, temp_s1);
    } else {
        func_80B78764(this, globalCtx, temp_s1, temp_s2);
    }

    if (!(this->unk_2F4 & 0x400)) {
        func_80B783E0(this, globalCtx, 1, temp_s2);
    } else {
        func_80B78764(this, globalCtx, temp_s2, temp_s1);
    }

    func_80B78A54(this, globalCtx, 0, temp_s1, temp_s2);
    func_80B78A54(this, globalCtx, 1, temp_s2, temp_s1);
    return 0;
}

s32 func_80B78D08(ObjUm* this, GlobalContext* globalCtx) {
    s32 pad[3];

    this->unk_424[0].dim.pos.x = this->unk_358->actor.world.pos.x;
    this->unk_424[0].dim.pos.y = this->unk_358->actor.world.pos.y + 70.0f;
    this->unk_424[0].dim.pos.z = this->unk_358->actor.world.pos.z;

    this->unk_424[1].dim.pos.x = this->unk_35C->actor.world.pos.x;
    this->unk_424[1].dim.pos.y = this->unk_35C->actor.world.pos.y + 70.0f;
    this->unk_424[1].dim.pos.z = this->unk_35C->actor.world.pos.z;

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->unk_424[0].base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->unk_424[1].base);
    return 0;
}

s32 func_80B78DF0(ObjUm* this, GlobalContext* globalCtx) {
    func_80B78C18(this, globalCtx);
    func_80B78D08(this, globalCtx);
    return 0;
}

// ObjUm_SetupAction
void ObjUm_SetupAction(ObjUm* this, ObjUmActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void func_80B78E38(ObjUm* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (this->unk_2F4 & 0x20) {
        player->actor.world.pos = this->unk_308;
        player->actor.prevPos = this->unk_308;
    }
}

void func_80B78E88(ObjUm* this, GlobalContext* globalCtx, s16 arg2) {
    Player* player = PLAYER;

    player->actor.shape.rot.y = player->actor.world.rot.y = player->currentYaw = this->dyna.actor.shape.rot.y + arg2;
}

void func_80B78EBC(ObjUm* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    player->actor.focus.rot.x = 0;
    player->actor.focus.rot.z = 0;
    player->actor.focus.rot.y = player->actor.shape.rot.y;

    player->unk_AAC.x = 0;
    player->unk_AAC.y = 0;
    player->unk_AAC.z = 0;

    player->unk_AB2.x = 0;
    player->unk_AB2.y = 0;
    player->unk_AB2.z = 0;

    player->currentYaw = player->actor.focus.rot.y;
}

void func_80B78EFC(ObjUm* this, GlobalContext* globalCtx, s16 arg2) {
    Player* player = PLAYER;

    player->actor.focus.rot.y += arg2;
}

void ObjUm_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjUm* this = THIS;
    s32 sp54 = true;
    s32 i;

    BcCheck3_BgActorInit(&this->dyna, 0);
    this->unk_350 = 0;

    this->unk_2C4 = this->dyna.actor.world.pos;
    this->unk_2DC = this->dyna.actor.world.pos;
    this->unk_308 = this->dyna.actor.world.pos;

    for (i = 0; i < 3; i++) {
        this->unk_314[i] = 5;
        this->unk_320[i] = 0;
        this->unk_32C[i] = D_801D15B0;
    }

    this->unk_2B8 = NULL;
    this->unk_354 = 0;
    this->unk_420 = 0;
    this->unk_4BC = this->dyna.actor.world.pos;

    this->unk_4CC = 0;
    this->unk_4D4 = 0;
    this->unk_2F4 = 0;
    this->dyna.actor.gravity = -3.5f;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    ActorShape_Init(&this->dyna.actor.shape, 0.0f, NULL, 50.0f);
    SkelAnime_InitSV(globalCtx, &this->unk_160, &D_06011DF8, NULL, this->unk_1A4, this->unk_228, 0x16);
    SkelAnime_ChangeAnimDefaultRepeat(&this->unk_160, &D_06012CC0);

    this->unk_2AC = 0;
    func_80B7B154(this, globalCtx);

    this->unk_2AE = (thisx->params & 0xFF00) >> 8;
    this->unk_2B0 = (thisx->params & 0xFF);

    if (!(gSaveContext.weekEventReg[0x16] & 1)) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }

    if (this->unk_2AE == 0) {
        ObjUm_SetupAction(this, func_80B7AEFC);
    } else if (this->unk_2AE == 1) {
        this->unk_2BC = this->unk_2B0;
        if (gSaveContext.weekEventReg[0x1F] & 0x80) {
            sp54 = false;
            this->unk_2F4 |= 0x100;
            ObjUm_SetupAction(this, func_80B7A144);
            func_800FE484();
        } else {
            if ((gSaveContext.weekEventReg[0x22] & 0x80)  || gSaveContext.time >= CLOCK_TIME(19, 0) || (s32) gSaveContext.time <= CLOCK_TIME(6, 0) || (gSaveContext.weekEventReg[0x34] & 1) || (gSaveContext.weekEventReg[0x34] & 2)) {
                Actor_MarkForDeath(&this->dyna.actor);
                return;
            }
            this->dyna.actor.targetMode = 6;
            this->unk_2B4 = 0;
            ObjUm_SetupAction(this, func_80B79A50);
        }
    } else if (this->unk_2AE == 2) {
        if (!(gSaveContext.weekEventReg[0x1F] & 0x80) || (gSaveContext.weekEventReg[0x34] & 1)) {
            Actor_MarkForDeath(&this->dyna.actor);
            return;
        }

        if (!(gSaveContext.weekEventReg[0x34] & 2)) {
            this->unk_2BC = this->unk_2B0;
            sp54 = false;
            func_800FE484();
            ObjUm_SetupAction(this, func_80B7A400);
            this->unk_354 = 0;
            func_80B78E88(this, globalCtx, 0);
        }
    } else if (this->unk_2AE == 3) {
        if (!(gSaveContext.weekEventReg[0x1F] & 0x80)) {
            Actor_MarkForDeath(&this->dyna.actor);
            return;
        }

        this->unk_2BC = this->unk_2B0;
        sp54 = false;
        func_800FE484();
        ObjUm_SetupAction(this, func_80B7AC94);
        this->unk_354 = 0;
        func_80B78E88(this, globalCtx, 0);
    } else if (this->unk_2AE == 4) {
        if (!(gSaveContext.weekEventReg[0x34] & 1) || (gSaveContext.weekEventReg[0x3B] & 2)) {
            Actor_MarkForDeath(&this->dyna.actor);
            return;
        }

        this->unk_2BC = this->unk_2B0;
        sp54 = false;
        func_800FE484();
        ObjUm_SetupAction(this, func_80B7AE58);
        this->unk_354 = 0;
        func_80B78E88(this, globalCtx, 0);
        func_801A3098(0x19);
    } else {
        this->unk_2AE = 0;
        ObjUm_SetupAction(this, func_80B7AEFC);
    }

    this->unk_2F8 = this->unk_2FE = D_801D15BC;;

    if (sp54) {
        BcCheck3_BgActorInit(&this->dyna, 0);
        BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_06007E20);
    } else {
        BcCheck3_BgActorInit(&this->dyna, 3);
        BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_06007F50);
    }

    if (this->dyna.bgId == 0x32) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }

    func_800C636C(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);

    this->unk_2B8 = Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_HORSE, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, 0, this->dyna.actor.shape.rot.y, 0, 0x8012);

    if (this->unk_2B8 == NULL) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }

    Collider_InitAndSetCylinder(globalCtx, &this->unk_424[0], &this->dyna.actor, &sCylinderInit);
    Collider_InitAndSetCylinder(globalCtx, &this->unk_424[1], &this->dyna.actor, &sCylinderInit);

    return;
}

void ObjUm_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjUm* this = THIS;
    s32 i;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);

    for (i = 0; i < ARRAY_COUNT(this->unk_32C); i++) {
        func_801A72CC(&this->unk_32C[i]);
    }

    Collider_DestroyCylinder(globalCtx, &this->unk_424[0]);
    Collider_DestroyCylinder(globalCtx, &this->unk_424[1]);
}

void func_80B79524(ObjUm* this) {
    Actor_MarkForDeath(&this->dyna.actor);
    if (this->unk_2B8 != NULL) {
        Actor_MarkForDeath(&this->unk_2B8->actor);
    }
}

void func_80B79560(GlobalContext* globalCtx, ObjUm* this, s32 arg2, u16 arg3) {
    if (arg3 == 0x33BF) {
        ObjUm_SetupAction(this, func_80B7AC94);
    }
}

s32 func_80B795A0(GlobalContext* globalCtx, ObjUm* this, s32 arg2) {
    s32 pad[2];
    s32 phi_v1 = true;
    u16 textId = this->dyna.actor.textId;
    Player* player;

    switch (textId) {
        case 0x33B4:
        case 0x33CF:
            gSaveContext.weekEventReg[0x1F] |= 0x40;
            if (globalCtx->msgCtx.choiceIndex == 0) {
                player = PLAYER;
                func_8019F208();
                gSaveContext.weekEventReg[0x1F] |= 0x80;
                globalCtx->nextEntranceIndex = 0x64B0;
                if (player->stateFlags1 & 0x800000) {
                    D_801BDAA0 = 1;
                }
                globalCtx->unk_1887F = 0x40;
                gSaveContext.nextTransition = 3;
                globalCtx->sceneLoadFlag = 0x14;
                phi_v1 = true;
            } else {
                func_800E8EA0(globalCtx, &this->dyna.actor, 0x33B5U);
                func_8019F230();
                func_80151BB4(globalCtx, 6U);
                phi_v1 = false;
            }
            break;
        case 0x33BB:
            func_800E8EA0(globalCtx, &this->dyna.actor, 0x33BCU);
            phi_v1 = false;
            break;
        case 0x33BC:
            func_800E8EA0(globalCtx, &this->dyna.actor, 0x33BDU);
            phi_v1 = false;
            break;
        case 0x33BD:
            if (globalCtx->msgCtx.choiceIndex == 0) {
                func_800E8EA0(globalCtx, &this->dyna.actor, 0x33BEU);
                func_8019F230();
            } else {
                func_800E8EA0(globalCtx, &this->dyna.actor, 0x33BFU);
                func_8019F208();
            }
            phi_v1 = false;
            break;
        case 0x33BE:
            func_800E8EA0(globalCtx, &this->dyna.actor, 0x33BCU);
            phi_v1 = false;
            break;
    }
    return phi_v1;
}

s32 func_80B79734(GlobalContext* globalCtx, ObjUm* this, s32 arg2) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    s32 sp20 = false;

    switch (func_80152498(msgCtx)) {
        case 2:
            func_80B79560(globalCtx, this, arg2, this->dyna.actor.textId);
            return true;

        case 4:
        case 5:
            if (func_80147624(globalCtx) && func_80B795A0(globalCtx, this, arg2)) {
                msgCtx->unk11F22 = 0x43;
                sp20 = true;
            }
            break;
    }
    return sp20;
}

u16 func_80B797EC(GlobalContext* globalCtx, ObjUm* this, s32 arg2) {
    u16 phi_v1;

    if (gSaveContext.playerForm == PLAYER_FORM_HUMAN) {
        if (gSaveContext.weekEventReg[0x1F] & 0x40) {
            phi_v1 = 0x33CF;
        } else {
            phi_v1 = 0x33B4;
        }
    } else {
        phi_v1 = 0x33B7;
    }

    if (phi_v1 == 0) {
        phi_v1 = 1;
    }
    return phi_v1;
}

s32 func_80B7984C(GlobalContext* globalCtx, ObjUm* this, s32 arg2, s32* arg3) {
    s16 temp_v0_2;
    s16 phi_v1;

    if (*arg3 == 4) {
        return 0;
    }
    if (*arg3 == 2) {
        func_801518B0(globalCtx, this->dyna.actor.textId, &this->dyna.actor);
        *arg3 = 1;
        return 0;
    }
    if (*arg3 == 3) {
        func_80151938(globalCtx, this->dyna.actor.textId);
        *arg3 = 1;
        return 0;
    }

    if (func_800B84D0(&this->dyna.actor, globalCtx) != 0) {
        *arg3 = 1;
        return 1;
    }

    if (*arg3 == 1) {
        if (func_80B79734(globalCtx, this, arg2) != 0) {
            *arg3 = 0;
        }
        return 0;
    }

    phi_v1 = this->dyna.actor.yawTowardsPlayer - this->dyna.actor.shape.rot.y;
    temp_v0_2 = ABS_ALT((s16)phi_v1);

    if (temp_v0_2 >= 0x4E20) {
        return 0;
    }

    if ((this->dyna.actor.xyzDistToPlayerSq > 10000.0f) && (this->dyna.actor.isTargeted == 0)) {
        return 0;
    }

    if (this->dyna.actor.xyzDistToPlayerSq <= 2500.0f) {
        if (func_800B8614(&this->dyna.actor, globalCtx, 50.0f) != 0) {
            this->dyna.actor.textId = func_80B797EC(globalCtx, this, arg2);
        }
    } else if (func_800B863C(&this->dyna.actor, globalCtx) != 0) {
        this->dyna.actor.textId = func_80B797EC(globalCtx, this, arg2);
    }

    return 0;
}

s32 func_80B79A24(s32 arg0) {
    if ((arg0 == 1) || (arg0 == 2) || (arg0 == 3)) {
        return 1;
    }
    return 0;
}

void func_80B79A50(ObjUm* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    this->dyna.actor.flags |= 1;
    SkelAnime_FrameUpdateMatrix(&this->unk_160);
    func_80B7B18C(this, globalCtx, 2);
    this->unk_2F4 |= 8;
    if (gSaveContext.time > CLOCK_TIME(18, 0) && gSaveContext.time <= CLOCK_TIME(19, 0)) {
        if (!(player->stateFlags1 & 0x800000)) {
            func_80B7984C(globalCtx, this, 0, &this->unk_2B4);
        }
    } else if (!func_80B79A24(this->unk_2B4) && gSaveContext.time > CLOCK_TIME(19, 0)) {
        gSaveContext.weekEventReg[0x22] |= 0x80;
        ObjUm_SetupAction(this, func_80B79F10);
    }

    switch (globalCtx->msgCtx.unk11F04) {
        default:
            this->unk_4CC = 0;
            this->unk_4D4 = 0;
            break;

        case 0x33B7:
        case 0x33B4:
            this->unk_4CC = 0;
            this->unk_4D4 = 1;
            break;

        case 0x33B5:
            this->unk_4CC = 3;
            this->unk_4D4 = 1;
            break;
    }
}

s32 func_80B79BA0(ObjUm* this, GlobalContext* globalCtx) {
    Path* sp6C = &globalCtx->setupPathList[this->unk_2BC];
    s32 sp68;
    Vec3s* sp64;
    f32 phi_f12;
    f32 phi_f14;
    Vec3f sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s32 aux;
    s32 sp3C;
    s16 phi_a2;

    sp68 = sp6C->count;
    sp64 = Lib_SegmentedToVirtual(sp6C->points);
    sp3C = 0;

    if (sp68 == 0) {
        return 0;
    }

    Math_Vec3s_ToVec3f(&sp50, &sp64[this->unk_2BE]);

    if (this->unk_2BE == 0) {
        phi_f12 = sp64[1].x - sp64[0].x;
        phi_f14 = sp64[1].z - sp64[0].z;
    } else if ((this->unk_2BE + 1) == sp6C->count) {
        phi_f12 = sp64[sp6C->count-1].x - sp64[sp6C->count-2].x;
        phi_f14 = sp64[sp6C->count-1].z - sp64[sp6C->count-2].z;
    } else {
        phi_f12 = sp64[this->unk_2BE+1].x - sp64[this->unk_2BE-1].x;
        phi_f14 = sp64[this->unk_2BE+1].z - sp64[this->unk_2BE-1].z;
    }

    aux = Math_Atan2S(phi_f12, phi_f14);

    func_8017B7F8(&sp50, (s16)aux, &sp4C, &sp48, &sp44);
    if (((this->dyna.actor.world.pos.x * sp4C) + (sp48 * this->dyna.actor.world.pos.z) + sp44) > 0.0f) {
        this->unk_2BE++;

        if (this->unk_2BE >= (sp68 - 7)) {
            sp3C = 3;
        }
        if (this->unk_2BE >= (sp68 - 3)) {
            sp3C = 1;
        }
        if (this->unk_2BE >= (sp68 - 2)) {
            sp3C = 4;
        }
        if (this->unk_2BE >= sp68) {
            this->unk_2BE = 0;
            sp3C = 2;
        }

        Math_Vec3s_ToVec3f(&sp50, &sp64[this->unk_2BE]);
    }

    if (this->unk_2B8 != 0) {
        this->dyna.actor.world.rot.y = Math_Vec3f_Yaw(&this->dyna.actor.world.pos, &sp50);
        func_800F415C(this->unk_2B8, &sp50, 0x190);

        if (1) {}

        phi_a2 = this->unk_2B8->actor.shape.rot.y - this->dyna.actor.shape.rot.y;
        if (fabsf(phi_a2) < 2730.0f) {
            if (fabsf(phi_a2) < 100.0f) {
                this->dyna.actor.shape.rot.y = this->unk_2B8->actor.shape.rot.y;
            } else if (phi_a2 > 0) {
                this->dyna.actor.shape.rot.y = this->dyna.actor.shape.rot.y + 0x64;
                phi_a2 = 0x64;
            } else if (phi_a2 < 0) {
                this->dyna.actor.shape.rot.y = this->dyna.actor.shape.rot.y - 0x64;
                phi_a2 = -0x64;
            }
        } else if (phi_a2 > 0) {
            this->dyna.actor.shape.rot.y = this->dyna.actor.shape.rot.y + 0x190;
            phi_a2 = 0x190;
        } else {
            if (phi_a2 < 0) {
                this->dyna.actor.shape.rot.y = this->dyna.actor.shape.rot.y - 0x190;
                phi_a2 = -0x190;
            }
        }

        if (this->unk_2F4 & 0x14) {
            func_80B78EFC(this, globalCtx, phi_a2);
        }
    }

    if (this->unk_304 == 0) {
        this->dyna.actor.speedXZ = 4.0f;
    } else if (this->unk_304 == 1) {
        this->dyna.actor.speedXZ = 8.0f;
    }

    return sp3C;
}

void func_80B79F10(ObjUm* this, GlobalContext* globalCtx) {
    s32 temp_v0;

    this->unk_2AC += 0x3E8;
    this->unk_2F4 &= ~0x08;
    func_80B7B18C(this, globalCtx, 0);

    temp_v0 = func_80B79BA0(this, globalCtx);
    if ((temp_v0 == 1) || (temp_v0 == 2)) {
        if (gSaveContext.weekEventReg[0x1F] & 0x80) {
            ActorCutscene_Stop(this->dyna.actor.cutscene);
            globalCtx->nextEntranceIndex = 0x3E50;
            globalCtx->unk_1887F = 0x40;
            gSaveContext.nextTransition = 3;
            globalCtx->sceneLoadFlag = 0x14;
        } else {
            func_80B79524(this);
        }
    } else {
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->dyna.actor);
    }
}

void func_80B79FFC(ObjUm* this, GlobalContext* globalCtx) {
    func_80B7B18C(this, globalCtx, 2);

    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        this->unk_4C8 = gSaveContext.time;
        ObjUm_SetupAction(this, func_80B7A0E0);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void func_80B7A070(ObjUm* this, GlobalContext* globalCtx) {
    func_80B79F10(this, globalCtx);
    func_80B78E88(this, globalCtx, 0);

    switch (globalCtx->msgCtx.unk11F04) {
        case 0x33B6:
            this->unk_4CC = 1;
            this->unk_4D4 = 1;
            break;

        default:
            this->unk_4CC = 0;
            this->unk_4D4 = 0;
            break;
    }
}

void func_80B7A0E0(ObjUm* this, GlobalContext* globalCtx) {
    func_80B7B18C(this, globalCtx, 2);
    if (gSaveContext.time != this->unk_4C8) {
        func_80B7B18C(this, globalCtx, 0);
        ObjUm_SetupAction(this, func_80B7A070);
    }
}

void func_80B7A144(ObjUm* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    func_80B78E38(this, globalCtx);
    this->unk_2F4 |= 0x100;
    this->unk_2F4 |= 0x004;
    player->stateFlags1 |= 0x20;
    func_80B7B18C(this, globalCtx, 2);
    ObjUm_SetupAction(this, func_80B79FFC);
}

void func_80B7A1B4(ObjUm* this, GlobalContext* globalCtx) {
    func_80B78E38(this, globalCtx);
    this->unk_2F4 |= 4;

    switch (globalCtx->msgCtx.unk11F04) {
        case 0x33B8:
            this->unk_4CC = 0;
            this->unk_4D4 = 3;
            break;

        case 0x33B9:
            this->unk_4CC = 2;
            this->unk_4D4 = 0;
            break;

        default:
            this->unk_2F4 &= ~0x800;
            this->unk_4CC = 0;
            this->unk_4D4 = 0;
            break;
    }
}

void func_80B7A240(ObjUm* this, GlobalContext* globalCtx) {
    func_80B7B18C(this, globalCtx, 2);
    if (gSaveContext.time != this->unk_4C8) {
        ObjUm_SetupAction(this, func_80B7A2AC);
    }

    this->unk_4C8 = gSaveContext.time;
    func_80B7A1B4(this, globalCtx);
}

void func_80B7A2AC(ObjUm* this, GlobalContext* globalCtx) {
    s32 temp_v0;

    this->unk_2AC += 0x3E8;
    func_80B7B18C(this, globalCtx, 0);

    temp_v0 = func_80B79BA0(this, globalCtx);
    if (temp_v0 == 1 || temp_v0 == 2) {
        globalCtx->nextEntranceIndex = 0xCE40;
        globalCtx->unk_1887F = 0x40;
        gSaveContext.nextTransition = 3;
        globalCtx->sceneLoadFlag = 0x14;
    } else {
        if (gSaveContext.time == this->unk_4C8) {
            ObjUm_SetupAction(this, func_80B7A240);
        }

        this->unk_4C8 = gSaveContext.time;
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->dyna.actor);
        func_80B7A1B4(this, globalCtx);
    }
}

void func_80B7A394(ObjUm* this, GlobalContext* globalCtx) {
    ObjUm* temp_a0;

    func_80B78E38(this, globalCtx);
    this->unk_2F4 |= 4;
    if (gSaveContext.time != this->unk_4C8) {
        func_80B7B18C(this, globalCtx, 0);
        ObjUm_SetupAction(this, func_80B7A2AC);
    }
}

void func_80B7A400(ObjUm* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    func_80B78E38(this, globalCtx);
    this->unk_2F4 |= 4;
    player->stateFlags1 |= 0x20;
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        this->unk_4C8 = gSaveContext.time;
        ObjUm_SetupAction(this, func_80B7A394);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void func_80B7A494(ObjUm* this, GlobalContext* globalCtx) {
    s32 temp_v0;

    func_80B78E38(this, globalCtx);
    func_80B78E88(this, globalCtx, 0x7FFF);
    this->unk_2AC += 0x7D0;
    this->unk_2F4 |= 0x10;
    func_80B7B18C(this, globalCtx, 1);

    temp_v0 = func_80B79BA0(this, globalCtx);
    if (temp_v0 == 1 || temp_v0 == 2) {
        gSaveContext.seqIndex = 0xFF;
        gSaveContext.weekEventReg[0x1F] &= (u8)~0x80;
        gSaveContext.nightSeqIndex = 0xFF;

        if (!(gSaveContext.weekEventReg[0x34] & 1) && !(gSaveContext.weekEventReg[0x34] & 2)) {
            if (this->unk_4E0 == 0) {
                globalCtx->nextEntranceIndex = 0x3E60;
                globalCtx->unk_1887F = 0x40;
                gSaveContext.nextTransition = 3;
                globalCtx->sceneLoadFlag = 0x14;
                gSaveContext.weekEventReg[0x34] |= 0x01;
                gSaveContext.weekEventReg[0x34] &= (u8)~0x2;
            } else {
                globalCtx->nextEntranceIndex = 0x6480;
                globalCtx->unk_1887F = 0x40;
                gSaveContext.nextTransition = 3;
                globalCtx->sceneLoadFlag = 0x14;
                gSaveContext.weekEventReg[0x34] |= 0x02;
                gSaveContext.weekEventReg[0x34] &= (u8)~0x1;
            }
        }
    } else {
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->dyna.actor);
        func_80B78DF0(this, globalCtx);
    }
}

void func_80B7A614(ObjUm* this, GlobalContext* globalCtx) {
    s32 pad;

    func_80B78E38(this, globalCtx);
    func_80B78E88(this, globalCtx, 0x7FFF);
    this->unk_2AC += 0x7D0;
    this->unk_2F4 |= 0x10;
    this->unk_2F4 |= 0x80;
    func_80B7B18C(this, globalCtx, 1);

    if (func_80B79BA0(this, globalCtx) == 3 && this->unk_4DC == 0) {
        this->unk_4DC = 1;
    } else if (this->unk_4DC > 0) {
        if (this->unk_4DC == 1) {
            s32 i;

            this->unk_4E0 = 1;

            for (i = 0; i != 3; i++) {
                if (this->unk_314[i] != 1) {
                    this->unk_4E0 = 0;
                    break;
                }
            }

            this->unk_2F4 |= 0x2000;

            dummy_label: ;
        }

        this->unk_4DC++;
    }

    if (this->unk_2F4 & 0x2000) {
        s32 sp20 = ActorCutscene_GetAdditionalCutscene(this->dyna.actor.cutscene);

        if (this->unk_4E0 != 0) {
            sp20 = ActorCutscene_GetAdditionalCutscene(sp20);
        }
        if (ActorCutscene_GetCanPlayNext(sp20) != 0) {
            ActorCutscene_StartAndSetUnkLinkFields(sp20, &this->dyna.actor);
            ObjUm_SetupAction(this, func_80B7A494);
            this->unk_2F4 &= ~0x80;
        } else {
            ActorCutscene_SetIntentToPlay(sp20);
        }
    }

    Actor_SetVelocityAndMoveYRotationAndGravity(&this->dyna.actor);
    func_80B78DF0(this, globalCtx);
}

void func_80B7A7AC(ObjUm* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    this->unk_4DC = 0;
    this->unk_4E0 = 0;
    player->stateFlags1 &= ~0x20;
    func_80B78E38(this, globalCtx);
    func_80B78E88(this, globalCtx, 0x7FFF);
    func_80B78EBC(this, globalCtx);
    this->unk_2F4 |= 0x10;
    func_80B78DF0(this, globalCtx);
    this->unk_2F4 |= 4;
    func_80B7B18C(this, globalCtx, 1);
    ObjUm_SetupAction(this, func_80B7A614);
}

void func_80B7A860(ObjUm* this, GlobalContext* globalCtx) {
    func_80B78E38(this, globalCtx);
    func_80B78E88(this, globalCtx, 0);
    this->unk_2F4 |= 4;

    if (globalCtx->csCtx.frames == 0x1C1) {
        func_80B77FA4(this, globalCtx);
    } else if (globalCtx->csCtx.frames >= 0x1C2) {
        func_80B78DF0(this, globalCtx);
    }

    if (globalCtx->csCtx.state == 0) {
        ActorCutscene_Stop((s16) this->dyna.actor.cutscene);
        ObjUm_SetupAction(this, func_80B7A7AC);
    }

    switch (globalCtx->msgCtx.unk11F04) {
        case 0x33BA:
            this->unk_4CC = 2;
            this->unk_4D4 = 3;
            break;

        case 0x33BB:
            if (IS_ZERO(this->unk_160.animCurrentFrame) && !(this->unk_2F4 & 0x1000)) {
                this->unk_2F4 = this->unk_2F4 | 0x1000;
                this->unk_4CC = 4;
                this->unk_4D4 = 0;
            } else if (IS_ZERO(this->unk_160.transCurrentFrame)) {
                this->unk_4CC = 2;
                this->unk_4D4 = 2;
            } else {
                this->unk_4CC = 5;
                this->unk_4D4 = 0;
            }

            this->unk_2F4 |= 0x800;
            break;

        case 0x33BC:
            if (IS_ZERO(this->unk_160.animCurrentFrame) && !(this->unk_2F4 & 0x1000)) {
                this->unk_2F4 |= 0x1000;
                this->unk_4CC = 4;
                this->unk_4D4 = 0;
            } else if (IS_ZERO(this->unk_160.transCurrentFrame)) {
                this->unk_4CC = 2;
                this->unk_4D4 = 2;
            } else {
                this->unk_4CC = 5;
                this->unk_4D4 = 0;
            }
            this->unk_2F4 |= 0x800;
            break;

        case 0x33BD:
            if (IS_ZERO(this->unk_160.animCurrentFrame) && !(this->unk_2F4 & 0x1000)) {
                this->unk_2F4 |= 0x1000;
                this->unk_4CC = 4;
                this->unk_4D4 = 0;
            } else if (IS_ZERO(this->unk_160.transCurrentFrame)) {
                this->unk_4CC = 2;
            } else {
                this->unk_4CC = 5;
            }
            this->unk_4D4 = 0;
            this->unk_4D8 = 0;
            this->unk_2F4 |= 0x800;
            break;

        case 0x33BE:
            this->unk_2F4 |= 0x800;
            this->unk_4CC = 2;
            this->unk_4D4 = 3;
            break;

        case 0x33BF:
            this->unk_4D8++;
            if (IS_ZERO(this->unk_160.transCurrentFrame) && this->unk_4D8 >= 6) {
                this->unk_4CC = 0;
                this->unk_4D4 = 0;
            } else {
                this->unk_4CC = 2;
                this->unk_4D4 = 2;
            }
            this->unk_2F4 &= ~0x800;
            break;

        default:
            this->unk_4CC = 0;
            this->unk_4D4 = 0;
            break;
    }
}

void func_80B7AB78(ObjUm* this, GlobalContext* globalCtx) {
    func_80B7B18C(this, globalCtx, 2);
    if (gSaveContext.time != this->unk_4C8) {
        ObjUm_SetupAction(this, func_80B7ABE4);
    }

    this->unk_4C8 = gSaveContext.time;
    func_80B7A860(this, globalCtx);
}

void func_80B7ABE4(ObjUm* this, GlobalContext* globalCtx) {
    this->unk_2AC += 0x3E8;
    func_80B7B18C(this, globalCtx, 0);
    if (func_80B79BA0(this, globalCtx) == 2) {
        func_80B79524(this);
        return;
    }

    if (gSaveContext.time == this->unk_4C8) {
        ObjUm_SetupAction(this, func_80B7AB78);
    }
    this->unk_4C8 = gSaveContext.time;
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->dyna.actor);
    func_80B7A860(this, globalCtx);
}

void func_80B7AC94(ObjUm* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    player->stateFlags1 |= 0x20;
    func_80B78E38(this, globalCtx);
    func_80B78E88(this, globalCtx, 0);
    this->unk_2F4 |= 4;

    if (ActorCutscene_GetCanPlayNext((s16) this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        this->unk_4C8 = gSaveContext.time;
        ObjUm_SetupAction(this, func_80B7ABE4);
    } else {
        ActorCutscene_SetIntentToPlay((s16) this->dyna.actor.cutscene);
    }
}

void func_80B7AD34(ObjUm* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    player->stateFlags1 |= 0x20;
    func_80B78E38(this, globalCtx);
    func_80B78E88(this, globalCtx, 0);
    this->unk_2F4 |= 4;
    this->unk_2AC += 0x3E8;
    func_80B7B18C(this, globalCtx, 0);

    if ((func_80B79BA0(this, globalCtx) == 4) && !(gSaveContext.weekEventReg[0x3B] & 2)) {
        ActorCutscene_Stop((s16) this->dyna.actor.cutscene);
        func_801A3F54(0);
        gSaveContext.weekEventReg[0x3B] |= 2;
        gSaveContext.unk_3F4A = 0xFFF3;
        globalCtx->nextEntranceIndex = 0x5400;
        globalCtx->unk_1887F = 0x40;
        gSaveContext.nextTransition = 3;
        globalCtx->sceneLoadFlag = 0x14;
        gSaveContext.time += 0xAAC;
    }
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->dyna.actor);
}

void func_80B7AE58(ObjUm* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    player->stateFlags1 |= 0x20;
    func_80B78E38(this, globalCtx);
    func_80B78E88(this, globalCtx, 0);
    this->unk_2F4 |= 4;
    func_80B7B18C(this, globalCtx, 2);

    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        ObjUm_SetupAction(this, func_80B7AD34);
    } else {
        ActorCutscene_SetIntentToPlay((s16) this->dyna.actor.cutscene);
    }
}

void func_80B7AEFC(ObjUm* this, GlobalContext* globalCtx) {
    func_80B7B18C(this, globalCtx, 2);
    SkelAnime_FrameUpdateMatrix(&this->unk_160);
}

void func_80B7AF30(ObjUm* this, GlobalContext* globalCtx) {
    if (!(this->unk_2F4 & 1)) {
        this->dyna.actor.shape.rot.x = 0;
        this->dyna.actor.shape.rot.z = 0;
    } else {
        CollisionPoly* sp44;
        s32 pad;
        s32 pad2;
        Vec3f sp30;

        this->unk_2F4 &= ~1;

        if (1) { } 

        this->unk_2D0 = this->unk_2C4;
        this->unk_2E8 = this->unk_2DC;

        this->unk_2D0.y = func_800C3FA0(&globalCtx->colCtx, &sp44, &this->unk_2C4);
        if (this->unk_2D0.y == -32000.0f) {
            this->unk_2D0.y = this->dyna.actor.floorHeight;
        }

        if (1) { } 

        this->unk_2E8.y = func_800C3FA0(&globalCtx->colCtx, &sp44, &this->unk_2DC);
        if (this->unk_2E8.y == -32000.0f) {
            this->unk_2E8.y = this->dyna.actor.floorHeight;
        }

        sp30.x = (this->unk_2D0.x + this->unk_2E8.x) * 0.5f;
        sp30.y = (this->unk_2D0.y + this->unk_2E8.y) * 0.5f;
        sp30.z = (this->unk_2D0.z + this->unk_2E8.z) * 0.5f;

        this->dyna.actor.shape.rot.x = (s16) Math_Atan2S(sp30.y - this->dyna.actor.world.pos.y, sqrtf(SQ(sp30.x - this->dyna.actor.world.pos.x) + SQ(sp30.z - this->dyna.actor.world.pos.z)));
        this->dyna.actor.shape.rot.z = (s16) -Math_Atan2S(sp30.y - this->unk_2D0.y, sqrtf(SQ(sp30.x - this->unk_2D0.x) + SQ(sp30.z - this->unk_2D0.z)));
        if (this->unk_2F4 & 2) {
            this->dyna.actor.shape.rot.x += (s16) ((Rand_ZeroOne() * 100.0f) - 50.0f);
            this->dyna.actor.shape.rot.z += (s16) ((Rand_ZeroOne() * 100.0f) - 50.0f);
        }
    }
}

void func_80B7B154(ObjUm* this, GlobalContext* globalCtx) {
    SkelAnime_ChangeAnimDefaultStop(&this->unk_160, &D_06012CC0);
    this->unk_304 = 0;
}

void func_80B7B18C(ObjUm* this, GlobalContext* globalCtx, s32 arg2) {
    s32 sp3C;
    s32 temp;
    s32 sp34;
    f32 phi_f0;

    sp34 = arg2;
    phi_f0 = 0.0f;

    if (D_80B7C25C[arg2].unk_04 != 0) {
        this->unk_2F4 |= 2;
    } else {
        this->unk_2F4 &= ~2;
    }

    if (arg2 == 0) {
        phi_f0 = this->dyna.actor.speedXZ * 0.25f;
    } else if (arg2 == 1) {
        phi_f0 = this->dyna.actor.speedXZ * 0.2f;
    } else if (arg2 == 2) {
        phi_f0 = 1.0f;
    }
    this->unk_160.animPlaybackSpeed = phi_f0;

    if (this->unk_2F4 & 0x800) {
        this->unk_160.animPlaybackSpeed = 1.0f;
        arg2 = -1;
    }

    sp3C = arg2 != this->unk_304;
    if ((SkelAnime_FrameUpdateMatrix(&this->unk_160) != 0) || (sp3C)) {
        this->unk_304 = arg2;
        if (arg2 != -1) {
            if (this->unk_2B8 != NULL) {
                this->unk_2B8->unk_538 = arg2;
            }

            if (sp3C) {
                SkelAnime_ChangeAnimTransitionStop(&this->unk_160, D_80B7C25C[arg2].unk_00, -3.0f);
            } else {
                SkelAnime_ChangeAnimDefaultStop(&this->unk_160, D_80B7C25C[arg2].unk_00);
            }
        } else {
            EnHorse* unk_2B8 = this->unk_2B8;

            if (unk_2B8 != NULL) {
                unk_2B8->unk_538 = sp34;
            }

            if (sp3C) {
                temp = 3-arg2;
                SkelAnime_ChangeAnimTransitionStop(&this->unk_160, D_80B7C25C[temp].unk_00, -10.0f);
            } else {
                temp = 3-arg2;
                SkelAnime_ChangeAnimDefaultStop(&this->unk_160, D_80B7C25C[temp].unk_00);
            }
        }
    }

    if (this->unk_2AC / 0x199A != this->unk_420) {
        this->unk_420 = this->unk_2AC / 0x199A;
        if (!D_80B7C25C) {}
        Audio_PlayActorSound2(&this->dyna.actor, 0x2958);
    }
}

void ObjUm_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjUm* this = THIS;

    this->actionFunc(this, globalCtx);
    this->unk_350 += 1;
    Actor_UpdateBgCheckInfo(globalCtx, &this->dyna.actor, 0.0f, 0.0f, 0.0f, 0x1C);

    if (this->unk_2B8 != NULL) {
        this->unk_2B8->actor.world.pos.x = this->dyna.actor.world.pos.x;
        this->unk_2B8->actor.world.pos.y = this->dyna.actor.floorHeight;
        this->unk_2B8->actor.world.pos.z = this->dyna.actor.world.pos.z;
    }

    if (this->unk_2F4 & 0x10) {
        func_80123F2C(globalCtx, 0x63);
        this->unk_2F4 &= ~0x10;
    }
    else if (this->unk_2F4 & 4) {
        func_80123F2C(globalCtx, -3);
        this->unk_2F4 &= ~4;
    }

    if (this->unk_2F4 & 0x100) {
        this->unk_2F4 &= ~0x100;
        func_80B78E88(this, globalCtx, 0);
        func_80B78EBC(this, globalCtx);
    }

    func_80B7AF30(this, globalCtx);
    switch (this->unk_4CC) {
        case 0:
            switch (this->unk_4D0) {
                case 0:
                    if (Rand_ZeroOne() < 0.025f) {
                        this->unk_4D0 = 1;
                    }
                    break;

                case 1:
                    if (Rand_ZeroOne() < 0.6f) {
                        this->unk_4D0 = 2;
                    }
                    break;

                case 2:
                    if (Rand_ZeroOne() < 0.6f) {
                        this->unk_4D0 = 0;
                    }
                    break;

                default:
                    this->unk_4D0 = 0;
                    break;
            }
            break;

        case 1:
            this->unk_4D0 = 3;
            break;
        case 2:
            this->unk_4D0 = 4;
            break;
        case 3:
            this->unk_4D0 = 5;
            break;
        case 4:
            this->unk_4D0 = 2;
            break;
        case 5:
            this->unk_4D0 = 0;
            break;
        default:
            this->unk_4CC = 0;
            this->unk_4D0 = 0;
            break;
    }
}


#ifdef NON_EQUIVALENT
s32 func_80B7B598(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    ObjUm* this = THIS;
    Player* player = PLAYER;
    Vec3f sp5C;
    Vec3f sp50;
    Gfx* sp44;
    Gfx* sp40;
    s16 sp3E;
    Vec3f sp30;
    s16 temp_v0_3;

    sp5C = D_80B7C284;
    sp50 = D_80B7C290;

    if ((limbIndex >= 0xB) && (this->unk_2AE == 0)) {
        *dList = NULL;
        return 0;
    }
    if (limbIndex == 0xD) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80B7C110[this->unk_4D0]));
        gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80B7C128[this->unk_4D4]));

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
    if (limbIndex == 3) {
        if ((this->unk_2F4 & 2) != 0) {
            rot->x = -this->unk_2AC;
        }
        SysMatrix_MultiplyVector3fByState(&sp5C, &this->unk_2C4);
    } else if (limbIndex == 4) {
        if ((this->unk_2F4 & 2) != 0) {
            rot->x = this->unk_2AC;
        }
        SysMatrix_MultiplyVector3fByState((Vec3f* ) &sp50, &this->unk_2DC);
    } else if ((limbIndex == 0xD) && ((this->unk_2F4 & 8) != 0)) {
        if ((func_8013D5E8(this->dyna.actor.shape.rot.y, 0x4E20, this->dyna.actor.yawTowardsPlayer) != 0) && (this->dyna.actor.xzDistToPlayer < 500.0f)) {
            sp30 = player->actor.world.pos;
            sp30.y = player->bodyPartsPos[7].y + 3.0f;

            sp3E = Math_Vec3f_Yaw(&this->dyna.actor.focus.pos, &sp30) - this->dyna.actor.shape.rot.y;
            temp_v0_3 = Math_Atan2S(this->dyna.actor.focus.pos.y - sp30.y, Math3D_XZLength(sp30.x - this->dyna.actor.focus.pos.x, sp30.z - this->dyna.actor.focus.pos.z));
            this->unk_2FE.x = (s16) (rot->x + sp3E);
            this->unk_2FE.y = (s16) rot->y;
            this->unk_2FE.z = (s16) (rot->z + temp_v0_3);
            Math_SmoothStepToS(&this->unk_2F8.x, this->unk_2FE.x, 4, 0x3E8, (s16) 1);
            Math_SmoothStepToS(&this->unk_2F8.z, this->unk_2FE.z, 4, 0x3E8, (s16) 1);
            this->unk_2F8.y = (s16) rot->y;
            rot->x = this->unk_2F8.x;
            rot->z = this->unk_2F8.z;

            // return 0;
        } else {
            this->unk_2FE.x = (s16) rot->x;
            this->unk_2FE.y = (s16) rot->y;
            this->unk_2FE.z = (s16) rot->z;
            Math_SmoothStepToS(&this->unk_2F8.x, this->unk_2FE.x, 4, 0x3E8, (s16) 1);
            Math_SmoothStepToS(&this->unk_2F8.z, this->unk_2FE.z, 4, 0x3E8, (s16) 1);
            this->unk_2F8.y = (s16) rot->y;
            rot->x = this->unk_2F8.x;
            rot->z = this->unk_2F8.z;
        }
    } else if ((limbIndex == 7) && ((this->unk_2F4 & 0x80) != 0)) {
        *dList = NULL;
    }
    return 0;
}
#else
s32 func_80B7B598(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7B598.s")
#endif

void func_80B7B93C(GlobalContext* globalCtx, Vec3f* arg1) {
    Vec3f sp8C = {0.0f, -1.0f, 0.0f};
    Gfx* sp80[] = {D_06000040, D_06000910, D_060011E0};
    s32 i;
    Vec3f sp70;

    EffectSsHitMark_SpawnFixedScale(globalCtx, 0, arg1);

    for (i = 0; i < 20; i++) {
        sp70.x = (Rand_ZeroOne() * 20.0f) - 10.0f;
        sp70.y = -((Rand_ZeroOne() * 20.0f) - 10.0f);
        sp70.z = (Rand_ZeroOne() * 20.0f) - 10.0f;
        EffectSsHahen_Spawn(globalCtx, arg1, &sp70, &sp8C, 1, 0x64, 0x1FC, 0xA, sp80[(s32)(Rand_ZeroOne() * ARRAY_COUNT(sp80))]);
    }
}

Gfx* D_80B7C2B4 [] = {
    0x00000000,
    0x060052B0,
    0x06003C60,
    0x06003C60,
    0x06003C60,
    0x060067C0,
};

Gfx* D_80B7C2CC[] = {
    0x00000000,
    0x00000000,
    0x06004B60,
    0x060043E0,
    0x00000000,
    0x00000000,
};

f32 D_80B7C2E4[] = {
    0.0f,
    1070.0f,
    1070.0f,
    1070.0f,
    1070.0f,
    2100.0f,
};

Vec3f D_80B7C2FC = {2000.0f, 1070.0f, 0.0f};
Vec3f D_80B7C308 = {2500.0f, 200.0f, 0.0f};
Vec3f D_80B7C314 = {2000.0f, 0.0f, -2000.0f};


#ifdef MIPS_2_C_OUTPUT
void func_80B7BABC(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor) {
    ? spFC;
    ? spE4;
    ? spCC;
    f32 spC4;
    ? spC0;
    ? spB4;
    f32 spB0;
    ? spA4;
    ? sp98;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    s16 sp84;
    s16 sp82;
    s16 sp80;
    f32 sp70;
    MtxF* sp4C;
    Gfx* temp_v0;
    Gfx* temp_v0_2;
    Gfx* temp_v0_3;
    GraphicsContext* temp_s2;
    Mtx* temp_s3;
    s32 temp_s6;
    s32 phi_v0;
    f32* phi_s5;
    Actor* phi_s0;
    Vec3f* phi_s7;
    s32 phi_s6;

    temp_s2 = globalCtx->state.gfxCtx;
    spFC.unk0 = (s32) D_80B7C2B4.unk0;
    spFC.unk4 = (s32) D_80B7C2B4.unk4;
    spFC.unkC = (s32) D_80B7C2B4.unkC;
    spFC.unk8 = (s32) D_80B7C2B4.unk8;
    spFC.unk10 = (s32) D_80B7C2B4.unk10;
    spFC.unk14 = (s32) D_80B7C2B4.unk14;
    spE4.unk4 = (s32) D_80B7C2CC.unk4;
    spE4.unk0 = (s32) D_80B7C2CC.unk0;
    spE4.unk8 = (s32) D_80B7C2CC.unk8;
    spE4.unkC = (s32) D_80B7C2CC.unkC;
    spE4.unk14 = (s32) D_80B7C2CC.unk14;
    spE4.unk10 = (s32) D_80B7C2CC.unk10;
    spCC.unk0 = (s32) D_80B7C2E4.unk0;
    spCC.unk4 = (s32) D_80B7C2E4.unk4;
    spCC.unk8 = (s32) D_80B7C2E4.unk8;
    spCC.unkC = (s32) D_80B7C2E4.unkC;
    spCC.unk10 = (s32) D_80B7C2E4.unk10;
    spCC.unk14 = (s32) D_80B7C2E4.unk14;
    spC0.unk0 = (f32) D_801D15B0.x;
    spC0.unk4 = (f32) D_801D15B0.y;
    spC0.unk8 = (f32) D_801D15B0.z;
    spC4 += D_80B7C3F4;
    if (limbIndex == 5) {
        spA4.unk0 = (s32) D_80B7C2FC.unk0;
        spA4.unk4 = (s32) D_80B7C2FC.unk4;
        spA4.unk8 = (s32) D_80B7C2FC.unk8;
        SysMatrix_MultiplyVector3fByState((Vec3f* ) &spA4, actor + 0x308);
        actor->unk2F4 = (s32) (actor->unk2F4 | 0x20);
    }
    phi_v0 = 5;
    if (limbIndex == 5) {
        sp98.unk0 = (s32) D_80B7C308.unk0;
        sp98.unk4 = (s32) D_80B7C308.unk4;
        sp98.unk8 = (s32) D_80B7C308.unk8;
        SysMatrix_MultiplyVector3fByState((Vec3f* ) &sp98, actor + 0x4BC);
        phi_v0 = 5;
    }
    if (limbIndex == phi_v0) {
        sp70.unk0 = (s32) D_80B7C314.unk0;
        sp70.unk4 = (s32) D_80B7C314.unk4;
        sp70.unk8 = (s32) D_80B7C314.unk8;
        sp80 = 0;
        sp84 = 0;
        sp88 = D_80B7C3F8;
        sp4C = &globalCtx->projectionMatrix;
        phi_s5 = &sp70;
        phi_s0 = actor;
        phi_s7 = actor + 0x32C;
        phi_s6 = 0;
loop_6:
        sp90 = *phi_s5;
        sp8C = *(&spCC + (phi_s0->unk314 * 4));
        if (phi_s0->unk314 == 5) {
            sp82 = 0x4000;
        } else {
            sp82 = -0x4000;
        }
        SysMatrix_StatePush();
        SysMatrix_RotateAndTranslateState((Vec3f* ) &sp88, (Vec3s* ) &sp80);
        temp_s3 = Matrix_NewMtx(temp_s2);
        SysMatrix_MultiplyVector3fByState((Vec3f* ) &spC0, (Vec3f* ) &spB4);
        SkinMatrix_Vec3fMtxFMultXYZW(sp4C, (Vec3f* ) &spB4, phi_s7, &spB0);
        if (phi_s0->unk320 != 0) {
            phi_s0->unk320 = 0;
            if (phi_s0->unk314 == 1) {
                func_80B7B93C(globalCtx, (Vec3f* ) &spB4);
            } else {
                EffectSsHitMark_SpawnFixedScale(globalCtx, 0, (Vec3f* ) &spB4);
            }
        }
        SysMatrix_StatePop();
        if (temp_s3 != 0) {
            temp_v0 = temp_s2->polyOpa.p;
            temp_s2->polyOpa.p = temp_v0 + 8;
            temp_v0->words.w1 = (u32) temp_s3;
            temp_v0->words.w0 = 0xDA380003;
            temp_s6 = phi_s6 + 0xC;
            if (*(&spFC + (phi_s0->unk314 * 4)) != 0) {
                temp_v0_2 = temp_s2->polyOpa.p;
                temp_s2->polyOpa.p = temp_v0_2 + 8;
                temp_v0_2->words.w0 = 0xDE000000;
                temp_v0_2->words.w1 = *(&spFC + (phi_s0->unk314 * 4));
                if ((sp + (phi_s0->unk314 * 4))->unkE4 != 0) {
                    temp_v0_3 = temp_s2->polyOpa.p;
                    temp_s2->polyOpa.p = temp_v0_3 + 8;
                    temp_v0_3->words.w0 = 0xDE000000;
                    temp_v0_3->words.w1 = (sp + (phi_s0->unk314 * 4))->unkE4;
                }
            }
            phi_s5 += 4;
            phi_s0 += 4;
            phi_s7 += 0xC;
            phi_s6 = temp_s6;
            if (temp_s6 == 0x24) {
                goto block_18;
            }
            goto loop_6;
        }
    } else {
block_18:
        if (limbIndex == 0xD) {
            SysMatrix_GetStateTranslation((Vec3f* ) &actor->focus);
        }
    }
}
#else
void func_80B7BABC(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7BABC.s")
#endif

void func_80B7BEA4(Vec3f* arg0, s16 arg1, Vec3f* arg2, u8 arg3, GlobalContext* globalCtx) {
    f32 temp;
    Vec3f sp108;
    CollisionPoly* sp104;
    Mtx* sp100;
    MtxF spC0;
    MtxF sp80;
    MtxF sp40;

    VEC_SET(sp108, arg0->x, arg0->y + 1.0f, arg0->z);

    temp = func_800C4000(globalCtx, &globalCtx->colCtx, &sp104, &sp108);
    if (sp104 != NULL) {
        func_800C0094(sp104, arg0->x, temp, arg0->z, &spC0);
    } else {
        SkinMatrix_SetTranslate(&spC0, arg0->x, arg0->y, arg0->z);
    }

    SkinMatrix_MulYRotation( &spC0, arg1);
    SkinMatrix_SetScale(&sp80, arg2->x, 1.0f, arg2->z);
    SkinMatrix_MtxFMtxFMult(&spC0, &sp80, &sp40);

    sp100 = SkinMatrix_MtxFToNewMtx(globalCtx->state.gfxCtx, &sp40);
    if (sp100 != NULL) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        gSPMatrix(POLY_OPA_DISP++, &D_801D1DE0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        POLY_OPA_DISP = Gfx_CallSetupDL(POLY_OPA_DISP, 0x2C);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, arg3);
        gSPMatrix(POLY_OPA_DISP++, sp100, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, D_04075A40);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void ObjUm_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjUm* this = THIS;
    Vec3f sp34;

    this->unk_2F4 |= 1;
    SkelAnime_DrawSV(globalCtx, this->unk_160.skeleton, this->unk_160.limbDrawTbl, this->unk_160.dListCount, func_80B7B598, func_80B7BABC, &this->dyna.actor);
    sp34.x = 0.45f;
    sp34.y = 0.0f;
    sp34.z = 0.7f;
    func_80B7BEA4(&this->unk_4BC, this->dyna.actor.shape.rot.y, &sp34, 0xB4, globalCtx);
    func_80B77770(this, globalCtx);
}
