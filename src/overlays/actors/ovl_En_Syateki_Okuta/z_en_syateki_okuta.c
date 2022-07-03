/*
 * File: z_en_syateki_okuta.c
 * Overlay: ovl_En_Syateki_Okuta
 * Description: Shooting Gallery Octorok
 */

#include "z_en_syateki_okuta.h"
#include "overlays/actors/ovl_En_Syateki_Man/z_en_syateki_man.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_8000000)

#define THIS ((EnSyatekiOkuta*)thisx)

void EnSyatekiOkuta_Init(Actor* thisx, PlayState* play);
void EnSyatekiOkuta_Destroy(Actor* thisx, PlayState* play);
void EnSyatekiOkuta_Update(Actor* thisx, PlayState* play);
void EnSyatekiOkuta_Draw(Actor* thisx, PlayState* play);

void func_80A36260(EnSyatekiOkuta* this);
void func_80A362A8(EnSyatekiOkuta* this, PlayState* play);
void func_80A362F8(EnSyatekiOkuta* this);
void func_80A36350(EnSyatekiOkuta* this, PlayState* play);
void func_80A363B4(EnSyatekiOkuta* this, PlayState* play);
void func_80A36444(EnSyatekiOkuta* this);
void func_80A36488(EnSyatekiOkuta* this, PlayState* play);
void func_80A364C0(EnSyatekiOkuta* this);
void func_80A36504(EnSyatekiOkuta* this, PlayState* play);
void func_80A365EC(EnSyatekiOkuta* this, PlayState* play);
void func_80A36CB0(EnSyatekiOkuta* this);

const ActorInit En_Syateki_Okuta_InitVars = {
    ACTOR_EN_SYATEKI_OKUTA,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_OKUTA,
    sizeof(EnSyatekiOkuta),
    (ActorFunc)EnSyatekiOkuta_Init,
    (ActorFunc)EnSyatekiOkuta_Destroy,
    (ActorFunc)EnSyatekiOkuta_Update,
    (ActorFunc)EnSyatekiOkuta_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT3,
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
    { 20, 40, -30, { 0, 0, 0 } },
};

static AnimationInfo sAnimations[] = {
    { &gOctorokShootAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &gOctorokDieAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &gOctorokHideAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &gOctorokFloatAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -1.0f },
    { &gOctorokAppearAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &gOctorokHitAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
};

#include "assets/overlays/ovl_En_Syateki_Okuta/ovl_En_Syateki_Okuta.c"

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, 66, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 6500, ICHAIN_STOP),
};

Color_RGBA8 D_80A37B90 = { 255, 255, 255, 255 };

Color_RGBA8 D_80A37B94 = { 150, 150, 150, 255 };

Vec3f D_80A37B98 = { 0.0f, -0.5, 0.0f };

Color_RGBA8 D_80A37BA4 = { 255, 255, 255, 255 };

Color_RGBA8 D_80A37BA8 = { 150, 150, 150, 0 };

void EnSyatekiOkuta_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnSyatekiOkuta* this = THIS;
    WaterBox* waterbox;
    f32 ySurface;
    s32 bgId;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    SkelAnime_Init(play, &this->skelAnime, &gOctorokSkel, &gOctorokAppearAnim, this->jointTable, this->morphTable,
                   OCTOROK_LIMB_MAX);
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);

    this->actor.floorHeight =
        BgCheck_EntityRaycastFloor5(&play->colCtx, &this->actor.floorPoly, &bgId, &this->actor, &this->actor.world.pos);

    if (!(WaterBox_GetSurface1_2(play, &play->colCtx, this->actor.world.pos.x, this->actor.world.pos.z, &ySurface,
                                 &waterbox)) ||
        (ySurface <= this->actor.floorHeight)) {
        Actor_MarkForDeath(&this->actor);
    } else {
        this->actor.world.pos.y = this->actor.home.pos.y = ySurface;
    }

    this->unk_2A4 = 0;
    this->unk_2AA = 0;
    func_80A36260(this);
}

