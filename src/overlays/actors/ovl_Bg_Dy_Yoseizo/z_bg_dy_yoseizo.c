/*
 * File: z_bg_dy_yoseizo.c
 * Overlay: ovl_Bg_Dy_Yoseizo
 * Description: Great Fairy
 */

#include "z_bg_dy_yoseizo.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_2000000)

#define THIS ((BgDyYoseizo*)thisx)

void BgDyYoseizo_Init(Actor* thisx, PlayState* play);
void BgDyYoseizo_Destroy(Actor* thisx, PlayState* play);
void BgDyYoseizo_Update(Actor* thisx, PlayState* play);
void func_80A0BD40(Actor* thisx, PlayState* play);

void func_80A0AE1C(BgDyYoseizo* this, PlayState* play);
void func_80A0B078(BgDyYoseizo* this, PlayState* play);
void func_80A0B184(BgDyYoseizo* this, PlayState* play);
void func_80A0B290(BgDyYoseizo* this, PlayState* play);
void func_80A0B35C(BgDyYoseizo* this, PlayState* play);
void func_80A0B500(BgDyYoseizo* this, PlayState* play);
void func_80A0B5F0(BgDyYoseizo* this, PlayState* play);
void func_80A0B75C(BgDyYoseizo* this, PlayState* play);
void func_80A0B8CC(BgDyYoseizo* this, PlayState* play);
void func_80A0BB08(BgDyYoseizo* this, PlayState* play);

/* Effect functions */
void func_80A0BE60(BgDyYoseizo* this, Vec3f* initPos, Vec3f* initVelocity, Vec3f* accel, Color_RGB8* primColor,
                   Color_RGB8* envColor, f32 scale, s16 life, s16 type);
void func_80A0BF70(BgDyYoseizo* this, PlayState* play);
void func_80A0C270(BgDyYoseizo* this, PlayState* play);

const ActorInit Bg_Dy_Yoseizo_InitVars = {
    ACTOR_BG_DY_YOSEIZO,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_DY_OBJ,
    sizeof(BgDyYoseizo),
    (ActorFunc)BgDyYoseizo_Init,
    (ActorFunc)BgDyYoseizo_Destroy,
    (ActorFunc)BgDyYoseizo_Update,
    (ActorFunc)NULL,
};

static AnimationHeader* sAnimations[] = {
    0x0600129C, 0x06002338, 0x0600C500, 0x060045FC, 0x06005238, 0x06008090, 0x0600D15C, 0x06006DE4, 0x06005E20,
};

extern Gfx D_0600D1B0[];
extern Gfx D_0600D228[];
extern AnimationHeader D_06008090;
extern FlexSkeletonHeader D_0601C8B4;
extern AnimatedMaterial D_0601C6F4[];

void BgDyYoseizo_Init(Actor* thisx, PlayState* play) {
    BgDyYoseizo* this = THIS;

    this->unk2EC = this->actor.world.pos.y + 40.0f;
    this->actor.focus.pos = this->actor.world.pos;

    SkelAnime_InitFlex(play, &this->skelAnime, &D_0601C8B4, &D_06008090, this->jointTable, this->morphTable, 28);

    this->actionFunc = func_80A0BB08;
    Actor_SetScale(&this->actor, 0.0f);
    this->eyeIndex = 0;
    this->mouthIndex = 0;
    this->blinkTimer = 0;
    this->unk2F8 = 0;
    this->actor.home.rot.z = 1;
    this->unk302 = 0;
}

void BgDyYoseizo_Destroy(Actor* thisx, PlayState* play) {
}

// Has no visible effect since no segment set for manually-controllable eye textures
// BgDyYoseizo_UpdateEyes
void func_80A0A96C(BgDyYoseizo* this) {
    if (this->blinkTimer != 0) {
        this->blinkTimer--;
    }

    if (this->blinkTimer == 0) {
        this->eyeIndex++;
        if (this->eyeIndex >= 3) {
            this->eyeIndex = 0;
            this->blinkTimer = (s32)Rand_ZeroFloat(60.0f) + 20;
        }
    }
}

