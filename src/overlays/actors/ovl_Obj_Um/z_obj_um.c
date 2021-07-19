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

#if 0
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
#endif

/*
f32 func_800C3FA0(s32, ?*, void*, void*); // extern
f32 func_800C4000(GlobalContext*, CollisionContext*, CollisionPoly**, f32*); // extern
? func_800F415C(void*, ?*, ?); // extern
? func_8017B7F8(?*, s16, f32*, f32*, f32*); // extern
? func_801A3F54(?); // extern
? func_80B781DC(ObjUm* arg0, EnHorse* arg1, EnHorse* arg2, GlobalContext* arg3); // static
? func_80B783E0(ObjUm* arg0, GlobalContext* arg1, s32 arg2, EnHorse* arg3); // static
? func_80B78764(ObjUm* arg0, GlobalContext* arg1, EnHorse* arg2, EnHorse* arg3); // static
? func_80B78A54(ObjUm* arg0, GlobalContext* arg1, s32 arg2, EnHorse* arg3, EnHorse* arg4); // static
s32 func_80B795A0(GlobalContext*, ObjUm*, s32); // static
s32 func_80B79734(GlobalContext* arg0, ObjUm* arg1, s32 arg2, s32*); // static
? func_80B7984C(GlobalContext* arg0, Actor* arg1, s32 arg2, s32* arg3); // static
s32 func_80B79BA0(ObjUm* arg0, GlobalContext* arg1); // static
void func_80B7AF30(void* arg0, s32 arg1); // static
void func_80B7B93C(GlobalContext* arg0, Vec3f* arg1); // static
extern f32 D_80B7C320;
extern f32 D_80B7C324;
extern f32 D_80B7C398;
extern f32 D_80B7C39C;
extern f32 D_80B7C3A0;
extern f32 D_80B7C3CC;
extern f32 D_80B7C3F4;
extern f32 D_80B7C3F8;
extern f32 D_80B7C3FC;
extern f32 D_80B7C400;
static ? D_80B7C110; // unable to generate initializer
static ? D_80B7C128; // unable to generate initializer
static ? D_80B7C164; // unable to generate initializer
static ? D_80B7C25C; // unable to generate initializer
static ? D_80B7C260; // unable to generate initializer
static ? D_80B7C274; // unable to generate initializer
static ? D_80B7C284; // unable to generate initializer
static ? D_80B7C290; // unable to generate initializer
static ? D_80B7C29C; // unable to generate initializer
static ? D_80B7C2A8; // unable to generate initializer
static ? D_80B7C2B4; // unable to generate initializer
static ? D_80B7C2CC; // unable to generate initializer
static ? D_80B7C2E4; // unable to generate initializer
static ? D_80B7C2FC; // unable to generate initializer
static ? D_80B7C308; // unable to generate initializer
static ? D_80B7C314; // unable to generate initializer
ColliderCylinderInit D_80B7C138 = {
    {3, 0, 9, 0, 0x10, 1},
    {1, {0, 0, 0}, {0x20, 0, 0}, 0, 1, 0},
    {0x28, 0x40, 0, {0, 0, 0}},
};
InitChainEntry D_80B7C254[2]; // unable to generate initializer
*/
// D_80B7C110
// D_80B7C128
extern ColliderCylinderInit D_80B7C138;
// D_80B7C164
extern InitChainEntry D_80B7C254[2];
// D_80B7C25C
// D_80B7C260
extern AnimationHeader D_80B7C274[];
extern Vec3f D_80B7C284;
extern Vec3f D_80B7C290;
extern Vec3f D_80B7C29C;
extern Gfx* D_80B7C2A8[];
// D_80B7C2B4
// D_80B7C2CC
// D_80B7C2E4
extern Vec3f D_80B7C2FC;
extern Vec3f D_80B7C308;
extern Vec3f D_80B7C314;

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


// global?
extern Vec3s D_801D15BC;

extern FlexSkeletonHeader D_06011DF8;
extern AnimationHeader D_06012CC0;
extern CollisionHeader D_06007E20;
extern CollisionHeader D_06007F50;

extern Gfx D_06000040[];
extern Gfx D_06000910[];
extern Gfx D_060011E0[];

extern Gfx D_04075A40[];


