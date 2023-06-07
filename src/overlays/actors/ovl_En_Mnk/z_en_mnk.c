/*
 * File: z_en_mnk.c
 * Overlay: ovl_En_Mnk
 * Description: Monkey
 */

#include "z_en_mnk.h"
#include "objects/object_mnk/object_mnk.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnMnk*)thisx)

void EnMnk_Init(Actor* thisx, PlayState* play);
void EnMnk_Destroy(Actor* thisx, PlayState* play);
void EnMnk_Update(Actor* thisx, PlayState* play);
void EnMnk_Draw(Actor* thisx, PlayState* play);

// Draw funcs
void EnMnk_TiedUpMonkey_Draw(Actor* thisx, PlayState* play);
void EnMnk_HangingMonkey_Draw(Actor* thisx, PlayState* play);

// Action funcs
void EnMnk_Monkey_WaitToRunAndWaitAtEachPoint(EnMnk* this, PlayState* play);
void EnMnk_TiedUpMonkey_Wait(EnMnk* this, PlayState* play);
void EnMnk_HangingMonkey_StruggleBeforeDunk(EnMnk* this, PlayState* play);
void EnMnk_Monkey_WaitToTalkAfterRun(EnMnk* this, PlayState* play);
void EnMnk_Monkey_WaitForPlayerApproach(EnMnk* this, PlayState* play);
void EnMnk_Monkey_WaitToFollowPath(EnMnk* this, PlayState* play);
void EnMnk_TiedUpMonkey_WaitUnused(EnMnk* this, PlayState* play);
void EnMnk_TiedUpMonkey_WaitForInstrument(EnMnk* this, PlayState* play);
void EnMnk_TiedUpMonkey_WaitForCutRope(EnMnk* this, PlayState* play);
void EnMnk_HangingMonkey_WaitAfterDunk(EnMnk* this, PlayState* play);
void EnMnk_Monkey_WaitToTalkAfterSaved(EnMnk* this, PlayState* play);

void EnMnk_DoNothing(EnMnk* this, PlayState* play);
void EnMnk_Monkey_WaitOutsideWoods(EnMnk* this, PlayState* play);
void EnMnk_Monkey_WaitOutsideChamber(EnMnk* this, PlayState* play);
void EnMnk_Monkey_WaitToGuideThroughWoods(EnMnk* this, PlayState* play);
void func_80AB9084(EnMnk* this, PlayState* play);
void func_80AB92CC(EnMnk* this, PlayState* play);

// IDK
s32 EnMnk_ValidatePictograph(PlayState* play, Actor* thisx);
s32 EnMnk_AlreadyExists(EnMnk* this, PlayState* play);

const ActorInit En_Mnk_InitVars = {
    ACTOR_EN_MNK,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MNK,
    sizeof(EnMnk),
    (ActorFunc)EnMnk_Init,
    (ActorFunc)EnMnk_Destroy,
    (ActorFunc)EnMnk_Update,
    (ActorFunc)EnMnk_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x01000200, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 15, 30, 0, { 0, 0, 0 } },
};

AnimationHeader* sTiedUpMonkeyAnims[] = { &object_mnk_Anim_00D1C8, &object_mnk_Anim_00CD4C, &object_mnk_Anim_00C23C,
                                  &object_mnk_Anim_00F248, &object_mnk_Anim_00F9A4, &object_mnk_Anim_00FE34,
                                  &object_mnk_Anim_00EC44, &object_mnk_Anim_010298, &object_mnk_Anim_00CAE8 };

AnimationHeader* sTiedUpMonkeyPoleAnims[] = { &object_mnk_Anim_003584, &object_mnk_Anim_005194, &object_mnk_Anim_0052C4,
                                  &object_mnk_Anim_003854, &object_mnk_Anim_005390, &object_mnk_Anim_005414,
                                  &object_mnk_Anim_0037E8, &object_mnk_Anim_0054B4, &object_mnk_Anim_003504 };

AnimationHeader* sHangingMonkeyAnims[] = { &object_mnk_Anim_0062D8, &object_mnk_Anim_007380, &gHangingMonkeyStruggleAnim };

AnimationHeader* sHangingMonkeyRopeAnims[] = { &object_mnk_Anim_01C1B8, &object_mnk_Anim_01C1F8, &gHangingMonkeyRopeStruggleAnim };

AnimationHeader* sMonkeyAnims[] = { &object_mnk_Anim_0105DC, &object_mnk_Anim_009FE0, &object_mnk_Anim_0099B0,
                                  &object_mnk_Anim_0095B4, &object_mnk_Anim_0095B4, &object_mnk_Anim_00B864,
                                  &object_mnk_Anim_00B864, &object_mnk_Anim_009CC0, &object_mnk_Anim_009CC0,
                                  &object_mnk_Anim_008814, &object_mnk_Anim_005A08, &object_mnk_Anim_01A4F8,
                                  &object_mnk_Anim_01B468, &object_mnk_Anim_01BB0C, &object_mnk_Anim_01C17C };

u32 D_80AB9DD8[] = { 2, 2, 3, 4, 5, 6, 100 };

Color_RGBA8 sHangingMonkeySplashPrimColor = { 255, 255, 155, 255 };
Color_RGBA8 sHangingMonkeySplashEnvColor = { 255, 100, 0, 255 };

Vec3f focusPosOffset = { 300.0f, 400.0f, 0.0f };

u64* sMonkeyFaceTextures[] = { object_mnk_Tex_015020, object_mnk_Tex_015920, object_mnk_Tex_016120, object_mnk_Tex_016920, object_mnk_Tex_017120, object_mnk_Tex_017920, object_mnk_Tex_018120, NULL, NULL, NULL };

void EnMnk_TiedUpMonkey_ChangeAnims(EnMnk* this, s32 animNum, u8 mode, f32 transitionRate) {
    Animation_Change(&this->skelAnime, sTiedUpMonkeyAnims[animNum], 1.0f, 0.0f, Animation_GetLastFrame(&sTiedUpMonkeyAnims[animNum]->common),
                     mode, transitionRate);
    Animation_Change(&this->propSkelAnime, sTiedUpMonkeyPoleAnims[animNum], 1.0f, 0.0f, Animation_GetLastFrame(&sTiedUpMonkeyPoleAnims[animNum]->common),
                     mode, transitionRate);

    switch (animNum) {
        case 0:
            this->unk_3E0 = 5;
            break;
        case 6:
            this->unk_3E0 = 4;
            break;
        case 3:
        case 8:
            this->unk_3E0 = 6;
            break;
        default:
            this->unk_3E0 = 0;
            break;
    }
    this->curAnim = animNum;
}

void EnMnk_TiedUpMonkey_SetAnim(EnMnk* this, s32 animNum) {
    EnMnk_TiedUpMonkey_ChangeAnims(this, animNum, ANIMMODE_LOOP, -5.0f);
}

void EnMnk_TiedUpMonkey_SetNewAnim(EnMnk* this, s32 animNum) {
    if (this->curAnim != animNum) {
        EnMnk_TiedUpMonkey_ChangeAnims(this, animNum, ANIMMODE_LOOP, -5.0f);
    }
}

void EnMnk_HangingMonkey_ChangeAnims(EnMnk* this, s32 animNum, u8 mode, f32 transitionRate) {
    Animation_Change(&this->skelAnime, sHangingMonkeyAnims[animNum], 1.0f, 0.0f, Animation_GetLastFrame(&sHangingMonkeyAnims[animNum]->common),
                     mode, transitionRate);
    Animation_Change(&this->propSkelAnime, sHangingMonkeyRopeAnims[animNum], 1.0f, 0.0f, Animation_GetLastFrame(&sHangingMonkeyRopeAnims[animNum]->common),
                     mode, transitionRate);
    this->curAnim = animNum;
}

void EnMnk_HangingMonkey_SetAnim(EnMnk* this, s32 animNum) {
    EnMnk_HangingMonkey_ChangeAnims(this, animNum, ANIMMODE_LOOP, -5.0f);
}

void EnMnk_Monkey_ChangeAnim(EnMnk* this, s32 animNum, u8 mode, f32 morphFrames) {
    s32 pad;

    if (animNum == 100) {
        animNum = (s32)Rand_ZeroFloat(3.99f) + 7;
    }
    if ((animNum == 4) || (animNum == 6)) {
        Animation_Change(&this->skelAnime, sMonkeyAnims[animNum], -1.0f, Animation_GetLastFrame(&sMonkeyAnims[animNum]->common),
                         0.0f, mode, morphFrames);
    } else {
        Animation_Change(&this->skelAnime, sMonkeyAnims[animNum], 1.0f, 0.0f,
                         Animation_GetLastFrame(&sMonkeyAnims[animNum]->common), mode, morphFrames);
    }
    this->unk_3E0 = 0;
    this->curAnim = animNum;
}

void EnMnk_Monkey_SetAnim(EnMnk* this, s32 animNum) {
    EnMnk_Monkey_ChangeAnim(this, animNum, ANIMMODE_LOOP, -5.0f);
}

void EnMnk_Monkey_SetupWaitToRunAndWaitAtEachPoint(EnMnk* this, PlayState* play) {
    this->picto.actor.textId = 0x7D8; // "Ah! You came! You came!"
    this->actionFunc = EnMnk_Monkey_WaitToRunAndWaitAtEachPoint;
    this->destPointIndex = 0;
    this->unk_3E4 |= 0x3;
    this->unk_3E4 &= ~0x40;
    Animation_PlayLoop(&this->skelAnime, &object_mnk_Anim_008814);
    this->picto.actor.velocity.y = 0.0f;
    this->picto.actor.terminalVelocity = 0.0f;
    this->picto.actor.gravity = 0.0f;
}

void EnMnk_Monkey_StartInvisible(EnMnk* this, PlayState* play) {
    this->picto.actor.draw = NULL;
    this->picto.actor.flags &= ~ACTOR_FLAG_1;
    this->collider.dim.radius = 0x64;
    this->unk_3E4 |= 0x8;
    this->unk_3E4 |= 0x20;
    if ((GET_MONKEY_7F(this) != 0x7F) && Flags_GetSwitch(play, GET_MONKEY_7F(this))) {
        Actor_Kill(&this->picto.actor);
    }
}

void EnMnk_TiedUpMonkey_Init(EnMnk* this, PlayState* play) {
    EnMnk* this2 = this;
    s16 curCutsceneIndex;
    s32 i;

    this2->actionFunc = EnMnk_TiedUpMonkey_Wait;
    this2->picto.actor.flags |= ACTOR_FLAG_2000000;
    SkelAnime_InitFlex(play, &this2->propSkelAnime, &gTiedUpMonkeyPoleSkeleton, &object_mnk_Anim_003584, this2->propJointTable,
                       this2->propMorphTable, 5);
    this2->unk_3D0 = 4;
    this2->curAnim = -1;
    EnMnk_TiedUpMonkey_ChangeAnims(this2, TIEDUPMONKEY_ANIM_KICKAROUND, ANIMMODE_ONCE, 0.0f);
    this2->picto.actor.draw = EnMnk_TiedUpMonkey_Draw;
    this2->picto.actor.shape.shadowDraw = NULL;
    this2->unk_3E4 |= 0x223;
    curCutsceneIndex = this2->picto.actor.csId;

    for (i = 0; i < ARRAY_COUNT(this2->cutsceneIndices); i++) {
        this2->cutsceneIndices[i] = curCutsceneIndex;
        if (curCutsceneIndex != -1) {
            this2->picto.actor.csId = curCutsceneIndex;
            curCutsceneIndex = CutsceneManager_GetAdditionalCsId(this2->picto.actor.csId);
        }
    }

    this2->unk_3BC = -1;
    this2->picto.actor.csId = this2->cutsceneIndices[0];
}

