/*
 * File: z_en_kakasi.c
 * Overlay: ovl_En_Kakasi
 * Description: Pierre the Scarecorw
 */

#include "z_en_kakasi.h"
#include "objects/object_ka/object_ka.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((EnKakasi*)thisx)

void EnKakasi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKakasi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKakasi_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKakasi_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnKakasi_SetupPostSongLearnDialogue(EnKakasi* this, GlobalContext* globalCtx);
void EnKakasi_InitTimeSkipDialogue(EnKakasi* this);
void EnKakasi_SetupIdleStanding(EnKakasi* this);

void EnKakasi_8096F88C(GlobalContext* globalCtx, EnKakasi* this);

void EnKakasi_TimeSkipDialogue(EnKakasi* this, GlobalContext* globalCtx);
void EnKakasi_IdleStanding(EnKakasi* this, GlobalContext* globalCtx);
void EnKakasi_OcarinaRemark(EnKakasi* this, GlobalContext* globalCtx);
void EnKakasi_TeachingSong(EnKakasi* this, GlobalContext* globalCtx);
void EnKakasi_PostSongLearnTwirl(EnKakasi* this, GlobalContext* globalCtx);
void EnKakasi_PostSongLearnDialogue(EnKakasi* this, GlobalContext* globalCtx);
void EnKakasi_SetupDigAway(EnKakasi* this);
void EnKakasi_DiggingAway(EnKakasi* this, GlobalContext* globalCtx);
void EnKakasi_RisenDialogue(EnKakasi* this, GlobalContext* globalCtx);
void EnKakasi_SetupIdleUnderground(EnKakasi* this);
void EnKakasi_IdleUnderground(EnKakasi* this, GlobalContext* globalCtx);
void EnKakasi_SetupIdleRisen(EnKakasi* this);
void EnKakasi_IdleRisen(EnKakasi* this, GlobalContext* globalCtx);
void EnKakasi_SetupRiseOutOfGround(EnKakasi* this, GlobalContext* globalCtx);
void EnKakasi_RisingOutOfGround(EnKakasi* this, GlobalContext* globalCtx);
void EnKakasi_DancingRemark(EnKakasi* this, GlobalContext* globalCtx);
void EnKakasi_SetupDanceNightAway(EnKakasi* this);
void EnKakasi_DancingNightAway(EnKakasi* this, GlobalContext* globalCtx);
void EnKakasi_DoNothing(EnKakasi* this, GlobalContext* globalCtx);
void EnKakasi_RegularDialogue(EnKakasi* this, GlobalContext* globalCtx);
void EnKakasi_SetupSongTeach(EnKakasi* this, GlobalContext* globalCtx);

void EnKakasi_SetupDialogue(EnKakasi* this);

static ColliderCylinderInit D_80971D80 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 20, 70, 0, { 0, 0, 0 } },
};

const ActorInit En_Kakasi_InitVars = {
    ACTOR_EN_KAKASI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_KA,
    sizeof(EnKakasi),
    (ActorFunc)EnKakasi_Init,
    (ActorFunc)EnKakasi_Destroy,
    (ActorFunc)EnKakasi_Update,
    (ActorFunc)EnKakasi_Draw,
};

static Vec3f D_80971DCC[] = {
    { 0.0f, 60.0f, 60.0f },   { 40.0f, 40.0f, 50.0f },   { -40.0f, 40.0f, 50.0f },
    { 40.0f, 20.0f, 110.0f }, { -40.0f, 20.0f, 110.0f }, { 0.0f, 80.0f, 60.0f },
    { 50.0f, 40.0f, -30.0f }, { -50.0f, 40.0f, -30.0f }, { 0.0f, 50.0f, 60.0f },
};
Vec3f D_80971E38[] = {
    { 0.0f, 55.0f, 60.0f },   { 0.0f, 55.0f, 60.0f },   { -80.0f, 35.0f, 15.0f }, { 80.0f, 45.0f, 15.0f },
    { -10.0f, 35.0f, 65.0f }, { 0.0f, 110.0f, 180.0f }, { 0.0f, 60.0f, 70.0f },   { 0.0f, 60.0f, 70.0f },
    { -80.0f, 50.0f, 40.0f }, { 0.0f, -10.0f, 50.0f },  { 80.0f, 50.0f, 40.0f },  { 0.0f, 120.0f, 40.0f },
    { 0.0f, 28.0f, -50.0f },  { 0.0f, 60.0f, 50.0f },   { 0.0f, 80.0f, 160.0f },
};

Vec3f D_80971EEC[] = {
    { 12.0f, 1.0f, 2.0f },    { 12.0f, 1.0f, 2.0f },  { 2.0f, -6.0f, 0.0f },  { 12.0f, -6.0f, -10.0f },
    { -88.0f, 14.0, -10.0f }, { 0.0f, 0.0f, 0.0f },   { 0.0f, 0.0f, 0.0f },   { 0.0f, 0.0f, 0.0f },
    { 0.0f, -10.0f, 0.0f },   { 0.0f, -10.0f, 0.0f }, { 0.0f, -10.0f, 0.0f }, { 0.0f, -10.0f, 0.0f },
    { 0.0f, -10.0f, 0.0f },   { 0.0f, 0.0f, 0.0f },   { 0.0f, 0.0f, 0.0f },
};

Vec3f D_80971FA0[] = {
    { -50.0f, 160.0f, -40.0f }, { -50.0f, 160.0f, -40.0f }, { -20.0f, 80.0f, 60.0f },
    { 57.0f, 60.0f, 120.0f },   { 27.0f, 80.0f, 60.0f },    { -3.0f, 50.0f, 70.0f },
};

Vec3f D_80971FE8[] = {
    { 0.0f, 0.0f, 0.0f },    { 0.0f, 0.0f, 0.0f },  { -10.0f, -5.0f, 0.0f },
    { 10.0f, -10.0f, 7.0f }, { 20.0f, 5.0f, 2.0f }, { 10.0f, 5.0f, 2.0f },
};

// both use in digging away function
Vec3f D_80972030 = { -3.0f, 50.0f, 90.0f };
Vec3f D_8097203C = { 10.0f, -15.0f, 2.0f };