#ifdef MIPS_2_C_OUTPUT
void func_80B77770(ObjUm* this, GlobalContext* globalCtx) {
    ? sp108;
    ? spFC;
    ? spF0;
    ? spE4;
    ? spD8;
    ? spCC;
    ? spC0;
    ? spB4;
    ? spA8;
    ? sp9C;
    ? sp90;
    ? sp84;
    ? sp78;
    ? sp6C;
    ? sp60;
    void* sp58;
    void* sp54;
    void* sp50;
    void* sp4C;
    Vec3f* sp48;
    Vec3f* sp44;
    Vec3f* sp40;
    Vec3f* sp3C;
    Vec3f* sp38;
    void* sp34;
    Vec3f* sp30;
    Vec3f* sp2C;
    s8* sp28;
    s32 sp24;
    s32 sp20;
    Vec3f* temp_t6_3;
    Vec3f* temp_t6_4;
    Vec3f* temp_t6_5;
    Vec3f* temp_t8_3;
    Vec3f* temp_t8_4;
    Vec3f* temp_t8_5;
    Vec3f* temp_t9;
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_s1;
    s8* temp_t7;
    void* temp_t6;
    void* temp_t6_2;
    void* temp_t8;
    void* temp_t8_2;
    void* temp_t8_6;

    temp_s1 = this->dyna.actor.shape.rot.y;
    sp60.unk0 = (f32) this->dyna.actor.world.pos.x;
    temp_a0 = temp_s1 + 0x4000;
    sp60.unk4 = (f32) this->dyna.actor.world.pos.y;
    sp60.unk8 = (f32) this->dyna.actor.world.pos.z;
    this->unk414 = (f32) sp60.unk0;
    this->unk418 = (f32) sp60.unk4;
    temp_t8 = this + 0x408;
    this->unk41C = (f32) sp60.unk8;
    sp6C.unk0 = (f32) sp60.unk0;
    sp6C.unk4 = (f32) sp60.unk4;
    sp6C.unk8 = (f32) sp60.unk8;
    sp58 = temp_t8;
    temp_t8->unk0 = (f32) sp6C.unk0;
    temp_t8->unk4 = (f32) sp6C.unk4;
    temp_t6 = this + 0x3FC;
    temp_t8->unk8 = (f32) sp6C.unk8;
    sp78.unk0 = (f32) sp6C.unk0;
    sp78.unk4 = (f32) sp6C.unk4;
    sp78.unk8 = (f32) sp6C.unk8;
    sp54 = temp_t6;
    temp_t6->unk0 = (f32) sp78.unk0;
    temp_t6->unk4 = (f32) sp78.unk4;
    temp_t8_2 = this + 0x3F0;
    temp_t6->unk8 = (f32) sp78.unk8;
    sp84.unk0 = (f32) sp78.unk0;
    sp84.unk4 = (f32) sp78.unk4;
    sp84.unk8 = (f32) sp78.unk8;
    sp50 = temp_t8_2;
    temp_t8_2->unk0 = (f32) sp84.unk0;
    temp_t8_2->unk4 = (f32) sp84.unk4;
    temp_t6_2 = this + 0x3E4;
    temp_t8_2->unk8 = (f32) sp84.unk8;
    sp90.unk0 = (f32) sp84.unk0;
    sp90.unk4 = (f32) sp84.unk4;
    sp90.unk8 = (f32) sp84.unk8;
    sp4C = temp_t6_2;
    temp_t6_2->unk0 = (f32) sp90.unk0;
    temp_t6_2->unk4 = (f32) sp90.unk4;
    temp_t8_3 = this + 0x3D8;
    temp_t6_2->unk8 = (f32) sp90.unk8;
    sp9C.unk0 = (f32) sp90.unk0;
    sp9C.unk4 = (f32) sp90.unk4;
    sp9C.unk8 = (f32) sp90.unk8;
    sp48 = temp_t8_3;
    temp_t8_3->x = sp9C.unk0;
    temp_t8_3->y = sp9C.unk4;
    temp_t8_3->z = sp9C.unk8;
    spA8.unk0 = (f32) sp9C.unk0;
    spA8.unk4 = (f32) sp9C.unk4;
    spA8.unk8 = (f32) sp9C.unk8;
    this->unk3CC = (f32) spA8.unk0;
    this->unk3D0 = (f32) spA8.unk4;
    temp_t6_3 = this + 0x3C0;
    this->unk3D4 = (f32) spA8.unk8;
    spB4.unk0 = (f32) spA8.unk0;
    spB4.unk4 = (f32) spA8.unk4;
    spB4.unk8 = (f32) spA8.unk8;
    sp44 = temp_t6_3;
    temp_t6_3->x = spB4.unk0;
    temp_t6_3->y = spB4.unk4;
    temp_t8_4 = this + 0x3B4;
    temp_t6_3->z = spB4.unk8;
    spC0.unk0 = (f32) spB4.unk0;
    spC0.unk4 = (f32) spB4.unk4;
    spC0.unk8 = (f32) spB4.unk8;
    sp40 = temp_t8_4;
    temp_t8_4->x = spC0.unk0;
    temp_t8_4->y = spC0.unk4;
    temp_t8_4->z = spC0.unk8;
    spCC.unk0 = (f32) spC0.unk0;
    spCC.unk4 = (f32) spC0.unk4;
    spCC.unk8 = (f32) spC0.unk8;
    this->unk3A8 = (f32) spCC.unk0;
    this->unk3AC = (f32) spCC.unk4;
    temp_t6_4 = this + 0x39C;
    this->unk3B0 = (f32) spCC.unk8;
    spD8.unk0 = (f32) spCC.unk0;
    spD8.unk4 = (f32) spCC.unk4;
    spD8.unk8 = (f32) spCC.unk8;
    sp3C = temp_t6_4;
    temp_t6_4->x = spD8.unk0;
    temp_t6_4->y = spD8.unk4;
    temp_t8_5 = this + 0x390;
    temp_t6_4->z = spD8.unk8;
    spE4.unk0 = (f32) spD8.unk0;
    spE4.unk4 = (f32) spD8.unk4;
    spE4.unk8 = (f32) spD8.unk8;
    sp38 = temp_t8_5;
    temp_t8_5->x = spE4.unk0;
    temp_t8_5->y = spE4.unk4;
    temp_t8_5->z = spE4.unk8;
    spF0.unk0 = (f32) spE4.unk0;
    spF0.unk4 = (f32) spE4.unk4;
    spF0.unk8 = (f32) spE4.unk8;
    temp_t8_6 = this + 0x384;
    sp34 = temp_t8_6;
    temp_t8_6->unk0 = (f32) spF0.unk0;
    temp_t8_6->unk4 = (f32) spF0.unk4;
    temp_t8_6->unk8 = (f32) spF0.unk8;
    spFC.unk0 = (f32) spF0.unk0;
    spFC.unk4 = (f32) spF0.unk4;
    temp_t9 = this + 0x378;
    spFC.unk8 = (f32) spF0.unk8;
    sp30 = temp_t9;
    temp_t9->x = spFC.unk0;
    temp_t9->y = spFC.unk4;
    temp_t9->z = spFC.unk8;
    sp108.unk0 = (f32) spFC.unk0;
    sp108.unk4 = (f32) spFC.unk4;
    temp_t6_5 = this + 0x36C;
    sp108.unk8 = (f32) spFC.unk8;
    sp2C = temp_t6_5;
    temp_t6_5->x = sp108.unk0;
    temp_t6_5->y = sp108.unk4;
    temp_t7 = this->unk_360;
    temp_t6_5->z = sp108.unk8;
    sp28 = temp_t7;
    temp_t7->unk0 = (f32) sp108.unk0;
    temp_t7->unk4 = (f32) sp108.unk4;
    temp_t7->unk8 = (f32) sp108.unk8;
    sp24 = (s32) temp_a0;
    this->unk_360 = (bitwise s8* ) ((bitwise f32) this->unk_360 + (110.0f * Math_SinS(temp_a0)));
    temp_a0_2 = temp_s1 - 0x4000;
    this->unk368 = (f32) (this->unk368 + (110.0f * Math_CosS(sp26)));
    sp20 = (s32) temp_a0_2;
    this->unk36C = (f32) (this->unk36C + (110.0f * Math_SinS(temp_a0_2)));
    this->unk374 = (f32) (this->unk374 + (110.0f * Math_CosS(sp22)));
    Math_Vec3f_Copy(sp30, (Vec3f* ) sp28);
    this->unk378 = (f32) (this->unk378 - (200.0f * Math_SinS(temp_s1)));
    this->unk380 = (f32) (this->unk380 - (200.0f * Math_CosS(temp_s1)));
    Math_Vec3f_Copy(sp38, sp2C);
    this->unk390 = (f32) (this->unk390 - (200.0f * Math_SinS(temp_s1)));
    this->unk398 = (f32) (this->unk398 - (200.0f * Math_CosS(temp_s1)));
    this->unk384 = (f32) (this->unk384 - (220.0f * Math_SinS(temp_s1)));
    this->unk38C = (f32) (this->unk38C - (220.0f * Math_CosS(temp_s1)));
    Math_Vec3f_Copy(sp3C, (Vec3f* ) sp28);
    this->unk39C = (f32) (this->unk39C - (500.0f * Math_SinS(temp_s1)));
    this->unk3A4 = (f32) (this->unk3A4 - (500.0f * Math_CosS(temp_s1)));
    Math_Vec3f_Copy(sp40, sp2C);
    this->unk3B4 = (f32) (this->unk3B4 - (500.0f * Math_SinS(temp_s1)));
    this->unk3BC = (f32) (this->unk3BC - (500.0f * Math_CosS(temp_s1)));
    this->unk3A8 = (f32) (this->unk3A8 - (500.0f * Math_SinS(temp_s1)));
    this->unk3B0 = (f32) (this->unk3B0 - (500.0f * Math_CosS(temp_s1)));
    Math_Vec3f_Copy(sp44, (Vec3f* ) sp28);
    this->unk3C0 = (f32) (this->unk3C0 - (700.0f * Math_SinS(temp_s1)));
    this->unk3C8 = (f32) (this->unk3C8 - (700.0f * Math_CosS(temp_s1)));
    Math_Vec3f_Copy(sp48, sp2C);
    this->unk3D8 = (f32) (this->unk3D8 - (700.0f * Math_SinS(temp_s1)));
    this->unk3E0 = (f32) (this->unk3E0 - (700.0f * Math_CosS(temp_s1)));
    this->unk3CC = (f32) (this->unk3CC - (700.0f * Math_SinS(temp_s1)));
    this->unk3D4 = (f32) (this->unk3D4 - (700.0f * Math_CosS(temp_s1)));
    sp4C->unk0 = (f32) temp_t8_6->unk0;
    sp4C->unk4 = (f32) temp_t8_6->unk4;
    sp4C->unk8 = (f32) temp_t8_6->unk8;
    this->unk3E4 = (f32) (this->unk3E4 + (40.0f * Math_SinS(sp26)));
    this->unk3EC = (f32) (this->unk3EC + (40.0f * Math_CosS(sp26)));
    sp50->unk0 = (f32) temp_t8_6->unk0;
    sp50->unk4 = (f32) temp_t8_6->unk4;
    sp50->unk8 = (f32) temp_t8_6->unk8;
    this->unk3F0 = (f32) (this->unk3F0 + (40.0f * Math_SinS(sp22)));
    this->unk3F8 = (f32) (this->unk3F8 + (40.0f * Math_CosS(sp22)));
    sp54->unk0 = (f32) sp30->x;
    sp54->unk4 = (f32) sp30->y;
    sp54->unk8 = (f32) sp30->z;
    sp58->unk0 = (f32) temp_t8_5->x;
    sp58->unk4 = (f32) temp_t8_5->y;
    sp58->unk8 = (f32) temp_t8_5->z;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B77770.asm")
#endif

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
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B77FA4.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
? func_80B781DC(ObjUm* arg0, EnHorse* arg1, EnHorse* arg2, GlobalContext* arg3) {
    ?* temp_s0;
    f32 temp_f20;
    s32 temp_s4;
    s32 temp_t1;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;
    ?* phi_s0;
    s32 phi_s3;
    s32 phi_s2;
    s32 phi_s4;
    f32 phi_f20;

    phi_s0 = &D_80B7C164;
    phi_s3 = -1;
    phi_s2 = 0;
    phi_s4 = 0;
    phi_f20 = 0.0f;
    do {
        temp_v1 = phi_s0->unk0;
        if (arg1->unk_550 == temp_v1) {
            temp_v0 = phi_s0->unk4;
            if (arg2->unk_550 != temp_v0) {
                if (temp_v1 != 3) {
                    if (temp_v0 == 3) {
                        if (Player_GetMask(arg3) != 8) {
                            goto block_7;
                        }
                    } else {
block_7:
                        phi_s3 = phi_s0->unk4;
                        phi_s4 = phi_s0->unk8;
                        phi_f20 = phi_s0->unkC;
                        goto block_14;
                    }
                } else {
                    temp_v1_2 = arg1->unk_54C;
                    if (((temp_v1_2 != 5) || (temp_v0 != 2)) && ((temp_v1_2 != 7) || (temp_v0 != 4))) {
                        temp_s4 = phi_s0->unk8;
                        temp_f20 = phi_s0->unkC;
                        phi_s3 = temp_v0;
                        phi_s4 = temp_s4;
                        phi_f20 = temp_f20;
                        if ((2.0f * Rand_ZeroOne()) < 1.0f) {
                            phi_s3 = temp_v0;
                            phi_s4 = temp_s4;
                            phi_f20 = temp_f20 * -1.0f;
                        }
block_14:
                        phi_s2 = phi_s0->unk10;
                    }
                }
            }
        }
        temp_s0 = phi_s0 + 0x14;
        phi_s0 = temp_s0;
    } while (temp_s0 != D_80B7C254);
    if (phi_s3 == -1) {

    } else {
        temp_t1 = arg1->unk_550;
        arg1->unk_540.x = arg1->actor.world.pos.x;
        arg1->unk_550 = phi_s3;
        arg1->unk_55C = phi_s2;
        arg1->unk_560 = phi_s2;
        arg1->unk_564 = phi_s4;
        arg1->unk_568 = phi_f20;
        arg1->unk_540.y = arg1->actor.world.pos.y;
        arg1->unk_54C = temp_t1;
        arg1->unk_540.z = arg1->actor.world.pos.z;
        if (phi_s3 == 3) {
            arg1->unk_558 = (s32) (Rand_ZeroOne() * 3.0f);
        } else {
            arg1->unk_558 = 0;
        }
    }
    return 0;
}
#else
s32 func_80B781DC(ObjUm* this, EnHorse* arg2, EnHorse* arg3, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B781DC.asm")
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

#ifdef NON_MATCHING
void ObjUm_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjUm* this = THIS;
    s32 sp54 = true;
    Vec3s sp48;
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

    Actor_ProcessInitChain((Actor* ) this, D_80B7C254);
    ActorShape_Init(&this->dyna.actor.shape, 0.0f, NULL, 50.0f);
    SkelAnime_InitSV(globalCtx, &this->unk_160, &D_06011DF8, NULL, this->unk_1A4, this->unk_228, 0x16);
    SkelAnime_ChangeAnimDefaultRepeat(&this->unk_160, &D_06012CC0);

    this->unk_2AC = 0;
    func_80B7B154(this, globalCtx);

    // needs extra lh
    this->unk_2AE = ((this->dyna.actor.params & 0xFF00) >> 8);
    this->unk_2B0 = (this->dyna.actor.params & 0xFF);

    if ((gSaveContext.weekEventReg[0x16] & 1) == 0) {
        Actor_MarkForDeath((Actor* ) this);
        return;
    }

    if (this->unk_2AE == 0) {
        ObjUm_SetupAction(this, func_80B7AEFC);
    } else if (this->unk_2AE == 1) {
        this->unk_2BC = this->unk_2B0;
        if ((gSaveContext.weekEventReg[0x1F] & 0x80) != 0) {
            sp54 = false;
            this->unk_2F4 |= 0x100;
            ObjUm_SetupAction(this, func_80B7A144);
            func_800FE484();
        } else {
            if (((gSaveContext.weekEventReg[0x38] & 0x80) != 0) || (s32) (gSaveContext.time) >= 0xCAAA || (s32) gSaveContext.time < 0x4001 || ((gSaveContext.weekEventReg[0x36]) & 1) != 0 || ((gSaveContext.weekEventReg[0x36] & 2) != 0)) {
                Actor_MarkForDeath((Actor* ) this);
                return;
            }
            this->dyna.actor.targetMode = 6;
            this->unk_2B4 = 0;
            ObjUm_SetupAction(this, func_80B79A50);
        }
    } else if (this->unk_2AE == 2) {
        if ((gSaveContext.weekEventReg[0x1F] & 0x80) == 0 || (((gSaveContext.weekEventReg[0x34]) & 1) != 0)) {
            Actor_MarkForDeath((Actor* ) this);
            return;
        }

        if ((gSaveContext.weekEventReg[0x34] & 2) == 0) {
            this->unk_2BC = this->unk_2B0;
            sp54 = false;
            func_800FE484();
            ObjUm_SetupAction(this, func_80B7A400);
            this->unk_354 = 0;
            func_80B78E88(this, globalCtx, 0);
        }
    } else if (this->unk_2AE == 3) {
        if ((gSaveContext.weekEventReg[0x36] & 0x80) == 0) {
            Actor_MarkForDeath((Actor* ) this);
            return;
        }
        this->unk_2BC = this->unk_2B0;
        sp54 = false;
        func_800FE484();
        ObjUm_SetupAction(this, func_80B7AC94);
        this->unk_354 = 0;
        func_80B78E88(this, globalCtx, 0);
    } else if (this->unk_2AE == 4) {
        if ((gSaveContext.weekEventReg[0x34] & 1) == 0 || (gSaveContext.weekEventReg[0x3B] & 2) != 0) {
            Actor_MarkForDeath((Actor* ) this);
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

    sp48 = D_801D15BC;

    this->unk_2FE = sp48;
    this->unk_2F8 = sp48;

    if (sp54) {
        BcCheck3_BgActorInit((DynaPolyActor* ) this, 0);
        BgCheck3_LoadMesh(globalCtx, (DynaPolyActor* ) this, &D_06007E20);
    } else {
        BcCheck3_BgActorInit((DynaPolyActor* ) this, 3);
        BgCheck3_LoadMesh(globalCtx, (DynaPolyActor* ) this, &D_06007F50);
    }

    if (this->dyna.bgId == 0x32) {
        Actor_MarkForDeath((Actor* ) this);
        return ;
    }

    func_800C636C(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);

    this->unk_2B8 = Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xD, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, (s16) 0, (s16) (s32) this->dyna.actor.shape.rot.y, (s16) 0, 0x8012);

    if (this->unk_2B8 == NULL) {
        Actor_MarkForDeath((Actor* ) this);
        return;
    }

    Collider_InitAndSetCylinder(globalCtx, &this->unk_424[0], (Actor* ) this, &D_80B7C138);
    Collider_InitAndSetCylinder(globalCtx, &this->unk_424[1], (Actor* ) this, &D_80B7C138);

    return;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/ObjUm_Init.asm")
#endif

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
        Actor_MarkForDeath(this->unk_2B8);
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
                func_800E8EA0(globalCtx, (Actor* ) this, 0x33B5U);
                func_8019F230();
                func_80151BB4(globalCtx, 6U);
                phi_v1 = false;
            }
            break;
        case 0x33BB:
            func_800E8EA0(globalCtx, (Actor* ) this, 0x33BCU);
            phi_v1 = false;
            break;
        case 0x33BC:
            func_800E8EA0(globalCtx, (Actor* ) this, 0x33BDU);
            phi_v1 = false;
            break;
        case 0x33BD:
            if (globalCtx->msgCtx.choiceIndex == 0) {
                func_800E8EA0(globalCtx, (Actor* ) this, 0x33BEU);
                func_8019F230();
            } else {
                func_800E8EA0(globalCtx, (Actor* ) this, 0x33BFU);
                func_8019F208();
            }
            phi_v1 = false;
            break;
        case 0x33BE:
            func_800E8EA0(globalCtx, (Actor* ) this, 0x33BCU);
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
        func_801518B0(globalCtx, this->dyna.actor.textId, (Actor* ) this);
        *arg3 = 1;
        return 0;
    }
    if (*arg3 == 3) {
        func_80151938(globalCtx, this->dyna.actor.textId);
        *arg3 = 1;
        return 0;
    }

    if (func_800B84D0((Actor* ) this, globalCtx) != 0) {
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
        if (func_800B8614((Actor* ) this, globalCtx, 50.0f) != 0) {
            this->dyna.actor.textId = func_80B797EC(globalCtx, this, arg2);
        }
    } else if (func_800B863C((Actor* ) this, globalCtx) != 0) {
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

#ifdef MIPS_2_C_OUTPUT
s32 func_80B79BA0(ObjUm* arg0, GlobalContext* arg1) {
    void* sp6C;
    s32 sp68;
    void* sp64;
    ? sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s32 sp3C;
    f32 temp_f2;
    s16 temp_a2_2;
    s16 temp_a2_3;
    s16 temp_v0_3;
    s16 temp_v1_3;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 temp_v1_2;
    u8 temp_a0;
    u8 temp_t1;
    void* temp_a2;
    void* temp_t0;
    void* temp_v0;
    void* temp_v0_2;
    f32 phi_f12;
    f32 phi_f14;
    s32 phi_v0;
    s32 phi_v1;
    s16 phi_a2;

    temp_a2 = arg1->setupPathList + (arg0->unk_2BC * 8);
    temp_t1 = temp_a2->unk0;
    sp6C = temp_a2;
    sp68 = (s32) temp_t1;
    temp_t0 = Lib_SegmentedToVirtual(temp_a2->unk4);
    sp3C = 0;
    if (temp_t1 == 0) {
        return 0;
    }
    sp68 = (s32) temp_t1;
    sp64 = temp_t0;
    sp6C = temp_a2;
    Math_Vec3s_ToVec3f((Vec3f* ) &sp50, (arg0->unk_2BE * 6) + temp_t0);
    temp_v1 = arg0->unk_2BE;
    if (temp_v1 == 0) {
        phi_f12 = (f32) (temp_t0->unk6 - temp_t0->unk0);
        phi_f14 = (f32) (temp_t0->unkA - temp_t0->unk4);
    } else {
        temp_a0 = temp_a2->unk0;
        if (temp_a0 == (temp_v1 + 1)) {
            temp_v0 = temp_t0 + (temp_a0 * 6);
            phi_f12 = (f32) (temp_v0->unk-6 - temp_v0->unk-C);
            phi_f14 = (f32) (temp_v0->unk-2 - temp_v0->unk-8);
        } else {
            temp_v0_2 = temp_t0 + (temp_v1 * 6);
            phi_f12 = (f32) (temp_v0_2->unk6 - temp_v0_2->unk-6);
            phi_f14 = (f32) (temp_v0_2->unkA - temp_v0_2->unk-2);
        }
    }
    sp64 = temp_t0;
    sp68 = (s32) temp_t1;
    func_8017B7F8(&sp50, Math_Atan2S(phi_f12, phi_f14), &sp4C, &sp48, &sp44);
    if (((arg0->dyna.actor.world.pos.x * sp4C) + (sp48 * arg0->dyna.actor.world.pos.z) + sp44) > 0.0f) {
        temp_v1_2 = arg0->unk_2BE + 1;
        arg0->unk_2BE = temp_v1_2;
        if (temp_v1_2 >= (temp_t1 - 7)) {
            sp3C = 3;
        }
        phi_v0 = sp3C;
        if (temp_v1_2 >= (temp_t1 - 3)) {
            phi_v0 = 1;
        }
        if (temp_v1_2 >= (temp_t1 - 2)) {
            phi_v0 = 4;
        }
        phi_v1 = temp_v1_2;
        if (temp_v1_2 >= (s32) temp_t1) {
            arg0->unk_2BE = 0;
            phi_v0 = 2;
            phi_v1 = 0;
        }
        sp3C = phi_v0;
        Math_Vec3s_ToVec3f((Vec3f* ) &sp50, (phi_v1 * 6) + temp_t0);
    }
    if (arg0->unk_2B8 != 0) {
        arg0->dyna.actor.world.rot.y = Math_Vec3f_Yaw(arg0 + 0x24, (Vec3f* ) &sp50);
        func_800F415C(arg0->unk_2B8, &sp50, 0x190);
        temp_v1_3 = arg0->dyna.actor.shape.rot.y;
        temp_v0_3 = arg0->unk_2B8->unkBE;
        temp_a2_2 = temp_v0_3 - temp_v1_3;
        temp_a2_3 = temp_a2_2;
        temp_f2 = fabsf((f32) temp_a2_3);
        if (temp_f2 < D_80B7C3A0) {
            if (temp_f2 < 100.0f) {
                arg0->dyna.actor.shape.rot.y = temp_v0_3;
                phi_a2 = temp_a2_3;
            } else if ((s32) temp_a2_3 > 0) {
                arg0->dyna.actor.shape.rot.y = temp_v1_3 + 0x64;
                phi_a2 = 0x64;
            } else {
                phi_a2 = temp_a2_3;
                if ((s32) temp_a2_3 < 0) {
                    arg0->dyna.actor.shape.rot.y = temp_v1_3 - 0x64;
                    phi_a2 = -0x64;
                }
            }
        } else if ((s32) temp_a2_3 > 0) {
            arg0->dyna.actor.shape.rot.y = temp_v1_3 + 0x190;
            phi_a2 = 0x190;
        } else {
            phi_a2 = temp_a2_3;
            if ((s32) temp_a2_3 < 0) {
                arg0->dyna.actor.shape.rot.y = temp_v1_3 - 0x190;
                phi_a2 = -0x190;
            }
        }
        if ((arg0->unk_2F4 & 0x14) != 0) {
            func_80B78EFC(arg0, arg1, phi_a2);
        }
    }
    temp_v0_4 = arg0->unk_304;
    if (temp_v0_4 == 0) {
        arg0->dyna.actor.speedXZ = 4.0f;
    } else if (temp_v0_4 == 1) {
        arg0->dyna.actor.speedXZ = 8.0f;
    }
    return sp3C;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B79BA0.asm")
#endif

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

#ifdef NON_MATCHING
// v0/v1 problems
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
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A400.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
void func_80B7A494(ObjUm* this, GlobalContext* globalCtx) {
    s32 temp_v0;
    u8 temp_t1;
    u8 temp_t9;
    u8 temp_v1;

    func_80B78E38(this, globalCtx);
    func_80B78E88(this, globalCtx, 0x7FFF);
    this->unk_2AC += 0x7D0;
    this->unk_2F4 |= 0x10;
    func_80B7B18C(this, globalCtx, 1);
    temp_v0 = func_80B79BA0(this, globalCtx);
    if ((temp_v0 == 1) || (temp_v0 == 2)) {
        temp_v1 = gSaveContext.unkF2C;
        gSaveContext.seqIndex = 0xFF;
        gSaveContext.unkF17 = (u8) (gSaveContext.unkF17 & 0x7F);
        gSaveContext.nightSeqIndex = 0xFF;
        if (((temp_v1 & 1) == 0) && ((temp_v1 & 2) == 0)) {
            if (this->unk_4E0 == 0) {
                globalCtx->nextEntranceIndex = 0x3E60;
                globalCtx->unk_1887F = 0x40;
                gSaveContext.nextTransition = 3;
                globalCtx->sceneLoadFlag = 0x14;
                temp_t1 = gSaveContext.unkF2C | 1;
                gSaveContext.unkF2C = temp_t1;
                gSaveContext.unkF2C = (u8) (temp_t1 & 0xFD);
                return;
            }
            globalCtx->nextEntranceIndex = 0x6480;
            globalCtx->unk_1887F = 0x40;
            gSaveContext.nextTransition = 3;
            globalCtx->sceneLoadFlag = 0x14;
            temp_t9 = gSaveContext.unkF2C | 2;
            gSaveContext.unkF2C = temp_t9;
            gSaveContext.unkF2C = (u8) (temp_t9 & 0xFE);
            return;
        }
        // Duplicate return node #8. Try simplifying control flow for better match
        return;
    }
    Actor_SetVelocityAndMoveYRotationAndGravity((Actor* ) this);
    func_80B78DF0(this, globalCtx);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A494.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
void func_80B7A614(ObjUm* this, GlobalContext* globalCtx) {
    s32 sp20;
    s16 temp_v0_3;
    s32 temp_t9;
    s32 temp_v0;
    s32 temp_v0_2;
    ObjUm* phi_v1;
    s32 phi_v0;
    s16 phi_v1_2;

    func_80B78E38(this, globalCtx);
    func_80B78E88(this, globalCtx, 0x7FFF);
    temp_t9 = this->unk_2F4 | 0x10;
    this->unk_2F4 = temp_t9;
    this->unk_2AC += 0x7D0;
    this->unk_2F4 = temp_t9 | 0x80;
    func_80B7B18C(this, globalCtx, 1);
    if ((func_80B79BA0(this, globalCtx) == 3) && (this->unk_4DC == 0)) {
        this->unk_4DC = 1;
    } else {
        temp_v0 = this->unk_4DC;
        if (temp_v0 > 0) {
            if (temp_v0 == 1) {
                this->unk_4E0 = 1;
                phi_v1 = this;
                phi_v0 = 0;
loop_6:
                temp_v0_2 = phi_v0 + 4;
                if (phi_v1->unk_314[0] != 1) {
                    this->unk_4E0 = 0;
                } else {
                    phi_v1 += 4;
                    phi_v0 = temp_v0_2;
                    if (temp_v0_2 != 0xC) {
                        goto loop_6;
                    }
                }
                this->unk_2F4 |= 0x2000;
            }
            this->unk_4DC += 1;
        }
    }
    if ((this->unk_2F4 & 0x2000) != 0) {
        temp_v0_3 = ActorCutscene_GetAdditionalCutscene((s16) this->dyna.actor.cutscene);
        phi_v1_2 = temp_v0_3;
        if (this->unk_4E0 != 0) {
            phi_v1_2 = ActorCutscene_GetAdditionalCutscene(temp_v0_3);
        }
        sp20 = (s32) phi_v1_2;
        if (ActorCutscene_GetCanPlayNext(phi_v1_2) != 0) {
            ActorCutscene_StartAndSetUnkLinkFields(phi_v1_2, (Actor* ) this);
            ObjUm_SetupAction(this, func_80B7A494);
            this->unk_2F4 &= -0x81;
        } else {
            ActorCutscene_SetIntentToPlay(phi_v1_2);
        }
    }
    Actor_SetVelocityAndMoveYRotationAndGravity((Actor* ) this);
    func_80B78DF0(this, globalCtx);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A614.asm")
#endif

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

#ifdef MIPS_2_C_OUTPUT
void func_80B7AF30(void* arg0, s32 arg1) {
    ? sp44;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    void* sp28;
    s32 sp24;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f10;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f4;
    f32 temp_f8;
    s32 temp_a0;
    s32 temp_cond;
    s32 temp_v0;
    void* temp_a2;
    void* temp_a3;

    temp_v0 = arg0->unk2F4;
    temp_a2 = arg0 + 0x2C4;
    if ((temp_v0 & 1) == 0) {
        arg0->unkBC = 0;
        arg0->unkC0 = 0;
        return;
    }
    arg0->unk2F4 = (s32) (temp_v0 & ~1);
    temp_a3 = arg0 + 0x2DC;
    arg0->unk2D0 = (f32) temp_a2->unk0;
    arg0->unk2D4 = (f32) temp_a2->unk4;
    arg0->unk2D8 = (f32) temp_a2->unk8;
    arg0->unk2E8 = (f32) temp_a3->unk0;
    arg0->unk2EC = (f32) temp_a3->unk4;
    arg0->unk2F0 = (f32) temp_a3->unk8;
    sp28 = temp_a3;
    temp_a0 = arg1 + 0x830;
    sp24 = temp_a0;
    temp_f0 = func_800C3FA0(temp_a0, &sp44, temp_a2, temp_a3);
    temp_cond = temp_f0 == -32000.0f;
    arg0->unk2D4 = temp_f0;
    if (temp_cond) {
        arg0->unk2D4 = (f32) arg0->unk88;
    }
    temp_f0_2 = func_800C3FA0(temp_a0, &sp44, temp_a3, temp_a3);
    arg0->unk2EC = temp_f0_2;
    if (temp_f0_2 == -32000.0f) {
        arg0->unk2EC = (f32) arg0->unk88;
    }
    temp_f10 = (arg0->unk2D0 + arg0->unk2E8) * 0.5f;
    sp30 = temp_f10;
    temp_f4 = (arg0->unk2D4 + arg0->unk2EC) * 0.5f;
    sp34 = temp_f4;
    temp_f8 = (arg0->unk2D8 + arg0->unk2F0) * 0.5f;
    sp38 = temp_f8;
    temp_f2 = temp_f10 - arg0->unk24;
    temp_f16 = temp_f8 - arg0->unk2C;
    arg0->unkBC = Math_Atan2S(temp_f4 - arg0->unk28, sqrtf((temp_f2 * temp_f2) + (temp_f16 * temp_f16)));
    temp_f2_2 = sp30 - arg0->unk2D0;
    temp_f16_2 = sp38 - arg0->unk2D8;
    arg0->unkC0 = (s16) -Math_Atan2S(temp_f4 - arg0->unk2D4, sqrtf((temp_f2_2 * temp_f2_2) + (temp_f16_2 * temp_f16_2)));
    if ((arg0->unk2F4 & 2) != 0) {
        arg0->unkBC = (s16) (arg0->unkBC + (s32) ((Rand_ZeroOne() * 100.0f) - 50.0f));
        arg0->unkC0 = (s16) (arg0->unkC0 + (s32) ((Rand_ZeroOne() * 100.0f) - 50.0f));
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7AF30.asm")
#endif

void func_80B7B154(ObjUm* this, GlobalContext* globalCtx) {
    SkelAnime_ChangeAnimDefaultStop(&this->unk_160, &D_06012CC0);
    this->unk_304 = 0;
}

#ifdef MIPS_2_C_OUTPUT
void func_80B7B18C(ObjUm* this, GlobalContext* globalCtx, s32 arg2) {
    s32 sp3C;
    s32 sp34;
    SkelAnime* sp24;
    Actor* temp_v0_2;
    Actor* temp_v1_2;
    AnimationHeader** temp_v0;
    SkelAnime* temp_a0;
    s32 temp_a1;
    s32 temp_lo;
    s32 temp_v1;
    f32 phi_f0;
    s32 phi_a3;

    temp_v1 = arg2;
    temp_a0 = &this->unk_160;
    if (*(&D_80B7C260 + (arg2 * 8)) != 0) {
        this->unk_2F4 |= 2;
    } else {
        this->unk_2F4 &= -3;
    }
    if (arg2 == 0) {
        phi_f0 = this->dyna.actor.speedXZ * 0.25f;
    } else if (arg2 == 1) {
        phi_f0 = this->dyna.actor.speedXZ * D_80B7C3CC;
    } else {
        phi_f0 = 0.0f;
        if (arg2 == 2) {
            phi_f0 = 1.0f;
        }
    }
    this->unk_160.animPlaybackSpeed = phi_f0;
    phi_a3 = arg2;
    if ((this->unk_2F4 & 0x800) != 0) {
        this->unk_160.animPlaybackSpeed = 1.0f;
        phi_a3 = -1;
    }
    arg2 = phi_a3;
    sp24 = temp_a0;
    temp_a1 = phi_a3 != this->unk_304;
    sp3C = temp_a1;
    sp34 = temp_v1;
    if ((SkelAnime_FrameUpdateMatrix(temp_a0) != 0) || (temp_a1 != 0)) {
        this->unk_304 = arg2;
        if (arg2 != -1) {
            temp_v1_2 = this->unk_2B8;
            temp_v0 = (arg2 * 8) + &D_80B7C25C;
            if (temp_v1_2 != 0) {
                temp_v1_2->unk538 = arg2;
            }
            if (temp_a1 != 0) {
                SkelAnime_ChangeAnimTransitionStop(temp_a0, *temp_v0, -3.0f);
            } else {
                SkelAnime_ChangeAnimDefaultStop(temp_a0, *temp_v0);
            }
        } else {
            temp_v0_2 = this->unk_2B8;
            if (temp_v0_2 != 0) {
                temp_v0_2->unk538 = temp_v1;
            }
            if (temp_a1 != 0) {
                SkelAnime_ChangeAnimTransitionStop(temp_a0, *(&D_80B7C274 + (arg2 * -8)), -10.0f);
            } else {
                SkelAnime_ChangeAnimDefaultStop(temp_a0, *(&D_80B7C274 + (arg2 * -8)));
            }
        }
    }
    temp_lo = (s32) this->unk_2AC / 0x199A;
    if (this->unk_420 != temp_lo) {
        this->unk_420 = temp_lo;
        Audio_PlayActorSound2((Actor* ) this, 0x2958U);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7B18C.asm")
#endif

void ObjUm_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjUm* this = THIS;

    this->actionFunc(this, globalCtx);
    this->unk_350 += 1;
    Actor_UpdateBgCheckInfo(globalCtx, &this->dyna.actor, 0.0f, 0.0f, 0.0f, 0x1C);

    if (this->unk_2B8 != 0) {
        this->unk_2B8->world.pos.x = this->dyna.actor.world.pos.x;
        this->unk_2B8->world.pos.y = this->dyna.actor.floorHeight;
        this->unk_2B8->world.pos.z = this->dyna.actor.world.pos.z;
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


#ifdef MIPS_2_C_OUTPUT
s32 func_80B7B598(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor) {
    Actor* sp70;
    ? sp5C;
    ? sp50;
    GraphicsContext* sp4C;
    Gfx* sp44;
    Gfx* sp40;
    s16 sp3E;
    f32 sp34;
    f32 sp30;
    Gfx* temp_v0;
    Gfx* temp_v0_2;
    GraphicsContext* temp_v1;
    f32 temp_f16;
    s16 temp_v0_3;

    sp70 = globalCtx->actorCtx.actorList[2].first;
    sp5C.unk0 = (s32) D_80B7C284.unk0;
    sp5C.unk4 = (s32) D_80B7C284.unk4;
    sp5C.unk8 = (s32) D_80B7C284.unk8;
    sp50.unk0 = (s32) D_80B7C290.unk0;
    sp50.unk4 = (s32) D_80B7C290.unk4;
    sp50.unk8 = (s32) D_80B7C290.unk8;
    if ((limbIndex >= 0xB) && (actor->unk2AE == 0)) {
        *dList = NULL;
        return 0;
    }
    if (limbIndex == 0xD) {
        temp_v1 = globalCtx->state.gfxCtx;
        temp_v0 = temp_v1->polyOpa.p;
        temp_v1->polyOpa.p = temp_v0 + 8;
        temp_v0->words.w0 = 0xDB060020;
        limbIndex = limbIndex;
        sp4C = temp_v1;
        sp44 = temp_v0;
        sp44->words.w1 = Lib_SegmentedToVirtual(*(&D_80B7C110 + (actor->unk4D0 * 4)));
        temp_v0_2 = temp_v1->polyOpa.p;
        temp_v1->polyOpa.p = temp_v0_2 + 8;
        temp_v0_2->words.w0 = 0xDB060024;
        limbIndex = limbIndex;
        sp40 = temp_v0_2;
        sp40->words.w1 = Lib_SegmentedToVirtual(*(&D_80B7C128 + (actor->unk4D4 * 4)));
    }
    if (limbIndex == 3) {
        if ((actor->unk2F4 & 2) != 0) {
            rot->x = (s16) -(s32) actor->unk2AC;
        }
        SysMatrix_MultiplyVector3fByState((Vec3f* ) &sp5C, actor + 0x2C4);
    } else if (limbIndex == 4) {
        if ((actor->unk2F4 & 2) != 0) {
            rot->x = actor->unk2AC;
        }
        SysMatrix_MultiplyVector3fByState((Vec3f* ) &sp50, actor + 0x2DC);
    } else if ((limbIndex == 0xD) && ((actor->unk2F4 & 8) != 0)) {
        if ((func_8013D5E8(actor->shape.rot.y, 0x4E20, actor->yawTowardsPlayer) != 0) && (actor->xzDistToPlayer < 500.0f)) {
            sp30.unk0 = (f32) sp70->world.pos.x;
            sp30.unk4 = (f32) sp70->world.pos.y;
            sp30.unk8 = (f32) sp70->world.pos.z;
            temp_f16 = sp70->unkC44 + 3.0f;
            sp34 = temp_f16;
            sp3E = Math_Vec3f_Yaw((Vec3f* ) &actor->focus, (Vec3f* ) &sp30) - actor->shape.rot.y;
            temp_v0_3 = Math_Atan2S(actor->focus.pos.y - temp_f16, Math3D_XZLength(sp30 - actor->focus.pos.x, sp38 - actor->focus.pos.z));
            actor->unk2FE = (s16) (rot->x + sp3E);
            actor->unk300 = (s16) rot->y;
            actor->unk302 = (s16) (rot->z + temp_v0_3);
            Math_SmoothStepToS(actor + 0x2F8, actor->unk2FE, 4, 0x3E8, (s16) 1);
            Math_SmoothStepToS(actor + 0x2FC, actor->unk302, 4, 0x3E8, (s16) 1);
            actor->unk2FA = (s16) rot->y;
            rot->x = actor->unk2F8;
            rot->z = actor->unk2FC;
        } else {
            actor->unk2FE = (s16) rot->x;
            actor->unk300 = (s16) rot->y;
            actor->unk302 = (s16) rot->z;
            Math_SmoothStepToS(actor + 0x2F8, actor->unk2FE, 4, 0x3E8, (s16) 1);
            Math_SmoothStepToS(actor + 0x2FC, actor->unk302, 4, 0x3E8, (s16) 1);
            actor->unk2FA = (s16) rot->y;
            rot->x = actor->unk2F8;
            rot->z = actor->unk2FC;
        }
    } else if ((limbIndex == 7) && ((actor->unk2F4 & 0x80) != 0)) {
        *dList = NULL;
    }
    return 0;
}
#else
s32 func_80B7B598(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7B598.asm")
#endif

#ifdef NON_MATCHING
// Needs to import data
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
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7B93C.asm")
#endif

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
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7BABC.asm")
#endif

#ifdef NON_EQUIVALENT
void func_80B7BEA4(Vec3f* arg0, s16 arg1, Vec3f* arg2, u8 arg3, GlobalContext* globalCtx) {
    Vec3f sp108;
    CollisionPoly* sp104;
    Mtx* sp100;
    MtxF spC0;
    MtxF sp80;
    MtxF sp40;

    sp108.x = arg0->x;
    sp108.y = arg0->y + 1.0f;
    sp108.z = arg0->z;
    if (sp104 != 0) {
        func_800C0094(sp104, arg0->x, func_800C4000(globalCtx, &globalCtx->colCtx, &sp104, &sp108), arg0->z, (MtxF* ) &spC0);
    } else {
        SkinMatrix_SetTranslate(&spC0, arg0->x, arg0->y, arg0->z);
    }

    SkinMatrix_MulYRotation( &spC0, arg1);
    SkinMatrix_SetScale(&sp80, arg2->x, 1.0f, arg2->z);
    SkinMatrix_MtxFMtxFMult(&spC0, &sp80, &sp40);

    sp100 = SkinMatrix_MtxFToNewMtx(globalCtx->state.gfxCtx, &sp40);
    if (sp100 != NULL) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        /*
        temp_s0 = globalCtx->state.gfxCtx;
        temp_v0_2 = temp_s0->polyOpa.p;
        temp_s0->polyOpa.p = temp_v0_2 + 8;
        temp_v0_2->words.w1 = (u32) &D_801D1DE0;
        temp_v0_2->words.w0 = 0xDA380003;
        */
        gSPMatrix(POLY_OPA_DISP++, &D_801D1DE0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        sp100 = sp100;
        /*
        temp_s0->polyOpa.p = Gfx_CallSetupDL(temp_s0->polyOpa.p, 0x2CU);
        temp_v0_3 = temp_s0->polyOpa.p;
        temp_s0->polyOpa.p = temp_v0_3 + 8;
        temp_v0_3->words.w0 = 0xFA000000;
        */
        POLY_OPA_DISP = Gfx_CallSetupDL(POLY_OPA_DISP, 0x2C);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);

        /*
        temp_v0_3->words.w1 = (u32) arg3;
        temp_v0_4 = temp_s0->polyOpa.p;
        temp_s0->polyOpa.p = temp_v0_4 + 8;
        temp_v0_4->words.w1 = (u32) sp100;
        temp_v0_4->words.w0 = 0xDA380003;
        */
        gSPMatrix(POLY_OPA_DISP++, sp100, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        /*
        temp_v0_5 = temp_s0->polyOpa.p;
        temp_s0->polyOpa.p = temp_v0_5 + 8;
        temp_v0_5->words.w1 = 0x04075A40;
        temp_v0_5->words.w0 = 0xDE000000;
        */
        gSPDisplayList(POLY_OPA_DISP++, D_04075A40);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
#else
void func_80B7BEA4(Vec3f* arg0, s16 arg1, Vec3f* arg2, u8 arg3, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7BEA4.asm")
#endif

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
