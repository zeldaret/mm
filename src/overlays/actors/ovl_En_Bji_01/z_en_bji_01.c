/*
 * File: z_en_bji_01.c
 * Overlay: ovl_En_Bji_01
 * Description: Professor Shikashi (Astral Observatory Proprietor)
 */

#include "z_en_bji_01.h"
#include "objects/object_bji/object_bji.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnBji01*)thisx)

void EnBji01_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBji01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBji01_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBji01_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809CCE98(EnBji01* this, GlobalContext* globalCtx);
void func_809CCEE8(EnBji01* this, GlobalContext* globalCtx);
void func_809CD028(EnBji01* this, GlobalContext* globalCtx);
void EnBji01_DialogueHandler(EnBji01* this, GlobalContext* globalCtx);
void func_809CCDE0(EnBji01* this, GlobalContext* globalCtx);
void func_809CD634(EnBji01* this, GlobalContext* globalCtx);
void EnBji01_DoNothing(EnBji01* this, GlobalContext* globalCtx);
void func_809CD6C0(EnBji01* this, GlobalContext* globalCtx);
void func_809CD70C(EnBji01* this, GlobalContext* globalCtx);
void func_809CD77C(EnBji01* this, GlobalContext* globalCtx);

s32 EnBji01_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                             Actor* thisx);
void EnBji01_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);

const ActorInit En_Bji_01_InitVars = {
    ACTOR_EN_BJI_01,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BJI,
    sizeof(EnBji01),
    (ActorFunc)EnBji01_Init,
    (ActorFunc)EnBji01_Destroy,
    (ActorFunc)EnBji01_Update,
    (ActorFunc)EnBji01_Draw,
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
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 18, 64, 0, { 0, 0, 0 } },
};

/* Animations struct */
static AnimationSpeedInfo D_809CDC7C[] = {
    { &object_bji_Anim_000FDC, 1.0f, ANIMMODE_LOOP, 0.0f },  /* Looking through telescope */
    { &object_bji_Anim_005B58, 1.0f, ANIMMODE_LOOP, 10.0f }, /* Breathing? Unused? */
    { &object_bji_Anim_000AB0, 1.0f, ANIMMODE_LOOP, 0.0f },  /* Talking */
    { &object_bji_Anim_00066C, 1.0f, ANIMMODE_ONCE, -5.0f }, /* Scratching chin? */
};

void func_809CCDE0(EnBji01* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp58;
    s32 pad[2];

    Math_Vec3f_Copy(&sp58, &player->actor.world.pos);
    sp58.y = player->bodyPartsPos[7].y + 3.0f;
    func_8013E950(&this->actor.world.pos, &this->actor.focus.pos, this->actor.shape.rot.y, &player->actor.world.pos,
                  &sp58, &this->headZRotAdj, &this->headXRotAdj, &this->torsoZRotAdj, &this->torsoXRotAdj, 0x1554,
                  0x1FFE, 0xE38, 0x1C70);
}

void func_809CCE98(EnBji01* this, GlobalContext* globalCtx) {
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_809CDC7C, 0, &this->animationIndex);
    this->actor.textId = 0;
    this->actionFunc = func_809CCEE8;
}

void func_809CCEE8(EnBji01* this, GlobalContext* globalCtx) {
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 0x444);
    if (this->actor.params == ENBJI01_PARAMS_DEFAULT) {
        if ((this->actor.xzDistToPlayer <= 60.0f) && (this->actor.playerHeightRel <= 10.0f)) {
            this->actor.flags |= ACTOR_FLAG_10000;
        } else {
            this->actor.flags &= ~ACTOR_FLAG_10000;
        }
    }
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        globalCtx->msgCtx.msgMode = 0;
        globalCtx->msgCtx.unk11F10 = 0;
        func_809CD028(this, globalCtx);
    } else {
        if (this->moonsTear != NULL) {
            if (this->moonsTear->actor.colChkInfo.health == 1) {
                func_809CD6C0(this, globalCtx);
                return;
            }
        } else {
            this->moonsTear = (ObjMoonStone*)SubS_FindActor(globalCtx, NULL, ACTORCAT_PROP, ACTOR_OBJ_MOON_STONE);
        }
        func_800B8500(&this->actor, globalCtx, 60.0f, 10.0f, EXCH_ITEM_NONE);
    }
}