typedef enum {
    /* 0x0 */ ENKAKASI_ANIM_ARMS_CROSSED_ROCKING, // arms crossed and rocking back and forth
    /* 0x1 */ ENKAKASI_ANIM_SIDEWAYS_SHAKING,
    /* 0x2 */ ENKAKASI_ANIM_HOPPING_REGULAR,    // bounce bounce bounce (repeat)
    /* 0x3 */ ENKAKASI_ANIM_SPIN_REACH_OFFER,   // spin and then reaching toward player
    /* 0x4 */ ENKAKASI_ANIM_TWIRL,              // slower cinimatic twirl
    /* 0x5 */ ENKAKASI_ANIM_ARMS_CROSSED_STILL, // arms crossed but still, also some noise sfx
    /* 0x6 */ ENKAKASI_ANIM_WAVE,               // "wave" short sideways shake, stops early, partial? unused?
    /* 0x7 */ ENKAKASI_ANIM_SLOWROLL,           // partial bounch, ends looking left, OFFER anim takes over
    /* 0x8 */ ENKAKASI_ANIM_IDLE,               // slow stretching wiggle, ends in regular position
} EnKakasi_Animations;

static AnimationHeader* kakasiAnimations[] = {
    &object_ka_Anim_007444, &object_ka_Anim_00686C, &object_ka_Anim_0081A4,
    &object_ka_Anim_007B90, &object_ka_Anim_0071EC, &object_ka_Anim_007444,
    &object_ka_Anim_00686C, &object_ka_Anim_0081A4, &object_ka_Anim_000214,
};

static u8 sAnimModes[] = {
    ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_ONCE,
    ANIMMODE_ONCE, ANIMMODE_ONCE, ANIMMODE_ONCE, ANIMMODE_ONCE,
};

void EnKakasi_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnKakasi* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnKakasi_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnKakasi* this = THIS;
    s32 tempCutscene;
    s32 i;

    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_80971D80);
    SkelAnime_InitFlex(globalCtx, &this->skelanime, &object_ka_Skel_0065B0, &object_ka_Anim_000214, 0, 0, 0);

    this->songSummonDist = GET_KAKASI_SUMMON_DISTANCE(this) * 20.0f;
    if (this->songSummonDist < 40.0f) {
        this->songSummonDist = 40.0f;
    }

    this->unkHeight = (this->actor.world.rot.z * 20.0f) + 60.0f;
    this->actor.world.rot.z = 0;
    this->actor.targetMode = 0;
    if (this->actor.world.rot.x > 0 && this->actor.world.rot.x < 8) {
        this->actor.targetMode = this->actor.world.rot.x - 1;
    }
    this->actor.shape.rot.y = this->actor.world.rot.y;

    this->aboveGroundStatus = GET_KAKASI_ABOVE_GROUND(this);
    this->actor.world.rot.x = 0;
    this->actor.flags |= ACTOR_FLAG_400;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    Actor_SetScale(&this->actor, 0.01f);

    i = 0;
    tempCutscene = this->actor.cutscene;
    while (tempCutscene != -1) {
        // This might be a fake match, no others found yet
        tempCutscene = ActorCutscene_GetAdditionalCutscene(this->actorCutscenes[i] = tempCutscene);
        i++;
    }

    if (this->aboveGroundStatus) {
        if (gSaveContext.save.weekEventReg[79] & 8) {
            this->aboveGroundStatus = ENKAKASI_ABOVE_GROUND_TYPE;
            this->songSummonDist = 80.0f;
            EnKakasi_SetupIdleUnderground(this);
        } else {
            Actor_SetFocus(&this->actor, 60.0f);
            this->unkFunc = EnKakasi_8096F88C;
            if (gSaveContext.save.weekEventReg[83] & 1) {
                EnKakasi_InitTimeSkipDialogue(this);
            } else {
                EnKakasi_SetupIdleStanding(this);
            }
        }
    } else {
        EnKakasi_SetupIdleUnderground(this);
    }
}

void EnKakasi_SetAnimation(EnKakasi* this, s32 index) {
    this->animIndex = index;
    this->animeFrameCount = Animation_GetLastFrame(&kakasiAnimations[this->animIndex]->common);
    // 1: regular playback speed, 0: starting frame
    Animation_Change(&this->skelanime, kakasiAnimations[this->animIndex], 1.0f, 0.0f, this->animeFrameCount,
                     sAnimModes[this->animIndex], -4.0f);
}

/*
 * set by init, called... nowhere? left over from OOT?
 */
void EnKakasi_8096F88C(GlobalContext* globalCtx, EnKakasi* this) {
    func_8013A530(globalCtx, &this->actor, 0x7, &this->actor.focus.pos, &this->actor.shape.rot, 280.0f, 1800.0f, -1);
}

void EnKakasi_CheckAnimationSfx(EnKakasi* this) {
    if (this->animIndex == ENKAKASI_ANIM_SIDEWAYS_SHAKING || this->animIndex == ENKAKASI_ANIM_ARMS_CROSSED_STILL) {
        if (Animation_OnFrame(&this->skelanime, 1.0f) || Animation_OnFrame(&this->skelanime, 8.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_KAKASHI_SWING);
        }
    }
    if (this->animIndex == ENKAKASI_ANIM_HOPPING_REGULAR || this->animIndex == ENKAKASI_ANIM_SLOWROLL) {
        if (Animation_OnFrame(&this->skelanime, 4.0f) || Animation_OnFrame(&this->skelanime, 8.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_KAKASHI_SWING);
        }
        if (Animation_OnFrame(&this->skelanime, 1.0f) || Animation_OnFrame(&this->skelanime, 9.0f) ||
            Animation_OnFrame(&this->skelanime, 16.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_KAKASHI_JUMP);
        }
        if (Animation_OnFrame(&this->skelanime, 18.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_KAKASHI_ROLL);
        }
    }
    if (this->animIndex == ENKAKASI_ANIM_SPIN_REACH_OFFER || this->animIndex == ENKAKASI_ANIM_TWIRL) {
        if (Animation_OnFrame(&this->skelanime, 1.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_KAKASH_LONGI_ROLL);
        }
    }
}

/*
 * moves the player's position relative to scarecrow during song teach, also each frame of dance the night away
 */
void EnKakasi_CheckPlayerPosition(EnKakasi* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (globalCtx->sceneNum == SCENE_8ITEMSHOP) {
        player->actor.world.pos.x = -50.0f;
        player->actor.world.pos.z = 155.0f;
    } else if (globalCtx->sceneNum == SCENE_TENMON_DAI) {
        player->actor.world.pos.x = 60.0f;
        player->actor.world.pos.z = -190.0f;
    }

    Math_SmoothStepToS(&player->actor.shape.rot.y, (this->actor.yawTowardsPlayer + 0x8000), 5, 1000, 0);
}

