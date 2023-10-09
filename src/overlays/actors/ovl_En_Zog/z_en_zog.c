/*
 * File: z_en_zog.c
 * Overlay: ovl_En_Zog
 * Description: Mikau
 */

#include "z_en_zog.h"
#include "objects/object_zog/object_zog.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY)

#define THIS ((EnZog*)thisx)

void EnZog_Init(Actor* thisx, PlayState* play);
void EnZog_Destroy(Actor* thisx, PlayState* play);
void EnZog_Update(Actor* thisx, PlayState* play);
void EnZog_Draw(Actor* thisx, PlayState* play);

void func_80B943A0(EnZog* this, PlayState* play);
void func_80B943C0(EnZog* this, PlayState* play);
void func_80B94470(EnZog* this, PlayState* play);
void func_80B9451C(EnZog* this, PlayState* play);
void func_80B9461C(EnZog* this, PlayState* play);
void func_80B946B4(EnZog* this, PlayState* play);
void func_80B946FC(EnZog* this, PlayState* play);
void func_80B948A8(EnZog* this, PlayState* play);
void func_80B94A00(EnZog* this, PlayState* play);
void func_80B94C5C(EnZog* this, PlayState* play);
void func_80B94D0C(EnZog* this, PlayState* play);
void func_80B94E34(EnZog* this, PlayState* play);
void func_80B95128(EnZog* this, PlayState* play);
void func_80B95240(EnZog* this, PlayState* play);

static u8 D_80B95E10;

ActorInit En_Zog_InitVars = {
    /**/ ACTOR_EN_ZOG,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_ZOG,
    /**/ sizeof(EnZog),
    /**/ EnZog_Init,
    /**/ EnZog_Destroy,
    /**/ EnZog_Update,
    /**/ EnZog_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_PLAYER,
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
    { 30, 40, 0, { 0, 0, 0 } },
};

static TexturePtr D_80B958AC[] = { object_zog_Tex_024750, object_zog_Tex_024F50, object_zog_Tex_025750 };

static TexturePtr D_80B958B8[] = { object_zog_Tex_025F50, object_zog_Tex_026750 };

static AnimationHeader* D_80B958C0[] = {
    &object_zog_Anim_00FC0C, &object_zog_Anim_0106B0, &object_zog_Anim_0166F4, &object_zog_Anim_017170,
    &object_zog_Anim_014B10, &object_zog_Anim_018600, &object_zog_Anim_01A06C,
};

static AnimationHeader* D_80B958DC[] = { &object_zog_Anim_00CA94, &object_zog_Anim_00F110 };

static AnimationHeader* D_80B958E4[] = { &object_zog_Anim_01579C, &object_zog_Anim_015B80, &object_zog_Anim_00ECBC };

static AnimationHeader* D_80B958F0[] = { &object_zog_Anim_008EB8, &object_zog_Anim_0099A4 };

static AnimationHeader* D_80B958F8[] = { &object_zog_Anim_00931C, &object_zog_Anim_009EC4, &object_zog_Anim_00B01C };

static AnimationHeader* D_80B95904[] = {
    &object_zog_Anim_00BF38, &object_zog_Anim_01A990, &object_zog_Anim_01AD58,
    &object_zog_Anim_01B72C, &object_zog_Anim_01BC88,
};

static AnimationHeader* D_80B95918 = &object_zog_Anim_001000;

static AnimationHeader* D_80B9591C = &object_zog_Anim_001970;

static AnimationHeader* D_80B95920 = &object_zog_Anim_002344;

static AnimationHeader* D_80B95924 = &object_zog_Anim_002894;

static AnimationHeader* D_80B95928 = &object_zog_Anim_0030E0;

static AnimationHeader* D_80B9592C = &object_zog_Anim_0037F8;

static AnimationHeader* D_80B95930 = &object_zog_Anim_0041D0;

static AnimationHeader* D_80B95934 = &object_zog_Anim_004BDC;

static AnimationHeader* D_80B95938 = &object_zog_Anim_0055B4;

static s16 D_80B9593C[] = { 0, 1, 2, 3 };

static s16 D_80B95944[] = { 4, 5 };

static s16 D_80B95948[] = { 5, 6, 7, 0 };

static s16 D_80B95950[] = { 7, 8, 9, 10, 7, 11, 12, 13, 14, 15, 12, 13, 14, 15, 12, 16, 17, 0 };

static s16* D_80B95974[] = { D_80B9593C, D_80B95944, D_80B95948, D_80B95950 };

static s16 D_80B95984[] = { 4, 2, 3, 17 };

static Vec3f D_80B9598C = { 0.0f, -0.05f, 0.0f };

static Vec3f D_80B95998 = { 0.0f, -0.025f, 0.0f };

