/*
 * File: z_en_mm3.c
 * Overlay: ovl_En_Mm3
 * Description: Counting Game Postman
 */

#include "z_en_mm3.h"
#include "objects/object_mm/object_mm.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnMm3*)thisx)

void EnMm3_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMm3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMm3_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMm3_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A6F270(EnMm3* this);
void func_80A6F2C8(EnMm3* this, GlobalContext* globalCtx);
void func_80A6F9C8(EnMm3* this);
void func_80A6F9DC(EnMm3* this, GlobalContext* globalCtx);
void func_80A6FBA0(EnMm3* this);
void func_80A6FBFC(EnMm3* this, GlobalContext* globalCtx);
void func_80A6FE1C(EnMm3* this);
void func_80A6FE30(EnMm3* this, GlobalContext* globalCtx);
void func_80A6FED8(EnMm3* this);
void func_80A6FEEC(EnMm3* this, GlobalContext* globalCtx);
s32 func_80A6FFAC(EnMm3* this, GlobalContext* globalCtx);
void func_80A70084(EnMm3* this, GlobalContext* globalCtx);

const ActorInit En_Mm3_InitVars = {
    ACTOR_EN_MM3,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MM,
    sizeof(EnMm3),
    (ActorFunc)EnMm3_Init,
    (ActorFunc)EnMm3_Destroy,
    (ActorFunc)EnMm3_Update,
    (ActorFunc)EnMm3_Draw,
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
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 18, 63, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

static AnimationInfo sAnimations[] = {
    { &object_mm_Anim_002238, 1.0f, 0.0f, 0.0f, 0, -7.0f },  { &object_mm_Anim_00A4E0, -1.0f, 0.0f, 0.0f, 2, -7.0f },
    { &object_mm_Anim_00C640, 1.0f, 0.0f, 0.0f, 0, -7.0f },  { &object_mm_Anim_00A4E0, 1.0f, 0.0f, 0.0f, 2, -7.0f },
    { &object_mm_Anim_000468, 1.0f, 0.0f, 0.0f, 0, -7.0f },  { &object_mm_Anim_00CD90, 1.0f, 0.0f, 0.0f, 0, -12.0f },
    { &object_mm_Anim_00DA50, 1.0f, 0.0f, 0.0f, 0, -12.0f }, { &object_mm_Anim_00DA50, 1.0f, 0.0f, 10.0f, 2, -10.0f },
};

#include "overlays/ovl_En_Mm3/ovl_En_Mm3.c"

Vec3f D_80A704F0 = { 0.0f, 0.0f, 0.0f };

TexturePtr D_80A704FC[] = { object_mm_Tex_002950, object_mm_Tex_002750 };

void EnMm3_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnMm3* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 21.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_mm_Skel_0096E8, &object_mm_Anim_00A4E0, this->jointTable,
                       this->morphTable, 16);
    Animation_Change(&this->skelAnime, &object_mm_Anim_00A4E0, -1.0f, Animation_GetLastFrame(&object_mm_Anim_00A4E0),
                     0.0f, 2, 0.0f);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, NULL, &sColChkInfoInit);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    this->actor.parent = NULL;
    this->actor.targetMode = 0;
    this->unk_1DC = 1;
    this->unk_2B4 = 0;
    this->unk_2AE = 0;
    this->unk_2B0 &= ~1;
    this->actor.world.pos.y = this->actor.floorHeight;
    func_80A6F270(this);
}

void EnMm3_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnMm3* this = THIS;

    gSaveContext.save.weekEventReg[63] &= (u8)~1;
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

s32 func_80A6F22C(EnMm3* this) {
    s16 abs = BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y);

    abs = ABS_ALT(abs);
    if (abs < 0x4000) {
        return true;
    }
    return false;
}

void func_80A6F270(EnMm3* this) {
    this->unk_1DC = 1;
    this->unk_2B0 &= ~1;
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 5);
    this->actionFunc = func_80A6F2C8;
}

void func_80A6F2C8(EnMm3* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        Message_StartTextbox(globalCtx, 0x278A, &this->actor);
        this->unk_2B4 = 0x278A;
        func_80A6F9C8(this);
    } else if (func_80A6F22C(this)) {
        func_800B8614(&this->actor, globalCtx, 100.0f);
    }

    Math_SmoothStepToS(&this->unk_2A0.x, 0, 5, 0x1000, 0x100);
    Math_SmoothStepToS(&this->unk_2A0.y, 0, 5, 0x1000, 0x100);
    Math_SmoothStepToS(&this->unk_2A6.x, 0, 5, 0x1000, 0x100);
    Math_SmoothStepToS(&this->unk_2A6.y, 0, 5, 0x1000, 0x100);
}

