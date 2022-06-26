/*
 * File: z_obj_shutter.c
 * Overlay: ovl_Obj_Shutter
 * Description: Unused West Clock Town bank closing shutter
 */

#include "z_obj_shutter.h"
#include "objects/object_f53_obj/object_f53_obj.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjShutter*)thisx)

void ObjShutter_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjShutter_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjShutter_Update(Actor* thisx, GlobalContext* globalCtx2);
void ObjShutter_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Shutter_InitVars = {
    ACTOR_OBJ_SHUTTER,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_F53_OBJ,
    sizeof(ObjShutter),
    (ActorFunc)ObjShutter_Init,
    (ActorFunc)ObjShutter_Destroy,
    (ActorFunc)ObjShutter_Update,
    (ActorFunc)ObjShutter_Draw,
};

void ObjShutter_Init(Actor* thisx, GlobalContext* globalCtx) {
}

void ObjShutter_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

static u8 sScheduleScript[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(10, 0, 20, 0, 0x9 - 0x6),
    /* 0x6 */ SCHEDULE_CMD_RET_VAL_L(2),
    /* 0x9 */ SCHEDULE_CMD_RET_VAL_L(1),
};

void ObjShutter_Update(Actor* thisx, GlobalContext* globalCtx2) {
    ObjShutter* this = THIS;
    GlobalContext* globalCtx = globalCtx2;
    ScheduleResult schedule;

    Schedule_RunScript(globalCtx, sScheduleScript, &schedule);
    if (schedule.result == 1) {
        if (this->scheduleResult != schedule.result) {
            this->actor.velocity.y = 0.0f;
        }
        if ((this->verticalOffset >= 80.0f) || (this->scheduleResult == 0)) {
            this->actor.velocity.y = 0.0f;
            this->verticalOffset = 80.0f;
        } else {
            this->verticalOffset += 10.0f;
        }
    } else {
        if (this->scheduleResult != schedule.result) {
            this->actor.velocity.y = 0.0f;
        }
        if (this->verticalOffset != 0.0f) {
            this->actor.velocity.y -= 3.0f;
            this->verticalOffset += this->actor.velocity.y;
            if (this->verticalOffset <= 0.0f) {
                this->actor.velocity.y = fabsf(this->actor.velocity.y) * 0.8f;
                if ((s32)this->actor.velocity.y == 0) {
                    this->actor.velocity.y = 0.0f;
                    this->verticalOffset = 0.0f;
                }
            }
        }
    }
    this->scheduleResult = schedule.result;
}

void ObjShutter_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjShutter* this = THIS;

    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y + this->verticalOffset, this->actor.world.pos.z,
                     MTXMODE_NEW);
    Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
    Matrix_RotateYS(this->actor.world.rot.y, MTXMODE_APPLY);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_f53_obj_DL_0011E0);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
