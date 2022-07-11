/*
 * File: z_dm_char04.c
 * Overlay: ovl_Dm_Char04
 * Description: Unused(?) Tatl and Tael actors
 */

#include "z_dm_char04.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmChar04*)thisx)

void DmChar04_Init(Actor* thisx, PlayState* play);
void DmChar04_Destroy(Actor* thisx, PlayState* play);
void DmChar04_Update(Actor* thisx, PlayState* play);
void DmChar04_Draw(Actor* thisx, PlayState* play);

void func_80AABC40(SkelAnime*, AnimationInfo* str, u16 arg2);
void func_80AABE34(DmChar04* this, PlayState* play);
s32 func_80AABF74(PlayState* play2, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx, Gfx** gfx);

#if 1
const ActorInit Dm_Char04_InitVars = {
    ACTOR_DM_CHAR04,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DmChar04),
    (ActorFunc)DmChar04_Init,
    (ActorFunc)DmChar04_Destroy,
    (ActorFunc)DmChar04_Update,
    (ActorFunc)DmChar04_Draw,
};

static AnimationInfo D_80AAC460[2] = {
    { (AnimationHeader *)0x0402B2E8, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { (AnimationHeader *)0x04029140, 1.0f, 0.0f, -1.0f, 0, 0.0f },
};

unkStruct D_80AAC490[3] = {
    { 250.0f, 255.0f, 230.0f, 255.0f },
    { 10.0f, 10.0f, 40.0f, 255.0f },
    { 255.0f, 235.0f, 220.0f, 255.0f },
};
unkStruct D_80AAC4C0[3] = {
    { 220.0f, 160.0f, 80.0f, 255.0f },
    { 120.0f, 255.0f, 255.0f, 255.0f },
    { 255.0f, 235.0f, 220.0f, 255.0f },
};

static Vec3f D_80AAC4F0 = { 0.0f, 0.0f, 0.0f };
#endif

extern unkStruct D_80AAC490[];
extern unkStruct D_80AAC4C0[];
extern AnimationHeader D_04029140;
extern SkeletonHeader D_0402AF58;
extern AnimationInfo D_80AAC460[];
extern Vec3f D_80AAC4F0;

void func_80AABC40(SkelAnime* arg0, AnimationInfo* animation, u16 arg2) {
    f32 phi_fv1;

    animation += arg2;

    if (animation->frameCount < 0.0f) {
        phi_fv1 = Animation_GetLastFrame(animation->animation);
    } else {
        phi_fv1 = animation->frameCount;
    }
    Animation_Change(arg0, animation->animation, animation->playSpeed, animation->startFrame, phi_fv1, animation->mode,
                     animation->morphFrames);
}

void DmChar04_Init(Actor* thisx, PlayState* play) {
    DmChar04* this = THIS;

    this->str = D_80AAC490[this->actor.params];
    this->str2 = D_80AAC4C0[this->actor.params];
    this->actor.targetArrowOffset = 3000.0f;
    this->unk260 = 0x63;
    this->unk262 = this->actor.params << 0xB;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    SkelAnime_Init(play, &this->skelAnime, &D_0402AF58, &D_04029140, &this->jointTable, &this->morphTable, 7);
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 15.0f);
    func_80AABC40(&this->skelAnime, &D_80AAC460, 0);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80AABE34;
}

void DmChar04_Destroy(Actor* thisx, PlayState* play) {
}

void func_80AABE34(DmChar04* this, PlayState* play) {
    u16 params = this->actor.params + 0x71;

    if (Cutscene_CheckActorAction(play, params) != 0) {
        s32 actionIndex = Cutscene_GetActorActionIndex(play, params);

        if (play->csCtx.frames == play->csCtx.actorActions[actionIndex]->startFrame) {
            if (this->unk260 != play->csCtx.actorActions[actionIndex]->action) {
                this->unk260 = play->csCtx.actorActions[actionIndex]->action;
                if (play->csCtx.actorActions[actionIndex]->action == 1) {
                    this->unk261 = 0;
                } else {
                    this->unk261 = 0;
                }
                func_80AABC40(&this->skelAnime, &D_80AAC460[this->unk261], 0);
            }
        }
        Cutscene_ActorTranslateAndYaw(&this->actor, play, actionIndex);
    } else {
        this->unk260 = 0x63;
    }
}

void DmChar04_Update(Actor* thisx, PlayState* play) {
    DmChar04* this = THIS;

    SkelAnime_Update(&this->skelAnime);
    this->actionFunc(this, play);
    this->unk262++;
}

s32 func_80AABF74(PlayState* play2, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    PlayState* play = play2;
    f32 sp28;
    Vec3f sp1C;
    DmChar04* this = THIS;

    if (limbIndex == 6) {
        sp28 = ((Math_SinS((this->unk262 << 0xC)) * 0.1f) + 1.0f) * 0.012f * (this->actor.scale.x * 124.99999f);
        Matrix_MultVec3f(&D_80AAC4F0, &sp1C);
        Matrix_Translate(sp1C.x, sp1C.y, sp1C.z, MTXMODE_NEW);
        Matrix_Scale(sp28, sp28, sp28, MTXMODE_APPLY);
    }
    return false;
}
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char04/DmChar04_Draw.s")

void DmChar04_Draw(Actor* thisx, PlayState* play) {
    Gfx* gfx = GRAPH_ALLOC(play->state.gfxCtx, sizeof(Gfx) * 4);
    s32 phi_a0;
    s32 pad;
    DmChar04* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C94C(play->state.gfxCtx);
    phi_a0 = (this->unk262 * 0x32) & 0x1FF;
    if (phi_a0 >= 0x100) {
        phi_a0 = 0x1FF - phi_a0;
    }
    gSPSegment(POLY_XLU_DISP++, 0x08, &gfx[0]);
    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, 0x01, (u8)this->str.unk_240, (u8)this->str.unk_244, (u8)this->str.unk_248,
                    (u8)(this->str.unk_24C * 1));
    gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_ZB_CLD_SURF2);
    gSPEndDisplayList(gfx);
    gDPSetEnvColor(POLY_XLU_DISP++, (u8)(s8)this->str2.unk_240, (u8)(s8)this->str2.unk_244, (u8)(s8)this->str2.unk_248,
                   (u8)(s8)((f32)phi_a0 * 1));
    gDPSetDither(POLY_XLU_DISP++, G_CD_BAYER);
    POLY_XLU_DISP = SkelAnime_Draw(play, this->skelAnime.skeleton, this->skelAnime.jointTable, func_80AABF74, NULL,
                                   &this->actor, POLY_XLU_DISP);
    CLOSE_DISPS(play->state.gfxCtx);
}
