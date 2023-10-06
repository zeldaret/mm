/*
 * File: z_en_weather_tag.c
 * Overlay: ovl_En_Weather_Tag
 * Description: Local weather changes
 */

#include "z_en_weather_tag.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnWeatherTag*)thisx)

void EnWeatherTag_Init(Actor* thisx, PlayState* play);
void EnWeatherTag_Destroy(Actor* thisx, PlayState* play);
void EnWeatherTag_Update(Actor* thisx, PlayState* play);
void EnWeatherTag_Draw(Actor* thisx, PlayState* play);

void func_80966A08(EnWeatherTag* this, PlayState* play);
void func_80966A68(EnWeatherTag* this, PlayState* play);
void EnWeatherTag_Die(EnWeatherTag* this, PlayState* play);
void func_80966B08(EnWeatherTag* this, PlayState* play);
void func_80966BF4(EnWeatherTag* this, PlayState* play);
void func_80966D20(EnWeatherTag* this, PlayState* play);
void func_80966E0C(EnWeatherTag* this, PlayState* play);
void func_80966E84(EnWeatherTag* this, PlayState* play);
void func_80966EF0(EnWeatherTag* this, PlayState* play);
void func_80966F74(EnWeatherTag* this, PlayState* play);
void func_80966FEC(EnWeatherTag* this, PlayState* play);
void func_80967060(EnWeatherTag* this, PlayState* play);
void func_80967148(EnWeatherTag* this, PlayState* play);
void EnWeatherTag_DoNothing(EnWeatherTag* this, PlayState* play);
void EnWeatherTag_Unused_80967250(EnWeatherTag* this, PlayState* play);
void EnWeatherTag_Unused_809671B8(EnWeatherTag* this, PlayState* play);
void func_809672DC(EnWeatherTag* this, PlayState* play);
void func_809674C8(EnWeatherTag* this, PlayState* play);
void func_80967608(EnWeatherTag* this, PlayState* play);

ActorInit En_Weather_Tag_InitVars = {
    ACTOR_EN_WEATHER_TAG,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnWeatherTag),
    (ActorFunc)EnWeatherTag_Init,
    (ActorFunc)EnWeatherTag_Destroy,
    (ActorFunc)EnWeatherTag_Update,
    (ActorFunc)EnWeatherTag_Draw,
};

void EnWeatherTag_SetupAction(EnWeatherTag* this, EnWeatherTagActionFunc func) {
    this->actionFunc = func;
}

void EnWeatherTag_Destroy(Actor* thisx, PlayState* play) {
}

void EnWeatherTag_Init(Actor* thisx, PlayState* play) {
    EnWeatherTag* this = THIS;
    s32 pad;
    Path* path;
    s32 pathID;

    // flag: is targetable. Should do nothing as not set by default above
    this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;

    switch (WEATHER_TAG_TYPE(&this->actor)) {
        case WEATHERTAG_TYPE_UNK0:
            this->unk154 = 0;
            this->fadeDistance = this->actor.world.rot.x;
            this->unk158 = this->actor.world.rot.y;
            EnWeatherTag_SetupAction(this, func_80966A08);
            break;

        case WEATHERTAG_TYPE_UNK1:
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_STONE_TOWER_TEMPLE)) {
                Actor_Kill(&this->actor);
            }
            EnWeatherTag_SetupAction(this, func_80966B08);
            break;

        case WEATHERTAG_TYPE_WINTERFOG:
            EnWeatherTag_SetupAction(this, func_80966E0C);
            break;

        case WEATHERTAG_TYPE_UNK3:
            EnWeatherTag_SetupAction(this, func_80966EF0);
            break;

        case WEATHERTAG_TYPE_UNK4:
            EnWeatherTag_SetupAction(this, func_80966FEC);
            break;

        case WEATHERTAG_TYPE_UNK5:
            func_800BC154(play, &play->actorCtx, &this->actor, 7);
            play->skyboxId = SKYBOX_3;
            play->envCtx.lightConfig = 5;
            play->envCtx.changeLightNextConfig = 5;
            D_801F4E74 = 1.0f;
            EnWeatherTag_SetupAction(this, func_80966BF4);
            break;

        case WEATHERTAG_TYPE_WATERMURK:
            pathID = WEATHER_TAG_PATHID(&this->actor);
            path = &play->setupPathList[pathID];
            this->pathPoints = Lib_SegmentedToVirtual(path->points);
            this->pathCount = path->count;
            EnWeatherTag_SetupAction(this, func_809672DC);
            break;

        case WEATHERTAG_TYPE_LOCALDAY2RAIN:
            EnWeatherTag_SetupAction(this, func_809674C8);
            break;

        default:
            break;
    }
}

