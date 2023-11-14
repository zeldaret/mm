/*
 * File: z_en_osk.c
 * Overlay: ovl_En_Osk
 * Description: Igos du Ikana's and his lackey's floating heads
 */

#include "z_en_osk.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_ikn_demo/object_ikn_demo.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY)

#define THIS ((EnOsk*)thisx)

void EnOsk_Init(Actor* thisx, PlayState* play);
void EnOsk_Destroy(Actor* thisx, PlayState* play);
void EnOsk_Update(Actor* thisx, PlayState* play);
void EnOsk_Draw(Actor* thisx, PlayState* play);

void func_80BF5F60(EnOsk* this, PlayState* play);
void func_80BF61EC(EnOsk* this, PlayState* play);
void func_80BF656C(EnOsk* this, PlayState* play);
void func_80BF6A20(EnOsk* this, PlayState* play);

ActorInit En_Osk_InitVars = {
    /**/ ACTOR_EN_OSK,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_IKN_DEMO,
    /**/ sizeof(EnOsk),
    /**/ EnOsk_Init,
    /**/ EnOsk_Destroy,
    /**/ EnOsk_Update,
    /**/ EnOsk_Draw,
};

AnimationHeader* D_80BF6FA0[] = {
    &object_ikn_demo_Anim_003CAC, &object_ikn_demo_Anim_004208, &object_ikn_demo_Anim_004514,
    &object_ikn_demo_Anim_004A58, &object_ikn_demo_Anim_0065D8,
};

AnimationHeader* D_80BF6FB4[] = {
    &object_ikn_demo_Anim_0067B8, &object_ikn_demo_Anim_0083F4, &object_ikn_demo_Anim_0081A8,
    &object_ikn_demo_Anim_008AF4, &object_ikn_demo_Anim_008724, &object_ikn_demo_Anim_008F1C,
    &object_ikn_demo_Anim_008CEC, &object_ikn_demo_Anim_009254, &object_ikn_demo_Anim_009044,
    &object_ikn_demo_Anim_0098E4, &object_ikn_demo_Anim_009CC8, &object_ikn_demo_Anim_009A44,
};

AnimationHeader* D_80BF6FE4[] = {
    &object_ikn_demo_Anim_009EA8, &object_ikn_demo_Anim_00B8C0, &object_ikn_demo_Anim_00B704,
    &object_ikn_demo_Anim_00BDB4, &object_ikn_demo_Anim_00B9E4, &object_ikn_demo_Anim_00C154,
    &object_ikn_demo_Anim_00BF04, &object_ikn_demo_Anim_00CA74, &object_ikn_demo_Anim_00C804,
    &object_ikn_demo_Anim_00D044, &object_ikn_demo_Anim_00CD28, &object_ikn_demo_Anim_00C59C,
    &object_ikn_demo_Anim_00C2C4,
};

Vec3f D_80BF7018 = { 0.0f, 0.5f, 0.0f };

Vec3f D_80BF7024 = { 0.0f, 0.0f, 0.0f };

void EnOsk_Init(Actor* thisx, PlayState* play) {
    EnOsk* this = THIS;

    Actor_SetScale(&this->actor, 0.013f);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 10.0f);

    this->actionFunc = func_80BF5F60;
    this->unk_254 = -1;
    this->cueId = -1;
    this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;

    switch (ENOSK_GET_F(&this->actor)) {
        case ENOSK_1:
            SkelAnime_InitFlex(play, &this->skelAnime, &object_ikn_demo_Skel_007B48, &object_ikn_demo_Anim_006808,
                               this->jointTable, this->morphTable, 7);
            Animation_PlayLoop(&this->skelAnime, &object_ikn_demo_Anim_006808);
            this->actionFunc = func_80BF656C;
            this->cueType = CS_CMD_ACTOR_CUE_528;
            break;

        case ENOSK_2:
            SkelAnime_InitFlex(play, &this->skelAnime, &object_ikn_demo_Skel_00B490, &object_ikn_demo_Anim_009F00,
                               this->jointTable, this->morphTable, 7);
            Animation_PlayLoop(&this->skelAnime, &object_ikn_demo_Anim_006808);
            this->actionFunc = func_80BF6A20;
            this->cueType = CS_CMD_ACTOR_CUE_529;
            break;

        default:
            Actor_SetScale(&this->actor, 0.017f);
            SkelAnime_InitFlex(play, &this->skelAnime, &object_ikn_demo_Skel_0038F0, &object_ikn_demo_Anim_0000B8,
                               this->jointTable, this->morphTable, 17);
            Animation_PlayLoop(&this->skelAnime, &object_ikn_demo_Anim_0000B8);
            this->actionFunc = func_80BF61EC;
            this->cueType = CS_CMD_ACTOR_CUE_530;
            this->actor.home.rot.z = 0;
            this->unk_25C = 0.0f;
            break;
    }
}