/*
 * this goes off every frame of dancing the night away, and song teaching
 * something to do with cutscene camera?
 */
void func_8096FAAC(EnKakasi* this, GlobalContext* globalCtx) {
    if (this->cutsceneCamId != CAM_ID_MAIN) {
        Math_ApproachF(&this->unk214.x, this->unk238.x, 0.4f, 4.0f);
        Math_ApproachF(&this->unk214.y, this->unk238.y, 0.4f, 4.0f);
        Math_ApproachF(&this->unk214.z, this->unk238.z, 0.4f, 4.0f);

        Math_ApproachF(&this->unk220.x, this->unk244.x, 0.4f, 4.0f);
        Math_ApproachF(&this->unk220.y, this->unk244.y, 0.4f, 4.0f);
        Math_ApproachF(&this->unk220.z, this->unk244.z, 0.4f, 4.0f);

        Math_ApproachF(&this->unk20C, this->unk210, 0.3f, 10.0f);

        Play_CameraSetAtEye(globalCtx, this->cutsceneCamId, &this->unk220, &this->unk214);
        Play_CameraSetFov(globalCtx, this->cutsceneCamId, this->unk20C);
    }
}

/*
 * goes off every frame of song teach, but... doing what?
 */
void func_8096FBB8(EnKakasi* this, GlobalContext* globalCtx) {
    if (globalCtx->msgCtx.unk12048 == 0 || globalCtx->msgCtx.unk12048 == 1 || globalCtx->msgCtx.unk12048 == 2 ||
        globalCtx->msgCtx.unk12048 == 3 || globalCtx->msgCtx.unk12048 == 4) {
        // why not 0 < x < 4? fewer branches
        this->unk190++;
    }
    if (this->unk190 != 0 && this->animIndex != ENKAKASI_ANIM_SIDEWAYS_SHAKING) {
        EnKakasi_SetAnimation(this, ENKAKASI_ANIM_SIDEWAYS_SHAKING);
    }
    if (this->unk190 > 8) {
        this->unk190 = 8;
    }
    if (this->unk190 != 0) {
        Math_ApproachF(&this->skelanime.playSpeed, 1.0f, 0.1f, 0.2f);
        this->actor.shape.rot.y += 0x800;
    }
}

void EnKakasi_InitTimeSkipDialogue(EnKakasi* this) {
    EnKakasi_SetAnimation(this, ENKAKASI_ANIM_SLOWROLL);
    this->actionFunc = EnKakasi_TimeSkipDialogue;
}

void EnKakasi_TimeSkipDialogue(EnKakasi* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (gSaveContext.respawnFlag != -4 && gSaveContext.respawnFlag != -8) {
        if (gSaveContext.save.time != CLOCK_TIME(6, 0) && gSaveContext.save.time != CLOCK_TIME(18, 0) &&
            !(gSaveContext.eventInf[1] & 0x80)) {

            if (this->actor.textId == 0) {
                // dialogue after skipped time 'did you feel that? went by in an instant'
                this->actor.textId = 0x1653;
                gSaveContext.save.weekEventReg[83] &= (u8)~1;
                this->unkMsgState1AC = 5;
                player->stateFlags1 |= 0x20;
                this->actor.flags |= ACTOR_FLAG_10000;
            }

            if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
                player->stateFlags1 &= ~0x20;
                this->unkState196 = 2;
                this->actor.flags &= ~ACTOR_FLAG_10000;
                this->actionFunc = EnKakasi_RegularDialogue;
            } else {
                func_800B8500(&this->actor, globalCtx, 9999.9f, 9999.9f, -1);
            }
        }
    }
}

void EnKakasi_SetupIdleStanding(EnKakasi* this) {
    this->unkState196 = 0;
    this->actionFunc = EnKakasi_IdleStanding;
}

void EnKakasi_IdleStanding(EnKakasi* this, GlobalContext* globalCtx) {
    u32 saveContextDay = gSaveContext.save.day;
    s16 x;
    s16 y;

    // first talk to scarecrow dialogue
    this->actor.textId = 0x1644;
    if (func_800B8718(&this->actor, &globalCtx->state)) {
        this->skelanime.playSpeed = 1.0f;
        EnKakasi_SetupSongTeach(this, globalCtx);
        return;
    }
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->skelanime.playSpeed = 1.0f;
        EnKakasi_SetupDialogue(this);
        return;
    }
    if (globalCtx->actorCtx.unk5 & 0x4) {
        Actor_GetScreenPos(globalCtx, &this->actor, &x, &y);
        if (this->actor.projectedPos.z > -20.0f && x > 0 && x < SCREEN_WIDTH && y > 0 && y < SCREEN_HEIGHT &&
            this->animIndex != ENKAKASI_ANIM_SIDEWAYS_SHAKING) {
            // faster shaking
            EnKakasi_SetAnimation(this, ENKAKASI_ANIM_SIDEWAYS_SHAKING);
            this->skelanime.playSpeed = 2.0f;
        }
    } else if (Player_GetMask(globalCtx) == PLAYER_MASK_KAMARO) {
        if (this->animIndex != ENKAKASI_ANIM_SIDEWAYS_SHAKING) {
            EnKakasi_SetAnimation(this, ENKAKASI_ANIM_SIDEWAYS_SHAKING);
            this->skelanime.playSpeed = 2.0f;
        }
    } else if (saveContextDay == 3 && gSaveContext.save.isNight) {
        this->skelanime.playSpeed = 1.0f;
        if (this->animIndex != ENKAKASI_ANIM_SIDEWAYS_SHAKING) {
            EnKakasi_SetAnimation(this, 1);
        }
    } else if (this->animIndex != ENKAKASI_ANIM_IDLE) {
        EnKakasi_SetAnimation(this, ENKAKASI_ANIM_IDLE);
    }
    if (this->actor.xzDistToPlayer < 120.0f) {
        func_800B8614(&this->actor, globalCtx, 100.0f);
        func_800B874C(&this->actor, globalCtx, 100.0f, 80.0f);
    }
}