void EnSyatekiOkuta_Destroy(Actor* thisx, PlayState* play) {
    EnSyatekiOkuta* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void func_80A36148(Vec3f* pos, Vec3f* velocity, s16 scaleStep, PlayState* play) {
    func_800B0DE0(play, pos, velocity, &gZeroVec3f, &D_80A37B90, &D_80A37B94, 400, scaleStep);
}

void func_80A361B0(EnSyatekiOkuta* this, PlayState* play) {
    EffectSsGSplash_Spawn(play, &this->actor.home.pos, NULL, NULL, 0, 800);
}

s32 func_80A361F4(EnSyatekiOkuta* this) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v1;
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    temp_v1 = EN_SYATEKI_OKUTA_GET_F(&this->actor);
    if ((temp_v1 == 1) || (temp_v1 == 4)) {
        temp_a0 = syatekiMan->octorokFlags;
        temp_a1 = (temp_v1 * 2) + 6;

        if ((temp_a0 >> temp_a1) & 3) {
            return true;
        }

        if ((temp_a1 == 8) && ((temp_a0 >> 0xE) & 3)) {
            return true;
        }
    }

    return false;
}

void func_80A36260(EnSyatekiOkuta* this) {
    Animation_PlayOnceSetSpeed(&this->skelAnime, &gOctorokAppearAnim, 0.0f);
    this->actor.draw = NULL;
    this->actionFunc = func_80A362A8;
}

void func_80A362A8(EnSyatekiOkuta* this, PlayState* play) {
    Actor* actorIt = play->actorCtx.actorLists[ACTORCAT_NPC].first;

    while (actorIt != NULL) {
        if (actorIt->id == ACTOR_EN_SYATEKI_MAN) {
            this->actor.parent = actorIt;
            func_80A362F8(this);
            break;
        } else {
            actorIt = actorIt->next;
        }
    }
}

void func_80A362F8(EnSyatekiOkuta* this) {
    Animation_PlayOnceSetSpeed(&this->skelAnime, &gOctorokAppearAnim, 0.0f);
    this->actor.draw = NULL;
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80A36350;
}

void func_80A36350(EnSyatekiOkuta* this, PlayState* play) {
}

void func_80A36360(EnSyatekiOkuta* this) {
    this->actor.draw = EnSyatekiOkuta_Draw;
    this->unk_2AA = 0;
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 4);
    this->actionFunc = func_80A363B4;
}

void func_80A363B4(EnSyatekiOkuta* this, PlayState* play) {
    if ((Animation_OnFrame(&this->skelAnime, 2.0f)) || (Animation_OnFrame(&this->skelAnime, 15.0f))) {
        if (func_80A361F4(this)) {
            return;
        } else {
            func_80A361B0(this, play);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_OCTAROCK_JUMP);
        }
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        func_80A36444(this);
    }
}

void func_80A36444(EnSyatekiOkuta* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
    this->actionFunc = func_80A36488;
}

void func_80A36488(EnSyatekiOkuta* this, PlayState* play) {
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    if (syatekiMan->perGameVar1.octorokState >= SG_OCTO_STATE_INITIAL) {
        func_80A364C0(this);
    }
}

void func_80A364C0(EnSyatekiOkuta* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
    this->actionFunc = func_80A36504;
}

void func_80A36504(EnSyatekiOkuta* this, PlayState* play) {
    if (Animation_OnFrame(&this->skelAnime, 4.0f)) {
        func_80A361B0(this, play);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_DAIOCTA_LAND);
    } else if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        func_80A362F8(this);
    }
}

void func_80A3657C(EnSyatekiOkuta* this) {
    this->unk_2A4 = 0;
    this->unk_2AA = 300;
    if (this->unk_2A6 == 1) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_OCTAROCK_DEAD1);
    }

    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
    this->actionFunc = func_80A365EC;
}

