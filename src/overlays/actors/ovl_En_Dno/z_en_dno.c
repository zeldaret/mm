/*
 * File: z_en_dno.c
 * Overlay: ovl_En_Dno
 * Description: Deku Butler
 */

#include "z_en_dno.h"
#include "overlays/actors/ovl_Bg_Crace_Movebg/z_bg_crace_movebg.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_dno/object_dno.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnDno*)thisx)

void EnDno_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDno_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDno_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDno_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A71B04(EnDno* this, GlobalContext* globalCtx);
void EnDno_DoNothing(EnDno* this, GlobalContext* globalCtx);
void func_80A71B68(EnDno* this, GlobalContext* globalCtx);
void func_80A71C3C(EnDno* this, GlobalContext* globalCtx);
void func_80A71E54(EnDno* this, GlobalContext* globalCtx);
void func_80A71F18(EnDno* this, GlobalContext* globalCtx);
void func_80A72438(EnDno* this, GlobalContext* globalCtx);
void func_80A724B8(EnDno* this, GlobalContext* globalCtx);
void func_80A725E0(EnDno* this, GlobalContext* globalCtx);
void func_80A725F8(EnDno* this, GlobalContext* globalCtx);
void func_80A72AE4(EnDno* this, GlobalContext* globalCtx);
void func_80A72B3C(EnDno* this, GlobalContext* globalCtx);
void func_80A72B84(EnDno* this, GlobalContext* globalCtx);
void func_80A72BA4(EnDno* this, GlobalContext* globalCtx);
void func_80A72C04(EnDno* this, GlobalContext* globalCtx);
void func_80A72CF8(EnDno* this, GlobalContext* globalCtx);
void func_80A730A0(EnDno* this, GlobalContext* globalCtx);
void func_80A73244(EnDno* this, GlobalContext* globalCtx);
void func_80A732C8(EnDno* this, GlobalContext* globalCtx);
s32 EnDno_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void EnDno_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);

static AnimationSpeedInfo sAnimations[] = {
    { &object_dno_Anim_000470, 1.0f, ANIMMODE_ONCE, 0.0f }, { &object_dno_Anim_0008F0, 1.0f, ANIMMODE_ONCE, 0.0f },
    { &object_dno_Anim_000F6C, 1.0f, ANIMMODE_LOOP, 0.0f }, { &object_dno_Anim_001A50, 1.0f, ANIMMODE_ONCE, 0.0f },
    { &object_dno_Anim_002530, 1.0f, ANIMMODE_ONCE, 0.0f }, { &object_dno_Anim_003320, 1.0f, ANIMMODE_ONCE, 0.0f },
    { &object_dno_Anim_0036D0, 1.0f, ANIMMODE_LOOP, 0.0f }, { &object_dno_Anim_0041CC, 1.0f, ANIMMODE_ONCE, 0.0f },
    { &object_dno_Anim_004DD8, 1.0f, ANIMMODE_ONCE, 0.0f }, { &object_dno_Anim_005F98, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &object_dno_Anim_006488, 1.0f, ANIMMODE_ONCE, 0.0f }, { &object_dno_Anim_0073E4, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &object_dno_Anim_0077A8, 1.0f, ANIMMODE_LOOP, 0.0f }, { &object_dno_Anim_007CA4, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &object_dno_Anim_008324, 1.0f, ANIMMODE_LOOP, 0.0f }, { &object_dno_Anim_008AE4, 1.0f, ANIMMODE_ONCE, 0.0f },
    { &object_dno_Anim_009100, 1.0f, ANIMMODE_ONCE, 0.0f }, { &object_dno_Anim_0051E4, 1.0f, ANIMMODE_ONCE, 0.0f },
    { &object_dno_Anim_005E20, 1.0f, ANIMMODE_LOOP, 0.0f }, { &object_dno_Anim_006F84, 1.0f, ANIMMODE_LOOP, 0.0f },
};

const ActorInit En_Dno_InitVars = {
    ACTOR_EN_DNO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNO,
    sizeof(EnDno),
    (ActorFunc)EnDno_Init,
    (ActorFunc)EnDno_Destroy,
    (ActorFunc)EnDno_Update,
    (ActorFunc)EnDno_Draw,
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
    { 17, 58, 0, { 0, 0, 0 } },
};

static Vec3f D_80A73B2C = { 0.0f, 0.0f, 1.0f };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneDownward, 80, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_STOP),
};

void func_80A711D0(EnDno* this, GlobalContext* globalCtx, Vec3f* vec) {
    f32 rand = Rand_ZeroOne() * 0.5f;

    Lights_PointGlowSetInfo(&this->lightInfo, vec->x, vec->y, vec->z, (127.5f * rand) + 127.5f,
                            (100.0f * rand) + 100.0f, (40.0f * rand) + 40.0f, 320);
}

