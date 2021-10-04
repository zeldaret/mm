/*
 * File: z_en_giant.c
 * Overlay: ovl_En_Giant
 * Description: Giant
 */

#include "z_en_giant.h"

#define FLAGS 0x00000030

#define THIS ((EnGiant*)thisx)

void EnGiant_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGiant_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGiant_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGiant_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B023D0(EnGiant* this, GlobalContext* globalCtx);
void func_80B024AC(EnGiant* this, GlobalContext* globalCtx);
void func_80B024D8(EnGiant* this, GlobalContext* globalCtx);

const ActorInit En_Giant_InitVars = {
    ACTOR_EN_GIANT,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GIANT,
    sizeof(EnGiant),
    (ActorFunc)EnGiant_Init,
    (ActorFunc)EnGiant_Destroy,
    (ActorFunc)EnGiant_Update,
    (ActorFunc)EnGiant_Draw,
};

extern AnimationHeader D_06002168;
extern Gfx D_06005A80[];
extern Gfx D_06006280[];
extern Gfx D_06007610[];
extern Gfx D_06006A80[];
extern FlexSkeletonHeader D_060079B0;
extern AnimationHeader D_06008394;
extern AnimationHeader D_060096E4;
extern AnimationHeader D_0600A1C4;
extern AnimationHeader D_0600ACA4;
extern AnimationHeader D_0600B784;
extern AnimationHeader D_0600C5D4;
extern AnimationHeader D_0600D040;
extern AnimationHeader D_0600DE84;
extern AnimationHeader D_060102A4;
extern AnimationHeader D_060116E4;
extern AnimationHeader D_06012A38;
extern AnimationHeader D_06013004;
extern AnimationHeader D_06013FE8;
extern AnimationHeader D_06015334;
extern AnimationHeader D_06017944;

static AnimationHeader* sAnimationTable[] = {
    &D_06008394, &D_060096E4, &D_060102A4, &D_060116E4, &D_06012A38, &D_06013004, &D_06013FE8, &D_06015334,
    &D_06017944, &D_0600A1C4, &D_0600D040, &D_0600DE84, &D_0600ACA4, &D_0600B784, &D_0600C5D4,
};

static TexturePtr sFaceTextures[] = { D_06005A80, D_06006280, D_06006A80 };

void EnGiant_ChangeAnimation(EnGiant* this, s16 newAnimationId) {
    if (newAnimationId >= GIANT_ANIMATION_LOOK_UP_START && newAnimationId < GIANT_ANIMATION_MAX) {
        if ((this->animationId == GIANT_ANIMATION_WALKING_LOOP && newAnimationId != GIANT_ANIMATION_WALKING_LOOP) ||
            (newAnimationId == GIANT_ANIMATION_WALKING_LOOP && this->animationId != GIANT_ANIMATION_WALKING_LOOP)) {
            SkelAnime_ChangeAnim(&this->skelAnime, sAnimationTable[newAnimationId], 1.0f, 0.0f,
                                 SkelAnime_GetFrameCount(&sAnimationTable[newAnimationId]->common), 2, 10.0f);
        } else {
            SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, sAnimationTable[newAnimationId]);
        }
        this->animationId = newAnimationId;
    }
}

