/*
 * File: z_obj_tokeidai.c
 * Overlay: ovl_Obj_Tokeidai
 * Description: Components of the Clock Tower (gears, clock face, counterweight, etc). Also used for wall clocks.
 */

#include "z_obj_tokeidai.h"

#define FLAGS 0x00000030

#define THIS ((ObjTokeidai*)thisx)

void ObjTokeidai_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_Draw(Actor* thisx, GlobalContext* globalCtx);

void ObjTokeidai_DoNothing(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_TowerClock_TransformedIdle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_TowerGear_TransformedIdle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_Counterweight_TransformedIdle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_TowerClock_Idle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_WallClock_Idle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_TowerGear_Idle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_Counterweight_Idle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_Walls_Idle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_StaircaseIntoTower_Idle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_SetupTowerTransformation(ObjTokeidai* this);
void ObjTokeidai_Clock_Draw(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_Counterweight_Draw(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_TowerGear_Draw(Actor* thisx, GlobalContext* globalCtx);

// Used for regular clock functions
#define clockFaceRotationalVelocity actionVar1
#define clockFaceRotationTimer actionVar2
#define sunMoonDiskRotationalVelocity actionVar3
#define clockHour actionVar4

// Used for regular counterweight functions
#define spotlightIntensity actionVar4

// Used in ObjTokeidai_TowerTransformation_FinishRaise
#define settleTimer actionVar1
#define settleAmount actionVar2

// Used in ObjTokeidai_TowerTransformation_DropCounterweight
#define transformationRotationalVelocity actionVar1
#define transformationRotationalAcceleration actionVar2

// Used in ObjTokeidai_TowerTransformation_Wait
#define transformationWaitTimer actionVar1

// Used in ObjTokeidai_TowerClock_SlideOff and ObjTokeidai_TowerClock_Fall
#define slidingClockFaceAngle actionVar1
#define aerialClockFaceSpeed actionVar2
#define fallingClockFaceRotationalVelocity actionVar3

const ActorInit Obj_Tokeidai_InitVars = {
    ACTOR_OBJ_TOKEIDAI,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_OBJECT_UNSET_TOKEIDAI,
    sizeof(ObjTokeidai),
    (ActorFunc)ObjTokeidai_Init,
    (ActorFunc)ObjTokeidai_Destroy,
    (ActorFunc)ObjTokeidai_Update,
    (ActorFunc)ObjTokeidai_Draw,
};

// static InitChainEntry sInitChain
static InitChainEntry D_80AB49E0[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 3300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1100, ICHAIN_STOP),
};

extern Gfx D_06009A08[]; // the tower's four walls, used in Termina Field
extern Gfx D_0600B0C0[]; // spotlight emitted from the counterweight at night
extern Gfx D_0600B208[]; // the tower's counterweight
extern Gfx D_0600BA78[]; // rotating gear on the side of the tower
extern Gfx D_0600BEE8[]; // clock center and "hand"
extern Gfx D_0600C368[]; // sun and moon disk
extern Gfx D_0600CF28[]; // outer ring of the clock face
extern Gfx D_0600D388[]; // unused tower wall
extern Gfx D_0600D8E0[]; // empty dlist
extern Gfx D_0600D8E8[]; // spiral staircase to tower interior
extern Gfx D_0600E818[]; // clock tower clock face
extern Gfx D_0600F518[]; // wall clock clock face

/**
 * Returns the angle necessary to show the correct side of
 * the sun and moon disk based on the time of day. The actual
 * angle can differ from the target angle if the disk is in
 * the middle of rotating.
 */
s32 ObjTokeidai_GetTargetSunMoonDiskRotation() {
    if (gSaveContext.isNight) {
        return 0x8000;
    }
    return 0;
}

void ObjTokeidai_SetupClockOrGear(ObjTokeidai* this) {
    s32 currentMinute;

    currentMinute = OBJ_TOKEIDAI_GET_CURRENT_MINUTE(this);
    this->clockMinute = currentMinute;
    this->outerRingOrGearRotation = OBJ_TOKEIDAI_GET_OUTER_RING_OR_GEAR_ROTATION(currentMinute);
    this->outerRingOrGearRotationalVelocity = 0x3C;
    this->outerRingOrGearRotationTimer = 0;
}

void ObjTokeidai_Clock_Init(ObjTokeidai* this) {
    s32 currentHour;

    ObjTokeidai_SetupClockOrGear(this);
    currentHour = OBJ_TOKEIDAI_GET_CURRENT_HOUR(this);
    this->clockHour = currentHour;
    this->clockFaceRotation = OBJ_TOKEIDAI_GET_CLOCK_FACE_ROTATION(currentHour);
    this->clockFaceRotationalVelocity = 0;
    this->clockFaceRotationTimer = 0;
    this->sunMoonDiskRotationalVelocity = 0;
    this->sunMoonDiskRotation = ObjTokeidai_GetTargetSunMoonDiskRotation();
}

void ObjTokeidai_TowerGear_Init(ObjTokeidai* this, GlobalContext* globalCtx) {
    this->actor.draw = ObjTokeidai_TowerGear_Draw;
    this->opaDList = D_0600BA78;
    ObjTokeidai_SetupClockOrGear(this);

    if ((globalCtx->sceneNum == SCENE_CLOCKTOWER && gSaveContext.sceneSetupIndex == 2 &&
         globalCtx->csCtx.unk_12 == 0) ||
        (globalCtx->sceneNum == SCENE_00KEIKOKU && gSaveContext.sceneSetupIndex == 2 && globalCtx->csCtx.unk_12 == 0)) {
        ObjTokeidai_SetupTowerTransformation(this);
    } else if (OBJ_TOKEIDAI_IS_TRANSFORMED()) {
        this->actionFunc = ObjTokeidai_TowerGear_TransformedIdle;
        this->actor.world.pos.y += this->actor.scale.y * 1900.0f;
        this->actor.shape.yOffset = 1500.0f;
        gSaveContext.weekEventReg[8] |= 0x40;
    } else {
        this->actionFunc = ObjTokeidai_TowerGear_Idle;
    }
}

void ObjTokeidai_TowerClock_Init(ObjTokeidai* this, GlobalContext* globalCtx) {
    this->actor.draw = ObjTokeidai_Clock_Draw;
    ObjTokeidai_Clock_Init(this);

    if ((globalCtx->sceneNum == SCENE_CLOCKTOWER && gSaveContext.sceneSetupIndex == 2 &&
         globalCtx->csCtx.unk_12 == 0) ||
        (globalCtx->sceneNum == SCENE_00KEIKOKU && gSaveContext.sceneSetupIndex == 2 && globalCtx->csCtx.unk_12 == 0)) {
        ObjTokeidai_SetupTowerTransformation(this);
    } else if (OBJ_TOKEIDAI_IS_TRANSFORMED()) {
        this->actor.world.pos.y += (this->actor.scale.y * 5191.0f) - 50.0f;
        this->actor.world.pos.x += Math_SinS(this->actor.world.rot.y) * this->actor.scale.z * 1791.0f;
        this->actor.world.pos.z += -Math_CosS(this->actor.world.rot.y) * this->actor.scale.z * 1791.0f;
        this->clockFaceZTranslation = -0x140;
        this->actor.shape.rot.x = -0x4000;
        this->actor.home.pos = this->actor.world.pos;
        this->actor.home.pos.y -= 1178.0f;
        this->actor.home.pos.z += 13.0f;
        this->actionFunc = ObjTokeidai_TowerClock_TransformedIdle;
    } else {
        this->actionFunc = ObjTokeidai_TowerClock_Idle;
    }
}

void ObjTokeidai_Counterweight_Init(ObjTokeidai* this, GlobalContext* globalCtx) {
    s32 type;

    this->actor.draw = ObjTokeidai_Counterweight_Draw;
    this->opaDList = D_0600B208;
    this->xluDList = D_0600B0C0;
    if (gSaveContext.isNight) {
        this->spotlightIntensity = 100;
    } else {
        this->spotlightIntensity = 0;
    }

    if ((globalCtx->sceneNum == SCENE_CLOCKTOWER && gSaveContext.sceneSetupIndex == 2 &&
         globalCtx->csCtx.unk_12 == 0) ||
        (globalCtx->sceneNum == SCENE_00KEIKOKU && gSaveContext.sceneSetupIndex == 2 && globalCtx->csCtx.unk_12 == 0)) {
        this->spotlightIntensity = 0;
        ObjTokeidai_SetupTowerTransformation(this);
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
    } else if (OBJ_TOKEIDAI_IS_TRANSFORMED()) {
        this->spotlightIntensity = 0;
        this->actor.world.pos.y += this->actor.scale.y * -2160.0f;
        this->actor.world.pos.x += Math_SinS(this->actor.world.rot.y) * this->actor.scale.z * 5400.0f;
        this->actor.world.pos.z += -Math_CosS(this->actor.world.rot.y) * this->actor.scale.z * 5400.0f;
        this->actor.shape.rot.x = -0x4000;
        this->actionFunc = ObjTokeidai_Counterweight_TransformedIdle;
    } else {
        this->actionFunc = ObjTokeidai_Counterweight_Idle;
    }
}

void ObjTokeidai_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjTokeidai* this = THIS;

    Actor_ProcessInitChain(&this->actor, D_80AB49E0);
    this->actionFunc = ObjTokeidai_DoNothing;
    this->opaDList = NULL;
    this->xluDList = NULL;
    this->xRotation = 0;
    this->yTranslation = 0;
    this->clockFaceZTranslation = 0;
    this->currentTime = gSaveContext.time;
    this->actor.home.rot.x = 0;

    switch (OBJ_TOKEIDAI_TYPE(&this->actor)) {
        case OBJ_TOKEIDAI_TYPE_TOWER_GEAR_TERMINA_FIELD:
            Actor_SetScale(&this->actor, 0.15f);
            ObjTokeidai_TowerGear_Init(this, globalCtx);
            break;
        case OBJ_TOKEIDAI_TYPE_TOWER_GEAR_CLOCK_TOWN:
            ObjTokeidai_TowerGear_Init(this, globalCtx);
            break;
        case OBJ_TOKEIDAI_TYPE_UNUSED_WALL:
            this->opaDList = D_0600D388;
            break;
        case OBJ_TOKEIDAI_TYPE_TOWER_WALLS_TERMINA_FIELD:
            Actor_SetScale(&this->actor, 1.0f);
            this->opaDList = D_06009A08;
            this->actionFunc = ObjTokeidai_Walls_Idle;
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
        case OBJ_TOKEIDAI_TYPE_STAIRCASE_INTO_TOWER:
            this->opaDList = D_0600D8E8;
            this->xluDList = D_0600D8E0;
            this->actionFunc = ObjTokeidai_StaircaseIntoTower_Idle;
            break;
    }
}

void ObjTokeidai_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void ObjTokeidai_RotateOnMinuteChange(ObjTokeidai* this, s32 playSound) {
    s32 currentMinute;

    currentMinute = OBJ_TOKEIDAI_GET_CURRENT_MINUTE(this);
    if (currentMinute != this->clockMinute) {
        if (this->outerRingOrGearRotationTimer == 8 && playSound) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_CLOCK_TOWER_SECOND_HAND);
        }

        if (this->outerRingOrGearRotationTimer >= 9) {
            // This actually performs the rotation to the next minute
            // for the outer ring or gear.
            this->outerRingOrGearRotationalVelocity += 0x3C;
            this->outerRingOrGearRotation += this->outerRingOrGearRotationalVelocity;
        } else {
            // This makes the outer ring or gear wiggle in place for a bit
            // before rotating to the next position.
            if ((this->outerRingOrGearRotationTimer & 3) == 0) {
                this->outerRingOrGearRotation += 0x5A;
            }
            if ((this->outerRingOrGearRotationTimer & 3) == 1) {
                this->outerRingOrGearRotation -= 0x5A;
            }
        }

        this->outerRingOrGearRotationTimer++;
        if ((currentMinute == 15 && this->outerRingOrGearRotation < 0) ||
            (currentMinute != 15 &&
             this->outerRingOrGearRotation > OBJ_TOKEIDAI_GET_OUTER_RING_OR_GEAR_ROTATION(currentMinute))) {
            this->outerRingOrGearRotation = OBJ_TOKEIDAI_GET_OUTER_RING_OR_GEAR_ROTATION(currentMinute);
            this->clockMinute = currentMinute;
            this->outerRingOrGearRotationalVelocity = 0x5A;
            this->outerRingOrGearRotationTimer = 0;
        }
    }
}

