/*
 * File: z_en_minifrog.c
 * Overlay: ovl_En_Minifrog
 * Description: Five Frogs of the Frog Choir
 */

#include "z_en_minifrog.h"
#include "objects/object_fr/object_fr.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnMinifrog*)thisx)

void EnMinifrog_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMinifrog_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMinifrog_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMinifrog_Draw(Actor* thisx, GlobalContext* globalCtx);

EnMinifrog* EnMinifrog_GetFrog(GlobalContext* globalCtx);

void EnMinifrog_SpawnGrowAndShrink(EnMinifrog* this, GlobalContext* globalCtx);
void EnMinifrog_Idle(EnMinifrog* this, GlobalContext* globalCtx);
void EnMinifrog_SetupNextFrogInit(EnMinifrog* this, GlobalContext* globalCtx);
void EnMinifrog_UpdateMissingFrog(Actor* thisx, GlobalContext* globalCtx);
void EnMinifrog_YellowFrogDialog(EnMinifrog* this, GlobalContext* globalCtx);
void EnMinifrog_SetupYellowFrogDialog(EnMinifrog* this, GlobalContext* globalCtx);

const ActorInit En_Minifrog_InitVars = {
    ACTOR_EN_MINIFROG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_FR,
    sizeof(EnMinifrog),
    (ActorFunc)EnMinifrog_Init,
    (ActorFunc)EnMinifrog_Destroy,
    (ActorFunc)EnMinifrog_Update,
    (ActorFunc)EnMinifrog_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 12, 14, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit sColChkInfoInit = { 1, 12, 14, MASS_IMMOVABLE };

// sEyeTextures???
static TexturePtr D_808A4D74[] = {
    object_fr_Tex_0059A0,
    object_fr_Tex_005BA0,
};

// gSaveContext.save.weekEventReg[KEY] = VALUE
// KEY | VALUE
static u16 isFrogReturnedFlags[] = {
    (0 << 8) | 0x00,  // NULL
    (32 << 8) | 0x40, // Woodfall Temple Frog Returned
    (32 << 8) | 0x80, // Great Bay Temple Frog Returned
    (33 << 8) | 0x01, // Southern Swamp Frog Returned
    (33 << 8) | 0x02, // Laundry Pool Frog Returned
};

static s32 isInitialized = false;

static InitChainEntry sInitChain[] = {
    ICHAIN_F32_DIV1000(gravity, -800, ICHAIN_STOP),
};

void EnMinifrog_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnMinifrog* this = THIS;
    int i;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 15.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_fr_Skel_00B538, &object_fr_Anim_001534, this->jointTable,
                       this->morphTable, 24);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, NULL, &sColChkInfoInit);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);

    if (!isInitialized) {
        for (i = 0; i < 2; i++) {
            D_808A4D74[i] = Lib_SegmentedToVirtual(D_808A4D74[i]);
        }
        isInitialized = true;
    }

    this->frogIndex = (this->actor.params & 0xF);
    if (this->frogIndex >= 5) {
        this->frogIndex = MINIFROG_YELLOW;
    }

    this->actor.speedXZ = 0.0f;
    this->actionFunc = EnMinifrog_Idle;
    this->jumpState = MINIFROG_STATE_GROUND;
    this->flags = 0;
    this->timer = 0;

    if (1) {}
    if (!EN_MINIFROG_IS_RETURNED(this)) {
        if ((this->frogIndex == MINIFROG_YELLOW) ||
            ((gSaveContext.save.weekEventReg[isFrogReturnedFlags[this->frogIndex] >> 8] &
              (u8)isFrogReturnedFlags[this->frogIndex]))) {
            Actor_MarkForDeath(&this->actor);
        } else {
            this->timer = 30;
            this->actionFunc = EnMinifrog_SpawnGrowAndShrink;
            this->actor.textId = 0xD81; // "Ah! Don Gero! It has been so long."
            this->actor.colChkInfo.mass = 30;
        }
    } else { // Frogs in mountain village
        if (this->frogIndex == MINIFROG_YELLOW) {
            this->actor.textId = 0;
            this->actionFunc = EnMinifrog_SetupYellowFrogDialog;

            // Not spoken to MINIFROG_YELLOW
            if (!(gSaveContext.save.weekEventReg[34] & 1)) {
                this->actor.flags |= ACTOR_FLAG_10000;
            }

            this->actor.home.rot.x = this->actor.home.rot.z = 0;
            this->frog = NULL;
        } else {
            this->frog = EnMinifrog_GetFrog(globalCtx);
            this->actor.flags &= ~ACTOR_FLAG_1;

            // Frog has been returned
            if ((gSaveContext.save.weekEventReg[isFrogReturnedFlags[this->frogIndex] >> 8] &
                 (u8)isFrogReturnedFlags[this->frogIndex])) {
                this->actionFunc = EnMinifrog_SetupNextFrogInit;
            } else {
                this->actor.draw = NULL;
                this->actor.update = EnMinifrog_UpdateMissingFrog;
            }
        }
    }
}