void func_809CD028(EnBji01* this, GlobalContext* globalCtx) {
    s32 tempDay;
    f32 tempTimeBeforeMoonCrash;

    switch (this->actor.params) {
        case ENBJI01_PARAMS_DEFAULT:
        case ENBJI01_PARAMS_FINISHED_CONVERSATION:
            switch (gSaveContext.save.playerForm) {
                case PLAYER_FORM_DEKU:
                    if (gSaveContext.save.weekEventReg[17] & 0x10) {
                        if (gSaveContext.save.weekEventReg[74] & 0x80) {
                            this->textId = 0x5F4;
                        } else {
                            this->textId = 0x5E2;
                        }
                    } else {
                        this->textId = 0x5EC;
                        gSaveContext.save.weekEventReg[17] |= 0x10;
                    }
                    break;
                case PLAYER_FORM_HUMAN:
                    if (Player_GetMask(globalCtx) == PLAYER_MASK_KAFEIS_MASK) {
                        this->textId = 0x236A;
                    } else if (gSaveContext.save.weekEventReg[74] & 0x10) {
                        this->textId = 0x5F6;
                    } else {
                        this->textId = 0x5F5;
                        gSaveContext.save.weekEventReg[74] |= 0x10;
                    }
                    break;
                case PLAYER_FORM_GORON:
                case PLAYER_FORM_ZORA:
                    if (gSaveContext.save.weekEventReg[75] & 8) {
                        this->textId = 0x5E4;
                    } else {
                        this->textId = 0x5DC;
                        gSaveContext.save.weekEventReg[75] |= 8;
                    }
                    break;
            }
            break;
        case ENBJI01_PARAMS_LOOKED_THROUGH_TELESCOPE:
            switch (gSaveContext.save.playerForm) {
                case PLAYER_FORM_DEKU:
                    if (gSaveContext.save.weekEventReg[74] & 0x80) {
                        this->textId = 0x5F2;
                    } else {
                        this->textId = 0x5F1;
                    }
                    func_800B8500(&this->actor, globalCtx, this->actor.xzDistToPlayer, this->actor.playerHeightRel,
                                  EXCH_ITEM_NONE);
                    break;
                case PLAYER_FORM_HUMAN:
                    this->textId = 0x5F7;
                    break;
                case PLAYER_FORM_GORON:
                case PLAYER_FORM_ZORA:
                    switch (CURRENT_DAY) {
                        case 1:
                            this->textId = 0x5E9;
                            break;
                        case 2:
                            this->textId = 0x5EA;
                            break;
                        case 3:
                            tempDay = gSaveContext.save.day;
                            tempTimeBeforeMoonCrash =
                                ((-(tempDay % 5 << 0x10) - ((u16)(gSaveContext.save.time - 0x4000))) + 0x40000);
                            if (tempTimeBeforeMoonCrash < CLOCK_TIME_F(1, 0)) { /* 1 hr */
                                this->textId = 0x5E8;
                            } else {
                                this->textId = 0x5EB;
                            }
                            break;
                    }
            }
            break;
    }
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_809CDC7C, 2, &this->animationIndex);
    this->actionFunc = EnBji01_DialogueHandler;
}

