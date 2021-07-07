/*
 * File: z_en_ma_yto.c
 * Overlay: ovl_En_Ma_Yto
 * Description: Romani. As oposed as EnMa4, this actor is used in conjunction of another actor, like EnMaYto.
 */

#include "z_en_ma_yts.h"

#define FLAGS 0x02100009

#define THIS ((EnMaYts*)thisx)

void EnMaYts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMaYts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMaYts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMaYts_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnMaYts_SetupDoNothing(EnMaYts* this);
void EnMaYts_DoNothing(EnMaYts* this, GlobalContext* globalCtx);
void EnMaYts_SetupStartDialogue(EnMaYts* this);
void EnMaYts_StartDialogue(EnMaYts* this, GlobalContext* globalCtx);
void EnMaYts_SetupDialogueHandler(EnMaYts* this);
void EnMaYts_DialogueHandler(EnMaYts* this, GlobalContext* globalCtx);
void EnMaYts_SetupEndCreditsHandler(EnMaYts* this);
void EnMaYts_EndCreditsHandler(EnMaYts* this, GlobalContext* globalCtx);
void EnMaYts_ChooseNextDialogue(EnMaYts* this, GlobalContext* globalCtx);

void EnMaYts_SetFaceExpression(EnMaYts* this, s16 overrideEyeTexIndex, s16 mouthTexIndex);

void EnMaYts_DrawSleeping(Actor* thisx, GlobalContext* globalCtx);

extern AnimationHeader D_06009E58;
extern AnimationHeader D_06018948;
extern AnimationHeader D_0601B76C;
extern AnimationHeader D_06007328;
extern AnimationHeader D_06014088;
extern AnimationHeader D_06002A8C;
extern AnimationHeader D_06015B7C;
extern AnimationHeader D_06007D98;
extern AnimationHeader D_0600852C;
extern AnimationHeader D_06008F6C;
extern AnimationHeader D_060180DC;

extern u64 D_060127C8[];
extern u64 D_06012BC8[];
extern u64 D_06012FC8[];
extern u64 D_060133C8[];

extern u64 D_0600FFC8[];
extern u64 D_060107C8[];
extern u64 D_06010FC8[];
extern u64 D_060117C8[];
extern u64 D_06011FC8[];

extern FlexSkeletonHeader D_06013928;

extern AnimationHeader D_06009E58;
extern AnimationHeader D_06007D98;

// Bow
extern Gfx D_060003B0[];

// Sleeping
extern Gfx D_060043A0[];

const ActorInit En_Ma_Yts_InitVars = {
    ACTOR_EN_MA_YTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MA1,
    sizeof(EnMaYts),
    (ActorFunc)EnMaYts_Init,
    (ActorFunc)EnMaYts_Destroy,
    (ActorFunc)EnMaYts_Update,
    (ActorFunc)EnMaYts_Draw,
};

void EnMaYts_UpdateEyes(EnMaYts* this) {
    if (this->overrideEyeTexIndex != 0) {
        this->eyeTexIndex = this->overrideEyeTexIndex;
    } else if (DECR(this->blinkTimer) == 0) {
        this->eyeTexIndex++;
        if (this->eyeTexIndex >= 3) {
            this->blinkTimer = Rand_S16Offset(30, 30);
            this->eyeTexIndex = 0;
        }
    }
}

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 18, 46, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit2 = {
    0, 0, 0, 0, MASS_IMMOVABLE,
};

