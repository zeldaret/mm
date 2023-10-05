#include "prevent_bss_reordering.h"
#include "z64.h"
#include "regs.h"
#include "functions.h"
#include "z64vismono.h"

// Variables are put before most headers as a hacky way to bypass bss reordering
s16 sTransitionFillTimer;
Input D_801F6C18;
TransitionTile sTransitionTile;
s32 gTransitionTileState;
VisMono sPlayVisMono;
Color_RGBA8_u32 gVisMonoColor;
Struct_80140E80 D_801F6D38;
Struct_80140E80* D_801F6D4C;
BombersNotebook sBombersNotebook;
u8 sBombersNotebookOpen;
u8 sMotionBlurStatus;

#include "variables.h"
#include "macros.h"
#include "buffers.h"
#include "idle.h"
#include "sys_cfb.h"
#include "z64bombers_notebook.h"
#include "z64debug_display.h"
#include "z64quake.h"
#include "z64rumble.h"
#include "z64shrink_window.h"
#include "z64view.h"

#include "overlays/gamestates/ovl_daytelop/z_daytelop.h"
#include "overlays/gamestates/ovl_opening/z_opening.h"
#include "overlays/gamestates/ovl_file_choose/z_file_select.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"
#include "debug.h"

s32 gDbgCamEnabled = false;
u8 D_801D0D54 = false;

typedef enum {
    /* 0 */ MOTION_BLUR_OFF,
    /* 1 */ MOTION_BLUR_SETUP,
    /* 2 */ MOTION_BLUR_PROCESS
} MotionBlurStatus;

void Play_DrawMotionBlur(PlayState* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;
    s32 alpha;
    Gfx* gfx;
    Gfx* gfxHead;

    if (R_MOTION_BLUR_PRIORITY_ENABLED) {
        alpha = R_MOTION_BLUR_PRIORITY_ALPHA;

        if (sMotionBlurStatus == MOTION_BLUR_OFF) {
            sMotionBlurStatus = MOTION_BLUR_SETUP;
        }
    } else if (R_MOTION_BLUR_ENABLED) {
        alpha = R_MOTION_BLUR_ALPHA;

        if (sMotionBlurStatus == MOTION_BLUR_OFF) {
            sMotionBlurStatus = MOTION_BLUR_SETUP;
        }
    } else {
        alpha = 0;
        sMotionBlurStatus = MOTION_BLUR_OFF;
    }

    if (sMotionBlurStatus != MOTION_BLUR_OFF) {
        OPEN_DISPS(gfxCtx);

        gfxHead = POLY_OPA_DISP;
        gfx = Graph_GfxPlusOne(gfxHead);

        gSPDisplayList(OVERLAY_DISP++, gfx);

        this->pauseBgPreRender.fbuf = gfxCtx->curFrameBuffer;
        this->pauseBgPreRender.fbufSave = this->unk_18E64;

        if (sMotionBlurStatus == MOTION_BLUR_PROCESS) {
            func_80170AE0(&this->pauseBgPreRender, &gfx, alpha);
        } else {
            sMotionBlurStatus = MOTION_BLUR_PROCESS;
        }

        PreRender_SaveFramebuffer(&this->pauseBgPreRender, &gfx);

        gSPEndDisplayList(gfx++);

        Graph_BranchDlist(gfxHead, gfx);

        POLY_OPA_DISP = gfx;

        CLOSE_DISPS(gfxCtx);
    }
}

void Play_InitMotionBlur(void) {
    R_MOTION_BLUR_ENABLED = false;
    R_MOTION_BLUR_PRIORITY_ENABLED = false;
    sMotionBlurStatus = MOTION_BLUR_OFF;
}

void Play_DestroyMotionBlur(void) {
    R_MOTION_BLUR_ENABLED = false;
    R_MOTION_BLUR_PRIORITY_ENABLED = false;
    sMotionBlurStatus = MOTION_BLUR_OFF;
}

void Play_SetMotionBlurAlpha(u32 alpha) {
    R_MOTION_BLUR_ALPHA = alpha;
}

void Play_EnableMotionBlur(u32 alpha) {
    R_MOTION_BLUR_ALPHA = alpha;
    R_MOTION_BLUR_ENABLED = true;
}

void Play_DisableMotionBlur(void) {
    R_MOTION_BLUR_ENABLED = false;
}

// How much each color component contributes to the intensity image.
// These coefficients are close to what the YUV color space defines Y (luminance) as:
// https://en.wikipedia.org/wiki/YUV#Conversion_to/from_RGB
#define PLAY_INTENSITY_RED 2
#define PLAY_INTENSITY_GREEN 4
#define PLAY_INTENSITY_BLUE 1
#define PLAY_INTENSITY_NORM (0x1F * PLAY_INTENSITY_RED + 0x1F * PLAY_INTENSITY_GREEN + 0x1F * PLAY_INTENSITY_BLUE)
#define PLAY_INTENSITY_MIX(r, g, b, m) \
    ((((r)*PLAY_INTENSITY_RED + (g)*PLAY_INTENSITY_GREEN + (b)*PLAY_INTENSITY_BLUE) * (m)) / PLAY_INTENSITY_NORM)

/**
 * Converts an RGBA16 buffer to an Intensity Image
 *
 * @param[out] destI destination buffer
 * @param[in] srcRgba16 source buffer
 * @param[in] rgba16Width width of a full row for the RGBA16
 * @param[in] pixelLeft X coordinate of the top-left RGBA16 pixel to start with
 * @param[in] pixelTop Y coordinate of the top-left RGBA16 pixel to start with
 * @param[in] pixelRight X coordinate of the bottom-right RGBA16 pixel to end with
 * @param[in] pixelBottom Y coordinate of the bottom-right RGBA16 pixel to end with
 * @param[in] bitDepth bit depth for the intensity image
 */
void Play_ConvertRgba16ToIntensityImage(void* destI, u16* srcRgba16, s32 rgba16Width, s32 pixelLeft, s32 pixelTop,
                                        s32 pixelRight, s32 pixelBottom, s32 bitDepth) {
    s32 i;
    s32 j;
    u32 pixel;
    u32 r;
    u32 g;
    u32 b;

    switch (bitDepth) {
        case 4: {
            u8* destI4 = destI;
            u32 upper;
            u32 lower;

            for (i = pixelTop; i <= pixelBottom; i++) {
                for (j = pixelLeft; j <= pixelRight; j += 2) {
                    pixel = srcRgba16[i * rgba16Width + j];
                    r = RGBA16_GET_R(pixel);
                    g = RGBA16_GET_G(pixel);
                    b = RGBA16_GET_B(pixel);
                    upper = PLAY_INTENSITY_MIX(r, g, b, 15);

                    pixel = srcRgba16[i * rgba16Width + j + 1];
                    r = RGBA16_GET_R(pixel);
                    g = RGBA16_GET_G(pixel);
                    b = RGBA16_GET_B(pixel);
                    lower = PLAY_INTENSITY_MIX(r, g, b, 15);

                    *(destI4++) = (upper << 4) | lower;
                }
            }
            break;
        }

        case 5: {
            u8* destI5 = destI;

            for (i = pixelTop; i <= pixelBottom; i++) {
                for (j = pixelLeft; j <= pixelRight; j++) {
                    pixel = srcRgba16[i * rgba16Width + j];
                    r = RGBA16_GET_R(pixel);
                    g = RGBA16_GET_G(pixel);
                    b = RGBA16_GET_B(pixel);

                    pixel = 0;

                    *(destI5++) = PLAY_INTENSITY_MIX(r, g, b, 255) & 0xF8;
                }
            }
            break;
        }

        case 8: {
            u8* destI8 = destI;

            for (i = pixelTop; i <= pixelBottom; i++) {
                for (j = pixelLeft; j <= pixelRight; j++) {
                    pixel = srcRgba16[i * rgba16Width + j];

                    r = RGBA16_GET_R(pixel);
                    g = RGBA16_GET_G(pixel);
                    b = RGBA16_GET_B(pixel);

                    *(destI8++) = PLAY_INTENSITY_MIX(r, g, b, 255);
                }
            }
            break;
        }

        case 16: {
            u16* destI16 = destI;

            for (i = pixelTop; i <= pixelBottom; i++) {
                for (j = pixelLeft; j <= pixelRight; j++) {
                    *(destI16++) = srcRgba16[i * rgba16Width + j];
                }
            }
            break;
        }
    }
}

void Play_SetMotionBlurPriorityAlpha(u32 alpha) {
    R_MOTION_BLUR_PRIORITY_ALPHA = alpha;
}

void Play_EnableMotionBlurPriority(u32 alpha) {
    R_MOTION_BLUR_PRIORITY_ALPHA = alpha;
    R_MOTION_BLUR_PRIORITY_ENABLED = true;
}

void Play_DisableMotionBlurPriority(void) {
    R_MOTION_BLUR_PRIORITY_ENABLED = false;
}

// Will take the photograph, but doesn't compress and save it
void Play_TriggerPictoPhoto(void) {
    R_PICTO_PHOTO_STATE = PICTO_PHOTO_STATE_SETUP;
}

void Play_TakePictoPhoto(PreRender* prerender) {
    PreRender_ApplyFilters(prerender);
    Play_ConvertRgba16ToIntensityImage(gPictoPhotoI8, prerender->fbufSave, SCREEN_WIDTH, PICTO_PHOTO_TOPLEFT_X,
                                       PICTO_PHOTO_TOPLEFT_Y, (PICTO_PHOTO_TOPLEFT_X + PICTO_PHOTO_WIDTH) - 1,
                                       (PICTO_PHOTO_TOPLEFT_Y + PICTO_PHOTO_HEIGHT) - 1, 8);
}

s32 Play_ChooseDynamicTransition(PlayState* this, s32 transitionType) {
    s32 nextTransitionType = transitionType;

    if (transitionType == TRANS_TYPE_FADE_DYNAMIC) {
        if (!gSaveContext.save.isNight) {
            nextTransitionType = TRANS_TYPE_FADE_WHITE;
        } else {
            nextTransitionType = TRANS_TYPE_FADE_BLACK;
        }
    }
    if (nextTransitionType != transitionType) {
        this->transitionType = nextTransitionType;
    }
    return nextTransitionType;
}

void Play_SetupTransition(PlayState* this, s32 transitionType) {
    TransitionContext* transitionCtx = &this->transitionCtx;
    s32 fbdemoType;

    bzero(transitionCtx, sizeof(TransitionContext));

    fbdemoType = -1;
    if (transitionType & TRANS_TYPE_WIPE3) {
        fbdemoType = FBDEMO_WIPE3;
    } else if ((transitionType & 0x78) == TRANS_TYPE_WIPE4) { // Checks not only type, but also a max value of 39
        fbdemoType = FBDEMO_WIPE4;
    } else if (!(transitionType & (TRANS_TYPE_WIPE3 | TRANS_TYPE_WIPE4))) {
        switch (transitionType) {
            case TRANS_TYPE_TRIFORCE:
                fbdemoType = FBDEMO_TRIFORCE;
                break;

            case TRANS_TYPE_WIPE:
            case TRANS_TYPE_WIPE_FAST:
                fbdemoType = FBDEMO_WIPE1;
                break;

            case TRANS_TYPE_FADE_BLACK:
            case TRANS_TYPE_FADE_WHITE:
            case TRANS_TYPE_FADE_BLACK_FAST:
            case TRANS_TYPE_FADE_WHITE_FAST:
            case TRANS_TYPE_FADE_BLACK_SLOW:
            case TRANS_TYPE_FADE_WHITE_SLOW:
            case TRANS_TYPE_FADE_WHITE_CS_DELAYED:
            case TRANS_TYPE_FADE_WHITE_INSTANT:
            case TRANS_TYPE_FADE_GREEN:
            case TRANS_TYPE_FADE_BLUE:
                fbdemoType = FBDEMO_FADE;
                break;

            case TRANS_TYPE_FILL_WHITE_FAST:
            case TRANS_TYPE_FILL_WHITE:
                this->transitionMode = TRANS_MODE_FILL_WHITE_INIT;
                break;

            case TRANS_TYPE_INSTANT:
                this->transitionMode = TRANS_MODE_INSTANT;
                break;

            case TRANS_TYPE_FILL_BROWN:
                this->transitionMode = TRANS_MODE_FILL_BROWN_INIT;
                break;

            case TRANS_TYPE_SANDSTORM_PERSIST:
                this->transitionMode = TRANS_MODE_SANDSTORM_INIT;
                break;

            case TRANS_TYPE_SANDSTORM_END:
                this->transitionMode = TRANS_MODE_SANDSTORM_END_INIT;
                break;

            case TRANS_TYPE_CS_BLACK_FILL:
                this->transitionMode = TRANS_MODE_CS_BLACK_FILL_INIT;
                break;

            case TRANS_TYPE_CIRCLE:
                fbdemoType = FBDEMO_CIRCLE;
                break;

            case TRANS_TYPE_WIPE5:
                fbdemoType = FBDEMO_WIPE5;
                break;

            default:
                fbdemoType = -1;
                _dbg_hungup("../z_play.c", 1420);
        }
    } else {
        fbdemoType = -1;
        _dbg_hungup("../z_play.c", 1423);
    }

    transitionCtx->transitionType = transitionType;
    transitionCtx->fbdemoType = fbdemoType;
    if (fbdemoType != -1) {
        Transition_Init(transitionCtx);
    }
}

