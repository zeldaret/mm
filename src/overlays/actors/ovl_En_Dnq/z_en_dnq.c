/*
 * File: z_en_dnq.c
 * Overlay: ovl_En_Dnq
 * Description: Deku King
 *
 * This actor's name is probably short for "Dekunuts Queen". This is likely a misnamed actor,
 * since it uses assets from object_dno (probably short for "Dekunuts Ou (king)").
 */

#include "z_en_dnq.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnDnq*)thisx)

void EnDnq_Init(Actor* thisx, PlayState* play);
void EnDnq_Destroy(Actor* thisx, PlayState* play);
void EnDnq_Update(Actor* thisx, PlayState* play);
void EnDnq_Draw(Actor* thisx, PlayState* play);

void func_80A52FB8(EnDnq* this, PlayState* play);

static s32 D_80A53400[] = {
    0x00120100, 0x150E0899, 0x0C120F08, 0x9A0C0F08, 0x9B0C0F08, 0x9C0C1112, 0x01100E08, 0x980C1000, 0x00120200,
    0x0C0E089D, 0x0C0F089E, 0x0C111202, 0x100E089F, 0x0C100000, 0x0E08A10C, 0x0F08A20C, 0x10000000,
};

ActorInit En_Dnq_InitVars = {
    /**/ ACTOR_EN_DNQ,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_DNO,
    /**/ sizeof(EnDnq),
    /**/ EnDnq_Init,
    /**/ EnDnq_Destroy,
    /**/ EnDnq_Update,
    /**/ EnDnq_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT1,
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
    { 34, 80, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 1, 0, 0, 0, MASS_IMMOVABLE };

static AnimationInfoS sAnimationInfo[] = {
    { &gDekuKingIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gDekuKingIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuKingSurpriseAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gDekuKingJumpedOnStartAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gDekuKingJumpedOnLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuKingJumpedOnEndAnim, 0.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gDekuKingJumpedOnEndAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gDekuKingLyingDownTwitchAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuKingWailLoopAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gDekuKingFootStampStartAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gDekuKingFootStampLoopAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gDekuKingWailStartAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gDekuKingMarchAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gDekuKingSpinScepterAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gDekuKingIntimidateAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuKingPointScepterAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuKingJumpAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuKingLaughAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gDekuKingFootStampLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuKingLaughAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
};

s32 EnDnq_ValidatePictograph(PlayState* play, Actor* thisx) {
    return Snap_ValidatePictograph(play, thisx, PICTO_VALID_DEKU_KING, &thisx->focus.pos, &thisx->world.rot, 120.0f,
                                   480.0f, 0x38E3);
}

s32 func_80A5257C(EnDnq* this, s32 arg1) {
    s32 phi_v1 = false;
    s32 ret = false;

    if ((arg1 == 0) || (arg1 == 1)) {
        switch (this->unk_398) {
            case 0:
            case 1:
                break;

            default:
                phi_v1 = true;
                break;
        }
    } else if (arg1 != this->unk_398) {
        phi_v1 = true;
    }

    if (phi_v1) {
        this->unk_398 = arg1;
        ret = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, arg1);
    }

    return ret;
}

void func_80A52604(EnDnq* this, PlayState* play) {
    Collider_UpdateCylinder(&this->picto.actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

s32 func_80A52648(EnDnq* this, PlayState* play) {
    s32 ret = false;

    if (play->csCtx.state != CS_STATE_IDLE) {
        if (!(this->unk_37C & 0x20)) {
            this->picto.actor.flags &= ~ACTOR_FLAG_1;
            this->cueId = 255;
            this->unk_37C |= 0x20;
        }
        SubS_UpdateFlags(&this->unk_37C, 0, 7);
        ret = true;
    } else {
        if (this->unk_37C & 0x20) {
            this->picto.actor.flags |= ACTOR_FLAG_1;
            this->cueId = 255;
            this->unk_37C &= ~0x20;
            SubS_UpdateFlags(&this->unk_37C, 3, 7);
        }
    }

    return ret;
}

s32 func_80A526F8(EnDnq* this) {
    if (this->unk_386 == 0) {
        func_80A5257C(this, 8);
        this->unk_38C = ((s32)(Rand_ZeroOne() * 100.0f) % 4) + 3;
        this->unk_388 = 0;
        this->unk_386 = 1;
    } else if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        switch (this->unk_398) {
            case 8:
                if (DECR(this->unk_38C) == 0) {
                    func_80A5257C(this, 9);
                }
                break;

            case 9:
                func_80A5257C(this, 10);
                this->unk_38C = ((s32)(Rand_ZeroOne() * 100.0f) % 3) + 2;
                break;

            case 10:
                if (DECR(this->unk_38C) == 0) {
                    this->unk_388++;
                    if ((this->unk_38C != 0) || (this->unk_388 < 2)) {
                        func_80A5257C(this, 11);
                    } else {
                        func_80A5257C(this, 17);
                        this->unk_38C = 4;
                    }
                }
                break;

            case 11:
                func_80A5257C(this, 8);
                this->unk_38C = ((s32)(Rand_ZeroOne() * 100.0f) % 4) + 3;
                break;

            case 17:
                if (DECR(this->unk_38C) == 0) {
                    this->unk_386 = 0;
                }
                break;
        }

        if (this->unk_386 != 0) {
            this->skelAnime.curFrame = 0.0f;
        }
    }

    this->unk_38A = 0;
    return 0;
}

s32 func_80A52944(EnDnq* this) {
    s16 phi_v1 = 0;

    if (this->unk_386 == 0) {
        func_80A5257C(this, 12);
        this->unk_38C = 1;
        this->picto.actor.shape.rot.y = this->picto.actor.world.rot.y;
        this->unk_386 = 1;
        phi_v1 = this->unk_38C * 0x2000;
        this->picto.actor.shape.rot.y += phi_v1;
    } else if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        this->unk_386++;
        if (this->unk_386 >= 6) {
            func_80A5257C(this, 12);
            this->unk_386 = 1;
            phi_v1 = this->unk_38C * 0x2000;
        } else if (this->unk_386 <= 3) {
            this->unk_38C = -this->unk_38C;
            this->skelAnime.curFrame = 0.0f;
            phi_v1 = this->unk_38C * 0x2000;
        } else {
            func_80A5257C(this, 13);
            this->skelAnime.curFrame = 0.0f;
        }
        this->picto.actor.shape.rot.y = this->picto.actor.world.rot.y;
        this->picto.actor.shape.rot.y += phi_v1;
    }

    this->unk_38A = 0;
    return 0;
}

s32 func_80A52A78(EnDnq* this, PlayState* play) {
    static s32 D_80A535DC[] = {
        17, 12, 14, 13, 16,
    };

    if (this->unk_38A == 0) {
        this->unk_38C = 0;
        this->unk_38A = 1;
        this->unk_388 = play->state.frames % 5;
    }

    this->picto.actor.shape.rot.y = this->picto.actor.world.rot.y;
    if (this->unk_38C != 0) {
        this->unk_38C--;
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        if (this->unk_38C == 0) {
            this->unk_38C = Rand_S16Offset(20, 20);
            this->unk_388 += 3;
            this->unk_388 %= 5;
        }
        func_80A5257C(this, D_80A535DC[this->unk_388]);
        this->skelAnime.curFrame = 0.0f;
    }

    this->unk_386 = 0;
    return 0;
}

s32 func_80A52B68(EnDnq* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    u16 temp = play->msgCtx.currentTextId;

    if ((player->stateFlags1 & PLAYER_STATE1_40) && (player->talkActor == &this->picto.actor)) {
        switch (temp) {
            case 0x89B:
                func_80A5257C(this, 18);
                break;

            case 0x89E:
                func_80A5257C(this, 19);
                break;

            case 0x898:
            case 0x89F:
                func_80A5257C(this, 16);
                break;

            case 0x899:
            case 0x89D:
                func_80A5257C(this, 14);
                break;

            case 0x89A:
            case 0x89C:
                func_80A5257C(this, 15);
                break;
        }
        this->unk_39C = 1;
    } else if (this->unk_39C != 0) {
        func_80A5257C(this, 0);
        this->unk_39C = 0;
        this->unk_37E = 0;
        this->unk_386 = 0;
    }

    return 0;
}

void func_80A52C6C(EnDnq* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 pad;
    Vec3f sp34 = { 0.0f, 0.0f, 110.0f };
    Vec3f sp28;
    Vec3f sp1C;

    Math_Vec3f_Copy(&sp1C, &player->actor.world.pos);
    Lib_Vec3f_TranslateAndRotateY(&this->picto.actor.world.pos, this->picto.actor.world.rot.y, &sp34, &sp28);
    Math_Vec3f_Copy(&this->unk_370, &sp28);
    this->picto.actor.xzDistToPlayer = Math_Vec3f_DistXZ(&sp28, &sp1C);
}

s32* func_80A52CF8(EnDnq* this, PlayState* play) {
    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_23_20)) {
        return &D_80A53400[14];
    }

    if (this->unk_3A4 != 0) {
        return &D_80A53400[8];
    }

    return &D_80A53400[0];
}