void EnMnk_HangingMonkey_Init(EnMnk* this, PlayState* play) {
    func_800BC154(play, &play->actorCtx, &this->picto.actor, ACTORCAT_PROP);
    this->actionFunc = EnMnk_HangingMonkey_StruggleBeforeDunk;
    this->picto.actor.textId = 0x8E8; // "Ooh! Hot! Hot! St-stop it! Please!!!"
    SkelAnime_InitFlex(play, &this->propSkelAnime, &gHangingMonkeyRopeSkeleton, &gHangingMonkeyStruggleAnim, this->propJointTable,
                       this->propMorphTable, 4);
    EnMnk_HangingMonkey_ChangeAnims(this, HANGINGMONKEY_ANIM_STRUGGLE, ANIMMODE_LOOP, 0.0f);
    this->unk_3E0 = 5;
    this->picto.actor.draw = EnMnk_HangingMonkey_Draw;
    this->picto.actor.shape.shadowDraw = NULL;
    this->unk_3E4 |= 0x23;
    this->approachPlayerRadius = -0.3f;
    this->unk_3C8 = 60;
    play->envCtx.lightSettingOverride = 1;
    gSaveContext.save.saveInfo.weekEventReg[83] &= (u8)~0x8;
}

void EnMnk_Init(Actor* thisx, PlayState* play) {
    EnMnk* this = (EnMnk*)thisx;
    s32 pad;

    Actor_SetScale(&this->picto.actor, 0.012f);
    ActorShape_Init(&this->picto.actor.shape, 0.0f, ActorShadow_DrawCircle, 12.0f);
    this->actionFunc = EnMnk_DoNothing;
    SkelAnime_InitFlex(play, &this->skelAnime, &gMonkeySkeleton, &object_mnk_Anim_0105DC, this->jointTable,
                       this->morphTable, 23);
    Animation_PlayLoop(&this->skelAnime, &object_mnk_Anim_0105DC);
    this->unk_3E4 = 0;
    this->unk_3D4 = 0;
    this->unk_3E0 = 0;
    this->unk_3CC = 0;
    this->unk_3CE = 0;
    this->unk_3D0 = 0;
    this->picto.actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->picto.actor.colChkInfo.cylRadius = 40;
    this->picto.actor.velocity.y = -9.0f;
    this->picto.actor.terminalVelocity = -9.0f;
    this->picto.actor.gravity = -1.0f;
    Collider_InitAndSetCylinder(play, &this->collider, &this->picto.actor, &sCylinderInit);
    Collider_UpdateCylinder(&this->picto.actor, &this->collider);
    this->nextPathIndex = GET_MONKEY_F800(thisx);
    this->approachPlayerRadius = 0.0f;
    if (this->nextPathIndex == 0x1F) {
        this->nextPathIndex = -1;
    }

    switch (GET_MONKEY_TYPE(thisx)) {
        case MONKEY_0:
            if (!Flags_GetSwitch(play, GET_MONKEY_7F(this)) ||
                Flags_GetSwitch(play, GET_MONKEY_7F(this) + 1) || (gSaveContext.save.saveInfo.weekEventReg[9] & 0x80)) {
                Actor_Kill(&this->picto.actor);
                return;
            }
            break;
        case MONKEY_OUTSIDEWOODS:
        case MONKEY_OUTSIDEPALACE:
            if (Flags_GetSwitch(play, GET_MONKEY_7F(this))) {
                Actor_Kill(thisx);
                return;
            }
            break;
        case MONKEY_OUTSIDECHAMBER:
            if (Flags_GetSwitch(play, GET_MONKEY_7F(this)) || (gSaveContext.save.saveInfo.weekEventReg[29] & 0x80)) {
                Actor_Kill(thisx);
                return;
            }
            break;
        case MONKEY_TIED_UP:
            if ((gSaveContext.save.saveInfo.weekEventReg[9] & 0x80) || (gSaveContext.save.saveInfo.weekEventReg[23] & 0x20)) {
                Actor_Kill(thisx);
                return;
            }
            break;
        case MONKEY_HANGING:
            if (!(gSaveContext.save.saveInfo.weekEventReg[9] & 0x80) || (gSaveContext.save.saveInfo.weekEventReg[23] & 0x20)) {
                Actor_Kill(thisx);
                return;
            }
            break;
        case MONKEY_8:
            if (!(gSaveContext.save.saveInfo.weekEventReg[23] & 0x20) || (gSaveContext.save.saveInfo.weekEventReg[29] & 0x80)) {
                Actor_Kill(thisx);
                return;
            }
            break;
        case MONKEY_AFTER_SAVED:
            if (!(gSaveContext.save.saveInfo.weekEventReg[29] & 0x80)) {
                Actor_Kill(thisx);
                return;
            }
            break;
        case MONKEY_BY_WITCH:
            if ((gSaveContext.save.saveInfo.weekEventReg[79] & 0x2) || (gSaveContext.save.saveInfo.weekEventReg[12] & 0x8) ||
                Flags_GetSwitch(play, GET_MONKEY_7F(this))) {
                Actor_Kill(thisx);
                return;
            }
            break;
        case MONKEY_WOODS_GUIDE:
            if ((gSaveContext.save.saveInfo.weekEventReg[79] & 0x2) || (gSaveContext.save.saveInfo.weekEventReg[12] & 0x8)) {
                Actor_Kill(thisx);
                return;
            }
            if (EnMnk_AlreadyExists(this, play)) {
                Actor_Kill(thisx);
                return;
            }
            break;
        default:
            break;
    }

    switch (GET_MONKEY_TYPE(thisx)) {
        case MONKEY_0:
            EnMnk_Monkey_SetupWaitToRunAndWaitAtEachPoint(this, play);
            break;
        case MONKEY_OUTSIDEWOODS:
            this->actionFunc = EnMnk_Monkey_WaitOutsideWoods;
            gSaveContext.eventInf[2] &= (u8)~0x20;
            gSaveContext.eventInf[2] &= (u8)~0x40;
            this->picto.actor.textId = 0x7D0; // "You have strange powers, no?"
            EnMnk_Monkey_StartInvisible(this, play);
            break;
        case MONKEY_OUTSIDECHAMBER:
            this->picto.actor.textId = 0x7D3; // "Was my brother alright?"
            this->actionFunc = EnMnk_Monkey_WaitOutsideChamber;
            EnMnk_Monkey_StartInvisible(this, play);
            this->collider.dim.radius = 0x78;
            break;
        case MONKEY_BY_WITCH:
            EnMnk_Monkey_SetAnim(this, 0);
            this->actionFunc = EnMnk_Monkey_WaitToFollowPath;
            this->unk_3C8 = 0;
            this->unk_3E4 |= 2;
            this->picto.actor.flags &= ~ACTOR_FLAG_1;
            this->picto.actor.velocity.y = 0.0f;
            this->picto.actor.terminalVelocity = 0.0f;
            this->picto.actor.gravity = 0.0f;
            break;
        case MONKEY_OUTSIDEPALACE:
            EnMnk_Monkey_SetAnim(this, 0);
            this->actionFunc = EnMnk_Monkey_WaitToFollowPath;
            this->unk_3C8 = 0;
            break;
        case MONKEY_TIED_UP:
            EnMnk_TiedUpMonkey_Init(this, play);
            break;
        case MONKEY_HANGING:
            EnMnk_HangingMonkey_Init(this, play);
            break;
        case MONKEY_WOODS_GUIDE:
            this->picto.actor.room = -1;
            EnMnk_Monkey_SetAnim(this, 0);
            this->actionFunc = EnMnk_Monkey_WaitToGuideThroughWoods;
            this->unk_3C8 = 0;
            this->destPointIndex = 0;
            switch (this->picto.actor.home.rot.x) {
                case 1:
                    this->picto.actor.textId = 0x7DD; // "Mmm... Follow me!"
                    break;
                case 2:
                    this->picto.actor.textId = 0x7DE; // "Mmm... Follow me!"
                    break;
                default:
                    this->picto.actor.textId = 0x7DC; // "Mmm... Follow me!"
                    break;
            }
            break;
        case MONKEY_8:
            this->actionFunc = func_80AB9084;
            this->unk_3D0 = 0;
            break;
        case MONKEY_AFTER_SAVED:
            EnMnk_Monkey_SetAnim(this, 0);
            this->unk_3C8 = 0;
            this->actionFunc = EnMnk_Monkey_WaitToTalkAfterSaved;
            this->picto.actor.textId = 0x8E5; // "I'm sorry for all that trouble."
            break;
        case MONKEY_10:
            this->actionFunc = func_80AB92CC;
            this->unk_3D0 = 0;
            break;
        default:
        dummy:
            this->actionFunc = EnMnk_DoNothing;
            break;
    }

    this->picto.actor.world.rot.x = this->picto.actor.world.rot.z = 0;
    this->picto.actor.shape.rot.x = this->picto.actor.shape.rot.z = 0;
    this->picto.validationFunc = EnMnk_ValidatePictograph;
}

void EnMnk_Destroy(Actor* thisx, PlayState* play) {
    EnMnk* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
    if ((GET_MONKEY_TYPE(this) == MONKEY_TIED_UP) && (this->unk_3E4 & 0x2000)) {
        Item_Give(play, ITEM_SONG_SONATA);
        gSaveContext.eventInf[2] &= (u8)~0x10;
    }
}

s32 EnMnk_AlreadyExists(EnMnk* this, PlayState* play) {
    Actor* thisActor = &this->picto.actor;
    Actor* nextActor = NULL;
    Actor* curActor;

    while (true) {
        curActor = SubS_FindActor(play, nextActor, ACTORCAT_NPC, ACTOR_EN_MNK);
        if ((curActor != NULL) && (curActor != thisActor)) {
            if ((thisActor->home.pos.x == curActor->home.pos.x) && (thisActor->home.pos.y == curActor->home.pos.y) &&
                (thisActor->home.pos.z == curActor->home.pos.z)) {
                return true;
            } else {
                nextActor = curActor->next;
                continue;
            }
        }

        if (curActor != NULL && curActor->next != NULL) {
            nextActor = curActor->next;
        } else {
            return false;
        }
    };
}

s32 EnMnk_ValidatePictograph(PlayState* play, Actor* thisx) {
    return Snap_ValidatePictograph(play, thisx, PICTO_VALID_MONKEY, &thisx->focus.pos, &thisx->shape.rot, 50.0f, 500.0f, -1);
}

void EnMnk_PlayWalkSfx(EnMnk* this) {
    if (Animation_OnFrame(&this->skelAnime, 1.0f) != 0) {
        Actor_PlaySfx(&this->picto.actor, NA_SE_EV_MONKEY_VO_WALK);
        Actor_PlaySfx(&this->picto.actor, NA_SE_EV_MONKEY_WALK);
    }
}

