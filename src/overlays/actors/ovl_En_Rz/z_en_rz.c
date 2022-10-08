/*
 * File: z_en_rz.c
 * Overlay: ovl_En_Rz
 * Description: Rosa Sisters, Judo (red) and Marilla (blue)
 */

#include "z_en_rz.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnRz*)thisx)

void EnRz_Init(Actor* thisx, PlayState* play);
void EnRz_Destroy(Actor* thisx, PlayState* play);
void EnRz_Update(Actor* thisx, PlayState* play);
void EnRz_Draw(Actor* thisx, PlayState* play);

void EnRz_ActorShadowFunc(Actor* thisx, Lights* mapper, PlayState* play);
void EnRz_ChangeAnim(PlayState*, EnRz*, s16 animIndex, u8 animMode, f32 transitionRate);
s32 func_80BFBA50(EnRz* this, PlayState* play);
EnRz* EnRz_FindSister(EnRz* this, PlayState*);
void func_80BFC058(EnRz* this, PlayState* play);
void func_80BFC078(EnRz* this, PlayState* play);
void func_80BFC3F8(EnRz* this, PlayState* play);
void func_80BFC674(EnRz* this, PlayState* play);
void func_80BFC7E0(EnRz* this, PlayState* play);
void func_80BFC8F8(EnRz* this, PlayState* play);

#define EN_RZ_STATE_1 (1 << 0)
#define EN_RZ_STATE_2 (1 << 1)

typedef enum {
    /* 0 */ EN_RZ_ANIM_MIN,
    /* 1 */ EN_RZ_STANDING_ANIM,
    /* 2 */ EN_RZ_WALKING_ANIM,
    /* 3 */ EN_RZ_SITTING_ANIM,
    /* 4 */ EN_RZ_APPLAUDING_ANIM,
    /* 5 */ EN_RZ_ON_KNEES_ANIM,
    /* 6 */ EN_RZ_DANCE_ANIM,
    /* 7 */ EN_RZ_LINK_NORMAL_WAIT_FREE_ANIM,
    /* 8 */ EN_RZ_LINK_DANCE_ANIM,
    /* 9 */ EN_RZ_ANIM_MAX
} EnRzAnimations;

const ActorInit En_Rz_InitVars = {
    ACTOR_EN_RZ,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_RZ,
    sizeof(EnRz),
    (ActorFunc)EnRz_Init,
    (ActorFunc)EnRz_Destroy,
    (ActorFunc)EnRz_Update,
    (ActorFunc)EnRz_Draw,
};

static TexturePtr sEyeTextures[] = {
    object_rz_Tex_00BC50, object_rz_Tex_00C190, object_rz_Tex_00C590, object_rz_Tex_00C990, object_rz_Tex_00CD90,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 20, 40, 0, { 0, 0, 0 } },
};