void Play_ClearTransition(PlayState* this) {
    if (this->transitionCtx.fbdemoType != -1) {
        Transition_Destroy(&this->transitionCtx);
    }
    this->transitionCtx.transitionType = -1;
}

Gfx* Play_SetFog(PlayState* this, Gfx* gfx) {
    s32 fogFar = this->lightCtx.zFar * (5.0f / 64.0f);

    return Gfx_SetFogWithSync(gfx, this->lightCtx.fogColor[0], this->lightCtx.fogColor[1], this->lightCtx.fogColor[2],
                              0, this->lightCtx.fogNear, ((fogFar <= 1000) ? 1000 : fogFar));
}

void Play_Destroy(GameState* thisx) {
    PlayState* this = (PlayState*)thisx;
    GraphicsContext* gfxCtx = this->state.gfxCtx;

    if (sBombersNotebookOpen) {
        MsgEvent_SendNullTask();
        SysCfb_SetLoResMode();
        gfxCtx->curFrameBuffer = SysCfb_GetFramebuffer(gfxCtx->framebufferIndex % 2);
        gfxCtx->zbuffer = SysCfb_GetZBuffer();
        gfxCtx->viMode = gActiveViMode;
        gfxCtx->viConfigFeatures = gViConfigFeatures;
        gfxCtx->xScale = gViConfigXScale;
        gfxCtx->yScale = gViConfigYScale;
        gfxCtx->updateViMode = true;
        sBombersNotebookOpen = false;
    }

    BombersNotebook_Destroy(&sBombersNotebook);
    this->state.gfxCtx->callback = NULL;
    this->state.gfxCtx->callbackArg = 0;
    Play_DestroyMotionBlur();

    if (R_PAUSE_BG_PRERENDER_STATE != PAUSE_BG_PRERENDER_OFF) {
        PreRender_ApplyFiltersSlowlyDestroy(&this->pauseBgPreRender);
        R_PAUSE_BG_PRERENDER_STATE = PAUSE_BG_PRERENDER_OFF;
    }

    R_PICTO_PHOTO_STATE = PICTO_PHOTO_STATE_OFF;
    PreRender_Destroy(&this->pauseBgPreRender);
    this->unk_18E58 = NULL;
    this->pictoPhotoI8 = NULL;
    this->unk_18E60 = NULL;
    this->unk_18E64 = NULL;
    this->unk_18E68 = NULL;
    Effect_DestroyAll(this);
    EffectSS_Clear(this);
    CollisionCheck_DestroyContext(this, &this->colChkCtx);

    if (gTransitionTileState == TRANS_TILE_READY) {
        TransitionTile_Destroy(&sTransitionTile);
        gTransitionTileState = TRANS_TILE_OFF;
    }

    if ((this->transitionMode == TRANS_MODE_INSTANCE_RUNNING) || D_801D0D54) {
        this->transitionCtx.destroy(&this->transitionCtx.instanceData);
        Play_ClearTransition(this);
        this->transitionMode = TRANS_MODE_OFF;
    }

    ShrinkWindow_Destroy();
    TransitionFade_Destroy(&this->unk_18E48);
    VisMono_Destroy(&sPlayVisMono);
    func_80140EA0(D_801F6D4C);
    D_801F6D4C = NULL;

    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_92_80)) {
        Actor_CleanupContext(&this->actorCtx, this);
    }
    CLEAR_WEEKEVENTREG(WEEKEVENTREG_92_80);

    Interface_Destroy(this);
    KaleidoScopeCall_Destroy(this);
    KaleidoManager_Destroy();
    ZeldaArena_Cleanup();
}

#define PLAY_COMPRESS_BITS 5
#define PLAY_DECOMPRESS_BITS 8

void Play_CompressI8ToI5(void* srcI8, void* destI5, size_t size) {
    u32 i;
    u8* src = srcI8;
    s8* dest = destI5;
    s32 bitsLeft = PLAY_DECOMPRESS_BITS; // Bits left in the current dest pixel left to compress into
    u32 destPixel = 0;
    s32 shift;
    u32 srcPixel;

    for (i = 0; i < size; i++) {
        srcPixel = *src++;
        srcPixel = (srcPixel * 0x1F + 0x80) / 0xFF;
        shift = bitsLeft - PLAY_COMPRESS_BITS;
        if (shift > 0) {
            destPixel |= srcPixel << shift;
        } else {
            destPixel |= srcPixel >> -shift;
            *dest++ = destPixel;
            shift += PLAY_DECOMPRESS_BITS;
            destPixel = srcPixel << shift;
        }
        bitsLeft = shift;
    }

    if (bitsLeft < PLAY_DECOMPRESS_BITS) {
        *dest = destPixel;
    }
}

void Play_DecompressI5ToI8(void* srcI5, void* destI8, size_t size) {
    u32 i;
    u8* src = srcI5;
    s8* dest = destI8;
    s32 bitsLeft = PLAY_DECOMPRESS_BITS; // Bits left in the current src pixel left to decompress
    u32 destPixel;
    s32 shift;
    u32 srcPixel = *src++;

    for (i = 0; i < size; i++) {
        shift = bitsLeft - PLAY_COMPRESS_BITS;
        if (shift > 0) {
            destPixel = 0;
            destPixel |= srcPixel >> shift;
        } else {
            destPixel = 0;
            destPixel |= srcPixel << -shift;
            srcPixel = *src++;
            shift += PLAY_DECOMPRESS_BITS;
            destPixel |= srcPixel >> shift;
        }
        destPixel = (destPixel & 0x1F) * 0xFF / 0x1F;
        *dest++ = destPixel;
        bitsLeft = shift;
    }
}

f32 Play_GetWaterSurface(PlayState* this, Vec3f* pos, s32* lightIndex) {
    Player* player = GET_PLAYER(this);
    f32 waterSurfaceY = player->actor.world.pos.y;
    WaterBox* waterBox;
    s32 bgId;

    if (!WaterBox_GetSurfaceImpl(this, &this->colCtx, pos->x, pos->z, &waterSurfaceY, &waterBox, &bgId)) {
        return BGCHECK_Y_MIN;
    }

    if (waterSurfaceY < pos->y) {
        return BGCHECK_Y_MIN;
    }

    *lightIndex = WaterBox_GetLightSettingIndex(&this->colCtx, waterBox);
    return waterSurfaceY;
}

void Play_UpdateWaterCamera(PlayState* this, Camera* camera) {
    static s16 sQuakeIndex = -1;
    static s16 sIsCameraUnderwater = false;
    s32 pad;
    s32 lightIndex;
    Player* player = GET_PLAYER(this);

    sIsCameraUnderwater = camera->stateFlags & CAM_STATE_UNDERWATER;
    if (Play_GetWaterSurface(this, &camera->eye, &lightIndex) != BGCHECK_Y_MIN) {
        if (!sIsCameraUnderwater) {
            Camera_SetStateFlag(camera, CAM_STATE_UNDERWATER);
            sQuakeIndex = -1;
            Distortion_Request(DISTORTION_TYPE_UNDERWATER_ENTRY);
            Distortion_SetDuration(80);
        }

        func_801A3EC0(0x20);
        Environment_EnableUnderwaterLights(this, lightIndex);

        if ((sQuakeIndex == -1) || (Quake_GetTimeLeft(sQuakeIndex) == 10)) {
            s16 quakeIndex = Quake_Request(camera, QUAKE_TYPE_5);

            sQuakeIndex = quakeIndex;
            if (quakeIndex != 0) {
                Quake_SetSpeed(sQuakeIndex, 550);
                Quake_SetPerturbations(sQuakeIndex, 1, 1, 180, 0);
                Quake_SetDuration(sQuakeIndex, 1000);
            }
        }
        if (player->stateFlags3 & PLAYER_STATE3_8000) {
            Distortion_Request(DISTORTION_TYPE_ZORA_SWIMMING);
            Distortion_RemoveRequest(DISTORTION_TYPE_NON_ZORA_SWIMMING);
        } else {
            Distortion_Request(DISTORTION_TYPE_NON_ZORA_SWIMMING);
            Distortion_RemoveRequest(DISTORTION_TYPE_ZORA_SWIMMING);
        }
    } else {
        if (sIsCameraUnderwater) {
            Camera_UnsetStateFlag(camera, CAM_STATE_UNDERWATER);
        }
        Distortion_RemoveRequest(DISTORTION_TYPE_NON_ZORA_SWIMMING);
        Distortion_RemoveRequest(DISTORTION_TYPE_UNDERWATER_ENTRY);
        Distortion_RemoveRequest(DISTORTION_TYPE_ZORA_SWIMMING);
        if (sQuakeIndex != 0) {
            Quake_RemoveRequest(sQuakeIndex);
        }
        Environment_DisableUnderwaterLights(this);
        func_801A3EC0(0);
    }
}