void EnMnk_PlayWaterWalkSfx(EnMnk* this) {
    if (Animation_OnFrame(&this->skelAnime, 1.0f) != 0) {
        Actor_PlaySfx(&this->picto.actor, NA_SE_EV_MONKEY_VO_WALK);
        Actor_PlaySfx(&this->picto.actor, NA_SE_EV_WALK_WATER);
    }
}

void EnMnk_SpawnWaterEffects(EnMnk* this, PlayState* play) {
    Vec3f* effSpawnPos = &this->picto.actor.world.pos;

    EffectSsGRipple_Spawn(play, effSpawnPos, 150, 500, 0);
    EffectSsGSplash_Spawn(play, effSpawnPos, NULL, NULL, 0, 200);
}

void EnMnk_StartNextPath(EnMnk* this, PlayState* play) {
    s32 nextPathIndex;

    EnMnk_Monkey_SetAnim(this, 1);
    nextPathIndex = this->nextPathIndex;
    this->picto.actor.speed = 0.0f;
    if (nextPathIndex != -1) {
        this->path = &play->setupPathList[nextPathIndex];
    } else {
        this->path = NULL;
    }
}

s32 EnMnk_FollowPath(EnMnk* this, u16 flags) {
    Path* path;
    Vec3s* destPoint;
    f32 dx;
    f32 dz;
    f32 distSquared;
    s16 arcTan;

    if (this->path == NULL) {
        return FOLLOWPATH_RESULT_SHORTRANGE_REACHEDPOINT;
    }

    path = this->path;
    destPoint = &((Vec3s*)Lib_SegmentedToVirtual(path->points))[this->destPointIndex];
    dx = destPoint->x - this->picto.actor.world.pos.x;
    dz = destPoint->z - this->picto.actor.world.pos.z;
    arcTan = Math_Atan2S_XY(dz, dx);
    Math_SmoothStepToS(&this->picto.actor.world.rot.y, arcTan, 2, 0xBB8, 0xC8);
    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.world.rot.y, 2, 0xBB8, 0xC8);
    arcTan -= this->picto.actor.world.rot.y;

    if (ABS_ALT(arcTan) < 0x3E8) {
        if (this->picto.actor.speed < 7.5f) {
            this->picto.actor.speed += 1.5f;
        }
    } else {
        if (this->picto.actor.speed > 4.0f) {
            this->picto.actor.speed -= 1.5f;
        } else if (this->picto.actor.speed < 2.0f) {
            this->picto.actor.speed += 1.5f;
        }
    }

    distSquared = (dx * dx) + (dz * dz);
    if (distSquared < 64.0f) {
        this->destPointIndex++;
        this->picto.actor.world.pos.x = destPoint->x;
        this->picto.actor.world.pos.z = destPoint->z;
        if (this->destPointIndex >= path->count) {
            return FOLLOWPATH_RESULT_SHORTRANGE_FINISHEDPATH;
        }
        if (flags & FOLLOWPATH_FLAGS_REACHNEXTPOINT) {
            return FOLLOWPATH_RESULT_SHORTRANGE_REACHEDPOINT;
        }
    } else if ((flags & FOLLOWPATH_FLAGS_LONGRANGE) && (distSquared < 400.0f)) {
        this->destPointIndex++;
        if (this->destPointIndex >= path->count) {
            return FOLLOWPATH_RESULT_LONGRANGE_FINISHEDPATH;
        }
        if (flags & FOLLOWPATH_FLAGS_REACHNEXTPOINT) {
            return FOLLOWPATH_RESULT_LONGRANGE_REACHEDPOINT;
        }
    }
    return FOLLOWPATH_RESULT_FOLLOWING;
}

void func_80AB5F6C(EnMnk* this) {
    s32 pad;
    u32 temp_a1;

    this->picto.actor.shape.rot.y = this->picto.actor.yawTowardsPlayer;
    this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;
    SkelAnime_Update(&this->skelAnime);
    if ((s32)this->skelAnime.curFrame == 0) {
        if (this->unk_3C8 < 0) {
            EnMnk_Monkey_ChangeAnim(this, 0x64, ANIMMODE_LOOP, 0.0f);
            this->unk_3C8++;
        } else if (this->unk_3C8 > 0) {
            this->unk_3C8--;
        } else {

            do {
                temp_a1 = D_80AB9DD8[(s32)Rand_ZeroFloat(7.0f)];
            } while (temp_a1 == this->unk_3D4);

            EnMnk_Monkey_ChangeAnim(this, temp_a1, ANIMMODE_LOOP, 0.0f);
            switch (temp_a1) {
                case 100:
                    this->unk_3C8 = -(s32)(Rand_ZeroFloat(6.0f) + 6.0f);
                    break;
                case 2:
                    this->unk_3C8 = Rand_ZeroFloat(6.0f) + 6.0f;
                    break;
                default:
                    this->unk_3C8 = Rand_ZeroFloat(2.0f) + 1.0f;
                    break;
            }
            this->unk_3D4 = temp_a1;
        }
    }
}

void func_80AB60FC(EnMnk* this, PlayState* play) {
    f32 depthInWater;

    SkelAnime_Update(&this->skelAnime);
    if (EnMnk_FollowPath(this, 0) != FOLLOWPATH_RESULT_FOLLOWING) {
        this->nextPathIndex = this->path->additionalPathIndex;
        if (this->nextPathIndex == 0xFF) {
            Flags_SetSwitch(play, GET_MONKEY_7F(this) + 1);
            Actor_Kill(&this->picto.actor);
            return;
        }
    }

    depthInWater = this->picto.actor.depthInWater;
    if (depthInWater > 0.0f) {
        this->picto.actor.world.pos.y += depthInWater;
        if ((s32)this->skelAnime.curFrame == 0) {
            EnMnk_SpawnWaterEffects(this, play);
        }
        EnMnk_PlayWaterWalkSfx(this);
        return;
    }
    if (this->picto.actor.bgCheckFlags & 1) {
        EnMnk_PlayWalkSfx(this);
    }
}

void func_80AB61E8(EnMnk* this, PlayState* play) {
    this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;
    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.world.rot.y, 2, 0xBB8, 0xC8);
    if ((Message_GetState(&play->msgCtx) == 5) && Message_ShouldAdvance(play)) {
        switch (play->msgCtx.currentTextId) {
            case 0x7D9: // "So? So? You get?"
                Message_ContinueTextbox(play, 0x7DA);
                EnMnk_Monkey_SetAnim(this, 3);
                break;
            case 0x7DA:
                Message_ContinueTextbox(play, 0x7DB);
                EnMnk_Monkey_SetAnim(this, 2);
                break;
            case 0x7DB:
                Message_CloseTextbox(play);
                EnMnk_StartNextPath(this, play);
                this->destPointIndex = 0;
                this->actionFunc = func_80AB60FC;
                this->picto.actor.velocity.y = -20.0f;
                this->picto.actor.terminalVelocity = -20.0f;
                break;
        }
    }
    SkelAnime_Update(&this->skelAnime);
}

void func_80AB6304(EnMnk* this, PlayState* play) {
    this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;
    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.world.rot.y, 2, 0xBB8, 0xC8);
    if ((Message_GetState(&play->msgCtx) == 5) && Message_ShouldAdvance(play)) {
        this->unk_3E4 |= 4;
    }
    SkelAnime_Update(&this->skelAnime);
    if (this->unk_3E4 & 0x4) {
        Message_ContinueTextbox(play, 0x7D9); // "So? So? You get?"
        EnMnk_Monkey_SetAnim(this, 7);
        this->actionFunc = func_80AB61E8;
        this->unk_3E4 &= ~0x4;
    }
}

void func_80AB63CC(EnMnk* this, PlayState* play) {
    s32 pad;

    if ((Message_GetState(&play->msgCtx) == 5) && Message_ShouldAdvance(play)) {
        this->unk_3E4 |= 4;
    }
    this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;
    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.world.rot.y, 2, 0xBB8, 0xC8);
    if (SkelAnime_Update(&this->skelAnime)) {
        Animation_PlayLoop(&this->skelAnime, &object_mnk_Anim_008814);
        this->actionFunc = func_80AB6304;
    }
    if (this->picto.actor.velocity.y < 0.0f) {
        this->unk_3E4 &= ~0x2;
    }
    if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
        Actor_PlaySfx(&this->picto.actor, NA_SE_EV_MONKEY_VO_JOY);
    }
}

void func_80AB64B8(EnMnk* this, PlayState* play) {
    if (!(this->unk_3E4 & 0x8)) {
        SkelAnime_Update(&this->skelAnime);
        this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;
        Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.world.rot.y, 2, 0xBB8, 0xC8);
    }

    if (Actor_ProcessTalkRequest(&this->picto.actor, &play->state)) {
        this->picto.actor.flags &= ~ACTOR_FLAG_10000;
        this->actionFunc = func_80AB63CC;
        EnMnk_Monkey_ChangeAnim(this, 9, ANIMMODE_ONCE, -5.0f);
        this->picto.actor.velocity.y = 3.6f;
        this->picto.actor.terminalVelocity = -9.0f;
        this->picto.actor.gravity = -0.4f;
        this->unk_3E4 &= ~0x1;
        this->unk_3E4 &= ~0x4;
    } else if (this->picto.actor.xzDistToPlayer < 100.0f) {
        this->picto.actor.flags |= ACTOR_FLAG_10000;
        func_800B8614(&this->picto.actor, play, 120.0f);
    } else {
        this->picto.actor.flags &= ~ACTOR_FLAG_10000;
    }
}

void EnMnk_Monkey_RunAndWaitAtEachPoint(EnMnk* this, PlayState* play) {
    FollowPathResult temp_v0;

    SkelAnime_Update(&this->skelAnime);
    temp_v0 = EnMnk_FollowPath(this, FOLLOWPATH_FLAGS_REACHNEXTPOINT | FOLLOWPATH_FLAGS_LONGRANGE);
    if (temp_v0 != FOLLOWPATH_RESULT_FOLLOWING) {
        if ((temp_v0 == FOLLOWPATH_RESULT_SHORTRANGE_FINISHEDPATH) || (temp_v0 == FOLLOWPATH_RESULT_LONGRANGE_FINISHEDPATH)) {
            this->nextPathIndex = this->path->additionalPathIndex;
            if (this->nextPathIndex == 0xFF) {
                this->nextPathIndex = -1;
            }
            this->path = &play->setupPathList[this->nextPathIndex];
            this->destPointIndex = 0;
            EnMnk_Monkey_SetAnim(this, 0);
            this->actionFunc = func_80AB64B8;
            this->picto.actor.terminalVelocity = -9.0f;
            this->picto.actor.velocity.y = 0.0f;
            this->picto.actor.speed = 0.0f;
            this->picto.actor.gravity = -1.0f;
        } else if (this->picto.actor.xzDistToPlayer > 160.0f) {
            this->actionFunc = EnMnk_Monkey_WaitToRunAndWaitAtEachPoint;
            this->unk_3E4 |= 3;
            this->picto.actor.speed = 0.0f;
            EnMnk_Monkey_SetAnim(this, 9);
            return;
        }
    }

    if (this->unk_3E4 & 0x40) {
        EnMnk_PlayWalkSfx(this);
    } else {
        if ((s32)this->skelAnime.curFrame == 0) {
            EnMnk_SpawnWaterEffects(this, play);
        }
        EnMnk_PlayWaterWalkSfx(this);
    }
}

