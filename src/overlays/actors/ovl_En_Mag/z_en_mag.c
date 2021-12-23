/*
 * File: z_en_mag.c
 * Overlay: ovl_En_Mag
 * Description: Title Logo
 */

#include "z_en_mag.h"
#include "objects/object_mag/object_mag.h"

#define FLAGS 0x00000030

#define THIS ((EnMag*)thisx)

void EnMag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMag_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMag_Draw(Actor* thisx, GlobalContext* globalCtx);

static s16 D_8096E910 = 0; // case 13 timer

static s16 sZeldaEffectColorTimer = 30;
static s16 sZeldaEffectColorTargetIndex = 0;

static s16 sTextAlphaTargetIndex = 0;
static s16 sTextAlphaTimer = 20;

const ActorInit En_Mag_InitVars = {
    ACTOR_EN_MAG,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_MAG,
    sizeof(EnMag),
    (ActorFunc)EnMag_Init,
    (ActorFunc)EnMag_Destroy,
    (ActorFunc)EnMag_Update,
    (ActorFunc)EnMag_Draw,
};

void EnMag_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnMag* this = (EnMag*)thisx;
    u16 i;

    this->unk11F54 = 6;
    this->unk11F56 = 10;

    for (i = 0; i < 6; i++) {
        this->unk11F36[i] = 0;
        this->unk11F44[i] = 0;
    }

    this->majorasMaskEffectPrimColor[0] = 255;
    this->majorasMaskEffectPrimColor[1] = 155;
    this->majorasMaskEffectPrimColor[2] = 255;
    this->majorasMaskEffectEnvColor[0] = 0;
    this->majorasMaskEffectEnvColor[1] = 255;
    this->majorasMaskEffectEnvColor[2] = 155;
    this->majorasMaskEffectPrimLodFrac = 20;
    this->majorasMaskEffectAlpha = 0;

    this->zeldaEffectPrimColor[0] = 255;
    this->zeldaEffectPrimColor[1] = 155;
    this->zeldaEffectPrimColor[2] = 255;
    this->zeldaEffectEnvColor[0] = 0;
    this->zeldaEffectEnvColor[1] = 255;
    this->zeldaEffectEnvColor[2] = 155;
    this->zeldaEffectPrimLodFrac = 55;
    this->zeldaEffectAlpha = 0;

    this->majorasMaskAlpha = 0;
    this->majorasMaskEnvColor[0] = this->majorasMaskEnvColor[1] = this->majorasMaskEnvColor[2] = 255;

    this->mainTitleAlpha = this->subtitleAlpha = this->unk11F32 = this->copyrightAlpha = 0;

    this->unk11F02 = 30;
    this->unk11F00 = this->unk11F04 = 0;

    if (gSaveContext.unk_3F1E != 0) {
        this->mainTitleAlpha = 210;
        this->unk11F32 = 255;
        this->copyrightAlpha = 255;

        this->majorasMaskEffectPrimLodFrac = 100;
        this->majorasMaskEffectAlpha = 255;
        this->majorasMaskEffectPrimColor[0] = 255;
        this->majorasMaskEffectPrimColor[1] = 255;
        this->majorasMaskEffectPrimColor[2] = 255;
        this->majorasMaskEffectEnvColor[0] = 0;
        this->majorasMaskEffectEnvColor[1] = 255;
        this->majorasMaskEffectEnvColor[2] = 155;

        this->zeldaEffectPrimLodFrac = 100;
        this->zeldaEffectAlpha = 255;
        this->zeldaEffectPrimColor[0] = 255;
        this->zeldaEffectPrimColor[1] = 255;
        this->zeldaEffectPrimColor[2] = 255;
        this->zeldaEffectEnvColor[0] = 0;
        this->zeldaEffectEnvColor[1] = 255;
        this->zeldaEffectEnvColor[2] = 155;

        gSaveContext.unk_3F1E = 0;
        this->unk11F04 = 2;
        D_8096E910 = 20;
        gSaveContext.fadeDuration = 1;
        gSaveContext.unk_3F51 = 255;
    }

    Font_LoadOrderedFont(&this->font);

    this->unk11F58 = 0;
    this->unk11F5A = 0;
    this->unk11F5C = 0;
    this->unk11F60 = 0;

    this->unk11F64 = 25;
    this->unk11F66 = 25;
    this->unk11F68 = 20;
    this->unk11F6A = 40;
    this->unk11F6C = 10;
    this->unk11F6E = 10;
    this->unk11F70 = 15;

    sZeldaEffectColorTimer = 30;
    sZeldaEffectColorTargetIndex = 0;
}

void EnMag_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

/**
 * Steps `var` towards `target` linearly, so that it will arrive in `timeRemaining` seconds. Can be used from either
 * direction. `timeRemaining` must be decremented separately for this to work properly, and obviously timeRemaining = 0
 * must be handled separately.
 *
 * @param var Variable to step.
 * @param target Target to step towards.
 * @param timeRemaining Number of times this function should be run for `var` to reach `target`
 * @param stepVar Variable to use for the step (required to match).
 *
 * The progression is not quite linear because of truncation in the division, but the variable will always reach
 * `target` at the appropriate time since the last step is always the full difference.
 */
#define TIMED_STEP_TO(var, target, timeRemaining, stepVar) \
    {                                                      \
        stepVar = ABS_ALT(var - target) / timeRemaining;   \
        if (var >= target) {                               \
            var -= stepVar;                                \
        } else {                                           \
            var += stepVar;                                \
        }                                                  \
    }                                                      \
    (void)0

/**
 * Similar to `TIMED_STEP_TO`, but will always increase `var`. If var > target, this will eventually increase `var` by
 * an amount that is at most ( timeRemaining + 1 ) * | var - target |, but which depends on the amount lost to
 * truncation from the divisions.
 */
#define TIMED_STEP_UP_TO(var, target, timeRemaining, stepVar) \
    {                                                         \
        stepVar = ABS_ALT(var - target) / timeRemaining;      \
        var += stepVar;                                       \
    }                                                         \
    (void)0