s32 func_80A71424(s16* arg0, s16 arg1, s16 yawToPlayer, s16 rotY, s16 arg4, s16 arg5) {
    s16 temp_v0 = yawToPlayer - rotY;
    s32 ret;

    if (arg4 >= ABS(temp_v0)) {
        ret = Math_ScaledStepToS(arg0, arg1 + temp_v0, arg5);
    } else {
        ret = Math_ScaledStepToS(arg0, arg1, arg5);
    }

    return ret;
}

void func_80A714B4(EnDno* this, GlobalContext* globalCtx) {
    Actor* actor = NULL;

    do {
        actor = SubS_FindActor(globalCtx, actor, ACTORCAT_BG, ACTOR_BG_CRACE_MOVEBG);
        if (actor != NULL) {
            if (ENDNO_GET_F(actor) == ENDNO_GET_F_1) {
                Flags_SetSwitch(globalCtx, ENDNO_GET_7F0(actor));
            }
            actor = actor->next;
        }
    } while (actor != NULL);
}

// Unused?
void func_80A7153C(EnDno* this, Vec3f* arg1, Vec3f* arg2) {
    f32 sp1C = Math_CosS(this->actor.home.rot.y);
    f32 sp18 = Math_SinS(this->actor.home.rot.y);
    f32 temp_f2 = arg2->x - this->actor.home.pos.x;
    f32 temp_f12 = arg2->z - this->actor.home.pos.z;

    arg1->x = (temp_f2 * sp1C) - (temp_f12 * sp18);
    arg1->z = (temp_f12 * sp1C) + (temp_f2 * sp18);
    arg1->y = arg2->y - this->actor.home.pos.y;
}

void func_80A715DC(EnDno* this, GlobalContext* globalCtx) {
    BgCraceMovebg* crace = NULL;
    s32 pad[2];
    Vec3f sp88;
    Vec3f sp7C;
    Vec3f sp70;

    do {
        crace = (BgCraceMovebg*)SubS_FindActor(globalCtx, &crace->actor, ACTORCAT_BG, ACTOR_BG_CRACE_MOVEBG);
        if (crace != NULL) {
            if (ENDNO_GET_F(&crace->actor) == ENDNO_GET_F_0 && !(crace->unk_170 & 1)) {
                if (func_8013E5CC(&crace->actor.home.pos, &crace->actor.home.rot, &D_80A73B2C, &this->actor.prevPos,
                                  &this->actor.world.pos, &sp88)) {
                    Math_Vec3f_Diff(&this->actor.world.pos, &crace->actor.home.pos, &sp7C);
                    Matrix_RotateY(-crace->actor.home.rot.y, MTXMODE_NEW);
                    Matrix_MultiplyVector3fByState(&sp7C, &sp70);
                    if ((fabsf(sp70.x) < 100.0f) && (sp70.y >= -10.0f) && (sp70.y <= 180.0f) && (sp70.z < 0.0f)) {
                        crace->unk_170 |= 1;
                    }
                }
            }
            crace = (BgCraceMovebg*)crace->actor.next;
        }
    } while (crace != NULL);
}

void func_80A71788(EnDno* this, GlobalContext* globalCtx) {
    Actor* actor = NULL;

    do {
        actor = SubS_FindActor(globalCtx, actor, ACTORCAT_BG, ACTOR_BG_CRACE_MOVEBG);
        if (actor != NULL) {
            Flags_UnsetSwitch(globalCtx, ENDNO_GET_7F0(actor));
            actor = actor->next;
        }
    } while (actor != NULL);
}