void ObjTokeidai_TowerGear_Collapse(ObjTokeidai* this, GlobalContext* globalCtx) {
    if ((this->actor.bgCheckFlags & 1) || this->actor.world.pos.y < 0.0f) {
        this->actionFunc = ObjTokeidai_DoNothing;
    } else {
        this->actor.shape.rot.x += 0x50;
        this->actor.shape.rot.z += 0x50;
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    }
}

void ObjTokeidai_TowerGear_TransformedIdle(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (func_800EE29C(globalCtx, 0x84) && globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x84)]->unk0 == 2) {
        this->actionFunc = ObjTokeidai_TowerGear_Collapse;
        this->actor.speedXZ = this->actor.scale.y * 5.0f;
        this->actor.velocity.y = 0.0f;
        this->actor.minVelocityY = this->actor.scale.y * -50.0f;
        this->actor.gravity = this->actor.scale.y * -5.0f;
    }
}

/**
 * This doesn't seem to be used in the final game. This, used in conjunction
 * with the following function, would make the tower's clock slide off the
 * tower and spin through the air.
 */
void ObjTokeidai_TowerClock_Fall(ObjTokeidai* this, GlobalContext* globalCtx) {
    this->actor.shape.rot.x += this->fallingClockFaceRotationalVelocity;
    if (this->fallingClockFaceRotationalVelocity >= 0xA1) {
        this->fallingClockFaceRotationalVelocity -= 5;
    }
    this->actor.world.pos.z += 4.0f;
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    if (this->actor.world.pos.y < 0.0f) {
        this->actionFunc = ObjTokeidai_DoNothing;
    }
}

