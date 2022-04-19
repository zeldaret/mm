/*
 * File: z_obj_tokei_step.c
 * Overlay: obj_Tokei_Step
 * Description: Door to Top of Clock Tower
 */

#include "z_obj_tokei_step.h"
#include "objects/object_tokei_step/object_tokei_step.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_400000)

#define THIS ((ObjTokeiStep*)thisx)

void ObjTokeiStep_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeiStep_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeiStep_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeiStep_Draw(Actor* thisx, GlobalContext* globalCtx);

void ObjTokeiStep_SetupBeginOpen(ObjTokeiStep* this);
void ObjTokeiStep_BeginOpen(ObjTokeiStep* this, GlobalContext* globalCtx);
void ObjTokeiStep_SetupDoNothing(ObjTokeiStep* this);
void ObjTokeiStep_DoNothing(ObjTokeiStep* this, GlobalContext* globalCtx);
void ObjTokeiStep_SetupOpen(ObjTokeiStep* this);
void ObjTokeiStep_Open(ObjTokeiStep* this, GlobalContext* globalCtx);
void ObjTokeiStep_SetupDoNothingOpen(ObjTokeiStep* this);
void ObjTokeiStep_DoNothingOpen(ObjTokeiStep* this, GlobalContext* globalCtx);
void ObjTokeiStep_DrawOpen(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Tokei_Step_InitVars = {
    ACTOR_OBJ_TOKEI_STEP,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_TOKEI_STEP,
    sizeof(ObjTokeiStep),
    (ActorFunc)ObjTokeiStep_Init,
    (ActorFunc)ObjTokeiStep_Destroy,
    (ActorFunc)ObjTokeiStep_Update,
    (ActorFunc)ObjTokeiStep_Draw,
};

static f32 sPanelXOffsets[] = { -105.0f, -90.0f, -75.0f, -60.0f, -45.0f, -30.0f, -15.0f };

static f32 sDustSpawnXOffsets[] = { -60.0f, -40.0f, -20.0f, 0.0f, 20.0f, 40.0f, 60.0f };

static Vec3f sDustEffectAccel = { 0.0f, 0.3f, 0.0f };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void ObjTokeiStep_SetSysMatrix(ObjTokeiStepPanel* panel) {
    MtxF* mtx = Matrix_GetCurrentState();

    mtx->wx = panel->pos.x;
    mtx->wy = panel->pos.y;
    mtx->wz = panel->pos.z;
}

void ObjTokeiStep_AddQuake(ObjTokeiStep* this, GlobalContext* globalCtx) {
    s32 pad[2];
    s16 quake = Quake_Add(GET_ACTIVE_CAM(globalCtx), 3);

    Quake_SetSpeed(quake, 20000);
    Quake_SetQuakeValues(quake, 1, 0, 0, 0);
    Quake_SetCountdown(quake, 7);
    func_8013ECE0(this->dyna.actor.xyzDistToPlayerSq, 120, 20, 10);
}

void ObjTokeiStep_SpawnDust(ObjTokeiStep* this, ObjTokeiStepPanel* panel, GlobalContext* globalCtx) {
    s32 i;
    s32 pad;
    Vec3f dustSpawnOffset;
    Vec3f dustSpawnPos;

    Matrix_RotateY(this->dyna.actor.shape.rot.y, MTXMODE_NEW);

    dustSpawnOffset.y = 115.0f;
    dustSpawnOffset.z = -10.0f;
    for (i = 0; i < 7; i++) {
        dustSpawnOffset.x = sDustSpawnXOffsets[i];
        Matrix_MultiplyVector3fByState(&dustSpawnOffset, &dustSpawnPos);
        dustSpawnPos.x += panel->pos.x;
        dustSpawnPos.y += panel->pos.y;
        dustSpawnPos.z += panel->pos.z;
        func_800B1210(globalCtx, &dustSpawnPos, &gZeroVec3f, &sDustEffectAccel, (s32)((Rand_ZeroOne() * 40.0f) + 80.0f),
                      (s32)((Rand_ZeroOne() * 20.0f) + 50.0f));
    }
}

void ObjTokeiStep_InitSteps(ObjTokeiStep* this) {
    s32 i;
    ObjTokeiStepPanel* panel;
    Vec3f panelOffset;
    s32 pad;

    Matrix_SetStateRotationAndTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                                          this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);

    panelOffset.x = 0.0f;
    panelOffset.y = 0.0f;
    for (i = 0; i < ARRAY_COUNT(this->panels); i++) {
        panel = &this->panels[i];
        panelOffset.z = i * -20.0f;
        Matrix_MultiplyVector3fByState(&panelOffset, &panel->pos);
        panel->posChangeY = 0.0f;
        panel->numBounces = 0;
    }
}

void ObjTokeiStep_InitStepsOpen(ObjTokeiStep* this) {
    s32 i;
    ObjTokeiStepPanel* panel;
    Vec3f panelOffset;

    Matrix_SetStateRotationAndTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                                          this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);

    panelOffset.x = 0.0f;
    for (i = 0; i < ARRAY_COUNT(this->panels); i++) {
        panel = &this->panels[i];
        panelOffset.y = sPanelXOffsets[i];
        panelOffset.z = i * -20.0f;
        Matrix_MultiplyVector3fByState(&panelOffset, &panel->pos);
    }
}

void ObjTokeiStep_InitTimers(ObjTokeiStep* this) {
    s32 i;

    this->panels[0].startFallingTimer = 0;
    for (i = 1; i < ARRAY_COUNT(this->panels); i++) {
        this->panels[i].startFallingTimer = 10;
    }
}

