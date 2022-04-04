/*
 * File: z_obj_tokeidai.c
 * Overlay: ovl_Obj_Tokeidai
 * Description: Components of the Clock Tower. Also used for wall clocks. The specific components are:
 * - ClockFace: The decorated face of the clock that spins every hour.
 * - MinuteRing: The ring around the clock face that spins every two minutes.
 * - ExteriorGear: The two gears on the side of the tower that spin every two minutes.
 * - SunAndMoonPanel: A panel with a sun and moon image that tells whether it is day or night.
 * - Counterweight: The spinning weight on top of the tower that emits a spotlight at night.
 * - StaircaseToRooftop: The staircase to tower's rooftop that opens after midnight on the Final Day.
 * - TerminaFieldWalls: The walls of the Clock Tower visible from Termina Field.
 * - UnusedWall: A single wall of the Clock Tower, unused in the final game.
 *
 * Sometimes, the ClockFace, MinuteRing, and SunAndMoonPanel are treated as a single clock entity.
 * This is called Clock if it applies to both the Clock Tower clock and wall clocks, and
 * TowerClock/WallClock, respectively, if it only applies to one of them.
 *
 * On the midnight of the Final Day, the Clock Tower opens up, and the various pieces of it
 * are moved around. This actor is responsible for managing all of this movement, which is handled
 * via the series of action functions labeled with TowerOpening.
 *
 * All components have at least one of these three actions:
 * - Idle: The "default" action, and for some components the only action.
 *       The component is either completely still, or it's telling the time, depending on the component.
 * - OpenedIdle: The action for certain Clock Tower components after midnight on the Final Day.
 *       The TowerClock, ExteriorGears, and Counterweight no longer tell time and are moved to a different position.
 *       Called "opened" because it corresponds to when the staircase to the tower's rooftop is opened up.
 * - Collapse: The action for certain Clock Tower components when the moon crashes into Termina.
 *       This action is responsible for making the component fall during the moon crash cutscene.
 */

#include "z_obj_tokeidai.h"
#include "objects/object_obj_tokeidai/object_obj_tokeidai.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjTokeidai*)thisx)

#define GET_CURRENT_CLOCK_HOUR(this) ((s32)((this)->clockTime * (24.0f / 0x10000)))
#define GET_CURRENT_CLOCK_MINUTE(this) ((s32)((this)->clockTime * (360 * 2.0f / 0x10000)) % 30)
#define GET_CLOCK_FACE_ROTATION(currentClockHour) ((s16)(currentClockHour * (0x10000 / 24.0f)))
#define GET_MINUTE_RING_OR_EXTERIOR_GEAR_ROTATION(currentClockMinute) \
    ((s16)(currentClockMinute * (0x10000 * 12.0f / 360)))

void ObjTokeidai_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_Draw(Actor* thisx, GlobalContext* globalCtx);

