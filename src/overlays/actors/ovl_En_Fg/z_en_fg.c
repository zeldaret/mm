#include "z_en_fg.h"

#define FLAGS 0x00004209

#define THIS ((EnFg*)thisx)

void EnFg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFg_Draw(Actor* thisx, GlobalContext* globalCtx);

u8 func_80A2D400(EnFg* this);
s32 func_80A2D42C(EnFg* this);

// void func_80A2D280(EnFg* this, GlobalContext* globalCtx); // wrong argument types
void func_80A2D348(EnFg* this, GlobalContext* globalCtx);
void func_80A2D3D4(EnFg* this, GlobalContext* globalCtx);
void func_80A2D4B8(EnFg* this, GlobalContext* globalCtx); // unneeded
void func_80A2D778(EnFg* this, GlobalContext* globalCtx);
void func_80A2D9CC(EnFg* this, GlobalContext* globalCtx);
void func_80A2D9DC(EnFg* this, GlobalContext* globalCtx);

// s32 func_80A2DCE0(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx);


const ActorInit En_Fg_InitVars = { ACTOR_EN_FG,
                                   ACTORCAT_NPC,
                                   FLAGS,
                                   OBJECT_FR,
                                   sizeof(EnFg),
                                   (ActorFunc)EnFg_Init,
                                   (ActorFunc)EnFg_Destroy,
                                   (ActorFunc)EnFg_Update,
                                   (ActorFunc)EnFg_Draw };  

// ColliderCylinderInit sCylinderInit
s32 D_80A2E500[] = { 0x00000939, 0x10010000, 0x01000000, 0x00000000, 0x00000000, 0x000010AA,
                     0x00000000, 0x00050100, 0x0008000A, 0x00000000, 0x00000000 };

// sColChkInfoInit2
CollisionCheckInfoInit2 D_80A2E52C[] = { 
    1, 0, 0, 0, MASS_IMMOVABLE };