void func_80A6F3B4(EnMm3* this, GlobalContext* globalCtx) {
    if (Message_ShouldAdvance(globalCtx)) {
        switch (this->unk_2B4) {
            case 0x278E:
                if (globalCtx->msgCtx.choiceIndex == 0) {
                    if (this->unk_2B2 & 0x20) {
                        if (gSaveContext.save.playerData.rupees >= globalCtx->msgCtx.unk1206C) {
                            func_8019F208();
                            Message_StartTextbox(globalCtx, 0x2790, &this->actor);
                            this->unk_2B4 = 0x2790;
                            func_801159EC(-globalCtx->msgCtx.unk1206C);
                        } else {
                            play_sound(NA_SE_SY_ERROR);
                            Message_StartTextbox(globalCtx, 0x279C, &this->actor);
                            this->unk_2B4 = 0x279C;
                            func_80151BB4(globalCtx, 0xB);
                        }
                    } else {
                        func_8019F208();
                        Message_StartTextbox(globalCtx, 0x2790, &this->actor);
                        this->unk_2B4 = 0x2790;
                    }
                } else {
                    func_8019F230();
                    Message_StartTextbox(globalCtx, 0x278F, &this->actor);
                    this->unk_2B4 = 0x278F;
                    func_80151BB4(globalCtx, 0xB);
                }
                break;

            case 0x279A:
                if (globalCtx->msgCtx.choiceIndex == 0) {
                    if (gSaveContext.save.playerData.rupees >= globalCtx->msgCtx.unk1206C) {
                        func_8019F208();
                        Message_StartTextbox(globalCtx, 0x2790, &this->actor);
                        this->unk_2B4 = 0x2790;
                        func_801159EC(-globalCtx->msgCtx.unk1206C);
                    } else {
                        play_sound(NA_SE_SY_ERROR);
                        Message_StartTextbox(globalCtx, 0x279C, &this->actor);
                        this->unk_2B4 = 0x279C;
                        func_80151BB4(globalCtx, 0xB);
                    }
                } else {
                    func_8019F230();
                    Message_StartTextbox(globalCtx, 0x279B, &this->actor);
                    this->unk_2B4 = 0x279B;
                    func_80151BB4(globalCtx, 0xB);
                }
                break;
        }
    }
}

void func_80A6F5E4(EnMm3* this, GlobalContext* globalCtx) {
    if (((this->unk_2B4 != 0x2791) || (this->unk_2AC == 0)) && Message_ShouldAdvance(globalCtx)) {
        switch (this->unk_2B4) {
            case 0x278A:
                if (func_80A6FFAC(this, globalCtx)) {
                    Message_StartTextbox(globalCtx, 0x279D, &this->actor);
                    this->unk_2B4 = 0x279D;
                } else {
                    func_80A70084(this, globalCtx);
                    if (Player_GetMask(globalCtx) == PLAYER_MASK_BUNNY) {
                        Message_StartTextbox(globalCtx, 0x27A0, &this->actor);
                        this->unk_2B4 = 0x27A0;
                    } else {
                        Message_StartTextbox(globalCtx, 0x278B, &this->actor);
                        this->unk_2B4 = 0x278B;
                    }
                }
                this->unk_1DC = 0;
                this->unk_2B0 |= 1;
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 7);
                break;

            case 0x278B:
            case 0x27A0:
                this->unk_2AE = 0;
                Message_StartTextbox(globalCtx, 0x278C, &this->actor);
                this->unk_2B4 = 0x278C;
                break;

            case 0x278C:
                Message_StartTextbox(globalCtx, 0x278D, &this->actor);
                this->unk_2B4 = 0x278D;
                break;

            case 0x279D:
                this->unk_2AE = 0;
                Message_StartTextbox(globalCtx, 0x279E, &this->actor);
                this->unk_2B4 = 0x279E;
                break;

            case 0x279E:
                this->unk_2B2 |= 0x20;
                Message_StartTextbox(globalCtx, 0x279F, &this->actor);
                this->unk_2B4 = 0x279F;
                break;

            case 0x278D:
            case 0x279F:
                Message_StartTextbox(globalCtx, 0x278E, &this->actor);
                this->unk_2B4 = 0x278E;
                break;

            case 0x2791:
                if (gSaveContext.unk_3DE0[0] == 1000) {
                    Message_StartTextbox(globalCtx, 0x2792, &this->actor);
                    this->unk_2B4 = 0x2792;
                } else if ((gSaveContext.unk_3DE0[0] >= 1500)) {
                    Message_StartTextbox(globalCtx, 0x2797, &this->actor);
                    this->unk_2B4 = 0x2797;
                } else if ((gSaveContext.unk_3DE0[0] <= 1050) && (gSaveContext.unk_3DE0[0] >= 950)) {
                    Message_StartTextbox(globalCtx, 0x2795, &this->actor);
                    this->unk_2B4 = 0x2795;
                } else {
                    Message_StartTextbox(globalCtx, 0x2796, &this->actor);
                    this->unk_2B4 = 0x2796;
                }
                break;

            case 0x2792:
                Message_StartTextbox(globalCtx, 0x2793, &this->actor);
                this->unk_2B4 = 0x2793;
                break;

            case 0x2793:
                func_801477B4(globalCtx);
                func_80A6FE1C(this);
                func_80A6FE30(this, globalCtx);
                break;

            case 0x2795:
            case 0x2796:
            case 0x2797:
                if (gSaveContext.save.weekEventReg[63] & 2) {
                    Message_StartTextbox(globalCtx, 0x279B, &this->actor);
                    this->unk_2B4 = 0x279B;
                    func_80151BB4(globalCtx, 0xB);
                } else {
                    Message_StartTextbox(globalCtx, 0x2798, &this->actor);
                    this->unk_2B4 = 0x2798;
                }
                break;

            case 0x2798:
                Message_StartTextbox(globalCtx, 0x2799, &this->actor);
                this->unk_2B4 = 0x2799;
                break;

            case 0x2799:
                Message_StartTextbox(globalCtx, 0x279A, &this->actor);
                this->unk_2B4 = 0x279A;
                break;
        }
    } else if ((this->unk_2AC > 0) && (this->unk_2B4 == 0x2791)) {
        this->unk_2AC--;
        if (this->unk_2AC == 0) {
            if (gSaveContext.unk_3DE0[0] == 1000) {
                func_801A3098(0x922);
            } else {
                play_sound(NA_SE_SY_ERROR);
            }
        }
    }
}

