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

void func_80BFB780(Actor* thisx, Lights* mapper, PlayState* play);
void EnRz_SetAnimation(PlayState*, EnRz*, s16 animIndex, u8 animMode, f32 transitionRate);
s32 func_80BFBA50(EnRz* this, PlayState* play);
Actor* func_80BFBDA0(EnRz* this, PlayState*);
void func_80BFC058(EnRz* this, PlayState* play);
void func_80BFC078(EnRz* this, PlayState* play);
void func_80BFC3F8(EnRz* this, PlayState* play);
void func_80BFC674(EnRz* this, PlayState* play);
void func_80BFC7E0(EnRz* this, PlayState* play);
void func_80BFC8F8(EnRz* this, PlayState* play);

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

static u64* D_80BFCCE0[] = { object_rz_Tex_00BC50, object_rz_Tex_00C190, object_rz_Tex_00C590 };

static u64* D_80BFCCEC = object_rz_Tex_00C990;

static u64* D_80BFCCF0 = object_rz_Tex_00CD90;

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

static AnimationHeader* D_80BFCD20[] = {
    &object_rz_Anim_00457C, &object_rz_Anim_003A20, &object_rz_Anim_005E50, &object_rz_Anim_003098,
    &object_rz_Anim_00059C, &object_rz_Anim_000DE8, &object_rz_Anim_0028D4,
};

static AnimationHeader* D_80BFCD3C[] = {
    &object_rz_Anim_003A20, &object_rz_Anim_003A20, &object_rz_Anim_005390, &object_rz_Anim_003098,
    &object_rz_Anim_00059C, &object_rz_Anim_000DE8, &object_rz_Anim_0028D4,
};

static LinkAnimationHeader* gLinkAnimations[] = { &gameplay_keep_Linkanim_00DF28, &gameplay_keep_Linkanim_00CF98 };

static Vec3f D_80BFCD60 = { 500.0f, -500.0f, 0.0f };

void EnRz_Init(Actor* thisx, PlayState* play) {
    EnRz* this = THIS;
    s16 tempCutscene = this->actor.cutscene;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->cutscenes) - 1; i++) {
        this->cutscenes[i] = tempCutscene;
        if (tempCutscene != -1) {
            this->actor.cutscene = tempCutscene;
            tempCutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
        }
    }

    Actor_SetScale(&this->actor, 0.01f);
    ActorShape_Init(&this->actor.shape, 0.0f, func_80BFB780, 20.0f);

    SkelAnime_InitFlex(play, &this->skelAnime, &object_rz_Skel_00D8D8, &object_rz_Anim_003A20,
                       (intptr_t)this->jointTable & ~0xF, (intptr_t)this->morphTable & ~0xF, OBJECT_RZ_LIMB_MAX);
    Animation_PlayLoop(&this->skelAnime, &object_rz_Anim_003A20);

    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;

    this->actionFunc = func_80BFC058;
    func_80BFBA50(this, play);
    this->currentAnimIndex = 9;
    this->actor.targetMode = 0;
    this->actor.terminalVelocity = -9.0f;
    this->actor.gravity = -1.0f;

    switch (EN_RZ_GET_PARAM_F(thisx)) {
        case 1:
            if (!(gSaveContext.save.weekEventReg[77] & 4)) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            EnRz_SetAnimation(play, this, 3, 0, 0.0f);
            this->actionFunc = func_80BFC674;
            this->actor.shape.yOffset = -1500.0f;
            break;

        case 2:
            this->actor.flags |= ACTOR_FLAG_10;
            if (gSaveContext.save.weekEventReg[77] & 4) {
                EnRz_SetAnimation(play, this, 8, 0, 0.0f);
            } else {
                EnRz_SetAnimation(play, this, 6, 0, 0.0f);
            }
            this->actionFunc = func_80BFC3F8;
            this->unk_40C = func_80BFBDA0(this, play);
            this->actor.uncullZoneForward = 300.0f;
            break;

        default:
            this->unk_420 |= 2;
            if (gSaveContext.save.weekEventReg[77] & 4) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            EnRz_SetAnimation(play, this, 2, 0, 0.0f);
            this->actionFunc = func_80BFC8F8;
            if (!EN_RZ_GET_PARAM_8000(thisx)) {
                this->actor.textId = 0x291C;
            } else {
                this->actor.textId = 0x2920;
            }
            break;
    }
    if (!EN_RZ_GET_PARAM_8000(thisx)) {
        this->csAction = 0x226;
    } else {
        this->csAction = 0x227;
    }

    this->unk_428 = 0;
}