void EnMnk_Monkey_WaitToRunAndWaitAtEachPoint(EnMnk* this, PlayState* play) {
    s32 pad[2];

    this->picto.actor.shape.rot.y = this->picto.actor.yawTowardsPlayer;
    this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;
    SkelAnime_Update(&this->skelAnime);
    if (this->picto.actor.xzDistToPlayer < 160.0f) {
        this->unk_3E4 |= 0x80;
        EnMnk_StartNextPath(this, play);
        this->actionFunc = EnMnk_Monkey_RunAndWaitAtEachPoint;
        this->unk_3E4 &= ~0x1;
        this->unk_3E4 &= ~0x2;
    }
    if ((this->unk_3E4 & 0x40) == 0) {
        if (((s32)this->skelAnime.curFrame == 0) || (Animation_OnFrame(&this->skelAnime, 14.0f))) {
            EnMnk_SpawnWaterEffects(this, play);
        }
    }
    if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
        if ((this->unk_3D4 % 4) != 0) {
            Actor_PlaySfx(&this->picto.actor, NA_SE_EV_MONKEY_VO_JOY);
        }
        this->unk_3D4++;
    }
}

void EnMnk_Monkey_TalkAfterRun(EnMnk* this, PlayState* play) {
    if ((Message_GetState(&play->msgCtx) == 5) && Message_ShouldAdvance(play)) {
        this->unk_3E4 |= 4;
        Message_CloseTextbox(play);
    }
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->unk_3E4 & 0x4) {
            EnMnk_Monkey_SetAnim(this, 0);
            this->actionFunc = EnMnk_Monkey_WaitToTalkAfterRun;
        } else {
            Animation_PlayOnce(&this->skelAnime, &object_mnk_Anim_009CC0);
        }
    }
}

void EnMnk_Monkey_WaitToTalkAfterRun(EnMnk* this, PlayState* play) {
    s32 pad[2];

    this->picto.actor.shape.rot.y = this->picto.actor.yawTowardsPlayer;
    this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;
    SkelAnime_Update(&this->skelAnime);
    if (Actor_ProcessTalkRequest(&this->picto.actor, &play->state)) {
        Animation_PlayOnce(&this->skelAnime, &object_mnk_Anim_009CC0);
        this->actionFunc = EnMnk_Monkey_TalkAfterRun;
        this->unk_3E4 &= ~0x4;
    } else if (this->picto.actor.xzDistToPlayer < 100.0f) {
        func_800B8614(&this->picto.actor, play, 120.0f);
    }
}

void EnMnk_Monkey_Run(EnMnk* this, PlayState* play) {
    s32 temp_v1;

    SkelAnime_Update(&this->skelAnime);
    if (EnMnk_FollowPath(this, FOLLOWPATH_FLAGS_LONGRANGE) != FOLLOWPATH_RESULT_FOLLOWING) {
        EnMnk_Monkey_SetAnim(this, 0);
        this->picto.actor.velocity.y = -9.0f;
        this->picto.actor.terminalVelocity = -9.0f;
        this->picto.actor.gravity = -1.0f;
        this->picto.actor.speed = 0.0f;
        if (GET_MONKEY_TYPE(this) == MONKEY_OUTSIDECHAMBER) {
            temp_v1 = GET_MONKEY_7F(this);
            if (temp_v1 != 0x7F) {
                Flags_SetSwitch(play, temp_v1 + 1);
            }
            Actor_Kill(&this->picto.actor);
        } else {
            this->picto.actor.textId = 0x7D2; // "Help!"
            this->actionFunc = EnMnk_Monkey_WaitToTalkAfterRun;
        }
    }

    if (this->picto.actor.depthInWater > 0.0f) {
        this->picto.actor.world.pos.y += this->picto.actor.depthInWater;
        if ((s32)this->skelAnime.curFrame == 0) {
            EnMnk_SpawnWaterEffects(this, play);
        }
        EnMnk_PlayWaterWalkSfx(this);
    } else if (this->picto.actor.bgCheckFlags & 0x1) {
        EnMnk_PlayWalkSfx(this);
    }
}

void EnMnk_Monkey_WaitToRun(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (gSaveContext.eventInf[2] & 0x20) {
        EnMnk_StartNextPath(this, play);
        this->destPointIndex = 0;
        this->actionFunc = EnMnk_Monkey_Run;
        this->collider.dim.radius = 0xF;
        Collider_UpdateCylinder(&this->picto.actor, &this->collider);
        this->unk_3E4 &= ~0x8;
    }
}

void EnMnk_Monkey_SetupRunAfterTalk(EnMnk* this, PlayState* play) {
    Message_CloseTextbox(play);
    EnMnk_StartNextPath(this, play);
    this->destPointIndex = 0;
    this->actionFunc = EnMnk_Monkey_Run;
    this->collider.dim.radius = 0xF;
    Collider_UpdateCylinder(&this->picto.actor, &this->collider);
    this->unk_3E0 = 0;
    this->unk_3E4 &= ~0x8;
}

void EnMnk_Monkey_TalkAfterApproach(EnMnk* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        EnMnk_Monkey_ChangeAnim(this, 0x64, ANIMMODE_ONCE, 0.0f);
        SkelAnime_Update(&this->skelAnime);
    }

    switch (Message_GetState(&play->msgCtx)) {
        case 4:
            if (Message_ShouldAdvance(play)) {
                switch (play->msgCtx.choiceIndex) {
                    case 1:
                        func_8019F208();
                        EnMnk_Monkey_ChangeAnim(this, 0xA, ANIMMODE_ONCE, -5.0f);
                        Message_ContinueTextbox(play, 0x7D7); // "Oh! You smart."
                        break;
                    case 0:
                        func_8019F230();
                        EnMnk_Monkey_SetAnim(this, 7);
                        Message_ContinueTextbox(play, 0x7D6); // "Mmm...so..."
                        this->unk_3E0 = 6;
                        break;
                }
            }
            break;
        case 5:
            if (Message_ShouldAdvance(play)) {
                switch (play->msgCtx.currentTextId) {
                    case 0x7D0: // "You have strange powers, no?"
                        EnMnk_Monkey_SetAnim(this, 3);
                        Message_ContinueTextbox(play, 0x7D1); // "Lately, this swamp, filled with poison water."
                        this->unk_3E0 = 5;
                        break;
                    case 0x7D3: // "Was my brother alright?"
                    case 0x7D6: // "Mmm...so..."
                        EnMnk_Monkey_SetAnim(this, 3);
                        Message_ContinueTextbox(play, 0x7D4); // "Did you see entrance to cage?"
                        break;
                    case 0x7D1: // "Lately, this swamp, filled with poison water."
                        EnMnk_Monkey_SetAnim(this, 7);
                        Message_ContinueTextbox(play, 0x7D2); // "Help!"
                        this->unk_3E0 = 4;
                        break;
                    case 0x7D4: // "Did you see entrance to cage?"
                        EnMnk_Monkey_SetAnim(this, 5);
                        Message_ContinueTextbox(play, 0x7D5);
                        this->unk_3E0 = 6;
                        break;
                    case 0x7D2: // "Help!"
                        gSaveContext.eventInf[2] |= 0x20;
                        EnMnk_Monkey_SetupRunAfterTalk(this, play);
                        gSaveContext.save.saveInfo.weekEventReg[0x4F] |= 0x2;
                        break;
                    case 0x7D7: // "Oh! You smart."
                        EnMnk_Monkey_SetupRunAfterTalk(this, play);
                        gSaveContext.save.saveInfo.weekEventReg[8] |= 0x2;
                        break;
                }
            }
            break;
    }
}

void EnMnk_Monkey_MoveRelativeToPlayer(EnMnk* this, PlayState* play) {
    Player* player;
    s16 angleToPlayer;

    player = GET_PLAYER(play);
    angleToPlayer = Math_Atan2S_XY(player->actor.world.pos.z - this->picto.actor.home.pos.z,
                             player->actor.world.pos.x - this->picto.actor.home.pos.x);
    this->picto.actor.shape.rot.y = angleToPlayer;
    if (this->unk_3E4 & 0x10) {
        this->picto.actor.shape.rot.y = (this->picto.actor.shape.rot.y + 0x8000) & 0xFFFF;
    }
    this->picto.actor.world.rot.y = this->picto.actor.shape.rot.y;
    this->picto.actor.world.pos.x = (Math_SinS(angleToPlayer) * this->approachPlayerRadius) + this->picto.actor.home.pos.x;
    this->picto.actor.world.pos.z = (Math_CosS(angleToPlayer) * this->approachPlayerRadius) + this->picto.actor.home.pos.z;
}

void EnMnk_Monkey_UnapproachPlayer(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    this->approachPlayerRadius -= 5.0f;
    EnMnk_Monkey_MoveRelativeToPlayer(this, play);
    if (this->approachPlayerRadius < 4.0f) {
        EnMnk_Monkey_SetAnim(this, 0);
        this->actionFunc = EnMnk_Monkey_WaitForPlayerApproach;
        this->unk_3E4 &= ~0x10;
        this->approachPlayerRadius = 0.0f;
    }
    EnMnk_PlayWalkSfx(this);
    if ((GET_MONKEY_TYPE(this) == MONKEY_OUTSIDEWOODS) && (GET_MONKEY_7F(this) != 0x7F) &&
        (Flags_GetSwitch(play, GET_MONKEY_7F(this)) != 0)) {
        EnMnk_Monkey_SetAnim(this, 2);
        this->actionFunc = EnMnk_Monkey_WaitToRun;
    }
}

void EnMnk_Monkey_WaitToTalkAfterApproach(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    EnMnk_Monkey_MoveRelativeToPlayer(this, play);
    if (Actor_ProcessTalkRequest(&this->picto.actor, &play->state)) {
        if (GET_MONKEY_TYPE(this) == MONKEY_OUTSIDECHAMBER) {
            EnMnk_Monkey_SetAnim(this, 2);
        } else {
            EnMnk_Monkey_SetAnim(this, 5);
        }
        this->unk_3E0 = 6;
        this->actionFunc = EnMnk_Monkey_TalkAfterApproach;
        if (GET_MONKEY_7F(this) != 0x7F) {
            Flags_SetSwitch(play, GET_MONKEY_7F(this));
        }
    } else if ((GET_MONKEY_TYPE(this) == MONKEY_OUTSIDEWOODS) && (GET_MONKEY_7F(this) != 0x7F) &&
               (Flags_GetSwitch(play, GET_MONKEY_7F(this)) != 0)) {
        EnMnk_Monkey_SetAnim(this, 2);
        this->actionFunc = EnMnk_Monkey_WaitToRun;
    } else if (this->picto.actor.xzDistToPlayer > 150.0f) {
        EnMnk_Monkey_SetAnim(this, 1);
        this->unk_3E4 |= 0x10;
        this->actionFunc = EnMnk_Monkey_UnapproachPlayer;
    } else if (this->picto.actor.xzDistToPlayer < 100.0f) {
        func_800B8614(&this->picto.actor, play, 120.0f);
    }
}

