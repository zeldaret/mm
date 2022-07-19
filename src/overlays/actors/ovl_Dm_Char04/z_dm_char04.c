/*
 * File: z_dm_char04.c
 * Overlay: ovl_Dm_Char04
 * Description: Unused(?) Tatl and Tael actors
 */

#include "z_dm_char04.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmChar04*)thisx)

void DmChar04_Init(Actor* thisx, PlayState* play);
void DmChar04_Destroy(Actor* thisx, PlayState* play);
void DmChar04_Update(Actor* thisx, PlayState* play);
void DmChar04_Draw(Actor* thisx, PlayState* play);

void func_80AABE34(DmChar04* this, PlayState* play);

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

void DmChar04_ChangeAnim(SkelAnime* skelAnime, AnimationInfo* animation, u16 index) {
    f32 endFrame;

    animation += index;

    if (animation->frameCount < 0.0f) {
        endFrame = Animation_GetLastFrame(animation->animation);
    } else {
        endFrame = animation->frameCount;
    }
    Animation_Change(skelAnime, animation->animation, animation->playSpeed, animation->startFrame, endFrame,
                     animation->mode, animation->morphFrames);
}

static AnimationInfo sAnimations[] = {
    { &gameplay_keep_Anim_02B2E8, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gameplay_keep_Anim_029140, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
};

Color_RGBAf sPrimColors[] = {
    { 250.0f, 255.0f, 230.0f, 255.0f },
    { 10.0f, 10.0f, 40.0f, 255.0f },
    { 255.0f, 235.0f, 220.0f, 255.0f },
};
Color_RGBAf sEnvColors[] = {
    { 220.0f, 160.0f, 80.0f, 255.0f },
    { 120.0f, 255.0f, 255.0f, 255.0f },
    { 255.0f, 235.0f, 220.0f, 255.0f },
};

void DmChar04_Init(Actor* thisx, PlayState* play) {
    DmChar04* this = THIS;

    this->primColors = sPrimColors[this->actor.params];
    this->envColors = sEnvColors[this->actor.params];
    this->actor.targetArrowOffset = 3000.0f;
    this->csAction = 0x63;
    this->timer = this->actor.params << 0xB;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    SkelAnime_Init(play, &this->skelAnime, &gameplay_keep_Skel_02AF58.sh, &gameplay_keep_Anim_029140, this->jointTable,
                   this->morphTable, 7);
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 15.0f);
    DmChar04_ChangeAnim(&this->skelAnime, sAnimations, 0);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80AABE34;
}

void DmChar04_Destroy(Actor* thisx, PlayState* play) {
}

void func_80AABE34(DmChar04* this, PlayState* play) {
    u16 params = this->actor.params + 0x71;

    if (Cutscene_CheckActorAction(play, params)) {
        s32 actionIndex = Cutscene_GetActorActionIndex(play, params);

        if (play->csCtx.frames == play->csCtx.actorActions[actionIndex]->startFrame) {
            if (this->csAction != play->csCtx.actorActions[actionIndex]->action) {
                this->csAction = play->csCtx.actorActions[actionIndex]->action;
                if (play->csCtx.actorActions[actionIndex]->action == 1) {
                    this->animationIndex = 0;
                } else {
                    this->animationIndex = 0;
                }
                DmChar04_ChangeAnim(&this->skelAnime, &sAnimations[this->animationIndex], 0);
            }
        }
        Cutscene_ActorTranslateAndYaw(&this->actor, play, actionIndex);
    } else {
        this->csAction = 0x63;
    }
}

void DmChar04_Update(Actor* thisx, PlayState* play) {
    DmChar04* this = THIS;

    SkelAnime_Update(&this->skelAnime);
    this->actionFunc(this, play);
    this->timer++;
}
static Vec3f D_80AAC4F0 = { 0.0f, 0.0f, 0.0f };

s32 DmChar04_OverrideLimbDraw(PlayState* play2, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                              Gfx** gfx) {
    PlayState* play = play2;
    f32 sp28;
    Vec3f sp1C;
    DmChar04* this = THIS;

    if (limbIndex == 6) {
        sp28 = ((Math_SinS(this->timer << 0xC) * 0.1f) + 1.0f) * 0.012f * (this->actor.scale.x * (1.0f / 0.008f));
        Matrix_MultVec3f(&D_80AAC4F0, &sp1C);
        Matrix_Translate(sp1C.x, sp1C.y, sp1C.z, MTXMODE_NEW);
        Matrix_Scale(sp28, sp28, sp28, MTXMODE_APPLY);
    }
    return false;
}

void DmChar04_Draw(Actor* thisx, PlayState* play) {
    Gfx* gfx = GRAPH_ALLOC(play->state.gfxCtx, sizeof(Gfx) * 4);
    s32 alpha;
    s32 pad;
    DmChar04* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C94C(play->state.gfxCtx);
    alpha = (this->timer * 50) & 0x1FF;
    if (alpha > 255) {
        alpha = 511 - alpha;
    }
    gSPSegment(POLY_XLU_DISP++, 0x08, &gfx[0]);
    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, 0x01, (u8)this->primColors.r, (u8)this->primColors.g, (u8)this->primColors.b,
                    (u8)(this->primColors.a * 1));
    gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_ZB_CLD_SURF2);
    gSPEndDisplayList(gfx);
    gDPSetEnvColor(POLY_XLU_DISP++, (u8)(s8)this->envColors.r, (u8)(s8)this->envColors.g, (u8)(s8)this->envColors.b,
                   (u8)(s8)((f32)alpha * 1));
    gDPSetDither(POLY_XLU_DISP++, G_CD_BAYER);
    POLY_XLU_DISP = SkelAnime_Draw(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   DmChar04_OverrideLimbDraw, NULL, &this->actor, POLY_XLU_DISP);
    CLOSE_DISPS(play->state.gfxCtx);
}
