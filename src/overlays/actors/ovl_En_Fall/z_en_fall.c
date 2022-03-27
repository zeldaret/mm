/*
 * File: z_en_fall.c
 * Overlay: ovl_En_Fall
 * Description: The moon and related effects, along with the Moon's Tear that falls from its eye.
 *
 * This actor handles mutliple types of moon as well as a variety of effects. Specifically, it handles:
 * - Moon: A high-detail moon, used in Termina Field, the Clock Tower, and a few cutscenes.
 * - StoppedClosedMouthMoon: A high-detail moon, used in the Clock Tower after the Giants stop the moon from crashing.
 * - StoppedOpenMouthMoon: A high-detail open-mouthed moon, used in the cutscene prior to warping to the moon.
 * - CrashingMoon: An enlarged high-detail moon, used for when the moon is crashing.
 * - LodMoon: A low-detail moon, used everywhere else.
 * - MoonsTear: The Moon's Tear that can be seen falling from the telescope, along with its associated fire trail.
 * - Fireball: The ball of fire that surrounds the moon when it is crashing.
 * - RisingDebris: The debris that rises from the ground as the moon is crashing.
 * - FireRing: The ring of fire that expands outward when the moon is almost done crashing.
 */

#include "z_en_fall.h"
#include "objects/object_fall/object_fall.h"
#include "objects/object_fall2/object_fall2.h"
#include "objects/object_lodmoon/object_lodmoon.h"
#include "objects/object_moonston/object_moonston.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnFall*)thisx)

#define FLAG_FIRE_BALL_INTENSIFIES (1 << 0)
#define FLAG_FIRE_RING_APPEARS (1 << 1)

void EnFall_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFall_Update(Actor* thisx, GlobalContext* globalCtx);

void EnFall_Setup(EnFall* this, GlobalContext* globalCtx);
void EnFall_CrashingMoon_PerformCutsceneActions(EnFall* this, GlobalContext* globalCtx);
void EnFall_StoppedOpenMouthMoon_PerformCutsceneActions(EnFall* this, GlobalContext* globalCtx);
void EnFall_StoppedClosedMouthMoon_PerformCutsceneActions(EnFall* this, GlobalContext* globalCtx);
void EnFall_ClockTowerOrTitleScreenMoon_PerformCutsceneActions(EnFall* this, GlobalContext* globalCtx);
void EnFall_Moon_PerformDefaultActions(EnFall* this, GlobalContext* globalCtx);
void EnFall_MoonsTear_Fall(EnFall* this, GlobalContext* globalCtx);
void EnFall_Fireball_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFall_RisingDebris_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFall_FireRing_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFall_Moon_Draw(Actor* thisx, GlobalContext* globalCtx);
void EnFall_OpenMouthMoon_Draw(Actor* thisx, GlobalContext* globalCtx);
void EnFall_LodMoon_DrawWithoutLerp(Actor* thisx, GlobalContext* globalCtx);
void EnFall_LodMoon_DrawWithLerp(Actor* thisx, GlobalContext* globalCtx);
void EnFall_Fireball_Draw(Actor* thisx, GlobalContext* globalCtx);
void EnFall_RisingDebris_Draw(Actor* thisx, GlobalContext* globalCtx);
void EnFall_FireRing_Draw(Actor* thisx, GlobalContext* globalCtx);
void EnFall_MoonsTear_Draw(Actor* thisx, GlobalContext* globalCtx);

typedef struct {
    u8 modelIndex;
    Vec3f pos;
    Vec3f velocity;
    Vec3s rot;
} EnFallDebrisParticle;

EnFallDebrisParticle debrisParticles[50];

const ActorInit En_Fall_InitVars = {
    ACTOR_EN_FALL,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnFall),
    (ActorFunc)EnFall_Init,
    (ActorFunc)EnFall_Destroy,
    (ActorFunc)EnFall_Update,
    (ActorFunc)NULL,
};

/**
 * Sets the scale of the moon depending on the current day. On the Final Day,
 * it also moves the moon closer to the ground depending on the current time.
 */