void EnOsk_Destroy(Actor* thisx, PlayState* play) {
}

void func_80BF5E00(EnOsk* this, AnimationHeader** animations, s16 index, f32 morphFrame) {
    if (index == this->unk_254) {
        return;
    }
    Animation_MorphToLoop(&this->skelAnime, animations[index], morphFrame);
    this->unk_254 = index;
}

void func_80BF5E68(EnOsk* this, AnimationHeader** animations, s16 index, f32 playSpeed) {
    Animation_MorphToPlayOnce(&this->skelAnime, animations[index], playSpeed);
    this->unk_254 = index;
}

void func_80BF5EBC(EnOsk* this, PlayState* play) {
    Vec3f sp2C;

    sp2C.x = Rand_CenteredFloat(30.0f) + this->actor.world.pos.x;
    sp2C.z = Rand_CenteredFloat(30.0f) + this->actor.world.pos.z;
    sp2C.y = Rand_CenteredFloat(30.0f) + this->actor.world.pos.y;

    func_800B3030(play, &sp2C, &D_80BF7018, &D_80BF7018, 100, 0, 2);
}

void func_80BF5F60(EnOsk* this, PlayState* play) {
}

void func_80BF5F70(EnOsk* this) {
    if ((this->cueId != 1) && (this->cueId != 6)) {
        this->actor.draw = EnOsk_Draw;
        Actor_SetScale(&this->actor, 0.017f);
    }

    switch (this->cueId) {
        case 1:
            this->actor.draw = NULL;
            break;

        case 2:
            func_80BF5E00(this, D_80BF6FA0, 3, -5.0f);
            break;

        case 3:
            func_80BF5E00(this, D_80BF6FA0, 2, -5.0f);
            break;

        case 4:
            func_80BF5E00(this, D_80BF6FA0, 1, -5.0f);
            break;

        case 5:
            func_80BF5E00(this, D_80BF6FA0, 0, -5.0f);
            break;

        case 6:
            func_80BF5E00(this, D_80BF6FA0, 1, -5.0f);
            break;

        case 7:
            func_80BF5E00(this, D_80BF6FA0, 4, -5.0f);
            this->actor.home.rot.z = 1;
            break;
    }
}

void func_80BF609C(EnOsk* this, PlayState* play) {
    if (this->actor.draw != NULL) {
        if (this->actor.home.rot.z != 0) {
            if (play->msgCtx.currentTextId == 0x1531) {
                this->actor.home.rot.z = 0;
            }
        } else {
            if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
                this->unk_25C = Rand_ZeroFloat(3.0f);
            }

            switch (this->unk_254) {
                case 0:
                    if (Animation_OnFrame(&this->skelAnime, this->unk_25C) ||
                        Animation_OnFrame(&this->skelAnime, this->unk_25C + 8.0f)) {
                        Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_TALK);
                    }
                    break;

                case 1:
                    if (Animation_OnFrame(&this->skelAnime, this->unk_25C)) {
                        Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_TALK);
                    }
                    break;

                case 2:
                    if (Animation_OnFrame(&this->skelAnime, this->unk_25C) ||
                        Animation_OnFrame(&this->skelAnime, this->unk_25C + 6.0f)) {
                        Actor_PlaySfx(&this->actor, NA_SE_EN_BOSU_TALK);
                    }
                    break;
            }
        }
    }
}