void func_80A0A9E4(BgDyYoseizo* this, PlayState* play) {
    this->actor.shape.yOffset = Math_SinS(play->gameplayFrames * 1000) * 15.0f;
}

void func_80A0AA40(BgDyYoseizo* this, s16 arg1, s32 arg2) {
    static Color_RGB8 sEffectPrimColors[] = {
        { 255, 235, 220 }, { 255, 220, 220 }, { 220, 255, 220 },
        { 220, 220, 255 }, { 255, 255, 200 }, { 255, 255, 170 },
    };
    static Color_RGB8 sEffectEnvColors[] = {
        { 255, 150, 0 }, { 255, 0, 0 }, { 0, 255, 0 }, { 0, 0, 255 }, { 255, 255, 0 }, { 255, 100, 255 },
    };
    Vec3f vel;
    Vec3f accel;
    Vec3f pos;
    Color_RGB8 primColor;
    Color_RGB8 envColor;
    f32 spawnHeightVariation;
    f32 scale;
    s32 effectType;
    s32 life;
    s32 i;

    if (!(this->actor.scale.y < 0.01f)) {
        spawnHeightVariation = this->actor.scale.y * 3500.0f;
        accel.x = Rand_ZeroOne() - 0.5f;
        accel.y = Rand_ZeroOne() - 0.5f;
        accel.z = Rand_ZeroOne() - 0.5f;
        vel.x = accel.x * 10.0f;
        vel.y = accel.y * 10.0f;
        vel.z = accel.z * 10.0f;

        for (i = 0; i < arg2; i++) {
            switch (arg1) {
                case 2:
                    scale = 1.0f;
                    life = 90;

                    vel.x = accel.x * 100.0f;
                    vel.y = accel.y * 100.0f;
                    vel.z = accel.z * 100.0f;

                    effectType = this->actor.params & 0xF;

                    pos.x = this->actor.world.pos.x;
                    pos.y = this->actor.world.pos.y + spawnHeightVariation +
                            (Rand_ZeroOne() - 0.5f) * (spawnHeightVariation * 0.5f);
                    pos.z = this->actor.world.pos.z + 30.0f;
                    break;

                case 0:
                    scale = 1.0f;
                    life = 90;
                    effectType = this->actor.params & 0xF;

                    pos.x = this->actor.world.pos.x;
                    pos.y = this->actor.world.pos.y + spawnHeightVariation +
                            (Rand_ZeroOne() - 0.5f) * (spawnHeightVariation * 0.5f);
                    pos.z = this->actor.world.pos.z + 30.0f;
                    break;

                default:
                    scale = 0.2f;
                    life = 50;
                    effectType = 5;

                    pos.x = randPlusMinusPoint5Scaled(10.0f) + this->actor.world.pos.x;
                    pos.y = this->actor.world.pos.y + spawnHeightVariation + 50.0f +
                            (Rand_ZeroOne() - 0.5f) * (spawnHeightVariation * 0.1f);
                    pos.z = this->actor.world.pos.z + 30.0f;
                    break;
            }

            primColor.r = sEffectPrimColors[effectType].r;
            primColor.g = sEffectPrimColors[effectType].g;
            primColor.b = sEffectPrimColors[effectType].b;
            envColor.r = sEffectEnvColors[effectType].r;
            envColor.g = sEffectEnvColors[effectType].g;
            envColor.b = sEffectEnvColors[effectType].b;

            func_80A0BE60(this, &pos, &vel, &accel, &primColor, &envColor, scale, life, effectType);
        }
    }
}