void EnRz_Init(Actor* thisx, PlayState* play) {
    EnRz* this = THIS;
    s16 tempCutscene = this->actor.cutscene;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->cutscenes); i++) {
        this->cutscenes[i] = tempCutscene;
        if (tempCutscene != -1) {
            this->actor.cutscene = tempCutscene;
            tempCutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
        }
    }

    Actor_SetScale(&this->actor, 0.01f);
    ActorShape_Init(&this->actor.shape, 0.0f, EnRz_ActorShadowFunc, 20.0f);

    // @bug this alignment is because of player animations, but should be using ALIGN16
    SkelAnime_InitFlex(play, &this->skelAnime, &object_rz_Skel_00D8D8, &gRosaSistersStandingAnim,
                       (uintptr_t)this->jointTable & ~0xF, (uintptr_t)this->morphTable & ~0xF, OBJECT_RZ_LIMB_MAX);
    Animation_PlayLoop(&this->skelAnime, &gRosaSistersStandingAnim);

    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;

    this->actionFunc = func_80BFC058;
    func_80BFBA50(this, play);
    this->animIndex = EN_RZ_ANIM_MAX;
    this->actor.targetMode = 0;
    this->actor.terminalVelocity = -9.0f;
    this->actor.gravity = -1.0f;

    switch (EN_RZ_GET_TYPE(thisx)) {
        case ROSA_SISTERS_TYPE_1:
            if (!(gSaveContext.save.weekEventReg[77] & 4)) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            EnRz_ChangeAnim(play, this, EN_RZ_SITTING_ANIM, ANIMMODE_LOOP, 0.0f);
            this->actionFunc = func_80BFC674;
            this->actor.shape.yOffset = -1500.0f;
            break;

        case ROSA_SISTERS_TYPE_2:
            this->actor.flags |= ACTOR_FLAG_10;
            if (gSaveContext.save.weekEventReg[77] & 4) {
                EnRz_ChangeAnim(play, this, EN_RZ_LINK_DANCE_ANIM, ANIMMODE_LOOP, 0.0f);
            } else {
                EnRz_ChangeAnim(play, this, EN_RZ_DANCE_ANIM, ANIMMODE_LOOP, 0.0f);
            }
            this->actionFunc = func_80BFC3F8;
            this->sister = EnRz_FindSister(this, play);
            this->actor.uncullZoneForward = 300.0f;
            break;

        default: // ROSA_SISTERS_TYPE_0
            this->stateFlags |= EN_RZ_STATE_2;
            if (gSaveContext.save.weekEventReg[77] & 4) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            EnRz_ChangeAnim(play, this, EN_RZ_WALKING_ANIM, ANIMMODE_LOOP, 0.0f);
            this->actionFunc = func_80BFC8F8;
            if (!EN_RZ_GET_SISTER(thisx)) {
                this->actor.textId = 0x291C;
            } else {
                this->actor.textId = 0x2920;
            }
            break;
    }

    if (!EN_RZ_GET_SISTER(thisx)) {
        this->csAction = 0x226;
    } else {
        this->csAction = 0x227;
    }

    this->actionIndex = 0;
}

/**
 * Custom shadow draw function of type ActorShadowFunc.
 */
void EnRz_ActorShadowFunc(Actor* thisx, Lights* mapper, PlayState* play) {
    Vec3f oldPos;
    EnRz* this = THIS;

    if (this->animIndex == EN_RZ_LINK_DANCE_ANIM) {
        f32 tempScale = (((27.0f - this->shadowPos.y) + this->actor.world.pos.y) * ((1 / 2.25f) * 0.001f)) + 0.01f;

        this->actor.scale.x = tempScale;
    }

    Math_Vec3f_Copy(&oldPos, &this->actor.world.pos);
    Math_Vec3f_Copy(&this->actor.world.pos, &this->shadowPos);
    func_800B4AEC(play, &this->actor, 50.0f);

    if (oldPos.y < this->actor.floorHeight) {
        this->actor.world.pos.y = this->actor.floorHeight;
    } else {
        this->actor.world.pos.y = oldPos.y;
    }

    ActorShadow_DrawCircle(&this->actor, mapper, play);
    Math_Vec3f_Copy(&this->actor.world.pos, &oldPos);
    this->actor.scale.x = 0.01f;
}

void EnRz_ChangeAnim(PlayState* play, EnRz* this, s16 animIndex, u8 animMode, f32 transitionRate) {
    static AnimationHeader* sJudoAnimations[] = {
        &gRosaSistersThinkingAnim, &gRosaSistersStandingAnim,   &gRosaSistersWalkingWhileThinkingAnim,
        &gRosaSistersSittingAnim,  &gRosaSistersApplaudingAnim, &gRosaSistersOnKneesAnim,
        &gRosaSistersDancingAnim,
    };
    static AnimationHeader* sMarillaAnimations[] = {
        &gRosaSistersStandingAnim,   &gRosaSistersStandingAnim, &gRosaSistersWalkingAnim, &gRosaSistersSittingAnim,
        &gRosaSistersApplaudingAnim, &gRosaSistersOnKneesAnim,  &gRosaSistersDancingAnim,
    };
    static LinkAnimationHeader* sLinkAnimations[] = {
        &gPlayerAnim_link_normal_wait_free,
        &gPlayerAnim_alink_dance_loop,
    };
    f32 endFrame;
    AnimationHeader** animationPtr;

    if (!EN_RZ_GET_SISTER(&this->actor)) {
        animationPtr = sJudoAnimations;
    } else {
        animationPtr = sMarillaAnimations;
    }

    if ((animIndex >= EN_RZ_ANIM_MIN) && (animIndex < EN_RZ_ANIM_MAX) &&
        ((animIndex != this->animIndex) || (animMode != ANIMMODE_LOOP))) {
        if (animIndex >= ARRAY_COUNT(sJudoAnimations)) {
            endFrame = Animation_GetLastFrame(sLinkAnimations[animIndex - ARRAY_COUNT(sJudoAnimations)]);
            if (animMode == ANIMMODE_LOOP) {
                LinkAnimation_Change(play, &this->skelAnime, sLinkAnimations[animIndex - ARRAY_COUNT(sJudoAnimations)],
                                     2.0f / 3.0f, 0.0f, endFrame, ANIMMODE_LOOP, transitionRate);
            } else {
                LinkAnimation_Change(play, &this->skelAnime, sLinkAnimations[animIndex - ARRAY_COUNT(sJudoAnimations)],
                                     2.0f / 3.0f, 0.0f, endFrame, ANIMMODE_LOOP, transitionRate);
            }
        } else {
            Animation_Change(&this->skelAnime, animationPtr[animIndex], 1.0f, 0.0f,
                             Animation_GetLastFrame(animationPtr[animIndex]), animMode, transitionRate);
        }

        this->animIndex = animIndex;
    }
}

