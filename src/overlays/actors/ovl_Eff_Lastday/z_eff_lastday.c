/*
 * File: z_eff_lastday.c
 * Overlay: ovl_Eff_Lastday
 * Description: Moon Crash Cutscene Fire Wall
 */

#include "z_eff_lastday.h"
#include "objects/object_lastday/object_lastday.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EffLastday*)thisx)

void EffLastday_Init(Actor* thisx, PlayState* play2);
void EffLastday_Destroy(Actor* thisx, PlayState* play);
void EffLastday_Update(Actor* thisx, PlayState* play);
void EffLastday_Draw(Actor* thisx, PlayState* play);

void func_80BEBD0C(EffLastday* this, PlayState* play);
void func_80BEBDF8(EffLastday* this, PlayState* play);
void func_80BEBEB8(EffLastday* this, PlayState* play);
void func_80BEBF78(EffLastday* this, PlayState* play);

const ActorInit Eff_Lastday_InitVars = {
    ACTOR_EFF_LASTDAY,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_LASTDAY,
    sizeof(EffLastday),
    (ActorFunc)EffLastday_Init,
    (ActorFunc)EffLastday_Destroy,
    (ActorFunc)EffLastday_Update,
    (ActorFunc)EffLastday_Draw,
};

void EffLastday_Init(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EffLastday* this = THIS;

    Actor_SetScale(&this->actor, 0.1f);
    switch (this->actor.params & 0xF) {
        case 1:
            this->dList = object_lastday_DL_000510;
            this->matAnim = Lib_SegmentedToVirtual(object_lastday_Matanimheader_000608);
            this->actionCmd = 0x1FC;
            this->actionFunc = func_80BEBDF8;
            Actor_SetScale(&this->actor, 1.0f);
            break;
        case 2:
            this->dList = object_lastday_DL_000210;
            this->matAnim = Lib_SegmentedToVirtual(object_lastday_Matanimheader_000308);
            this->actionCmd = 0x1FD;
            this->actionFunc = func_80BEBEB8;
            Actor_SetScale(&this->actor, 0.5f);
            break;
        case 3:
            this->dList = object_lastday_DL_000060;
            this->matAnim = Lib_SegmentedToVirtual(object_lastday_Matanimheader_000148);
            this->actionCmd = 0x1FE;
            this->actionFunc = func_80BEBF78;
            Actor_SetScale(&this->actor, 0.2f);
            this->actor.home.rot.z = 0;
            break;
        default:
            this->dList = object_lastday_DL_000370;
            this->matAnim = Lib_SegmentedToVirtual(object_lastday_Matanimheader_000448);
            this->actionCmd = 0x1FB;
            this->actionFunc = func_80BEBD0C;
            Actor_SetScale(&this->actor, 1.0f);
            Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EFF_LASTDAY, this->actor.world.pos.x,
                               this->actor.world.pos.y, this->actor.world.pos.z, 0, this->actor.world.rot.y, 0, 1);
            Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EFF_LASTDAY, this->actor.world.pos.x,
                               this->actor.world.pos.y, this->actor.world.pos.z, 0, this->actor.world.rot.y, 0, 2);
            Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EFF_LASTDAY, this->actor.world.pos.x,
                               this->actor.world.pos.y, this->actor.world.pos.z, 0, this->actor.world.rot.y, 0, 3);
            break;
    }
}

void EffLastday_Destroy(Actor* thisx, PlayState* play) {
}

void func_80BEBD0C(EffLastday* this, PlayState* play) {
    u16 action;

    if ((Cutscene_CheckActorAction(play, this->actionCmd))) {
        Cutscene_ActorTranslateAndYaw(&this->actor, play, Cutscene_GetActorActionIndex(play, this->actionCmd));
        action = play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, this->actionCmd)]->action;
        switch (action) {
            default:
                this->actor.draw = NULL;
                this->alpha = 0;
                this->step = 0;
                break;
            case 2:
                this->actor.draw = NULL;
                this->actor.draw = EffLastday_Draw;
                if (this->alpha < 255) {
                    this->alpha = this->alpha + 10;
                }
                if (this->alpha > 255) {
                    this->alpha = 255;
                }
                this->step += 1;
                break;
            case 3:
                this->actor.draw = EffLastday_Draw;
                break;
        }
    } else {
        this->actor.draw = NULL;
    }
}