void func_80A0AD50(BgDyYoseizo* this) {
    f32 scale = this->actor.scale.x;
    f32 heightTarget = this->actor.home.pos.y + 40.0f;

    Math_ApproachF(&this->actor.world.pos.y, heightTarget, this->unk2F0, 100.0f);
    Math_ApproachF(&scale, 0.035f, this->unk2F4, 0.005f);
    Math_ApproachF(&this->unk2F0, 0.8f, 0.1f, 0.02f);
    Math_ApproachF(&this->unk2F4, 0.2f, 0.03f, 0.05f);
    func_80A0AA40(this, 0, 2);
    Actor_SetScale(&this->actor, scale);
}

void func_80A0AE1C(BgDyYoseizo* this, PlayState* play) {
    f32 scale = this->actor.scale.x;
    f32 heightTarget = this->actor.home.pos.y;

    if (scale < 0.003f) {
        this->actionFunc = func_80A0BB08;
        Actor_SetScale(&this->actor, 0.0f);
        this->unk2F0 = 0.0f;
        this->unk2F4 = 0.0f;
        this->unk2F8 = 0;

        if ((this->actor.params & 0xF) < 4) {
            Actor_Spawn(&play->actorCtx, play, ACTOR_DEMO_EFFECT, this->actor.world.pos.x,
                        this->actor.world.pos.y + 20.0f, this->actor.world.pos.z, 0, 0, 0,
                        (this->actor.params & 0xF) + 4);
        } else {
            Actor_Spawn(&play->actorCtx, play, ACTOR_DEMO_EFFECT, this->actor.world.pos.x,
                        this->actor.world.pos.y + 20.0f, this->actor.world.pos.z, 0, 0, 0, 4);
        }
        play_sound(NA_SE_SY_WHITE_OUT_T);
    } else {
        Math_ApproachF(&this->actor.world.pos.y, heightTarget, this->unk2F0, 100.0f);
        Math_ApproachZeroF(&scale, this->unk2F4, 0.005f);
        Math_ApproachF(&this->unk2F0, 0.8f, 0.1f, 0.02f);
        Math_ApproachF(&this->unk2F4, 0.2f, 0.03f, 0.05f);

        this->actor.shape.rot.y += this->unk2F8;
        if (this->unk2F8 < 0x1770) {
            this->unk2F8 += 0x12C;
        }

        func_80A0AA40(this, 0, 2);
        Actor_SetScale(&this->actor, scale);
    }
}

void func_80A0AFDC(BgDyYoseizo* this) {
    Animation_Change(&this->skelAnime, sAnimations[2], 0.0f, 46.0f, Animation_GetLastFrame(sAnimations[2]), 2, 0.0f);
    this->actionFunc = func_80A0AE1C;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_VO_FR_LAUGH_0);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_GREAT_FAIRY_VANISH);
    this->unk2F8 = 0;
    this->actor.velocity.y = 0.0f;
    this->unk2F0 = 0.0f;
    this->unk2F4 = 0.0f;
    this->actor.shape.yOffset = 0.0f;
}

void func_80A0B078(BgDyYoseizo* this, PlayState* play) {
    func_80A0A9E4(this, play);
    SkelAnime_Update(&this->skelAnime);

    if (Cutscene_CheckActorAction(play, 0x67) &&
        (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x67)]->action == 7)) {
        Animation_Change(&this->skelAnime, sAnimations[4], 1.0f, 0.0f, Animation_GetLastFrame(sAnimations[4]), 0, 0.0f);
        this->actionFunc = func_80A0B184;
    } else if (Cutscene_CheckActorAction(play, 0x67) &&
               (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x67)]->action == 6)) {
        func_80A0AFDC(this);
    }
}

void func_80A0B184(BgDyYoseizo* this, PlayState* play) {
    func_80A0A9E4(this, play);
    SkelAnime_Update(&this->skelAnime);

    if (Cutscene_CheckActorAction(play, 0x67) &&
        (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x67)]->action == 8)) {
        Animation_Change(&this->skelAnime, sAnimations[5], 1.0f, 0.0f, Animation_GetLastFrame(sAnimations[5]), 0, 0.0f);
        this->actionFunc = func_80A0B078;
    } else if (Cutscene_CheckActorAction(play, 0x67) &&
               (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x67)]->action == 6)) {
        func_80A0AFDC(this);
    }
}