void EnDno_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnDno* this = THIS;
    s32 pad;
    Actor* actor = NULL;

    while (true) {
        actor = SubS_FindActor(globalCtx, actor, ACTORCAT_NPC, ACTOR_EN_DNO);
        if (actor != NULL) {
            if (actor != thisx) {
                Actor_MarkForDeath(thisx);
                break;
            }
            actor = actor->next;
        }

        if (actor == NULL) {
            Actor_ProcessInitChain(thisx, sInitChain);
            ActorShape_Init(&thisx->shape, 0.0f, ActorShadow_DrawCircle, 21.0f);
            SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_dno_Skel_00E1F8, &object_dno_Anim_007CA4,
                               this->jointTable, this->morphTable, 28);
            Collider_InitCylinder(globalCtx, &this->collider);
            Collider_SetCylinder(globalCtx, &this->collider, thisx, &sCylinderInit);
            Actor_UpdateBgCheckInfo(globalCtx, thisx, 0.0f, 0.0f, 0.0f, 4);
            Animation_Change(&this->skelAnime, sAnimations[14].animation, 1.0f, 0.0f,
                             Animation_GetLastFrame(sAnimations[14].animation), sAnimations[14].mode,
                             sAnimations[14].morphFrames);
            this->unk_3BE = 0x3E93;
            this->unk_3C0 = 60.0f;
            this->unk_3B0 = 0;
            this->unk_468 = 99;
            this->skelAnime.playSpeed = 0.0f;

            switch (ENDNO_GET_C000(thisx)) {
                case ENDNO_GET_C000_0:
                    func_80A71788(this, globalCtx);
                    if (!(gSaveContext.save.weekEventReg[23] & 0x20) || (gSaveContext.save.weekEventReg[93] & 2)) {
                        Actor_MarkForDeath(thisx);
                    } else {
                        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 14, &this->unk_32C);
                        thisx->room = -1;
                        gSaveContext.unk_3DD0[1] = 5;
                        this->lightNode = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &this->lightInfo);
                        this->unk_3B0 |= 1;
                        this->actionFunc = func_80A72438;
                        this->unk_454 = 0.0f;
                    }
                    break;

                case ENDNO_GET_C000_1:
                    if (gSaveContext.save.weekEventReg[23] & 0x20) {
                        Actor_MarkForDeath(thisx);
                    } else {
                        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 13, &this->unk_32C);
                        this->unk_460 = SubS_FindActor(globalCtx, NULL, ACTORCAT_NPC, ACTOR_EN_DNQ);
                        if (this->unk_460 == NULL) {
                            Actor_MarkForDeath(thisx);
                        } else {
                            this->actionFunc = func_80A71B68;
                        }
                    }
                    break;

                default:
                    this->actionFunc = func_80A71B04;
                    break;
            }
            break;
        }
    }
}

void EnDno_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnDno* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
    LightContext_RemoveLight(globalCtx, &globalCtx->lightCtx, this->lightNode);
}

void func_80A71B04(EnDno* this, GlobalContext* globalCtx) {
    this->unk_452 = 0;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 19, &this->unk_32C);
    this->actionFunc = EnDno_DoNothing;
}

void EnDno_DoNothing(EnDno* this, GlobalContext* globalCtx) {
}

void func_80A71B68(EnDno* this, GlobalContext* globalCtx) {
    this->unk_452 = 0;
    this->actor.textId = 0;
    if (CHECK_QUEST_ITEM(QUEST_SONG_SONATA)) {
        if (gSaveContext.save.weekEventReg[27] & 1) {
            if (!(this->unk_3B0 & 0x20)) {
                SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 6, &this->unk_32C);
                this->actor.shape.rot.y = Actor_YawBetweenActors(&this->actor, this->unk_460);
            }
        } else {
            SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 13, &this->unk_32C);
        }
    } else {
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 13, &this->unk_32C);
    }
    this->actionFunc = func_80A71C3C;
}

void func_80A71C3C(EnDno* this, GlobalContext* globalCtx) {
    switch (this->unk_32C) {
        case 9:
        case 16:
            SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 10, &this->unk_32C);
            break;

        case 3:
        case 10:
            if (this->skelAnime.curFrame == this->skelAnime.endFrame) {
                SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 13, &this->unk_32C);
            }
            break;

        case 11:
            SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 15, &this->unk_32C);
            break;

        case 15:
            if (this->skelAnime.curFrame == this->skelAnime.endFrame) {
                SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 6, &this->unk_32C);
            }

        case 6:
            Math_SmoothStepToS(&this->actor.shape.rot.y, Actor_YawBetweenActors(&this->actor, this->unk_460), 2, 0xE38,
                               0x222);
            break;
    }

    if ((this->unk_32C == 13) && (this->actor.xzDistToPlayer <= 120.0f)) {
        func_80A71424(&this->unk_466, 0, this->actor.yawTowardsPlayer, this->actor.shape.rot.y, 0x2000, 0x16C);
    } else {
        Math_ScaledStepToS(&this->unk_466, 0, 0x16C);
    }

    if ((this->unk_32C != 3) && (this->unk_32C != 15) && (this->unk_32C != 6)) {
        Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 0x222);
    }

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        globalCtx->msgCtx.msgMode = 0;
        globalCtx->msgCtx.unk11F10 = 0;
        func_80A71E54(this, globalCtx);
    } else if (this->actor.xzDistToPlayer < 60.0f) {
        func_800B8614(&this->actor, globalCtx, 60.0f);
    }
}