static Color_RGBA8 D_80B959A4 = { 220, 220, 255, 255 };

static Color_RGBA8 D_80B959A8 = { 80, 80, 220, 255 };

static Vec3f D_80B959AC = { 0.0f, 0.0f, 15.0f };

void func_80B93310(Actor* thisx, Lights* mapper, PlayState* play) {
    Vec3f sp34;
    EnZog* this = THIS;
    f32 sp2C;

    if (this->unk_322 > 0) {
        if (this->unk_30A & 8) {
            this->actor.shape.shadowAlpha = this->unk_322;
        } else {
            this->actor.shape.shadowAlpha = 255;
        }

        Math_Vec3f_Copy(&sp34, &this->actor.world.pos);

        sp2C = sqrtf(SQ(this->actor.focus.pos.x - this->unk_2F0.x) + SQ(this->actor.focus.pos.z - this->unk_2F0.z));
        if (sp2C < 12.0f) {
            sp2C = 12.0f;
        } else if (sp2C > 60.0f) {
            sp2C = 60.0f;
        }

        Math_Vec3f_Copy(&this->actor.world.pos, &this->unk_2F0);
        func_800B4AEC(play, &this->actor, 50.0f);
        if (sp34.y < this->actor.floorHeight) {
            this->actor.world.pos.y = this->actor.floorHeight;
        } else {
            this->actor.world.pos.y = sp34.y;
        }
        this->actor.scale.z *= sp2C * (1 / 12.0f);
        ActorShadow_DrawCircle(&this->actor, mapper, play);
        this->actor.scale.z = this->actor.scale.x;
        Math_Vec3f_Copy(&this->actor.world.pos, &sp34);
    }
}

void func_80B93468(EnZog* this, PlayState* play) {
    Vec3s* points;

    this->unk_2E8 = &play->setupPathList[ENZOG_GET_FC00(&this->actor)];
    if (this->unk_2E8 != NULL) {
        points = &((Vec3s*)Lib_SegmentedToVirtual(this->unk_2E8->points))[this->unk_2EC];
        points++;

        this->actor.world.pos.x = points[-1].x;
        this->actor.world.pos.z = points[-1].z;
        this->actor.world.rot.y = Math_Atan2S(points->x - this->actor.world.pos.x, points->z - this->actor.world.pos.z);
        this->actor.speed = 0.0f;
    }
}

void EnZog_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnZog* this = THIS;
    s32 i;
    s16 csId;

    if (!D_80B95E10) {
        for (i = 0; i < ARRAY_COUNT(D_80B958AC); i++) {
            D_80B958AC[i] = Lib_SegmentedToVirtual(D_80B958AC[i]);
        }

        for (i = 0; i < ARRAY_COUNT(D_80B958B8); i++) {
            D_80B958B8[i] = Lib_SegmentedToVirtual(D_80B958B8[i]);
        }

        D_80B95E10 = true;
    }

    ActorShape_Init(&this->actor.shape, 0.0f, func_80B93310, 24.0f);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80B95128;
    this->actor.textId = 0x1004;
    SkelAnime_InitFlex(play, &this->skelAnime, &object_zog_Skel_029170, &object_zog_Anim_00FC0C, this->jointTable,
                       this->morphTable, 23);
    Animation_PlayOnce(&this->skelAnime, &object_zog_Anim_00FC0C);
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;

    if ((ENZOG_GET_F(&this->actor) != ENZOG_F_2) && (INV_CONTENT(ITEM_MASK_ZORA) == ITEM_MASK_ZORA) &&
        ((play->csCtx.scriptIndex != 2) || (gSaveContext.sceneLayer != 0) || (play->sceneId != SCENE_30GYOSON))) {
        Actor_Kill(&this->actor);
        return;
    }

    this->actor.terminalVelocity = -4.0f;
    this->actor.gravity = -1.0f;
    this->actor.uncullZoneScale = 3000.0f;
    this->actor.shape.yOffset = 1000.0f;
    this->unk_308 = 0;
    this->unk_30A = 0;
    this->unk_31C = 2;
    this->unk_31E = 0;
    this->csIdIndex = -1;
    this->unk_322 = 100;

    Math_Vec3f_Copy(&this->unk_2F0, &this->actor.world.pos);

    if (ENZOG_GET_F(&this->actor) == ENZOG_F_2) {
        this->actionFunc = func_80B95240;
        this->unk_322 = 255;
        this->unk_31C = 0;
        this->unk_31E = 0;
        this->actor.shape.yOffset = 0.0f;
    }

    this->unk_2EC = 0;
    if (ENZOG_GET_FC00(&this->actor) != ENZOG_FC00_63) {
        func_80B93468(this, play);
    } else {
        this->unk_2E8 = NULL;
    }

    this->unk_2FC = 0;
    this->unk_302 = 0;
    this->unk_2EC++;
    this->unk_304 = 0;
    this->unk_2FE = this->unk_2FC;
    this->unk_300 = this->unk_302;
    csId = this->actor.csId;

    for (i = 0; i < ARRAY_COUNT(this->csIdList); i++) {
        this->csIdList[i] = csId;
        if (csId != CS_ID_NONE) {
            this->actor.csId = csId;
            csId = CutsceneManager_GetAdditionalCsId(this->actor.csId);
        }
    }

    this->actor.flags |= ACTOR_FLAG_10000;
    this->actor.home.rot.z = 0;
    if (ENZOG_GET_F(&this->actor) != ENZOG_F_2) {
        for (i = 0; i < 5; i++) {
            Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_TANRON4, this->actor.world.pos.x,
                               this->actor.world.pos.y + 500.0f, this->actor.world.pos.z, 0, 0, 0, 100);
        }
    }

    if ((ENZOG_GET_F(&this->actor) != ENZOG_F_2) && CHECK_WEEKEVENTREG(WEEKEVENTREG_88_10)) {
        this->unk_302 = this->unk_300 = 0;
        this->unk_2FC = this->unk_2FE = 3;
        this->actor.flags |= ACTOR_FLAG_2000000;
        this->actor.flags &= ~ACTOR_FLAG_10000;
        this->unk_31C = 2;
        this->unk_31E = 0;

        Animation_PlayLoop(&this->skelAnime, D_80B958DC[0]);
        this->actor.textId = 0x1009;
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_91_02)) {
            this->actor.textId = 0x103C;
            this->actionFunc = func_80B9451C;
        } else {
            this->actionFunc = func_80B948A8;
        }
        this->actor.shape.rot.y = 0x4000;
        this->actor.world.rot.y = 0x4000;
        this->actor.world.pos.x = -376.0f;
        this->actor.world.pos.y = 80.0f;
        this->actor.world.pos.z = 4793.0f;
        this->actor.shape.yOffset = 0.0f;
    }
}

