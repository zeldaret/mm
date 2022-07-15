/*
 * File: z_en_mkk.c
 * Overlay: ovl_En_Mkk
 * Description: Black and White Boe (Name origin: Makkurokurosuke)
 */

#include "z_en_mkk.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4)

#define THIS ((EnMkk*)thisx)

void EnMkk_Init(Actor* thisx, PlayState* play);
void EnMkk_Destroy(Actor* thisx, PlayState* play);
void EnMkk_Update(Actor* thisx, PlayState* play);
void EnMkk_Draw(Actor* thisx, PlayState* play);

void func_80A4E100(EnMkk* this, PlayState* play);
void func_80A4E1F0(EnMkk* this, PlayState* play);
void func_80A4E2E8(EnMkk* this, PlayState* play);
void func_80A4E60C(EnMkk* this, PlayState* play);
void func_80A4E72C(EnMkk* this, PlayState* play);
void func_80A4EE48(EnMkk* this, PlayState* play);
void func_80A4EF74(EnMkk* this, PlayState* play);
void func_80A4E0CC(EnMkk* this); //(EnMkk* this, s32);
void func_80A4E190(EnMkk* this);
void func_80A4E2B8(EnMkk* this);
void func_80A4E58C(EnMkk* this);
void func_80A4EDF0(EnMkk* this, s32);
void func_80A4EEF4(EnMkk* this);
void func_80A4F16C(Actor* thisx, PlayState* play);
void func_80A4F4C8(Actor* thisx, PlayState* play);
void func_80A4E67C(EnMkk* this);
void func_80A4E84C(EnMkk* this);
#if 0
const ActorInit En_Mkk_InitVars = {
    ACTOR_EN_MKK,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_MKK,
    sizeof(EnMkk),
    (ActorFunc)EnMkk_Init,
    (ActorFunc)EnMkk_Destroy,
    (ActorFunc)EnMkk_Update,
    (ActorFunc)EnMkk_Draw,
};

static s16 D_80A4F748[2] = { 0xF, 0x64 };
static Color_RGBA8 D_80A4F780 = { 0xFA, 0xFA, 0xFA, 0xFF };
static Color_RGBA8 D_80A4F784 = { 0xB4, 0xB4, 0xB4, 0xFF };
static Vec3f D_80A4F788 = { 0.0f, 0.45f, 0.0f };
static s32 D_80A4F794[2] = { 0x323232FF, 0xFFFFFFFF };
static s32 D_80A4F79C[2] = { 0xC8C8C8FF, 0xFFFFFFFF };
static struct _struct_D_80A4F7A4_0x10 D_80A4F7A4[2] = {
    { 0x06000030, 0x060000B0, (Mtx *)0x060000C8, 0x06000140 },
    { 0x060001F0, 0x06000278, (Mtx *)0x06000290, 0x06000310 },
};
static s32 D_80A4F7C4[7] = { 0xFFFFFFFF, 0x808080FF, 0xFF, 0xFF, 0x808080FF, 0xFFFFFFFF, 0 };

// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_80A4F720 = {
    { COLTYPE_HIT3, AT_NONE | AT_TYPE_ENEMY, AC_NONE | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
    { 1, { { 0, 0, 0 }, 15 }, 100 },
};

// sColChkInfoInit
static CollisionCheckInfoInit D_80A4F74C = { 1, 15, 30, 10 };

