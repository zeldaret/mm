/*
 * File: z_en_zov.c
 * Overlay: ovl_En_Zov
 * Description: Zora Vocalist - Lulu
 */

#include "z_en_zov.h"
#include "objects/object_zov/object_zov.h"
#include "overlays/actors/ovl_En_Elf/z_en_elf.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnZov*)thisx)

void EnZov_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZov_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZov_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZov_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BD1570(EnZov* this, s16 index, u8 mode);
void func_80BD187C(EnZov* this, GlobalContext* globalCtx);
void func_80BD19FC(EnZov* this, GlobalContext* globalCtx);
void func_80BD1BF0(EnZov* this, GlobalContext* globalCtx);
void func_80BD1C38(EnZov* this, GlobalContext* globalCtx);
void func_80BD1C84(EnZov* this, GlobalContext* globalCtx);
void func_80BD1D94(EnZov* this, GlobalContext* globalCtx);
void func_80BD1DB8(EnZov* this, GlobalContext* globalCtx);
void func_80BD1F1C(EnZov* this, GlobalContext* globalCtx);
s32 func_80BD1FC8(GlobalContext* globalCtx, EnZov* this);

const ActorInit En_Zov_InitVars = {
    ACTOR_EN_ZOV,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZOV,
    sizeof(EnZov),
    (ActorFunc)EnZov_Init,
    (ActorFunc)EnZov_Destroy,
    (ActorFunc)EnZov_Update,
    (ActorFunc)EnZov_Draw,
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

static AnimationHeader* D_80BD270C[] = {
    &object_zov_Anim_00D3EC, &object_zov_Anim_008120, &object_zov_Anim_00B4CC, &object_zov_Anim_00A888,
    &object_zov_Anim_00C510, &object_zov_Anim_00CAA8, &object_zov_Anim_008120, &object_zov_Anim_00A888,
    &object_zov_Anim_002B5C, &object_zov_Anim_00418C, &object_zov_Anim_005A6C, &object_zov_Anim_0066A4,
    &object_zov_Anim_0017D4, &object_zov_Anim_0023F4,
};

static Vec3f D_80BD2744 = { 400.0f, 600.0f, 0.0f };

static Vec3f D_80BD2750 = { 400.0f, 600.0f, 0.0f };

static TexturePtr D_80BD275C[] = { object_zov_Tex_013C38, object_zov_Tex_015138, object_zov_Tex_014138 };

static TexturePtr D_80BD2768[] = { object_zov_Tex_0135F8, object_zov_Tex_014538 };

static s8 D_80BD2770[] = {
    1, 2, 1, 0, 0, 1, 2, 1,
};

void EnZov_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnZov* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    Actor_SetScale(&this->actor, 0.01f);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_zov_Skel_016258, &object_zov_Anim_00D3EC, this->jontTable,
                       this->morphTable, 23);
    Animation_PlayLoop(&this->skelAnime, &object_zov_Anim_00D3EC);

    this->unk_320 = 0;
    this->unk_32C = -1;
    this->unk_326 = -1;
    this->unk_328[0] = this->actor.cutscene;
    this->unk_328[1] = 0x7C;
    this->unk_322 = 0;
    this->actionFunc = func_80BD1C84;
    this->unk_144 = func_80BD1FC8;

    Math_Vec3f_Copy(&this->unk_2FC, &this->actor.world.pos);
    Math_Vec3f_Copy(&this->unk_308, &this->actor.world.pos);
    Math_Vec3f_Copy(&this->unk_314, &this->actor.world.pos);

    switch (ENZOV_GET_F(&this->actor)) {
        case ENZOV_F_1:
            this->actionFunc = func_80BD1F1C;
            func_80BD1570(this, 9, 0);
            if (!(gSaveContext.save.weekEventReg[55] & 0x80)) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            break;

        case ENZOV_F_2:
            this->actionFunc = func_80BD1C38;
            this->actor.shape.shadowDraw = NULL;
            break;

        default:
            this->unk_320 |= 2;
            if ((gSaveContext.save.weekEventReg[55] & 0x80) || (gSaveContext.save.weekEventReg[53] & 0x20)) {
                Actor_MarkForDeath(&this->actor);
            }
            break;
    }
}

void EnZov_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnZov* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80BD13DC(EnZov* this) {
    if (this->unk_32C != -1) {
        if (ActorCutscene_GetCurrentIndex() == this->unk_328[this->unk_32C]) {
            ActorCutscene_Stop(this->unk_328[this->unk_32C]);
        }
        this->unk_32C = -1;
    }
}

void func_80BD1440(EnZov* this, s16 arg1) {
    func_80BD13DC(this);
    this->unk_32C = arg1;
}

