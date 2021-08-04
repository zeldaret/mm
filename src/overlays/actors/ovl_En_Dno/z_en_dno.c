/*
 * File: z_en_dno.c
 * Overlay: ovl_En_Dno
 * Description: Deku Butler
 */

#include "z_en_dno.h"
#include "overlays/actors/ovl_Bg_Crace_Movebg/z_bg_crace_movebg.h"

#define FLAGS 0x00000039

#define THIS ((EnDno*)thisx)

void EnDno_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDno_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDno_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDno_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A72438(EnDno* this, GlobalContext* globalCtx);
void func_80A71B68(EnDno* this, GlobalContext* globalCtx);
void func_80A71B04(EnDno* this, GlobalContext* globalCtx);
void func_80A724B8(EnDno* this, GlobalContext* globalCtx);
void func_80A71C3C(EnDno* this, GlobalContext* globalCtx);
void func_80A71B58(EnDno* this, GlobalContext* globalCtx);
void func_80A725E0(EnDno* this, GlobalContext* globalCtx);
void func_80A71E54(EnDno* this, GlobalContext* globalCtx);
void func_80A725F8(EnDno* this, GlobalContext* globalCtx);
void func_80A71F18(EnDno* this, GlobalContext* globalCtx);
void func_80A72AE4(EnDno* this, GlobalContext* globalCtx);
void func_80A72CF8(EnDno* this, GlobalContext* globalCtx);
void func_80A72B84(EnDno* this, GlobalContext* globalCtx);
void func_80A72B3C(EnDno* this, GlobalContext* globalCtx);
void func_80A72BA4(EnDno* this, GlobalContext* globalCtx);
void func_80A72C04(EnDno* this, GlobalContext* globalCtx);
void func_80A730A0(EnDno* this, GlobalContext* globalCtx);
void func_80A73244(EnDno* this, GlobalContext* globalCtx);
void func_80A732C8(EnDno* this, GlobalContext* globalCtx);
s32 func_80A7361C(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void func_80A73654(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);

extern u8 D_801C20C0;
extern FlexSkeletonHeader D_0600E1F8;
extern AnimationHeader D_06007CA4;
extern AnimationHeader D_06000470;
extern AnimationHeader D_060008F0;
extern AnimationHeader D_06000F6C;
extern AnimationHeader D_06001A50;
extern AnimationHeader D_06002530;
extern AnimationHeader D_06003320;
extern AnimationHeader D_060036D0;
extern AnimationHeader D_060041CC;
extern AnimationHeader D_06004DD8;
extern AnimationHeader D_06005F98;
extern AnimationHeader D_06006488;
extern AnimationHeader D_060073E4;
extern AnimationHeader D_060077A8;
extern AnimationHeader D_06007CA4;
extern AnimationHeader D_06008324;
extern AnimationHeader D_06008AE4;
extern AnimationHeader D_06009100;
extern AnimationHeader D_060051E4;
extern AnimationHeader D_06005E20;
extern AnimationHeader D_06006F84;

static struct_80B8E1A8 D_80A739A0[] = {
    { &D_06000470, 1.0f, 2, 0.0f }, { &D_060008F0, 1.0f, 2, 0.0f }, { &D_06000F6C, 1.0f, 0, 0.0f },
    { &D_06001A50, 1.0f, 2, 0.0f }, { &D_06002530, 1.0f, 2, 0.0f }, { &D_06003320, 1.0f, 2, 0.0f },
    { &D_060036D0, 1.0f, 0, 0.0f }, { &D_060041CC, 1.0f, 2, 0.0f }, { &D_06004DD8, 1.0f, 2, 0.0f },
    { &D_06005F98, 1.0f, 0, 0.0f }, { &D_06006488, 1.0f, 2, 0.0f }, { &D_060073E4, 1.0f, 0, 0.0f },
    { &D_060077A8, 1.0f, 0, 0.0f }, { &D_06007CA4, 1.0f, 0, 0.0f }, { &D_06008324, 1.0f, 0, 0.0f },
    { &D_06008AE4, 1.0f, 2, 0.0f }, { &D_06009100, 1.0f, 2, 0.0f }, { &D_060051E4, 1.0f, 2, 0.0f },
    { &D_06005E20, 1.0f, 0, 0.0f }, { &D_06006F84, 1.0f, 0, 0.0f },
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
        actor = func_ActorCategoryIterateById(globalCtx, actor, ACTORCAT_BG, ACTOR_BG_CRACE_MOVEBG);
        if (actor != NULL) {
            if (ENDNO_PARAMS_F(actor) == ENDNO_PARAMS_F_1) {
                Actor_SetSwitchFlag(globalCtx, ENDNO_PARAMS_7F0(actor));
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
    f32 temp_f8 = temp_f2 * sp18;

    arg1->x = (temp_f2 * sp1C) - (temp_f12 * sp18);
    arg1->z = (temp_f12 * sp1C) + temp_f8;
    arg1->y = arg2->y - this->actor.home.pos.y;
}

void func_80A715DC(EnDno* this, GlobalContext* globalCtx) {
    BgCraceMovebg* crace = NULL;
    s32 pad[2];
    Vec3f sp88;
    Vec3f sp7C;
    Vec3f sp70;

    do {
        crace =
            (BgCraceMovebg*)func_ActorCategoryIterateById(globalCtx, &crace->actor, ACTORCAT_BG, ACTOR_BG_CRACE_MOVEBG);
        if (crace != NULL) {
            if (ENDNO_PARAMS_F(&crace->actor) == ENDNO_PARAMS_F_0 && !(crace->unk_170 & 1)) {
                if (func_8013E5CC(&crace->actor.home.pos, &crace->actor.home.rot, &D_80A73B2C, &this->actor.prevPos,
                                  &this->actor.world.pos, &sp88)) {
                    Math_Vec3f_Diff(&this->actor.world.pos, &crace->actor.home.pos, &sp7C);
                    Matrix_RotateY(-crace->actor.home.rot.y, 0);
                    SysMatrix_MultiplyVector3fByState(&sp7C, &sp70);
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
        actor = func_ActorCategoryIterateById(globalCtx, actor, ACTORCAT_BG, ACTOR_BG_CRACE_MOVEBG);
        if (actor != NULL) {
            Actor_UnsetSwitchFlag(globalCtx, ENDNO_PARAMS_7F0(actor));
            actor = actor->next;
        }
    } while (actor != NULL);
}

void EnDno_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnDno* this = THIS;
    s32 pad;
    Actor* actor = NULL;

    while (true) {
        actor = func_ActorCategoryIterateById(globalCtx, actor, ACTORCAT_NPC, ACTOR_EN_DNO);
        if (actor != NULL) {
            if (actor != thisx) {
                Actor_MarkForDeath(&this->actor);
                break;
            }
            actor = actor->next;
        }

        if (actor == NULL) {
            Actor_ProcessInitChain(&this->actor, sInitChain);
            ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 21.0f);
            SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600E1F8, &D_06007CA4, this->jointTable, this->morphTable,
                             28);
            Collider_InitCylinder(globalCtx, &this->collider);
            Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
            SkelAnime_ChangeAnim(&this->skelAnime, D_80A739A0[14].animationSeg, 1.0f, 0.0f,
                                 SkelAnime_GetFrameCount(&(D_80A739A0[14].animationSeg)->common), D_80A739A0[14].mode,
                                 D_80A739A0[14].transitionRate);
            this->unk_3BE = 0x3E93;
            this->unk_3C0 = 60.0f;
            this->unk_3B0 = 0;
            this->unk_468 = 99;
            this->skelAnime.animPlaybackSpeed = 0.0f;

            switch (ENDNO_PARAMS_C000(&this->actor)) {
                case ENDNO_PARAMS_C000_0:
                    func_80A71788(this, globalCtx);
                    if (!(gSaveContext.weekEventReg[23] & 0x20) || (gSaveContext.weekEventReg[93] & 2)) {
                        Actor_MarkForDeath(&this->actor);
                    } else {
                        func_8013E1C8(&this->skelAnime, D_80A739A0, 14, &this->unk_32C);
                        this->actor.room = -1;
                        gSaveContext.unk_3DD0[1] = 5;
                        this->lightNode = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &this->lightInfo);
                        this->unk_3B0 |= 1;
                        this->actionFunc = func_80A72438;
                        this->unk_454 = 0.0f;
                    }
                    break;

                case ENDNO_PARAMS_C000_1:
                    if (gSaveContext.weekEventReg[23] & 0x20) {
                        Actor_MarkForDeath(&this->actor);
                    } else {
                        func_8013E1C8(&this->skelAnime, D_80A739A0, 13, &this->unk_32C);
                        this->unk_460 = func_ActorCategoryIterateById(globalCtx, NULL, ACTORCAT_NPC, ACTOR_EN_DNQ);
                        if (this->unk_460 == NULL) {
                            Actor_MarkForDeath(&this->actor);
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
    func_8013E1C8(&this->skelAnime, D_80A739A0, 19, &this->unk_32C);
    this->actionFunc = func_80A71B58;
}

void func_80A71B58(EnDno* this, GlobalContext* globalCtx) {
}

void func_80A71B68(EnDno* this, GlobalContext* globalCtx) {
    this->unk_452 = 0;
    this->actor.textId = 0;
    if (CHECK_QUEST_ITEM(6)) {
        if (gSaveContext.weekEventReg[27] & 1) {
            if (!(this->unk_3B0 & 0x20)) {
                func_8013E1C8(&this->skelAnime, D_80A739A0, 6, &this->unk_32C);
                this->actor.shape.rot.y = Actor_YawBetweenActors(&this->actor, this->unk_460);
            }
        } else {
            func_8013E1C8(&this->skelAnime, D_80A739A0, 13, &this->unk_32C);
        }
    } else {
        func_8013E1C8(&this->skelAnime, D_80A739A0, 13, &this->unk_32C);
    }
    this->actionFunc = func_80A71C3C;
}

void func_80A71C3C(EnDno* this, GlobalContext* globalCtx) {
    switch (this->unk_32C) {
        case 9:
        case 16:
            func_8013E1C8(&this->skelAnime, D_80A739A0, 10, &this->unk_32C);
            break;

        case 3:
        case 10:
            if (this->skelAnime.animCurrentFrame == this->skelAnime.animFrameCount) {
                func_8013E1C8(&this->skelAnime, D_80A739A0, 13, &this->unk_32C);
            }
            break;

        case 11:
            func_8013E1C8(&this->skelAnime, D_80A739A0, 15, &this->unk_32C);
            break;

        case 15:
            if (this->skelAnime.animCurrentFrame == this->skelAnime.animFrameCount) {
                func_8013E1C8(&this->skelAnime, D_80A739A0, 6, &this->unk_32C);
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

    if (func_800B84D0(&this->actor, globalCtx)) {
        globalCtx->msgCtx.unk11F22 = 0;
        globalCtx->msgCtx.unk11F10 = 0;
        func_80A71E54(this, globalCtx);
    } else if (this->actor.xzDistToPlayer < 60.0f) {
        func_800B8614(&this->actor, globalCtx, 60.0f);
    }
}

void func_80A71E54(EnDno* this, GlobalContext* globalCtx) {
    if (CHECK_QUEST_ITEM(6)) {
        if (gSaveContext.weekEventReg[27] & 1) {
            this->unk_464 = 0x811;
        } else {
            this->unk_464 = 0x80F;
            gSaveContext.weekEventReg[27] |= 1;
        }
    } else if (gSaveContext.weekEventReg[26] & 0x80) {
        this->unk_464 = 0x80B;
    } else {
        this->unk_464 = 0x80C;
        gSaveContext.weekEventReg[26] |= 0x80;
    }

    if (this->unk_464 != 0x811) {
        this->unk_3B0 |= 0x10;
    } else {
        this->unk_3B0 &= ~0x10;
    }

    this->actionFunc = func_80A71F18;
}

void func_80A71F18(EnDno* this, GlobalContext* globalCtx) {
    Math_ScaledStepToS(&this->unk_466, 0, 0x16C);
    switch (func_80152498(&globalCtx->msgCtx)) {
        case 0:
            if (!(this->unk_3B0 & 0x10) ||
                Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xE38)) {
                switch (this->unk_464) {
                    case 0x80B:
                        func_8013E1C8(&this->skelAnime, D_80A739A0, 16, &this->unk_32C);

                    case 0x811:
                        func_801518B0(globalCtx, this->unk_464, &this->actor);
                        break;

                    case 0x80C:
                    case 0x80F:
                        if (this->unk_32C == 13) {
                            func_8013E1C8(&this->skelAnime, D_80A739A0, 4, &this->unk_32C);
                        } else if ((this->unk_32C == 4) &&
                                   (this->skelAnime.animCurrentFrame == this->skelAnime.animFrameCount)) {
                            func_8013E1C8(&this->skelAnime, D_80A739A0, 11, &this->unk_32C);
                            func_801518B0(globalCtx, this->unk_464, &this->actor);
                        }
                        break;
                }
            }
            break;

        case 3:
            if (globalCtx->msgCtx.unk11F04 == 0x80B) {
                switch (this->unk_32C) {
                    case 16:
                        if (this->skelAnime.animCurrentFrame == this->skelAnime.animFrameCount) {
                            func_8013E1C8(&this->skelAnime, D_80A739A0, 9, &this->unk_32C);
                        }
                        Math_ScaledStepToS(&this->actor.shape.rot.y,
                                           Actor_YawBetweenActors(&this->actor, this->unk_460), 0x71C);
                        break;

                    case 10:
                        if (this->skelAnime.animCurrentFrame == this->skelAnime.animFrameCount) {
                            func_801477B4(globalCtx);
                            func_8013E1C8(&this->skelAnime, D_80A739A0, 0xD, &this->unk_32C);
                            func_80A71B68(this, globalCtx);
                        }
                        break;
                }
            }
            break;

        case 4:
        case 5:
        case 6:
            switch (globalCtx->msgCtx.unk11F04) {
                case 0x80B:
                    switch (this->unk_32C) {
                        case 16:
                            if (this->skelAnime.animCurrentFrame == this->skelAnime.animFrameCount) {
                                func_8013E1C8(&this->skelAnime, D_80A739A0, 9, &this->unk_32C);
                            }
                            break;

                        case 9:
                            if (func_80147624(globalCtx)) {
                                func_8013E1C8(&this->skelAnime, D_80A739A0, 10, &this->unk_32C);
                                globalCtx->msgCtx.unk11F22 = 0x44;
                            }
                            break;

                        case 10:
                            if (this->skelAnime.animCurrentFrame == this->skelAnime.animFrameCount) {
                                func_801477B4(globalCtx);
                                func_8013E1C8(&this->skelAnime, D_80A739A0, 13, &this->unk_32C);
                                func_80A71B68(this, globalCtx);
                            }
                            break;
                    }
                    break;

                case 0x80C:
                    if (func_80147624(globalCtx)) {
                        func_80151938(globalCtx, 0x80D);
                    }
                    break;

                case 0x80D:
                    if (func_80147624(globalCtx)) {
                        func_80151938(globalCtx, 0x80E);
                    }
                    break;

                case 0x80E:
                    if (this->unk_32C == 11) {
                        func_8013E1C8(&this->skelAnime, D_80A739A0, 3, &this->unk_32C);
                    } else if (this->unk_32C == 3) {
                        if (this->skelAnime.animCurrentFrame == this->skelAnime.animFrameCount) {
                            func_8013E1C8(&this->skelAnime, D_80A739A0, 13, &this->unk_32C);
                        }
                    } else if ((this->unk_32C == 13) && func_80147624(globalCtx)) {
                        func_801477B4(globalCtx);
                        func_80A71B68(this, globalCtx);
                    }
                    break;

                case 0x80F:
                    if (func_80147624(globalCtx)) {
                        func_80151938(globalCtx, 0x810);
                    }
                    break;

                case 0x810:
                    if (func_80147624(globalCtx)) {
                        this->unk_3B0 |= 0x20;
                        func_801477B4(globalCtx);
                        func_80A71B68(this, globalCtx);
                        break;
                    }

                    switch (this->unk_32C) {
                        case 11:
                            func_8013E1C8(&this->skelAnime, D_80A739A0, 15, &this->unk_32C);
                            break;

                        case 15:
                            if (this->skelAnime.animCurrentFrame == this->skelAnime.animFrameCount) {
                                func_8013E1C8(&this->skelAnime, D_80A739A0, 6, &this->unk_32C);
                            }
                            break;
                    }
                    break;

                case 0x811:
                    if (func_80147624(globalCtx)) {
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
    func_8013E1C8(&this->skelAnime, D_80A739A0, 14, &this->unk_32C);
    this->actor.textId = 0;
    if (Flags_GetSwitch(globalCtx, ENDNO_PARAMS_3F80(&this->actor))) {
        this->unk_454 = 1.0f;
    }
    this->actionFunc = func_80A724B8;
}

void func_80A724B8(EnDno* this, GlobalContext* globalCtx) {
    if (this->actor.xzDistToPlayer < 120.0f) {
        func_80A71424(&this->unk_466, 0, this->actor.yawTowardsPlayer, this->actor.home.rot.y, 0x2000, 0x2D8);
    }

    if (func_800B84D0(&this->actor, globalCtx)) {
        func_80A725E0(this, globalCtx);
    } else if (this->actor.xzDistToPlayer < 60.0f) {
        func_800B8614(&this->actor, globalCtx, 60.0f);
    }
}

void func_80A7256C(EnDno* this, GlobalContext* globalCtx) {
    func_800B8500(&this->actor, globalCtx, this->actor.xzDistToPlayer, this->actor.yDistToPlayer, -1);
}

void func_80A72598(EnDno* this, GlobalContext* globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx)) {
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
    switch (func_80152498(&globalCtx->msgCtx)) {
        case 0:
            switch (this->unk_328) {
                case 0:
                    if (this->unk_32C == 14) {
                        if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x2D8)) {
                            func_8013E1C8(&this->skelAnime, D_80A739A0, 5, &this->unk_32C);
                        }
                    } else if ((this->unk_32C == 5) &&
                               func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount)) {
                        if (Flags_GetSwitch(globalCtx, ENDNO_PARAMS_3F80(&this->actor))) {
                            func_801518B0(globalCtx, 0x801, &this->actor);
                        } else if (Player_GetMask(globalCtx) == PLAYER_MASK_MASK_OF_SCENTS) {
                            func_801518B0(globalCtx, 0x806, &this->actor);
                        } else {
                            func_801518B0(globalCtx, 0x800, &this->actor);
                        }
                        func_8013E1C8(&this->skelAnime, D_80A739A0, 14, &this->unk_32C);
                    }
                    break;

                case 2:
                    if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x2D8)) {
                        gSaveContext.weekEventReg[93] |= 2;
                        func_801518B0(globalCtx, 0x802, &this->actor);
                    }
                    break;

                case 3:
                    func_801518B0(globalCtx, 0x804, &this->actor);
                    break;
            }
            break;

        case 1:
        case 2:
        case 3:
            if (((globalCtx->msgCtx.unk11F04 == 0x800) || (globalCtx->msgCtx.unk11F04 == 0x801)) &&
                (this->unk_32C == 8)) {
                Math_SmoothStepToF(&this->unk_454, 1.0f, 1.0f, 0.1f, 0.01f);
                if (this->skelAnime.animCurrentFrame <= 23.0f) {
                    this->unk_452 = 3;
                    if (func_801378B8(&this->skelAnime, 23.0f)) {
                        Audio_PlayActorSound2(&this->actor, NA_SE_EV_OPEN_AMBRELLA);
                    }
                } else if (this->skelAnime.animCurrentFrame <= 24.0f) {
                    this->unk_452 = 4;
                } else if (this->skelAnime.animCurrentFrame >= 25.0f) {
                    this->unk_452 = 2;
                }

                if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount)) {
                    func_8013E1C8(&this->skelAnime, D_80A739A0, 12, &this->unk_32C);
                    func_801518B0(globalCtx, 0x803, &this->actor);
                }
            }
            break;

        case 4:
        case 5:
        case 6:
            switch (globalCtx->msgCtx.unk11F04) {
                case 0x800:
                case 0x801:
                    if (func_80147624(globalCtx)) {
                        globalCtx->msgCtx.unk11F22 = 0x44;
                        this->unk_452 = 1;
                        this->unk_454 = 0.0f;
                        func_8013E1C8(&this->skelAnime, D_80A739A0, 8, &this->unk_32C);
                    }
                    break;

                case 0x802:
                    if (func_80147624(globalCtx)) {
                        if (gSaveContext.inventory.items[D_801C20C0] == ITEM_MASK_SCENTS) {
                            this->unk_458 = 4;
                        } else {
                            this->unk_458 = 142;
                        }
                        func_800B8A1C(&this->actor, globalCtx, this->unk_458, 60.0f, 60.0f);
                        func_801477B4(globalCtx);
                        func_80A72B84(this, globalCtx);
                    }
                    break;

                case 0x803:
                    if (func_80147624(globalCtx)) {
                        func_80A72AE4(this, globalCtx);
                    }
                    break;

                case 0x804:
                    if (this->unk_32C == 14) {
                        if (func_80147624(globalCtx)) {
                            func_8013E1C8(&this->skelAnime, D_80A739A0, 5, &this->unk_32C);
                            if (!(this->unk_3B0 & 0x40)) {
                                func_80A72CF8(this, globalCtx);
                                this->unk_3B0 |= 0x40;
                            }
                        }
                    } else if ((this->unk_32C == 5) &&
                               (this->skelAnime.animCurrentFrame == this->skelAnime.animFrameCount)) {
                        func_801477B4(globalCtx);
                        func_80A72438(this, globalCtx);
                    }
                    break;

                case 0x806:
                    if (func_80147624(globalCtx)) {
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
    func_8013E1C8(&this->skelAnime, D_80A739A0, 0, &this->unk_32C);
    func_80A714B4(this, globalCtx);
    this->actionFunc = func_80A72B3C;
}

void func_80A72B3C(EnDno* this, GlobalContext* globalCtx) {
    if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount)) {
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
        func_800B8A1C(&this->actor, globalCtx, this->unk_458, 60.0f, 60.0f);
    }
}

void func_80A72C04(EnDno* this, GlobalContext* globalCtx) {
    func_8013E1C8(&this->skelAnime, D_80A739A0, 0, &this->unk_32C);
    this->actor.flags |= 0x8000000;
    this->actor.flags &= ~(8 | 1);
    Math_Vec3f_Copy(&this->unk_334, &this->actor.world.pos);
    func_8013DCE0(globalCtx, &this->unk_334, &this->actor, &this->unk_340, globalCtx->setupPathList,
                  ENDNO_PARAMS_7F(&this->actor), 1, 0, 1, 0);
    func_8013DF3C(globalCtx, &this->unk_340);
    this->actor.world.rot.y = this->unk_340.unk_56;
    this->actor.world.rot.x = this->unk_340.unk_54;
    Actor_SetSwitchFlag(globalCtx, ENDNO_PARAMS_3F80(&this->actor));
    this->actionFunc = func_80A730A0;
}

void func_80A72CF8(EnDno* this, GlobalContext* globalCtx) {
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_DOOR_WARP1, this->actor.world.pos.x + 80.0f,
                       this->actor.floorHeight, this->actor.world.pos.z, 0, 0, 0, 0x201);
}

s32 func_80A72D8C(GlobalContext* globalCtx, ActorUnkStruct* arg1) {
    Actor* actor = arg1->unk_48;
    s32 pad;
    s32 ret = false;
    f32 sp38;
    s16 temp_v0;
    s32 temp_v0_2;
    s32 sp2C;

    actor->gravity = 0.0f;
    temp_v0 = actor->yawTowardsPlayer - actor->world.rot.y;
    if ((temp_v0 <= 0x4000) && (temp_v0 >= -0x4000)) {
        Math_SmoothStepToF(&actor->speedXZ, 15.0f, 0.8f, 1.0f, 0.01f);
    } else {
        if (actor->xzDistToPlayer <= 80.0f) {
            Math_SmoothStepToF(&actor->speedXZ, 8.0f, 0.5f, 0.5f, 0.01f);
        } else if (actor->xzDistToPlayer <= 360.0f) {
            Math_SmoothStepToF(&actor->speedXZ, 7.0f, 0.5f, 0.5f, 0.01f);
        } else {
            Math_SmoothStepToF(&actor->speedXZ, 3.5f, 0.5f, 0.5f, 0.01f);
        }
    }

    if (arg1->unk_50 < SQ(actor->speedXZ)) {
        ret = true;
    } else {
        sp38 = actor->speedXZ / sqrtf(arg1->unk_4C);
        sp2C = ABS(arg1->unk_54 - actor->world.rot.x);
        temp_v0_2 = sp2C;
        temp_v0_2 *= sp38;
        temp_v0_2 += 0x71C;
        sp2C = ABS(arg1->unk_56 - actor->world.rot.y);

        Math_ScaledStepToS(&actor->world.rot.x, arg1->unk_54, temp_v0_2);
        Math_ScaledStepToS(&actor->world.rot.y, arg1->unk_56, (s32)(sp2C * sp38) + 0x71C);
    }

    return ret;
}

s32 func_80A72FAC(GlobalContext* globalCtx, ActorUnkStruct* arg1) {
    Actor* actor = arg1->unk_48;
    EnDno* dno = (EnDno*)actor;
    f32 sp24 = Math_CosS(-actor->world.rot.x) * actor->speedXZ;
    f32 sp20 = gFramerateDivisorHalf;

    actor->velocity.x = Math_SinS(actor->world.rot.y) * sp24;
    actor->velocity.y = Math_SinS(-actor->world.rot.x) * actor->speedXZ;
    actor->velocity.z = Math_CosS(actor->world.rot.y) * sp24;

    dno->unk_334.x += (dno->actor.velocity.x * sp20) + dno->actor.colChkInfo.displacement.x;
    dno->unk_334.y += (dno->actor.velocity.y * sp20) + dno->actor.colChkInfo.displacement.y;
    dno->unk_334.z += (dno->actor.velocity.z * sp20) + dno->actor.colChkInfo.displacement.z;

    return 0;
}

void func_80A730A0(EnDno* this, GlobalContext* globalCtx) {
    f32 temp_f10;
    s32 phi_a2;

    if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount)) {
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
            func_8013E1C8(&this->skelAnime, D_80A739A0, phi_a2, &this->unk_32C);
        }
    }

    func_8013DE04(globalCtx, &this->unk_340, func_8013DF3C, func_80A72D8C, func_80A72FAC, func_8013E0A4);
    this->unk_45C += 6553;
    this->unk_340.unk_2C.x = 0.0f;
    this->unk_340.unk_2C.y = 0.0f;
    this->unk_340.unk_2C.z = 0.0f;
    Math_Vec3f_Copy(&this->actor.world.pos, &this->unk_334);
    temp_f10 = (4.0f + Math_SinS(this->unk_3AE)) * Math_SinS(this->unk_3AC);
    this->actor.world.pos.y += temp_f10;
    this->unk_3AC += 4500;
    this->unk_3AE += 1000;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    func_80A715DC(this, globalCtx);
    func_800B9010(&this->actor, 0x2153);
    if (this->unk_340.unk_1C & 0x20) {
        Math_Vec3f_Copy(&this->actor.world.pos, &this->unk_340.unk_20);
        this->actor.speedXZ = 0.0f;
        this->actor.velocity.x = 0.0f;
        this->actor.velocity.y = 0.0f;
        this->actor.velocity.z = 0.0f;
        func_80A73244(this, globalCtx);
    }
}