void EnZog_Destroy(Actor* thisx, PlayState* play) {
    EnZog* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void func_80B939C0(EnZog* this, s16 arg1, u8 arg2) {
    Animation_Change(&this->skelAnime, D_80B958C0[arg1], 1.0f, 0.0f, Animation_GetLastFrame(D_80B958C0[arg1]), arg2,
                     -5.0f);
    this->unk_304 = arg1;
}

void func_80B93A48(EnZog* this, PlayState* play) {
    s16* table;

    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->unk_302 != this->unk_300) {
            this->unk_302++;
        } else if (this->unk_302 == 0) {
            if (this->unk_2FC != this->unk_2FE) {
                this->unk_2FC = this->unk_2FE;
            }
        }

        if (this->unk_302 >= D_80B95984[this->unk_2FC]) {
            this->unk_302 = 0;
            this->unk_300 = 0;
            if (this->unk_2FC != this->unk_2FE) {
                this->unk_2FC = this->unk_2FE;
            }
        }

        table = D_80B95974[this->unk_2FC];

        this->unk_304 = table[this->unk_302];
        Animation_PlayOnce(&this->skelAnime, D_80B958C0[this->unk_304]);
        SkelAnime_Update(&this->skelAnime);
    }
}

void func_80B93B44(EnZog* this) {
    if (!(this->unk_30A & 4)) {
        if (this->csIdIndex != -1) {
            CutsceneManager_Stop(this->csIdList[this->csIdIndex]);
        }
    }
    this->csIdIndex = -1;
    this->unk_30A &= ~4;
}

void func_80B93BA8(EnZog* this, s16 csIdIndex) {
    func_80B93B44(this);
    this->csIdIndex = csIdIndex;
    this->unk_30A |= 4;
}

s32 func_80B93BE0(EnZog* this, PlayState* play) {
    Path* path = this->unk_2E8;
    s16 temp_v0;
    Vec3s* points;

    if (this->unk_2E8 == 0) {
        return false;
    }

    points = &((Vec3s*)Lib_SegmentedToVirtual(path->points))[this->unk_2EC];

    if (this->unk_30A & 1) {
        this->actor.world.pos.x = points->x;
        this->actor.world.pos.z = points->z;
        return true;
    }

    points++;
    temp_v0 = Math_Atan2S(points->x - this->actor.world.pos.x, points->z - this->actor.world.pos.z);

    if (ABS_ALT(temp_v0 - this->actor.world.rot.y) > 0x4000) {
        this->unk_2EC++;
        func_80B93468(this, play);
        if ((this->unk_2EC + 1) >= this->unk_2E8->count) {
            this->unk_30A |= 1;
            return true;
        }
    } else {
        this->actor.world.rot.y = temp_v0;
    }

    return false;
}