static struct_80B8E1A8 D_80B8E1A8[] = {
    { &D_06009E58, 1.0f, 0, 0.0f },  { &D_06009E58, 1.0f, 0, -6.0f }, { &D_06018948, 1.0f, 2, 0.0f },
    { &D_06018948, 1.0f, 2, -6.0f }, { &D_0601B76C, 1.0f, 0, 0.0f },  { &D_0601B76C, 1.0f, 0, -6.0f },
    { &D_06007328, 1.0f, 0, 0.0f },  { &D_06007328, 1.0f, 0, -6.0f }, { &D_06014088, 1.0f, 0, 0.0f },
    { &D_06014088, 1.0f, 0, -6.0f }, { &D_06002A8C, 1.0f, 0, 0.0f },  { &D_06002A8C, 1.0f, 0, -6.0f },
    { &D_06015B7C, 1.0f, 0, 0.0f },  { &D_06015B7C, 1.0f, 0, -6.0f }, { &D_06007D98, 1.0f, 0, 0.0f },
    { &D_06007D98, 1.0f, 0, -6.0f }, { &D_0600852C, 1.0f, 0, 0.0f },  { &D_0600852C, 1.0f, 0, -6.0f },
    { &D_06008F6C, 1.0f, 0, 0.0f },  { &D_06008F6C, 1.0f, 0, -6.0f }, { &D_060180DC, 1.0f, 2, 0.0f },
    { &D_060180DC, 1.0f, 2, -6.0f },
};

static void* sMouthTextures[] = {
    D_060127C8,
    D_06012BC8,
    D_06012FC8,
    D_060133C8,
};

static void* sEyeTextures[] = {
    D_0600FFC8, D_060107C8, D_06010FC8, D_060117C8, D_06011FC8,
};

static u16 D_80B8E32C = 99;

void EnMaYts_ChangeAnim(EnMaYts* this, s32 index) {
    SkelAnime_ChangeAnim(&this->skelAnime, D_80B8E1A8[index].animationSeg, 1.0f, 0.0f,
                         SkelAnime_GetFrameCount(&D_80B8E1A8[index].animationSeg->common), D_80B8E1A8[index].mode,
                         D_80B8E1A8[index].transitionRate);
}

void func_80B8D12C(EnMaYts* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s16 flag = this->unk_32C == 2 ? true : false;

    if ((this->unk_32C == 0) || (this->actor.parent == NULL)) {
        this->unk_1D8.unk_18 = player->actor.world.pos;
        this->unk_1D8.unk_18.y -= -10.0f;
    } else {
        Math_Vec3f_StepTo(&this->unk_1D8.unk_18, &this->actor.parent->world.pos, 8.0f);
        this->unk_1D8.unk_18.y -= -10.0f;
    }

    func_800BD888(&this->actor, &this->unk_1D8, 0, flag);
}

void EnMaYts_InitAnimation(EnMaYts* this, GlobalContext* globalCtx) {
    switch (this->type) {
        case EN_NA_YTS_TYPE_BARN:
            this->actor.targetMode = 0;
            EnMaYts_ChangeAnim(this, 0);
            break;

        case EN_NA_YTS_TYPE_SITTING:
            this->actor.targetMode = 6;
            // Day 1 or "Winning" the alien invasion
            if (CURRENT_DAY == 1 || (gSaveContext.weekEventReg[0x16] & 1)) {
                EnMaYts_ChangeAnim(this, 14);
            } else {
                EnMaYts_ChangeAnim(this, 18);
            }
            break;

        case EN_NA_YTS_TYPE_SLEEPING:
            this->actor.targetMode = 0;
            this->actor.draw = EnMaYts_DrawSleeping;
            EnMaYts_ChangeAnim(this, 0);
            break;

        case EN_NA_YTS_TYPE_ENDCREDITS:
            this->actor.targetMode = 0;
            EnMaYts_ChangeAnim(this, 0);
            break;

        default:
            EnMaYts_ChangeAnim(this, 0);
            break;
    }
}

s32 EnMaYts_CheckValidSpawn(EnMaYts* this, GlobalContext* globalCtx) {
    switch (this->type) {
        case EN_NA_YTS_TYPE_SITTING:
            switch (CURRENT_DAY) {
                case 1:
                    break;

                case 2:
                    // Failing the alien invasion
                    if (!(gSaveContext.weekEventReg[0x16] & 1)) {
                        return false;
                    }
                    break;

                case 3:
                    // "Winning" the alien invasion
                    if (gSaveContext.weekEventReg[0x16] & 1) {
                        return false;
                    }
                    break;
            }
            break;

        case EN_NA_YTS_TYPE_BARN:
            // Failing the alien invasion
            if (!(gSaveContext.weekEventReg[0x16] & 1)) {
                return false;
            } else if ((gSaveContext.time >= 0xD555) && (CURRENT_DAY == 3)) {
                return false;
            }
            break;

        case EN_NA_YTS_TYPE_SLEEPING:
            // "Winning" the alien invasion
            if (gSaveContext.weekEventReg[0x16] & 1) {
                return false;
            }
            break;

        case EN_NA_YTS_TYPE_ENDCREDITS:
            break;
    }

    return true;
}

