#include "z_en_fg.h"

#define FLAGS 0x00004209

#define THIS ((EnFg*)thisx)

void EnFg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFg_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A2D778(EnFg* this, GlobalContext* globalCtx);
void func_80A2D9CC(EnFg* this, GlobalContext* globalCtx);
void func_80A2D9DC(EnFg* this, GlobalContext* globalCtx);
void EnFg_AddDust(EnFgEffectDust* dustEffect, Vec3f* worldPos);
void EnFg_UpdateDust(EnFgEffectDust* dustEffect);
void EnFg_DrawDust(GlobalContext* globalCtx, EnFgEffectDust* dustEffect);

extern u64 D_0408F7E0[]; 
extern u64 D_0408F3E0[]; 
extern u64 D_0408EFE0[]; 
extern u64 D_0408EBE0[]; 
extern u64 D_0408E7E0[]; 
extern u64 D_0408E3E0[]; 
extern u64 D_0408DFE0[]; 
extern u64 D_0408DBE0[];
extern AnimationHeader D_06001534;
extern AnimationHeader D_060011C0;
extern AnimationHeader D_060007BC;
extern Gfx* D_060059A0[];
extern Gfx* D_0600B328[];
extern Gfx* D_0600B338[];
extern SkeletonHeader D_0600B538;

