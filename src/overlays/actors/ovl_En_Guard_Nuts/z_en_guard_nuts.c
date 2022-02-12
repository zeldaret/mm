/*
 * File: z_en_guard_nuts.c
 * Overlay: ovl_En_Guard_Nuts
 * Description: Deku Palace - Entrance Guard
 */

#include "z_en_guard_nuts.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_100000 | ACTOR_FLAG_80000000)

#define THIS ((EnGuardNuts*)thisx)

void EnGuardNuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGuardNuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGuardNuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGuardNuts_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnGuardNuts_ChangeAnim(EnGuardNuts* this, s32 index);
void EnGuardNuts_SetupWait(EnGuardNuts* this);
void EnGuardNuts_Wait(EnGuardNuts* this, GlobalContext* globalCtx);
void func_80ABB540(EnGuardNuts* this);
void func_80ABB590(EnGuardNuts* this, GlobalContext* globalCtx);
void EnGuardNuts_Burrow(EnGuardNuts* this, GlobalContext* globalCtx);
void EnGuardNuts_SetupUnburrow(EnGuardNuts* this, GlobalContext* globalCtx);
void EnGuardNuts_Unburrow(EnGuardNuts* this, GlobalContext* globalCtx);

const ActorInit En_Guard_Nuts_InitVars = {
    ACTOR_EN_GUARD_NUTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNK,
    sizeof(EnGuardNuts),
    (ActorFunc)EnGuardNuts_Init,
    (ActorFunc)EnGuardNuts_Destroy,
    (ActorFunc)EnGuardNuts_Update,
    (ActorFunc)EnGuardNuts_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON | OCELEM_UNK3,
    },
    { 50, 50, 0, { 0, 0, 0 } },
};

s32 D_80ABBE1C = 0;

s32 D_80ABBE20 = 0;

static u16 sTextIDs[] = { 0x0824, 0x0825, 0x0826, 0x082D, 0x0827, 0x0828, 0x0829, 0x082A, 0x082B, 0x082C };

s16 D_80ABBE38[] = { 0x0000, 0x0000, 0x0002, 0x0001, 0x0000, 0x0000, 0x0002, 0x0000, 0x0000, 0x0002 };

static AnimationHeader* sAnimations[] = {
    &gDekuPalaceGuardWaitAnim,
    &gDekuPalaceGuardWalkAnim,
    &gDekuPalaceGuardDigAnim,
    &gDekuPalaceGuardWalkAnim,
};

static u8 sAnimModes[] = { ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_ONCE };

static TexturePtr sEyeTextures[] = { gDekuPalaceGuardEyeOpenTex, gDekuPalaceGuardEyeHalfTex, gDekuPalaceGuardEyeClosedTex };

void EnGuardNuts_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnGuardNuts* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &gDekuPalaceGuardSkel, &gDekuPalaceGuardWaitAnim, this->jointTable,
                   this->morphTable, OBJECT_DNK_LIMB_MAX);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.targetMode = 1;
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    Actor_SetScale(&this->actor, 0.015f);
    Math_Vec3f_Copy(&this->unk228, &this->actor.world.pos);
    this->unk21E = D_80ABBE1C;
    D_80ABBE1C++;

    // If you have returned deku princess guards will Init burrowed.
    if (!(gSaveContext.weekEventReg[23] & 0x20)) {
        EnGuardNuts_SetupWait(this);
    } else {
        EnGuardNuts_Burrow(this, globalCtx);
    }
}

void EnGuardNuts_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnGuardNuts* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

/**
 * @brief Changes the animation to the provided index. Updates animIndex and animFrameCount for the animation.
 *
 * @param this
 * @param index the index of sAnimations to change to
 */
void EnGuardNuts_ChangeAnim(EnGuardNuts* this, s32 index) {
    this->animIndex = index;
    this->animFrameCount = Animation_GetLastFrame(sAnimations[this->animIndex]);
    Animation_Change(&this->skelAnime, sAnimations[this->animIndex], 1.0f, 0.0f, this->animFrameCount,
                     sAnimModes[this->animIndex], -2.0f);
}

void EnGuardNuts_SetupWait(EnGuardNuts* this) {
    EnGuardNuts_ChangeAnim(this, WAIT_ANIM);
    this->unk21C = 0;
    this->actionFunc = EnGuardNuts_Wait;
}