void func_80BF61EC(EnOsk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if (Cutscene_IsCueInChannel(play, this->cueType)) {
        Cutscene_ActorTranslateAndYaw(&this->actor, play, Cutscene_GetCueChannel(play, this->cueType));
        if (this->cueId != play->csCtx.actorCues[Cutscene_GetCueChannel(play, this->cueType)]->id) {
            this->cueId = play->csCtx.actorCues[Cutscene_GetCueChannel(play, this->cueType)]->id;
            func_80BF5F70(this);
        }
        func_80BF609C(this, play);
    } else {
        this->actor.draw = NULL;
    }

    if (this->cueId == 6) {
        if (this->actor.scale.x > 0.85f * 0.001f) {
            this->actor.scale.x -= 0.85f * 0.001f;
            Actor_SetScale(&this->actor, this->actor.scale.x);
            func_80BF5EBC(this, play);
            Actor_PlaySfx_Flagged(&this->actor, NA_SE_EN_COMMON_EXTINCT_LEV - SFX_FLAG);
        } else {
            this->actor.draw = NULL;
        }
    }
}

void func_80BF6314(EnOsk* this) {
    if ((this->cueId != 1) && (this->cueId != 9)) {
        this->actor.draw = EnOsk_Draw;
        Actor_SetScale(&this->actor, 0.013f);
    }

    switch (this->cueId) {
        case 1:
            this->actor.draw = NULL;
            break;

        case 2:
            func_80BF5E00(this, D_80BF6FB4, 9, -5.0f);
            Actor_SetScale(&this->actor, 0.0f);
            break;

        case 3:
            func_80BF5E68(this, D_80BF6FB4, 2, -5.0f);
            break;

        case 4:
            func_80BF5E68(this, D_80BF6FB4, 4, 0);
            break;

        case 5:
            func_80BF5E68(this, D_80BF6FB4, 8, -5.0f);
            break;

        case 6:
            func_80BF5E68(this, D_80BF6FB4, 11, -5.0f);
            break;

        case 7:
            func_80BF5E68(this, D_80BF6FB4, 6, -5.0f);
            break;

        case 8:
            func_80BF5E00(this, D_80BF6FB4, 0, -5.0f);
            break;

        case 9:
            func_80BF5E00(this, D_80BF6FB4, 0, -5.0f);
            break;
    }
}

void func_80BF6478(EnOsk* this) {
    if (this->actor.draw != NULL) {
        switch (this->unk_254) {
            case 1:
                if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 6.0f) ||
                    Animation_OnFrame(&this->skelAnime, 11.0f)) {
                    Actor_PlaySfx(&this->actor, NA_SE_EN_DEBU_HEAD_UP);
                }
                break;

            case 3:
                if (Animation_OnFrame(&this->skelAnime, 11.0f)) {
                    Actor_PlaySfx(&this->actor, NA_SE_EN_DEBU_HEAD_UP);
                }
                break;

            case 4:
                if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
                    Actor_PlaySfx(&this->actor, NA_SE_EN_DEBU_HEAD_UP);
                }
                break;

            case 10:
            case 11:
                Actor_PlaySfx_Flagged(&this->actor, NA_SE_EN_YASE_LAUGH_K - SFX_FLAG);
                break;
        }
    }
}