void EnKakasi_SetupDialogue(EnKakasi* this) {
    // bug? starts one animation then changes it a few lines down?
    if (this->animIndex != ENKAKASI_ANIM_SIDEWAYS_SHAKING) {
        EnKakasi_SetAnimation(this, ENKAKASI_ANIM_SIDEWAYS_SHAKING);
    }

    this->unkMsgState1AC = 5;
    this->unkState196 = 1;
    EnKakasi_SetAnimation(this, ENKAKASI_ANIM_SPIN_REACH_OFFER);
    this->actionFunc = EnKakasi_RegularDialogue;
}

void EnKakasi_RegularDialogue(EnKakasi* this, GlobalContext* globalCtx) {
    u32 saveContextDay = gSaveContext.save.day;
    f32 currentAnimeFrame = this->skelanime.curFrame;

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 2000, 0);
    // if first dialogue
    if (this->actor.textId != 0x1644 && this->animeFrameCount <= currentAnimeFrame &&
        this->animIndex == ENKAKASI_ANIM_SLOWROLL) {

        EnKakasi_SetAnimation(this, ENKAKASI_ANIM_SPIN_REACH_OFFER);
        this->unkCounter1A4 = 0;
    }

    // if dialogue: oh sorry come back again
    if (this->actor.textId == 0x1651 || this->actor.textId == 0x1659) {
        if (this->animeFrameCount <= currentAnimeFrame && this->animIndex != ENKAKASI_ANIM_SPIN_REACH_OFFER) {
            if (++this->unkCounter1A4 >= 2) {
                this->unkCounter1A4 = 0;
                EnKakasi_SetAnimation(this, ENKAKASI_ANIM_SPIN_REACH_OFFER);
            }
        }
    }

    if (this->unkState1A8 == 2 && this->unkState196 == 2) {
        func_800B7298(globalCtx, &this->actor, 0x49);
        this->unkState1A8 = 0;
    }

    if (this->unkMsgState1AC == Message_GetState(&globalCtx->msgCtx) && Message_ShouldAdvance(globalCtx) != 0) {
        func_801477B4(globalCtx);
        if (this->unkMsgState1AC == 5) {
            // bad song input
            if (this->unkState196 == 2 && this->actor.textId == 0x1647) {
                func_800B7298(globalCtx, &this->actor, 6);
            }

            // after timeskip
            if (this->actor.textId == 0x1653) {
                u32 saveContextDay2 = gSaveContext.save.day;

                if (this->animIndex != ENKAKASI_ANIM_SIDEWAYS_SHAKING) {
                    EnKakasi_SetAnimation(this, ENKAKASI_ANIM_SIDEWAYS_SHAKING);
                }

                if (saveContextDay2 == 3 && gSaveContext.save.isNight) {
                    // text: dangerous outside
                    this->actor.textId = 0x164F;
                } else if (gSaveContext.save.isNight) {
                    // text: would you like to skip time?
                    this->actor.textId = 0x164E;
                } else {
                    // text: would you like to skip time? 2
                    this->actor.textId = 0x1645;
                }

                func_80151938(globalCtx, this->actor.textId);
                return;

            } else if (this->actor.textId == 0x165D || this->actor.textId == 0x165F || this->actor.textId == 0x1660 ||
                       this->actor.textId == 0x1652) {
                func_800B7298(globalCtx, &this->actor, 4);
                if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                    ActorCutscene_Stop(0x7C);
                    ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
                    this->actionFunc = EnKakasi_DancingRemark;
                } else {
                    if (!ActorCutscene_GetCanPlayNext(this->actorCutscenes[0])) {
                        ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
                        this->actionFunc = EnKakasi_DancingRemark;
                    } else {
                        ActorCutscene_StartAndSetUnkLinkFields(this->actorCutscenes[0], &this->actor);
                        this->cutsceneCamId = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
                        this->actionFunc = EnKakasi_DancingRemark;
                    }
                }
                return;

            } else if (this->actor.textId == 0x1645 || this->actor.textId == 0x164E) {
                this->actor.textId = 0x1650; // "Shall we dance?  No Yes"
                if (this->animIndex != ENKAKASI_ANIM_SIDEWAYS_SHAKING) {
                    EnKakasi_SetAnimation(this, ENKAKASI_ANIM_SIDEWAYS_SHAKING);
                }
                this->unkMsgState1AC = 4;

            } else if (this->actor.textId == 0x1644) {
                if (this->animIndex != ENKAKASI_ANIM_SIDEWAYS_SHAKING) {
                    EnKakasi_SetAnimation(this, ENKAKASI_ANIM_SIDEWAYS_SHAKING);
                }
                if (gSaveContext.save.isNight) {
                    this->actor.textId = 0x164E;
                } else {
                    this->actor.textId = 0x1645;
                }

            } else if (this->actor.textId == 0x164F) {
                if (this->animIndex != ENKAKASI_ANIM_SIDEWAYS_SHAKING) {
                    EnKakasi_SetAnimation(this, ENKAKASI_ANIM_SIDEWAYS_SHAKING);
                }
                this->actor.textId = 0x165A;
            } else if (this->actor.textId == 0x1651) {
                if (this->animIndex != ENKAKASI_ANIM_SIDEWAYS_SHAKING) {
                    EnKakasi_SetAnimation(this, ENKAKASI_ANIM_SIDEWAYS_SHAKING);
                }
                this->actor.textId = 0x1654;
            } else if (this->actor.textId == 0x1654) {
                this->actor.textId = 0x1655;
            } else if (this->actor.textId == 0x1655) {
                this->actor.textId = 0x1656;
                this->unkMsgState1AC = 4;
            } else if (this->actor.textId == 0x1658) {
                this->actor.textId = 0x1659;
            } else if (this->actor.textId == 0x165A) {
                this->actor.textId = 0x165B;
            } else if (this->actor.textId == 0x165B) {
                this->actor.textId = 0x165C;
                this->unkMsgState1AC = 4;

            } else if (this->actor.textId == 0x165E) {
                this->actor.textId = 0x165F;
            } else {
                EnKakasi_SetupIdleStanding(this);
                return;
            }
        } else {
            this->unkMsgState1AC = 5;

            if (globalCtx->msgCtx.choiceIndex == 1) {
                func_8019F208();
                if (this->actor.textId == 0x1656) {
                    this->actor.textId = 0x1658;
                } else if (this->actor.textId == 0x165C) {
                    this->actor.textId = 0x165E;
                } else if (saveContextDay == 3 && gSaveContext.save.isNight) {
                    this->actor.textId = 0x164F;
                } else {
                    this->actor.textId = 0x1652;
                }
                EnKakasi_SetAnimation(this, ENKAKASI_ANIM_HOPPING_REGULAR);
            } else {
                func_8019F230();
                if (this->actor.textId == 0x1656) { // would you like to learn a song? yes/no
                    this->actor.textId = 0x1657;
                } else if (this->actor.textId == 0x165C) { // would you like to learn a song? yes/no
                    this->actor.textId = 0x165D;
                } else {
                    this->actor.textId = 0x1651;
                }
                this->unkCounter1A4 = 0;
                if (this->animIndex != ENKAKASI_ANIM_ARMS_CROSSED_ROCKING) {
                    EnKakasi_SetAnimation(this, ENKAKASI_ANIM_ARMS_CROSSED_ROCKING);
                }
            }
        }
        func_80151938(globalCtx, this->actor.textId);
    }
}