void func_80A365EC(EnSyatekiOkuta* this, PlayState* play) {
    Vec3f sp84;
    Vec3f sp78;
    s32 pad;
    s32 i;

    if (this->unk_2AA > 0) {
        this->unk_2AA -= 15;
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        if (this->unk_2A4 == 0) {
            sp78.x = this->actor.world.pos.x;
            sp78.y = this->actor.world.pos.y + 40.0f;
            sp78.z = this->actor.world.pos.z;
            sp84.x = 0.0f;
            sp84.y = -0.5f;
            sp84.z = 0.0f;
            func_80A36148(&sp78, &sp84, -20, play);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_OCTAROCK_DEAD2);
        }

        this->unk_2A4++;
    }

    if (Animation_OnFrame(&this->skelAnime, 15.0f)) {
        func_80A361B0(this, play);
    }

    if (this->unk_2A4 < 3) {
        Actor_SetScale(&this->actor, ((this->unk_2A4 * 0.25f) + 1.0f) * 0.01f);
    } else if (this->unk_2A4 < 6) {
        Actor_SetScale(&this->actor, (1.5f - ((this->unk_2A4 - 2) * 0.2333f)) * 0.01f);
    } else if (this->unk_2A4 < 11) {
        Actor_SetScale(&this->actor, (((this->unk_2A4 - 5) * 0.04f) + 0.8f) * 0.01f);
    } else {
        if (Math_StepToF(&this->actor.scale.x, 0.0f, 0.002f)) {
            SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 30, NA_SE_EN_COMMON_WATER_MID);
            for (i = 0; i < 10; i++) {
                sp84.x = (Rand_ZeroOne() - 0.5f) * 7.0f;
                sp84.y = Rand_ZeroOne() * 7.0f;
                sp84.z = (Rand_ZeroOne() - 0.5f) * 7.0f;
                EffectSsDtBubble_SpawnCustomColor(play, &this->actor.world.pos, &sp84, &D_80A37B98, &D_80A37BA4,
                                                  &D_80A37BA8, Rand_S16Offset(100, 50), 25, 0);
            }

            func_80A362F8(this);
        }

        this->actor.scale.y = this->actor.scale.x;
        this->actor.scale.z = this->actor.scale.x;
    }
}

void func_80A368E0(EnSyatekiOkuta* this, PlayState* play) {
    this->collider.dim.height =
        (sCylinderInit.dim.height - this->collider.dim.yShift) * this->unk_1D8.y * this->actor.scale.y * 100.0f;
    this->collider.dim.radius = sCylinderInit.dim.radius * this->actor.scale.x * 100.0f;

    if (this->actionFunc == func_80A363B4) {
        if ((this->unk_2A6 == 2) && func_80A361F4(this)) {
            return;
        }

        if (this->skelAnime.curFrame < (this->skelAnime.endFrame - 5.0f)) {
            this->collider.dim.height *= 1.35f;
        }
    }

    if (this->unk_2A6 == 1) {
        this->collider.dim.radius += 10;
        this->collider.dim.height += 15;
    }

    this->collider.dim.pos.x = this->actor.world.pos.x;
    // jointTable->y is the y-translation of the skeleton root
    this->collider.dim.pos.y = this->actor.world.pos.y + (this->skelAnime.jointTable->y * this->actor.scale.y);
    this->collider.dim.pos.z = this->actor.world.pos.z;
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
}

s32 func_80A36A90(EnSyatekiOkuta* this, PlayState* play) {
    if ((this->actionFunc == func_80A365EC) || (this->actionFunc == func_80A36350)) {
        return false;
    }

    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        return true;
    }

    func_80A368E0(this, play);
    return false;
}