void EnMaYts_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnMaYts* this = THIS;
    s32 pad;

    this->type = EN_MA_YTS_PARSE_TYPE(thisx);
    if (!EnMaYts_CheckValidSpawn(this, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
    }
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 18.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06013928, NULL, this->limbDrawTbl, this->transitionDrawTbl,
                     OBJECT_MA1_LIMB_TABLE_COUNT);
    EnMaYts_InitAnimation(this, globalCtx);

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit2);

    if (this->type == EN_NA_YTS_TYPE_SLEEPING) {
        this->collider.dim.radius = 40;
    }

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 0x4);
    Actor_SetScale(&this->actor, 0.01f);

    this->unk_1D8.unk_00 = 0;
    this->unk_200 = 0;
    this->blinkTimer = 0;

    if (this->type == EN_NA_YTS_TYPE_ENDCREDITS) {
        this->hasBow = true;
    } else {
        this->hasBow = false;
    }

    if (CURRENT_DAY == 1 || (gSaveContext.weekEventReg[0x16] & 1)) {
        this->overrideEyeTexIndex = 0;
        this->eyeTexIndex = 0;
        this->mouthTexIndex = 0;
        this->unk_32C = 0;
    } else {
        this->overrideEyeTexIndex = 1;
        this->eyeTexIndex = 1;
        this->mouthTexIndex = 2;
        this->unk_32C = 2;
    }

    if (this->type == EN_NA_YTS_TYPE_ENDCREDITS) {
        this->overrideEyeTexIndex = 0;
        this->eyeTexIndex = 0;
        this->mouthTexIndex = 0;
        this->unk_32C = 2;
        EnMaYts_SetupEndCreditsHandler(this);
    } else if (CURRENT_DAY == 2 && gSaveContext.isNight == 1 && (gSaveContext.weekEventReg[0x16] & 1)) {
        EnMaYts_SetupStartDialogue(this);
    } else {
        EnMaYts_SetupDoNothing(this);
    }
}

void EnMaYts_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnMaYts* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnMaYts_SetupDoNothing(EnMaYts* this) {
    this->actionFunc = EnMaYts_DoNothing;
}

void EnMaYts_DoNothing(EnMaYts* this, GlobalContext* globalCtx) {
}

void EnMaYts_SetupStartDialogue(EnMaYts* this) {
    EnMaYts_SetFaceExpression(this, 0, 0);
    this->actionFunc = EnMaYts_StartDialogue;
}