void func_80BD1470(EnZov* this, s16 index, u8 mode, f32 transitionRate) {
    f32 frame;

    if (((index != this->unk_322) || mode) && (index >= 0) && (index < ARRAY_COUNT(D_80BD270C))) {
        switch (index) {
            case 6:
                frame = 30.0f;
                break;

            case 7:
                frame = 57.0f;
                break;

            default:
                frame = 0.0f;
                break;
        }
        Animation_Change(&this->skelAnime, D_80BD270C[index], 1.0f, frame, Animation_GetLastFrame(D_80BD270C[index]),
                         mode, transitionRate);
        this->unk_322 = index;
    }
}

void func_80BD1570(EnZov* this, s16 index, u8 mode) {
    func_80BD1470(this, index, mode, 5.0f);
}

s32 func_80BD15A4(EnZov* this, GlobalContext* globalCtx) {
    if ((this->actor.xzDistToPlayer < 100.0f) && Player_IsFacingActor(&this->actor, 0x3000, globalCtx) &&
        Actor_IsFacingPlayer(&this->actor, 0x3000)) {
        return true;
    }
    return false;
}

void func_80BD160C(EnZov* this, GlobalContext* globalCtx) {
    s32 textId = 0;

    if (gSaveContext.save.weekEventReg[53] & 0x20) {
        this->unk_320 &= ~2;
        if (gSaveContext.save.playerForm != PLAYER_FORM_ZORA) {
            textId = 0x1024;
            if ((this->unk_322 == 0) || (this->unk_322 == 4)) {
                func_80BD1570(this, 4, 2);
            } else {
                func_80BD1570(this, 6, 2);
            }
        } else if (this->unk_320 & 4) {
            textId = 0x1023;
        } else {
            textId = 0x1022;
            this->unk_320 |= 4;
            func_80BD1570(this, 3, 2);
        }
    } else if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
        func_80BD1570(this, 2, 2);
        this->actionFunc = func_80BD19FC;
        this->unk_324 = 10;
        func_80BD1440(this, 0);
    } else {
        textId = 0x1020;
        func_80BD1570(this, 5, 2);
    }

    this->unk_320 |= 1;
    if (textId != 0) {
        Message_StartTextbox(globalCtx, textId, &this->actor);
    }
}

void func_80BD1764(EnZov* this) {
    if (SkelAnime_Update(&this->skelAnime)) {
        switch (this->unk_322) {
            case 1:
            case 6:
                func_80BD1570(this, 6, 2);
                break;

            case 3:
            case 7:
                func_80BD1570(this, 7, 2);
                break;

            case 4:
                func_80BD1570(this, 0, 0);
                break;

            case 8:
                func_80BD1570(this, 9, 0);
                break;

            case 10:
                func_80BD1570(this, 11, 0);
                break;

            case 12:
                func_80BD1570(this, 13, 0);
                break;

            default:
                func_80BD1570(this, 0, 0);
                this->unk_320 &= ~1;
                break;
        }

        SkelAnime_Update(&this->skelAnime);
    }
}

void func_80BD187C(EnZov* this, GlobalContext* globalCtx) {
    func_80BD1764(this);

    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 5:
            if (Message_ShouldAdvance(globalCtx)) {
                switch (globalCtx->msgCtx.currentTextId) {
                    case 0x1022:
                        func_80151938(globalCtx, 0x1023);
                        break;

                    case 0x1023:
                        if ((this->unk_322 != 6) && (this->unk_322 != 1)) {
                            func_80BD1570(this, 1, 2);
                        }
                        func_801477B4(globalCtx);
                        this->actionFunc = func_80BD1C84;
                        break;

                    case 0x1024:
                        if (this->unk_322 != 6) {
                            func_80BD1570(this, 0, 0);
                        }
                        func_801477B4(globalCtx);
                        this->actionFunc = func_80BD1C84;
                        break;

                    default:
                        this->unk_320 &= ~1;
                        func_80BD1570(this, 0, 0);
                        func_801477B4(globalCtx);
                        this->actionFunc = func_80BD1C84;
                        break;
                }
            }
            break;

        case 2:
            func_801477B4(globalCtx);
            this->actionFunc = func_80BD1C84;
            this->unk_320 &= ~1;
            func_80BD1570(this, 0, 0);
            break;
    }
}

void func_80BD19FC(EnZov* this, GlobalContext* globalCtx) {
    func_80BD1764(this);
    if (this->unk_322 == 0) {
        if (!(this->unk_320 & 2)) {
            this->unk_320 |= 2;
            this->unk_2EE = 3;
        }

        if (this->unk_324 > 0) {
            this->unk_324--;
        } else {
            func_80BD13DC(this);
            Message_StartTextbox(globalCtx, 0x1021, &this->actor);
            ((EnElf*)(GET_PLAYER(globalCtx)->tatlActor))->unk_264 |= 4;
            Actor_ChangeFocus(&this->actor, globalCtx, GET_PLAYER(globalCtx)->tatlActor);
            this->actionFunc = func_80BD187C;
        }
    } else if (Animation_OnFrame(&this->skelAnime, 10.0f)) {
        this->unk_320 &= ~2;
        this->unk_2EE = 3;
    }
}