// matches but unused params is suspicious
// called WeatherTag_CheckEnableWeatherEffect in OOT, that's where "weatherMode" came from
u8 func_80966608(EnWeatherTag* this, PlayState* play, UNK_TYPE a3, UNK_TYPE a4, u8 lightConfig,
                 u8 changeLightNextConfig, u16 changeDuration, u8 weatherMode) {
    Player* player = GET_PLAYER(play);
    u8 returnVal = 0;

    if (WEATHER_TAG_RANGE100(&this->actor) > Actor_WorldDistXZToActor(&player->actor, &this->actor)) {
        if (play->envCtx.lightConfig == play->envCtx.changeLightNextConfig) {
            gInterruptSongOfStorms = true;
            if (!(play->envCtx.lightMode == LIGHT_MODE_TIME) ||
                ((play->envCtx.lightConfig != 1) && !play->envCtx.changeLightEnabled)) {

                gInterruptSongOfStorms = false;
                if (gWeatherMode != weatherMode) {
                    gWeatherMode = weatherMode;
                    play->envCtx.changeLightEnabled = true;
                    play->envCtx.lightConfig = lightConfig;
                    play->envCtx.changeLightNextConfig = changeLightNextConfig;
                    gLightConfigAfterUnderwater = changeLightNextConfig;
                    play->envCtx.changeDuration = changeDuration;
                    play->envCtx.changeLightTimer = play->envCtx.changeDuration;
                }
                returnVal = 1;
            }
        }
    }
    return returnVal;
}

// again with the unused parameters
// called WeatherTag_CheckRestoreWeather in OOT
u8 func_80966758(EnWeatherTag* this, PlayState* play, UNK_TYPE a3, UNK_TYPE a4, u8 lightConfig,
                 u8 changeLightNextConfig, u16 changeDuration) {
    Player* player = GET_PLAYER(play);
    u8 returnVal = 0;

    if (WEATHER_TAG_RANGE100(&this->actor) < Actor_WorldDistXZToActor(&player->actor, &this->actor)) {
        if (play->envCtx.lightConfig == play->envCtx.changeLightNextConfig) {
            gInterruptSongOfStorms = true;
            if (!(play->envCtx.lightMode == LIGHT_MODE_TIME) ||
                ((play->envCtx.lightConfig != 1) && !play->envCtx.changeLightEnabled)) {

                gInterruptSongOfStorms = false;
                gWeatherMode = WEATHER_MODE_CLEAR;
                play->envCtx.changeLightEnabled = true;
                play->envCtx.lightConfig = lightConfig;
                play->envCtx.changeLightNextConfig = changeLightNextConfig;
                gLightConfigAfterUnderwater = changeLightNextConfig;
                play->envCtx.changeDuration = changeDuration;
                play->envCtx.changeLightTimer = play->envCtx.changeDuration;
                returnVal = 1;
            }
        }
    }
    return returnVal;
}

// modify wind?
void func_8096689C(EnWeatherTag* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 distance;
    f32 partialResult;

    distance = Actor_WorldDistXZToActor(&player->actor, &this->actor);
    if (this->fadeDistance < distance) {
        distance = this->fadeDistance;
    }

    if (this->fadeDistance == 0) {
        this->fadeDistance = 1; // div by zero protection
    }

    // this separation is to match, can't be separate temps without regalloc
    partialResult = (1.0f - (distance / this->fadeDistance));  // strength based on distance?
    partialResult = (this->unk154 / 32768.0f) * partialResult; // another scale applied

    play->envCtx.windSpeed = (this->actor.world.rot.z * partialResult) + 30.0f;
    if (partialResult > 0.01f) {
        play->envCtx.sandstormState = SANDSTORM_8;
        D_801F4E30 = 0x9B;
    } else if (play->envCtx.sandstormState == SANDSTORM_8) {
        D_801F4E30 = 0;
        play->envCtx.sandstormState = SANDSTORM_9;
    }
}