/**
 * This doesn't seem to be used in the final game. Presumably, this would make the
 * tower's clock slide off as the moon crashes into it.
 */
void ObjTokeidai_TowerClock_SlideOff(ObjTokeidai* this, GlobalContext* globalCtx) {
    f32 cos;
    f32 sin;
    Actor* thisx = &this->actor;

    if (this->slidingClockFaceAngle < 0x4000) {
        this->slidingClockFaceAngle += 0x28;
    }
    if (this->slidingClockFaceAngle >= 0x801) {
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
            thisx->minVelocityY = -7.5f;
            thisx->gravity = -0.75f;
            thisx->velocity.y = -2.0f;
        }
    }

    sin = Math_SinS(this->slidingClockFaceAngle);
    cos = Math_CosS(this->slidingClockFaceAngle);
    thisx->world.pos.y = (1178.0f * cos) - (this->aerialClockFaceSpeed * sin) + thisx->home.pos.y;
    thisx->world.pos.z = (1178.0f * sin) + (this->aerialClockFaceSpeed * cos) + thisx->home.pos.z;
}

void ObjTokeidai_TowerClock_TransformedIdle(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (func_800EE29C(globalCtx, 0x84) && globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x84)]->unk0 == 1) {
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
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    }
}

void ObjTokeidai_Counterweight_TransformedIdle(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (func_800EE29C(globalCtx, 0x84) && globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x84)]->unk0 == 3) {
        this->actionFunc = ObjTokeidai_Counterweight_Collapse;
        this->xRotation = 0;
        this->actor.velocity.y = 0.0f;
        this->actor.minVelocityY = this->actor.scale.y * -50.0f;
        this->actor.gravity = this->actor.scale.y * -5.0f;
    }
}