void EnBji01_DialogueHandler(EnBji01* this, GlobalContext* globalCtx) {
    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 0:
            Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x444);
            func_809CCDE0(this, globalCtx);
            if (this->actor.shape.rot.y == this->actor.yawTowardsPlayer) {
                Message_StartTextbox(globalCtx, this->textId, &this->actor);
            }
            break;
        case 4:
            if (Message_ShouldAdvance(globalCtx) != 0) {
                this->actor.flags &= ~ACTOR_FLAG_10000;
                this->actor.params = ENBJI01_PARAMS_FINISHED_CONVERSATION;
                switch (globalCtx->msgCtx.choiceIndex) {
                    case 0:
                        func_8019F208();
                        func_801477B4(globalCtx);
                        func_809CD634(this, globalCtx);
                        break;
                    case 1:
                        func_8019F230();
                        switch (gSaveContext.save.playerForm) {
                            case PLAYER_FORM_DEKU:
                                func_80151938(globalCtx, 0x5F0);
                                break;
                            case PLAYER_FORM_HUMAN:
                                func_80151938(globalCtx, 0x5F8);
                                break;
                            case PLAYER_FORM_GORON:
                            case PLAYER_FORM_ZORA:
                                func_80151938(globalCtx, 0x5E1);
                                break;
                        }
                        break;
                }
            }
            break;
        case 5:
            if (Message_ShouldAdvance(globalCtx) != 0) {
                this->actor.flags &= ~ACTOR_FLAG_10000;
                switch (globalCtx->msgCtx.currentTextId) {
                    case 0x5DE:
                        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_809CDC7C, 3, &this->animationIndex);
                        func_80151938(globalCtx, 0x5DF);
                        break;
                    case 0x5E4:
                        func_80151938(globalCtx, 0x5E7);
                        break;
                    case 0x5E5:
                        func_80151938(globalCtx, 0x5E0);
                        break;
                    case 0x5E7:
                        func_80151938(globalCtx, 0x5E5);
                        break;
                    case 0x5DC:
                    case 0x5DD:
                    case 0x5DF:
                    case 0x5EC:
                    case 0x5ED:
                    case 0x5EE:
                    case 0x5F2:
                    case 0x5F5:
                        func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                        break;
                    case 0x5F0:
                    case 0x5F6:
                        func_80151938(globalCtx, 0x5EF);
                        break;
                    case 0x5E1:
                    case 0x5E8:
                    case 0x5E9:
                    case 0x5EA:
                    case 0x5EB:
                    case 0x5F1:
                    case 0x5F3:
                    case 0x5F4:
                    case 0x5F7:
                    case 0x5F8:
                        func_801477B4(globalCtx);
                        this->actor.flags &= ~ACTOR_FLAG_10000;
                        this->actor.params = ENBJI01_PARAMS_FINISHED_CONVERSATION;
                        func_809CCE98(this, globalCtx);
                        break;
                }
            }
            break;
        case 6:
            this->actor.params = ENBJI01_PARAMS_FINISHED_CONVERSATION;
            this->actor.flags &= ~ACTOR_FLAG_10000;
            func_809CCE98(this, globalCtx);
            break;
    }
    if ((this->animationIndex == 3) && (this->skelAnime.curFrame == this->skelAnime.endFrame)) {
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_809CDC7C, 2, &this->animationIndex);
    }
}

void func_809CD634(EnBji01* this, GlobalContext* globalCtx) {
    func_801A5BD0(0x6F);
    Audio_QueueSeqCmd(0xE0000101);
    globalCtx->nextEntranceIndex = 0x54A0; /* Termina Field from telescope */
    gSaveContext.respawn[RESTART_MODE_DOWN].entranceIndex = globalCtx->nextEntranceIndex;
    func_80169EFC(&globalCtx->state); /* Load new entrance? */
    gSaveContext.respawnFlag = -2;
    this->actionFunc = EnBji01_DoNothing;
}

void EnBji01_DoNothing(EnBji01* this, GlobalContext* globalCtx) {
}

void func_809CD6C0(EnBji01* this, GlobalContext* globalCtx) {
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, D_809CDC7C, 2, &this->animationIndex);
    this->actionFunc = func_809CD70C;
}

void func_809CD70C(EnBji01* this, GlobalContext* globalCtx) {
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x444);
    func_809CCDE0(this, globalCtx);
    if (this->actor.shape.rot.y == this->actor.yawTowardsPlayer) {
        Actor_ChangeFocus(&this->moonsTear->actor, globalCtx, &this->actor); /* Z-Target the Moon's Tear? */
        this->actionFunc = func_809CD77C;
    }
}