void func_80A71E54(EnDno* this, GlobalContext* globalCtx) {
    if (CHECK_QUEST_ITEM(QUEST_SONG_SONATA)) {
        if (gSaveContext.save.weekEventReg[27] & 1) {
            this->textId = 0x811;
        } else {
            this->textId = 0x80F;
            gSaveContext.save.weekEventReg[27] |= 1;
        }
    } else if (gSaveContext.save.weekEventReg[26] & 0x80) {
        this->textId = 0x80B;
    } else {
        this->textId = 0x80C;
        gSaveContext.save.weekEventReg[26] |= 0x80;
    }

    if (this->textId != 0x811) {
        this->unk_3B0 |= 0x10;
    } else {
        this->unk_3B0 &= ~0x10;
    }

    this->actionFunc = func_80A71F18;
}

void func_80A71F18(EnDno* this, GlobalContext* globalCtx) {
    Math_ScaledStepToS(&this->unk_466, 0, 0x16C);
    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 0:
            if (!(this->unk_3B0 & 0x10) ||
                Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xE38)) {
                switch (this->textId) {
                    case 0x80B:
                        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 16, &this->unk_32C);

                    case 0x811:
                        Message_StartTextbox(globalCtx, this->textId, &this->actor);
                        break;

                    case 0x80C:
                    case 0x80F:
                        if (this->unk_32C == 13) {
                            SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 4, &this->unk_32C);
                        } else if ((this->unk_32C == 4) && (this->skelAnime.curFrame == this->skelAnime.endFrame)) {
                            SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 11, &this->unk_32C);
                            Message_StartTextbox(globalCtx, this->textId, &this->actor);
                        }
                        break;
                }
            }
            break;

        case 3:
            if (globalCtx->msgCtx.currentTextId == 0x80B) {
                switch (this->unk_32C) {
                    case 16:
                        if (this->skelAnime.curFrame == this->skelAnime.endFrame) {
                            SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 9, &this->unk_32C);
                        }
                        Math_ScaledStepToS(&this->actor.shape.rot.y,
                                           Actor_YawBetweenActors(&this->actor, this->unk_460), 0x71C);
                        break;

                    case 10:
                        if (this->skelAnime.curFrame == this->skelAnime.endFrame) {
                            func_801477B4(globalCtx);
                            SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 13, &this->unk_32C);
                            func_80A71B68(this, globalCtx);
                        }
                        break;
                }
            }
            break;

        case 4:
        case 5:
        case 6:
            switch (globalCtx->msgCtx.currentTextId) {
                case 0x80B:
                    switch (this->unk_32C) {
                        case 16:
                            if (this->skelAnime.curFrame == this->skelAnime.endFrame) {
                                SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 9, &this->unk_32C);
                            }
                            break;

                        case 9:
                            if (Message_ShouldAdvance(globalCtx)) {
                                SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 10, &this->unk_32C);
                                globalCtx->msgCtx.msgMode = 0x44;
                            }
                            break;

                        case 10:
                            if (this->skelAnime.curFrame == this->skelAnime.endFrame) {
                                func_801477B4(globalCtx);
                                SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 13, &this->unk_32C);
                                func_80A71B68(this, globalCtx);
                            }
                            break;
                    }
                    break;

                case 0x80C:
                    if (Message_ShouldAdvance(globalCtx)) {
                        func_80151938(globalCtx, 0x80D);
                    }
                    break;

                case 0x80D:
                    if (Message_ShouldAdvance(globalCtx)) {
                        func_80151938(globalCtx, 0x80E);
                    }
                    break;

                case 0x80E:
                    if (this->unk_32C == 11) {
                        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 3, &this->unk_32C);
                    } else if (this->unk_32C == 3) {
                        if (this->skelAnime.curFrame == this->skelAnime.endFrame) {
                            SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 13, &this->unk_32C);
                        }
                    } else if ((this->unk_32C == 13) && Message_ShouldAdvance(globalCtx)) {
                        func_801477B4(globalCtx);
                        func_80A71B68(this, globalCtx);
                    }
                    break;

                case 0x80F:
                    if (Message_ShouldAdvance(globalCtx)) {
                        func_80151938(globalCtx, 0x810);
                    }
                    break;

                case 0x810:
                    if (Message_ShouldAdvance(globalCtx)) {
                        this->unk_3B0 |= 0x20;
                        func_801477B4(globalCtx);
                        func_80A71B68(this, globalCtx);
                        break;
                    }

                    switch (this->unk_32C) {
                        case 11:
                            SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 15, &this->unk_32C);
                            break;

                        case 15:
                            if (this->skelAnime.curFrame == this->skelAnime.endFrame) {
                                SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 6, &this->unk_32C);
                            }
                            break;
                    }
                    break;

                case 0x811:
                    if (Message_ShouldAdvance(globalCtx)) {
                        func_801477B4(globalCtx);
                        func_80A71B68(this, globalCtx);
                    }
                    break;
            }
            break;
    }
}