void func_80A73244(EnDno* this, GlobalContext* globalCtx) {
    this->actor.flags &= ~0x8000000;
    this->actor.flags |= (8 | 1);
    this->unk_328 = 2;
    this->actor.speedXZ = 0.0f;
    Actor_UnsetSwitchFlag(globalCtx, ENDNO_PARAMS_3F80(&this->actor));
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
            func_8013E1C8(&this->skelAnime, D_80A739A0, 7, &this->unk_32C);
        }
    } else if (this->unk_44E == 3) {
        if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount)) {
            func_8013E1C8(&this->skelAnime, D_80A739A0, 14, &this->unk_32C);
            func_80A72438(this, globalCtx);
        } else {
            if (this->skelAnime.animCurrentFrame >= 20.0f) {
                Math_SmoothStepToF(&this->unk_454, 0.0f, 1.0f, 0.125f, 0.01f);
            }

            if (func_801378B8(&this->skelAnime, 4.0f)) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EV_CLOSE_AMBRELLA);
                this->unk_452 = 4;
            } else if (func_801378B8(&this->skelAnime, 5.0f)) {
                this->unk_452 = 3;
            }
        }
    }
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void func_80A73408(EnDno* this, GlobalContext* globalCtx) {
    s32 phi_a2;
    u8 sp33 = true;
    u32 temp_v0;

    if (func_800EE29C(globalCtx, 0x1DB)) {
        temp_v0 = func_800EE200(globalCtx, 0x1DB);
        if (this->unk_468 != globalCtx->csCtx.npcActions[temp_v0]->unk0) {
            switch (globalCtx->csCtx.npcActions[temp_v0]->unk0) {
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
                func_8013E1C8(&this->skelAnime, D_80A739A0, phi_a2, &this->unk_32C);
            }
        }
        func_800EDF24(&this->actor, globalCtx, temp_v0);
    }

    if ((func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount)) && (this->unk_32C == 17)) {
        if (0) {};
        func_8013E1C8(&this->skelAnime, D_80A739A0, 18, &this->unk_32C);
    }
}