s32 EnGiant_IsNotFreed(EnGiant* this) {
    switch (GIANT_TYPE(&this->actor)) {
        case GIANT_TYPE_SWAMP_TERMINA_FIELD:
        case GIANT_TYPE_SWAMP_CLOCK_TOWER_SUCCESS:
        case GIANT_TYPE_SWAMP_GIANTS_CHAMBER_AND_ENDING:
        case GIANT_TYPE_SWAMP_CLOCK_TOWER_FAILURE:
            if (!CHECK_QUEST_ITEM(0)) {
                return 1;
            }
            break;
        case GIANT_TYPE_MOUNTAIN_TERMINA_FIELD:
        case GIANT_TYPE_MOUNTAIN_CLOCK_TOWER_SUCCESS:
        case GIANT_TYPE_MOUNTAIN_GIANTS_CHAMBER_AND_ENDING:
        case GIANT_TYPE_MOUNTAIN_CLOCK_TOWER_FAILURE:
            if (!CHECK_QUEST_ITEM(1)) {
                return 1;
            }
            break;
        case GIANT_TYPE_OCEAN_TERMINA_FIELD:
        case GIANT_TYPE_OCEAN_CLOCK_TOWER_SUCCESS:
        case GIANT_TYPE_OCEAN_GIANTS_CHAMBER_AND_ENDING:
        case GIANT_TYPE_OCEAN_CLOCK_TOWER_FAILURE:
            if (!CHECK_QUEST_ITEM(2)) {
                return 1;
            }
            break;
        case GIANT_TYPE_CANYON_TERMINA_FIELD:
        case GIANT_TYPE_CANYON_CLOCK_TOWER_SUCCESS:
        case GIANT_TYPE_CANYON_GIANTS_CHAMBER_AND_ENDING:
        case GIANT_TYPE_CANYON_CLOCK_TOWER_FAILURE:
            if (!CHECK_QUEST_ITEM(3)) {
                return 1;
            }
            break;
    }

    return 0;
}

void EnGiant_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnGiant* this = THIS;
    s32 type = GIANT_TYPE(thisx);

    this->actor.uncullZoneForward = 4000.0f;
    this->actor.uncullZoneScale = 2000.0f;
    this->actor.uncullZoneDownward = 2400.0f;
    Actor_SetScale(&this->actor, 0.32f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_060079B0, &D_06002168, this->jointTable, this->morphTable, 16);
    EnGiant_ChangeAnimation(this, GIANT_ANIMATION_IDLE_LOOP);
    this->unk_24C = 0;
    this->actionFunc = func_80B024D8;
    this->actor.draw = NULL;
    this->alpha = 0;
    this->actor.velocity.y = -10.0f;
    this->actor.minVelocityY = -10.0f;
    this->actor.gravity = -5.0f;
    switch (type) {
        case GIANT_TYPE_CANYON_TERMINA_FIELD:
        case GIANT_TYPE_CANYON_CLOCK_TOWER_SUCCESS:
        case GIANT_TYPE_CANYON_GIANTS_CHAMBER_AND_ENDING:
            this->unk_24A = 0x1C6;
            break;
        case GIANT_TYPE_SWAMP_TERMINA_FIELD:
        case GIANT_TYPE_SWAMP_CLOCK_TOWER_SUCCESS:
        case GIANT_TYPE_SWAMP_GIANTS_CHAMBER_AND_ENDING:
            this->unk_24A = 0x1C7;
            break;
        case GIANT_TYPE_OCEAN_TERMINA_FIELD:
        case GIANT_TYPE_OCEAN_CLOCK_TOWER_SUCCESS:
        case GIANT_TYPE_OCEAN_GIANTS_CHAMBER_AND_ENDING:
            this->unk_24A = 0x1C8;
            break;
        default:
            this->unk_24A = 0x1C5;
            break;
    }

    if (type >= GIANT_TYPE_MOUNTAIN_CLOCK_TOWER_SUCCESS && type < GIANT_TYPE_MOUNTAIN_GIANTS_CHAMBER_AND_ENDING) {
        if (!(gSaveContext.weekEventReg[0x19] & 2)) {
            Actor_MarkForDeath(&this->actor);
            return;
        }
        this->unk_24A = 0x1C5;
        Actor_SetScale(&this->actor, 0.32f);
        this->actionFunc = func_80B023D0;
        SkelAnime_ChangeAnim(&this->skelAnime, &D_060116E4, 0.0f, SkelAnime_GetFrameCount(&D_060116E4.common) - 1.0f,
                             SkelAnime_GetFrameCount(&D_060116E4.common), 2, 0.0f);
        this->actor.draw = EnGiant_Draw;
        this->actor.velocity.y = 0.0f;
        this->actor.minVelocityY = 0.0f;
        this->actor.gravity = 0.0f;
    }

    if (type >= GIANT_TYPE_MOUNTAIN_CLOCK_TOWER_FAILURE && type < GIANT_TYPE_MAX) {
        Actor_SetScale(&this->actor, 0.32f);
        this->actionFunc = func_80B024AC;
        SkelAnime_ChangeAnim(&this->skelAnime, &D_06013FE8, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_06013004.common), 0,
                             0.0f);
        this->actor.draw = EnGiant_Draw;
        this->actor.velocity.y = 0.0f;
        this->actor.minVelocityY = 0.0f;
        this->actor.gravity = 0.0f;
        if (EnGiant_IsNotFreed(this)) {
            Actor_MarkForDeath(&this->actor);
        }
    }

    if (type >= GIANT_TYPE_MOUNTAIN_CLOCK_TOWER_SUCCESS) {
        this->alpha = 255;
    }

    this->sfxId = 0xFFFF;
    if (type >= GIANT_TYPE_MOUNTAIN_GIANTS_CHAMBER_AND_ENDING && type < GIANT_TYPE_MOUNTAIN_CLOCK_TOWER_FAILURE) {
        switch (gSaveContext.sceneSetupIndex) {
            case 0:
            case 10:
                this->sfxId = NA_SE_EV_KYOJIN_GRATITUDE2 - SFX_FLAG;
                break;
            case 1:
            case 2:
            case 3:
                this->sfxId = NA_SE_EV_KYOJIN_GRATITUDE1 - SFX_FLAG;
                break;
            default:
                this->sfxId = NA_SE_EV_KYOJIN_GRATITUDE0 - SFX_FLAG;
                break;
        }
    }
}