void func_80B93D2C(EnZog* this, PlayState* play) {
    s32 pad;
    Vec3f sp28 = this->actor.world.pos;

    sp28.y += this->actor.depthInWater;
    this->actor.world.pos.y += (this->actor.depthInWater - 10.0f) + (2.0f * Math_SinS(this->unk_308));
    this->unk_308 += 0x200;
    if ((play->gameplayFrames % 16) == 0) {
        EffectSsGRipple_Spawn(play, &sp28, 150, 500, 0);
    }
}

void func_80B93DE8(Vec3f* arg0, PlayState* play, s32 arg2) {
    Vec3f sp2C;

    sp2C.x = Rand_CenteredFloat(30.0f) + arg0->x;
    sp2C.y = arg0->y + 3.0f;
    sp2C.z = Rand_CenteredFloat(30.0f) + arg0->z;
    EffectSsKirakira_SpawnDispersed(play, &sp2C, &D_80B9598C, &D_80B95998, &D_80B959A4, &D_80B959A8, 1000, arg2);
}

s32 func_80B93EA0(EnZog* this, PlayState* play) {
    s16 cueId;

    if (SkelAnime_Update(&this->skelAnime)) {
        switch (this->cueId) {
            case 2:
            case 3:
                Animation_PlayLoop(&this->skelAnime, *D_80B958F0);
                this->unk_31C = 0;
                this->unk_31E = 1;
                break;

            case 4:
                Animation_PlayLoop(&this->skelAnime, *D_80B958F8);
                this->unk_31C = 2;
                this->unk_31E = 1;
                break;

            case 5:
                switch (this->unk_304) {
                    case 16:
                        Animation_PlayOnce(&this->skelAnime, *D_80B95904);
                        this->unk_304 = 17;
                        this->unk_31C = 2;
                        this->unk_31E = 0;
                        break;

                    case 17:
                        Animation_Change(&this->skelAnime, *D_80B958DC, 0.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f);
                        break;
                }
                break;

            case 6:
                Animation_PlayLoop(&this->skelAnime, *D_80B958E4);
                this->unk_31C = 1;
                this->unk_31E = 1;
                break;

            case 12:
                Animation_PlayLoop(&this->skelAnime, D_80B95930);
                break;

            case 13:
                Animation_PlayLoop(&this->skelAnime, D_80B95938);
                break;

            case 14:
                Animation_PlayLoop(&this->skelAnime, D_80B95928);
                break;

            case 15:
                Animation_PlayLoop(&this->skelAnime, D_80B9591C);
                break;
        }
        SkelAnime_Update(&this->skelAnime);
    }

    if (Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_471)) {
        cueId = play->csCtx.actorCues[Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_471)]->id;
        Cutscene_ActorTranslateAndYaw(&this->actor, play, Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_471));

        switch (this->cueId) {
            case 2:
                if (play->csCtx.curFrame == 60) {
                    Actor_PlaySfx(&this->actor, NA_SE_EV_JUMP_SAND);
                }
                break;

            case 8:
                if (this->unk_322 > 4) {
                    this->unk_322 -= 4;
                } else {
                    this->unk_322 = 0;
                }

                if (this->unk_322 > 0) {
                    func_80B93DE8(&this->unk_2F0, play, 20);
                    func_80B93DE8(&this->actor.world.pos, play, 20);
                    func_80B93DE8(&this->actor.focus.pos, play, 20);
                }
                break;

            case 9:
            case 10:
                if (this->unk_322 < 150) {
                    this->unk_322 += 15;
                } else {
                    this->unk_322 = 150;
                }
                break;

            default:
                this->unk_30A &= ~8;
                break;
        }

        if (this->cueId != cueId) {
            this->cueId = cueId;

            switch (this->cueId) {
                case 1:
                    func_80B939C0(this, 7, ANIMMODE_LOOP);
                    this->unk_31C = 2;
                    this->unk_31E = 0;
                    break;

                case 2:
                    func_80B939C0(this, 11, ANIMMODE_ONCE);
                    this->unk_31C = 1;
                    this->unk_31E = 0;
                    break;

                case 3:
                    func_80B939C0(this, 15, ANIMMODE_ONCE);
                    this->unk_31C = 0;
                    this->unk_31E = 1;
                    break;

                case 4:
                    func_80B939C0(this, 13, ANIMMODE_ONCE);
                    this->unk_31C = 2;
                    this->unk_31E = 1;
                    break;

                case 5:
                    func_80B939C0(this, 16, ANIMMODE_ONCE);
                    this->unk_31C = 2;
                    this->unk_31E = 1;
                    break;

                case 6:
                    func_80B939C0(this, 8, ANIMMODE_ONCE);
                    this->unk_31C = 1;
                    this->unk_31E = 0;
                    break;

                case 8:
                    this->unk_322 = 0xFA;
                    this->unk_30A |= 8;
                    break;

                case 9:
                    this->unk_322 = 0;
                    this->unk_30A |= 8;
                    func_80B939C0(this, 18, ANIMMODE_LOOP);
                    this->unk_31C = 0;
                    this->unk_31E = 0;
                    this->unk_30A &= ~2;
                    break;

                case 10:
                    func_80B939C0(this, 14, ANIMMODE_LOOP);
                    this->unk_31C = 0;
                    this->unk_30A |= 2;
                    this->unk_31E = 1;
                    break;

                case 11:
                    Animation_PlayLoop(&this->skelAnime, D_80B95920);
                    break;

                case 12:
                    Animation_PlayOnce(&this->skelAnime, D_80B9592C);
                    break;

                case 13:
                    Animation_PlayOnce(&this->skelAnime, D_80B95934);
                    break;

                case 14:
                    this->unk_30A |= 2;
                    Animation_PlayOnce(&this->skelAnime, D_80B95924);
                    break;

                case 15:
                    Animation_PlayOnce(&this->skelAnime, D_80B95918);
                    break;
            }
        }
        return true;
    }

    return false;
}