void EnFall_Moon_AdjustScaleAndPosition(EnFall* this, GlobalContext* globalCtx) {
    u16 currentTime = gSaveContext.save.time;
    u16 dayStartTime = this->dayStartTime;
    f32 finalDayRelativeHeight;

    if (currentTime < dayStartTime) {
        finalDayRelativeHeight = 1.0f - (((f32)dayStartTime - (f32)currentTime) * (1.0f / 0x10000));
    } else {
        finalDayRelativeHeight = ((f32)currentTime - (f32)dayStartTime) * (1.0f / 0x10000);
    }
    switch (CURRENT_DAY) {
        case 0:
            Actor_SetScale(&this->actor, this->scale * 1.2f);
            this->actor.world.pos.y = this->actor.home.pos.y;
            break;

        case 1:
            Actor_SetScale(&this->actor, this->scale * 2.4f);
            this->actor.world.pos.y = this->actor.home.pos.y;
            break;

        case 2:
            Actor_SetScale(&this->actor, this->scale * 3.6f);
            this->actor.world.pos.y = this->actor.home.pos.y;
            break;

        case 3:
            Actor_SetScale(&this->actor, this->scale * 3.6f);
            if (EN_FALL_TYPE(&this->actor) == EN_FALL_TYPE_LODMOON_INVERTED_STONE_TOWER) {
                this->actor.world.pos.y =
                    this->actor.home.pos.y + (finalDayRelativeHeight * 6700.0f * (this->scale * 6.25f));
            } else {
                this->actor.world.pos.y =
                    this->actor.home.pos.y - (finalDayRelativeHeight * 6700.0f * (this->scale * 6.25f));
            }
            break;
    }
}

void EnFall_RisingDebris_ResetParticles(EnFall* this) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(debrisParticles); i++) {
        debrisParticles[i].modelIndex = 3;
    }
    this->activeDebrisParticleCount = 0;
}

void EnFall_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFall* this = THIS;
    s32 objectIndex;

    this->eyeGlowIntensity = 0.0f;
    this->flags = 0;

    // This system is basically never used in the final game; all instances
    // of EnFall will use the default case.
    switch (EN_FALL_SCALE(&this->actor)) {
        case 1:
            this->scale = 0.08f;
            break;

        case 2:
            this->scale = 0.04f;
            break;

        case 3:
            this->scale = 0.02f;
            break;

        case 4:
            this->scale = 0.01f;
            break;

        default:
            this->scale = 0.16f;
            break;
    }

    switch (EN_FALL_TYPE(&this->actor)) {
        case EN_FALL_TYPE_LODMOON_NO_LERP:
        case EN_FALL_TYPE_LODMOON:
        case EN_FALL_TYPE_LODMOON_INVERTED_STONE_TOWER:
            objectIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_LODMOON);
            break;

        case EN_FALL_TYPE_MOONS_TEAR:
            objectIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_MOONSTON);
            break;

        case EN_FALL_TYPE_STOPPED_MOON_OPEN_MOUTH:
            objectIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_FALL2);
            break;

        default:
            objectIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_FALL);
            break;
    }

    if (objectIndex < 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    this->objIndex = objectIndex;
    this->actionFunc = EnFall_Setup;
}

void EnFall_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

/**
 * Finds the Termina Field moon so the Moon's Tear can spawn in the correct place.
 */
Actor* EnFall_MoonsTear_GetTerminaFieldMoon(GlobalContext* globalCtx) {
    Actor* itemAction = globalCtx->actorCtx.actorLists[ACTORCAT_ITEMACTION].first;

    while (itemAction != NULL) {
        if (itemAction->id == ACTOR_EN_FALL && EN_FALL_TYPE(itemAction) == EN_FALL_TYPE_TERMINA_FIELD_MOON) {
            return itemAction;
        }
        itemAction = itemAction->next;
    }
    return NULL;
}