void func_80BF656C(EnOsk* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        switch (this->unk_254) {
            case 2:
                func_80BF5E00(this, D_80BF6FB4, 1, 0.0f);
                break;

            case 4:
                func_80BF5E00(this, D_80BF6FB4, 3, 0.0f);
                break;

            case 8:
                func_80BF5E00(this, D_80BF6FB4, 7, -5.0f);
                break;

            case 11:
                func_80BF5E00(this, D_80BF6FB4, 10, -5.0f);
                break;

            case 6:
                func_80BF5E00(this, D_80BF6FB4, 5, -5.0f);
                break;
        }
    }

    if (Cutscene_IsCueInChannel(play, this->cueType)) {
        Cutscene_ActorTranslateAndYaw(&this->actor, play, Cutscene_GetCueChannel(play, this->cueType));
        if (this->cueId != play->csCtx.actorCues[Cutscene_GetCueChannel(play, this->cueType)]->id) {
            this->cueId = play->csCtx.actorCues[Cutscene_GetCueChannel(play, this->cueType)]->id;
            func_80BF6314(this);
        }
        func_80BF6478(this);
    } else {
        this->actor.draw = NULL;
    }

    if ((this->cueId == 2) && (this->actor.scale.x < 13.0f * 0.001f)) {
        this->actor.scale.x += 0.65f * 0.001f;
        Actor_SetScale(&this->actor, this->actor.scale.x);
    }

    if (this->cueId == 9) {
        if (this->actor.scale.x > 0.65f * 0.001f) {
            this->actor.scale.x -= 0.65f * 0.001f;
            Actor_SetScale(&this->actor, this->actor.scale.x);
            func_80BF5EBC(this, play);
            Actor_PlaySfx_Flagged(&this->actor, NA_SE_EN_COMMON_EXTINCT_LEV - SFX_FLAG);
        } else {
            this->actor.draw = NULL;
        }
    }
}

void func_80BF67A8(EnOsk* this) {
    if ((this->cueId != 1) && (this->cueId != 8)) {
        this->actor.draw = EnOsk_Draw;
        Actor_SetScale(&this->actor, 0.013f);
    }

    switch (this->cueId) {
        case 1:
            this->actor.draw = NULL;
            break;

        case 2:
            func_80BF5E68(this, D_80BF6FE4, 2, -5.0f);
            break;

        case 3:
            func_80BF5E68(this, D_80BF6FE4, 8, -5.0f);
            break;

        case 4:
            func_80BF5E68(this, D_80BF6FE4, 4, -5.0f);
            break;

        case 5:
            func_80BF5E68(this, D_80BF6FE4, 6, -5.0f);
            break;

        case 6:
            func_80BF5E68(this, D_80BF6FE4, 10, -5.0f);
            break;

        case 7:
        case 8:
            func_80BF5E00(this, D_80BF6FE4, 0, -5.0f);
            break;

        case 9:
            func_80BF5E68(this, D_80BF6FE4, 12, -5.0f);
            break;
    }
}

void func_80BF68E0(EnOsk* this) {
    if (this->actor.draw != NULL) {
        switch (this->unk_254) {
            case 1:
            case 7:
                if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 6.0f) ||
                    Animation_OnFrame(&this->skelAnime, 11.0f)) {
                    Actor_PlaySfx(&this->actor, NA_SE_EN_DEBU_HEAD_UP);
                }
                break;

            case 2:
                if (Animation_OnFrame(&this->skelAnime, 4.0f)) {
                    Actor_PlaySfx(&this->actor, NA_SE_EN_DEBU_HEAD_UP);
                }
                break;

            case 4:
                if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
                    Actor_PlaySfx(&this->actor, NA_SE_EN_DEBU_HEAD_UP);
                }
                break;

            case 5:
                if (Animation_OnFrame(&this->skelAnime, 6.0f) || Animation_OnFrame(&this->skelAnime, 11.0f)) {
                    Actor_PlaySfx(&this->actor, NA_SE_EN_DEBU_HEAD_UP);
                }
                break;

            case 8:
                if (Animation_OnFrame(&this->skelAnime, 13.0f)) {
                    Actor_PlaySfx(&this->actor, NA_SE_EN_DEBU_HEAD_UP);
                }
                break;
        }
    }
}