void EnKakasi_SetupSongTeach(EnKakasi* this, GlobalContext* globalCtx) {
    this->actor.textId = 0x1646;
    Message_StartTextbox(globalCtx, this->actor.textId, &this->actor);
    this->cutsceneCamId = CAM_ID_MAIN;
    this->unk20C = 0.0f;
    this->unk210 = 60.0f;
    EnKakasi_SetAnimation(this, ENKAKASI_ANIM_TWIRL);
    this->unkState196 = 2;
    this->actionFunc = EnKakasi_OcarinaRemark;
}

/*
 * you took out ocarina hes talking about how he wants to hear you play him a song
 * before actually teaching
 */
void EnKakasi_OcarinaRemark(EnKakasi* this, GlobalContext* globalCtx) {
    if (Message_GetState(&globalCtx->msgCtx) == 5 && Message_ShouldAdvance(globalCtx) != 0) {
        func_80152434(globalCtx, 0x35);
        this->unkState1A8 = 0;
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
            this->actionFunc = EnKakasi_TeachingSong;

        } else if (ActorCutscene_GetCanPlayNext(this->actorCutscenes[0]) == 0) {
            ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
            this->actionFunc = EnKakasi_TeachingSong;

        } else {
            this->unkState1A8 = 1;
            ActorCutscene_StartAndSetUnkLinkFields(this->actorCutscenes[0], &this->actor);
            this->cutsceneCamId = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
            Math_Vec3f_Copy(&this->unk22C, &this->actor.home.pos);
            this->actionFunc = EnKakasi_TeachingSong;
        }
    }
}

void EnKakasi_TeachingSong(EnKakasi* this, GlobalContext* globalCtx) {
    Vec3f tempVec;

    EnKakasi_CheckPlayerPosition(this, globalCtx);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 1, 3000, 0);
    if (this->unkState1A8 == 0) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
            return;
        }
        if (ActorCutscene_GetCanPlayNext(this->actorCutscenes[0]) == 0) {
            ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
            return;
        }
        ActorCutscene_StartAndSetUnkLinkFields(this->actorCutscenes[0], &this->actor);
        this->cutsceneCamId = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
        Math_Vec3f_Copy(&this->unk22C, &this->actor.home.pos);
        this->unkState1A8 = 1;
        this->unkState1A8 = 1;
    }

    if (this->unkState1A8 == 1) {
        this->unk22C.y = this->actor.home.pos.y + 50.0f;
        this->unk238.x = D_80971DCC[this->unk190].x;
        this->unk238.y = D_80971DCC[this->unk190].y;
        this->unk238.z = D_80971DCC[this->unk190].z;

        Math_Vec3f_Copy(&tempVec, &this->unk238);
        OLib_DbCameraVec3fSum(&this->actor.home, &tempVec, &this->unk238, 1);
        Math_Vec3f_Copy(&this->unk244, &this->unk22C);
        Math_Vec3f_Copy(&this->unk214, &this->unk238);
        Math_Vec3f_Copy(&this->unk220, &this->unk244);
        func_8096FAAC(this, globalCtx);
        func_8096FBB8(this, globalCtx);

        if (globalCtx->msgCtx.ocarinaMode == 4) { // song failed
            this->unk190 = 0;
            this->unkCounter1A4 = 0;
            ActorCutscene_Stop(this->actorCutscenes[0]);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_YASE_DEAD);
            if (this) {}
            this->unkState196 = 2;
            this->cutsceneCamId = CAM_ID_MAIN;
            this->actor.textId = 0x1647;
            this->unkState1A8 = 2;
            this->unkMsgState1AC = 5;
            EnKakasi_SetAnimation(this, ENKAKASI_ANIM_ARMS_CROSSED_ROCKING);
            this->actionFunc = EnKakasi_RegularDialogue;

        } else if (globalCtx->msgCtx.ocarinaMode == 3) { // song success
            this->postTeachTimer = 30;
            this->skelanime.playSpeed = 2.0f;
            EnKakasi_SetAnimation(this, ENKAKASI_ANIM_HOPPING_REGULAR);
            this->actionFunc = EnKakasi_PostSongLearnTwirl;
        }
    }
}

void EnKakasi_PostSongLearnTwirl(EnKakasi* this, GlobalContext* globalCtx) {
    f32 animeFrame = this->skelanime.curFrame;

    if (this->postTeachTimer == 0 && this->animIndex != ENKAKASI_ANIM_TWIRL) {
        EnKakasi_SetAnimation(this, ENKAKASI_ANIM_TWIRL);
        this->skelanime.playSpeed = 2.0f;
    }
    if (this->postTeachTimer == 0 && this->animIndex == ENKAKASI_ANIM_TWIRL && this->animeFrameCount <= animeFrame) {
        EnKakasi_SetupPostSongLearnDialogue(this, globalCtx);
    }
}

void EnKakasi_SetupPostSongLearnDialogue(EnKakasi* this, GlobalContext* globalCtx) {
    ActorCutscene_Stop(this->actorCutscenes[0]);
    globalCtx->msgCtx.ocarinaMode = 4;
    this->unk190 = 0;
    this->unkCounter1A4 = 0;
    EnKakasi_SetAnimation(this, ENKAKASI_ANIM_HOPPING_REGULAR);
    this->cutsceneCamId = CAM_ID_MAIN;
    this->unkMsgState1AC = 5;
    this->unkState1A8 = 1;
    this->actionFunc = EnKakasi_PostSongLearnDialogue;
    this->unk20C = 0.0f;
    this->unk210 = 60.0f;
}