void ObjTokeidai_DoNothing(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_TowerClock_OpenedIdle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_ExteriorGear_OpenedIdle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_Counterweight_OpenedIdle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_TowerClock_Idle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_WallClock_Idle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_ExteriorGear_Idle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_Counterweight_Idle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_TerminaFieldWalls_Idle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_StaircaseToRooftop_Idle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_SetupTowerOpening(ObjTokeidai* this);
void ObjTokeidai_Clock_Draw(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_Counterweight_Draw(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_ExteriorGear_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Tokeidai_InitVars = {
    ACTOR_OBJ_TOKEIDAI,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_OBJ_TOKEIDAI,
    sizeof(ObjTokeidai),
    (ActorFunc)ObjTokeidai_Init,
    (ActorFunc)ObjTokeidai_Destroy,
    (ActorFunc)ObjTokeidai_Update,
    (ActorFunc)ObjTokeidai_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 3300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1100, ICHAIN_STOP),
};

/**
 * Returns the angle necessary to show the correct side of
 * the sun and moon panel based on the time of day. The actual
 * angle can differ from the target angle if the panel is in
 * the middle of rotating.
 */
s32 ObjTokeidai_GetTargetSunMoonPanelRotation() {
    if (gSaveContext.save.isNight) {
        return 0x8000;
    }
    return 0;
}

void ObjTokeidai_SetupClockOrExteriorGear(ObjTokeidai* this) {
    s32 currentClockMinute = GET_CURRENT_CLOCK_MINUTE(this);

    this->clockMinute = currentClockMinute;
    this->minuteRingOrExteriorGearRotation = GET_MINUTE_RING_OR_EXTERIOR_GEAR_ROTATION(currentClockMinute);
    this->minuteRingOrExteriorGearRotationalVelocity = 0x3C;
    this->minuteRingOrExteriorGearRotationTimer = 0;
}

void ObjTokeidai_Clock_Init(ObjTokeidai* this) {
    s32 currentClockHour;

    ObjTokeidai_SetupClockOrExteriorGear(this);
    currentClockHour = GET_CURRENT_CLOCK_HOUR(this);
    this->clockHour = currentClockHour;
    this->clockFaceRotation = GET_CLOCK_FACE_ROTATION(currentClockHour);
    this->clockFaceRotationalVelocity = 0;
    this->clockFaceRotationTimer = 0;
    this->sunMoonPanelRotationalVelocity = 0;
    this->sunMoonPanelRotation = ObjTokeidai_GetTargetSunMoonPanelRotation();
}

void ObjTokeidai_ExteriorGear_Init(ObjTokeidai* this, GlobalContext* globalCtx) {
    this->actor.draw = ObjTokeidai_ExteriorGear_Draw;
    this->opaDList = gClockTowerExteriorGearDL;
    ObjTokeidai_SetupClockOrExteriorGear(this);

    if (((globalCtx->sceneNum == SCENE_CLOCKTOWER) && (gSaveContext.sceneSetupIndex == 2) &&
         (globalCtx->csCtx.currentCsIndex == 0)) ||
        ((globalCtx->sceneNum == SCENE_00KEIKOKU) && (gSaveContext.sceneSetupIndex == 2) &&
         (globalCtx->csCtx.currentCsIndex == 0))) {
        ObjTokeidai_SetupTowerOpening(this);
    } else if ((CURRENT_DAY == 3 && gSaveContext.save.time < CLOCK_TIME(6, 0)) || CURRENT_DAY >= 4) {
        this->actionFunc = ObjTokeidai_ExteriorGear_OpenedIdle;
        this->actor.world.pos.y += this->actor.scale.y * 1900.0f;
        this->actor.shape.yOffset = 1500.0f;
        gSaveContext.save.weekEventReg[8] |= 0x40;
    } else {
        this->actionFunc = ObjTokeidai_ExteriorGear_Idle;
    }
}

void ObjTokeidai_TowerClock_Init(ObjTokeidai* this, GlobalContext* globalCtx) {
    this->actor.draw = ObjTokeidai_Clock_Draw;
    ObjTokeidai_Clock_Init(this);

    if (((globalCtx->sceneNum == SCENE_CLOCKTOWER) && (gSaveContext.sceneSetupIndex == 2) &&
         (globalCtx->csCtx.currentCsIndex == 0)) ||
        ((globalCtx->sceneNum == SCENE_00KEIKOKU) && (gSaveContext.sceneSetupIndex == 2) &&
         (globalCtx->csCtx.currentCsIndex == 0))) {
        ObjTokeidai_SetupTowerOpening(this);
    } else if ((CURRENT_DAY == 3 && gSaveContext.save.time < CLOCK_TIME(6, 0)) || CURRENT_DAY >= 4) {
        this->actor.world.pos.y += (this->actor.scale.y * 5191.0f) - 50.0f;
        this->actor.world.pos.x += Math_SinS(this->actor.world.rot.y) * this->actor.scale.z * 1791.0f;
        this->actor.world.pos.z += -Math_CosS(this->actor.world.rot.y) * this->actor.scale.z * 1791.0f;

        this->clockFaceZTranslation = -0x140;
        this->actor.shape.rot.x = -0x4000;

        this->actor.home.pos = this->actor.world.pos;
        this->actor.home.pos.y -= 1178.0f;
        this->actor.home.pos.z += 13.0f;

        this->actionFunc = ObjTokeidai_TowerClock_OpenedIdle;
    } else {
        this->actionFunc = ObjTokeidai_TowerClock_Idle;
    }
}

void ObjTokeidai_Counterweight_Init(ObjTokeidai* this, GlobalContext* globalCtx) {
    s32 type;

    this->actor.draw = ObjTokeidai_Counterweight_Draw;
    this->opaDList = gClockTowerCounterweightDL;
    this->xluDList = gClockTowerSpotlightDL;
    if (gSaveContext.save.isNight) {
        this->spotlightIntensity = 100;
    } else {
        this->spotlightIntensity = 0;
    }

    if (((globalCtx->sceneNum == SCENE_CLOCKTOWER) && (gSaveContext.sceneSetupIndex == 2) &&
         (globalCtx->csCtx.currentCsIndex == 0)) ||
        ((globalCtx->sceneNum == SCENE_00KEIKOKU) && (gSaveContext.sceneSetupIndex == 2) &&
         (globalCtx->csCtx.currentCsIndex == 0))) {
        this->spotlightIntensity = 0;
        ObjTokeidai_SetupTowerOpening(this);

        if (this->actor.child == NULL) {
            type = OBJ_TOKEIDAI_TYPE(&this->actor);
            if (type == OBJ_TOKEIDAI_TYPE_COUNTERWEIGHT_CLOCK_TOWN ||
                type == OBJ_TOKEIDAI_TYPE_COUNTERWEIGHT_TERMINA_FIELD) {
                this->actor.child =
                    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_HANABI, this->actor.world.pos.x,
                                this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 0);
            }
        }

        if (this->actor.child != NULL) {
            if (OBJ_TOKEIDAI_TYPE(&this->actor) == OBJ_TOKEIDAI_TYPE_COUNTERWEIGHT_TERMINA_FIELD) {
                this->actor.child->home.rot.x = 0x384;
            } else {
                this->actor.child->home.rot.x = 0x12C;
            }
        }
    } else if ((CURRENT_DAY == 3 && gSaveContext.save.time < CLOCK_TIME(6, 0)) || CURRENT_DAY >= 4) {
        this->spotlightIntensity = 0;
        this->actor.world.pos.y += this->actor.scale.y * -2160.0f;
        this->actor.world.pos.x += Math_SinS(this->actor.world.rot.y) * this->actor.scale.z * 5400.0f;
        this->actor.world.pos.z += -Math_CosS(this->actor.world.rot.y) * this->actor.scale.z * 5400.0f;
        this->actor.shape.rot.x = -0x4000;
        this->actionFunc = ObjTokeidai_Counterweight_OpenedIdle;
    } else {
        this->actionFunc = ObjTokeidai_Counterweight_Idle;
    }
}

void ObjTokeidai_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjTokeidai* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->actionFunc = ObjTokeidai_DoNothing;
    this->opaDList = NULL;
    this->xluDList = NULL;
    this->xRotation = 0;
    this->yTranslation = 0;
    this->clockFaceZTranslation = 0;
    this->clockTime = gSaveContext.save.time;
    this->actor.home.rot.x = 0;

    switch (OBJ_TOKEIDAI_TYPE(&this->actor)) {
        case OBJ_TOKEIDAI_TYPE_EXTERIOR_GEAR_TERMINA_FIELD:
            Actor_SetScale(&this->actor, 0.15f);
            ObjTokeidai_ExteriorGear_Init(this, globalCtx);
            break;

        case OBJ_TOKEIDAI_TYPE_EXTERIOR_GEAR_CLOCK_TOWN:
            ObjTokeidai_ExteriorGear_Init(this, globalCtx);
            break;

        case OBJ_TOKEIDAI_TYPE_UNUSED_WALL:
            this->opaDList = gClockTowerUnusedTowerWallDL;
            break;

        case OBJ_TOKEIDAI_TYPE_TOWER_WALLS_TERMINA_FIELD:
            Actor_SetScale(&this->actor, 1.0f);
            this->opaDList = gClockTowerTerminaFieldWallsDL;
            this->actionFunc = ObjTokeidai_TerminaFieldWalls_Idle;
            break;

        case OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_TERMINA_FIELD:
            Actor_SetScale(&this->actor, 0.15f);
            ObjTokeidai_TowerClock_Init(this, globalCtx);
            break;

        case OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_CLOCK_TOWN:
            ObjTokeidai_TowerClock_Init(this, globalCtx);
            break;

        case OBJ_TOKEIDAI_TYPE_WALL_CLOCK:
            Actor_SetScale(&this->actor, 0.02f);
            this->actor.draw = ObjTokeidai_Clock_Draw;
            ObjTokeidai_Clock_Init(this);
            this->actionFunc = ObjTokeidai_WallClock_Idle;
            break;

        case OBJ_TOKEIDAI_TYPE_SMALL_WALL_CLOCK:
            Actor_SetScale(&this->actor, 0.01f);
            this->actor.draw = ObjTokeidai_Clock_Draw;
            ObjTokeidai_Clock_Init(this);
            this->actionFunc = ObjTokeidai_WallClock_Idle;
            break;

        case OBJ_TOKEIDAI_TYPE_COUNTERWEIGHT_TERMINA_FIELD:
            Actor_SetScale(&this->actor, 0.15f);
            ObjTokeidai_Counterweight_Init(this, globalCtx);
            break;

        case OBJ_TOKEIDAI_TYPE_COUNTERWEIGHT_CLOCK_TOWN:
            ObjTokeidai_Counterweight_Init(this, globalCtx);
            break;

        case OBJ_TOKEIDAI_TYPE_STAIRCASE_TO_ROOFTOP:
            this->opaDList = gClockTowerStaircaseToRooftopDL;
            this->xluDList = gClockTowerEmptyDL;
            this->actionFunc = ObjTokeidai_StaircaseToRooftop_Idle;
            break;
    }
}