void func_80A0B290(BgDyYoseizo* this, PlayState* play) {
    func_80A0A9E4(this, play);
    SkelAnime_Update(&this->skelAnime);

    if (Cutscene_CheckActorAction(play, 0x67) &&
        (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x67)]->action == 7)) {
        Animation_Change(&this->skelAnime, sAnimations[4], 1.0f, 0.0f, (f32)Animation_GetLastFrame(sAnimations[4]), 0,
                         -10.0f);
        this->actionFunc = func_80A0B184;
        this->mouthIndex = 0;
    }
}

void func_80A0B35C(BgDyYoseizo* this, PlayState* play) {
    func_80A0A9E4(this, play);
    SkelAnime_Update(&this->skelAnime);

    if (this->timer == 60) {
        if (!Flags_GetSwitch(play, (this->actor.params & 0xFE00) >> 9)) {
            switch (this->actor.params & 0xF) {
                case 0:
                    if (gSaveContext.save.playerData.magicAcquired != 1) {
                        gSaveContext.save.playerData.magicAcquired = 1;
                        gSaveContext.unk_3F30 = 0x30;
                    }
                    break;

                case 2:
                    if (gSaveContext.save.playerData.doubleMagic != 1) {
                        gSaveContext.save.playerData.doubleMagic = 1;
                        gSaveContext.unk_3F30 = 0x60;
                        gSaveContext.save.playerData.magicLevel = 0;
                    }
                    break;

                case 3:
                    if (gSaveContext.save.playerData.doubleDefense != 1) {
                        gSaveContext.save.playerData.doubleDefense = 1;
                    }
                    break;
            }
        }
        Interface_ChangeAlpha(9);
    }

    if ((this->timer < 50) && ((this->actor.params & 0xF) == 3)) {
        if (gSaveContext.save.inventory.defenseHearts < 20) {
            gSaveContext.save.inventory.defenseHearts++;
        }
    }

    if (this->timer == 50) {
        gSaveContext.healthAccumulator = 0x140;
        Parameter_AddMagic(play,
                           ((void)0, gSaveContext.unk_3F30) + ((gSaveContext.save.playerData.doubleMagic + 1) * 0x30));
    }

    if (this->timer == 0) {
        this->unk2E8->unk14A = 1;
        this->actionFunc = func_80A0B290;
    }
}

void func_80A0B500(BgDyYoseizo* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    func_80A0A9E4(this, play);

    if (SkelAnime_Update(&this->skelAnime)) {
        Vec3f pos;

        Animation_Change(&this->skelAnime, sAnimations[1], 1.0f, 0.0f, Animation_GetLastFrame(sAnimations[1]), 0, 0.0f);
        this->actionFunc = func_80A0B35C;
        pos.x = player->actor.world.pos.x;
        pos.y = player->actor.world.pos.y + 200.0f;
        pos.z = player->actor.world.pos.z;
        this->unk2E8 = (EnDyExtra*)Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_DY_EXTRA, pos.x,
                                                      pos.y, pos.z, 0, 0, 0, this->actor.params & 0xF);
        this->timer = 120;
    }
}

void func_80A0B5F0(BgDyYoseizo* this, PlayState* play) {
    func_80A0A9E4(this, play);

    if (SkelAnime_Update(&this->skelAnime)) {
        Animation_Change(&this->skelAnime, sAnimations[4], 1.0f, 0.0f, Animation_GetLastFrame(sAnimations[4]), 0, 0.0f);
    }

    if (Cutscene_CheckActorAction(play, 0x67) &&
        (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x67)]->action == 5)) {
        Animation_Change(&this->skelAnime, sAnimations[0], 1.0f, 0.0f, Animation_GetLastFrame(sAnimations[0]), 2,
                         -5.0f);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_VO_FR_SMILE_0);
        this->mouthIndex = 1;
        this->eyeIndex = 0;
        this->actionFunc = func_80A0B500;
    }

    if (Cutscene_CheckActorAction(play, 0x67) &&
        (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x67)]->action == 6)) {
        func_80A0AFDC(this);
    }

    func_80A0A96C(this);
}

