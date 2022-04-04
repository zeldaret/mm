/*
 * File: z_obj_raillift.c
 * Overlay: ovl_Obj_Raillift
 * Description: Moving Deku Flower Platform and OoT Water Temple Waterfall Platform
 */

#include "z_obj_raillift.h"
#include "objects/object_raillift/object_raillift.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjRaillift*)thisx)

void ObjRaillift_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjRaillift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjRaillift_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjRaillift_Draw(Actor* thisx, GlobalContext* globalCtx);

void ObjRaillift_DrawDekuFlowerPlatformColorful(Actor* thisx, GlobalContext* globalCtx);
void ObjRaillift_DrawDekuFlowerPlatform(Actor* thisx, GlobalContext* globalCtx);

void ObjRaillift_DoNothing(ObjRaillift* this, GlobalContext* globalCtx);
void ObjRaillift_Idle(ObjRaillift* this, GlobalContext* globalCtx);
void ObjRaillift_UpdatePosition(ObjRaillift* this, s32 arg1);
void ObjRaillift_StartCutscene(ObjRaillift* this, GlobalContext* globalCtx);
void ObjRaillift_Teleport(ObjRaillift* this, GlobalContext* globalCtx);
void ObjRaillift_Wait(ObjRaillift* this, GlobalContext* globalCtx);
void ObjRaillift_Move(ObjRaillift* this, GlobalContext* globalCtx);

const ActorInit Obj_Raillift_InitVars = {
    ACTOR_OBJ_RAILLIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_RAILLIFT,
    sizeof(ObjRaillift),
    (ActorFunc)ObjRaillift_Init,
    (ActorFunc)ObjRaillift_Destroy,
    (ActorFunc)ObjRaillift_Update,
    (ActorFunc)ObjRaillift_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 400, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

static CollisionHeader* sColHeaders[] = { &object_raillift_Colheader_004FF8, &object_raillift_Colheader_0048D0 };

void ObjRaillift_UpdatePosition(ObjRaillift* this, s32 idx) {
    Math_Vec3s_ToVec3f(&this->dyna.actor.world.pos, &this->points[idx]);
}

void ObjRaillift_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjRaillift* this = THIS;
    s32 pad;
    Path* path;
    s32 type = OBJRAILLIFT_GET_TYPE(thisx);
    s32 isColorful = false;

    Actor_ProcessInitChain(thisx, sInitChain);

    thisx->shape.rot.x = 0;
    thisx->world.rot.x = 0;
    thisx->shape.rot.z = 0;
    thisx->world.rot.z = 0;
    DynaPolyActor_Init(&this->dyna, 1);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, sColHeaders[type]);
    this->speed = OBJRAILLIFT_GET_SPEED(thisx);
    if (this->speed < 0.0f) {
        this->speed = -this->speed;
        isColorful = true;
    }
    if (type == DEKU_FLOWER_PLATFORM) {
        Actor_SpawnAsChild(&globalCtx->actorCtx, thisx, globalCtx, ACTOR_OBJ_ETCETERA, thisx->world.pos.x,
                           thisx->world.pos.y, thisx->world.pos.z, thisx->shape.rot.x, thisx->shape.rot.y,
                           thisx->shape.rot.z, 0);
        if (isColorful) {
            thisx->draw = ObjRaillift_DrawDekuFlowerPlatformColorful;
        } else {
            thisx->draw = ObjRaillift_DrawDekuFlowerPlatform;
        }
    }
    if (this->speed < 0.01f) {
        this->actionFunc = ObjRaillift_DoNothing;
    } else {
        path = &globalCtx->setupPathList[OBJRAILLIFT_GET_PATH(thisx)];
        this->curPoint = OBJRAILLIFT_GET_STARTING_POINT(thisx);
        this->endPoint = path->count - 1;
        this->direction = 1;
        this->points = Lib_SegmentedToVirtual(path->points);
        ObjRaillift_UpdatePosition(this, this->curPoint);
        if (OBJRAILLIFT_HAS_FLAG(thisx) && !Flags_GetSwitch(globalCtx, OBJRAILLIFT_GET_FLAG(thisx))) {
            this->actionFunc = ObjRaillift_Idle;
        } else {
            this->actionFunc = ObjRaillift_Move;
        }
    }
}