// WEATHERTAG_TYPE_UNK0
void func_80966A08(EnWeatherTag* this, PlayState* play) {
    this->unk154 += this->unk158;
    if (this->unk154 > 0x8000) {
        this->unk154 = 0x8000;
        EnWeatherTag_SetupAction(this, func_80966A68);
    }
    func_8096689C(this, play);
}

// WEATHERTAG_TYPE_UNK0 2
void func_80966A68(EnWeatherTag* this, PlayState* play) {
    this->unk154 -= (this->unk158 >> 1);
    if (this->unk154 == 0) {
        this->unk154 = 1;
    }
    if ((s16)this->unk154 < 0) { // cast req
        this->unk154 = 0;
        // redundant code
        Actor_Kill(&this->actor);
        EnWeatherTag_SetupAction(this, EnWeatherTag_Die);
    }
    func_8096689C(this, play);
}

void EnWeatherTag_Die(EnWeatherTag* this, PlayState* play) {
    Actor_Kill(&this->actor);
}

// WEATHERTAG_TYPE_UNK1
// areas that use: all of ikana, swamp, termina field,stonetower temple,
//  poisoned swamp: placed behind the water fall from ikana
// this tag stops spawning after STT cleared?
void func_80966B08(EnWeatherTag* this, PlayState* play) {
    if (func_80966608(this, play, 0, 0, play->envCtx.lightConfig, 5, 100, 2) || (gWeatherMode == WEATHER_MODE_2)) {
        play->skyboxId = SKYBOX_3;
        EnWeatherTag_SetupAction(this, func_80966D20);
    } else if (D_801F4E74 <= 0.01f) {
        play->skyboxId = SKYBOX_NORMAL_SKY;
    } else {
        Math_SmoothStepToF(&D_801F4E74, 0.0f, 0.2f, 0.02f, 0.001f);
    }
}

// WEATHERTAG_TYPE_UNK5: only one in ikana canyon, corner of cliff right outside of stone tower entrance
// because it uses cutsecnes.. is this the clear ikana cutcsene?
void func_80966BF4(EnWeatherTag* this, PlayState* play) {
    u8 changeLightNextConfig;
    CsCmdActorCue* cue;

    if (Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_567)) {
        cue = play->csCtx.actorCues[Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_567)];
        if ((play->csCtx.curFrame >= cue->startFrame) && (cue->id >= 2)) {
            switch (gSaveContext.save.day) {
                case 0:
                case 1:
                default:
                    changeLightNextConfig = 0;
                    break;

                case 2:
                    changeLightNextConfig = 3;
                    break;

                case 3:
                    changeLightNextConfig = 4;
                    break;
            }

            Math_SmoothStepToF(&D_801F4E74, 0.0f, 0.2f, 0.02f, 0.001f);

            if (play->envCtx.changeLightNextConfig != changeLightNextConfig) {
                play->envCtx.changeLightEnabled = true;
                play->envCtx.changeLightNextConfig = changeLightNextConfig;
                play->envCtx.changeDuration = 100;
                play->envCtx.changeLightTimer = play->envCtx.changeDuration;
            }
        }
    }
}

// WEATHERTAG_TYPE_UNK1 2
void func_80966D20(EnWeatherTag* this, PlayState* play) {
    u8 newUnk20;

    switch (gSaveContext.save.day) {
        case 0:
        case 1:
        default:
            newUnk20 = 0;
            break;

        case 2:
            newUnk20 = 3;
            break;

        case 3:
            newUnk20 = 4;
            break;
    }

    Math_SmoothStepToF(&D_801F4E74, 1.0f, 0.2f, 0.02f, 0.001f);
    if (func_80966758(this, play, 1, 0, 5, newUnk20, 100)) {
        EnWeatherTag_SetupAction(this, func_80966B08);
    }

    if (gWeatherMode != WEATHER_MODE_2) {
        EnWeatherTag_SetupAction(this, func_80966B08);
    }
}

// WEATHERTAG_TYPE_WINTERFOG:
// areas affected: winter goron village, path to mountain village,
//   path to goron village winter, winter mountain village
void func_80966E0C(EnWeatherTag* this, PlayState* play) {
    if (func_80966608(this, play, 0, 1, 0, 2, 60, 3)) {
        play->envCtx.precipitation[PRECIP_SNOW_MAX] = 128;
        EnWeatherTag_SetupAction(this, func_80966E84);
    }
}