void ObjTokeidai_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void ObjTokeidai_RotateOnMinuteChange(ObjTokeidai* this, s32 playSfx) {
    s32 currentClockMinute = GET_CURRENT_CLOCK_MINUTE(this);

    if (currentClockMinute != this->clockMinute) {
        if (this->minuteRingOrExteriorGearRotationTimer == 8 && playSfx) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CLOCK_TOWER_SECOND_HAND);
        }

        if (this->minuteRingOrExteriorGearRotationTimer > 8) {
            // This actually performs the rotation to the next minute
            // for the minute ring or exterior gear.
            this->minuteRingOrExteriorGearRotationalVelocity += 0x3C;
            this->minuteRingOrExteriorGearRotation += this->minuteRingOrExteriorGearRotationalVelocity;
        } else {
            // This makes the minute ring or exterior gear wiggle in place for a bit
            // before rotating to the next position.
            if ((this->minuteRingOrExteriorGearRotationTimer & 3) == 0) {
                this->minuteRingOrExteriorGearRotation += 0x5A;
            }
            if ((this->minuteRingOrExteriorGearRotationTimer & 3) == 1) {
                this->minuteRingOrExteriorGearRotation -= 0x5A;
            }
        }

        this->minuteRingOrExteriorGearRotationTimer++;

        if ((currentClockMinute == 15 && this->minuteRingOrExteriorGearRotation < 0) ||
            (currentClockMinute != 15 &&
             this->minuteRingOrExteriorGearRotation > GET_MINUTE_RING_OR_EXTERIOR_GEAR_ROTATION(currentClockMinute))) {
            this->minuteRingOrExteriorGearRotation = GET_MINUTE_RING_OR_EXTERIOR_GEAR_ROTATION(currentClockMinute);
            this->clockMinute = currentClockMinute;
            this->minuteRingOrExteriorGearRotationalVelocity = 0x5A;
            this->minuteRingOrExteriorGearRotationTimer = 0;
        }
    }
}