void Play_UpdateTransition(PlayState* this) {
    s32 pad;

    if (this->transitionMode == TRANS_MODE_OFF) {
        return;
    }

    switch (this->transitionMode) {
        case TRANS_MODE_SETUP:
            if (this->transitionTrigger != TRANS_TRIGGER_END) {
                s16 sceneLayer = 0;

                Interface_SetHudVisibility(HUD_VISIBILITY_NONE);

                if (gSaveContext.nextCutsceneIndex >= 0xFFF0) {
                    sceneLayer = (gSaveContext.nextCutsceneIndex & 0xF) + 1;
                }

                if ((!(Entrance_GetTransitionFlags(this->nextEntrance + sceneLayer) & 0x8000) ||
                     ((this->nextEntrance == ENTRANCE(PATH_TO_MOUNTAIN_VILLAGE, 1)) &&
                      !CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_SNOWHEAD_TEMPLE)) ||
                     ((this->nextEntrance == ENTRANCE(ROAD_TO_SOUTHERN_SWAMP, 1)) &&
                      !CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_WOODFALL_TEMPLE)) ||
                     ((this->nextEntrance == ENTRANCE(TERMINA_FIELD, 2)) &&
                      !CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_GREAT_BAY_TEMPLE)) ||
                     ((this->nextEntrance == ENTRANCE(ROAD_TO_IKANA, 1)) &&
                      !CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_STONE_TOWER_TEMPLE))) &&
                    (!Environment_IsFinalHours(this) || (Entrance_GetSceneId(this->nextEntrance + sceneLayer) < 0) ||
                     (AudioSeq_GetActiveSeqId(SEQ_PLAYER_BGM_MAIN) != NA_BGM_FINAL_HOURS))) {
                    func_801A4058(20);
                    gSaveContext.seqId = (u8)NA_BGM_DISABLED;
                    gSaveContext.ambienceId = AMBIENCE_ID_DISABLED;
                }

                if (Environment_IsForcedSequenceDisabled()) {
                    func_801A4058(20);
                    gSaveContext.seqId = (u8)NA_BGM_DISABLED;
                    gSaveContext.ambienceId = AMBIENCE_ID_DISABLED;
                }

                if (Environment_IsFinalHours(this) && (Entrance_GetSceneId(this->nextEntrance + sceneLayer) >= 0) &&
                    (AudioSeq_GetActiveSeqId(SEQ_PLAYER_BGM_MAIN) == NA_BGM_FINAL_HOURS)) {
                    func_801A41C8(20);
                }
            }

            if (!D_801D0D54) {
                Play_SetupTransition(this, Play_ChooseDynamicTransition(this, this->transitionType));
            }

            if (this->transitionMode >= TRANS_MODE_FILL_WHITE_INIT) {
                // non-instance modes break out of this switch
                break;
            }
            // fallthrough
        case TRANS_MODE_INSTANCE_INIT: {
            s32 transWipeSpeed;
            s32 transFadeDuration;
            u32 color;

            this->transitionCtx.init(&this->transitionCtx.instanceData);

            if (this->transitionCtx.transitionType & (TRANS_TYPE_WIPE3 | TRANS_TYPE_WIPE4)) {
                this->transitionCtx.setType(&this->transitionCtx.instanceData,
                                            this->transitionCtx.transitionType | TRANS_TYPE_SET_PARAMS);
            }

            if ((this->transitionCtx.transitionType == TRANS_TYPE_WIPE_FAST) ||
                (this->transitionCtx.transitionType == TRANS_TYPE_FILL_WHITE_FAST)) {
                //! @bug TRANS_TYPE_FILL_WHITE_FAST will never reach this code.
                //! It is a non-instance type transition which doesn't run this case.
                transWipeSpeed = 28;
            } else {
                transWipeSpeed = 14;
            }
            gSaveContext.transWipeSpeed = transWipeSpeed;

            switch (this->transitionCtx.transitionType) {
                case TRANS_TYPE_FADE_BLACK_FAST:
                case TRANS_TYPE_FADE_WHITE_FAST:
                    transFadeDuration = 20;
                    break;

                case TRANS_TYPE_FADE_BLACK_SLOW:
                case TRANS_TYPE_FADE_WHITE_SLOW:
                    transFadeDuration = 150;
                    break;

                case TRANS_TYPE_FADE_WHITE_INSTANT:
                    transFadeDuration = 2;
                    break;

                default:
                    transFadeDuration = 60;
                    break;
            }
            gSaveContext.transFadeDuration = transFadeDuration;

            switch (this->transitionCtx.transitionType) {
                case TRANS_TYPE_FADE_WHITE:
                case TRANS_TYPE_FADE_WHITE_FAST:
                case TRANS_TYPE_FADE_WHITE_SLOW:
                case TRANS_TYPE_FADE_WHITE_CS_DELAYED:
                case TRANS_TYPE_FADE_WHITE_INSTANT:
                    color = RGBA8(160, 160, 160, 255);
                    break;

                case TRANS_TYPE_FADE_GREEN:
                    color = RGBA8(140, 140, 100, 255);
                    break;

                case TRANS_TYPE_FADE_BLUE:
                    color = RGBA8(70, 100, 110, 255);
                    break;

                default:
                    color = RGBA8(0, 0, 0, 255);
                    break;
            }

            this->transitionCtx.setColor(&this->transitionCtx.instanceData, color);
            if (this->transitionCtx.setEnvColor != NULL) {
                this->transitionCtx.setEnvColor(&this->transitionCtx.instanceData, color);
            }

            this->transitionCtx.setType(&this->transitionCtx.instanceData,
                                        (this->transitionTrigger == TRANS_TRIGGER_END) ? TRANS_INSTANCE_TYPE_FILL_OUT
                                                                                       : TRANS_INSTANCE_TYPE_FILL_IN);
            this->transitionCtx.start(&this->transitionCtx.instanceData);

            if (this->transitionCtx.transitionType == TRANS_TYPE_FADE_WHITE_CS_DELAYED) {
                this->transitionMode = TRANS_MODE_INSTANCE_WAIT;
            } else {
                this->transitionMode = TRANS_MODE_INSTANCE_RUNNING;
            }
            break;
        }

        case TRANS_MODE_INSTANCE_RUNNING:
            if (this->transitionCtx.isDone(&this->transitionCtx.instanceData)) {
                if (this->transitionTrigger != TRANS_TRIGGER_END) {
                    if (this->transitionCtx.transitionType == TRANS_TYPE_CIRCLE) {
                        D_801D0D54 = false;
                    }

                    if (gSaveContext.gameMode == GAMEMODE_OWL_SAVE) {
                        STOP_GAMESTATE(&this->state);
                        SET_NEXT_GAMESTATE(&this->state, TitleSetup_Init, sizeof(TitleSetupState));
                    } else if (gSaveContext.gameMode != GAMEMODE_FILE_SELECT) {
                        STOP_GAMESTATE(&this->state);
                        SET_NEXT_GAMESTATE(&this->state, Play_Init, sizeof(PlayState));
                        gSaveContext.save.entrance = this->nextEntrance;

                        if (gSaveContext.minigameStatus == MINIGAME_STATUS_ACTIVE) {
                            gSaveContext.minigameStatus = MINIGAME_STATUS_END;
                        }
                    } else { // GAMEMODE_FILE_SELECT
                        STOP_GAMESTATE(&this->state);
                        SET_NEXT_GAMESTATE(&this->state, FileSelect_Init, sizeof(FileSelectState));
                    }
                } else {
                    if (this->transitionCtx.transitionType == TRANS_TYPE_CIRCLE) {
                        D_801D0D54 = true;
                    } else {
                        this->transitionCtx.destroy(&this->transitionCtx.instanceData);
                        Play_ClearTransition(this);
                    }
                    this->transitionMode = TRANS_MODE_OFF;
                    if (gTransitionTileState == TRANS_TILE_READY) {
                        TransitionTile_Destroy(&sTransitionTile);
                        gTransitionTileState = TRANS_TILE_OFF;
                        GameState_SetFramerateDivisor(&this->state, 3);
                    }
                }
                this->transitionTrigger = TRANS_TRIGGER_OFF;
            } else {
                this->transitionCtx.update(&this->transitionCtx.instanceData, this->state.framerateDivisor);
            }
            break;
    }

    // update non-instance transitions
    switch (this->transitionMode) {
        case TRANS_MODE_FILL_WHITE_INIT:
            sTransitionFillTimer = 0;
            this->envCtx.fillScreen = true;
            this->envCtx.screenFillColor[0] = 160;
            this->envCtx.screenFillColor[1] = 160;
            this->envCtx.screenFillColor[2] = 160;

            if (this->transitionTrigger != TRANS_TRIGGER_END) {
                this->envCtx.screenFillColor[3] = 0;
                this->transitionMode = TRANS_MODE_FILL_IN;
            } else {
                this->envCtx.screenFillColor[3] = 255;
                this->transitionMode = TRANS_MODE_FILL_OUT;
            }
            break;

        case TRANS_MODE_FILL_IN:
            this->envCtx.screenFillColor[3] = (sTransitionFillTimer / 20.0f) * 255.0f;

            if (sTransitionFillTimer >= 20) {
                STOP_GAMESTATE(&this->state);
                SET_NEXT_GAMESTATE(&this->state, Play_Init, sizeof(PlayState));
                gSaveContext.save.entrance = this->nextEntrance;
                this->transitionTrigger = TRANS_TRIGGER_OFF;
                this->transitionMode = TRANS_MODE_OFF;
            } else {
                sTransitionFillTimer++;
            }
            break;

        case TRANS_MODE_FILL_OUT:
            this->envCtx.screenFillColor[3] = (1.0f - (sTransitionFillTimer / 20.0f)) * 255.0f;

            if (sTransitionFillTimer >= 20) {
                gTransitionTileState = TRANS_TILE_OFF;
                GameState_SetFramerateDivisor(&this->state, 3);
                this->transitionTrigger = TRANS_TRIGGER_OFF;
                this->transitionMode = TRANS_MODE_OFF;
                this->envCtx.fillScreen = false;
            } else {
                sTransitionFillTimer++;
            }
            break;

        case TRANS_MODE_FILL_BROWN_INIT:
            sTransitionFillTimer = 0;
            this->envCtx.fillScreen = true;
            this->envCtx.screenFillColor[0] = 170;
            this->envCtx.screenFillColor[1] = 160;
            this->envCtx.screenFillColor[2] = 150;

            if (this->transitionTrigger != TRANS_TRIGGER_END) {
                this->envCtx.screenFillColor[3] = 0;
                this->transitionMode = TRANS_MODE_FILL_IN;
            } else {
                this->envCtx.screenFillColor[3] = 255;
                this->transitionMode = TRANS_MODE_FILL_OUT;
            }
            break;

        case TRANS_MODE_INSTANT:
            if (this->transitionTrigger != TRANS_TRIGGER_END) {
                STOP_GAMESTATE(&this->state);
                SET_NEXT_GAMESTATE(&this->state, Play_Init, sizeof(PlayState));
                gSaveContext.save.entrance = this->nextEntrance;
                this->transitionTrigger = TRANS_TRIGGER_OFF;
                this->transitionMode = TRANS_MODE_OFF;
            } else {
                gTransitionTileState = TRANS_TILE_OFF;
                GameState_SetFramerateDivisor(&this->state, 3);
                this->transitionTrigger = TRANS_TRIGGER_OFF;
                this->transitionMode = TRANS_MODE_OFF;
            }
            break;

        case TRANS_MODE_INSTANCE_WAIT:
            if (gSaveContext.cutsceneTransitionControl != 0) {
                this->transitionMode = TRANS_MODE_INSTANCE_RUNNING;
            }
            break;

        case TRANS_MODE_SANDSTORM_INIT:
            if (this->transitionTrigger != TRANS_TRIGGER_END) {
                this->envCtx.sandstormState = SANDSTORM_FILL;
                this->transitionMode = TRANS_MODE_SANDSTORM;
            } else {
                this->envCtx.sandstormState = SANDSTORM_UNFILL;
                this->envCtx.sandstormPrimA = 255;
                this->envCtx.sandstormEnvA = 255;
                this->transitionMode = TRANS_MODE_SANDSTORM;
            }
            break;

        case TRANS_MODE_SANDSTORM:
            Audio_PlaySfx_2(NA_SE_EV_SAND_STORM - SFX_FLAG);
            if (this->transitionTrigger == TRANS_TRIGGER_END) {
                if (this->envCtx.sandstormPrimA < 110) {
                    gTransitionTileState = TRANS_TILE_OFF;
                    GameState_SetFramerateDivisor(&this->state, 3);
                    this->transitionTrigger = TRANS_TRIGGER_OFF;
                    this->transitionMode = TRANS_MODE_OFF;
                }
            } else {
                if (this->envCtx.sandstormEnvA == 255) {
                    STOP_GAMESTATE(&this->state);
                    SET_NEXT_GAMESTATE(&this->state, Play_Init, sizeof(PlayState));
                    gSaveContext.save.entrance = this->nextEntrance;
                    this->transitionTrigger = TRANS_TRIGGER_OFF;
                    this->transitionMode = TRANS_MODE_OFF;
                }
            }
            break;

        case TRANS_MODE_SANDSTORM_END_INIT:
            if (this->transitionTrigger == TRANS_TRIGGER_END) {
                this->envCtx.sandstormState = SANDSTORM_DISSIPATE;
                this->envCtx.sandstormPrimA = 255;
                this->envCtx.sandstormEnvA = 255;

                // "It's here!!!!!!!!!"
                (void)"来た!!!!!!!!!!!!!!!!!!!!!";

                this->transitionMode = TRANS_MODE_SANDSTORM_END;
            } else {
                this->transitionMode = TRANS_MODE_SANDSTORM_INIT;
            }
            break;

        case TRANS_MODE_SANDSTORM_END:
            Audio_PlaySfx_2(NA_SE_EV_SAND_STORM - SFX_FLAG);

            if (this->transitionTrigger == TRANS_TRIGGER_END) {
                if (this->envCtx.sandstormPrimA <= 0) {
                    gTransitionTileState = TRANS_TILE_OFF;
                    GameState_SetFramerateDivisor(&this->state, 3);
                    this->transitionTrigger = TRANS_TRIGGER_OFF;
                    this->transitionMode = TRANS_MODE_OFF;
                }
            }
            break;

        case TRANS_MODE_CS_BLACK_FILL_INIT:
            sTransitionFillTimer = 0;
            this->envCtx.fillScreen = true;
            this->envCtx.screenFillColor[0] = 0;
            this->envCtx.screenFillColor[1] = 0;
            this->envCtx.screenFillColor[2] = 0;
            this->envCtx.screenFillColor[3] = 255;
            this->transitionMode = TRANS_MODE_CS_BLACK_FILL;
            break;

        case TRANS_MODE_CS_BLACK_FILL:
            if (gSaveContext.cutsceneTransitionControl != 0) {
                this->envCtx.screenFillColor[3] = gSaveContext.cutsceneTransitionControl;

                if (gSaveContext.cutsceneTransitionControl <= 100) {
                    gTransitionTileState = TRANS_TILE_OFF;
                    GameState_SetFramerateDivisor(&this->state, 3);
                    this->transitionTrigger = TRANS_TRIGGER_OFF;
                    this->transitionMode = TRANS_MODE_OFF;
                }
            }
            break;
    }
}

const char D_801DFA34[][4] = {
    "all", "a",  "a",  "b",  "b",  "c",  "c",  "d",   "d",   "e",  "e",  "f",  "fa", "fa", "fb", "fb",
    "fc",  "fc", "fd", "fd", "fe", "fe", "fg", "fg",  "fh",  "fh", "fi", "fi", "fj", "fj", "fk", "fk",
    "f",   "g",  "g",  "h",  "h",  "i",  "i",  "all", "all", "a",  "b",  "c",  "d",  "e",  "f",  "g",
    "h",   "i",  "f",  "fa", "fb", "fc", "fd", "fe",  "ff",  "fg", "fh", "fi", "fj", "fk",
};