void func_80A6F9C8(EnMm3* this) {
    this->actionFunc = func_80A6F9DC;
}

void func_80A6F9DC(EnMm3* this, GlobalContext* globalCtx) {
    this->unk_2B0 &= ~2;

    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 0:
        case 1:
        case 2:
            break;

        case 3:
            this->unk_2B0 |= 2;
            break;

        case 4:
            func_80A6F3B4(this, globalCtx);
            break;

        case 5:
            func_80A6F5E4(this, globalCtx);
            break;

        case 6:
            if (Message_ShouldAdvance(globalCtx)) {
                if (this->unk_2B4 == 0x2790) {
                    Player* player = GET_PLAYER(globalCtx);

                    player->stateFlags1 |= 0x20;
                    if (Player_GetMask(globalCtx) == PLAYER_MASK_BUNNY) {
                        func_8010EA9C(0, 2);
                    } else {
                        func_8010EA9C(0, 0);
                    }
                    func_801477B4(globalCtx);
                    play_sound(NA_SE_SY_START_SHOT);
                    func_80A6FBA0(this);
                } else {
                    gSaveContext.save.weekEventReg[63] &= (u8)~1;
                    gSaveContext.save.weekEventReg[63] &= (u8)~2;
                    func_80A6F270(this);
                }
            }
            break;
    }

    if ((this->skelAnime.mode == 2) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
    }

    if (((this->unk_2B4 == 0x279D) || (this->unk_2B4 == 0x27A0) || (this->unk_2B4 == 0x278B)) &&
        Animation_OnFrame(&this->skelAnime, 8.0f) && (this->unk_2AE == 0)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_LIE_DOWN_ON_BED);
        this->unk_2AE = 1;
    }
}

void func_80A6FBA0(EnMm3* this) {
    func_801A5BD0(0x6F);
    func_801A0238(0, 5);
    gSaveContext.save.weekEventReg[63] |= 1;
    gSaveContext.save.weekEventReg[63] &= (u8)~2;
    this->actionFunc = func_80A6FBFC;
}

void func_80A6FBFC(EnMm3* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    OSTime a;
    OSTime b;

    if (gSaveContext.unk_3DD0[0] == 0x10) {
        player->stateFlags1 &= ~0x20;
        this->actor.flags |= ACTOR_FLAG_10000;
        if (gSaveContext.unk_3DE0[0] >= 0x5DD) {
            gSaveContext.unk_3DE0[0] = 0x5DC;
        } else {
            a = gSaveContext.unk_3DE0[0];
            if (a >= (OSTime)(995 - XREG(16))) {
                b = gSaveContext.unk_3DE0[0];
                if ((OSTime)(XREG(17) + 1005) >= b) {
                    gSaveContext.unk_3DE0[0] = 1000;
                }
            }
        }
    } else if (gSaveContext.unk_3DE0[0] >= 0x5DD) {
        gSaveContext.unk_3DD0[0] = 15;
        gSaveContext.unk_3DC8 = osGetTime();
    }

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        func_801A5BD0(0);
        func_801A0238(0x7F, 5);
        Message_StartTextbox(globalCtx, 0x2791, &this->actor);
        this->unk_2B4 = 0x2791;
        this->unk_2AC = 7;
        gSaveContext.unk_3DD0[0] = 0;
        this->actor.flags &= ~ACTOR_FLAG_10000;
        play_sound(NA_SE_SY_START_SHOT);
        func_80A6F9C8(this);
    } else {
        func_800B8614(&this->actor, globalCtx, this->actor.xzDistToPlayer + 10.0f);
        func_80123E90(globalCtx, &this->actor);
        if (Player_GetMask(globalCtx) == PLAYER_MASK_BUNNY) {
            play_sound(NA_SE_SY_STOPWATCH_TIMER_INF - SFX_FLAG);
        } else {
            play_sound(NA_SE_SY_STOPWATCH_TIMER_3 - SFX_FLAG);
        }
    }
}