void func_80BFB9E4(PlayState* play, EnRz* this, s16 animIndex) {
    EnRz_ChangeAnim(play, this, animIndex, ANIMMODE_LOOP, -5.0f);
}

void func_80BFBA1C(PlayState* play, EnRz* this, s16 animIndex) {
    EnRz_ChangeAnim(play, this, animIndex, ANIMMODE_LOOP, 0.0f);
}

s32 func_80BFBA50(EnRz* this, PlayState* play) {
    if (EN_RZ_GET_PATH(&this->actor) != 0x3F) {
        this->path = &play->setupPathList[EN_RZ_GET_PATH(&this->actor)];
        if (this->path != NULL) {
            Path* path = this->path;
            Vec3s* points = (Vec3s*)Lib_SegmentedToVirtual(path->points);
            f32 diffX = points->x - this->actor.world.pos.x;
            f32 diffY = points->z - this->actor.world.pos.z;

            if ((SQ(diffX) + SQ(diffY)) < SQ(10.0f)) {
                this->curPointIndex = 0;
                this->stateFlags &= ~EN_RZ_STATE_1;
            } else {
                this->curPointIndex = path->count - 1;
                this->stateFlags |= EN_RZ_STATE_1;
                return true;
            }
        }
    } else {
        this->path = NULL;
        this->curPointIndex = 0;
    }
    return false;
}

s32 func_80BFBB44(EnRz* this) {
    Path* path = this->path;
    Vec3s* curPoint;
    f32 diffX;
    f32 diffZ;

    if (path == NULL) {
        return true;
    }

    curPoint = &((Vec3s*)Lib_SegmentedToVirtual(path->points))[this->curPointIndex];
    diffX = curPoint->x - this->actor.world.pos.x;
    diffZ = curPoint->z - this->actor.world.pos.z;
    this->actor.world.rot.y = Math_Atan2S(diffX, diffZ);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 2, 0x07D0, 0xC8);

    if ((SQ(diffX) + SQ(diffZ)) < SQ(10.0f)) {
        if (this->stateFlags & EN_RZ_STATE_1) {
            this->curPointIndex--;
            if (this->curPointIndex < 0) {
                return 2;
            }
        } else {
            this->curPointIndex++;
            if (this->curPointIndex >= path->count) {
                return 2;
            }
        }
        return 1;
    }
    return 0;
}

s32 EnRz_CanTalk(EnRz* this, PlayState* play) {
    if ((this->actor.xzDistToPlayer < 80.0f) && (fabsf(this->actor.playerHeightRel) < 20.0f) &&
        Player_IsFacingActor(&this->actor, 0x3000, play)) {
        return true;
    }
    return false;
}

s32 func_80BFBCEC(EnRz* this, PlayState* play) {
    s32 pad;
    Player* player = GET_PLAYER(play);

    if ((this->actor.xzDistToPlayer < 100.0f) && Actor_IsFacingPlayer(&this->actor, 0x3000) &&
        (player->stateFlags2 & PLAYER_STATE2_2000000)) {
        return true;
    }
    return false;
}