#ifdef NON_MATCHING
// Stack issues
void Play_UpdateMain(PlayState* this) {
    Input* input = this->state.input;
    u8 freezeFlashTimer;
    s32 sp5C = false;

    gSegments[4] = VIRTUAL_TO_PHYSICAL(this->objectCtx.slots[this->objectCtx.mainKeepSlot].segment);
    gSegments[5] = VIRTUAL_TO_PHYSICAL(this->objectCtx.slots[this->objectCtx.subKeepSlot].segment);
    gSegments[2] = VIRTUAL_TO_PHYSICAL(this->sceneSegment);

    if (R_PICTO_PHOTO_STATE == PICTO_PHOTO_STATE_PROCESS) {
        R_PICTO_PHOTO_STATE = PICTO_PHOTO_STATE_READY;
        MsgEvent_SendNullTask();
        Play_TakePictoPhoto(&this->pauseBgPreRender);
        R_PICTO_PHOTO_STATE = PICTO_PHOTO_STATE_OFF;
    }
    Actor_SetMovementScale(this->state.framerateDivisor);

    if (FrameAdvance_Update(&this->frameAdvCtx, &input[1])) {
        if ((this->transitionMode == TRANS_MODE_OFF) && (this->transitionTrigger != TRANS_TRIGGER_OFF)) {
            this->transitionMode = TRANS_MODE_SETUP;
        }

        if (gTransitionTileState != TRANS_TILE_OFF) {
            switch (gTransitionTileState) {
                case TRANS_TILE_PROCESS:
                    if (TransitionTile_Init(&sTransitionTile, 10, 7) == NULL) {
                        gTransitionTileState = TRANS_TILE_OFF;
                    } else {
                        sTransitionTile.zBuffer = gZBufferPtr;
                        gTransitionTileState = TRANS_TILE_READY;
                        GameState_SetFramerateDivisor(&this->state, 1);
                    }
                    break;

                case TRANS_TILE_READY:
                    TransitionTile_Update(&sTransitionTile);
                    break;

                default:
                    break;
            }
        }
        Play_UpdateTransition(this);
        if (gTransitionTileState != TRANS_TILE_READY) {
            if ((gSaveContext.gameMode == GAMEMODE_NORMAL) &&
                (((this->msgCtx.msgMode == MSGMODE_NONE)) ||
                 ((this->msgCtx.currentTextId == 0xFF) && (this->msgCtx.msgMode == MSGMODE_TEXT_DONE) &&
                  (this->msgCtx.textboxEndType == TEXTBOX_ENDTYPE_41)) ||
                 ((this->msgCtx.currentTextId >= 0x100) && (this->msgCtx.currentTextId <= 0x200))) &&
                (this->gameOverCtx.state == GAMEOVER_INACTIVE)) {
                KaleidoSetup_Update(this);
            }

            sp5C = (this->pauseCtx.state != 0) || (this->pauseCtx.debugEditor != DEBUG_EDITOR_NONE);

            AnimationContext_Reset(&this->animationCtx);
            Object_UpdateEntries(&this->objectCtx);

            if (!sp5C && (IREG(72) == 0)) {
                this->gameplayFrames++;
                Rumble_SetUpdateEnabled(true);
                if ((this->actorCtx.freezeFlashTimer != 0) && (this->actorCtx.freezeFlashTimer-- < 5)) {
                    freezeFlashTimer = this->actorCtx.freezeFlashTimer;
                    if ((freezeFlashTimer > 0) && ((freezeFlashTimer % 2) != 0)) {
                        this->envCtx.fillScreen = true;
                        this->envCtx.screenFillColor[0] = this->envCtx.screenFillColor[1] =
                            this->envCtx.screenFillColor[2] = 150;
                        this->envCtx.screenFillColor[3] = 80;
                    } else {
                        this->envCtx.fillScreen = false;
                    }
                } else {
                    Room_HandleLoadCallbacks(this, &this->roomCtx);
                    CollisionCheck_AT(this, &this->colChkCtx);
                    CollisionCheck_OC(this, &this->colChkCtx);
                    CollisionCheck_Damage(this, &this->colChkCtx);
                    CollisionCheck_ClearContext(this, &this->colChkCtx);
                    if (!this->haltAllActors) {
                        Actor_UpdateAll(this, &this->actorCtx);
                    }
                    Cutscene_UpdateManual(this, &this->csCtx);
                    Cutscene_UpdateScripted(this, &this->csCtx);
                    Effect_UpdateAll(this);
                    EffectSS_UpdateAllParticles(this);
                    EffFootmark_Update(this);
                }
            } else {
                Rumble_SetUpdateEnabled(false);
            }

            Room_Noop(this, &this->roomCtx.curRoom, &input[1], 0);
            Room_Noop(this, &this->roomCtx.prevRoom, &input[1], 1);
            Skybox_Update(&this->skyboxCtx);

            if ((this->pauseCtx.state != 0) || (this->pauseCtx.debugEditor != DEBUG_EDITOR_NONE)) {
                KaleidoScopeCall_Update(this);
            } else if (this->gameOverCtx.state != GAMEOVER_INACTIVE) {
                GameOver_Update(this);
            }

            Message_Update(this);
            Interface_Update(this);
            AnimationContext_Update(this, &this->animationCtx);
            SoundSource_UpdateAll(this);
            ShrinkWindow_Update(this->state.framerateDivisor);
            TransitionFade_Update(&this->unk_18E48, this->state.framerateDivisor);
        }
    }

    if (!sp5C || gDbgCamEnabled) {
        s32 sp54;   // camId
        Vec3s sp48; // InputDir

        this->nextCamera = this->activeCamId;
        for (sp54 = 0; sp54 < 4; sp54++) {
            if ((sp54 != this->nextCamera) && (this->cameraPtrs[sp54] != NULL)) {
                Camera_Update(&sp48, this->cameraPtrs[sp54]);
            }
        }
        Camera_Update(&sp48, this->cameraPtrs[this->nextCamera]);
    }

    if (!sp5C) {
        Play_UpdateWaterCamera(this, this->cameraPtrs[this->nextCamera]);
        Distortion_Update();
    }

    Environment_Update(this, &this->envCtx, &this->lightCtx, &this->pauseCtx, &this->msgCtx, &this->gameOverCtx,
                       this->state.gfxCtx);

    if (this->sramCtx.status != 0) {
        if (gSaveContext.save.isOwlSave) {
            Sram_UpdateWriteToFlashOwlSave(&this->sramCtx);
        } else {
            Sram_UpdateWriteToFlashDefault(&this->sramCtx);
        }
    }
}
#else
void Play_UpdateMain(PlayState* this);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_UpdateMain.s")
#endif

void Play_Update(PlayState* this) {
    if (!sBombersNotebookOpen) {
        if (this->pauseCtx.bombersNotebookOpen) {
            sBombersNotebookOpen = true;
            sBombersNotebook.loadState = BOMBERS_NOTEBOOK_LOAD_STATE_NONE;
        }
    } else if (CHECK_BTN_ALL(CONTROLLER1(&this->state)->press.button, BTN_L) ||
               CHECK_BTN_ALL(CONTROLLER1(&this->state)->press.button, BTN_B) ||
               CHECK_BTN_ALL(CONTROLLER1(&this->state)->press.button, BTN_START) || (gIrqMgrResetStatus != 0)) {
        sBombersNotebookOpen = false;
        this->pauseCtx.bombersNotebookOpen = false;
        sBombersNotebook.loadState = BOMBERS_NOTEBOOK_LOAD_STATE_NONE;
        this->msgCtx.msgLength = 0;
        this->msgCtx.msgMode = MSGMODE_NONE;
        this->msgCtx.currentTextId = 0;
        this->msgCtx.stateTimer = 0;
        Audio_PlaySfx(NA_SE_SY_CANCEL);
    }
    if (sBombersNotebookOpen) {
        BombersNotebook_Update(this, &sBombersNotebook, this->state.input);
        Message_Update(this);
    } else {
        Play_UpdateMain(this);
    }
}

void Play_PostWorldDraw(PlayState* this) {
    if ((this->pauseCtx.state != 0) || (this->pauseCtx.debugEditor != DEBUG_EDITOR_NONE)) {
        KaleidoScopeCall_Draw(this);
    }

    if (gSaveContext.gameMode == GAMEMODE_NORMAL) {
        Interface_Draw(this);
    }

    if (((this->pauseCtx.state == 0) && (this->pauseCtx.debugEditor == DEBUG_EDITOR_NONE)) ||
        (this->msgCtx.currentTextId != 0xFF)) {
        Message_Draw(this);
    }

    if (this->gameOverCtx.state != GAMEOVER_INACTIVE) {
        GameOver_FadeLights(this);
    }

    // Shrink the whole screen display (at the end of First and Second Day by default)
    if (gSaveContext.screenScaleFlag) {
        Gfx* nextOpa;
        Gfx* opa;
        GraphicsContext* gfxCtx = this->state.gfxCtx;

        D_801F6D4C->scale = gSaveContext.screenScale / 1000.0f;

        OPEN_DISPS(gfxCtx);

        opa = POLY_OPA_DISP;
        nextOpa = Graph_GfxPlusOne(opa);
        gSPDisplayList(OVERLAY_DISP++, nextOpa);

        func_80141778(D_801F6D4C, &nextOpa, this->unk_18E60, gfxCtx);

        gSPEndDisplayList(nextOpa++);
        Graph_BranchDlist(opa, nextOpa);
        POLY_OPA_DISP = nextOpa;

        CLOSE_DISPS(gfxCtx);
    }
}