void EnMnk_Monkey_ApproachPlayer(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    this->approachPlayerRadius += 5.0f;
    EnMnk_Monkey_MoveRelativeToPlayer(this, play);
    if (this->approachPlayerRadius > 84.0f) {
        if (GET_MONKEY_TYPE(this) == MONKEY_OUTSIDECHAMBER) {
            EnMnk_Monkey_SetAnim(this, 7);
        } else {
            EnMnk_Monkey_SetAnim(this, 2);
        }
        this->actionFunc = EnMnk_Monkey_WaitToTalkAfterApproach;
    }
    EnMnk_PlayWalkSfx(this);
    if ((GET_MONKEY_TYPE(this) == MONKEY_OUTSIDEWOODS) && (GET_MONKEY_7F(this) != 0x7F) &&
        (Flags_GetSwitch(play, GET_MONKEY_7F(this)) != 0)) {
        EnMnk_Monkey_SetAnim(this, 2);
        this->actionFunc = EnMnk_Monkey_WaitToRun;
    }
}

void EnMnk_Monkey_WaitForPlayerApproach(EnMnk* this, PlayState* play) {
    EnMnk_Monkey_MoveRelativeToPlayer(this, play);
    SkelAnime_Update(&this->skelAnime);
    if (this->picto.actor.xzDistToPlayer < 200.0f) {
        EnMnk_Monkey_SetAnim(this, 1);
        this->actionFunc = EnMnk_Monkey_ApproachPlayer;
    }
    if ((GET_MONKEY_TYPE(this) == MONKEY_OUTSIDEWOODS) && (GET_MONKEY_7F(this) != 0x7F) &&
        (Flags_GetSwitch(play, GET_MONKEY_7F(this)) != 0)) {
        EnMnk_Monkey_SetAnim(this, 2);
        this->actionFunc = EnMnk_Monkey_WaitToRun;
    }
}

void EnMnk_Monkey_Drop(EnMnk* this, PlayState* play) {
    if (((this->picto.actor.world.pos.y - this->picto.actor.home.pos.y) < 40.0f) && SkelAnime_Update(&this->skelAnime)) {
        EnMnk_Monkey_SetAnim(this, 0);
        this->actionFunc = EnMnk_Monkey_WaitForPlayerApproach;
        if (GET_MONKEY_TYPE(this) == MONKEY_OUTSIDEWOODS) {
            Actor_PlaySfx(&this->picto.actor, NA_SE_EV_MONKEY_WALK);
        }
    }
}

void EnMnk_Monkey_SetupDrop(EnMnk* this) {
    this->unk_3E4 &= ~0x20;
    this->picto.actor.world.pos.y = this->picto.actor.home.pos.y + 200.0f;
    this->actionFunc = EnMnk_Monkey_Drop;
    this->picto.actor.velocity.y = -10.0f;
    this->picto.actor.terminalVelocity = -10.0f;
    this->picto.actor.flags |= ACTOR_FLAG_1;
    this->picto.actor.draw = EnMnk_Draw;
    Animation_Change(&this->skelAnime, &object_mnk_Anim_008814, 1.0f, 10.0f,
                     Animation_GetLastFrame(&object_mnk_Anim_008814), ANIMMODE_ONCE, 0.0f);
}

void EnMnk_Monkey_WaitOutsideWoods(EnMnk* this, PlayState* play) {
    this->picto.actor.shape.rot.y = this->picto.actor.yawTowardsPlayer;
    this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;

    if (((this->picto.actor.xzDistToPlayer < 200.0f) && (gSaveContext.save.saveInfo.weekEventReg[12] & 0x8)) ||
        (gSaveContext.eventInf[2] & 0x40)) {
        gSaveContext.eventInf[2] |= 0x40;
        EnMnk_Monkey_SetupDrop(this);
    }
}

void EnMnk_Monkey_WaitOutsideChamber(EnMnk* this, PlayState* play) {
    this->picto.actor.shape.rot.y = this->picto.actor.yawTowardsPlayer;
    this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;
    if ((this->picto.actor.xzDistToPlayer < 200.0f) &&
        (((gSaveContext.save.saveInfo.weekEventReg[18] & 0x1) || (gSaveContext.save.saveInfo.weekEventReg[88] & 0x1)) &&
         (play->curSpawn != 0))) {
        EnMnk_Monkey_SetupDrop(this);
    }
}

void EnMnk_Monkey_FollowPathAndWait(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (EnMnk_FollowPath(this, FOLLOWPATH_FLAGS_LONGRANGE) != FOLLOWPATH_RESULT_FOLLOWING) {
        this->nextPathIndex = this->path->additionalPathIndex;
        if (this->nextPathIndex == 0xFF) {
            Flags_SetSwitch(play, GET_MONKEY_7F(this));
            Actor_Kill(&this->picto.actor);
            return;
        }
        EnMnk_Monkey_SetAnim(this, 0);
        this->actionFunc = EnMnk_Monkey_WaitToFollowPath;
        this->picto.actor.speed = 0.0f;
    }
    EnMnk_PlayWalkSfx(this);
}

void EnMnk_Monkey_WaitToFollowPath(EnMnk* this, PlayState* play) {
    if ((this->picto.actor.playerHeightRel > -10.0f) && (this->picto.actor.xzDistToPlayer < 160.0f)) {
        EnMnk_StartNextPath(this, play);
        this->destPointIndex = 0;
        this->actionFunc = EnMnk_Monkey_FollowPathAndWait;
    } else {
        func_80AB5F6C(this);
    }
}

s32 EnMnk_PlayerIsInTalkRange(EnMnk* this, PlayState* play) {
    s32 absYawTowardsPlayer;

    if ((this->picto.actor.xzDistToPlayer < 100.0f) && (this->picto.actor.xzDistToPlayer > 20.0f)) {
        absYawTowardsPlayer = ABS_ALT(this->picto.actor.yawTowardsPlayer);
        if ((absYawTowardsPlayer >= 0x4001) && Player_IsFacingActor(&this->picto.actor, 0x3000, play)) {
            return 1;
        }
    }
    return 0;
}

void EnMnk_TiedUpMonkey_TeachSong(EnMnk* this, PlayState* play) {
    s32 pad;

    SkelAnime_Update(&this->skelAnime);
    SkelAnime_Update(&this->propSkelAnime);

    switch (play->msgCtx.currentTextId) {
        case 0x8D9: // "By the way...who are you?"
            EnMnk_TiedUpMonkey_SetNewAnim(this, TIEDUPMONKEY_ANIM_CONFUSED);
            break;
        case 0x8DC: // "...Whoa! That's not important now..."
        case 0x8DF: // "Then I will tell you and tell you..."
            EnMnk_TiedUpMonkey_SetNewAnim(this, TIEDUPMONKEY_ANIM_KICKAROUND);
            break;
        case 0x8DD: // "I was trying to find out about the poison in the swamp..."
            EnMnk_TiedUpMonkey_SetNewAnim(this, TIEDUPMONKEY_ANIM_SMALLCLAPFEET);
            this->unk_3E0 = 5;
            break;
        case 0x8DE: // "Do you understand my plight?"
            EnMnk_TiedUpMonkey_SetNewAnim(this, TIEDUPMONKEY_ANIM_CONFUSED);
            break;
        case 0x8E0: // "So then, that means..."
        case 0x1B66: // "Keep this song in your heart..."
            EnMnk_TiedUpMonkey_SetNewAnim(this, TIEDUPMONKEY_ANIM_LARGECLAPFEET);
            break;
        case 0x8E1: // "OK, now I'll teach you the melody..."
            EnMnk_TiedUpMonkey_SetNewAnim(this, TIEDUPMONKEY_ANIM_KICKUPANDDOWN);
            break;
        case 0x1B5C: // "Open your ears and listen hard!"
            EnMnk_TiedUpMonkey_SetNewAnim(this, TIEDUPMONKEY_ANIM_SING);
            break;
        case 0x8E2: // "You'd better take the shortcut..."
            EnMnk_TiedUpMonkey_SetNewAnim(this, TIEDUPMONKEY_ANIM_KICKAROUND);
            this->unk_3E0 = 0;
            break;
        default:
            break;
    }

    if ((Message_GetState(&play->msgCtx) == 4) && (!(this->unk_3E4 & 0x4000)) &&
        Message_ShouldAdvance(play)) {

        switch (play->msgCtx.choiceIndex) {
            case 1:
                this->picto.actor.csId = this->cutsceneIndices[5];
                this->unk_3BC = 5;
                gSaveContext.save.saveInfo.weekEventReg[9] |= 0x80;
                this->unk_3E4 |= 0x2000;
                func_8019F208();
                break;
            case 0:
                func_8019F230();
                this->picto.actor.csId = this->cutsceneIndices[4];
                this->unk_3BC = 4;
                break;
        }
        this->unk_3E4 |= 0x4000;
    }

    if (this->picto.actor.csId != -1) {
        if (CutsceneManager_IsNext(this->picto.actor.csId)) {
            this->unk_3E4 &= ~0x4000;
            CutsceneManager_StartWithPlayerCs(this->picto.actor.csId, &this->picto.actor);

            switch (this->unk_3BC) {
                case 2:
                    this->unk_3BC = 3;
                    break;
                case 4:
                    this->unk_3BC = 3;
                    break;
                case 5:
                    this->unk_3BC = 6;
                    break;
                default:
                    this->picto.actor.csId = -1;
                    return;
            }
            this->picto.actor.csId = this->cutsceneIndices[this->unk_3BC];
        } else {
            CutsceneManager_Queue(this->picto.actor.csId);
        }
    }
}

void EnMnk_TiedUpMonkey_ReactToWrongInstrument(EnMnk* this, PlayState* play) {
    Actor* actor = &this->picto.actor;

    SkelAnime_Update(&this->skelAnime);
    SkelAnime_Update(&this->propSkelAnime);
    if ((Message_GetState(&play->msgCtx) == 5) && Message_ShouldAdvance(play)) {

        switch (play->msgCtx.currentTextId) {
            case 0x8D4: // "That tiny thing will never do..."
            case 0x8DA: // "By the way...who are you?"
            case 0x8DB: // "By the way...who are you?"
                Message_CloseTextbox(play);
                this->actionFunc = EnMnk_TiedUpMonkey_WaitForInstrument;
                play->msgCtx.ocarinaMode = 4;
                EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_WAIT);
                if (this->unk_3BC != -1) {
                    CutsceneManager_Stop(this->unk_3BC);
                    this->picto.actor.csId = (s8)this->cutsceneIndices[0];
                    this->unk_3BC = -1;
                    return;
                }
                break;
            case 0x8D5: // "Hmm... That definitely makes noise..."
                Message_ContinueTextbox(play, 0x8DA);
                EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_CONFUSED);
                break;
            case 0x8D6: // "That's not it..."
                Message_ContinueTextbox(play, 0x8DB);
                EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_CONFUSED);
                break;
        }
    }

    if (actor->csId != -1) {
        if (CutsceneManager_IsNext(actor->csId)) {
            CutsceneManager_Start(actor->csId, actor);

            this->unk_3BC = actor->csId;
            actor->csId = (actor->csId == this->cutsceneIndices[0]) ? this->cutsceneIndices[1] : -1;
        } else {
            CutsceneManager_Queue(actor->csId);
        }
    }
}

void EnMnk_TiedUpMonkey_TalkUnused(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    SkelAnime_Update(&this->propSkelAnime);
    if (Actor_TextboxIsClosing(&this->picto.actor, play) != 0) {
        this->actionFunc = EnMnk_TiedUpMonkey_WaitUnused;
    }
}