void EnMaYts_StartDialogue(EnMaYts* this, GlobalContext* globalCtx) {
    s16 sp26 = this->actor.shape.rot.y - this->actor.yawTowardsPlayer;

    if (func_800B84D0(&this->actor, globalCtx)) { // if (Actor_IsTalking)
        if (!(gSaveContext.playerForm == 4)) {    // PLAYER_FORM != HUMAN_FORM
            if (!(gSaveContext.weekEventReg[0x41] & 0x80)) {
                // Saying to non-human Link: "Cremia went to town."
                gSaveContext.weekEventReg[0x41] |= 0x80;
                EnMaYts_SetFaceExpression(this, 0, 0);
                func_801518B0(globalCtx, 0x335F, &this->actor);
                this->textId = 0x335F;
            } else {
                // Saying to non-human Link: "Pretend you did not hear that."
                EnMaYts_SetFaceExpression(this, 4, 3);
                func_801518B0(globalCtx, 0x3362, &this->actor);
                this->textId = 0x3362;
                func_80151BB4(globalCtx, 5);
            }
        } else if (Player_GetMask(globalCtx) != PLAYER_MASK_NONE) {
            if (!(gSaveContext.weekEventReg[0x41] & 0x40)) {
                gSaveContext.weekEventReg[0x41] |= 0x40;
                EnMaYts_SetFaceExpression(this, 0, 0);
                func_801518B0(globalCtx, 0x3363, &this->actor);
                this->textId = 0x3363;
            } else {
                EnMaYts_SetFaceExpression(this, 4, 2);
                func_801518B0(globalCtx, 0x3366, &this->actor);
                this->textId = 0x3366;
                func_80151BB4(globalCtx, 5);
            }
        } else if (!(gSaveContext.weekEventReg[0x15] & 0x20)) {
            EnMaYts_SetFaceExpression(this, 0, 0);
            func_801518B0(globalCtx, 0x3367, &this->actor);
            this->textId = 0x3367;
        } else {
            if (!(gSaveContext.weekEventReg[0x41] & 0x20)) {
                // Saying to Grasshopper: "Cremia went to town."
                gSaveContext.weekEventReg[0x41] |= 0x20;
                EnMaYts_SetFaceExpression(this, 4, 2);
                func_801518B0(globalCtx, 0x3369, &this->actor);
                this->textId = 0x3369;
            } else {
                // Saying to Grasshopper: "You're our bodyguard."
                EnMaYts_SetFaceExpression(this, 0, 0);
                func_801518B0(globalCtx, 0x336C, &this->actor);
                this->textId = 0x336C;
                func_80151BB4(globalCtx, 5);
            }
        }
        EnMaYts_SetupDialogueHandler(this);
    } else if (ABS_ALT(sp26) < 0x4000) {
        func_800B8614(&this->actor, globalCtx, 120.0f);
    }
}

void EnMaYts_SetupDialogueHandler(EnMaYts* this) {
    this->actionFunc = EnMaYts_DialogueHandler;
}

void EnMaYts_DialogueHandler(EnMaYts* this, GlobalContext* globalCtx) {
    switch (func_80152498(&globalCtx->msgCtx)) {
        case 5: // End message block
            EnMaYts_ChooseNextDialogue(this, globalCtx);
            break;

        case 6: // End conversation
            if (func_80147624(globalCtx) != 0) {
                EnMaYts_SetupStartDialogue(this);
            }
            break;

        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            break;
    }
}

void EnMaYts_SetupEndCreditsHandler(EnMaYts* this) {
    this->actor.flags |= 0x10;
    EnMaYts_SetFaceExpression(this, 0, 0);
    this->actionFunc = EnMaYts_EndCreditsHandler;
}

void EnMaYts_EndCreditsHandler(EnMaYts* this, GlobalContext* globalCtx) {
    u32 actionIndex;

    if (func_800EE29C(globalCtx, 0x78) != 0) {
        actionIndex = func_800EE200(globalCtx, 0x78);
        if (globalCtx->csCtx.frames == globalCtx->csCtx.npcActions[actionIndex]->startFrame) {
            if (globalCtx->csCtx.npcActions[actionIndex]->unk0 != D_80B8E32C) {
                D_80B8E32C = globalCtx->csCtx.npcActions[actionIndex]->unk0;
                this->endCreditsFlag = 0;
                switch (globalCtx->csCtx.npcActions[actionIndex]->unk0) {
                    case 1:
                        this->hasBow = true;
                        EnMaYts_ChangeAnim(this, 0);
                        break;

                    case 2:
                        this->hasBow = false;
                        EnMaYts_ChangeAnim(this, 2);
                        break;

                    case 3:
                        this->hasBow = true;
                        EnMaYts_ChangeAnim(this, 12);
                        break;

                    case 4:
                        this->hasBow = true;
                        EnMaYts_ChangeAnim(this, 20);
                        break;
                }
            }
        }

        func_800EDF24(&this->actor, globalCtx, actionIndex);
        if ((D_80B8E32C == 2) && (this->endCreditsFlag == 0) &&
            (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount) != 0)) {
            this->endCreditsFlag++;
            EnMaYts_ChangeAnim(this, 5);
        }
    } else {
        D_80B8E32C = 99;
        this->hasBow = true;
    }
}