/**
 * This doesn't seem to be used in the final game. Presumably, this would make the walls of
 * the clock tower appear to buckle as the moon crashes into it.
 */
void ObjTokeidai_Walls_Collapse(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (this->actor.shape.rot.x < 0x4000) {
        this->actor.shape.rot.x += +0x28;
    }
}

void ObjTokeidai_Walls_Idle(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (func_800EE29C(globalCtx, 0x84) != 0 && globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x84)]->unk0 == 1) {
        this->actionFunc = ObjTokeidai_Walls_Collapse;
    }
}

void ObjTokeidai_TowerTransformation_EndCutscene(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (func_800EE29C(globalCtx, 0x84) != 0 && globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x84)]->unk0 == 5) {
        gSaveContext.weekEventReg[8] |= 0x40;
        if ((globalCtx->sceneNum == SCENE_CLOCKTOWER && gSaveContext.sceneSetupIndex == 2 &&
             globalCtx->csCtx.unk_12 == 0) ||
            (globalCtx->sceneNum == SCENE_00KEIKOKU && gSaveContext.sceneSetupIndex == 2 &&
             globalCtx->csCtx.unk_12 == 0)) {
            func_801A3F54(0);
            gSaveContext.cutscene = 0;
            gSaveContext.nextCutsceneIndex = 0;
            gSaveContext.respawnFlag = 2;
            globalCtx->sceneLoadFlag = 0x14;
            globalCtx->nextEntranceIndex = gSaveContext.respawn[1].entranceIndex;
            globalCtx->unk_1887F = 2;
            if (gSaveContext.respawn[1].playerParams == 0xCFF) {
                gSaveContext.nextTransition = 0x15;
            } else {
                gSaveContext.nextTransition = 2;
            }
        }
        this->actionFunc = ObjTokeidai_DoNothing;
    }
}

