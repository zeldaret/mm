/*
 * File: z_dm_ravine.c
 * Overlay: ovl_Dm_Ravine
 * Description: Lost Woods Cutscene - Tree Trunk
 */

#include "z_dm_ravine.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmRavine*)thisx)

void DmRavine_Init(Actor* thisx, GlobalContext* globalCtx);
void DmRavine_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmRavine_DoNothing(DmRavine* this, GlobalContext* globalCtx);
void DmRavine_Update(Actor* thisx, GlobalContext* globalCtx);
void DmRavine_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Dm_Ravine_InitVars = {
    ACTOR_DM_RAVINE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_KEIKOKU_DEMO,
    sizeof(DmRavine),
    (ActorFunc)DmRavine_Init,
    (ActorFunc)DmRavine_Destroy,
    (ActorFunc)DmRavine_Update,
    (ActorFunc)DmRavine_Draw,
};

void DmRavine_Init(Actor* thisx, GlobalContext* globalCtx) {
    DmRavine* this = THIS;
    u8 flag = gSaveContext.save.weekEventReg[0];
    if (((flag & 0x10) | cREG(0)) != 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->isActive = false;
    globalCtx->roomCtx.unk7A[0] = 1;
    globalCtx->roomCtx.unk7A[1] = 0;
    this->state = 0;
    Actor_SetScale(&this->actor, 1.0f);
    this->actionFunc = DmRavine_DoNothing;
}

void DmRavine_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void DmRavine_DoNothing(DmRavine* this, GlobalContext* globalCtx) {
}

void DmRavine_Update(Actor* thisx, GlobalContext* globalCtx) {
    DmRavine* this = THIS;
    RoomContext* roomCtx;

    switch ((DmRavineState)this->state) {
        case DM_RAVINE_STATE_INITIALIZED:
            return;
        case DM_RAVINE_STATE_ACTIVE:
            this->isActive = true;
            globalCtx->roomCtx.unk7A[1]++;
            if (globalCtx->roomCtx.unk7A[1] > 254) {
                globalCtx->roomCtx.unk7A[1] = 254;
                if (globalCtx->csCtx.frames > 700) {
                    globalCtx->roomCtx.unk7A[1] = 255;
                    globalCtx->roomCtx.unk7A[0] = 0;
                    this->state++; // -> DM_RAVINE_STATE_PENDING_DEATH
                }
            }
            break;
        case DM_RAVINE_STATE_PENDING_DEATH:
            Actor_MarkForDeath(&this->actor);
            break;
    }
}

void DmRavine_Draw(Actor* thisx, GlobalContext* globalCtx) {
}