/**
 * Similar to `TIMED_STEP_TO`, but will always increase `var`. If var < target, this will eventually dncrease `var` by
 * an amount that is at most ( timeRemaining + 1 ) * | var - target |, but which depends on the amount lost to
 * truncation from the divisions.
 */
#define TIMED_STEP_DOWN_TO(var, target, timeRemaining, stepVar) \
    {                                                           \
        stepVar = ABS_ALT(var - target) / timeRemaining;        \
        var -= stepVar;                                         \
    }                                                           \
    (void)0

// EnMag_UpdateZeldaEffectColors ?
void func_8096B604(Actor* thisx) {
    static s16 sZeldaEffectPrimRedTargets[] = { 155, 255 };
    static s16 sZeldaEffectPrimGreenTargets[] = { 255, 155 };
    static s16 sZeldaEffectPrimBlueTargets[] = { 55, 255 };
    static s16 sZeldaEffectEnvRedTargets[] = { 255, 0 };
    static s16 sZeldaEffectEnvBlueTargets[] = { 255, 155 };
    EnMag* this = THIS;
    s16 colorStep;

    TIMED_STEP_TO(this->zeldaEffectPrimColor[0], sZeldaEffectPrimRedTargets[sZeldaEffectColorTargetIndex],
                  sZeldaEffectColorTimer, colorStep);
    TIMED_STEP_TO(this->zeldaEffectPrimColor[1], sZeldaEffectPrimGreenTargets[sZeldaEffectColorTargetIndex],
                  sZeldaEffectColorTimer, colorStep);
    TIMED_STEP_TO(this->zeldaEffectPrimColor[2], sZeldaEffectPrimBlueTargets[sZeldaEffectColorTargetIndex],
                  sZeldaEffectColorTimer, colorStep);
    TIMED_STEP_TO(this->zeldaEffectEnvColor[0], sZeldaEffectEnvRedTargets[sZeldaEffectColorTargetIndex],
                  sZeldaEffectColorTimer, colorStep);
    // Skips 1, i.e. green.
    TIMED_STEP_TO(this->zeldaEffectEnvColor[2], sZeldaEffectEnvBlueTargets[sZeldaEffectColorTargetIndex],
                  sZeldaEffectColorTimer, colorStep);

    // colorStep = ABS_ALT(this->zeldaEffectPrimColor[0] - sZeldaEffectPrimRedTargets[sZeldaEffectColorTargetIndex]) /
    // sZeldaEffectColorTimer; if (this->zeldaEffectPrimColor[0] >=
    // sZeldaEffectPrimRedTargets[sZeldaEffectColorTargetIndex]) {
    //     this->zeldaEffectPrimColor[0] -= colorStep;
    // } else {
    //     this->zeldaEffectPrimColor[0] += colorStep;
    // }

    // colorStep = ABS_ALT(this->zeldaEffectPrimColor[1] - sZeldaEffectPrimGreenTargets[sZeldaEffectColorTargetIndex]) /
    // sZeldaEffectColorTimer; if (this->zeldaEffectPrimColor[1] >=
    // sZeldaEffectPrimGreenTargets[sZeldaEffectColorTargetIndex]) {
    //     this->zeldaEffectPrimColor[1] -= colorStep;
    // } else {
    //     this->zeldaEffectPrimColor[1] += colorStep;
    // }

    // colorStep = ABS_ALT(this->zeldaEffectPrimColor[2] - sZeldaEffectPrimBlueTargets[sZeldaEffectColorTargetIndex]) /
    // sZeldaEffectColorTimer; if (this->zeldaEffectPrimColor[2] >=
    // sZeldaEffectPrimBlueTargets[sZeldaEffectColorTargetIndex]) {
    //     this->zeldaEffectPrimColor[2] -= colorStep;
    // } else {
    //     this->zeldaEffectPrimColor[2] += colorStep;
    // }

    // colorStep = ABS_ALT(this->zeldaEffectEnvColor[0] - sZeldaEffectEnvRedTargets[sZeldaEffectColorTargetIndex]) /
    // sZeldaEffectColorTimer; if (this->zeldaEffectEnvColor[0] >=
    // sZeldaEffectEnvRedTargets[sZeldaEffectColorTargetIndex]) {
    //     this->zeldaEffectEnvColor[0] -= colorStep;
    // } else {
    //     this->zeldaEffectEnvColor[0] += colorStep;
    // }

    // // Skips 1, i.e. green.

    // colorStep = ABS_ALT(this->zeldaEffectEnvColor[2] - sZeldaEffectEnvBlueTargets[sZeldaEffectColorTargetIndex]) /
    // sZeldaEffectColorTimer; if (this->zeldaEffectEnvColor[2] >=
    // sZeldaEffectEnvBlueTargets[sZeldaEffectColorTargetIndex]) {
    //     this->zeldaEffectEnvColor[2] -= colorStep;
    // } else {
    //     this->zeldaEffectEnvColor[2] += colorStep;
    // }

    sZeldaEffectColorTimer--;
    if (sZeldaEffectColorTimer == 0) {
        this->zeldaEffectPrimColor[0] = sZeldaEffectPrimRedTargets[sZeldaEffectColorTargetIndex];
        this->zeldaEffectPrimColor[1] = sZeldaEffectPrimGreenTargets[sZeldaEffectColorTargetIndex];
        this->zeldaEffectPrimColor[2] = sZeldaEffectPrimBlueTargets[sZeldaEffectColorTargetIndex];
        this->zeldaEffectEnvColor[0] = sZeldaEffectEnvRedTargets[sZeldaEffectColorTargetIndex];
        // Skips 1, i.e. green.
        this->zeldaEffectEnvColor[2] = sZeldaEffectEnvBlueTargets[sZeldaEffectColorTargetIndex];
        sZeldaEffectColorTimer = 30;
        sZeldaEffectColorTargetIndex ^= 1;
    }
}

