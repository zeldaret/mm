/*
 * File: z_en_fg.c
 * Overlay: ovl_En_Fg
 * Description: Likely beta frogs, a version where they were all enemies
 */

#include "z_en_fg.h"
#include "objects/object_fr/object_fr.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_200 | ACTOR_FLAG_4000)

#define THIS ((EnFg*)thisx)

void EnFg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFg_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnFg_Jump(EnFg* this, GlobalContext* globalCtx);
void EnFg_DoNothing(EnFg* this, GlobalContext* globalCtx);
void EnFg_Knockback(EnFg* this, GlobalContext* globalCtx);
void EnFg_AddDust(EnFgEffectDust* dustEffect, Vec3f* worldPos);
void EnFg_UpdateDust(EnFgEffectDust* dustEffect);
void EnFg_DrawDust(GlobalContext* globalCtx, EnFgEffectDust* dustEffect);

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
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x1),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0x1),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(0, 0x0),
    /* Sword          */ DMG_ENTRY(0, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(0, 0x0),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(0, 0x0),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
    /* Zora punch     */ DMG_ENTRY(0, 0x0),
    /* Spin attack    */ DMG_ENTRY(0, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};

static AnimationInfoS sAnimations[] = {
    { &object_fr_Anim_001534, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_fr_Anim_001534, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_fr_Anim_0011C0, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_fr_Anim_0007BC, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
};

s32 EnFg_UpdateAnimation(SkelAnime* skelAnime, s16 animIndex) {
    s16 frameCount;
    s32 ret;

    ret = false;
    if (animIndex >= 0 && animIndex < 4) {
        ret = true;
        frameCount = sAnimations[animIndex].frameCount;
        if (frameCount < 0) {
            frameCount = Animation_GetLastFrame(sAnimations[animIndex].animation);
        }
        Animation_Change(skelAnime, sAnimations[animIndex].animation, sAnimations[animIndex].playSpeed,
                         sAnimations[animIndex].startFrame, frameCount, sAnimations[animIndex].mode,
                         sAnimations[animIndex].morphFrames);
    }
    return ret;
}

void func_80A2D348(EnFg* this, GlobalContext* globalCtx) {
    if (this->actor.colChkInfo.health != 0) {
        this->collider.dim.pos.x = this->actor.world.pos.x;
        this->collider.dim.pos.y = this->actor.world.pos.y;
        this->collider.dim.pos.z = this->actor.world.pos.z;
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void func_80A2D3D4(EnFg* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
}

u8 EnFg_UpdateHealth(EnFg* this) {
    if (this->actor.colChkInfo.damage >= this->actor.colChkInfo.health) {
        this->actor.colChkInfo.health = 0;
    } else {
        this->actor.colChkInfo.health -= this->actor.colChkInfo.damage;
    }
    return this->actor.colChkInfo.health;
}

s32 EnFg_GetDamageEffect(EnFg* this) {
    s32 ret = 0;

    if (this->collider.base.acFlags & AC_HIT) {
        switch (this->actor.colChkInfo.damageEffect) {
            case 1:
                ret = FG_DMGEFFECT_DEKUSTICK;
                break;
            case 15:
                ret = FG_DMGEFFECT_HOOKSHOT;
                break;
            case 14:
                ret = FG_DMGEFFECT_ARROW;
                break;
            case 3:
                ret = FG_DMGEFFECT_ICEARROW;
                break;
            default:
                ret = FG_DMGEFFECT_EXPLOSION;
                break;
        }
        this->collider.base.acFlags &= ~AC_HIT;
        EnFg_UpdateHealth(this);
    }
    return ret;
}

void EnFg_Idle(EnFg* this, GlobalContext* globalCtx) {
    Actor* ac;
    s16 rotY;
    s16 rotX;

    switch (EnFg_GetDamageEffect(this)) {
        case FG_DMGEFFECT_DEKUSTICK:
            this->actor.flags &= ~ACTOR_FLAG_1;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FROG_CRY_1);
            this->skelAnime.playSpeed = 0.0f;
            this->actor.shape.shadowDraw = NULL;
            this->actor.scale.x *= 1.5f;
            this->actor.scale.z *= 1.5f;
            this->actor.scale.y = 0.001f;
            this->actor.world.pos.y = this->actor.floorHeight + 2.0f;
            this->actionFunc = EnFg_DoNothing;
            break;
        case FG_DMGEFFECT_HOOKSHOT:
            break;
        case FG_DMGEFFECT_ARROW:
            this->actor.flags &= ~ACTOR_FLAG_1;
            this->skelAnime.playSpeed = 0.0f;
            rotY = this->collider.base.ac->world.rot.y;
            rotX = this->collider.base.ac->world.rot.x;
            this->actor.scale.x = fabsf(0.01f * Math_CosS(rotY));
            this->actor.scale.y = fabsf(0.01f * Math_CosS(rotX));
            this->actor.scale.z = fabsf(0.01f * Math_SinS(rotY));
            this->actor.scale.x = CLAMP_MIN(this->actor.scale.x, 0.001f);
            this->actor.scale.y = CLAMP_MIN(this->actor.scale.y, 0.001f);
            this->actor.scale.z = CLAMP_MIN(this->actor.scale.z, 0.001f);
            this->actionFunc = EnFg_DoNothing;
            break;
        case FG_DMGEFFECT_EXPLOSION:
            this->actor.flags &= ~ACTOR_FLAG_1;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FROG_CRY_0);
            if (1) {}
            this->actor.params = FG_BLACK;
            this->skelAnime.playSpeed = 0.0f;
            ac = this->collider.base.ac;
            this->actor.world.rot.y = Math_Vec3f_Yaw(&ac->world.pos, &this->actor.world.pos);
            this->actor.shape.rot = this->actor.world.rot;
            this->actor.velocity.y = 10.0f;
            this->actor.speedXZ = 3.0f;
            this->actor.gravity = -0.8f;
            this->bounceCounter = 1;
            this->timer = 0;
            this->actionFunc = EnFg_Knockback;
            break;
        default:
            if (DECR(this->timer) == 0) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FROG_JUMP);
                EnFg_UpdateAnimation(&this->skelAnime, 3);
                this->actor.velocity.y = 10.0f;
                this->timer = Rand_S16Offset(30, 30);
                this->actionFunc = EnFg_Jump;
            }
    }
    Actor_MoveWithGravity(&this->actor);
}