void EnKakasi_PostSongLearnDialogue(EnKakasi* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 tempAnimFrame = this->skelanime.curFrame;
    Vec3f vec3fCopy;

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 1, 3000, 0);
    Math_SmoothStepToS(&player->actor.shape.rot.y, this->actor.yawTowardsPlayer + 0x8000, 5, 1000, 0);

    if (this->unk190 == 0) {
        func_801477B4(globalCtx);
        func_800B7298(globalCtx, &this->actor, 0x56);
        this->actor.textId = 0x1648;
        Message_StartTextbox(globalCtx, (this->actor.textId), &this->actor);
        this->unkState1A8 = 0;
        this->unk190 = 1;
    }

    if (this->actor.textId == 0x1648 && this->animIndex == ENKAKASI_ANIM_HOPPING_REGULAR &&
        this->animeFrameCount <= tempAnimFrame) {
        this->unkCounter1A4++;
        if (this->unkCounter1A4 >= 2) {
            EnKakasi_SetAnimation(this, ENKAKASI_ANIM_ARMS_CROSSED_ROCKING);
        }
    }

    if (this->actor.textId == 0x164B && this->animIndex == ENKAKASI_ANIM_ARMS_CROSSED_ROCKING &&
        this->animeFrameCount <= tempAnimFrame) {
        this->unkCounter1A4++;
        if (this->unkCounter1A4 >= 2) {
            EnKakasi_SetAnimation(this, ENKAKASI_ANIM_SPIN_REACH_OFFER);
        }
    }

    if (this->unkState1A8 == 0) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
            return;
        }
        if (ActorCutscene_GetCanPlayNext(this->actorCutscenes[0]) == 0) {
            ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
            return;
        }
        Math_Vec3f_Copy(&this->unk22C, &this->actor.home.pos);
        ActorCutscene_StartAndSetUnkLinkFields(this->actorCutscenes[0], &this->actor);
        this->cutsceneCamId = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
        func_800B7298(globalCtx, &this->actor, 0x56);
        this->unkState1A8 = 1;
    }

    if (this->cutsceneCamId != CAM_ID_MAIN) {
        this->unk22C.y = this->actor.home.pos.y + 50.0f;
        EnKakasi_CheckPlayerPosition(this, globalCtx);
        this->unk238.x = D_80971FA0[this->unk190].x;
        this->unk238.y = D_80971FA0[this->unk190].y;
        this->unk238.z = D_80971FA0[this->unk190].z;
        Math_Vec3f_Copy(&vec3fCopy, &this->unk238);
        OLib_DbCameraVec3fSum(&this->actor.home, &vec3fCopy, &this->unk238, 1);
        this->unk244.x = D_80971FE8[this->unk190].x + this->unk22C.x;
        this->unk244.y = D_80971FE8[this->unk190].y + this->unk22C.y;
        this->unk244.z = D_80971FE8[this->unk190].z + this->unk22C.z;
        Math_Vec3f_Copy(&this->unk214, &this->unk238);
        Math_Vec3f_Copy(&this->unk220, &this->unk244);
    }

    func_8096FAAC(this, globalCtx);

    if (this->unkState1A8 != 0 && Message_GetState(&globalCtx->msgCtx) == this->unkMsgState1AC &&
        Message_ShouldAdvance(globalCtx) != 0) {

        func_801477B4(globalCtx);

        if (this->unkMsgState1AC == 5) {
            this->unk190++;
            if (this->unk190 > 5) {
                this->unk190 = 5;
            }

            if (this->actor.textId == 0x1648) {
                func_800B7298(globalCtx, &this->actor, 7);
                this->actor.textId = 0x1649;
                if (this->animIndex != ENKAKASI_ANIM_ARMS_CROSSED_ROCKING) {
                    EnKakasi_SetAnimation(this, ENKAKASI_ANIM_ARMS_CROSSED_ROCKING);
                }

            } else if (this->actor.textId == 0x1649) {
                this->actor.textId = 0x1660;
                this->unkMsgState1AC = 4;

            } else if (this->actor.textId == 0x164A) {
                this->actor.textId = 0x164B;

            } else if (this->actor.textId == 0x164B) {
                this->actor.textId = 0x164C;
                EnKakasi_SetAnimation(this, ENKAKASI_ANIM_TWIRL);

            } else {
                if (this->actor.textId == 0x164C || this->actor.textId == 0x1661) {
                    EnKakasi_SetupDigAway(this);
                    return;
                }
            }

        } else {
            this->unkMsgState1AC = 5;
            if (globalCtx->msgCtx.choiceIndex == 1) {
                func_8019F208(); // play 0x4808 sfx (decide) and calls func_801A75E8
                this->actor.textId = 0x164A;
            } else {
                func_8019F230(); // play 0x480A sfx (cancel) and calls func_801A75E8
                this->actor.textId = 0x1661;
            }
        }
        func_80151938(globalCtx, this->actor.textId);
    }
}

/*
 * talking before dancing the night away, and cutscene setup
 */
void EnKakasi_DancingRemark(EnKakasi* this, GlobalContext* globalCtx) {
    u32 currentDay = gSaveContext.save.day;

    this->unkState196 = 3;
    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
    } else if (ActorCutscene_GetCanPlayNext(this->actorCutscenes[0]) == 0) {
        ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
    } else {
        ActorCutscene_StartAndSetUnkLinkFields(this->actorCutscenes[0], &this->actor);
        this->cutsceneCamId = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
        if (currentDay == 3 && gSaveContext.save.isNight) {
            EnKakasi_SetupDigAway(this);
        } else {
            func_801A2BB8(NA_BGM_SARIAS_SONG);
            EnKakasi_SetupDanceNightAway(this);
        }
    }
}

void EnKakasi_SetupDanceNightAway(EnKakasi* this) {
    this->unk190 = 0;
    this->unkCounter1A4 = 0;
    this->unk20C = 0.0f;
    this->unk210 = 60.0f;
    EnKakasi_SetAnimation(this, ENKAKASI_ANIM_TWIRL);
    Math_Vec3f_Copy(&this->unk22C, &this->actor.home.pos);
    func_8016566C(0xB4);
    this->actionFunc = EnKakasi_DancingNightAway;
}