#ifdef NON_MATCHING
// Something weird going on with the stack of the unused arg0 of `Camera_Update`
void Play_DrawMain(PlayState* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;
    Lights* sp268;
    Vec3f sp25C;
    u8 sp25B = false;

    if (R_PAUSE_BG_PRERENDER_STATE >= PAUSE_BG_PRERENDER_UNK4) {
        PreRender_ApplyFiltersSlowlyDestroy(&this->pauseBgPreRender);
        R_PAUSE_BG_PRERENDER_STATE = PAUSE_BG_PRERENDER_OFF;
    }

    if ((R_PAUSE_BG_PRERENDER_STATE <= PAUSE_BG_PRERENDER_SETUP) && (gTransitionTileState <= TRANS_TILE_SETUP)) {
        if (this->skyboxCtx.skyboxShouldDraw || (this->roomCtx.curRoom.roomShape->base.type == ROOM_SHAPE_TYPE_IMAGE)) {
            func_8012CF0C(gfxCtx, false, true, 0, 0, 0);
        } else {
            func_8012CF0C(gfxCtx, true, true, this->lightCtx.fogColor[0], this->lightCtx.fogColor[1],
                          this->lightCtx.fogColor[2]);
        }
    } else {
        func_8012CF0C(gfxCtx, false, false, 0, 0, 0);
    }

    OPEN_DISPS(gfxCtx);

    gSegments[4] = VIRTUAL_TO_PHYSICAL(this->objectCtx.slots[this->objectCtx.mainKeepSlot].segment);
    gSegments[5] = VIRTUAL_TO_PHYSICAL(this->objectCtx.slots[this->objectCtx.subKeepSlot].segment);
    gSegments[2] = VIRTUAL_TO_PHYSICAL(this->sceneSegment);

    gSPSegment(POLY_OPA_DISP++, 0x04, this->objectCtx.slots[this->objectCtx.mainKeepSlot].segment);
    gSPSegment(POLY_XLU_DISP++, 0x04, this->objectCtx.slots[this->objectCtx.mainKeepSlot].segment);
    gSPSegment(OVERLAY_DISP++, 0x04, this->objectCtx.slots[this->objectCtx.mainKeepSlot].segment);

    gSPSegment(POLY_OPA_DISP++, 0x05, this->objectCtx.slots[this->objectCtx.subKeepSlot].segment);
    gSPSegment(POLY_XLU_DISP++, 0x05, this->objectCtx.slots[this->objectCtx.subKeepSlot].segment);
    gSPSegment(OVERLAY_DISP++, 0x05, this->objectCtx.slots[this->objectCtx.subKeepSlot].segment);

    gSPSegment(POLY_OPA_DISP++, 0x02, this->sceneSegment);
    gSPSegment(POLY_XLU_DISP++, 0x02, this->sceneSegment);
    gSPSegment(OVERLAY_DISP++, 0x02, this->sceneSegment);

    if (1) {
        f32 var_fv0; // zFar

        ShrinkWindow_Draw(gfxCtx);

        POLY_OPA_DISP = Play_SetFog(this, POLY_OPA_DISP);
        POLY_XLU_DISP = Play_SetFog(this, POLY_XLU_DISP);

        // zFar
        var_fv0 = this->lightCtx.zFar;
        if (var_fv0 > 12800.0f) {
            var_fv0 = 12800.0f;
        }

        View_SetPerspective(&this->view, this->view.fovy, this->view.zNear, var_fv0);

        View_Apply(&this->view, 0xF);

        // The billboard matrix temporarily stores the viewing matrix
        Matrix_MtxToMtxF(&this->view.viewing, &this->billboardMtxF);
        Matrix_MtxToMtxF(&this->view.projection, &this->viewProjectionMtxF);

        this->projectionMtxFDiagonal.x = this->viewProjectionMtxF.xx;
        this->projectionMtxFDiagonal.y = this->viewProjectionMtxF.yy;
        this->projectionMtxFDiagonal.z = -this->viewProjectionMtxF.zz;

        SkinMatrix_MtxFMtxFMult(&this->viewProjectionMtxF, &this->billboardMtxF, &this->viewProjectionMtxF);

        this->billboardMtxF.mf[3][2] = this->billboardMtxF.mf[3][1] = this->billboardMtxF.mf[3][0] =
            this->billboardMtxF.mf[2][3] = this->billboardMtxF.mf[1][3] = this->billboardMtxF.mf[0][3] = 0.0f;

        Matrix_Transpose(&this->billboardMtxF);

        this->billboardMtx = GRAPH_ALLOC(this->state.gfxCtx, 2 * sizeof(Mtx));

        Matrix_MtxFToMtx(&this->billboardMtxF, this->billboardMtx);
        Matrix_RotateYF(BINANG_TO_RAD((s16)(Camera_GetCamDirYaw(GET_ACTIVE_CAM(this)) + 0x8000)), MTXMODE_NEW);
        Matrix_ToMtx(this->billboardMtx + 1);

        gSPSegment(POLY_OPA_DISP++, 0x01, this->billboardMtx);
        gSPSegment(POLY_XLU_DISP++, 0x01, this->billboardMtx);
        gSPSegment(OVERLAY_DISP++, 0x01, this->billboardMtx);

        if (1) {
            Gfx* sp218;
            Gfx* sp214 = POLY_OPA_DISP;

            sp218 = Graph_GfxPlusOne(sp214);
            gSPDisplayList(OVERLAY_DISP++, sp218);

            if (((this->transitionMode == TRANS_MODE_INSTANCE_RUNNING) ||
                 (this->transitionMode == TRANS_TYPE_INSTANT)) ||
                D_801D0D54) {
                View spA8;

                View_Init(&spA8, gfxCtx);
                spA8.flags = 0xA;

                SET_FULLSCREEN_VIEWPORT(&spA8);

                View_ApplyTo(&spA8, &sp218);
                this->transitionCtx.draw(&this->transitionCtx.instanceData, &sp218);
            }

            TransitionFade_Draw(&this->unk_18E48, &sp218);

            if (gVisMonoColor.a != 0) {
                sPlayVisMono.primColor.rgba = gVisMonoColor.rgba;
                VisMono_Draw(&sPlayVisMono, &sp218);
            }

            gSPEndDisplayList(sp218++);
            Graph_BranchDlist(sp214, sp218);
            POLY_OPA_DISP = sp218;
        }

        if (gTransitionTileState == TRANS_TILE_READY) {
            Gfx* sp90 = POLY_OPA_DISP;

            TransitionTile_Draw(&sTransitionTile, &sp90);
            POLY_OPA_DISP = sp90;
            sp25B = true;
            goto PostWorldDraw;
        }

        PreRender_SetValues(&this->pauseBgPreRender, gCfbWidth, gCfbHeight, gfxCtx->curFrameBuffer, gfxCtx->zbuffer);

        if (R_PAUSE_BG_PRERENDER_STATE == PAUSE_BG_PRERENDER_PROCESS) {
            MsgEvent_SendNullTask();
            if (!gSaveContext.screenScaleFlag) {
                PreRender_ApplyFiltersSlowlyInit(&this->pauseBgPreRender);
            }
            R_PAUSE_BG_PRERENDER_STATE = PAUSE_BG_PRERENDER_READY;
            SREG(33) |= 1;
        } else {
            if (R_PAUSE_BG_PRERENDER_STATE == PAUSE_BG_PRERENDER_READY) {
                Gfx* sp8C = POLY_OPA_DISP;

                if (this->pauseBgPreRender.filterState == PRERENDER_FILTER_STATE_DONE) {
                    PreRender_RestoreFramebuffer(&this->pauseBgPreRender, &sp8C);
                } else {
                    func_80170798(&this->pauseBgPreRender, &sp8C);
                }

                gSPDisplayList(sp8C++, D_0E000000.syncSegments);
                POLY_OPA_DISP = sp8C;
                sp25B = true;
                goto PostWorldDraw;
            }

            if (!this->unk_18844) {
                if (1) {
                    if (((u32)this->skyboxId != SKYBOX_NONE) && !this->envCtx.skyboxDisabled) {
                        if ((this->skyboxId == SKYBOX_NORMAL_SKY) || (this->skyboxId == SKYBOX_3)) {
                            Environment_UpdateSkybox(this->skyboxId, &this->envCtx, &this->skyboxCtx);
                            Skybox_Draw(&this->skyboxCtx, gfxCtx, this->skyboxId, this->envCtx.skyboxBlend,
                                        this->view.eye.x, this->view.eye.y, this->view.eye.z);
                        } else if (!this->skyboxCtx.skyboxShouldDraw) {
                            Skybox_Draw(&this->skyboxCtx, gfxCtx, this->skyboxId, 0, this->view.eye.x, this->view.eye.y,
                                        this->view.eye.z);
                        }
                    }

                    Environment_Draw(this);
                }

                sp268 = LightContext_NewLights(&this->lightCtx, gfxCtx);

                if (this->roomCtx.curRoom.enablePosLights || (MREG(93) != 0)) {
                    sp268->enablePosLights = true;
                }

                Lights_BindAll(sp268, this->lightCtx.listHead, NULL, this);
                Lights_Draw(sp268, gfxCtx);

                if (1) {
                    u32 roomDrawFlags = ((1) ? 1 : 0) | (((void)0, 1) ? 2 : 0); // FAKE:

                    Scene_Draw(this);
                    if (this->roomCtx.unk78) {
                        Room_Draw(this, &this->roomCtx.curRoom, roomDrawFlags & 3);
                        Room_Draw(this, &this->roomCtx.prevRoom, roomDrawFlags & 3);
                    }
                }

                if (this->skyboxCtx.skyboxShouldDraw) {
                    Vec3f sp78;

                    if (1) {
                        Camera_GetQuakeOffset(&sp78, GET_ACTIVE_CAM(this));
                        Skybox_Draw(&this->skyboxCtx, gfxCtx, this->skyboxId, 0, this->view.eye.x + sp78.x,
                                    this->view.eye.y + sp78.y, this->view.eye.z + sp78.z);
                    }
                }

                if (this->envCtx.precipitation[PRECIP_RAIN_CUR] != 0) {
                    Environment_DrawRain(this, &this->view, gfxCtx);
                }
            }

            if (1) {
                Environment_FillScreen(gfxCtx, 0, 0, 0, this->bgCoverAlpha, 1);
            }

            if (1) {
                Actor_DrawAll(this, &this->actorCtx);
            }

            if (1) {
                if (!this->envCtx.sunDisabled) {
                    sp25C.x = this->view.eye.x + this->envCtx.sunPos.x;
                    sp25C.y = this->view.eye.y + this->envCtx.sunPos.y;
                    sp25C.z = this->view.eye.z + this->envCtx.sunPos.z;
                    Environment_DrawSunLensFlare(this, &this->envCtx, &this->view, gfxCtx, sp25C);
                }

                Environment_DrawCustomLensFlare(this);
            }

            if (1) {
                if (R_PLAY_FILL_SCREEN_ON) {
                    Environment_FillScreen(gfxCtx, R_PLAY_FILL_SCREEN_R, R_PLAY_FILL_SCREEN_G, R_PLAY_FILL_SCREEN_B,
                                           R_PLAY_FILL_SCREEN_ALPHA, 3);
                }

                switch (this->envCtx.fillScreen) {
                    case 1:
                        Environment_FillScreen(gfxCtx, this->envCtx.screenFillColor[0], this->envCtx.screenFillColor[1],
                                               this->envCtx.screenFillColor[2], this->envCtx.screenFillColor[3], 3);
                        break;

                    default:
                        break;
                }
            }

            if (1) {
                if (this->envCtx.sandstormState != SANDSTORM_OFF) {
                    Environment_DrawSandstorm(this, this->envCtx.sandstormState);
                }
            }

            if (this->worldCoverAlpha != 0) {
                Environment_FillScreen(gfxCtx, 0, 0, 0, this->worldCoverAlpha, 3);
            }

            if (1) {
                DebugDisplay_DrawObjects(this);
            }

            Play_DrawMotionBlur(this);

            if ((R_PAUSE_BG_PRERENDER_STATE == PAUSE_BG_PRERENDER_SETUP) ||
                (gTransitionTileState == TRANS_TILE_SETUP) || (R_PICTO_PHOTO_STATE == PICTO_PHOTO_STATE_SETUP)) {
                Gfx* sp74;
                Gfx* sp70 = POLY_OPA_DISP;

                sp74 = Graph_GfxPlusOne(sp70);
                gSPDisplayList(OVERLAY_DISP++, sp74);
                this->pauseBgPreRender.fbuf = gfxCtx->curFrameBuffer;

                if (R_PAUSE_BG_PRERENDER_STATE == PAUSE_BG_PRERENDER_SETUP) {
                    R_PAUSE_BG_PRERENDER_STATE = PAUSE_BG_PRERENDER_PROCESS;
                    this->pauseBgPreRender.fbufSave = gfxCtx->zbuffer;
                    this->pauseBgPreRender.cvgSave = this->unk_18E58;
                } else if (R_PICTO_PHOTO_STATE == PICTO_PHOTO_STATE_SETUP) {
                    R_PICTO_PHOTO_STATE = PICTO_PHOTO_STATE_PROCESS;
                    this->pauseBgPreRender.fbufSave = gfxCtx->zbuffer;
                    this->pauseBgPreRender.cvgSave = this->unk_18E58;
                } else {
                    gTransitionTileState = TRANS_TILE_PROCESS;
                    this->pauseBgPreRender.fbufSave = gfxCtx->zbuffer;
                    this->pauseBgPreRender.cvgSave = NULL;
                }

                PreRender_SaveFramebuffer(&this->pauseBgPreRender, &sp74);

                if (this->pauseBgPreRender.cvgSave != NULL) {
                    PreRender_DrawCoverage(&this->pauseBgPreRender, &sp74);
                }

                gSPEndDisplayList(sp74++);
                Graph_BranchDlist(sp70, sp74);
                POLY_OPA_DISP = sp74;
                this->unk_18B49 = 2;
                SREG(33) |= 1;
                goto SkipPostWorldDraw;
            }

        PostWorldDraw:
            if (1) {
                Play_PostWorldDraw(this);
            }
        }
    }

SkipPostWorldDraw:

    if ((this->view.unk164 != 0) && !gDbgCamEnabled) {
        Vec3s sp4C;

        Camera_Update(&sp4C, GET_ACTIVE_CAM(this));
        View_UpdateViewingMatrix(&this->view);
        this->view.unk164 = 0;
        if ((this->skyboxId != SKYBOX_NONE) && !this->envCtx.skyboxDisabled) {
            Skybox_UpdateMatrix(&this->skyboxCtx, this->view.eye.x, this->view.eye.y, this->view.eye.z);
        }
    }

    if (!sp25B) {
        Environment_DrawSkyboxStars(this);
    }

    CLOSE_DISPS(gfxCtx);
}
#else
void Play_DrawMain(PlayState* this);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_play/Play_DrawMain.s")
#endif

void Play_Draw(PlayState* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;

    {
        GraphicsContext* gfxCtx2 = this->state.gfxCtx;

        if (sBombersNotebookOpen) {
            if (gSysCfbHiResEnabled != 1) {
                MsgEvent_SendNullTask();
                SysCfb_SetHiResMode();
                gfxCtx2->curFrameBuffer = SysCfb_GetFramebuffer(gfxCtx2->framebufferIndex % 2);
                gfxCtx2->zbuffer = SysCfb_GetZBuffer();
                gfxCtx2->viMode = gActiveViMode;
                gfxCtx2->viConfigFeatures = gViConfigFeatures;
                gfxCtx2->xScale = gViConfigXScale;
                gfxCtx2->yScale = gViConfigYScale;
                gfxCtx2->updateViMode = true;
            }
        } else {
            if (gSysCfbHiResEnabled != 0) {
                MsgEvent_SendNullTask();
                SysCfb_SetLoResMode();
                gfxCtx2->curFrameBuffer = SysCfb_GetFramebuffer(gfxCtx2->framebufferIndex % 2);
                gfxCtx2->zbuffer = SysCfb_GetZBuffer();
                gfxCtx2->viMode = gActiveViMode;
                gfxCtx2->viConfigFeatures = gViConfigFeatures;
                gfxCtx2->xScale = gViConfigXScale;
                gfxCtx2->yScale = gViConfigYScale;
                gfxCtx2->updateViMode = true;
            }
        }
    }

    if (sBombersNotebookOpen && ((SREG(2) != 2) || (gZBufferPtr == NULL))) {
        BombersNotebook_Draw(&sBombersNotebook, gfxCtx);
        Message_Draw(this);
    } else {
        Play_DrawMain(this);
    }
}