void func_80B943A0(EnZog* this, PlayState* play) {
    func_80B93EA0(this, play);
}

void func_80B943C0(EnZog* this, PlayState* play) {
    if (!(this->unk_30A & 4)) {
        this->actionFunc = func_80B943A0;
        this->cueId = -1;
    }
}

void func_80B943EC(EnZog* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (this->unk_30A & 0x10) {
        if (!(player->stateFlags2 & PLAYER_STATE2_8000000)) {
            this->unk_30A &= ~0x10;
        }
    } else if ((player->stateFlags2 & PLAYER_STATE2_8000000) && (this->actor.xzDistToPlayer < 120.0f)) {
        this->unk_30A |= 0x10;
        Actor_PlaySfx(&this->actor, NA_SE_SY_TRE_BOX_APPEAR);
    }
}

void func_80B94470(EnZog* this, PlayState* play) {
    if (Message_GetState(&play->msgCtx) == TEXT_STATE_5) {
        if (Message_ShouldAdvance(play) && (play->msgCtx.currentTextId == 0x103C)) {
            Message_CloseTextbox(play);
            this->actionFunc = func_80B9451C;
            this->unk_300 = this->unk_302 = 0;
            this->unk_31C = 2;
            this->unk_31E = 0;
        }
    }
    func_80B93A48(this, play);
}

void func_80B9451C(EnZog* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->unk_300 = 2;
        this->actionFunc = func_80B94470;
    } else if ((play->msgCtx.ocarinaMode == OCARINA_MODE_EVENT) && (this->actor.xzDistToPlayer < 120.0f)) {
        if ((play->msgCtx.lastPlayedSong == OCARINA_SONG_HEALING) && (GET_PLAYER_FORM == PLAYER_FORM_HUMAN)) {
            func_80B93BA8(this, 2);
            this->actionFunc = func_80B943C0;
            this->actor.shape.shadowDraw = NULL;
        }
    } else if (this->actor.xzDistToPlayer < 120.0f) {
        Actor_OfferTalk(&this->actor, play, 150.0f);
    }
    func_80B943EC(this, play);
}

void func_80B9461C(EnZog* this, PlayState* play) {
    if (!func_80B93EA0(this, play)) {
        this->actor.textId = 0x103C;
        this->actionFunc = func_80B9451C;
        this->actor.flags |= ACTOR_FLAG_2000000;
        SET_WEEKEVENTREG(WEEKEVENTREG_91_02);
    }

    if ((this->unk_304 == 11) && ((s32)this->skelAnime.curFrame >= 55)) {
        this->unk_30A |= 2;
    }
}

void func_80B946B4(EnZog* this, PlayState* play) {
    func_80B93A48(this, play);
    if (!(this->unk_30A & 4)) {
        this->actionFunc = func_80B9461C;
        this->cueId = -1;
    }
}