void EnMinifrog_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnMinifrog* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
    if (this->flags & 0x100) {
        func_801A1F88();
    }
}

EnMinifrog* EnMinifrog_GetFrog(GlobalContext* globalCtx) {
    EnMinifrog* frog = (EnMinifrog*)globalCtx->actorCtx.actorLists[ACTORCAT_NPC].first;

    while (frog != NULL) {
        if ((frog->actor.id != ACTOR_EN_MINIFROG) || (frog->actor.params & 0xF)) {
            frog = (EnMinifrog*)frog->actor.next;
        } else {
            return frog;
        }
    }

    return NULL;
}

void EnMinifrog_SetJumpState(EnMinifrog* this) {
    if (this->jumpState == MINIFROG_STATE_GROUND) {
        this->jumpState = MINIFROG_STATE_JUMP;
        Animation_Change(&this->skelAnime, &object_fr_Anim_0007BC, 1.0f, 0.0f, 7.0f, 2, -5.0f);
    }
}

void EnMinifrog_JumpTimer(EnMinifrog* this) {
    if (this->timer > 0) {
        this->timer--;
    } else {
        this->timer = 60 + (s32)Rand_ZeroFloat(40.0f);
        EnMinifrog_SetJumpState(this);
    }
}

void EnMinifrog_Jump(EnMinifrog* this) {
    SkelAnime_Update(&this->skelAnime);
    switch (this->jumpState) {
        case MINIFROG_STATE_JUMP:
            if (Animation_OnFrame(&this->skelAnime, 4.0f)) {
                this->actor.bgCheckFlags &= ~1;
                this->actor.velocity.y = 6.0f;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FROG_JUMP);
                this->jumpState = MINIFROG_STATE_AIR;
            }
            break;
        case MINIFROG_STATE_AIR:
            if (this->actor.bgCheckFlags & 1) {
                this->jumpState = MINIFROG_STATE_GROUND;
                Animation_MorphToLoop(&this->skelAnime, &object_fr_Anim_001534, -2.5f);
                SkelAnime_Update(&this->skelAnime);
            }
            break;
    }
}

void EnMinifrog_TurnToPlayer(EnMinifrog* this) {
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x400);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void EnMinifrog_TurnToMissingFrog(EnMinifrog* this) {
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 0x400);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

static Color_RGBA8 sPrimColor = { 255, 255, 255, 255 };
static Color_RGBA8 sEnvColor = { 80, 80, 80, 255 };

void EnMinifrog_SpawnDust(EnMinifrog* this, GlobalContext* globalCtx) {
    Vec3f pos;
    Vec3f vec5;
    Vec3f vel;
    Vec3f accel;
    s16 yaw;
    s16 pitch;
    Vec3f eye = GET_ACTIVE_CAM(globalCtx)->eye;
    s32 i;

    yaw = Math_Vec3f_Yaw(&eye, &this->actor.world.pos);
    pitch = -Math_Vec3f_Pitch(&eye, &this->actor.world.pos);
    vec5.x = this->actor.world.pos.x - (5.0f * Math_SinS(yaw) * Math_CosS(pitch));
    vec5.y = this->actor.world.pos.y - (5.0f * Math_SinS(pitch));
    vec5.z = this->actor.world.pos.z - (5.0f * Math_CosS(yaw) * Math_CosS(pitch));

    for (i = 0; i < 5; i++) {
        vel.x = randPlusMinusPoint5Scaled(4.0f);
        vel.y = randPlusMinusPoint5Scaled(4.0f);
        vel.z = randPlusMinusPoint5Scaled(4.0f);
        accel.x = -vel.x * 0.1f;
        accel.y = -vel.y * 0.1f;
        accel.z = -vel.z * 0.1f;
        pos.x = vec5.x + vel.x;
        pos.y = vec5.y + vel.y;
        pos.z = vec5.z + vel.z;
        func_800B0F80(globalCtx, &pos, &vel, &accel, &sPrimColor, &sEnvColor, 300, 30, 10);
    }
}

