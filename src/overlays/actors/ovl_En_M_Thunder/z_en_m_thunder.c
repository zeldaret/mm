/*
 * File: z_en_m_thunder.c
 * Overlay: ovl_En_M_Thunder
 * Description: Spin attack and sword beams
 */

#include "z_en_m_thunder.h"
#include "z64rumble.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnMThunder*)thisx)

void EnMThunder_Init(Actor* thisx, PlayState* play);
void EnMThunder_Destroy(Actor* thisx, PlayState* play);
void EnMThunder_Update(Actor* thisx, PlayState* play);
void EnMThunder_Draw(Actor* thisx, PlayState* play);

void func_808B65BC(Actor* thisx, PlayState* play);

void func_808B5890(PlayState* play, f32 arg1);

void func_808B5984(EnMThunder* this, PlayState* play);
void func_808B5F68(EnMThunder* this, PlayState* play);
void func_808B60D4(EnMThunder* this, PlayState* play);
void func_808B6310(EnMThunder* this, PlayState* play);

const ActorInit En_M_Thunder_InitVars = {
    ACTOR_EN_M_THUNDER,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnMThunder),
    (ActorFunc)EnMThunder_Init,
    (ActorFunc)EnMThunder_Destroy,
    (ActorFunc)EnMThunder_Update,
    (ActorFunc)EnMThunder_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808B7120 = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_PLAYER,
        AC_NONE,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0x01000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NONE,
        BUMP_ON,
        OCELEM_ON,
    },
    { 200, 200, 0, { 0, 0, 0 } },
};

u8 D_808B714C[] = { 1, 2, 3, 4, 1, 2, 3, 4 };
u16 D_808B7154[] = { NA_SE_IT_ROLLING_CUT_LV2, NA_SE_IT_ROLLING_CUT_LV1, NA_SE_IT_ROLLING_CUT_LV2, NA_SE_IT_ROLLING_CUT_LV1 };
f32 D_808B715C[] = { 0.1f, 0.15f, 0.2f, 0.25f, 0.3f, 0.25f, 0.2f, 0.15f, 0.0f };

void func_808B53C0(EnMThunder* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    this->actor.update = func_808B65BC;
    this->unk1C2 = 0;
    this->unk1BE = 1;
    this->unk1C1 = 2;
    this->actionFunc = func_808B6310;
    this->unk1BC = 8;
    this->unk1A4 = 1.0f;
    Audio_PlaySfxGeneral(NA_SE_IT_ROLLING_CUT_LV1, &player->actor.projectedPos, 4, &D_801DB4B0, &D_801DB4B0,
                         &gSfxDefaultReverb);
    this->actor.child = NULL;
}