void func_80B946FC(EnZog* this, PlayState* play) {
    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_CHOICE:
            if (Message_ShouldAdvance(play)) {
                switch (play->msgCtx.choiceIndex) {
                    case 0:
                        Audio_PlaySfx_MessageDecide();
                        play->msgCtx.msgLength = 0;
                        this->actionFunc = func_80B946B4;
                        func_80B93BA8(this, 1);
                        break;

                    case 1:
                        Audio_PlaySfx_MessageCancel();
                        Message_ContinueTextbox(play, 0x1014);
                        break;
                }
            }
            break;

        case TEXT_STATE_5:
            if (Message_ShouldAdvance(play)) {
                switch (play->msgCtx.currentTextId) {
                    case 0x1008:
                        Message_ContinueTextbox(play, play->msgCtx.currentTextId + 1);
                        break;

                    case 0x1009:
                        this->unk_300 = 4;
                        Message_ContinueTextbox(play, play->msgCtx.currentTextId + 1);
                        break;

                    case 0x1014:
                        Message_ContinueTextbox(play, play->msgCtx.currentTextId + 1);
                        break;

                    case 0x1015:
                        Message_CloseTextbox(play);
                        this->actionFunc = func_80B948A8;
                        this->unk_300 = this->unk_302 = 0;
                        this->unk_31C = 2;
                        this->unk_31E = 0;
                        return;
                }
            }
            break;
    }

    func_80B93A48(this, play);
}

void func_80B948A8(EnZog* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->unk_300 = 2;
        this->actionFunc = func_80B946FC;
    } else if ((play->msgCtx.ocarinaMode == OCARINA_MODE_EVENT) && (this->actor.xzDistToPlayer < 120.0f)) {
        if ((play->msgCtx.lastPlayedSong == OCARINA_SONG_HEALING) && (GET_PLAYER_FORM == PLAYER_FORM_HUMAN)) {
            func_80B93BA8(this, 2);
            this->actionFunc = func_80B943C0;
            this->actor.shape.shadowDraw = NULL;
        }
        return;
    } else {
        if ((this->unk_302 == 2) && (this->unk_2FC == 2)) {
            this->unk_300 = 0;
            this->unk_2FE = 3;
            this->unk_302 = this->unk_300;
            this->unk_2FC = this->unk_2FE;
            func_80B93B44(this);
        }

        if ((this->unk_302 == 0) && (this->actor.xzDistToPlayer < 120.0f)) {
            Actor_OfferTalk(&this->actor, play, 150.0f);
        }
    }
    func_80B93A48(this, play);
    func_80B943EC(this, play);
}

void func_80B94A00(EnZog* this, PlayState* play) {
    s32 pad;
    Vec3f sp30;

    if (func_80B93BE0(this, play)) {
        this->actionFunc = func_80B948A8;
        this->actor.flags |= ACTOR_FLAG_2000000;
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_29_20)) {
            this->actor.textId = 0x1009;
        } else {
            this->actor.textId = 0x1008;
            SET_WEEKEVENTREG(WEEKEVENTREG_29_20);
        }
        this->unk_300 = 2;
        this->unk_31C = 2;
        this->unk_31E = 0;
        return;
    }

    if ((this->skelAnime.curFrame >= 35.0f) ||
        ((this->skelAnime.curFrame >= 10.0f) && (this->skelAnime.curFrame <= 24.0f))) {
        this->actor.speed = 0.0f;
    } else {
        this->actor.speed = 1.5f;
    }

    if ((this->actor.depthInWater > 0.0f) && ((play->gameplayFrames % 8) == 0)) {
        sp30 = this->actor.world.pos;
        sp30.y += this->actor.depthInWater;
        EffectSsGRipple_Spawn(play, &sp30, 150, 500, 0);
    }

    if (this->actor.shape.yOffset > 0.0f) {
        this->actor.shape.yOffset -= 20.0f;
    }

    func_80B93A48(this, play);

    if ((this->unk_304 == 4) &&
        (Animation_OnFrame(&this->skelAnime, 136.0f) || Animation_OnFrame(&this->skelAnime, 155.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_PL_WALK_GROUND + SURFACE_SFX_OFFSET_WATER_SHALLOW);
    }

    if ((this->unk_304 == 5) &&
        (Animation_OnFrame(&this->skelAnime, 12.0f) || Animation_OnFrame(&this->skelAnime, 37.0f))) {
        if (this->actor.depthInWater > 0.0f) {
            Actor_PlaySfx(&this->actor, NA_SE_PL_WALK_GROUND + SURFACE_SFX_OFFSET_WATER_SHALLOW);
        } else {
            Actor_PlaySfx(&this->actor, NA_SE_PL_WALK_GROUND + SURFACE_SFX_OFFSET_SAND);
        }
    }
}

void func_80B94C5C(EnZog* this, PlayState* play) {
    this->actor.speed = 0.0f;
    if (this->unk_304 != 0) {
        if (this->actor.shape.yOffset > 0.0f) {
            this->actor.shape.yOffset -= 20.0f;
        }
        this->actor.velocity.y = -1.0f;
        this->actor.terminalVelocity = -1.0f;
    }

    if ((this->unk_2FC == 1) && (this->unk_302 == 0)) {
        this->unk_2FE = 2;
        this->unk_300 = 2;
    }

    if (this->unk_304 == 5) {
        this->actionFunc = func_80B94A00;
    }

    func_80B93A48(this, play);
}