void EnGiant_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

/**
 * The animations in sAnimationTable are organized such that looping animations
 * appear immediately after their respective starting animations. The point of
 * this function is to play the requested start animation if it has not been
 * played yet and play the respetive looping animation otherwise.
 **/
void EnGiant_ChangeToStartOrLoopAnimation(EnGiant* this, s16 requestedAnimationId) {
    s16 nextAnimationId = requestedAnimationId + 1;

    if (this->animationId != nextAnimationId) {
        if (this->animationId != requestedAnimationId) {
            EnGiant_ChangeAnimation(this, requestedAnimationId);
        } else {
            EnGiant_ChangeAnimation(this, nextAnimationId);
        }
    }
}

void func_80B01EE8(EnGiant* this) {
    switch (this->unk_24C) {
        case 1:
            EnGiant_ChangeAnimation(this, GIANT_ANIMATION_IDLE_LOOP);
            break;
        case 2:
            EnGiant_ChangeAnimation(this, GIANT_ANIMATION_WALKING_LOOP);
            break;
        case 5:
            EnGiant_ChangeAnimation(this, GIANT_ANIMATION_STRUGGLE_START);
            break;
        case 6:
            EnGiant_ChangeAnimation(this, GIANT_ANIMATION_FALLING_OVER);
            break;
        case 7:
            EnGiant_ChangeAnimation(this, GIANT_ANIMATION_IDLE_LOOP);
            this->alpha = 0;
            break;
        case 8:
            EnGiant_ChangeAnimation(this, GIANT_ANIMATION_BIG_CALL_START);
            break;
        case 9:
            EnGiant_ChangeAnimation(this, GIANT_ANIMATION_BIG_CALL_END);
            break;
        case 10:
            EnGiant_ChangeAnimation(this, GIANT_ANIMATION_SMALL_CALL_START);
            break;
        case 11:
            EnGiant_ChangeAnimation(this, GIANT_ANIMATION_SMALL_CALL_END);
            break;
        case 12:
            EnGiant_ChangeAnimation(this, GIANT_ANIMATION_IDLE_LOOP);
            break;
        case 13:
            EnGiant_ChangeAnimation(this, GIANT_ANIMATION_WALKING_LOOP);
            break;
        case 14:
            if (this->animationId != GIANT_ANIMATION_WALKING_LOOP) {
                EnGiant_ChangeAnimation(this, GIANT_ANIMATION_WALKING_LOOP);
            }
            break;
        case 15:
            SkelAnime_ChangeAnim(&this->skelAnime, &D_060116E4, 0.0f,
                                 SkelAnime_GetFrameCount(&D_060116E4.common) - 1.0f,
                                 SkelAnime_GetFrameCount(&D_060116E4.common), 2, 0.0f);
            break;
    }
}