void EnMinifrog_ReturnFrogCutscene(EnMinifrog* this, GlobalContext* globalCtx) {
    u8 flag;

    EnMinifrog_TurnToPlayer(this);
    EnMinifrog_Jump(this);
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        EnMinifrog_SetJumpState(this);

        switch (globalCtx->msgCtx.currentTextId) {
            case 0xD81: // "Ah! Don Gero! It has been so long."
            case 0xD83: // "Could it be... Has spring finally come to the mountains?"
            case 0xD84: // "That look...It is true! Winter was so long that I began to lose all hope."
            case 0xD86: // "Could it be... You came all this way looking for me?"
            case 0xD87: // "Ah! You need not say a thing. Upon seeing that face, I understand!" ...
                func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                break;
            case 0xD82:                                          // "What has brought you all this way?"
                if (gSaveContext.save.weekEventReg[33] & 0x80) { // Mountain village is unfrozen
                    func_80151938(globalCtx, 0xD83); // "Could it be... Has spring finally come to the mountains?"
                } else {
                    func_80151938(globalCtx, 0xD86); // "Could it be... You came all this way looking for me?"
                }

                flag = gSaveContext.save.weekEventReg[isFrogReturnedFlags[this->frogIndex] >> 8];
                gSaveContext.save.weekEventReg[isFrogReturnedFlags[this->frogIndex] >> 8] =
                    flag | (u8)isFrogReturnedFlags[this->frogIndex];
                break;
            case 0xD85: // "I understand. I shall head for the mountains immediately."
            default:
                func_801477B4(globalCtx);
                EnMinifrog_SpawnDust(this, globalCtx);
                SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 30, NA_SE_EN_NPC_FADEAWAY);
                if (this->actor.cutscene != -1) {
                    if (ActorCutscene_GetCurrentIndex() == this->actor.cutscene) {
                        ActorCutscene_Stop(this->actor.cutscene);
                    }
                }

                Actor_MarkForDeath(&this->actor);
                return;
        }
    }

    if (this->flags & 1) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
            ActorCutscene_Start(this->actor.cutscene, &this->actor);
            this->flags &= ~1;
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    }
}

// This can be seen when the Cyan and Pink frogs spawn after their respective minibosses
void EnMinifrog_SpawnGrowAndShrink(EnMinifrog* this, GlobalContext* globalCtx) {
    EnMinifrog_Jump(this);
    if (this->timer > 0) {
        Actor_SetScale(&this->actor, (0.01f + 0.0003f * this->timer * Math_SinS(0x1000 * (this->timer & 7))));
        this->timer--;
    } else {
        Actor_SetScale(&this->actor, 0.01f);
        this->actionFunc = EnMinifrog_Idle;
    }
}

void EnMinifrog_Idle(EnMinifrog* this, GlobalContext* globalCtx) {
    EnMinifrog_TurnToPlayer(this);
    EnMinifrog_Jump(this);
    EnMinifrog_JumpTimer(this);
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = EnMinifrog_ReturnFrogCutscene;
        if (this->actor.cutscene != -1) {
            this->flags |= 1;
        }
    } else if ((this->actor.xzDistToPlayer < 100.0f) && Player_IsFacingActor(&this->actor, 0x3000, globalCtx) &&
               (Player_GetMask(globalCtx) == PLAYER_MASK_DON_GERO)) {
        func_800B8614(&this->actor, globalCtx, 110.0f);
    }
}

