/*
 * File: z_dm_opstage.c
 * Overlay: ovl_Dm_Opstage
 * Description: Lost Woods Cutscene Trees and Floor
 */

#include "z_dm_opstage.h"
#include "objects/object_keikoku_demo/object_keikoku_demo.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmOpstage*)thisx)

void DmOpstage_Init(Actor* thisx, PlayState* play);
void DmOpstage_Destroy(Actor* thisx, PlayState* play);
void DmOpstage_Update(Actor* thisx, PlayState* play);
void DmOpstage_Draw(Actor* thisx, PlayState* play);

void DmOpstage_FollowCutsceneScript(DmOpstage* this, PlayState* play);

const ActorInit Dm_Opstage_InitVars = {
    ACTOR_DM_OPSTAGE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_KEIKOKU_DEMO,
    sizeof(DmOpstage),
    (ActorFunc)DmOpstage_Init,
    (ActorFunc)DmOpstage_Destroy,
    (ActorFunc)DmOpstage_Update,
    (ActorFunc)DmOpstage_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 300, ICHAIN_STOP),
};

void DmOpstage_SetupAction(DmOpstage* this, DmOpstageActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void DmOpstage_Init(Actor* thisx, PlayState* play) {
    DmOpstage* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DmOpstage_SetupAction(this, DmOpstage_FollowCutsceneScript);
    Actor_SetScale(&this->dyna.actor, 0.1f);

    if (DMOPSTAGE_GET_TYPE(&this->dyna.actor) == DMOPSTAGE_TYPE_GROUND) {
        DynaPolyActor_Init(&this->dyna, 0);
        DynaPolyActor_LoadMesh(play, &this->dyna, &gKeikokuDemoFloorColliderHeader);
    }

    if (DMOPSTAGE_GET_TYPE(&this->dyna.actor) > DMOPSTAGE_TYPE_GROUND) {
        // trees move their world pos to map origin/center, then draw at their starting position
        this->drawOffset.x = this->dyna.actor.world.pos.x;
        this->drawOffset.y = this->dyna.actor.world.pos.y;
        this->drawOffset.z = this->dyna.actor.world.pos.z;
        this->dyna.actor.world.pos.x = 0.0f;
        this->dyna.actor.world.pos.y = 0.0f;
        this->dyna.actor.world.pos.z = 0.0f;
    }
}

void DmOpstage_Destroy(Actor* thisx, PlayState* play) {
    DmOpstage* this = THIS;

    if (DMOPSTAGE_GET_TYPE(&this->dyna.actor) == DMOPSTAGE_TYPE_GROUND) {
        DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
    }
}

void DmOpstage_FollowCutsceneScript(DmOpstage* this, PlayState* play) {
    s32 actionIndex;

    if (DMOPSTAGE_GET_TYPE(&this->dyna.actor) == DMOPSTAGE_TYPE_GROUND) {
        if (Cutscene_CheckActorAction(play, 0x73)) {
            actionIndex = Cutscene_GetActorActionIndex(play, 0x73);
            if (play->csCtx.actorActions[actionIndex]->action == 2) {
                this->dyna.actor.scale.x = 0.075f;
                this->dyna.actor.scale.z = 0.3f;
            } else {
                this->dyna.actor.scale.x = 0.1f;
                this->dyna.actor.scale.z = 0.1f;
            }
            Cutscene_ActorTranslateAndYaw(&this->dyna.actor, play, actionIndex);
        }
    } else if (Cutscene_CheckActorAction(play, DMOPSTAGE_GET_ACTORACTION(&this->dyna.actor) + 0x74)) {
        Cutscene_ActorTranslateAndYaw(
            &this->dyna.actor, play,
            Cutscene_GetActorActionIndex(play, DMOPSTAGE_GET_ACTORACTION(&this->dyna.actor) + 0x74));
    }
}

void DmOpstage_Update(Actor* thisx, PlayState* play) {
    DmOpstage* this = THIS;

    this->actionFunc(this, play);
    if ((play->sceneNum == SCENE_SPOT00) && (gSaveContext.sceneSetupIndex == 0) && (play->csCtx.frames == 480)) {
        // This actor is responsible for playing the fairy sound during the exposition in the intro,
        // during the transition to Lost Woods, before Ocarina gets stolen.
        func_8019F128(NA_SE_EV_NAVY_FLY_REBIRTH);
    }
}

void DmOpstage_Draw(Actor* thisx, PlayState* play) {
    DmOpstage* this = THIS;

    if (DMOPSTAGE_GET_TYPE(&this->dyna.actor) > DMOPSTAGE_TYPE_GROUND) {
        // Assumption: worldPos is being manipulated by cutscene
        Matrix_Translate(this->dyna.actor.world.pos.x + this->drawOffset.x,
                         this->dyna.actor.world.pos.y + this->drawOffset.y,
                         this->dyna.actor.world.pos.z + this->drawOffset.z, MTXMODE_NEW);
        Matrix_RotateYS(this->dyna.actor.world.rot.y, MTXMODE_APPLY);
        Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
    }

    switch (DMOPSTAGE_GET_TYPE(&this->dyna.actor)) {
        case DMOPSTAGE_TYPE_GROUND:
            Gfx_DrawDListOpa(play, gKeikokuDemoFloorDL);
            Gfx_DrawDListXlu(play, gKeikokuDemoFloorEmptyDL);
            break;

        case DMOPSTAGE_TYPE_ROOT_TREE:
            Gfx_DrawDListOpa(play, gKeikokuDemoTallTreeWithRootBaseDL);
            Gfx_DrawDListXlu(play, gKeikokuDemoTallTreeWithRootBaseEmptyDL);
            break;

        case DMOPSTAGE_TYPE_CUT_TREE:
            Gfx_DrawDListOpa(play, gKeikokuDemoTallTreeCutDL);
            Gfx_DrawDListXlu(play, gKeikokuDemoTallTreeCutEmptyDL);
            break;

        case DMOPSTAGE_TYPE_STRAIGHT_TREE:
            Gfx_DrawDListOpa(play, gKeikokuDemoTallTreeStraightDL);
            Gfx_DrawDListXlu(play, gKeikokuDemoTallTreeStraightEmptyDL);
            break;
    }
}