void Play_Main(GameState* thisx) {
    static Input* prevInput = NULL;
    PlayState* this = (PlayState*)thisx;

    prevInput = CONTROLLER1(&this->state);
    DebugDisplay_Init();

    {
        GraphicsContext* gfxCtx = this->state.gfxCtx;

        if (1) {
            this->state.gfxCtx = NULL;
        }
        Play_Update(this);
        this->state.gfxCtx = gfxCtx;
    }

    {
        Input input = *CONTROLLER1(&this->state);

        if (1) {
            *CONTROLLER1(&this->state) = D_801F6C18;
        }
        Play_Draw(this);
        *CONTROLLER1(&this->state) = input;
    }

    CutsceneManager_Update();
    CutsceneManager_ClearWaiting();
}

s32 Play_InCsMode(PlayState* this) {
    return (this->csCtx.state != CS_STATE_IDLE) || Player_InCsMode(this);
}

f32 Play_GetFloorSurfaceImpl(PlayState* this, MtxF* mtx, CollisionPoly** poly, s32* bgId, Vec3f* pos) {
    f32 floorHeight = BgCheck_EntityRaycastFloor3(&this->colCtx, poly, bgId, pos);

    if (floorHeight > BGCHECK_Y_MIN) {
        func_800C0094(*poly, pos->x, floorHeight, pos->z, mtx);
    } else {
        mtx->xy = 0.0f;
        mtx->zx = 0.0f;
        mtx->yx = 0.0f;
        mtx->xx = 0.0f;
        mtx->wz = 0.0f;
        mtx->xz = 0.0f;
        mtx->wy = 0.0f;
        mtx->wx = 0.0f;
        mtx->zz = 0.0f;
        mtx->yz = 0.0f;
        mtx->zy = 0.0f;
        mtx->yy = 1.0f;
        mtx->xw = pos->x;
        mtx->yw = pos->y;
        mtx->zw = pos->z;
        mtx->ww = 1.0f;
    }

    return floorHeight;
}

void Play_GetFloorSurface(PlayState* this, MtxF* mtx, Vec3f* pos) {
    CollisionPoly* poly;
    s32 bgId;

    Play_GetFloorSurfaceImpl(this, mtx, &poly, &bgId, pos);
}

void* Play_LoadFile(PlayState* this, RomFile* entry) {
    size_t size = entry->vromEnd - entry->vromStart;
    void* allocp = THA_AllocTailAlign16(&this->state.tha, size);

    DmaMgr_SendRequest0(allocp, entry->vromStart, size);

    return allocp;
}

void Play_InitEnvironment(PlayState* this, s16 skyboxId) {
    Skybox_Init(&this->state, &this->skyboxCtx, skyboxId);
    Environment_Init(this, &this->envCtx, 0);
}

void Play_InitScene(PlayState* this, s32 spawn) {
    this->curSpawn = spawn;
    this->linkActorEntry = NULL;
    this->actorCsCamList = NULL;
    this->setupEntranceList = NULL;
    this->setupExitList = NULL;
    this->naviQuestHints = NULL;
    this->setupPathList = NULL;
    this->sceneMaterialAnims = NULL;
    this->roomCtx.unk74 = NULL;
    this->numSetupActors = 0;
    Object_InitContext(&this->state, &this->objectCtx);
    LightContext_Init(this, &this->lightCtx);
    Door_InitContext(&this->state, &this->doorCtx);
    Room_Init(this, &this->roomCtx);
    gSaveContext.worldMapArea = 0;
    Scene_ExecuteCommands(this, this->sceneSegment);
    Play_InitEnvironment(this, this->skyboxId);
}

void Play_SpawnScene(PlayState* this, s32 sceneId, s32 spawn) {
    s32 pad;
    SceneTableEntry* scene = &gSceneTable[sceneId];

    scene->unk_D = 0;
    this->loadedScene = scene;
    this->sceneId = sceneId;
    this->sceneConfig = scene->drawConfig;
    this->sceneSegment = Play_LoadFile(this, &scene->segment);
    scene->unk_D = 0;
    gSegments[2] = VIRTUAL_TO_PHYSICAL(this->sceneSegment);
    Play_InitScene(this, spawn);
    Room_AllocateAndLoad(this, &this->roomCtx);
}

void Play_GetScreenPos(PlayState* this, Vec3f* worldPos, Vec3f* screenPos) {
    f32 invW;

    // screenPos temporarily stores the projectedPos
    Actor_GetProjectedPos(this, worldPos, screenPos, &invW);

    screenPos->x = (SCREEN_WIDTH / 2) + (screenPos->x * invW * (SCREEN_WIDTH / 2));
    screenPos->y = (SCREEN_HEIGHT / 2) - (screenPos->y * invW * (SCREEN_HEIGHT / 2));
}

s16 Play_CreateSubCamera(PlayState* this) {
    s16 subCamId;

    for (subCamId = CAM_ID_SUB_FIRST; subCamId < NUM_CAMS; subCamId++) {
        if (this->cameraPtrs[subCamId] == NULL) {
            break;
        }
    }

    // if no subCameras available
    if (subCamId == NUM_CAMS) {
        return CAM_ID_NONE;
    }

    this->cameraPtrs[subCamId] = &this->subCameras[subCamId - CAM_ID_SUB_FIRST];
    Camera_Init(this->cameraPtrs[subCamId], &this->view, &this->colCtx, this);
    this->cameraPtrs[subCamId]->camId = subCamId;

    return subCamId;
}

s16 Play_GetActiveCamId(PlayState* this) {
    return this->activeCamId;
}

s32 Play_ChangeCameraStatus(PlayState* this, s16 camId, s16 status) {
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;

    if (status == CAM_STATUS_ACTIVE) {
        this->activeCamId = camIdx;
    }

    return Camera_ChangeStatus(this->cameraPtrs[camIdx], status);
}

void Play_ClearCamera(PlayState* this, s16 camId) {
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;

    if (this->cameraPtrs[camIdx] != NULL) {
        Camera_ChangeStatus(this->cameraPtrs[camIdx], CAM_STATUS_INACTIVE);
        this->cameraPtrs[camIdx] = NULL;
    }
}

void Play_ClearAllSubCameras(PlayState* this) {
    s16 subCamId;

    for (subCamId = CAM_ID_SUB_FIRST; subCamId < NUM_CAMS; subCamId++) {
        if (this->cameraPtrs[subCamId] != NULL) {
            Play_ClearCamera(this, subCamId);
        }
    }

    this->activeCamId = CAM_ID_MAIN;
}

Camera* Play_GetCamera(PlayState* this, s16 camId) {
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;

    return this->cameraPtrs[camIdx];
}

/**
 * @return bit-packed success if each of the params were applied
 */
s32 Play_SetCameraAtEye(PlayState* this, s16 camId, Vec3f* at, Vec3f* eye) {
    s32 successfullySet = 0;
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;
    Camera* camera = this->cameraPtrs[camIdx];

    successfullySet |= Camera_SetViewParam(camera, CAM_VIEW_AT, at);
    successfullySet <<= 1;
    successfullySet |= Camera_SetViewParam(camera, CAM_VIEW_EYE, eye);

    camera->dist = Math3D_Distance(at, eye);

    if (camera->focalActor != NULL) {
        camera->focalActorAtOffset.x = at->x - camera->focalActor->world.pos.x;
        camera->focalActorAtOffset.y = at->y - camera->focalActor->world.pos.y;
        camera->focalActorAtOffset.z = at->z - camera->focalActor->world.pos.z;
    } else {
        camera->focalActorAtOffset.x = camera->focalActorAtOffset.y = camera->focalActorAtOffset.z = 0.0f;
    }

    camera->atLerpStepScale = 0.01f;

    return successfullySet;
}

/**
 * @return bit-packed success if each of the params were applied
 */
s32 Play_SetCameraAtEyeUp(PlayState* this, s16 camId, Vec3f* at, Vec3f* eye, Vec3f* up) {
    s32 successfullySet = 0;
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;
    Camera* camera = this->cameraPtrs[camIdx];

    successfullySet |= Camera_SetViewParam(camera, CAM_VIEW_AT, at);
    successfullySet <<= 1;
    successfullySet |= Camera_SetViewParam(camera, CAM_VIEW_EYE, eye);
    successfullySet <<= 1;
    successfullySet |= Camera_SetViewParam(camera, CAM_VIEW_UP, up);

    camera->dist = Math3D_Distance(at, eye);

    if (camera->focalActor != NULL) {
        camera->focalActorAtOffset.x = at->x - camera->focalActor->world.pos.x;
        camera->focalActorAtOffset.y = at->y - camera->focalActor->world.pos.y;
        camera->focalActorAtOffset.z = at->z - camera->focalActor->world.pos.z;
    } else {
        camera->focalActorAtOffset.x = camera->focalActorAtOffset.y = camera->focalActorAtOffset.z = 0.0f;
    }

    camera->atLerpStepScale = 0.01f;

    return successfullySet;
}

/**
 * @return true if the fov was successfully set
 */
s32 Play_SetCameraFov(PlayState* this, s16 camId, f32 fov) {
    s32 successfullySet = Camera_SetViewParam(this->cameraPtrs[camId], CAM_VIEW_FOV, &fov) & 1;

    if (1) {}
    return successfullySet;
}

s32 Play_SetCameraRoll(PlayState* this, s16 camId, s16 roll) {
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;
    Camera* camera = this->cameraPtrs[camIdx];

    camera->roll = roll;

    return 1;
}

void Play_CopyCamera(PlayState* this, s16 destCamId, s16 srcCamId) {
    s16 srcCamId2 = (srcCamId == CAM_ID_NONE) ? this->activeCamId : srcCamId;
    s16 destCamId1 = (destCamId == CAM_ID_NONE) ? this->activeCamId : destCamId;

    Camera_Copy(this->cameraPtrs[destCamId1], this->cameraPtrs[srcCamId2]);
}

// Same as Play_ChangeCameraSetting but also calls Camera_InitFocalActorSettings
s32 func_80169A50(PlayState* this, s16 camId, Player* player, s16 setting) {
    Camera* camera;
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;

    camera = this->cameraPtrs[camIdx];
    Camera_InitFocalActorSettings(camera, &player->actor);
    return Camera_ChangeSetting(camera, setting);
}

s32 Play_ChangeCameraSetting(PlayState* this, s16 camId, s16 setting) {
    return Camera_ChangeSetting(Play_GetCamera(this, camId), setting);
}

// Related to bosses and fishing
void func_80169AFC(PlayState* this, s16 camId, s16 timer) {
    s16 camIdx = (camId == CAM_ID_NONE) ? this->activeCamId : camId;
    s16 i;

    Play_ClearCamera(this, camIdx);

    for (i = CAM_ID_SUB_FIRST; i < NUM_CAMS; i++) {
        if (this->cameraPtrs[i] != NULL) {
            Play_ClearCamera(this, i);
        }
    }

    if (timer <= 0) {
        Play_ChangeCameraStatus(this, CAM_ID_MAIN, CAM_STATUS_ACTIVE);
        this->cameraPtrs[CAM_ID_MAIN]->childCamId = this->cameraPtrs[CAM_ID_MAIN]->doorTimer2 = 0;
    }
}

s16 Play_GetCameraUID(PlayState* this, s16 camId) {
    Camera* camera = this->cameraPtrs[camId];

    if (camera != NULL) {
        return camera->uid;
    } else {
        return -1;
    }
}

// Unused in both MM and OoT, purpose is very unclear
s16 func_80169BF8(PlayState* this, s16 camId, s16 uid) {
    Camera* camera = this->cameraPtrs[camId];

    if (camera != NULL) {
        return 0;
    } else if (camera->uid != uid) {
        return 0;
    } else if (camera->status != CAM_STATUS_ACTIVE) {
        return 2;
    } else {
        return 1;
    }
}

u16 Play_GetActorCsCamSetting(PlayState* this, s32 csCamDataIndex) {
    ActorCsCamInfo* actorCsCamList = &this->actorCsCamList[csCamDataIndex];

    return actorCsCamList->setting;
}