void func_80A36AF8(EnSyatekiOkuta* this, PlayState* play) {
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;
    s16 temp_v1_2;

    if ((this->actionFunc != func_80A36488) && (this->actionFunc != func_80A363B4) &&
        (syatekiMan->shootingGameState == SG_GAME_STATE_RUNNING) &&
        (syatekiMan->perGameVar1.octorokState == SG_OCTO_STATE_SPAWNING)) {
        temp_v1_2 = (syatekiMan->octorokFlags >> (EN_SYATEKI_OKUTA_GET_F(&this->actor) * 2)) & 3;
        if (temp_v1_2 > 0) {
            Actor_SetScale(&this->actor, 0.01f);
            this->unk_2A6 = temp_v1_2;
            func_80A36360(this);
        }
    }
}

void EnSyatekiOkuta_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnSyatekiOkuta* this = THIS;
    EnSyatekiMan* syatekiMan;

    this->actionFunc(this, play);

    if (this->actionFunc != func_80A36350) {
        SkelAnime_Update(&this->skelAnime);
    }

    func_80A36AF8(this, play);

    if (func_80A36A90(this, play)) {
        syatekiMan = (EnSyatekiMan*)this->actor.parent;
        if (this->unk_2A6 == 1) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_SY_TRE_BOX_APPEAR);
            play->interfaceCtx.unk_25C++;
            syatekiMan->score++;
            syatekiMan->perGameVar2.octorokHitType = SG_OCTO_HIT_TYPE_RED;
        } else {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_SY_ERROR);
            syatekiMan->perGameVar2.octorokHitType = SG_OCTO_HIT_TYPE_BLUE;
        }

        func_80A3657C(this);
    } else {
        this->collider.base.acFlags &= ~AC_HIT;
    }

    func_80A36CB0(this);
}

void func_80A36CB0(EnSyatekiOkuta* this) {
    f32 curFrame = this->skelAnime.curFrame;

    if (this->actionFunc == func_80A363B4) {
        if (curFrame < 8.0f) {
            this->unk_1D8.x = this->unk_1D8.y = this->unk_1D8.z = 1.0f;
        } else if (curFrame < 10.0f) {
            this->unk_1D8.x = this->unk_1D8.z = 1.0f;
            this->unk_1D8.y = ((curFrame - 7.0f) * 0.4f) + 1.0f;
        } else if (curFrame < 14.0f) {
            this->unk_1D8.x = this->unk_1D8.z = ((curFrame - 9.0f) * 0.075f) + 1.0f;
            this->unk_1D8.y = 1.8f - ((curFrame - 9.0f) * 0.25f);
        } else {
            this->unk_1D8.x = this->unk_1D8.z = 1.3f - ((curFrame - 13.0f) * 0.05f);
            this->unk_1D8.y = ((curFrame - 13.0f) * 0.0333f) + 0.8f;
        }
    } else if (this->actionFunc == func_80A36488) {
        this->unk_1D8.x = this->unk_1D8.z = 1.0f;
        this->unk_1D8.y = (sin_rad((M_PI / 16) * curFrame) * 0.2f) + 1.0f;
    } else if (this->actionFunc == func_80A36504) {
        if (curFrame < 3.0f) {
            this->unk_1D8.y = 1.0f;
        } else if (curFrame < 4.0f) {
            this->unk_1D8.y = (curFrame - 2.0f) + 1.0f;
        } else {
            this->unk_1D8.y = 2.0f - ((curFrame - 3.0f) * 0.333f);
        }
        this->unk_1D8.x = this->unk_1D8.z = 1.0f;
    } else if (this->actionFunc == func_80A365EC) {
        curFrame += this->unk_2A4;
        if (curFrame >= 35.0f) {
            this->unk_1D8.x = this->unk_1D8.y = this->unk_1D8.z = 1.0f;
        } else if (curFrame < 4.0f) {
            this->unk_1D8.x = this->unk_1D8.z = 1.0f - (curFrame * 0.0666f);
            this->unk_1D8.y = (curFrame * 0.1666f) + 1.0f;
        } else if (curFrame < 25.0f) {
            this->unk_1D8.x = this->unk_1D8.z = ((curFrame - 4.0f) * 0.01f) + 0.8f;
            this->unk_1D8.y = 1.5f - ((curFrame - 4.0f) * 0.025f);
        } else if (curFrame < 27.0f) {
            this->unk_1D8.x = this->unk_1D8.y = this->unk_1D8.z = ((curFrame - 24.0f) * 0.25f) + 1.0f;
        } else if (curFrame < 30.0f) {
            this->unk_1D8.x = this->unk_1D8.y = this->unk_1D8.z = 1.5f - ((curFrame - 26.0f) * 0.233f);
        } else {
            this->unk_1D8.x = this->unk_1D8.y = this->unk_1D8.z = ((curFrame - 29.0f) * 0.04f) + 0.8f;
        }
    } else {
        this->unk_1D8.x = this->unk_1D8.y = this->unk_1D8.z = 1.0f;
    }
}