void func_80B94D0C(EnZog* this, PlayState* play) {
    func_80B93D2C(this, play);
    this->actor.speed = 0.0f;
    if (this->unk_320 > 0) {
        this->unk_320--;
        this->unk_31C = 1;
        this->unk_31E = 1;
    } else {
        this->unk_31C = 2;
        this->unk_31E = 0;
    }

    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
        this->unk_320 = 5;
        switch (play->msgCtx.currentTextId) {
            case 0x1004:
            case 0x1005:
            case 0x1006:
                Message_ContinueTextbox(play, play->msgCtx.currentTextId + 1);
                break;

            case 0x1007:
                Message_CloseTextbox(play);
                this->actionFunc = func_80B94E34;
                this->unk_300 = 5;
                this->unk_320 = 0;
                this->unk_31C = 2;
                this->unk_31E = 0;
                func_80B93B44(this);
                break;
        }
    }
    func_80B93A48(this, play);
}

void func_80B94E34(EnZog* this, PlayState* play) {
    s32 pad;
    Player* player = GET_PLAYER(play);

    func_80B93D2C(this, play);
    func_80B93BE0(this, play);
    if (this->actor.speed < 0.1f) {
        this->actor.speed = 0.0f;
    } else {
        if (this->actor.speed > 0.1f) {
            WaterBox* sp44;
            Vec3f sp38;

            Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.shape.rot.y, &D_80B959AC, &sp38);
            sp38.x += Rand_CenteredFloat(30.0f);
            sp38.y += 20.0f;
            sp38.z += Rand_CenteredFloat(30.0f);
            if (WaterBox_GetSurface1(play, &play->colCtx, sp38.x, sp38.z, &sp38.y, &sp44) &&
                (this->actor.world.pos.y < sp38.y)) {
                EffectSsGSplash_Spawn(play, &sp38, NULL, NULL, 1,
                                      Rand_ZeroFloat(this->actor.speed * 40.0f) + (this->actor.speed * 60.0f));
            }

            if ((player->actor.speed > 3.0f) && (this->unk_324 == 0)) {
                this->unk_324 = 25;
                Player_PlaySfx(player, player->ageProperties->voiceSfxIdOffset + NA_SE_VO_LI_PUSH);
            }
        }
        this->actor.speed *= 0.3f;
    }

    if (ABS_ALT(this->actor.yawTowardsPlayer - this->actor.world.rot.y) > 0x5000) {
        Actor_OfferGetItem(&this->actor, play, GI_NONE, 60.0f, 40.0f);
    }

    if (this->unk_324 > 0) {
        this->unk_324--;
    }

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actionFunc = func_80B94D0C;
        this->actor.speed = 0.0f;
        this->unk_300 = 2;
    } else if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        this->actor.home.rot.z = 1;
        this->actionFunc = func_80B94C5C;
        this->actor.speed = 0.0f;
        this->unk_2FE = 1;
        this->actor.velocity.y = 0.0f;
        this->actor.terminalVelocity = 0.0f;
        this->actor.gravity = 0.0f;
        this->unk_31C = 1;
        this->unk_31E = 0;
        func_80B93BA8(this, 0);
        SET_WEEKEVENTREG(WEEKEVENTREG_88_10);
    } else if ((this->actor.yawTowardsPlayer > 16000) && (this->actor.yawTowardsPlayer < 32000) &&
               (this->unk_302 == 0)) {
        Actor_OfferTalk(&this->actor, play, 150.0f);
    }

    this->actor.shape.rot.y = this->actor.world.rot.y;
    func_80B93A48(this, play);
}

void func_80B95128(EnZog* this, PlayState* play) {
    func_80B93D2C(this, play);
    func_80B93BE0(this, play);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actionFunc = func_80B94D0C;
        this->unk_300 = 2;
        this->actor.speed = 0.0f;

        switch (CURRENT_DAY) {
            case 1:
                func_80B93BA8(this, 4);
                break;

            case 2:
                func_80B93BA8(this, 5);
                break;

            default:
                func_80B93BA8(this, 6);
                break;
        }

        this->actor.flags &= ~ACTOR_FLAG_10000;
        SET_WEEKEVENTREG(WEEKEVENTREG_91_01);
    } else {
        Actor_OfferTalk(&this->actor, play, 150.0f);
    }
    this->actor.shape.rot.y = this->actor.world.rot.y;
    func_80B93A48(this, play);
}

void func_80B95240(EnZog* this, PlayState* play) {
    func_80B93EA0(this, play);
}