const ActorInit En_Fg_InitVars = {
    ACTOR_EN_FG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_FR,
    sizeof(EnFg),
    (ActorFunc)EnFg_Init,
    (ActorFunc)EnFg_Destroy,
    (ActorFunc)EnFg_Update,
    (ActorFunc)EnFg_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x000010AA, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 8, 10, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit2 = {
    1, 0, 0, 0, MASS_IMMOVABLE,
};

static DamageTable sDamageTable = {
    0x00, 0x11, 0x00, 0x01, 0x00, 0xE1, 0x11, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static EnFgAnimation sAnimations[] = {
    { &D_06001534, 1.0f, -1, 0, 0, 0 },
    { &D_06001534, 1.0f, -1, 0, 0, -4 },
    { &D_060011C0, 1.0f, -1, 0, 0, -4 },
    { &D_060007BC, 1.0f, -1, 0, 2, -4 },
};

s32 func_80A2D280(SkelAnime* skelAnime, s16 animIndex) {
    s16 frameCount;
    s32 ret = false;

    if (animIndex >= 0 && animIndex < 4) {
        ret = true;
        frameCount = sAnimations[animIndex].frameCount;
        if (frameCount < 0) {
            frameCount = SkelAnime_GetFrameCount((GenericAnimationHeader*)&sAnimations[animIndex].animationSeg);
        }
        SkelAnime_ChangeAnim(skelAnime, sAnimations[animIndex].animationSeg, sAnimations[animIndex].playbackSpeed,
                                sAnimations[animIndex].frame, frameCount, sAnimations[animIndex].mode,
                                sAnimations[animIndex].transitionRate);
    }
    return ret;
}

void func_80A2D348(EnFg* this, GlobalContext* globalCtx) {
    if (this->actor.colChkInfo.health != 0) {
        this->collider.dim.pos.x = this->actor.world.pos.x;
        this->collider.dim.pos.y = this->actor.world.pos.y;
        this->collider.dim.pos.z = this->actor.world.pos.z; 
        CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
    }
}

void func_80A2D3D4(EnFg* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
}

u8 func_80A2D400(EnFg* this) {
    if (this->actor.colChkInfo.damage >= this->actor.colChkInfo.health) {
        this->actor.colChkInfo.health = 0;
    } else {
        this->actor.colChkInfo.health = this->actor.colChkInfo.health - this->actor.colChkInfo.damage;
    }
    return this->actor.colChkInfo.health;
}

s32 func_80A2D42C(EnFg* this) {
    s32 ret = 0;

    if (this->collider.base.acFlags & 2) {
        switch (this->actor.colChkInfo.damageEffect) {
            case 1:
                ret = 2;
                break;
            case 15:
                ret = 3;
                break;
            case 14:
                ret = 4;
                break;
            case 3:
                ret = 5;
                break;
            default:
                ret = 1;
                break;
        }
        this->collider.base.acFlags &= ~2;
        func_80A2D400(this);
    }
    return ret; 
}

void func_80A2D4B8(EnFg* this, GlobalContext* globalCtx) {
    Actor* ac;
    s16 rotY;
    s16 rotX;

    switch (func_80A2D42C(this)) {
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
            this->actor.scale.x = fabsf(0.01f * Math_CosS(rotY));
            this->actor.scale.y = fabsf(0.01f * Math_CosS(rotX));
            this->actor.scale.z = fabsf(0.01f * Math_SinS(rotY));
            this->actor.scale.x = CLAMP_MIN(this->actor.scale.x, 0.001f);
            this->actor.scale.y = CLAMP_MIN(this->actor.scale.y, 0.001f);
            this->actor.scale.z = CLAMP_MIN(this->actor.scale.z, 0.001f);
            this->actionFunc = func_80A2D9CC;
            break;
        case 1:
            if(1) {}
            this->actor.flags &= ~1;
            Audio_PlayActorSound2(this, 0x28E3);
            this->actor.params = 5;
            this->skelAnime.animPlaybackSpeed = 0.0f;
            ac = this->collider.base.ac;
            this->actor.world.rot.y = Math_Vec3f_Yaw(&ac->world.pos, &this->actor.world.pos);
            this->actor.shape.rot = this->actor.world.rot;
            this->actor.velocity.y = 10.0f;
            this->actor.speedXZ = 3.0f;
            this->actor.gravity = -0.8f;
            this->unk_2FA = 1;
            this->timer = 0;
            this->actionFunc = func_80A2D9DC;
            break;
        default:
            if (DECR(this->timer) == 0) {
                Audio_PlayActorSound2(this, 0x28B1);
                func_80A2D280(&this->skelAnime, 3);
                this->actor.velocity.y = 10.0f;
                this->timer = Rand_S16Offset(30, 30);
                this->actionFunc = func_80A2D778;
            }
    }
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void func_80A2D778(EnFg* this, GlobalContext* globalCtx) {
    Actor* ac;
    s32 pad;
    s16 rotY;
    s16 rotX;

    switch (func_80A2D42C(this)) {
        case 4:
            this->actor.flags &= ~1;
            this->skelAnime.animPlaybackSpeed = 0.0f;
            ac = this->collider.base.ac;
            rotY = ac->world.rot.y;
            rotX = ac->world.rot.x;
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
            ac = this->collider.base.ac;
            this->actor.world.rot.y = Math_Vec3f_Yaw(&ac->world.pos, &this->actor.world.pos);
            this->actor.shape.rot = this->actor.world.rot;
            this->actor.velocity.y = 10.0f;
            this->actor.speedXZ = 3.0f;
            this->actor.gravity = -0.8f;
            this->unk_2FA = 1;
            this->timer = 0;
            this->actionFunc = func_80A2D9DC;
            break;
        default:
            if (func_801378B8(&this->skelAnime, 8.0f)) {
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

void func_80A2D9CC(EnFg* this, GlobalContext* globalCtx) {
}

void func_80A2D9DC(EnFg* this, GlobalContext* globalCtx) {
    if ((this->actor.velocity.y <= 0.0f) && (this->actor.bgCheckFlags & 1)) {
        this->unk_2FA++;
        if (this->unk_2FA < 4) {
            this->actor.shape.rot.x += 0x1000;
            this->actor.velocity.y = 10.0f / this->unk_2FA;
        } else {
            this->actionFunc = func_80A2D9CC;
        }
    } else {
        if (this->actor.bgCheckFlags & 8) {
            this->actor.world.rot.y = this->actor.wallYaw;
            this->actor.shape.rot = this->actor.world.rot;
        }

        if (DECR(this->timer) == 0) {
            EnFg_AddDust(&this->dustEffect[0], &this->actor.world.pos);
        }
        this->actor.shape.rot.x += 0x1000;
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    }
}

void EnFg_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFg* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 10.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600B538, NULL, this->limbDrawTbl, this->transitionDrawTbl, 24);
    func_80A2D280(&this->skelAnime, 0);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit2);
    this->actor.flags |= 0x4000;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.gravity = -1.6f;
    this->actionFunc = func_80A2D4B8;
}

void EnFg_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnFg* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

#ifdef NON_MATCHING
void EnFg_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFg* this = THIS;

    // Both "> 1" should be "> 0" to be equivalent, but loses the xor in the assembly. 
    // xor typically involes a negation of the > sign, can't pinpoint the matching.
    if (((this->actor.flags & 0x2000 ^ 0x2000) > 1) && ((this->actor.flags & 0x8000 ^ 0x8000) > 1)) {
        this->actionFunc(this, globalCtx);
        func_800B78B8(globalCtx, &this->actor, BASE_REG(16, 0), BASE_REG(16, 1), 0.0f, 5);
    }

    func_80A2D3D4(this, globalCtx);
    EnFg_UpdateDust(&this->dustEffect);
    func_80A2D348(this, globalCtx);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fg_0x80A2D280/EnFg_Update.asm")
#endif

s32 EnFg_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, EnFg* this) {
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

void EnFg_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
    EnFg* this = THIS;
    s16 pad;
    Vec3f vec1 = { 0.0f, 0.0f, 0.0f };
    
    if ((limbIndex == 7) || (limbIndex == 8)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        Matrix_Push();
        SysMatrix_NormalizeXYZ(&globalCtx->unk187FC);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, *dList);
        Matrix_Pop();
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }

    if (limbIndex == 4) {
        SysMatrix_MultiplyVector3fByState(&vec1, &this->actor.focus.pos);
    }
} 

void EnFg_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnFg* this = THIS;
    s32 pad;
    Color_RGBA8 envColor[] = {
        { 200, 170, 0, 255 },   { 0, 170, 200, 255 },   { 210, 120, 100, 255 },
        { 120, 130, 230, 255 }, { 190, 190, 190, 255 }, { 0, 0, 0, 255 },
    };

    Matrix_Push();
    EnFg_DrawDust(globalCtx, &this->dustEffect[0]);
    Matrix_Pop();

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetEnvColor(POLY_OPA_DISP++, envColor[this->actor.params].r, envColor[this->actor.params].g, envColor[this->actor.params].b, envColor[this->actor.params].a);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(&D_060059A0));
    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(&D_060059A0));
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, EnFg_OverrideLimbDraw, EnFg_PostLimbDraw, &this->actor);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnFg_AddDust(EnFgEffectDust* dustEffect, Vec3f* worldPos) {
    Vec3f vel = { 0.0f, 3.0f, 0.0f };
    Vec3f unk_20 = { 0.0f, 0.0f, 0.0f };
    s32 i;

    for (i = 0; i < 10; i++, dustEffect++) {
        if (!dustEffect->type) {
            dustEffect->type = true;
            dustEffect->timer = 16;
            dustEffect->pos = *worldPos;
            dustEffect->velocity = vel;
            dustEffect->unk_20 = unk_20;
            dustEffect->xyScale = 0.4f;
            break;
        }
    }
}