void EnGuardNuts_Wait(EnGuardNuts* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 phi_a1;
    s16 yawDiff;

    SkelAnime_Update(&this->skelAnime);
    yawDiff = ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.home.rot.y));
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        func_80ABB540(this);
        return;
    }
    // From what I can tell this is when you enter from behind the entrance guards
    if (yawDiff > 0x6000) {
        D_80ABBE20 = 2;
    }
    if (player->transformation == PLAYER_FORM_DEKU) {
        // this is the palace of...
        this->textId = 0;
        if ((gSaveContext.weekEventReg[17] & 4) && (!this->unk224)) {
            // I told you not to enter!!
            this->textId = 7;
        } else if (gSaveContext.weekEventReg[12] & 0x40) {
            // come do see the money again?
            this->textId = 4;
        }
    } else {
        // No place for an outsider
        this->textId = 3;
    }
    this->actor.textId = sTextIDs[this->textId];
    phi_a1 = this->actor.world.rot.y;
    if (D_80ABBE20 == 2) {
        EnGuardNuts_Burrow(this, globalCtx);
        return;
    }
    if (D_80ABBE20 == 1) {
        if (this->animIndex != WALK_ANIM) {
            EnGuardNuts_ChangeAnim(this, WALK_ANIM);
        }
        phi_a1 = (this->actor.home.rot.y + 0x8000);
    }
    if (fabsf((f32)(this->actor.shape.rot.y - phi_a1)) < 100.0f) {
        this->actor.shape.rot.y = phi_a1;
        if ((D_80ABBE20 == 1) && (this->animIndex != WALK_ANIM_2)) {
            EnGuardNuts_ChangeAnim(this, WALK_ANIM_2);
        }
    } else {
        Math_SmoothStepToS(&this->actor.shape.rot.y, phi_a1, 1, 0xBB8, 0);
    }
    if (this->unk23A.x == 0) {
        if (fabsf((f32)this->actor.world.rot.y - (f32)this->actor.yawTowardsPlayer) < 10000.0f) {
            this->unk23A.y = this->actor.world.rot.y - this->actor.yawTowardsPlayer;
            this->unk23A.y = -this->unk23A.y;
        }
    }
    func_800B8614(&this->actor, globalCtx, 70.0f);
}

void func_80ABB540(EnGuardNuts* this) {
    EnGuardNuts_ChangeAnim(this, WALK_ANIM);
    this->unk23A.y = 0;
    this->unk23A.x = this->unk23A.y;
    this->unk214 = 16;
    this->unk21C = 1;
    this->actionFunc = func_80ABB590;
}

void func_80ABB590(EnGuardNuts* this, GlobalContext* globalCtx) {
    s16 yaw = this->actor.yawTowardsPlayer;
    f32 curFrame;

    if (D_80ABBE20 == 1) {
        yaw = (this->actor.home.rot.y + 0x8000);
    }
    if (fabsf((this->actor.shape.rot.y - yaw)) < 100.0f) {
        this->actor.shape.rot.y = yaw;
        curFrame = this->skelAnime.curFrame;
        if ((curFrame < this->animFrameCount) || (this->textId >= 7)) {
            SkelAnime_Update(&this->skelAnime);
        }
    } else {
        SkelAnime_Update(&this->skelAnime);
        Math_SmoothStepToS(&this->actor.shape.rot.y, yaw, 1, 0xBB8, 0);
    }
    if (Message_GetState(&globalCtx->msgCtx) == 5) {
        this->unk23A.y = 0;
        this->unk23A.x = 0;
        if ((this->textId == 3) && (this->animIndex == WAIT_ANIM)) {
            EnGuardNuts_ChangeAnim(this, WAIT_ANIM);
        }
        if (func_80147624(globalCtx) != 0) {
            if (D_80ABBE38[this->textId] != 1) {
                if (D_80ABBE38[this->textId] == 2) {
                    func_801477B4(globalCtx);
                    D_80ABBE20 = 2;
                    gSaveContext.weekEventReg[12] |= 0x40;
                    EnGuardNuts_Burrow(this, globalCtx);
                } else {
                    this->textId++;
                    func_801518B0(globalCtx, sTextIDs[this->textId], &this->actor);
                    if (D_80ABBE38[this->textId] == 2) {
                        D_80ABBE20 = 1;
                    }
                    this->unk214 = 16;
                }
            } else if (this->textId != 3) {
                this->unk23A.x = 0;
                this->unk23A.y = this->unk23A.x;
                func_801477B4(globalCtx);
                this->unk21C = 4;
                this->actionFunc = EnGuardNuts_Unburrow;
            } else {
                func_801477B4(globalCtx);
                EnGuardNuts_SetupWait(this);
            }
        }
    } else if ((Message_GetState(&globalCtx->msgCtx) >= 3) && (D_80ABBE20 == 0)) {
        if ((this->textId == 0) || (this->textId == 3) || (this->textId >= 7)) {
            if (this->unk214 == 0) {
                this->unk214 = 2;
                this->unk23A.y ^= 0x2000;
            }
        } else if (this->unk214 == 0) {
            this->unk214 = 2;
            this->unk23A.x ^= 0x2000;
        }
    }
}