Vec3s* Play_GetActorCsCamFuncData(PlayState* this, s32 csCamDataIndex) {
    ActorCsCamInfo* actorCsCamList = &this->actorCsCamList[csCamDataIndex];

    return Lib_SegmentedToVirtual(actorCsCamList->actorCsCamFuncData);
}

/**
 * Converts the number of a scene to its "original" equivalent, the default version of the area which the player first
 * enters.
 */
s16 Play_GetOriginalSceneId(s16 sceneId) {
    // Inverted Stone Tower Temple -> Stone Tower Temple
    if (sceneId == SCENE_INISIE_R) {
        return SCENE_INISIE_N;
    }

    // Purified Southern Swamp -> Poisoned Sothern Swamp
    if (sceneId == SCENE_20SICHITAI2) {
        return SCENE_20SICHITAI;
    }

    // Spring Mountain Village -> Winter Mountain Village
    if (sceneId == SCENE_10YUKIYAMANOMURA2) {
        return SCENE_10YUKIYAMANOMURA;
    }

    // Spring Goron Village -> Winter Goron Village
    if (sceneId == SCENE_11GORONNOSATO2) {
        return SCENE_11GORONNOSATO;
    }

    // Spring Path to Goron Village -> Winter Path to Goron Village
    if (sceneId == SCENE_17SETUGEN2) {
        return SCENE_17SETUGEN;
    }

    // Inverted Stone Tower -> Stone Tower
    if (sceneId == SCENE_F41) {
        return SCENE_F40;
    }

    return sceneId;
}

/**
 * Copies the flags set in ActorContext over to the current scene's CycleSceneFlags, usually using the original scene
 * number. Exception for Inverted Stone Tower Temple, which uses its own.
 */
void Play_SaveCycleSceneFlags(GameState* thisx) {
    PlayState* this = (PlayState*)thisx;
    CycleSceneFlags* cycleSceneFlags;

    cycleSceneFlags = &gSaveContext.cycleSceneFlags[Play_GetOriginalSceneId(this->sceneId)];
    cycleSceneFlags->chest = this->actorCtx.sceneFlags.chest;
    cycleSceneFlags->switch0 = this->actorCtx.sceneFlags.switches[0];
    cycleSceneFlags->switch1 = this->actorCtx.sceneFlags.switches[1];

    if (this->sceneId == SCENE_INISIE_R) { // Inverted Stone Tower Temple
        cycleSceneFlags = &gSaveContext.cycleSceneFlags[this->sceneId];
    }

    cycleSceneFlags->collectible = this->actorCtx.sceneFlags.collectible[0];
    cycleSceneFlags->clearedRoom = this->actorCtx.sceneFlags.clearedRoom;
}

void Play_SetRespawnData(GameState* thisx, s32 respawnMode, u16 entrance, s32 roomIndex, s32 playerParams, Vec3f* pos,
                         s16 yaw) {
    PlayState* this = (PlayState*)thisx;

    gSaveContext.respawn[respawnMode].entrance = Entrance_Create(entrance >> 9, 0, entrance & 0xF);
    gSaveContext.respawn[respawnMode].roomIndex = roomIndex;
    gSaveContext.respawn[respawnMode].pos = *pos;
    gSaveContext.respawn[respawnMode].yaw = yaw;
    gSaveContext.respawn[respawnMode].playerParams = playerParams;
    gSaveContext.respawn[respawnMode].tempSwitchFlags = this->actorCtx.sceneFlags.switches[2];
    gSaveContext.respawn[respawnMode].unk_18 = this->actorCtx.sceneFlags.collectible[1];
    gSaveContext.respawn[respawnMode].tempCollectFlags = this->actorCtx.sceneFlags.collectible[2];
}

void Play_SetupRespawnPoint(GameState* thisx, s32 respawnMode, s32 playerParams) {
    PlayState* this = (PlayState*)thisx;
    Player* player = GET_PLAYER(this);

    if (this->sceneId != SCENE_KAKUSIANA) { // Grottos
        Play_SetRespawnData(&this->state, respawnMode, ((void)0, gSaveContext.save.entrance), this->roomCtx.curRoom.num,
                            playerParams, &player->actor.world.pos, player->actor.shape.rot.y);
    }
}

// Override respawn data in Sakon's Hideout
void func_80169ECC(PlayState* this) {
    if (this->sceneId == SCENE_SECOM) {
        this->nextEntrance = ENTRANCE(IKANA_CANYON, 6);
        gSaveContext.respawnFlag = -7;
    }
}

// Gameplay_TriggerVoidOut ?
// Used by Player, Ikana_Rotaryroom, Bji01, Kakasi, LiftNuts, Test4, Warptag, WarpUzu, Roomtimer
void func_80169EFC(GameState* thisx) {
    PlayState* this = (PlayState*)thisx;

    gSaveContext.respawn[RESPAWN_MODE_DOWN].tempSwitchFlags = this->actorCtx.sceneFlags.switches[2];
    gSaveContext.respawn[RESPAWN_MODE_DOWN].unk_18 = this->actorCtx.sceneFlags.collectible[1];
    gSaveContext.respawn[RESPAWN_MODE_DOWN].tempCollectFlags = this->actorCtx.sceneFlags.collectible[2];
    this->nextEntrance = gSaveContext.respawn[RESPAWN_MODE_DOWN].entrance;
    gSaveContext.respawnFlag = 1;
    func_80169ECC(this);
    this->transitionTrigger = TRANS_TRIGGER_START;
    this->transitionType = TRANS_TYPE_FADE_BLACK;
}

// Gameplay_LoadToLastEntrance ?
// Used by game_over and Test7
void func_80169F78(GameState* thisx) {
    PlayState* this = (PlayState*)thisx;

    this->nextEntrance = gSaveContext.respawn[RESPAWN_MODE_TOP].entrance;
    gSaveContext.respawnFlag = -1;
    func_80169ECC(this);
    this->transitionTrigger = TRANS_TRIGGER_START;
    this->transitionType = TRANS_TYPE_FADE_BLACK;
}

// Gameplay_TriggerRespawn ?
// Used for void by Wallmaster, Deku Shrine doors. Also used by Player, Kaleido, DoorWarp1
void func_80169FDC(GameState* thisx) {
    func_80169F78(thisx);
}

s32 Play_CamIsNotFixed(GameState* thisx) {
    PlayState* this = (PlayState*)thisx;

    return this->roomCtx.curRoom.roomShape->base.type != ROOM_SHAPE_TYPE_IMAGE;
}

s32 FrameAdvance_IsEnabled(GameState* thisx) {
    PlayState* this = (PlayState*)thisx;

    return this->frameAdvCtx.enabled != 0;
}

// Unused, unchanged from OoT, which uses it only in one Camera function.
/**
 * @brief Tests if \p actor is a door and the sides are different rooms.
 *
 * @param[in] thisx GameState, promoted to play inside.
 * @param[in] actor Actor to test.
 * @param[out] yaw Facing angle of the actor, or reverse if in the back room.
 * @return true if \p actor is a door and the sides are in different rooms, false otherwise
 */
s32 func_8016A02C(GameState* thisx, Actor* actor, s16* yaw) {
    PlayState* this = (PlayState*)thisx;
    TransitionActorEntry* transitionActor;
    s8 frontRoom;

    if (actor->category != ACTORCAT_DOOR) {
        return false;
    }

    transitionActor = &this->doorCtx.transitionActorList[(u16)actor->params >> 10];
    frontRoom = transitionActor->sides[0].room;
    if (frontRoom == transitionActor->sides[1].room) {
        return false;
    }

    if (frontRoom == actor->room) {
        *yaw = actor->shape.rot.y;
    } else {
        *yaw = actor->shape.rot.y + 0x8000;
    }

    return true;
}

// Unused
/**
 * @brief Tests if \p pos is underwater.
 *
 * @param[in] this PlayState
 * @param[in] pos position to test
 * @return true if inside a waterbox and not above a void.
 */
s32 Play_IsUnderwater(PlayState* this, Vec3f* pos) {
    WaterBox* waterBox;
    CollisionPoly* poly;
    Vec3f waterSurfacePos;
    s32 bgId;

    waterSurfacePos = *pos;

    if ((WaterBox_GetSurface1(this, &this->colCtx, waterSurfacePos.x, waterSurfacePos.z, &waterSurfacePos.y,
                              &waterBox) == true) &&
        (pos->y < waterSurfacePos.y) &&
        (BgCheck_EntityRaycastFloor3(&this->colCtx, &poly, &bgId, &waterSurfacePos) != BGCHECK_Y_MIN)) {
        return true;
    } else {
        return false;
    }
}

s32 Play_IsDebugCamEnabled(void) {
    return gDbgCamEnabled;
}

// A mapping from playerCsIds to sGlobalCamDataSettings indices.
s16 sPlayerCsIdToCsCamId[] = {
    CS_CAM_ID_GLOBAL_ITEM_OCARINA,        // PLAYER_CS_ID_ITEM_OCARINA
    CS_CAM_ID_GLOBAL_ITEM_GET,            // PLAYER_CS_ID_ITEM_GET
    CS_CAM_ID_GLOBAL_ITEM_BOTTLE,         // PLAYER_CS_ID_ITEM_BOTTLE
    CS_CAM_ID_GLOBAL_ITEM_SHOW,           // PLAYER_CS_ID_ITEM_SHOW
    CS_CAM_ID_GLOBAL_WARP_PAD_MOON,       // PLAYER_CS_ID_WARP_PAD_MOON
    CS_CAM_ID_GLOBAL_MASK_TRANSFORMATION, // PLAYER_CS_ID_MASK_TRANSFORMATION
    CS_CAM_ID_GLOBAL_DEATH,               // PLAYER_CS_ID_DEATH
    CS_CAM_ID_GLOBAL_REVIVE,              // PLAYER_CS_ID_REVIVE
    CS_CAM_ID_GLOBAL_SONG_WARP,           // PLAYER_CS_ID_SONG_WARP
    CS_CAM_ID_GLOBAL_WARP_PAD_ENTRANCE,   // PLAYER_CS_ID_WARP_PAD_ENTRANCE
};

// Used by Player
/**
 * Extract the common cutscene ids used by Player from the scene and set the cutscene ids in this->playerCsIds.
 * If a playerCsId is not present in the scene, then that particular id is set to CS_ID_NONE.
 * Otherwise, if there is an ActorCutscene where csCamId matches the appropriate element of sPlayerCsIdToCsCamId,
 * set the corresponding playerActorCsId (and possibly change its priority for the zeroth one).
 */
void Play_AssignPlayerCsIdsFromScene(GameState* thisx, s32 spawnCsId) {
    PlayState* this = (PlayState*)thisx;
    s32 i;
    s16* curPlayerCsId = this->playerCsIds;
    s16* csCamId = sPlayerCsIdToCsCamId;

    for (i = 0; i < ARRAY_COUNT(this->playerCsIds); i++, curPlayerCsId++, csCamId++) {
        ActorCutscene* csEntry;
        s32 curCsId;

        *curPlayerCsId = CS_ID_NONE;

        for (curCsId = spawnCsId; curCsId != CS_ID_NONE; curCsId = csEntry->additionalCsId) {
            csEntry = CutsceneManager_GetCutsceneEntry(curCsId);

            if (csEntry->csCamId == *csCamId) {
                if ((csEntry->csCamId == CS_CAM_ID_GLOBAL_ITEM_OCARINA) && (csEntry->priority == 700)) {
                    csEntry->priority = 550;
                }
                *curPlayerCsId = curCsId;
                break;
            }
        }
    }
}

// Set values to fill screen
void Play_FillScreen(GameState* thisx, s16 fillScreenOn, u8 red, u8 green, u8 blue, u8 alpha) {
    R_PLAY_FILL_SCREEN_ON = fillScreenOn;
    R_PLAY_FILL_SCREEN_R = red;
    R_PLAY_FILL_SCREEN_G = green;
    R_PLAY_FILL_SCREEN_B = blue;
    R_PLAY_FILL_SCREEN_ALPHA = alpha;
}