void EnFall_Setup(EnFall* this, GlobalContext* globalCtx) {
    Actor* moon;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->objIndex)) {
        this->actor.objBankIndex = this->objIndex;
        this->actionFunc = EnFall_Moon_PerformDefaultActions;
        switch (EN_FALL_TYPE(&this->actor)) {
            case EN_FALL_TYPE_TITLE_SCREEN_MOON:
                this->actor.draw = EnFall_Moon_Draw;
                this->actionFunc = EnFall_ClockTowerOrTitleScreenMoon_PerformCutsceneActions;
                Actor_SetScale(&this->actor, this->scale);
                break;

            case EN_FALL_TYPE_STOPPED_MOON_CLOSED_MOUTH:
                this->actor.draw = EnFall_Moon_Draw;
                this->actionFunc = EnFall_StoppedClosedMouthMoon_PerformCutsceneActions;
                Actor_SetScale(&this->actor, this->scale * 3.0f);
                if (!(gSaveContext.save.weekEventReg[25] & 2)) {
                    Actor_MarkForDeath(&this->actor);
                }
                break;

            case EN_FALL_TYPE_CLOCK_TOWER_MOON:
                this->actionFunc = EnFall_ClockTowerOrTitleScreenMoon_PerformCutsceneActions;
                Actor_SetScale(&this->actor, this->scale * 3.0f);
                this->actor.draw = EnFall_Moon_Draw;
                if (gSaveContext.save.weekEventReg[25] & 2) {
                    Actor_MarkForDeath(&this->actor);
                }
                break;

            case EN_FALL_TYPE_CRASHING_MOON:
                this->actor.draw = EnFall_Moon_Draw;
                Actor_SetScale(&this->actor, this->scale * 5.3999996f);
                this->actionFunc = EnFall_CrashingMoon_PerformCutsceneActions;
                break;

            case EN_FALL_TYPE_CRASH_FIRE_BALL:
                this->actor.update = EnFall_Fireball_Update;
                this->actor.draw = EnFall_Fireball_Draw;
                this->scale = 1.0f;
                this->actor.shape.rot.z = 0;
                this->fireballIntensity = 0.0f;
                this->fireballAlpha = 100;
                this->actor.shape.rot.x = this->actor.shape.rot.z;
                break;

            case EN_FALL_TYPE_CRASH_RISING_DEBRIS:
                this->actor.update = EnFall_RisingDebris_Update;
                this->actor.draw = EnFall_RisingDebris_Draw;
                this->scale = 1.0f;
                EnFall_RisingDebris_ResetParticles(this);
                Actor_SetScale(&this->actor, 1.0f);
                this->actor.shape.rot.x = 0;
                break;

            case EN_FALL_TYPE_LODMOON_NO_LERP:
                this->actor.draw = EnFall_LodMoon_DrawWithoutLerp;
                this->dayStartTime = CLOCK_TIME(6, 0);
                this->currentDay = CURRENT_DAY;
                EnFall_Moon_AdjustScaleAndPosition(this, globalCtx);
                break;

            case EN_FALL_TYPE_LODMOON:
            case EN_FALL_TYPE_LODMOON_INVERTED_STONE_TOWER:
                this->actor.draw = EnFall_LodMoon_DrawWithLerp;
                this->dayStartTime = CLOCK_TIME(6, 0);
                this->currentDay = CURRENT_DAY;
                EnFall_Moon_AdjustScaleAndPosition(this, globalCtx);
                break;

            case EN_FALL_TYPE_MOONS_TEAR:
                this->actor.update = EnFall_Update;
                this->actor.draw = NULL;
                this->actionFunc = EnFall_MoonsTear_Fall;
                Actor_SetScale(&this->actor, 0.02f);
                if (!(globalCtx->actorCtx.unk5 & 2)) {
                    Actor_MarkForDeath(&this->actor);
                }
                moon = EnFall_MoonsTear_GetTerminaFieldMoon(globalCtx);
                this->actor.child = moon;
                if (moon == NULL) {
                    Actor_MarkForDeath(&this->actor);
                }
                break;

            case EN_FALL_TYPE_STOPPED_MOON_OPEN_MOUTH:
                this->actor.draw = NULL;
                this->actionFunc = EnFall_StoppedOpenMouthMoon_PerformCutsceneActions;
                Actor_SetScale(&this->actor, this->scale * 3.0f);
                break;

            case EN_FALL_TYPE_CRASH_FIRE_RING:
                this->actor.update = EnFall_FireRing_Update;
                this->actor.draw = EnFall_FireRing_Draw;
                Actor_SetScale(&this->actor, 0.2f);
                break;

            default:
                // used for EN_FALL_TYPE_TERMINA_FIELD_MOON and anything else that isn't in the enum
                this->actor.draw = EnFall_Moon_Draw;
                this->dayStartTime = CLOCK_TIME(6, 0);
                this->currentDay = CURRENT_DAY;
                EnFall_Moon_AdjustScaleAndPosition(this, globalCtx);
                break;
        }
    }
}

void EnFall_CrashingMoon_HandleGiantsCutscene(EnFall* this, GlobalContext* globalCtx) {
    static s32 sGiantsCutsceneState = 0;

    if (globalCtx->sceneNum == SCENE_00KEIKOKU && gSaveContext.sceneSetupIndex == 1 &&
        globalCtx->csCtx.currentCsIndex == 0) {
        switch (sGiantsCutsceneState) {
            case 0:
                if (globalCtx->csCtx.state != 0) {
                    sGiantsCutsceneState += 2;
                }
                break;

            case 2:
                if (CHECK_QUEST_ITEM(QUEST_REMAINS_ODOWLA) && CHECK_QUEST_ITEM(QUEST_REMAINS_GOHT) &&
                    CHECK_QUEST_ITEM(QUEST_REMAINS_GYORG) && CHECK_QUEST_ITEM(QUEST_REMAINS_TWINMOLD)) {
                    if (gSaveContext.save.weekEventReg[93] & 4) {
                        if (ActorCutscene_GetCanPlayNext(0xC)) {
                            ActorCutscene_Start(0xC, &this->actor);
                            sGiantsCutsceneState++;
                        } else {
                            ActorCutscene_SetIntentToPlay(0xC);
                        }
                    } else if (ActorCutscene_GetCanPlayNext(0xB)) {
                        ActorCutscene_Start(0xB, &this->actor);
                        gSaveContext.save.weekEventReg[93] |= 4;
                        sGiantsCutsceneState++;
                    } else {
                        ActorCutscene_SetIntentToPlay(0xB);
                    }
                } else if (globalCtx->csCtx.frames > 1600) {
                    globalCtx->nextEntranceIndex = 0x2C00;
                    gSaveContext.nextCutsceneIndex = 0xFFF2;
                    globalCtx->sceneLoadFlag = 0x14;
                    globalCtx->unk_1887F = 2;
                    gSaveContext.nextTransition = 2;
                    sGiantsCutsceneState = 9;
                }
                break;

            case 9:
                globalCtx->csCtx.frames--;
                break;
        }
    }
}