void ObjTokeidai_TowerTransformation_FinishTransformation(ObjTokeidai* this, GlobalContext* globalCtx) {
    s32 type;

    if (this->clockFaceZTranslation >= -0x13F) {
        // Recess the clock face before ending the cutscene, since the Termina
        // Field version of the cutscene looks right at it.
        this->clockFaceZTranslation -= 0xA;
    } else {
        type = OBJ_TOKEIDAI_TYPE(&this->actor);
        if ((type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_CLOCK_TOWN) ||
            (type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_TERMINA_FIELD)) {
            ObjTokeidai_TowerTransformation_EndCutscene(this, globalCtx);
        } else {
            this->actionFunc = ObjTokeidai_DoNothing;
            if (this->actor.child != NULL) {
                this->actor.child->home.rot.x = 0;
            }
        }
    }
}

void ObjTokeidai_TowerTransformation_Wait(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (this->transformationWaitTimer > 0) {
        this->transformationWaitTimer--;
    } else {
        this->actionFunc = ObjTokeidai_TowerTransformation_FinishTransformation;
        this->transformationWaitTimer = 0;
    }
}

void ObjTokeidai_TowerTransformation_DropCounterweight(ObjTokeidai* this, GlobalContext* globalCtx) {
    this->xRotation += this->transformationRotationalVelocity;
    if (this->xRotation < 0x4000) {
        this->transformationRotationalVelocity += this->transformationRotationalAcceleration;
        return;
    }

    this->transformationRotationalAcceleration = 0x14;
    this->xRotation = 0x4000;
    switch (this->boundCount) {
        case 0:
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_CLOCK_TOWER_BOUND_0);
            break;
        case 1:
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_CLOCK_TOWER_BOUND_1);
            break;
        case 2:
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_CLOCK_TOWER_BOUND_2);
            break;
    }
    this->boundCount++;

    if (this->transformationRotationalVelocity >= 0x191) {
        // This condition is met for the first bound, causing the counterweight
        // to rebound upwards quickly.
        this->transformationRotationalVelocity = -0xC8;
    } else if (this->transformationRotationalVelocity >= 0x33) {
        // This condition is met for the second bound, causing the counterweight
        // to rebound upwards slowly.
        this->transformationRotationalVelocity = -(this->transformationRotationalVelocity >> 1);
    } else {
        // This condition is met for the third bound, causing the counterweight
        // to stop moving.
        this->actionFunc = ObjTokeidai_TowerTransformation_Wait;
        this->transformationWaitTimer = 10;
    }
}

void ObjTokeidai_TowerTransformation_FinishRaise(ObjTokeidai* this, GlobalContext* globalCtx) {
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
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_CLOCK_TOWER_FALL);
        }
        this->yTranslation = 3400;
        this->actionFunc = ObjTokeidai_TowerTransformation_DropCounterweight;
        this->transformationRotationalVelocity = 0;
        this->transformationRotationalAcceleration = 0xA;
        this->boundCount = 0;
    }
}

void ObjTokeidai_TowerTransformation_RaiseTower(ObjTokeidai* this, GlobalContext* globalCtx) {
    s32 type;

    if (this->yTranslation < 3400) {
        type = OBJ_TOKEIDAI_TYPE(&this->actor);
        this->yTranslation += 0x19;
        if ((type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_CLOCK_TOWN) ||
            (type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_TERMINA_FIELD)) {
            func_800B9010(&this->actor, NA_SE_EV_CLOCK_TOWER_UP - SFX_FLAG);
        }
    } else {
        type = OBJ_TOKEIDAI_TYPE(&this->actor);
        if ((type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_CLOCK_TOWN) ||
            (type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_TERMINA_FIELD)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_CLOCK_TOWER_STOP);
        }
        this->yTranslation = 3400;
        this->actionFunc = ObjTokeidai_TowerTransformation_FinishRaise;
        this->settleTimer = 10;
        this->settleAmount = 20;
    }
}