void EnMinifrog_SetupNextFrogInit(EnMinifrog* this, GlobalContext* globalCtx) {
    EnMinifrog* nextFrog;
    EnMinifrog* missingFrog;

    EnMinifrog_Jump(this);
    nextFrog = this->frog;
    if (nextFrog != NULL) {
        missingFrog = nextFrog->frog;
        if (nextFrog->frog != NULL) {
            this->actor.home.rot.y =
                (s16)Actor_YawBetweenActors(&this->actor, &missingFrog->actor); // Set home to missing frog
            EnMinifrog_TurnToMissingFrog(this);
        } else {
            EnMinifrog_TurnToPlayer(this);
        }

        if (this->frog->actor.home.rot.z == (this->actor.params & 0xF)) {
            EnMinifrog_SetJumpState(this);
            this->frog->actor.home.rot.z = 0;
        }
    }
}

void EnMinifrog_CheckChoirSuccess(EnMinifrog* this, GlobalContext* globalCtx) {
    this->actionFunc = EnMinifrog_YellowFrogDialog;
    if (this->frog != NULL) {
        func_80151938(globalCtx, 0xD78); // "Unfortunately, it seems not all of our members have gathered."
    } else {
        func_80151938(globalCtx,
                      0xD7C); // "The conducting was spectacular. And all of our members rose to the occasion!"
    }

    EnMinifrog_SetJumpState(this);
    this->frog = NULL;
    this->actor.home.rot.z = 0;
}

void EnMinifrog_ContinueChoirCutscene(EnMinifrog* this, GlobalContext* globalCtx) {
    EnMinifrog_Jump(this);
    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        EnMinifrog_CheckChoirSuccess(this, globalCtx);
        return; // necessary to match
    } else if (ActorCutscene_GetCanPlayNext(0x7C)) {
        ActorCutscene_Start(0x7C, NULL);
        EnMinifrog_CheckChoirSuccess(this, globalCtx);
        return; // necessary to match
    } else if (this->actor.cutscene != -1 && ActorCutscene_GetCurrentIndex() == this->actor.cutscene) {
        ActorCutscene_Stop(this->actor.cutscene);
        ActorCutscene_SetIntentToPlay(0x7C);
        return; // necessary to match
    } else {
        ActorCutscene_SetIntentToPlay(0x7C);
    }
}

void EnMinifrog_NextFrogMissing(EnMinifrog* this, GlobalContext* globalCtx) {
    EnMinifrog_TurnToMissingFrog(this);
    EnMinifrog_Jump(this);
    if (this->timer > 0) {
        this->timer--;
    } else {
        this->actionFunc = EnMinifrog_ContinueChoirCutscene;
    }
}

void EnMinifrog_NextFrogReturned(EnMinifrog* this, GlobalContext* globalCtx) {
    EnMinifrog_Jump(this);
    if (this->timer > 0) {
        this->timer--;
    } else {
        this->actionFunc = EnMinifrog_ContinueChoirCutscene;
        this->flags &= ~(0x2 << MINIFROG_YELLOW | 0x2 << MINIFROG_CYAN | 0x2 << MINIFROG_PINK | 0x2 << MINIFROG_BLUE |
                         0x2 << MINIFROG_WHITE);
        globalCtx->setPlayerTalkAnim(globalCtx, &gameplay_keep_Linkanim_00DEA8, 0);
    }
}

void EnMinifrog_SetupNextFrogChoir(EnMinifrog* this, GlobalContext* globalCtx) {
    u8 frogIndex;

    EnMinifrog_Jump(this);
    frogIndex = func_801A39F8();
    if (frogIndex != MINIFROG_INVALID) {
        if (frogIndex == MINIFROG_YELLOW) {
            EnMinifrog_SetJumpState(this);
        } else {
            this->actor.home.rot.z = frogIndex; // This is strange to store the frog index in home z rotation
        }

        if (!(this->flags & (0x2 << frogIndex))) {
            this->flags |= (0x2 << frogIndex);
            this->timer--;
        }
    }

    if (this->frog != NULL) {
        this->actor.home.rot.z = 0;
        this->actionFunc = EnMinifrog_NextFrogMissing;
        this->timer = 60;
        this->actor.home.rot.y = Actor_YawBetweenActors(&this->actor, &this->frog->actor);
        func_801A1F88();
        this->flags &= ~0x100;
        this->flags &= ~(0x2 << MINIFROG_YELLOW | 0x2 << MINIFROG_CYAN | 0x2 << MINIFROG_PINK | 0x2 << MINIFROG_BLUE |
                         0x2 << MINIFROG_WHITE);
        globalCtx->setPlayerTalkAnim(globalCtx, &gameplay_keep_Linkanim_00DEA8, 0);
    } else if (this->timer <= 0) {
        this->actionFunc = EnMinifrog_NextFrogReturned;
        this->timer = 30;
    }
}