void func_80B020A0(EnGiant* this) {
    switch (this->unk_24C) {
        case 6:
            if (this->skelAnime.animCurrentFrame >= 90.0f && this->alpha > 0) {
                this->alpha -= 12;
            }
            break;
        case 14:
            this->alpha -= 12;
            break;
        default:
            if (this->alpha < 255) {
                this->alpha += 8;
            }
            break;
    }
}

void func_80B0211C(EnGiant* this) {
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) &&
        (this->animationId != GIANT_ANIMATION_FALLING_OVER || this->unk_24C != 6)) {
        EnGiant_ChangeAnimation(this, this->animationId);
        switch (this->unk_24C) {
            case 3:
                EnGiant_ChangeToStartOrLoopAnimation(this, GIANT_ANIMATION_LOOK_UP_START);
                break;
            case 4:
                EnGiant_ChangeToStartOrLoopAnimation(this, GIANT_ANIMATION_RAISED_ARMS_START);
                break;
            case 5:
                EnGiant_ChangeToStartOrLoopAnimation(this, GIANT_ANIMATION_STRUGGLE_START);
                break;
            case 6:
                EnGiant_ChangeToStartOrLoopAnimation(this, GIANT_ANIMATION_FALLING_OVER);
                break;
            case 8:
                EnGiant_ChangeAnimation(this, GIANT_ANIMATION_BIG_CALL_LOOP);
                break;
            case 9:
            case 11:
                EnGiant_ChangeAnimation(this, GIANT_ANIMATION_IDLE_LOOP);
                break;
            case 10:
                EnGiant_ChangeAnimation(this, GIANT_ANIMATION_SMALL_CALL_LOOP);
                break;
        }
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    }
}

void EnGiant_PlaySound(EnGiant* this) {
    if (this->actor.draw != NULL && this->alpha > 0) {
        if (this->animationId == GIANT_ANIMATION_WALKING_LOOP &&
            (func_801378B8(&this->skelAnime, 40.0f) || func_801378B8(&this->skelAnime, 100.0f))) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_KYOJIN_WALK);
        }
        if (this->animationId == GIANT_ANIMATION_FALLING_OVER && func_801378B8(&this->skelAnime, 40.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_KYOJIN_VOICE_FAIL);
        }
        if (this->sfxId != 0xFFFF &&
            ((this->animationId == GIANT_ANIMATION_BIG_CALL_START && this->skelAnime.animCurrentFrame >= 18.0f) ||
             this->animationId == GIANT_ANIMATION_BIG_CALL_LOOP)) {
            func_800B9010(&this->actor, this->sfxId);
        }
        if ((this->animationId == GIANT_ANIMATION_SMALL_CALL_START && this->skelAnime.animCurrentFrame >= 18.0f) ||
            this->animationId == GIANT_ANIMATION_SMALL_CALL_LOOP) {
            func_800B9010(&this->actor, NA_SE_EV_KYOJIN_SIGN - SFX_FLAG);
        }
    }
}

void func_80B02354(EnGiant* this, GlobalContext* globalCtx, u32 arg2) {
    CsCmdActorAction* actorAction = globalCtx->csCtx.npcActions[arg2];
    f32 floatUnk10 = actorAction->unk10;
    s32 pad[2];
    f32 floatUnk1C = actorAction->unk1C;
    f32 functionTemp;

    functionTemp = func_800F5A8C(actorAction->endFrame, actorAction->startFrame, globalCtx->csCtx.frames, globalCtx);
    this->actor.world.pos.y = ((floatUnk1C - floatUnk10) * functionTemp) + floatUnk10;
}