void ObjTokeidai_ExteriorGear_Collapse(ObjTokeidai* this, GlobalContext* globalCtx) {
    if ((this->actor.bgCheckFlags & 1) || this->actor.world.pos.y < 0.0f) {
        this->actionFunc = ObjTokeidai_DoNothing;
    } else {
        this->actor.shape.rot.x += 0x50;
        this->actor.shape.rot.z += 0x50;
        Actor_MoveWithGravity(&this->actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    }
}

void ObjTokeidai_ExteriorGear_OpenedIdle(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (Cutscene_CheckActorAction(globalCtx, 132) &&
        globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 132)]->action == 2) {
        this->actionFunc = ObjTokeidai_ExteriorGear_Collapse;
        this->actor.speedXZ = this->actor.scale.y * 5.0f;
        this->actor.velocity.y = 0.0f;
        this->actor.terminalVelocity = this->actor.scale.y * -50.0f;
        this->actor.gravity = this->actor.scale.y * -5.0f;
    }
}

/**
 * This, used in conjunction with the following function, makes the
 * tower's clock slide off the tower and spin through the air when the moon crashes.
 */
void ObjTokeidai_TowerClock_Fall(ObjTokeidai* this, GlobalContext* globalCtx) {
    this->actor.shape.rot.x += this->fallingClockFaceRotationalVelocity;
    if (this->fallingClockFaceRotationalVelocity > 0xA0) {
        this->fallingClockFaceRotationalVelocity -= 5;
    }

    this->actor.world.pos.z += 4.0f;
    Actor_MoveWithGravity(&this->actor);
    if (this->actor.world.pos.y < 0.0f) {
        this->actionFunc = ObjTokeidai_DoNothing;
    }
}

/**
 * This makes the tower's clock slide off as the moon crashes into it. It's
 * the tower clock's equivalent to other components' Collapse functions.
 */
void ObjTokeidai_TowerClock_SlideOff(ObjTokeidai* this, GlobalContext* globalCtx) {
    f32 cos;
    f32 sin;
    Actor* thisx = &this->actor;

    if (this->slidingClockFaceAngle < 0x4000) {
        this->slidingClockFaceAngle += 0x28;
    }
    if (this->slidingClockFaceAngle > 0x800) {
        this->aerialClockFaceSpeed += 4;
    }

    if (this->aerialClockFaceSpeed < 0x80) {
        thisx->shape.rot.x = this->slidingClockFaceAngle - 0x4000;
        this->fallingClockFaceRotationalVelocity = 0x28;
    } else {
        if (thisx->shape.rot.x < -0x1000) {
            thisx->shape.rot.x += this->fallingClockFaceRotationalVelocity;
            if (this->fallingClockFaceRotationalVelocity < 0x1E0) {
                this->fallingClockFaceRotationalVelocity += 0xA;
            }
        } else {
            thisx->shape.rot.x += this->fallingClockFaceRotationalVelocity;
            this->actionFunc = ObjTokeidai_TowerClock_Fall;
            thisx->terminalVelocity = -7.5f;
            thisx->gravity = -0.75f;
            thisx->velocity.y = -2.0f;
        }
    }

    sin = Math_SinS(this->slidingClockFaceAngle);
    cos = Math_CosS(this->slidingClockFaceAngle);
    thisx->world.pos.y = (1178.0f * cos) - (this->aerialClockFaceSpeed * sin) + thisx->home.pos.y;
    thisx->world.pos.z = (1178.0f * sin) + (this->aerialClockFaceSpeed * cos) + thisx->home.pos.z;
}

void ObjTokeidai_TowerClock_OpenedIdle(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (Cutscene_CheckActorAction(globalCtx, 132) &&
        globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 132)]->action == 1) {
        this->actionFunc = ObjTokeidai_TowerClock_SlideOff;
        this->slidingClockFaceAngle = 0;
        this->aerialClockFaceSpeed = -0xD;
    }
}