void EnMnk_TiedUpMonkey_TransitionAfterTalk(EnMnk* this, PlayState* play) {
    s32 pad;

    SkelAnime_Update(&this->skelAnime);
    SkelAnime_Update(&this->propSkelAnime);
    if (play->msgCtx.currentTextId == 0x8CD) {
        if (this->skelAnime.curFrame <= 17.0f) {
            this->unk_3E0 = 0;
        } else {
            this->unk_3E0 = 2;
        }
    }

    if ((Message_GetState(&play->msgCtx) == 5) && Message_ShouldAdvance(play)) {
        switch (play->msgCtx.currentTextId) {
            case 0x8CA: // "They keep saying I kidnapped her..."
                EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_SHAKEHEAD);
                if (play->curSpawn != 1) {
                    Message_ContinueTextbox(play, 0x8CB);
                    gSaveContext.save.saveInfo.weekEventReg[88] |= 0x1;
                } else {
                    Message_ContinueTextbox(play, 0x8EB);
                    this->unk_3E4 |= 0x1000;
                }
                break;
            case 0x8CB: // "Please, believe my words..."
            case 0x8EB: // "Why won't they believe what I say?"
            case 0x8EC: // "I have nothing else to say to you Deku Scrubs!"
                Message_CloseTextbox(play);
                this->actionFunc = EnMnk_TiedUpMonkey_Wait;
                this->unk_3D0 = 4;
                EnMnk_TiedUpMonkey_ChangeAnims(this, TIEDUPMONKEY_ANIM_KICKAROUND, ANIMMODE_ONCE, -5.0f);
                break;
            case 0x8CC: // "Oh! You... How did you get here?"
                EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_SHH);
                this->unk_3E0 = 2;
                Message_ContinueTextbox(play, 0x8CD);
                break;
            case 0x8CD: // "Shhh! If they see you, they'll capture you!"
                EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_SHAKEHEAD);
                Message_ContinueTextbox(play, 0x8CE);
                break;
            case 0x8CE: // "What? My brother asked for your help?"
                EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_KICKUPANDDOWN);
                Message_ContinueTextbox(play, 0x8CF);
                break;
            case 0x8CF: // "Just try to cut my rope..."
            case 0x8D0: // "What are you doing? Quick--cut this rope!"
            case 0x8D1: // "Huh? That guy... Where did he go???"
                Message_CloseTextbox(play);
                this->actionFunc = EnMnk_TiedUpMonkey_WaitForCutRope;
                EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_KICKUPANDDOWN);
                break;
            case 0x8D3: // "If you have one, show me!"
                if ((gSaveContext.save.playerForm == PLAYER_FORM_FIERCE_DEITY) ||
                    (gSaveContext.save.playerForm == PLAYER_FORM_HUMAN)) {
                    Message_CloseTextbox(play);
                    this->actionFunc = EnMnk_TiedUpMonkey_WaitForInstrument;
                    EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_WAIT);
                } else {
                    EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_CONFUSED);
                    Message_ContinueTextbox(play, 0x8D7);
                }
                break;
            case 0x8D2: // "Hmm...No good, after all!"
            case 0x8D7: // "Huh? That guy... Where did he go?"
                Message_CloseTextbox(play);
                this->actionFunc = EnMnk_TiedUpMonkey_WaitForInstrument;
                EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_WAIT);
                break;
            default:
                break;
        }
    }
}

void EnMnk_TiedUpMonkey_WaitUnused(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    SkelAnime_Update(&this->propSkelAnime);
    if (Actor_ProcessTalkRequest(&this->picto.actor, &play->state)) {
        this->actionFunc = EnMnk_TiedUpMonkey_TalkUnused;
        this->unk_3E0 = 0;
    } else if (EnMnk_PlayerIsInTalkRange(this, play)) {
        this->picto.actor.textId = 0x8E2; // "You'd better take the shortcut..."
        func_800B8614(&this->picto.actor, play, 120.0f);
    }
}

void EnMnk_TiedUpMonkey_WaitForInstrument(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    SkelAnime_Update(&this->propSkelAnime);
    if (func_800B8718(&this->picto.actor, &play->state)) {
        switch (gSaveContext.save.playerForm) {
            case PLAYER_FORM_HUMAN:
            case PLAYER_FORM_FIERCE_DEITY:
                this->picto.actor.textId = 0x8D4; // "That tiny thing will never do..."
                EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_SHAKEHEAD);
                break;
            case PLAYER_FORM_GORON:
                this->picto.actor.textId = 0x8D5; // "Hmm... That definitely makes noise..."
                EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_SHAKEHEAD);
                break;
            case PLAYER_FORM_ZORA:
                this->picto.actor.textId = 0x8D6; // "That's not it..."
                EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_SHAKEHEAD);
                break;
            case PLAYER_FORM_DEKU:
                this->picto.actor.textId = 0x8D8; // "Oh! You have them! You do! Just like the princess..."
                EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_KICKUPANDDOWN);
                this->actionFunc = EnMnk_TiedUpMonkey_TeachSong;
                this->unk_3BC = 2;
                gSaveContext.eventInf[2] |= 0x10;
                this->picto.actor.csId = this->cutsceneIndices[2];
                play->msgCtx.ocarinaMode = 4;
                CutsceneManager_Queue(this->cutsceneIndices[2]);
                return;
            default:
                this->picto.actor.textId = 0x8D4; // "That tiny thing will never do..."
                EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_SHAKEHEAD);
                break;
        }
        this->actionFunc = EnMnk_TiedUpMonkey_ReactToWrongInstrument;
        this->picto.actor.csId = this->cutsceneIndices[0];
        Message_StartTextbox(play, this->picto.actor.textId, NULL);
        CutsceneManager_Queue(this->picto.actor.csId);
    } else if (Actor_ProcessTalkRequest(&this->picto.actor, &play->state)) {
        this->actionFunc = EnMnk_TiedUpMonkey_TransitionAfterTalk;
        EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_KICKAROUND);
    } else if (EnMnk_PlayerIsInTalkRange(this, play)) {
        this->picto.actor.textId = 0x8D3; // "If you have one, show me!"
        func_800B8614(&this->picto.actor, play, 100.0f);
        func_800B874C(&this->picto.actor, play, 100.0f, 100.0f);
    }
}

void EnMnk_TiedUpMonkey_TalkAfterCutRope(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    SkelAnime_Update(&this->propSkelAnime);
    if (Actor_ProcessTalkRequest(&this->picto.actor, &play->state)) {
        this->actionFunc = EnMnk_TiedUpMonkey_TransitionAfterTalk;
        this->picto.actor.flags &= ~ACTOR_FLAG_10000;
    } else {
        func_800B8614(&this->picto.actor, play, 150.0f);
    }
}

void EnMnk_TiedUpMonkey_WaitForCutRope(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    SkelAnime_Update(&this->propSkelAnime);
    if (Actor_ProcessTalkRequest(&this->picto.actor, &play->state)) {
        if ((gSaveContext.save.playerForm == PLAYER_FORM_FIERCE_DEITY) || (gSaveContext.save.playerForm == PLAYER_FORM_HUMAN)) {
            EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_SHH);
            this->unk_3E0 = 5;
        } else {
            EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_CONFUSED);
        }
        this->actionFunc = EnMnk_TiedUpMonkey_TransitionAfterTalk;
    } else if (this->collider.base.acFlags & 0x2) {
        this->actionFunc = EnMnk_TiedUpMonkey_TalkAfterCutRope;
        this->picto.actor.textId = 0x8D2; // "Hmm...No good, after all!"
        EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_SHAKEHEAD);
        this->picto.actor.flags |= ACTOR_FLAG_10000;
    } else if (EnMnk_PlayerIsInTalkRange(this, play)) {
        if ((gSaveContext.save.playerForm != PLAYER_FORM_FIERCE_DEITY) && (gSaveContext.save.playerForm != PLAYER_FORM_HUMAN)) {
            this->picto.actor.textId = 0x8D1; // "Huh? That guy... Where did he go???"
        } else {
            this->picto.actor.textId = 0x8D0; // "What are you doing? Quick--cut this rope!"
        }
        func_800B8614(&this->picto.actor, play, 100.0f);
    }
}

void EnMnk_TiedUpMonkey_Wait(EnMnk* this, PlayState* play) {
    s32 pad;

    SkelAnime_Update(&this->skelAnime);
    if (SkelAnime_Update(&this->propSkelAnime)) {
        this->unk_3D0--;
        if (this->unk_3D0 < 0) {
            this->unk_3D0 = 4;
            EnMnk_TiedUpMonkey_ChangeAnims(this, TIEDUPMONKEY_ANIM_KICKAROUND, ANIMMODE_ONCE, -5.0f);
        } else if (this->unk_3D0 == 0) {
            EnMnk_TiedUpMonkey_ChangeAnims(this, TIEDUPMONKEY_ANIM_SHAKEHEAD, ANIMMODE_ONCE, -5.0f);
        } else {
            EnMnk_TiedUpMonkey_ChangeAnims(this, TIEDUPMONKEY_ANIM_KICKAROUND, ANIMMODE_ONCE, 0.0f);
            SkelAnime_Update(&this->skelAnime);
            SkelAnime_Update(&this->propSkelAnime);
        }
    }
    if (func_800B8718(&this->picto.actor, &play->state)) {
        this->picto.actor.textId = 0x8D8; // "Oh! You have them! Just like the princes..."
        EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_KICKUPANDDOWN);
        this->actionFunc = EnMnk_TiedUpMonkey_TeachSong;
        this->unk_3BC = 2;
        gSaveContext.eventInf[2] |= 0x10;
        this->picto.actor.csId = this->cutsceneIndices[2];
        play->msgCtx.ocarinaMode = 4;
        CutsceneManager_Queue(this->cutsceneIndices[2]);
    } else if (Actor_ProcessTalkRequest(&this->picto.actor, &play->state)) {
        if (gSaveContext.save.playerForm == PLAYER_FORM_DEKU) {
            if (this->picto.actor.textId == 0x8EC) { // "I have nothing else to say to you Deku Scrubs!"
                EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_SHAKEHEAD);
            } else {
                EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_KICKAROUND);
            }
        } else {
            EnMnk_TiedUpMonkey_SetAnim(this, TIEDUPMONKEY_ANIM_KICKUPANDDOWN);
        }
        this->actionFunc = EnMnk_TiedUpMonkey_TransitionAfterTalk;
    } else if (EnMnk_PlayerIsInTalkRange(this, play)) {
        if (gSaveContext.save.playerForm == PLAYER_FORM_DEKU) {
            if ((this->unk_3E4 & 0x1000) != 0) {
                this->picto.actor.textId = 0x8EC;
            } else {
                this->picto.actor.textId = 0x8CA;
            }
            func_800B874C(&this->picto.actor, play, 100.0f, 100.0f);
        } else {
            this->picto.actor.textId = 0x8CC; // Oh! You... How did you get here?
        }
        func_800B8614(&this->picto.actor, play, 120.0f);
    } else if ((play->curSpawn != 1) && (this->picto.actor.xzDistToPlayer < 140.0f) &&
               Player_IsFacingActor(&this->picto.actor, 0x3000, play)) {
        this->picto.actor.textId = 0x8CA;
        func_800B8614(&this->picto.actor, play, 140.0f);
    }
}