void func_80BEBDF8(EffLastday* this, PlayState* play) {
    u16 action;

    if (Cutscene_CheckActorAction(play, this->actionCmd)) {
        Cutscene_ActorTranslateAndYaw(&this->actor, play, Cutscene_GetActorActionIndex(play, this->actionCmd));
        action = play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, this->actionCmd)]->action;
        switch (action) {
            default:
                this->actor.draw = NULL;
                this->step = 0;
                break;
            case 2:
                this->actor.draw = EffLastday_Draw;
                this->step += 1;
                break;
            case 3:
                this->actor.draw = EffLastday_Draw;
                break;
        }
    } else {
        this->actor.draw = NULL;
    }
}

void func_80BEBEB8(EffLastday* this, PlayState* play) {
    u16 action;

    if (Cutscene_CheckActorAction(play, this->actionCmd)) {
        Cutscene_ActorTranslateAndYaw(&this->actor, play, Cutscene_GetActorActionIndex(play, this->actionCmd));
        action = play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, this->actionCmd)]->action;
        switch (action) {
            default:
                this->actor.draw = NULL;
                this->step = 0;
                break;
            case 2:
                this->actor.draw = EffLastday_Draw;
                this->step += 1;
                break;
            case 3:
                this->actor.draw = EffLastday_Draw;
                break;
        }
    } else {
        this->actor.draw = NULL;
    }
}

void func_80BEBF78(EffLastday* this, PlayState* play) {
    u16 action;

    if (Cutscene_CheckActorAction(play, this->actionCmd)) {
        Cutscene_ActorTranslateAndYaw(&this->actor, play, Cutscene_GetActorActionIndex(play, this->actionCmd));
        action = play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, this->actionCmd)]->action;
        switch (action) {
            default:
                this->actor.draw = NULL;
                this->alpha = 0;
                this->step = 0;
                break;
            case 2:
                if (!this->actor.home.rot.z) {
                    this->actor.home.rot.z = true;
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_COMING_FIRE);
                }
                this->actor.draw = EffLastday_Draw;
                if (this->alpha < 255) {
                    this->alpha += 5;
                }
                if (this->alpha >= 0x100) {
                    this->alpha = 255;
                }
                this->step += 1;
                break;
            case 3:
                this->actor.draw = EffLastday_Draw;
                break;
        }
    } else {
        this->actor.draw = NULL;
    }
}

void EffLastday_Update(Actor* thisx, PlayState* play) {
    EffLastday* this = THIS;

    this->actionFunc(this, play);
}

void EffLastday_Draw_SetVtxAlpha(s16 alpha) {
    Vtx* vtx = Lib_SegmentedToVirtual(object_lastday_Vtx_000000);

    vtx[0].v.cn[3] = alpha;
    vtx[3].v.cn[3] = alpha;
    vtx[4].v.cn[3] = alpha;
    vtx[5].v.cn[3] = alpha;
}

void EffLastday_Draw(Actor* thisx, PlayState* play) {
    EffLastday* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    switch (this->actor.params & 0xF) {
        case 1:
        case 2:
            break;
        case 3:
            EffLastday_Draw_SetVtxAlpha(this->alpha);
            break;
        default:
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 170, this->alpha);
            break;
    }
    AnimatedMat_DrawAlphaStep(play, this->matAnim, 1.0f, this->step);
    Gfx_DrawDListXlu(play, this->dList);

    CLOSE_DISPS(play->state.gfxCtx);
}