void EnFall_CrashingMoon_PerformCutsceneActions(EnFall* this, GlobalContext* globalCtx) {
    EnFall_CrashingMoon_HandleGiantsCutscene(this, globalCtx);
    if (Cutscene_CheckActorAction(globalCtx, 0x85)) {
        if (Cutscene_CheckActorAction(globalCtx, 133) &&
            globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 133)]->action == 1) {
            this->actor.draw = NULL;
        } else {
            this->actor.draw = EnFall_Moon_Draw;
            if (Cutscene_CheckActorAction(globalCtx, 133) &&
                globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 133)]->action == 2) {
                Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, Cutscene_GetActorActionIndex(globalCtx, 133));
            }
        }
    } else {
        this->actor.draw = NULL;
    }
}

void EnFall_StoppedOpenMouthMoon_PerformCutsceneActions(EnFall* this, GlobalContext* globalCtx) {
    if (Cutscene_CheckActorAction(globalCtx, 133)) {
        switch (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 133)]->action) {
            case 3:
                if (this->eyeGlowIntensity == 0.0f) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_MOON_EYE_FLASH);
                }
                this->eyeGlowIntensity += 1 / 30.0f;
                if (this->eyeGlowIntensity > 1.0f) {
                    this->eyeGlowIntensity = 1.0f;
                }
                break;

            case 4:
                this->actor.draw = EnFall_OpenMouthMoon_Draw;
                break;
        }
    }
}

void EnFall_StoppedClosedMouthMoon_PerformCutsceneActions(EnFall* this, GlobalContext* globalCtx) {
    if (Cutscene_CheckActorAction(globalCtx, 133)) {
        switch (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 133)]->action) {
            case 2:
                Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, Cutscene_GetActorActionIndex(globalCtx, 133));
                break;

            case 4:
                this->actor.draw = NULL;
                break;
        }
    }

    if (globalCtx->sceneNum == SCENE_OKUJOU && gSaveContext.sceneSetupIndex == 2) {
        switch (globalCtx->csCtx.currentCsIndex) {
            case 0:
                switch (globalCtx->csCtx.frames) {
                    case 1060:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_MOON_SCREAM1);
                        break;

                    case 1089:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_MOON_CRY);
                        break;

                    case 1303:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_SLIP_MOON);
                        break;
                }
                if (globalCtx->csCtx.frames >= 1145) {
                    func_800B9010(&this->actor, NA_SE_EV_FALL_POWER - SFX_FLAG);
                }
                break;

            case 1:
                switch (globalCtx->csCtx.frames) {
                    case 561:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_MOON_SCREAM1);
                        break;

                    case 590:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_MOON_CRY);
                        break;

                    case 737:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_SLIP_MOON);
                        break;
                }
                if (globalCtx->csCtx.frames >= 650) {
                    func_800B9010(&this->actor, NA_SE_EV_FALL_POWER - SFX_FLAG);
                }
                break;
        }
    }
}

void EnFall_ClockTowerOrTitleScreenMoon_PerformCutsceneActions(EnFall* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.state != 0 && globalCtx->sceneNum == SCENE_OKUJOU) {
        func_800B9010(&this->actor, NA_SE_EV_MOON_FALL - SFX_FLAG);
    }
}

/**
 * Used by the Moon in Termina Field, as well as all LodMoons.
 */
void EnFall_Moon_PerformDefaultActions(EnFall* this, GlobalContext* globalCtx) {
    u16 currentDay;

    if (Cutscene_CheckActorAction(globalCtx, 133)) {
        if (Cutscene_CheckActorAction(globalCtx, 133) &&
            globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 133)]->action == 1) {
            this->actor.draw = NULL;
        } else {
            Actor_SetScale(&this->actor, this->scale * 3.6f);
            this->actor.draw = EnFall_Moon_Draw;
            if (Cutscene_CheckActorAction(globalCtx, 133) &&
                globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 133)]->action == 2) {
                Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, Cutscene_GetActorActionIndex(globalCtx, 133));
            }
        }
    } else {
        if (this->actor.draw == NULL) {
            this->actor.draw = EnFall_Moon_Draw;
        }
        currentDay = CURRENT_DAY;
        if ((u16)this->currentDay != (u32)currentDay) {
            this->currentDay = currentDay;
            this->dayStartTime = gSaveContext.save.time;
        }
        EnFall_Moon_AdjustScaleAndPosition(this, globalCtx);
    }
}