// WEATHERTAG_TYPE_WINTERFOG 2
void func_80966E84(EnWeatherTag* this, PlayState* play) {
    if (func_80966758(this, play, 1, 0, 2, 0, 60)) {
        play->envCtx.precipitation[PRECIP_SNOW_MAX] = 0;
        EnWeatherTag_SetupAction(this, func_80966E0C);
    }
}

// WEATHERTAG_TYPE_UNK3: unused in vanilla?
//  just a heavy fog like the winter fog, but unused?
// wait if you enter the scene through a room instead of fog you get a flash rain shower
void func_80966EF0(EnWeatherTag* this, PlayState* play) {
    if (func_80966608(this, play, 0, 1, 0, 2, 100, 4)) {
        Environment_PlayStormNatureAmbience(play);
        play->envCtx.precipitation[PRECIP_RAIN_MAX] = 60;
        EnWeatherTag_SetupAction(this, func_80966F74);
    }
}

// WEATHERTAG_TYPE_UNK3 2
void func_80966F74(EnWeatherTag* this, PlayState* play) {
    if (func_80966758(this, play, 1, 0, 2, 0, 100)) {
        Environment_StopStormNatureAmbience(play);
        play->envCtx.precipitation[PRECIP_RAIN_MAX] = 0;
        EnWeatherTag_SetupAction(this, func_80966EF0);
    }
}

// WEATHERTAG_TYPE_UNK4: no visible effect, what does it doooo??
// used in south clock town??? romani ranch, clock tower rooftop woodfall..? stt
// all of them have shorter distances though, like 0xA and 0x6, so their locations are important
void func_80966FEC(EnWeatherTag* this, PlayState* play) {
    // weirdly, not the same as the other param lookup used in the rest of the file, which is float
    s32 distance = WEATHER_TAG_RANGE100INT(&this->actor);
    if (distance > 0) {
        gSkyboxNumStars = distance;
    }

    if ((play->sceneId == SCENE_KAIZOKU) && (play->actorCtx.flags & ACTORCTX_FLAG_1)) {
        EnWeatherTag_SetupAction(this, func_80967060);
    }
}

// type 4_2 pirates fortres only?
void func_80967060(EnWeatherTag* this, PlayState* play) {
    Vec3f worldPos;
    Vec3f screenPos;

    worldPos.x = 1055.0f;
    worldPos.y = -145.0f;
    worldPos.z = 181.0f;

    Play_GetScreenPos(play, &worldPos, &screenPos);

    if (play->view.fovy < 25.0f) {
        if ((screenPos.x >= 70.0f) && (screenPos.x < (SCREEN_WIDTH - 70.0f)) && (screenPos.y >= 30.0f) &&
            (screenPos.y < (SCREEN_HEIGHT - 30.0f))) {
            EnWeatherTag_SetupAction(this, func_80967148);
        }
    }
}

// type 4_3, start cutscene then die?
void func_80967148(EnWeatherTag* this, PlayState* play) {
    s16 csId = this->actor.csId;

    if (CutsceneManager_IsNext(csId)) {
        CutsceneManager_Start(csId, &this->actor);
        EnWeatherTag_SetupAction(this, EnWeatherTag_DoNothing);
    } else {
        CutsceneManager_Queue(csId);
    }
}

void EnWeatherTag_DoNothing(EnWeatherTag* this, PlayState* play) {
}

// these two are isolated, they call themselves but nothing calls them?
void EnWeatherTag_Unused_809671B8(EnWeatherTag* this, PlayState* play) {
    if (func_80966608(this, play, 0, 1, 0, 4, 100, 5)) {
        Environment_PlayStormNatureAmbience(play);
        play->envCtx.lightningState = LIGHTNING_ON;
        play->envCtx.precipitation[PRECIP_RAIN_MAX] = 60;
        EnWeatherTag_SetupAction(this, EnWeatherTag_Unused_80967250);
    }
}