void ObjTokeidai_Counterweight_Collapse(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (this->actor.world.pos.y < 0.0f) {
        this->actionFunc = ObjTokeidai_DoNothing;
    } else {
        this->xRotation += 0x64;
        Actor_MoveWithGravity(&this->actor);
    }
}

void ObjTokeidai_Counterweight_OpenedIdle(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (Cutscene_CheckActorAction(globalCtx, 132) &&
        globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 132)]->action == 3) {
        this->actionFunc = ObjTokeidai_Counterweight_Collapse;
        this->xRotation = 0;
        this->actor.velocity.y = 0.0f;
        this->actor.terminalVelocity = this->actor.scale.y * -50.0f;
        this->actor.gravity = this->actor.scale.y * -5.0f;
    }
}

void ObjTokeidai_TerminaFieldWalls_Collapse(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (this->actor.shape.rot.x < 0x4000) {
        this->actor.shape.rot.x += 0x28;
    }
}

void ObjTokeidai_TerminaFieldWalls_Idle(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (Cutscene_CheckActorAction(globalCtx, 132) != 0 &&
        globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 132)]->action == 1) {
        this->actionFunc = ObjTokeidai_TerminaFieldWalls_Collapse;
    }
}

void ObjTokeidai_TowerOpening_EndCutscene(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (Cutscene_CheckActorAction(globalCtx, 132) != 0 &&
        globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 132)]->action == 5) {
        gSaveContext.save.weekEventReg[8] |= 0x40;
        if (((globalCtx->sceneNum == SCENE_CLOCKTOWER) && (gSaveContext.sceneSetupIndex == 2) &&
             (globalCtx->csCtx.currentCsIndex == 0)) ||
            ((globalCtx->sceneNum == SCENE_00KEIKOKU) && (gSaveContext.sceneSetupIndex == 2) &&
             (globalCtx->csCtx.currentCsIndex == 0))) {
            Audio_SetCutsceneFlag(false);
            gSaveContext.save.cutscene = 0;
            gSaveContext.nextCutsceneIndex = 0;
            gSaveContext.respawnFlag = 2;
            globalCtx->sceneLoadFlag = 0x14;
            globalCtx->nextEntranceIndex = gSaveContext.respawn[RESTART_MODE_RETURN].entranceIndex;
            globalCtx->unk_1887F = 2;
            if (gSaveContext.respawn[RESTART_MODE_RETURN].playerParams == 0xCFF) {
                gSaveContext.nextTransition = 0x15;
            } else {
                gSaveContext.nextTransition = 2;
            }
        }
        this->actionFunc = ObjTokeidai_DoNothing;
    }
}

void ObjTokeidai_TowerOpening_FinishOpening(ObjTokeidai* this, GlobalContext* globalCtx) {
    s32 type;

    if (this->clockFaceZTranslation > -320) {
        // Recess the clock face before ending the cutscene, since the Termina
        // Field version of the cutscene looks right at it.
        this->clockFaceZTranslation -= 10;
    } else {
        type = OBJ_TOKEIDAI_TYPE(&this->actor);
        if ((type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_CLOCK_TOWN) ||
            (type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_TERMINA_FIELD)) {
            ObjTokeidai_TowerOpening_EndCutscene(this, globalCtx);
        } else {
            this->actionFunc = ObjTokeidai_DoNothing;
            if (this->actor.child != NULL) {
                this->actor.child->home.rot.x = 0;
            }
        }
    }
}

void ObjTokeidai_TowerOpening_Wait(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (this->openingWaitTimer > 0) {
        this->openingWaitTimer--;
    } else {
        this->actionFunc = ObjTokeidai_TowerOpening_FinishOpening;
        this->openingWaitTimer = 0;
    }
}

void ObjTokeidai_TowerOpening_DropCounterweight(ObjTokeidai* this, GlobalContext* globalCtx) {
    this->xRotation += this->counterweightRotationalVelocity;
    if (this->xRotation < 0x4000) {
        this->counterweightRotationalVelocity += this->counterweightRotationalAcceleration;
        return;
    }

    this->counterweightRotationalAcceleration = 0x14;
    this->xRotation = 0x4000;
    switch (this->boundCount) {
        case 0:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CLOCK_TOWER_BOUND_0);
            break;

        case 1:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CLOCK_TOWER_BOUND_1);
            break;

        case 2:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CLOCK_TOWER_BOUND_2);
            break;
    }
    this->boundCount++;

    if (this->counterweightRotationalVelocity > 0x190) {
        // This condition is met for the first bound, causing the counterweight
        // to rebound upwards quickly.
        this->counterweightRotationalVelocity = -0xC8;
    } else if (this->counterweightRotationalVelocity > 0x32) {
        // This condition is met for the second bound, causing the counterweight
        // to rebound upwards slowly.
        this->counterweightRotationalVelocity = -(this->counterweightRotationalVelocity >> 1);
    } else {
        // This condition is met for the third bound, causing the counterweight
        // to stop moving.
        this->actionFunc = ObjTokeidai_TowerOpening_Wait;
        this->openingWaitTimer = 10;
    }
}