void EnMThunder_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnMThunder* this = THIS;
    Player* player = GET_PLAYER(play);

    Collider_InitCylinder(play, &this->unk144);
    Collider_SetCylinder(play, &this->unk144, &this->actor, &D_808B7120);
    this->unk1BF = ENMTHUNDER_GET_UNK1BF(&this->actor);
    Lights_PointNoGlowSetInfo(&this->unk194, this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                              255, 255, 255, 0);
    this->unk190 = LightContext_InsertLight(play, &play->lightCtx, &this->unk194);

    if (this->unk1BF == 0x80) {
        func_808B53C0(this, play);
        return;
    }
    this->unk144.dim.radius = 0;
    this->unk144.dim.height = 40;
    this->unk144.dim.yShift = -20;
    this->unk1BC = 8;
    this->unk1AC = 0.0f;
    this->actor.world.pos = player->bodyPartsPos[0];
    this->unk1A4 = 0.0f;
    this->unk1B4 = 0.0f;
    this->actor.shape.rot.y = player->actor.shape.rot.y + 0x8000;
    this->actor.shape.rot.x = -this->actor.world.rot.x;
    this->actor.room = -1;
    Actor_SetScale(&this->actor, 0.1f);
    this->unk1C2 = 0;

    if (player->stateFlags2 & PLAYER_STATE2_20000) {
        if (!gSaveContext.save.playerData.magicAcquired || (gSaveContext.unk_3F28 != 0) ||
            ((ENMTHUNDER_GET_MAGIC_COST(&this->actor) != 0) &&
             !func_80115DB4(play, ENMTHUNDER_GET_MAGIC_COST(&this->actor), 0))) {
            Audio_PlaySfxGeneral(NA_SE_IT_ROLLING_CUT, &player->actor.projectedPos, 4, &D_801DB4B0, &D_801DB4B0,
                                 &gSfxDefaultReverb);
            Audio_PlaySfxGeneral(NA_SE_IT_SWORD_SWING_HARD, &player->actor.projectedPos, 4, &D_801DB4B0, &D_801DB4B0,
                                 &gSfxDefaultReverb);
            Actor_MarkForDeath(&this->actor);
            return;
        }
        player->stateFlags2 &= ~PLAYER_STATE2_20000;
        this->unk1C2 = 0;
        if (gSaveContext.save.weekEventReg[23] & 2) {
            player->unk_B08[0] = 1.0f;
            this->unk144.info.toucher.damage = D_808B714C[this->unk1BF + 4];
            this->unk1BE = 0;
            if (this->unk1BF == 3) {
                this->unk1C1 = 6;
            } else if (this->unk1BF == 2) {
                this->unk1C1 = 4;
            } else {
                this->unk1C1 = 3;
            }
        } else {
            player->unk_B08[0] = 0.5f;
            this->unk144.info.toucher.damage = D_808B714C[this->unk1BF];
            this->unk1BE = 1;
            if (this->unk1BF == 3) {
                this->unk1C1 = 4;
            } else if (this->unk1BF == 2) {
                this->unk1C1 = 3;
            } else {
                this->unk1C1 = 2;
            }
        }
        if (player->meleeWeaponAnimation < 30) {
            this->unk1BE += 2;
            this->actionFunc = func_808B60D4;
            this->unk1BC = 1;
            this->unk1C1 = 12;
            this->unk144.info.toucher.dmgFlags = 0x02000000;
            this->unk144.info.toucher.damage = 3;
        } else {
            this->actionFunc = func_808B5F68;
            this->unk1BC = 8;
        }
        Audio_PlaySfxGeneral(NA_SE_IT_ROLLING_CUT_LV1, &player->actor.projectedPos, 4, &D_801DB4B0, &D_801DB4B0,
                             &gSfxDefaultReverb);
        this->unk1A4 = 1.0f;
    } else {
        this->actionFunc = func_808B5984;
    }
    this->actor.child = NULL;
}

void EnMThunder_Destroy(Actor* thisx, PlayState* play) {
    EnMThunder* this = THIS;

    if (this->unk1C2 != 0) {
        func_80115D5C(&play->state);
    }
    Collider_DestroyCylinder(play, &this->unk144);
    func_808B5890(play, 0.0f);
    LightContext_RemoveLight(play, &play->lightCtx, this->unk190);
}

void func_808B5890(PlayState* play, f32 arg1) {
    func_800FD2B4(play, arg1, 850.0f, 0.2f, 0.0f);
}