void func_80A6FE1C(EnMm3* this) {
    this->actionFunc = func_80A6FE30;
}

void func_80A6FE30(EnMm3* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        if (!(gSaveContext.save.weekEventReg[77] & 1)) {
            gSaveContext.save.weekEventReg[77] |= 1;
        }
        this->actor.parent = NULL;
        func_80A6FED8(this);
    } else if (gSaveContext.save.weekEventReg[77] & 1) {
        Actor_PickUp(&this->actor, globalCtx, GI_RUPEE_PURPLE, 500.0f, 100.0f);
    } else {
        Actor_PickUp(&this->actor, globalCtx, GI_HEART_PIECE, 500.0f, 100.0f);
    }
}

void func_80A6FED8(EnMm3* this) {
    this->actionFunc = func_80A6FEEC;
}

void func_80A6FEEC(EnMm3* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        player->stateFlags1 &= ~0x20;
        Message_StartTextbox(globalCtx, 0x2794, &this->actor);
        this->unk_2B4 = 0x2794;
        func_80151BB4(globalCtx, 0xB);
        func_80151BB4(globalCtx, 0x2B);
        this->actor.flags &= ~ACTOR_FLAG_10000;
        func_80A6F9C8(this);
    } else {
        func_800B85E0(&this->actor, globalCtx, 200.0f, -1);
    }
}

s32 func_80A6FFAC(EnMm3* this, GlobalContext* globalCtx) {
    switch (gSaveContext.save.playerForm) {
        case 4:
            if (Player_GetMask(globalCtx) == PLAYER_MASK_BUNNY) {
                if (this->unk_2B2 & 0x10) {
                    return true;
                }
            } else if (this->unk_2B2 & 1) {
                return true;
            }
            break;

        case 3:
            if (this->unk_2B2 & 2) {
                return true;
            }
            break;

        case 2:
            if (this->unk_2B2 & 4) {
                return true;
            }
            break;

        case 1:
            if (this->unk_2B2 & 8) {
                return true;
            }
            break;
    }

    return false;
}

void func_80A70084(EnMm3* this, GlobalContext* globalCtx) {
    switch (gSaveContext.save.playerForm) {
        case 4:
            if (Player_GetMask(globalCtx) == PLAYER_MASK_BUNNY) {
                this->unk_2B2 |= 0x10;
                this->unk_2B2 |= 1;
            } else {
                this->unk_2B2 |= 1;
            }
            break;

        case 3:
            this->unk_2B2 |= 2;
            break;

        case 2:
            this->unk_2B2 |= 4;
            break;

        case 1:
            this->unk_2B2 |= 8;
            break;
    }
}

void EnMm3_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnMm3* this = THIS;

    this->actionFunc(this, globalCtx);

    SkelAnime_Update(&this->skelAnime);

    if (this->unk_2B0 & 1) {
        func_800E9250(globalCtx, &this->actor, &this->unk_2A0, &this->unk_2A6, this->actor.focus.pos);
    }

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

s32 EnMm3_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnMm3* this = THIS;

    if (limbIndex == 8) {
        rot->x += this->unk_2A6.y;
        rot->y -= this->unk_2A6.x;
    } else if (limbIndex == 15) {
        rot->x += this->unk_2A0.y;
        rot->z += this->unk_2A0.x;
        if ((this->unk_2B0 & 2) && ((globalCtx->gameplayFrames % 3) == 0)) {
            Matrix_InsertTranslation(40.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        }
    }
    return false;
}

void EnMm3_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnMm3* this = THIS;

    if (limbIndex == 15) {
        Matrix_MultiplyVector3fByState(&D_80A704F0, &this->actor.focus.pos);
    }
}

void EnMm3_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnMm3* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80A704FC[this->unk_1DC]));
    gSPSegment(POLY_OPA_DISP++, 0x0C, sEnMm3DL);

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnMm3_OverrideLimbDraw, EnMm3_PostLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