s32 func_80BD1AE0(EnZov* this, GlobalContext* globalCtx) {
    func_80BD1764(this);

    if (Cutscene_CheckActorAction(globalCtx, 504)) {
        s16 action = globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 504)]->action;

        if (action != this->unk_326) {
            this->unk_326 = action;
            switch (this->unk_326) {
                case 1:
                    func_80BD1570(this, 0, 0);
                    break;

                case 2:
                    func_80BD1570(this, 8, 2);
                    this->unk_320 |= 0x10;
                    break;

                case 3:
                    func_80BD1470(this, 10, 2, 0.0f);
                    break;

                case 4:
                    func_80BD1570(this, 12, 2);
                    break;
            }
        }
        return true;
    }

    return false;
}

void func_80BD1BF0(EnZov* this, GlobalContext* globalCtx) {
    if (!func_80BD1AE0(this, globalCtx)) {
        func_80BD1570(this, 0, 0);
        this->actionFunc = func_80BD1C84;
    }
}

void func_80BD1C38(EnZov* this, GlobalContext* globalCtx) {
    if (func_80BD1AE0(this, globalCtx)) {
        Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, Cutscene_GetActorActionIndex(globalCtx, 504));
    }
}

void func_80BD1C84(EnZov* this, GlobalContext* globalCtx) {
    func_80BD1764(this);

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80BD187C;
        func_80BD160C(this, globalCtx);
    } else if (func_80BD15A4(this, globalCtx)) {
        func_800B8614(&this->actor, globalCtx, 120.0f);
    }

    if (Cutscene_CheckActorAction(globalCtx, 0x1F8)) {
        this->actionFunc = func_80BD1BF0;
        func_80BD1BF0(this, globalCtx);
    }
}

void func_80BD1D30(EnZov* this, GlobalContext* globalCtx) {
    u16 textId;

    if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
        if (gSaveContext.save.weekEventReg[79] & 1) {
            textId = 0x1032;
        } else {
            textId = 0x1033;
        }
    } else {
        textId = 0x1031;
    }
    Message_StartTextbox(globalCtx, textId, &this->actor);
}

void func_80BD1D94(EnZov* this, GlobalContext* globalCtx) {
    func_80BD1764(this);
}

void func_80BD1DB8(EnZov* this, GlobalContext* globalCtx) {
    func_80BD1764(this);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0x1000, 0x200);
    this->actor.world.rot.y = this->actor.shape.rot.y;

    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        switch (globalCtx->msgCtx.currentTextId) {
            case 0x1033:
            case 0x1034:
            case 0x1035:
            case 0x1036:
            case 0x1037:
            case 0x1038:
                func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                break;

            case 0x1039:
                globalCtx->nextEntranceIndex = globalCtx->setupExitList[ENZOV_GET_FE00(&this->actor)];
                globalCtx->unk_1887F = 5;
                globalCtx->sceneLoadFlag = 0x14;
                gSaveContext.save.weekEventReg[78] |= 1;
                this->actionFunc = func_80BD1D94;
                globalCtx->msgCtx.unk11F10 = 0;
                Audio_QueueSeqCmd(0x101400FF);
                break;

            default:
                func_801477B4(globalCtx);
                this->actionFunc = func_80BD1F1C;
                break;
        }
    }
}

void func_80BD1F1C(EnZov* this, GlobalContext* globalCtx) {
    func_80BD1764(this);

    if (this->actor.home.rot.y != this->actor.shape.rot.y) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 2, 0x1000, 0x200);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80BD1DB8;
        func_80BD1D30(this, globalCtx);
    } else if (func_80BD15A4(this, globalCtx)) {
        func_800B8614(&this->actor, globalCtx, 120.0f);
    }
}

s32 func_80BD1FC8(GlobalContext* globalCtx, EnZov* this) {
    s32 ret;
    s32 pad;

    ret = func_8013A530(globalCtx, &this->actor, 4, &this->actor.focus.pos, &this->actor.shape.rot, 10.0f, 300.0f, -1);
    ret |= func_8013A530(globalCtx, &this->actor, 5, &this->unk_308, &this->actor.shape.rot, 50.0f, 160.0f, 0x3000);
    ret |= func_8013A530(globalCtx, &this->actor, 6, &this->unk_314, &this->actor.shape.rot, 50.0f, 160.0f, 0x3000);
    return ret;
}