void EnFall_MoonsTear_Initialize(EnFall* this) {
    s32 pad[2];

    this->actor.draw = EnFall_MoonsTear_Draw;
    if (this->actor.child != NULL) {
        // The focus of the child needs to be shifted in EnFall_Moon_Draw first,
        // otherwise the tear will spawn in the wrong place.
        Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.child->focus.pos);
    }
    this->actor.world.rot.y = Math_Vec3f_Yaw(&this->actor.world.pos, &this->actor.home.pos);
    this->actor.world.rot.x = Math_Vec3f_Pitch(&this->actor.world.pos, &this->actor.home.pos);
    this->actor.speedXZ = Math_Vec3f_DistXYZ(&this->actor.world.pos, &this->actor.home.pos) / 82.0f;
    this->actor.shape.rot.x = this->actor.world.rot.x;
    this->actor.shape.rot.y = this->actor.world.rot.y;
}

void EnFall_MoonsTear_DoNothing(EnFall* this, GlobalContext* globalCtx) {
}

void EnFall_MoonsTear_Fall(EnFall* this, GlobalContext* globalCtx) {
    s32 pad;

    if (Cutscene_CheckActorAction(globalCtx, 517) &&
        globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 517)]->action == 2 &&
        this->actor.draw == NULL) {
        EnFall_MoonsTear_Initialize(this);
    }

    if (this->actor.draw != NULL) {
        if (Math_Vec3f_StepTo(&this->actor.world.pos, &this->actor.home.pos, this->actor.speedXZ) <= 0.0f) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_GORON_BOUND_1);
            gSaveContext.save.weekEventReg[74] |= 0x80;
            gSaveContext.save.weekEventReg[74] |= 0x20;
            Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_TEST, this->actor.world.pos.x,
                               this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, -2);
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->actor.world.pos.x,
                        this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, CLEAR_TAG_LARGE_EXPLOSION);
            this->actor.draw = NULL;
            this->actionFunc = EnFall_MoonsTear_DoNothing;
        } else {
            func_800B9010(&this->actor, NA_SE_EV_MOONSTONE_FALL - SFX_FLAG);
        }
    }
}

void EnFall_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFall* this = THIS;
    this->actionFunc(this, globalCtx);
}

/**
 * Updates the alpha for every vertex in the fire ball so that some parts of
 * the sphere are more transparent or opaque than others.
 */
void EnFall_Fireball_SetPerVertexAlpha(f32 fireballAlpha) {
    static u8 sAlphaTableIndex[] = {
        4, 4, 0, 1, 1, 1, 1, 1, 1, 3, 3, 0, 0, 3, 0, 1, 1, 1, 4, 0, 4, 0, 1, 1, 1, 3, 0, 3, 0, 1, 1, 1, 4, 4, 1,
        1, 0, 4, 4, 0, 1, 1, 1, 1, 1, 1, 3, 3, 0, 0, 3, 3, 0, 0, 1, 1, 1, 1, 1, 4, 0, 4, 4, 0, 4, 4, 1, 1, 1, 1,
        1, 1, 3, 3, 0, 0, 3, 3, 0, 0, 1, 1, 1, 1, 1, 1, 4, 4, 0, 4, 0, 1, 1, 1, 3, 0, 3, 3, 0, 0, 1, 1, 1, 1, 1,
        1, 4, 4, 0, 4, 4, 0, 1, 1, 1, 1, 1, 1, 3, 3, 0, 0, 0, 0, 0, 2, 2, 1, 1, 0, 0, 2, 2, 0, 1, 1, 0, 0, 1, 0,
        2, 0, 0, 1, 0, 2, 0, 0, 2, 1, 2, 0, 1, 0, 1, 0, 0, 1, 2, 2, 0, 0, 2, 1, 1, 0, 0, 1, 1, 0, 0, 2, 2, 0, 0,
        0, 0, 2, 0, 2, 2, 0, 1, 1, 0, 0, 1, 0, 0, 1, 2, 2, 0, 0, 0, 2, 2, 1, 1, 0, 0, 1, 1, 0, 0, 2, 2, 0, 0,
    };

    s32 pad;
    u8 perVertexAlphaTable[5];
    Vtx* vertices = Lib_SegmentedToVirtual(gMoonFireballVtx);
    s32 i;

    if (fireballAlpha > 1.0f) {
        fireballAlpha = 1.0f;
    }
    perVertexAlphaTable[0] = 0;
    perVertexAlphaTable[1] = (s8)(255.0f * fireballAlpha);
    perVertexAlphaTable[2] = (s8)(155.0f * fireballAlpha);
    perVertexAlphaTable[3] = (s8)(104.0f * fireballAlpha);
    perVertexAlphaTable[4] = (s8)(54.0f * fireballAlpha);

    for (i = 0; i < ARRAY_COUNT(sAlphaTableIndex); i++, vertices++) {
        vertices->v.cn[3] = perVertexAlphaTable[sAlphaTableIndex[i]];
    }
}