void func_80A0B75C(BgDyYoseizo* this, PlayState* play) {
    func_80A0AD50(this);
    SkelAnime_Update(&this->skelAnime);
    if (Cutscene_CheckActorAction(play, 0x67) &&
        (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x67)]->action == 4)) {
        this->actor.shape.rot.y = 0;
        this->actionFunc = func_80A0B5F0;
        Animation_Change(&this->skelAnime, sAnimations[3], 1.0f, 2.0f, Animation_GetLastFrame(sAnimations[3]), 2, 0.0f);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_VO_FR_SMILE_0);
        this->unk2F8 = 0;
    }
}

void func_80A0B834(BgDyYoseizo* this) {
    this->actor.draw = func_80A0BD40;
    Animation_Change(&this->skelAnime, sAnimations[2], 1.0f, 0.0f, Animation_GetLastFrame(sAnimations[2]), 2, 0.0f);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_VO_FR_LAUGH_0);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_GREAT_FAIRY_APPEAR);
    func_80A0AA40(this, 2, 30);
}

void func_80A0B8CC(BgDyYoseizo* this, PlayState* play) {
    s16 sp36;
    s32 pad;
    Player* player = GET_PLAYER(play);

    SkelAnime_Update(&this->skelAnime);

    sp36 = 0;
    if (Cutscene_CheckActorAction(play, 0x67)) {
        sp36 = play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x67)]->action;
        Cutscene_ActorTranslateAndYaw(&this->actor, play, Cutscene_GetActorActionIndex(play, 0x67));
    } else {
        if (this->actor.home.rot.z != 0) {
            this->actor.home.pos.x = player->actor.world.pos.x;
            this->actor.home.pos.z = player->actor.world.pos.z;
            this->actor.home.rot.z = 0;
        } else {
            player->actor.world.pos.x = this->actor.home.pos.x;
            player->actor.world.pos.z = this->actor.home.pos.z;
        }

        if (this->unk302 & 1) {
            if (this->timer == 0) {
                if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
                    ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
                    this->unk302 &= ~1;
                } else {
                    ActorCutscene_SetIntentToPlay(this->actor.cutscene);
                }
            }
        } else if (!(this->unk302 & 2) && (player->meleeWeaponState != 0)) {
            if (player->meleeWeaponAnimation >= PLAYER_MWA_SPIN_ATTACK_1H) {
                if (player->unk_B08[0] >= 0.85f) {
                    this->unk302 |= 1;
                    this->unk302 |= 2;
                    if (play->msgCtx.currentTextId == 0x59A) {
                        func_801477B4(play);
                    }
                    this->timer = 20;
                    return;
                }
            }

            if (play->msgCtx.currentTextId != 0x59A) {
                Message_StartTextbox(play, 0x59A, &this->actor);
            }
        }
    }

    if (sp36 != this->unk2F8) {
        switch (sp36) {
            case 9:
                Animation_PlayLoop(&this->skelAnime, sAnimations[6]);
                break;
            case 10:
                Animation_PlayLoop(&this->skelAnime, sAnimations[7]);
                break;
            case 11:
                Animation_PlayOnce(&this->skelAnime, sAnimations[8]);
                break;
        }
        this->unk2F8 = sp36;
    }
}

