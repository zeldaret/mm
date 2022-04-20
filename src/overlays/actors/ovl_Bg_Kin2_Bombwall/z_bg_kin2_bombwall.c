/*
 * File: z_bg_kin2_bombwall.c
 * Overlay: ovl_Bg_Kin2_Bombwall
 * Description: Ocean Spider House - Bombable Wall
 */
#include "z_bg_kin2_bombwall.h"

#define FLAGS 0x10000010
#define THIS ((BgKin2Bombwall*)thisx)

void BgKin2Bombwall_Init(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Bombwall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Bombwall_Update(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Bombwall_Draw(Actor* thisx, GlobalContext* globalCtx);
#if 0
const ActorInit Bg_Kin2_Bombwall_InitVars = {
    ACTOR_BG_KIN2_BOMBWALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KIN2_OBJ,
    sizeof(BgKin2Bombwall),
    (ActorFunc)BgKin2Bombwall_Init,
    (ActorFunc)BgKin2Bombwall_Destroy,
    (ActorFunc)BgKin2Bombwall_Update,
    (ActorFunc)BgKin2Bombwall_Draw,
};
// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B6E6F0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000008, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 60, 60, 0, { 0, 0, 0 } },
};
// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B6E748[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};
#endif
extern UNK_TYPE D_06000128;
extern UNK_TYPE D_06000360;
extern UNK_TYPE D_06000490;
extern ColliderCylinderInit D_80B6E6F0;
extern InitChainEntry D_80B6E748[];

//from func_80B6E090 :
extern Color_RGBA8 D_80B6E71C;
extern Color_RGBA8 D_80B6E720;
extern Vec3f D_80B6E724;
extern s8 D_80B6E730;
extern s8 D_80B6E735; //? type before
extern s8 D_80B6E738; //? type before

//from Draw function :
extern Gfx D_060002C0;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/func_80B6E020.s")

s32 func_80B6E020(BgKin2Bombwall *arg0, GlobalContext *arg1) {
    Actor *temp_v0;

    if ((arg0->unk15C.base.acFlags & 2) != 0) {
        temp_v0 = arg0->unk15C.base.ac;
        if ((temp_v0 != 0) && (Math3D_Vec3fDistSq(&arg0->actor.world.pos, &temp_v0->world.pos) < 6400.0f)) {
            return 1;
        }
    }
    return 0;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/func_80B6E090.s")
void func_80B6E090(BgKin2Bombwall *arg0, GlobalContext *arg1) { //100-e8 = 0x18 too few allocated on stack
    BgKin2Bombwall *this = arg0;
    GlobalContext *globalCtx = arg1;
    Vec3f spF0; //size: 3 floats = 3 times 4 = 0xC bytes
    Vec3f spE4;
    f32 spE0;
    f32 spDC; //unused, only assigned value to.
    f32 spD8; 
    f32 spD4;  //unused, only assigned value to.
    f32 spD0; //unused, only assigned value to.
    f32 spCC;
    s32 spAC;
    Vec3f *temp_s5;
    s32 temp_a0;
    s32 phi_s0; //s0
    s32 phi_s1;
    s32 temp_s2;
    s32 temp_s3;
    s8 *temp_s4;
    s32 phi_v0;
    s8 *phi_s4; //$f6 that should be $f16
    //s32 phi_s3; //confirmed fake
    
    s32 phi_s0_2;

    Matrix_RotateY(this->actor.shape.rot.y, 0); //s6 should be actor.
    temp_s5 = &spF0;
    phi_v0 = 0;
    temp_s3 = 0;
    
    do {
        temp_a0 = phi_v0 + 1; //result should go into a0.
        spAC = temp_a0; //should be stored into a0 for next function.
        phi_s4 = &D_80B6E730;
loop_2:
        temp_s3 = (temp_s3 + 1) & 7;
        spD8 = (f32) ((Rand_Next() >> 0x1C) + *phi_s4); //spD8 should be $f6?
        spD8 = ((Rand_ZeroOne() - 0.5f) * 15.0f) + ((f32) temp_a0 * 15.0f);  //temp_a0 should be $f22
        //should be sub.s $f18,$f0,$f20
        //should be mul.s $f4,$f18,$f24
        //should be add.s $f6,$f4,$f22
        spD8 = (Rand_ZeroOne() * 20.0f) - 10.0f;//must find $f10 (is spD8 for now)
        spCC = (2.0f * (Rand_ZeroOne() - 0.5f)) + (spD8 * 0.018461538f);//must find $f10.
        spD0 = (Rand_ZeroOne() * 7.0f) + 4.0f;
        spD4 = spE0 * 0.3f;
        Matrix_MultiplyVector3fByState((Vec3f *) &spD8, temp_s5);
        Matrix_MultiplyVector3fByState((Vec3f *) &spCC, &spE4);
        //spF0 = (bitwise f32) spF0 + arg0->actor.world.pos.x;
        spF0.x += this->actor.world.pos.x; //guessed
        spF0.y += this->actor.world.pos.y;
        spF0.z += this->actor.world.pos.z;
        //phi_s3 = temp_s3;
        //phi_s3 = temp_s3;
        if ((Rand_Next() & 3) == 0) {
            phi_s0_2 = 0x20;
        } else {
            phi_s0_2 = 0x40;
        }
        phi_s0 = phi_s0_2;
        if ((temp_s3 < 2) || (phi_s1 = 0, (Rand_Next() > 0))) {
            temp_s2 = (temp_s2 | 1);//Rand_Next();
            phi_s0 =  (s32) (s16) (phi_s0_2 | 1);
            // phi_s0 = (s32) (s16) (phi_s0_2 | 1);q
            func_800B0E48(globalCtx, temp_s5, &D_801D15B0, &D_80B6E724, &D_80B6E71C, &D_80B6E720, 
                            (s16) (((u32) temp_s2 >> 0x1B) + 0x46), 
                            (s16) ((Rand_Next() >> 0x1A) + 0x3C));
            
            phi_s1 = 1;
        }
        EffectSsKakera_Spawn(globalCtx, temp_s5, &spE4, temp_s5, (s16) -0x226, (s16) phi_s0, (s16) 0x1E, (s16) 0, (s16) 0, (s16) (s32) *(&D_80B6E738 + (temp_s3 * 2)), (s16) phi_s1, (s16) 0, 0x32, (s16) -1, (s16) 0x1F5, (Gfx *) &D_06000128);
        temp_s4 = phi_s4 + 1;
        phi_s4 = temp_s4;
        if (temp_s4 != &D_80B6E735) {
            goto loop_2;
        }
        phi_v0 = spAC;
    } while (spAC != 6);
}
// void func_80B6E090(BgKin2Bombwall *arg0, GlobalContext *arg1) {
//     Vec3f spF0;
//     Vec3f spE4;
//     f32 spE0;
//     f32 spDC;
//     f32 spD8;
//     f32 spD4;
//     f32 spD0;
//     f32 spCC;
//     s32 spAC;
//     Vec3f *temp_s5;
//     s32 temp_a0;
//     s32 temp_s2;
//     s32 temp_s3;
//     s8 *temp_s4;
//     s32 phi_v0;
//     s8 *phi_s4;
//     s32 phi_s3;
//     s32 phi_s0;
//     s32 phi_s1;
//     s32 phi_s0_2;

//     Matrix_RotateY(arg0->actor.shape.rot.y, 0);
//     temp_s5 = &spF0;
//     phi_v0 = 0;
//     phi_s3 = 0;
//     do {
//         temp_a0 = phi_v0 + 1;
//         spAC = temp_a0;
//         phi_s4 = &D_80B6E730;
// loop_2:
//         temp_s3 = (phi_s3 + 1) & 7;
//         spD8 = (f32) ((Rand_Next() >> 0x1C) + *phi_s4);
//         spDC = ((Rand_ZeroOne() - 0.5f) * 15.0f) + ((f32) temp_a0 * 15.0f);
//         spE0 = (Rand_ZeroOne() * 20.0f) - 10.0f;
//         spCC = (2.0f * (Rand_ZeroOne() - 0.5f)) + (spD8 * 0.018461538f);
//         spD0 = (Rand_ZeroOne() * 7.0f) + 4.0f;
//         spD4 = spE0 * 0.3f;
//         Matrix_MultiplyVector3fByState((Vec3f *) &spD8, temp_s5);
//         Matrix_MultiplyVector3fByState((Vec3f *) &spCC, &spE4);
//         // spF0 = (bitwise f32) spF0 + arg0->actor.world.pos.x;
//         spF0.x += arg0->actor.world.pos.x; //guessed
//         spF0.y += arg0->actor.world.pos.y;
//         spF0.z += arg0->actor.world.pos.z;
//         phi_s3 = temp_s3;
//         phi_s3 = temp_s3;
//         if ((Rand_Next() & 3) == 0) {
//             phi_s0_2 = 0x20;
//         } else {
//             phi_s0_2 = 0x40;
//         }
//         phi_s0 = phi_s0_2;
//         if ((temp_s3 < 2) || (phi_s1 = 0, (Rand_Next() > 0))) {
//             temp_s2 = Rand_Next();
//             func_800B0E48(arg1, temp_s5, &D_801D15B0, &D_80B6E724, &D_80B6E71C, &D_80B6E720, (s16) (((u32) temp_s2 >> 0x1B) + 0x46), (s16) ((Rand_Next() >> 0x1A) + 0x3C));
//             phi_s0 = (s32) (s16) (phi_s0_2 | 1);
//             phi_s1 = 1;
//         }
//         EffectSsKakera_Spawn(arg1, temp_s5, &spE4, temp_s5, (s16) -0x226, (s16) phi_s0, (s16) 0x1E, (s16) 0, (s16) 0, (s16) (s32) *(&D_80B6E738 + (temp_s3 * 2)), (s16) phi_s1, (s16) 0, 0x32, (s16) -1, (s16) 0x1F5, (Gfx *) &D_06000128);
//         temp_s4 = phi_s4 + 1;
//         phi_s4 = temp_s4;
//         if (temp_s4 != &D_80B6E735) {
//             goto loop_2;
//         }
//         phi_v0 = spAC;
//     } while (spAC != 6);
// }
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/BgKin2Bombwall_Init.s")
    
void func_80B6E4B8(BgKin2Bombwall *);                  /* extern */

void BgKin2Bombwall_Init(Actor *thisx, GlobalContext *globalCtx) {
    BgKin2Bombwall *this = (BgKin2Bombwall *) thisx;
    ColliderCylinder *sp24;
    //ColliderCylinder *temp_a1;
    
    Actor_ProcessInitChain(&this->actor, D_80B6E748);
    DynaPolyActor_Init((DynaPolyActor *) this, 0);
    sp24 = &this->unk15C;
    //sp24 = temp_a1;
    Collider_InitCylinder(globalCtx, sp24);
    if (Flags_GetSwitch(globalCtx, this->actor.params & 0x7F) != 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    DynaPolyActor_LoadMesh(globalCtx, (DynaPolyActor *) this, (CollisionHeader *) &D_06000490);
    Collider_SetCylinder(globalCtx, sp24, &this->actor, &D_80B6E6F0);
    Collider_UpdateCylinder(&this->actor, sp24);
    Actor_SetHeight(&this->actor, 60.0f);
    func_80B6E4B8(this);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/BgKin2Bombwall_Destroy.s")
void BgKin2Bombwall_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    DynaCollisionContext *temp_a1;
    GlobalContext *temp_a0;
    BgKin2Bombwall *this = (BgKin2Bombwall *) thisx;

    temp_a0 = globalCtx;
    temp_a1 = &globalCtx->colCtx.dyna;
    globalCtx = globalCtx;
    DynaPoly_DeleteBgActor(temp_a0, temp_a1, this->unk_144[0]);
    Collider_DestroyCylinder(globalCtx, &this->unk15C);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/func_80B6E4B8.s")
void func_80B6E4CC(BgKin2Bombwall *, GlobalContext *); /* extern */

void func_80B6E4B8(BgKin2Bombwall *arg0) {
    arg0->actionFunc = func_80B6E4CC;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/func_80B6E4CC.s")

s32 func_80B6E020(BgKin2Bombwall *, GlobalContext *); /* extern */
void func_80B6E544(BgKin2Bombwall *);                  /* extern */ //was ? return type at first

void func_80B6E4CC(BgKin2Bombwall *arg0, GlobalContext *arg1) {
    BgKin2Bombwall *temp_a0;
    s8 temp_a0_2;

    temp_a0 = arg0;
    arg0 = arg0;
    if (func_80B6E020(temp_a0, arg1) != 0) {
        temp_a0_2 = arg0->actor.cutscene;
        arg0->unk15C.base.acFlags &= 0xFFFD;
        arg0 = arg0;
        ActorCutscene_SetIntentToPlay((s16) temp_a0_2);
        func_80B6E544(arg0);
        return;
    }
    CollisionCheck_SetAC(arg1, &arg1->colChkCtx, &arg0->unk15C.base);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/func_80B6E544.s")
void func_80B6E558(BgKin2Bombwall *, GlobalContext *); /* extern */

void func_80B6E544(BgKin2Bombwall *arg0) {
    arg0->actionFunc = func_80B6E558;
}
// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/func_80B6E558.s")
void func_80B6E090(BgKin2Bombwall *, GlobalContext *); /* extern */ //was ? return type before.
void func_80B6E5F8(BgKin2Bombwall *);                  /* extern */ //was ? return type before.

void func_80B6E558(BgKin2Bombwall *arg0, GlobalContext *arg1) {
    if (ActorCutscene_GetCanPlayNext((s16) arg0->actor.cutscene) != 0) {
        ActorCutscene_StartAndSetUnkLinkFields((s16) arg0->actor.cutscene, &arg0->actor);
        Actor_SetSwitchFlag(arg1, arg0->actor.params & 0x7F);
        Audio_PlaySoundAtPosition(arg1, &arg0->actor.world.pos, 0x3C, 0x2810U);
        func_800C62BC(arg1, &arg1->colCtx.dyna, arg0->unk_144[0]);
        arg0->actor.draw = NULL;
        func_80B6E090(arg0, arg1);
        func_80B6E5F8(arg0);
        return;
    }
    ActorCutscene_SetIntentToPlay((s16) arg0->actor.cutscene);
}
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/func_80B6E5F8.s")

void func_80B6E614(BgKin2Bombwall *, GlobalContext *); /* extern */

void func_80B6E5F8(BgKin2Bombwall *arg0) {
    arg0->unk_1AC[0] = 0x28;
    arg0->actionFunc = func_80B6E614;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/func_80B6E614.s")

void func_80B6E614(BgKin2Bombwall *arg0, GlobalContext *arg1) {
    s8 temp_a0;

    arg0->unk_1AC[0] += -1;//-1
    if ((s32) arg0->unk_1AC[0] <= 0) {
        temp_a0 = arg0->actor.cutscene;
        arg0 = arg0;
        ActorCutscene_Stop((s16) temp_a0);
        Actor_MarkForDeath(&arg0->actor);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/BgKin2Bombwall_Update.s")

void BgKin2Bombwall_Update(Actor *thisx, GlobalContext *globalCtx) {
    BgKin2Bombwall *this = (BgKin2Bombwall *) thisx;
    this->actionFunc(this, globalCtx);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/BgKin2Bombwall_Draw.s")

void BgKin2Bombwall_Draw(Actor *thisx, GlobalContext *globalCtx) {
    BgKin2Bombwall *this = (BgKin2Bombwall *) thisx;
    func_800BDFC0(globalCtx, (Gfx *) &D_06000360);
    func_800BE03C(globalCtx, &D_060002C0);
}

