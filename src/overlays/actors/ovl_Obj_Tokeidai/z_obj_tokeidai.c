/*
 * File: z_obj_tokeidai.c
 * Overlay: ovl_Obj_Tokeidai
 * Description: Clock Face
 */

#include "z_obj_tokeidai.h"

#define FLAGS 0x00000030

#define THIS ((ObjTokeidai*)thisx)

void ObjTokeidai_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_Draw(Actor* thisx, GlobalContext* globalCtx);

void ObjTokeidai_CollapseGear(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_TransformedGearIdle(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB32F0(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3370(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_TransformedClockIdle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_CollapseTop(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_TransformedTopIdle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_CollapseWalls(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_WallsIdle(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_TowerTransformationFinish(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_TowerTransformationWait(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_TowerTopFall(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_TowerRaiseFinished(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_RaiseTower(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_TowerTransformationStart(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_DoNothing(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_StaircaseIntoTowerIdle(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3ED0(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB4040(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB4080(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB4160(ObjTokeidai* this, GlobalContext* globalCtx);
void ObjTokeidai_SetupTowerTransformationStart(ObjTokeidai* this);
void ObjTokeidai_DrawClock(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_DrawTowerTop(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_DrawTowerGear(Actor* thisx, GlobalContext* globalCtx);

// Silly overload defines that I'm not sure I should even be doing
#define settleTimer clockFaceAdditionalRotation
#define unk_154 clockFaceAdditionalRotation
#define settleAmount clockFaceRotationTimer
#define unk_156 clockFaceRotationTimer
#define unk_15C sunMoonDiskAdditionalRotation
#define lightIntensity clockHour

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

extern Gfx D_06009A08[]; // central part of the tower
extern Gfx D_0600B0C0[]; // light beam
extern Gfx D_0600B208[]; // thing at the top of the tower
extern Gfx D_0600BA78[]; // gear on the side of the tower
extern Gfx D_0600BEE8[]; // clock center and "hand"
extern Gfx D_0600C368[]; // sun and moon circle
extern Gfx D_0600CF28[]; // outer ring of the clock face
extern Gfx D_0600D388[]; // tower base?
extern Gfx D_0600D8E0[]; // empty dlist
extern Gfx D_0600D8E8[]; // spiral staircase to tower interior
extern Gfx D_0600E818[]; // clock tower clock face
extern Gfx D_0600F518[]; // small and very small clock face

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
    this->outerRingOrGearAdditionalRotation = 0x3C;
    this->outerRingOrGearRotationTimer = 0;
}

void ObjTokeidai_InitClock(ObjTokeidai* this) {
    s32 currentHour;

    ObjTokeidai_SetupClockOrGear(this);
    currentHour = OBJ_TOKEIDAI_GET_CURRENT_HOUR(this);
    this->clockHour = currentHour;
    this->clockFaceRotation = OBJ_TOKEIDAI_GET_CLOCK_FACE_ROTATION(currentHour);
    this->clockFaceAdditionalRotation = 0;
    this->clockFaceRotationTimer = 0;
    this->sunMoonDiskAdditionalRotation = 0;
    this->sunMoonDiskRotation = ObjTokeidai_GetTargetSunMoonDiskRotation();
}

void ObjTokeidai_InitTowerGear(ObjTokeidai* this, GlobalContext* globalCtx) {
    this->actor.draw = ObjTokeidai_DrawTowerGear;
    this->opaDList = D_0600BA78;
    ObjTokeidai_SetupClockOrGear(this);
    if ((globalCtx->sceneNum == SCENE_CLOCKTOWER && gSaveContext.sceneSetupIndex == 2 &&
         globalCtx->csCtx.unk_12 == 0) ||
        (globalCtx->sceneNum == SCENE_00KEIKOKU && gSaveContext.sceneSetupIndex == 2 && globalCtx->csCtx.unk_12 == 0)) {
        ObjTokeidai_SetupTowerTransformationStart(this);
    } else if ((gSaveContext.day % 5 == 3 && gSaveContext.time < CLOCK_TIME(6, 0)) || gSaveContext.day % 5 >= 4) {
        this->actionFunc = ObjTokeidai_TransformedGearIdle;
        this->actor.world.pos.y += this->actor.scale.y * 1900.0f;
        this->actor.shape.yOffset = 1500.0f;
        gSaveContext.weekEventReg[8] |= 0x40;
    } else {
        this->actionFunc = func_80AB4080;
    }
}

void ObjTokeidai_InitTowerClock(ObjTokeidai* this, GlobalContext* globalCtx) {
    this->actor.draw = ObjTokeidai_DrawClock;
    ObjTokeidai_InitClock(this);
    if ((globalCtx->sceneNum == SCENE_CLOCKTOWER && gSaveContext.sceneSetupIndex == 2 &&
         globalCtx->csCtx.unk_12 == 0) ||
        (globalCtx->sceneNum == SCENE_00KEIKOKU && gSaveContext.sceneSetupIndex == 2 && globalCtx->csCtx.unk_12 == 0)) {
        ObjTokeidai_SetupTowerTransformationStart(this);
    } else if ((gSaveContext.day % 5 == 3 && gSaveContext.time < CLOCK_TIME(6, 0)) || gSaveContext.day % 5 >= 4) {
        this->actor.world.pos.y += (this->actor.scale.y * 5191.0f) - 50.0f;
        this->actor.world.pos.x += Math_SinS(this->actor.world.rot.y) * this->actor.scale.z * 1791.0f;
        this->actor.world.pos.z += -Math_CosS(this->actor.world.rot.y) * this->actor.scale.z * 1791.0f;
        this->clockFaceZTranslation = -0x140;
        this->actor.shape.rot.x = -0x4000;
        this->actor.home.pos = this->actor.world.pos;
        this->actor.home.pos.y -= 1178.0f;
        this->actor.home.pos.z += 13.0f;
        this->actionFunc = ObjTokeidai_TransformedClockIdle;
    } else {
        this->actionFunc = func_80AB3ED0;
    }
}

void ObjTokeidai_InitTowerTop(ObjTokeidai* this, GlobalContext* globalCtx) {
    s32 type;

    this->actor.draw = ObjTokeidai_DrawTowerTop;
    this->opaDList = D_0600B208;
    this->xluDList = D_0600B0C0;
    if (gSaveContext.isNight) {
        this->lightIntensity = 100;
    } else {
        this->lightIntensity = 0;
    }
    if ((globalCtx->sceneNum == SCENE_CLOCKTOWER && gSaveContext.sceneSetupIndex == 2 &&
         globalCtx->csCtx.unk_12 == 0) ||
        (globalCtx->sceneNum == SCENE_00KEIKOKU && gSaveContext.sceneSetupIndex == 2 && globalCtx->csCtx.unk_12 == 0)) {
        this->lightIntensity = 0;
        ObjTokeidai_SetupTowerTransformationStart(this);
        if (this->actor.child == NULL) {
            type = OBJ_TOKEIDAI_TYPE(&this->actor);
            if (type == OBJ_TOKEIDAI_TYPE_TOWER_TOP_CLOCK_TOWN || type == OBJ_TOKEIDAI_TYPE_TOWER_TOP_TERMINA_FIELD) {
                this->actor.child =
                    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_HANABI, this->actor.world.pos.x,
                                this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 0);
            }
        }
        if (this->actor.child != NULL) {
            if (OBJ_TOKEIDAI_TYPE(&this->actor) == OBJ_TOKEIDAI_TYPE_TOWER_TOP_TERMINA_FIELD) {
                this->actor.child->home.rot.x = 0x384;
            } else {
                this->actor.child->home.rot.x = 0x12C;
            }
        }
    } else if ((gSaveContext.day % 5 == 3 && gSaveContext.time < CLOCK_TIME(6, 0)) || gSaveContext.day % 5 >= 4) {
        this->lightIntensity = 0;
        this->actor.world.pos.y += this->actor.scale.y * -2160.0f;
        this->actor.world.pos.x += Math_SinS(this->actor.world.rot.y) * this->actor.scale.z * 5400.0f;
        this->actor.world.pos.z += -Math_CosS(this->actor.world.rot.y) * this->actor.scale.z * 5400.0f;
        this->actor.shape.rot.x = -0x4000;
        this->actionFunc = ObjTokeidai_TransformedTopIdle;
    } else {
        this->actionFunc = func_80AB4160;
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
            ObjTokeidai_InitTowerGear(this, globalCtx);
            break;
        case OBJ_TOKEIDAI_TYPE_TOWER_GEAR_CLOCK_TOWN:
            ObjTokeidai_InitTowerGear(this, globalCtx);
            break;
        case OBJ_TOKEIDAI_TYPE_UNUSED_WALL:
            this->opaDList = D_0600D388;
            break;
        case OBJ_TOKEIDAI_TYPE_TOWER_WALLS_TERMINA_FIELD:
            Actor_SetScale(&this->actor, 1.0f);
            this->opaDList = D_06009A08;
            this->actionFunc = ObjTokeidai_WallsIdle;
            break;
        case OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_TERMINA_FIELD:
            Actor_SetScale(&this->actor, 0.15f);
            ObjTokeidai_InitTowerClock(this, globalCtx);
            break;
        case OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_CLOCK_TOWN:
            ObjTokeidai_InitTowerClock(this, globalCtx);
            break;
        case OBJ_TOKEIDAI_TYPE_SMALL_CLOCK:
            Actor_SetScale(&this->actor, 0.02f);
            this->actor.draw = ObjTokeidai_DrawClock;
            ObjTokeidai_InitClock(this);
            this->actionFunc = func_80AB4040;
            break;
        case OBJ_TOKEIDAI_TYPE_VERY_SMALL_CLOCK:
            Actor_SetScale(&this->actor, 0.01f);
            this->actor.draw = ObjTokeidai_DrawClock;
            ObjTokeidai_InitClock(this);
            this->actionFunc = func_80AB4040;
            break;
        case OBJ_TOKEIDAI_TYPE_TOWER_TOP_TERMINA_FIELD:
            Actor_SetScale(&this->actor, 0.15f);
            ObjTokeidai_InitTowerTop(this, globalCtx);
            break;
        case OBJ_TOKEIDAI_TYPE_TOWER_TOP_CLOCK_TOWN:
            ObjTokeidai_InitTowerTop(this, globalCtx);
            break;
        case OBJ_TOKEIDAI_TYPE_STAIRCASE_INTO_TOWER:
            this->opaDList = D_0600D8E8;
            this->xluDList = D_0600D8E0;
            this->actionFunc = ObjTokeidai_StaircaseIntoTowerIdle;
            break;
    }
}

void ObjTokeidai_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80AB3010(ObjTokeidai* this, s32 playSound) {
    s32 currentMinute;

    currentMinute = OBJ_TOKEIDAI_GET_CURRENT_MINUTE(this);
    if (currentMinute != this->clockMinute) {
        if (this->outerRingOrGearRotationTimer == 8 && playSound) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_CLOCK_TOWER_SECOND_HAND);
        }
        if (this->outerRingOrGearRotationTimer >= 9) {
            this->outerRingOrGearAdditionalRotation += 0x3C;
            this->outerRingOrGearRotation += this->outerRingOrGearAdditionalRotation;
        } else {
            if ((this->outerRingOrGearRotationTimer & 3) == 0) {
                this->outerRingOrGearRotation += 0x5A;
            }
            if ((this->outerRingOrGearRotationTimer & 3) == 1) {
                this->outerRingOrGearRotation -= 0x5A;
            }
        }
        this->outerRingOrGearRotationTimer++;
        if ((currentMinute == 15 && this->outerRingOrGearRotation < 0) || (currentMinute != 15 && this->outerRingOrGearRotation > OBJ_TOKEIDAI_GET_OUTER_RING_OR_GEAR_ROTATION(currentMinute))) {
            this->outerRingOrGearRotation = OBJ_TOKEIDAI_GET_OUTER_RING_OR_GEAR_ROTATION(currentMinute);
            this->clockMinute = currentMinute;
            this->outerRingOrGearAdditionalRotation = 0x5A;
            this->outerRingOrGearRotationTimer = 0;
        }
    }
}

void ObjTokeidai_CollapseGear(ObjTokeidai* this, GlobalContext* globalCtx) {
    if ((this->actor.bgCheckFlags & 1) || this->actor.world.pos.y < 0.0f) {
        this->actionFunc = ObjTokeidai_DoNothing;
        return;
    }
    this->actor.shape.rot.x += 0x50;
    this->actor.shape.rot.z += 0x50;
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
}

void ObjTokeidai_TransformedGearIdle(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (func_800EE29C(globalCtx, 0x84) != 0) {
        if (globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x84)]->unk0 == 2) {
            this->actionFunc = ObjTokeidai_CollapseGear;
            this->actor.speedXZ = this->actor.scale.y * 5.0f;
            this->actor.velocity.y = 0.0f;
            this->actor.minVelocityY = this->actor.scale.y * -50.0f;
            this->actor.gravity = this->actor.scale.y * -5.0f;
        }
    }
}

void func_80AB32F0(ObjTokeidai* this, GlobalContext* globalCtx) {
    this->actor.shape.rot.x += this->unk_15C;
    if (this->unk_15C >= 0xA1) {
        this->unk_15C -= 5;
    }
    this->actor.world.pos.z += 4.0f;
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    if (this->actor.world.pos.y < 0.0f) {
        this->actionFunc = ObjTokeidai_DoNothing;
    }
}

void func_80AB3370(ObjTokeidai* this, GlobalContext* globalCtx) {
    f32 cos;
    f32 sin;
    Actor* thisx = &this->actor;

    if (this->unk_154 < 0x4000) {
        this->unk_154 += 0x28;
    }
    if (this->unk_154 >= 0x801) {
        this->unk_156 += 4;
    }
    if (this->unk_156 < 0x80) {
        thisx->shape.rot.x = this->unk_154 - 0x4000;
        this->unk_15C = 0x28;
    } else {
        if (thisx->shape.rot.x < -0x1000) {
            thisx->shape.rot.x += this->unk_15C;
            if (this->unk_15C < 0x1E0) {
                this->unk_15C += 0xA;
            }
        } else {
            thisx->shape.rot.x += this->unk_15C;
            this->actionFunc = func_80AB32F0;
            thisx->minVelocityY = -7.5f;
            thisx->gravity = -0.75f;
            thisx->velocity.y = -2.0f;
        }
    }

    sin = Math_SinS(this->unk_154);
    cos = Math_CosS(this->unk_154);
    thisx->world.pos.y = (1178.0f * cos) - (this->unk_156 * sin) + thisx->home.pos.y;
    thisx->world.pos.z = (1178.0f * sin) + (this->unk_156 * cos) + thisx->home.pos.z;
}

void ObjTokeidai_TransformedClockIdle(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (func_800EE29C(globalCtx, 0x84) != 0 && globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x84)]->unk0 == 1) {
        this->actionFunc = func_80AB3370;
        this->unk_154 = 0;
        this->unk_156 = -0xD;
    }
}

void ObjTokeidai_CollapseTop(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (this->actor.world.pos.y < 0.0f) {
        this->actionFunc = ObjTokeidai_DoNothing;
        return;
    }
    this->xRotation += 0x64;
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void ObjTokeidai_TransformedTopIdle(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (func_800EE29C(globalCtx, 0x84) != 0) {
        if (globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x84)]->unk0 == 3) {
            this->actionFunc = ObjTokeidai_CollapseTop;
            this->xRotation = 0;
            this->actor.velocity.y = 0.0f;
            this->actor.minVelocityY = this->actor.scale.y * -50.0f;
            this->actor.gravity = this->actor.scale.y * -5.0f;
        }
    }
}

void ObjTokeidai_CollapseWalls(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (this->actor.shape.rot.x < 0x4000) {
        this->actor.shape.rot.x += +0x28;
    }
}

void ObjTokeidai_WallsIdle(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (func_800EE29C(globalCtx, 0x84) != 0 && globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x84)]->unk0 == 1) {
        this->actionFunc = ObjTokeidai_CollapseWalls;
    }
}

void ObjTokeidai_TowerTransformationEndCutscene(ObjTokeidai* this, GlobalContext* globalCtx) {
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

void ObjTokeidai_TowerTransformationFinish(ObjTokeidai* this, GlobalContext* globalCtx) {
    s32 type;

    if (this->clockFaceZTranslation >= -0x13F) {
        this->clockFaceZTranslation -= 0xA;
    } else {
        type = OBJ_TOKEIDAI_TYPE(&this->actor);
        if ((type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_CLOCK_TOWN) || (type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_TERMINA_FIELD)) {
            ObjTokeidai_TowerTransformationEndCutscene(this, globalCtx);
        } else {
            this->actionFunc = ObjTokeidai_DoNothing;
            if (this->actor.child != NULL) {
                this->actor.child->home.rot.x = 0;
            }
        }
    }
}

void ObjTokeidai_TowerTransformationWait(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (this->unk_154 > 0) {
        this->unk_154--;
    } else {
        this->actionFunc = ObjTokeidai_TowerTransformationFinish;
        this->unk_154 = 0;
    }
}

void ObjTokeidai_TowerTopFall(ObjTokeidai* this, GlobalContext* globalCtx) {
    this->xRotation += this->unk_154;
    if (this->xRotation < 0x4000) {
        this->unk_154 += this->unk_156;
        return;
    }
    this->unk_156 = 0x14;
    this->xRotation = 0x4000;
    switch (this->reboundCount) {
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
    this->reboundCount += 1;
    if (this->unk_154 >= 0x191) {
        this->unk_154 = -0xC8;
    } else if (this->unk_154 >= 0x33) {
        this->unk_154 = -(this->unk_154 >> 1);
    } else {
        this->actionFunc = ObjTokeidai_TowerTransformationWait;
        this->unk_154 = 0xA;
    }
}

void ObjTokeidai_TowerRaiseFinished(ObjTokeidai* this, GlobalContext* globalCtx) {
    s32 type;

    if (this->settleTimer > 0) {
        if ((this->settleTimer & 1) != 0) {
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
        if ((type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_CLOCK_TOWN) || (type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_TERMINA_FIELD)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_CLOCK_TOWER_FALL);
        }
        this->yTranslation = 3400;
        this->actionFunc = ObjTokeidai_TowerTopFall;
        this->unk_154 = 0;
        this->unk_156 = 0xA;
        this->reboundCount = 0;
    }
}

void ObjTokeidai_RaiseTower(ObjTokeidai* this, GlobalContext* globalCtx) {
    s32 type;

    if (this->yTranslation < 3400) {
        type = OBJ_TOKEIDAI_TYPE(&this->actor);
        this->yTranslation += 0x19;
        if ((type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_CLOCK_TOWN) || (type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_TERMINA_FIELD)) {
            func_800B9010(&this->actor, NA_SE_EV_CLOCK_TOWER_UP - SFX_FLAG);
        }
    } else {
        type = OBJ_TOKEIDAI_TYPE(&this->actor);
        if ((type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_CLOCK_TOWN) || (type == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_TERMINA_FIELD)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_CLOCK_TOWER_STOP);
        }
        this->yTranslation = 3400;
        this->actionFunc = ObjTokeidai_TowerRaiseFinished;
        this->settleTimer = 10;
        this->settleAmount = 20;
    }
}

void ObjTokeidai_TowerTransformationStart(ObjTokeidai* this, GlobalContext* globalCtx) {
    if ((func_800EE29C(globalCtx, 0x84) != 0 &&
         globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x84)]->unk0 == 4) ||
        ((gSaveContext.weekEventReg[8] & 0x40) != 0)) {
        this->actionFunc = ObjTokeidai_RaiseTower;
    }
}

void ObjTokeidai_SetupTowerTransformationStart(ObjTokeidai* this) {
    this->actionFunc = ObjTokeidai_TowerTransformationStart;
    this->unk_154 = 0;
    this->unk_156 = 0;
    this->yTranslation = 0;
    this->xRotation = 0;
    this->clockFaceZTranslation = 0;
}

void ObjTokeidai_DoNothing(ObjTokeidai* this, GlobalContext* globalCtx) {
}

void ObjTokeidai_StaircaseIntoTowerIdle(ObjTokeidai* this, GlobalContext* globalCtx) {
    if ((gSaveContext.day % 5 == 3 && gSaveContext.time < CLOCK_TIME(6, 0)) || (gSaveContext.day % 5 >= 4) ||
        ((gSaveContext.weekEventReg[8] & 0x40) != 0)) {
        this->actor.draw = ObjTokeidai_Draw;
    } else {
        this->actor.draw = NULL;
    }
}

s32 func_80AB3C50(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (gSaveContext.inventory.items[0] == 0xFF) {
        return false;
    }
    if (gSaveContext.day % 5 == 3 && gSaveContext.time < CLOCK_TIME(6, 0)) {
        ObjTokeidai_SetupTowerTransformationStart(this);
        return true;
    }
    return false;
}

void func_80AB3CCC(ObjTokeidai* this, GlobalContext* globalCtx) {
    s32 currentHour;

    currentHour = OBJ_TOKEIDAI_GET_CURRENT_HOUR(this);
    if (currentHour != this->clockHour) {
        if (this->clockFaceRotationTimer >= 13) {
            this->clockFaceAdditionalRotation += 0xA;
            this->clockFaceRotation += this->clockFaceAdditionalRotation;
        } else {
            if ((this->clockFaceRotationTimer & 3) == 0) {
                this->clockFaceRotation += 0x3C;
            }
            if ((this->clockFaceRotationTimer & 3) == 1) {
                this->clockFaceRotation -= 0x3C;
            }
        }
        this->clockFaceRotationTimer++;
        if ((currentHour == 12 && this->clockFaceRotation < 0) || (currentHour != 12 && this->clockFaceRotation > OBJ_TOKEIDAI_GET_CLOCK_FACE_ROTATION(currentHour))) {
            this->clockFaceRotation = OBJ_TOKEIDAI_GET_CLOCK_FACE_ROTATION(currentHour);
            this->clockHour = currentHour;
            this->clockFaceAdditionalRotation = 0;
            this->clockFaceRotationTimer = 0;
        }
    }
    if (this->sunMoonDiskRotation != ObjTokeidai_GetTargetSunMoonDiskRotation()) {
        if (this->clockHour == 6) {
            this->sunMoonDiskAdditionalRotation += 0x222;
            this->sunMoonDiskRotation += this->sunMoonDiskAdditionalRotation;
            if (this->sunMoonDiskRotation >= 0x10001) {
                this->sunMoonDiskRotation = ObjTokeidai_GetTargetSunMoonDiskRotation();
                this->sunMoonDiskAdditionalRotation = 0;
            }
        }
        if (this->clockHour == 18) {
            this->sunMoonDiskAdditionalRotation += 0x222;
            this->sunMoonDiskRotation += this->sunMoonDiskAdditionalRotation;
            if (this->sunMoonDiskRotation >= 0x8001) {
                this->sunMoonDiskRotation = ObjTokeidai_GetTargetSunMoonDiskRotation();
                this->sunMoonDiskAdditionalRotation = 0;
            }
        }
    }
}

void func_80AB3ED0(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (gSaveContext.day % 5 == 3 && this->clockHour < 6 && gSaveContext.time < CLOCK_TIME(6, 0)) {
        this->actor.draw = ObjTokeidai_DrawClock;
        ObjTokeidai_SetupTowerTransformationStart(this);
        gSaveContext.weekEventReg[8] |= 0x40;
        return;
    }
    if (globalCtx->csCtx.state != 0) {
        this->actor.home.rot.x = 1;
        this->currentTime += 3;
        this->actor.draw = ObjTokeidai_DrawClock;
    } else {
        if ((globalCtx->actorCtx.unk5 & 2) == 0 &&
            OBJ_TOKEIDAI_TYPE(&this->actor) == OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_TERMINA_FIELD &&
            ActorCutscene_GetCurrentIndex() == -1) {
            this->actor.draw = NULL;
        }
        this->currentTime = gSaveContext.time;
        if (this->actor.home.rot.x != 0) {
            ObjTokeidai_InitClock(this);
            this->actor.home.rot.x = 0;
        }
    }
    if (gSaveContext.day % 5 != 3 || gSaveContext.time >= CLOCK_TIME(6, 0)) {
        func_80AB3010(this, true);
    }
    func_80AB3CCC(this, globalCtx);
}

void func_80AB4040(ObjTokeidai* this, GlobalContext* globalCtx) {
    this->currentTime = gSaveContext.time;
    func_80AB3010(this, true);
    func_80AB3CCC(this, globalCtx);
}

void func_80AB4080(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (func_80AB3C50(this, globalCtx)) {
        this->actor.draw = ObjTokeidai_DrawTowerGear;
    } else {
        if (globalCtx->csCtx.state != 0) {
            this->actor.home.rot.x = 1;
            this->currentTime += 3;
            this->actor.draw = ObjTokeidai_DrawTowerGear;
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
        func_80AB3010(this, false);
    }
}

void func_80AB4160(ObjTokeidai* this, GlobalContext* globalCtx) {
    s32 type;

    if (func_80AB3C50(this, globalCtx)) {
        this->lightIntensity = 0;
        if ((this->actor.child == NULL)) {
            type = OBJ_TOKEIDAI_TYPE(&this->actor);
            if (type == OBJ_TOKEIDAI_TYPE_TOWER_TOP_CLOCK_TOWN || type == OBJ_TOKEIDAI_TYPE_TOWER_TOP_TERMINA_FIELD) {
                this->actor.child =
                    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_HANABI, this->actor.world.pos.x,
                                this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 0);
            }
        }
        if (this->actor.child != NULL) {
            if (OBJ_TOKEIDAI_TYPE(&this->actor) == OBJ_TOKEIDAI_TYPE_TOWER_TOP_TERMINA_FIELD) {
                this->actor.child->home.rot.x = 0x384;
            } else {
                this->actor.child->home.rot.x = 0x12C;
            }
        }
    } else {
        this->actor.shape.rot.y += -0x40;
        if (gSaveContext.isNight != 0) {
            if (this->lightIntensity < 100) {
                this->lightIntensity += +4;
            }
        } else if (this->lightIntensity > 0) {
            this->lightIntensity -= 4;
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

void ObjTokeidai_DrawClock(Actor* thisx, GlobalContext* globalCtx) {
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
    if (OBJ_TOKEIDAI_TYPE(&this->actor) == OBJ_TOKEIDAI_TYPE_SMALL_CLOCK ||
        OBJ_TOKEIDAI_TYPE(&this->actor) == OBJ_TOKEIDAI_TYPE_VERY_SMALL_CLOCK) {
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

void ObjTokeidai_DrawTowerTop(Actor* thisx, GlobalContext* globalCtx) {
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
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 255, 255, 235, 180, (s32)(this->lightIntensity * 2.55f));
    gSPDisplayList(POLY_XLU_DISP++, this->xluDList);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void ObjTokeidai_DrawTowerGear(Actor* thisx, GlobalContext* globalCtx) {
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