s32 ObjTokeiStep_OpenProcess(ObjTokeiStep* this, GlobalContext* globalCtx) {
    ObjTokeiStep* this2 = this;
    s32 i;
    ObjTokeiStepPanel* panel;
    f32 finalPosY;
    s32 isOpen = true;
    s32 hasPrevBounced = true;

    for (i = 0; i < ARRAY_COUNT(this->panels); i++) {
        panel = &this->panels[i];
        if (hasPrevBounced && (panel->startFallingTimer > 0)) {
            panel->startFallingTimer--;
            isOpen = false;
        }
        if (hasPrevBounced && (panel->numBounces < 3) && (panel->startFallingTimer <= 0)) {
            finalPosY = sPanelXOffsets[i] + this->dyna.actor.world.pos.y;
            if (!panel->hasSoundPlayed) {
                Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_CLOCK_TOWER_STAIR_MOVE);
                panel->hasSoundPlayed = true;
            }
            panel->posChangeY += -2.5f;
            panel->posChangeY *= 0.83f;
            panel->pos.y += panel->posChangeY;
            isOpen = false;
            if (panel->pos.y < finalPosY) {
                panel->numBounces++;
                if (panel->numBounces >= 3) {
                    panel->pos.y = finalPosY;
                } else {
                    panel->posChangeY *= -0.4f;
                    if (panel->posChangeY > 4.0f) {
                        panel->posChangeY = 4.0f;
                    }
                    panel->pos.y = (panel->pos.y - finalPosY) * -0.4f;
                    if (panel->posChangeY < panel->pos.y) {
                        panel->pos.y = panel->posChangeY + finalPosY;
                    } else {
                        panel->pos.y += finalPosY;
                    }
                    if (panel->numBounces == 1) {
                        ObjTokeiStep_SpawnDust(this2, panel, globalCtx);
                        ObjTokeiStep_AddQuake(this2, globalCtx);
                    }
                }
            }
        }
        hasPrevBounced = panel->numBounces > 0;
    }
    return isOpen;
}

void ObjTokeiStep_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjTokeiStep* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 0);
    if ((globalCtx->sceneNum == SCENE_CLOCKTOWER) && (gSaveContext.sceneSetupIndex == 2) &&
        (globalCtx->csCtx.currentCsIndex == 0)) {
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &gClocktowerPanelCol);
        ObjTokeiStep_InitSteps(this);
        ObjTokeiStep_SetupBeginOpen(this);
    } else if (((CURRENT_DAY == 3) && (gSaveContext.save.time < CLOCK_TIME(6, 0))) || (gSaveContext.save.day >= 4)) {
        this->dyna.actor.draw = ObjTokeiStep_DrawOpen;
        ObjTokeiStep_InitStepsOpen(this);
        ObjTokeiStep_SetupDoNothingOpen(this);
    } else {
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &gClocktowerPanelCol);
        ObjTokeiStep_InitSteps(this);
        ObjTokeiStep_SetupDoNothing(this);
    }
}

void ObjTokeiStep_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjTokeiStep* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void ObjTokeiStep_SetupBeginOpen(ObjTokeiStep* this) {
    this->actionFunc = ObjTokeiStep_BeginOpen;
}

void ObjTokeiStep_BeginOpen(ObjTokeiStep* this, GlobalContext* globalCtx) {
    CsCmdActorAction* action;

    if (Cutscene_CheckActorAction(globalCtx, 134)) {
        action = globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 134)];

        if ((action->startFrame == globalCtx->csCtx.frames) && (action->action != 0)) {
            this->dyna.actor.draw = ObjTokeiStep_DrawOpen;
            ObjTokeiStep_SetupOpen(this);
        }
    }
}

void ObjTokeiStep_SetupDoNothing(ObjTokeiStep* this) {
    this->actionFunc = ObjTokeiStep_DoNothing;
}

void ObjTokeiStep_DoNothing(ObjTokeiStep* this, GlobalContext* globalCtx) {
}

void ObjTokeiStep_SetupOpen(ObjTokeiStep* this) {
    ObjTokeiStep_InitTimers(this);
    this->actionFunc = ObjTokeiStep_Open;
}

void ObjTokeiStep_Open(ObjTokeiStep* this, GlobalContext* globalCtx) {
    if (ObjTokeiStep_OpenProcess(this, globalCtx)) {
        func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        ObjTokeiStep_SetupDoNothingOpen(this);
    }
}

void ObjTokeiStep_SetupDoNothingOpen(ObjTokeiStep* this) {
    this->dyna.actor.flags &= ~ACTOR_FLAG_10;
    this->actionFunc = ObjTokeiStep_DoNothingOpen;
}

void ObjTokeiStep_DoNothingOpen(ObjTokeiStep* this, GlobalContext* globalCtx) {
}

void ObjTokeiStep_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjTokeiStep* this = THIS;

    this->actionFunc(this, globalCtx);
}

void ObjTokeiStep_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjTokeiStep* this = THIS;

    Gfx_DrawDListOpa(globalCtx, gClocktowerPanelDL);
}

void ObjTokeiStep_DrawOpen(Actor* thisx, GlobalContext* globalCtx) {
    ObjTokeiStep* this = THIS;
    s32 i;
    ObjTokeiStepPanel* panel;
    Gfx* gfx;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    gfx = POLY_OPA_DISP;
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x19]);

    for (i = 0; i < ARRAY_COUNT(this->panels); i++) {
        panel = &this->panels[i];
        ObjTokeiStep_SetSysMatrix(panel);
        gSPMatrix(gfx++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfx++, gClocktowerPanelDL);
    }
    POLY_OPA_DISP = gfx;
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