void EnZov_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnZov* this = THIS;

    Actor_MoveWithGravity(&this->actor);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 10.0f, 10.0f, 10.0f, 4);

    this->actionFunc(this, globalCtx);

    if (!Cutscene_CheckActorAction(globalCtx, 0x1F8)) {
        this->unk_320 &= ~0x10;
    }

    if ((this->unk_320 & 1) && func_80BD15A4(this, globalCtx)) {
        func_800E9250(globalCtx, &this->actor, &this->unk_2F0, &this->unk_2F6, this->actor.focus.pos);
    } else {
        if ((this->unk_320 & 0x10) && (this->unk_322 == 0)) {
            Math_SmoothStepToS(&this->unk_2F0.x, -0x1B58, 6, 0x1838, 0x64);
        } else {
            Math_SmoothStepToS(&this->unk_2F0.x, 0, 6, 0x1838, 0x64);
        }
        Math_SmoothStepToS(&this->unk_2F0.y, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->unk_2F6.x, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->unk_2F6.y, 0, 6, 0x1838, 0x64);
    }

    if (DECR(this->unk_2EE) == 0) {
        this->unk_2EE = Rand_S16Offset(60, 60);
    }

    this->unk_2EC = this->unk_2EE;
    if (this->unk_2EC >= 3) {
        this->unk_2EC = 0;
    }

    if ((this->unk_32C != -1) && (ActorCutscene_GetCurrentIndex() != this->unk_328[this->unk_32C])) {
        if ((this->unk_32C == 0) && (ActorCutscene_GetCurrentIndex() == 0x7C)) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->unk_328[this->unk_32C]);
        } else if (ActorCutscene_GetCanPlayNext(this->unk_328[this->unk_32C])) {
            ActorCutscene_Start(this->unk_328[this->unk_32C], &this->actor);
        } else {
            ActorCutscene_SetIntentToPlay(this->unk_328[this->unk_32C]);
        }
    }
}

s32 EnZov_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnZov* this = THIS;

    if (limbIndex == 12) {
        rot->x += this->unk_2F0.y;
        if ((this->unk_320 & 0x10) && (this->unk_322 == 0)) {
            rot->z += this->unk_2F0.x;
        }
    }

    if (limbIndex == 11) {
        rot->x += this->unk_2F6.y;
    }
    return false;
}

void EnZov_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnZov* this = THIS;

    if (limbIndex == 12) {
        Matrix_MultiplyVector3fByState(&D_80BD2744, &this->actor.focus.pos);
        Math_Vec3f_Copy(&this->unk_2FC, &this->actor.focus.pos);
        this->unk_2FC.y += 10.0f;
    }

    if (limbIndex == 18) {
        Matrix_MultiplyVector3fByState(&D_80BD2750, &this->unk_308);
    }

    if (limbIndex == 13) {
        Matrix_MultiplyVector3fByState(&D_80BD2750, &this->unk_314);
    }
}

void EnZov_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnZov* this = THIS;
    Gfx* gfx;
    s32 curFrame;
    s32 phi_a1;
    u8 phi_v1;

    if (1) {}

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    phi_a1 = 0;
    curFrame = this->skelAnime.curFrame;
    phi_v1 = this->unk_2EC;

    switch (this->unk_322) {
        case 0:
            if ((this->unk_2EC == 0) && !(this->unk_320 & 0x10)) {
                phi_v1 = 1;
            }
            break;

        case 5:
            if (this->unk_2EC == 0) {
                phi_v1 = 1;
            }
            break;

        case 2:
            if (curFrame < 23) {
                phi_v1 = 0;
            } else if (curFrame >= 26) {
                phi_v1 = 1;
            } else if (curFrame == 24) {
                phi_v1 = 0;
            } else {
                phi_v1 = 1;
            }
            break;

        case 3:
        case 7:
            if (curFrame <= 50) {
                if (curFrame < 43) {
                    phi_v1 = 0;
                } else {
                    phi_v1 = D_80BD2770[(curFrame - 43) & 3];
                }
            }
            phi_a1 = 1;
            break;

        case 4:
            if ((curFrame < 14) || (curFrame >= 24)) {
                phi_v1 = 1;
            } else {
                phi_v1 = D_80BD2770[4 + ((curFrame - 14) & 3)];
            }
            phi_a1 = 1;
            break;

        case 8:
            phi_v1 = 0;
            break;

        case 9:
            phi_v1 = 0;
            phi_a1 = 1;
            break;
    }

    gfx = POLY_OPA_DISP;
    gSPSegment(&gfx[0], 0x09, Lib_SegmentedToVirtual(D_80BD275C[phi_v1]));
    gSPSegment(&gfx[1], 0x08, Lib_SegmentedToVirtual(D_80BD2768[phi_a1]));
    POLY_OPA_DISP = &gfx[2];

    CLOSE_DISPS(globalCtx->state.gfxCtx);

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnZov_OverrideLimbDraw, EnZov_PostLimbDraw, &this->actor);
}