void func_809CD77C(EnBji01* this, GlobalContext* globalCtx) {
    if (this->moonsTear->actor.colChkInfo.health == 0) {
        func_809CCE98(this, globalCtx);
    }
}

void EnBji01_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBji01* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_bji_Skel_00578C, &object_bji_Anim_000FDC, this->jointTable,
                       this->morphTable, BJI_LIMB_MAX);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.targetMode = 0;
    this->actor.child = NULL;
    this->animationIndex = -1;

    Actor_SetScale(&this->actor, 0.01f);
    SubS_FillCutscenesList(&this->actor, this->cutscenes, ARRAY_COUNT(this->cutscenes));
    this->moonsTear = (ObjMoonStone*)SubS_FindActor(globalCtx, NULL, ACTORCAT_PROP, ACTOR_OBJ_MOON_STONE);

    switch (gSaveContext.save.entranceIndex) {
        case 0x4C00: /* Observatory from ECT */
        case 0x4C10: /* Observatory from Termina Field door */
            this->actor.params = ENBJI01_PARAMS_DEFAULT;
            func_809CCE98(this, globalCtx);
            break;
        case 0x4C20: /* Observatory from Termina Field telescope */
            this->actor.flags |= ACTOR_FLAG_10000;
            func_801A5BD0(0);
            Audio_QueueSeqCmd(0xE0000100);
            this->actor.params = ENBJI01_PARAMS_LOOKED_THROUGH_TELESCOPE;
            func_809CCE98(this, globalCtx);
            break;
        default:
            Actor_MarkForDeath(&this->actor);
            break;
    }
}

void EnBji01_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBji01* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnBji01_Update(Actor* thisx, GlobalContext* globalCtx) {
    static s16 sBlinkSequence[] = { 0, 1, 2, 1, 0, 0 };
    EnBji01* this = THIS;
    s32 pad;

    this->actionFunc(this, globalCtx);
    Actor_UpdateBgCheckInfo(globalCtx, (Actor*)this, 0.0f, 0.0f, 0.0f, 4U);
    SkelAnime_Update(&this->skelAnime);

    if (this->blinkTimer-- <= 0) {
        if (--this->blinkSeqIndex < 0) {
            this->blinkSeqIndex = 4;
            this->blinkTimer = (Rand_ZeroOne() * 60.0f) + 20.0f;
        } else {
            this->eyeTexIndex = sBlinkSequence[this->blinkSeqIndex];
        }
    }

    Actor_SetFocus(&this->actor, 40.0f);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

s32 EnBji01_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                             Actor* thisx) {
    EnBji01* this = THIS;

    if ((limbIndex == BJI_LIMB_NONE) && ((globalCtx->gameplayFrames % 2) != 0)) {
        *dList = NULL;
    }
    if (limbIndex == BJI_LIMB_NONE) {
        rot->x = rot->x;
        rot->y = rot->y;
        rot->z = rot->z;
    }
    switch (limbIndex) {
        case BJI_LIMB_TORSO:
            rot->x += this->torsoXRotAdj;
            rot->z += this->torsoZRotAdj;
            break;
        case BJI_LIMB_HEAD:
            rot->x += this->headXRotAdj;
            rot->z += this->headZRotAdj;
            break;
    }
    return false;
}

void EnBji01_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_809CDCC8 = { 1088.0f, 1200.0f, 0.0f };
    EnBji01* this = THIS;
    Vec3f sp20;
    s32 temp_f4 = 0;

    if (limbIndex == BJI_LIMB_HEAD) {
        Math_Vec3f_Copy(&sp20, &D_809CDCC8);
        sp20.x += temp_f4 * 0.1f;
        sp20.y += temp_f4 * 0.1f;
        sp20.z += temp_f4 * 0.1f;
        Matrix_MultiplyVector3fByState(&sp20, &this->actor.focus.pos);
    }
}

void EnBji01_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static TexturePtr sEyeTextures[] = { object_bji_Tex_0049F0, object_bji_Tex_004E70, object_bji_Tex_005270 };
    EnBji01* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeTexIndex]));
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnBji01_OverrideLimbDraw, EnBji01_PostLimbDraw, &this->actor);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