/*
* Updates either Link's or Rosa Sisters animations every frame
*/
s32 EnRz_UpdateSkelAnime(EnRz* this, PlayState* play) {
    if (this->animIndex < EN_RZ_LINK_NORMAL_WAIT_FREE_ANIM) {
        return SkelAnime_Update(&this->skelAnime);
    } else {
        return LinkAnimation_Update(play, &this->skelAnime);
    }
}

EnRz* EnRz_FindSister(EnRz* this, PlayState* play) {
    Actor* npc = play->actorCtx.actorLists[ACTORCAT_NPC].first;

    while (npc != NULL) {
        if ((npc->id == ACTOR_EN_RZ) && (EN_RZ_GET_TYPE(&this->actor) == EN_RZ_GET_TYPE(npc))) {
            if (&this->actor != npc) {
                return (EnRz*)npc;
            }
        }
        npc = npc->next;
    }
    return NULL;
}

void func_80BFBDFC(PlayState* play) {
    if (gSaveContext.save.weekEventReg[75] & 0x80) {
        func_80151BB4(play, 0x27);
    }
    func_80151BB4(play, 0xC);
}

void EnRz_Destroy(Actor* thisx, PlayState* play) {
    EnRz* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

s32 func_80BFBE70(EnRz* this, PlayState* play) {
    u16 action;

    if (!EN_RZ_GET_SISTER(&this->actor) && (this->animIndex == EN_RZ_APPLAUDING_ANIM)) {
        func_800B9010(&this->actor, NA_SE_EV_CLAPPING_2P - SFX_FLAG);
    }

    if (Cutscene_CheckActorAction(play, this->csAction)) {
        Cutscene_ActorTranslateAndYaw(&this->actor, play, Cutscene_GetActorActionIndex(play, this->csAction));
        action = play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, this->csAction)]->action;
        if (this->actionIndex != action) {
            this->actionIndex = action;
            switch (action & 0xFFFF) {
                case 1:
                    func_80BFBA1C(play, this, EN_RZ_STANDING_ANIM);
                    break;

                case 2:
                    func_80BFBA1C(play, this, EN_RZ_ON_KNEES_ANIM);
                    break;

                case 3:
                    func_80BFBA1C(play, this, EN_RZ_APPLAUDING_ANIM);
                    break;

                case 4:
                    func_80BFBA1C(play, this, EN_RZ_LINK_DANCE_ANIM);
                    break;
            }
        }
        return true;
    }
    return false;
}

s32 func_80BFBFAC(EnRz* this, PlayState* play) {
    if (this->actor.cutscene == -1) {
        Message_StartTextbox(play, 0x2925, &this->actor);
        this->actionFunc = func_80BFC078;
    } else if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        return false;
    } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_Start(this->actor.cutscene, &this->actor);
        return true;
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
    return false;
}

void func_80BFC058(EnRz* this, PlayState* play) {
    EnRz_UpdateSkelAnime(this, play);
}

void func_80BFC078(EnRz* this, PlayState* play) {
    s32 pad;
    Vec3f sp28;

    EnRz_UpdateSkelAnime(this, play);

    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
        switch (play->msgCtx.currentTextId) {
            case 0x2927:
            case 0x2928:
                func_80151938(play, play->msgCtx.currentTextId + 1);
                gSaveContext.save.weekEventReg[77] |= 4;
                break;

            default:
                func_801477B4(play);
                this->actionFunc = func_80BFC3F8;
                if (this->animIndex != EN_RZ_LINK_DANCE_ANIM) {
                    func_80BFB9E4(play, this, 6);
                    if (this->sister != NULL) {
                        func_80BFB9E4(play, this->sister, 6);
                    }
                }
                break;
        }
    }

    if (!EN_RZ_GET_SISTER(&this->actor)) {
        sp28.x = this->actor.projectedPos.x;
        sp28.y = this->actor.projectedPos.y;
        sp28.z = this->actor.projectedPos.z;
        func_801A1FB4(3, &sp28, NA_BGM_ROSA_SISTERS, 900.0f);
    }
}