void func_80A0BB08(BgDyYoseizo* this, PlayState* play) {
    if (Cutscene_CheckActorAction(play, 0x67) &&
        (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x67)]->action == 2)) {
        func_80A0B834(this);
        this->actionFunc = func_80A0B75C;
    }

    if (Cutscene_CheckActorAction(play, 0x67) &&
        (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x67)]->action == 7)) {
        this->actor.draw = func_80A0BD40;
        Animation_PlayLoop(&this->skelAnime, sAnimations[4]);
        this->actionFunc = func_80A0B184;
        this->mouthIndex = 0;
        this->actor.world.pos.y = this->actor.home.pos.y + 40.0f;
        Actor_SetScale(&this->actor, 0.035f);
        this->unk2F8 = 0;
    }

    if (Cutscene_CheckActorAction(play, 0x67) &&
        (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x67)]->action == 9)) {
        Actor_SetScale(&this->actor, 0.01f);
        Animation_PlayLoop(&this->skelAnime, sAnimations[6]);
        this->unk2F8 = 9;
        this->actionFunc = func_80A0B8CC;
        this->actor.draw = func_80A0BD40;
    }
}

void BgDyYoseizo_Update(Actor* thisx, PlayState* play) {
    BgDyYoseizo* this = THIS;

    this->actionFunc(this, play);
    Actor_MoveWithGravity(&this->actor);

    if (this->timer != 0) {
        this->timer--;
    }
    func_80A0BF70(this, play);
}

s32 func_80A0BCD8(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    BgDyYoseizo* this = THIS;

    if (limbIndex == 8) {
        rot->x += this->unk2E2.y;
    }
    if (limbIndex == 15) {
        rot->x += this->unk2DC.y;
        rot->z += this->unk2DC.z;
    }
    return false;
}

void func_80A0BD40(Actor* thisx, PlayState* play) {
    static TexturePtr sMouthTextures[] = {
        0x0601A588, // closed
        0x0601B588  // open
    };
    BgDyYoseizo* this = (BgDyYoseizo*)thisx;
    u32 step = 0;

    switch (this->actor.params & 0xF) {
        case 1:
            step = 2;
            break;

        case 2:
            step = 1;
            break;

        case 3:
        case 4:
            step = this->actor.params & 0xF;
            break;

        default:
            break;
    }

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    AnimatedMat_DrawStepOpa(play, Lib_SegmentedToVirtual(D_0601C6F4), step);

    {
        Gfx* gfx = POLY_OPA_DISP;
        s16 index = this->mouthIndex;
        TexturePtr mouthTex = Lib_SegmentedToVirtual(sMouthTextures[index]);

        gSPSegment(&gfx[0], 0x09, mouthTex);
        POLY_OPA_DISP = &gfx[1];
    }

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          func_80A0BCD8, NULL, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);

    func_80A0C270(this, play);
}

/* Effects functions */

// BgDyYoseizo_SpawnEffect
void func_80A0BE60(BgDyYoseizo* this, Vec3f* initPos, Vec3f* initVelocity, Vec3f* accel, Color_RGB8* primColor,
                   Color_RGB8* envColor, f32 scale, s16 life, s16 type) {
    BgDyYoseizoEffect* effect = this->effects;
    s16 i;

    for (i = 0; i < BG_DY_YOSEIZO_EFFECT_COUNT; i++, effect++) {
        if (effect->alive == 0) {
            effect->alive = 1;
            effect->pos = *initPos;
            effect->velocity = *initVelocity;
            effect->accel = *accel;
            effect->primColor = *primColor;
            effect->alpha = 0;
            effect->envColor = *envColor;
            effect->scale = scale;
            effect->timer = life;
            effect->type = type;
            effect->pitch = 0;
            effect->yaw = (s32)randPlusMinusPoint5Scaled(30000.0f);
            effect->roll = 0;
            return;
        }
    }
}

