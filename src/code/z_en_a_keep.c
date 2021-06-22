#include <ultra64.h>
#include <global.h>

#define THIS ((EnAObj*)thisx)

void EnAObj_Update1(EnAObj* this, struct GlobalContext* globalCtx);
void EnAObj_Update2(EnAObj* this, struct GlobalContext* globalCtx);

void EnAObj_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnAObj* this = THIS;

    this->base.textId = ((this->base.params >> 8) & 0xFF) | 0x300;
    this->base.params = (this->base.params & 0xFF) - 9;
    Actor_ProcessInitChain(&this->base, &enAObjInitVar);

    ActorShape_Init(&this->base.shape, 0, func_800B3FC0, 12);
    Collider_InitAndSetCylinder(globalCtx, &this->collision, &this->base, &enAObjCylinderInit);
    Collider_UpdateCylinder(&this->base, &this->collision);

    this->base.colChkInfo.mass = 255;
    this->actionFunc = (EnAObjActionFunc)EnAObj_Update1;
}

void EnAObj_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnAObj* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collision);
}

void EnAObj_Update1(EnAObj* this, GlobalContext* globalCtx) {
    s16 v0;
    s32 v1;
    if (func_800B84D0(&this->base, globalCtx) != 0) {
        this->actionFunc = (EnAObjActionFunc)EnAObj_Update2;
    } else {
        v0 = this->base.yawTowardsPlayer - this->base.shape.rot.y;
        v1 = (v0 < 0)? -v0 : v0;
        if ((v1 < 10240) || ((this->base.params == 1) && (v1 > 22528))) {
            func_800B863C(&this->base, globalCtx);
        }
    }
}

void EnAObj_Update2(EnAObj* this, struct GlobalContext* globalCtx) {
    if (func_800B867C(&this->base, globalCtx) != 0) {
        this->actionFunc = (EnAObjActionFunc)EnAObj_Update1;
    }
}

void EnAObj_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnAObj* this = THIS;

    this->actionFunc((struct EnAObj *)this, globalCtx);

    Actor_SetHeight(&this->base, 45.0f);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collision.base);
}

void EnAObj_Draw(Actor* thisx, GlobalContext* globalCtx) {
    func_800BDFC0(globalCtx, enAObjDisplayLists[thisx->params]);
}