void EnKakasi_DancingNightAway(EnKakasi* this, GlobalContext* globalCtx) {
    f32 currentFrame;
    Vec3f localVec3f;
    Player* player;

    currentFrame = this->skelanime.curFrame;
    EnKakasi_CheckPlayerPosition(this, globalCtx);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 1, 3000, 0);
    this->unk22C.y = this->actor.home.pos.y + 50.0f;

    this->unk238.x = D_80971E38[this->unk190].x;
    this->unk238.y = D_80971E38[this->unk190].y;
    this->unk238.z = D_80971E38[this->unk190].z;
    Math_Vec3f_Copy(&localVec3f, &this->unk238);
    OLib_DbCameraVec3fSum(&this->actor.home, &localVec3f, &this->unk238, 1);

    if (1) {}
    this->unk244.x = D_80971EEC[this->unk190].x + this->unk22C.x;
    this->unk244.y = D_80971EEC[this->unk190].y + this->unk22C.y;
    this->unk244.z = D_80971EEC[this->unk190].z + this->unk22C.z;
    if (this->unk190 != 6 && this->unk190 != 7) {
        Math_Vec3f_Copy(&this->unk214, &this->unk238);
        Math_Vec3f_Copy(&this->unk220, &this->unk244);
    }
    if (this->unk190 >= 7 && this->unk190 != 0xE) {
        this->actor.shape.rot.y += 0x800;
    }

    func_8096FAAC(this, globalCtx);

    // switching through manual cutscene states
    switch (this->unk190) {
        case 0:
            // twirling
            this->unk204 = 0x28;
            this->unk190++;
            return;
        case 1:
            // end of twirl, start shaking back and forth
            if (this->unk204 == 0 && this->animeFrameCount <= currentFrame) {
                this->unk204 = 0x14;
                this->unk190++;
                EnKakasi_SetAnimation(this, ENKAKASI_ANIM_SIDEWAYS_SHAKING);
            }
            return;
        case 2:
            // camera view on the left
            if (this->unk204 == 0) {
                this->unk204 = 0x14;
                this->unk190++;
            }
            return;
        case 3:
            // camera view on the right
            if (this->unk204 == 0) {
                this->unk204 = 0x14;
                this->unk190++;
            }
            return;
        case 4:
            // camera view close up front
            if (this->unk204 == 0) {
                this->unk204 = 0x14;
                this->unk190++;
            }
            return;
        case 5:
            // camera view zoomed out front
            if (this->unk204 == 0) {
                this->unk204 = 0xF;
                this->unk190++;
            }
            return;
        case 6:
            // zoom in and sweep down in from case 5
            if (this->unk204 == 0) {
                this->unk204 = 0xF;
                this->unk190++;
            }
            return;
        case 7:
            // zoom in close from case 6
            if (this->unk204 == 0) {
                this->unk204 = 0xA;
                this->unk190++;
            }
            return;

        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            // multiple quick angle cuts viewing from multiple sides
            if (this->unk204 == 0) {
                this->unk190++;
                this->unk204 = 0xA;
                if (this->unk190 == 0xE) {
                    func_800B7298(globalCtx, &this->actor, 0x49);
                    func_80165690();
                    this->unk204 = 0x14;
                }
            }
            return;
        case 14:
            // goes off once for some camera changes,
            // otherwise its the end when camera is back to normal and link is confused
            Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 1000, 0);
            if (this->unk204 == 0) {
                player = GET_PLAYER(globalCtx);

                Play_SetRespawnData(&globalCtx->state, RESTART_MODE_DOWN, Entrance_CreateIndexFromSpawn(0),
                                    player->unk_3CE, 0xBFF, &player->unk_3C0, player->unk_3CC);
                func_80169EFC(&globalCtx->state);

                if (0) {}
                if (gSaveContext.save.time > CLOCK_TIME(18, 0) || gSaveContext.save.time < CLOCK_TIME(6, 0)) {
                    gSaveContext.save.time = CLOCK_TIME(6, 0);
                    gSaveContext.respawnFlag = -4;
                    gSaveContext.eventInf[2] |= 0x80;
                } else {
                    gSaveContext.save.time = CLOCK_TIME(18, 0);
                    gSaveContext.respawnFlag = -8;
                }
                gSaveContext.save.weekEventReg[83] |= 1;
                this->unk190 = 0;
                this->actionFunc = EnKakasi_DoNothing;
            }
    }
}

void EnKakasi_DoNothing(EnKakasi* this, GlobalContext* globalCtx) {
}

void EnKakasi_SetupDigAway(EnKakasi* this) {
    if (this->animIndex != ENKAKASI_ANIM_SIDEWAYS_SHAKING) {
        EnKakasi_SetAnimation(this, ENKAKASI_ANIM_SIDEWAYS_SHAKING);
    }
    this->unk190 = 0;
    this->unkCounter1A4 = 0;
    this->unk210 = 60.0f;
    this->unk20C = 60.0f;
    Math_Vec3f_Copy(&this->unk22C, &this->actor.home.pos);
    this->unkState196 = 4;
    this->actionFunc = EnKakasi_DiggingAway;
}