void EnMag_Update(Actor* thisx, GlobalContext* globalCtx) {
    static s16 sMajorasMaskEffectPrimGreenTargets[] = { 255, 155 };
    static s16 sMajorasMaskEffectEnvRedTargets[] = { 255, 0 };
    static s16 sMajorasMaskEffectEnvBlueTargets[] = { 0, 155 };
    s16 step;
    s32 pad[2];
    EnMag* this = (EnMag*)thisx;

    if (gSaveContext.fileNum != 0xFEDC) {
        if (this->unk11F04 == 0) {
            if (CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_START) ||
                CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_A) ||
                CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_B)) {

                if (!EnvFlags_Get(globalCtx, 4)) {
                    play_sound(NA_SE_SY_PIECE_OF_HEART);
                    this->unk11F04 = 10;
                    this->unk11F00 = 0;
                    this->unk11F02 = 30;
                    D_8096E910 = 20;
                    gSaveContext.fadeDuration = 1;
                    gSaveContext.unk_3F51 = 255;
                }
            }
        } else {
            switch (this->unk11F04) {
                case 1:
                    step = ABS_ALT(this->majorasMaskEffectPrimColor[1] - sMajorasMaskEffectPrimGreenTargets[0]) / this->unk11F64;
                    if (this->majorasMaskEffectPrimColor[1] >= sMajorasMaskEffectPrimGreenTargets[0]) {
                        this->majorasMaskEffectPrimColor[1] -= step;
                    } else {
                        this->majorasMaskEffectPrimColor[1] += step;
                    }

                    step = ABS_ALT(this->majorasMaskEffectEnvColor[0] - sMajorasMaskEffectEnvRedTargets[0]) / this->unk11F64;
                    if (this->majorasMaskEffectEnvColor[0] >= sMajorasMaskEffectEnvRedTargets[0]) {
                        this->majorasMaskEffectEnvColor[0] -= step;
                    } else {
                        this->majorasMaskEffectEnvColor[0] += step;
                    }

                    step = ABS_ALT(this->majorasMaskEffectEnvColor[2] - sMajorasMaskEffectEnvBlueTargets[0]) / this->unk11F64;
                    if (this->majorasMaskEffectEnvColor[2] >= sMajorasMaskEffectEnvBlueTargets[0]) {
                        this->majorasMaskEffectEnvColor[2] -= step;
                    } else {
                        this->majorasMaskEffectEnvColor[2] += step;
                    }

                    step = ABS_ALT(this->majorasMaskEffectAlpha - 255) / this->unk11F64;
                    this->majorasMaskEffectAlpha += step;

                    step = ABS_ALT(this->majorasMaskEffectPrimLodFrac - 32) / this->unk11F64;
                    this->majorasMaskEffectPrimLodFrac += step;

                    this->unk11F64--;
                    if (this->unk11F64 == 0) {
                        this->majorasMaskEffectPrimColor[1] = sMajorasMaskEffectPrimGreenTargets[0];
                        this->majorasMaskEffectEnvColor[0] = sMajorasMaskEffectEnvRedTargets[0];
                        this->majorasMaskEffectEnvColor[2] = sMajorasMaskEffectEnvBlueTargets[0];
                        this->majorasMaskEffectAlpha = 255;
                        this->unk11F04 = 2;
                        this->unk11F72 = 5;
                    }
                    break;

                case 2:
                    if (this->unk11F72 == 0) {
                        step = ABS_ALT(this->majorasMaskEffectPrimColor[1] - sMajorasMaskEffectPrimGreenTargets[1]) / this->unk11F66;
                        if (this->majorasMaskEffectPrimColor[1] >= sMajorasMaskEffectPrimGreenTargets[1]) {
                            this->majorasMaskEffectPrimColor[1] -= step;
                        } else {
                            this->majorasMaskEffectPrimColor[1] += step;
                        }

                        step = ABS_ALT(this->majorasMaskEffectEnvColor[0] - sMajorasMaskEffectEnvRedTargets[1]) / this->unk11F66;
                        if (this->majorasMaskEffectEnvColor[0] >= sMajorasMaskEffectEnvRedTargets[1]) {
                            this->majorasMaskEffectEnvColor[0] -= step;
                        } else {
                            this->majorasMaskEffectEnvColor[0] += step;
                        }

                        step = ABS_ALT(this->majorasMaskEffectEnvColor[2] - sMajorasMaskEffectEnvBlueTargets[1]) / this->unk11F66;
                        if (this->majorasMaskEffectEnvColor[2] >= sMajorasMaskEffectEnvBlueTargets[1]) {
                            this->majorasMaskEffectEnvColor[2] -= step;
                        } else {
                            this->majorasMaskEffectEnvColor[2] += step;
                        }

                        step = ABS_ALT(this->majorasMaskEffectPrimLodFrac - 128) / this->unk11F66;
                        this->majorasMaskEffectPrimLodFrac += step;

                        step = ABS_ALT(this->majorasMaskAlpha - 255) / this->unk11F66;
                        this->majorasMaskAlpha += step;

                        this->unk11F66--;
                        if (this->unk11F66 == 0) {
                            this->majorasMaskEffectPrimColor[1] = sMajorasMaskEffectPrimGreenTargets[1];
                            this->majorasMaskEffectEnvColor[0] = sMajorasMaskEffectEnvRedTargets[1];
                            this->majorasMaskEffectEnvColor[2] = sMajorasMaskEffectEnvBlueTargets[1];
                            this->majorasMaskEffectPrimLodFrac = 128;
                            this->majorasMaskAlpha = 255;
                            this->unk11F04 = 3;
                            this->unk11F72 = 5;
                        }
                    } else {
                        this->unk11F72--;
                    }
                    break;

                case 3:
                    if (this->unk11F72 == 0) {
                        step = ABS_ALT(this->mainTitleAlpha - 255) / this->unk11F68;
                        this->mainTitleAlpha += step;

                        this->unk11F68--;
                        if (this->unk11F68 == 0) {
                            this->unk11F68 = 1;
                            this->mainTitleAlpha = 255;
                        }

                        step = ABS_ALT(this->majorasMaskEffectAlpha - 60) / this->unk11F6A;
                        this->majorasMaskEffectAlpha -= step;

                        step = ABS_ALT(this->zeldaEffectAlpha - 255) / this->unk11F6A;
                        this->zeldaEffectAlpha += step;

                        step = ABS_ALT(this->zeldaEffectPrimLodFrac - 128) / this->unk11F6A;
                        this->zeldaEffectPrimLodFrac += step;

                        this->unk11F6A--;

                        if (this->unk11F6A == 0) {
                            this->majorasMaskEffectAlpha = 60;
                            this->zeldaEffectAlpha = 255;
                            this->zeldaEffectPrimLodFrac = 128;
                            this->unk11F04 = 5;
                            this->unk11F72 = 20;
                        }
                    } else {
                        this->unk11F72--;
                    }
                    break;

                case 5:
                    func_8096B604(&this->actor);

                    if (this->unk11F72 == 0) {
                        step = ABS_ALT(this->subtitleAlpha - 255) / this->unk11F6C;
                        this->subtitleAlpha += step;

                        this->unk11F6C--;
                        if (this->unk11F6C == 0) {
                            this->zeldaEffectAlpha = 255;
                            this->unk11F04 = 6;
                            this->unk11F72 = 20;
                        }
                    } else {
                        this->unk11F72--;
                    }
                    break;

                case 6:
                    func_8096B604(&this->actor);

                    if (this->unk11F72 == 0) {
                        step = ABS_ALT(this->copyrightAlpha - 255) / this->unk11F6E;
                        this->copyrightAlpha += step;

                        this->unk11F6E--;
                        if (this->unk11F6E == 0) {
                            this->copyrightAlpha = 255;
                            this->unk11F04 = 13;
                        }
                    } else {
                        this->unk11F72--;
                    }
                    break;

                case 10:
                    this->majorasMaskEffectPrimColor[1] = sMajorasMaskEffectPrimGreenTargets[0];
                    this->majorasMaskEffectEnvColor[0] = sMajorasMaskEffectEnvRedTargets[0];
                    this->majorasMaskEffectEnvColor[2] = sMajorasMaskEffectEnvBlueTargets[0];
                    this->majorasMaskEffectAlpha = 60;
                    this->majorasMaskEffectPrimLodFrac = 128;
                    this->majorasMaskAlpha = 255;
                    this->mainTitleAlpha = 255;
                    this->zeldaEffectAlpha = 255;
                    this->zeldaEffectPrimLodFrac = 128;
                    this->subtitleAlpha = 255;
                    this->copyrightAlpha = 255;
                    this->unk11F04 = 13;
                    break;

                case 13:
                    func_8096B604(&this->actor);

                    if (D_8096E910 == 0) {
                        if (CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_START) ||
                            CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_A) ||
                            CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_B)) {
                            if (globalCtx->sceneLoadFlag != 0x14) {
                                func_801A3F54(0);
                                D_801BB12C++;
                                if (D_801BB12C >= 2) {
                                    D_801BB12C = 0;
                                }
                                play_sound(NA_SE_SY_PIECE_OF_HEART);
                                gSaveContext.gameMode = 2; // Go to FileChoose
                                globalCtx->sceneLoadFlag = 0x14;
                                globalCtx->unk_1887F = 2;
                                globalCtx->nextEntranceIndex = 0x1C00;
                                gSaveContext.cutscene = 0;
                                gSaveContext.sceneSetupIndex = 0;
                            }
                            this->unk11F54 = 15;
                            this->unk11F56 = 25;
                            this->unk11F04 = 20;
                        }
                    } else {
                        D_8096E910--;
                    }
                    break;

                case 20:
                    step = ABS_ALT(this->majorasMaskEffectAlpha) / this->unk11F70;
                    this->majorasMaskEffectAlpha -= step;

                    step = ABS_ALT(this->majorasMaskAlpha) / this->unk11F70;
                    this->majorasMaskAlpha -= step;

                    step = ABS_ALT(this->zeldaEffectAlpha) / this->unk11F70;
                    this->zeldaEffectAlpha -= step;

                    step = ABS_ALT(this->mainTitleAlpha) / this->unk11F70;
                    this->mainTitleAlpha -= step;

                    step = ABS_ALT(this->subtitleAlpha) / this->unk11F70;
                    this->subtitleAlpha -= step;

                    step = ABS_ALT(this->copyrightAlpha) / this->unk11F70;
                    this->copyrightAlpha -= step;

                    this->unk11F70--;
                    if (this->unk11F70 == 0) {
                        this->majorasMaskEffectAlpha = 0;
                        this->majorasMaskAlpha = 0;
                        this->mainTitleAlpha = 0;
                        this->subtitleAlpha = 0;
                        this->zeldaEffectAlpha = 0;
                        this->copyrightAlpha = 0;
                        this->unk11F04 = 21;
                    }
                    break;
            }

            if ((this->unk11F04 > 0) && (this->unk11F04 < 10)) {
                if (CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_START) ||
                    CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_A) ||
                    CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_B)) {
                    play_sound(NA_SE_SY_PIECE_OF_HEART);
                    this->unk11F04 = 10;
                }
            }
        }
    }

    if (this->unk11F04 == 0) {
        if (EnvFlags_Get(globalCtx, 3)) {
            this->unk11F02 = 40;
            this->unk11F04 = 1;
        }
    } else if (this->unk11F04 < 20) {
        if (EnvFlags_Get(globalCtx, 4)) {
            this->unk11F04 = 20;
        }
    }
}