void EnFg_Jump(EnFg* this, GlobalContext* globalCtx) {
    Actor* ac;
    s32 pad;
    s16 rotY;
    s16 rotX;

    switch (EnFg_GetDamageEffect(this)) {
        case FG_DMGEFFECT_ARROW:
            this->actor.flags &= ~ACTOR_FLAG_1;
            this->skelAnime.playSpeed = 0.0f;
            ac = this->collider.base.ac;
            rotY = ac->world.rot.y;
            rotX = ac->world.rot.x;
            this->actor.scale.x = fabsf(Math_CosS(rotY) * 0.01f);
            this->actor.scale.y = fabsf(Math_CosS(rotX) * 0.01f);
            this->actor.scale.z = fabsf(Math_SinS(rotY) * 0.01f);
            this->actor.scale.x = CLAMP_MIN(this->actor.scale.x, 0.001f);
            this->actor.scale.y = CLAMP_MIN(this->actor.scale.y, 0.001f);
            this->actor.scale.z = CLAMP_MIN(this->actor.scale.z, 0.001f);
            this->actionFunc = EnFg_DoNothing;
            break;
        case FG_DMGEFFECT_HOOKSHOT:
            break;
        case FG_DMGEFFECT_EXPLOSION:
            this->actor.flags &= ~ACTOR_FLAG_1;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FROG_CRY_0);
            EnFg_UpdateAnimation(&this->skelAnime, 0);
            this->actor.params = FG_BLACK;
            this->skelAnime.playSpeed = 0.0f;
            ac = this->collider.base.ac;
            this->actor.world.rot.y = Math_Vec3f_Yaw(&ac->world.pos, &this->actor.world.pos);
            this->actor.shape.rot = this->actor.world.rot;
            this->actor.velocity.y = 10.0f;
            this->actor.speedXZ = 3.0f;
            this->actor.gravity = -0.8f;
            this->bounceCounter = 1;
            this->timer = 0;
            this->actionFunc = EnFg_Knockback;
            break;
        default:
            if (Animation_OnFrame(&this->skelAnime, 8.0f)) {
                this->skelAnime.curFrame = 8.0f;
                this->skelAnime.playSpeed = 0.0f;
            }

            if ((this->actor.velocity.y <= 0.0f) && (this->actor.bgCheckFlags & 1)) {
                EnFg_UpdateAnimation(&this->skelAnime, 0);
                this->actionFunc = EnFg_Idle;
                this->actor.velocity.y = 0.0f;
            } else {
                Actor_MoveWithGravity(&this->actor);
            }
    }
}