void func_80BF6A20(EnOsk* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        switch (this->unk_254) {
            case 2:
                func_80BF5E00(this, D_80BF6FE4, 1, -5.0f);
                break;

            case 8:
                func_80BF5E00(this, D_80BF6FE4, 7, -5.0f);
                break;

            case 4:
                func_80BF5E00(this, D_80BF6FE4, 3, -5.0f);
                break;

            case 6:
                func_80BF5E00(this, D_80BF6FE4, 5, -5.0f);
                break;

            case 10:
                func_80BF5E00(this, D_80BF6FE4, 9, -5.0f);
                break;

            case 12:
                func_80BF5E00(this, D_80BF6FE4, 11, -5.0f);
                break;
        }
    }

    if (Cutscene_IsCueInChannel(play, this->cueType)) {
        Cutscene_ActorTranslateAndYaw(&this->actor, play, Cutscene_GetCueChannel(play, this->cueType));
        if (this->cueId != play->csCtx.actorCues[Cutscene_GetCueChannel(play, this->cueType)]->id) {
            this->cueId = play->csCtx.actorCues[Cutscene_GetCueChannel(play, this->cueType)]->id;
            func_80BF67A8(this);
        }
        func_80BF68E0(this);
    } else {
        this->actor.draw = NULL;
    }

    if (this->cueId == 8) {
        if (this->actor.scale.x > 0.65f * 0.001f) {
            this->actor.scale.x -= 0.65f * 0.001f;
            Actor_SetScale(&this->actor, this->actor.scale.x);
            func_80BF5EBC(this, play);
            Actor_PlaySfx_Flagged(&this->actor, NA_SE_EN_COMMON_EXTINCT_LEV - SFX_FLAG);
        } else {
            this->actor.draw = NULL;
        }
    }
}

void EnOsk_Update(Actor* thisx, PlayState* play) {
    EnOsk* this = THIS;

    this->actionFunc(this, play);
}

void func_80BF6C54(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnOsk* this = THIS;

    if (limbIndex == 1) {
        Matrix_MultVec3f(&D_80BF7024, &this->actor.focus.pos);
    }
}

void EnOsk_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    EnOsk* this = THIS;
    Gfx* gfx;
    Vec3f sp80;
    s32 pad2[4];

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Gfx_PrimColor(play->state.gfxCtx, 0x80, 255, 255, 255, 255));

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, NULL,
                          func_80BF6C54, &this->actor);

    {
        s16 sp62;
        s16 sp60;
        Vec3f sp54;

        sp54 = GET_ACTIVE_CAM(play)->eye;

        sp62 = Math_Vec3f_Yaw(&sp54, &this->actor.focus.pos);
        sp60 = -Math_Vec3f_Pitch(&sp54, &this->actor.focus.pos);

        sp80.x = -(15.0f * (Math_SinS(sp62)) * Math_CosS(sp60));
        sp80.y = -(Math_SinS(sp60) * 15.0f);
        sp80.z = -(15.0f * (Math_CosS(sp62)) * Math_CosS(sp60));

        Matrix_Translate(this->actor.focus.pos.x + sp80.x, this->actor.focus.pos.y + sp80.y,
                         sp80.z = this->actor.focus.pos.z + sp80.z, MTXMODE_NEW);

        sp80.z = Math_SinS(play->gameplayFrames * 0x4000);
        sp80.z = ((sp80.z + 1.0f) * 0.1f) + 2.0f;
        Matrix_Scale(this->actor.scale.x * sp80.z, this->actor.scale.y * sp80.z, this->actor.scale.z * sp80.z,
                     MTXMODE_APPLY);
    }

    gfx = POLY_XLU_DISP;
    gfx = Gfx_SetupDL20_NoCD(gfx);

    gDPSetDither(gfx++, G_CD_NOISE);
    gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
    gSPDisplayList(gfx++, gameplay_keep_DL_029CB0);
    gDPSetPrimColor(gfx++, 0, 0, 130, 0, 255, 100);
    gSPMatrix(gfx++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, gameplay_keep_DL_029CF0);

    POLY_XLU_DISP = gfx;

    CLOSE_DISPS(play->state.gfxCtx);
}