void EnGuardNuts_Burrow(EnGuardNuts* this, GlobalContext* globalCtx) {
    Vec3f digPos;

    EnGuardNuts_ChangeAnim(this, DIG_ANIM);
    Math_Vec3f_Copy(&digPos, &this->actor.world.pos);
    digPos.y = this->actor.floorHeight;
    EffectSsHahen_SpawnBurst(globalCtx, &digPos, 4.0f, 0, 10, 3, 15, -1, 10, NULL);
    this->unk23A.y = 0;
    this->actor.flags |= ACTOR_FLAG_8000000;
    this->unk23A.x = this->unk23A.y;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_DOWN);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_UP);
    this->actionFunc = EnGuardNuts_SetupUnburrow;
}

void EnGuardNuts_SetupUnburrow(EnGuardNuts* this, GlobalContext* globalCtx) {
    f32 curFrame = this->skelAnime.curFrame;

    SkelAnime_Update(&this->skelAnime);
    if (this->animFrameCount <= curFrame) {
        this->unk21C = 3;
        this->actionFunc = EnGuardNuts_Unburrow;
        this->actor.world.rot.y = this->actor.home.rot.y;
        this->actor.shape.rot.y = this->actor.home.rot.y;
    }
}

void EnGuardNuts_Unburrow(EnGuardNuts* this, GlobalContext* globalCtx) {
    s16 yawDiff;
    Vec3f digPos;

    // If you have returned Deku Princess, guards will not unburrow
    if (!(gSaveContext.weekEventReg[23] & 0x20)) {
        yawDiff = ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.home.rot.y));
        if ((yawDiff < 0x4000) && ((D_80ABBE20 == 0) || (this->actor.xzDistToPlayer > 150.0f))) {
            Math_Vec3f_Copy(&digPos, &this->actor.world.pos);
            digPos.y = this->actor.floorHeight;
            EffectSsHahen_SpawnBurst(globalCtx, &digPos, 4.0f, 0, 10, 3, 15, -1, 10, NULL);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_UP);
            D_80ABBE20 = 0;
            if (this->textId == 9) {
                this->unk224 = true;
            }
            this->actor.flags &= ~ACTOR_FLAG_8000000;
            EnGuardNuts_SetupWait(this);
        }
    }
}

void EnGuardNuts_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGuardNuts* this = THIS;
    s32 pad;

    if (this->blinkTimer == 0) {
        this->eyeState++;
        if (this->eyeState >= 3) {
            this->eyeState = 0;
            this->blinkTimer = (s16)Rand_ZeroFloat(60.0f) + 20;
        }
    }
    if ((this->animIndex == WALK_ANIM) &&
        ((Animation_OnFrame(&this->skelAnime, 1.0f)) || (Animation_OnFrame(&this->skelAnime, 5.0f)))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_WALK);
    }

    this->actionFunc(this, globalCtx);
    Actor_SetFocus(&this->actor, 40.0f);
    Math_SmoothStepToS(&this->headRot.x, this->unk23A.x, 1, 0xBB8, 0);
    Math_SmoothStepToS(&this->headRot.y, this->unk23A.y, 1, 0xBB8, 0);

    if (this->blinkTimer != 0) {
        this->blinkTimer--;
    }
    if (this->unk214 != 0) {
        this->unk214--;
    }

    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 60.0f, 0x1D);
    if ((this->unk21C != 3) && (this->unk21C != 4)) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

s32 EnGuardNuts_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                 Actor* thisx) {
    EnGuardNuts* this = THIS;

    if (limbIndex == OBJECT_DNK_LIMB_HEAD) {
        rot->x += this->headRot.x;
        rot->y += this->headRot.y;
        rot->z += this->headRot.z;
    }
    return false;
}

void EnGuardNuts_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnGuardNuts* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeState]));

    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, EnGuardNuts_OverrideLimbDraw,
                      NULL, &this->actor);
    Matrix_InsertTranslation(this->unk228.x, this->actor.floorHeight, this->unk228.z, 0);
    Matrix_Scale(0.015f, 0.015f, 0.015f, 1);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_OPA_DISP++, object_dnk_DL_002700);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
