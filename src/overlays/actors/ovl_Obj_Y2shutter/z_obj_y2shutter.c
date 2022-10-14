/*
 * File: z_obj_y2shutter.c
 * Overlay: ovl_Obj_Y2shutter
 * Description: Pirates' Fortress sliding grated/barred shutters
 */

#include "z_obj_y2shutter.h"
#include "objects/object_kaizoku_obj/object_kaizoku_obj.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjY2shutter*)thisx)

void ObjY2shutter_Init(Actor* thisx, PlayState* play);
void ObjY2shutter_Destroy(Actor* thisx, PlayState* play);
void ObjY2shutter_Update(Actor* thisx, PlayState* play);
void ObjY2shutter_Draw(Actor* thisx, PlayState* play);

typedef struct ShutterInfo {
    /* 0x00 */ Gfx* dList;
    /* 0x04 */ CollisionHeader* colHeader;
    /* 0x08 */ f32 raisedOffsetY;
    /* 0x0C */ f32 raiseVelocity;
    /* 0x10 */ f32 raiseAccel;
    /* 0x14 */ f32 lowerVelocity;
    /* 0x18 */ f32 lowerAccel;
    /* 0x1C */ u8 raiseStartSettleTimer;
    /* 0x1D */ u8 raiseEndAndCloseSettleTimer;
    /* 0x1E */ u8 raiseTimer;
} ShutterInfo; // size = 0x20

const ActorInit Obj_Y2shutter_InitVars = {
    ACTOR_OBJ_Y2SHUTTER,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KAIZOKU_OBJ,
    sizeof(ObjY2shutter),
    (ActorFunc)ObjY2shutter_Init,
    (ActorFunc)ObjY2shutter_Destroy,
    (ActorFunc)ObjY2shutter_Update,
    (ActorFunc)ObjY2shutter_Draw,
};

ShutterInfo sShutterInfo[] = {
    { gPirateBarredShutterDL, &gPirateBarredShutterCol, 120.0f, 20.0f, 3.0f, -20.0f, 3.0f, 4, 8, 160 },
    { gPirateGratedShutterDL, &gPirateGratedShutterCol, 150.0f, 1.0f, 0.04f, -1.0f, 0.04f, 6, 12, 160 },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 800, ICHAIN_STOP),
};

void ObjY2shutter_Init(Actor* thisx, PlayState* play) {
    s32 pad[2];
    ShutterInfo* info = &sShutterInfo[OBJY2SHUTTER_GET_TYPE(thisx)];
    ObjY2shutter* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 0);
    DynaPolyActor_LoadMesh(play, &this->dyna, info->colHeader);
}

void ObjY2shutter_Destroy(Actor* thisx, PlayState* play) {
    ObjY2shutter* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void ObjY2shutter_SetupRaise(ObjY2shutter* this, ShutterInfo* info, ShutterType shutterType) {
    this->raiseTimer = info->raiseTimer;
    this->settleTimer = info->raiseStartSettleTimer;
    if (shutterType == SHUTTER_BARRED) {
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_METALDOOR_OPEN);
    }
}

void ObjY2shutter_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    ObjY2shutter* this = THIS;
    ShutterType shutterType = OBJY2SHUTTER_GET_TYPE(&this->dyna.actor);
    ShutterInfo* info = &sShutterInfo[shutterType];
    f32 targetPosY = this->dyna.actor.world.pos.y;
    f32 targetVelocityY = 0.0f;
    f32 accelY = 0.0f;

    sShutterInfo[0].raiseTimer = DREG(84) + 160;
    sShutterInfo[1].raiseTimer = DREG(85) + 160;

    if (((shutterType == SHUTTER_BARRED) && (DREG(86) != 0)) || ((shutterType != SHUTTER_BARRED) && (DREG(87) != 0))) {
        if (shutterType == SHUTTER_BARRED) {
            DREG(86) = 0;
        } else {
            DREG(87) = 0;
        }

        if (Flags_GetSwitch(play, OBJY2SHUTTER_GET_SWITCHFLAG(&this->dyna.actor))) {
            Flags_UnsetSwitch(play, OBJY2SHUTTER_GET_SWITCHFLAG(&this->dyna.actor));
        } else {
            Flags_SetSwitch(play, OBJY2SHUTTER_GET_SWITCHFLAG(&this->dyna.actor));
        }
    }

    if (this->settleTimer == 0) {
        if (Flags_GetSwitch(play, OBJY2SHUTTER_GET_SWITCHFLAG(&this->dyna.actor))) {
            s16 cutscene = this->dyna.actor.cutscene;

            if (this->raiseTimer == 0) {
                if ((cutscene >= 0) && !ActorCutscene_GetCanPlayNext(cutscene)) {
                    ActorCutscene_SetIntentToPlay(cutscene);
                } else if (cutscene >= 0) {
                    ActorCutscene_StartAndSetUnkLinkFields(cutscene, &this->dyna.actor);
                    this->raiseTimer = -1;
                } else {
                    ObjY2shutter_SetupRaise(this, info, shutterType);
                }
            } else if (this->raiseTimer < 0) {
                if (func_800F22C4(cutscene, &this->dyna.actor)) {
                    ObjY2shutter_SetupRaise(this, info, shutterType);
                }
            } else {
                targetPosY = this->dyna.actor.home.pos.y + info->raisedOffsetY;
                targetVelocityY = info->raiseVelocity;
                accelY = info->raiseAccel;
                if (this->raiseTimer < 2) {
                    Flags_UnsetSwitch(play, OBJY2SHUTTER_GET_SWITCHFLAG(&this->dyna.actor));
                } else {
                    this->raiseTimer--;
                }
            }
        } else if (this->raiseTimer != 0) {
            this->raiseTimer = 0;
            this->settleTimer = info->raiseStartSettleTimer;
            if (shutterType == SHUTTER_BARRED) {
                Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_METALDOOR_CLOSE);
            }
        } else {
            targetPosY = this->dyna.actor.home.pos.y;
            targetVelocityY = info->lowerVelocity;
            accelY = info->lowerAccel;
        }
    }

    Math_StepToF(&this->dyna.actor.velocity.y, targetVelocityY, accelY);
    this->dyna.actor.world.pos.y += this->dyna.actor.velocity.y;

    if (((this->dyna.actor.world.pos.y - targetPosY) * targetVelocityY) >= 0.0f) {
        this->dyna.actor.world.pos.y = targetPosY;
        this->dyna.actor.velocity.y = 0.0f;
        if (!this->isStationary) {
            this->isStationary = true;
            this->settleTimer = info->raiseEndAndCloseSettleTimer;
            if (shutterType != SHUTTER_BARRED) {
                Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_METALDOOR_STOP);
            }
        }
    } else {
        this->isStationary = false;
        if (shutterType != SHUTTER_BARRED) {
            func_800B9010(&this->dyna.actor, NA_SE_EV_METALDOOR_SLIDE - SFX_FLAG);
        }
    }

    if (DECR(this->settleTimer)) {
        this->dyna.actor.shape.yOffset = 2.0f * (this->settleTimer & 1) * this->settleTimer;
    }
}

void ObjY2shutter_Draw(Actor* thisx, PlayState* play) {
    ObjY2shutter* this = THIS;
    ShutterInfo* info = &sShutterInfo[(OBJY2SHUTTER_GET_TYPE(&this->dyna.actor))];

    Gfx_DrawDListOpa(play, info->dList);
}