void EnMinifrog_BeginChoirCutscene(EnMinifrog* this, GlobalContext* globalCtx) {
    EnMinifrog_Jump(this);
    if (this->actor.cutscene == -1) {
        this->actionFunc = EnMinifrog_SetupNextFrogChoir;
    } else if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_Start(this->actor.cutscene, &this->actor);
        this->actionFunc = EnMinifrog_SetupNextFrogChoir;
        this->timer = 5;
        func_801A1F00(3, NA_BGM_FROG_SONG);
        this->flags |= 0x100;
        globalCtx->setPlayerTalkAnim(globalCtx, &gameplay_keep_Linkanim_00E2A8, 0);
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void EnMinifrog_EndChoir(EnMinifrog* this, GlobalContext* globalCtx) {
    EnMinifrog_TurnToPlayer(this);
    EnMinifrog_Jump(this);
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        Message_StartTextbox(globalCtx, 0xD7E, &this->actor); // "Let us do it again sometime."
        this->actionFunc = EnMinifrog_YellowFrogDialog;
    } else {
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, EXCH_ITEM_MINUS1);
    }
}

void EnMinifrog_GetFrogHP(EnMinifrog* this, GlobalContext* globalCtx) {
    EnMinifrog_TurnToPlayer(this);
    EnMinifrog_Jump(this);
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->actionFunc = EnMinifrog_EndChoir;
        this->actor.flags |= ACTOR_FLAG_10000;
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, EXCH_ITEM_NONE);
    } else {
        Actor_PickUp(&this->actor, globalCtx, GI_HEART_PIECE, 10000.0f, 50.0f);
    }
}

void EnMinifrog_YellowFrogDialog(EnMinifrog* this, GlobalContext* globalCtx) {
    EnMinifrog_TurnToPlayer(this);
    EnMinifrog_Jump(this);
    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 4:
            if (Message_ShouldAdvance(globalCtx)) {
                switch (globalCtx->msgCtx.choiceIndex) {
                    case 0: // Yes
                        func_8019F208();
                        this->actionFunc = EnMinifrog_BeginChoirCutscene;
                        globalCtx->msgCtx.unk11F10 = 0;
                        break;
                    case 1: // No
                        func_8019F230();
                        func_80151938(globalCtx, 0xD7E); // "Let us do it again sometime."
                        break;
                }
            }
            break;
        case 5:
            if (Message_ShouldAdvance(globalCtx)) {
                EnMinifrog_SetJumpState(this);
                switch (globalCtx->msgCtx.currentTextId) {
                    case 0xD76: // "I have been waiting for you, Don Gero. Forgive me if I'm mistaken, but it looks like
                                // you've lost a little weight..."
                        func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                        this->actor.flags &= ~ACTOR_FLAG_10000;
                        gSaveContext.save.weekEventReg[34] |= 1; // Spoken to MINIFROG_YELLOW
                        break;
                    case 0xD78: // "Unfortunately, it seems not all of our members have gathered."
                    case 0xD79: // "Perhaps it is because winter was too long? They must not have realized that spring
                                // has come to the mountains..."
                    case 0xD7A: // "And when the great Don Gero has come for us, too...What a pity."
                    case 0xD7F: // "Well, if it isn't the great Don Gero."
                        func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                        break;
                    case 0xD77: // "Let us begin our chorus"
                        this->actionFunc = EnMinifrog_BeginChoirCutscene;
                        globalCtx->msgCtx.unk11F10 = 0;
                        break;
                    case 0xD7C: // "The conducting was spectacular. And all of our members rose to the occasion!"
                        if (gSaveContext.save.weekEventReg[35] & 0x80) { // Obtained Heart Piece
                            func_80151938(globalCtx, 0xD7E);
                        } else {
                            func_80151938(globalCtx, 0xD7D); // Get Heart Piece
                            gSaveContext.save.weekEventReg[35] |= 0x80;
                        }
                        break;
                    case 0xD7D: // "This is how deeply we were moved by your spectacular conducting..."
                        func_801477B4(globalCtx);
                        this->actionFunc = EnMinifrog_GetFrogHP;
                        EnMinifrog_GetFrogHP(this, globalCtx);
                        break;
                    case 0xD7B: // "Where in the world could the other members be, and what could they be doing?"
                    case 0xD7E: // "Let us do it again sometime."
                    default:
                        func_801477B4(globalCtx);
                        this->actionFunc = EnMinifrog_SetupYellowFrogDialog;
                        this->actor.flags &= ~ACTOR_FLAG_10000;
                        break;
                }
            }
    }
}