void Play_Init(GameState* thisx) {
    PlayState* this = (PlayState*)thisx;
    GraphicsContext* gfxCtx = this->state.gfxCtx;
    s32 pad;
    uintptr_t zAlloc;
    s32 zAllocSize;
    Player* player;
    s32 i;
    s32 spawn;
    u8 sceneLayer;
    s32 scene;

    if ((gSaveContext.respawnFlag == -4) || (gSaveContext.respawnFlag == -0x63)) {
        if (CHECK_EVENTINF(EVENTINF_TRIGGER_DAYTELOP)) {
            CLEAR_EVENTINF(EVENTINF_TRIGGER_DAYTELOP);
            STOP_GAMESTATE(&this->state);
            SET_NEXT_GAMESTATE(&this->state, DayTelop_Init, sizeof(DayTelopState));
            return;
        }

        gSaveContext.unk_3CA7 = 1;
        if (gSaveContext.respawnFlag == -0x63) {
            gSaveContext.respawnFlag = 2;
        }
    } else {
        gSaveContext.unk_3CA7 = 0;
    }

    if (gSaveContext.save.entrance == -1) {
        gSaveContext.save.entrance = 0;
        STOP_GAMESTATE(&this->state);
        SET_NEXT_GAMESTATE(&this->state, TitleSetup_Init, sizeof(TitleSetupState));
        return;
    }

    if ((gSaveContext.nextCutsceneIndex == 0xFFEF) || (gSaveContext.nextCutsceneIndex == 0xFFF0)) {
        scene = ((void)0, gSaveContext.save.entrance) >> 9;
        spawn = (((void)0, gSaveContext.save.entrance) >> 4) & 0x1F;

        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_SNOWHEAD_TEMPLE)) {
            if (scene == ENTR_SCENE_MOUNTAIN_VILLAGE_WINTER) {
                scene = ENTR_SCENE_MOUNTAIN_VILLAGE_SPRING;
            } else if (scene == ENTR_SCENE_GORON_VILLAGE_WINTER) {
                scene = ENTR_SCENE_GORON_VILLAGE_SPRING;
            } else if (scene == ENTR_SCENE_PATH_TO_GORON_VILLAGE_WINTER) {
                scene = ENTR_SCENE_PATH_TO_GORON_VILLAGE_SPRING;
            } else if ((scene == ENTR_SCENE_SNOWHEAD) || (scene == ENTR_SCENE_PATH_TO_SNOWHEAD) ||
                       (scene == ENTR_SCENE_PATH_TO_MOUNTAIN_VILLAGE) || (scene == ENTR_SCENE_GORON_SHRINE) ||
                       (scene == ENTR_SCENE_GORON_RACETRACK)) {
                gSaveContext.nextCutsceneIndex = 0xFFF0;
            }
        }

        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_WOODFALL_TEMPLE)) {
            if (scene == ENTR_SCENE_SOUTHERN_SWAMP_POISONED) {
                scene = ENTR_SCENE_SOUTHERN_SWAMP_CLEARED;
            } else if (scene == ENTR_SCENE_WOODFALL) {
                gSaveContext.nextCutsceneIndex = 0xFFF1;
            }
        }

        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_STONE_TOWER_TEMPLE) && (scene == ENTR_SCENE_IKANA_CANYON)) {
            gSaveContext.nextCutsceneIndex = 0xFFF2;
        }

        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_GREAT_BAY_TEMPLE) &&
            ((scene == ENTR_SCENE_GREAT_BAY_COAST) || (scene == ENTR_SCENE_ZORA_CAPE))) {
            gSaveContext.nextCutsceneIndex = 0xFFF0;
        }

        // "First cycle" Termina Field
        if (INV_CONTENT(ITEM_OCARINA_OF_TIME) != ITEM_OCARINA_OF_TIME) {
            if ((scene == ENTR_SCENE_TERMINA_FIELD) &&
                (((void)0, gSaveContext.save.entrance) != ENTRANCE(TERMINA_FIELD, 10))) {
                gSaveContext.nextCutsceneIndex = 0xFFF4;
            }
        }
        //! FAKE:
        gSaveContext.save.entrance =
            Entrance_Create(((void)0, scene), spawn, ((void)0, gSaveContext.save.entrance) & 0xF);
    }

    GameState_Realloc(&this->state, 0);
    KaleidoManager_Init(this);
    ShrinkWindow_Init();
    View_Init(&this->view, gfxCtx);
    func_801A3EC0(0);
    Quake_Init();
    Distortion_Init(this);

    for (i = 0; i < ARRAY_COUNT(this->cameraPtrs); i++) {
        this->cameraPtrs[i] = NULL;
    }

    Camera_Init(&this->mainCamera, &this->view, &this->colCtx, this);
    Camera_ChangeStatus(&this->mainCamera, CAM_STATUS_ACTIVE);

    for (i = 0; i < ARRAY_COUNT(this->subCameras); i++) {
        Camera_Init(&this->subCameras[i], &this->view, &this->colCtx, this);
        Camera_ChangeStatus(&this->subCameras[i], CAM_STATUS_INACTIVE);
    }

    this->cameraPtrs[CAM_ID_MAIN] = &this->mainCamera;
    this->cameraPtrs[CAM_ID_MAIN]->uid = CAM_ID_MAIN;
    this->activeCamId = CAM_ID_MAIN;

    Camera_OverwriteStateFlags(&this->mainCamera, CAM_STATE_0 | CAM_STATE_CHECK_WATER | CAM_STATE_2 | CAM_STATE_3 |
                                                      CAM_STATE_4 | CAM_STATE_DISABLE_MODE_CHANGE | CAM_STATE_6);
    Sram_Alloc(&this->state, &this->sramCtx);
    Regs_InitData(this);
    Message_Init(this);
    GameOver_Init(this);
    SoundSource_InitAll(this);
    EffFootmark_Init(this);
    Effect_Init(this);
    EffectSS_Init(this, 100);
    CollisionCheck_InitContext(this, &this->colChkCtx);
    AnimationContext_Reset(&this->animationCtx);
    Cutscene_InitContext(this, &this->csCtx);

    if (gSaveContext.nextCutsceneIndex != 0xFFEF) {
        gSaveContext.save.cutsceneIndex = gSaveContext.nextCutsceneIndex;
        gSaveContext.nextCutsceneIndex = 0xFFEF;
    }

    if (gSaveContext.save.cutsceneIndex == 0xFFFD) {
        gSaveContext.save.cutsceneIndex = 0;
    }

    if (gSaveContext.nextDayTime != NEXT_TIME_NONE) {
        gSaveContext.save.time = gSaveContext.nextDayTime;
        gSaveContext.skyboxTime = gSaveContext.nextDayTime;
    }

    if ((gSaveContext.save.time >= CLOCK_TIME(18, 0)) || (gSaveContext.save.time < CLOCK_TIME(6, 30))) {
        gSaveContext.save.isNight = true;
    } else {
        gSaveContext.save.isNight = false;
    }

    func_800EDDB0(this);

    if (((gSaveContext.gameMode != GAMEMODE_NORMAL) && (gSaveContext.gameMode != GAMEMODE_TITLE_SCREEN)) ||
        (gSaveContext.save.cutsceneIndex >= 0xFFF0)) {
        gSaveContext.nayrusLoveTimer = 0;
        Magic_Reset(this);
        gSaveContext.sceneLayer = (gSaveContext.save.cutsceneIndex & 0xF) + 1;

        // Set saved cutscene to 0 so it doesn't immediately play, but instead let the `CutsceneManager` handle it.
        gSaveContext.save.cutsceneIndex = 0;
    } else {
        gSaveContext.sceneLayer = 0;
    }

    sceneLayer = gSaveContext.sceneLayer;

    Play_SpawnScene(
        this, Entrance_GetSceneIdAbsolute(((void)0, gSaveContext.save.entrance) + ((void)0, gSaveContext.sceneLayer)),
        Entrance_GetSpawnNum(((void)0, gSaveContext.save.entrance) + ((void)0, gSaveContext.sceneLayer)));
    KaleidoScopeCall_Init(this);
    Interface_Init(this);

    if (gSaveContext.nextDayTime != NEXT_TIME_NONE) {
        if (gSaveContext.nextDayTime == NEXT_TIME_DAY) {
            gSaveContext.save.day++;
            gSaveContext.save.eventDayCount++;
            gSaveContext.dogIsLost = true;
            gSaveContext.nextDayTime = NEXT_TIME_DAY_SET;
        } else {
            gSaveContext.nextDayTime = NEXT_TIME_NIGHT_SET;
        }
    }

    Play_InitMotionBlur();

    R_PAUSE_BG_PRERENDER_STATE = PAUSE_BG_PRERENDER_OFF;
    R_PICTO_PHOTO_STATE = PICTO_PHOTO_STATE_OFF;

    PreRender_Init(&this->pauseBgPreRender);
    PreRender_SetValuesSave(&this->pauseBgPreRender, gCfbWidth, gCfbHeight, NULL, NULL, NULL);
    PreRender_SetValues(&this->pauseBgPreRender, gCfbWidth, gCfbHeight, NULL, NULL);

    this->unk_18E64 = gWorkBuffer;
    this->pictoPhotoI8 = gPictoPhotoI8;
    this->unk_18E68 = D_80784600;
    this->unk_18E58 = D_80784600;
    this->unk_18E60 = D_80784600;
    gTransitionTileState = TRANS_TILE_OFF;
    this->transitionMode = TRANS_MODE_OFF;
    D_801D0D54 = false;

    FrameAdvance_Init(&this->frameAdvCtx);
    Rand_Seed(osGetTime());
    Matrix_Init(&this->state);

    this->state.main = Play_Main;
    this->state.destroy = Play_Destroy;

    this->transitionTrigger = TRANS_TRIGGER_END;
    this->worldCoverAlpha = 0;
    this->bgCoverAlpha = 0;
    this->haltAllActors = false;
    this->unk_18844 = false;

    if (gSaveContext.gameMode != GAMEMODE_TITLE_SCREEN) {
        if (gSaveContext.nextTransitionType == TRANS_NEXT_TYPE_DEFAULT) {
            this->transitionType =
                (Entrance_GetTransitionFlags(((void)0, gSaveContext.save.entrance) + sceneLayer) >> 7) & 0x7F;
        } else {
            this->transitionType = gSaveContext.nextTransitionType;
            gSaveContext.nextTransitionType = TRANS_NEXT_TYPE_DEFAULT;
        }
    } else {
        this->transitionType = TRANS_TYPE_FADE_BLACK;
    }

    TransitionFade_Init(&this->unk_18E48);
    TransitionFade_SetType(&this->unk_18E48, 3);
    TransitionFade_SetColor(&this->unk_18E48, RGBA8(160, 160, 160, 255));
    TransitionFade_Start(&this->unk_18E48);
    VisMono_Init(&sPlayVisMono);

    gVisMonoColor.a = 0;
    D_801F6D4C = &D_801F6D38;
    func_80140E80(D_801F6D4C);
    D_801F6D4C->lodProportion = 0.0f;
    D_801F6D4C->mode = 1;
    D_801F6D4C->primColor.r = 0;
    D_801F6D4C->primColor.g = 0;
    D_801F6D4C->primColor.b = 0;
    D_801F6D4C->primColor.a = 0;
    D_801F6D4C->envColor.r = 0;
    D_801F6D4C->envColor.g = 0;
    D_801F6D4C->envColor.b = 0;
    D_801F6D4C->envColor.a = 0;
    CutsceneFlags_UnsetAll(this);
    THA_GetRemaining(&this->state.tha);
    zAllocSize = THA_GetRemaining(&this->state.tha);
    zAlloc = (uintptr_t)THA_AllocTailAlign16(&this->state.tha, zAllocSize);
    ZeldaArena_Init(((zAlloc + 8) & ~0xF), (zAllocSize - ((zAlloc + 8) & ~0xF)) + zAlloc); //! @bug: Incorrect ALIGN16s
    Actor_InitContext(this, &this->actorCtx, this->linkActorEntry);

    while (!Room_HandleLoadCallbacks(this, &this->roomCtx)) {}

    if ((CURRENT_DAY != 0) && ((this->roomCtx.curRoom.behaviorType1 == ROOM_BEHAVIOR_TYPE1_1) ||
                               (this->roomCtx.curRoom.behaviorType1 == ROOM_BEHAVIOR_TYPE1_5))) {
        Actor_Spawn(&this->actorCtx, this, ACTOR_EN_TEST4, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0);
    }

    player = GET_PLAYER(this);

    Camera_InitFocalActorSettings(&this->mainCamera, &player->actor);
    gDbgCamEnabled = false;

    if (PLAYER_GET_BG_CAM_INDEX(&player->actor) != 0xFF) {
        Camera_ChangeActorCsCamIndex(&this->mainCamera, PLAYER_GET_BG_CAM_INDEX(&player->actor));
    }

    CutsceneManager_StoreCamera(&this->mainCamera);
    Interface_SetSceneRestrictions(this);
    Environment_PlaySceneSequence(this);
    gSaveContext.seqId = this->sequenceCtx.seqId;
    gSaveContext.ambienceId = this->sequenceCtx.ambienceId;
    AnimationContext_Update(this, &this->animationCtx);
    Cutscene_HandleEntranceTriggers(this);
    gSaveContext.respawnFlag = 0;
    sBombersNotebookOpen = false;
    BombersNotebook_Init(&sBombersNotebook);
}