void ObjTokeidai_TowerOpening_FinishRaise(ObjTokeidai* this, GlobalContext* globalCtx) {
    s32 type;

    if (this->settleTimer > 0) {
        // Jiggle the parts of the tower up and down to give it the appearance
        // of "settling" into place.
        if (this->settleTimer & 1) {
            this->yTranslation = this->settleAmount + 3400;
        } else {
            this->yTranslation = 3400 - this->settleAmount;
            if (this->settleAmount > 0) {
                this->settleAmount -= 4;
            }
        }
        this->settleTimer--;
    } else {
        type = OBJ_TOKEIDAI_TYPE(&this->actor);
        if ((type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_CLOCK_TOWN) ||
            (type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_TERMINA_FIELD)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CLOCK_TOWER_FALL);
        }
        this->yTranslation = 3400;
        this->actionFunc = ObjTokeidai_TowerOpening_DropCounterweight;
        this->counterweightRotationalVelocity = 0;
        this->counterweightRotationalAcceleration = 0xA;
        this->boundCount = 0;
    }
}

void ObjTokeidai_TowerOpening_RaiseTower(ObjTokeidai* this, GlobalContext* globalCtx) {
    s32 type;

    if (this->yTranslation < 3400) {
        type = OBJ_TOKEIDAI_TYPE(&this->actor);
        this->yTranslation += 25;
        if ((type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_CLOCK_TOWN) ||
            (type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_TERMINA_FIELD)) {
            func_800B9010(&this->actor, NA_SE_EV_CLOCK_TOWER_UP - SFX_FLAG);
        }
    } else {
        type = OBJ_TOKEIDAI_TYPE(&this->actor);
        if ((type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_CLOCK_TOWN) ||
            (type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_TERMINA_FIELD)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CLOCK_TOWER_STOP);
        }
        this->yTranslation = 3400;
        this->actionFunc = ObjTokeidai_TowerOpening_FinishRaise;
        this->settleTimer = 10;
        this->settleAmount = 20;
    }
}

void ObjTokeidai_TowerOpening_Start(ObjTokeidai* this, GlobalContext* globalCtx) {
    if ((Cutscene_CheckActorAction(globalCtx, 132) &&
         globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 132)]->action == 4) ||
        (gSaveContext.save.weekEventReg[8] & 0x40)) {
        this->actionFunc = ObjTokeidai_TowerOpening_RaiseTower;
    }
}

/**
 * Sets up the sequence where the Clock Tower opens up
 * on the midnight of the Final Day.
 */
void ObjTokeidai_SetupTowerOpening(ObjTokeidai* this) {
    this->actionFunc = ObjTokeidai_TowerOpening_Start;
    this->clockFaceRotationalVelocity = 0;
    this->clockFaceRotationTimer = 0;
    this->yTranslation = 0;
    this->xRotation = 0;
    this->clockFaceZTranslation = 0;
}

void ObjTokeidai_DoNothing(ObjTokeidai* this, GlobalContext* globalCtx) {
}

void ObjTokeidai_StaircaseToRooftop_Idle(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (((CURRENT_DAY == 3 && gSaveContext.save.time < CLOCK_TIME(6, 0)) || CURRENT_DAY >= 4) ||
        (gSaveContext.save.weekEventReg[8] & 0x40)) {
        this->actor.draw = ObjTokeidai_Draw;
    } else {
        this->actor.draw = NULL;
    }
}

s32 ObjTokeidai_IsPostFirstCycleFinalHours(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (gSaveContext.save.inventory.items[SLOT_OCARINA] == ITEM_NONE) {
        return false;
    }
    if (CURRENT_DAY == 3 && gSaveContext.save.time < CLOCK_TIME(6, 0)) {
        ObjTokeidai_SetupTowerOpening(this);
        return true;
    }
    return false;
}