void func_80A72438(EnDno* this, GlobalContext* globalCtx) {
    this->unk_452 = 1;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 14, &this->unk_32C);
    this->actor.textId = 0;
    if (Flags_GetSwitch(globalCtx, ENDNO_GET_3F80(&this->actor))) {
        this->unk_454 = 1.0f;
    }
    this->actionFunc = func_80A724B8;
}

void func_80A724B8(EnDno* this, GlobalContext* globalCtx) {
    if (this->actor.xzDistToPlayer < 120.0f) {
        func_80A71424(&this->unk_466, 0, this->actor.yawTowardsPlayer, this->actor.home.rot.y, 0x2000, 0x2D8);
    }

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        func_80A725E0(this, globalCtx);
    } else if (this->actor.xzDistToPlayer < 60.0f) {
        func_800B8614(&this->actor, globalCtx, 60.0f);
    }
}

void func_80A7256C(EnDno* this, GlobalContext* globalCtx) {
    func_800B8500(&this->actor, globalCtx, this->actor.xzDistToPlayer, this->actor.playerHeightRel, EXCH_ITEM_MINUS1);
}

void func_80A72598(EnDno* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        func_80A725E0(this, globalCtx);
    } else {
        func_80A7256C(this, globalCtx);
    }
}

void func_80A725E0(EnDno* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80A725F8;
}

void func_80A725F8(EnDno* this, GlobalContext* globalCtx) {
    s32 pad[2];

    func_80A71424(&this->unk_466, 0, 0, 0, 0x2000, 0x16C);
    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 0:
            switch (this->unk_328) {
                case 0:
                    if (this->unk_32C == 14) {
                        if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x2D8)) {
                            SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 5, &this->unk_32C);
                        }
                    } else if ((this->unk_32C == 5) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                        if (Flags_GetSwitch(globalCtx, ENDNO_GET_3F80(&this->actor))) {
                            Message_StartTextbox(globalCtx, 0x801, &this->actor);
                        } else if (Player_GetMask(globalCtx) == PLAYER_MASK_SCENTS) {
                            Message_StartTextbox(globalCtx, 0x806, &this->actor);
                        } else {
                            Message_StartTextbox(globalCtx, 0x800, &this->actor);
                        }
                        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 14, &this->unk_32C);
                    }
                    break;

                case 2:
                    if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x2D8)) {
                        gSaveContext.save.weekEventReg[93] |= 2;
                        Message_StartTextbox(globalCtx, 0x802, &this->actor);
                    }
                    break;

                case 3:
                    Message_StartTextbox(globalCtx, 0x804, &this->actor);
                    break;
            }
            break;

        case 1:
        case 2:
        case 3:
            if (((globalCtx->msgCtx.currentTextId == 0x800) || (globalCtx->msgCtx.currentTextId == 0x801)) &&
                (this->unk_32C == 8)) {
                Math_SmoothStepToF(&this->unk_454, 1.0f, 1.0f, 0.1f, 0.01f);
                if (this->skelAnime.curFrame <= 23.0f) {
                    this->unk_452 = 3;
                    if (Animation_OnFrame(&this->skelAnime, 23.0f)) {
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_OPEN_AMBRELLA);
                    }
                } else if (this->skelAnime.curFrame <= 24.0f) {
                    this->unk_452 = 4;
                } else if (this->skelAnime.curFrame >= 25.0f) {
                    this->unk_452 = 2;
                }

                if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 12, &this->unk_32C);
                    Message_StartTextbox(globalCtx, 0x803, &this->actor);
                }
            }
            break;

        case 4:
        case 5:
        case 6:
            switch (globalCtx->msgCtx.currentTextId) {
                case 0x800:
                case 0x801:
                    if (Message_ShouldAdvance(globalCtx)) {
                        globalCtx->msgCtx.msgMode = 0x44;
                        this->unk_452 = 1;
                        this->unk_454 = 0.0f;
                        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 8, &this->unk_32C);
                    }
                    break;

                case 0x802:
                    if (Message_ShouldAdvance(globalCtx)) {
                        if (INV_CONTENT(ITEM_MASK_SCENTS) == ITEM_MASK_SCENTS) {
                            this->unk_458 = GI_RUPEE_RED;
                        } else {
                            this->unk_458 = GI_MASK_SCENTS;
                        }
                        Actor_PickUp(&this->actor, globalCtx, this->unk_458, 60.0f, 60.0f);
                        func_801477B4(globalCtx);
                        func_80A72B84(this, globalCtx);
                    }
                    break;

                case 0x803:
                    if (Message_ShouldAdvance(globalCtx)) {
                        func_80A72AE4(this, globalCtx);
                    }
                    break;

                case 0x804:
                    if (this->unk_32C == 14) {
                        if (Message_ShouldAdvance(globalCtx)) {
                            SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 5, &this->unk_32C);
                            if (!(this->unk_3B0 & 0x40)) {
                                func_80A72CF8(this, globalCtx);
                                this->unk_3B0 |= 0x40;
                            }
                        }
                    } else if ((this->unk_32C == 5) && (this->skelAnime.curFrame == this->skelAnime.endFrame)) {
                        func_801477B4(globalCtx);
                        func_80A72438(this, globalCtx);
                    }
                    break;

                case 0x806:
                    if (Message_ShouldAdvance(globalCtx)) {
                        func_80151938(globalCtx, 0x800);
                    }
                    break;

                default:
                    func_80A72438(this, globalCtx);
                    break;
            }
            break;
    }
}

