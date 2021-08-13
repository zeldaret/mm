#include "global.h"

#define THIS ((EnAObj*)thisx)

void EnAObj_Update1(EnAObj* this, GlobalContext* globalCtx);
void EnAObj_Update2(EnAObj* this, GlobalContext* globalCtx);

void EnAObj_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnAObj* this = THIS;

    this->actor.textId = ((this->actor.params >> 8) & 0xFF) | 0x300;
    this->actor.params = (this->actor.params & 0xFF) - 9;
    Actor_ProcessInitChain(&this->actor, &enAObjInitVar);
    ActorShape_Init(&this->actor.shape, 0, func_800B3FC0, 12);
    Collider_InitAndSetCylinder(globalCtx, &this->collision, &this->actor, &enAObjCylinderInit);
    Collider_UpdateCylinder(&this->actor, &this->collision);
    this->actor.colChkInfo.mass = 255;
    this->actionFunc = EnAObj_Update1;
}

void EnAObj_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnAObj* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collision);
}

void EnAObj_Update1(EnAObj* this, GlobalContext* globalCtx) {
    s32 yawDiff;

    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        this->actionFunc = EnAObj_Update2;
    } else {
        yawDiff = ABS_ALT((s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y));

        if ((yawDiff < 0x2800) || ((this->actor.params == 1) && (yawDiff > 0x5800))) {
            func_800B863C(&this->actor, globalCtx);
        }
    }
}

void EnAObj_Update2(EnAObj* this, GlobalContext* globalCtx) {
    if (func_800B867C(&this->actor, globalCtx) != 0) {
        this->actionFunc = EnAObj_Update1;
    }
}

void EnAObj_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnAObj* this = THIS;

    this->actionFunc(this, globalCtx);
    Actor_SetHeight(&this->actor, 45.0f);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collision.base);
}

void EnAObj_Draw(Actor* thisx, GlobalContext* globalCtx) {
    func_800BDFC0(globalCtx, enAObjDisplayLists[thisx->params]);
}