void EnFg_UpdateDust(EnFgEffectDust* dustEffect) {
    s32 i;
    
    for (i = 0; i < 10; i++, dustEffect++) {
        if (dustEffect->type) {
            if (DECR(dustEffect->timer) == 0) {
                dustEffect->type = false;
            } 
            dustEffect->pos.y += dustEffect->velocity.y;
        }
    }
}

u64* sDustTex[] = {
    D_0408F7E0, D_0408F3E0, D_0408EFE0, D_0408EBE0, D_0408E7E0, D_0408E3E0, D_0408DFE0, D_0408DBE0,
};

void EnFg_DrawDust(GlobalContext* globalCtx, EnFgEffectDust* dustEffect) {
    s16 i;
    s16 alpha;
    s16 index;
    s16 firstDone = false; 

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    for (i = 0; i < 10; i++, dustEffect++) {
        if (dustEffect->type) {
            if (!firstDone) {
                POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 0);
                gSPDisplayList(POLY_XLU_DISP++, D_0600B328);
                gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, 0);
                firstDone = true;
            }

            if (1) {}
            alpha =  (255.0f / 16.0f) * dustEffect->timer;
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 0, 0, 0, alpha);
            gDPPipeSync(POLY_XLU_DISP++);
            SysMatrix_InsertTranslation(dustEffect->pos.x, dustEffect->pos.y, dustEffect->pos.z, MTXMODE_NEW);
            SysMatrix_NormalizeXYZ(&globalCtx->unk187FC);
            Matrix_Scale(dustEffect->xyScale, dustEffect->xyScale, 1.0f, MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            index = 0.5f * dustEffect->timer;
            gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(sDustTex[index]));
            gSPDisplayList(POLY_XLU_DISP++, D_0600B338);
        }
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