// static DamageTable sDamageTable = {
static DamageTable D_80A4F754 = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x0),
    /* Ice arrow      */ DMG_ENTRY(2, 0x0),
    /* Light arrow    */ DMG_ENTRY(2, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A4F774[] = {
    ICHAIN_F32_DIV1000(gravity, -500, ICHAIN_CONTINUE),
    ICHAIN_F32(terminalVelocity, -5, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 3000, ICHAIN_STOP),
};

#endif

extern ColliderSphereInit D_80A4F720;
extern CollisionCheckInfoInit D_80A4F74C;
extern DamageTable D_80A4F754;
extern InitChainEntry D_80A4F774[];
extern f32 D_80A4F7E0;
extern f32 D_80A4F7E4;
extern f32 D_80A4F7E8;
extern f32 D_80A4F7EC;
extern f32 D_80A4F7F0;
extern f32 D_80A4F7F4;
extern f32 D_80A4F7F8;
extern f32 D_80A4F7FC;
extern f32 D_80A4F800;
extern f32 D_80A4F804;
extern f32 D_80A4F808;
extern f32 D_80A4F80C;
extern f32 D_80A4F810;
extern f32 D_80A4F814;
extern f32 D_80A4F818;
extern f32 D_80A4F81C;
extern f32 D_80A4F820;
extern f32 D_80A4F824;
extern f32 D_80A4F828;
extern f32 D_80A4F82C;
extern f32 D_80A4F830;
extern f32 D_80A4F834;
extern f32 D_80A4F83C;
extern f32 D_80A4F840;
extern s16 D_80A4F748;
extern Vec3f D_80A4F788;
extern Color_RGBA8 D_80A4F780;
extern Color_RGBA8 D_80A4F784;
extern Color_RGBA8 D_80A4F794[];
extern Color_RGBA8 D_80A4F79C[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/EnMkk_Init.s")
/*
void EnMkk_Init(Actor *thisx, PlayState *play) {
    //s32 sp2C;
    //PosRot *sp24;
    //PosRot *temp_a1;
    //s16 temp_v0;
    //s16 temp_v0_2;
    //s16 temp_v0_3;
    s32 params2;
    s32 params8;
    u8 phi_v1;
    EnMkk *this = (EnMkk *) thisx;

    Actor_ProcessInitChain(&this->actor, D_80A4F774);
    Collider_InitAndSetSphere(play, &this->unk17C, &this->actor, &D_80A4F720);
    this->unk17C.dim.worldSphere.radius = D_80A4F748;
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &D_80A4F754, &D_80A4F74C);
    ActorShape_Init(&this->actor.shape, 1000.0f, NULL, 0.0f);
    //temp_v0 = this->actor.shape.rot.x;
    this->unk148 = 0;
    this->unk149 = 0;
    if (this->actor.shape.rot.x >= 0) {
        this->unk152 = this->actor.shape.rot.x;
    } else {
        this->unk152 = this->actor.shape.rot.x * -0x50;
    }
    //temp_v0_2 = this->actor.shape.rot.z;
    //temp_a1 = &this->actor.world;

    if (this->actor.shape.rot.z < 0) {
        this->unk14C = 0;
    } else {
        this->unk14C = this->actor.shape.rot.z;
        if (this->actor.shape.rot.z >= 0x11) {
            this->unk14C = 0x10;
        } else {
        }
            this->unk14C = this->actor.shape.rot.z;
        //this->unk14C = phi_v1;
    }
    this->actor.shape.rot.z = 0;
    this->actor.world.rot.z = 0;
    this->actor.shape.rot.x = 0;
    this->actor.world.rot.x = 0;
    //sp24 = temp_a1;
    Math_Vec3f_Copy(&this->unk154, &this->actor.world.pos);
    Math_Vec3f_Copy(&this->unk160, &this->actor.world.pos);
    if ((this->actor.params & 4) != 0) {
        this->unk14B = 8;
    } else {
        this->unk14B = 0;
    }
    //temp_v0_3 = this->actor.params;
    this->actor.params = this->actor.params & 1;
    params8 = (this->actor.params >> 8) & 0xFF;
    params2 = this->actor.params & 2;
    if (this->actor.params == 1) {
        this->actor.hintId = 0x3C;
    } else {
        this->actor.hintId = 0x2C;
    }
    if ((params8 == 0) || (params8 == 0xFF)) {
        //sp2C = params2;
        func_80A4E0CC(this, params2);
        this->unk178 = D_80A4F7E0;
        if (params2 > 0) {
            this->unk14B |= 4;
        }
    } else {
        this->unk178 = (f32) params8 * 40.0f * D_80A4F7E4;
        func_80A4EDF0(this, params2);
        this->unk14E = 0;
    }
}
*/
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/EnMkk_Destroy.s")

void EnMkk_Destroy(Actor* thisx, PlayState* play) {
    EnMkk* this = THIS;
    Collider_DestroySphere(play, &this->unk17C);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E0CC.s")

void func_80A4E0CC(EnMkk* this) {
    this->unk14A = 0;
    this->unk14B |= 3;
    this->actor.flags &= -2;
    this->actionFunc = func_80A4E100;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E100.s")

void func_80A4E100(EnMkk* this, PlayState* play) {
    s32 phi_v0;

    if ((this->unk14B & 4) != 0) {
        phi_v0 = this->unk14A + 0xF;
    } else {
        phi_v0 = this->unk14A + 5;
    }
    if (phi_v0 >= 0xFF) {
        this->unk148 = 3;
        this->unk17C.base.acFlags |= 1;
        this->unk14A = 0xFF;
        this->actor.flags |= 1;
        this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
        this->unk14B = this->unk14B & 0xFFFB;
        func_80A4E190(this);
    } else {
        this->unk14A = (u8)phi_v0;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E190.s")

void func_80A4E190(EnMkk* this) {
    this->unk14E = (s32)(Rand_ZeroOne() * 20.0f) + 0xA;
    if (this->unk149 != 0) {
        this->unk149--;
    }
    this->actionFunc = func_80A4E1F0;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E1F0.s")

void func_80A4E1F0(EnMkk* this, PlayState* play) {
    this->unk14E--;
    if (this->unk14E == 0) {
        func_80A4E2B8(this);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E22C.s")

void func_80A4E22C(EnMkk* this, PlayState* play) {
    Vec3f pos;

    pos.x = this->actor.world.pos.x;
    pos.y = this->actor.world.pos.y + 15.0f;
    pos.z = this->actor.world.pos.z;
    func_800B0DE0(play, &pos, &gZeroVec3f, &D_80A4F788, &D_80A4F780, &D_80A4F784, 0x15E, 0x14);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E2B8.s")

void func_80A4E2B8(EnMkk* this) {
    this->unk14E = 0x1E;
    this->unk150 = this->actor.shape.rot.y;
    this->unk14B = this->unk14B & 0xFFFE;
    this->actionFunc = func_80A4E2E8;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E2E8.s")

void func_80A4E2E8(EnMkk* this, PlayState* play) {
    Player* sp24 = GET_PLAYER(play);
    s32 sp20;

    this->unk14E--;
    if ((this->actor.params == 1) && (this->actor.bgCheckFlags & 1) && (this->actor.speedXZ > 2.5f) &&
        (!(play->gameplayFrames % 3))) {
        func_80A4E22C(this, play);
    }
    if (this->unk14E > 0) {
        Math_StepToF(&this->actor.speedXZ, 5.0f, 0.7f);
        sp20 = 0;
    } else {
        sp20 = Math_StepToF(&this->actor.speedXZ, 0.0f, 0.7f);
    }
    if (((sp24->stateFlags3 & 0x100)) || (Player_GetMask(play) == 0x10)) {
        Math_ScaledStepToS(&this->unk150, Actor_YawToPoint(&this->actor, &this->actor.home.pos), 0x400);
    } else if ((sp24->stateFlags2 & 0x80) || (sp24->actor.freezeTimer > 0)) {
        Math_ScaledStepToS(&this->unk150, this->actor.yawTowardsPlayer + 0x8000, 0x400);
    } else {
        Math_ScaledStepToS(&this->unk150, this->actor.yawTowardsPlayer, 0x400);
    }
    this->actor.shape.rot.y =
        (s32)(sin_rad(this->unk14E * 0.41887903f) * (614.4f * this->actor.speedXZ)) + this->unk150;
    func_800B9010(&this->actor, 0x30BC);
    if (sp20 != 0) {
        this->unk14B &= 0xFFFD;
        func_80A4E190(this);
    } else {
        if ((this->unk149 == 0) && ((sp24->stateFlags3 & 0x100) == 0) && (Player_GetMask(play) != 0x10) &&
            ((this->actor.bgCheckFlags & 1) != 0) && (Actor_IsFacingPlayer(&this->actor, 0x1800) != 0) &&
            (this->actor.xzDistToPlayer < 120.0f) && (fabsf(this->actor.playerHeightRel) < 100.0f)) {
            func_80A4E58C(this);
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E58C.s")

void func_80A4E58C(EnMkk* this) {
    this->unk14B = this->unk14B | 1;
    this->actor.speedXZ = 3.0f;
    this->actor.velocity.y = 5.0f;
    Actor_PlaySfxAtPos(this, 0x38BD);
    this->unk17C.base.atFlags = this->unk17C.base.atFlags | 1;
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x800);
    this->actionFunc = func_80A4E60C;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E60C.s")

void func_80A4E60C(EnMkk* this, PlayState* play) {
    if ((this->unk17C.base.atFlags & 2)) {
        this->unk17C.base.atFlags = (this->unk17C.base.atFlags) & 0xFFFC;
    }
    if ((this->actor.velocity.y < 0.0f) && ((this->actor.bgCheckFlags & 1))) {
        this->unk149 = 2;
        this->unk17C.base.atFlags &= 0xFFFE;
        func_80A4E2B8(this);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E67C.s")

void func_80A4E67C(EnMkk* this) {
    this->unk14B |= 1;
    this->actor.flags &= ~1;
    this->unk17C.base.acFlags &= -2;
    this->actor.flags = this->actor.flags | 0x10;
    Actor_PlaySfxAtPos(&this->actor, 0x3876);
    this->unk14A = 0xFE;
    func_800BE568(&this->actor, &this->unk17C);
    this->actor.speedXZ = 7.0f;
    this->actor.shape.rot.y = this->actor.world.rot.y;
    this->actor.velocity.y = 5.0f;
    this->actor.gravity = -1.3f;
    this->actor.bgCheckFlags &= 0xFFFE;
    this->actionFunc = func_80A4E72C;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E72C.s")
void func_80A4E72C(EnMkk* this, PlayState* play) {
    Vec3f temp;

    if ((this->actor.bgCheckFlags & 1)) {
        if (this->actor.velocity.y > -1.0f) {
            temp.x = this->actor.world.pos.x;
            temp.y = this->actor.world.pos.y + 15.0f;
            temp.z = this->actor.world.pos.z;
            EffectSsDeadDb_Spawn(play, &temp, &gZeroVec3f, &gZeroVec3f, &D_80A4F794[this->actor.params],
                                 &D_80A4F79C[this->actor.params], 0x46, 4, 0xC);
            Actor_PlaySfxAtPos(&this->actor, 0x3878);
            if (this->unk14C != 0) {
                Item_DropCollectibleRandom(play, &this->actor, &this->actor.world.pos, (this->unk14C * 0x10));
            }
            func_80A4EEF4(this);
        } else {
            this->actor.velocity.y = (f32)this->actor.velocity.y * -0.8f;
            this->actor.bgCheckFlags = this->actor.bgCheckFlags & 0xFFFE;
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E84C.s")

void func_80A4E84C(EnMkk *arg0) {
    if ((arg0->unk14B & 3) != 0) {
        Vec3f sp34;
        f32 temp_fv0 = Math_Vec3f_DistXYZ(&arg0->actor.world.pos, &arg0->actor.prevPos);
        
        Math_Vec3f_Copy(&sp34, &arg0->unk154);
        if (temp_fv0 < D_80A4F7F8) {
            Math_Vec3f_Copy(&arg0->unk154, &arg0->actor.prevPos);
        } else {
            temp_fv0 = 1.0f / temp_fv0;
            
            arg0->unk154.x = ((arg0->actor.prevPos.x - arg0->actor.world.pos.x) * temp_fv0 * 10.0f) + arg0->actor.world.pos.x;
            arg0->unk154.y = ((arg0->actor.prevPos.y - arg0->actor.world.pos.y) * temp_fv0 * 10.0f) + arg0->actor.world.pos.y;
            arg0->unk154.z = ((arg0->actor.prevPos.z - arg0->actor.world.pos.z) * temp_fv0 * 10.0f) + arg0->actor.world.pos.z;
        }
        temp_fv0 = Math_Vec3f_DistXYZ(&arg0->unk154, &sp34);
        if (temp_fv0 < D_80A4F7FC) {
            Math_Vec3f_Copy(&arg0->unk160, &sp34);
        } else {
            temp_fv0 = 1.0f / temp_fv0;
            
            arg0->unk160.x = ((sp34.x - arg0->unk154.x) * temp_fv0 * 12.0f) + arg0->unk154.x;
            arg0->unk160.y = ((sp34.y - arg0->unk154.y) * temp_fv0 * 12.0f) + arg0->unk154.y;
            arg0->unk160.z = ((sp34.z - arg0->unk154.z) * temp_fv0 * 12.0f) + arg0->unk154.z;
        }
    } else {
        arg0->unk160.y = arg0->unk154.y;
        arg0->unk154.y = arg0->actor.world.pos.y;
        arg0->unk154.x = arg0->actor.world.pos.x - 10.0f * Math_SinS(arg0->actor.shape.rot.y + (s32) (D_80A4F804 * arg0->actor.speedXZ * sin_rad(arg0->unk14E * D_80A4F800)));
        arg0->unk154.z = arg0->actor.world.pos.z - 10.0f * Math_CosS(arg0->actor.shape.rot.y + (s32) (D_80A4F80C * arg0->actor.speedXZ * sin_rad(arg0->unk14E * D_80A4F808)));
        arg0->unk160.x = arg0->unk154.x - 12.0f * Math_SinS(arg0->actor.shape.rot.y - (s32) (D_80A4F814 * arg0->actor.speedXZ * sin_rad(arg0->unk14E * D_80A4F810)));
        arg0->unk160.z = arg0->unk154.z - 12.0f * Math_CosS(arg0->actor.shape.rot.y - (s32) (D_80A4F81C * arg0->actor.speedXZ * sin_rad(arg0->unk14E * D_80A4F818)));
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4EBBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/EnMkk_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4EDF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4EE48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4EEF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4EF74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4F16C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/EnMkk_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4F4C8.s")
