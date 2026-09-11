/*
 * File: z_obj_lupygamelift.c
 * Overlay: ovl_Obj_Lupygamelift
 * Description: Deku Scrub Playground - Rupee Elevator
 */

#include "z_obj_lupygamelift.h"
#include "assets/objects/object_raillift/object_raillift.h"

#define FLAGS (ACTOR_FLAG_UPDATE_CULLING_DISABLED | ACTOR_FLAG_DRAW_CULLING_DISABLED)

void ObjLupygamelift_Init(Actor* thisx, PlayState* play);
void ObjLupygamelift_Destroy(Actor* thisx, PlayState* play);
void ObjLupygamelift_Update(Actor* thisx, PlayState* play);
void ObjLupygamelift_Draw(Actor* thisx, PlayState* play);

void ObjLupygamelift_SetupWait(ObjLupygamelift* this);
void ObjLupygamelift_Wait(ObjLupygamelift* this, PlayState* play);
void ObjLupygamelift_StartMoving(ObjLupygamelift* this);
void ObjLupygamelift_Moving(ObjLupygamelift* this, PlayState* play);

ActorProfile Obj_Lupygamelift_Profile = {
    /**/ ACTOR_OBJ_LUPYGAMELIFT,
    /**/ ACTORCAT_BG,
    /**/ FLAGS,
    /**/ OBJECT_RAILLIFT,
    /**/ sizeof(ObjLupygamelift),
    /**/ ObjLupygamelift_Init,
    /**/ ObjLupygamelift_Destroy,
    /**/ ObjLupygamelift_Update,
    /**/ ObjLupygamelift_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(cullingVolumeDistance, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(cullingVolumeScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(cullingVolumeDownward, 400, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void ObjLupygamelift_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    ObjLupygamelift* this = (ObjLupygamelift*)thisx;
    Path* path;
    s32 params;

    Actor_ProcessInitChain(thisx, sInitChain);
    this->dyna.actor.scale.y = 0.15f;
    this->dyna.actor.shape.rot.x = 0;
    this->dyna.actor.world.rot.x = 0;
    this->dyna.actor.shape.rot.z = 0;
    this->dyna.actor.world.rot.z = 0;
    this->timer = 0;
    Actor_UpdateBgCheckInfo(play, thisx, 0.0f, 0.0f, 0.0f, UPDBGCHECKINFO_FLAG_4);
    ActorShape_Init(&thisx->shape, 0.0f, ActorShadow_DrawSquare, 0.0f);
    DynaPolyActor_Init(&this->dyna, DYNA_TRANSFORM_POS);
    DynaPolyActor_LoadMesh(play, &this->dyna, &object_raillift_Colheader_0048D0);
    this->targetSpeedXZ = thisx->home.rot.z * 0.1f;
    if (this->targetSpeedXZ < 0.0f) {
        this->targetSpeedXZ = -this->targetSpeedXZ;
    }
    this->dyna.actor.home.rot.x = 0;
    this->dyna.actor.home.rot.y = 0;
    this->dyna.actor.home.rot.z = 0;

    path = &play->setupPathList[OBJLUPYGAMELIFT_GET_PATH_INDEX(thisx)];
    this->pointIndex = OBJLUPYGAMELIFT_GET_START_POINT(thisx);
    this->count = path->count;
    if (this->pointIndex >= this->count) {
        this->pointIndex = 0;
    }
    this->pathPoints = Lib_SegmentedToVirtual(path->points);
    Actor_SpawnAsChild(&play->actorCtx, &this->dyna.actor, play, ACTOR_OBJ_ETCETERA, this->dyna.actor.world.pos.x,
                       this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, this->dyna.actor.shape.rot.x,
                       this->dyna.actor.shape.rot.y, this->dyna.actor.shape.rot.z, 0);
    if (OBJLUPYGAMELIFT_GET_RUPEE_COLOR(thisx) != 0) {
        params = 1;
    } else {
        params = 0;
    }
    Actor_Spawn(&play->actorCtx, play, ACTOR_EN_GAMELUPY, this->dyna.actor.home.pos.x, this->dyna.actor.home.pos.y,
                this->dyna.actor.home.pos.z, 0, 0, 0, params);
    ObjLupygamelift_SetupWait(this);
}

void ObjLupygamelift_Destroy(Actor* thisx, PlayState* play) {
    ObjLupygamelift* this = (ObjLupygamelift*)thisx;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void ObjLupygamelift_UpdateShadow(ObjLupygamelift* this) {
    static f32 sShadowAlphaMin = 100.0f;
    static f32 sShadowAlphaMax = 255.0f;
    static f32 sShadowScaleMin = 5.0f;
    static f32 sShadowScaleMax = 10.0f;
    static f32 sLiftHeightMin = -240.0f;
    static f32 sLiftHeightMax = 30.0f;
    f32 shadowAlphaRange = sShadowAlphaMax - sShadowAlphaMin;
    f32 liftHeightRange = sLiftHeightMax - sLiftHeightMin;
    f32 shadowScaleRange = sShadowScaleMax - sShadowScaleMin;
    f32 liftHeight;
    f32 percent;

    liftHeight = this->dyna.actor.world.pos.y - sLiftHeightMin;
    if (liftHeight < 0.0f) {
        percent = 0.0f;
    } else if (liftHeightRange < liftHeight) {
        percent = 1.0f;
    } else {
        percent = liftHeight / liftHeightRange;
    }
    this->dyna.actor.shape.shadowAlpha = sShadowAlphaMax - (percent * shadowAlphaRange);
    this->dyna.actor.shape.shadowScale = sShadowScaleMax - (percent * shadowScaleRange);
}

void ObjLupygamelift_SetupWait(ObjLupygamelift* this) {
    this->timer = 5;
    this->actionFunc = ObjLupygamelift_Wait;
}

void ObjLupygamelift_Wait(ObjLupygamelift* this, PlayState* play) {
    if (this->timer == 0) {
        ObjLupygamelift_StartMoving(this);
    } else {
        this->timer--;
    }
}

void ObjLupygamelift_StartMoving(ObjLupygamelift* this) {
    this->actionFunc = ObjLupygamelift_Moving;
    this->dyna.actor.speed = this->targetSpeedXZ;
}

void ObjLupygamelift_Moving(ObjLupygamelift* this, PlayState* play) {
    f32 distRemaining;
    Vec3f target;

    target.x = this->pathPoints[this->pointIndex].x;
    target.y = this->pathPoints[this->pointIndex].y;
    target.z = this->pathPoints[this->pointIndex].z;
    distRemaining = Math_Vec3f_StepTo(&this->dyna.actor.world.pos, &target, this->dyna.actor.speed);
    if (distRemaining > 30.0f) {
        Math_SmoothStepToF(&this->dyna.actor.speed, this->targetSpeedXZ, 0.5f, 5.0f, 0.1f);
    } else if (distRemaining > 0.0f) {
        Math_SmoothStepToF(&this->dyna.actor.speed, 5.0f, 0.5f, 5.0f, 1.0f);
    } else {
        if (this->pointIndex < (this->count - 1)) {
            this->pointIndex++;
        } else {
            this->pointIndex = 0;
        }
    }
    if (this->dyna.actor.child->update == NULL) {
        this->dyna.actor.child = NULL;
    } else {
        this->dyna.actor.child->world.pos.x = this->dyna.actor.world.pos.x;
        this->dyna.actor.child->world.pos.y = this->dyna.actor.world.pos.y;
        this->dyna.actor.child->world.pos.z = this->dyna.actor.world.pos.z;
    }
    ObjLupygamelift_UpdateShadow(this);
}

void ObjLupygamelift_Update(Actor* thisx, PlayState* play) {
    ObjLupygamelift* this = (ObjLupygamelift*)thisx;

    this->actionFunc(this, play);
}

void ObjLupygamelift_Draw(Actor* thisx, PlayState* play) {
    Gfx_DrawDListOpa(play, object_raillift_DL_0071B8);
}
