/*
 * File: z_en_light.c
 * Overlay: ovl_En_Light
 * Description: Deku Shrine - Flames of Varying Colours
 */

#include "z_en_light.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

#define FLAGS 0x00000000

void EnLight_Init(Actor* thisx, PlayState* play);
void EnLight_Destroy(Actor* thisx, PlayState* play);
void EnLight_Update(Actor* thisx, PlayState* play);
void EnLight_Draw(Actor* thisx, PlayState* play);

void EnLight_UpdateSwitch(Actor* thisx, PlayState* play);

ActorProfile En_Light_Profile = {
    /**/ ACTOR_EN_LIGHT,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(EnLight),
    /**/ EnLight_Init,
    /**/ EnLight_Destroy,
    /**/ EnLight_Update,
    /**/ EnLight_Draw,
};

typedef struct {
    /* 0x0 */ Color_RGBA8 primColor;
    /* 0x4 */ Color_RGB8 envColor;
    /* 0x7 */ u8 scale;
} EnLightStruct; // size = 0x8

EnLightStruct D_808666D0[] = {
    { { 255, 200, 0, 255 }, { 255, 0, 0 }, 75 },     { { 255, 235, 175, 255 }, { 255, 0, 0 }, 75 },
    { { 0, 170, 255, 255 }, { 0, 0, 255 }, 75 },     { { 170, 255, 0, 255 }, { 0, 150, 0 }, 75 },
    { { 255, 200, 0, 255 }, { 255, 0, 0 }, 40 },     { { 255, 200, 0, 255 }, { 255, 0, 0 }, 75 },
    { { 170, 255, 0, 255 }, { 0, 150, 0 }, 75 },     { { 0, 170, 255, 255 }, { 0, 0, 255 }, 75 },
    { { 255, 0, 170, 255 }, { 200, 0, 0 }, 75 },     { { 255, 255, 170, 255 }, { 255, 50, 0 }, 75 },
    { { 255, 255, 170, 255 }, { 255, 255, 0 }, 75 }, { { 255, 255, 170, 255 }, { 100, 255, 0 }, 75 },
    { { 255, 170, 255, 255 }, { 255, 0, 100 }, 75 }, { { 255, 170, 255, 255 }, { 100, 0, 255 }, 75 },
    { { 170, 255, 255, 255 }, { 0, 0, 255 }, 75 },   { { 170, 255, 255, 255 }, { 0, 150, 255 }, 75 },
};

void EnLight_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnLight* this = (EnLight*)thisx;

    if (!ENLIGHT_GET_4000(&this->actor)) {
        if ((gSaveContext.gameMode == GAMEMODE_END_CREDITS) || ENLIGHT_GET_2000(&this->actor)) {
            Lights_PointNoGlowSetInfo(&this->lightInfo, this->actor.world.pos.x,
                                      ((this->actor.params < 0) ? 1 : 40) + (s32)this->actor.world.pos.y,
                                      this->actor.world.pos.z, 255, 255, 180, -1);
        } else {
            Lights_PointGlowSetInfo(&this->lightInfo, this->actor.world.pos.x,
                                    ((this->actor.params < 0) ? 1 : 40) + (s32)this->actor.world.pos.y,
                                    this->actor.world.pos.z, 255, 255, 180, -1);
        }
        this->lightNode = LightContext_InsertLight(play, &play->lightCtx, &this->lightInfo);
    }

    Actor_SetScale(&this->actor, D_808666D0[ENLIGHT_GET_F(&this->actor)].scale * 0.0001f);

    this->timer = (s8)(Rand_ZeroOne() * 255.0f);

    if (ENLIGHT_GET_800(&this->actor)) {
        this->actor.update = EnLight_UpdateSwitch;
        if (ENLIGHT_GET_1000(&this->actor) && Flags_GetSwitch(play, ENLIGHT_SWITCH_FLAG(&this->actor))) {
            Actor_SetScale(&this->actor, 0.0f);
        }
    } else if (ENLIGHT_GET_2000(&this->actor)) {
        this->actor.draw = NULL;
    }
}

void EnLight_Destroy(Actor* thisx, PlayState* play) {
    EnLight* this = (EnLight*)thisx;

    if (!ENLIGHT_GET_4000(&this->actor)) {
        LightContext_RemoveLight(play, &play->lightCtx, this->lightNode);
    }
}

void EnLight_UpdatePosRot(EnLight* this, PlayState* play) {
    // update yaw for billboard effect
    this->actor.shape.rot.y = BINANG_ROT180(Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)));

    if (this->actor.parent != NULL) {
        Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.parent->world.pos);
        this->actor.world.pos.y += 17.0f;
    }

    this->timer++;
}

