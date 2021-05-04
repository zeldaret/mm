/*
 * File: z_obj_tokei_step.c
 * Overlay: obj_Tokei_Step
 * Description: Door to Top of Clock Tower
 */

#include "z_obj_tokei_step.h"

#define FLAGS 0x00400010

#define THIS ((ObjTokeiStep*)thisx)

void ObjTokeiStep_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeiStep_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeiStep_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeiStep_Draw(Actor* thisx, GlobalContext* globalCtx);

void ObjTokeiStep_SetBeginCutscene(ObjTokeiStep *this);
void ObjTokeiStep_SetupCutscene(ObjTokeiStep *this, GlobalContext* globalCtx);
void ObjTokeiStep_SetDoNothing(ObjTokeiStep *this);
void ObjTokeiStep_DoNothing(ObjTokeiStep *this, GlobalContext* globalCtx);
void ObjTokeiStep_BeginCutscene(ObjTokeiStep *this);
void ObjTokeiStep_Open(ObjTokeiStep *this, GlobalContext* globalCtx);
void ObjTokeiStep_SetDoNothingOpen(ObjTokeiStep *this);
void ObjTokeiStep_DoNothingOpen(ObjTokeiStep *this, GlobalContext* globalCtx);
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
    (ActorFunc)ObjTokeiStep_Draw
};

extern Gfx D_06000088[];

extern CollisionHeader D_06000968;

static f32 D_80AD6620[] = {-105.0f, -90.0f, -75.0f, -60.0f, -45.0f, -30.0f, -15.0f};

static f32 D_80AD663C[] = {-60.0f, -40.0f, -20.0f, 0.0f, 20.0f, 40.0f, 60.0f};

static Vec3f D_80AD6658 = {0.0f, 0.3f, 0.0f};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};


void ObjTokeiStep_SetSysMatrix(ObjTokeiStepStep *step) {
    MtxF* sysMatrix;

    sysMatrix = SysMatrix_GetCurrentState();
    sysMatrix->wx = step->pos.x;
    sysMatrix->wy = step->pos.y;
    sysMatrix->wz = step->pos.z;
}

void ObjTokeiStep_AddQuake(ObjTokeiStep *this, GlobalContext *globalCtx) {
    s32 pad[2];
    s16 quake;

    quake = Quake_Add(ACTIVE_CAM, 3);
    Quake_SetSpeed(quake, 0x4E20);
    Quake_SetQuakeValues(quake, 1, 0, 0, 0);
    Quake_SetCountdown(quake, 7);
    func_8013ECE0(this->dyna.actor.xyzDistToPlayerSq, 0x78, 0x14, 0xA);
}

void ObjTokeiStep_SpawnDust(ObjTokeiStep *this, ObjTokeiStepStep *step, GlobalContext *globalCtx) {
    s32 i;
    s32 pad;
    Vec3f sp84;
    Vec3f sp78;
    
    Matrix_RotateY(this->dyna.actor.shape.rot.y, 0);

    sp84.y = 115.0f;
    sp84.z = -10.0f;
    for (i=0; i<7; i++) {
        sp84.x = D_80AD663C[i];
        SysMatrix_MultiplyVector3fByState(&sp84, &sp78);
        sp78.x += step->pos.x;
        sp78.y += step->pos.y;
        sp78.z += step->pos.z;
        func_800B1210(globalCtx, &sp78, &D_801D15B0, &D_80AD6658, (s32) ((Rand_ZeroOne() * 40.0f) + 80.0f), (s32) ((Rand_ZeroOne() * 20.0f) + 50.0f));
    }
}

void ObjTokeiStep_InitSteps(ObjTokeiStep *this) {
    s32 i;
    ObjTokeiStepStep *step;
    Vec3f sp4c;
    s32 pad;

    SysMatrix_SetStateRotationAndTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);
 
    sp4c.x = 0.0f;
    sp4c.y = 0.0f;
    for (i=0; i<7; i++) {
        step = &this->steps[i];
        sp4c.z = i * -20.0f;
        SysMatrix_MultiplyVector3fByState(&sp4c, &step->pos);
        step->posChangeY = 0.0f;
        step->numBounces = 0;
    }
}

void ObjTokeiStep_InitStepsOpen(ObjTokeiStep *this) {
    s32 i;
    ObjTokeiStepStep *step;
    Vec3f sp44;

    SysMatrix_SetStateRotationAndTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);
    
    sp44.x = 0.0f;
    for (i=0; i<7; i++) {
        step = &this->steps[i];
        sp44.y = D_80AD6620[i];
        sp44.z = i * -20.0f;
        SysMatrix_MultiplyVector3fByState(&sp44, &step->pos);
    }
}

void ObjTokeiStep_InitTimers(ObjTokeiStep *this) {
    s32 i;

    this->steps[0].startFallingTimer = 0;
    for (i=1; i<7; i++) {
        this->steps[i].startFallingTimer = 10;
    }
}