void ObjTokeidai_TowerTransformation_Start(ObjTokeidai* this, GlobalContext* globalCtx) {
    if ((func_800EE29C(globalCtx, 0x84) && globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x84)]->unk0 == 4) ||
        (gSaveContext.weekEventReg[8] & 0x40)) {
        this->actionFunc = ObjTokeidai_TowerTransformation_RaiseTower;
    }
}

void ObjTokeidai_SetupTowerTransformation(ObjTokeidai* this) {
    this->actionFunc = ObjTokeidai_TowerTransformation_Start;
    this->clockFaceRotationalVelocity = 0;
    this->clockFaceRotationTimer = 0;
    this->yTranslation = 0;
    this->xRotation = 0;
    this->clockFaceZTranslation = 0;
}

void ObjTokeidai_DoNothing(ObjTokeidai* this, GlobalContext* globalCtx) {
}

void ObjTokeidai_StaircaseIntoTower_Idle(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (OBJ_TOKEIDAI_IS_TRANSFORMED() || (gSaveContext.weekEventReg[8] & 0x40)) {
        this->actor.draw = ObjTokeidai_Draw;
    } else {
        this->actor.draw = NULL;
    }
}

s32 ObjTokeidai_IsPostFirstCycleFinalHours(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (gSaveContext.inventory.items[0] == 0xFF) {
        return false;
    }
    if (gSaveContext.day % 5 == 3 && gSaveContext.time < CLOCK_TIME(6, 0)) {
        ObjTokeidai_SetupTowerTransformation(this);
        return true;
    }
    return false;
}