void EnDno_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnDno* this = THIS;
    s32 pad;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_80A73408(this, globalCtx);
    this->actionFunc(this, globalCtx);
    if (this->unk_3B0 & 4) {
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    }
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_SetHeight(&this->actor, 51.0f);
}

void EnDno_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnDno* this = THIS;

    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     func_80A7361C, func_80A73654, &this->actor);
}

s32 func_80A7361C(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnDno* this = THIS;

    *dList = NULL;
    if (limbIndex == 9) {
        rot->x += this->unk_466;
    }
    return 0;
}

void func_80A73654(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
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
            Matrix_Scale(this->unk_454, this->unk_454, this->unk_454, 1);
            SysMatrix_InsertXRotation_s(this->unk_45C, 1);
        }

        gfxOpa = POLY_OPA_DISP;
        gSPMatrix(gfxOpa, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxOpa + 1, *dList);

        POLY_OPA_DISP = gfxOpa + 2;
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }

    if ((this->unk_3B0 & 1) && (limbIndex == 26)) {
        u32 frames;

        OPEN_DISPS(globalCtx->state.gfxCtx);

        SysMatrix_StatePush();
        frames = globalCtx->gameplayFrames;
        SysMatrix_MultiplyVector3fByState(&D_80A73B40, &sp84);
        func_80A711D0(this, globalCtx, &sp84);
        SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);
        Matrix_Scale(0.15f, 0.15f, 1.0f, 1);
        SysMatrix_InsertTranslation(0.0f, -3200.0f, 0.0f, 1);
        gfxXlu = func_8012C2B4(POLY_XLU_DISP);

        gSPMatrix(gfxXlu, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(gfxXlu + 1, 0x08,
                   Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0, -frames * 20, 0x20, 0x80));
        gDPSetPrimColor(gfxXlu + 2, 0x80, 0x80, 255, 255, 0, 255);
        gDPSetEnvColor(gfxXlu + 3, 255, 0, 0, 0);
        gSPDisplayList(gfxXlu + 4, D_0407D590);

        POLY_XLU_DISP = gfxXlu + 5;

        SysMatrix_StatePop();

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