void EnZog_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnZog* this = THIS;

    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, 10.0f, 10.0f, UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_4);
    if (Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_471) && (ENZOG_GET_F(&this->actor) != ENZOG_F_2)) {
        this->actionFunc = func_80B9461C;
        this->actor.shape.yOffset = 0.0f;
    }

    this->actionFunc(this, play);

    if (((this->unk_304 == 6) && Animation_OnFrame(&this->skelAnime, 43.0f)) ||
        ((this->unk_304 == 17) && Animation_OnFrame(&this->skelAnime, 14.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_EV_LAND_SAND);
    }

    if (this->unk_30A & 1) {
        this->collider.dim.pos.x = this->unk_2F0.x;
        this->collider.dim.pos.y = this->actor.world.pos.y;
        this->collider.dim.pos.z = this->unk_2F0.z;
    } else {
        Collider_UpdateCylinder(&this->actor, &this->collider);
    }
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);

    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 30.0f;

    if (this->unk_30A & 4) {
        if (this->csIdIndex == -1) {
            this->unk_30A &= ~4;
        } else if (this->csIdList[this->csIdIndex] == CS_ID_NONE) {
            this->unk_30A &= ~4;
        } else if (CutsceneManager_GetCurrentCsId() == CS_ID_GLOBAL_TALK) {
            CutsceneManager_Stop(CS_ID_GLOBAL_TALK);
            CutsceneManager_Queue(this->csIdList[this->csIdIndex]);
        } else if (CutsceneManager_IsNext(this->csIdList[this->csIdIndex])) {
            CutsceneManager_StartWithPlayerCs(this->csIdList[this->csIdIndex], &this->actor);
            this->unk_30A &= ~4;
        } else {
            CutsceneManager_Queue(this->csIdList[this->csIdIndex]);
        }
    }
}

void EnZog_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80B959B8 = { 0.0f, 0.0f, 0.0f };
    EnZog* this = THIS;

    D_80B959B8.y = 1000.0f;
    if (limbIndex == 9) {
        Matrix_MultVec3f(&D_80B959B8, &this->actor.focus.pos);
    }
    D_80B959B8.y = 0.0f;

    if (limbIndex == 1) {
        Matrix_MultVec3f(&D_80B959B8, &this->unk_2F0);
    }

    if ((this->unk_30A & 2) && (limbIndex == 17)) {
        OPEN_DISPS(play->state.gfxCtx);

        gSPDisplayList(POLY_OPA_DISP++, object_zog_DL_0280A8);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

void func_80B95598(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    static Vec3f D_80B959C4 = { 0.0f, 0.0f, 0.0f };
    EnZog* this = THIS;

    D_80B959C4.y = 1000.0f;
    if (limbIndex == 9) {
        Matrix_MultVec3f(&D_80B959C4, &this->actor.focus.pos);
    }
    D_80B959C4.y = 0.0f;

    if (limbIndex == 1) {
        Matrix_MultVec3f(&D_80B959C4, &this->unk_2F0);
    }

    if ((this->unk_30A & 2) && (limbIndex == 17)) {
        gSPDisplayList((*gfx)++, object_zog_DL_0280A8);
    }
}

void EnZog_Draw(Actor* thisx, PlayState* play) {
    EnZog* this = THIS;
    Gfx* gfx;

    OPEN_DISPS(play->state.gfxCtx);

    if (this->unk_30A & 8) {
        if (this->unk_322 > 128) {
            gfx = POLY_XLU_DISP++;
            Gfx_SetupDL71(gfx);
            Scene_SetRenderModeXlu(play, 2, 2);
        } else {
            gfx = POLY_XLU_DISP++;
            Gfx_SetupDL72(gfx);
            Scene_SetRenderModeXlu(play, 1, 2);
        }

        gfx = POLY_XLU_DISP;

        gSPSegment(&gfx[0], 0x08, Lib_SegmentedToVirtual(D_80B958AC[this->unk_31C]));
        gSPSegment(&gfx[1], 0x09, Lib_SegmentedToVirtual(D_80B958B8[this->unk_31E]));
        gDPSetEnvColor(&gfx[2], 0, 0, 0, this->unk_322);

        POLY_XLU_DISP = &gfx[3];
        POLY_XLU_DISP =
            SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                               NULL, func_80B95598, &this->actor, POLY_XLU_DISP);
    } else {
        Gfx_SetupDL25_Opa(play->state.gfxCtx);
        Scene_SetRenderModeXlu(play, 0, 1);

        gfx = POLY_OPA_DISP;

        gSPSegment(&gfx[0], 0x08, Lib_SegmentedToVirtual(D_80B958AC[this->unk_31C]));
        gSPSegment(&gfx[1], 0x09, Lib_SegmentedToVirtual(D_80B958B8[this->unk_31E]));
        gDPSetEnvColor(&gfx[2], 0, 0, 0, 255);

        POLY_OPA_DISP = &gfx[3];
        SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                              NULL, EnZog_PostLimbDraw, &this->actor);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
