/*
 * File: z_tg_sw.c
 * Overlay: ovl_TG_Sw
 * Description: Skulltula spider bonk detector
 */

#include "z_tg_sw.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((TGSw*)thisx)

// Prototypes
void TGSw_Init(Actor* thisx, GlobalContext* globalCtx);
void TGSw_Destroy(Actor* thisx, GlobalContext* globalCtx);
void TGSw_Update(Actor* thisx, GlobalContext* globalCtx);
void TGSw_Draw(Actor* thisx, GlobalContext* globalCtx);

void TGSw_ActionExecuteOneShot(struct TGSw* this, GlobalContext* globalCtx);

const ActorInit TG_Sw_InitVars = {
    ACTOR_TG_SW,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(TGSw),
    (ActorFunc)TGSw_Init,
    (ActorFunc)TGSw_Destroy,
    (ActorFunc)TGSw_Update,
    (ActorFunc)TGSw_Draw,
};

void TGSw_ActionDecider(TGSw* this, GlobalContext* globalCtx) {
    f32 scaledAbsoluteRotZ;
    f32 scaledAbsoluteRotY;
    u8 unk1F4;

    // Maybe actorCtx Debug Flag?
    if (globalCtx->actorCtx.unk1F5 != 0) {
        scaledAbsoluteRotY = ABS_ALT(this->actor.world.rot.y) * 4.0f;
        scaledAbsoluteRotZ = ABS_ALT(this->actor.world.rot.z) * 4.0f;

        if ((scaledAbsoluteRotZ < this->actor.xzDistToPlayer) || (scaledAbsoluteRotY < this->actor.playerHeightRel)) {
            return;
        }
        unk1F4 = globalCtx->actorCtx.unk1F4;
        if (unk1F4 == 2 || unk1F4 == 0) {
            this->actionFunc = &TGSw_ActionExecuteOneShot;
        }
    }
}

void TGSw_ActionExecuteOneShot(TGSw* this, GlobalContext* globalCtx) {
    Actor* actor = NULL;

    if (1) {}

    do {
        actor = SubS_FindActor(globalCtx, actor, ACTORCAT_ENEMY, ACTOR_EN_SW);
        if (actor == NULL) {
            break;
        }
        if ((((this->actor.params & 0xFC) >> 2) & 0xFF) == (((actor->params & 0xFC) >> 2) & 0xFF)) {
            actor->parent = &this->actor;
            actor->speedXZ = ABS_ALT(this->actor.world.rot.x);
            break;
        }
        actor = actor->next;
    } while (actor != NULL);

    actor = NULL;

    do {
        actor = SubS_FindActor(globalCtx, actor, ACTORCAT_NPC, ACTOR_EN_SW);

        if (actor == NULL) {
            break;
        }
        if ((((this->actor.params & 0xFC) >> 2) & 0xFF) == (((actor->params & 0xFC) >> 2) & 0xFF)) {
            actor->parent = &this->actor;
            actor->speedXZ = ABS_ALT(this->actor.world.rot.x);
            break;
        }
        actor = actor->next;
    } while (actor != NULL);

    Actor_MarkForDeath(&this->actor);
}

void TGSw_Init(Actor* thisx, GlobalContext* globalCtx) {
    TGSw* this = THIS;
    this->actor.cutscene = this->actor.world.rot.z;
    this->actionFunc = &TGSw_ActionDecider;
}

void TGSw_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ;
}

void TGSw_Update(Actor* thisx, GlobalContext* globalCtx) {
    TGSw* this = THIS;
    this->actionFunc(this, globalCtx);
}

void TGSw_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    f32 scale;
    s32 absRot;

    if (sREG(0) != 0) {
        absRot = ABS_ALT(thisx->world.rot.z);
        scale = absRot * 0.2f;
        absRot = ABS_ALT(thisx->world.rot.y);

        DebugDisplay_AddObject(thisx->world.pos.x, thisx->world.pos.y, thisx->world.pos.z, 0, thisx->shape.rot.y, 0,
                               0.1f, 0.1f, scale, 160, 160, 160, 255, 6, globalCtx->state.gfxCtx);

        scale = absRot * 0.2f;
        DebugDisplay_AddObject(thisx->world.pos.x, thisx->world.pos.y, thisx->world.pos.z, 0, 0, 0, 0.1f, scale, 0.1f,
                               160, 160, 160, 255, 6, globalCtx->state.gfxCtx);
        thisx->shape.rot.y += 0x1000;
    }
}