// these two are isolated, they call themselves but nothing calls them
void EnWeatherTag_Unused_80967250(EnWeatherTag* this, PlayState* play) {
    if (func_80966758(this, play, 1, 0, 4, 0, 100)) {
        Environment_StopStormNatureAmbience(play);
        play->envCtx.lightningState = LIGHTNING_LAST;
        play->envCtx.precipitation[PRECIP_RAIN_MAX] = 0;
        EnWeatherTag_SetupAction(this, EnWeatherTag_Unused_809671B8);
    }
}

// WEATHERTAG_TYPE_WATERMURK: (pinnacle rock, zora cape, zora coast)
void func_809672DC(EnWeatherTag* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 pad;
    f32 distance;
    f32 range;
    f32 strength = 0.0f;

    Actor_GetClosestPosOnPath(this->pathPoints, this->pathCount, &GET_PLAYER(play)->actor.world.pos,
                              &this->actor.world.pos, false);

    distance = Actor_WorldDistXZToActor(&player->actor, &this->actor);
    range = WEATHER_TAG_RANGE100(&this->actor);

    if (distance < range) {
        play->envCtx.sandstormState = SANDSTORM_6;
        strength = 1.0f - (distance / range);
        if (0.8f < strength) {
            strength = 1.0f;
        }
        D_801F4E30 = (200.0f * strength);
    } else {
        if (play->envCtx.sandstormState == SANDSTORM_6) {
            D_801F4E30 = 0;
            play->envCtx.sandstormState = SANDSTORM_7;
        }
    }

    Math_SmoothStepToS(&play->envCtx.adjLightSettings.fogNear, -40.0f * strength, 1, 1, 1);
}

// WEATHERTAG_TYPE_LOCALDAY2RAIN: rain proximity as approaching rainy scene
// (milk road day 2 approaching ranch it rains, walking away towards termfield no rain)
void func_809674C8(EnWeatherTag* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (Actor_WorldDistXZToActor(&player->actor, &this->actor) < WEATHER_TAG_RANGE100(&this->actor)) {
        if (CURRENT_DAY == 2) {
            if ((gSaveContext.save.time >= CLOCK_TIME(7, 0)) && (gSaveContext.save.time < CLOCK_TIME(17, 30)) &&
                (play->envCtx.precipitation[PRECIP_SNOW_CUR] == 0)) {

                gWeatherMode = WEATHER_MODE_1;
                Environment_PlayStormNatureAmbience(play);
                play->envCtx.precipitation[PRECIP_SOS_MAX] = 32;
                EnWeatherTag_SetupAction(this, func_80967608);
            }
        }
    } else {
        if ((play->envCtx.precipitation[PRECIP_SOS_MAX] != 0) && !(play->state.frames & 3)) {
            play->envCtx.precipitation[PRECIP_SOS_MAX]--;
            if ((play->envCtx.precipitation[PRECIP_SOS_MAX]) == 8) {
                Environment_StopStormNatureAmbience(play);
            }
        }
    }
}

// WEATHERTAG_TYPE_LOCALDAY2RAIN 2
void func_80967608(EnWeatherTag* this, PlayState* play) {
    if ((WEATHER_TAG_RANGE100(&this->actor) + 10.0f) <
        Actor_WorldDistXZToActor(&GET_PLAYER(play)->actor, &this->actor)) {
        gWeatherMode = WEATHER_MODE_CLEAR;
        EnWeatherTag_SetupAction(this, func_809674C8);
    }
}

void EnWeatherTag_Update(Actor* thisx, PlayState* play) {
    EnWeatherTag* this = THIS;

    this->actionFunc(this, play);
    if ((play->actorCtx.flags & ACTORCTX_FLAG_1) && (play->msgCtx.msgMode != MSGMODE_NONE) &&
        (play->msgCtx.currentTextId == 0x5E6) && !FrameAdvance_IsEnabled(&play->state) &&
        (play->transitionTrigger == TRANS_TRIGGER_OFF) && (CutsceneManager_GetCurrentCsId() == CS_ID_NONE) &&
        (play->csCtx.state == CS_STATE_IDLE)) {

        gSaveContext.save.time = ((void)0, gSaveContext.save.time) + (u16)R_TIME_SPEED;
        if (R_TIME_SPEED != 0) {
            gSaveContext.save.time =
                ((void)0, gSaveContext.save.time) + (u16)((void)0, gSaveContext.save.timeSpeedOffset);
        }
    }
}

void EnWeatherTag_Draw(Actor* thisx, PlayState* play) {
}
