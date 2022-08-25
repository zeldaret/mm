/*
 * File: z_bg_umajump.c
 * Overlay: ovl_Bg_Umajump
 * Description: Horse Jumping Fence
 */

#include "z_bg_umajump.h"
#include "assets/objects/object_umajump/object_umajump.h"

#define FLAGS 0x00000000

#define THIS ((BgUmajump*)thisx)

void BgUmajump_Init(Actor* thisx, PlayState* play);
void BgUmajump_Destroy(Actor* thisx, PlayState* play);
void BgUmajump_Update(Actor* thisx, PlayState* play);
void BgUmajump_Draw(Actor* thisx, PlayState* play);

void func_8091A5A0(Actor* thisx, PlayState* play);

const ActorInit Bg_Umajump_InitVars = {
    ACTOR_BG_UMAJUMP,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(BgUmajump),
    (ActorFunc)BgUmajump_Init,
    (ActorFunc)BgUmajump_Destroy,
    (ActorFunc)BgUmajump_Update,
    (ActorFunc)NULL,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void func_80919F30(BgUmajump* this, PlayState* play) {
    if (this->objectIndex >= 90) {
        this->objectIndex = 0;
    }

    this->objectIndex++;
    this->dyna.actor.shape.yOffset =
        Math_SinS((this->objectIndex / 90.0f) * 65536.0f) * (20.0f / this->dyna.actor.scale.y);
}

void BgUmajump_StopCutscene(BgUmajump* this, PlayState* play) {
    if ((play->csCtx.frames >= 6) && !this->hasSoundPlayed) {
        this->hasSoundPlayed = true;
        play_sound(NA_SE_EV_KID_HORSE_NEIGH);
    }

    if (!play->csCtx.state) {
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        this->dyna.actor.update = Actor_Noop;
    }
}

void BgUmajump_PlayCutscene(BgUmajump* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        gSaveContext.save.weekEventReg[89] |= 0x20;
        this->actionFunc = BgUmajump_StopCutscene;
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void BgUmajump_CheckDistance(BgUmajump* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if ((this->horse != NULL) && (player != NULL) &&
        (Math3D_XZDistance(this->horse->world.pos.x, this->horse->world.pos.z, player->actor.world.pos.x,
                           player->actor.world.pos.z) < 1400.0f)) {
        this->actionFunc = BgUmajump_PlayCutscene;
    }
}

void BgUmajump_Init(Actor* thisx, PlayState* play) {
    BgUmajump* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);

    this->actionFunc = NULL;
    this->horse = NULL;
    this->hasSoundPlayed = false;

    DynaPolyActor_Init(&this->dyna, 0);

    this->objectIndex = BG_UMAJUMP_GET_OBJECT_INDEX(thisx);
    thisx->params &= 0xFF;

    if ((this->dyna.actor.params == 2)) {
        if ((((play->sceneNum == SCENE_F01) && !(gSaveContext.save.weekEventReg[89] & 0x20)) &&
             !CHECK_QUEST_ITEM(QUEST_SONG_EPONA)) &&
            (this->dyna.actor.cutscene != -1)) {
            this->actionFunc = BgUmajump_CheckDistance;
            this->dyna.actor.update = func_8091A5A0;
            this->dyna.actor.flags |= ACTOR_FLAG_10;
            this->horse = SubS_FindActor(play, this->horse, ACTORCAT_BG, ACTOR_EN_HORSE);
        } else {
            this->dyna.actor.update = Actor_Noop;
        }
    } else {
        this->objectIndex = Object_GetIndex(&play->objectCtx, OBJECT_UMAJUMP);

        if (this->objectIndex < 0) {
            Actor_MarkForDeath(&this->dyna.actor);
        }

        if ((this->dyna.actor.params == 3) && CHECK_QUEST_ITEM(QUEST_SONG_EPONA)) {
            Actor_Spawn(&play->actorCtx, play, ACTOR_EN_KANBAN, this->dyna.actor.world.pos.x,
                        this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, this->dyna.actor.shape.rot.x,
                        this->dyna.actor.shape.rot.y, this->dyna.actor.shape.rot.z, 0x3E);
            Actor_MarkForDeath(&this->dyna.actor);
        }
    }
}

void BgUmajump_Destroy(Actor* thisx, PlayState* play) {
    BgUmajump* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void BgUmajump_Update(Actor* thisx, PlayState* play) {
    BgUmajump* this = THIS;

    if (Object_IsLoaded(&play->objectCtx, this->objectIndex)) {
        this->dyna.actor.objBankIndex = this->objectIndex;
        this->dyna.actor.draw = BgUmajump_Draw;

        Actor_SetObjectDependency(play, &this->dyna.actor);

        if (this->dyna.actor.params == 5) {
            if (gSaveContext.save.weekEventReg[22] & 1) {
                DynaPolyActor_LoadMesh(play, &this->dyna, &object_umajump_Colheader_001558);
            }
        } else if (this->dyna.actor.params == 6) {
            if (!(gSaveContext.save.weekEventReg[22] & 1)) {
                DynaPolyActor_LoadMesh(play, &this->dyna, &object_umajump_Colheader_001558);
            }
        } else if ((this->dyna.actor.params == 4) || (this->dyna.actor.params == 3)) {
            DynaPolyActor_LoadMesh(play, &this->dyna, &object_umajump_Colheader_001558);
        } else {
            DynaPolyActor_LoadMesh(play, &this->dyna, &object_umajump_Colheader_001438);
        }

        if (this->dyna.actor.params == 1) {
            this->objectIndex = 0;
            this->actionFunc = func_80919F30;
            this->dyna.actor.update = func_8091A5A0;
        } else if (this->dyna.actor.params == 3) {
            this->dyna.actor.update = func_8091A5A0;
        } else if ((this->dyna.actor.params == 5) || (this->dyna.actor.params == 6)) {
            if (this->dyna.actor.params == 5) {
                if ((this->dyna.bgId == BGACTOR_NEG_ONE) && (gSaveContext.save.weekEventReg[22] & 1)) {
                    DynaPolyActor_LoadMesh(play, &this->dyna, &object_umajump_Colheader_001558);
                }
            } else if ((this->dyna.actor.params == 6) && (this->dyna.bgId == BGACTOR_NEG_ONE) &&
                       (!(gSaveContext.save.weekEventReg[22] & 1) ||
                        ((gSaveContext.save.day == 2) && (gSaveContext.save.isNight == true) &&
                         ((gSaveContext.save.time >= CLOCK_TIME(5, 30)) &&
                          (gSaveContext.save.time <= CLOCK_TIME(6, 0)))))) {
                DynaPolyActor_LoadMesh(play, &this->dyna, &object_umajump_Colheader_001558);
            }
            func_800C641C(play, &play->colCtx.dyna, this->dyna.bgId);
            this->dyna.actor.update = func_8091A5A0;
        } else if (this->dyna.actor.params == 4) {
            func_800C641C(play, &play->colCtx.dyna, this->dyna.bgId);
            this->dyna.actor.update = Actor_Noop;
        } else {
            this->dyna.actor.update = Actor_Noop;
        }
    }
}

void func_8091A5A0(Actor* thisx, PlayState* play) {
    BgUmajump* this = THIS;

    if (this->actionFunc != NULL) {
        this->actionFunc(this, play);
    }

    if ((this->dyna.actor.params == 3) && CHECK_QUEST_ITEM(QUEST_SONG_EPONA)) {
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_KANBAN, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                    this->dyna.actor.world.pos.z, this->dyna.actor.shape.rot.x, this->dyna.actor.shape.rot.y,
                    this->dyna.actor.shape.rot.z, 0x3E);
        Actor_MarkForDeath(&this->dyna.actor);
    }

    if (this->dyna.actor.params == 5) {
        if ((this->dyna.bgId == BGACTOR_NEG_ONE) && (gSaveContext.save.weekEventReg[22] & 1)) {
            DynaPolyActor_LoadMesh(play, &this->dyna, &object_umajump_Colheader_001558);
        } else if ((this->dyna.bgId != -1) && !(gSaveContext.save.weekEventReg[22] & 1)) {
            DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
        }
    } else if (this->dyna.actor.params == 6) {
        if ((this->dyna.bgId == BGACTOR_NEG_ONE) &&
            (!(gSaveContext.save.weekEventReg[22] & 1) ||
             ((gSaveContext.save.day == 2) && (gSaveContext.save.isNight == true) &&
              (gSaveContext.save.time >= CLOCK_TIME(5, 30)) && (gSaveContext.save.time <= CLOCK_TIME(6, 0))))) {
            DynaPolyActor_LoadMesh(play, &this->dyna, &object_umajump_Colheader_001558);
        } else if ((this->dyna.bgId != -1) && (gSaveContext.save.weekEventReg[22] & 1) &&
                   ((gSaveContext.save.day != 2) || (gSaveContext.save.isNight != true) ||
                    (gSaveContext.save.time < CLOCK_TIME(5, 30)) || (gSaveContext.save.time > CLOCK_TIME(6, 0)))) {
            DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
        }
    }
}

void BgUmajump_Draw(Actor* thisx, PlayState* play) {
    BgUmajump* this = THIS;

    if (this->dyna.bgId != -1) {
        Gfx_DrawDListOpa(play, gHorseJumpFenceDL);
    }
}
