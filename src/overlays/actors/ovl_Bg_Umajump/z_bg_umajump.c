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
void Debug_PrintToScreen(Actor* thisx, PlayState* play);
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
    if (this->objectIndex >= 0x5A) {
        this->objectIndex = 0;
    }

    this->objectIndex++;
    this->dyna.actor.shape.yOffset =
        Math_SinS((this->objectIndex / 90.0f) * 65536.0f) * (20.0f / this->dyna.actor.scale.y);
}

void func_80919FC8(BgUmajump* this, PlayState* play) {
    if ((play->csCtx.frames >= 6) && !this->unk164) {
        this->unk164 = true;
        play_sound(NA_SE_EV_KID_HORSE_NEIGH);
    }
    if (!play->csCtx.state) {
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        this->dyna.actor.update = Actor_Noop;
    }
}

void func_8091A044(BgUmajump* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        gSaveContext.save.weekEventReg[0x59] |= 0x20;
        this->actionFunc = func_80919FC8;
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void func_8091A0B8(BgUmajump* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if ((this->horse != NULL) && (player != NULL) &&
        (Math3D_XZDistance(this->horse->world.pos.x, this->horse->world.pos.z, player->actor.world.pos.x,
                           player->actor.world.pos.z) < 1400.0f)) {
        this->actionFunc = func_8091A044;
    }
}

void BgUmajump_Init(Actor* thisx, PlayState* play) {
    BgUmajump* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);

    this->actionFunc = NULL;
    this->horse = NULL;
    this->unk164 = false;

    DynaPolyActor_Init(&this->dyna, 0);

    this->objectIndex = (thisx->params >> 8) & 0xFF;
    thisx->params = thisx->params & 0xFF;

    if ((this->dyna.actor.params == 2)) {
        if ((((play->sceneNum == SCENE_F01) && !(gSaveContext.save.weekEventReg[0x59] & 0x20)) &&
             !CHECK_QUEST_ITEM(QUEST_SONG_EPONA)) &&
            (this->dyna.actor.cutscene != -1)) {
            this->actionFunc = func_8091A0B8;
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
            if (gSaveContext.save.weekEventReg[0x16] & 1) {
                DynaPolyActor_LoadMesh(play, &this->dyna, &object_umajump_Colheader_001558);
            }
        } else if (this->dyna.actor.params == 6) {
            if (!(gSaveContext.save.weekEventReg[0x16] & 1)) {
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
                if ((this->dyna.bgId == -1) && (gSaveContext.save.weekEventReg[0x16] & 1)) {
                    DynaPolyActor_LoadMesh(play, &this->dyna, &object_umajump_Colheader_001558);
                }
            } else if ((this->dyna.actor.params == 6) && (this->dyna.bgId == -1) &&
                       (!(gSaveContext.save.weekEventReg[0x16] & 1) ||
                        ((gSaveContext.save.day == 2) && (gSaveContext.save.isNight == 1) &&
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
        if ((this->dyna.bgId == -1) && (gSaveContext.save.weekEventReg[0x16] & 1)) {
            DynaPolyActor_LoadMesh(play, &this->dyna, &object_umajump_Colheader_001558);
        } else if ((this->dyna.bgId != -1) && !(gSaveContext.save.weekEventReg[0x16] & 1)) {
            DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
        }
    } else if (this->dyna.actor.params == 6) {
        if ((this->dyna.bgId == -1) &&
            (!(gSaveContext.save.weekEventReg[0x16] & 1) ||
             ((gSaveContext.save.day == 2) && (gSaveContext.save.isNight == 1) &&
              (gSaveContext.save.time >= CLOCK_TIME(5, 30)) && (gSaveContext.save.time <= CLOCK_TIME(6, 0))))) {
            DynaPolyActor_LoadMesh(play, &this->dyna, &object_umajump_Colheader_001558);
        } else if ((this->dyna.bgId != -1) && (gSaveContext.save.weekEventReg[0x16] & 1) &&
                   ((gSaveContext.save.day != 2) || (gSaveContext.save.isNight != 1) ||
                    (gSaveContext.save.time < CLOCK_TIME(5, 30)) || (gSaveContext.save.time > CLOCK_TIME(6, 0)))) {
            DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
        }
    }
}

void Debug_PrintToScreen(Actor* thisx, PlayState* play) {
    //ObjBean* this = THIS;
    BgUmajump* this = THIS;
    // with explanation comments
    GfxPrint printer;
    Gfx* gfx;

    OPEN_DISPS(play->state.gfxCtx);

    // the dlist will be written in the opa buffer because that buffer is larger,
    // but executed from the overlay buffer (overlay draws last, for example the hud is drawn to overlay)
    gfx = POLY_OPA_DISP + 1;
    gSPDisplayList(OVERLAY_DISP++, gfx);

    // initialize GfxPrint struct
    GfxPrint_Init(&printer);
    GfxPrint_Open(&printer, gfx);

    GfxPrint_SetColor(&printer, 255, 255, 255, 255);
    GfxPrint_SetPos(&printer, 1, 7);
    GfxPrint_Printf(&printer, "unk164: %X", this->unk164);
    GfxPrint_SetPos(&printer, 1, 10);
    GfxPrint_Printf(&printer, "play->csCtx.frames: %X", play->csCtx.frames);

    { // address locations
        u32 convertedAddr = (u32)Fault_ConvertAddress((void*)this->actionFunc);
        GfxPrint_SetPos(&printer, 1, 11);
        //GfxPrint_Printf(&printer, "func %X", &EnPoSisters_CheckCollision);
    }

    GfxPrint_SetPos(&printer, 1, 13);

    //GfxPrint_Printf(&printer, "drawflags %X", this->drawFlags);
    //GfxPrint_Printf(&printer, "BREG86 %X", BREG(86));
    GfxPrint_Printf(&printer, "mesgState %X", Message_GetState(&play->msgCtx));

    // end of text printing
    gfx = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);

    gSPEndDisplayList(gfx++);
    // make the opa dlist jump over the part that will be executed as part of overlay
    gSPBranchList(POLY_OPA_DISP, gfx);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(play->state.gfxCtx);
    //Debug_PrintToScreen(thisx, play);
}

void BgUmajump_Draw(Actor* thisx, PlayState* play) {
    BgUmajump* this = THIS;

    if (this->dyna.bgId != -1) {
        Gfx_DrawDListOpa(play, gHorseJumpFence);
    }

    Debug_PrintToScreen(thisx, play);
}