void EnLight_Update(Actor* thisx, PlayState* play) {
    EnLight* this = (EnLight*)thisx;

    if (!ENLIGHT_GET_4000(&this->actor)) {
        EnLightStruct* sp28 = &D_808666D0[ENLIGHT_GET_F(&this->actor)];
        f32 temp_f2 = (Rand_ZeroOne() * 0.5f) + 0.5f;
        s32 radius = (this->actor.params < 0) ? 100 : ENLIGHT_GET_2000(&this->actor) ? 730 : 300;

        Lights_PointSetColorAndRadius(&this->lightInfo, (u8)(sp28->primColor.r * temp_f2),
                                      (u8)(sp28->primColor.g * temp_f2), (u8)(sp28->primColor.b * temp_f2), radius);
    }

    EnLight_UpdatePosRot(this, play);

    if ((this->actor.params >= 0) && !ENLIGHT_GET_4000(&this->actor)) {
        Actor_PlaySfx(&this->actor, NA_SE_EV_TORCH - SFX_FLAG);
    }
}

void EnLight_UpdateSwitch(Actor* thisx, PlayState* play) {
    EnLight* this = (EnLight*)thisx;
    EnLightStruct* sp38 = &D_808666D0[ENLIGHT_GET_F(&this->actor)];
    f32 temp_f2;
    f32 scale = this->actor.scale.x / (sp38->scale * 0.0001f);
    s32 sp2C = false;

    if (ENLIGHT_GET_1000(&this->actor)) {
        if (Flags_GetSwitch(play, ENLIGHT_SWITCH_FLAG(&this->actor))) {
            Math_StepToF(&scale, 1.0f, 0.05f);
            sp2C = true;
        } else {
            if (scale < 0.1f) {
                Actor_SetScale(&this->actor, 0.0f);
                scale = 0.0f;
            }
            Math_StepToF(&scale, 0.0f, 0.05f);
        }
    } else if (Flags_GetSwitch(play, ENLIGHT_SWITCH_FLAG(&this->actor))) {
        if (scale < 0.1f) {
            Actor_SetScale(&this->actor, 0.0f);
            scale = 0.0f;
        }
        Math_StepToF(&scale, 0.0f, 0.05f);
    } else {
        Math_StepToF(&scale, 1.0f, 0.05f);
        sp2C = true;
    }

    Actor_SetScale(&this->actor, sp38->scale * 0.0001f * scale);

    if (!ENLIGHT_GET_4000(&this->actor)) {
        temp_f2 = (Rand_ZeroOne() * 0.5f) + 0.5f;
        Lights_PointSetColorAndRadius(&this->lightInfo, (u8)(sp38->primColor.r * temp_f2),
                                      (u8)(sp38->primColor.g * temp_f2), (u8)(sp38->primColor.b * temp_f2),
                                      300.0f * scale);
    }

    EnLight_UpdatePosRot(this, play);

    if ((this->actor.params >= 0) && (sp2C == true)) {
        Actor_PlaySfx(&this->actor, NA_SE_EV_TORCH - SFX_FLAG);
    }
}

void EnLight_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    EnLight* this = (EnLight*)thisx;
    EnLightStruct* sp6C = &D_808666D0[ENLIGHT_GET_F(&this->actor)];
    Gfx* dList;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);

    if (this->actor.params >= 0) {
        gSPSegment(
            POLY_XLU_DISP++, 0x08,
            Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0, (this->timer * -20) & 0x1FF, 0x20, 0x80));
        dList = gEffFire1DL;
        gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, sp6C->primColor.r, sp6C->primColor.g, sp6C->primColor.b,
                        sp6C->primColor.a);
        gDPSetEnvColor(POLY_XLU_DISP++, sp6C->envColor.r, sp6C->envColor.g, sp6C->envColor.b, 0);
    } else {
        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, 0, 0x10, 0x20, 1, (this->timer * 2) & 0x3F,
                                    (this->timer * -6) & 0x7F, 0x10, 0x20));
        dList = gameplay_keep_DL_01ACF0;
        gDPSetPrimColor(POLY_XLU_DISP++, 0xC0, 0xC0, 255, 200, 0, 0);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 0, 0);
    }

    Matrix_RotateYS(BINANG_ROT180(Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)) - this->actor.shape.rot.y), MTXMODE_APPLY);

    if (ENLIGHT_GET_1(&this->actor)) {
        Matrix_RotateYF(M_PIf, MTXMODE_APPLY);
    }

    Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);

    MATRIX_FINALIZE_AND_LOAD(POLY_XLU_DISP++, play->state.gfxCtx);
    gSPDisplayList(POLY_XLU_DISP++, dList);

    CLOSE_DISPS(play->state.gfxCtx);
}