void ObjTokeidai_RotateOnHourChange(ObjTokeidai* this, GlobalContext* globalCtx) {
    s32 currentHour;

    currentHour = OBJ_TOKEIDAI_GET_CURRENT_HOUR(this);
    if (currentHour != this->clockHour) {
        if (this->clockFaceRotationTimer >= 13) {
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
        if ((currentHour == 12 && this->clockFaceRotation < 0) ||
            (currentHour != 12 && this->clockFaceRotation > OBJ_TOKEIDAI_GET_CLOCK_FACE_ROTATION(currentHour))) {
            this->clockFaceRotation = OBJ_TOKEIDAI_GET_CLOCK_FACE_ROTATION(currentHour);
            this->clockHour = currentHour;
            this->clockFaceRotationalVelocity = 0;
            this->clockFaceRotationTimer = 0;
        }
    }

    // If the sun and moon disk doesn't have the target rotation (e.g., the time of day
    // just changed), rotate it until it matches the target.
    if (this->sunMoonDiskRotation != ObjTokeidai_GetTargetSunMoonDiskRotation()) {
        if (this->clockHour == 6) {
            this->sunMoonDiskRotationalVelocity += 0x222;
            this->sunMoonDiskRotation += this->sunMoonDiskRotationalVelocity;
            if (this->sunMoonDiskRotation >= 0x10001) {
                this->sunMoonDiskRotation = ObjTokeidai_GetTargetSunMoonDiskRotation();
                this->sunMoonDiskRotationalVelocity = 0;
            }
        }
        if (this->clockHour == 18) {
            this->sunMoonDiskRotationalVelocity += 0x222;
            this->sunMoonDiskRotation += this->sunMoonDiskRotationalVelocity;
            if (this->sunMoonDiskRotation >= 0x8001) {
                this->sunMoonDiskRotation = ObjTokeidai_GetTargetSunMoonDiskRotation();
                this->sunMoonDiskRotationalVelocity = 0;
            }
        }
    }
}

void ObjTokeidai_TowerClock_Idle(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (gSaveContext.day % 5 == 3 && this->clockHour < 6 && gSaveContext.time < CLOCK_TIME(6, 0)) {
        this->actor.draw = ObjTokeidai_Clock_Draw;
        ObjTokeidai_SetupTowerTransformation(this);
        gSaveContext.weekEventReg[8] |= 0x40;
        return;
    }

    if (globalCtx->csCtx.state != 0) {
        this->actor.home.rot.x = 1;
        this->currentTime += 3;
        this->actor.draw = ObjTokeidai_Clock_Draw;
    } else {
        if ((globalCtx->actorCtx.unk5 & 2) == 0 &&
            OBJ_TOKEIDAI_TYPE(&this->actor) == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_TERMINA_FIELD &&
            ActorCutscene_GetCurrentIndex() == -1) {
            this->actor.draw = NULL;
        }
        this->currentTime = gSaveContext.time;
        if (this->actor.home.rot.x != 0) {
            ObjTokeidai_Clock_Init(this);
            this->actor.home.rot.x = 0;
        }
    }

    if (gSaveContext.day % 5 != 3 || gSaveContext.time >= CLOCK_TIME(6, 0)) {
        ObjTokeidai_RotateOnMinuteChange(this, true);
    }
    ObjTokeidai_RotateOnHourChange(this, globalCtx);
}

void ObjTokeidai_WallClock_Idle(ObjTokeidai* this, GlobalContext* globalCtx) {
    this->currentTime = gSaveContext.time;
    ObjTokeidai_RotateOnMinuteChange(this, true);
    ObjTokeidai_RotateOnHourChange(this, globalCtx);
}

void ObjTokeidai_TowerGear_Idle(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (ObjTokeidai_IsPostFirstCycleFinalHours(this, globalCtx)) {
        this->actor.draw = ObjTokeidai_TowerGear_Draw;
    } else {
        if (globalCtx->csCtx.state != 0) {
            this->actor.home.rot.x = 1;
            this->currentTime += 3;
            this->actor.draw = ObjTokeidai_TowerGear_Draw;
        } else {
            if ((globalCtx->actorCtx.unk5 & 2) == 0 &&
                OBJ_TOKEIDAI_TYPE(&this->actor) == OBJ_TOKEIDAI_TYPE_TOWER_GEAR_TERMINA_FIELD &&
                ActorCutscene_GetCurrentIndex() == -1) {
                this->actor.draw = NULL;
            }
            this->currentTime = gSaveContext.time;
            if (this->actor.home.rot.x != 0) {
                ObjTokeidai_SetupClockOrGear(this);
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
        if (gSaveContext.isNight != 0) {
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

void ObjTokeidai_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjTokeidai* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (this->opaDList != 0) {
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        func_8012C28C(globalCtx->state.gfxCtx);
        gSPDisplayList(POLY_OPA_DISP++, this->opaDList);
    }
    if (this->xluDList != 0) {
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
    Matrix_InsertZRotation_s(-this->outerRingOrGearRotation, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_0600CF28);
    Matrix_StatePop();
    Matrix_InsertTranslation(0.0f, 0.0f, this->clockFaceZTranslation, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_0600BEE8);
    Matrix_InsertZRotation_s(-this->clockFaceRotation * 2, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (OBJ_TOKEIDAI_TYPE(&this->actor) == OBJ_TOKEIDAI_TYPE_WALL_CLOCK ||
        OBJ_TOKEIDAI_TYPE(&this->actor) == OBJ_TOKEIDAI_TYPE_SMALL_WALL_CLOCK) {
        gSPDisplayList(POLY_OPA_DISP++, D_0600F518);
    } else {
        gSPDisplayList(POLY_OPA_DISP++, D_0600E818);
    }
    Matrix_InsertTranslation(0.0f, -1112.0f, -19.6f, 1);
    Matrix_RotateY((s16)this->sunMoonDiskRotation, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_0600C368);

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

    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, -gameplayFrames, 0, 0x20, 0x20));
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPDisplayList(POLY_OPA_DISP++, this->opaDList);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C2DC(globalCtx->state.gfxCtx);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 255, 255, 235, 180, (s32)(this->spotlightIntensity * 2.55f));
    gSPDisplayList(POLY_XLU_DISP++, this->xluDList);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void ObjTokeidai_TowerGear_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjTokeidai* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_InsertTranslation(0.0f, this->yTranslation, 0.0f, MTXMODE_APPLY);
    Matrix_InsertTranslation(0.0f, 0.0f, -1791.0f, MTXMODE_APPLY);
    Matrix_RotateY(-this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_InsertXRotation_s(-this->xRotation, MTXMODE_APPLY);
    Matrix_RotateY(thisx->shape.rot.y, MTXMODE_APPLY);
    Matrix_InsertTranslation(0.0f, 0.0f, 1791.0f, MTXMODE_APPLY);
    Matrix_InsertZRotation_s(this->outerRingOrGearRotation, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPDisplayList(POLY_OPA_DISP++, D_0600BA78);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