s32 ObjTokeiStep_OpenProcess(ObjTokeiStep *this, GlobalContext *globalCtx) {
    ObjTokeiStep *this2 = this;
    s32 i;
    ObjTokeiStepStep *step;
    f32 finalPosY;
    s32 isOpen = 1;
    s32 prevBounced = 1;

    for (i=0; i<7; i++) {
        step = &this->steps[i];
        if (prevBounced && step->startFallingTimer > 0) {
            step->startFallingTimer--;
            isOpen = 0;
        }
        if (prevBounced && step->numBounces < 3 && step->startFallingTimer <= 0){
            finalPosY = D_80AD6620[i] + this->dyna.actor.world.pos.y;
            if (!step->hasSoundPlayed) {
                Audio_PlayActorSound2(&this->dyna.actor, 0x2945);
                step->hasSoundPlayed = true;
            }
            step->posChangeY += -2.5f;
            step->posChangeY *= 0.83f;
            step->pos.y += step->posChangeY;
            isOpen = 0;
            if (step->pos.y < finalPosY) {
                step->numBounces++;
                if (step->numBounces >= 3) {
                    step->pos.y = finalPosY;
                } else {
                    step->posChangeY *= -0.4f;
                    if (step->posChangeY > 4.0f) {
                        step->posChangeY = 4.0f;
                    }
                    step->pos.y = (step->pos.y - finalPosY) * -0.4f;
                    if (step->posChangeY < step->pos.y) {
                        step->pos.y = step->posChangeY + finalPosY;
                    } else {
                        step->pos.y += finalPosY;
                    }
                    if (step->numBounces == 1) {
                        ObjTokeiStep_SpawnDust(this2, step, globalCtx);
                        ObjTokeiStep_AddQuake(this2, globalCtx);
                    }
                }
            }
        }
        prevBounced = step->numBounces > 0;
    }
    return isOpen;
}

void ObjTokeiStep_Init(Actor *thisx, GlobalContext *globalCtx) {
    ObjTokeiStep *this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    BcCheck3_BgActorInit(&this->dyna, 0);
    if ((globalCtx->sceneNum == 0x6F) && (gSaveContext.extra.sceneSetupIndex == 2) && (globalCtx->csCtx.unk12 == 0)) {
        BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_06000968);
        ObjTokeiStep_InitSteps(this);
        ObjTokeiStep_SetBeginCutscene(this);
    }
    else if (!((((s32) gSaveContext.perm.day % 5) != 3) || (gSaveContext.perm.time >= 0x4000)) || (s32) gSaveContext.perm.day >= 4) {
        this->dyna.actor.draw = ObjTokeiStep_DrawOpen;
        ObjTokeiStep_InitStepsOpen(this);
        ObjTokeiStep_SetDoNothingOpen(this);
    } else {
        BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_06000968);
        ObjTokeiStep_InitSteps(this);
        ObjTokeiStep_SetDoNothing(this);
    }
}

void ObjTokeiStep_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    ObjTokeiStep *this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}


void ObjTokeiStep_SetBeginCutscene(ObjTokeiStep *this) {
    this->actionFunc = ObjTokeiStep_SetupCutscene;
}

void ObjTokeiStep_SetupCutscene(ObjTokeiStep *this, GlobalContext *globalCtx) {
    CsCmdActorAction *action;

    if (func_800EE29C(globalCtx, 0x86)) {
        action = globalCtx->csCtx.actorActions[func_800EE200(globalCtx, 0x86)];
        if ((globalCtx->csCtx.frames == (*action).startFrame) && action->unk0) {
            this->dyna.actor.draw = ObjTokeiStep_DrawOpen;
            ObjTokeiStep_BeginCutscene(this);
        }
    }
}

void ObjTokeiStep_SetDoNothing(ObjTokeiStep *this) {
    this->actionFunc = ObjTokeiStep_DoNothing;
}

void ObjTokeiStep_DoNothing(ObjTokeiStep *this, GlobalContext *globalCtx) {
}

void ObjTokeiStep_BeginCutscene(ObjTokeiStep *this) {
    ObjTokeiStep_InitTimers(this);
    this->actionFunc = ObjTokeiStep_Open;
}

void ObjTokeiStep_Open(ObjTokeiStep *this, GlobalContext *globalCtx) {
    if (ObjTokeiStep_OpenProcess(this, globalCtx)) {
        func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        ObjTokeiStep_SetDoNothingOpen(this);
    }
}

void ObjTokeiStep_SetDoNothingOpen(ObjTokeiStep *this) {
    this->dyna.actor.flags &= ~0x10;
    this->actionFunc = ObjTokeiStep_DoNothingOpen;
}

void ObjTokeiStep_DoNothingOpen(ObjTokeiStep *this, GlobalContext *globalCtx) {
}

void ObjTokeiStep_Update(Actor *thisx, GlobalContext *globalCtx) {
    ObjTokeiStep *this = THIS;

    this->actionFunc(this, globalCtx);
}

void ObjTokeiStep_Draw(Actor *thisx, GlobalContext *globalCtx) {
    ObjTokeiStep *this = THIS;

    func_800BDFC0(globalCtx, D_06000088);
}

void ObjTokeiStep_DrawOpen(Actor *thisx, GlobalContext *globalCtx) {
    ObjTokeiStep *this = THIS;
    int i;
    ObjTokeiStepStep *step;
    Gfx *gfx;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    gfx = POLY_OPA_DISP;
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x19]);

    for(i=0; i<7; i++) {
        step = &this->steps[i];
        ObjTokeiStep_SetSysMatrix(step);
        gSPMatrix(gfx++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfx++, D_06000088);
    }
    POLY_OPA_DISP = gfx;
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
