/*
 * File: z_bg_umajump.c
 * Overlay: ovl_Bg_Umajump
 * Description: Horse Jumping Fence
 */

#include "z_bg_umajump.h"

#define FLAGS 0x00000000

#define THIS ((BgUmajump*)thisx)

void BgUmajump_Init(Actor* thisx, PlayState* play);
void BgUmajump_Destroy(Actor* thisx, PlayState* play);
void BgUmajump_Update(Actor* thisx, PlayState* play);

void func_8091A5A0(BgUmajump* this, PlayState* play);
void func_8091A0B8(BgUmajump* this, PlayState* play);
void func_8091A044(BgUmajump* this, PlayState* play);
void func_80919FC8(BgUmajump* this, PlayState* play);
void func_80919F30(BgUmajump* this, PlayState* play); /* extern */
void func_8091A7B0(Actor* thisx, PlayState* play);

#if 1
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

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8091A810[] = {
    ICHAIN_F32(uncullZoneScale, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_8091A810[];
extern CollisionHeader D_06001438;

extern Gfx* D_06001220;
extern UNK_TYPE D_06001558;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Umajump/func_80919F30.s")

void func_80919F30(BgUmajump* this, PlayState* play) {
    if (this->unk160 >= 0x5A) {
        this->unk160 = 0;
        this->unk160 = 0;
    }

    this->unk160++;
    this->dyna.actor.shape.yOffset = Math_SinS((this->unk160 / 90.0f) * 65536.0f) * (20.0f / this->dyna.actor.scale.y);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Umajump/func_80919FC8.s")

void func_80919FC8(BgUmajump* this, PlayState* play) {
    if ((play->csCtx.frames >= 6) && (this->unk164 == 0)) {
        this->unk164 = 1;
        play_sound(0x2844);
    }
    if (!play->csCtx.state) {
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        this->dyna.actor.update = Actor_Noop;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Umajump/func_8091A044.s")

void func_8091A044(BgUmajump* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        gSaveContext.save.weekEventReg[0x59] |= 0x20;
        this->actionFunc = func_80919FC8;
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Umajump/func_8091A0B8.s")

void func_8091A0B8(BgUmajump* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if ((this->horse != NULL) && (player != NULL) &&
        (Math3D_XZDistance(this->horse->world.pos.x, this->horse->world.pos.z, player->actor.world.pos.x,
                           player->actor.world.pos.z) < 1400.0f)) {
        this->actionFunc = func_8091A044;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Umajump/BgUmajump_Init.s")

void BgUmajump_Init(Actor* thisx, PlayState* play) {
    BgUmajump* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, D_8091A810);

    this->actionFunc = NULL;
    this->horse = NULL;
    this->unk164 = 0;

    DynaPolyActor_Init(&this->dyna, 0);

    this->unk160 = (thisx->params >> 8) & 0xFF;
    thisx->params = thisx->params & 0xFF;

    if ((this->dyna.actor.params == 2)) {
        if ((((play->sceneNum == SCENE_F01) && (!(gSaveContext.save.weekEventReg[0x59] & 0x20))) &&
             (!CHECK_QUEST_ITEM(QUEST_SONG_EPONA))) &&
            (this->dyna.actor.cutscene != -1)) {
            this->actionFunc = func_8091A0B8;
            this->dyna.actor.update = func_8091A5A0;
            this->dyna.actor.flags |= 0x10;
            this->horse = SubS_FindActor(play, this->horse, ACTORCAT_BG, ACTOR_EN_HORSE);
        } else {
            this->dyna.actor.update = Actor_Noop;
        }
    } else {
        this->unk160 = Object_GetIndex(&play->objectCtx, 0xD2);
        if (this->unk160 < 0) {
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

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Umajump/BgUmajump_Destroy.s")

void BgUmajump_Destroy(Actor* thisx, PlayState* play) {
    BgUmajump* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Umajump/BgUmajump_Update.s")

void BgUmajump_Update(Actor* thisx, PlayState* play) {
    BgUmajump* this = (BgUmajump*)thisx;
    if (Object_IsLoaded(&play->objectCtx, this->unk160) != 0) {
        this->dyna.actor.objBankIndex = this->unk160;
        this->dyna.actor.draw = func_8091A7B0;
        Actor_SetObjectDependency(play, &this->dyna.actor);
        if (this->dyna.actor.params == 5) {
            if ((gSaveContext.save.weekEventReg[0x16] & 1) != 0) {
                DynaPolyActor_LoadMesh(play, &this->dyna, (CollisionHeader*)&D_06001558);
            }
        } else if (this->dyna.actor.params == 6) {
            if ((gSaveContext.save.weekEventReg[0x16] & 1) == 0) {
                DynaPolyActor_LoadMesh(play, &this->dyna, (CollisionHeader*)&D_06001558);
            }
        } else {
            if ((this->dyna.actor.params == 4) || (this->dyna.actor.params == 3)) {
                DynaPolyActor_LoadMesh(play, &this->dyna, (CollisionHeader*)&D_06001558);
            } else {
                DynaPolyActor_LoadMesh(play, &this->dyna, &D_06001438);
            }
        }
        if (this->dyna.actor.params == 1) {
            this->unk160 = 0;
            this->actionFunc = func_80919F30;
            this->dyna.actor.update = func_8091A5A0;
            return;
        }
        if (this->dyna.actor.params == 3) {
            this->dyna.actor.update = func_8091A5A0;
            return;
        }
        if ((this->dyna.actor.params == 5) || (this->dyna.actor.params == 6)) {
            if (this->dyna.actor.params == 5) {
                if ((this->dyna.bgId == -1) && ((gSaveContext.save.weekEventReg[0x16] & 1) != 0)) {
                    DynaPolyActor_LoadMesh(play, &this->dyna, (CollisionHeader*)&D_06001558);
                }
            } else if ((this->dyna.actor.params == 6) && (this->dyna.bgId == -1) &&
                       (((gSaveContext.save.weekEventReg[0x16] & 1) == 0) ||
                        ((gSaveContext.save.day == 2) && (gSaveContext.save.isNight == 1) &&
                         ((gSaveContext.save.time >= 0x3AAA) && (gSaveContext.save.time <= 0x4000))))) {
                DynaPolyActor_LoadMesh(play, &this->dyna, (CollisionHeader*)&D_06001558);
            }
            func_800C641C(play, &play->colCtx.dyna, this->dyna.bgId);
            this->dyna.actor.update = func_8091A5A0;
            return;
        }
        if (this->dyna.actor.params == 4) {
            func_800C641C(play, &play->colCtx.dyna, this->dyna.bgId);
            this->dyna.actor.update = Actor_Noop;
        } else {
            this->dyna.actor.update = Actor_Noop;
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Umajump/func_8091A5A0.s")

void func_8091A5A0(BgUmajump* this, PlayState* play) {
    if (this->actionFunc != NULL) {
        this->actionFunc(this, play);
    }
    if ((this->dyna.actor.params == 3) && (CHECK_QUEST_ITEM(QUEST_SONG_EPONA))) {
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_KANBAN, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                    this->dyna.actor.world.pos.z, this->dyna.actor.shape.rot.x, this->dyna.actor.shape.rot.y,
                    this->dyna.actor.shape.rot.z, 0x3E);
        Actor_MarkForDeath(&this->dyna.actor);
    }
    if (this->dyna.actor.params == 5) {
        if ((this->dyna.bgId == -1) && (gSaveContext.save.weekEventReg[0x16] & 1)) {
            DynaPolyActor_LoadMesh(play, &this->dyna, (CollisionHeader*)&D_06001558);
        }
        else if ((this->dyna.bgId != -1) && !(gSaveContext.save.weekEventReg[0x16] & 1)) {
            DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
        }
    } else if (this->dyna.actor.params == 6) {
        if ((this->dyna.bgId == -1) &&
            (((gSaveContext.save.weekEventReg[0x16] & 1) == 0) ||
             ((gSaveContext.save.day == 2) && (gSaveContext.save.isNight == 1) &&
              (((gSaveContext.save.time >= 0x3AAA))) && (gSaveContext.save.time <= 0x4000)))) {
            DynaPolyActor_LoadMesh(play, &this->dyna, (CollisionHeader*)&D_06001558);
        }
        else if ((this->dyna.bgId != -1) && ((gSaveContext.save.weekEventReg[0x16] & 1) != 0) &&
            ((gSaveContext.save.day != 2) || (gSaveContext.save.isNight != 1) ||
             ( ((gSaveContext.save.time < 0x3AAA))) || (gSaveContext.save.time > 0x4000))) {
            DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Umajump/func_8091A7B0.s")

void func_8091A7B0(Actor* thisx, PlayState* play) {
    BgUmajump* this = THIS;

    if (this->dyna.bgId != -1) {
        Gfx_DrawDListOpa(play, &D_06001220);
    }
}