void func_80A72AE4(EnDno* this, GlobalContext* globalCtx) {
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 0, &this->unk_32C);
    func_80A714B4(this, globalCtx);
    this->actionFunc = func_80A72B3C;
}

void func_80A72B3C(EnDno* this, GlobalContext* globalCtx) {
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        this->unk_44E = 0;
        func_80A72C04(this, globalCtx);
    }
}

void func_80A72B84(EnDno* this, GlobalContext* globalCtx) {
    this->unk_328 = 3;
    this->actionFunc = func_80A72BA4;
}

void func_80A72BA4(EnDno* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->actionFunc = func_80A72598;
    } else {
        Actor_PickUp(&this->actor, globalCtx, this->unk_458, 60.0f, 60.0f);
    }
}

void func_80A72C04(EnDno* this, GlobalContext* globalCtx) {
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 0, &this->unk_32C);
    this->actor.flags |= ACTOR_FLAG_8000000;
    this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_8);
    Math_Vec3f_Copy(&this->unk_334, &this->actor.world.pos);
    SubS_ActorPathing_Init(globalCtx, &this->unk_334, &this->actor, &this->actorPath, globalCtx->setupPathList,
                           ENDNO_GET_7F(&this->actor), 1, 0, 1, 0);
    SubS_ActorPathing_ComputePointInfo(globalCtx, &this->actorPath);

    this->actor.world.rot.y = this->actorPath.rotToCurPoint.y;
    this->actor.world.rot.x = this->actorPath.rotToCurPoint.x;

    Flags_SetSwitch(globalCtx, ENDNO_GET_3F80(&this->actor));
    this->actionFunc = func_80A730A0;
}

void func_80A72CF8(EnDno* this, GlobalContext* globalCtx) {
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_DOOR_WARP1, this->actor.world.pos.x + 80.0f,
                       this->actor.floorHeight, this->actor.world.pos.z, 0, 0, 0, 0x201);
}

s32 EnDno_ActorPathing_UpdateActorInfo(GlobalContext* globalCtx, ActorPathing* actorPath) {
    Actor* thisx = actorPath->actor;
    s32 pad;
    s32 ret = false;
    f32 sp38;
    s16 temp_v0;
    s32 temp_v0_2;
    s32 sp2C;

    thisx->gravity = 0.0f;
    temp_v0 = thisx->yawTowardsPlayer - thisx->world.rot.y;
    if ((temp_v0 <= 0x4000) && (temp_v0 >= -0x4000)) {
        Math_SmoothStepToF(&thisx->speedXZ, 15.0f, 0.8f, 1.0f, 0.01f);
    } else {
        if (thisx->xzDistToPlayer <= 80.0f) {
            Math_SmoothStepToF(&thisx->speedXZ, 8.0f, 0.5f, 0.5f, 0.01f);
        } else if (thisx->xzDistToPlayer <= 360.0f) {
            Math_SmoothStepToF(&thisx->speedXZ, 7.0f, 0.5f, 0.5f, 0.01f);
        } else {
            Math_SmoothStepToF(&thisx->speedXZ, 3.5f, 0.5f, 0.5f, 0.01f);
        }
    }

    if (actorPath->distSqToCurPoint < SQ(thisx->speedXZ)) {
        ret = true;
    } else {
        sp38 = thisx->speedXZ / sqrtf(actorPath->distSqToCurPointXZ);
        sp2C = ABS(actorPath->rotToCurPoint.x - thisx->world.rot.x);
        temp_v0_2 = sp2C;
        temp_v0_2 *= sp38;
        temp_v0_2 += 0x71C;
        sp2C = ABS(actorPath->rotToCurPoint.y - thisx->world.rot.y);

        Math_ScaledStepToS(&thisx->world.rot.x, actorPath->rotToCurPoint.x, temp_v0_2);
        Math_ScaledStepToS(&thisx->world.rot.y, actorPath->rotToCurPoint.y, (s32)(sp2C * sp38) + 0x71C);
    }

    return ret;
}