void ObjTokeidai_RotateOnHourChange(ObjTokeidai* this, GlobalContext* globalCtx) {
    s32 currentClockHour = GET_CURRENT_CLOCK_HOUR(this);

    if (currentClockHour != this->clockHour) {
        if (this->clockFaceRotationTimer > 12) {
            // This actually performs the rotation to the next hour
            // for the clock face.
            this->clockFaceRotationalVelocity += 0xA;
            this->clockFaceRotation += this->clockFaceRotationalVelocity;
        } else {
            // This makes the clock face wiggle in place for a bit
            // before rotating to the next position.
            if ((this->clockFaceRotationTimer & 3) == 0) {
                this->clockFaceRotation += 0x3C;
            }
            if ((this->clockFaceRotationTimer & 3) == 1) {
                this->clockFaceRotation -= 0x3C;
            }
        }

        this->clockFaceRotationTimer++;

        if ((currentClockHour == 12 && this->clockFaceRotation < 0) ||
            (currentClockHour != 12 && this->clockFaceRotation > GET_CLOCK_FACE_ROTATION(currentClockHour))) {
            this->clockFaceRotation = GET_CLOCK_FACE_ROTATION(currentClockHour);
            this->clockHour = currentClockHour;
            this->clockFaceRotationalVelocity = 0;
            this->clockFaceRotationTimer = 0;
        }
    }

    // If the sun and moon panel doesn't have the target rotation (e.g., the time of day
    // just changed), rotate it until it matches the target.
    if (this->sunMoonPanelRotation != ObjTokeidai_GetTargetSunMoonPanelRotation()) {
        if (this->clockHour == 6) {
            this->sunMoonPanelRotationalVelocity += 0x222;
            this->sunMoonPanelRotation += this->sunMoonPanelRotationalVelocity;
            if (this->sunMoonPanelRotation > 0x10000) {
                this->sunMoonPanelRotation = ObjTokeidai_GetTargetSunMoonPanelRotation();
                this->sunMoonPanelRotationalVelocity = 0;
            }
        }
        if (this->clockHour == 18) {
            this->sunMoonPanelRotationalVelocity += 0x222;
            this->sunMoonPanelRotation += this->sunMoonPanelRotationalVelocity;
            if (this->sunMoonPanelRotation > 0x8000) {
                this->sunMoonPanelRotation = ObjTokeidai_GetTargetSunMoonPanelRotation();
                this->sunMoonPanelRotationalVelocity = 0;
            }
        }
    }
}

void ObjTokeidai_TowerClock_Idle(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (CURRENT_DAY == 3 && this->clockHour < 6 && gSaveContext.save.time < CLOCK_TIME(6, 0)) {
        this->actor.draw = ObjTokeidai_Clock_Draw;
        ObjTokeidai_SetupTowerOpening(this);
        gSaveContext.save.weekEventReg[8] |= 0x40;
        return;
    }

    if (globalCtx->csCtx.state != 0) {
        this->actor.home.rot.x = 1;
        this->clockTime += 3;
        this->actor.draw = ObjTokeidai_Clock_Draw;
    } else {
        if (!(globalCtx->actorCtx.unk5 & 2) &&
            OBJ_TOKEIDAI_TYPE(&this->actor) == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_TERMINA_FIELD &&
            ActorCutscene_GetCurrentIndex() == -1) {
            this->actor.draw = NULL;
        }
        this->clockTime = gSaveContext.save.time;
        if (this->actor.home.rot.x != 0) {
            ObjTokeidai_Clock_Init(this);
            this->actor.home.rot.x = 0;
        }
    }

    if (CURRENT_DAY != 3 || gSaveContext.save.time >= CLOCK_TIME(6, 0)) {
        ObjTokeidai_RotateOnMinuteChange(this, true);
    }
    ObjTokeidai_RotateOnHourChange(this, globalCtx);
}

void ObjTokeidai_WallClock_Idle(ObjTokeidai* this, GlobalContext* globalCtx) {
    this->clockTime = gSaveContext.save.time;
    ObjTokeidai_RotateOnMinuteChange(this, true);
    ObjTokeidai_RotateOnHourChange(this, globalCtx);
}

void ObjTokeidai_ExteriorGear_Idle(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (ObjTokeidai_IsPostFirstCycleFinalHours(this, globalCtx)) {
        this->actor.draw = ObjTokeidai_ExteriorGear_Draw;
    } else {
        if (globalCtx->csCtx.state != 0) {
            this->actor.home.rot.x = 1;
            this->clockTime += 3;
            this->actor.draw = ObjTokeidai_ExteriorGear_Draw;
        } else {
            if ((globalCtx->actorCtx.unk5 & 2) == 0 &&
                OBJ_TOKEIDAI_TYPE(&this->actor) == OBJ_TOKEIDAI_TYPE_EXTERIOR_GEAR_TERMINA_FIELD &&
                ActorCutscene_GetCurrentIndex() == -1) {
                this->actor.draw = NULL;
            }
            this->clockTime = gSaveContext.save.time;
            if (this->actor.home.rot.x != 0) {
                ObjTokeidai_SetupClockOrExteriorGear(this);
                this->actor.home.rot.x = 0;
            }
        }
        ObjTokeidai_RotateOnMinuteChange(this, false);
    }
}