void EnFg_DoNothing(EnFg* this, GlobalContext* globalCtx) {
}

void EnFg_Knockback(EnFg* this, GlobalContext* globalCtx) {
    if ((this->actor.velocity.y <= 0.0f) && (this->actor.bgCheckFlags & 1)) {
        this->bounceCounter++;
        if (this->bounceCounter < 4) {
            this->actor.shape.rot.x += 0x1000;
            this->actor.velocity.y = 10.0f / this->bounceCounter;
        } else {
            this->actionFunc = EnFg_DoNothing;
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
        Actor_MoveWithGravity(&this->actor);
    }
}

void EnFg_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFg* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 10.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_fr_Skel_00B538, NULL, this->jointTable, this->morphTable,
                       24);
    EnFg_UpdateAnimation(&this->skelAnime, 0);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit2);
    this->actor.flags |= ACTOR_FLAG_4000;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.gravity = -1.6f;
    this->actionFunc = EnFg_Idle;
}

void EnFg_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnFg* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnFg_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFg* this = THIS;
    s32 flag;
    s32 flagSet;

    flag = this->actor.flags;
    flagSet = ((flag & 0x2000) == 0x2000);
    if (1) {}
    if (!flagSet) {
        flagSet = ((flag & 0x8000) == 0x8000);
        if (1) {}
        if (!flagSet) {
            this->actionFunc(this, globalCtx);
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, BASE_REG(16, 0), BASE_REG(16, 1), 0.0f, 0x5);
        }
    }

    func_80A2D3D4(this, globalCtx);
    EnFg_UpdateDust(&this->dustEffect[0]);
    func_80A2D348(this, globalCtx);
}

s32 EnFg_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnFg* this = THIS;

    if ((limbIndex == 7) || (limbIndex == 8)) {
        *dList = NULL;
    }

    if (this->actor.colChkInfo.health == 0) {
        if ((limbIndex == 5) || (limbIndex == 9)) {
            *dList = NULL;
        }
    }
    return false;
}

void EnFg_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnFg* this = THIS;
    s16 pad;
    Vec3f vec1 = { 0.0f, 0.0f, 0.0f };

    if ((limbIndex == 7) || (limbIndex == 8)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        Matrix_StatePush();
        Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, *dList);
        Matrix_StatePop();
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }

    if (limbIndex == 4) {
        Matrix_MultiplyVector3fByState(&vec1, &this->actor.focus.pos);
    }
}

void EnFg_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnFg* this = THIS;
    s32 pad;
    Color_RGBA8 envColor[] = {
        { 200, 170, 0, 255 },   { 0, 170, 200, 255 },   { 210, 120, 100, 255 },
        { 120, 130, 230, 255 }, { 190, 190, 190, 255 }, { 0, 0, 0, 255 },
    };

    Matrix_StatePush();
    EnFg_DrawDust(globalCtx, &this->dustEffect[0]);
    Matrix_StatePop();

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetEnvColor(POLY_OPA_DISP++, envColor[this->actor.params].r, envColor[this->actor.params].g,
                   envColor[this->actor.params].b, envColor[this->actor.params].a);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(object_fr_Tex_0059A0));
    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(object_fr_Tex_0059A0));
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnFg_OverrideLimbDraw, EnFg_PostLimbDraw, &this->actor);
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
        if (dustEffect->type == true) {
            if (DECR(dustEffect->timer) == 0) {
                dustEffect->type = false;
            }
            dustEffect->pos.y += dustEffect->velocity.y;
        }
    }
}

TexturePtr sDustTex[] = {
    gDust8Tex, gDust7Tex, gDust6Tex, gDust5Tex, gDust4Tex, gDust3Tex, gDust2Tex, gDust1Tex,
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
                gSPDisplayList(POLY_XLU_DISP++, object_fr_DL_00B328);
                gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, 0);
                firstDone = true;
            }

            if (1) {}
            alpha = (255.0f / 16.0f) * dustEffect->timer;
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 0, 0, 0, alpha);
            gDPPipeSync(POLY_XLU_DISP++);
            Matrix_InsertTranslation(dustEffect->pos.x, dustEffect->pos.y, dustEffect->pos.z, MTXMODE_NEW);
            Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
            Matrix_Scale(dustEffect->xyScale, dustEffect->xyScale, 1.0f, MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            index = 0.5f * dustEffect->timer;
            gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(sDustTex[index]));
            gSPDisplayList(POLY_XLU_DISP++, object_fr_DL_00B338);
        }
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