s32 func_80A52D44(EnDnq* this, PlayState* play) {
    s32 ret = false;

    if ((this->unk_37C & 7) && Actor_ProcessTalkRequest(&this->picto.actor, &play->state)) {
        SubS_UpdateFlags(&this->unk_37C, 0, 7);
        this->unk_380 = func_80A52CF8(this, play);
        this->actionFunc = func_80A52FB8;
        ret = true;
    }

    return ret;
}

void func_80A52DC8(EnDnq* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 yaw = this->picto.actor.yawTowardsPlayer - this->picto.actor.world.rot.y;

    if (yaw <= 0x3800) {
        SubS_UpdateFlags(&this->unk_37C, 3, 7);
    } else {
        SubS_UpdateFlags(&this->unk_37C, 0, 7);
    }

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_23_20)) {
        this->unk_390 = 70.0f;
        if (Inventory_HasItemInBottle(ITEM_DEKU_PRINCESS) && !Play_InCsMode(play) &&
            (Message_GetState(&play->msgCtx) == TEXT_STATE_NONE) && (CutsceneManager_GetCurrentCsId() == CS_ID_NONE)) {
            if ((DECR(this->unk_384) == 0) && CHECK_WEEKEVENTREG(WEEKEVENTREG_29_40)) {
                Message_StartTextbox(play, 0x969, NULL);
                this->unk_384 = 200;
            }
        }

        this->unk_394 = this->picto.actor.xzDistToPlayer;
        func_80A52C6C(this, play);
        if (this->picto.actor.xzDistToPlayer < this->unk_390) {
            player->unk_B2B = 0x1A;
        }

        this->picto.actor.xzDistToPlayer = this->unk_394;

        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_83_08)) {
            func_80A52A78(this, play);
        } else if (this->unk_3A4 == 0) {
            Math_ApproachS(&this->picto.actor.shape.rot.y, this->picto.actor.world.rot.y, 3, 0x2AA8);
            func_80A526F8(this);
        } else {
            func_80A52944(this);
        }
    } else {
        Math_ApproachS(&this->picto.actor.shape.rot.y, this->picto.actor.world.rot.y, 3, 0x2AA8);
        this->unk_390 = 70.0f;
    }
}