void ObjRaillift_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjRaillift* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void ObjRaillift_DoNothing(ObjRaillift* this, GlobalContext* globalCtx) {
}

void ObjRaillift_Move(ObjRaillift* this, GlobalContext* globalCtx) {
    s32 isTeleporting;
    Vec3f nextPoint;
    f32 speed;
    f32 target;
    f32 step;
    s32 isPosUpdated;
    Vec3s* initialPoint;
    Vec3s* endPoint;
    s32 pad;

    if (OBJRAILLIFT_HAS_FLAG(&this->dyna.actor)) {
        if (!Flags_GetSwitch(globalCtx, OBJRAILLIFT_GET_FLAG(&this->dyna.actor))) {
            this->actionFunc = ObjRaillift_Idle;
            return;
        }

        if (OBJRAILLIFT_GET_TYPE(&this->dyna.actor) == DEKU_FLOWER_PLATFORM) {
            func_800B9010(&this->dyna.actor, NA_SE_EV_PLATE_LIFT_LEVEL - SFX_FLAG);
        }
    }

    Math_Vec3s_ToVec3f(&nextPoint, &(&this->points[this->curPoint])[this->direction]);
    Math_Vec3f_Diff(&nextPoint, &this->dyna.actor.world.pos, &this->dyna.actor.velocity);
    speed = Math3D_Vec3fMagnitude(&this->dyna.actor.velocity);
    if ((speed < (this->speed * 8.0f)) && (this->speed > 2.0f)) {
        target = ((this->speed - 2.0f) * 0.1f) + 2.0f;
        step = this->speed * 0.03f;
    } else {
        target = this->speed;
        step = this->speed * 0.16f;
    }

    Math_StepToF(&this->dyna.actor.speedXZ, target, step);
    if ((this->dyna.actor.speedXZ + 0.05f) < speed) {
        Math_Vec3f_Scale(&this->dyna.actor.velocity, this->dyna.actor.speedXZ / speed);
        this->dyna.actor.world.pos.x += this->dyna.actor.velocity.x;
        this->dyna.actor.world.pos.y += this->dyna.actor.velocity.y;
        this->dyna.actor.world.pos.z += this->dyna.actor.velocity.z;
    } else {
        this->curPoint += this->direction;
        if (1) {}
        this->dyna.actor.speedXZ *= 0.4f;
        isTeleporting = OBJRAILLIFT_SHOULD_TELEPORT(&this->dyna.actor);
        isPosUpdated = true;
        if (((this->curPoint >= this->endPoint) && (this->direction > 0)) ||
            ((this->curPoint <= 0) && (this->direction < 0))) {
            if (!isTeleporting) {
                this->direction = -this->direction;
                this->waitTimer = 10;
                this->actionFunc = ObjRaillift_Wait;
            } else {
                endPoint = &this->points[this->endPoint];
                this->curPoint = this->direction > 0 ? 0 : this->endPoint;
                initialPoint = &this->points[0];
                if ((initialPoint->x != endPoint->x) || (initialPoint->y != endPoint->y) ||
                    (initialPoint->z != endPoint->z)) {
                    this->actionFunc = ObjRaillift_Teleport;
                    func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
                    isPosUpdated = false;
                }
            }
        }

        if (isPosUpdated) {
            ObjRaillift_UpdatePosition(this, this->curPoint);
        }
    }
}

/*
Will teleport to what ever curpoint is set to
*/
void ObjRaillift_Teleport(ObjRaillift* this, GlobalContext* globalCtx) {
    if (!DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
        ObjRaillift_UpdatePosition(this, this->curPoint);
        func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        this->actionFunc = ObjRaillift_Move;
    }
}