s32 EnDno_ActorPathing_Move(GlobalContext* globalCtx, ActorPathing* actorPath) {
    Actor* thisx = actorPath->actor;
    EnDno* this = (EnDno*)thisx;
    f32 sp24 = Math_CosS(-thisx->world.rot.x) * thisx->speedXZ;
    f32 sp20 = gFramerateDivisorHalf;

    thisx->velocity.x = Math_SinS(thisx->world.rot.y) * sp24;
    thisx->velocity.y = Math_SinS(-thisx->world.rot.x) * thisx->speedXZ;
    thisx->velocity.z = Math_CosS(thisx->world.rot.y) * sp24;

    this->unk_334.x += (this->actor.velocity.x * sp20) + this->actor.colChkInfo.displacement.x;
    this->unk_334.y += (this->actor.velocity.y * sp20) + this->actor.colChkInfo.displacement.y;
    this->unk_334.z += (this->actor.velocity.z * sp20) + this->actor.colChkInfo.displacement.z;

    return false;
}

void func_80A730A0(EnDno* this, GlobalContext* globalCtx) {
    f32 temp_f10;
    s32 phi_a2;

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        phi_a2 = -1;
        switch (this->unk_32C) {
            case 0:
                if (this->unk_44E >= 20) {
                    phi_a2 = 1;
                } else {
                    this->unk_44E = 20;
                }
                break;

            case 1:
                phi_a2 = 2;
                break;
        }

        if (phi_a2 >= 0) {
            SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, phi_a2, &this->unk_32C);
        }
    }

    SubS_ActorPathing_Update(globalCtx, &this->actorPath, SubS_ActorPathing_ComputePointInfo,
                             EnDno_ActorPathing_UpdateActorInfo, EnDno_ActorPathing_Move,
                             SubS_ActorPathing_SetNextPoint);
    this->unk_45C += 6553;
    this->actorPath.pointOffset.x = 0.0f;
    this->actorPath.pointOffset.y = 0.0f;
    this->actorPath.pointOffset.z = 0.0f;
    Math_Vec3f_Copy(&this->actor.world.pos, &this->unk_334);
    temp_f10 = (4.0f + Math_SinS(this->unk_3AE)) * Math_SinS(this->unk_3AC);
    this->actor.world.pos.y += temp_f10;
    this->unk_3AC += 4500;
    this->unk_3AE += 1000;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    func_80A715DC(this, globalCtx);
    func_800B9010(&this->actor, NA_SE_EV_BUTLER_FRY - SFX_FLAG);
    if (this->actorPath.flags & ACTOR_PATHING_REACHED_END_PERMANENT) {
        Math_Vec3f_Copy(&this->actor.world.pos, &this->actorPath.curPoint);
        this->actor.speedXZ = 0.0f;
        this->actor.velocity.x = 0.0f;
        this->actor.velocity.y = 0.0f;
        this->actor.velocity.z = 0.0f;
        func_80A73244(this, globalCtx);
    }
}

void func_80A73244(EnDno* this, GlobalContext* globalCtx) {
    this->actor.flags &= ~ACTOR_FLAG_8000000;
    this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
    this->unk_328 = 2;
    this->actor.speedXZ = 0.0f;
    Flags_UnsetSwitch(globalCtx, ENDNO_GET_3F80(&this->actor));
    gSaveContext.unk_3DD0[1] = 5;
    this->unk_44E = 0;
    this->actionFunc = func_80A732C8;
}

void func_80A732C8(EnDno* this, GlobalContext* globalCtx) {
    s32 pad;

    if (this->unk_44E == 0) {
        if (Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0x71C)) {
            this->unk_3B0 |= 4;
            this->unk_44E = 3;
            SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 7, &this->unk_32C);
        }
    } else if (this->unk_44E == 3) {
        if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 14, &this->unk_32C);
            func_80A72438(this, globalCtx);
        } else {
            if (this->skelAnime.curFrame >= 20.0f) {
                Math_SmoothStepToF(&this->unk_454, 0.0f, 1.0f, 0.125f, 0.01f);
            }

            if (Animation_OnFrame(&this->skelAnime, 4.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CLOSE_AMBRELLA);
                this->unk_452 = 4;
            } else if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
                this->unk_452 = 3;
            }
        }
    }
    Actor_MoveWithGravity(&this->actor);
}