void EnKakasi_DiggingAway(EnKakasi* this, GlobalContext* globalCtx) {
    Vec3f tempunk238;
    Vec3f tempWorldPos;

    if (this->cutsceneCamId != CAM_ID_MAIN) {
        this->unk22C.y = this->actor.home.pos.y + 50.0f;
        this->unk238.x = D_80972030.x;
        this->unk238.y = D_80972030.y;
        this->unk238.z = D_80972030.z;

        Math_Vec3f_Copy(&tempunk238, &this->unk238);
        OLib_DbCameraVec3fSum(&this->actor.home, &tempunk238, &this->unk238, 1);
        this->unk244.x = ((f32)D_8097203C.x) + this->unk22C.x; // cast req
        this->unk244.y = ((f32)D_8097203C.y) + this->unk22C.y;
        this->unk244.z = ((f32)D_8097203C.z) + this->unk22C.z;
        Math_Vec3f_Copy(&this->unk214, &this->unk238);
        Math_Vec3f_Copy(&this->unk220, &this->unk244);
        func_8096FAAC(this, globalCtx);
    }

    if (this->unkCounter1A4 < 15) {
        this->unkCounter1A4++;
        return;
    }

    this->actor.shape.rot.y += 0x3000;
    Math_SmoothStepToS(&this->unk190, 500, 5, 50, 0);
    if ((globalCtx->gameplayFrames % 4) == 0) {
        Math_Vec3f_Copy(&tempWorldPos, &this->actor.world.pos);
        tempWorldPos.y = this->actor.floorHeight;
        tempWorldPos.x += randPlusMinusPoint5Scaled(2.0f);
        tempWorldPos.z += randPlusMinusPoint5Scaled(2.0f);

        if (globalCtx->sceneNum == SCENE_8ITEMSHOP) {
            EffectSsGSplash_Spawn(globalCtx, &tempWorldPos, 0, 0, 0, randPlusMinusPoint5Scaled(100.0f) + 200.0f);
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &tempWorldPos, 0x32, NA_SE_EV_BOMB_DROP_WATER);

        } else {
            Actor_SpawnFloorDustRing(globalCtx, &this->actor, &this->actor.world.pos,
                                     this->actor.shape.shadowScale - 20.0f, 5, 4.0f, 200, 10, 1);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
        }
    }

    Math_ApproachF(&this->actor.shape.yOffset, -6000.0f, 0.5f, 200.0f);
    if (fabsf(this->actor.shape.yOffset + 6000.0f) < 10.0f) {
        gSaveContext.save.weekEventReg[79] |= 8;
        func_800B7298(globalCtx, &this->actor, 6);
        ActorCutscene_Stop(this->actorCutscenes[0]);
        this->aboveGroundStatus = ENKAKASI_ABOVE_GROUND_TYPE;
        this->songSummonDist = 80.0f;
        EnKakasi_SetupIdleUnderground(this);
    }
}

void EnKakasi_SetupIdleUnderground(EnKakasi* this) {
    this->actor.shape.yOffset = -7000.0;
    this->actor.draw = NULL;
    this->actor.flags |= ACTOR_FLAG_8000000;
    this->unkState196 = 5;
    this->actionFunc = EnKakasi_IdleUnderground;
}

void EnKakasi_IdleUnderground(EnKakasi* this, GlobalContext* globalCtx) {
    if ((gSaveContext.save.weekEventReg[79] & 8) && this->actor.xzDistToPlayer < this->songSummonDist &&
        (BREG(1) != 0 || globalCtx->msgCtx.ocarinaMode == 0xD)) {
        this->actor.flags &= ~ACTOR_FLAG_8000000;
        globalCtx->msgCtx.ocarinaMode = 4;
        this->actionFunc = EnKakasi_SetupRiseOutOfGround;
    }
}

void EnKakasi_SetupRiseOutOfGround(EnKakasi* this, GlobalContext* globalCtx) {
    s32 cutsceneIndex;

    cutsceneIndex = 0;
    if (this->aboveGroundStatus == ENKAKASI_ABOVE_GROUND_TYPE) {
        cutsceneIndex = 1;
    }

    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(this->actorCutscenes[cutsceneIndex]);

    } else if (ActorCutscene_GetCanPlayNext(this->actorCutscenes[cutsceneIndex]) == 0) {
        ActorCutscene_SetIntentToPlay(this->actorCutscenes[cutsceneIndex]);

    } else {
        ActorCutscene_StartAndSetUnkLinkFields(this->actorCutscenes[cutsceneIndex], &this->actor);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
        this->actor.draw = EnKakasi_Draw;
        this->unkState196 = 6;
        this->actionFunc = EnKakasi_RisingOutOfGround;
    }
}

void EnKakasi_RisingOutOfGround(EnKakasi* this, GlobalContext* globalCtx) {
    this->actor.shape.rot.y += 0x3000;

    if (this->animIndex != ENKAKASI_ANIM_SIDEWAYS_SHAKING) {
        EnKakasi_SetAnimation(this, ENKAKASI_ANIM_SIDEWAYS_SHAKING);
    }
    if (this->actor.shape.yOffset < -10.0f) {
        if ((globalCtx->gameplayFrames % 8) == 0) {
            Actor_SpawnFloorDustRing(globalCtx, &this->actor, &this->actor.world.pos,
                                     this->actor.shape.shadowScale - 20.0f, 10, 8.0f, 500, 10, 1);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
        }
        Math_ApproachF(&this->actor.shape.yOffset, 0.0f, 0.5f, 200.0f);
    } else {
        EnKakasi_SetupIdleRisen(this);
    }
}

void EnKakasi_SetupIdleRisen(EnKakasi* this) {
    // text: great to see you again
    this->actor.textId = 0x164D;
    this->unkState196 = 7;
    this->actionFunc = EnKakasi_IdleRisen;
    this->actor.shape.yOffset = 0.0f;
}

void EnKakasi_IdleRisen(EnKakasi* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 1000, 0);
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = EnKakasi_RisenDialogue;
    } else {
        func_800B8614(&this->actor, globalCtx, 70.0f);
    }
}

void EnKakasi_RisenDialogue(EnKakasi* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 1000, 0);

    if (Message_GetState(&globalCtx->msgCtx) == 5 && Message_ShouldAdvance(globalCtx) != 0) {
        func_801477B4(globalCtx);
        EnKakasi_SetupIdleRisen(this);
    }
}

void EnKakasi_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnKakasi* this = THIS;
    s32 pad;

    SkelAnime_Update(&this->skelanime);
    if (this->actor.draw != NULL) {
        EnKakasi_CheckAnimationSfx(this);
    }

    this->actor.world.rot.y = this->actor.shape.rot.y;
    DECR(this->postTeachTimer);
    DECR(this->unk204);

    if (this->unkState196 != 5) {
        if (this->unk1BC.x != 0.0f || this->unk1BC.z != 0.0f) {
            Math_Vec3f_Copy(&this->actor.focus.pos, &this->unk1BC);
            this->actor.focus.pos.y += 10.0f;
            if (this->cutsceneCamId == CAM_ID_MAIN) {
                Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
            } else {
                Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.home.rot);
            }
        }
    } else {
        Actor_SetFocus(&this->actor, this->unkHeight);
    }

    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 50.0f, 50.0f, 100.0f, 0x1C);
    if (this->actor.draw != NULL) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void EnKakasi_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnKakasi* this = THIS;

    if (limbIndex == 4) {
        Matrix_MultiplyVector3fByState(&gZeroVec3f, &this->unk1BC);
    }
}

void EnKakasi_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnKakasi* this = THIS;
    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelanime.skeleton, this->skelanime.jointTable, this->skelanime.dListCount,
                          NULL, EnKakasi_PostLimbDraw, &this->actor);
}