// Select the following dialogue based on the current one, and an appropiate face expression
void EnMaYts_ChooseNextDialogue(EnMaYts* this, GlobalContext* globalCtx) {
    if (func_80147624(globalCtx) != 0) {
        switch (this->textId) {
            case 0x335F:
                EnMaYts_SetFaceExpression(this, 0, 2);
                func_801518B0(globalCtx, 0x3360, &this->actor);
                this->textId = 0x3360;
                break;

            case 0x3360:
                EnMaYts_SetFaceExpression(this, 4, 3);
                func_801518B0(globalCtx, 0x3361, &this->actor);
                this->textId = 0x3361;
                func_80151BB4(globalCtx, 5);
                break;

            case 0x3363:
                EnMaYts_SetFaceExpression(this, 1, 1);
                func_801518B0(globalCtx, 0x3364, &this->actor);
                this->textId = 0x3364;
                break;

            case 0x3364:
                EnMaYts_SetFaceExpression(this, 4, 2);
                func_801518B0(globalCtx, 0x3365, &this->actor);
                this->textId = 0x3365;
                func_80151BB4(globalCtx, 5);
                break;

            case 0x3367:
                EnMaYts_SetFaceExpression(this, 4, 3);
                func_801518B0(globalCtx, 0x3368, &this->actor);
                this->textId = 0x3368;
                func_80151BB4(globalCtx, 5);
                break;

            case 0x3369:
                EnMaYts_SetFaceExpression(this, 0, 0);
                func_801518B0(globalCtx, 0x336A, &this->actor);
                this->textId = 0x336A;
                break;

            case 0x336A:
                EnMaYts_SetFaceExpression(this, 3, 3);
                func_801518B0(globalCtx, 0x336B, &this->actor);
                this->textId = 0x336B;
                func_80151BB4(globalCtx, 5);
                break;

            default:
                break;
        }
    }
}

void EnMaYts_SetFaceExpression(EnMaYts* this, s16 overrideEyeTexIndex, s16 mouthTexIndex) {
    this->overrideEyeTexIndex = overrideEyeTexIndex;
    this->mouthTexIndex = mouthTexIndex;
    if (this->overrideEyeTexIndex == 0) {
        this->eyeTexIndex = 0;
    }
}

void EnMaYts_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnMaYts* this = THIS;
    ColliderCylinder* collider;

    this->actionFunc(this, globalCtx);
    collider = &this->collider;
    Collider_UpdateCylinder(&this->actor, collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &collider->base);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    EnMaYts_UpdateEyes(this);
    func_80B8D12C(this, globalCtx);
}

s32 EnMaYts_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                             Actor* thisx) {
    EnMaYts* this = THIS;
    Vec3s sp4;

    if (limbIndex == OBJECT_MA1_LIMB_HAIR_TOP) {
        sp4 = this->unk_1D8.unk_08;
        rot->x += sp4.y;
        if ((this->skelAnime.animCurrentSeg == &D_06009E58) || (this->skelAnime.animCurrentSeg == &D_06007D98)) {
            rot->z += sp4.x;
        }
    } else if (limbIndex == OBJECT_MA1_LIMB_HEAD) {
        sp4 = this->unk_1D8.unk_0E;
        rot->x += sp4.y;
        rot->z += sp4.x;
    }

    return 0;
}

void EnMaYts_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnMaYts* this = THIS;

    if (limbIndex == OBJECT_MA1_LIMB_HAIR_TOP) {
        SysMatrix_GetStateTranslation(&this->actor.focus.pos);
    } else if (limbIndex == OBJECT_MA1_LIMB_ARM_RIGHT) {
        if (this->hasBow == true) {
            OPEN_DISPS(globalCtx->state.gfxCtx);
            gSPDisplayList(POLY_OPA_DISP++, D_060003B0);
            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}

void EnMaYts_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnMaYts* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(sMouthTextures[this->mouthTexIndex]));
    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(sEyeTextures[this->eyeTexIndex]));

    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     EnMaYts_OverrideLimbDraw, EnMaYts_PostLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

// Alternative draw function
void EnMaYts_DrawSleeping(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_060043A0);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