void func_80B023D0(EnGiant* this, GlobalContext* globalCtx) {
    if (func_800EE29C(globalCtx, this->unk_24A)) {
        func_80B02354(this, globalCtx, func_800EE200(globalCtx, this->unk_24A));
        if (this->unk_24C != globalCtx->csCtx.npcActions[func_800EE200(globalCtx, this->unk_24A)]->unk0) {
            this->unk_24C = globalCtx->csCtx.npcActions[func_800EE200(globalCtx, this->unk_24A)]->unk0;
            func_80B01EE8(this);
        }
        func_80B020A0(this);
    }

    EnGiant_PlaySound(this);
    if (this->unk_24C == 5) {
        func_800B9010(&this->actor, 0x1063);
    }
    func_80B0211C(this);
}

void func_80B024AC(EnGiant* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
}

void func_80B024D8(EnGiant* this, GlobalContext* globalCtx) {
    this->actor.draw = EnGiant_Draw;

    if (func_800EE29C(globalCtx, this->unk_24A)) {
        func_800EDF24(&this->actor, globalCtx, func_800EE200(globalCtx, this->unk_24A));
        if (this->unk_24C != globalCtx->csCtx.npcActions[func_800EE200(globalCtx, this->unk_24A)]->unk0) {
            this->unk_24C = globalCtx->csCtx.npcActions[func_800EE200(globalCtx, this->unk_24A)]->unk0;
            func_80B01EE8(this);
        }
        func_80B020A0(this);
    }

    if (GIANT_TYPE(&this->actor) < GIANT_TYPE_MOUNTAIN_CLOCK_TOWER_SUCCESS && EnGiant_IsNotFreed(this)) {
        this->actor.draw = NULL;
    }

    EnGiant_PlaySound(this);
    func_80B0211C(this);
}

void EnGiant_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGiant* this = THIS;
    s32 blinkTimerTemp;

    this->actionFunc(this, globalCtx);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);

    if (this->blinkTimer == 0) {
        blinkTimerTemp = 0;
    } else {
        this->blinkTimer--;
        blinkTimerTemp = this->blinkTimer;
    }

    if (!blinkTimerTemp) {
        this->blinkTimer = Rand_S16Offset(60, 60);
    }
    this->faceIndex = this->blinkTimer;
    if (this->faceIndex >= 3) {
        this->faceIndex = 0;
    }
}

void func_80B02688(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    if (limbIndex == 1) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        gSPDisplayList(POLY_OPA_DISP++, D_06007610);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void func_80B026C4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnGiant* this = THIS;

    if (limbIndex == 1) {
        SysMatrix_CopyCurrentState(&this->unk_254);
    }
}

void EnGiant_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnGiant* this = THIS;

    if (this->alpha > 0) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        if (this->alpha >= 255) {
            func_8012C28C(globalCtx->state.gfxCtx);
            gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sFaceTextures[this->faceIndex]));
            gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
            Scene_SetRenderModeXlu(globalCtx, 0, 1);
            SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl,
                             this->skelAnime.dListCount, NULL, func_80B02688, thisx);
            return;
        } else if (this->alpha > 0) {
            if (this->alpha >= 129) {
                func_8012C2B4(POLY_XLU_DISP++);
                Scene_SetRenderModeXlu(globalCtx, 2, 2);
            } else {
                func_8012C304(POLY_XLU_DISP++);
                Scene_SetRenderModeXlu(globalCtx, 1, 2);
            }
            gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(sFaceTextures[this->faceIndex]));
            gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->alpha);
            POLY_XLU_DISP = SkelAnime_DrawSV2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl,
                                              this->skelAnime.dListCount, NULL, func_80B026C4, thisx, POLY_XLU_DISP);
            SysMatrix_InsertMatrix(&this->unk_254, MTXMODE_NEW);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, D_06007610);
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