void func_80A73408(EnDno* this, GlobalContext* globalCtx) {
    s32 phi_a2;
    u8 sp33 = true;
    s32 temp_v0;

    if (Cutscene_CheckActorAction(globalCtx, 475)) {
        temp_v0 = Cutscene_GetActorActionIndex(globalCtx, 475);
        if (this->unk_468 != globalCtx->csCtx.actorActions[temp_v0]->action) {
            switch (globalCtx->csCtx.actorActions[temp_v0]->action) {
                case 1:
                    phi_a2 = 13;
                    break;

                case 2:
                    phi_a2 = 17;
                    break;

                default:
                    phi_a2 = 0;
                    sp33 = false;
                    break;
            }

            if (sp33) {
                SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, phi_a2, &this->unk_32C);
            }
        }
        Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, temp_v0);
    }

    if ((Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) && (this->unk_32C == 17)) {
        if (0) {};
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, 18, &this->unk_32C);
    }
}

void EnDno_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnDno* this = THIS;
    s32 pad;

    SkelAnime_Update(&this->skelAnime);
    func_80A73408(this, globalCtx);
    this->actionFunc(this, globalCtx);
    if (this->unk_3B0 & 4) {
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    }
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_SetFocus(&this->actor, 51.0f);
}

void EnDno_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnDno* this = THIS;

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnDno_OverrideLimbDraw, EnDno_PostLimbDraw, &this->actor);
}

s32 EnDno_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnDno* this = THIS;

    *dList = NULL;
    if (limbIndex == 9) {
        rot->x += this->unk_466;
    }
    return false;
}

void EnDno_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80A73B40 = { 0.0f, 0.0f, 0.0f };
    Gfx* gfxOpa;
    Gfx* gfxXlu;
    Vec3f sp84;
    EnDno* this = THIS;
    s32 pad;
    s32 phi_v0 = false;

    if (*dList != NULL) {
        switch (this->unk_452) {
            case 0:
                if ((limbIndex != 25) && (limbIndex != 26) && (limbIndex != 13) && (limbIndex != 15) &&
                    (limbIndex != 16) && (limbIndex != 14)) {
                    phi_v0 = true;
                }
                break;

            case 1:
                if ((limbIndex != 26) && (limbIndex != 13) && (limbIndex != 15) && (limbIndex != 16) &&
                    (limbIndex != 14)) {
                    phi_v0 = true;
                }
                break;

            case 2:
                if ((limbIndex != 15) && (limbIndex != 16)) {
                    phi_v0 = true;
                }
                break;

            case 3:
                if ((limbIndex != 16) && (limbIndex != 14)) {
                    phi_v0 = true;
                }
                break;

            case 4:
                if ((limbIndex != 15) && (limbIndex != 14)) {
                    phi_v0 = true;
                }
                break;
        }
    }

    if (phi_v0 == true) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C28C(globalCtx->state.gfxCtx);
        if (limbIndex == 13) {
            Matrix_Scale(this->unk_454, this->unk_454, this->unk_454, MTXMODE_APPLY);
            Matrix_InsertXRotation_s(this->unk_45C, MTXMODE_APPLY);
        }

        gfxOpa = POLY_OPA_DISP;
        gSPMatrix(gfxOpa, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(&gfxOpa[1], *dList);

        POLY_OPA_DISP = gfxOpa + 2;
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }

    if ((this->unk_3B0 & 1) && (limbIndex == 26)) {
        u32 frames;

        OPEN_DISPS(globalCtx->state.gfxCtx);

        Matrix_StatePush();
        frames = globalCtx->gameplayFrames;
        Matrix_MultiplyVector3fByState(&D_80A73B40, &sp84);
        func_80A711D0(this, globalCtx, &sp84);
        Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
        Matrix_Scale(0.15f, 0.15f, 1.0f, MTXMODE_APPLY);
        Matrix_InsertTranslation(0.0f, -3200.0f, 0.0f, MTXMODE_APPLY);
        gfxXlu = func_8012C2B4(POLY_XLU_DISP);

        gSPMatrix(gfxXlu, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(&gfxXlu[1], 0x08,
                   Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0, -frames * 20, 0x20, 0x80));
        gDPSetPrimColor(&gfxXlu[2], 0x80, 0x80, 255, 255, 0, 255);
        gDPSetEnvColor(&gfxXlu[3], 255, 0, 0, 0);
        gSPDisplayList(&gfxXlu[4], gGameplayKeepDrawFlameDL);

        POLY_XLU_DISP = gfxXlu + 5;

        Matrix_StatePop();

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