void func_80BFC19C(EnRz* this, PlayState* play) {
    EnRz_UpdateSkelAnime(this, play);
    if (!func_80BFBE70(this, play)) {
        this->actionFunc = func_80BFC3F8;
        func_80BFBA1C(play, this, EN_RZ_LINK_DANCE_ANIM);
        if (this->sister != NULL) {
            func_80BFBA1C(play, this->sister, EN_RZ_LINK_DANCE_ANIM);
        }
    }
}

void func_80BFC214(EnRz* this, PlayState* play) {
    EnRz_UpdateSkelAnime(this, play);
    if (!func_80BFBE70(this, play) && func_80BFBFAC(this, play)) {
        this->actionFunc = func_80BFC19C;
    }
}

void func_80BFC270(EnRz* this, PlayState* play) {
    EnRz_UpdateSkelAnime(this, play);
    if (Actor_HasParent(&this->actor, play)) {
        this->actor.parent = NULL;
        this->actionFunc = func_80BFC214;
        func_80BFBDFC(play);
    } else {
        Actor_PickUp(&this->actor, play, GI_HEART_PIECE, 2000.0f, 1000.0f);
    }
}

void func_80BFC2F4(EnRz* this, PlayState* play) {
    EnRz_UpdateSkelAnime(this, play);
    if (!func_80BFBE70(this, play)) {
        func_801477B4(play);
        Actor_PickUp(&this->actor, play, GI_HEART_PIECE, 2000.0f, 1000.0f);
        this->actionFunc = func_80BFC270;
    }
}

void func_80BFC36C(EnRz* this, PlayState* play) {
    EnRz_UpdateSkelAnime(this, play);
    if (func_80BFBFAC(this, play)) {
        gSaveContext.save.weekEventReg[77] |= 4;
        if (gSaveContext.save.weekEventReg[75] & 0x80) {
            this->actionFunc = func_80BFC214;
        } else {
            this->actionFunc = func_80BFC2F4;
            gSaveContext.save.weekEventReg[75] |= 0x80;
        }
        this->actor.cutscene = this->cutscenes[1];
    }
}

void func_80BFC3F8(EnRz* this, PlayState* play) {
    s32 pad;
    Vec3f sp30;

    EnRz_UpdateSkelAnime(this, play);

    if (this->sister == NULL) {
        this->sister = EnRz_FindSister(this, play);
    }

    if (!func_80BFBE70(this, play)) {
        if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
            this->actionFunc = func_80BFC078;

            if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_10000)) {
                this->actionFunc = func_80BFC36C;
                this->actor.cutscene = this->cutscenes[0];
                this->actor.flags &= ~ACTOR_FLAG_10000;
            } else if (Player_GetMask(play) == PLAYER_MASK_KAMARO) {
                if (gSaveContext.save.weekEventReg[77] & 4) {
                    Message_StartTextbox(play, 0x2925, &this->actor);
                    func_80BFBDFC(play);
                } else {
                    Message_StartTextbox(play, 0x2926, &this->actor);
                    func_80BFBDFC(play);
                }
            } else {
                Message_StartTextbox(play, 0x2926, &this->actor);
                func_80BFBDFC(play);
            }

        } else if (EnRz_CanTalk(this, play)) {
            if (func_80BFBCEC(this, play) && !(gSaveContext.save.weekEventReg[77] & 4) && this->sister != NULL) {
                this->actor.flags |= ACTOR_FLAG_10000;
                func_800B8500(&this->actor, play, 1000.0f, 1000.0f, -1);
            } else {
                this->actor.flags &= ~ACTOR_FLAG_10000;
                func_800B8614(&this->actor, play, 120.0f);
            }
        }

        if (!EN_RZ_GET_SISTER(&this->actor)) {
            sp30.x = this->actor.projectedPos.x;
            sp30.y = this->actor.projectedPos.y;
            sp30.z = this->actor.projectedPos.z;
            func_801A1FB4(3, &sp30, NA_BGM_ROSA_SISTERS, 900.0f);
        }
    }
}

void func_80BFC608(EnRz* this, PlayState* play) {
    EnRz_UpdateSkelAnime(this, play);

    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
        func_801477B4(play);
        this->actionFunc = func_80BFC674;
    }
}