void EnMnk_HangingMonkey_WaitForTextboxAfterDunk(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    SkelAnime_Update(&this->propSkelAnime);
    if ((Message_GetState(&play->msgCtx) == 5) && Message_ShouldAdvance(play)) {
        if (this->unk_3E4 & 0x800) {
            this->unk_3E4 &= ~0x800;
            CutsceneManager_Stop(this->picto.actor.csId);
        }
        Message_CloseTextbox(play);
        this->actionFunc = EnMnk_HangingMonkey_WaitAfterDunk;
        func_800B7298(play, NULL, 6);
        gSaveContext.save.saveInfo.weekEventReg[83] &= (u8)~0x8;
    }
}

void EnMnk_HangingMonkey_RaiseFromDunk2(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    SkelAnime_Update(&this->propSkelAnime);
    if (this->unk_3C8 > 0) {
        this->unk_3D0 -= 0x320;
        this->approachPlayerRadius -= 0.01f;
        this->unk_3C8--;
    } else {
        this->unk_3C8 = 240;
        this->actionFunc = EnMnk_HangingMonkey_WaitForTextboxAfterDunk;
        EnMnk_HangingMonkey_SetAnim(this, HANGINGMONKEY_ANIM_FREEZE);
        Message_ContinueTextbox(play, 0x8EA); // "........."
    }
}

void EnMnk_HangingMonkey_PauseDuringDunk2(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    SkelAnime_Update(&this->propSkelAnime);
    if (this->unk_3C8 > 0) {
        this->unk_3C8--;
    } else {
        this->unk_3C8 = 60;
        this->actionFunc = EnMnk_HangingMonkey_RaiseFromDunk2;
        EnMnk_HangingMonkey_ChangeAnims(this, HANGINGMONKEY_ANIM_RISE, ANIMMODE_ONCE, -5.0f);
        this->unk_3E0 = 3;
    }
}

void EnMnk_HangingMonkey_MakeSplash(EnMnk* this, PlayState* play) {
    Vec3f effSpawnPos;

    Math_Vec3f_Copy(&effSpawnPos, &this->picto.actor.focus.pos);
    effSpawnPos.y += 20.0f;
    EffectSsGSplash_Spawn(play, &effSpawnPos, &sHangingMonkeySplashPrimColor, &sHangingMonkeySplashEnvColor, 0, 300);
}

void EnMnk_HangingMonkey_Dunk2(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    SkelAnime_Update(&this->propSkelAnime);
    if (this->unk_3C8 > 0) {
        this->unk_3D0 += 0x320;
        this->approachPlayerRadius += 0.01f;
        this->unk_3C8--;
        if (this->unk_3C8 == 0xA) {
            Actor_PlaySfx(&this->picto.actor, NA_SE_EV_BOMB_DROP_WATER);
            EnMnk_HangingMonkey_MakeSplash(this, play);
        }
    } else {
        this->unk_3C8 = 20;
        this->actionFunc = EnMnk_HangingMonkey_PauseDuringDunk2;
    }
}

void EnMnk_HangingMonkey_Plead(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    SkelAnime_Update(&this->propSkelAnime);
    if ((Message_GetState(&play->msgCtx) == 5) && Message_ShouldAdvance(play)) {
        switch (play->msgCtx.currentTextId) {
            case 0x8E8: // "Ooh! Hot! Hot! St-stop it! Please!!!"
                Message_ContinueTextbox(play, 0x8E9);
                break;
            case 0x8E9: // "They keep saying that I kidnapped her"
                this->actionFunc = EnMnk_HangingMonkey_Dunk2;
                Message_CloseTextbox(play);
                func_800B7298(play, &this->picto.actor, 7);
                this->unk_3C8 = 60;
                break;
        }
    }
    if (!(this->unk_3E4 & 0x800)) {
        if (CutsceneManager_GetCurrentCsId() == 0x7C) {
            CutsceneManager_Stop(0x7C);
            CutsceneManager_Queue(this->picto.actor.csId);
        } else if (CutsceneManager_IsNext(this->picto.actor.csId)) {
            CutsceneManager_StartWithPlayerCs(this->picto.actor.csId, &this->picto.actor);
            this->unk_3E4 |= 0x800;
        } else {
            CutsceneManager_Queue(this->picto.actor.csId);
        }
    }
}

void EnMnk_HangingMonkey_WaitAfterDunk(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    SkelAnime_Update(&this->propSkelAnime);
    if (Actor_ProcessTalkRequest(&this->picto.actor, &play->state)) {
        this->actionFunc = EnMnk_HangingMonkey_Plead;
        CutsceneManager_Queue(this->picto.actor.csId);
        gSaveContext.save.saveInfo.weekEventReg[83] |= 0x8;
        EnMnk_HangingMonkey_SetAnim(this, HANGINGMONKEY_ANIM_STRUGGLE);
        this->unk_3E0 = 5;
    } else if (this->unk_3C8 > 0) {
        this->unk_3C8--;
        if (this->picto.actor.isTargeted && (this->picto.actor.csId != -1)) {
            func_800B8614(&this->picto.actor, play, 1000.0f);
        }
    } else {
        this->unk_3C8 = 240;
        this->actionFunc = EnMnk_HangingMonkey_StruggleBeforeDunk;
        EnMnk_HangingMonkey_SetAnim(this, HANGINGMONKEY_ANIM_STRUGGLE);
        this->unk_3E0 = 5;
    }
}

void EnMnk_HangingMonkey_RaiseFromDunk(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    SkelAnime_Update(&this->propSkelAnime);
    if (this->unk_3C8 > 0) {
        this->unk_3D0 -= 0x320;
        this->approachPlayerRadius -= 0.01f;
        this->unk_3C8--;
    } else {
        this->unk_3C8 = 240;
        this->actionFunc = EnMnk_HangingMonkey_WaitAfterDunk;
        EnMnk_HangingMonkey_SetAnim(this, HANGINGMONKEY_ANIM_FREEZE);
    }
}

void EnMnk_HangingMonkey_PauseDuringDunk(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    SkelAnime_Update(&this->propSkelAnime);
    if (this->unk_3C8 > 0) {
        this->unk_3C8--;
    } else {
        this->unk_3C8 = 60;
        this->actionFunc = EnMnk_HangingMonkey_RaiseFromDunk;
        EnMnk_HangingMonkey_ChangeAnims(this, HANGINGMONKEY_ANIM_RISE, ANIMMODE_ONCE, -5.0f);
        this->unk_3E0 = 3;
    }
}

void EnMnk_HangingMonkey_Dunk(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    SkelAnime_Update(&this->propSkelAnime);
    if (this->unk_3C8 > 0) {
        this->unk_3D0 += 0x320;
        this->approachPlayerRadius += 0.01f;
        this->unk_3C8--;
        if (this->unk_3C8 == 0xA) {
            Actor_PlaySfx(&this->picto.actor, NA_SE_EV_BOMB_DROP_WATER);
            EnMnk_HangingMonkey_MakeSplash(this, play);
        }
    } else {
        this->unk_3C8 = 20;
        this->actionFunc = EnMnk_HangingMonkey_PauseDuringDunk;
    }
}

void EnMnk_HangingMonkey_StruggleBeforeDunk(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    SkelAnime_Update(&this->propSkelAnime);
    if (Actor_ProcessTalkRequest(&this->picto.actor, &play->state)) {
        this->actionFunc = EnMnk_HangingMonkey_Plead;
        CutsceneManager_Queue(this->picto.actor.csId);
        gSaveContext.save.saveInfo.weekEventReg[83] |= 0x8;
    } else if (this->unk_3C8 > 0) {
        this->unk_3C8--;
        if (this->picto.actor.isTargeted) {
            func_800B8614(&this->picto.actor, play, 1000.0f);
        }
    } else {
        this->unk_3C8 = 60;
        this->actionFunc = EnMnk_HangingMonkey_Dunk;
    }
}

void EnMnk_Monkey_GuideThroughWoods(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (EnMnk_FollowPath(this, 0) != FOLLOWPATH_RESULT_FOLLOWING) {
        this->nextPathIndex = this->path->additionalPathIndex;
        if (this->nextPathIndex == 0xFF) {
            Actor_Kill(&this->picto.actor);
            return;
        }
        this->path = &play->setupPathList[this->nextPathIndex];
        this->destPointIndex = 0;
    }
    EnMnk_PlayWalkSfx(this);
}

void EnMnk_Monkey_TalkBeforeGuideThroughWoods(EnMnk* this, PlayState* play) {
    Math_SmoothStepToS(&this->picto.actor.world.rot.y, this->picto.actor.yawTowardsPlayer, 2, 0xBB8, 0xC8);
    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.world.rot.y, 2, 0xBB8, 0xC8);
    SkelAnime_Update(&this->skelAnime);
    if (Actor_TextboxIsClosing(&this->picto.actor, play)) {
        EnMnk_StartNextPath(this, play);
        this->actionFunc = EnMnk_Monkey_GuideThroughWoods;
        this->unk_3E4 |= 0x8000;
    }
}

void EnMnk_Monkey_SetupTalkBeforeGuideThroughWoods(EnMnk* this) {
    switch ((u32)Rand_ZeroFloat(6.0f)) {
        case 0:
            EnMnk_Monkey_SetAnim(this, 3);
            break;
        case 1:
            EnMnk_Monkey_SetAnim(this, 4);
            break;
        case 2:
            EnMnk_Monkey_SetAnim(this, 5);
            break;
        case 3:
            EnMnk_Monkey_SetAnim(this, 6);
            break;
        case 4:
            EnMnk_Monkey_SetAnim(this, 2);
            break;
        default:
            EnMnk_Monkey_SetAnim(this, 7);
            break;
    }
    this->actionFunc = EnMnk_Monkey_TalkBeforeGuideThroughWoods;
}

void EnMnk_Monkey_WaitToGuideThroughWoods(EnMnk* this, PlayState* play) {
    func_80AB5F6C(this);
    if (Actor_ProcessTalkRequest(&this->picto.actor, &play->state)) {
        EnMnk_Monkey_SetupTalkBeforeGuideThroughWoods(this);
    } else if (this->picto.actor.isTargeted || (this->picto.actor.xzDistToPlayer < 100.0f)) {
        func_800B8614(&this->picto.actor, play, 120.0f);
    }
    if (gSaveContext.save.saveInfo.weekEventReg[12] & 0x8) {
        Actor_Kill(&this->picto.actor);
    }
}

void EnMnk_Monkey_TalkAfterSaved(EnMnk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if ((Message_GetState(&play->msgCtx) == 5) && Message_ShouldAdvance(play)) {
        switch (play->msgCtx.currentTextId) {
            case 0x8E5: // "I'm sorry for all that trouble."
                Message_ContinueTextbox(play, 0x8E6); // "...You know, the swamp may be back to normal..."
                EnMnk_Monkey_SetAnim(this, 3);
                break;
            case 0x8E6: // "...You know, the swamp may be back to normal..."
                Message_ContinueTextbox(play, 0x8E7); // "I wonder what it could be..."
                EnMnk_Monkey_SetAnim(this, 5);
                break;
            case 0x8E7: // "I wonder what it could be..."
                Message_CloseTextbox(play);
                this->actionFunc = EnMnk_Monkey_WaitToTalkAfterSaved;
                EnMnk_Monkey_SetAnim(this, 0);
                break;
        }
    }
}