void func_80BFB780(Actor* thisx, Lights* mapper, PlayState* play) {
    Vec3f oldPos;
    EnRz* this = THIS;

    if (this->currentAnimIndex == 8) {
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

void EnRz_SetAnimation(PlayState* play, EnRz* this, s16 animIndex, u8 animMode, f32 transitionRate) {
    f32 endFrame;
    AnimationHeader** animationPtr;

    if (!EN_RZ_GET_PARAM_8000(&this->actor)) {
        animationPtr = D_80BFCD20;
    } else {
        animationPtr = D_80BFCD3C;
    }
    if ((animIndex >= 0) && (animIndex < 9) && ((animIndex != this->currentAnimIndex) || (animMode != 0))) {
        if (animIndex >= 7) {
            endFrame = Animation_GetLastFrame(gLinkAnimations[animIndex - 7]);
            if (animMode == 0) {
                LinkAnimation_Change(play, &this->skelAnime, gLinkAnimations[animIndex - 7], 2.0f / 3.0f, 0.0f,
                                     endFrame, 0, transitionRate);
            } else {
                LinkAnimation_Change(play, &this->skelAnime, gLinkAnimations[animIndex - 7], 2.0f / 3.0f, 0.0f,
                                     endFrame, 0, transitionRate);
            }
        } else {
            Animation_Change(&this->skelAnime, animationPtr[animIndex], 1.0f, 0.0f,
                             Animation_GetLastFrame(animationPtr[animIndex]), animMode, transitionRate);
        }
        this->currentAnimIndex = animIndex;
    }
}

void func_80BFB9E4(PlayState* play, EnRz* this, s16 animIndex) {
    EnRz_SetAnimation(play, this, animIndex, 0, -5.0f);
}

void func_80BFBA1C(PlayState* play, EnRz* this, s16 animIndex) {
    EnRz_SetAnimation(play, this, animIndex, 0, 0.0f);
}

s32 func_80BFBA50(EnRz* this, PlayState* play) {
    if (EN_RZ_GET_PATH(&this->actor) != 0x3F) {
        this->path = &play->setupPathList[EN_RZ_GET_PATH(&this->actor)];
        if (this->path != NULL) {
            Path* path = this->path;
            Vec3s* points = (Vec3s*)Lib_SegmentedToVirtual(path->points);
            f32 temp_fv0 = points->x - this->actor.world.pos.x;
            f32 temp_fv1 = points->z - this->actor.world.pos.z;

            if ((SQ(temp_fv0) + SQ(temp_fv1)) < SQ(10.0f)) {
                this->unk_3BC = 0;
                this->unk_420 &= ~1;
            } else {
                this->unk_3BC = path->count - 1;
                this->unk_420 |= 1;
                return true;
            }
        }
    } else {
        this->path = NULL;
        this->unk_3BC = 0;
    }
    return false;
}

s32 func_80BFBB44(EnRz* this) {
    Path* path;
    Vec3s* pointPos;
    f32 temp_fa0;
    f32 temp_fa1;

    path = this->path;
    if (path == NULL) {
        return true;
    }

    pointPos = &((Vec3s*)Lib_SegmentedToVirtual(path->points))[this->unk_3BC];
    temp_fa0 = pointPos->x - this->actor.world.pos.x;
    temp_fa1 = pointPos->z - this->actor.world.pos.z;
    this->actor.world.rot.y = Math_Atan2S(temp_fa0, temp_fa1);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 2, 2000, 200);

    if ((SQ(temp_fa0) + SQ(temp_fa1)) < SQ(10.0f)) {
        if (this->unk_420 & 1) {
            this->unk_3BC--;
            if (this->unk_3BC < 0) {
                return 2;
            }
        } else {
            this->unk_3BC++;
            if (this->unk_3BC >= path->count) {
                return 2;
            }
        }
        return true;
    }
    return false;
}

s32 EnRz_CanTalk(EnRz* this, PlayState* play) {
    if (this->actor.xzDistToPlayer < 80.0f && (fabsf(this->actor.playerHeightRel) < 20.0f) &&
        Player_IsFacingActor(&this->actor, 0x3000, play)) {
        return true;
    }
    return false;
}

s32 func_80BFBCEC(EnRz* this, PlayState* play) {
    s32 pad;
    Player* player = GET_PLAYER(play);

    if (this->actor.xzDistToPlayer < 100.0f && Actor_IsFacingPlayer(&this->actor, 0x3000) &&
        player->stateFlags2 & 0x2000000) {
        return true;
    }

    return false;
}

void func_80BFBD54(EnRz* this, PlayState* play) {
    if (this->currentAnimIndex < 7) {
        SkelAnime_Update(&this->skelAnime);
    } else {
        LinkAnimation_Update(play, &this->skelAnime);
    }
}

Actor* func_80BFBDA0(EnRz* this, PlayState* play) {
    Actor* npc = play->actorCtx.actorLists[ACTORCAT_NPC].first;

    while (npc != NULL) {
        if ((npc->id == ACTOR_EN_RZ) && (EN_RZ_GET_PARAM_F(&this->actor) == EN_RZ_GET_PARAM_F(npc))) {
            if (&this->actor != npc) {
                return npc;
            }
        }
        npc = npc->next;
    }
    return NULL;
}

void func_80BFBDFC(PlayState* play) {
    if ((gSaveContext.save.weekEventReg[75] & 0x80)) {
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
    if (!EN_RZ_GET_PARAM_8000(&this->actor) && this->currentAnimIndex == 4) {
        func_800B9010(&this->actor, NA_SE_EV_CLAPPING_2P - SFX_FLAG);
    }
    if (Cutscene_CheckActorAction(play, this->csAction)) {
        Cutscene_ActorTranslateAndYaw(&this->actor, play, Cutscene_GetActorActionIndex(play, this->csAction));
        action = play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, this->csAction)]->action;
        if (this->unk_428 != action) {
            this->unk_428 = action;
            switch (action & 0xFFFF) {
                case 1:
                    func_80BFBA1C(play, this, 1);
                    break;

                case 2:
                    func_80BFBA1C(play, this, 5);
                    break;

                case 3:
                    func_80BFBA1C(play, this, 4);
                    break;

                case 4:
                    func_80BFBA1C(play, this, 8);
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
    func_80BFBD54(this, play);
}

void func_80BFC078(EnRz* this, PlayState* play) {
    s32 pad;
    Vec3f sp28;

    func_80BFBD54(this, play);

    if (Message_GetState(&play->msgCtx) == 5 && Message_ShouldAdvance(play)) {
        switch (play->msgCtx.currentTextId) {
            case 0x2927:
            case 0x2928:
                func_80151938(play, play->msgCtx.currentTextId + 1);
                gSaveContext.save.weekEventReg[77] |= 4;
                break;

            default:
                func_801477B4(play);
                this->actionFunc = func_80BFC3F8;
                if (this->currentAnimIndex != 8) {
                    func_80BFB9E4(play, this, 6);
                    if (this->unk_40C != NULL) {
                        func_80BFB9E4(play, (EnRz*)this->unk_40C, 6);
                    }
                }
                break;
        }
    }

    if (!EN_RZ_GET_PARAM_8000(&this->actor)) {
        sp28.x = this->actor.projectedPos.x;
        sp28.y = this->actor.projectedPos.y;
        sp28.z = this->actor.projectedPos.z;
        func_801A1FB4(3, &sp28, 0x2A, 900.0f);
    }
}

void func_80BFC19C(EnRz* this, PlayState* play) {
    func_80BFBD54(this, play);
    if (!func_80BFBE70(this, play)) {
        this->actionFunc = func_80BFC3F8;
        func_80BFBA1C(play, this, 8);
        if (this->unk_40C != NULL) {
            func_80BFBA1C(play, (EnRz*)this->unk_40C, 8);
        }
    }
}

void func_80BFC214(EnRz* this, PlayState* play) {
    func_80BFBD54(this, play);
    if (!func_80BFBE70(this, play) && func_80BFBFAC(this, play)) {
        this->actionFunc = func_80BFC19C;
    }
}

void func_80BFC270(EnRz* this, PlayState* play) {
    func_80BFBD54(this, play);
    if (Actor_HasParent(&this->actor, play)) {
        this->actor.parent = NULL;
        this->actionFunc = func_80BFC214;
        func_80BFBDFC(play);
    } else {
        Actor_PickUp(&this->actor, play, GI_HEART_PIECE, 2000.0f, 1000.0f);
    }
}

void func_80BFC2F4(EnRz* this, PlayState* play) {
    func_80BFBD54(this, play);
    if (!func_80BFBE70(this, play)) {
        func_801477B4(play);
        Actor_PickUp(&this->actor, play, GI_HEART_PIECE, 2000.0f, 1000.0f);
        this->actionFunc = func_80BFC270;
    }
}

void func_80BFC36C(EnRz* this, PlayState* play) {
    func_80BFBD54(this, play);
    if (func_80BFBFAC(this, play)) {
        gSaveContext.save.weekEventReg[77] |= 4;
        if ((gSaveContext.save.weekEventReg[75] & 0x80)) {
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

    func_80BFBD54(this, play);
    if (this->unk_40C == NULL) {
        this->unk_40C = func_80BFBDA0(this, play);
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
            if (func_80BFBCEC(this, play) && !(gSaveContext.save.weekEventReg[77] & 4) && this->unk_40C != NULL) {
                this->actor.flags |= ACTOR_FLAG_10000;
                func_800B8500(&this->actor, play, 1000.0f, 1000.0f, -1);
            } else {
                this->actor.flags &= ~ACTOR_FLAG_10000;
                func_800B8614(&this->actor, play, 120.0f);
            }
        }

        if (!EN_RZ_GET_PARAM_8000(&this->actor)) {
            sp30.x = this->actor.projectedPos.x;
            sp30.y = this->actor.projectedPos.y;
            sp30.z = this->actor.projectedPos.z;
            func_801A1FB4(3, &sp30, 0x2A, 900.0f);
        }
    }
}

void func_80BFC608(EnRz* this, PlayState* play) {
    func_80BFBD54(this, play);
    if ((Message_GetState(&play->msgCtx) == 5) && Message_ShouldAdvance(play)) {
        func_801477B4(play);
        this->actionFunc = func_80BFC674;
    }
}

void func_80BFC674(EnRz* this, PlayState* play) {
    func_80BFBD54(this, play);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actionFunc = func_80BFC608;
        if (Player_GetMask(play) == PLAYER_MASK_KAMARO) {
            Message_StartTextbox(play, 0x2925, &this->actor);
            return;
        }
        Message_StartTextbox(play, 0x2924, &this->actor);
        return;
    }

    if (EnRz_CanTalk(this, play)) {
        func_800B8614(&this->actor, play, 120.0f);
    }
}

void func_80BFC728(EnRz* this, PlayState* play) {
    func_80BFBD54(this, play);

    if ((Message_GetState(&play->msgCtx) == 5) && Message_ShouldAdvance(play)) {
        func_801477B4(play);
        this->actionFunc = func_80BFC7E0;
        this->actor.textId++;
        if (!EN_RZ_GET_PARAM_8000(&this->actor)) {
            if (this->actor.textId >= 0x2920) {
                this->actor.textId = 0x291C;
            }
        } else if (this->actor.textId >= 0x2924) {
            this->actor.textId = 0x2920;
        }
    }
}

void func_80BFC7E0(EnRz* this, PlayState* play) {
    s32 new_var;

    func_80BFBD54(this, play);
    new_var = this->timer;
    if (new_var > 0) {
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
    s32 temp_v0;

    func_80BFBD54(this, play);
    this->actor.speedXZ = 1.5f;
    temp_v0 = func_80BFBB44(this);
    if (temp_v0 != 1) {
        if (temp_v0 == 2) {
            func_80BFBA50(this, play);
            func_80BFC8AC(this, play);
        }
    } else {
        func_80BFC8AC(this, play);
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
    s32 phi_v0;
    s32 pad;
    EnRz* this = THIS;

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 40.0f, 25.0f, 40.0f, 5);

    this->actionFunc(this, play);
    if (!this->unk_412) {
        phi_v0 = false;
    } else {
        this->unk_412--;
        phi_v0 = this->unk_412;
    }

    if (!phi_v0) {
        this->unk_412 = Rand_S16Offset(60, 60);
    }

    this->unk_410 = this->unk_412;
    if (this->unk_410 >= 3) {
        this->unk_410 = 0;
    }
}

void func_80BFCAD0(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnRz* this = THIS;

    if (limbIndex == OBJECT_RZ_LIMB_0B) {
        Matrix_MultVec3f(&D_80BFCD60, &thisx->focus.pos);
    }
    if (limbIndex == OBJECT_RZ_LIMB_03) {
        Matrix_MultVec3f(&gZeroVec3f, &this->shadowPos);
    }
}

void EnRz_Draw(Actor* thisx, PlayState* play) {
    EnRz* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    if (!EN_RZ_GET_PARAM_8000(thisx)) {
        AnimatedMat_DrawStepOpa(play, Lib_SegmentedToVirtual(&object_rz_Matanimheader_00D768), 0);
    } else {
        AnimatedMat_DrawStepOpa(play, Lib_SegmentedToVirtual(&object_rz_Matanimheader_00D768), 1);
    }

    if (this->currentAnimIndex == 4) {
        gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80BFCCF0));
    } else if (this->unk_420 & 2) {
        gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80BFCCEC));
    } else {
        gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80BFCCE0[this->unk_410]));
    }

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, NULL,
                          func_80BFCAD0, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