void EnFall_Fireball_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFall* this = THIS;

    if (globalCtx->sceneNum == SCENE_00KEIKOKU && gSaveContext.sceneSetupIndex == 0 &&
        globalCtx->csCtx.currentCsIndex == 2) {
        globalCtx->skyboxCtx.rotY -= 0.05f;
    }

    if (Cutscene_CheckActorAction(globalCtx, 450)) {
        this->actor.draw = EnFall_Fireball_Draw;
        if (this->flags & FLAG_FIRE_BALL_INTENSIFIES) {
            this->fireballIntensity += 0.01f;
            if (this->fireballIntensity > 1.0f) {
                this->fireballIntensity = 1.0f;
            }
        }
        Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, Cutscene_GetActorActionIndex(globalCtx, 450));

        switch (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 450)]->action) {
            default:
                this->actor.draw = NULL;
                this->fireballAlpha = 0;
                break;

            case 2:
                if (this->fireballAlpha < 100) {
                    this->fireballAlpha += 4;
                }
                if (this->fireballAlpha > 100) {
                    this->fireballAlpha = 100;
                }
                EnFall_Fireball_SetPerVertexAlpha(this->fireballAlpha * 0.01f);
                break;

            case 3:
                if (this->fireballAlpha > 0) {
                    this->fireballAlpha -= 2;
                }
                if (this->fireballAlpha < 0) {
                    this->fireballAlpha = 0;
                }
                EnFall_Fireball_SetPerVertexAlpha(this->fireballAlpha * 0.01f);
                break;

            case 4:
                this->flags |= FLAG_FIRE_BALL_INTENSIFIES;
                break;

            case 5:
                break;
        }
    } else {
        this->actor.draw = NULL;
    }

    if (Cutscene_CheckActorAction(globalCtx, 0x1C2) && this->fireballAlpha > 0) {
        func_8019F128(NA_SE_EV_MOON_FALL_LAST - SFX_FLAG);
    }
    Actor_SetScale(&this->actor, this->scale * 1.74f);
}

void EnFall_RisingDebris_UpdateParticles(EnFall* this) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(debrisParticles); i++) {
        if (debrisParticles[i].modelIndex < 3) {
            debrisParticles[i].pos.x += debrisParticles[i].velocity.x;
            debrisParticles[i].pos.y += debrisParticles[i].velocity.y;
            debrisParticles[i].pos.z += debrisParticles[i].velocity.z;
            debrisParticles[i].rot.x += 0x64;
            debrisParticles[i].rot.y += 0xC8;
            debrisParticles[i].rot.z += 0x12C;
            if ((this->actor.world.pos.y + 3000.0f) < debrisParticles[i].pos.y) {
                debrisParticles[i].modelIndex = 3;
                this->activeDebrisParticleCount--;
            }
        }
    }
}

s32 EnFall_RisingDebris_InitializeParticles(EnFall* this) {
    s16 angle;
    s32 i;
    f32 scale;

    for (i = 0; i < ARRAY_COUNT(debrisParticles); i++) {
        if (debrisParticles[i].modelIndex >= 3) {
            debrisParticles[i].modelIndex = (s32)Rand_ZeroFloat(3.0f);
            debrisParticles[i].pos.x = this->actor.world.pos.x;
            debrisParticles[i].pos.y = this->actor.world.pos.y;
            debrisParticles[i].pos.z = this->actor.world.pos.z;
            angle = randPlusMinusPoint5Scaled(0x10000);
            scale = (1.0f - (Rand_ZeroFloat(1.0f) * Rand_ZeroFloat(1.0f))) * 3000.0f;
            debrisParticles[i].pos.x += Math_SinS(angle) * scale;
            debrisParticles[i].pos.z += Math_CosS(angle) * scale;
            debrisParticles[i].velocity.x = 0.0f;
            debrisParticles[i].velocity.z = 0.0f;
            debrisParticles[i].velocity.y = 80.0f;
            debrisParticles[i].rot.x = randPlusMinusPoint5Scaled(0x10000);
            debrisParticles[i].rot.y = randPlusMinusPoint5Scaled(0x10000);
            debrisParticles[i].rot.z = randPlusMinusPoint5Scaled(0x10000);
            this->activeDebrisParticleCount++;
            return true;
        }
    }

    return false;
}