void EnMnk_Monkey_WaitToTalkAfterSaved(EnMnk* this, PlayState* play) {
    this->picto.actor.shape.rot.y = this->picto.actor.yawTowardsPlayer;
    this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;
    SkelAnime_Update(&this->skelAnime);
    if (Actor_ProcessTalkRequest(&this->picto.actor, &play->state)) {
        this->actionFunc = EnMnk_Monkey_TalkAfterSaved;
        EnMnk_Monkey_SetAnim(this, 7);
    } else if ((this->picto.actor.xzDistToPlayer < 100.0f) && Player_IsFacingActor(&this->picto.actor, 0x3000, play)) {
        func_800B8614(&this->picto.actor, play, 110.0f);
    }
}

void func_80AB9084(EnMnk* this, PlayState* play) {
    s16 sp2E;

    sp2E = 0;
    if (SkelAnime_Update(&this->skelAnime)) {
        switch (this->unk_3D0) {
            case 2:
                EnMnk_Monkey_SetAnim(this, 0xD);
                break;
            case 3:
                EnMnk_Monkey_SetAnim(this, 0);
                break;
            case 4:
                EnMnk_Monkey_SetAnim(this, 0);
                break;
        }
        SkelAnime_Update(&this->skelAnime);
        gSaveContext.save.saveInfo.weekEventReg[29] |= 0x80;
    }

    if (Cutscene_IsCueInChannel(play, 0x6A) != 0) {
        Cutscene_ActorTranslateAndYaw(&this->picto.actor, play, Cutscene_GetCueChannel(play, 0x6A));
        sp2E = play->csCtx.actorCues[Cutscene_GetCueChannel(play, 0x6A)]->id;
    }

    if ((sp2E == 0) && (this->curAnim != 0)) {
        EnMnk_Monkey_SetAnim(this, 0);
    } else if (sp2E != this->unk_3D0) {
        switch (sp2E) {
            case 1:
                EnMnk_Monkey_ChangeAnim(this, 0, ANIMMODE_LOOP, 0.0f);
                break;
            case 2:
                EnMnk_Monkey_ChangeAnim(this, 0xC, ANIMMODE_ONCE, 0.0f);
                this->unk_3E0 = 6;
                break;
            case 3:
                EnMnk_Monkey_ChangeAnim(this, 0xB, ANIMMODE_ONCE, 0.0f);
                break;
            case 4:
                EnMnk_Monkey_ChangeAnim(this, 0xE, ANIMMODE_ONCE, -5.0f);
                break;
        }
        this->unk_3D0 = sp2E;
    }

    if (this->curAnim == 0xB) {
        if ((this->skelAnime.curFrame >= 8.0f) && (this->skelAnime.curFrame < 14.0f)) {
            this->unk_3E0 = 2;
        } else {
            this->unk_3E0 = 0;
        }
        if (Animation_OnFrame(&this->skelAnime, 8.0f) != 0) {
            Actor_PlaySfx(&this->picto.actor, NA_SE_EV_MONKEY_VO_REWARD);
        }
    }
}

void func_80AB92CC(EnMnk* this, PlayState* play) {
    s16 sp2E;

    sp2E = 0;
    if (SkelAnime_Update(&this->skelAnime)) {
        switch (this->unk_3D0) {
            case 2:
                EnMnk_Monkey_SetAnim(this, 0xD);
                break;
            case 3:
                EnMnk_Monkey_SetAnim(this, 0);
                break;
            case 4:
                EnMnk_Monkey_SetAnim(this, 0);
                break;
        }
        SkelAnime_Update(&this->skelAnime);
    }
    if (Cutscene_IsCueInChannel(play, 0x6A) != 0) {
        Cutscene_ActorTranslateAndYaw(&this->picto.actor, play, Cutscene_GetCueChannel(play, 0x6A));
        sp2E = play->csCtx.actorCues[Cutscene_GetCueChannel(play, 0x6A)]->id;
    }
    if ((sp2E == 0) && (this->curAnim != 0)) {
        EnMnk_Monkey_SetAnim(this, 0);
    } else if (sp2E != this->unk_3D0) {
        switch (sp2E) {
            case 1:
                EnMnk_Monkey_ChangeAnim(this, 0, ANIMMODE_LOOP, 0.0f);
                break;
            case 2:
                EnMnk_Monkey_ChangeAnim(this, 0xC, ANIMMODE_ONCE, 0.0f);
                this->unk_3E0 = 6;
                break;
            case 3:
                EnMnk_Monkey_ChangeAnim(this, 0xB, ANIMMODE_ONCE, 0.0f);
                break;
            case 4:
                EnMnk_Monkey_ChangeAnim(this, 0xE, ANIMMODE_ONCE, -5.0f);
                break;
        }
        this->unk_3D0 = sp2E;
    }
    if (this->curAnim == 0xB) {
        if ((this->skelAnime.curFrame >= 8.0f) && (this->skelAnime.curFrame < 14.0f)) {
            this->unk_3E0 = 2;
        } else {
            this->unk_3E0 = 0;
        }
    }
}

void EnMnk_DoNothing(EnMnk* this, PlayState* play) {
}

void EnMnk_Update(Actor* thisx, PlayState* play) {
    EnMnk* this = THIS;

    if (!(this->unk_3E4 & 0x1)) {
        Actor_MoveWithGravity(&this->picto.actor);
    }
    if (!(this->unk_3E4 & 0x2)) {
        Actor_UpdateBgCheckInfo(play, &this->picto.actor, 20.0f, 25.0f, 0.0f, 4);
        if (this->picto.actor.bgCheckFlags & 0x1) {
            this->unk_3E4 |= 0x40;
        }
    }

    this->actionFunc(this, play);

    if (!(this->unk_3E4 & 0x20)) {
        if (!(this->unk_3E4 & 0x8)) {
            Collider_UpdateCylinder(&this->picto.actor, &this->collider);
        }
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
    if (this->unk_3E4 & 0x200) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    }

    if (DECR(this->blinkTimer) == 0) {
        this->blinkTimer = Rand_S16Offset(60, 60);
    }

    this->blinkFrame = this->blinkTimer;
    if (this->blinkFrame >= 3) {
        this->blinkFrame = 0;
    }

    if (this->unk_3E4 & 0x80) {
        s8 cutscene = this->picto.actor.csId;

        if (cutscene == -1) {
            this->unk_3E4 &= ~0x80;
        } else if (CutsceneManager_IsNext(cutscene)) {
            CutsceneManager_StartWithPlayerCs(this->picto.actor.csId, &this->picto.actor);
            this->picto.actor.csId = CutsceneManager_GetAdditionalCsId(this->picto.actor.csId);
        } else {
            CutsceneManager_Queue(this->picto.actor.csId);
        }
    }
}

s32 EnMnk_Monkey_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnMnk* this = THIS;

    if (limbIndex == 3) {
        rot->x += this->unk_3CC;
        rot->z += this->unk_3CE;
    }
    return 0;
}

s32 EnMnk_TiedUpMonkey_PropOverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if (limbIndex == 1) {
        *dList = NULL;
    }
    return 0;
}

s32 EnMnk_HangingMonkey_PropOverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if ((limbIndex == 1) || (limbIndex == 2) || (limbIndex == 3)) {
        *dList = NULL;
    }
    return 0;
}

void EnMnk_Monkey_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnMnk* this = THIS;

    if (limbIndex == 4) {
        Matrix_MultVec3f(&focusPosOffset, &this->picto.actor.focus.pos);
    }
}

void EnMnk_TiedUpMonkey_PropPostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnMnk* this = THIS;

    if (limbIndex == 4) {
        Matrix_Get(&this->unk_36C);
    }
}

void EnMnk_HangingMonkey_PropPostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnMnk* this = (EnMnk*)thisx;

    switch (limbIndex) {
        case 1:
            if (*dList != 0) {
                OPEN_DISPS(play->state.gfxCtx);
                Matrix_Push();
                Matrix_RotateZS(this->unk_3D0, MTXMODE_APPLY);
                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, *dList);
                Matrix_Pop();
                CLOSE_DISPS(play->state.gfxCtx);
            }
            break;
        case 2:
            if (*dList != 0) {
                OPEN_DISPS(play->state.gfxCtx);
                Matrix_Scale(this->approachPlayerRadius + 1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, *dList);
                CLOSE_DISPS(play->state.gfxCtx);
            }
            break;
        case 3:
            if (*dList != 0) {
                OPEN_DISPS(play->state.gfxCtx);
                Matrix_Scale(1.0f, 1.0f / (this->approachPlayerRadius + 1.0f), 1.0f, 1);
                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, *dList);
                CLOSE_DISPS(play->state.gfxCtx);
            }
            Matrix_Get(&this->unk_36C);
    }
}

void EnMnk_Monkey_DrawFace(EnMnk* this, PlayState* play) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);
    Gfx_SetupDL37_Opa(play->state.gfxCtx);
    switch (this->unk_3E0) {
        case 4:
        case 5:
        case 6:
            if (this->blinkFrame != 2) {
                gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sMonkeyFaceTextures[this->unk_3E0]));
            } else {
                gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sMonkeyFaceTextures[this->blinkFrame]));
            }
            return;
        case 2:
        case 3:
            gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sMonkeyFaceTextures[this->unk_3E0]));
            return;
    }
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sMonkeyFaceTextures[this->blinkFrame]));
    CLOSE_DISPS(play->state.gfxCtx);
}

void EnMnk_Draw(Actor* thisx, PlayState* play) {
    EnMnk* this = THIS;

    EnMnk_Monkey_DrawFace(this, play);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnMnk_Monkey_OverrideLimbDraw, EnMnk_Monkey_PostLimbDraw, &this->picto.actor);
}

void EnMnk_TiedUpMonkey_Draw(Actor* thisx, PlayState* play) {
    EnMnk* this = THIS;

    SkelAnime_DrawFlexOpa(play, this->propSkelAnime.skeleton, this->propSkelAnime.jointTable,
                          this->propSkelAnime.dListCount, EnMnk_TiedUpMonkey_PropOverrideLimbDraw, EnMnk_TiedUpMonkey_PropPostLimbDraw, &this->picto.actor);
    EnMnk_Monkey_DrawFace(this, play);
    Matrix_Mult(&this->unk_36C, MTXMODE_NEW);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnMnk_Monkey_OverrideLimbDraw, EnMnk_Monkey_PostLimbDraw, &this->picto.actor);
}

void EnMnk_HangingMonkey_Draw(Actor* thisx, PlayState* play) {
    EnMnk* this = THIS;

    SkelAnime_DrawFlexOpa(play, this->propSkelAnime.skeleton, this->propSkelAnime.jointTable,
                          this->propSkelAnime.dListCount, EnMnk_HangingMonkey_PropOverrideLimbDraw, EnMnk_HangingMonkey_PropPostLimbDraw, &this->picto.actor);
    EnMnk_Monkey_DrawFace(this, play);
    Matrix_Mult(&this->unk_36C, MTXMODE_NEW);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnMnk_Monkey_OverrideLimbDraw, EnMnk_Monkey_PostLimbDraw, &this->picto.actor);
}