void func_80A52FB8(EnDnq* this, PlayState* play) {
    s16 sp2E = this->picto.actor.yawTowardsPlayer;

    if (func_8010BF58(&this->picto.actor, play, this->unk_380, NULL, &this->unk_1E0)) {
        SubS_UpdateFlags(&this->unk_37C, 3, 7);
        this->unk_386 = 0;
        this->actionFunc = func_80A52DC8;
    } else {
        Math_ApproachS(&this->picto.actor.shape.rot.y, sp2E, 3, 0x2AA8);
    }
}

void func_80A53038(EnDnq* this, PlayState* play) {
    static s32 D_80A535FC[] = {
        0, 1, 2, 3, 5, 6,
    };
    s32 cueChannel;
    u32 cueId;

    if (Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_105)) {
        cueChannel = Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_105);
        cueId = play->csCtx.actorCues[cueChannel]->id;
        if (this->cueId != (u8)cueId) {
            func_80A5257C(this, D_80A535FC[cueId]);
            this->cueId = cueId;
        }

        if ((this->unk_398 == 4) && Animation_OnFrame(&this->skelAnime, 2.0f)) {
            Actor_PlaySfx(&this->picto.actor, NA_SE_EN_KINGNUTS_DAMAGE);
        }

        if (((this->unk_398 == 3) || (this->unk_398 == 6)) &&
            Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            func_80A5257C(this, this->unk_398 + 1);
        }

        Cutscene_ActorTranslateAndYaw(&this->picto.actor, play, cueChannel);
    }
}

void EnDnq_Init(Actor* thisx, PlayState* play) {
    EnDnq* this = THIS;

    ActorShape_Init(&this->picto.actor.shape, 0.0f, NULL, 14.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gDekuKingSkel, NULL, this->jointTable, this->morphTable,
                       DEKU_KING_LIMB_MAX);
    this->unk_398 = -1;
    func_80A5257C(this, 0);
    Collider_InitAndSetCylinder(play, &this->collider, &this->picto.actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->picto.actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    Actor_SetScale(&this->picto.actor, 0.02f);
    this->picto.actor.targetMode = 1;
    this->unk_386 = 0;
    this->unk_37C = 0;
    SubS_UpdateFlags(&this->unk_37C, 3, 7);
    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_09_80)) {
        this->unk_3A4 = 1;
    } else {
        this->unk_3A4 = 0;
    }
    this->picto.validationFunc = EnDnq_ValidatePictograph;
    this->actionFunc = func_80A52DC8;
}

void EnDnq_Destroy(Actor* thisx, PlayState* play) {
    EnDnq* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnDnq_Update(Actor* thisx, PlayState* play) {
    EnDnq* this = THIS;

    if (!func_80A52D44(this, play) && func_80A52648(this, play)) {
        func_80A53038(this, play);
        SkelAnime_Update(&this->skelAnime);
    } else {
        this->actionFunc(this, play);
        func_80A52B68(this, play);
        SkelAnime_Update(&this->skelAnime);
        Actor_UpdateBgCheckInfo(play, &this->picto.actor, 30.0f, 12.0f, 0.0f, UPDBGCHECKINFO_FLAG_4);
        this->unk_394 = this->picto.actor.xzDistToPlayer;
        func_80A52C6C(this, play);
        func_8013C964(&this->picto.actor, play, this->unk_390, fabsf(this->picto.actor.playerHeightRel) + 1.0f,
                      PLAYER_IA_NONE, this->unk_37C & 7);
        this->picto.actor.xzDistToPlayer = this->unk_394;
        Actor_SetFocus(&this->picto.actor, 46.0f);
        func_80A52604(this, play);
    }
}

void EnDnq_Draw(Actor* thisx, PlayState* play) {
    EnDnq* this = THIS;

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, NULL,
                          NULL, &this->picto.actor);
}