void ObjTokeidai_Counterweight_Idle(ObjTokeidai* this, GlobalContext* globalCtx) {
    s32 type;

    if (ObjTokeidai_IsPostFirstCycleFinalHours(this, globalCtx)) {
        this->spotlightIntensity = 0;

        if (this->actor.child == NULL) {
            type = OBJ_TOKEIDAI_TYPE(&this->actor);
            if (type == OBJ_TOKEIDAI_TYPE_COUNTERWEIGHT_CLOCK_TOWN ||
                type == OBJ_TOKEIDAI_TYPE_COUNTERWEIGHT_TERMINA_FIELD) {
                this->actor.child =
                    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_HANABI, this->actor.world.pos.x,
                                this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 0);
            }
        }

        if (this->actor.child != NULL) {
            if (OBJ_TOKEIDAI_TYPE(&this->actor) == OBJ_TOKEIDAI_TYPE_COUNTERWEIGHT_TERMINA_FIELD) {
                this->actor.child->home.rot.x = 0x384;
            } else {
                this->actor.child->home.rot.x = 0x12C;
            }
        }
    } else {
        this->actor.shape.rot.y -= 0x40;
        if (gSaveContext.save.isNight) {
            if (this->spotlightIntensity < 100) {
                this->spotlightIntensity += 4;
            }
        } else if (this->spotlightIntensity > 0) {
            this->spotlightIntensity -= 4;
        }
    }
}

void ObjTokeidai_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjTokeidai* this = THIS;
    this->actionFunc(this, globalCtx);
}

/**
 * Used for TerminaFieldWalls StaircaseToRooftop, and UnusedWall
 */
void ObjTokeidai_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjTokeidai* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (this->opaDList != NULL) {
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        func_8012C28C(globalCtx->state.gfxCtx);
        gSPDisplayList(POLY_OPA_DISP++, this->opaDList);
    }

    if (this->xluDList != NULL) {
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        func_8012C2DC(globalCtx->state.gfxCtx);
        gSPDisplayList(POLY_XLU_DISP++, this->xluDList);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void ObjTokeidai_Clock_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjTokeidai* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    Matrix_InsertTranslation(0.0f, this->yTranslation, 0.0f, MTXMODE_APPLY);
    Matrix_InsertTranslation(0.0f, 0.0f, -1791.0f, MTXMODE_APPLY);
    Matrix_InsertXRotation_s(-this->xRotation, MTXMODE_APPLY);
    Matrix_InsertTranslation(0.0f, 0.0f, 1791.0f, MTXMODE_APPLY);

    Matrix_StatePush();
    Matrix_InsertZRotation_s(-this->minuteRingOrExteriorGearRotation, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gClockTowerMinuteRingDL);
    Matrix_StatePop();

    Matrix_InsertTranslation(0.0f, 0.0f, this->clockFaceZTranslation, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gClockTowerClockCenterAndHandDL);

    Matrix_InsertZRotation_s(-this->clockFaceRotation * 2, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (OBJ_TOKEIDAI_TYPE(&this->actor) == OBJ_TOKEIDAI_TYPE_WALL_CLOCK ||
        OBJ_TOKEIDAI_TYPE(&this->actor) == OBJ_TOKEIDAI_TYPE_SMALL_WALL_CLOCK) {
        gSPDisplayList(POLY_OPA_DISP++, gWallClockClockFace);
    } else {
        gSPDisplayList(POLY_OPA_DISP++, gClockTowerClockFace);
    }

    Matrix_InsertTranslation(0.0f, -1112.0f, -19.6f, MTXMODE_APPLY);
    Matrix_RotateY((s16)this->sunMoonPanelRotation, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gClockTowerSunAndMoonPanelDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void ObjTokeidai_Counterweight_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    u32 gameplayFrames = globalCtx->gameplayFrames;
    ObjTokeidai* this = THIS;

    Matrix_RotateY(-this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_InsertTranslation(0.0f, this->yTranslation, 0.0f, MTXMODE_APPLY);
    Matrix_InsertTranslation(0.0f, -5480.0f, 80.0f, MTXMODE_APPLY);
    Matrix_InsertXRotation_s(-this->xRotation, MTXMODE_APPLY);
    Matrix_InsertTranslation(0.0f, 5480.0f, -80.0f, MTXMODE_APPLY);
    Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_APPLY);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    // For scrolling the spotlight's mask texture down the length of the light beam.
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, -gameplayFrames, 0, 0x20, 0x20));

    // Draws the counterweight
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPDisplayList(POLY_OPA_DISP++, this->opaDList);

    // Draws the spotlight
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C2DC(globalCtx->state.gfxCtx);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 255, 255, 235, 180, (s32)(this->spotlightIntensity * 2.55f));
    gSPDisplayList(POLY_XLU_DISP++, this->xluDList);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void ObjTokeidai_ExteriorGear_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjTokeidai* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_InsertTranslation(0.0f, this->yTranslation, 0.0f, MTXMODE_APPLY);
    Matrix_InsertTranslation(0.0f, 0.0f, -1791.0f, MTXMODE_APPLY);
    Matrix_RotateY(-this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_InsertXRotation_s(-this->xRotation, MTXMODE_APPLY);
    Matrix_RotateY(thisx->shape.rot.y, MTXMODE_APPLY);
    Matrix_InsertTranslation(0.0f, 0.0f, 1791.0f, MTXMODE_APPLY);
    Matrix_InsertZRotation_s(this->minuteRingOrExteriorGearRotation, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPDisplayList(POLY_OPA_DISP++, gClockTowerExteriorGearDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