#define EnMag_DrawTextureI8 func_8096C998
/**
 * Draws an i8 texture.
 *
 * @param gfxp Pointer to current displaylist.
 * @param texture Texture to draw.
 * @param texWidth Width of the texture.
 * @param texHeight Height of the texture.
 * @param rectLeft X coordinate of the top-left of the draw position.
 * @param rectTop Y coordinate of the top-left of the draw position.
 */
void EnMag_DrawTextureI8(Gfx** gfxp, void* texture, s16 texWidth, s16 texHeight, s16 rectLeft, s16 rectTop) {
    Gfx* gfx = *gfxp;

    gDPLoadTextureBlock(gfx++, texture, G_IM_FMT_I, G_IM_SIZ_8b, texWidth, texHeight, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(gfx++, rectLeft << 2, rectTop << 2, (rectLeft + texWidth) << 2, (rectTop + texHeight) << 2,
                        G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

    *gfxp = gfx;
}

#define EnMag_DrawTextureIA8 func_8096CBB0
/**
 * Draws an ia8 texture.
 *
 * @param gfxp Pointer to current displaylist.
 * @param texture Texture to draw.
 * @param texWidth Width of the texture.
 * @param texHeight Height of the texture.
 * @param rectLeft X coordinate of the top-left of the draw position.
 * @param rectTop Y coordinate of the top-left of the draw position.
 */
void EnMag_DrawTextureIA8(Gfx** gfxp, void* texture, s16 texWidth, s16 texHeight, s16 rectLeft, s16 rectTop) {
    Gfx* gfx = *gfxp;

    gDPLoadTextureBlock(gfx++, texture, G_IM_FMT_IA, G_IM_SIZ_8b, texWidth, texHeight, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(gfx++, rectLeft << 2, rectTop << 2, (rectLeft + texWidth) << 2, (rectTop + texHeight) << 2,
                        G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

    *gfxp = gfx;
}

// index is an index into the scrolling arrays
#define EnMag_DrawEffectTextures func_8096CDC8

/**
 * Draws an i8 effect texture, masking it with an i4 mask, with shifting
 *
 * @param gfxp Pointer to current displaylist.
 * @param maskTex Texture with which to mask.
 * @param effectTex Effect texture to draw.
 * @param maskWidth Width of masking texture.
 * @param maskHeight Height of masking texture.
 * @param effectWidth Width of effect texture.
 * @param effectHeight Height of effect texture.
 * @param rectLeft X coordinate of the top-left of the draw position.
 * @param rectTop Y coordinate of the top-left of the draw position.
 * @param shifts
 * @param shiftt
 * @param index Index into the ??? arrays to use for tile size.
 * @param this Pointer to EnMag instance.
 */
void EnMag_DrawEffectTextures(Gfx** gfxp, void* maskTex, void* effectTex, s16 maskWidth, s16 maskHeight,
                              s16 effectWidth, s16 effectHeight, s16 rectLeft, s16 rectTop, u16 shifts, u16 shiftt,
                              u16 index, EnMag* this) {
    Gfx* gfx = *gfxp;

    gDPLoadMultiBlock_4b(gfx++, maskTex, 0x0000, G_TX_RENDERTILE, G_IM_FMT_I, maskWidth, maskHeight, 0,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                         G_TX_NOLOD);

    gDPLoadMultiBlock(gfx++, effectTex, 0x0100, 1, G_IM_FMT_I, G_IM_SIZ_8b, effectWidth, effectHeight, 0,
                      G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, shifts, shiftt);

    gDPSetTileSize(gfx++, 1, this->unk11F36[index] & 0x7F, this->unk11F44[index] & 0x7F,
                   (this->unk11F36[index] & 0x7F) + 0xF, (this->unk11F44[index] & 0x7F) + 0xF);

    gSPTextureRectangle(gfx++, rectLeft << 2, rectTop << 2, (rectLeft + maskWidth) << 2, (rectTop + maskHeight) << 2,
                        G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

    *gfxp = gfx;
}

#define gDPSetTileCustom(pkt, fmt, siz, width, height, pal, cms, cmt, masks, maskt, shifts, shiftt)                    \
    {                                                                                                                  \
        gDPPipeSync(pkt);                                                                                              \
        gDPTileSync(pkt);                                                                                              \
        gDPSetTile(pkt, fmt, siz, (((width)*siz##_TILE_BYTES) + 7) >> 3, 0, G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, \
                   masks, shifts);                                                                                     \
        gDPTileSync(pkt);                                                                                              \
        gDPSetTile(pkt, fmt, siz, (((width)*siz##_TILE_BYTES) + 7) >> 3, 0, G_TX_RENDERTILE, pal, cmt, maskt, shiftt,  \
                   cms, masks, shifts);                                                                                \
        gDPSetTileSize(pkt, G_TX_RENDERTILE, 0, 0, ((width)-1) << G_TEXTURE_IMAGE_FRAC,                                \
                       ((height)-1) << G_TEXTURE_IMAGE_FRAC);                                                          \
    }

#define TMEM_SIZE (1 << 12)

// EnMag_DrawImageRGBA32
#define EnMag_DrawImageRGBA32 func_8096D230
/**
 * Draws an rgba32 texture. Because these are so large, this will draw the texture in horizontal stripes, each narrow
 * enough that that part of the texture will fit into TMEM's 4kB.
 *
 * @param gfxp Pointer to current displaylist.
 * @param centerX X coordinate of the center of the draw position.
 * @param centerY Y coordinate of the center of the draw position.
 * @param source Texture to draw.
 * @param width Width of the texture.
 * @param height Height of the texture.
 */
void EnMag_DrawImageRGBA32(Gfx** gfxp, s16 centerX, s16 centerY, void* source, u32 width, u32 height) {
    Gfx* gfx = *gfxp;
    uintptr_t curTexture;
    s32 textureCount;
    u32 rectLeft;
    u32 rectTop;
    u32 textureHeight;
    s32 remainingSize;
    s32 textureSize;
    s32 pad;
    s32 i;

    func_8012CA0C(&gfx);

    curTexture = source;
    rectLeft = centerX - (width / 2);
    rectTop = centerY - (height / 2);
    textureHeight = TMEM_SIZE / (width << 2);
    remainingSize = (width * height) << 2;
    textureSize = (width * textureHeight) << 2;
    textureCount = remainingSize / textureSize;
    if ((remainingSize % textureSize) != 0) {
        textureCount++;
    }

    gDPSetTileCustom(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, width, textureHeight, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                     G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    remainingSize -= textureSize;

    for (i = 0; i < textureCount; i++) {
        gDPSetTextureImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, width, curTexture);

        gDPLoadSync(gfx++);
        gDPLoadTile(gfx++, G_TX_LOADTILE, 0, 0, (width - 1) << 2, (textureHeight - 1) << 2);

        gSPTextureRectangle(gfx++, rectLeft << 2, rectTop << 2, (rectLeft + (s32)width) << 2,
                            (rectTop + textureHeight) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

        curTexture += textureSize;
        rectTop += textureHeight;

        if ((remainingSize - textureSize) < 0) {
            if (remainingSize > 0) {
                textureHeight = remainingSize / (s32)(width << 2);
                remainingSize -= textureSize;

                gDPSetTileCustom(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, width, textureHeight, 0,
                                 G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                 G_TX_NOLOD, G_TX_NOLOD);
            }
        } else {
            remainingSize -= textureSize;
        }
    }

    *gfxp = gfx;
}

#define EnMag_DrawCharTexture func_8096D60C
/**
 * Draws one character, expected to be a 16 by 16 i4 texture.
 *
 * @param gfxp Pointer to current displaylist.
 * @param texture Texture to draw.
 * @param rectLeft X coordinate of the top-left of the draw position.
 * @param rectTop Y coordinate of the top-left of the draw position.
 */
// Should this actually use FONT_CHAR_TEX_WIDTH/FONT_CHAR_TEX_HEIGHT?
void EnMag_DrawCharTexture(Gfx** gfxp, void* texture, s32 rectLeft, s32 rectTop) {
    Gfx* gfx = *gfxp;

    gDPLoadTextureBlock_4b(gfx++, texture, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(gfx++, rectLeft << 2, rectTop << 2, (rectLeft + 10) << 2, (rectTop + 10) << 2, G_TX_RENDERTILE,
                        0, 0, 1625, 1625);

    *gfxp = gfx;
}

#define MAJORAS_MASK_TEX_WIDTH 128
#define MAJORAS_MASK_TEX_HEIGHT 112
#define MAJORAS_MASK_TEX_CENTER_X 124
#define MAJORAS_MASK_TEX_CENTER_Y 103

#define ZELDA_TEX_WIDTH 144
#define ZELDA_TEX_HEIGHT 64
#define ZELDA_TEX_CENTER_X 177
#define ZELDA_TEX_CENTER_Y 105

#define SUBTITLE_TEX_WIDTH 104
#define SUBTITLE_TEX_HEIGHT 16
#define SUBTITLE_TEX_LEFT 151
#define SUBTITLE_TEX_TOP 124

#define THE_LEGEND_OF_TEX_WIDTH 72
#define THE_LEGEND_OF_TEX_HEIGHT 8
#define THE_LEGEND_OF_TEX_LEFT 158
#define THE_LEGEND_OF_TEX_TOP 71

#define COPYRIGHT_TEX_WIDTH 128
#define COPYRIGHT_TEX_HEIGHT 16
#define COPYRIGHT_TEX_LEFT 94
#define COPYRIGHT_TEX_TOP 198

#define NO_CONTROLLER_FIRST_TEX_WIDTH 256
#define NO_CONTROLLER_FIRST_TEX_HEIGHT 9
#define NO_CONTROLLER_FIRST_TEX_LEFT 35
#define NO_CONTROLLER_FIRST_TEX_TOP 175

#define NO_CONTROLLER_SECOND_TEX_WIDTH 144
#define NO_CONTROLLER_SECOND_TEX_HEIGHT 9
#define NO_CONTROLLER_SECOND_TEX_LEFT 91
#define NO_CONTROLLER_SECOND_TEX_TOP 188

// Top-left of the text itself, not the shadow
#define PRESS_START_LEFT 119
#define PRESS_START_TOP 174
#define PRESS_START_CHAR_SPACING 7 // Amount of rightward shift before printing next char
#define PRESS_START_SPACE 5        // Extra space between the words

// EnMag_DrawInner
/**
 * Loads title, PRESS START text, etc. graphics into the displaylist array specified by gfxp, which lives on
 * POLY_OPA_DISP, but is used by OVERLAY_DISP.
 */
void func_8096D74C(Actor* thisx, GlobalContext* globalCtx, Gfx** gfxp) {
    static u8 pressStartFontIndices[] = {
        0x19, 0x1B, 0x0E, 0x1C, 0x1C, 0x1C, 0x1D, 0x0A, 0x1B, 0x1D,
    }; // TODO: understand what's going on here
    static TexturePtr D_8096E970[] = { 0x600CF40, 0x600D740, 0x600EF40, 0x600DF40, 0x600E740, 0x600F740 };
    static TexturePtr D_8096E988[] = { 0x6009F40, 0x600A740, 0x600BF40, 0x600AF40, 0x600B740, 0x600C740 };
    static TexturePtr D_8096E9A0[] = {
        gTitleScreenFlame0Tex, gTitleScreenFlame1Tex, gTitleScreenFlame1Tex,
        gTitleScreenFlame2Tex, gTitleScreenFlame3Tex, gTitleScreenFlame3Tex,
    };
    static s16 D_8096E9B8[] = { -1, 1, 1, -1, 1, 1 };
    static s16 D_8096E9C4[] = { -2, -2, -2, 2, 2, 2 };
    static s16 sTextAlpha = 0; // For drawing both the No Controller message and "PRESS START"
    static s16 sTextAlphaTargets[] = { 255, 0 };
    s32 pad;
    EnMag* this = THIS;
    Font* font = &this->font;
    Gfx* gfx = *gfxp;
    u16 i;
    u16 j;
    u16 k;
    s32 rectLeft;
    s32 rectTop;
    s16 step;

    // Set segment 6 to the object, since this will be read by OVERLAY_DISP where it is not set by default.
    gSPSegment(gfx++, 0x06, globalCtx->objectCtx.status[this->actor.objBankIndex].segment);

    func_8012C680(&gfx);

    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_2CYCLE);
    gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
    gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_CLD_SURF2);
    gDPSetCombineLERP(gfx++, TEXEL1, PRIMITIVE, PRIM_LOD_FRAC, TEXEL0, TEXEL1, 1, PRIM_LOD_FRAC, TEXEL0, PRIMITIVE,
                      ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0);

    gDPSetPrimColor(gfx++, 0, this->majorasMaskEffectPrimLodFrac, this->majorasMaskEffectPrimColor[0],
                    this->majorasMaskEffectPrimColor[1], this->majorasMaskEffectPrimColor[2],
                    this->majorasMaskEffectAlpha);
    gDPSetEnvColor(gfx++, this->majorasMaskEffectEnvColor[0], this->majorasMaskEffectEnvColor[1],
                   this->majorasMaskEffectEnvColor[2], 255);

    // Glowy effects behind Mask
    if (this->majorasMaskEffectPrimLodFrac != 0) {
        for (k = 0, i = 0, rectTop = 38; i < 2; i++, rectTop += 64) {
            for (j = 0, rectLeft = 57; j < 3; j++, k++, rectLeft += 64) {
                this->unk11F36[k] += D_8096E9B8[k];
                this->unk11F44[k] += D_8096E9C4[k];
                EnMag_DrawEffectTextures(&gfx, D_8096E970[k], D_8096E9A0[k], 64, 64, 32, 32, rectLeft, rectTop, 1, 1, k,
                                         this);
            }
        }
    }

    func_8012C680(&gfx);

    if (this->majorasMaskAlpha != 0) {
        gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                          ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);

        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, this->majorasMaskAlpha);
        gDPSetEnvColor(gfx++, this->majorasMaskEnvColor[0], this->majorasMaskEnvColor[1], this->majorasMaskEnvColor[2],
                       255);

        EnMag_DrawImageRGBA32(&gfx, MAJORAS_MASK_TEX_CENTER_X, MAJORAS_MASK_TEX_CENTER_Y, gTitleScreenMajorasMaskTex,
                              MAJORAS_MASK_TEX_WIDTH, MAJORAS_MASK_TEX_HEIGHT);
    }

    gDPPipeSync(gfx++);

    gDPSetCycleType(gfx++, G_CYC_2CYCLE);
    gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
    gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_CLD_SURF2);
    gDPSetCombineLERP(gfx++, TEXEL1, PRIMITIVE, PRIM_LOD_FRAC, TEXEL0, TEXEL1, 1, PRIM_LOD_FRAC, TEXEL0, PRIMITIVE,
                      ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0);

    gDPSetPrimColor(gfx++, 0, this->zeldaEffectPrimLodFrac, this->zeldaEffectPrimColor[0],
                    this->zeldaEffectPrimColor[1], this->zeldaEffectPrimColor[2], this->zeldaEffectAlpha);
    gDPSetEnvColor(gfx++, this->zeldaEffectEnvColor[0], this->zeldaEffectEnvColor[1], this->zeldaEffectEnvColor[2],
                   255);

    // Glowy effects behind "ZELDA"
    if (this->zeldaEffectPrimLodFrac != 0) {
        for (k = 0, i = 0, rectTop = 38; i < 2; i++, rectTop += 64) {
            for (j = 0, rectLeft = 57; j < 3; j++, k++, rectLeft += 64) {
                EnMag_DrawEffectTextures(&gfx, D_8096E988[k], D_8096E9A0[k], 64, 64, 32, 32, rectLeft, rectTop, 1, 1, k,
                                         this);
            }
        }
    }

    if (this->subtitleAlpha != 0) {
        func_8012C680(&gfx);

        gDPSetAlphaCompare(gfx++, G_AC_NONE);
        gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

        if (this->mainTitleAlpha < 100) {
            gDPSetRenderMode(gfx++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
        } else {
            gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        }

        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, this->subtitleAlpha);
        gDPSetEnvColor(gfx++, 100, 0, 100, 255);

        EnMag_DrawTextureI8(&gfx, gTitleScreenMajorasMaskSubtitleMaskTex, SUBTITLE_TEX_WIDTH, SUBTITLE_TEX_HEIGHT,
                            SUBTITLE_TEX_LEFT, SUBTITLE_TEX_TOP);
    }

    func_8012C680(&gfx);

    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    if (this->mainTitleAlpha < 100) {
        gDPSetRenderMode(gfx++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
    } else {
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }

    gDPSetPrimColor(gfx++, 0, 120, 208, 102, 222, this->subtitleAlpha);

    EnMag_DrawTextureI8(&gfx, gTitleScreenMajorasMaskSubtitleTex, SUBTITLE_TEX_WIDTH, SUBTITLE_TEX_HEIGHT,
                        SUBTITLE_TEX_LEFT, SUBTITLE_TEX_TOP);

    func_8012C680(&gfx);

    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    if (this->mainTitleAlpha != 0) {
        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, this->mainTitleAlpha);

        EnMag_DrawImageRGBA32(&gfx, ZELDA_TEX_CENTER_X, ZELDA_TEX_CENTER_Y, gTitleScreenZeldaLogoTex, ZELDA_TEX_WIDTH,
                              ZELDA_TEX_HEIGHT);

        gDPPipeSync(gfx++);

        if (this->mainTitleAlpha < 100) {
            gDPSetRenderMode(gfx++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
        } else {
            gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        }

        gDPSetPrimColor(gfx++, 0, 0, 208, 102, 222, this->mainTitleAlpha);

        EnMag_DrawTextureI8(&gfx, gTitleScreenTheLegendOfTextTex, THE_LEGEND_OF_TEX_WIDTH, THE_LEGEND_OF_TEX_HEIGHT,
                            THE_LEGEND_OF_TEX_LEFT, THE_LEGEND_OF_TEX_TOP);
    }

    func_8012C680(&gfx);

    if (this->copyrightAlpha != 0) {
        gDPSetAlphaCompare(gfx++, G_AC_NONE);
        gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(gfx++, 0, 0, this->copyrightAlpha, this->copyrightAlpha, this->copyrightAlpha,
                        this->copyrightAlpha);

        EnMag_DrawTextureIA8(&gfx, gTitleScreenCopyright2000NintendoTex, COPYRIGHT_TEX_WIDTH, COPYRIGHT_TEX_HEIGHT,
                             COPYRIGHT_TEX_LEFT, COPYRIGHT_TEX_TOP);
    }

    if (gSaveContext.fileNum == 0xFEDC) {
        // Draw No controller message
        step = ABS_ALT(sTextAlpha - sTextAlphaTargets[sTextAlphaTargetIndex]) / sTextAlphaTimer;
        if (sTextAlpha >= sTextAlphaTargets[sTextAlphaTargetIndex]) {
            sTextAlpha -= step;
        } else {
            sTextAlpha += step;
        }

        gDPPipeSync(gfx++);
        gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);

        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE,
                          0);
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, sTextAlpha);
        gDPLoadTextureBlock_4b(gfx++, gTitleScreenControllerNotConnectedTextTex, G_IM_FMT_I,
                               NO_CONTROLLER_FIRST_TEX_WIDTH, NO_CONTROLLER_FIRST_TEX_HEIGHT, 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);
        // Texture shadow
        gSPTextureRectangle(gfx++, (NO_CONTROLLER_FIRST_TEX_LEFT + 1) << 2, (NO_CONTROLLER_FIRST_TEX_TOP + 1) << 2,
                            (NO_CONTROLLER_FIRST_TEX_LEFT + 1 + NO_CONTROLLER_FIRST_TEX_WIDTH) << 2,
                            (NO_CONTROLLER_FIRST_TEX_TOP + 1 + NO_CONTROLLER_FIRST_TEX_HEIGHT) << 2, G_TX_RENDERTILE, 0,
                            0, 1 << 10, 1 << 10);
        // Actual texture
        gDPSetPrimColor(gfx++, 0, 0, 205, 255, 255, sTextAlpha);
        gSPTextureRectangle(gfx++, NO_CONTROLLER_FIRST_TEX_LEFT << 2, NO_CONTROLLER_FIRST_TEX_TOP << 2,
                            (NO_CONTROLLER_FIRST_TEX_LEFT + NO_CONTROLLER_FIRST_TEX_WIDTH) << 2,
                            (NO_CONTROLLER_FIRST_TEX_TOP + NO_CONTROLLER_FIRST_TEX_HEIGHT) << 2, G_TX_RENDERTILE, 0, 0,
                            1 << 10, 1 << 10);

        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, sTextAlpha);
        gDPLoadTextureBlock_4b(gfx++, gTitleScreenInsertControllerTextTex, G_IM_FMT_I, NO_CONTROLLER_SECOND_TEX_WIDTH,
                               NO_CONTROLLER_SECOND_TEX_HEIGHT, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        // Texture shadow
        gSPTextureRectangle(gfx++, (NO_CONTROLLER_SECOND_TEX_LEFT + 1) << 2, (NO_CONTROLLER_SECOND_TEX_TOP + 1) << 2,
                            (NO_CONTROLLER_SECOND_TEX_LEFT + 1 + NO_CONTROLLER_SECOND_TEX_WIDTH) << 2,
                            (NO_CONTROLLER_SECOND_TEX_TOP + 1 + NO_CONTROLLER_SECOND_TEX_HEIGHT) << 2, G_TX_RENDERTILE,
                            0, 0, 1 << 10, 1 << 10);
        // Actual texture
        gDPSetPrimColor(gfx++, 0, 0, 205, 255, 255, sTextAlpha);
        gSPTextureRectangle(gfx++, NO_CONTROLLER_SECOND_TEX_LEFT << 2, NO_CONTROLLER_SECOND_TEX_TOP << 2,
                            (NO_CONTROLLER_SECOND_TEX_LEFT + NO_CONTROLLER_SECOND_TEX_WIDTH) << 2,
                            (NO_CONTROLLER_SECOND_TEX_TOP + NO_CONTROLLER_SECOND_TEX_HEIGHT) << 2, G_TX_RENDERTILE, 0,
                            0, 1 << 10, 1 << 10);

        sTextAlphaTimer--;
        if (sTextAlphaTimer == 0) {
            sTextAlpha = sTextAlphaTargets[sTextAlphaTargetIndex];
            if (gSaveContext.fileNum == 0xFEDC) {
                sTextAlphaTimer = 40;
            } else {
                sTextAlphaTimer = 20;
            }
            sTextAlphaTargetIndex ^= 1;
        }
    } else if (this->copyrightAlpha != 0) {
        // Draw "PRESS START" characters

        step = ABS_ALT(sTextAlpha - sTextAlphaTargets[sTextAlphaTargetIndex]) / sTextAlphaTimer;
        if (sTextAlpha >= sTextAlphaTargets[sTextAlphaTargetIndex]) {
            sTextAlpha -= step;
        } else {
            sTextAlpha += step;
        }

        // Text shadow
        gDPPipeSync(gfx++);
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE,
                          0);
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, sTextAlpha);

        rectLeft = PRESS_START_LEFT + 1;
        for (i = 0; i < ARRAY_COUNT(pressStartFontIndices); i++) {
            EnMag_DrawCharTexture(&gfx, font->fontBuf + pressStartFontIndices[i] * FONT_CHAR_TEX_SIZE, rectLeft,
                                  PRESS_START_TOP + 1);

            rectLeft += PRESS_START_CHAR_SPACING;
            if (i == 4) {
                rectLeft += PRESS_START_SPACE;
            }
        }

        // Actual text
        gDPPipeSync(gfx++);
        gDPSetPrimColor(gfx++, 0, 0, 255, 30, 30, sTextAlpha);

        rectLeft = PRESS_START_LEFT;
        for (i = 0; i < ARRAY_COUNT(pressStartFontIndices); i++) {
            EnMag_DrawCharTexture(&gfx, font->fontBuf + pressStartFontIndices[i] * FONT_CHAR_TEX_SIZE, rectLeft,
                                  PRESS_START_TOP);
            rectLeft += PRESS_START_CHAR_SPACING;
            if (i == 4) {
                rectLeft += PRESS_START_SPACE;
            }
        }

        sTextAlphaTimer--;
        if (sTextAlphaTimer == 0) {
            sTextAlpha = sTextAlphaTargets[sTextAlphaTargetIndex];
            if (gSaveContext.fileNum == 0xFEDC) {
                sTextAlphaTimer = 40;
            } else {
                sTextAlphaTimer = 20;
            }
            sTextAlphaTargetIndex ^= 1;
        }
    }
    *gfxp = gfx;
}

void EnMag_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    Gfx* gfx;
    Gfx* gfxRef;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gfxRef = POLY_OPA_DISP;
    gfx = Graph_GfxPlusOne(gfxRef);
    gSPDisplayList(OVERLAY_DISP++, gfx);

    func_8096D74C(thisx, globalCtx, &gfx);

    gSPEndDisplayList(gfx++);
    Graph_BranchDlist(gfxRef, gfx);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