// BgDyYoseizo_UpdateEffects
void func_80A0BF70(BgDyYoseizo* this, PlayState* play) {
    BgDyYoseizoEffect* effect = this->effects;
    Player* player = GET_PLAYER(play);
    Vec3f sp94;
    Vec3f sp88;
    s32 pad[2];
    f32 goalPitch;
    f32 goalYaw;
    f32 floatAngle;
    s16 i = 0;

    for (i = 0; i < BG_DY_YOSEIZO_EFFECT_COUNT; i++, effect++) {
        if (effect->alive != 0) {
            effect->roll += 3000;

            if (effect->type < 5) {
                effect->pos.x += effect->velocity.x;
                effect->pos.y += effect->velocity.y;
                effect->pos.z += effect->velocity.z;
                effect->velocity.x += effect->accel.x;
                effect->velocity.y += effect->accel.y;
                effect->velocity.z += effect->accel.z;
            } else {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_HEALING - SFX_FLAG);

                sp94 = player->actor.world.pos;
                sp94.y = player->actor.world.pos.y - 150.0f;
                sp94.z = player->actor.world.pos.z - 50.0f;

                goalPitch = Math_Vec3f_Pitch(&effect->pos, &sp94);
                goalYaw = Math_Vec3f_Yaw(&effect->pos, &sp94);

                floatAngle = effect->pitch;
                Math_ApproachF(&floatAngle, goalPitch, 0.9f, 5000.0f);
                effect->pitch = floatAngle;

                floatAngle = effect->yaw;
                Math_ApproachF(&floatAngle, goalYaw, 0.9f, 5000.0f);
                effect->yaw = floatAngle;

                Matrix_Push();
                Matrix_RotateYS(effect->yaw, MTXMODE_NEW);
                Matrix_RotateXS(effect->pitch, MTXMODE_APPLY);

                sp94.x = sp94.y = sp94.z = 3.0f;

                Matrix_MultVec3f(&sp94, &sp88);
                Matrix_Pop();
                effect->pos.x += sp88.x;
                effect->pos.y += sp88.y;
                effect->pos.z += sp88.z;
            }
        }

        // fade up, fade down, vanish and reset
        if (effect->timer != 0) {
            effect->timer--;
            effect->alpha += 30;

            if (effect->alpha > 255) {
                effect->alpha = 255;
            }
        } else {
            effect->alpha -= 30;

            if (effect->alpha <= 0) {
                effect->alpha = 0;
                effect->alive = 0;
            }
        }
    }
}

// BgDyYoseizo_DrawEffects
void func_80A0C270(BgDyYoseizo* this, PlayState* play) {
    static f32 sStretchFactors[] = {
        1.0f, 1.1f, 1.15f, 1.1f, 1.0f, 0.9f, 0.85f, 0.9f,
    };
    GraphicsContext* gfxCtx = play->state.gfxCtx;
    u8 flag = 0;
    BgDyYoseizoEffect* effect = this->effects;
    f32 stretchFactor = sStretchFactors[play->gameplayFrames & 7];
    s16 i;

    OPEN_DISPS(gfxCtx);

    func_8012C2DC(play->state.gfxCtx);

    for (i = 0; i < BG_DY_YOSEIZO_EFFECT_COUNT; i++, effect++) {
        if (effect->alive == 1) {
            if (flag == 0) {
                gSPDisplayList(POLY_XLU_DISP++, D_0600D1B0);
                gDPPipeSync(POLY_XLU_DISP++);
                flag++;
            }

            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, effect->primColor.r, effect->primColor.g, effect->primColor.b,
                            effect->alpha);
            gDPSetEnvColor(POLY_XLU_DISP++, effect->envColor.r, effect->envColor.g, effect->envColor.b, 0);

            Matrix_Translate(effect->pos.x, effect->pos.y, effect->pos.z, MTXMODE_NEW);
            Matrix_ReplaceRotation(&play->billboardMtxF);

            Matrix_Scale(effect->scale, effect->scale * stretchFactor, 1.0f, MTXMODE_APPLY);
            Matrix_RotateZS(effect->roll, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, D_0600D228);
        }
    }

    CLOSE_DISPS(gfxCtx);
}