s32 func_80A370EC(EnSyatekiOkuta* this, f32 arg1, Vec3f* arg2) {
    if (this->actionFunc == func_80A363B4) {
        arg2->y = 1.0f;
        arg2->z = 1.0f;
        arg2->x = (sin_rad((M_PI / 16) * arg1) * 0.4f) + 1.0f;
    } else if (this->actionFunc == func_80A365EC) {
        if ((arg1 >= 35.0f) || (arg1 < 25.0f)) {
            return false;
        }

        if (arg1 < 27.0f) {
            arg2->z = 1.0f;
            arg2->x = arg2->y = ((arg1 - 24.0f) * 0.5f) + 1.0f;
        } else if (arg1 < 30.0f) {
            arg2->z = (arg1 - 26.0f) * 0.333f + 1.0f;
            arg2->x = arg2->y = 2.0f - (arg1 - 26.0f) * 0.333f;
        } else {
            arg2->z = 2.0f - ((arg1 - 29.0f) * 0.2f);
            arg2->x = arg2->y = 1.0f;
        }
    } else {
        return false;
    }

    return true;
}

s32 EnSyatekiOkuta_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    s32 pad;
    Vec3f sp20;
    f32 curFrame;
    EnSyatekiOkuta* this = THIS;

    curFrame = this->skelAnime.curFrame;
    if (this->actionFunc == func_80A365EC) {
        curFrame += this->unk_2A4;
    }

    if (limbIndex == OCTOROK_LIMB_HEAD) {
        sp20 = this->unk_1D8;
        Matrix_Scale(sp20.x, sp20.y, sp20.z, MTXMODE_APPLY);
    } else if ((limbIndex == OCTOROK_LIMB_SNOUT) && (func_80A370EC(this, curFrame, &sp20))) {
        Matrix_Scale(sp20.x, sp20.y, sp20.z, MTXMODE_APPLY);
    }

    return false;
}

void EnSyatekiOkuta_Draw(Actor* thisx, PlayState* play) {
    EnSyatekiOkuta* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    if (this->unk_2A6 == 1) {
        gSPSegment(POLY_OPA_DISP++, 0x08, D_801AEFA0);
    } else {
        gSPSegment(POLY_OPA_DISP++, 0x08, gShootingGalleryOctorokBlueMaterialDL);
    }

    SkelAnime_DrawOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, EnSyatekiOkuta_OverrideLimbDraw, NULL,
                      &this->actor);
    func_8012C2DC(play->state.gfxCtx);
    if (this->actionFunc == func_80A365EC) {
        Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y + 30.0f, this->actor.world.pos.z + 20.0f,
                         MTXMODE_NEW);

        if (this->unk_2AA >= 256) {
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 210, 64, 32, 255);
        } else {
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 210, 64, 32, this->unk_2AA);
        }

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        if (this->unk_2A6 == 2) {
            gSPDisplayList(POLY_XLU_DISP++, gShootingGalleryOctorokCrossDL);
        } else {
            gSPDisplayList(POLY_XLU_DISP++, gShootingGalleryOctorokCircleDL);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