// sDamageTable
DamageTable D_80A2E538[] = {
    0x00, 0x11, 0x00, 0x01, 0x00, 0xE1, 0x11, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
s32 D_80A2E558[] = { 0x06001534, 0x3F800000, 0x0000FFFF, 0x00000000, 0x06001534, 0x3F800000, 0x0000FFFF, 0x0000FFFC,
                     0x060011C0, 0x3F800000, 0x0000FFFF, 0x0000FFFC, 0x060007BC, 0x3F800000, 0x0000FFFF, 0x0200FFFC };
s32 D_80A2E598[] = { 0x00000000, 0x00000000, 0x00000000 };
s32 D_80A2E5A4[] = { 0xC8AA00FF, 0x00AAC8FF, 0xD27864FF, 0x7882E6FF, 0xBEBEBEFF, 0x000000FF };
s32 D_80A2E5BC[] = { 0x00000000, 0x40400000, 0x00000000 };
s32 D_80A2E5C8[] = { 0x00000000, 0x00000000, 0x00000000 };
s32 D_80A2E5D4[] = { 0x0408F7E0, 0x0408F3E0, 0x0408EFE0, 0x0408EBE0, 0x0408E7E0, 0x0408E3E0,
                     0x0408DFE0, 0x0408DBE0, 0x00000000, 0x00000000, 0x00000000 };

extern SkeletonHeader D_0600B538;

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2D280.asm")
// void func_80A2D280(EnFg *this, GlobalContext *globalCtx) {
//     s32 sp30;
//     void *sp2C;
//     s16 temp_a1;
//     s16 temp_t0;
//     s32 temp_t6;
//     void *temp_v1;
//     s16 phi_t0;

//     temp_a1 = (s16) globalCtx;
//     if ((s32) temp_a1 >= 0) {
//         temp_t6 = temp_a1 * 0x10;
//         if ((s32) temp_a1 < 4) {
//             temp_v1 = temp_t6 + D_80A2E558;
//             temp_t0 = temp_v1->unkA;
//             phi_t0 = temp_t0;
//             if ((s32) temp_t0 < 0) {
//                 sp2C = temp_v1;
//                 sp30 = 1;
//                 phi_t0 = SkelAnime_GetFrameCount(temp_v1->unk0);
//             }
//             sp30 = 1;
//             SkelAnime_ChangeAnim((SkelAnime *) this, (temp_t6 + D_80A2E558)->unk0, (bitwise f32) (temp_t6 + D_80A2E558)->unk4, (f32) (temp_t6 + D_80A2E558)->unk8, (f32) phi_t0, (?32) (temp_t6 + D_80A2E558)->unkC, (f32) (temp_t6 + D_80A2E558)->unkE);
//         }
//     }
// }


// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2D348.asm")
void func_80A2D348(EnFg *this, GlobalContext *globalCtx) {

    if (this->actor.colChkInfo.health != 0) {
        this->collider.dim.pos.x = this->actor.world.pos.x;
        this->collider.dim.pos.y = this->actor.world.pos.y;
        this->collider.dim.pos.z = this->actor.world.pos.z;
        CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
    }
}


// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2D3D4.asm")
void func_80A2D3D4(EnFg *this, GlobalContext *globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
}


// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2D400.asm")
u8 func_80A2D400(EnFg *this) {

    if (this->actor.colChkInfo.damage >= this->actor.colChkInfo.health) {
        this->actor.colChkInfo.health = 0;
    } else {
        this->actor.colChkInfo.health = this->actor.colChkInfo.health - this->actor.colChkInfo.damage;
    }

    return this->actor.colChkInfo.health;
}

#ifdef NON_MATCHING
s32 func_80A2D42C(EnFg* this) {
    s32 phi_v1;
    s32 retVal;

    retVal = 0;

    if (this->collider.base.acFlags & 2) {

        switch (this->actor.colChkInfo.damageEffect) {
            case 3:
                phi_v1 = 2;
                break;
            case 15:
                phi_v1 = 3;
                break;
            case 14:
                phi_v1 = 4;
                break;
            case 1:
                phi_v1 = 5;
                break;
            default:
                phi_v1 = 1;
                break;
        }

        this->collider.base.acFlags &= 2;
        func_80A2D400(this);
        retVal = phi_v1;

    }

    return retVal;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2D42C.asm")
#endif

#ifdef NON_MATCHING
void func_80A2D4B8(EnFg *this, GlobalContext *globalCtx) {
    s16 rotX;
    s16 rotY;

    switch(func_80A2D42C(this)) {

        case 2:
            this->actor.flags &= ~1;
            Audio_PlayActorSound2(this, 0x28E4);
            this->skelAnime.animPlaybackSpeed = 0.0f;
            this->actor.shape.shadowDraw = NULL;
            this->actor.scale.x *= 1.5f;
            this->actor.scale.z *= 1.5f;
            this->actor.world.pos.y = this->actor.floorHeight + 2.0f;
            this->actionFunc = func_80A2D9CC;
            this->actor.scale.y = 0.001f;
            break;

        case 3:
            break;

        case 4:
            this->actor.flags &= ~1;
            this->skelAnime.animPlaybackSpeed = 0.0f;

            rotY = this->collider.base.ac->world.rot.y;
            rotX = this->collider.base.ac->world.rot.x;

            this->actor.scale.x = fabsf(0.01f*Math_CosS(rotY));
            this->actor.scale.y = fabsf(0.01f*Math_CosS(rotX));
            this->actor.scale.z = fabsf(0.01f*Math_SinS(rotY));

            this->actor.scale.x = CLAMP_MIN(this->actor.scale.x, 0.001f);
            this->actor.scale.y = CLAMP_MIN(this->actor.scale.y, 0.001f);
            this->actor.scale.z = CLAMP_MIN(this->actor.scale.z, 0.001f);

            this->actionFunc = func_80A2D9CC;
            break;

        case 1:
            this->actor.flags &= ~1;
            Audio_PlayActorSound2(this, 0x28E3);
            this->actor.params = 5;
            this->skelAnime.animPlaybackSpeed = 0.0f;
            this->actor.world.rot.y = Math_Vec3f_Yaw(&this->collider.base.ac->world.pos, &this->actor.world.pos);
            this->actor.shape.rot = this->actor.world.rot; 
            this->actor.velocity.y = 10.0f;
            this->actor.speedXZ = 3.0f;
            this->limbDrawTbl[0].x = 0;
            this->unk_2FA = 1;
            this->actionFunc = func_80A2D9DC;
            this->actor.gravity = -0.8f;
            break;

        default:
            if (DECR(this->limbDrawTbl[0].x)) {
                Audio_PlayActorSound2(this, 0x28B1);
                func_80A2D280(&this->skelAnime, 3);
                this->actor.velocity.y = 10.0f;
                this->limbDrawTbl[0].x = Rand_S16Offset(30, 30);
                this->actionFunc = func_80A2D778;
            }

    }

    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2D4B8.asm")
#endif

#ifdef NON_MATCHING
void func_80A2D778(EnFg *this, GlobalContext *globalCtx) {
    s16 rotY;
    s16 rotX;

    switch(func_80A2D42C(this)) {
        case 4:
            this->actor.flags &= ~1;
            this->skelAnime.animPlaybackSpeed = 0.0f;

            rotY = this->collider.base.ac->world.rot.y;
            rotX = this->collider.base.ac->world.rot.x;

            this->actor.scale.x = fabsf(Math_CosS(rotY) * 0.01f);
            this->actor.scale.y = fabsf(Math_CosS(rotX) * 0.01f);
            this->actor.scale.z = fabsf(Math_SinS(rotY) * 0.01f);

            this->actor.scale.x = CLAMP_MIN(this->actor.scale.x, 0.001f);
            this->actor.scale.y = CLAMP_MIN(this->actor.scale.y, 0.001f);
            this->actor.scale.z = CLAMP_MIN(this->actor.scale.z, 0.001f);

            this->actionFunc = func_80A2D9CC;
            break;
            
        case 3:
            break;

        case 1:
            this->actor.flags &= ~1;
            Audio_PlayActorSound2(this, 0x28E3);
            func_80A2D280(&this->skelAnime, 0);
            this->actor.params = 5;
            this->skelAnime.animPlaybackSpeed = 0.0f;
            this->actor.world.rot.y = Math_Vec3f_Yaw(&this->collider.base.ac->world.pos, &this->actor.world.pos);
            this->actor.shape.rot = this->actor.world.rot;
            this->actor.velocity.y = 10.0f;
            this->actor.speedXZ = 3.0f;
            this->unk_2FA = 1;
            this->unk_2F8 = 0;
            this->actionFunc = func_80A2D9DC;
            this->actor.gravity = -0.8f;
            break;

        default:
            if (func_801378B8(&this->skelAnime, 8.0f) != 0) {
                this->skelAnime.animCurrentFrame = 8.0f;
                this->skelAnime.animPlaybackSpeed = 0.0f;
            }

            if ((this->actor.velocity.y <= 0.0f) && (this->actor.bgCheckFlags & 1)) {
                func_80A2D280(&this->skelAnime, 0);
                this->actionFunc = func_80A2D4B8;
                this->actor.velocity.y = 0.0f;
            } else {
                Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
            }
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2D778.asm")
#endif


// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2D9CC.asm")
void func_80A2D9CC(EnFg *this, GlobalContext *globalCtx) {}


// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2D9DC.asm")
void func_80A2D9DC(EnFg *this, GlobalContext *globalCtx) {

    if ((this->actor.velocity.y <= 0.0f) && (this->actor.bgCheckFlags & 1)) {
        this->unk_2FA++;
        if (this->unk_2FA < 4) {
            this->actor.shape.rot.x += 0x1000;
            this->actor.velocity.y = 10.0f / this->unk_2FA; // cast to (f32)?
        } else {
            this->actionFunc = func_80A2D9CC;
        }
    } else {
        if (this->actor.bgCheckFlags & 8) {
            this->actor.world.rot.y = this->actor.wallYaw;
            this->actor.shape.rot = this->actor.world.rot;
        }

        if (DECR(this->unk_2F8) == 0) {
            func_80A2DFC4(&this->unk_2FC, &this->actor.world, this);
        }
        this->actor.shape.rot.x += 0x1000;
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    }
}


// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/EnFg_Init.asm")
void EnFg_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFg* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 10.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600B538, NULL, &this->limbDrawTbl, &this->transitionDrawTbl, 24);
    func_80A2D280(&this->skelAnime, 0);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_80A2E500);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &D_80A2E538, &D_80A2E52C);
    this->actor.flags |= 0x4000;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.gravity = -1.6f;
    this->actionFunc = func_80A2D4B8;
}


// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/EnFg_Destroy.asm")
void EnFg_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnFg* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}


#ifdef NON_MATCHING
void EnFg_Update(Actor *thisx, GlobalContext *globalCtx) {
    EnFg* this = THIS;

    // Only need to figure out the logic of this if statement condition. Involves xor
    if (((this->actor.flags & 0x2000) != 0x2000) && ((this->actor.flags & 0x8000) != 0x8000)) {
        this->actionFunc(this, globalCtx);
        func_800B78B8(globalCtx, &this->actor, BASE_REG(16, 0), BASE_REG(16, 1), 0.0f, 5);
    }

    func_80A2D3D4(this, globalCtx);
    func_80A2E0A0(&this->unk_2FC);
    func_80A2D348(this, globalCtx);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/EnFg_Update.asm")
#endif

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2DCE0.asm")
// s32 EnFg_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
s32 func_80A2DCE0(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, EnFg *this) {
    if ((limbIndex == 7) || (limbIndex == 8)) {
        *dList = NULL;
    }
    if (this->actor.colChkInfo.health == 0) {
        if ((limbIndex == 5) || (limbIndex == 9)) {
            *dList = NULL;
        }
    }
    return 0;
}


#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2DD34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/EnFg_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2DFC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2E0A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/func_80A2E268.asm")