void EnMinifrog_SetupYellowFrogDialog(EnMinifrog* this, GlobalContext* globalCtx) {
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x180);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    EnMinifrog_TurnToPlayer(this);
    EnMinifrog_Jump(this);
    EnMinifrog_JumpTimer(this);
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = EnMinifrog_YellowFrogDialog;
        if (!(gSaveContext.save.weekEventReg[34] & 1)) { // Not spoken with MINIFROG_YELLOW
            Message_StartTextbox(globalCtx, 0xD76,
                                 &this->actor); // "I have been waiting for you, Don Gero. Forgive me if I'm mistaken,
                                                // but it looks like you've lost a little weight..."
        } else {
            Message_StartTextbox(globalCtx, 0xD7F, &this->actor); // "Well, if it isn't the great Don Gero."
        }
    } else if ((this->actor.xzDistToPlayer < 150.0f) &&
               (Player_IsFacingActor(&this->actor, 0x3000, globalCtx) ||
                CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_10000)) &&
               Player_GetMask(globalCtx) == PLAYER_MASK_DON_GERO) {
        func_800B8614(&this->actor, globalCtx, 160.0f);
    }
}

void EnMinifrog_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnMinifrog* this = THIS;
    s32 pad;

    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 25.0f, 12.0f, 0.0f, 0x1D);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    this->actor.focus.rot.y = this->actor.shape.rot.y;
}

void EnMinifrog_UpdateMissingFrog(Actor* thisx, GlobalContext* globalCtx) {
    EnMinifrog* this = THIS;
    EnMinifrog* missingFrog;

    missingFrog = this->frog;
    if ((missingFrog != NULL) && (missingFrog->actor.home.rot.z == (this->actor.params & 0xF))) {
        missingFrog->frog = this;
    }
}

s32 EnMinifrog_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                Actor* thisx) {
    if (limbIndex == 1) {
        pos->z -= 500.0f;
    }

    if ((limbIndex == 7) || (limbIndex == 8)) {
        *dList = NULL;
    }

    return false;
}

void EnMinifrog_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnMinifrog* this = THIS;

    if ((limbIndex == 7) || (limbIndex == 8)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, *dList);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }

    if (limbIndex == 4) {
        Matrix_GetStateTranslation(&this->actor.focus.pos);
    }
}

static Color_RGBA8 sEnMinifrogColor[] = {
    { 200, 170, 0, 255 }, { 0, 170, 200, 255 }, { 210, 120, 100, 255 }, { 120, 130, 230, 255 }, { 190, 190, 190, 255 },
};

void EnMinifrog_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnMinifrog* this = THIS;
    Color_RGBA8* envColor;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    envColor = &sEnMinifrogColor[this->frogIndex];
    gSPSegment(POLY_OPA_DISP++, 0x08, D_808A4D74[0]);
    gSPSegment(POLY_OPA_DISP++, 0x09, D_808A4D74[0]);
    gDPSetEnvColor(POLY_OPA_DISP++, envColor->r, envColor->g, envColor->b, envColor->a);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnMinifrog_OverrideLimbDraw, EnMinifrog_PostLimbDraw, &this->actor);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