void EnFall_RisingDebris_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFall* this = THIS;

    if (Cutscene_CheckActorAction(globalCtx, 451)) {
        if (Cutscene_CheckActorAction(globalCtx, 451) &&
            globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 451)]->action == 2) {
            EnFall_RisingDebris_UpdateParticles(this);
            EnFall_RisingDebris_InitializeParticles(this);
        } else if (this->activeDebrisParticleCount != 0) {
            EnFall_RisingDebris_ResetParticles(this);
        }
    } else if (thisx->home.rot.x != 0) {
        EnFall_RisingDebris_UpdateParticles(this);
        EnFall_RisingDebris_InitializeParticles(this);
    }
}

void EnFall_FireRing_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFall* this = THIS;

    if (Cutscene_CheckActorAction(globalCtx, 450) &&
        globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 450)]->action == 5) {
        if (!(this->flags & FLAG_FIRE_RING_APPEARS)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_DM_RING_EXPLOSION);
        }
        this->flags |= FLAG_FIRE_RING_APPEARS;
    }
    if (this->flags & FLAG_FIRE_RING_APPEARS) {
        this->fireRingAlpha += 1 / 30.0f;
        if (this->fireRingAlpha > 1.0f) {
            this->fireRingAlpha = 1.0f;
        }
        if (this->actor.scale.x < 18.0f) {
            this->actor.scale.x += 0.2f;
        }
        this->actor.scale.z = this->actor.scale.x;
        this->actor.scale.y = Math_SinS(this->fireWallYScale) * 5.0f;
        if (this->fireWallYScale < 0x4000) {
            this->fireWallYScale += 0x147;
        }
    }
}

/**
 * Used for all closed-mouth high-detail moons, including
 * StoppedClosedMouthMoon and CrashingMoon.
 */
void EnFall_Moon_Draw(Actor* thisx, GlobalContext* globalCtx) {
    // This offsets the moon's focus so that the Moon's Tear actually falls
    // out of its eye when looking at it through the telescope.
    static Vec3f sFocusOffset[] = { 1800.0f, 1000.0f, 4250.0f };
    EnFall* this = THIS;
    s32 primColor;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    Matrix_MultiplyVector3fByState(sFocusOffset, &this->actor.focus.pos);

    primColor = (this->eyeGlowIntensity * 200.0f) + 40.0f;
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x80, primColor, primColor, primColor, 255);

    gSPDisplayList(POLY_OPA_DISP++, gMoonDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnFall_OpenMouthMoon_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnFall* this = THIS;
    s32 primColor;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    primColor = (this->eyeGlowIntensity * 200.0f) + 40.0f;
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x80, primColor, primColor, primColor, 255);

    gSPDisplayList(POLY_OPA_DISP++, gOpenMouthMoonDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnFall_LodMoon_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnFall* this = THIS;
    s32 primColor;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 20, 25, 30, 0, 0x3E7, 0x3200);
    gDPSetRenderMode(POLY_OPA_DISP++, G_RM_PASS, G_RM_AA_ZB_OPA_SURF2);
    gSPLoadGeometryMode(POLY_OPA_DISP++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);

    primColor = (this->eyeGlowIntensity * 200.0f) + 40.0f;
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x80, primColor, primColor, primColor, 255);

    gSPDisplayList(POLY_OPA_DISP++, gLodmoonEyesDL);
    gSPLoadGeometryMode(POLY_OPA_DISP++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH);
    gSPDisplayList(POLY_OPA_DISP++, gLodmoonMoonDL);
    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnFall_LodMoon_DrawWithoutLerp(Actor* thisx, GlobalContext* globalCtx) {
    EnFall_LodMoon_Draw(thisx, globalCtx);
}

/**
 * If the moon is more than 9000 units away from the eye, this will lerp it
 * to be 9000 units away before drawing it.
 */
