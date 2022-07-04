/*
 * File: z_en_sth2.c
 * Overlay: ovl_En_Sth2
 * Description: Guy waving at the telescope in Termina Field
 */

#include "z_en_sth2.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnSth2*)thisx)

void EnSth2_Init(Actor* thisx, PlayState* play);
void EnSth2_Destroy(Actor* thisx, PlayState* play);
void EnSth2_Update(Actor* thisx, PlayState* play);
void EnSth2_Draw(Actor* thisx, PlayState* play2);

void func_80BF75A0(EnSth2* this, PlayState* play);
void func_80BF7688(Actor* thisx, PlayState* play);
s32 func_80BF76AC(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void func_80BF77AC(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);

const ActorInit En_Sth2_InitVars = {
    ACTOR_EN_STH2,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnSth2),
    (ActorFunc)EnSth2_Init,
    (ActorFunc)EnSth2_Destroy,
    (ActorFunc)EnSth2_Update,
    (ActorFunc)NULL,
};

#include "overlays/ovl_En_Sth2/ovl_En_Sth2.c"

extern FlexSkeletonHeader D_060031F8;

static Vec3f D_80BFA010 = { 700.0f, 400.0f, 0.0f };

static Color_RGB8 D_80BFA01C[] = { { 190, 110, 0 },  { 0, 180, 110 },   { 0, 255, 80 },
                                   { 255, 160, 60 }, { 190, 230, 250 }, { 240, 230, 120 } };

void EnSth2_Init(Actor* thisx, PlayState* play) {
    EnSth2* this = THIS;

    this->objIndex = Object_GetIndex(&play->objectCtx, 0x26A);
    Actor_SetScale(&this->actor, 0.01f);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 36.0f);
    this->unk248 = 0;

    if ((play->actorCtx.unk5 & 2) != 0) {
        this->actor.flags |= 0x30;
    } else {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    this->actionFunc = func_80BF75A0;
}

void EnSth2_Destroy(Actor* thisx, PlayState* play) {
}

void func_80BF75A0(EnSth2* this, PlayState* play) {
    SkelAnime_Update(&this->unk144);
}

void EnSth2_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnSth2* this = THIS;

    if (Object_IsLoaded(&play->objectCtx, (s32)(u8)this->objIndex) != 0) {
        this->actor.objBankIndex = (s8)(u8)this->objIndex;
        Actor_SetObjectDependency(play, &this->actor);
        SkelAnime_InitFlex(play, &this->unk144, (FlexSkeletonHeader*)&D_060031F8, &D_80BFA000, &this->unk188,
                           &this->unk1E8, 0x10);
        Animation_PlayLoop(&this->unk144, &D_80BFA000);
        this->actor.update = func_80BF7688;
        this->actor.draw = EnSth2_Draw;
    }
}

void func_80BF7688(Actor* thisx, PlayState* play) {
    EnSth2* this = THIS;
    this->actionFunc(this, play);
}

s32 func_80BF76AC(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    s32 pad;

    if (limbIndex == 15) {
        *dList = D_80BF9550;
    }
    if ((limbIndex == 8) || (limbIndex == 10) || (limbIndex == 13)) {
        rot->y += (s16)(Math_SinS((play->state.frames * ((limbIndex * 0x32) + 0x814))) * 200.0f);
        rot->z += (s16)(Math_CosS((play->state.frames * ((limbIndex * 0x32) + 0x940))) * 200.0f);
    }
    return false;
}

void func_80BF77AC(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    if (limbIndex == 15) {
        Matrix_MultVec3f(&D_80BFA010, &thisx->focus.pos);
        OPEN_DISPS(play->state.gfxCtx);
        gSPDisplayList(POLY_OPA_DISP++, &D_80BF9870);
        CLOSE_DISPS(play->state.gfxCtx);
    }
}

void EnSth2_Draw(Actor* thisx, PlayState* play2) {
    EnSth2* this = THIS;
    PlayState* play = play2;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08,
               Gfx_EnvColor(play->state.gfxCtx, (s32)D_80BFA01C[1].r, (s32)D_80BFA01C[1].g, (s32)D_80BFA01C[1].b, 255));
    gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(play->state.gfxCtx, 90, 110, 130, 255));
    SkelAnime_DrawFlexOpa(play, this->unk144.skeleton, this->unk144.jointTable, (s32)this->unk144.dListCount,
                          func_80BF76AC, func_80BF77AC, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
