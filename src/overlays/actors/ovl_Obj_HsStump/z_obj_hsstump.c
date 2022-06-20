/*
 * File: z_obj_hsstump.c
 * Overlay: ovl_Obj_HsStump
 * Description: Ikana Canyon - Hookshotable Tree
 */

#include "z_obj_hsstump.h"
#include "objects/object_hsstump/object_hsstump.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjHsStump*)thisx)

void ObjHsStump_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHsStump_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHsStump_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHsStump_Draw(Actor* thisx, GlobalContext* globalCtx);

void ObjHsStump_SetupIdle(ObjHsStump* this, GlobalContext* globalCtx);
void ObjHsStump_Idle(ObjHsStump* this, GlobalContext* globalCtx);
void ObjHsStump_SetupAppear(ObjHsStump* this, GlobalContext* globalCtx);
void ObjHsStump_Appear(ObjHsStump* this, GlobalContext* globalCtx);

const ActorInit Obj_HsStump_InitVars = {
    ACTOR_OBJ_HSSTUMP,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_HSSTUMP,
    sizeof(ObjHsStump),
    (ActorFunc)ObjHsStump_Init,
    (ActorFunc)ObjHsStump_Destroy,
    (ActorFunc)ObjHsStump_Update,
    (ActorFunc)ObjHsStump_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 180, ICHAIN_STOP),
};

static Vec3f sIceSmokeAccel = { 0.0f, 0.0f, 0.0f };

void ObjHsStump_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjHsStump* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    this->isHidden = OBJHSSTUMP_GET_ISHIDDEN(thisx);
    this->switchFlag = OBJHSSTUMP_GET_SWITCHFLAG(thisx);
    DynaPolyActor_Init(&this->dyna, 1);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_hsstump_Colheader_0011B0);
    switch (this->isHidden) {
        case true:
            if (Flags_GetSwitch(globalCtx, this->switchFlag)) {
                this->isHidden = false;
            } else {
                this->dyna.actor.draw = NULL;
                Actor_SetScale(&this->dyna.actor, 0.0f);
                func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
            }
        case false:
            ObjHsStump_SetupIdle(this, globalCtx);
    }
}

void ObjHsStump_SetupIdle(ObjHsStump* this, GlobalContext* globalCtx) {
    this->actionFunc = ObjHsStump_Idle;
}

void ObjHsStump_Idle(ObjHsStump* this, GlobalContext* globalCtx) {
    if (this->isHidden == true && Flags_GetSwitch(globalCtx, this->switchFlag)) {
        ObjHsStump_SetupAppear(this, globalCtx);
    }
}

void ObjHsStump_SetupAppear(ObjHsStump* this, GlobalContext* globalCtx) {
    this->dyna.actor.draw = ObjHsStump_Draw;
    this->framesAppeared = 0;
    this->rotAngle = 0;
    this->rotFactor = 3640.0f;
    func_8019F128(NA_SE_EN_NPC_APPEAR);
    this->actionFunc = ObjHsStump_Appear;
}

void ObjHsStump_Appear(ObjHsStump* this, GlobalContext* globalCtx) {
    if (this->framesAppeared >= 0) {
        Math_SmoothStepToF(&this->rotFactor, 0.0f, 1.0f, this->framesAppeared + 18.0f, 0.01f);
        this->dyna.actor.shape.rot.x = (Math_SinS(this->rotAngle) * this->rotFactor) + this->dyna.actor.home.rot.x;
        this->dyna.actor.shape.rot.z = (Math_SinS(this->rotAngle * 2) * this->rotFactor) + this->dyna.actor.home.rot.z;
        this->rotAngle += 0x2000;
    }
    if (this->framesAppeared <= 10) {
        if (this->framesAppeared == 0) {
            s32 i;
            f32 angleDeg;
            s16 numDirections = 4;
            Vec3f iceSmokePosOffset;
            Vec3f iceSmokeVelOffset;
            s16 offsetAngle;
            Vec3f iceSmokeVel;
            f32 angleBrad;
            Vec3f iceSmokePos;

            iceSmokePosOffset.x = 1.0f;
            iceSmokePosOffset.y = 0.5f;
            iceSmokePosOffset.z = 0.0f;

            iceSmokeVelOffset.x = 1.0f;
            iceSmokeVelOffset.y = 0.5f;
            iceSmokeVelOffset.z = 0.0f;

            angleDeg = (360.0f / numDirections);
            angleBrad = (s32)(angleDeg * (0x10000 / 360.0f));

            for (i = 0; i < numDirections; i++) {
                offsetAngle = i * angleBrad;
                Lib_Vec3f_TranslateAndRotateY(&this->dyna.actor.world.pos, offsetAngle, &iceSmokePosOffset,
                                              &iceSmokePos);
                Lib_Vec3f_TranslateAndRotateY(&gZeroVec3f, offsetAngle, &iceSmokeVelOffset, &iceSmokeVel);
                EffectSsIceSmoke_Spawn(globalCtx, &iceSmokePos, &iceSmokeVel, &sIceSmokeAccel, 100);
            }
        }
    }
    if (this->framesAppeared >= 10) {
        Math_SmoothStepToF(&this->dyna.actor.scale.x, 18.0f * 0.01f, 1.0f, 0.01f, 0.001f);
        Actor_SetScale(&this->dyna.actor, this->dyna.actor.scale.x);
    }
    if (this->dyna.actor.scale.x == 18.0f * 0.01f) {
        this->isHidden = false;
        func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        ObjHsStump_SetupIdle(this, globalCtx);
    }
    this->framesAppeared++;
}

void ObjHsStump_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjHsStump* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void ObjHsStump_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjHsStump* this = THIS;

    this->actionFunc(this, globalCtx);
}

void ObjHsStump_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Gfx_DrawDListOpa(globalCtx, object_hsstump_DL_0003B8);
}