void EnFall_LodMoon_DrawWithLerp(Actor* thisx, GlobalContext* globalCtx) {
    f32 distanceToEye = Actor_DistanceToPoint(thisx, &globalCtx->view.eye);
    f32 scale;
    Vec3f translation;

    if (distanceToEye > 9000.0f) {
        scale = 9000.0f / distanceToEye;
        translation.x = (-(globalCtx->view.eye.x - thisx->world.pos.x) * scale) + globalCtx->view.eye.x;
        translation.y = (-(globalCtx->view.eye.y - thisx->world.pos.y) * scale) + globalCtx->view.eye.y;
        translation.z = (-(globalCtx->view.eye.z - thisx->world.pos.z) * scale) + globalCtx->view.eye.z;
        Matrix_InsertTranslation(translation.x, translation.y, translation.z, MTXMODE_NEW);
        Matrix_Scale(thisx->scale.x, thisx->scale.y, thisx->scale.z, MTXMODE_APPLY);
        Matrix_RotateY(thisx->shape.rot.y, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(thisx->shape.rot.x, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(thisx->shape.rot.z, MTXMODE_APPLY);
    }

    EnFall_LodMoon_Draw(thisx, globalCtx);
}

void EnFall_Fireball_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnFall* this = THIS;
    u32 gameplayFrames = globalCtx->gameplayFrames;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C2DC(globalCtx->state.gfxCtx);

    this->fireballYTexScroll1 += (s32)(4.0f + (this->fireballIntensity * 12.0f));
    this->fireballYTexScroll2 += (s32)(2.0f + (this->fireballIntensity * 6.0f));

    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80,
                    (s32)(((1.0f - this->fireballIntensity) * 160.0f) + (255.0f * this->fireballIntensity)),
                    (s32)((70.0f * (1.0f - this->fireballIntensity)) + (255.0f * this->fireballIntensity)),
                    (s32)(70.0f * (1.0f - this->fireballIntensity)), 255);
    gDPSetEnvColor(
        POLY_XLU_DISP++, (s32)(((1.0f - this->fireballIntensity) * 50.0f) + (200.0f * this->fireballIntensity)),
        (s32)(20.0f * (1.0f - this->fireballIntensity)), (s32)(20.0f * (1.0f - this->fireballIntensity)), 255);

    // For the glowing sphere of fire
    gSPSegment(POLY_XLU_DISP++, 0x09,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, gameplayFrames, -this->fireballYTexScroll2, 64, 64, 1,
                                -gameplayFrames, -this->fireballYTexScroll1, 64, 64));

    // For the "flecks" of fire around the fireball
    gSPSegment(POLY_XLU_DISP++, 0x0A,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, gameplayFrames * 2, -this->fireballYTexScroll1, 64, 64, 1,
                                -gameplayFrames * 2, -this->fireballYTexScroll1, 64, 64));

    gDPSetColorDither(POLY_XLU_DISP++, G_CD_NOISE);
    gDPSetAlphaDither(POLY_XLU_DISP++, G_AD_NOISE);
    gSPDisplayList(POLY_XLU_DISP++, gMoonFireballDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnFall_RisingDebris_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static Gfx* sDebrisModelDLists[] = { gMoonDebrisModel1DL, gMoonDebrisModel2DL, gMoonDebrisModel3DL };
    EnFall* this = THIS;
    f32 scale = this->scale * 0.06f;
    s32 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPDisplayList(POLY_OPA_DISP++, gMoonDebrisMaterialDL);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);

    for (i = 0; i < ARRAY_COUNT(debrisParticles); i++) {
        if (debrisParticles[i].modelIndex < 3) {
            Matrix_InsertTranslation(debrisParticles[i].pos.x, debrisParticles[i].pos.y, debrisParticles[i].pos.z,
                                     MTXMODE_NEW);
            Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);
            Matrix_InsertRotation(debrisParticles[i].rot.x, debrisParticles[i].rot.y, debrisParticles[i].rot.z,
                                  MTXMODE_APPLY);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, sDebrisModelDLists[debrisParticles[i].modelIndex]);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnFall_FireRing_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnFall* this = THIS;

    if (!(this->fireRingAlpha <= 0.0f)) {
        if (this->fireRingAlpha > 1.0f) {
            this->fireRingAlpha = 1.0f;
        }
        OPEN_DISPS(globalCtx->state.gfxCtx);

        AnimatedMat_DrawXlu(globalCtx, Lib_SegmentedToVirtual(gMoonFireRingTexAnim));
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        func_8012C2DC(globalCtx->state.gfxCtx);

        gDPSetColorDither(POLY_XLU_DISP++, G_CD_NOISE);
        gDPSetAlphaDither(POLY_XLU_DISP++, G_AD_NOISE);

        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 255, (s32)(this->fireRingAlpha * 255.0f));

        gSPDisplayList(POLY_XLU_DISP++, gMoonFireRingDL);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void EnFall_MoonsTear_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(gFallingMoonsTearTexAnim));
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C28C(globalCtx->state.gfxCtx);

    gSPDisplayList(POLY_OPA_DISP++, gFallingMoonsTearDL);

    Matrix_Scale(3.0f, 3.0f, 6.0f, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPDisplayList(POLY_XLU_DISP++, gFallingMoonsTearFireDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