void func_808B58CC(EnMThunder* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (player->stateFlags2 & PLAYER_STATE2_20000) {
        if (player->meleeWeaponAnimation >= 30) {
            Audio_PlaySfxGeneral(NA_SE_IT_ROLLING_CUT, &player->actor.projectedPos, 4, &D_801DB4B0, &D_801DB4B0,
                                 &gSfxDefaultReverb);
            Audio_PlaySfxGeneral(NA_SE_IT_SWORD_SWING_HARD, &player->actor.projectedPos, 4, &D_801DB4B0, &D_801DB4B0,
                                 &gSfxDefaultReverb);
        }
        Actor_MarkForDeath(&this->actor);
    } else if (!(player->stateFlags1 & PLAYER_STATE1_1000)) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_808B5984(EnMThunder* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Actor* child = this->actor.child;

    this->unk1B0 = player->unk_B08[0];
    this->actor.world.pos = player->bodyPartsPos[0];
    this->actor.shape.rot.y = player->actor.shape.rot.y + 0x8000;

    if ((this->unk1C2 == 0) && (player->unk_B08[0] >= 0.1f)) {
        if ((gSaveContext.unk_3F28 != 0) || ((ENMTHUNDER_GET_MAGIC_COST(&this->actor) != 0) &&
                                             !func_80115DB4(play, ENMTHUNDER_GET_MAGIC_COST(&this->actor), 4))) {
            func_808B58CC(this, play);
            this->actionFunc = func_808B58CC;
            this->unk1C0 = 0;
            this->unk1B4 = 0.0f;
            this->unk1A4 = 0.0f;
            return;
        }
        this->unk1C2 = 1;
    }

    if (player->unk_B08[0] >= 0.1f) {
        Rumble_Request(0.0f, (s32)(player->unk_B08[0] * 150.0f), 2, (s32)(player->unk_B08[0] * 150.0f));
    }

    if (player->stateFlags2 & PLAYER_STATE2_20000) {
        if ((child != NULL) && (child->update != NULL)) {
            child->parent = NULL;
        }
        if (player->unk_B08[0] <= 0.15f) {
            if ((player->unk_B08[0] >= 0.1f) && (player->meleeWeaponAnimation >= 30)) {
                Audio_PlaySfxGeneral(NA_SE_IT_ROLLING_CUT, &player->actor.projectedPos, 4, &D_801DB4B0, &D_801DB4B0,
                                     &gSfxDefaultReverb);
                Audio_PlaySfxGeneral(NA_SE_IT_SWORD_SWING_HARD, &player->actor.projectedPos, 4, &D_801DB4B0,
                                     &D_801DB4B0, &gSfxDefaultReverb);
            }
            Actor_MarkForDeath(&this->actor);
            return;
        }
        player->stateFlags2 &= ~PLAYER_STATE2_20000;
        if (ENMTHUNDER_GET_MAGIC_COST(&this->actor) != 0) {
            gSaveContext.unk_3F28 = 1;
        }
        if (player->unk_B08[0] < 0.85f) {
            this->unk144.info.toucher.damage = D_808B714C[this->unk1BF];
            this->unk1BE = 1;
            if (this->unk1BF == 3) {
                this->unk1C1 = 4;
            } else if (this->unk1BF == 2) {
                this->unk1C1 = 3;
            } else {
                this->unk1C1 = 2;
            }
        } else {
            this->unk144.info.toucher.damage = D_808B714C[this->unk1BF + 4];
            this->unk1BE = 0;
            if (this->unk1BF == 3) {
                this->unk1C1 = 6;
            } else if (this->unk1BF == 2) {
                this->unk1C1 = 4;
            } else {
                this->unk1C1 = 3;
            }
        }
        if (player->meleeWeaponAnimation < 30) {
            this->unk1BE += 2;
            this->actionFunc = func_808B60D4;
            this->unk1BC = 1;
        } else {
            this->actionFunc = func_808B5F68;
            this->unk1BC = 8;
        }
        Audio_PlaySfxGeneral(D_808B7154[this->unk1BE], &player->actor.projectedPos, 4, &D_801DB4B0, &D_801DB4B0,
                             &gSfxDefaultReverb);
        this->unk1A4 = 1.0f;
        return;
    }

    if (!(player->stateFlags1 & PLAYER_STATE1_1000)) {
        if (this->actor.child != NULL) {
            this->actor.child->parent = NULL;
        }
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (player->unk_B08[0] > 0.15f) {
        this->unk1C0 = 0xFF;
        if (this->actor.child == NULL) {
            Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EFF_DUST, this->actor.world.pos.x,
                               this->actor.world.pos.y, this->actor.world.pos.z, 0, this->actor.shape.rot.y, 0, 2);
        }
        this->unk1B4 += (((player->unk_B08[0] - 0.15f) * 1.5f) - this->unk1B4) * 0.5f;
    } else if (player->unk_B08[0] > .1f) {
        this->unk1C0 = (s32)((player->unk_B08[0] - .1f) * 255.0f * 20.0f);
        this->unk1A4 = (player->unk_B08[0] - .1f) * 10.0f;
    } else {
        this->unk1C0 = 0;
    }
    if (player->unk_B08[0] > 0.85f) {
        func_8019F900(&player->actor.projectedPos, 2);
    } else if (player->unk_B08[0] > 0.15f) {
        func_8019F900(&player->actor.projectedPos, 1);
    } else if (player->unk_B08[0] > 0.1f) {
        func_8019F900(&player->actor.projectedPos, 0);
    }

    if (Play_InCsMode(play)) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_808B5EEC(EnMThunder* this, PlayState* play) {
    if (this->unk1BC < 2) {
        if (this->unk1C0 < 40) {
            this->unk1C0 = 0;
        } else {
            this->unk1C0 -= 40;
        }
    }

    this->unk1AC += 2.0f * this->unk1A8;

    if (this->unk1B4 < this->unk1A4) {
        this->unk1B4 = F32_LERPIMP(this->unk1B4, this->unk1A4, 0.1f);
    } else {
        this->unk1B4 = this->unk1A4;
    }
}

void func_808B5F68(EnMThunder* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (Math_StepToF(&this->unk1A4, 0.0f, 0.0625f)) {
        Actor_MarkForDeath(&this->actor);
    } else {
        Math_SmoothStepToF(&this->actor.scale.x, (s32)this->unk1C1, 0.6f, 0.8f, 0.0f);
        Actor_SetScale(&this->actor, this->actor.scale.x);
        this->unk144.dim.radius = this->actor.scale.x * 30.0f;
        Collider_UpdateCylinder(&this->actor, &this->unk144);
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->unk144.base);
    }

    if (this->unk1BC > 0) {
        this->actor.world.pos.x = player->bodyPartsPos[0].x;
        this->actor.world.pos.z = player->bodyPartsPos[0].z;
        this->unk1BC--;
    }

    if (this->unk1A4 > (6.0f / 10.0f)) {
        this->unk1A8 = 1.0f;
    } else {
        this->unk1A8 = this->unk1A4 * (10.0f / 6.0f);
    }

    func_808B5EEC(this, play);

    if (Play_InCsMode(play)) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_808B60D4(EnMThunder* this, PlayState* play) {
    s32 pad[2];
    f32 sp2C;

    if (this->unk1A4 > (9.0f / 10.0f)) {
        this->unk1A8 = 1.0f;
    } else {
        this->unk1A8 = this->unk1A4 * (10.0f / 9.0f);
    }
    if (Math_StepToF(&this->unk1A4, 0.0f, 0.05f)) {
        Actor_MarkForDeath(&this->actor);
    } else {
        sp2C = -80.0f * Math_CosS(this->actor.world.rot.x);

        this->actor.world.pos.x += sp2C * Math_SinS(this->actor.shape.rot.y);
        this->actor.world.pos.z += sp2C * Math_CosS(this->actor.shape.rot.y);
        this->actor.world.pos.y += -80.0f * Math_SinS(this->actor.world.rot.x);

        Math_SmoothStepToF(&this->actor.scale.x, this->unk1C1, 0.6f, 2.0f, 0.0f);
        Actor_SetScale(&this->actor, this->actor.scale.x);

        this->unk144.dim.radius = this->actor.scale.x * 5.0f;

        this->unk144.dim.pos.x = this->actor.world.pos.x;
        this->unk144.dim.pos.y = this->actor.world.pos.y;
        this->unk144.dim.pos.z = this->actor.world.pos.z;

        this->unk144.dim.pos.x =
            (Math_SinS(this->actor.shape.rot.y) * -5.0f * this->actor.scale.x) + this->actor.world.pos.x;
        this->unk144.dim.pos.y = this->actor.world.pos.y;
        this->unk144.dim.pos.z =
            (Math_CosS(this->actor.shape.rot.y) * -5.0f * this->actor.scale.z) + this->actor.world.pos.z;

        CollisionCheck_SetAT(play, &play->colChkCtx, &this->unk144.base);
    }
    if (this->unk1BC > 0) {
        this->unk1BC--;
    }
    func_808B5EEC(this, play);
}

void func_808B6310(EnMThunder* this, PlayState* play) {
    if (Math_StepToF(&this->unk1A4, 0.0f, 0.0625f)) {
        Actor_MarkForDeath(&this->actor);
    } else {
        Math_SmoothStepToF(&this->actor.scale.x, (s32)this->unk1C1, 0.6f, 0.8f, 0.0f);
        Actor_SetScale(&this->actor, this->actor.scale.x);
    }

    if (this->unk1A4 > (6.0f / 10.0f)) {
        this->unk1A8 = 1.0f;
    } else {
        this->unk1A8 = this->unk1A4 * (10.0f / 6.0f);
    }
    func_808B5EEC(this, play);
}

void EnMThunder_Update(Actor* thisx, PlayState* play) {
    EnMThunder* this = THIS;

    this->actionFunc(this, play);
    func_808B5890(play, this->unk1B4);
    Lights_PointNoGlowSetInfo(&this->unk194, this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                              this->unk1A4 * 255.0f, this->unk1A4 * 255.0f, this->unk1A4 * 100.0f,
                              this->unk1A4 * 800.0f);
}

void func_808B65BC(Actor* thisx, PlayState* play) {
    EnMThunder* this = THIS;

    this->actionFunc(this, play);
    Lights_PointNoGlowSetInfo(&this->unk194, this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                              this->unk1A4 * 255.0f, this->unk1A4 * 255.0f, this->unk1A4 * 100.0f,
                              this->unk1A4 * 800.0f);
}

void EnMThunder_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnMThunder* this = THIS;
    Player* player = GET_PLAYER(play);
    f32 scale;
    s32 spA4;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C2DC(play->state.gfxCtx);
    Matrix_Scale(0.02f, 0.02f, 0.02f, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    switch (this->unk1BE) {
        case 0:
        case 1:
            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0xFF - ((u16)(s32)(this->unk1AC * 30.0f) & 0xFF), 0, 64,
                                        32, 1, 0xFF - ((u16)(s32)(this->unk1AC * 20.0f) & 0xFF), 0, 8, 8));
            break;

        case 2:
        case 3:
            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, 0, 16, 64, 1, 0,
                                        0x1FF - ((u16)(s32)(this->unk1AC * 10.0f) & 0x1FF), 32, 128));
            break;

        default:
            break;
    }

    switch (this->unk1BE) {
        case 0:
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 170, (u16)(this->unk1A8 * 255.0f));
            gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_025DD0);
            gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_025EF0);
            break;

        case 1:
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 170, 255, 255, (u16)(this->unk1A8 * 255.0f));
            gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_025850);
            gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_025970);
            break;

        case 3:
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 170, 255, 255, (u16)(this->unk1A8 * 255.0f));
            gDPSetEnvColor(POLY_XLU_DISP++, 0, 100, 255, 128);
            gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_027CA0);
            break;

        case 2:
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 0, 255, 255, (u16)(this->unk1A8 * 255.0f));
            gDPSetEnvColor(POLY_XLU_DISP++, 200, 200, 200, 128);
            gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_027CA0);
            break;

        default:
            break;
    }

    Matrix_Mult(&player->mf_CC4, MTXMODE_NEW);

    if (this->unk1BF == 2) {
        Matrix_Translate(0.0f, 220.0f, 0.0f, MTXMODE_APPLY);
        Matrix_Scale(-1.2f, -0.8f, -0.6f, MTXMODE_APPLY);
        Matrix_RotateXS(0x4000, MTXMODE_APPLY);
    } else {
        Matrix_Translate(0.0f, 220.0f, 0.0f, MTXMODE_APPLY);
        Matrix_Scale(-0.7f, -0.6f, -0.4f, MTXMODE_APPLY);
        Matrix_RotateXS(0x4000, MTXMODE_APPLY);
    }
    if (this->unk1B0 >= 0.85f) {
        scale = (D_808B715C[play->gameplayFrames & 7] * 6.0f) + 1.0f;
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 170, this->unk1C0);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 100, 0, 128);
        spA4 = 40;
    } else {
        scale = (D_808B715C[play->gameplayFrames & 7] * 2.0f) + 1.0f;
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 170, 255, 255, this->unk1C0);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 100, 255, 128);
        spA4 = 20;
    }

    Matrix_Scale(1.0f, scale, scale, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_XLU_DISP++, 0x09,
               Gfx_TwoTexScroll(play->state.gfxCtx, 0, (play->gameplayFrames * 5) & 0xFF, 0, 32, 32, 1,
                                (play->gameplayFrames * 20) & 0xFF, (play->gameplayFrames * spA4) & 0xFF, 8, 8));
    gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_0268F0);

    CLOSE_DISPS(play->state.gfxCtx);
}
