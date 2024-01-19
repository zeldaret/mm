/*
 * File: z_tg_sw.c
 * Overlay: ovl_TG_Sw
 * Description: Skulltula spider bonk detector
 */

#include "z_tg_sw.h"
#include "z64debug_display.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((TGSw*)thisx)

// Prototypes
void TGSw_Init(Actor* thisx, PlayState* play);
void TGSw_Destroy(Actor* thisx, PlayState* play);
void TGSw_Update(Actor* thisx, PlayState* play);
void TGSw_Draw(Actor* thisx, PlayState* play);

void TGSw_ActionExecuteOneShot(struct TGSw* this, PlayState* play);

ActorInit TG_Sw_InitVars = {
    /**/ ACTOR_TG_SW,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(TGSw),
    /**/ TGSw_Init,
    /**/ TGSw_Destroy,
    /**/ TGSw_Update,
    /**/ TGSw_Draw,
};

void TGSw_ActionDecider(TGSw* this, PlayState* play) {
    f32 scaledAbsoluteRotZ;
    f32 scaledAbsoluteRotY;
    PlayerImpactType playerImpactType;

    if (play->actorCtx.playerImpact.timer != 0) {
        scaledAbsoluteRotY = ABS_ALT(this->actor.world.rot.y) * 4.0f;
        scaledAbsoluteRotZ = ABS_ALT(this->actor.world.rot.z) * 4.0f;

        if ((scaledAbsoluteRotZ < this->actor.xzDistToPlayer) || (scaledAbsoluteRotY < this->actor.playerHeightRel)) {
            return;
        }
        playerImpactType = play->actorCtx.playerImpact.type;
        if ((playerImpactType == PLAYER_IMPACT_BONK) || (playerImpactType == PLAYER_IMPACT_GORON_GROUND_POUND)) {
            this->actionFunc = TGSw_ActionExecuteOneShot;
        }
    }
}

void TGSw_ActionExecuteOneShot(TGSw* this, PlayState* play) {
    Actor* actor = NULL;

    if (1) {}

    do {
        actor = SubS_FindActor(play, actor, ACTORCAT_ENEMY, ACTOR_EN_SW);
        if (actor == NULL) {
            break;
        }
        if ((((this->actor.params & 0xFC) >> 2) & 0xFF) == (((actor->params & 0xFC) >> 2) & 0xFF)) {
            actor->parent = &this->actor;
            actor->speed = ABS_ALT(this->actor.world.rot.x);
            break;
        }
        actor = actor->next;
    } while (actor != NULL);

    actor = NULL;

    do {
        actor = SubS_FindActor(play, actor, ACTORCAT_NPC, ACTOR_EN_SW);

        if (actor == NULL) {
            break;
        }
        if ((((this->actor.params & 0xFC) >> 2) & 0xFF) == (((actor->params & 0xFC) >> 2) & 0xFF)) {
            actor->parent = &this->actor;
            actor->speed = ABS_ALT(this->actor.world.rot.x);
            break;
        }
        actor = actor->next;
    } while (actor != NULL);

    Actor_Kill(&this->actor);
}

void TGSw_Init(Actor* thisx, PlayState* play) {
    TGSw* this = THIS;

    this->actor.csId = this->actor.world.rot.z;
    this->actionFunc = TGSw_ActionDecider;
}

void TGSw_Destroy(Actor* thisx, PlayState* play) {
}

void TGSw_Update(Actor* thisx, PlayState* play) {
    TGSw* this = THIS;

    this->actionFunc(this, play);
}

void TGSw_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    f32 scale;
    s32 absRot;

    if (sREG(0) != 0) {
        absRot = ABS_ALT(thisx->world.rot.z);
        scale = absRot * 0.2f;
        absRot = ABS_ALT(thisx->world.rot.y);

        DebugDisplay_AddObject(thisx->world.pos.x, thisx->world.pos.y, thisx->world.pos.z, 0, thisx->shape.rot.y, 0,
                               0.1f, 0.1f, scale, 160, 160, 160, 255, 6, play->state.gfxCtx);

        scale = absRot * 0.2f;
        DebugDisplay_AddObject(thisx->world.pos.x, thisx->world.pos.y, thisx->world.pos.z, 0, 0, 0, 0.1f, scale, 0.1f,
                               160, 160, 160, 255, 6, play->state.gfxCtx);
        thisx->shape.rot.y += 0x1000;
    }
}