void func_80BFC674(EnRz* this, PlayState* play) {
    EnRz_UpdateSkelAnime(this, play);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actionFunc = func_80BFC608;
        if (Player_GetMask(play) == 0xE) {
            Message_StartTextbox(play, 0x2925, &this->actor);
        } else {
            Message_StartTextbox(play, 0x2924, &this->actor);
        }
    } else if (EnRz_CanTalk(this, play)) {
        func_800B8614(&this->actor, play, 120.0f);
    }
}

void func_80BFC728(EnRz* this, PlayState* play) {
    EnRz_UpdateSkelAnime(this, play);

    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
        func_801477B4(play);
        this->actionFunc = func_80BFC7E0;
        this->actor.textId++;
        if (!EN_RZ_GET_SISTER(&this->actor)) {
            if (this->actor.textId >= 0x2920) {
                this->actor.textId = 0x291C;
            }
        } else if (this->actor.textId >= 0x2924) {
            this->actor.textId = 0x2920;
        }
    }
}

void func_80BFC7E0(EnRz* this, PlayState* play) {
    EnRz_UpdateSkelAnime(this, play);

    if (this->timer > 0) {
        this->timer--;
    } else {
        this->actionFunc = func_80BFC8F8;
        func_80BFB9E4(play, this, 2);
    }

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actionFunc = func_80BFC728;
        func_80BFB9E4(play, this, 0);
        this->actor.speedXZ = 0.0f;
        func_80BFBDFC(play);
    } else if (EnRz_CanTalk(this, play)) {
        func_800B8614(&this->actor, play, 120.0f);
    }
}

void func_80BFC8AC(EnRz* this, PlayState* play) {
    this->timer = 100;
    this->actionFunc = func_80BFC7E0;
    this->actor.speedXZ = 0.0f;
    func_80BFB9E4(play, this, 0);
}

void func_80BFC8F8(EnRz* this, PlayState* play) {
    EnRz_UpdateSkelAnime(this, play);

    this->actor.speedXZ = 1.5f;

    switch (func_80BFBB44(this)) {
        case 2:
            func_80BFBA50(this, play);
            func_80BFC8AC(this, play);
            break;

        case 1:
            func_80BFC8AC(this, play);
            break;

        default:
            break;
    }

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actionFunc = func_80BFC728;
        func_80BFB9E4(play, this, 0);
        this->actor.speedXZ = 0.0f;
        func_80BFBDFC(play);
    } else if (EnRz_CanTalk(this, play)) {
        func_800B8614(&this->actor, play, 120.0f);
    }
}

void EnRz_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnRz* this = THIS;

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 40.0f, 25.0f, 40.0f, 5);

    this->actionFunc(this, play);

    if (DECR(this->blinkTimer) == 0) {
        this->blinkTimer = Rand_S16Offset(60, 60);
    }

    this->eyeIndex = this->blinkTimer;
    if (this->eyeIndex > 2) {
        this->eyeIndex = 0;
    }
}

void EnRz_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnRz* this = THIS;
    static Vec3f focusOffsetPos = { 500.0f, -500.0f, 0.0f };

    if (limbIndex == OBJECT_RZ_LIMB_0B) {
        Matrix_MultVec3f(&focusOffsetPos, &thisx->focus.pos);
    }
    if (limbIndex == OBJECT_RZ_LIMB_03) {
        Matrix_MultVec3f(&gZeroVec3f, &this->shadowPos);
    }
}

void EnRz_Draw(Actor* thisx, PlayState* play) {
    EnRz* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    if (!EN_RZ_GET_SISTER(thisx)) {
        AnimatedMat_DrawStepOpa(play, Lib_SegmentedToVirtual(&object_rz_Matanimheader_00D768), ROSA_SISTERS_JUDO);
    } else {
        AnimatedMat_DrawStepOpa(play, Lib_SegmentedToVirtual(&object_rz_Matanimheader_00D768), ROSA_SISTERS_MARILLA);
    }

    if (this->animIndex == EN_RZ_APPLAUDING_ANIM) {
        gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sEyeTextures[4]));
    } else if (this->stateFlags & EN_RZ_STATE_2) {
        gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sEyeTextures[3]));
    } else {
        gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sEyeTextures[this->eyeIndex]));
    }

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, NULL,
                          EnRz_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