void ObjRaillift_Wait(ObjRaillift* this, GlobalContext* globalCtx) {
    this->waitTimer--;
    if (this->waitTimer <= 0) {
        this->actionFunc = ObjRaillift_Move;
        this->dyna.actor.speedXZ = 0.0f;
    }
}

void ObjRaillift_Idle(ObjRaillift* this, GlobalContext* globalCtx) {
    if (Flags_GetSwitch(globalCtx, OBJRAILLIFT_GET_FLAG(&this->dyna.actor))) {
        this->dyna.actor.speedXZ = 0.0f;
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
        this->actionFunc = ObjRaillift_StartCutscene;
    }
}

void ObjRaillift_StartCutscene(ObjRaillift* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        this->cutsceneTimer = 50;
        this->actionFunc = ObjRaillift_Move;
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void ObjRaillift_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjRaillift* this = THIS;
    f32 target;
    f32 step;

    this->actionFunc(this, globalCtx);
    Actor_SetFocus(&this->dyna.actor, 10.0f);
    if (this->cutsceneTimer > 0) {
        this->cutsceneTimer--;
        if (this->cutsceneTimer == 0) {
            ActorCutscene_Stop(this->dyna.actor.cutscene);
        }
    }
    if (OBJRAILLIFT_SHOULD_REACT_TO_WEIGHT(thisx)) {
        s32 requiredScopeTemp;

        this->isWeightOnPrev = this->isWeightOn;
        if (DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
            this->isWeightOn = true;
        } else {
            this->isWeightOn = false;
        }
        if ((this->isWeightOn != this->isWeightOnPrev) && (this->maxHeight < 1.0f)) {
            this->cycle = -0x8000;
            this->maxHeight = 6.0f;
        }
        this->cycle += 0xCE4;
        Math_StepToF(&this->maxHeight, 0.0f, 0.12f);
        step = this->isWeightOn ? Math_CosS(fabsf(this->cycleSpeed) * 2048.0f) + 0.02f
                                : Math_SinS(fabsf(this->cycleSpeed) * 2048.0f) + 0.02f;
        target = this->isWeightOn ? -8.0f : 0.0f;
        Math_StepToF(&this->cycleSpeed, target, step);
        this->dyna.actor.shape.yOffset = ((Math_SinS(this->cycle) * this->maxHeight) + this->cycleSpeed) * 10.0f;
    }
    if (OBJRAILLIFT_GET_TYPE(thisx) == DEKU_FLOWER_PLATFORM && this->dyna.actor.child != NULL) {
        if (this->dyna.actor.child->update == NULL) {
            this->dyna.actor.child = NULL;
        } else {
            this->dyna.actor.child->world.pos.x = this->dyna.actor.world.pos.x;
            this->dyna.actor.child->world.pos.y =
                this->dyna.actor.world.pos.y + (this->dyna.actor.shape.yOffset * this->dyna.actor.scale.y);
            this->dyna.actor.child->world.pos.z = this->dyna.actor.world.pos.z;
        }
    }
}

void ObjRaillift_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08,
               Gfx_TwoTexScrollEnvColor(globalCtx->state.gfxCtx, 0, globalCtx->gameplayFrames, 0, 32, 32, 1, 0, 0, 32,
                                        32, 0, 0, 0, 160));
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_raillift_DL_004BF0);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/*
The non-colorful platforms are the ones found in Woodfall Temple
*/
void ObjRaillift_DrawDekuFlowerPlatform(Actor* thisx, GlobalContext* globalCtx) {
    Gfx_DrawDListOpa(globalCtx, object_raillift_DL_000208);
}

/*
The colorful platforms are the ones found in Deku Palace
*/
void ObjRaillift_DrawDekuFlowerPlatformColorful(Actor* thisx, GlobalContext* globalCtx) {
    Gfx_DrawDListOpa(globalCtx, object_raillift_DL_0071B8);
}
